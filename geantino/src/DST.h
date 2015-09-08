#ifndef DST_h
#define DST_h

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"

#include "TStyle.h"
#include "TCanvas.h"
#include "TString.h"
#include "TArrayI.h"
#include "TArrayL.h"
#include "TArrayF.h"
#include "TBranch.h"
#include "TMath.h"

#define MAXHITS 1000000

typedef struct
{
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

}Cell_t;

class DST {

	public:
		Cell_t cell;

		void SetData(TChain *chain);
}; 

#endif
