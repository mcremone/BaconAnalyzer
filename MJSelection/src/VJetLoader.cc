#include "../include/VJetLoader.hh"
#include <cmath>
#include <iostream> 

#include <string>
#include <sstream>

using namespace baconhep;

VJetLoader::VJetLoader(TTree *iTree,std::string iJet,std::string iAddJet) { 
  fVJets         = new TClonesArray("baconhep::TJet");
  fVAddJets      = new TClonesArray("baconhep::TAddJet");

  iTree->SetBranchAddress(iJet.c_str(),       &fVJets);
  iTree->SetBranchAddress(iAddJet.c_str(),    &fVAddJets);
  fVJetBr        = iTree->GetBranch(iJet.c_str());
  fVAddJetBr     = iTree->GetBranch(iAddJet.c_str());

  fN = 1;
}
VJetLoader::~VJetLoader() { 
  delete fVJets;
  delete fVJetBr;
  delete fVAddJets;
  delete fVAddJetBr;
}
void VJetLoader::reset() { 
  fNVJets = 0; 
  fVMT    = 0;
  fSelVJets.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
}
void VJetLoader::setupTree(TTree *iTree, std::string iJetLabel) { 
  reset();
  fLabels.clear();
  fLabels.push_back("mass");
  fLabels.push_back("csv");
  fLabels.push_back("CHF");
  fLabels.push_back("NHF");
  fLabels.push_back("NEFM");
  fLabels.push_back("tau21");
  fLabels.push_back("tau32");
  fLabels.push_back("msd");
  fLabels.push_back("rho");
  fLabels.push_back("phil");
  fLabels.push_back("minsubcsv");
  fLabels.push_back("maxsubcsv");
  //fLabels.push_back("mindPhi");
  //fLabels.push_back("mindFPhi");
  std::stringstream pSMT;   pSMT << iJetLabel << "0_mT";
  std::stringstream pSNJ;   pSNJ << iJetLabel << "0_njets";
  fTree = iTree;
  fTree->Branch(pSNJ.str().c_str() ,&fNVJets ,(pSNJ.str()+"/I").c_str());
  fTree->Branch(pSMT.str().c_str() ,&fVMT    ,(pSMT.str()+"/F").c_str());
  for(int i0 = 0; i0 < fN*3.;                    i0++) {double pVar = 0; fVars.push_back(pVar);} // declare array of vars
  for(int i0 = 0; i0 < fN*(int(fLabels.size())); i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars);                                                 // from MonoXUtils.cc => fN =1 *_pt,*_eta,*_phi for vjet0 (3*1=3)
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars,fN*3,fLabels);
}
void VJetLoader::load(int iEvent) { 
  fVJets       ->Clear();
  fVJetBr      ->GetEntry(iEvent);
  fVAddJets    ->Clear();
  fVAddJetBr   ->GetEntry(iEvent);
}
void VJetLoader::selectVJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,std::vector<TLorentzVector> &iVJet, double dR){
  reset(); 
  int lCount = 0; 
  iJets.clear(); iVJet.clear();
  for  (int i0 = 0; i0 < fVJets->GetEntriesFast(); i0++) { 
    TJet *pVJet = (TJet*)((*fVJets)[i0]);
    if(pVJet->pt        <=  200)                    continue;
    if(fabs(pVJet->eta) >=  2.4)                    continue;
    if(passVeto(pVJet->eta,pVJet->phi,dR,iVetoes))  continue;
    if(!passJetLooseSel(pVJet))                     continue;
    addVJet(pVJet,iJets,pVJet->mass);
    addJet(pVJet,fSelVJets);
    lCount++;
  }
  if(iJets.size() > 0){
    TLorentzVector ivJ;
    ivJ.SetPtEtaPhiM(fSelVJets[0]->pt,fSelVJets[0]->eta,fSelVJets[0]->phi,fSelVJets[0]->mass);
    iVJet.push_back(ivJ);
  }
  fNVJets = lCount;
  fillJet( fN,fSelVJets,fVars);
  fillVJet(fN,fSelVJets,fVars); 
}
void VJetLoader::fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals){ 
  int lBase = 3.*fN;
  int lMin = iObjects.size();
  int lNLabel = int(fLabels.size());
  if(iN < lMin) lMin = iN;
  for(int i0 = 0; i0 < lMin; i0++) { 
    TAddJet *pAddJet = getAddJet(iObjects[i0]);
    iVals[lBase+i0*lNLabel+0]  = iObjects[i0]->mass;
    iVals[lBase+i0*lNLabel+1]  = iObjects[i0]->csv;
    iVals[lBase+i0*lNLabel+2]  = iObjects[i0]->chHadFrac;
    iVals[lBase+i0*lNLabel+3]  = iObjects[i0]->neuHadFrac;
    iVals[lBase+i0*lNLabel+4]  = iObjects[i0]->neuEmFrac;
    iVals[lBase+i0*lNLabel+5]  = (pAddJet->tau2/pAddJet->tau1);
    iVals[lBase+i0*lNLabel+6]  = (pAddJet->tau3/pAddJet->tau2);
    iVals[lBase+i0*lNLabel+7]  = pAddJet     ->mass_sd0;
    iVals[lBase+i0*lNLabel+8]  = log((pAddJet->mass_sd0*pAddJet->mass_sd0)/iObjects[i0]->pt);
    iVals[lBase+i0*lNLabel+9]  = pAddJet->mass_sd0/log(iObjects[i0]->pt);
    iVals[lBase+i0*lNLabel+10] = TMath::Min(pAddJet->sj1_csv,pAddJet->sj2_csv);
    iVals[lBase+i0*lNLabel+11] = TMath::Max(TMath::Max(pAddJet->sj1_csv,pAddJet->sj2_csv),TMath::Max(pAddJet->sj3_csv,pAddJet->sj4_csv));
  }
}
void VJetLoader::addBoson(TGenParticle *iBoson) { 
  int lBase = 3.*fN;
  int lMin = int(fSelVJets.size());
  int lNLabel = int(fLabels.size());
  if(fN < lMin) lMin = fN;
  for(int i0 = 0; i0 < lMin; i0++) {
    float pDEta = fabs(iBoson->eta - fSelVJets[i0]->eta);
    float pDPhi = fabs(iBoson->phi - fSelVJets[i0]->phi);
    if(pDPhi > 2.*TMath::Pi()-pDPhi) pDPhi =  2.*TMath::Pi()-pDPhi;
    fVars[lBase+i0*lNLabel+lNLabel-1] = sqrt(pDEta*pDEta+pDPhi*pDPhi);
  }
}
TAddJet *VJetLoader::getAddJet(TJet *iJet) { 
  int lIndex = -1;
  TAddJet *lJet = 0; 
  for(int i0 = 0; i0 < fVJets->GetEntriesFast(); i0++) { 
    if((*fVJets)[i0] == iJet) { lIndex = i0; break;}
  }
  if(lIndex == -1) return 0;
  for  (int i0 = 0; i0 < fVAddJets->GetEntriesFast(); i0++) { 
    TAddJet *pJet = (TAddJet*)((*fVAddJets)[i0]);
    if(pJet->index == fabs(lIndex)) { lJet = pJet; break;}
  }
  return lJet;
}
int  VJetLoader::trigger(TJet *iJet) { 
  int pId = 0; 
  for(int i0 = 0; i0 < int(fTrigString.size()); i0++) if(fTrigger->passObj(fTrigString[i0],1,iJet->hltMatchBits))  pId += TMath::Power(2.,i0);
  return pId;
}
float VJetLoader::pullDot(float iY1,float iY2,float iPhi1,float iPhi2) { 
  return (iY1*iY1 + iPhi1*iPhi2);
}
TJet* VJetLoader::getLargeJet(TJet *iMatch) { 
  TJet *lFatJet = 0;
  for  (int i0 = 0; i0 < fFatJets->GetEntriesFast(); i0++) {
    TJet *pFatJet = (TJet*)((*fFatJets)[i0]);
    float pDEta = fabs(pFatJet->eta-iMatch->eta);
    float pDPhi = fabs(pFatJet->phi-iMatch->phi);
    if(pDPhi > 2.*TMath::Pi()-pDPhi) pDPhi =  2.*TMath::Pi()-pDPhi;
    if(sqrt(pDEta*pDEta+pDPhi*pDPhi) > 0.4) continue;
    lFatJet = pFatJet;
    break;
  }
  return lFatJet;
}
