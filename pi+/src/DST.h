//// From Makeclass
#ifndef DST_h
#define DST_h

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"

typedef struct
{
	//Declaration of leaves types
	Float_t         Energy;
	Float_t         Phi;
	Float_t         Theta;
	Float_t         Px;
	Float_t         Py;
	Float_t         Pz;
	Float_t         Eleak;
	Float_t         LCG;
	Float_t         SF[2];
	Float_t         Escint[2];
	Float_t         Eabs[2];
	Float_t         edep[2][16];
}Cell_t;

class DST {

	public:
		Cell_t cell;

		void SetData(TChain *chain);
}; 

#endif
