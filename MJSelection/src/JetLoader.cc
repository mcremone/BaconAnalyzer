#include "../include/JetLoader.hh"
#include <cmath>
#include <iostream> 
#include <sstream>

using namespace baconhep;

JetLoader::JetLoader(TTree *iTree,std::string btagScaleFactorFilename) { 
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
  fJetCalib = new BTagCalibration("csvv2",btagScaleFactorFilename);
  for(auto imtype : measurementTypes) { // freadersL 6
    for(auto ivtype : variationTypes) {
      freadersL.push_back(new BTagCalibrationReader(fJetCalib, BTagEntry::OP_LOOSE,  imtype, ivtype)); // first mujets(HF) then comb(LF) and first central(0,3) then up(1,4) and then down(2,5)
      freadersM.push_back(new BTagCalibrationReader(fJetCalib, BTagEntry::OP_MEDIUM, imtype, ivtype));
      freadersT.push_back(new BTagCalibrationReader(fJetCalib, BTagEntry::OP_TIGHT,  imtype, ivtype));
    }
  }
  freaders.push_back(freadersL); freaders.push_back(freadersM); freaders.push_back(freadersT);
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
  fGoodJets.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  for(unsigned int i0 = 0; i0 < fBTagVars.size(); i0++) fBTagVars[i0] = 0;
}
void JetLoader::setupTree(TTree *iTree, std::string iJetLabel) { 
  reset();
  fTree = iTree;
  //fTree->Branch("ht"            ,&fHT          ,"fHT/D");
  //fTree->Branch("nfwd"          ,&fNFwd        ,"fNFwd/I");
  fTree->Branch("nPUPPIjets"      ,&fNJets       ,"fNJets/I");
  fTree->Branch("nbtags"          ,&fNBTags      ,"fNBTags/I");
  fTree->Branch("mindphi"         ,&fMinDPhi     ,"fMinDPhi/D");
  fTree->Branch("nbPUPPIjetsL"    ,&fNBTagsL     ,"fNBTagsL/I");
  fTree->Branch("nbPUPPIjetsM"    ,&fNBTagsM     ,"fNBTagsM/I");
  fTree->Branch("nbPUPPIjetsT"    ,&fNBTagsT     ,"fNBTagsT/I");
  fTree->Branch("nbPUPPIjetsLdR2" ,&fNBTagsLdR2  ,"fNBTagsLdR2/I");
  std::stringstream diJet;
  diJet << "d" << iJetLabel;
  for(int i0 = 0; i0 < fN*(10)+6; i0++) {double pVar = 0; fVars.push_back(pVar);}     // declare array of 47 vars
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars);                                      // from MonoXUtils.cc => fN =4 j*_pt,j*_eta,j*_phi for j1,j2,j3,j4 (3*4=12)
  addOthers  (iJetLabel.c_str(),iTree,fN,fVars);                                      // Mass + b-tag + qgid + chf/nhf/emf + .. for j1,j2,j3,j4 (8*4=32)
  addDijet   (diJet.str().c_str(),iTree,1, fVars);                                    // Dijet: pt + mass + csv + ..  for dj1 (7*1 =7)
  for(int i0 = 0; i0 < 60; i0++) {float pBTagVar = 0; fBTagVars.push_back(pBTagVar);} // declare array of 60 vars ( L0,L1,Lminus1,L2, M0,M1,Mminus1,M2 T0,T1,Tminus1,T2) for (CENT,MISTAGUP,MISTAGDO,BTAGUP,BTAGDO)
  int i1 = 0;
  for(auto iwptype : wpTypes) { 
    addBTag(iJetLabel.c_str(),iTree,iwptype,fLabels,i1,fBTagVars);
    i1 += 20;
  }
}
void JetLoader::load(int iEvent) { 
  fJets   ->Clear();
  fJetBr ->GetEntry(iEvent);
}
void JetLoader::selectJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,double iMetPhi,double iRho) {
  reset(); 
  int lCount = 0,lNBTag = 0,lNFwd = 0,lNBTagL = 0,lNBTagM = 0,lNBTagT = 0,lNBTagLdR2 = 0;
  fMinDPhi   = 1000; 
  for  (int i0 = 0; i0 < fJets->GetEntriesFast(); i0++) { 
    TJet *pJet = (TJet*)((*fJets)[i0]);
    if(pJet->csv > 0.89 && fabs(pJet->eta) < 2.5 && pJet->pt  > 15 && passJet04Sel(pJet) && !passVeto(pJet->eta,pJet->phi,0.4,iVetoes)) lNBTag++;
    if(pJet->pt        <  30)                 continue;
    if(passVeto(pJet->eta,pJet->phi,0.4,iVetoes)) continue;
    if(fabs(pJet->eta) > 3.0) lNFwd++; 
    if(!passJetLooseSel(pJet) )  continue;
    fHT += pJet->pt;
    double pDPhi = TMath::Min(fabs(pJet->phi-iMetPhi),2.*TMath::Pi()-fabs(pJet->phi-iMetPhi));
    if(pDPhi < fMinDPhi && lCount < 4) fMinDPhi = pDPhi;
    lCount++;
    if(fabs(pJet->eta) > 2.5) continue;          
    addJet(pJet,fSelJets);
    fGoodJets.push_back(pJet);
    // jet and b-tag multiplicity
    if(fabs(pJet->eta) < 2.5 && pJet->csv > CSVL){
      lNBTagL++;
      TLorentzVector vPJet; vPJet.SetPtEtaPhiM(pJet->pt, pJet->eta, pJet->phi, pJet->mass);
      if(iJets.size()>0) {if(pJet->pt>0 && vPJet.DeltaR(iJets[0])>2) lNBTagLdR2++;}
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
  fillDiJet();
  fillBTag(fGoodJets);
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
void JetLoader::addBTag(std::string iHeader,TTree *iTree,std::string iLabel,std::vector<std::string> &iLabels,int iN,std::vector<float> &iVals) {
  for(int i0 = iN; i0 < iN+int(iLabels.size()); i0++) {
    int iBase =i0*4;
    std::stringstream pVal0,pVal1,pValminus1,pVal2;
    pVal0       << iHeader << "btagw" << iLabel << "0"      << "_" << iLabels[i0 % iLabels.size()]; //res_PUPPIbtagwL0_CENT -- just vary M,T and the others - first the others
    pVal1       << iHeader << "btagw" << iLabel << "1"      << "_" << iLabels[i0 % iLabels.size()]; //res_PUPPIbtagwL1_CENT
    pValminus1  << iHeader << "btagw" << iLabel << "minus1" << "_" << iLabels[i0 % iLabels.size()]; //res_PUPPIbtagwLminus1_CENT
    pVal2       << iHeader << "btagw" << iLabel << "2"      << "_" << iLabels[i0 % iLabels.size()]; //res_PUPPIbtagwL2_CENT
    iTree->Branch(pVal0      .str().c_str(),&iVals[iBase+0],(pVal0      .str()+"/F").c_str());
    iTree->Branch(pVal1      .str().c_str(),&iVals[iBase+1],(pVal1      .str()+"/F").c_str());
    iTree->Branch(pValminus1 .str().c_str(),&iVals[iBase+2],(pValminus1 .str()+"/F").c_str());
    iTree->Branch(pVal2      .str().c_str(),&iVals[iBase+3],(pVal2      .str()+"/F").c_str());
    iBase++;
  }
}
void JetLoader::fillBTag(std::vector<const TJet*> iObjects) {
  // CENT (), MISTAG(Ms), BTAG(Bs)  - 5 - CENT(vSFL.at(0)),MsUP(vSFL.at(1)),MsDO(vSFL.at(2)),BsUP(vSFL.at(3)),BsDO(vSFL.at(4))
  for(unsigned int j0=0; j0<3; j0++){
    int iN = j0*20;
    std::vector<std::vector<float>> vSFL,vSFL_nominal;
    for(auto iftype :flavorTypes) {vSFL_nominal.push_back(getJetSFs(iftype,iObjects, freaders[j0].at(0), freaders[j0].at(3)));} // 0 and 3 HF and LF respectively - flavor types:nominal,Ms,Bs
    vSFL.push_back(vSFL_nominal.at(0));
    for(unsigned int i0=1; i0<3; i0++){
      std::vector<float> vSF0,vSF1;
      for(unsigned int i1=0; i1<(vSFL.at(0)).size(); i1++) {
	vSF0.push_back((getJetSFs("Ms",iObjects, freaders[j0].at(i0), freaders[j0].at(i0+3))).at(i1) * (vSFL_nominal.at(2).at(i1)));
	vSF1.push_back((getJetSFs("Bs",iObjects, freaders[j0].at(i0), freaders[j0].at(i0+3))).at(i1) * (vSFL_nominal.at(1).at(i1)));
      }
      vSFL.push_back(vSF0); vSFL.push_back(vSF1);
    }
    for(unsigned int j1=0; j1<5; j1++){
      int lBase = j1*4+iN;
      fBTagVars[lBase+0] = getBtagEventReweight(0,  iObjects, vSFL.at(j1));
      fBTagVars[lBase+1] = getBtagEventReweight(1,  iObjects, vSFL.at(j1));
      fBTagVars[lBase+2] = getBtagEventReweight(-1, iObjects, vSFL.at(j1));
      fBTagVars[lBase+3] = getBtagEventReweight(2,  iObjects, vSFL.at(j1));  
    }
  }
}
