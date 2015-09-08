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
double R1 = 198.;
double R2 = 243.;

/// zero order approximation
double sf10 = 0.058; /// HCal Inner 
double sf20 = 0.019; /// HCal Outer

#ifdef CORRECTION
/// first order approximation
int innerHCalInitE[8];
int innerHCalnPara[8];
double innerHCalAsyE[8][100];
double innerHCalSF[8][100];

int outerHCalInitE[8];
int outerHCalnPara[8];
double outerHCalAsyE[8][100];
double outerHCalSF[8][100];

int ELeakInitE[8];
int ELeaknPara[8];
double ELeakAsyE[8][100];
double ELeak[8][100];
#endif

void writeHist(TFile *filename);

#ifdef CORRECTION
void readPara();
double extrapSF(int energy, double CG0, int layer);
double extrapEL(int energy, double CG0);
#endif

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
        if(argc==1){
                FileInput  = "test.list";
                FileOutput = "test.root";
        }
        if(argc==3){
                FileInput = argv[1];
                FileOutput = argv[2];
        }


	#ifdef CORRECTION
	readPara();
	#endif

	TChain *chain  = new TChain("T");

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
				chain->Add(FileList);
				fileNumber++;
			}
			delete ftmp;
		}
	}
	delete inputStream;
	printf(" files read in %d\n",fileNumber);

	int index[8] = { 4, 8, 16, 25, 32, 40, 50, 60 };

	char fspace[256];
	sprintf(fspace,"%s",FileOutput);
	rootfile = new TFile(fspace,"RECREATE");

	//// zero order approximation	
        hRecoE0vsInitE = new TH2D("hRecoE0vsInitE","hRecoE0vsInitE",1000,0.,100.,100,0.,100.);
        hRecoE10vsInitE = new TH2D("hRecoE10vsInitE","hRecoE10vsInitE",1000,0.,100.,100,0.,100.);
        hRecoE20vsInitE = new TH2D("hRecoE20vsInitE","hRecoE20vsInitE",1000,0.,100.,100,0.,100.);
        hELeakvsInitE = new TH2D("hELeakvsInitE","hELeakvsInitE",100,0.,100.,1000,0.,100.);
        hTowerEH1vsInitE = new TH2D("hTowerEH1vsInitE","hTowerEH1vsInitE",100,0.,100.,1000,0.,0.5);
        hTowerEH2vsInitE = new TH2D("hTowerEH2vsInitE","hTowerEH2vsInitE",100,0.,100.,1000,0.,0.5);

	char title[256]; 
	for(int i=0; i<8; i++)
	{
                sprintf(title,"hAsyE1vsLCG_%iGeV",index[i]);
                hAsyE1vsLCG[i] = new TH2D(title,title,180,183.,273.,100,-1.,1.);
                sprintf(title,"hAsyE2vsLCG_%iGeV",index[i]);
                hAsyE2vsLCG[i] = new TH2D(title,title,180,183.,273.,200,-50.,50.);
                sprintf(title,"hAsyE2vsAsyE1_%iGeV",index[i]);
                hAsyE2vsAsyE1[i] = new TH2D(title,title,100,-1.,1.,200,-50.,50.);

                sprintf(title,"hSF11vsAsyE1_%iGeV",index[i]);
                hSF11vsAsyE1[i] = new TH2D(title,title,100,-1.,1.,100,0.,0.1);
                sprintf(title,"hSF21vsAsyE1_%iGeV",index[i]);
                hSF21vsAsyE1[i] = new TH2D(title,title,100,-1.,1.,100,0.,0.1);
                sprintf(title,"hSF11vsAsyE2_%iGeV",index[i]);
                hSF11vsAsyE2[i] = new TH2D(title,title,100,-50.,50.,100,0.,0.1);
                sprintf(title,"hSF21vsAsyE2_%iGeV",index[i]);
                hSF21vsAsyE2[i] = new TH2D(title,title,100,-50.,50.,100,0.,0.1);
		
		sprintf(title,"hH1TowerYZ_%iGeV",index[i]);
		hH1TowerYZ[i] = new TH2D(title,title,40,0.,4.,40,0.,4.);
		sprintf(title,"hH2TowerYZ_%iGeV",index[i]);
		hH2TowerYZ[i] = new TH2D(title,title,40,0.,4.,40,0.,4.);

                sprintf(title,"hELeakvsAsyE1_%iGeV",index[i]);
                hELeakvsAsyE1[i] = new TH2D(title,title,100,-1.,1.,100,0.,100.);
                sprintf(title,"hELeakvsAsyE2_%iGeV",index[i]);
                hELeakvsAsyE2[i] = new TH2D(title,title,100,-50.,50.,100,0.,100.);

                sprintf(title,"hTotalEvsAsyE1_%iGeV",index[i]);
		hTotalEvsAsyE1[i] = new TH2D(title,title,400,-1.,1.,176,-0.2,2.);
	}

	//// first order approximation	
	#ifdef CORRECTION
	hRecoE1vsInitE = new TH2D("hRecoE1vsInitE","hRecoE1vsInitE",400,0.,100.,60,0.,60.);
	hRecoE11vsInitE = new TH2D("hRecoE11vsInitE","hRecoE11vsInitE",400,0.,100.,60,0.,60.);
	hRecoE21vsInitE = new TH2D("hRecoE21vsInitE","hRecoE21vsInitE",400,0.,100.,60,0.,60.);
	for(int i=0; i<8; i++)
	{
		sprintf(title,"hRecoE1vsAsyE_%iGeV",index[i]);
		hRecoE1vsAsyE[i] = new TH2D(title,title,100,-1.,1.,100,0.,100.);
		sprintf(title,"hRecoE1LvsAsyE_%iGeV",index[i]);
		hRecoE1LvsAsyE[i] = new TH2D(title,title,100,-1.,1.,100,0.,100.);
		sprintf(title,"hRecoE11vsAsyE_%iGeV",index[i]);
		hRecoE11vsAsyE[i] = new TH2D(title,title,100,-1.,1.,100,0.,100.);
		sprintf(title,"hRecoE21vsAsyE_%iGeV",index[i]);
		hRecoE21vsAsyE[i] = new TH2D(title,title,100,-1.,1.,100,0.,100.);
	}
	hRecoE1LvsInitE = new TH2D("hRecoE1LvsInitE","hRecoE1LvsInitE",400,0.,100.,60,0.,60.);
	#endif


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
		double Eleak = g4->cell.Eleak;
		double LCG = g4->cell.LCG;
		double SF1 = g4->cell.SF[0];
		double SF2 = g4->cell.SF[1];
		double Escint1 = g4->cell.Escint[0];
		double Escint2 = g4->cell.Escint[1];
		double AsyE1 = (Escint2-Escint1)/(Escint2+Escint1);
		double AsyE2 = (log(Escint2)-log(Escint1))/(Escint2+Escint1);
		double Eabs1 = g4->cell.Eabs[0];
		double Eabs2 = g4->cell.Eabs[1];

		double E01 = Escint1/sf10;
		double E02 = Escint2/sf20;

		hRecoE0vsInitE->Fill(E01+E02,Energy);
		hRecoE10vsInitE->Fill(E01,Energy);
		hRecoE20vsInitE->Fill(E02,Energy);

		hELeakvsInitE->Fill(Energy,Eleak*100/Energy);

		float sixw(0.), siyw(0.), siw(0.), soxw(0.), soyw(0.), sow(0.);
		for(int k=0; k<16; k++){
			if(g4->cell.edep[0][k]>0.) {
				hTowerEH1vsInitE->Fill(Energy,g4->cell.edep[0][k]);
				siw += g4->cell.edep[0][k];
				sixw += ((float)(k%4)+0.5)*g4->cell.edep[0][k];
				siyw += ((float)(k/4)+0.5)*g4->cell.edep[0][k];
			}
			if(g4->cell.edep[1][k]>0.) {
				hTowerEH2vsInitE->Fill(Energy,g4->cell.edep[1][k]);
				sow += g4->cell.edep[1][k];
				soxw += ((float)(k%4)+0.5)*g4->cell.edep[1][k];
				soyw += ((float)((k)/4)+0.5)*g4->cell.edep[1][k];
			}
		}

		if (siw>0.) {
			sixw = sixw/siw;
			siyw = siyw/siw;
		}
		if (sow>0.) { 
			soxw = soxw/sow;
			soyw = soyw/sow;
		}

		for(int j=0;j<8;j++) 
		{
			if( Energy>index[j]-0.5 && Energy<index[j]+0.5)
			{
				hAsyE1vsLCG[j]->Fill(LCG,AsyE1);
				hAsyE2vsLCG[j]->Fill(LCG,AsyE2);
				hAsyE2vsAsyE1[j]->Fill(AsyE1,AsyE2);
				hELeakvsAsyE1[j]->Fill(AsyE1,Eleak*100./Energy);
				hELeakvsAsyE2[j]->Fill(AsyE2,Eleak*100./Energy);
				hSF11vsAsyE1[j]->Fill(AsyE1,SF1);
				hSF21vsAsyE1[j]->Fill(AsyE1,SF2);
				hSF11vsAsyE2[j]->Fill(AsyE2,SF1);
				hSF21vsAsyE2[j]->Fill(AsyE2,SF2);
				hH1TowerYZ[j]->Fill(sixw,siyw);
				hH2TowerYZ[j]->Fill(soxw,soyw);
				hTotalEvsAsyE1[j]->Fill(AsyE1,Escint2+Escint1);
			}
		}
		
		#ifdef CORRECTION
		 ///// AsyE correction, first order appoximation /////
		double CorrInnerSF = extrapSF(Energy,AsyE1,1);
                double CorrOuterSF = extrapSF(Energy,AsyE1,2);
		double CorrEL = extrapEL(Energy,AsyE1);
		//cout<< "AsyE1 = "<< AsyE1 <<"\t CorrCEMCSF = "<<CorrCEMCSF << "\t CorrInnerSF = "<< CorrInnerSF << "\t CorrOuterSF = " << CorrOuterSF <<"\t CorrEL = " <<CorrEL <<endl;
		if(CorrInnerSF < 0. || CorrOuterSF < 0.) continue;

		double E11 = Escint1/CorrInnerSF;
		double E21 = Escint2/CorrOuterSF;
		double E1 = E11+E21;
		//cout<<"E1 = "<< E1 << "\t Energy = " << Energy <<endl;
		hRecoE1vsInitE->Fill(E1,Energy);
		hRecoE11vsInitE->Fill(E11,Energy);
		hRecoE21vsInitE->Fill(E21,Energy);

		for(int j=0;j<8;j++)
		{
			if( Energy>index[j]-0.5 && Energy<index[j]+0.5)
			{
				hRecoE1vsAsyE[j]->Fill(AsyE1,E1);
				hRecoE1LvsAsyE[j]->Fill(AsyE1,E1+CorrEL);
				hRecoE11vsAsyE[j]->Fill(AsyE1,E11);
				hRecoE21vsAsyE[j]->Fill(AsyE1,E21);
			}
		}
		if(CorrEL>0.) hRecoE1LvsInitE->Fill(E1+CorrEL,Energy);
		#endif

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

