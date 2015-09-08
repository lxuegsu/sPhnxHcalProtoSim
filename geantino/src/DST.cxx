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
	chain->SetBranchAddress("nG4SnglHits", &cell.nG4SnglHits);
	chain->SetBranchAddress("G4SnglHits", &cell.G4SnglHits_);

	chain->SetBranchAddress("G4SnglHits.detid", cell.detid);
	chain->SetBranchAddress("G4SnglHits.layer", cell.layer);
	chain->SetBranchAddress("G4SnglHits.scintid", cell.scintid);
	chain->SetBranchAddress("G4SnglHits.trackid", cell.trackid);
	chain->SetBranchAddress("G4SnglHits.x0", cell.x0);
	chain->SetBranchAddress("G4SnglHits.y0", cell.y0);
	chain->SetBranchAddress("G4SnglHits.z0", cell.z0);
	chain->SetBranchAddress("G4SnglHits.x1", cell.x1);
	chain->SetBranchAddress("G4SnglHits.y1", cell.y1);
	chain->SetBranchAddress("G4SnglHits.z1", cell.z1);
	chain->SetBranchAddress("G4SnglHits.edep", cell.edep);
}
