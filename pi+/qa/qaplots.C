#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

void qaplots()
{
        gROOT->Reset();
        gStyle->SetOptStat(0);
        gStyle->SetOptFit(111);
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


	///////----------open the root files----------////////
	int index[8] = { 4, 8, 16, 25, 32, 40, 50, 60 };
	TFile *f1 = new TFile("../output/pi+.root");
	TH2D *hTowerEH1vsInitE = (TH2D *)f1->Get("hTowerEH1vsInitE");
	TH2D *hTowerEH2vsInitE = (TH2D *)f1->Get("hTowerEH2vsInitE");
	TH1D *hTowerEH1[8];
	TH1D *hTowerEH2[8];
	char title[256];
	for( int i=0; i<8; i++)
        {
                sprintf(title,"hTowerEH1Px_%iGeV",index[i]);
                hTowerEH1[i] = (TH1D *) hTowerEH1vsInitE->ProjectionY(title,index[i]+1,index[i]+1);
		hTowerEH1[i]->Rebin(8);
                sprintf(title,"hTowerEH2Px_%iGeV",index[i]);
                hTowerEH2[i] = (TH1D *) hTowerEH2vsInitE->ProjectionY(title,index[i]+1,index[i]+1);
		hTowerEH2[i]->Rebin(10);
        }

	TH2D *hAsyE1vsLCG[8];
	TProfile *pAsyE1vsLCG[8];
	TH2D *hAsyE2vsLCG[8];
	TProfile *pAsyE2vsLCG[8];
	TH2D *hAsyE2vsAsyE1[8];
	TProfile *pAsyE2vsAsyE1[8];
	char title[256];
	for( int i=0; i<8; i++)
        {
		sprintf(title,"hAsyE1vsLCG_%iGeV",index[i]);
		hAsyE1vsLCG[i] = (TH2D *)f1->Get(title);
                pAsyE1vsLCG[i] = (TProfile *) hAsyE1vsLCG[i]->ProfileX();
		pAsyE1vsLCG[i]->Rebin(4);

		sprintf(title,"hAsyE2vsLCG_%iGeV",index[i]);
		hAsyE2vsLCG[i] = (TH2D *)f1->Get(title);
                pAsyE2vsLCG[i] = (TProfile *) hAsyE2vsLCG[i]->ProfileX();
		pAsyE2vsLCG[i]->Rebin(4);

		sprintf(title,"hAsyE2vsAsyE1_%iGeV",index[i]);
		hAsyE2vsAsyE1[i] = (TH2D *)f1->Get(title);
                pAsyE2vsAsyE1[i] = (TProfile *) hAsyE2vsAsyE1[i]->ProfileX();
		pAsyE2vsAsyE1[i]->Rebin(4);
        }

	TH2D *hSF11vsAsyE1[8];
        TProfile *pSF11vsAsyE1[8];
	TH2D *hSF21vsAsyE1[8];
        TProfile *pSF21vsAsyE1[8];
	TH2D *hSF11vsAsyE2[8];
        TProfile *pSF11vsAsyE2[8];
	TH2D *hSF21vsAsyE2[8];
        TProfile *pSF21vsAsyE2[8];
        char title[256];
        for( int i=0; i<8; i++)
        {
                sprintf(title,"hSF11vsAsyE1_%iGeV",index[i]);
                hSF11vsAsyE1[i] = (TH2D *)f1->Get(title);
                pSF11vsAsyE1[i] = (TProfile *) hSF11vsAsyE1[i]->ProfileX();
                pSF11vsAsyE1[i]->Rebin(4);

                sprintf(title,"hSF21vsAsyE1_%iGeV",index[i]);
                hSF21vsAsyE1[i] = (TH2D *)f1->Get(title);
                pSF21vsAsyE1[i] = (TProfile *) hSF21vsAsyE1[i]->ProfileX();
                pSF21vsAsyE1[i]->Rebin(4);

                sprintf(title,"hSF11vsAsyE2_%iGeV",index[i]);
                hSF11vsAsyE2[i] = (TH2D *)f1->Get(title);
                pSF11vsAsyE2[i] = (TProfile *) hSF11vsAsyE2[i]->ProfileX();
                if(i<3) pSF11vsAsyE2[i]->Rebin(4);
                else pSF11vsAsyE2[i]->Rebin(2);

                sprintf(title,"hSF21vsAsyE2_%iGeV",index[i]);
                hSF21vsAsyE2[i] = (TH2D *)f1->Get(title);
                pSF21vsAsyE2[i] = (TProfile *) hSF21vsAsyE2[i]->ProfileX();
                if(i<3) pSF21vsAsyE2[i]->Rebin(4);
		else pSF21vsAsyE2[i]->Rebin(2);
        }

	TH2D *hELeakvsAsyE1[8];
	TProfile *pELeakvsAsyE1[8];
	TH2D *hELeakvsAsyE2[8];
	TProfile *pELeakvsAsyE2[8];
	char title[256];
	for( int i=0; i<8; i++)
	{
		sprintf(title,"hELeakvsAsyE1_%iGeV",index[i]);
		hELeakvsAsyE1[i] = (TH2D *)f1->Get(title);
		pELeakvsAsyE1[i] = (TProfile *) hELeakvsAsyE1[i]->ProfileX();
		pELeakvsAsyE1[i]->Rebin(4);

		sprintf(title,"hELeakvsAsyE2_%iGeV",index[i]);
		hELeakvsAsyE2[i] = (TH2D *)f1->Get(title);
		pELeakvsAsyE2[i] = (TProfile *) hELeakvsAsyE2[i]->ProfileX();
		if(i<3) pELeakvsAsyE2[i]->Rebin(4);
		else pELeakvsAsyE2[i]->Rebin(2);
	}


	TH2D *hH1TowerYZ[8];
	TH2D *hH2TowerYZ[8];
	TH2D *hTotalEvsAsyE1[8];
	char title[256];
	for( int i=0; i<8; i++)
	{
		sprintf(title,"hH1TowerYZ_%iGeV",index[i]);
		hH1TowerYZ[i] = (TH2D *)f1->Get(title);
		sprintf(title,"hH2TowerYZ_%iGeV",index[i]);
		hH2TowerYZ[i] = (TH2D *)f1->Get(title);
		sprintf(title,"hTotalEvsAsyE1_%iGeV",index[i]);
		hTotalEvsAsyE1[i] = (TH2D *)f1->Get(title);
	}	


	/////////////////////////////////////////////////////////
	// H1, H2 Tower energy distributions
	//
	TCanvas *c0 = new TCanvas("c0","c0",1200,400);
	c0->Divide(4,2);
	c0->cd();

	for(int i=0; i<8; i++)
        {
		c0->cd(i+1);
		gPad->SetLogy();
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

                hTowerEH1[i]->GetXaxis()->SetRangeUser(0.,0.5);
                hTowerEH1[i]->GetXaxis()->SetTitle("Tower Energy (GeV)");
                hTowerEH1[i]->GetXaxis()->SetTitleColor(kBlack);
		hTowerEH1[i]->GetYaxis()->SetTitle("Counts");
		hTowerEH1[i]->GetXaxis()->SetTitleSize(0.05);
		hTowerEH1[i]->GetYaxis()->SetTitleSize(0.05);
                hTowerEH1[i]->GetXaxis()->SetTitleOffset(1.1);
                hTowerEH1[i]->GetYaxis()->SetTitleOffset(1.);
                hTowerEH1[i]->SetLineWidth(1.);
                hTowerEH1[i]->SetLineColor(kBlue);
                hTowerEH1[i]->Draw();

                TLegend *leg = new TLegend(0.2,0.66,0.57,0.86);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hTowerEH1[i]," HCal Inner Layer","");
                leg->AddEntry(hTowerEH1[i],name,"");
                leg->Draw();
	}
	c0->cd();
	c0->SaveAs("TowerEnergyH1.png");
	c0->SaveAs("TowerEnergyH1.pdf");

	for(int i=0; i<8; i++)
        {
		c0->cd(i+1);
		gPad->SetLogy();
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

                hTowerEH2[i]->GetXaxis()->SetRangeUser(0.,0.5);
                hTowerEH2[i]->GetXaxis()->SetTitle("Tower Energy (GeV)");
                hTowerEH2[i]->GetXaxis()->SetTitleColor(kBlack);
		hTowerEH2[i]->GetYaxis()->SetTitle("Counts");
		hTowerEH2[i]->GetXaxis()->SetTitleSize(0.05);
		hTowerEH2[i]->GetYaxis()->SetTitleSize(0.05);
                hTowerEH2[i]->GetXaxis()->SetTitleOffset(1.1);
                hTowerEH2[i]->GetYaxis()->SetTitleOffset(1.);
                hTowerEH2[i]->SetLineWidth(1.);
                hTowerEH2[i]->SetLineColor(kBlue);
                hTowerEH2[i]->Draw();

                TLegend *leg = new TLegend(0.2,0.66,0.57,0.86);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hTowerEH2[i]," HCal Outer Layer","");
                leg->AddEntry(hTowerEH2[i],name,"");
                leg->Draw();
	}
	c0->cd();
	c0->SaveAs("TowerEnergyH2.png");
	c0->SaveAs("TowerEnergyH2.pdf");



	/////////////////////////////////////////////////////////
	// Asymmetry Energy [ (E2-E1)/(E2+E1) ] vs. LCG
	//
	TCanvas *c1 = new TCanvas("c1","c1",1200,400);
	c1->Divide(4,2);
	c1->cd();

	for(int i=0; i<8; i++)
        {
		c1->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

                hAsyE1vsLCG[i]->GetXaxis()->SetTitle("Longitudinal Center of Gravity");
                hAsyE1vsLCG[i]->GetYaxis()->SetTitle("#frac{E2-E1}{E2+E1}");
                hAsyE1vsLCG[i]->GetXaxis()->SetTitleColor(kBlack);
		hAsyE1vsLCG[i]->GetXaxis()->SetTitleSize(0.05);
		hAsyE1vsLCG[i]->GetYaxis()->SetTitleSize(0.05);
                hAsyE1vsLCG[i]->GetXaxis()->SetTitleOffset(1.1);
                hAsyE1vsLCG[i]->GetYaxis()->SetTitleOffset(1.);
                hAsyE1vsLCG[i]->SetLineWidth(1.);
                hAsyE1vsLCG[i]->Draw("colz");
                pAsyE1vsLCG[i]->SetMarkerColor(kBlack);
                pAsyE1vsLCG[i]->SetMarkerStyle(26);
                pAsyE1vsLCG[i]->SetMarkerSize(0.5);
                pAsyE1vsLCG[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.32,0.18,0.82,0.28);
                leg->SetTextSize(0.05);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hAsyE1vsLCG[i],name,"");
                leg->Draw();
	}
	c1->cd();
	c1->SaveAs("hAsyE1vsLCG.png");
	c1->SaveAs("hAsyE1vsLCG.pdf");


	for(int i=0; i<8; i++)
        {
		c1->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

		if(i==0) hAsyE2vsLCG[i]->GetYaxis()->SetRangeUser(-50.,50.);
		else if(i<3) hAsyE2vsLCG[i]->GetYaxis()->SetRangeUser(-30.,50.);
		else if(i<4) hAsyE2vsLCG[i]->GetYaxis()->SetRangeUser(-10.,40.);
		else hAsyE2vsLCG[i]->GetYaxis()->SetRangeUser(-6.,35.);

                hAsyE2vsLCG[i]->GetXaxis()->SetTitle("Longitudinal Center of Gravity");
                hAsyE2vsLCG[i]->GetYaxis()->SetTitle("#frac{log(E2)-log(E1)}{E2+E1}");
                hAsyE2vsLCG[i]->GetXaxis()->SetTitleColor(kBlack);
		hAsyE2vsLCG[i]->GetXaxis()->SetTitleSize(0.05);
		hAsyE2vsLCG[i]->GetYaxis()->SetTitleSize(0.05);
                hAsyE2vsLCG[i]->GetXaxis()->SetTitleOffset(1.1);
                hAsyE2vsLCG[i]->GetYaxis()->SetTitleOffset(1.);
                hAsyE2vsLCG[i]->SetLineWidth(1.);
                hAsyE2vsLCG[i]->Draw("colz");
                pAsyE2vsLCG[i]->SetMarkerColor(kBlack);
                pAsyE2vsLCG[i]->SetMarkerStyle(26);
                pAsyE2vsLCG[i]->SetMarkerSize(0.5);
                pAsyE2vsLCG[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.17,0.68,0.65,0.88);
                leg->SetTextSize(0.05);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hAsyE2vsLCG[i],name,"");
                leg->Draw();
	}
	c1->cd();
	c1->SaveAs("hAsyE2vsLCG.png");
	c1->SaveAs("hAsyE2vsLCG.pdf");


	for(int i=0; i<8; i++)
        {
		c1->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

		if(i==0) hAsyE2vsAsyE1[i]->GetYaxis()->SetRangeUser(-50.,50.);
		else if(i<3) hAsyE2vsAsyE1[i]->GetYaxis()->SetRangeUser(-30.,50.);
		else if(i<4) hAsyE2vsAsyE1[i]->GetYaxis()->SetRangeUser(-10.,40.);
		else hAsyE2vsAsyE1[i]->GetYaxis()->SetRangeUser(-6.,35.);

                hAsyE2vsAsyE1[i]->GetXaxis()->SetTitle("#frac{E2-E1}{E2+E1}");
                hAsyE2vsAsyE1[i]->GetYaxis()->SetTitle("#frac{log(E2)-log(E1)}{E2+E1}");
                hAsyE2vsAsyE1[i]->GetXaxis()->SetTitleColor(kBlack);
		hAsyE2vsAsyE1[i]->GetXaxis()->SetTitleSize(0.05);
		hAsyE2vsAsyE1[i]->GetYaxis()->SetTitleSize(0.05);
                hAsyE2vsAsyE1[i]->GetXaxis()->SetTitleOffset(1.1);
                hAsyE2vsAsyE1[i]->GetYaxis()->SetTitleOffset(1.);
                hAsyE2vsAsyE1[i]->SetLineWidth(1.);
                hAsyE2vsAsyE1[i]->Draw("colz");
                pAsyE2vsAsyE1[i]->SetMarkerColor(kBlack);
                pAsyE2vsAsyE1[i]->SetMarkerStyle(26);
                pAsyE2vsAsyE1[i]->SetMarkerSize(0.5);
        //        pAsyE2vsAsyE1[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.17,0.68,0.65,0.88);
                leg->SetTextSize(0.05);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hAsyE2vsAsyE1[i],name,"");
                leg->Draw();
	}
	c1->cd();
	c1->SaveAs("hAsyE2vsAsyE1.png");
	c1->SaveAs("hAsyE2vsAsyE1.pdf");






	/////////////////////////////////////////////////////////
	// SF11, SF 12 vs. Asymmetry Energy [ (E2-E1)/(E2+E1) ]
	//
	TCanvas *c2 = new TCanvas("c2","c2",1200,400);
	c2->Divide(4,2);
	c2->cd();

	for(int i=0; i<8; i++)
        {
		c2->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

                hSF11vsAsyE1[i]->GetXaxis()->SetTitle("#frac{E2-E1}{E2+E1}");
                hSF11vsAsyE1[i]->GetYaxis()->SetTitle("Sampling Fraction Factor (Inner HCal)");
                hSF11vsAsyE1[i]->GetXaxis()->SetTitleColor(kBlack);
		hSF11vsAsyE1[i]->GetXaxis()->SetTitleSize(0.05);
		hSF11vsAsyE1[i]->GetYaxis()->SetTitleSize(0.05);
                hSF11vsAsyE1[i]->GetXaxis()->SetTitleOffset(1.1);
                hSF11vsAsyE1[i]->GetYaxis()->SetTitleOffset(1.);
                hSF11vsAsyE1[i]->SetLineWidth(1.);
                hSF11vsAsyE1[i]->Draw("colz");
                pSF11vsAsyE1[i]->SetMarkerColor(kBlack);
                pSF11vsAsyE1[i]->SetMarkerStyle(26);
                pSF11vsAsyE1[i]->SetMarkerSize(0.5);
                pSF11vsAsyE1[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.15,0.65,0.65,0.8);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hSF11vsAsyE1[i],name,"");
                leg->Draw();
	}
	c2->cd();
	c2->SaveAs("SF11vsAsyE1.png");
	c2->SaveAs("SF11vsAsyE1.pdf");


	for(int i=0; i<8; i++)
        {
		c2->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

                hSF21vsAsyE1[i]->GetXaxis()->SetTitle("#frac{E2-E1}{E2+E1}");
                hSF21vsAsyE1[i]->GetYaxis()->SetTitle("Sampling Fraction Factor (Outer HCal)");
                hSF21vsAsyE1[i]->GetXaxis()->SetTitleColor(kBlack);
		hSF21vsAsyE1[i]->GetXaxis()->SetTitleSize(0.05);
		hSF21vsAsyE1[i]->GetYaxis()->SetTitleSize(0.05);
                hSF21vsAsyE1[i]->GetXaxis()->SetTitleOffset(1.1);
                hSF21vsAsyE1[i]->GetYaxis()->SetTitleOffset(1.);
                hSF21vsAsyE1[i]->SetLineWidth(1.);
                hSF21vsAsyE1[i]->Draw("colz");
                pSF21vsAsyE1[i]->SetMarkerColor(kBlack);
                pSF21vsAsyE1[i]->SetMarkerStyle(26);
                pSF21vsAsyE1[i]->SetMarkerSize(0.5);
                pSF21vsAsyE1[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.15,0.65,0.65,0.8);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hSF21vsAsyE1[i],name,"");
                leg->Draw();
	}
	c2->cd();
	c2->SaveAs("SF21vsAsyE1.png");
	c2->SaveAs("SF21vsAsyE1.pdf");


	for(int i=0; i<8; i++)
        {
		c2->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

		if(i==0) hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-50.,50.);
		else if(i<3) hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-30.,50.);
		else if(i<4) hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-10.,40.);
		else hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-6.,35.);

		if(i==0) hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-50.,50.);
		else if(i<3) hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-30.,50.);
		else if(i<4) hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-10.,40.);
		else hSF11vsAsyE2[i]->GetXaxis()->SetRangeUser(-6.,35.);

                hSF11vsAsyE2[i]->GetXaxis()->SetTitle("#frac{log(E2)-log(E1)}{E2+E1}");
                hSF11vsAsyE2[i]->GetYaxis()->SetTitle("Sampling Fraction Factor (Inner HCal)");
                hSF11vsAsyE2[i]->GetXaxis()->SetTitleColor(kBlack);
		hSF11vsAsyE2[i]->GetXaxis()->SetTitleSize(0.05);
		hSF11vsAsyE2[i]->GetYaxis()->SetTitleSize(0.05);
                hSF11vsAsyE2[i]->GetXaxis()->SetTitleOffset(1.1);
                hSF11vsAsyE2[i]->GetYaxis()->SetTitleOffset(1.);
                hSF11vsAsyE2[i]->SetLineWidth(1.);
                hSF11vsAsyE2[i]->Draw("colz");
                pSF11vsAsyE2[i]->SetMarkerColor(kBlack);
                pSF11vsAsyE2[i]->SetMarkerStyle(26);
                pSF11vsAsyE2[i]->SetMarkerSize(0.5);
                pSF11vsAsyE2[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.15,0.65,0.65,0.8);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hSF11vsAsyE2[i],name,"");
                leg->Draw();
	}
	c2->cd();
	c2->SaveAs("SF11vsAsyE2.png");
	c2->SaveAs("SF11vsAsyE2.pdf");


	for(int i=0; i<8; i++)
        {
		c2->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

		if(i==0) hSF21vsAsyE2[i]->GetXaxis()->SetRangeUser(-50.,50.);
		else if(i<3) hSF21vsAsyE2[i]->GetXaxis()->SetRangeUser(-30.,50.);
		else if(i<4) hSF21vsAsyE2[i]->GetXaxis()->SetRangeUser(-10.,40.);
		else hSF21vsAsyE2[i]->GetXaxis()->SetRangeUser(-6.,35.);
                hSF21vsAsyE2[i]->GetXaxis()->SetTitle("#frac{log(E2)-log(E1)}{E2+E1}");
                hSF21vsAsyE2[i]->GetYaxis()->SetTitle("Sampling Fraction Factor (Outer HCal)");
                hSF21vsAsyE2[i]->GetXaxis()->SetTitleColor(kBlack);
		hSF21vsAsyE2[i]->GetXaxis()->SetTitleSize(0.05);
		hSF21vsAsyE2[i]->GetYaxis()->SetTitleSize(0.05);
                hSF21vsAsyE2[i]->GetXaxis()->SetTitleOffset(1.1);
                hSF21vsAsyE2[i]->GetYaxis()->SetTitleOffset(1.);
                hSF21vsAsyE2[i]->SetLineWidth(1.);
                hSF21vsAsyE2[i]->Draw("colz");
                pSF21vsAsyE2[i]->SetMarkerColor(kBlack);
                pSF21vsAsyE2[i]->SetMarkerStyle(26);
                pSF21vsAsyE2[i]->SetMarkerSize(0.5);
                pSF21vsAsyE2[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.15,0.65,0.65,0.8);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hSF21vsAsyE2[i],name,"");
                leg->Draw();
	}
	c2->cd();
	c2->SaveAs("SF21vsAsyE2.png");
	c2->SaveAs("SF21vsAsyE2.pdf");

	/////////////////////////////////////////////////////////
	// Energy Leakage vs. Asymmetry Energy [ (E2-E1)/(E2+E1) ]
	//
	TCanvas *c3 = new TCanvas("c3","c3",1200,400);
	c3->Divide(4,2);
	c3->cd();

	for(int i=0; i<8; i++)
        {
		c3->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

                hELeakvsAsyE1[i]->GetXaxis()->SetTitle("#frac{E2-E1}{E2+E1}");
                hELeakvsAsyE1[i]->GetYaxis()->SetTitle("Energy Leakage (%)");
                hELeakvsAsyE1[i]->GetXaxis()->SetTitleColor(kBlack);
		hELeakvsAsyE1[i]->GetXaxis()->SetTitleSize(0.05);
		hELeakvsAsyE1[i]->GetYaxis()->SetTitleSize(0.05);
                hELeakvsAsyE1[i]->GetXaxis()->SetTitleOffset(1.1);
                hELeakvsAsyE1[i]->GetYaxis()->SetTitleOffset(1.);
                hELeakvsAsyE1[i]->SetLineWidth(1.);
                hELeakvsAsyE1[i]->Draw("colz");
                pELeakvsAsyE1[i]->SetMarkerColor(kBlack);
                pELeakvsAsyE1[i]->SetMarkerStyle(26);
                pELeakvsAsyE1[i]->SetMarkerSize(0.5);
                pELeakvsAsyE1[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.15,0.65,0.65,0.8);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hELeakvsAsyE1[i],name,"");
                leg->Draw();
	}
	c3->cd();
	c3->SaveAs("ELeakvsAsyE1.png");
	c3->SaveAs("ELeakvsAsyE1.pdf");


	for(int i=0; i<8; i++)
        {
		c3->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

		if(i==0) hELeakvsAsyE2[i]->GetXaxis()->SetRangeUser(-50.,50.);
		else if(i<3) hELeakvsAsyE2[i]->GetXaxis()->SetRangeUser(-30.,50.);
		else if(i<4) hELeakvsAsyE2[i]->GetXaxis()->SetRangeUser(-10.,40.);
		else hELeakvsAsyE2[i]->GetXaxis()->SetRangeUser(-6.,35.);

                hELeakvsAsyE2[i]->GetXaxis()->SetTitle("#frac{log(E2)-log(E1)}{E2+E1}");
                hELeakvsAsyE2[i]->GetYaxis()->SetTitle("Energy Leakage (%)");
                hELeakvsAsyE2[i]->GetXaxis()->SetTitleColor(kBlack);
		hELeakvsAsyE2[i]->GetXaxis()->SetTitleSize(0.05);
		hELeakvsAsyE2[i]->GetYaxis()->SetTitleSize(0.05);
                hELeakvsAsyE2[i]->GetXaxis()->SetTitleOffset(1.1);
                hELeakvsAsyE2[i]->GetYaxis()->SetTitleOffset(1.);
                hELeakvsAsyE2[i]->SetLineWidth(1.);
                hELeakvsAsyE2[i]->Draw("colz");
                pELeakvsAsyE2[i]->SetMarkerColor(kBlack);
                pELeakvsAsyE2[i]->SetMarkerStyle(26);
                pELeakvsAsyE2[i]->SetMarkerSize(0.5);
                pELeakvsAsyE2[i]->Draw("SAME");

                TLegend *leg = new TLegend(0.15,0.65,0.65,0.8);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0",index[i]);
                leg->AddEntry(hELeakvsAsyE2[i],name,"");
                leg->Draw();
	}
	c3->cd();
	c3->SaveAs("ELeakvsAsyE2.png");
	c3->SaveAs("ELeakvsAsyE2.pdf");


	/////////////////////////////////////////////////////////
	// Center of Gravity in Y Z 
	//
	TCanvas *c4 = new TCanvas("c4","c4",1200,400);
	c4->Divide(4,2);
	c4->cd();

	for(int i=0; i<8; i++)
        {
		c4->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

              	hH1TowerYZ[i]->GetXaxis()->SetTitle("Center of Gravity in Z");
              	hH1TowerYZ[i]->GetYaxis()->SetTitle("Center of Gravity in Y");
		hH1TowerYZ[i]->GetXaxis()->SetTitleColor(kBlack);
		hH1TowerYZ[i]->GetXaxis()->SetTitleSize(0.05);
		hH1TowerYZ[i]->GetYaxis()->SetTitleSize(0.05);
		hH1TowerYZ[i]->GetXaxis()->SetTitleOffset(1.1);
		hH1TowerYZ[i]->GetYaxis()->SetTitleOffset(1.);
		hH1TowerYZ[i]->SetLineWidth(1.);
		hH1TowerYZ[i]->Draw("colz");

                TLegend *leg = new TLegend(0.15,0.7,0.65,0.85);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0, Inner HCal",index[i]);
		leg->AddEntry(hH1TowerYZ[i],name,"");
		leg->Draw();
	}
	c4->cd();
	c4->SaveAs("hH1TowerYZ.png");
	c4->SaveAs("hH1TowerYZ.pdf");


	for(int i=0; i<8; i++)
	{
		c4->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

                hH2TowerYZ[i]->GetXaxis()->SetTitle("Center of Gravity in Z");
                hH2TowerYZ[i]->GetYaxis()->SetTitle("Center of Gravity in Y");
                hH2TowerYZ[i]->GetXaxis()->SetTitleColor(kBlack);
		hH2TowerYZ[i]->GetXaxis()->SetTitleSize(0.05);
		hH2TowerYZ[i]->GetYaxis()->SetTitleSize(0.05);
                hH2TowerYZ[i]->GetXaxis()->SetTitleOffset(1.1);
                hH2TowerYZ[i]->GetYaxis()->SetTitleOffset(1.);
                hH2TowerYZ[i]->SetLineWidth(1.);
                hH2TowerYZ[i]->Draw("colz");

                TLegend *leg = new TLegend(0.15,0.7,0.65,0.85);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i GeV #pi^{+}, #mu^{-}, e^{-}, #eta = 0, outer hcal",index[i]);
                leg->AddEntry(hH2TowerYZ[i],name,"");
                leg->Draw();
	}
	c4->cd();
	c4->SaveAs("hH2TowerYZ.png");
	c4->SaveAs("hH2TowerYZ.pdf");


	/////////////////////////////////////////////////////////
	// total energy vs. energy asymmetry 
	//
	for(int i=0; i<8; i++)
        {
		c4->cd(i+1);
		gPad->SetLeftMargin(0.12);
		gPad->SetRightMargin(0.15);
		gPad->SetBottomMargin(0.15);

		hTotalEvsAsyE1[i]->GetYaxis()->SetRangeUser(0.,3.);
              	hTotalEvsAsyE1[i]->GetXaxis()->SetTitle("Asymmetry (h2-h1)/(h2+h1)");
              	hTotalEvsAsyE1[i]->GetYaxis()->SetTitle("Total energy in scint");
		hTotalEvsAsyE1[i]->GetXaxis()->SetTitleColor(kBlack);
		hTotalEvsAsyE1[i]->GetXaxis()->SetTitleSize(0.05);
		hTotalEvsAsyE1[i]->GetYaxis()->SetTitleSize(0.05);
		hTotalEvsAsyE1[i]->GetXaxis()->SetTitleOffset(1.1);
		hTotalEvsAsyE1[i]->GetYaxis()->SetTitleOffset(1.);
		hTotalEvsAsyE1[i]->SetLineWidth(1.);
		hTotalEvsAsyE1[i]->Draw("colz");

                TLegend *leg = new TLegend(0.15,0.7,0.65,0.85);
                leg->SetTextSize(0.06);
                leg->SetLineColor(4);
                leg->SetLineStyle(1);
                leg->SetLineWidth(1);
                leg->SetFillColor(0);
                leg->SetMargin(0.1);
                leg->SetFillStyle(0);
                leg->SetTextAlign(12);
                leg->SetBorderSize(0);
                char name[256];
                sprintf(name," %i Gev #pi^{+}, #mu^{-}, e^{-}, #eta = 0, HCal Prototype",index[i]);
		leg->AddEntry(hH1TowerYZ[i],name,"");
		leg->Draw();
	}
	c4->cd();
	c4->SaveAs("TotalEvsAsyE1.png");
	c4->SaveAs("TotalEvsAsyE1.pdf");

}
