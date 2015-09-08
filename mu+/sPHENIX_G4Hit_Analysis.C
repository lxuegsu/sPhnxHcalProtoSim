#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <TMath.h>
#include <TH1.h>

using namespace std;



void sPHENIX_G4Hit_Analysis( char* InputFile = "input/list",
                               char* OutputFile = "output/mu-.root" )
{
        cout<<"//////////////////////////////////////////////"<<endl;
        cout<<endl;
        cout<<"this program start at "<<endl;
        system("date");
        cout<<endl;
        cout<<"//////////////////////////////////////////////"<<endl;

	gROOT->Reset();
	float PI = TMath::Pi();
	const int MAXHITS = 500000;


	TChain *chain  = new TChain("T");
        int fileNumber = 0;
        char FileList[512];
        ifstream* inputStream = new ifstream;
        inputStream->open(InputFile);

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
				chain->Add(FileList);
				fileNumber++;
			}
			delete ftmp;
		}
	}
	delete inputStream;
	printf(" files read in %d\n",fileNumber);


	//Declaration of leaves types
	Float_t         Energy;
	Float_t         Phi;
	Float_t         Theta;
	Float_t         Px;
	Float_t         Py;
	Float_t         Pz;
	UInt_t          nG4SnglHits;
	Int_t           G4SnglHits_;

	Int_t           detid[MAXHITS];
	Int_t           layer[MAXHITS];
	Int_t           scintid[MAXHITS];
	Int_t           trackid[MAXHITS];
	Float_t         x0[MAXHITS];
	Float_t         y0[MAXHITS];
	Float_t         z0[MAXHITS];
	Float_t         x1[MAXHITS];
	Float_t         y1[MAXHITS];
	Float_t         z1[MAXHITS];
	Float_t         edep[MAXHITS];


	// Set branch addresses
	chain->SetMakeClass(1);
	chain->SetBranchStatus("*",0);  // disable all branches
	chain->SetBranchAddress("Energy", &Energy);
	chain->SetBranchAddress("Phi", &Phi);
	chain->SetBranchAddress("Theta", &Theta);
	chain->SetBranchAddress("Px", &Px);
	chain->SetBranchAddress("Py", &Py);
	chain->SetBranchAddress("Pz", &Pz);
	chain->SetBranchAddress("nG4SnglHits", &nG4SnglHits);
	chain->SetBranchAddress("G4SnglHits", &G4SnglHits_);

	chain->SetBranchAddress("G4SnglHits.detid", detid);
	chain->SetBranchAddress("G4SnglHits.layer", layer);
	chain->SetBranchAddress("G4SnglHits.scintid", scintid);
	chain->SetBranchAddress("G4SnglHits.trackid", trackid);
	chain->SetBranchAddress("G4SnglHits.x0", x0);
	chain->SetBranchAddress("G4SnglHits.y0", y0);
	chain->SetBranchAddress("G4SnglHits.z0", z0);
	chain->SetBranchAddress("G4SnglHits.x1", x1);
	chain->SetBranchAddress("G4SnglHits.y1", y1);
	chain->SetBranchAddress("G4SnglHits.z1", z1);
	chain->SetBranchAddress("G4SnglHits.edep", edep);
		

	char fspace[256];
	TFile *rootfile = new TFile(OutputFile,"RECREATE");

	TH1D *hTotalSF = new TH1D("hTotalSF","Total SF",100,0.,0.1);
        TH1D *hHCalInnerSF = new TH1D("hHCalInnerSF","HCal Inner SF",100,0.,0.1);
        TH1D *hHCalOuterSF = new TH1D("hHCalOuterSF","HCal Outer SF",100,0.,0.1);
        TH2D *hHCalYXScint = new TH2D("hHCalYXScint","hits in scintillator",480,170.,290.,400,-15.,85);
        TH2D *hHCalYXAbsor = new TH2D("hHCalYXAbsor","hits in absorber",480,170.,290.,400,-15.,85);

	Int_t mNEvts = (Int_t)chain->GetEntries();
        cout << "total number of events:  \t mNEvts = " << mNEvts << endl;

	for (int i=0; i<mNEvts; i++) 
	{ 
		if(i%100==0) cout << "processing: "<< i <<" event: "<<endl;
		chain->GetEntry(i);

		TLorentzVector particle(Px,Py,Pz,Energy);
		double mass = particle.M();

		double E1D = 0.;
		double E1L = 0.;
		double E2D = 0.;
		double E2L = 0.;

		for (int j=0; j<nG4SnglHits; j++){
			if(detid[j]==1){
				if(layer[j]==1) { E1D += edep[j]; }
				else if(layer[j]==2) { E2D += edep[j]; }
				hHCalYXScint->Fill(x0[j], y0[j]);
			}
			else if(detid[j]==2) {
				if(layer[j]==1) { E1L += edep[j]; }
				else if(layer[j]==2) { E2L += edep[j]; }
				hHCalYXAbsor->Fill(x0[j], y0[j]);
			}
		}
		hHCalInnerSF->Fill( E1D/(E1D+E1L) );
                hHCalOuterSF->Fill( E2D/(E2D+E2L) );
		hTotalSF->Fill( (E1D+E2D)/(E1D+E2D+E1L+E2L) );

	}

	rootfile->Write();
        rootfile->Close();

	return;
}