#ifdef CORRECTION
////////-----------------------------------------------------------------------------------
void readPara()
{
	int index[8] = { 4, 8, 10, 16, 24, 32, 40, 50 };

	char innerpara[256];
	sprintf(innerpara,"./input/innerHCal_%s.dat","pi+_eta0_0T");
	for(int i=0; i<8; i++){
		innerHCalInitE[i]=0;
		innerHCalnPara[i]=0;
		for (int j=0; j<100; j++) innerHCalAsyE[i][j]=0.;
		for (int j=0; j<100; j++) innerHCalSF[i][j]=0.;
	}
	fstream innerData;
	innerData.open(innerpara);
	for(int i=0;i<8;i++){
		innerData>>innerHCalInitE[i]>>innerHCalnPara[i];
		for(int j=0; j<innerHCalnPara[i]; j++) {
			innerData>>innerHCalAsyE[i][j];
		}
		for(int j=0; j<innerHCalnPara[i]; j++) {
			innerData>>innerHCalSF[i][j];
		}
	}

	for (int i=0; i<8; i++) {
		cout << "Energy = "<< innerHCalInitE[i] <<"\t Inner nPara = "<< innerHCalnPara[i] <<endl;
		for(int j=0; j<100; j++) if(innerHCalAsyE[i][j]) cout<< "Inner AsyE = "<<index[i]<<"\t "<<innerHCalAsyE[i][j] <<"\t Inner SF = "<<innerHCalSF[i][j]<<endl;
	}

	char outerpara[256];
	sprintf(outerpara,"./input/outerHCal_%s.dat","pi+_eta0_0T");
	for(int i=0; i<8; i++){
		outerHCalInitE[i]=0;
		outerHCalnPara[i]=0;
		for (int j=0; j<100; j++) outerHCalAsyE[i][j]=0.;
		for (int j=0; j<100; j++) outerHCalSF[i][j]=0.;
	}
	fstream outerData;
	outerData.open(outerpara);
	for(int i=0;i<8;i++){
		outerData>>outerHCalInitE[i]>>outerHCalnPara[i];
		for(int j=0; j<outerHCalnPara[i]; j++) {
			outerData>>outerHCalAsyE[i][j];
                }
		for(int j=0; j<outerHCalnPara[i]; j++) {
			outerData>>outerHCalSF[i][j];
		}
	}

	for (int i=0; i<8; i++){
		cout << "Energy = "<< outerHCalInitE[i] <<"\t Outer nPara = "<< outerHCalnPara[i] <<endl;
		for(int j=0; j<100; j++) if(outerHCalAsyE[i][j]) cout<< "Outer AsyE = "<< index[i] <<"\t "<<outerHCalAsyE[i][j] <<"\t Outer SF = "<<outerHCalSF[i][j]<<endl;
	}

	char eleakpara[256];
	sprintf(eleakpara,"./input/ELeak_%s.dat","pi+_eta0_0T");
	for(int i=0; i<8; i++){
		ELeakInitE[i]=0;
		ELeaknPara[i]=0;
		for (int j=0; j<100; j++) ELeakAsyE[i][j]=0.;
		for (int j=0; j<100; j++) ELeak[i][j]=0.;
	}
	fstream eleakData;
	eleakData.open(eleakpara);
	for(int i=0;i<8;i++){
		eleakData>>ELeakInitE[i]>>ELeaknPara[i];
		for(int j=0; j<ELeaknPara[i]; j++) {
			eleakData>>ELeakAsyE[i][j];
		}
		for(int j=0; j<ELeaknPara[i]; j++) {
			eleakData>>ELeak[i][j];
		}
	}
	for (int i=0; i<8; i++){
		cout << "Energy = "<< ELeakInitE[i] <<"\t Energy Leakage nPara = "<< ELeaknPara[i] <<endl;
		for(int j=0; j<100; j++) if(ELeakAsyE[i][j]) cout<< "Energy Leakage AsyE = "<< index[i] <<"\t "<<ELeakAsyE[i][j] <<"\t Energy Leakage = "<<ELeak[i][j]<<endl;
	}
}


