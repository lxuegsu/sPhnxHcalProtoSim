#include "TH1D.h"
#include "TH2D.h"
#include "TH3D.h"
#include "TProfile.h"

#include "DST.h"

//#define CORRECTION

TFile *rootfile;

///// Zero order approximation
///// We think the total deposited in scint is the zero order approximation
TH2D *hRecoE0vsInitE; /// total Zero order energy
TH2D *hRecoE10vsInitE; /// inner Zero order energy
TH2D *hRecoE20vsInitE; /// inner Zero order energy

TH2D *hELeakvsInitE;  /// energy leakage
TH2D *hTowerEH1vsInitE;  /// tower energy
TH2D *hTowerEH2vsInitE;  /// tower energy

TH2D *hAsyE1vsLCG[8];  /// (E2-E1)/(E2+E1) vs. LCG
TH2D *hAsyE2vsLCG[8];  /// (log(E2) - log(E1))/(E2+E1) vs. LCG
TH2D *hAsyE2vsAsyE1[8];  /// (log(E2) - log(E1))/(E2+E1) vs. (E2-E1)/(E2+E1) 
TH2D *hELeakvsAsyE1[8];
TH2D *hELeakvsAsyE2[8];
TH2D *hSF11vsAsyE1[8];
TH2D *hSF21vsAsyE1[8];
TH2D *hSF11vsAsyE2[8];
TH2D *hSF21vsAsyE2[8];

TH2D *hH1TowerYZ[8];
TH2D *hH2TowerYZ[8];
TH2D *hTotalEvsAsyE1[8];




#ifdef CORRECTION 
///// First order approximation
///// Reconstructed energy vs initial energy
///// Base on zero order approximation, we parameterize SF vs AsyE
///// apply the correction, get the first order reconstruction
TH2D *hRecoE1vsInitE;  /// Total recon energy
TH2D *hRecoE11vsInitE; /// inner HCal recon energy
TH2D *hRecoE21vsInitE; /// outer HCal recon energy

TH2D *hRecoE1LvsInitE;  /// Total recon energy + Energy Leakage

//------Some plots of reconstructed energy vs AsyE
TH2D *hRecoE1vsAsyE[8];
TH2D *hRecoE1LvsAsyE[8];
TH2D *hRecoE11vsAsyE[8];
TH2D *hRecoE21vsAsyE[8];
#endif
