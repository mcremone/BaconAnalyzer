{
  gSystem->CompileMacro("plotDistributions.C");

  TFile *fSig76 = new TFile("/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/singlebbits/Zprime.root");
  TFile *fSig74 = new TFile("/tmp/cmantill/Zprime74.root");
  TFile *fBg76 = new TFile("/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/singlebbits/QCD.root");
  TFile *fBg74 = new TFile("/tmp/cmantill/QCD74.root");

  TTree *tSig76 = (TTree*)fSig76->Get("Events");
  TTree *tSig74 = (TTree*)fSig74->Get("Events");
  TTree *tBg76 = (TTree*)fBg76->Get("Events");
  TTree *tBg74 = (TTree*)fBg74->Get("Events");

  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_maxsubcsv","bst15_PUPPIjet1maxsubcsv",20,0,1);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_pt","bst15_PUPPIjet1.Pt()",20,0,800);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_nTracks","bst15_PUPPIjet1nTracks",24,0,24);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_nSV","bst15_PUPPIjet1nSV",10,0,10);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_trackSip2dSigAboveCharm_0","bst15_PUPPIjet1trackSip2dSigAboveCharm",10,-1,30);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_trackSip2dSigAboveBottom_0","bst15_PUPPIjet1trackSip2dSigAboveBottom",10,-1,30);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_trackSip3dSig_3","bst15_PUPPIjet1trackSip3dSig_3",10,-1,30);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_trackSip3dSig_2","bst15_PUPPIjet1trackSip3dSig_2",10,-1,30);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_trackSip3dSig_1","bst15_PUPPIjet1trackSip3dSig_1",10,-1,30);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_trackSip3dSig_0","bst15_PUPPIjet1trackSip3dSig_0",10,-1,30);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_flightDistance2dSig","bst15_PUPPIjet1tau_SVmass_flightDistance2dSig",20,-1,100);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_vertexDeltaR","bst15_PUPPIjet1tau_SVmass_vertexDeltaR",15,-1,1);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_vertexNTracks","bst15_PUPPIjet1tau_SVmass_vertexNTracks",20,0,20);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_2","bst15_PUPPIjet1tau_SVmass_trackEtaRel_2",20,-1,10);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_1","bst15_PUPPIjet1tau_SVmass_trackEtaRel_1",20,-1,10);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_0","bst15_PUPPIjet1tau_SVmass_trackEtaRel_0",20,-1,10);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_vertexEnergyRatio","bst15_PUPPIjet1tau_SVmass_vertexEnergyRatio",20,-1,10);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_vertexMass","bst15_PUPPIjet1tau_SVmass_vertexMass",20,-1,30);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_vertexMass_corrected","bst15_PUPPIjet1tau_SVmass_vertexMass_corrected",20,-1,60);
  plotDistributions(tSig76,tBg76,tSig74,tBg74,"bst15_PUPPIjet0_tau_SVmass0_zratio","bst15_PUPPIjet1tau_SVmass_zratio",20,-1,50);
  gROOT->ProcessLine(".q");
}
