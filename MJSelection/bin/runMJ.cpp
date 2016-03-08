//================================================================================================
//
// Driver to run Bacon 
//
// Input arguments
//   argv[1] => lname = input bacon file name
//   argv[2] => lOption = dataset type: "mc", 
//                            "mcwjets",  "mcwplushf",  "mcwpluslf",
//                            "mczjets",  "mczplushf",  "mczpluslf",
//                            "mcdyjets", "mcdyplushf", "mcdypluslf",
//                            "mcgjets",  "mcgplushf",  "mcgpluslf",
//                            "mcbst",    "mccom",
//                            "mctt1l",   "mctt2l",     "mctthad",
//                            "data"
//   argv[3] => lJSON = JSON file for run-lumi filtering of data, specify "none" for MC or no filtering
//   argv[4] => lXS = cross section (pb), ignored for data 
//   argv[5] => weight = total weight, ignored for data
//________________________________________________________________________________________________

#include "../include/GenLoader.hh"
#include "../include/EvtLoader.hh"
#include "../include/ElectronLoader.hh"
#include "../include/MuonLoader.hh"
#include "../include/PhotonLoader.hh"
#include "../include/TauLoader.hh"
#include "../include/JetLoader.hh"
#include "../include/VJetLoader.hh"
#include "../include/RunLumiRangeMap.h"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

// Object Processors
GenLoader       *fGen      = 0; 
EvtLoader       *fEvt      = 0; 
MuonLoader      *fMuon     = 0; 
ElectronLoader  *fElectron = 0; 
TauLoader       *fTau      = 0; 
PhotonLoader    *fPhoton   = 0; 
JetLoader       *fJet      = 0; 
VJetLoader      *fVJet     = 0;
RunLumiRangeMap *fRangeMap = 0; 

//VJetLoader      *fVJet1     = 0;
//VJetLoader      *fVJet2     = 0;
//VJetLoader      *fVJet3     = 0;

TH1F *fHist                = 0; 

// Load tree and return infile
TTree* load(std::string iName) { 
  TFile *lFile = TFile::Open(iName.c_str());
  TTree *lTree = (TTree*) lFile->FindObjectAny("Events");
  fHist        = (TH1F* ) lFile->FindObjectAny("TotalEvents");
  return lTree;
}

// For Json 
bool passEvent(unsigned int iRun,unsigned int iLumi) { 
  RunLumiRangeMap::RunLumiPairType lRunLumi(iRun,iLumi);
  return fRangeMap->HasRunLumi(lRunLumi);
}

