//================================================================================================
//
// Perform preselection for hadronic mono-X events and produce bacon bits 
//
// Input arguments
//   argv[1] => lName = input bacon file name
//   argv[2] => lOption = dataset type: "mc", 
//                            "mcwplushf",  "mcwpluslf",
//                            "mczplushf",  "mczpluslf",
//                            "mcdyplushf", "mcdypluslf",
//                            "mcgplushf",  "mcgpluslf",
//                            "mctt",
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
GenLoader        *fGen      = 0; 
EvtLoader        *fEvt      = 0; 
MuonLoader       *fMuon     = 0; 
ElectronLoader   *fElectron = 0; 
TauLoader        *fTau      = 0; 
PhotonLoader     *fPhoton   = 0; 
JetLoader        *fJet      = 0; 
VJetLoader       *fVJet15   = 0;
RunLumiRangeMap  *fRangeMap = 0; 

TH1F *fHist                 = 0; 

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
  
  // Declare Readers 
  fEvt      = new EvtLoader       (lTree,lName);                                           // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon     = new MuonLoader      (lTree);                                                 // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron = new ElectronLoader  (lTree);                                                 // fElectrons and fElectronBr, fN = 2
  fTau      = new TauLoader       (lTree);                                                 // fTaus and fTaurBr, fN = 1
  fPhoton   = new PhotonLoader    (lTree);                                                 // fPhotons and fPhotonBr, fN = 1
  fJet      = new JetLoader       (lTree);                                                 // fJets and fJetBr => AK4PUPPI, fN = 4 - includes jet corrections (corrParams), fN = 4
  fVJet15   = new VJetLoader      (lTree,"CA15Puppi","AddCA15Puppi");                      // fVJets, fVJetBr =>CA8PUPPI, CA15PUPPI, AK8CHS, CA15CHS fN =1
  if(lOption.find("data")==std::string::npos) fGen      = new GenLoader     (lTree);       // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Events","Events");
  
  // Setup Tree
  fEvt      ->setupTree           (lOut); 
  fMuon     ->setupTree           (lOut);
  fElectron ->setupTree           (lOut);
  fTau      ->setupTree           (lOut);
  fPhoton   ->setupTree           (lOut);
  fJet      ->setupTree           (lOut,"res_PUPPIjet"); 
  fVJet15   ->setupTree           (lOut,"bst15_PUPPIjet"); 
  if(lOption.find("data")==std::string::npos) fGen ->setupTree (lOut,float(lXS));

  //
  // Loop over events
  //
  int neventstest = 0;
  for(int i0 = 0; i0 < int(lTree->GetEntriesFast()); i0++) {
  //for(int i0 = 0; i0 < int(10000); i0++){ // for testing
    // if(i0 % 10000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(lTree->GetEntriesFast())*100) << " -- " << lOption << std::endl;
    
    // Check json and GenInfo
    fEvt->load(i0);
    float lWeight = 1;
    if(lOption.find("data")!=std::string::npos){
      if(!passEvent(fEvt->fRun,fEvt->fLumi))                                                              continue;
    }
    else{
      fGen->load(i0);
      lWeight = (float(lXS)*1000.*fGen->fWeight)/weight;
    }

    // Primary vertex requirement
    if(!fEvt->PV()) continue;
    
    unsigned int trigbits=1;    
   
    // Objects
    std::vector<TLorentzVector> lMuons, lElectrons, lPhotons, lJets, lVJet15, lVJets15, lVetoes;
    std::vector<const TJet*> lGoodJets15, lGoodJetsCHS15;

    // Muons
    fMuon->load(i0);
    fMuon->selectMuons(lMuons);
    
    fEvt->fillEvent(trigbits,lWeight);
    
    // Electrons
    fElectron->load(i0);
    fElectron->selectElectrons(fEvt->fRho,lElectrons);
    
    // Fill Vetoes
    fEvt->fillVetoes(lElectrons,lVetoes);
    fEvt->fillVetoes(lMuons,lVetoes);
    
    // Taus
    fTau->load(i0);
    fTau->selectTaus(lVetoes);
    
    // Photons
    fPhoton->load(i0);
    fPhoton->selectPhotons(fEvt->fRho,lElectrons,lPhotons);
    
    // MET selection
    if(fEvt->fMet < 170. && fEvt->fPuppEt < 170. && fEvt->fFPuppEt < 170. && fEvt->fFMet < 170.) continue;
    
    // CA15Puppi Jets
    fVJet15->load(i0);
    fVJet15->selectVJets(lVetoes,lVJets15,lVJet15,1.5,fEvt->fRho,"looseJetID");
    if(lVJets15.size()>0) { 
      if(lOption.find("data")==std::string::npos){
	fVJet15->fisHadronicTop = fGen->ismatchedJet(lVJet15[0],1.5,fVJet15->ftopMatching,fVJet15->ftopSize);
	fVJet15->fisHadronicV = fGen->ismatchedJet(lVJet15[0],0.8,fVJet15->fvMatching,fVJet15->fvSize,25);
      }
      fEvt->fselectBits = fEvt->fselectBits | 2;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lVJet15,fVJet15->fVMT);
    }
    
    // AK4Puppi Jets
    fJet->load(i0); 
    fJet->selectJets(lVetoes,lVJets15,lJets,fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi);
    if(lJets.size()>0){
      fJet->fillGoodJets(lVJets15,1.5,lGoodJets15);
      fEvt->fselectBits =  fEvt->fselectBits | 4;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lJets,fJet->fMT);
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
