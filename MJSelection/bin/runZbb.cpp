//================================================================================================
//
// Perform preselection for Z(->bb)+jets events and produce bacon bits
//
// Input arguments:
//   argv[1] => input bacon file name
//   argv[2] => lOption = dataset type: "mc", "data"
//   argv[3] => JSON file for run-lumi filtering of data, specify "none" for MC or no filtering
//   argv[4] => cross section (pb), ignored for data
//   argv[5] => total weight, ignored for data  
//
//  **NOTE** Runs independentely from BaconAnalyzer functions - xCheck for Zprime
//________________________________________________________________________________________________

// bacon object headers
#include "BaconAna/DataFormats/interface/TEventInfo.hh"
#include "BaconAna/DataFormats/interface/TGenEventInfo.hh"
#include "BaconAna/DataFormats/interface/TElectron.hh"
#include "BaconAna/DataFormats/interface/TMuon.hh"
#include "BaconAna/DataFormats/interface/TTau.hh"
#include "BaconAna/DataFormats/interface/TJet.hh"
#include "BaconAna/DataFormats/interface/TAddJet.hh"
#include "BaconAna/DataFormats/interface/TGenParticle.hh"
#include "BaconAna/Utils/interface/TTrigger.hh"

// JSON file parser
#include "../include/RunLumiRangeMap.h"

// Analysis utilities (object IDs, gen particle finding, etc.)                                                                                                                                             
#include "../include/MonoXUtils.hh"

// ROOT headers
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TClonesArray.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TMath.h>

// Other C++ headers
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <cassert>

RunLumiRangeMap *fRangeMap = 0; 

bool passEvent(unsigned int iRun,unsigned int iLumi) { 
  RunLumiRangeMap::RunLumiPairType lRunLumi(iRun,iLumi);
  return fRangeMap->HasRunLumi(lRunLumi);
}

//=== MAIN =======================================================================================================

