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

double pi = 4.0*atan(1.0);

double tungstenRL = 0.3504; /// tungsten EM radition length in (cm)
double tungstenIL = 9.54; /// tungsten hadronic interaction length in (cm)
double scintRL = 5.534; /// scintillator EM radition length in (cm)
double scintIL = 40.99; /// scintillator hadronic interaction length in (cm)
double steelRL = 1.757; /// Fe EM radition length in (cm)
double steelIL = 16.57; /// Fe hadronic interaction length in (cm)


void writeHist(TFile *filename);
bool myfunction (pair<double,int> i, pair<double,int> j);


int main(int argc, char **argv)
{
        cout<<"//////////////////////////////////////////////"<<endl;
        cout<<endl;
        cout<<"this program start at "<<endl;
        system("date");
        cout<<endl;
        cout<<"//////////////////////////////////////////////"<<endl;


        if(argc != 4 && argc!=3 && argc!=1) return 0;

        char *FileInput=0;
        char *FileOutput=0;
        char *FilePar=0;

        if(argc==1){
                FileInput  = "example.list";
                FileOutput = "example.root";
        }

        if(argc==3){
                FileInput = argv[1];
                FileOutput = argv[2];
        }


	TChain *Chain  = new TChain("T");

	int fileNumber = 0;
	char FileList[512];
	ifstream* inputStream = new ifstream;
	inputStream->open(FileInput);
	if (!(inputStream))
	{
		printf("can not open list file\n");
		return 0;
	}
	for (;inputStream->good();)
	{
		inputStream->getline(FileList,512);

		if(strstr(FileList,".root")==NULL)
		{
			printf("%s is not a root-file address!!!\n",FileList);
			continue;
		}

		if  ( inputStream->good() )
		{
			TFile *ftmp = new TFile(FileList);
			if(!ftmp||!(ftmp->IsOpen())||!(ftmp->GetNkeys()))
			{
				printf(" file %s error in opening!!!\n",FileList);
			}

			else

			{
				printf(" read in file %s\n",FileList);
				Chain->Add(FileList);
				fileNumber++;
			}
			delete ftmp;
		}
	}
	delete inputStream;
	printf(" files read in %d\n",fileNumber);


	char fspace[256];
	sprintf(fspace,"%s.root",FileOutput);
	rootfile = new TFile(fspace,"RECREATE");
	
	hActLengthvsR = new TH2D("hActLengthvsR","hActLengthvsR",440,180.,290.,500,0.,100.);
	hAbsLengthvsR = new TH2D("hAbsLengthvsR","hAbsLengthvsR",440,180.,290.,500,0.,100.);
	pActLengthvsR = new TProfile("pActLengthvsR","pActLengthvsR",440,180.,290.,0.,100.);
	pAbsLengthvsR = new TProfile("pAbsLengthvsR","pAbsLengthvsR",440,180.,290.,0.,100.);
	hRinRLvsR = new TH2D("hRinRLvsR","hRinRLvsR",440,180.,290.,500,0.,50.);
	pRinRLvsR = new TProfile("pRinRLvsR","pRinRLvsR",440,180.,290.,0.,50.);
	hRinILvsR = new TH2D("hRinILvsR","hRinILvsR",440,180.,290.,500,0.,50.);
	pRinILvsR = new TProfile("pRinILvsR","pRinILvsR",440,180.,290.,0.,50.);

	DST *g4 = new DST();
	g4->SetData(Chain);

	int mNEvts = (int)Chain->GetEntries();

	cout << "total events:  \t mNEvts = " << mNEvts << endl;

	for (int i=0; i<mNEvts; i++) 
	{ 
		if(i%100==0) cout << "ievent = " << i <<endl;

		Chain->GetEntry(i);

		int nhits = g4->cell.nG4SnglHits;
		vector< pair<double,int> > vect;
		for(int j=0; j<nhits; j++) 
		{
			//int detid = g4->cell.detid[j];
			//int layer = g4->cell.layer[j];

			double x0 = g4->cell.x0[j];
			double y0 = g4->cell.y0[j];
			double z0 = g4->cell.z0[j];
			double x1 = g4->cell.x1[j];
			double y1 = g4->cell.y1[j];
			double z1 = g4->cell.z1[j];

			double r = sqrt( pow(0.5*(x0+x1),2) + pow(0.5*(y0+y1),2) + pow((z0+z1),2.) );
			double minr = sqrt( pow(x0,2) + pow(y0,2) + pow(z0,2) );
			double maxr = sqrt( pow(x1,2) + pow(y1,2) + pow(z1,2) );

			if( maxr<minr ) cout << "rmin = "<< minr << "\t rmax = "<<  maxr << endl;
			//if(minr>=maxr) continue;
		//	cout << m <<"\t hit radius = "<< r << "\t hit length = "<< sqrt(pow((x0-x1),2.)+pow((y0-y1),2.))<<"\t hit detid =  "<< detid << endl;

			double length = sqrt(pow((x0-x1),2.)+pow((y0-y1),2.) + pow((z0-z1),2) ) ;

			pair<double,int> tmp;
			tmp.first = maxr;
			tmp.second = j;
			vect.push_back(tmp);
		}

		sort(vect.begin(), vect.end(), myfunction);

		vector< pair<double,int> >::iterator it;
		double dActL=0.;
		double dAbsL=0.;
		double dLinRL=0.;
		double dLinIL=0.;

		for (it=vect.begin(); it!=vect.end(); ++it){
			int detid = g4->cell.detid[(*it).second];
			double x0 = g4->cell.x0[(*it).second];
			double y0 = g4->cell.y0[(*it).second];
			double z0 = g4->cell.z0[(*it).second];
			double x1 = g4->cell.x1[(*it).second];
			double y1 = g4->cell.y1[(*it).second];
			double z1 = g4->cell.z1[(*it).second];
			double length  = sqrt( pow((x0-x1),2.) + pow((y0-y1),2.) + pow((z0-z1),2.) ) ;

			cout << "first = " << (*it).first <<"\t second = "<< (*it).second << "\t detid = "<< detid <<endl;
	
			if( detid==1 ){
				dActL += length;
				hActLengthvsR->Fill((*it).first, dActL);
				pActLengthvsR->Fill((*it).first, dActL);
			}
			else if( detid==2 ){
				dAbsL += length;
				hAbsLengthvsR->Fill((*it).first, dAbsL);
				pAbsLengthvsR->Fill((*it).first, dAbsL);
			}

			if(detid==1 ) dLinRL += length/scintRL;
			else if(detid==2) dLinRL += length/steelRL;
			if (detid==1 || detid==2) hRinRLvsR->Fill((*it).first, dLinRL);
			if (detid==1 || detid==2) pRinRLvsR->Fill((*it).first, dLinRL);

			if(detid==1) dLinIL += length/scintIL;
			else if(detid==2) dLinIL += length/steelIL;
			if (detid==1 || detid==2) hRinILvsR->Fill((*it).first, dLinIL);
			if (detid==1 || detid==2) pRinILvsR->Fill((*it).first, dLinIL);

		}

	}


	writeHist(rootfile);

	delete Chain;

	return 0;


}

void writeHist(TFile *filename)
{
	if(filename != NULL) filename->Write();
	return;
}

bool myfunction (pair<double,int> i, pair<double,int> j) { return ( i.first < j.first ); }