int main( int argc, char **argv ) {
  gROOT->ProcessLine("#include <vector>");
  const std::string lName        = argv[1];
  const std::string lOption      = argv[2];
  const std::string lJSON        = argv[3];
  const double      lXS          = atof(argv[4]);
  const double      weight       = atof(argv[5]);

  fRangeMap = new RunLumiRangeMap();
  if(lJSON.size() > 0) fRangeMap->AddJSONFile(lJSON.c_str());

  TTree *lTree = load(lName); 
  float lWeight = (float(lXS)*1000.)/weight; if(lOption.find("data")!=std::string::npos) lWeight = 1.;
  
  // Declare Readers 
  fEvt      = new EvtLoader     (lTree,lName);                                           // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon     = new MuonLoader    (lTree);                                                 // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron = new ElectronLoader(lTree);                                                 // fElectrons and fElectronBr, fN = 2
  fTau      = new TauLoader     (lTree);                                                 // fTaus and fTaurBr, fN = 1
  fPhoton   = new PhotonLoader  (lTree);                                                 // fPhotons and fPhotonBr, fN = 1
  fJet      = new JetLoader     (lTree);                                                 // fJets and fJetBr => AK4CHS, fN = 4 - includes jet corrections (corrParams), fN = 4, Implement AK4CHS?
  fVJet     = new VJetLoader    (lTree,"CA15Puppi","AddCA15Puppi");                      // fVJets, fVJetBr =>CA8PUPPI, CA15PUPPI, AK8CHS, CA15CHS fN =1
  if(lOption.find("data")==std::string::npos) fGen      = new GenLoader     (lTree);     // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

  // for other types of jets and cone sizes
  //fVJet1    = new VJetLoader    (lTree,"CA15CHS","AddCA15CHS");
  //fVJet2    = new VJetLoader    (lTree,"CA8Puppi","AddCA8Puppi");
  //fVJet3    = new VJetLoader    (lTree,"AK8CHS","AddAK8CHS");

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Events","Events");

  // Setup Tree - Set branch address depends on object processor, see src/*Loader.cc
  fEvt     ->setupTree      (lOut,lWeight); 
  fJet     ->setupTree      (lOut,"res_PUPPIjet"); 
  fVJet    ->setupTree      (lOut,"bst15_PUPPIjet"); 
  fMuon    ->setupTree      (lOut); 
  fElectron->setupTree      (lOut); 
  fTau     ->setupTree      (lOut); 
  fPhoton  ->setupTree      (lOut); 
  if(lOption.find("data")==std::string::npos) fGen ->setupTree (lOut,float(lXS));

  // for other types of jets and cone sizes
  //fVJet1 ->setupTree      (lOut,"bst15_CHSjet");
  //fVJet2 ->setupTree      (lOut,"bst8_PUPPIjet");
  //fVJet3 ->setupTree      (lOut,"bst8_PUPPIjet");

  //
  // Loop over events i0 = iEvent
  //
  int neventstest = 0;
  //for(int i0 = 0; i0 < int(lTree->GetEntriesFast()); i0++) {
  for(int i0 = 0; i0 < int(100); i0++){ // for testing
    if(i0 % 1000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(lTree->GetEntriesFast())*100) << " -- " << lOption << std::endl;
    
    // check GenInfo
    fGen->load(i0);
    if(lOption.find("hf")!=std::string::npos && !(fGen->isGenParticle(4)) && !(fGen->isGenParticle(5)))                     continue;
    if(lOption.find("lf")!=std::string::npos && ((fGen->isGenParticle(4)) || (fGen->isGenParticle(5))))                     continue; 
    if(lOption.find("tt2l")!=std::string::npos && fGen->isttbarType()!=2)                                                     continue;
    if(lOption.find("tt1l")!=std::string::npos && fGen->isttbarType()!=1)  continue;
    if(lOption.find("tthad")!=std::string::npos && fGen->isttbarType()!=0)                                                     continue;
    if(lOption.find("ttbst")!=std::string::npos && fGen->isttbarType()!=2 && fGen->isttbarType()!=1 && fGen->isttbarType()!=0) continue;
    if(lOption.find("ttcom")!=std::string::npos && fGen->isttbarType()!=2 && fGen->isttbarType()!=1 && fGen->isttbarType()!=0) continue;
    
    // primary vertex requirement
    fEvt->load(i0);           if(!fEvt->PV()) continue;
    
    // triggerbits for MET, Electrons, Photons and Muons
    unsigned int trigbits=1;    
    if(fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_NoID_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_NoID_v*")) trigbits = trigbits | 2; 
    if(fEvt ->passTrigger("HLT_Ele27_WP85_Gsf_v*") ||
       fEvt ->passTrigger("HLT_Ele27_WPLoose_Gsf_v*") ||
       fEvt ->passTrigger("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*"))  trigbits = trigbits | 4;
    if(fEvt ->passTrigger("HLT_Photon175_v*") ||
       fEvt ->passTrigger("HLT_Photon165_HE10_v*")) trigbits = trigbits | 8;
    if(trigbits==1) continue;
    
    // Objects
    std::vector<TLorentzVector> lMuons, lElectrons, lPhotons, lVetoes;
    // Muons
    fMuon    ->load(i0);
    fMuon    ->selectMuons(lMuons);
    
    fEvt      ->load(i0);
    fEvt      ->fillEvent(trigbits);
      
    // Electrons
    fElectron ->load(i0);
    fElectron ->selectElectrons(fEvt->fRho,lElectrons);
    
    // Lepton SF
    fEvt->leptonSF(lMuons,lElectrons,fGen->ismatched(13,lMuons,0.3),fGen->ismatched(11,lElectrons,0.3));

    // Fill Vetoes
    fEvt->fillVetoes(lElectrons,lVetoes);
    fEvt->fillVetoes(lMuons,lVetoes);

    if(lOption.find("data")!=std::string::npos && !passEvent(fEvt->fRun,fEvt->fLumi)) continue;

    // Taus
    fTau     ->load(i0);
    fTau     ->selectTaus(lVetoes);

    // Photons
    fPhoton  ->load(i0);
    fPhoton  ->selectPhotons(fEvt->fRho,lElectrons,lPhotons);

    // MET selection
    fEvt->fillModifiedMet(lVetoes,lPhotons);
    if(fMuon->fNMuons == 0 && fEvt->fMet < 200. && fEvt->fPuppEt < 200. && fEvt->fFPuppEt < 200. && fEvt->fFMet < 200.) continue;
    //std::cout << i0 << " " << fEvt->fPuppEt << " " << fEvt->fFPuppEt << std::endl;

    // Trigger Efficiencies
    fEvt->triggerEff(lElectrons, lPhotons);
    //std::cout << fEvt->fEffTrigger << " " << lElectrons.size() << " " << lPhotons.size() << std::endl;
    //if(lElectrons.size() > 0 ) std::cout << lElectrons[0].Pt() << " " << lElectrons[0].Eta() << std::endl;

    // CA15Puppi Jets
    fVJet->load(i0);
    fVJet->selectVJets(lVetoes,1.5,fEvt->fMetPhi,fEvt->fRho);

    // int select = 1;
    // float top_size = 0;
    // match to top quark decay products
    // if(lType==kMCTTBST && ismatchedJet(fVJet->fSelVJets[0],1.5)) select = select | 2; // ask Matteo - which jet is it?
    // if(lType==kMCTTCOM && !ismatchedJet(fVJet->fSelVJets[0],1.5)) select = select | 2;
    // if(lType!=kMCTTBST && lType!=kMCTTCOM) select = select | 2;

    // AK4PUPPI Jets
    fJet->load(i0); 
    fJet->selectJets(lVetoes,fEvt->fMetPhi,fEvt->fRho);
    
    // fix Mt
    //fEvt->fillMt(fVJet->fJetPt,fVJet->fJetPhi);

    // ttbar, EWK and kFactor correction
    fGen->load(i0);
    if(lOption.find("mcg")!=std::string::npos){
      fGen->findBoson(22,0); // no matching
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"anlo1/anlo1_nominal","alo/alo_nominal","a_ewkcorr/a_ewkcorr");
    }
    if(lOption.find("mcz")!=std::string::npos || lOption.find("mcdy")!=std::string::npos){
      fGen->findBoson(23,0);
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"znlo012/znlo012_nominal","zlo/zlo_nominal","z_ewkcorr/z_ewkcorr");
    }
    if(lOption.find("mcw")!=std::string::npos){
      fGen->findBoson(24,0);
      if(fGen->fBosonPt>0){ fEvt->computeCorr(fGen->fBosonPt,"wnlo012/wnlo012_nominal","wlo/wlo_nominal","w_ewkcorr/w_ewkcorr"); }//std::cout << i0 << " " << fGen->fBosonPt << std::endl;}
    }
    if(lOption.find("tt")!=std::string::npos){
      fEvt->fevtWeight = fEvt->fevtWeight * fGen->computeTTbarCorr();
      if(lOption.find("tt1l")!=std::string::npos) fGen->findBoson(24,1);
      if(lOption.find("tt2l")!=std::string::npos) fGen->findBoson(6,1);
    }

    //fGen->selectBoson(2); // have to figure out if I will need this
    //fGen->fillGenEvent();
    
    //std::cout << "Filling Events tree" << std::endl;
    lOut->Fill();
    neventstest++;
  }
  std::cout << neventstest << std::endl;
  std::cout << lTree->GetEntriesFast() << std::endl;
  lFile->cd();
  lOut->Write();
  lFile->Close();
}
