#define MAXTOWER 16
#define LAYER 2

struct myTree{
	Float_t Energy;
	Float_t Phi;
	Float_t Theta;
	Float_t Px;
	Float_t Py;
	Float_t Pz;

	Float_t Eleak;
	Float_t LCG;  /// Longitudinal CG calculated with G4 hits
	Float_t SF[LAYER];   /// Sampling Fraction Factors for inner and outer HCal
	Float_t Escint[LAYER];  /// energy deposited in scint in each section
	Float_t Eabs[LAYER];   /// energy deposited in absorber in each section
	Float_t edep[LAYER][MAXTOWER];   /// energy deposited in each tower for H1 and H2
};
