#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

void plotMaterialThicknessvsR ()
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
        TH2D *hGeantinoTActLvsR = (TH2D *)f1->Get("hActLengthvsR");
        TProfile *pGeantinoTActLvsR = (TProfile *)f1->Get("pActLengthvsR");
        TH2D *hGeantinoTAbsLvsR = (TH2D *)f1->Get("hAbsLengthvsR");
        TProfile *pGeantinoTAbsLvsR = (TProfile *)f1->Get("pAbsLengthvsR");

        TH2D *hGeantinoTRinRLvsR = (TH2D *)f1->Get("hRinRLvsR");
        TProfile *pGeantinoTRinRLvsR = (TProfile *)f1->Get("pRinRLvsR");
        TH2D *hGeantinoTRinILvsR = (TH2D *)f1->Get("hRinILvsR");
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
        hGeantinoTActLvsR->GetXaxis()->CenterTitle(1);
        hGeantinoTActLvsR->GetYaxis()->CenterTitle(1);
        hGeantinoTActLvsR->GetYaxis()->SetRangeUser(0.,20.);
        hGeantinoTActLvsR->GetXaxis()->SetTitle("Radius (cm)");
        hGeantinoTActLvsR->GetXaxis()->SetTitleColor(kBlack);
        hGeantinoTActLvsR->GetYaxis()->SetTitle("Total scintillator length (cm)");
        hGeantinoTActLvsR->GetXaxis()->SetTitleSize(0.05);
        hGeantinoTActLvsR->GetYaxis()->SetTitleSize(0.05);
        hGeantinoTActLvsR->GetXaxis()->SetTitleOffset(1.1);
        hGeantinoTActLvsR->GetYaxis()->SetTitleOffset(1.);
        hGeantinoTActLvsR->SetLineWidth(2);
	hGeantinoTActLvsR->Draw("colz");
	TLegend *leg = new TLegend(0.15,0.7,0.57,0.85);
	leg->SetTextSize(0.035);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hGeantinoTActLvsR, "HCal Prototype","");
	leg->Draw();
        c1->SaveAs("hGeantino_TActLvsR.png");


	////--------------------------------------------------------------------////
	c1->cd();
	pGeantinoTActLvsR->GetXaxis()->CenterTitle(1);
	pGeantinoTActLvsR->GetYaxis()->CenterTitle(1);
	pGeantinoTActLvsR->GetYaxis()->SetRangeUser(0.,20.);
	pGeantinoTActLvsR->GetXaxis()->SetTitle("Radius (cm)");
	pGeantinoTActLvsR->GetXaxis()->SetTitleColor(kBlack);
	pGeantinoTActLvsR->GetYaxis()->SetTitle("Average total scintillator length (cm)");
	pGeantinoTActLvsR->GetXaxis()->SetTitleSize(0.05);
	pGeantinoTActLvsR->GetYaxis()->SetTitleSize(0.05);
	pGeantinoTActLvsR->GetXaxis()->SetTitleOffset(1.1);
	pGeantinoTActLvsR->GetYaxis()->SetTitleOffset(1.);
	pGeantinoTActLvsR->SetLineWidth(2);
	pGeantinoTActLvsR->Draw("colz");
	TLegend *leg = new TLegend(0.15,0.7,0.57,0.85);
	leg->SetTextSize(0.035);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(pGeantinoTActLvsR, "HCal Prototype","");
	leg->Draw();
	c1->SaveAs("hGeantino_AvgTActLvsR.png");

	////--------------------------------------------------------------------////
	c1->cd();
        hGeantinoTAbsLvsR->GetXaxis()->CenterTitle(1);
        hGeantinoTAbsLvsR->GetYaxis()->CenterTitle(1);
	hGeantinoTAbsLvsR->GetYaxis()->SetRangeUser(0.,70.);
        hGeantinoTAbsLvsR->GetXaxis()->SetTitle("Radius (cm)");
        hGeantinoTAbsLvsR->GetXaxis()->SetTitleColor(kBlack);
        hGeantinoTAbsLvsR->GetYaxis()->SetTitle("Total absorber length (cm)");
        hGeantinoTAbsLvsR->GetXaxis()->SetTitleSize(0.05);
        hGeantinoTAbsLvsR->GetYaxis()->SetTitleSize(0.05);
        hGeantinoTAbsLvsR->GetXaxis()->SetTitleOffset(1.1);
        hGeantinoTAbsLvsR->GetYaxis()->SetTitleOffset(1.);
        hGeantinoTAbsLvsR->SetLineWidth(2);
	hGeantinoTAbsLvsR->Draw("colz");
	TLegend *leg = new TLegend(0.15,0.7,0.57,0.85);
	leg->SetTextSize(0.035);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hGeantinoTAbsLvsR, "HCal Prototype","");
	leg->Draw();
        c1->SaveAs("hGeantino_TAbsLvsR.png");

	////--------------------------------------------------------------------////
	c1->cd();
	pGeantinoTAbsLvsR->GetXaxis()->CenterTitle(1);
	pGeantinoTAbsLvsR->GetYaxis()->CenterTitle(1);
	pGeantinoTAbsLvsR->GetYaxis()->SetRangeUser(0.,70.);
	pGeantinoTAbsLvsR->GetXaxis()->SetTitle("Radius (cm)");
	pGeantinoTAbsLvsR->GetXaxis()->SetTitleColor(kBlack);
	pGeantinoTAbsLvsR->GetYaxis()->SetTitle("Average total absorber length (cm)");
	pGeantinoTAbsLvsR->GetXaxis()->SetTitleSize(0.05);
	pGeantinoTAbsLvsR->GetYaxis()->SetTitleSize(0.05);
	pGeantinoTAbsLvsR->GetXaxis()->SetTitleOffset(1.1);
	pGeantinoTAbsLvsR->GetYaxis()->SetTitleOffset(1.);
	pGeantinoTAbsLvsR->SetLineWidth(2);
	pGeantinoTAbsLvsR->Draw("colz");
	TLegend *leg = new TLegend(0.15,0.7,0.57,0.85);
	leg->SetTextSize(0.035);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(pGeantinoTAbsLvsR, "HCal Prototype","");
	leg->Draw();
	c1->SaveAs("hGeantino_AvgTAbsLvsR.png");


	////--------------------------------------------------------------------////
	c1->cd();
        hGeantinoTRinRLvsR->GetXaxis()->CenterTitle(1);
        hGeantinoTRinRLvsR->GetYaxis()->CenterTitle(1);
        hGeantinoTRinRLvsR->GetYaxis()->SetRangeUser(0.,50.);
        hGeantinoTRinRLvsR->GetXaxis()->SetTitle("Radius (cm)");
        hGeantinoTRinRLvsR->GetXaxis()->SetTitleColor(kBlack);
        hGeantinoTRinRLvsR->GetYaxis()->SetTitle("Radius ( in X_{0})");
        hGeantinoTRinRLvsR->GetXaxis()->SetTitleSize(0.05);
        hGeantinoTRinRLvsR->GetYaxis()->SetTitleSize(0.05);
        hGeantinoTRinRLvsR->GetXaxis()->SetTitleOffset(1.1);
        hGeantinoTRinRLvsR->GetYaxis()->SetTitleOffset(1.);
        hGeantinoTRinRLvsR->SetLineWidth(2);
	hGeantinoTRinRLvsR->Draw("colz");
	TLegend *leg = new TLegend(0.25,0.7,0.65,0.85);
	leg->SetTextSize(0.05);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hGeantinoTRinRLvsR, "HCal Prototype","");
	leg->Draw();
        c1->SaveAs("hGeantino_TRinRLvsR.png");

	////--------------------------------------------------------------------////
	c1->cd();
        pGeantinoTRinRLvsR->GetXaxis()->CenterTitle(1);
        pGeantinoTRinRLvsR->GetYaxis()->CenterTitle(1);
        pGeantinoTRinRLvsR->GetYaxis()->SetRangeUser(0.,50.);
        pGeantinoTRinRLvsR->GetXaxis()->SetTitle("Radius (cm)");
        pGeantinoTRinRLvsR->GetXaxis()->SetTitleColor(kBlack);
        pGeantinoTRinRLvsR->GetYaxis()->SetTitle("Average radius ( in X_{0})");
        pGeantinoTRinRLvsR->GetXaxis()->SetTitleSize(0.05);
        pGeantinoTRinRLvsR->GetYaxis()->SetTitleSize(0.05);
        pGeantinoTRinRLvsR->GetXaxis()->SetTitleOffset(1.1);
        pGeantinoTRinRLvsR->GetYaxis()->SetTitleOffset(1.);
        pGeantinoTRinRLvsR->SetMarkerStyle(20);
        pGeantinoTRinRLvsR->SetMarkerSize(0.7);
	pGeantinoTRinRLvsR->Draw("colz");

	TLegend *leg = new TLegend(0.25,0.7,0.65,0.85);
	leg->SetTextSize(0.05);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(pGeantinoTRinRLvsR, "HCal Prototype","");
	leg->Draw();
        c1->SaveAs("hGeantino_AvgTRinRLvsR.png");

	////--------------------------------------------------------------------////
	c1->cd();
        hGeantinoTRinILvsR->GetXaxis()->CenterTitle(1);
        hGeantinoTRinILvsR->GetYaxis()->CenterTitle(1);
        hGeantinoTRinILvsR->GetYaxis()->SetRangeUser(0.,5.5);
        hGeantinoTRinILvsR->GetXaxis()->SetTitle("Radius (cm)");
        hGeantinoTRinILvsR->GetXaxis()->SetTitleColor(kBlack);
        hGeantinoTRinILvsR->GetYaxis()->SetTitle("Radius ( in #lambda_{0})");
        hGeantinoTRinILvsR->GetXaxis()->SetTitleSize(0.05);
        hGeantinoTRinILvsR->GetYaxis()->SetTitleSize(0.05);
        hGeantinoTRinILvsR->GetXaxis()->SetTitleOffset(1.1);
        hGeantinoTRinILvsR->GetYaxis()->SetTitleOffset(1.);
        hGeantinoTRinILvsR->SetLineWidth(2);
	hGeantinoTRinILvsR->Draw("colz");
	TLegend *leg = new TLegend(0.25,0.75,0.65,0.85);
	leg->SetTextSize(0.05);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(hGeantinoTRinILvsR, "HCal Prototype","");
	leg->Draw();
        c1->SaveAs("hGeantino_TRinILvsR.png");

	////--------------------------------------------------------------------////
	c1->cd();
        pGeantinoTRinILvsR->GetXaxis()->CenterTitle(1);
        pGeantinoTRinILvsR->GetYaxis()->CenterTitle(1);
        pGeantinoTRinILvsR->GetYaxis()->SetRangeUser(0.,5.5);
        pGeantinoTRinILvsR->GetXaxis()->SetTitle("Radius (cm)");
        pGeantinoTRinILvsR->GetXaxis()->SetTitleColor(kBlack);
        pGeantinoTRinILvsR->GetYaxis()->SetTitle("Average radius ( in #lambda_{0})");
        pGeantinoTRinILvsR->GetXaxis()->SetTitleSize(0.05);
        pGeantinoTRinILvsR->GetYaxis()->SetTitleSize(0.05);
        pGeantinoTRinILvsR->GetXaxis()->SetTitleOffset(1.1);
        pGeantinoTRinILvsR->GetYaxis()->SetTitleOffset(1.);
        pGeantinoTRinILvsR->SetMarkerStyle(20);
        pGeantinoTRinILvsR->SetMarkerSize(0.7);
	pGeantinoTRinILvsR->Draw("colz");

	TLegend *leg = new TLegend(0.25,0.75,0.65,0.85);
	leg->SetTextSize(0.05);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(pGeantinoTRinILvsR, "HCal Prototype","");
	leg->Draw();
        c1->SaveAs("hGeantino_AvgTRinILvsR.png");
}
