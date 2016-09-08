//================================================================================================
//
// Perform preselection for Lepton+Jets TT events and produce bacon bits 
//
// Input arguments
//   argv[1] => lName = input bacon file name
//   argv[2] => lOption = dataset type: "mc", "data"
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
#include "../include/BTagWeightLoader.hh"
#include "../include/RunLumiRangeMap.h"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

// Object Processors
GenLoader        *fGen        = 0; 
EvtLoader        *fEvt        = 0; 
MuonLoader       *fMuon       = 0; 
ElectronLoader   *fElectron   = 0; 
TauLoader        *fTau        = 0; 
PhotonLoader     *fPhoton     = 0; 
JetLoader        *fJet        = 0;
VJetLoader       *fVJet8      = 0;
BTagWeightLoader *fBTag       = 0; 
RunLumiRangeMap  *fRangeMap   = 0; 

TH1F *fHist                   = 0; 

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

// === MAIN =======================================================================================================
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
  
  // Declare Readers 
  fEvt       = new EvtLoader       (lTree,lName);
  fMuon      = new MuonLoader      (lTree);
  fElectron  = new ElectronLoader  (lTree);
  fTau       = new TauLoader       (lTree);
  fPhoton    = new PhotonLoader    (lTree);
  fJet       = new JetLoader       (lTree);
  fBTag      = new BTagWeightLoader(lTree);
  fVJet8     = new VJetLoader      (lTree,"AK8Puppi","AddAK8Puppi");             
  if(lOption.compare("data")!=0) fGen      = new GenLoader     (lTree);        

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Events","Events");

  // Setup Tree
  fEvt      ->setupTree      (lOut); 
  fJet      ->setupTree      (lOut,"AK4Puppijet");
  fBTag     ->setupTree      (lOut,"AK4Puppijet");
  fVJet8    ->setupTree      (lOut,"AK8Puppijet"); 
  fMuon     ->setupTree      (lOut); 
  fElectron ->setupTree      (lOut); 
  fTau      ->setupTree      (lOut); 
  fPhoton   ->setupTree      (lOut); 
  if(lOption.compare("data")!=0) fGen ->setupTree (lOut,float(lXS));

  // Loop over events i0 = iEvent
  int neventstest = 0;
  for(int i0 = 0; i0 < int(lTree->GetEntriesFast()); i0++) {
  // for(int i0 = 0; i0 < int(10); i0++){ // for testing

    // Check GenInfo
    fEvt->load(i0);
    float lWeight = 1;
    if(lOption.compare("data")!=0){
      fGen->load(i0);
      lWeight = (float(lXS)*1000.*fGen->fWeight)/weight;
    }
    else{
      if(!passEvent(fEvt->fRun,fEvt->fLumi)) continue;
    }

    // Primary vertex requirement
    if(!fEvt->PV()) continue;
    
    // Triggerbits
    unsigned int trigbits=1;   
    if(lOption.find("data")!=std::string::npos){
      if(fEvt ->passTrigger("HLT_Mu45_eta2p1_v*")
         ) trigbits = trigbits | 2;
      // if(trigbits==1) continue;
    }
    fEvt      ->fillEvent(trigbits,lWeight);
    
    // Objects
    std::vector<TLorentzVector> cleaningMuons, cleaningElectrons, cleaningPhotons;
    fMuon     ->load(i0);
    fMuon     ->selectMuons(cleaningMuons,fEvt->fMet,fEvt->fMetPhi);
    fElectron ->load(i0);
    fElectron ->selectElectrons(fEvt->fRho,cleaningElectrons);
    fTau      ->load(i0);
    fTau      ->selectTaus(cleaningElectrons, cleaningMuons);
    fPhoton   ->load(i0);
    fPhoton   ->selectPhotons(fEvt->fRho,cleaningElectrons,cleaningPhotons);
        
    // Lepton and Photon SF    
    if(lOption.find("data")==std::string::npos){
      fEvt->fillLepSF(fMuon->looseMuons,13,fMuon->fismu0Tight,fMuon->fismu1Tight);
      fEvt->fillLepSF(fElectron->looseElectrons,11,fElectron->fisele0Tight,fElectron->fisele1Tight);
    }
    fEvt      ->triggerEff(fElectron->looseElectrons, cleaningPhotons);

    // AK8Puppi Jets
    fVJet8    ->load(i0);
    fVJet8    ->selectVJets(cleaningElectrons,cleaningMuons,cleaningPhotons,0.8,fEvt->fRho);
    if(fVJet8->selectedVJets.size()>0){ fEvt->fselectBits =  fEvt->fselectBits | 2;}

    // AK4Puppi Jets
    fJet     ->load(i0);
    fJet     ->selectJets(cleaningElectrons,cleaningMuons,cleaningPhotons,fVJet8->selectedVJets,fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi);
    fJet     ->fillGoodJets(fVJet8->selectedVJets,0.8,fJet->selectedJets8);
    if(lOption.find("data")==std::string::npos)  fBTag->fillBTag(fJet->selectedJets8);
    if(fJet->selectedJets.size()>0){ fEvt->fselectBits =  fEvt->fselectBits | 4;}

    // Select at least one AK8 or one AK4 jet
    if(!(fEvt->fselectBits & 2) || !(fEvt->fselectBits & 4)) continue;

    // TTbar, EWK and kFactor correction
    if(lName.find("ZJets")!=std::string::npos || lName.find("DYJets")!=std::string::npos){
      fGen->findBoson(23,0);
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"ZJets_012j_NLO/nominal","ZJets_LO/inv_pt","EWKcorr/Z","ZJets_012j_NLO");
      if(fVJet8->selectedVJets.size()>0)  fVJet8->fisHadronicV = fGen->ismatchedJet(fVJet8->selectedVJets[0],0.8,fVJet8->fvMatching,fVJet8->fvSize,23);
    }
    if(lName.find("WJets")!=std::string::npos){
      fGen->findBoson(24,1);
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"WJets_012j_NLO/nominal","WJets_LO/inv_pt","EWKcorr/W","WJets_012j_NLO");
      if(fVJet8->selectedVJets.size()>0)  fVJet8->fisHadronicV = fGen->ismatchedJet(fVJet8->selectedVJets[0],0.8,fVJet8->fvMatching,fVJet8->fvSize,24);
    }
    if(lName.find("TTJets")!=std::string::npos){
      fEvt->fevtWeight *= fGen->computeTTbarCorr();
      if(lOption.find("tt1l")!=std::string::npos) fGen->findBoson(24,2);
      if(lOption.find("tt2l")!=std::string::npos) fGen->findBoson(6,3);
    }

    lOut->Fill();
    neventstest++;
  }
  std::cout << neventstest << std::endl;
  std::cout << lTree->GetEntriesFast() << std::endl;
  lFile->cd();
  lOut->Write();
  lFile->Close();
}
