#include "../include/MuonLoader.hh"

#include "TFile.h"
#include <cmath>
#include <iostream> 
#include <sstream> 

using namespace baconhep;

MuonLoader::MuonLoader(TTree *iTree,std::string imuScaleFactorFilename) { 
  fMuons  = new TClonesArray("baconhep::TMuon");
  iTree->SetBranchAddress("Muon",       &fMuons);
  fMuonBr  = iTree->GetBranch("Muon");
  fN = 2;
  TFile *fMuSF = new TFile(imuScaleFactorFilename.c_str());
  fhMuLoose =  (TH2D*) fMuSF->Get("scalefactors_Loose_mu");
  fhMuLoose->SetDirectory(0);
  fhMuTight =  (TH2D*) fMuSF->Get("scalefactors_Tight_mu");
  fhMuTight->SetDirectory(0);
  fMuSF->Close();

  for(int i0 = 0; i0 < fN*3.; i0++) {double pVar = 0; fVars.push_back(pVar);}
  for(int i0 = 0; i0 <     4; i0++) {double pVar = 0; fVars.push_back(pVar);}
  for(int i0 = 0; i0 <     3; i0++) {double pVar = 1; fmuoSFVars.push_back(pVar);}
}
MuonLoader::~MuonLoader() { 
  delete fMuons;
  delete fMuonBr;
}
void MuonLoader::reset() { 
  fNMuons      = 0; 
  fNMuonsTight = 0; 
  fSelMuons.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  for(unsigned int i0 = 0; i0 < fmuoSFVars.size(); i0++) fmuoSFVars[i0] = 1;
}
void MuonLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
  fTree->Branch("nmu",&fNMuons,"fNMuons/I"); 
  fTree->Branch("nmuTight",&fNMuonsTight,"fNMuonsTight/I");
  setupNtuple("vmuo",iTree,fN,fVars);        // add leading 2 muons: pt,eta,phi,mass (2*4=8)
  addDiMuon  ("vdimuo",iTree,1, fVars,fN*3); // add dimuon system: *_pt,mass,phi,y for dimuo0 (1*4)
  addLepSF   ("muoSF",iTree,fmuoSFVars);     // add lepSF: muoSF0,muoSF1,muoSF2
}
void MuonLoader::load(int iEvent) { 
  fMuons   ->Clear();
  fMuonBr ->GetEntry(iEvent);
}
void MuonLoader::selectMuons(std::vector<TLorentzVector> &iVetoes) {
  reset(); 
  // Tight multiplicity
  int lCount = 0,lTCount =0; 
  for  (int i0 = 0; i0 < fMuons->GetEntriesFast(); i0++) if(passMuonTightSel((TMuon*)fMuons->At(i0))) lTCount++; 
  fNMuonsTight = lTCount; 

  // Loose selection
  std::vector<TMuon*> lVeto;
  for  (int i0 = 0; i0 < fMuons->GetEntriesFast(); i0++) { 
    TMuon *pMuon = (TMuon*)((*fMuons)[i0]);
    if(pMuon->pt        <=  10)                      continue;
    if(fabs(pMuon->eta) >=  2.4)                     continue;
    // if(passVeto(pMuon->eta,pMuon->phi,0.4,iVetoes))  continue;
    if(!passMuonLooseSel(pMuon))                     continue;
    lCount++;
    lVeto.push_back(pMuon);
    addMuon(pMuon,fSelMuons);
  }
  fNMuons = lCount; 
  
  // Add selected tight muons to iVetoes
  if(fNMuons <= 1 && lVeto.size()==1){
    if(passMuonTightSel(lVeto[0]) && lVeto[0]->pt > 20) addVMuon(lVeto[0],iVetoes,MUON_MASS);
  }
  if(fVars.size() > 0)                fillMuon(fN,fSelMuons,fVars);
  if(fNMuons <= 2 && lVeto.size()==2) fillDiMuon(lVeto,iVetoes);
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
void MuonLoader::fillDiMuon(std::vector<TMuon*> lVeto, std::vector<TLorentzVector> &iVetoes) {
  TLorentzVector lVec; lVec.SetPtEtaPhiM(0,0,0,0);
  //TMuon *vMuo1,*vMuo2;
  if((lVeto[1]->q) * (lVeto[0]->q) < 0){ //  opposite charge dimuons 
    if((passMuonTightSel(lVeto[0]) && lVeto[0]->pt > 20) || (passMuonTightSel(lVeto[1]) && lVeto[1]->pt > 20)){ // at least one muon must pass tight selection
      // if(lVeto[0]->pt > lVeto[1]->pt){ //lep1 is the leading lepton 
      //   vMuo1 = lVeto[0];
      //   vMuo2 = lVeto[1];
      // }
      // else{
      //   vMuo2 = lVeto[0];
      //   vMuo1 = lVeto[1];
      // }
      TLorentzVector pVec0; pVec0.SetPtEtaPhiM(lVeto[0]->pt,lVeto[0]->eta,lVeto[0]->phi,MUON_MASS);
      TLorentzVector pVec1; pVec1.SetPtEtaPhiM(lVeto[1]->pt,lVeto[1]->eta,lVeto[1]->phi,MUON_MASS);
      lVec = pVec0+pVec1;
      //if(lVec.M() > 60 && lVec.M() < 120){
      iVetoes.push_back(pVec0);
      iVetoes.push_back(pVec1);
      //}
      int lBase = 3.*fN;
      fVars[lBase+0] = lVec.Pt();
      fVars[lBase+1] = lVec.M();
      fVars[lBase+2] = lVec.Phi();
      fVars[lBase+3] = lVec.Rapidity();
    }
  }
}
