#include "../include/TauLoader.hh"
#include <cmath>
#include <iostream> 

using namespace baconhep;

TauLoader::TauLoader(TTree *iTree) { 
  fTaus  = new TClonesArray("baconhep::TTau");
  iTree->SetBranchAddress("Tau",       &fTaus);
  fTauBr  = iTree->GetBranch("Tau");
  fN = 1;
}
TauLoader::~TauLoader() { 
  delete fTaus;
  delete fTauBr;
}
void TauLoader::reset() { 
  fNTaus = 0; 
  fTauIso = 0; 
  fSelTaus.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
}
void TauLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
  fTree->Branch("ntau",&fNTaus,"fNTaus/I");                 // tau multiplicity
  fTree->Branch("vtau0_iso",&fTauIso,"fTauIso/D");          // tau0_isolation
  for(int i0 = 0; i0 < fN*3.; i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple("vtau",iTree,fN,fVars);                       // tau0_pt, tau0_eta, tau0_phi (1*4=4)
}
void TauLoader::load(int iEvent) { 
  fTaus   ->Clear();
  fTauBr ->GetEntry(iEvent);
}
void TauLoader::selectTaus(std::vector<TLorentzVector> &iVetoes) {
  reset(); 
  int lCount = 0; 
  for  (int i0 = 0; i0 < fTaus->GetEntriesFast(); i0++) { 
    TTau *pTau = (TTau*)((*fTaus)[i0]);
    if(passVeto(pTau->eta,pTau->phi,0.4,iVetoes)) continue; 
    if(pTau->pt        <=  18)           continue;
    if(fabs(pTau->eta) >=  2.3)          continue;
    if(!passTauSel(pTau))                continue;
    //addVTau(pTau,iVetoes,pTau->m);                          // ask Matteo if we should include or not - seems like no
    addTau(pTau,fSelTaus);
    lCount++;
  }
  fNTaus = lCount;
  if(fVars.size() > 0) fillTau(fN,fSelTaus,fVars);
  if(fSelTaus.size()  > 0) fTauIso = fSelTaus[0]->rawIso3Hits;
}