////////-----------------------------------------------------------------------------------
double extrapSF(int energy, double AsyE, int layer)
{

  double corrSF = -999.;

   if(layer==1){
    for(int i=0;i<8;i++){
    int nPara = 0; int iBin = -1;
       if(energy == innerHCalInitE[i]){
         nPara = innerHCalnPara[i];
         for(int j=0; j<nPara-1; j++){
            if(AsyE>=innerHCalAsyE[i][j] && AsyE<innerHCalAsyE[i][j+1]){
                        iBin = j;
                        break;
                        }
                }
            if(iBin>=0 && iBin<nPara){
              double x1 = innerHCalAsyE[i][iBin];
              double x2 = innerHCalAsyE[i][iBin+1];
              double y1 = innerHCalSF[i][iBin];
              double y2 = innerHCalSF[i][iBin+1];
              corrSF = y1 + (AsyE-x1)*(y2-y1)/(x2-x1);
                }
          }
        }
     }
  else if(layer==2){
      for(int i=0;i<8;i++){
        int nPara = 0; int iBin = -1;
        if(energy == outerHCalInitE[i]){
           nPara = outerHCalnPara[i];
          for(int j=0; j<nPara-1; j++){
             if(AsyE>=outerHCalAsyE[i][j] && AsyE<outerHCalAsyE[i][j+1]){
                iBin = j;
                break;
                        }
                      }
           if(iBin>=0 && iBin<nPara){
                double x1 = outerHCalAsyE[i][iBin];
                double x2 = outerHCalAsyE[i][iBin+1];
                double y1 = outerHCalSF[i][iBin];
                double y2 = outerHCalSF[i][iBin+1];
                corrSF = y1 + (AsyE-x1)*(y2-y1)/(x2-x1);
                }
               }
            }
     }

return corrSF;

}



////////-----------------------------------------------------------------------------------
double extrapEL(int energy, double AsyE)
{
	double corrEL = -999.;

	for(int i=0;i<8;i++){
		int nPara = 0; int iBin = -1;
		if(energy == ELeakInitE[i]){
			nPara = ELeaknPara[i];
			for(int j=0; j<nPara-1; j++){
				if(AsyE>=ELeakAsyE[i][j] && AsyE<ELeakAsyE[i][j+1]){
					iBin = j;
					break;
				}
			}
			if(iBin>=0 && iBin<nPara){
				double x1 = ELeakAsyE[i][iBin];
				double x2 = ELeakAsyE[i][iBin+1];
				double y1 = ELeak[i][iBin];
				double y2 = ELeak[i][iBin+1];
				corrEL = y1 + (AsyE-x1)*(y2-y1)/(x2-x1);
			}
		}
	}

	return corrEL;
}
#endif
