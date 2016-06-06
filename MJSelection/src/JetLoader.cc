#include "../include/JetLoader.hh"
#include <cmath>
#include <iostream> 
#include <sstream>

using namespace baconhep;

JetLoader::JetLoader(TTree *iTree, std::string iJet) { 
  fJets  = new TClonesArray("baconhep::TJet");
  iTree->SetBranchAddress(iJet.c_str(),       &fJets);
  fJetBr = iTree->GetBranch(iJet.c_str());
  fN = 4; // 4 narrow jets
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
double JetLoader::correction(TJet &iJet,float iRho) { 
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
  fNJets           = 0;
  fNJetsAbove80GeV = 0;
  fNJetsdR2        = 0;
  fMT              = 0;
  fMinDPhi         = 1000;
  fMinDFPhi        = 1000; 
  fNBTags          = 0;
  fNBTagsL         = 0;
  fNBTagsM         = 0;
  fNBTagsT         = 0;
  fNBTagsLdR2      = 0;
  fNBTagsMdR2      = 0;
  fNBTagsTdR2      = 0;
  falphaT          = -1;
  fdPhiMin         = -1;
  fMR              = -1;
  fRsq             = -1;
  fHT              = 0;
  fMHT             = 0;
  fMT2             = 0;
  fSelJets.clear();
  fGoodJets.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  fNJetsdR08       = 0;
  fNBTagsLdR08     = 0;
  fNBTagsMdR08     = 0;
  fNBTagsTdR08     = 0;
  fNJetsdR15       = 0;
  fNBTagsLdR15     = 0;
  fNBTagsMdR15     = 0;
  fNBTagsTdR15     = 0;
}
void JetLoader::setupTree(TTree *iTree, std::string iJetLabel) { 
  reset();
  fTree = iTree;
  std::stringstream pSN,pSN80,pSNdR,pSdPhi,pSdFPhi,pSMT,pSb,pSbL,pSbM,pSbT,pSbLdR,pSbMdR,pSbTdR,pSNdR08,pSbLdR08,pSbMdR08,pSbTdR08,pSNdR15,pSbLdR15,pSbMdR15,pSbTdR15;   
  pSN     << iJetLabel << "s";
  pSN80   << iJetLabel << "sAbove80GeV";
  pSNdR   << iJetLabel << "sdR2";
  pSdPhi  << iJetLabel << "mindPhi";
  pSdFPhi << iJetLabel << "mindFPhi";
  pSMT    << iJetLabel << "mT";
  pSb     << iJetLabel << "btags";
  pSbL    << iJetLabel << "sL";
  pSbM    << iJetLabel << "sM";
  pSbT    << iJetLabel << "sT";
  pSbLdR  << iJetLabel << "sLdR2";
  pSbMdR  << iJetLabel << "sMdR2";
  pSbTdR  << iJetLabel << "sTdR2";

  pSNdR08 << iJetLabel << "sdR08";
  pSbLdR08<< iJetLabel << "sLdR08";
  pSbMdR08<< iJetLabel << "sMdR08";
  pSbTdR08<< iJetLabel << "sTdR08";

  pSNdR15 << iJetLabel << "sdR15";
  pSbLdR15<< iJetLabel << "sLdR15";
  pSbMdR15<< iJetLabel << "sMdR15";
  pSbTdR15<< iJetLabel << "sTdR15";

  fTree->Branch(pSN.str().c_str()           ,&fNJets           ,(pSN.str()+"/I").c_str());  // jet multiplicity
  fTree->Branch(pSN80.str().c_str()         ,&fNJetsAbove80GeV ,(pSN80.str()+"/I").c_str());
  fTree->Branch(pSdPhi.str().c_str()        ,&fMinDPhi         ,(pSdPhi.str()+"/D").c_str());
  fTree->Branch(pSdFPhi.str().c_str()       ,&fMinDFPhi        ,(pSdFPhi.str()+"/D").c_str());
  fTree->Branch(pSMT.str().c_str()          ,&fMT              ,(pSMT.str()+"/F").c_str());
  fTree->Branch(pSb.str().c_str()           ,&fNBTags          ,(pSb.str()+"/I").c_str());  // b tags
  fTree->Branch(pSbL.str().c_str()          ,&fNBTagsL         ,(pSbL.str()+"/I").c_str());
  fTree->Branch(pSbM.str().c_str()          ,&fNBTagsM         ,(pSbM.str()+"/I").c_str());
  fTree->Branch(pSbT.str().c_str()          ,&fNBTagsT         ,(pSbT.str()+"/I").c_str());

  fTree->Branch(pSNdR.str().c_str()         ,&fNJetsdR2        ,(pSNdR.str()+"/I").c_str());// outside of jet cone
  fTree->Branch(pSbLdR.str().c_str()        ,&fNBTagsLdR2      ,(pSbLdR.str()+"/I").c_str());
  fTree->Branch(pSbMdR.str().c_str()        ,&fNBTagsMdR2      ,(pSbMdR.str()+"/I").c_str());
  fTree->Branch(pSbTdR.str().c_str()        ,&fNBTagsTdR2      ,(pSbTdR.str()+"/I").c_str());

  fTree->Branch(pSNdR08.str().c_str()       ,&fNJetsdR08       ,(pSNdR08.str()+"/I").c_str());
  fTree->Branch(pSbLdR08.str().c_str()      ,&fNBTagsLdR08     ,(pSbLdR08.str()+"/I").c_str());
  fTree->Branch(pSbMdR08.str().c_str()      ,&fNBTagsMdR08     ,(pSbMdR08.str()+"/I").c_str());
  fTree->Branch(pSbTdR08.str().c_str()      ,&fNBTagsTdR08     ,(pSbTdR08.str()+"/I").c_str());

  fTree->Branch(pSNdR15.str().c_str()       ,&fNJetsdR15       ,(pSNdR15.str()+"/I").c_str());
  fTree->Branch(pSbLdR15.str().c_str()      ,&fNBTagsLdR15     ,(pSbLdR15.str()+"/I").c_str());
  fTree->Branch(pSbMdR15.str().c_str()      ,&fNBTagsMdR15     ,(pSbMdR15.str()+"/I").c_str());
  fTree->Branch(pSbTdR15.str().c_str()      ,&fNBTagsTdR15     ,(pSbTdR15.str()+"/I").c_str());

  for(int i0 = 0; i0 < fN*(10)+3; i0++) {double pVar = 0; fVars.push_back(pVar);}           // declare array of 43 vars
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars);                                            // from MonoXUtils.cc => fN =4 j*_pt,j*_eta,j*_phi for j1,j2,j3,j4 (3*4=12)
  addOthers  (iJetLabel.c_str(),iTree,fN,fVars);                                            // Mass + b-tag + qgid + chf/nhf/emf + .. for j1,j2,j3,j4 (8*4=32 -6*4=24)
}
void JetLoader::setupTreeDiJet(TTree *iTree, std::string iJetLabel) {
  reset();
  fTree = iTree;
  std::stringstream diJet;   diJet << "dj" << iJetLabel;
  addDijet   (diJet.str().c_str(),iTree,1, fVars);                                   
}
void JetLoader::setupTreeRazor(TTree *iTree, std::string iJetLabel) {
  reset();
  fTree = iTree;
  std::stringstream pSalphaT,pSdPhiMin,pSMR,pSRsq,pSdeltaPhi,pSHT,pSMHT;//,pSMT2;
  pSalphaT   << iJetLabel << "alphaT";
  pSdPhiMin  << iJetLabel << "mindFPhi";
  pSMR       << iJetLabel << "MR";
  pSRsq      << iJetLabel << "Rsq";
  pSdeltaPhi << iJetLabel << "deltaPhi";
  pSHT       << iJetLabel << "HT";
  pSMHT      << iJetLabel << "MHT";
  // pSMT2      << iJetLabel << "MT2";
  iTree->Branch(pSalphaT  .str().c_str(),&falphaT  ,(pSalphaT  .str()+"/F").c_str());     // alphaT
  iTree->Branch(pSdPhiMin .str().c_str(),&fdPhiMin ,(pSdPhiMin .str()+"/F").c_str());     // dPhi Min
  iTree->Branch(pSMR      .str().c_str(),&fMR      ,(pSMR      .str()+"/F").c_str());     // MR
  iTree->Branch(pSRsq     .str().c_str(),&fRsq     ,(pSRsq     .str()+"/F").c_str());     // Rsq
  iTree->Branch(pSdeltaPhi.str().c_str(),&fdeltaPhi,(pSdeltaPhi.str()+"/F").c_str());     // deltaPhi
  iTree->Branch(pSHT      .str().c_str(),&fHT      ,(pSHT      .str()+"/F").c_str());     // HT
  iTree->Branch(pSMHT     .str().c_str(),&fMHT     ,(pSMHT     .str()+"/F").c_str());     // MHT
  // iTree->Branch(pSMT2     .str().c_str(),&fMT2     ,(pSMT2     .str()+"/F").c_str());     // MT2
}
void JetLoader::load(int iEvent) { 
  fJets   ->Clear();
  fJetBr ->GetEntry(iEvent);
}
void JetLoader::selectJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iVJets,std::vector<TLorentzVector> &iJets,float iMet,float iMetPhi,float iFMet,float iFMetPhi){ 
  reset(); 
  int lCount = 0,lCountAbove80GeV = 0,lCountdR2 = 0,lNBTag = 0,lNBTagL = 0,lNBTagM = 0,lNBTagT = 0,lNBTagLdR2 = 0,lNBTagMdR2 = 0,lNBTagTdR2 = 0;
  double pDPhi(999),pDFPhi(999);
  float  pMhtX(0.), pMhtY(0.);

  for  (int i0 = 0; i0 < fJets->GetEntriesFast(); i0++) { 
    TJet *pJet = (TJet*)((*fJets)[i0]);
    if(pJet->csv > 0.89 && fabs(pJet->eta) < 2.5 && pJet->pt  > 15 && passJet04Sel(pJet) && !passVeto(pJet->eta,pJet->phi,0.4,iVetoes)) lNBTag++;
    if(passVeto(pJet->eta,pJet->phi,0.4,iVetoes)) continue;
    if(pJet->pt        <=  30)                    continue;
    if(fabs(pJet->eta) >= 4.5)                    continue;
    if(!passJetLooseSel(pJet))                    continue;
    lCount++;
    if(pJet->pt        >   80) lCountAbove80GeV++;
    addJet(pJet,fSelJets);
    addVJet(pJet,iJets,pJet->mass);

    TLorentzVector vPJet; vPJet.SetPtEtaPhiM(pJet->pt, pJet->eta, pJet->phi, pJet->mass);
    fHT += vPJet.Pt(); pMhtX += vPJet.Px(); pMhtY += vPJet.Py();
    fGoodJets.push_back(pJet);

    if(acos(cos(iMetPhi-pJet->phi))    < pDPhi)    pDPhi  = acos(cos(iMetPhi-pJet->phi));
    if(iFMet > 0){
      if(acos(cos(iFMetPhi-pJet->phi)) < pDFPhi)   pDFPhi = acos(cos(iFMetPhi-pJet->phi)); 
    }

    // jet and b-tag multiplicity
    if(iVJets.size()>0 && iVJets[0].Pt()>0 && vPJet.DeltaR(iVJets[0])>2) lCountdR2++;
    if(fabs(pJet->eta) < 2.5 && pJet->csv > CSVL){
      lNBTagL++;
      if(iVJets.size()>0) {if(pJet->pt>0 && vPJet.DeltaR(iVJets[0])>2) lNBTagLdR2++;}
    }
    if(fabs(pJet->eta) < 2.5 && pJet->csv > CSVM){ 
      lNBTagM++;
      if(iVJets.size()>0) {if(pJet->pt>0 && vPJet.DeltaR(iVJets[0])>2) lNBTagMdR2++;}
    }
    if(fabs(pJet->eta) < 2.5 && pJet->csv > CSVT){
      lNBTagT++;
      if(iVJets.size()>0) {if(pJet->pt>0 && vPJet.DeltaR(iVJets[0])>2) lNBTagTdR2++;}
    }
  }
  fNJets           = lCount;
  fNJetsAbove80GeV = lCountAbove80GeV;
  fNJetsdR2        = lCountdR2;
  fMinDPhi         = pDPhi;
  fMinDFPhi        = pDFPhi;
  fNBTags          = lNBTag;
  fNBTagsL         = lNBTagL;
  fNBTagsM         = lNBTagM;
  fNBTagsT         = lNBTagT;
  fNBTagsLdR2      = lNBTagLdR2;
  fNBTagsMdR2      = lNBTagMdR2;
  fNBTagsTdR2      = lNBTagTdR2;
  fillJet(fN,fSelJets,fVars);
  fillOthers(fN,fSelJets,fVars);
  fillDiJet();
  fillRazor(iJets,iMet,iMetPhi);
  TLorentzVector fMyMHT; fMyMHT.SetPxPyPzE(-pMhtX, -pMhtY, 0, sqrt(pow(pMhtX,2) + pow(pMhtY,2)));
  fMHT             = fMyMHT.Pt();
}
void JetLoader::fillGoodJets(std::vector<TLorentzVector> iVJets,double dR, std::vector<const TJet*> &iGoodJets){
  iGoodJets.clear();
  int lCountdR2 = 0,lNBTagLdR2 = 0,lNBTagMdR2 = 0,lNBTagTdR2 = 0;
  for(unsigned int i0 = 0; i0 < fGoodJets.size(); i0++) {
    TLorentzVector vPJet; vPJet.SetPtEtaPhiM(fGoodJets[i0]->pt, fGoodJets[i0]->eta, fGoodJets[i0]->phi, fGoodJets[i0]->mass);
    if(iVJets.size()>0 && iVJets[0].Pt()>0){
      if(vPJet.DeltaR(iVJets[0])>dR){
	iGoodJets.push_back(fGoodJets[i0]);
	lCountdR2++;
	if(fGoodJets[i0]->pt>0 && fabs(fGoodJets[i0]->eta) < 2.5 && fGoodJets[i0]->csv > CSVL) lNBTagLdR2++;
	if(fGoodJets[i0]->pt>0 && fabs(fGoodJets[i0]->eta) < 2.5 && fGoodJets[i0]->csv > CSVM) lNBTagMdR2++;
	if(fGoodJets[i0]->pt>0 && fabs(fGoodJets[i0]->eta) < 2.5 && fGoodJets[i0]->csv > CSVT) lNBTagTdR2++;
      }
    }
  }
  if(dR == 0.8){
    fNJetsdR08        = lCountdR2;
    fNBTagsLdR08      = lNBTagLdR2;
    fNBTagsMdR08      = lNBTagMdR2;
    fNBTagsTdR08      = lNBTagTdR2;  
  }
 if(dR == 1.5){
    fNJetsdR15        = lCountdR2;
    fNBTagsLdR15      = lNBTagLdR2;
    fNBTagsMdR15      = lNBTagMdR2;
    fNBTagsTdR15      = lNBTagTdR2;
  }
}
void JetLoader::addOthers(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals) { 
  for(int i0 = 0; i0 < iN; i0++) { 
    int lBase = iN*3.+i0*6.;
    std::stringstream pSMass,pSCSV,pSQGID,pSCHF,pSNHF,pSEMF;//,pSDPhi,pSPtT;  
    pSMass  << iHeader << i0 << "_mass";
    pSCSV   << iHeader << i0 << "_csv";
    pSQGID  << iHeader << i0 << "_qgid";
    pSCHF   << iHeader << i0 << "_CHF";
    pSNHF   << iHeader << i0 << "_NHF";
    pSEMF   << iHeader << i0 << "_NEMF";
    iTree->Branch(pSMass .str().c_str(),&iVals[lBase+0],(pSMass .str()+"/D").c_str());
    iTree->Branch(pSCSV .str().c_str() ,&iVals[lBase+1],(pSCSV  .str()+"/D").c_str());
    iTree->Branch(pSQGID.str().c_str() ,&iVals[lBase+2],(pSQGID .str()+"/D").c_str());
    iTree->Branch(pSCHF .str().c_str() ,&iVals[lBase+3],(pSCHF  .str()+"/D").c_str());
    iTree->Branch(pSNHF .str().c_str() ,&iVals[lBase+4],(pSNHF  .str()+"/D").c_str());
    iTree->Branch(pSEMF .str().c_str() ,&iVals[lBase+5],(pSEMF  .str()+"/D").c_str());
  }
}
void JetLoader::fillOthers(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals){ 
  int lBase = 3.*fN;
  int lMin = iObjects.size();
  if(iN < lMin) lMin = iN;
  for(int i0 = 0; i0 < lMin; i0++) { 
    iVals[lBase+i0*6+0] = iObjects[i0]->mass;
    iVals[lBase+i0*6+1] = iObjects[i0]->csv;
    iVals[lBase+i0*6+2] = iObjects[i0]->qgid;
    iVals[lBase+i0*6+3] = iObjects[i0]->chHadFrac;
    iVals[lBase+i0*6+4] = iObjects[i0]->neuHadFrac;
    iVals[lBase+i0*6+5] = iObjects[i0]->neuEmFrac;
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
void JetLoader::fillRazor(std::vector<TLorentzVector> iJets,float iMet, float iMetPhi) {
  std::vector<TLorentzVector> hemispheres = getHemispheres( iJets );
  TLorentzVector PFMET; PFMET.SetPtEtaPhiM(iMet, 0, iMetPhi, 0);
  // float testMass = -1.;
  fMR       = computeMR(hemispheres[0], hemispheres[1]);
  fRsq      = computeRsq(hemispheres[0], hemispheres[1], PFMET);
  fdeltaPhi = fabs(hemispheres[0].DeltaPhi(hemispheres[1]));
  // fMT2      = calcMT2(testMass, kFalse, iJets, PFMET, 0, 0);
}
