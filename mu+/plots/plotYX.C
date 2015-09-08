#include "TH1.h"
#include "TMath.h"
#include "TF1.h"
#include "TLegend.h"
#include "TCanvas.h"

void plotYX ()
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
	TH2D *YXScint = (TH2D *)f1->Get("hHCalYXScint");
	TH2D *YXAbsor = (TH2D *)f1->Get("hHCalYXAbsor");
	

        TCanvas *c1 = new TCanvas("c1","c1",700,500);
        c1->cd();
        c1->SetLeftMargin(0.15);
        c1->SetBottomMargin(0.15);
        c1->SetGridy(0);
        c1->SetGridx(0);

	YXScint->GetXaxis()->CenterTitle(1);
	YXScint->GetYaxis()->CenterTitle(1);
	YXScint->GetYaxis()->SetTitle("Y (cm)");
	YXScint->GetXaxis()->SetTitleColor(kBlack);
	YXScint->GetXaxis()->SetTitle("X (cm)");
	YXScint->GetYaxis()->SetTitleSize(0.065);
	YXScint->GetXaxis()->SetTitleSize(0.055);
	YXScint->GetXaxis()->SetTitleOffset(1.1);
	YXScint->GetYaxis()->SetTitleOffset(1.);
	YXScint->Draw("");

	TLegend *leg = new TLegend(0.17,0.77,0.35,0.87);
	leg->SetTextSize(0.045);
	leg->SetLineColor(4);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetMargin(0.1);
	leg->SetFillStyle(0);
	leg->SetTextAlign(12);
	leg->SetBorderSize(0);
	leg->AddEntry(YXScint,"G4 hits in scintillator plate","");
	leg->Draw();

	c1->SaveAs("YXScint.png");


        YXAbsor->GetXaxis()->CenterTitle(1);
        YXAbsor->GetYaxis()->CenterTitle(1);
        YXAbsor->GetYaxis()->SetTitle("Y (cm)");
        YXAbsor->GetXaxis()->SetTitleColor(kBlack);
        YXAbsor->GetXaxis()->SetTitle("X (cm)");
        YXAbsor->GetYaxis()->SetTitleSize(0.065);
        YXAbsor->GetXaxis()->SetTitleSize(0.055);
        YXAbsor->GetXaxis()->SetTitleOffset(1.1);
        YXAbsor->GetYaxis()->SetTitleOffset(1.);
        YXAbsor->Draw("");

	TLegend *leg = new TLegend(0.17,0.77,0.35,0.87);
        leg->SetTextSize(0.045);
        leg->SetLineColor(4);
        leg->SetLineStyle(1);
        leg->SetLineWidth(1);
        leg->SetFillColor(0);
        leg->SetMargin(0.1);
        leg->SetFillStyle(0);
        leg->SetTextAlign(12);
        leg->SetBorderSize(0);
        leg->AddEntry(YXScint,"G4 hits in absorber plates","");
        leg->Draw();

        c1->SaveAs("YXAbsor.png");
}
