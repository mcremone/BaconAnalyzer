{


	gROOT->ProcessLine(".L makeComparison13TeV.C");

//	makeComparisonBackground("PFLepton_deltaR"); 
 makeComparisonBackground("z_ratio1");
 // makeComparisonBackground("qvol");
 //makeComparisonBackground("SDchi");
	makeComparisonBackground("PFLepton_ptrel"); 

	makeComparisonBackground("PFLepton_ratioRel"); 

	//	makeComparisonBackground("PFLepton_IP2D"); 



//	makeComparisonBackground("PFElectron_deltaR");
//	makeComparisonBackground("PFElectron_ptrel "); 

//	makeComparisonBackground("PFElectron_ratioRel"); 
//	makeComparisonBackground("PFElectron_IP2D"); 
//
///	makeComparisonBackground("PFMuon_deltaR"); 

	//makeComparisonBackground("PFMuon_ptrel"); 

	//makeComparisonBackground("PFMuon_ratioRel"); 

	//makeComparisonBackground("PFMuon_IP2D"); 
    makeComparisonBackground("tau3/tau2");
    // makeComparisonBackground("tau2IVF/tau1IVF");

    //	makeComparisonBackground("massGroomed"); 

    //	makeComparisonBackground("ptGroomed"); 

//	makeComparisonBackground("etaGroomed"); 

//	makeComparisonBackground("phiGroomed"); 


	makeComparisonBackground("SV_flight_0"); 

	makeComparisonBackground("SV_flight_1"); 

	makeComparisonBackground("SV_flightErr_0"); 

	makeComparisonBackground("SV_flightErr_1"); 

	makeComparisonBackground("SV_flight2D_0"); 

	makeComparisonBackground("SV_flight2D_1"); 

	makeComparisonBackground("SV_flight2DErr_0"); 

	makeComparisonBackground("SV_flight2DErr_1"); 

	makeComparisonBackground("SV_totCharge_0"); 

	makeComparisonBackground("SV_totCharge_1"); 

	makeComparisonBackground("SV_mass_0"); 

	makeComparisonBackground("SV_mass_1"); 

	makeComparisonBackground("SV_vtx_pt_0"); 

	makeComparisonBackground("SV_vtx_pt_1"); 
	makeComparisonBackground("SV_vtx_EnergyRatio_0"); 
	makeComparisonBackground("SV_vtx_EnergyRatio_1");


	makeComparisonBackground("SV_vtx_deltaR_1"); 

	makeComparisonBackground("SV_vtx_deltaR_0"); 
	makeComparisonBackground("trackSumJetEtRatio");
	makeComparisonBackground("trackSumJetDeltaR"); 

	//makeComparisonBackground("trackSip2dValAboveCharm"); 

	//makeComparisonBackground("trackSip2dSigAboveCharm"); 

	// makeComparisonBackground("trackSip3dValAboveCharm"); 

	// makeComparisonBackground("trackSip3dSigAboveCharm"); 

	// makeComparisonBackground("vertexMass"); 

	// makeComparisonBackground("vertexEnergyRatio"); 

	//makeComparisonBackground("vertexJetDeltaR"); 

	// makeComparisonBackground("flightDistance2dVal"); 
	// makeComparisonBackground("flightDistance2dSig");  


   makeComparisonBackground("trackPtRel_0");

        makeComparisonBackground("trackPtRel_1");

        makeComparisonBackground("trackPtRel_2");

        makeComparisonBackground("trackPtRel_3");
        makeComparisonBackground("trackEtaRel_0");
        makeComparisonBackground("trackEtaRel_1");
        makeComparisonBackground("trackEtaRel_2");

//	makeComparisonBackground("flightDistance3dVal"); 
//
//	makeComparisonBackground("flightDistance3dSig"); 
    

//	makeComparisonBackground("trackSip2dSig_0"); 

//	makeComparisonBackground("trackSip2dSig_1"); 
//
//	makeComparisonBackground("trackSip2dSig_2"); 

//	makeComparisonBackground("trackSip2dSig_3"); 

	makeComparisonBackground("trackSip3dSig_0"); 

	makeComparisonBackground("trackSip3dSig_1"); 

	makeComparisonBackground("trackSip3dSig_2"); 

	makeComparisonBackground("trackSip3dSig_3"); 

  //       makeComparisonBackground("SubJet1_JP");
   //     makeComparisonBackground("SubJet1_JBP");
//        makeComparisonBackground("SubJet1_CSV");
//        makeComparisonBackground("SubJet1_CSVIVF");
//	makeComparisonBackground("TagVarCSV1_vertexMass");
//	makeComparisonBackground("TagVarCSV1_vertexEnergyRatio");
///	makeComparisonBackground("TagVarCSV1_vertexJetDeltaR");

//	makeComparisonBackground("SubJet1_pt");       
//	makeComparisonBackground("SubJet1_eta");      
	makeComparisonBackground("nSL"); 
//	makeComparisonBackground("nSE"); 
//	makeComparisonBackground("nSM");
	makeComparisonBackground("nSV"); 
	// makeComparisonBackground("flavour");
	// makeComparisonBackground("nbHadrons");
	makeComparisonBackground("SV_nTrk_0"); 
	makeComparisonBackground("SV_nTrk_1"); 
	makeComparisonBackground("jetNTracksEtaRel");
	//	makeComparisonBackground("jetNSecondaryVertices");
//	makeComparisonBackground("vertexNTracks");
//	makeComparisonBackground("vertexCategory");
	//makeComparisonBackground("TagVarCSV1_vertexCategory");
	//makeComparisonBackground("TagVarCSV1_jetNSecondaryVertices");




	gROOT->ProcessLine(".q");

} 
