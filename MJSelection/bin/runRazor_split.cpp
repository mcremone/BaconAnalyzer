//================================================================================================
//
// Produce bacon bits 
//
// Input arguments
//   argv[1] => lName = input bacon file name
//   argv[2] => lOption = dataset type: "mc",  **CHECK
//                            "mcwjets",  "mcwplushf",  "mcwpluslf",
//                            "mczjets",  "mczplushf",  "mczpluslf",
//                            "mcdyjets", "mcdyplushf", "mcdypluslf",
//                            "mcgjets",  "mcgplushf",  "mcgpluslf",
//                            "mctt",
//                            "data"
//   argv[3] => lJSON = JSON file for run-lumi filtering of data, specify "none" for MC or no filtering
//   argv[4] => Starting entry 
//   argv[5] => Ending entry
//   argv[6] => Name of the output file
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
GenLoader        *fGen       = 0; 
EvtLoader        *fEvt       = 0; 
MuonLoader       *fMuon      = 0; 
ElectronLoader   *fElectron  = 0; 
TauLoader        *fTau       = 0; 
PhotonLoader     *fPhoton    = 0; 
JetLoader        *fJetCHS    = 0; 
JetLoader        *fJetPuppi  = 0;
BTagWeightLoader *fBTagCHS   = 0;
BTagWeightLoader *fBTagPuppi = 0;
RunLumiRangeMap  *fRangeMap  = 0; 

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
  const int      startEntry      = atof(argv[4]);
  const int      endEntry        = atof(argv[5]);
  const std::string outName      = argv[6]; 

  fRangeMap = new RunLumiRangeMap();
  if(lJSON.size() > 0) fRangeMap->AddJSONFile(lJSON.c_str());

  TTree *lTree = load(lName); 
  if (lTree == 0)
  {
      cout << "No tree found\n";
      return 0;
  }  
  // Declare Readers 
  fEvt       = new EvtLoader     (lTree,lName);                                           // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon      = new MuonLoader    (lTree);                                                 // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron  = new ElectronLoader(lTree);                                                 // fElectrons and fElectronBr, fN = 2
  fTau       = new TauLoader     (lTree);                                                 // fTaus and fTaurBr, fN = 1
  fPhoton    = new PhotonLoader  (lTree);                                                 // fPhotons and fPhotonBr, fN = 1
  fJetCHS    = new JetLoader     (lTree,"AK4CHS");                                        // fJets and fJetBr => AK4PUPPI, fN = 4 - includes jet corrections (corrParams), fN = 4
  //fJetPuppi  = new JetLoader     (lTree,"AK4Puppi"); 
//  fBTagCHS   = new BTagWeightLoader(lTree);
//  fBTagPuppi = new BTagWeightLoader(lTree);
  if (lOption.find("data")==std::string::npos) fGen      = new GenLoader     (lTree);     // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

  TFile *lFile = new TFile(outName.c_str(),"RECREATE");
  TTree *lOut  = new TTree("Events","Events");
  TH1F *NEvents = new TH1F("NEvents", "NEvents", 1, 1, 2);

  // Setup Tree
  fEvt       ->setupTree      (lOut); 
/*  
  fMuon      ->setupTree      (lOut);
  fElectron  ->setupTree      (lOut);
  fTau       ->setupTree      (lOut);
  fPhoton    ->setupTree      (lOut);
  */
  fJetCHS    ->setupTree      (lOut,"res_CHSjet");
 // fJetCHS    ->setupTreeDiJet (lOut,"res_CHSjet");
  fJetCHS    ->setupTreeRazor (lOut,"res_CHSjet"); 
  //fJetPuppi  ->setupTree      (lOut,"res_PUPPIjet");
  //fJetPuppi  ->setupTreeDiJet (lOut,"res_PUPPIjet");
  //fJetPuppi  ->setupTreeRazor (lOut,"res_PUPPIjet");
