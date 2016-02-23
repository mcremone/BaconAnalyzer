//Driver to run Bacon 
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

//Object Processors
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

TTree* load(std::string iName) { 
  TFile *lFile = TFile::Open(iName.c_str());
  TTree *lTree = (TTree*) lFile->FindObjectAny("Events");
  fHist        = (TH1F* ) lFile->FindObjectAny("TotalEvents");
  return lTree;
}
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
  if(maxEvents == -1) maxEvents = float(lTree->GetEntriesFast()); 
  float lWeight = float(lXS)/maxEvents/1000.; if(lGen == 0) lWeight = 1.;
  if(lTree->GetEntriesFast() < maxEvents) maxEvents = float(lTree->GetEntriesFast()); 
  
  //Declare Readers
  fEvt      = new EvtLoader     (lTree,lName);
  fMuon     = new MuonLoader    (lTree);
  fElectron = new ElectronLoader(lTree);
  fTau      = new TauLoader     (lTree); 
  fPhoton   = new PhotonLoader  (lTree); 
  fJet      = new JetLoader     (lTree);
  fVJet     = new VJetLoader    (lTree);
  if(lGen == 1) fGen      = new GenLoader     (lTree);

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Tree","Tree");
  //Setup Tree
  fEvt     ->setupTree      (lOut,lWeight);
  fJet     ->setupTree      (lOut); 
  fVJet    ->setupTree      (lOut); 
  fMuon    ->setupTree      (lOut); 
  fElectron->setupTree      (lOut); 
  fTau     ->setupTree      (lOut); 
  fPhoton  ->setupTree      (lOut); 
  //if(lGen == 1) fGen ->setupTree (lOut,float(lXS));
  //Add the triggers we want
  fEvt ->addTrigger("HLT_PFJet320_v*");
  fEvt ->addTrigger("HLT_Jet370_NoJetID_v*");
  fEvt ->addTrigger("HLT_DiPFJetAve400_v*");
  for(int i0 = 0; i0 < int(maxEvents); i0++) { 
    if(i0 % 1000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(maxEvents)) << " -- " << lOption << std::endl;
    //Load event and require trigger
    std::vector<TLorentzVector> lVetoes; 
    fVJet->load(i0);
    if(!fVJet->selectVJets(lVetoes,true)) continue;
    fEvt     ->load(i0);
    fEvt     ->fillEvent();
    //Lepton Vetoes
    if(lGen == 0 && !passEvent(fEvt->fRun,fEvt->fLumi))    continue;
    fMuon    ->load(i0);     
    if(fMuon    ->selectMuons(lVetoes) > 0)                continue;
    fElectron->load(i0);
    if(fElectron->selectElectrons(fEvt->fRho,lVetoes) > 0) continue;
    fTau     ->load(i0);
    if(fTau     ->selectTaus(lVetoes) > 0)                 continue;
    fPhoton  ->load(i0);
    if(fPhoton  ->selectPhotons(fEvt->fRho,lVetoes) > 0)   continue;
    //Setup
    fJet->load(i0); 
    fJet->selectJets(lVetoes,fEvt->fMetPhi,fEvt->fRho);
    if(lGen == 1) {
      fGen->load(i0);
      fGen->selectBoson(lOption);
      fGen->fillGenEvent();
      //if(fGen->fBoson != 0) fVJet->addBoson(fGen->fBoson);
    }
    lOut->Fill();
  }
  lFile->cd();
  lOut->Write();
  lFile->Close();
}
