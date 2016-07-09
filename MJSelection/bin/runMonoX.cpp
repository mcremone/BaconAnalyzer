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
JetLoader        *fJetCHS   = 0;
BTagWeightLoader *fBTag     = 0;
BTagWeightLoader *fBTag15   = 0;
BTagWeightLoader *fBTagCHS15= 0;
BTagWeightLoader *fBTagCHS  = 0;
BTagWeightLoader *fBTag8T   = 0;
BTagWeightLoader *fBTagCHS8 = 0;
VJetLoader       *fVJet15   = 0;
VJetLoader       *fVJetCHS15= 0;
VJetLoader       *fVJet8T   = 0;
VJetLoader       *fVJetCHS8 = 0;
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
  //fJetCHS   = new JetLoader       (lTree,"AK4CHS");
  fBTag     = new BTagWeightLoader(lTree);
  fBTag15   = new BTagWeightLoader(lTree);
  //fBTagCHS15= new BTagWeightLoader(lTree);
  //fBTagCHS  = new BTagWeightLoader(lTree);
  //fBTag8T   = new BTagWeightLoader(lTree);
  //fBTagCHS8 = new BTagWeightLoader(lTree);
  fVJet15   = new VJetLoader      (lTree,"CA15Puppi","AddCA15Puppi");                      // fVJets, fVJetBr =>CA8PUPPI, CA15PUPPI, AK8CHS, CA15CHS fN =1
  //fVJetCHS15= new VJetLoader      (lTree,"CA15CHS","AddCA15CHS");
  //fVJet8T   = new VJetLoader      (lTree,"AK8Puppi","AddAK8Puppi");
  //fVJetCHS8 = new VJetLoader      (lTree,"AK8CHS","AddAK8CHS");
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
  //fJetCHS   ->setupTree           (lOut,"res_CHSjet");
  fBTag     ->setupTree           (lOut,"res_PUPPIjet");
  fBTag15   ->setupTree           (lOut,"res_PUPPIjetbst15");
  //fBTagCHS15->setupTree           (lOut,"res_CHSjetbst15");
  //fBTagCHS  ->setupTree           (lOut,"res_CHSjet");
  //fBTag8T   ->setupTree           (lOut,"res_PUPPIjetbst8T");
  //fBTagCHS8 ->setupTree           (lOut,"res_CHSjetbst8");
  fVJet15   ->setupTree           (lOut,"bst15_PUPPIjet"); 
  fVJet15   ->setupTreeSubJetBTag (lOut,"bst15_PUPPIjet");
  //fVJetCHS15->setupTree           (lOut,"bst15_CHSjet");
  //fVJetCHS15->setupTreeSubJetBTag (lOut,"bst15_CHSjet");
  //fVJet8T   ->setupTree           (lOut,"bst8_PUPPIjetT");
  //fVJet8T   ->setupTreeSubJetBTag (lOut,"bst8_PUPPIjetT");
  //fVJetCHS8 ->setupTree           (lOut,"bst8_CHSjet");
  //fVJetCHS8 ->setupTreeSubJetBTag (lOut,"bst8_CHSjet");
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
      //std::cout << fEvt->fRun << " " << fEvt->fLumi << std::endl;
      if(!passEvent(fEvt->fRun,fEvt->fLumi))                                                              continue;
    }
    else{
      fGen->load(i0);
      lWeight = (float(lXS)*1000.*fGen->fWeight)/weight;
      if(lOption.find("hf")!=std::string::npos && !(fGen->isGenParticle(4)) && !(fGen->isGenParticle(5))) continue;
      if(lOption.find("lf")!=std::string::npos && ((fGen->isGenParticle(4)) || (fGen->isGenParticle(5)))) continue;
      /*
      if(lOption.find("tt")!=std::string::npos){
        int nlep = fGen->isttbarType();
        if(lOption.find("tt2l")!=std::string::npos && nlep!=2)                                            continue;
        if(lOption.find("tt1l")!=std::string::npos && nlep!=1)                                            continue;
        if(lOption.find("tthad")!=std::string::npos && nlep!=0)                                           continue;
        if(lOption.find("ttbst")!=std::string::npos && nlep!=2 && nlep!=1 && nlep!=0)                     continue;
        if(lOption.find("ttcom")!=std::string::npos && nlep!=2 && nlep!=1 && nlep!=0)                     continue;
      }
      */
    }

    // Primary vertex requirement
    if(!fEvt->PV()) continue;
    
    // Triggerbits for MET, Electrons and Photons
    unsigned int trigbits=1;    
    if(lOption.find("data")!=std::string::npos){
      if(fEvt ->passTrigger("HLT_PFMET170_NoiseCleaned_v*")||
	 fEvt ->passTrigger("HLT_PFMET170_JetIdCleaned_v*") ||
	 fEvt ->passTrigger("HLT_PFMET170_HBHECleaned_v*") ||
	 fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*") ||
	 fEvt ->passTrigger("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*") ||
	 //fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_NoID_v*") ||
         fEvt ->passTrigger("HLT_PFMETNoMu100_NoiseCleaned_PFMHTNoMu100_IDTight_v*") ||
         fEvt ->passTrigger("HLT_PFMETNoMu100_JetIdCleaned_PFMHTNoMu100_IDTight_v*") ||
         //fEvt ->passTrigger("HLT_PFMETNoMu100_NoiseCleaned_PFMHTNoMu100_NoID_v*") ||
         fEvt ->passTrigger("HLT_PFMETNoMu110_NoiseCleaned_PFMHTNoMu110_IDTight_v*") ||
         fEvt ->passTrigger("HLT_PFMETNoMu110_JetIdCleaned_PFMHTNoMu110_IDTight_v*") ||
         //fEvt ->passTrigger("HLT_PFMETNoMu110_NoiseCleaned_PFMHTNoMu110_NoID_v*") ||
	 fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*") ||
	 fEvt ->passTrigger("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*")) trigbits = trigbits | 2; // ||
	 //fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_NoID_v*")) trigbits = trigbits | 2;
      if(fEvt ->passTrigger("HLT_Ele27_eta2p1_WPLoose_Gsf_v*") ||
	 fEvt ->passTrigger("HLT_Ele25_eta2p1_WPTight_Gsf_v*") ||
	 fEvt ->passTrigger("HLT_Ele35_WPLoose_Gsf_v*") ||
      	 fEvt ->passTrigger("HLT_Ele27_WPTight_Gsf_v*") ||
	 fEvt ->passTrigger("HLT_ECALHT800_v*")) trigbits= trigbits | 4;
      if(fEvt ->passTrigger("HLT_ECALHT800_v*") ||
	 fEvt ->passTrigger("HLT_Photon175_v*") ||
	 fEvt ->passTrigger("HLT_Photon165_HE10_v*") ||
	 fEvt ->passTrigger("HLT_Photon300_NoHE_v*") ||
         fEvt ->passTrigger("HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v*") ||
         fEvt ->passTrigger("HLT_Photon135_PFMET100_v*")) trigbits= trigbits | 8;
      //if(trigbits==1) continue;
    }

    // Objects
    std::vector<TLorentzVector> lMuons, lElectrons, lPhotons, lJets, lJetsCHS, lVJet15, lVJets15, lVJetCHS15, lVJetsCHS15, lVJet8T, lVJets8T, lVJetCHS8, lVJetsCHS8, lVetoes;
    std::vector<const TJet*> lGoodJets15, lGoodJetsCHS15, lGoodJets8T, lGoodJetsCHS8;

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
    fEvt->fillVetoes(lPhotons,lVetoes);

    // CA15Puppi Jets
    fVJet15->load(i0);
    fVJet15->selectVJets(lVetoes,lVJets15,lVJet15,1.5,fEvt->fRho,"tightJetID");
    if(lVJets15.size()>0) { 
      if(lOption.find("data")==std::string::npos){
	fVJet15->fisHadronicTop = fGen->ismatchedJet(lVJet15[0],1.5,fVJet15->ftopMatching,fVJet15->ftopSize);
	fVJet15->fisHadronicV = fGen->ismatchedJet(lVJet15[0],0.8,fVJet15->fvMatching,fVJet15->fvSize,25);
	fVJet15->fillSubJetBTag(fGen->fGens,fVJet15->fGoodVSubJets);
      }
      fEvt->fselectBits = fEvt->fselectBits | 2;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lVJet15,fVJet15->fVMT);
    }
    /*
    // CA15CHS Jets
    fVJetCHS15->load(i0);
    fVJetCHS15->selectVJets(lVetoes,lVJetsCHS15,lVJetCHS15,1.5,fEvt->fRho,"looseJetID");
    if(lVJetsCHS15.size()>0) {
      if(lOption.find("data")==std::string::npos){
        fVJetCHS15->fisHadronicTop = fGen->ismatchedJet(lVJetCHS15[0],1.5,fVJetCHS15->ftopMatching,fVJetCHS15->ftopSize);
        fVJetCHS15->fisHadronicV = fGen->ismatchedJet(lVJetCHS15[0],0.8,fVJetCHS15->fvMatching,fVJetCHS15->fvSize,25);
        fVJetCHS15->fillSubJetBTag(fGen->fGens,fVJetCHS15->fGoodVSubJets);
      }
      fEvt->fselectBits = fEvt->fselectBits | 4;
      fEvt->fillmT(fEvt->fMet,fEvt->fMetPhi,fEvt->fFMet,fEvt->fFMetPhi,lVJet15,fVJetCHS15->fVMT);
    }

    // CA8Puppi Jets
    fVJet8T->load(i0);
    fVJet8T->selectVJets(lVetoes,lVJets8T,lVJet8T,0.8,fEvt->fRho,"tightJetID");
    if(lVJets8T.size()>0) {
      if(lOption.find("data")==std::string::npos){
        fVJet8T->fisHadronicTop = fGen->ismatchedJet(lVJet8T[0],0.8,fVJet8T->ftopMatching,fVJet8T->ftopSize);
        fVJet8T->fisHadronicV = fGen->ismatchedJet(lVJet8T[0],0.8,fVJet8T->fvMatching,fVJet8T->fvSize,25);
        fVJet8T->fillSubJetBTag(fGen->fGens,fVJet8T->fGoodVSubJets);
      }
      fEvt->fselectBits =  fEvt->fselectBits | 8;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lVJet8T,fVJet8T->fVMT);
    }

    // AK8CHS Jets
    fVJetCHS8->load(i0);
    fVJetCHS8->selectVJets(lVetoes,lVJetsCHS8,lVJetCHS8,0.8,fEvt->fRho,"tightJetID");
    if(lVJetsCHS8.size()>0) {
      if(lOption.find("data")==std::string::npos){
        fVJetCHS8->fisHadronicTop = fGen->ismatchedJet(lVJetCHS8[0],0.8,fVJetCHS8->ftopMatching,fVJetCHS8->ftopSize);
        fVJetCHS8->fisHadronicV = fGen->ismatchedJet(lVJetCHS8[0],0.8,fVJetCHS8->fvMatching,fVJetCHS8->fvSize,25);
        fVJetCHS8->fillSubJetBTag(fGen->fGens,fVJetCHS8->fGoodVSubJets);
      }
      fEvt->fselectBits =  fEvt->fselectBits | 16;
      fEvt->fillmT(fEvt->fMet,fEvt->fMetPhi,fEvt->fFMet,fEvt->fFMetPhi,lVJetCHS8,fVJetCHS8->fVMT);
    }
    */
    // AK4Puppi Jets
    fJet->load(i0); 
    fJet->selectJets(lVetoes,lVJets15,lJets,fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi);
    if(lJets.size()>0){
      fJet->fillGoodJets(lVJets15,1.5,lGoodJets15);
      //fJet->fillGoodJets(lVJets8T,0.8,lGoodJets8T);
      if(lOption.find("data")==std::string::npos){
	fBTag->fillBTag(fJet->fGoodJets);
        fBTag15->fillBTag(lGoodJets15);
        //fBTag8T->fillBTag(lGoodJets8T);
      }
      fEvt->fselectBits =  fEvt->fselectBits | 4;
      fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lJets,fJet->fMT);
    }
    /*
    // AK4CHS Jets
    fJetCHS->load(i0);
    fJetCHS->selectJets(lVetoes,lVJetsCHS15,lJetsCHS,fEvt->fMet,fEvt->fMetPhi,fEvt->fFMet,fEvt->fFMetPhi);
    if(lJetsCHS.size()>0){
      fJetCHS->fillGoodJets(lVJetsCHS15,1.5,lGoodJetsCHS15);
      fJetCHS->fillGoodJets(lVJetsCHS8,0.8,lGoodJetsCHS8);
      if(lOption.find("data")==std::string::npos){
        fBTagCHS->fillBTag(fJetCHS->fGoodJets);
        fBTagCHS15->fillBTag(lGoodJetsCHS15);
        fBTagCHS8->fillBTag(lGoodJetsCHS8);
      }
      fEvt->fselectBits =  fEvt->fselectBits | 64;
      fEvt->fillmT(fEvt->fMet,fEvt->fMetPhi,fEvt->fFMet,fEvt->fFMetPhi,lJetsCHS,fJetCHS->fMT);
    }
    */
    // Select at least one Jet
    //if(!(fEvt->fselectBits & 2) && !(fEvt->fselectBits & 4)) continue; // && !(fEvt->fselectBits & 8) & !(fEvt->fselectBits & 16) & !(fEvt->fselectBits & 32) & !(fEvt->fselectBits & 64)) continue;
    
    // ttbar, EWK and kFactor correction
    if(lOption.find("mcg")!=std::string::npos){
      fGen->findBoson(22,0); 
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"GJets_1j_NLO/nominal_G","GJets_LO/inv_pt_G","EWKcorr/photon","GJets_1j_NLO");
    }
    if(lOption.find("mcz")!=std::string::npos || lOption.find("mcdy")!=std::string::npos){
      fGen->findBoson(23,1);
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"ZJets_012j_NLO/nominal","ZJets_LO/inv_pt","EWKcorr/Z","ZJets_012j_NLO");
    }
    if(lOption.find("mcw")!=std::string::npos){
      fGen->findBoson(24,1);
      if(fGen->fBosonPt>0)      fEvt->computeCorr(fGen->fBosonPt,"WJets_012j_NLO/nominal","WJets_LO/inv_pt","EWKcorr/W","WJets_012j_NLO"); 
    }
    if(lOption.find("tt")!=std::string::npos){
      fEvt->fevtWeight *= fGen->computeTTbarCorr();
    }
    if(lName.find("ZprimeToA0h")!=std::string::npos || lName.find("ZH_HToBB")!=std::string::npos){
      fGen->findBoson(25,0);
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
