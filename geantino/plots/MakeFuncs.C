#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

void MakeFuncs ()
{
        gROOT->Reset();
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(000);
	gStyle->SetPalette(1);
        gStyle->SetOptDate(0);
        gStyle->SetOptTitle(0000);

        gStyle->SetCanvasColor(kWhite);
        gStyle->SetFrameFillStyle(1001);
        gStyle->SetFrameFillColor(kWhite);
        gStyle->SetPadBorderMode(0);
        gStyle->SetPadColor(kWhite);
        gStyle->SetStatColor(kWhite);
        gStyle->SetPadTickX(1);
        gStyle->SetPadTickY(1);
//      gStyle->SetLabelSize(.05,"X");
//      gStyle->SetLabelSize(.05,"Y");
        gStyle->SetLabelColor(1,"X");
        gStyle->SetLabelColor(1,"Y");


	///////open the root files////////
	///// positive 100GeV 0T magnet field muon
	TFile *f1 = new TFile("../output/geantino.root");
        TProfile *pGeantinoTRinRLvsR = (TProfile *)f1->Get("pRinRLvsR");
        TProfile *pGeantinoTRinILvsR = (TProfile *)f1->Get("pRinILvsR");


	///////create plots////////
        TCanvas *c1 = new TCanvas("c1","c1",700,500);
        c1->cd();
        c1->SetLeftMargin(0.15);
        c1->SetBottomMargin(0.15);
        c1->SetGridy(0);
        c1->SetGridx(0);

	
	///// geantino
	////--------------------------------------------------------------------////
	char RILFile[256];
	sprintf(RILFile, "TabulateRadiandInteLength.h");
	ofstream RILData;
	RILData.open(RILFile);

	double RMin = 183.; 	double RMax=273.;
        double nBins = pGeantinoTRinRLvsR->GetNbinsX();
	int lowbin = pGeantinoTRinRLvsR->GetXaxis()->FindBin(183.);
	int upbin = pGeantinoTRinRLvsR->GetXaxis()->FindBin(273.);
	
	RILData<<"double RinRadiLengthFunc(double *x, double *par)"<<endl;
	RILData<<"{"<<endl;
	RILData<<"double RMin = "<<RMin<<";"<<endl;
	RILData<<"double RMax = "<<RMax<<";"<<endl;
	RILData<<"const int nBins = "<<upbin-lowbin<<";"<<endl;
	RILData<<"double binWidth = "<<"(RMax-RMin)/nBins;"<<endl;
	RILData<<""<<endl;
	RILData<<"double RinRadiLength[nBins+1]={";
	for(int i=lowbin; i<upbin+1; i++)
	{
		if(i==upbin)RILData<<pGeantinoTRinRLvsR->GetBinContent(i);
		else RILData<<pGeantinoTRinRLvsR->GetBinContent(i)<<", ";
	}
	RILData<<" };"<<endl;
	RILData<<""<<endl;
	RILData<<""<<endl;

	RILData<<"int iBin = (int)((x[0]-RMin)/binWidth);"<<endl;
	RILData<<"double dR = x[0] - RMin - iBin*binWidth;"<<endl;
	RILData<<"return ((1.-dR/binWidth)*RinRadiLength[iBin] + dR/binWidth*RinRadiLength[iBin+1]);"<<endl;
	RILData<<"}"<<endl;
	

	RILData<<""<<endl;
	RILData<<""<<endl;

	RILData<<"double RinInteLengthFunc(double *x, double *par)"<<endl;
	RILData<<"{"<<endl;
	RILData<<"double RMin = "<<RMin<<";"<<endl;
	RILData<<"double RMax = "<<RMax<<";"<<endl;
	RILData<<"const int nBins = "<<upbin-lowbin<<";"<<endl;
	RILData<<"double binWidth = "<<"(RMax-RMin)/nBins;"<<endl;
	RILData<<""<<endl;
	RILData<<"double RinInteLength[nBins+1]={";
	for(int i=lowbin; i<upbin+1; i++)
	{
		if(i==upbin)RILData<<pGeantinoTRinILvsR->GetBinContent(i);
		else RILData<<pGeantinoTRinILvsR->GetBinContent(i)<<", ";
	}
	RILData<<" };"<<endl;
	RILData<<""<<endl;
	RILData<<""<<endl;
	RILData<<"int iBin = (int)((x[0]-RMin)/binWidth);"<<endl;
	RILData<<"double dR = x[0] - RMin - iBin*binWidth;"<<endl;
	RILData<<"return ((1.-dR/binWidth)*RinInteLength[iBin] + dR/binWidth*RinInteLength[iBin+1]);"<<endl;
	RILData<<"}"<<endl;
	

	
}
