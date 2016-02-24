#include "../include/ElectronLoader.hh"

#include <cmath>
#include <iostream> 
#include <sstream> 

using namespace baconhep;

ElectronLoader::ElectronLoader(TTree *iTree) { 
  fElectrons  = new TClonesArray("baconhep::TElectron");
  iTree->SetBranchAddress("Electron",       &fElectrons);
  fElectronBr  = iTree->GetBranch("Electron");
  fN = 2;
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
  fIso1 = 0; 
  fIso2 = 0; 
}
void ElectronLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
  fTree->Branch("nele",&fNElectrons,"fNElectrons/I");
  fTree->Branch("neleTight",&fNElectrons,"fNElectronsTight/I");
  fTree->Branch("e0_iso",&fIso1,"fIso1/D");
  fTree->Branch("e1_iso",&fIso2,"fIso2/D");
  for(int i0 = 0; i0 < fN*3.; i0++) {double pVar = 0; fVars.push_back(pVar);} 
  for(int i0 = 0; i0 <     4; i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple("e",iTree,fN,fVars); // 2 electrons e*_pt,e*_eta,e*_phi (2*3=6)
  addDiElectron("de",iTree,1, fVars,fN*3); // dielectron de0_pt, _mass, _phi, _y (1*4 =4)
}
void ElectronLoader::load(int iEvent) { 
  fElectrons   ->Clear();
  fElectronBr ->GetEntry(iEvent);
}
bool ElectronLoader::selectElectrons(double iRho,std::vector<TLorentzVector> &iVetoes) {
  reset();
  int lCount = 0,lTCount=0; 
  for  (int i0 = 0; i0 < fElectrons->GetEntriesFast(); i0++) if(passEleTightSel((TElectron*)fElectrons->At(i0),iRho)) lTCount++;
  fNElectronsTight = lTCount;
  std::vector<TElectron*> lVeto;  
  for  (int i0 = 0; i0 < fElectrons->GetEntriesFast(); i0++) { 
    TElectron *pElectron = (TElectron*)((*fElectrons)[i0]);
    if(pElectron->pt        <=  10)                                            continue;
    if(fabs(pElectron->eta) >=  2.5)                                           continue;
    if(fabs(pElectron->eta) > 1.4442 && fabs(pElectron->eta) < 1.566)          continue;
    if(!passEleSel(pElectron, iRho))         continue;
    lCount++;

    if(!passEleSel(pElectron,iRho) || lTCount == 0)   continue; //?
    lVeto.push_back(pElectron);
    addElectron(pElectron,fSelElectrons);
  }
  for(unsigned int i0 = 0; i0 < lVeto.size(); i0++) addVElectron(lVeto[i0],iVetoes,0.000511);
  fNElectrons = lCount;
  if(fVars.size() > 0) fillElectron(fN,fSelElectrons,fVars);
  if(lCount == 0) return false;
  if(fSelElectrons.size() >  0) fIso1 = eleIso(fSelElectrons[0],iRho);
  if(fSelElectrons.size() >  1) fIso2 = eleIso(fSelElectrons[1],iRho);
  return true;
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
double ElectronLoader::fillDiElectron() { 
  //Select Di-jet
  double lTargetMass = 91.;
  double lMass = -1;
  //TMuon *pMu0=0,*pMu1=0;
  TLorentzVector lVec; lVec.SetPtEtaPhiM(0,0,0,0);
  for(unsigned int i0 = 0; i0 < fSelElectrons.size(); i0++) { 
    TLorentzVector pVec0; pVec0.SetPtEtaPhiM(fSelElectrons[i0]->pt,fSelElectrons[i0]->eta,fSelElectrons[i0]->phi,0.0005);
    for(unsigned int i1 = 0; i1 < i0; i1++) { 
      TLorentzVector pVec1; pVec1.SetPtEtaPhiM(fSelElectrons[i1]->pt,fSelElectrons[i1]->eta,fSelElectrons[i1]->phi,0.0005);
      if((fSelElectrons[i1]->q     )  *  (fSelElectrons[i0]->q) > 0)   continue;
      if((fSelElectrons[i1]->pt < 40) && (fSelElectrons[i0]->pt < 40)) continue;
      double pMass = (pVec0+pVec1).M();
      if(fabs(pMass-lTargetMass) < fabs(lMass-lTargetMass) || lMass < 0) { 
	lMass = pMass;
	lVec = pVec0+pVec1;
      } 
    }
  }
  int lBase = 3.*fN; 
  fVars[lBase+0] = lVec.Pt();
  fVars[lBase+1] = lMass;
  fVars[lBase+2] = lVec.Phi();
  fVars[lBase+3] = lVec.Rapidity();
  return lMass;
}
void ElectronLoader::setDiElectron(TLorentzVector &iVec) { 
  int lBase = 3.*fN; 
  fVars[lBase+0] = iVec.Pt();
  fVars[lBase+1] = iVec.M();
  fVars[lBase+2] = iVec.Phi();
  fVars[lBase+3] = iVec.Eta();
}
