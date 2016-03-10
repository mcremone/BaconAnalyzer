#include "../include/ElectronLoader.hh"

#include "TFile.h"
#include <cmath>
#include <iostream> 
#include <sstream> 

using namespace baconhep;

ElectronLoader::ElectronLoader(TTree *iTree,std::string ieleScaleFactorFilename) { 
  fElectrons  = new TClonesArray("baconhep::TElectron");
  iTree->SetBranchAddress("Electron",       &fElectrons);
  fElectronBr  = iTree->GetBranch("Electron");
  fN = 2;
  TFile *fEleSF = new TFile(ieleScaleFactorFilename.c_str());
  fhEleVeto =  (TH2D*) fEleSF->Get("factorized_scalefactors_Veto_ele");
  fhEleVeto->SetDirectory(0);
  fhEleTight = (TH2D*) fEleSF->Get("factorized_scalefactors_Tight_ele");
  fhEleTight->SetDirectory(0);
  fEleSF->Close();
}
ElectronLoader::~ElectronLoader() { 
  delete fElectrons;
  delete fElectronBr;
}
void ElectronLoader::reset() { 
  fNElectrons = 0; 
  fNElectronsTight = 0; 
  fSelElectrons.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  for(unsigned int i0 = 0; i0 < feleSFVars.size(); i0++) feleSFVars[i0] = 1;
  fIso1 = 0; 
  fIso2 = 0; 
}
void ElectronLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
  fTree->Branch("nele",&fNElectrons,"fNElectrons/I");
  fTree->Branch("neleTight",&fNElectrons,"fNElectronsTight/I");
  fTree->Branch("vele0_iso",&fIso1,"fIso1/D");
  fTree->Branch("vele1_iso",&fIso2,"fIso2/D");
  for(int i0 = 0; i0 < fN*3.; i0++) {double pVar = 0; fVars.push_back(pVar);} 
  for(int i0 = 0; i0 <     4; i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple("vele",iTree,fN,fVars);          // 2 electrons ele*_pt,ele*_eta,ele*_phi (2*3=6)
  addDiElectron("vdiele",iTree,1, fVars,fN*3); // dielectron diele0_pt, _mass, _phi, _y (1*4 =4)
  for(int i0 = 0; i0 <     3; i0++) {double pVar = 1; feleSFVars.push_back(pVar);}
  addLepSF("eleSF",iTree,feleSFVars);          // eleSF0,eleSF1,eleSF2
}
void ElectronLoader::load(int iEvent) { 
  fElectrons   ->Clear();
  fElectronBr ->GetEntry(iEvent);
}
void ElectronLoader::selectElectrons(double iRho,std::vector<TLorentzVector> &iVetoes) {
  reset();
  int lCount = 0,lTCount=0; 
  for  (int i0 = 0; i0 < fElectrons->GetEntriesFast(); i0++) if(passEleTightSel((TElectron*)fElectrons->At(i0),iRho)) lTCount++;
  fNElectronsTight = lTCount; // tight electrons multiplicity

  std::vector<TElectron*> lVeto;  
  for  (int i0 = 0; i0 < fElectrons->GetEntriesFast(); i0++) { 
    TElectron *pElectron = (TElectron*)((*fElectrons)[i0]);
    if(pElectron->pt        <=  10)                                            continue;
    if(fabs(pElectron->eta) >=  2.5)                                           continue;
    if(fabs(pElectron->eta) > 1.4442 && fabs(pElectron->eta) < 1.566)          continue;
    if(!passEleSel(pElectron, iRho))         continue;
    lCount++;

    lVeto.push_back(pElectron);
    addElectron(pElectron,fSelElectrons);
  }
  fNElectrons = lCount;
  if(fVars.size() > 0) fillElectron(fN,fSelElectrons,fVars);

  if(fSelElectrons.size() >  0) fIso1 = eleIso(fSelElectrons[0],iRho);
  if(fSelElectrons.size() >  1) fIso2 = eleIso(fSelElectrons[1],iRho);

  if(fNElectrons <= 1 && lVeto.size()==1) {
    if(passEleTightSel(lVeto[0], iRho) && lVeto[0]->pt > 40) {
      addVElectron(lVeto[0],iVetoes,0.000511);
    }
  }
  if(fNElectrons <= 2 && lVeto.size()==2){
    fillDiElectron(iRho,lVeto,iVetoes);
  }

}
void ElectronLoader::addDiElectron(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase) { 
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
void ElectronLoader::fillDiElectron(double iRho, std::vector<TElectron*> lVeto, std::vector<TLorentzVector> &iVetoes) { 
  TLorentzVector lVec; lVec.SetPtEtaPhiM(0,0,0,0);
  //TElectron *vEle1,*vEle2;
  if((lVeto[1]->q)  *  (lVeto[0]->q) < 0){ //opposite charge dielectron 
    if((passEleTightSel(lVeto[0], iRho) && lVeto[0]->pt > 40) || (passEleTightSel(lVeto[1], iRho) && lVeto[1]->pt > 40)){ // at least one electron must pass tight selection                                                     
      //if(lVeto[0]->pt > lVeto[1]->pt){ //lep1 is the leading lepton 
      //vEle1 = lVeto[0];
      //vEle2 = lVeto[1];
      //}
      //else{
      //vEle2 = lVeto[0];
      //vEle1 = lVeto[1];
      //}
      TLorentzVector pVec0; pVec0.SetPtEtaPhiM(lVeto[0]->pt,lVeto[0]->eta,lVeto[0]->phi,0.000510998910);
      TLorentzVector pVec1; pVec1.SetPtEtaPhiM(lVeto[1]->pt,lVeto[1]->eta,lVeto[1]->phi,0.000510998910);
      lVec = pVec0+pVec1;
      if(lVec.M() > 60 && lVec.M() < 120){
	iVetoes.push_back(pVec0);
	iVetoes.push_back(pVec1);
        //addVElectron(vEle1,iVetoes,0.000510998910);
        //addVElectron(vEle2,iVetoes,0.000510998910);
      }
    }
  }
  int lBase = 3.*fN; 
  fVars[lBase+0] = lVec.Pt();
  fVars[lBase+1] = lVec.M();
  fVars[lBase+2] = lVec.Phi();
  fVars[lBase+3] = lVec.Rapidity();
}
