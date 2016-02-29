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

// B-tag calibration and SF headers 
//#include "CondFormats/BTauObjects/interface/BTagEntry.h"
//#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
//#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
//#include "BaconSkim/Utils/bin/BTagCalibrationStandalone.h"

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
  const std::string lName        = argv[1];
  const std::string lOption      = argv[2];
  const std::string lJSON        = argv[3];
  const double      lXS          = atof(argv[4]);
  const double      weight       = atof(argv[5]);

  // determine dataset type name
  enum {
    kMC=1,       // MC signal
    kMCWJets,    // MC W + jets
    kMCZJets,    // MC Znunu + jets
    kMCDYJets,   // MC Zll + jets
    kMCWplusHF,  // MC W + jets
    kMCZplusHF,  // MC Znunu + jets
    kMCDYplusHF, // MC Zll + jets
    kMCWplusLF,  // MC W + jets
    kMCZplusLF,  // MC Znunu + jets
    kMCDYplusLF, // MC Zll + jets
    kMCGJets,    // MC gamma + jets
    kMCGplusHF,  // MC gamma + jets
    kMCGplusLF,  // MC gamma + jets
    kMCTTBST,    // top processes with all the top decay products matched to the fat jet
    kMCTTCOM,    // top processes that fail the previous requirement
    kMCTT1L,     // l + j ttbar
    kMCTT2L,     // dilepton ttbar
    kMCTTHAD,    // all had ttbar
    kData        // data
  };

  unsigned int lType=0;
  if     (lOption.compare("mc")==0)         { lType = kMC; }
  else if(lOption.compare("mcwjets")==0)    { lType = kMCWJets;}
  else if(lOption.compare("mczjets")==0)    { lType = kMCZJets;}
  else if(lOption.compare("mcdyjets")==0)   { lType = kMCDYJets;}
  else if(lOption.compare("mcgjets")==0)    { lType = kMCGJets; }
  else if(lOption.compare("mcwplushf")==0)  { lType = kMCWplusHF;}
  else if(lOption.compare("mczplushf")==0)  { lType = kMCZplusHF;}
  else if(lOption.compare("mcdyplushf")==0) { lType = kMCDYplusHF;}
  else if(lOption.compare("mcgplushf")==0)  { lType = kMCGplusHF; }
  else if(lOption.compare("mcwpluslf")==0)  { lType = kMCWplusLF;}
  else if(lOption.compare("mczpluslf")==0)  { lType = kMCZplusLF;}
  else if(lOption.compare("mcdypluslf")==0) { lType = kMCDYplusLF;}
  else if(lOption.compare("mcgpluslf")==0)  { lType = kMCGplusLF; }
  else if(lOption.compare("mcbst")==0)      { lType = kMCTTBST; }
  else if(lOption.compare("mccom")==0)      { lType = kMCTTCOM; }
  else if(lOption.compare("mctt1l")==0)     { lType = kMCTT1L; }
  else if(lOption.compare("mctt2l")==0)     { lType = kMCTT2L; }
  else if(lOption.compare("mctthad")==0)    { lType = kMCTTHAD; }
  else if(lOption.compare("data")==0)       { lType = kData; }
  assert(lType>0);

  fRangeMap = new RunLumiRangeMap();
  if(lJSON.size() > 0) fRangeMap->AddJSONFile(lJSON.c_str());

  TTree *lTree = load(lName); 
  float lWeight = float(lXS)/weight/1000.; if(lType == kData) lWeight = 1.; // xsWgt = 1000.*xsec*gen->weight/weight;
  
  // Declare Readers 
  fEvt      = new EvtLoader     (lTree,lName);                   // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon     = new MuonLoader    (lTree);                         // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron = new ElectronLoader(lTree);                         // fElectrons and fElectronBr, fN = 2
  fTau      = new TauLoader     (lTree);                         // fTaus and fTaurBr, fN = 1
  fPhoton   = new PhotonLoader  (lTree);                         // fPhotons and fPhotonBr, fN = 1
  fJet      = new JetLoader     (lTree);                         // fJets and fJetBr => AK4CHS, fN = 4 - includes jet corrections in a vector (corrParams) and then in a FactorizedJetCorrector: fJetCorr, fN = 4
  fVJet     = new VJetLoader    (lTree,"CA15Puppi","AddCA15Puppi"); // fVJets, fVJetBr =>CA8PUPPI, CA15PUPPI, AK8CHS, CA15CHS fN =1
  if(lType != kData) fGen      = new GenLoader     (lTree);     // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

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
  if(lType != kData) fGen ->setupTree (lOut,float(lXS));

  //
  // Loop over events i0 = iEvent
  //
  //for(int i0 = 0; i0 < int(lTree->GetEntriesFast()); i0++) { 
  for(int i0 = 0; i0 < int(10000); i0++) {
    if(i0 % 1000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(lTree->GetEntriesFast())*100) << " -- " << lOption << std::endl;
    
    // check GenInfo for HF and LF
    fGen->load(i0);
    std::string str = "hf"; if(lOption.find(str)!=std::string::npos && !(fGen->isGenParticle(4)) && !(fGen->isGenParticle(5))) continue;
    str = "lf";             if(lOption.find(str)!=std::string::npos && ((fGen->isGenParticle(4)) || (fGen->isGenParticle(5)))) continue;

    // check GenInfo for ttbar
    str = "tt1l";             if(lOption.find(str)!=std::string::npos && fGen->isttbarType()!=2) continue;
    str = "tt2l";             if(lOption.find(str)!=std::string::npos && fGen->isttbarType()!=1) continue;
    str = "tthad";            if(lOption.find(str)!=std::string::npos && fGen->isttbarType()!=0) continue;
    str = "ttbst";            if(lOption.find(str)!=std::string::npos && fGen->isttbarType()!=2 && fGen->isttbarType()!=1 && fGen->isttbarType()!=0) continue;
    str = "ttcom";            if(lOption.find(str)!=std::string::npos && fGen->isttbarType()!=2 && fGen->isttbarType()!=1 && fGen->isttbarType()!=0) continue;

    // *->load(i0) clear readers and getEntry
    std::vector<TLorentzVector> lVetoes; 

    // primary vertex requirement
    fEvt->load(i0);
    if(!fEvt->PV()) continue;

    // triggerbits
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
    
    // Muons
    fMuon    ->load(i0);
    fMuon    ->selectMuons(lVetoes);

    // SF for muons lepSF,  lep1SFtight, lep2SFtight,  lep1SFloose, lep2SFloose
    //if(fMuon->fNMuons == 1 && fGen->matchParticle(lVetoes[0],13,0.3)) lepSF = getVal2D(hMuTight,fabs(lVetoes[0].Eta()),lVetoes[0].Pt());
    //if(fMuon->fNMuons == 2){
    //  if(fGen->matchParticle(lVetoes[0],13,0.3)) lepSF = getVal2D(hMuTight,fabs(lVetoes[0].Eta()),lVetoes[0].Pt());
    //}

    fEvt->load(i0);
    fEvt->fillEvent(trigbits);

    // DiElectron
    fElectron->load(i0);
    fElectron->selectElectrons(fEvt->fRho,lVetoes);
    
    // Photons
    fPhoton->load(i0);
    fPhoton->selectPhotons(fEvt->fRho,lVetoes);

    // Tau    
    fTau     ->load(i0);
    fTau     ->selectTaus(lVetoes);

    if(lType == kData && !passEvent(fEvt->fRun,fEvt->fLumi)) continue; 

    // MET selection
    fEvt->fillModifiedMet(lVetoes); // what about photons for puppet?
    
    // MET selection
    if(fEvt->fMet < 200. && fEvt->fPuppEt < 200. && fEvt->fFMet < 200. && fEvt->fFPuppEt < 200.) continue;  
    
    // int select = 1;
    // get jets sfs
    // if(lType!=kMCTTBST && lType!=kMCTTCOM) select = select | 16;

    fVJet->load(i0);
    fVJet->selectVJets(lVetoes,1.5,fEvt->fMetPhi,fEvt->fRho);
    
    fJet->load(i0); 
    fJet->selectJets(lVetoes,fEvt->fMetPhi,fEvt->fRho);
    
    // fix Mt
    //fEvt->fillMt(fVJet->fJetPt,fVJet->fJetPhi); 

    fGen->load(i0);
    fGen->selectBoson(2);
    fGen->fillGenEvent();
    
    std::cout << "HERE" << std::endl;
    lOut->Fill();
  }
  lFile->cd();
  lOut->Write();
  lFile->Close();
}
