#include "../include/MuonLoader.hh"

#include "TFile.h"
#include <cmath>
#include <iostream> 
#include <sstream> 

using namespace baconhep;

MuonLoader::MuonLoader(TTree *iTree,std::string imuScaleFactorFilename,std::string imuScaleFactorTightFilename,std::string imuScaleFactorTrackFilename) { 
  fMuons  = new TClonesArray("baconhep::TMuon");
  iTree->SetBranchAddress("Muon",       &fMuons);
  fMuonBr  = iTree->GetBranch("Muon");
  fN = 2;
  TFile *fMuSF = new TFile(imuScaleFactorFilename.c_str());
  fhMuLoose =  (TH2D*) fMuSF->Get("scaleFactor_muon_looseid_RooCMSShape");
  fhMuLoose->SetDirectory(0);
  fMuSF->Close();
  TFile *fMuSFTight = new TFile(imuScaleFactorTightFilename.c_str());
  fhMuTight =  (TH2D*) fMuSFTight->Get("scaleFactor_muon_tightid_RooCMSShape");
  fhMuTight->SetDirectory(0);
  fMuSFTight->Close();
  TFile *fMuSFTrack = new TFile(imuScaleFactorTrackFilename.c_str());
  fhMuTrack = (TH1D*) fMuSFTrack->Get("htrack2");
  fhMuTrack->SetDirectory(0);
  fMuSFTrack->Close();

  for(int i0 = 0; i0 < fN*3.; i0++) {double pVar = 0; fVars.push_back(pVar);}
  for(int i0 = 0; i0 <     4; i0++) {double pVar = 0; fVars.push_back(pVar);}
  for(int i0 = 0; i0 <     3; i0++) {double pVar = 1; fmuoSFVars.push_back(pVar);}
}
MuonLoader::~MuonLoader() { 
  delete fMuons;
  delete fMuonBr;
}
void MuonLoader::reset() { 
  fNMuonsLoose = 0; 
  fNMuonsTight = 0;
  fismu0Tight  = 0; 
  fisDimuon    = 0;
  fmuoSFTrack  = 1;
  fSelMuons.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  for(unsigned int i0 = 0; i0 < fmuoSFVars.size(); i0++) fmuoSFVars[i0] = 1;
}
void MuonLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
//  fTree->Branch("nmuLoose"  ,&fNMuonsLoose ,"fNMuonsLoose/I"); 
//  fTree->Branch("nmuTight"  ,&fNMuonsTight ,"fNMuonsTight/I");
//  fTree->Branch("ismu0Tight",&fismu0Tight  ,"fismu0Tight/I");
//  fTree->Branch("isDimuon"  ,&fisDimuon    ,"fisDimuon/I");
//  fTree->Branch("muoSFTrack",&fmuoSFTrack  ,"fmuoSFTrack/D");
//  setupNtuple("vmuoLoose"   ,iTree,fN,fVars);       // add leading 2 muons: pt,eta,phi,mass (2*4=8)
//  addDiMuon  ("vdimuo"      ,iTree,1, fVars,fN*3);  // add dimuon system: *_pt,mass,phi,y for dimuo0 (1*4)
//  addSF      ("muoSF"       ,iTree,fmuoSFVars,3);   // add lepSF: muoSF0,muoSF1,muoSF2
}
void MuonLoader::load(int iEvent) { 
  fMuons  ->Clear();
  fMuonBr ->GetEntry(iEvent);
}
void MuonLoader::selectMuons(std::vector<TLorentzVector> &iVetoes, int &nLepLoose, int &islep0Tight, int &islep1Tight, int &lep0PdgId, int &lep1PdgId, float met, float metPhi) {
  reset(); 
  // Muon multiplicity
  std::vector<TMuon*> lVeto;
  int lCount = 0,lTCount =0; 
  fvMetNoMu.SetMagPhi(met,metPhi);

  // Muon selection
  for  (int i0 = 0; i0 < fMuons->GetEntriesFast(); i0++) { 
    TMuon *pMuon = (TMuon*)((*fMuons)[i0]);
    if(pMuon->pt        <=  10)                      continue;
    if(fabs(pMuon->eta) >=  2.4)                     continue;
    if(!passMuonLooseSel(pMuon))                     continue;
    lCount++;
    nLepLoose++;

    TVector2 vMu; vMu.SetMagPhi(pMuon->pt, pMuon->phi);
    fvMetNoMu = fvMetNoMu + vMu;

    if (nLepLoose==1) lep0PdgId=11;
    else if (nLepLoose==2) lep1PdgId=11;

    lVeto.push_back(pMuon);
    addMuon(pMuon,fSelMuons);

    if(pMuon->pt>20 && fabs(pMuon->eta)< 2.4 && passMuonTightSel(pMuon)){
      if(lCount==1) fismu0Tight = 1;
      if(nLepLoose==1)
        islep0Tight = 1;
      else if (nLepLoose==2)
        islep1Tight=1;
      lTCount++;
    }
  }
  fNMuonsLoose = lCount; 
  fNMuonsTight = lTCount;

  // Add Selected Tight Muons to iVetoes
  if(fNMuonsLoose <= 1 && lVeto.size()==1){
    if(passMuonTightSel(lVeto[0]) && lVeto[0]->pt > 20) addVMuon(lVeto[0],iVetoes,MUON_MASS);
  }
  if(fVars.size() > 0)                     fillMuon(fN,fSelMuons,fVars);
  if(fNMuonsLoose <= 2 && lVeto.size()==2) fillDiMuon(lVeto,iVetoes,fisDimuon);
}
// DIMUON
void MuonLoader::addDiMuon(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase) { 
 for(int i0 = 0; i0 < iN; i0++) { 
   std::stringstream pSPt,pSMass,pSPhi,pSY;
   pSPt    << iHeader << i0 << "_pt";
   pSMass  << iHeader << i0 << "_mass";
   pSPhi   << iHeader << i0 << "_phi";
   pSY     << iHeader << i0 << "_y";
   iTree->Branch(pSPt   .str().c_str(),&iVals[iBase+0],(pSPt   .str()+"/D").c_str());
   iTree->Branch(pSMass .str().c_str(),&iVals[iBase+1],(pSMass .str()+"/D").c_str());
   iTree->Branch(pSPhi  .str().c_str(),&iVals[iBase+2],(pSPhi  .str()+"/D").c_str());
   iTree->Branch(pSY    .str().c_str(),&iVals[iBase+3],(pSY    .str()+"/D").c_str());
 }
}
void MuonLoader::fillDiMuon(std::vector<TMuon*> lVeto, std::vector<TLorentzVector> &iVetoes, int &isDimuon) {
  TLorentzVector lVec; lVec.SetPtEtaPhiM(0,0,0,0);
  TMuon *vMuo0,*vMuo1;
  if((lVeto[1]->q) * (lVeto[0]->q) < 0){ //  opposite charge dimuons
    if(lVeto[0]->pt > lVeto[1]->pt){ 
      vMuo0 = lVeto[0];
      vMuo1 = lVeto[1];
    }
    else{
      vMuo1 = lVeto[0];
      vMuo0 = lVeto[1];
    }
    TLorentzVector pVec0; pVec0.SetPtEtaPhiM(vMuo0->pt,vMuo0->eta,vMuo0->phi,MUON_MASS);
    TLorentzVector pVec1; pVec1.SetPtEtaPhiM(vMuo1->pt,vMuo1->eta,vMuo1->phi,MUON_MASS);
    if((passMuonTightSel(vMuo0) && vMuo0->pt > 20) && (passMuonLooseSel(vMuo1) && vMuo1->pt > 20)){ // at least one muon must pass tight selection
      lVec = pVec0+pVec1;
      if(lVec.M() > 60 && lVec.M() < 120){
	iVetoes.push_back(pVec0);
	iVetoes.push_back(pVec1);
	isDimuon = 1;
      }
      int lBase = 3.*fN;
      fVars[lBase+0] = lVec.Pt();
      fVars[lBase+1] = lVec.M();
      fVars[lBase+2] = lVec.Phi();
      fVars[lBase+3] = lVec.Rapidity();
    }
  }
}
