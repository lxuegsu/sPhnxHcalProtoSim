#define DST_cxx

#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>
#include "DST.h"

void DST::SetData(TChain *chain) 
{
	// Set branch addresses
	chain->SetMakeClass(1);

	chain->SetBranchAddress("Energy", &cell.Energy);
	chain->SetBranchAddress("Phi", &cell.Phi);
	chain->SetBranchAddress("Theta", &cell.Theta);
	chain->SetBranchAddress("Px", &cell.Px);
	chain->SetBranchAddress("Py", &cell.Py);
	chain->SetBranchAddress("Pz", &cell.Pz);
	chain->SetBranchAddress("Eleak", &cell.Eleak);
	chain->SetBranchAddress("LCG", &cell.LCG);

	chain->SetBranchAddress("SF", cell.SF);
	chain->SetBranchAddress("Escint", cell.Escint);
	chain->SetBranchAddress("Eabs", cell.Eabs);
	chain->SetBranchAddress("edep", cell.edep);
}
