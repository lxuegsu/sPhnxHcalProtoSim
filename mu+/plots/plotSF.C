#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

void plotSF ()
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


	///////open the root files////////
	TFile *f1 = new TFile("../output/mu-.root");
	TH2D *InnerSF = (TH2D *)f1->Get("hHCalInnerSF");
	TH2D *OuterSF = (TH2D *)f1->Get("hHCalOuterSF");
	

        TCanvas *c1 = new TCanvas("c1","c1",700,500);
        c1->cd();
        c1->SetLeftMargin(0.15);
        c1->SetBottomMargin(0.15);
        c1->SetGridy(0);
        c1->SetGridx(0);

	TF1 *fit1 = new TF1("fit1","gaus",0.,0.1);
	InnerSF->Fit("fit1","","",0.042,0.07);

	InnerSF->GetXaxis()->CenterTitle(1);
	InnerSF->GetYaxis()->CenterTitle(1);
	InnerSF->GetXaxis()->SetRangeUser(0.02,0.1);
	InnerSF->GetYaxis()->SetRangeUser(0.,500);
	InnerSF->GetYaxis()->SetTitle("Counts");
	InnerSF->GetXaxis()->SetTitleColor(kBlack);
	InnerSF->GetXaxis()->SetTitle("Sampling fraction factors");
	InnerSF->GetYaxis()->SetTitleSize(0.065);
	InnerSF->GetXaxis()->SetTitleSize(0.055);
	InnerSF->GetXaxis()->SetTitleOffset(1.1);
	InnerSF->GetYaxis()->SetTitleOffset(1.);
	InnerSF->Draw("");


	TLegend *leg = new TLegend(0.3,0.55,0.62,0.65);
	leg->SetTextSize(0.04);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(InnerSF,"HCal Prototype Inner Layer","");
	leg->Draw();

	c1->SaveAs("InnerSF.png");


	TF1 *fit2 = new TF1("fit2","gaus",0.,0.1);
	OuterSF->Fit("fit2","","",0.01,0.026);

        OuterSF->GetXaxis()->CenterTitle(1);
        OuterSF->GetYaxis()->CenterTitle(1);
        OuterSF->GetXaxis()->SetRangeUser(0.0,0.1);
        OuterSF->GetYaxis()->SetRangeUser(0.,1000);
        OuterSF->GetYaxis()->SetTitle("Counts");
        OuterSF->GetXaxis()->SetTitleColor(kBlack);
        OuterSF->GetXaxis()->SetTitle("Sampling fraction factors");
        OuterSF->GetYaxis()->SetTitleSize(0.065);
        OuterSF->GetXaxis()->SetTitleSize(0.055);
        OuterSF->GetXaxis()->SetTitleOffset(1.1);
        OuterSF->GetYaxis()->SetTitleOffset(1.);
        OuterSF->Draw("");

	TLegend *leg = new TLegend(0.46,0.55,0.84,0.59);
        leg->SetTextSize(0.04);
        leg->SetLineColor(4);
        leg->SetLineStyle(1);
        leg->SetLineWidth(1);
        leg->SetFillColor(0);
        leg->SetMargin(0.1);
        leg->SetFillStyle(0);
        leg->SetTextAlign(12);
        leg->SetBorderSize(0);
        leg->AddEntry(InnerSF," HCal Prototype Outer Layer","");
        leg->Draw();

        c1->SaveAs("OuterSF.png");
}
