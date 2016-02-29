#include "../include/MuonLoader.hh"
#include <cmath>
#include <iostream> 
#include <sstream> 

using namespace baconhep;

MuonLoader::MuonLoader(TTree *iTree) { 
  fMuons  = new TClonesArray("baconhep::TMuon");
  iTree->SetBranchAddress("Muon",       &fMuons);
  fMuonBr  = iTree->GetBranch("Muon");
  fN = 2;
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
}
void MuonLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
  fTree->Branch("nmu",&fNMuons,"fNMuons/I"); 
  fTree->Branch("nmuTight",&fNMuonsTight,"fNMuonsTight/I");
  for(int i0 = 0; i0 < fN*3.; i0++) {double pVar = 0; fVars.push_back(pVar);} 
  for(int i0 = 0; i0 <     4; i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple("mu",iTree,fN,fVars); // 2 Muons pt,eta,phi (2*3=6)
  addDiMuon  ("dm",iTree,1, fVars,fN*3); // dimuon system *_pt,mass,phi,y for dm0 (1*4)
}
void MuonLoader::load(int iEvent) { 
  fMuons   ->Clear();
  fMuonBr ->GetEntry(iEvent);
}
bool MuonLoader::selectMuons(std::vector<TLorentzVector> &iVetoes) {
  reset(); 
  int lCount = 0,lTCount =0; 
  for  (int i0 = 0; i0 < fMuons->GetEntriesFast(); i0++) if(passMuonTightSel((TMuon*)fMuons->At(i0))) lTCount++; 
  fNMuonsTight = lTCount; // tight muons multiplicty

  std::vector<TMuon*> lVeto;
  for  (int i0 = 0; i0 < fMuons->GetEntriesFast(); i0++) { 
    TMuon *pMuon = (TMuon*)((*fMuons)[i0]);
    if(pMuon->pt        <=  10)                      continue;
    if(fabs(pMuon->eta) >=  2.4)                     continue;
    if(passVeto(pMuon->eta,pMuon->phi,0.4,iVetoes))  continue;
    if(!passMuonLooseSel(pMuon))                     continue;
    lCount++;
    lVeto.push_back(pMuon);
    addMuon(pMuon,fSelMuons); // addObject to fSelMuons
  }
  fNMuons = lCount; // loose muons multiplicity

  if(fNMuons == 1) fillMuon(fN,fSelMuons,fVars); // fillobject, fSelMuons->pt,eta,phi from fVars values
  if(fNMuons == 2){
    double pMass = fillDiMuon();
    if(pMass < 60 || pMass > 120) return false;
  }                                      
  for(unsigned int i0 = 0; i0 < lVeto.size(); i0++)    addVMuon(lVeto[i0],iVetoes,MUON_MASS);

  if(lCount == 0) return false; // no muons selected
  return true;
}
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
double MuonLoader::fillDiMuon() {
  double lMass = -1;
  TLorentzVector lVec; lVec.SetPtEtaPhiM(0,0,0,0);
  TLorentzVector pVec0, pVec1;
  if((fSelMuons[1]->q) * (fSelMuons[0]->q) > 0){ //  opposite charge dimuons 
    if((!passMuonTightSel(fSelMuons[0]) && fSelMuons[0]->pt < 20) || (!passMuonTightSel(fSelMuons[1]) && fSelMuons[1]->pt < 20)){ // at least one muon must pass tight selection
      if(fSelMuons[0]->pt > fSelMuons[1]->pt){ //lep1 is the leading lepton 
	pVec0.SetPtEtaPhiM(fSelMuons[0]->pt,fSelMuons[0]->eta,fSelMuons[0]->phi,MUON_MASS);
	pVec1.SetPtEtaPhiM(fSelMuons[1]->pt,fSelMuons[1]->eta,fSelMuons[1]->phi,MUON_MASS); 
      }
      else{
	pVec1.SetPtEtaPhiM(fSelMuons[0]->pt,fSelMuons[0]->eta,fSelMuons[0]->phi,MUON_MASS);
	pVec0.SetPtEtaPhiM(fSelMuons[1]->pt,fSelMuons[1]->eta,fSelMuons[1]->phi,MUON_MASS);
      }
      lMass = (pVec0+pVec1).M();
      lVec = pVec0+pVec1;
    }
  }
  int lBase = 3.*fN;
  fVars[lBase+0] = lVec.Pt();
  fVars[lBase+1] = lMass;
  fVars[lBase+2] = lVec.Phi();
  fVars[lBase+3] = lVec.Rapidity();   
  return lMass;
}