//  fBTagCHS   ->setupTree      (lOut,"res_CHSjet");
//  fBTagPuppi ->setupTree      (lOut,"res_PUPPIjet");
  if(lOption.find("data")==std::string::npos) fGen ->setupTree (lOut,1);

  //
  // Loop over events i0 = iEvent
  //
  int neventstest = 0;
  std::cout << "Starting Entry: " << startEntry << "          Ending Entry: " << endEntry << std::endl;
  //for(int i0 = 0; i0 < int(lTree->GetEntriesFast()); i0++) {
  for(int i0 = startEntry; i0 <= endEntry; i0++) {
    if (i0 > int(lTree->GetEntriesFast())) 
    {
        std::cout << "i0 " << i0 << " exceeds " << lTree->GetEntriesFast() << std::endl;
        break;
    }
    std::cout << "i0 " << i0 << std::endl;
    if(i0 % 1000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(lTree->GetEntriesFast())*100) << " -- " << lOption << std::endl;
     
    // Check JSON and GenInfo
    fEvt->load(i0);
    std::cout << "fEvt->load(" << i0 << ")\n";
    float lWeight = 1;
    if(lOption.find("data")!=std::string::npos){
      if(!passEvent(fEvt->fRun,fEvt->fLumi))                                                              continue;
    }
    else{
      fGen->load(i0);
      //lWeight = (float(lXS)*1000.*fGen->fWeight)/weight;
      lWeight = (float) fGen->fWeight;
      NEvents->SetBinContent( 1, NEvents->GetBinContent(1) + lWeight);

      if(lOption.find("hf")!=std::string::npos && !(fGen->isGenParticle(4)) && !(fGen->isGenParticle(5))) continue;
      if(lOption.find("lf")!=std::string::npos && ((fGen->isGenParticle(4)) || (fGen->isGenParticle(5)))) continue;
      if(lOption.find("tt")!=std::string::npos){
	int nlep = fGen->isttbarType();
	if(lOption.find("tt2l")!=std::string::npos && nlep!=2)                                            continue;
	if(lOption.find("tt1l")!=std::string::npos && nlep!=1)                                            continue;
	if(lOption.find("tthad")!=std::string::npos && nlep!=0)                                           continue;
	if(lOption.find("ttbst")!=std::string::npos && nlep!=2 && nlep!=1 && nlep!=0)                     continue;
	if(lOption.find("ttcom")!=std::string::npos && nlep!=2 && nlep!=1 && nlep!=0)                     continue;
      }
    }

    // Primary vertex requirement
    if(!fEvt->PV()) continue;

    // Triggerbits
    unsigned int trigbits=1;   
    if(lOption.find("data")!=std::string::npos) 
      {
	if(fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*") ||
	   fEvt ->passTrigger("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*") ||
	   fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_NoID_v*") ||
	   fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*") ||
	   fEvt ->passTrigger("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*") ||
	   fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_NoID_v*")) trigbits = trigbits | 2; 

	if(fEvt ->passTrigger("HLT_Ele27_WP85_Gsf_v*") ||
	   fEvt ->passTrigger("HLT_Ele27_WPLoose_Gsf_v*") || 
	   fEvt ->passTrigger("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*") || 
	   fEvt ->passTrigger("HLT_Ele23_WPLoose_Gsf_v*")) trigbits = trigbits | 4;
    
	if(fEvt ->passTrigger("HLT_IsoMu20_v*") ||
	   fEvt ->passTrigger("HLT_IsoMu27_v*") ||
	   fEvt ->passTrigger("HLT_IsoTkMu20_v*")) trigbits= trigbits | 8;
      
	if(fEvt ->passTrigger("HLT_ECALHT800_v*") ||
	   fEvt ->passTrigger("HLT_Photon175_v*") ||
	   fEvt ->passTrigger("HLT_Photon165_HE10_v*") ||
	   fEvt ->passTrigger("HLT_Photon300_NoHE_v*") ||
	   fEvt ->passTrigger("HLT_Photon120_R9Id90_HE10_Iso40_EBOnly_PFMET40_v*") ||
	   fEvt ->passTrigger("HLT_Photon135_PFMET100_v*")) trigbits = trigbits | 16;
    
       
	// Triggerbits for MR and Rsq
	if(fEvt ->passTrigger("HLT_RsqMR240_Rsq0p09_MR200_v*") ||
	   fEvt ->passTrigger("HLT_RsqMR240_Rsq0p09_MR200_4jet_v*") ||
	   fEvt ->passTrigger("HLT_RsqMR270_Rsq0p09_MR200_v*") ||
	   fEvt ->passTrigger("HLT_RsqMR270_Rsq0p09_MR200_4jet_v*") ||
	   fEvt ->passTrigger("HLT_RsqMR260_Rsq0p09_MR200_v*") ||
	   fEvt ->passTrigger("HLT_RsqMR260_Rsq0p09_MR200_4jet_v*") ||
	   fEvt ->passTrigger("HLT_RsqMR300_Rsq0p09_MR200_v*") ||
	   fEvt ->passTrigger("HLT_RsqMR300_Rsq0p09_MR200_4jet_v*") || 
	   fEvt ->passTrigger("HLT_Rsq0p25_v*") ||
	   fEvt ->passTrigger("HLT_Rsq0p30_v*") ||
	   fEvt ->passTrigger("HLT_Rsq0p36_v*") || 
	   fEvt ->passTrigger("HLT_Rsq0p02_MR300_TriPFJet80_60_40_BTagCSV_p063_p20_Mbb60_200_v*") ||
	   fEvt ->passTrigger("HLT_Rsq0p02_MR300_TriPFJet80_60_40_DoubleBTagCSV_p063_Mbb60_200_v*")) trigbits = trigbits | 32;
      //  if(trigbits==1) continue;
      }

    // Event info
    fEvt      ->fillEvent(trigbits,lWeight);

    // Objects
    std::vector<TLorentzVector> lMuons, lElectrons, lPhotons, lJetsCHS, lJetsPuppi, lVJet, lVJets, lVetoes;

    // Muons
    fMuon     ->load(i0);
    fMuon     ->selectMuons(lMuons,fEvt->fNLepLoose,fEvt->fislep0Tight,fEvt->fislep1Tight,fEvt->flep0PdgId,fEvt->flep1PdgId,fEvt->fMet,fEvt->fMetPhi);
    
    // Electrons
    fElectron ->load(i0);
    fElectron ->selectElectrons(fEvt->fRho,lElectrons,fEvt->fNLepLoose,fEvt->fislep0Tight,fEvt->fislep1Tight,fEvt->flep0PdgId,fEvt->flep1PdgId);
    
    // Lepton SF
    if(lOption.find("data")==std::string::npos){
      fEvt->fillLepSF(lElectrons,lMuons);
      fillLepSF(13,fEvt->fNVtx,fMuon->fNMuonsLoose,lMuons,
		fMuon->fhMuTrack,fElectron->fhEleTrack,fMuon->fhMuTight,fMuon->fhMuLoose,
		fGen->lepmatched(13,lMuons,0.3),fMuon->fmuoSFVars,fMuon->fmuoSFTrack);
      fillLepSF(11,fEvt->fNVtx,fElectron->fNElectronsLoose,lElectrons,
		fMuon->fhMuTrack,fElectron->fhEleTrack,fElectron->fhEleTight,fElectron->fhEleLoose,
		fGen->lepmatched(11,lElectrons,0.3),fElectron->feleSFVars,fElectron->feleSFTrack);
      fillPhoSF(22,fPhoton->fNPhotonsTight,lPhotons,fGen->lepmatched(22,lPhotons,0.3),fPhoton->fphoSFVars);
    }
    
    // Fill Vetoes
    fEvt     ->fillVetoes(lElectrons,lVetoes);
    fEvt     ->fillVetoes(lMuons,lVetoes);

    // Taus
    fTau     ->load(i0);
    fTau     ->selectTaus(lVetoes);

    // Photons
    fPhoton  ->load(i0);
    fPhoton  ->selectPhotons(fEvt->fRho,lElectrons,lPhotons);
//    fPhoton->selectPhotonsMVA(fEvt->fRho,lElectrons,lPhotonsMVA);
    
    // MET selection
    fEvt->fillModifiedMet(lVetoes,lPhotons);

    // Trigger Efficiencies
    fEvt->triggerEff(lElectrons, lPhotons);

    // AK4CHS Jets
    fJetCHS->load(i0); 
    fJetCHS->selectJets(lVetoes,lVJets,lJetsCHS,fEvt->fMet,fEvt->fMetPhi,fEvt->fFMet,fEvt->fFMetPhi);
    if(fJetCHS->fNJetsAbove80GeV>=2)
    {
      fEvt->fselectBits = fEvt->fselectBits | 4; // Set -1-- to fSelectBits
      fEvt->fillmT(fEvt->fMet,fEvt->fMetPhi,fEvt->fFMet,fEvt->fFMetPhi,lJetsCHS,fJetCHS->fMT);
    }
    
    // AK4Puppi Jets
    //fJetPuppi->load(i0); 
    //fJetPuppi->selectJets(lVetoes,lVJets,lJetsPuppi,fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi);
    //if(fJetPuppi->fNJetsAbove80GeV>1){
     // fEvt->fselectBits = fEvt->fselectBits | 2;
     // fEvt->fillmT(fEvt->fPuppEt,fEvt->fPuppEtPhi,fEvt->fFPuppEt,fEvt->fFPuppEtPhi,lJetsPuppi,fJetPuppi->fMT);
   // }

    // Select at least 2 narrow Jets
    if(!(fEvt->fselectBits & 2 || fEvt->fselectBits & 4)) continue;

    // ttbar, EWK and kFactor correction
//    if(lOption.find("data")==std::string::npos){
//      fGen->load(i0);
//      if(lJetsCHS.size()>0)     fBTagCHS->fillBTag(fJetCHS->fGoodJets);
//      if(lJetsPuppi.size()>0)   fBTagPuppi->fillBTag(fJetPuppi->fGoodJets);
//    }

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
    
    
    if (fMuon->fNMuonsLoose>0 || fElectron->fNElectronsLoose>0 || fPhoton->fNPhotonsLoose>0 || fTau->fNTaus>0) continue;   
    if (fJetCHS->fMR < 200. || fJetCHS->fRsq < 0.25 || fJetCHS->fdeltaPhi > 2.5) continue; 
   
    //if (fEvt->fMet < 200 || fJetCHS->fMinDPhi < 0.5 || fJetCHS->fJet0_pt < 100 || fabs(fJetCHS->fJet0_eta) > 2.5 || fJetCHS->fJet0_chf < 0.1 || fJetCHS->fJet0_nhf > 0.8) continue;
    lOut->Fill();
    neventstest++;
  }
  std::cout << "NEvents Filled = " << neventstest << std::endl;
  std::cout << "lTree->GetEntriesFast(): " << lTree->GetEntriesFast() << std::endl;
  lFile->cd();
  lOut->Write();
  NEvents->Write();
  lFile->Close();
  return 0;
}
