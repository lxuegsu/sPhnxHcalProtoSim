#include <ostream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <TMath.h>

#include <TROOT.h>
#include <TFile.h>
#include <TH3.h>
#include <TF3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TMinuit.h>
#include <TGraph.h>
#include "TVector3.h"
#include "TVector2.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TChain.h"
#include "math.h"
#include "analysis.h"

using namespace std;

int ntowers = 16;
double pi = 4.0*atan(1.0);

int build_tower(int scintid);
void writeHist(TFile *filename);


int main(int argc, char **argv)
{
        cout<<"//////////////////////////////////////////////"<<endl;
        cout<<endl;
        cout<<"this program start at "<<endl;
        system("date");
        cout<<endl;
        cout<<"//////////////////////////////////////////////"<<endl;

	char *FileInput=0;
	char *FileOutput=0;
	if(argc!=3){
		cout<<"Error: the usage is ./bin/analysis inputfile outputfile"<<endl;
		return 0;
	}
	else{
		FileInput = argv[1];
		FileOutput = argv[2];
	}

	TChain *chain  = new TChain("T");
	chain->Add(FileInput);

	char fspace[256];
	sprintf(fspace,"%s",FileOutput);
	rootfile = new TFile(fspace,"RECREATE");

	//////// initial tree ///////
	mTree = new TTree("T","Tree for HCal G4 Simulation");
	mTree->SetDirectory(rootfile);
 	mTree->Branch("Energy",&mDst.Energy,"Energy/F");
 	mTree->Branch("Phi",&mDst.Phi,"Phi/F");
 	mTree->Branch("Theta",&mDst.Theta,"Theta/F");
 	mTree->Branch("Px",&mDst.Px,"Px/F");
 	mTree->Branch("Py",&mDst.Py,"Py/F");
 	mTree->Branch("Pz",&mDst.Pz,"Pz/F");
 	mTree->Branch("Eleak",&mDst.Eleak,"Eleak/F");
 	mTree->Branch("LCG",&mDst.LCG,"LCG/F");
 	mTree->Branch("SF",mDst.SF,"SF[2]/F");
 	mTree->Branch("Escint",mDst.Escint,"Escint[2]/F");
 	mTree->Branch("Eabs",mDst.Eabs,"Eabs[2]/F");
 	mTree->Branch("edep",mDst.edep,"edep[2][16]/F");


	DST *g4 = new DST();
	g4->SetData(chain);

	int mNEvts = (int)chain->GetEntries();
	cout << "total events:  \t mNEvts = " << mNEvts << endl;

	for (int i=0; i<mNEvts; i++) 
	{ 
		if(i%100==0) cout << "ievent = " << i <<endl;

		chain->GetEntry(i);

		double Energy = g4->cell.Energy;
		double Phi = g4->cell.Phi;
		double Theta = g4->cell.Theta;
		double Px = g4->cell.Px;
		double Py = g4->cell.Py;
		double Pz = g4->cell.Pz;

		double E1D = 0.;   /// energy in HCal inner scint
		double E1L = 0.;   /// energy in HCal inner absorber
		double E2D = 0.;   /// energy in HCal inner scint
		double E2L = 0.;   /// energy in HCal inner absorber
		double r10 = 0.;   /// real CG for H1
		double r20 = 0.;   /// real CG for H2
		double edep10 = 0.; /// total deposited energy in H1
		double edep20 = 0.; /// total deposited energy in H2
		double edepSum[2][16]; /// total deposited energy in each scint tower
		for(int tmpk=0; tmpk<2; tmpk++){
			for(int tmpl=0; tmpl<ntowers; tmpl++){
				edepSum[tmpk][tmpl] = 0.0;
			}
		}

		int nG4SnglHits = g4->cell.nG4SnglHits;
		for(int j=0; j<nG4SnglHits; j++) 
		{
			double x0 = g4->cell.x0[j];
			double x1 = g4->cell.x1[j];
			double y0 = g4->cell.y0[j];
			double y1 = g4->cell.y1[j];
			double z0 = g4->cell.z0[j];
			double z1 = g4->cell.z1[j];

			double radi = sqrt(pow(0.5*(x0+x1),2) + pow(0.5*(y0+y1),2));
			//if(radi <= 183.0 || radi >= 273.) continue;

			TVector3 mom(0.5*(x0+x1), 0.5*(y0+y1), 0.5*(z0+z1));
		 	double eta = mom.PseudoRapidity();

			int layer = g4->cell.layer[j];      /// 1 for H1, 2 for H2
			int scintid = g4->cell.scintid[j];  /// -1 for absorber, 0-256 for scint
			int detid = g4->cell.detid[j];      /// 2 for scint, 3 for absorber
			double edep = g4->cell.edep[j];

			/// scintid>=0 and detid==1 should be equivalent 
			/// itower should be from 0 to 1407 for all hits in scint
			int itower = -999;
			if(detid==1){
				itower = build_tower(scintid);
			//	cout<< "scint ID: "<<scintid<<"\t itower: "<<itower<<endl;
				edepSum[layer-1][itower] += edep;
			}

			if(detid==1){
				if(layer==1) E1D += edep;
				else if(layer==2) E2D += edep;
			}
			else if(detid==2) {
				if(layer==1) E1L += edep;
				else if(layer==2) E2L += edep;
			}

			if(detid==1 || detid==2)
			{
				if(layer==1)
				{
					r10 += radi*edep;
					edep10 += edep;
				}
				else if(layer==2)
				{ 
					r20 += radi*edep;
					edep20 += edep;
				}
			}
		}
		
		r10 = r10/edep10;
		r20 = r20/edep20;

		double EL = Energy-E1D-E2D-E1L-E2L;
                double LCG = (r10*(E1D+E1L)+r20*(E2D+E2L))/(E1D+E1L+E2D+E2L);

		mDst.Energy = Energy;
		mDst.Phi = Phi;
		mDst.Theta = Theta;
		mDst.Px = Px;
		mDst.Py = Py;
		mDst.Pz = Pz;

		mDst.Eleak = EL;
		mDst.LCG = LCG;
		mDst.SF[0] = E1D/(E1D+E1L);
		mDst.SF[1] = E2D/(E2D+E2L);
		mDst.Escint[0] = E1D;
		mDst.Escint[1] = E2D;
		mDst.Eabs[0] = E1L;
		mDst.Eabs[1] = E2L;
		
		for(int k=0; k<2; k++){
			for(int m=0; m<ntowers; m++){
				mDst.edep[k][m] = edepSum[k][m];
			}
		}

		if(mTree) mTree->Fill();
	}

	writeHist(rootfile);

	delete chain;
	return 0;
}

////////-----------------------------------------------------------------------------------
void writeHist(TFile *filename)
{
	if(filename != NULL) filename->Write();
	return;
}

////////-----------------------------------------------------------------------------------
int build_tower(int scintid)
{
	int itower =  -999;

	for(int i=0; i<60; i++)
	{
		if(scintid==sctID[i]) { itower = twrID[i]; break;}
	}

	return itower;
}
