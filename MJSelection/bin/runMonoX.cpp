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
#include "../include/BTagWeightLoader.hh"
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
VJetLoader       *fVJet8T   = 0;
BTagWeightLoader *fBTag     = 0;
BTagWeightLoader *fBTag15   = 0;
BTagWeightLoader *fBTag8T   = 0;
RunLumiRangeMap  *fRangeMap = 0; 

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
  
  // Declare Readers 
  fEvt      = new EvtLoader     (lTree,lName);                                           // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon     = new MuonLoader    (lTree);                                                 // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron = new ElectronLoader(lTree);                                                 // fElectrons and fElectronBr, fN = 2
  fTau      = new TauLoader     (lTree);                                                 // fTaus and fTaurBr, fN = 1
  fPhoton   = new PhotonLoader  (lTree);                                                 // fPhotons and fPhotonBr, fN = 1
  fJet      = new JetLoader     (lTree);                                                 // fJets and fJetBr => AK4PUPPI, fN = 4 - includes jet corrections (corrParams), fN = 4
  fVJet15   = new VJetLoader    (lTree,"CA15Puppi","AddCA15Puppi");                      // fVJets, fVJetBr =>CA8PUPPI, CA15PUPPI, AK8CHS, CA15CHS fN =1
  fVJet8T   = new VJetLoader    (lTree,"CA8Puppi","AddCA8Puppi");
  if(lOption.find("data")==std::string::npos) fGen      = new GenLoader     (lTree);     // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Events","Events");

  // Setup Tree
  fEvt     ->setupTree      (lOut); 
  fMuon    ->setupTree      (lOut);
  fElectron->setupTree      (lOut);
  fTau     ->setupTree      (lOut);
  fPhoton  ->setupTree      (lOut);
  fJet     ->setupTree      (lOut,"res_PUPPIjet"); 
  fJet     ->setupTree      (lOut,"res_PUPPIjet");
  fBTag    ->setupTree      (lOut,"res_PUPPIjet");
  fBTag15  ->setupTree      (lOut,"res_PUPPIjetbst15");
  fBTag8T  ->setupTree      (lOut,"res_PUPPIjetbst8T");
  fVJet15  ->setupTree           (lOut,"bst15_PUPPIjet"); 
  fVJet15  ->setupTreeSubJetBTag (lOut,"bst15_PUPPIjet");
  fVJet8T  ->setupTree           (lOut,"bst8_PUPPIjetT");
  fVJet8T  ->setupTreeSubJetBTag (lOut,"bst8_PUPPIjetT");
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
      if(lOption.find("hf")!=std::string::npos && !(fGen->isGenParticle(4)) && !(fGen->isGenParticle(5))) continue;
      if(lOption.find("lf")!=std::string::npos && ((fGen->isGenParticle(4)) || (fGen->isGenParticle(5)))) continue;
    }

    // Primary vertex requirement
    if(!fEvt->PV()) continue;
    
    // Triggerbits for MET, Electrons and Photons
    unsigned int trigbits=1;    
    if(fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_NoID_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_NoID_v*")) trigbits = trigbits | 2; 
    if(fEvt ->passTrigger("HLT_Ele27_WP85_Gsf_v*") ||
       fEvt ->passTrigger("HLT_Ele27_WPLoose_Gsf_v*")) trigbits= trigbits | 4;
    if(fEvt ->passTrigger("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*") || 
       fEvt ->passTrigger("HLT_Ele23_WPLoose_Gsf_v*")) trigbits= trigbits | 8;
    if(fEvt ->passTrigger("HLT_Photon175_v*") ||
       fEvt ->passTrigger("HLT_Photon165_HE10_v*")) trigbits = trigbits | 16;
    if(trigbits==1) continue;
    
    // Objects
    std::vector<TLorentzVector> lMuons, lElectrons, lPhotons, lJets, lVJet15, lVJets15, lVJet8T, lVJets8T, lVetoes;
    std::vector<const TJet*> lGoodJets15, lGoodJets8T;

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
    
    // Lepton and Photon SF
    if(lOption.find("data")==std::string::npos){
      fillLepSF(13,fMuon->fNMuons,lMuons,fMuon->fhMuTight,fMuon->fhMuLoose,fGen->lepmatched(13,lMuons,0.3),fMuon->fmuoSFVars);
      fillLepSF(11,fElectron->fNElectrons,lElectrons,fElectron->fhEleTight,fElectron->fhEleVeto,fGen->lepmatched(11,lElectrons,0.3),fElectron->feleSFVars);
      fillPhoSF(22,fPhoton->fNPhotonsMedium,lPhotons,fGen->lepmatched(22,lPhotons,0.3),fPhoton->fphoSFVars);
    }

    // MET selection
    fEvt->fillModifiedMet(lVetoes,lPhotons);
    if(fEvt->fMet < 170. && fEvt->fPuppEt < 170. && fEvt->fFPuppEt < 170. && fEvt->fFMet < 170.) continue;

    // Trigger Efficiencies
    fEvt->triggerEff(lElectrons, lPhotons);
    
    // CA15Puppi Jets
    fVJet15->load(i0);
    fVJet15->selectVJets(lVetoes,lVJets15,lVJet15,1.5,"looseJetID");
    if(lVJets15.size()>0) { 
      if(lOption.find("data")==std::string::npos){
	fVJet15->fisHadronicTop = fGen->ismatchedJet(lVJet15[0],1.5,fVJet15->ftopMatching,fVJet15->ftopSize);
	fVJet15->fillSubJetBTag(fGen->fGens,fVJet15->fGoodVSubJets);
      }
      fEvt->fselectBits = fEvt->fselectBits | 2;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lVJet15,fVJet15->fVMT);
    }
    
    // CA8Puppi Jets
    fVJet8T->load(i0);
    fVJet8T->selectVJets(lVetoes,lVJets8T,lVJet8T,0.8,"tightJetID");
    if(lVJets8T.size()>0) {
      if(lOption.find("data")==std::string::npos){
        fVJet8T->fisHadronicTop = fGen->ismatchedJet(lVJet8T[0],0.8,fVJet8T->ftopMatching,fVJet8T->ftopSize);
        fVJet8T->fillSubJetBTag(fGen->fGens,fVJet8T->fGoodVSubJets);
      }
      fEvt->fselectBits =  fEvt->fselectBits | 4;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lVJet8T,fVJet8T->fVMT);
    }

    // AK4Puppi Jets
    fJet->load(i0); 
    fJet->selectJets(lVetoes,lVJets15,lJets,fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi);
    if(lJets.size()>0){
      if(lOption.find("data")==std::string::npos){
	fJet->fillGoodJets(lVJets15,lGoodJets15);
	fJet->fillGoodJets(lVJets8T,lGoodJets8T);
	fBTag->fillBTag(fJet->fGoodJets);
        fBTag15->fillBTag(lGoodJets15);
        fBTag8T->fillBTag(lGoodJets8T);
      }
      fEvt->fselectBits =  fEvt->fselectBits | 8;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lJets,fJet->fMT);
    }

    // Select only Puppi Jet
    if(!(fEvt->fselectBits & 2) && !(fEvt->fselectBits & 4) && !(fEvt->fselectBits & 8)) continue;

    // ttbar, EWK and kFactor correction
    if(lOption.find("mcg")!=std::string::npos){
      fGen->findBoson(22,0); 
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"GJets_1j_NLO/nominal_G","GJets_LO/inv_pt_G","EWKcorr/photon");
    }
    if(lOption.find("mcz")!=std::string::npos || lOption.find("mcdy")!=std::string::npos){
      fGen->findBoson(23,1);
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"ZJets_012j_NLO/nominal","ZJets_LO/inv_pt","EWKcorr/Z");
    }
    if(lOption.find("mcw")!=std::string::npos){
      fGen->findBoson(24,1);
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"WJets_012j_NLO/nominal","WJets_LO/inv_pt","EWKcorr/W"); 
    }
    if(lOption.find("tt")!=std::string::npos){
      fEvt->fevtWeight *= fGen->computeTTbarCorr();
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
