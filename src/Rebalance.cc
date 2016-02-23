#include "../include/Rebalance.hh"
#include "DataFormats/RecoCandidate/interface/FitQuality.h"
#include <cmath>
#include <iostream> 
#include <sstream>

using namespace baconhep;

Rebalance::Rebalance(TTree *iTree,bool isData) { 
  fRBZero = new RBZero(isData);
  fJets  = new TClonesArray("baconhep::TJet");
  iTree  ->SetBranchAddress("AK4CHS",       &fJets);
  fJetBr = iTree->GetBranch("AK4CHS");
  fN = 3;
}
Rebalance::~Rebalance() { 
  delete fJets;
  delete fJetBr;
}
void Rebalance::reset() { 
  fNFail     = 0; 
  fNJets     = 0;
  fNBTag     = 0;
  fChi2      = 0;
  fProb      = 0; 
  fMet       = 0; 
  fZMet      = 0; 
  fSMet      = 0;
  fSMetD     = 0;
  fSMetU     = 0; 
  fMetPhi    = 0; 
  fZMetPhi   = 0; 
  fSMetPhi   = 0;
  fSMetUPhi  = 0;
  fSMetDPhi  = 0; 
  fMetDPhi   = 999; 
  fZMetDPhi  = 999; 
  fSMetMDPhi = 999;
  fSMetUDPhi = 999;
  fSMetDDPhi = 999; 
 
  fIMetDPhi   = -1; 
  fIZMetDPhi  = -1; 
  fISMetMDPhi = -1;
  fISMetUDPhi = -1;
  fISMetDDPhi = -1; 
  fSelJets.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  fHT   = 0; 
  fSHT  = 0; 
  fSHTD = 0; 
  fSHTU = 0; 
}
void Rebalance::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
  fTree->Branch("ht"           ,&fHT      ,"fHT/D");
  fTree->Branch("htSamp"       ,&fSHT     ,"fSHT/D");
  fTree->Branch("htSampU"      ,&fSHTU    ,"fSHTU/D");
  fTree->Branch("htSampD"      ,&fSHTD    ,"fSHTD/D");
  fTree->Branch("nfail"        ,&fNFail   ,"fNFail/D");
  fTree->Branch("njets"        ,&fNJets   ,"fNJets/D");
  fTree->Branch("nbtags"       ,&fNBTag   ,"fNBTags/D");
  fTree->Branch("chi2"         ,&fChi2    ,"fChi2/D");
  fTree->Branch("prob"         ,&fProb    ,"fProb/D");
  fTree->Branch("metUncorr"    ,&fMet     ,"fMet/D");
  fTree->Branch("metZero"      ,&fZMet    ,"fZMet/D");
  fTree->Branch("metSamp"      ,&fSMet    ,"fSMet/D");
  fTree->Branch("metSampU"     ,&fSMetU   ,"fSMetU/D");
  fTree->Branch("metSampD"     ,&fSMetD   ,"fSMetD/D");
  fTree->Branch("metUncorrPhi" ,&fMetPhi  ,"fMetPhi/D");
  fTree->Branch("metZeroPhi"   ,&fZMetPhi ,"fZMetPhi/D");
  fTree->Branch("metSampPhi"   ,&fSMetPhi ,"fSMetPhi/D");
  fTree->Branch("metSampUPhi"  ,&fSMetUPhi,"fSMetUPhi/D");
  fTree->Branch("metSampDPhi"  ,&fSMetMDPhi,"fSMetMDPhi/D");
  fTree->Branch("metUncorrDPhi",&fMetDPhi ,"fMetDPhi/D");
  fTree->Branch("metZeroDPhi"  ,&fZMetDPhi,"fZMetDPhi/D");
  fTree->Branch("metSampUDPhi" ,&fSMetUDPhi,"fSMetUDPhi/D");
  fTree->Branch("metSampDDPhi" ,&fSMetDDPhi,"fSMetDDPhi/D");

  fTree->Branch("imetSampDPhi"  ,&fISMetMDPhi,"fISMetMDPhi/D");
  fTree->Branch("imetUncorrDPhi",&fIMetDPhi  ,"fIMetDPhi/D");
  fTree->Branch("imetZeroDPhi"  ,&fIZMetDPhi ,"fIZMetDPhi/D");
  fTree->Branch("imetSampUDPhi" ,&fISMetUDPhi,"fISMetUDPhi/D");
  fTree->Branch("imetSampDDPhi" ,&fISMetDDPhi,"fISMetDDPhi/D");

  //fLabels.push_back("mprune");
  //fLabels.push_back("t2t1");
  fLabels.push_back("pt");
  //fLabels.push_back("phi");
  fLabels.push_back("eta");
  //fLabels.push_back("mnew");
  fLabels.push_back("ptnew");
  //fLabels.push_back("phinew");
  fLabels.push_back("etanew"); 
  //fLabels.push_back("dphi");
  //fLabels.push_back("dphinew"); 
  fLabels.push_back("csv");
  //fLabels.push_back("flav");
  fLabels.push_back("chf");
  fLabels.push_back("nhf");
  for(int i0 = 0; i0 < fN*(int(fLabels.size())); i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple("j",iTree,fN,fVars,0.,fLabels);
}
void Rebalance::load(int iEvent) { 
  fJets   ->Clear();
  fJetBr ->GetEntry(iEvent);
}
bool Rebalance::selectJets(float &iMet,float &iMetPhi,std::vector<TLorentzVector> &iVetoes) {
  reset(); 
  std::vector<TLorentzVector> lJets;
  //std::vector<TLorentzVector> lGenJets;
  std::vector<double>         lCSV;
  for  (int i0 = 0; i0 < fJets->GetEntriesFast(); i0++) { 
    TJet *pJet = (TJet*)((*fJets)[i0]);
    if(pJet->pt          <  30)               continue;
    if(passVeto(pJet->eta,pJet->phi,iVetoes)) continue;
    if(pJet->chHadFrac   < 0.1)  {fNFail++; continue;}
    //if(pJet->neuEmFrac   > 0.7)  {fNFail++; continue;}
    if(pJet->neuHadFrac  > 0.8)  {fNFail++; continue;}              
    if(!passJet04Sel(pJet))                 continue;
    fHT += pJet->pt;
    if(pJet->csv         > 0.89) fNBTag++;
    fNJets++;
    TLorentzVector pVec ; pVec. SetPtEtaPhiM(pJet->pt,pJet->eta,pJet->phi,pJet->mass);
    TLorentzVector pGVec; pGVec.SetPtEtaPhiM(pJet->genpt,pJet->geneta,pJet->genphi,pJet->genm);
    if(lJets.size() < 4.) lJets.push_back(pVec);
    if(lJets.size() < 4.) addJet(pJet,fSelJets);
    //lGenJets.push_back(pGVec);
    double pCSV = pJet->csv;
    if(std::isnan(pCSV) ) pCSV = 0.;
    lCSV.push_back(pCSV);
  }
  //if(lJets.size() == 0) return true;
  TLorentzVector lMet; lMet.SetPtEtaPhiM(iMet,0.,iMetPhi,0);
  //std::cout << "HT:" << fHT << " --> Nwe ";
  double lHT = fHT;
  reco::FitQuality lFit = fRBZero->set(lJets,lMet,lCSV,fHT);
  std::vector<TLorentzVector> lFixJets    = fRBZero->particles();
  //std::cout << "---> Before : " << iMet << " -- After : " << met(lFixJets).Pt() << std::endl; 
  while(met(lFixJets).Pt() > iMet && lJets.size() > 1) {
    lJets.pop_back(); lCSV.pop_back();
    double pHT = lHT;
    lFit = fRBZero->set(lJets,lMet,lCSV,pHT);
    lFixJets  = fRBZero->particles();
    //std::cout << " ---> Before : " << iMet << " -- After : " << met(lFixJets).Pt() << " -- " << lJets.size() << std::endl; 
  }
  std::vector<TLorentzVector> lSmearJets  = fRBZero->smearParticles(0.);
  std::vector<TLorentzVector> lSmearJetsU = fRBZero->smearParticles(1);
  std::vector<TLorentzVector> lSmearJetsD = fRBZero->smearParticles(-1);
  fSHT = 0; 
  for(unsigned int i0 = 0; i0 < lSmearJets.size();  i0++) fSHT  += lSmearJets[i0].Pt();
  fSHTU = 0; 
  for(unsigned int i0 = 0; i0 < lSmearJetsU.size(); i0++) fSHTU += lSmearJetsU[i0].Pt();
  fSHTD = 0; 
  for(unsigned int i0 = 0; i0 < lSmearJetsD.size(); i0++) fSHTD += lSmearJetsD[i0].Pt();
  //TLorentzVector lXMet   = met(lJets);
  TLorentzVector  lZMet  = met(lFixJets);
  TLorentzVector  lSMet  = met(lSmearJets);
  TLorentzVector  lSMetU = met(lSmearJetsU);
  TLorentzVector  lSMetD = met(lSmearJetsD); 
  //fillJets( fN,fSelJets,fVars,lGenJets,lSMet);
  fillJets( fN,fSelJets,fVars,lSmearJets,lSMet);
  fChi2      = lFit.normalizedChi2();
  fProb      = TMath::Prob(lFit.chi2(),lFit.ndof());
  fMet       = lMet.Pt();
  fMetPhi    = lMet.Phi();
  fMetDPhi   = dPhi(lMet,lJets,fIMetDPhi);
  fZMet      = lZMet.Pt();
  fZMetPhi   = lZMet.Phi();
  fZMetDPhi  = dPhi(lZMet,lFixJets,fIZMetDPhi,1.);
  fSMet      = lSMet.Pt();
  fSMetPhi   = lSMet.Phi();
  fSMetMDPhi = dPhi(lSMet,lSmearJets,fISMetMDPhi,1.);
  fSMetU     = lSMetU.Pt();
  fSMetUPhi  = lSMetU.Phi();
  fSMetUDPhi = dPhi(lSMetU,lSmearJetsU,fISMetUDPhi,1.);
  fSMetD     = lSMetD.Pt();
  fSMetDPhi  = lSMetD.Phi();
  fSMetDDPhi = dPhi(lSMetD,lSmearJetsD,fISMetDDPhi,1.);
  return true;
}
void Rebalance::fillJets(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals,std::vector<TLorentzVector> &iVec,TLorentzVector &iMet) { 
  int lBase = 0.;
  int lMin = iObjects.size();
  int lNLabel = int(fLabels.size());
  if(iN < lMin) lMin = iN;
  for(int i0 = 0; i0 < lMin; i0++) { 
    TLorentzVector pVec; pVec.SetPtEtaPhiM(iObjects[i0]->pt,iObjects[i0]->eta,iObjects[i0]->phi,iObjects[i0]->mass);
    //iVals[lBase+i0*lNLabel+0]  = iObjects[i0]->mass;
    iVals[lBase+i0*lNLabel+0]  = iObjects[i0]->pt;
    iVals[lBase+i0*lNLabel+1]  = iObjects[i0]->eta;
    //iVals[lBase+i0*lNLabel+3]  = iObjects[i0]->phi;
    //iVals[lBase+i0*lNLabel+4]  = iVec[i0].M();
    iVals[lBase+i0*lNLabel+2]  = iVec[i0].Pt();
    iVals[lBase+i0*lNLabel+3]  = iVec[i0].Eta();
    //iVals[lBase+i0*lNLabel+7]  = iVec[i0].Phi();
    //iVals[lBase+i0*lNLabel+8]  = iMet.DeltaPhi(pVec);
    //iVals[lBase+i0*lNLabel+9]  = iMet.DeltaPhi(iVec[i0]);
    iVals[lBase+i0*lNLabel+4] = iObjects[i0]->csv;
    //iVals[lBase+i0*lNLabel+11] = iObjects[i0]->partonFlavor;
    iVals[lBase+i0*lNLabel+5] = iObjects[i0]->chHadFrac;
    iVals[lBase+i0*lNLabel+6] = iObjects[i0]->neuHadFrac;
  }
}
float Rebalance::dPhi(TLorentzVector &iMet,std::vector<TLorentzVector> iJets,double &iId,int iN) { 
  double lDPhi = 100; 
  iId = -1.;
  int lMax = iJets.size()-iN; 
  if(lMax > 4) lMax = 4.;
  for(int i0 = 0; i0 < lMax; i0++) { 
    if(iJets[i0].Pt() < 30) continue;
    double pDPhi = iMet.DeltaPhi(iJets[i0]);
    if(fabs(lDPhi) > fabs(pDPhi)) {lDPhi = pDPhi; iId = i0;}
  }
  return lDPhi;
}
TLorentzVector Rebalance::met(std::vector<TLorentzVector> iJets,int iN) { 
  TLorentzVector lMet; lMet.SetPtEtaPhiM(0,0,0,0);
  for(unsigned int i0 = 0; i0 < iJets.size()-iN; i0++) { 
    lMet -= iJets[i0];
  }
  return lMet;
}
