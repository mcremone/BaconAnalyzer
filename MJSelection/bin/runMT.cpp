//================================================================================================
//
// Driver to run Bacon 
//
// Input arguments
//   argv[1] => maxEvents = max Nevents (-1 = all)
//   argv[2] => lname = .root filename 
//   argv[3] => lgen = 0 if not MC, 1 for MC
//   argv[4] => lJSON = JSON file for run-lumi filtering of data, string size 0 for MC or no filtering
//   argv[5] => lOption < 0 Photon triggers, Photon?
//                      == 0 MET triggers
//                      == 1 Electron triggers, DiElectron vetoes?
//                      > 1 MET triggers, DiMuon vetoes?
//                      < 2
//   Implement lOption for kMC signal, MC Zbb , MC Zcc , MC Wcs ,   MC Vlf, 
//   MC W + jets, MC Znunu + jets, MC Zll + jets, MC gamma + jets (normal, HF, LF) 
//   top processes with all the top decay products matched to the fat jet 
//   top processes that fail the previous requirement
//   l + j ttbar, dilepton, all had, and DATA
//   argv[6] => lXS = cross section (pb), ignored for data
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
  float maxEvents     = atof(argv[1]); 
  std::string lName = argv[2];
  int         lGen  = atoi(argv[3]);
  std::string lJSON = argv[4];
  int         lOption  = atoi(argv[5]);
  double      lXS   = atof(argv[6]);
  fRangeMap = new RunLumiRangeMap();
  if(lJSON.size() > 0) fRangeMap->AddJSONFile(lJSON.c_str());

  TTree *lTree = load(lName); 
  float lWeight = float(lXS)/maxEvents/1000.; if(lGen == 0) lWeight = 1.; //      xsWgt = 1000.*xsec*gen->weight/weight;
  if(lTree->GetEntriesFast() < maxEvents || abs(maxEvents) == 1) maxEvents = float(lTree->GetEntriesFast()); 
  
  // Declare Readers 
  fEvt      = new EvtLoader     (lTree,lName); // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon     = new MuonLoader    (lTree); // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron = new ElectronLoader(lTree); // fElectrons and fElectronBr, fN = 2
  fTau      = new TauLoader     (lTree); // fTaus and fTaurBr, fN = 1
  fPhoton   = new PhotonLoader  (lTree); // fPhotons and fPhotonBr, fN = 1
  fJet      = new JetLoader     (lTree); // fJets and fJetBr => AK4CHS, fN = 4 - includes jet corrections in a vector (corrParams) and then in a FactorizedJetCorrector: fJetCorr, fN = 4
  fVJet     = new VJetLoader    (lTree); // fVJets, fVJetBr =>CA8PUPPI, fVAddJet, fVAddJetBr =>AddCA8Puppi, fFatJets, fFatJetBr => CA15PUPPI, fN =1
  if(lGen == 1) fGen      = new GenLoader     (lTree); // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Tree","Tree");
  int fCut = 0; // fCut - not used 
  lOut->Branch("cut",&fCut,"fCut/I");

  // Setup Tree - Set branch address depends on object processor, see src/*Loader.cc
  fEvt     ->setupTree      (lOut,lWeight); 
  fJet     ->setupTree      (lOut); 
  fVJet    ->setupTree      (lOut); 
  fMuon    ->setupTree      (lOut); 
  fElectron->setupTree      (lOut); 
  fTau     ->setupTree      (lOut); 
  fPhoton  ->setupTree      (lOut); 
  if(lGen == 1) fGen ->setupTree (lOut,float(lXS));

  // Add the triggers we want to a vector of strings i.e. void EvtLoader::addTrigger(std::string iName)
  if(lOption == 0 || lOption > 1) { 
    fEvt ->addTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*");
    fEvt ->addTrigger("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*");
    fEvt ->addTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_NoID_v*");
    fEvt ->addTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*");
    fEvt ->addTrigger("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*");
    fEvt ->addTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_NoID_v*");
    fEvt->addTrigger("HLT_MonoCentralPFJet80_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*");
    fEvt->addTrigger("HLT_MonoCentralPFJet80_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*");
    fEvt->addTrigger("HLT_MonoCentralPFJet80_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*");
    fEvt->addTrigger("HLT_MonoCentralPFJet80_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*");
    //fEvt->addTrigger("HLT_PFMET120_NoiseCleaned_BTagCSV07_v*");
    //fEvt->addTrigger("HLT_PFMET120_NoiseCleaned_BTagCSV0p72_v*");
    //fEvt->addTrigger("HLT_PFMET120_JetIdCleaned_BTagCSV0p72_v*");
    fEvt->addTrigger("HLT_PFMET170_NoiseCleaned_v*");
    fEvt->addTrigger("HLT_PFMET170_JetIdCleaned_v*");
    fEvt->addTrigger("HLT_PFMET170_HBHECleaned_v*");
    fEvt->addTrigger("HLT_PFMET170_v*");
  }
  if(lOption < 0) { 
    fEvt ->addTrigger("HLT_Photon175_v*");
    fEvt ->addTrigger("HLT_Photon165_HE10_v*");
  }
  if(lOption == 1) { 
    fEvt ->addTrigger("HLT_Ele27_WP85_Gsf_v*");
    fEvt ->addTrigger("HLT_Ele27_WPLoose_Gsf_v*");
    fEvt ->addTrigger("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*");
    fEvt ->addTrigger("HLT_Ele22_eta2p1_WPLoose_Gsf_v*");
    //fEvt ->addTrigger("HLT_Ele22_eta2p1_WP75_Gsf_v*");
    //fEvt ->addTrigger("HLT_Ele22_eta2p1_WPLoose_Gsf_v*");
  }

  // Trigger efficiency missing?

  //
  // Loop over events i0 = iEvent
  //
  for(int i0 = 0; i0 < int(maxEvents); i0++) { 
    if(i0 % 1000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(maxEvents)) << " -- " << lOption << std::endl;
    fCut = 0;

    // Load event and require trigger
    // *->load(i0) clear readers and getEntry
    std::vector<TLorentzVector> lVetoes; 

    // Select Di Muon
    if(lOption > 1) { 
      fMuon->load(i0); 
      fMuon->selectMuons(lVetoes);
      double pMass = fMuon->fillDiMuon(); // diMuon mass
      if(lVetoes.size() == 0) continue;
      if((pMass < 60 || pMass > 120) && lVetoes.size() > 1) continue;
    }
    fEvt     ->load(i0);
    fEvt     ->fillEvent();
    if(lOption == 1) { 
      fElectron->load(i0);
      fElectron->selectElectrons(fEvt->fRho,lVetoes);
      double pMass = fElectron->fillDiElectron(); // diElectron mass
      if(lVetoes.size() == 0) continue;
      if((pMass < 60 || pMass > 120) && lVetoes.size() > 1) continue;
    }
    if(lOption < 0) { 
      fPhoton->load(i0);
      if(fPhoton->selectPhotons(fEvt->fRho,lVetoes) == 0) continue;
      if(fPhoton->fSelPhotons.size() == 0) continue;
      if(lVetoes.size() > 0) fMuon  ->setDiMuon(lVetoes[0]);
    }

    ///Normal processing afterwards
    if(lGen == 0 && !passEvent(fEvt->fRun,fEvt->fLumi)) continue;
    if(lOption  < 2) {
      fMuon    ->load(i0);    
      //if(fMuon    ->selectMuons(lVetoes) > 0) fCut  += 1.;
      if(fMuon    ->selectMuons(lVetoes) > 0) continue;
    }
    if(lOption != 1) { 
      fElectron->load(i0);
      //if(fElectron->selectElectrons(fEvt->fRho,lVetoes) > 0) fCut = 10.;
      if(fElectron->selectElectrons(fEvt->fRho,lVetoes) > 0) continue;
    }  
    fTau     ->load(i0);
    //if(fTau     ->selectTaus(lVetoes) > 0) fCut += 100.;
    if(fTau     ->selectTaus(lVetoes) > 0) continue;
    if(lOption > -1) {
      fPhoton  ->load(i0);
      //if(fPhoton  ->selectPhotons(fEvt->fRho,lVetoes) > 0) fCut += 1000.;
      if(fPhoton  ->selectPhotons(fEvt->fRho,lVetoes) > 0) continue;
    }

    //Setup
    std::vector<TLorentzVector> lSig;
    if(lOption <  0 && fPhoton->fNPhotonsTight > 0) lSig.push_back(lVetoes[0]);
    if(lOption >  0 && lVetoes.size()          > 0) lSig.push_back(lVetoes[0]);    
    if(lOption >  1 && fMuon->fNMuons          > 1) lSig.push_back(lVetoes[1]);
    if(lOption == 1 && fElectron->fNElectrons  > 1 ) lSig.push_back(lVetoes[1]);
    if(lOption != 0) fEvt->fillModifiedMet(lSig); 
    if(fEvt->fMet < 100.) continue;
    //if(fEvt->fMet < 100.) fCut += 10000.;
    fVJet->load(i0);
    fVJet->selectVJets(lVetoes);
    fJet->load(i0); 
    fJet->selectJets(lVetoes,fEvt->fMetPhi,fEvt->fRho);
    if(lGen == 1) {
      fGen->load(i0);
      fGen->selectBoson(lOption);
      fGen->fillGenEvent();
    }
    lOut->Fill();
  }
  lFile->cd();
  lOut->Write();
  lFile->Close();
}
