#include "../include/JetLoader.hh"
#include <cmath>
#include <iostream> 
#include <sstream>

using namespace baconhep;

JetLoader::JetLoader(TTree *iTree) { 
  fJets  = new TClonesArray("baconhep::TJet");
  iTree->SetBranchAddress("AK4Puppi",       &fJets);
  fJetBr  = iTree->GetBranch("AK4Puppi");
  fN = 4;
  std::vector<JetCorrectorParameters> corrParams;
  corrParams.push_back(JetCorrectorParameters("/afs/cern.ch/work/p/pharris/public/bacon/prod/CMSSW_7_4_14/src/BaconProd/Utils/data/Summer15_25nsV6_DATA_L1FastJet_AK4PFchs.txt"));
  corrParams.push_back(JetCorrectorParameters("/afs/cern.ch/work/p/pharris/public/bacon/prod/CMSSW_7_4_14/src/BaconProd/Utils/data/Summer15_25nsV6_DATA_L2Relative_AK4PFchs.txt"));
  corrParams.push_back(JetCorrectorParameters("/afs/cern.ch/work/p/pharris/public/bacon/prod/CMSSW_7_4_14/src/BaconProd/Utils/data/Summer15_25nsV6_DATA_L3Absolute_AK4PFchs.txt"));
  corrParams.push_back(JetCorrectorParameters("/afs/cern.ch/work/p/pharris/public/bacon/prod/CMSSW_7_4_14/src/BaconProd/Utils/data/Summer15_25nsV6_DATA_L2L3Residual_AK4PFchs.txt"));
  fJetCorr = new FactorizedJetCorrector(corrParams);
}
JetLoader::~JetLoader() { 
  delete fJets;
  delete fJetBr;
}
double JetLoader::correction(TJet &iJet,double iRho) { 
  TLorentzVector lVec; lVec.SetPtEtaPhiM(iJet.ptRaw,iJet.eta,iJet.phi,iJet.mass);
  fJetCorr->setJetEta(iJet.eta);
  fJetCorr->setJetPt (iJet.ptRaw);
  fJetCorr->setJetPhi(iJet.phi);
  fJetCorr->setJetE  (lVec.E());
  fJetCorr->setRho   (iRho);
  fJetCorr->setJetA  (iJet.area);
  fJetCorr->setJetEMF(-99.0);     
  return ((fJetCorr->getCorrection())*iJet.ptRaw);
}
void JetLoader::reset() { 
  fHT     = 0; 
  fNJets  = 0; 
  fNBTags = 0;
  fNFwd   = 0; 
  fMinDPhi = 1000;
  fNBTagsL = 0;
  fNBTagsM = 0;
  fNBTagsT = 0;
  fNBTagsLdR2 = 0;
  fSelJets.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
}
void JetLoader::setupTree(TTree *iTree, std::string iJetLabel) { 
  reset();
  fTree = iTree;
  fTree->Branch("ht"    ,&fHT    ,"fHT/D");
  fTree->Branch("nPUPPIjets" ,&fNJets ,"fNJets/I");
  fTree->Branch("nbtags",&fNBTags,"fNBTags/I");
  fTree->Branch("nfwd"  ,&fNFwd  ,"fNFwd/I");
  fTree->Branch("mindphi",&fMinDPhi  ,"fMinDPhi/D");
  fTree->Branch("nbPUPPIjetsL" ,&fNBTagsL ,"fNBTagsL/I");
  fTree->Branch("nbPUPPIjetsM" ,&fNBTagsM ,"fNBTagsM/I");
  fTree->Branch("nbPUPPIjetsT" ,&fNBTagsT ,"fNBTagsT/I");
  fTree->Branch("nbPUPPIjetsLdR2" ,&fNBTagsLdR2 ,"fNBTagsLdR2/I");
  std::stringstream diJet;
  diJet << "d" << iJetLabel;
  for(int i0 = 0; i0 < fN*(10)+6; i0++) {double pVar = 0; fVars.push_back(pVar);} // declare array of 47 vars
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars);   // from MonoXUtils.cc => fN =4 j*_pt,j*_eta,j*_phi for j1,j2,j3,j4 (3*4=12)
  addOthers  (iJetLabel.c_str(),iTree,fN,fVars);   // Mass + b-tag + qgid + chf/nhf/emf + .. for j1,j2,j3,j4 (8*4=32)
  addDijet   (diJet.str().c_str(),iTree,1, fVars); // Dijet: pt + mass + csv + ..  for dj1 (7*1 =7)
}
void JetLoader::load(int iEvent) { 
  fJets   ->Clear();
  fJetBr ->GetEntry(iEvent);
}
void JetLoader::selectJets(std::vector<TLorentzVector> &iVetoes,double iMetPhi,double iRho) {
  reset(); 
  int lCount = 0,lNBTag = 0,lNFwd = 0,lNBTagL = 0,lNBTagM = 0,lNBTagT = 0,lNBTagLdR2 = 0;
  fMinDPhi   = 1000; 
  for  (int i0 = 0; i0 < fJets->GetEntriesFast(); i0++) { 
    TJet *pJet = (TJet*)((*fJets)[i0]);
    if(pJet->csv > 0.89 && fabs(pJet->eta) < 2.5 && pJet->pt  > 15 && passJet04Sel(pJet) && !passVeto(pJet->eta,pJet->phi,0.4,iVetoes)) lNBTag++;
    if(pJet->pt        <  30)                 continue;
    if(passVeto(pJet->eta,pJet->phi,0.4,iVetoes)) continue;
    if(fabs(pJet->eta) > 3.0) lNFwd++; 
    //if(i0 == 0) addVJet(pJet,iVetoes,pJet->mass);
    if(!passJetLooseSel(pJet) )  continue;
    fHT += pJet->pt;
    double pDPhi = TMath::Min(fabs(pJet->phi-iMetPhi),2.*TMath::Pi()-fabs(pJet->phi-iMetPhi));
    if(pDPhi < fMinDPhi && lCount < 4) fMinDPhi = pDPhi;
    lCount++;
    if(fabs(pJet->eta) > 2.5) continue;          
    addJet(pJet,fSelJets);

    // jet and b-tag multiplicity
    if(fabs(pJet->eta) < 2.5 && pJet->csv > CSVL){
      lNBTagL++;
      //if(pJet->pt>0 && pJet.DeltaR(vBst15PUPPIJet1)>2) lNBtagLdR2++;
    }
    if(fabs(pJet->eta) < 2.5 && pJet->csv > CSVM)     lNBTagM++;
    if(fabs(pJet->eta) < 2.5 && pJet->csv > CSVT)     lNBTagT++;

  }
  fNJets  = lCount;
  fNBTags = lNBTag;
  fNFwd   = lNFwd;
  fNBTagsL = lNBTagL;
  fNBTagsM = lNBTagM;
  fNBTagsT = lNBTagT;
  fNBTagsLdR2 = lNBTagLdR2;
  fillJet(fN,fSelJets,fVars);
  fillOthers(fN,fSelJets,fVars,iMetPhi,iRho);
  //if(fSelJets.size() == 0) return false; // ask Matteo, it seems to me not necessary
  //if(fSelJets.size() <  2) return true;
  fillDiJet();
  //return true;
}
void JetLoader::addOthers(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals) { 
  for(int i0 = 0; i0 < iN; i0++) { 
    int lBase = iN*3.+i0*8.;//iVals.size();
    std::stringstream pSMass,pSCSV,pSQGID,pSCHF,pSNHF,pSEMF,pSDPhi,pSPtT;  
    pSMass  << iHeader << i0 << "_mass";
    pSCSV   << iHeader << i0 << "_csv";
    pSQGID  << iHeader << i0 << "_qgid";
    pSCHF   << iHeader << i0 << "_CHF";
    pSNHF   << iHeader << i0 << "_NHF";
    pSEMF   << iHeader << i0 << "_NEMF";
    pSDPhi  << iHeader << i0 << "_dphi";
    pSPtT   << iHeader << i0 << "_pttrue";
    iTree->Branch(pSMass .str().c_str(),&iVals[lBase+0],(pSMass .str()+"/D").c_str());
    iTree->Branch(pSCSV .str().c_str() ,&iVals[lBase+1],(pSCSV  .str()+"/D").c_str());
    iTree->Branch(pSQGID.str().c_str() ,&iVals[lBase+2],(pSQGID .str()+"/D").c_str());
    iTree->Branch(pSCHF .str().c_str() ,&iVals[lBase+3],(pSCHF  .str()+"/D").c_str());
    iTree->Branch(pSNHF .str().c_str() ,&iVals[lBase+4],(pSNHF  .str()+"/D").c_str());
    iTree->Branch(pSEMF .str().c_str() ,&iVals[lBase+5],(pSEMF  .str()+"/D").c_str());
    iTree->Branch(pSDPhi.str().c_str() ,&iVals[lBase+6],(pSDPhi .str()+"/D").c_str());
    iTree->Branch(pSPtT .str().c_str() ,&iVals[lBase+7],(pSPtT  .str()+"/D").c_str());
  }
}
void JetLoader::fillOthers(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals,double iMetPhi,double iRho) { 
  int lBase = 3.*fN;
  int lMin = iObjects.size();
  if(iN < lMin) lMin = iN;
  //fMinDPhi = 1000;
  for(int i0 = 0; i0 < lMin; i0++) { 
    iVals[lBase+i0*8+0] = iObjects[i0]->mass;
    iVals[lBase+i0*8+1] = iObjects[i0]->csv;
    iVals[lBase+i0*8+2] = iObjects[i0]->qgid;
    iVals[lBase+i0*8+3] = iObjects[i0]->chHadFrac;
    iVals[lBase+i0*8+4] = iObjects[i0]->neuHadFrac;
    iVals[lBase+i0*8+5] = iObjects[i0]->neuEmFrac;
    double pDPhi = TMath::Min(fabs(iObjects[i0]->phi-iMetPhi),2.*TMath::Pi()-fabs(iObjects[i0]->phi-iMetPhi));
    iVals[lBase+i0*8+6] = pDPhi;
    iVals[lBase+i0*8+7] = correction(*(iObjects[i0]),iRho);
    //if(pDPhi < fMinDPhi) fMinDPhi = pDPhi;
  }
}
void JetLoader::addDijet(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals) { 
 for(int i0 = 0; i0 < iN; i0++) { 
   int iBase=11*fN;
   std::stringstream pSPt,pSMass,pSPhi,pSY,pSQG,pSCSV,pSJDPhi;
   pSPt    << iHeader << i0 << "_pt";
   pSMass  << iHeader << i0 << "_mass";
   pSPhi   << iHeader << i0 << "_phi";
   pSY     << iHeader << i0 << "_y";
   pSQG    << iHeader << i0 << "_qgid";
   pSCSV   << iHeader << i0 << "_csv";
   pSJDPhi << iHeader << i0 << "_jdphi";
   iTree->Branch(pSPt   .str().c_str(),&iVals[iBase+0],(pSPt   .str()+"/D").c_str());
   iTree->Branch(pSMass .str().c_str(),&iVals[iBase+1],(pSMass .str()+"/D").c_str());
   iTree->Branch(pSPhi  .str().c_str(),&iVals[iBase+2],(pSPhi  .str()+"/D").c_str());
   iTree->Branch(pSY    .str().c_str(),&iVals[iBase+3],(pSY    .str()+"/D").c_str());
   iTree->Branch(pSQG   .str().c_str(),&iVals[iBase+4],(pSQG   .str()+"/D").c_str());
   iTree->Branch(pSCSV  .str().c_str(),&iVals[iBase+5],(pSCSV  .str()+"/D").c_str());
   iTree->Branch(pSJDPhi.str().c_str(),&iVals[iBase+6],(pSJDPhi.str()+"/D").c_str());
 }
}
void JetLoader::fillDiJet() { 
  //Select Di-jet
  float lMass = -1;
  TJet *pJet0=0,*pJet1=0;
  TLorentzVector lVec;
  for(unsigned int i0 = 0; i0 < fSelJets.size(); i0++) { 
    TLorentzVector pVec0; pVec0.SetPtEtaPhiM(fSelJets[i0]->pt,fSelJets[i0]->eta,fSelJets[i0]->phi,fSelJets[i0]->mass);
    for(unsigned int i1 = i0+1; i1 < fSelJets.size(); i1++) { 
      TLorentzVector pVec1; pVec1.SetPtEtaPhiM(fSelJets[i1]->pt,fSelJets[i1]->eta,fSelJets[i1]->phi,fSelJets[i1]->mass);
      double pMass = (pVec0+pVec1).M();
      if(fabs(pMass-81.) < fabs(lMass-81.)) { 
	lMass = pMass;
	pJet0 = fSelJets[i0];
	pJet1 = fSelJets[i1];
	lVec = pVec0+pVec1;
      } 
    }
  }
  if(pJet0 == 0 || pJet1 == 0) return;
  int lBase = 11.*fN; 
  fVars[lBase+0] = lVec.Pt();
  fVars[lBase+1] = lMass;
  fVars[lBase+2] = lVec.Phi();
  fVars[lBase+3] = lVec.Rapidity();
  fVars[lBase+4] = pJet0->qgid + pJet1->qgid;
  fVars[lBase+5] = (pJet0->csv > pJet1->csv)*pJet0->csv + (pJet0->csv < pJet1->csv)*pJet0->csv;
  double lDPhi = fabs(pJet0->phi-pJet1->phi); 
  fVars[lBase+6] = TMath::Min(lDPhi,2.*TMath::Pi()-lDPhi);
}