int main(int argc, char **argv)
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings and constants
  //==============================================================================================================  
  
  // handle input arguments
  const std::string infilename   = argv[1];
  const std::string dstypename   = argv[2];
  const std::string jsonfilename = argv[3];
  const double      xsec         = atof(argv[4]);
  const double      weight       = atof(argv[5]);

  // Set up object to handle good run-lumi filtering if necessary
  bool hasJSON = false;
  fRangeMap = new RunLumiRangeMap();
  if(jsonfilename.compare("none")!=0){
    fRangeMap->AddJSONFile(jsonfilename.c_str());
    hasJSON = true;                                                                                                                                                                                     
  } 
    
  // determine dataset type
  enum {
    kMC=1,  // MC signal                                                                                                                                                                               
    kData   // data                                                                                                                                                                                   
  };

  unsigned int dstype=0;
  if     (dstypename.compare("mc")==0)    { dstype = kMC; }
  else if(dstypename.compare("data")==0)  { dstype = kData; }
  assert(dstype>0);

  const std::string cmssw_base = getenv("CMSSW_BASE");
 
  // Trigger bits mapping file
  std::string trigfilename = cmssw_base + std::string("/src/BaconAna/DataFormats/data/HLTFile_25ns");
  baconhep::TTrigger trigger(trigfilename);

  // Cuts
  const double BST_JET_PT_CUT  = 200;
  const double BST_JET_ETA_CUT = 2.4;

  // Print summary of selection cuts
  std::cout << " ===== Cuts ===== " << std::endl;
  std::cout << " -- Boosted Jet:  ";
  std::cout << " pT > "     << BST_JET_PT_CUT;
  std::cout << ", |eta| < " << BST_JET_ETA_CUT << std::endl;
  std::cout << std::endl;

  //--------------------------------------------------------------------------------------------------------------
  // Set up output file
  //==============================================================================================================
  unsigned int metfilter;       // MET filter bits
  float npu;                    // mean expected PU
  unsigned int nf8PUPPIjets;    // PUPPIjet multiplicity
  unsigned int nf8CHSjets;      // CHSjet multiplicity
  float scale1fb;               // cross section scale factor per 1/fb

  // boosted 0.8 cone variables                                                                                                                                                                            
  float           bst8_PUPPIjet1tau21;
  float           bst8_PUPPIjet1msd;
  float           bst8_PUPPIjet1minsubcsv;
  float           bst8_PUPPIjet1maxsubcsv;
  TLorentzVector           *bst8_PUPPIjet1=0;

  float           bst8_CHSjet1tau21;
  float           bst8_CHSjet1msd;
  float           bst8_CHSjet1minsubcsv;
  float           bst8_CHSjet1maxsubcsv;
  TLorentzVector           *bst8_CHSjet1=0;

  TFile *outFile = new TFile("Output.root","RECREATE");
  TH1D hTotalEvents("TotalEvents","TotalEvents",1,-10,10);
  TTree *outTree = new TTree("Events","Events");
  
  outTree->Branch("metfilter",   &metfilter,   "metfilter/i");
  outTree->Branch("npu",         &npu,         "npu/F");
  outTree->Branch("nf8PUPPIjets",    &nf8PUPPIjets,    "nf8PUPPIjets/i");
  outTree->Branch("nf8CHSjets",    &nf8CHSjets,    "nf8CHSjets/i");
  outTree->Branch("scale1fb",    &scale1fb,    "scale1fb/F");

  // boosted 0.8 cone variables                                                                                                                                                                             
  outTree->Branch("bst8_PUPPIjet1tau21",   &bst8_PUPPIjet1tau21,   "bst8_PUPPIjet1tau21/F");
  outTree->Branch("bst8_PUPPIjet1msd",     &bst8_PUPPIjet1msd,     "bst8_PUPPIjet1msd/F");
  outTree->Branch("bst8_PUPPIjet1minsubcsv",     &bst8_PUPPIjet1minsubcsv,     "bst8_PUPPIjet1minsubcsv/F");
  outTree->Branch("bst8_PUPPIjet1maxsubcsv",     &bst8_PUPPIjet1maxsubcsv,     "bst8_PUPPIjet1maxsubcsv/F");
  outTree->Branch("bst8_PUPPIjet1",   "TLorentzVector", &bst8_PUPPIjet1);
  outTree->Branch("bst8_CHSjet1tau21",   &bst8_CHSjet1tau21,   "bst8_CHSjet1tau21/F");
  outTree->Branch("bst8_CHSjet1msd",     &bst8_CHSjet1msd,     "bst8_CHSjet1msd/F");
  outTree->Branch("bst8_CHSjet1minsubcsv",     &bst8_CHSjet1minsubcsv,     "bst8_CHSjet1minsubcsv/F");
  outTree->Branch("bst8_CHSjet1maxsubcsv",     &bst8_CHSjet1maxsubcsv,     "bst8_CHSjet1maxsubcsv/F");
  outTree->Branch("bst8_CHSjet1",   "TLorentzVector", &bst8_CHSjet1);

  //--------------------------------------------------------------------------------------------------------------
  // Process input file
  //==============================================================================================================
  baconhep::TEventInfo *info = 0; TBranch *infoBr    = 0;
  baconhep::TGenEventInfo *gen = 0; TBranch *genBr    = 0;
  TClonesArray *eleArr       = 0; TBranch *eleBr     = 0;
  TClonesArray *muonArr      = 0; TBranch *muonBr    = 0;
  TClonesArray *tauArr       = 0; TBranch *tauBr     = 0;
  TClonesArray *phoArr       = 0; TBranch *phoBr      = 0;
  TClonesArray *PUPPIjetArr       = 0; TBranch *PUPPIjetBr     = 0;
  TClonesArray *f8PUPPIjetArr     = 0; TBranch *f8PUPPIjetBr  = 0;
  TClonesArray *addf8PUPPIjetArr  = 0; TBranch *addf8PUPPIjetBr = 0;
  TClonesArray *CHSjetArr       = 0; TBranch *CHSjetBr     = 0;
  TClonesArray *f8CHSjetArr     = 0; TBranch *f8CHSjetBr  = 0;
  TClonesArray *addf8CHSjetArr  = 0; TBranch *addf8CHSjetBr = 0;
  TClonesArray *pvArr        = 0; TBranch *pvBr      = 0;
  TClonesArray *genParArr    = 0; TBranch *genParBr  = 0;
    
  std::cout << "Processing " << infilename << "..." << std::endl;    
  TFile *infile    = TFile::Open(infilename.c_str()); assert(infile);
  TTree *eventTree = (TTree*)infile->Get("Events");   assert(eventTree);
  
  hTotalEvents.Add((TH1D*)infile->Get("TotalEvents"));

  eventTree->SetBranchAddress("Info",       &info,       &infoBr);
  eventTree->SetBranchAddress("Electron",   &eleArr,     &eleBr);
  eventTree->SetBranchAddress("Muon",       &muonArr,    &muonBr);
  eventTree->SetBranchAddress("Tau",        &tauArr,     &tauBr);
  eventTree->SetBranchAddress("Photon",    &phoArr,      &phoBr);
  eventTree->SetBranchAddress("AK4Puppi",     &PUPPIjetArr,     &PUPPIjetBr);
  eventTree->SetBranchAddress("CA8Puppi",    &f8PUPPIjetArr,    &f8PUPPIjetBr);
  eventTree->SetBranchAddress("AddCA8Puppi", &addf8PUPPIjetArr, &addf8PUPPIjetBr);
  eventTree->SetBranchAddress("AK4CHS",     &CHSjetArr,     &CHSjetBr);
  eventTree->SetBranchAddress("AK8CHS",    &f8CHSjetArr,    &f8CHSjetBr);
  eventTree->SetBranchAddress("AddAK8CHS", &addf8CHSjetArr, &addf8CHSjetBr);
  eventTree->SetBranchAddress("PV",         &pvArr,      &pvBr);
  if(dstype!=kData) {
    eventTree->SetBranchAddress("GenParticle", &genParArr, &genParBr);
    eventTree->SetBranchAddress("GenEvtInfo", &gen, &genBr);
  }

  //
  // loop over events
  //
  for(unsigned int ientry=0; ientry<eventTree->GetEntries(); ientry++) {
    infoBr->GetEntry(ientry);
 
    double xsWgt  = 1;  // event weight for cross section normalization

    if(dstype==kData) {
      if(hasJSON) {
        // JSON filter                                       
	if(!passEvent(info->runNum, info->lumiSec)) continue;
      }
    } else {
      genBr->GetEntry(ientry);
      xsWgt = 1000.*xsec*gen->weight/weight;
    }

    //
    // primary vertex requirement
    //
    if(!(info->hasGoodPV)) continue;
  
    //
    // trigger requirement
    //
    bool passTrigger = trigger.pass("HLT_AK8PFJet360_TrimMass30_v*", info->triggerBits) ||
      trigger.pass("HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v*", info->triggerBits);
   
    // not trigger requirement for now
    if(!passTrigger) continue;

    if(dstype==kMC){
      genParArr->Clear();
      genParBr->GetEntry(ientry);
    }

    //
    // lepton and photon vetoes
    //
    bool passVeto = true;

    muonArr->Clear();
    muonBr->GetEntry(ientry);
    for(int i=0; i<muonArr->GetEntriesFast(); i++) {
      const baconhep::TMuon *muon = (baconhep::TMuon*)muonArr->At(i);
    
      if(muon->pt        <= 10)  continue;
      if(fabs(muon->eta) >= 2.4) continue;
      if(!passMuonLooseSel(muon))     continue;

      ///// Good muon found! /////
                                                                                                                                                                      
      passVeto = false;
      break;
    }
    if(!passVeto) continue;

    eleArr->Clear();
    eleBr->GetEntry(ientry);
    for(int i=0; i<eleArr->GetEntriesFast(); i++) {
      const baconhep::TElectron *electron = (baconhep::TElectron*)eleArr->At(i);
  
      if(electron->pt        <= 10)           continue;
      if(fabs(electron->eta) >= 2.5)          continue;
      if(!passEleSel(electron, info->rhoIso)) continue;

      ///// Good electron found! /////                                                                                                                                                                      
      passVeto = false;
      break;
    }
    if(!passVeto) continue;

    tauArr->Clear();
    tauBr->GetEntry(ientry);
    for(int i=0; i<tauArr->GetEntriesFast(); i++) {
      const baconhep::TTau *tau = (baconhep::TTau*)tauArr->At(i);

      if(tau->pt        <= 10)  continue;
      if(fabs(tau->eta) >= 2.3) continue;
      if(!passTauSel(tau)) continue;

      ///// Good tau found! /////                                                                                                                                                                           
      passVeto = false;
      break;
    }
    if(!passVeto) continue;

    phoArr->Clear();
    phoBr->GetEntry(ientry);
    for(int i=0; i<phoArr->GetEntriesFast(); i++) {
      const baconhep::TPhoton *photon = (baconhep::TPhoton*)phoArr->At(i);

      if(photon->pt        <= 15)           continue;
      if(fabs(photon->eta) >= 2.5)          continue;
      if(!passPhoMediumSel(photon, info->rhoIso)) continue;

      ///// Good photon found! /////                                                                                                                                                                           
      passVeto = false;
      break;
    }
    if(!passVeto) continue;

    //
    // Jet selections in each category
    //
    bool select = false;

    addf8PUPPIjetArr->Clear();
    addf8PUPPIjetBr->GetEntry(ientry);
    f8PUPPIjetArr->Clear();
    f8PUPPIjetBr->GetEntry(ientry);
    PUPPIjetArr->Clear();
    PUPPIjetBr->GetEntry(ientry);

    addf8CHSjetArr->Clear();
    addf8CHSjetBr->GetEntry(ientry);
    f8CHSjetArr->Clear();
    f8CHSjetBr->GetEntry(ientry);
    CHSjetArr->Clear();
    CHSjetBr->GetEntry(ientry);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // boosted selection
    //
    //*********************************

    unsigned int nF8PUPPIJets=0;
    const baconhep::TJet *bst8PUPPIJet1=0;
    const baconhep::TAddJet *bst8AddPUPPIJet1=0;
    TLorentzVector vBst8PUPPIJet1;
    for(int i=0; i<addf8PUPPIjetArr->GetEntriesFast(); i++) {
      const baconhep::TAddJet *addfjet = (baconhep::TAddJet*)addf8PUPPIjetArr->At(i);
      const baconhep::TJet    *fjet    = (baconhep::TJet*)f8PUPPIjetArr->At(addfjet->index);

      TLorentzVector vFJet;
      vFJet.SetPtEtaPhiM(fjet->pt, fjet->eta, fjet->phi, fjet->mass);

      // not cut on pt spectra
      if(vFJet.Pt()       <= BST_JET_PT_CUT)  continue;
      if(abs(vFJet.Eta()) >= BST_JET_ETA_CUT) continue;
      if(!passJet04Sel(fjet))                   continue;

      nF8PUPPIJets++;

      if(!bst8PUPPIJet1 || vFJet.Pt() > vBst8PUPPIJet1.Pt()) {
        bst8PUPPIJet1    = fjet;
	bst8AddPUPPIJet1 = addfjet;
        vBst8PUPPIJet1   = vFJet;

      }
    }
    if(nF8PUPPIJets>0) {
      select = true;
    }
    unsigned int nF8CHSJets=0;
    const baconhep::TJet *bst8CHSJet1=0;
    const baconhep::TAddJet *bst8AddCHSJet1=0;
    TLorentzVector vBst8CHSJet1;
    for(int i=0; i<addf8CHSjetArr->GetEntriesFast(); i++) {
      const baconhep::TAddJet *addfjet = (baconhep::TAddJet*)addf8CHSjetArr->At(i);
      const baconhep::TJet    *fjet    = (baconhep::TJet*)f8CHSjetArr->At(addfjet->index);

      TLorentzVector vFJet;
      vFJet.SetPtEtaPhiM(fjet->pt, fjet->eta, fjet->phi, fjet->mass);

      // not cut on pt spectra
      if(vFJet.Pt()       <= BST_JET_PT_CUT)  continue;
      if(abs(vFJet.Eta()) >= BST_JET_ETA_CUT) continue;
      if(!passJet04Sel(fjet))                   continue;

      nF8CHSJets++;

      if(!bst8CHSJet1 || vFJet.Pt() > vBst8CHSJet1.Pt()) {
        bst8CHSJet1    = fjet;
	bst8AddCHSJet1 = addfjet;
        vBst8CHSJet1   = vFJet;

      }
    }
    if(nF8CHSJets>0) {
      select = true;
    }
    if(!select) continue;

    // Read in PV branch to get number of primary vertices
    pvArr->Clear();
    pvBr->GetEntry(ientry);

    //
    // Fill output tree
    //
    metfilter   = info->metFilterFailBits;
    npu         = info->nPUmean;
    nf8PUPPIjets     = nF8PUPPIJets;
    nf8CHSjets     = nF8CHSJets;
    scale1fb    = xsWgt;

    bst8_PUPPIjet1tau21   = (bst8AddPUPPIJet1) ? (bst8AddPUPPIJet1->tau2/bst8AddPUPPIJet1->tau1) : -999;
    bst8_PUPPIjet1msd     = (bst8AddPUPPIJet1) ? bst8AddPUPPIJet1->mass_sd0  : -999;
    bst8_PUPPIjet1minsubcsv = (bst8AddPUPPIJet1) ? TMath::Min(bst8AddPUPPIJet1->sj1_csv,bst8AddPUPPIJet1->sj2_csv) : -999;
    bst8_PUPPIjet1maxsubcsv = (bst8AddPUPPIJet1) ? TMath::Max(bst8AddPUPPIJet1->sj1_csv,bst8AddPUPPIJet1->sj2_csv) : -999;
    bst8_PUPPIjet1        = &vBst8PUPPIJet1;
    bst8_CHSjet1tau21   = (bst8AddCHSJet1) ? (bst8AddCHSJet1->tau2/bst8AddCHSJet1->tau1) : -999;
    bst8_CHSjet1msd     = (bst8AddCHSJet1) ? bst8AddCHSJet1->mass_sd0  : -999;
    bst8_CHSjet1minsubcsv = (bst8AddCHSJet1) ? TMath::Min(bst8AddCHSJet1->sj1_csv,bst8AddCHSJet1->sj2_csv) : -999;
    bst8_CHSjet1maxsubcsv = (bst8AddCHSJet1) ? TMath::Max(bst8AddCHSJet1->sj1_csv,bst8AddCHSJet1->sj2_csv) : -999;
    bst8_CHSjet1        = &vBst8CHSJet1;

    outTree->Fill();
  }

  delete infile;
  infile=0, eventTree=0;
  
  outFile->Write();
  outFile->Close();
  
  delete info;
  delete eleArr;
  delete muonArr;
  delete tauArr;
  delete phoArr;
  delete PUPPIjetArr;
  delete f8PUPPIjetArr;
  delete addf8PUPPIjetArr;
  delete CHSjetArr;
  delete f8CHSjetArr;
  delete addf8CHSjetArr;
  delete pvArr;
  
  return 0;
}
