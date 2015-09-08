int Fun4All_G4_HcalPrototype(
		int nEvents = 100,
		double mom=30.,
		const char *particle="mu+",
		const char *outputFile="G4Ntuple.root",
		const float field = 0 
		)
{
	cout << " particle: " << particle << endl;
	cout << " mom: " << mom << " GeV/c" << endl;
	cout << " output file: " << outputFile << endl;
	cout << " magnet field: " << field << endl;

	gSystem->Load("libfun4all");
	gSystem->Load("libg4detectors.so");
	gSystem->Load("libg4testbench");
	gSystem->Load("libg4picoDst.so");
	gSystem->ListLibraries();


	///////////////////////////////////////////
	// Make the Server
	//////////////////////////////////////////
	Fun4AllServer *se = Fun4AllServer::instance();
	se->Verbosity(0);

	PHG4ParticleGenerator *gen = new PHG4ParticleGenerator();
	gen->set_name(particle);
	gen->set_vtx(0, 0, 0);
	gen->set_eta_range(-0.02, -0.02);
	gen->set_mom_range(mom, mom);
	gen->set_phi_range(8./180.*TMath::Pi(), 8./180.*TMath::Pi());
	se->registerSubsystem(gen);

	PHG4Reco* g4Reco = new PHG4Reco();
	g4Reco->set_field(field);
	PHG4HcalPrototypeSubsystem *prototype = new PHG4HcalPrototypeSubsystem("HCal");
	prototype->SetActive();
	prototype->SetAbsorberActive();
	prototype->OverlapCheck(true);
	prototype->SuperDetector("HCAL");
	g4Reco->registerSubsystem(prototype);

	PHG4TruthSubsystem *truth = new PHG4TruthSubsystem();
	g4Reco->registerSubsystem(truth);

	se->registerSubsystem( g4Reco );


	mFillG4SnglHTCContainer* msngl = new mFillG4SnglHTCContainer();
	msngl->CreateNode("G4SnglHTCContainer");
	msngl->Set_MakeHit(true);
	msngl->Set_MakeTower(false);
	msngl->Set_MakeCluster(false);
	msngl->AddNode("HCAL",1);
	msngl->AddNode("ABSORBER_HCAL",2);
	se->registerSubsystem(msngl);


	///////////////////////////////////////////
	// IOManagers...
	///////////////////////////////////////////

	Fun4AllInputManager *in = new Fun4AllDummyInputManager( "JADE");
	se->registerInputManager( in );

	Fun4AllDstOutputManager *out = new Fun4AllDstOutputManager("DSTOUT",outputFile);
	out->AddNode("G4SnglHitContainer");
	se->registerOutputManager(out);

	se->run(nEvents);

	se->End();
	std::cout << "All done" << std::endl;
	delete se;
	   return 0;
	gSystem->Exit(0);

}
