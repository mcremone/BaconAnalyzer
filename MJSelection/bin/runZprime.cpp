//================================================================================================
//
// Perform preselection for W/Zprime(->qq)+jets events and produce bacon bits 
//
// Input arguments
//   argv[1] => lName = input bacon file name
//   argv[2] => lOption = dataset type: "mc", "mczbb", "mczcc", "mcwcs", "mcvlf", "data"
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
  float lWeight = (float(lXS)*1000.)/weight; if(lOption.find("data")!=std::string::npos) lWeight = 1.;
  
  // Declare Readers 
  fEvt      = new EvtLoader     (lTree,lName);                                           // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon     = new MuonLoader    (lTree);                                                 // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron = new ElectronLoader(lTree);                                                 // fElectrons and fElectronBr, fN = 2
  fTau      = new TauLoader     (lTree);                                                 // fTaus and fTaurBr, fN = 1
  fPhoton   = new PhotonLoader  (lTree);                                                 // fPhotons and fPhotonBr, fN = 1
  fVJetPuppi= new VJetLoader    (lTree,"CA8Puppi","AddCA8Puppi");                        // fVJets, fVJetBr => CA8PUPPI
  fVJetCHS  = new VJetLoader    (lTree,"AK8CHS","AddAK8CHS");                            // fVJets, fVJetBr => AK8CHS
  if(lOption.find("data")==std::string::npos) fGen      = new GenLoader     (lTree);     // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Events","Events");

  // Setup Tree - Set branch address depends on object processor, see src/*Loader.cc
  fEvt      ->setupTree      (lOut,lWeight); 
  fVJetPuppi->setupTree      (lOut,"bst8_PUPPIjet");
  fVJetCHS  ->setupTree      (lOut,"bst8_CHSjet"); 
  fMuon     ->setupTree      (lOut); 
  fElectron ->setupTree      (lOut); 
  fTau      ->setupTree      (lOut); 
  fPhoton   ->setupTree      (lOut); 
  if(lOption.find("data")==std::string::npos) fGen ->setupTree (lOut,float(lXS));

  //
  // Loop over events i0 = iEvent
  //
  int neventstest = 0;
  for(int i0 = 0; i0 < int(lTree->GetEntriesFast()); i0++) {
  //for(int i0 = 0; i0 < int(10); i0++){ // for testing
    if(i0 % 10000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(lTree->GetEntriesFast())*100) << " -- " << lOption << std::endl;
    
    // check GenInfo
    if(lOption.find("data")==std::string::npos)    fGen->load(i0);
    else if(lOption.find("zbb")!=std::string::npos && !fGen->isZbb()) continue;
    else if(lOption.find("zcc")!=std::string::npos && !fGen->isZcc()) continue;
    else if(lOption.find("wcs")!=std::string::npos && !fGen->isWcs()) continue;
    else if(lOption.find("wcs")!=std::string::npos && (fGen->isZbb() || fGen->isZcc() || fGen->isWcs())) continue;
    else{
      if(!passEvent(fEvt->fRun,fEvt->fLumi)) continue;
    }

    // primary vertex requirement
    fEvt->load(i0);           if(!fEvt->PV()) continue;
    
    // triggerbits for PFJet
    // unsigned int trigbits=1;   
    // if(fEvt ->passTrigger("HLT_AK8PFJet360_TrimMass30_v*") ||
    //    fEvt ->passTrigger("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v*")) trigbits = trigbits | 2; 
    // if(trigbits==1) continue;
    
    // Objects
    std::vector<TLorentzVector> lMuons, lElectrons, lPhotons, lJets;
    fEvt      ->load(i0);
    fEvt      ->fillEvent(trigbits);
    fMuon     ->load(i0);
    fMuon     ->selectMuons(lMuons);
    fElectron ->load(i0);
    fElectron ->selectElectrons(fEvt->fRho,lElectrons);
    fTau      ->load(i0);
    fTau      ->selectTaus(lVetoes);
    fPhoton   ->load(i0);
    fPhoton   ->selectPhotons(fEvt->fRho,lElectrons,lPhotons);
        
    // CA8Puppi Jets
    fVJetPuppi->load(i0);
    fVJetPuppi->selectVJets(lVetoes,lJets,1.5,fEvt->fPuppEtPhi,fEvt->fRho);
    
    // AK8CHS Jets
    fVJetCHS  ->load(i0); 
    fVJetCHS  ->selectVJets(lVetoes,lJets,fEvt->fMetPhi,fEvt->fRho);
    
    lOut->Fill();
    neventstest++;
  }
  std::cout << neventstest << std::endl;
  std::cout << lTree->GetEntriesFast() << std::endl;
  lFile->cd();
  lOut->Write();
  lFile->Close();
}
