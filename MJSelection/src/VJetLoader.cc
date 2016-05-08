#include "../include/VJetLoader.hh"
#include <cmath>
#include <iostream> 

#include <string>
#include <sstream>

using namespace baconhep;

VJetLoader::VJetLoader(TTree *iTree,std::string iJet,std::string iAddJet,int iN, std::string subjetbtagScaleFactorFilename) { 
  fVJets         = new TClonesArray("baconhep::TJet");
  // fFatJets       = new TClonesArray("baconhep::TJet");
  fVAddJets      = new TClonesArray("baconhep::TAddJet");

  iTree->SetBranchAddress(iJet.c_str(),       &fVJets);
  iTree->SetBranchAddress(iAddJet.c_str(),    &fVAddJets);
  fVJetBr        = iTree->GetBranch(iJet.c_str());
  fVAddJetBr     = iTree->GetBranch(iAddJet.c_str());

  // iTree->SetBranchAddress(iJet.c_str(),      &fFatJets);
  // fFatJetBr      = iTree->GetBranch(iJet.c_str());

  fN = iN;

  fSubJetCalib = new BTagCalibration("csvv2",subjetbtagScaleFactorFilename);
  fSubJetreadersL.clear(); fSubJetreadersM.clear();
  fSubJetreaders.clear();
  for(auto imtype : measurementTypes) { // fSubJetreadersL 6, M6 
    for(auto ivtype : variationTypes) {
      fSubJetreadersL.push_back(new BTagCalibrationReader(fSubJetCalib, BTagEntry::OP_LOOSE,  imtype, ivtype)); // first lt(HF) then incl(LF) and first central(0,3) then up(1,4) and then down(2,5)
      fSubJetreadersM.push_back(new BTagCalibrationReader(fSubJetCalib, BTagEntry::OP_MEDIUM, imtype, ivtype));
    }
  }
  fSubJetreaders.push_back(fSubJetreadersL); fSubJetreaders.push_back(fSubJetreadersM);

}
VJetLoader::~VJetLoader() { 
  //delete fVJets;
  //delete fVJetBr;
  //delete fVAddJets;
  //delete fVAddJetBr;
  // delete fFatJets;
  // delete fFatJetBr;
}
void VJetLoader::resetSubJetBTag() {
  for(unsigned int i0 = 0; i0 < fSubJetBTagVars.size(); i0++) fSubJetBTagVars[i0] = 1;
}
void VJetLoader::reset() { 
  fNVJets        = 0; 
  fVMT           = 0;
  ftopSize       = 999;
  ftopMatching   = 999;
  fisHadronicTop = 0;
  fSelVJets.clear();
  fGoodVSubJets.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  resetSubJetBTag();
}
void VJetLoader::setupTree(TTree *iTree, std::string iJetLabel) { 
  reset();
  fLabels.clear();
  fLabels.push_back("mass");
  fLabels.push_back("csv");
  fLabels.push_back("CHF");
  fLabels.push_back("NHF");
  fLabels.push_back("NEMF");
  fLabels.push_back("tau21");
  fLabels.push_back("tau32");
  fLabels.push_back("msd");
  fLabels.push_back("ddt");
  fLabels.push_back("rho");
  fLabels.push_back("phil");
  fLabels.push_back("minsubcsv");
  fLabels.push_back("maxsubcsv");
  fLabels.push_back("doublecsv");
  fLabels.push_back("fatjetcsv");

  std::stringstream pSMT;   pSMT << iJetLabel << "0_mT";
  std::stringstream pSNJ;   pSNJ << iJetLabel << "s";
  std::stringstream pSis;   pSis << iJetLabel << "0_isHadronicTop";
  std::stringstream pSTM;   pSTM << iJetLabel << "0_topMatching";
  std::stringstream pSTS;   pSTS << iJetLabel << "0_topSize";

  fTree = iTree;
  for(int i0 = 0; i0 < fN*4.;                    i0++) {double pVar = 0; fVars.push_back(pVar);} // declare array of vars
  for(int i0 = 0; i0 < fN*(int(fLabels.size())); i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars);                                                 // from MonoXUtils.cc => fN =1 *_pt,*_eta,*_phi for vjet0 (3*1=3)
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars,fN*3,fLabels);
  fTree->Branch(pSNJ.str().c_str() ,&fNVJets        ,(pSNJ.str()+"/I").c_str());
  fTree->Branch(pSMT.str().c_str() ,&fVMT           ,(pSMT.str()+"/F").c_str());
  fTree->Branch(pSis.str().c_str() ,&fisHadronicTop ,(pSis.str()+"/I").c_str());
  fTree->Branch(pSTM.str().c_str() ,&ftopMatching   ,(pSTM.str()+"/D").c_str());
  fTree->Branch(pSTS.str().c_str() ,&ftopSize       ,(pSTS.str()+"/D").c_str());
}
void VJetLoader::setupTreeSubJetBTag(TTree *iTree, std::string iJetLabel) {
  resetSubJetBTag();
  fTree = iTree;
  for(int i0 = 0; i0 < 40; i0++) {float pBTagVar = 1; fSubJetBTagVars.push_back(pBTagVar);} // declare array of 40 vars ( L0,L1,Lminus1,L2, M0,M1,Mminus1,M2) for (CENT,MISTAGUP,MISTAGDO,BTAGUP,BTAGDO)
  int i1 = 0;
  for(auto iwptype : wpTypes) {
    addSubJetBTag(iJetLabel.c_str(),iTree,iwptype,fBtagLabels,i1,fSubJetBTagVars);
    i1 += 20;
  }
}
void VJetLoader::load(int iEvent) { 
  fVJets       ->Clear();
  fVJetBr      ->GetEntry(iEvent);
  fVAddJets    ->Clear();
  fVAddJetBr   ->GetEntry(iEvent);
  // fFatJets     ->Clear();
  // fFatJetBr    ->GetEntry(iEvent);
}
void VJetLoader::selectVJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,std::vector<TLorentzVector> &iVJet, double dR, std::string iJetID){
  reset(); 
  iJets.clear(); iVJet.clear();
  int lCount = 0; 
  for  (int i0 = 0; i0 < fVJets->GetEntriesFast(); i0++) { 
    TJet *pVJet = (TJet*)((*fVJets)[i0]);
    if(pVJet->pt        <=  200)                                           continue;
    if(fabs(pVJet->eta) >=  2.4)                                           continue;
    if(passVeto(pVJet->eta,pVJet->phi,dR,iVetoes))                         continue;
    if(!passJetLooseSel(pVJet))                                            continue;
    if(iJetID.compare("tightJetID")==0 && !passJetTightLepVetoSel(pVJet))  continue;
    addVJet(pVJet,iJets,pVJet->mass);
    addJet(pVJet,fSelVJets);
    lCount++;
  }
  if(iJets.size() > 0){
    TLorentzVector ivJ; ivJ.SetPtEtaPhiM(fSelVJets[0]->pt,fSelVJets[0]->eta,fSelVJets[0]->phi,fSelVJets[0]->mass);
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
    iVals[lBase+i0*lNLabel+8]  = ddt(pAddJet->tau1,pAddJet->tau2,pAddJet->mass_sd0,iObjects[i0]->pt);
    iVals[lBase+i0*lNLabel+9]  = log((pAddJet->mass_sd0*pAddJet->mass_sd0)/iObjects[i0]->pt);
    iVals[lBase+i0*lNLabel+10] = pAddJet->mass_sd0/log(iObjects[i0]->pt);
    iVals[lBase+i0*lNLabel+11] = TMath::Min(pAddJet->sj1_csv,pAddJet->sj2_csv);
    iVals[lBase+i0*lNLabel+12] = TMath::Max(TMath::Max(pAddJet->sj1_csv,pAddJet->sj2_csv),TMath::Max(pAddJet->sj3_csv,pAddJet->sj4_csv));
    iVals[lBase+i0*lNLabel+13] = pAddJet     ->doublecsv;

    TJet *pLargeJet = getLargeJet(iObjects[i0]); 
    if(pLargeJet != 0) iVals[lBase+i0*lNLabel+14] = pLargeJet->csv;
    // if(pLargeJet != 0) iVals[lBase+i0*lNLabel+14] = pLargeJet->pt - iObjects[i0]->pt;
    // if(pLargeJet != 0) iVals[lBase+i0*lNLabel+15] = pullDot(pLargeJet->pullY,iObjects[i0]->pullY,pLargeJet->pullPhi,iObjects[i0]->pullPhi);
  
    TLorentzVector vSJ1; vSJ1.SetPtEtaPhiM(pAddJet->sj1_pt, pAddJet->sj1_eta, pAddJet->sj1_phi, pAddJet->sj1_m); if(pAddJet->sj1_pt>0) fGoodVSubJets.push_back(vSJ1); 
    TLorentzVector vSJ2; vSJ2.SetPtEtaPhiM(pAddJet->sj2_pt, pAddJet->sj2_eta, pAddJet->sj2_phi, pAddJet->sj2_m); if(pAddJet->sj2_pt>0) fGoodVSubJets.push_back(vSJ2);
    TLorentzVector vSJ3; vSJ3.SetPtEtaPhiM(pAddJet->sj3_pt, pAddJet->sj3_eta, pAddJet->sj3_phi, pAddJet->sj3_m); if(pAddJet->sj3_pt>0) fGoodVSubJets.push_back(vSJ3);
    TLorentzVector vSJ4; vSJ4.SetPtEtaPhiM(pAddJet->sj4_pt, pAddJet->sj4_eta, pAddJet->sj4_phi, pAddJet->sj4_m); if(pAddJet->sj4_pt>0) fGoodVSubJets.push_back(vSJ4);
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
void VJetLoader::addSubJetBTag(std::string iHeader,TTree *iTree,std::string iLabel,std::vector<std::string> &iLabels,int iN,std::vector<float> &iVals) {
  int iBase=iN;
  for(int i0 = 0; i0 < int(iLabels.size()); i0++) {
    std::stringstream pVal0,pVal1,pValminus1,pVal2;
    pVal0       << iHeader << "btagw" << iLabel << "0"      << "_" << iLabels[i0 % iLabels.size()]; //bst15_PUPPIbtagwL0_CENT -- where iLabel(L,M) and iLabels(CENT,MISTAGUP,MISTAGD0,BTAGUP,BTAGD0)
    pVal1       << iHeader << "btagw" << iLabel << "1"      << "_" << iLabels[i0 % iLabels.size()]; //bst15_PUPPIbtagwL1_CENT
    pValminus1  << iHeader << "btagw" << iLabel << "minus1" << "_" << iLabels[i0 % iLabels.size()]; //bst15_PUPPIbtagwLminus1_CENT
    pVal2       << iHeader << "btagw" << iLabel << "2"      << "_" << iLabels[i0 % iLabels.size()]; //bst15_PUPPIbtagwL2_CENT
    iTree->Branch(pVal0      .str().c_str(),&iVals[iBase+0],(pVal0      .str()+"/F").c_str());
    iTree->Branch(pVal1      .str().c_str(),&iVals[iBase+1],(pVal1      .str()+"/F").c_str());
    iTree->Branch(pValminus1 .str().c_str(),&iVals[iBase+2],(pValminus1 .str()+"/F").c_str());
    iTree->Branch(pVal2      .str().c_str(),&iVals[iBase+3],(pVal2      .str()+"/F").c_str());
    iBase+=4;
  }
}
void VJetLoader::fillSubJetBTag(const TClonesArray* iGens, std::vector<TLorentzVector> iObjects) {
  // vSFL should contain CENT (), MISTAG(Ms), BTAG(Bs)  - 5 - CENT(vSFL.at(0)),MsUP(vSFL.at(1)),MsDO(vSFL.at(2)),BsUP(vSFL.at(3)),BsDO(vSFL.at(4))
  int iN = 0;
  for(unsigned int j0=0; j0<2; j0++){  // L, M
    std::vector<std::vector<float>> vSFL,vSFL_nominal;
    vSFL_nominal.clear(); vSFL_nominal.push_back(getSubJetSFs("nominal",iGens,iObjects, fSubJetreaders[j0].at(0), fSubJetreaders[j0].at(3)));
    vSFL.clear(); vSFL.push_back(vSFL_nominal.at(0));

    for(auto iftype :flavorTypes) {
      vSFL_nominal.push_back(getSubJetSFs(iftype,iGens,iObjects, fSubJetreaders[j0].at(0), fSubJetreaders[j0].at(3))); // 0 and 3 HF and LF respectively - flavor types: Ms,Bs
    }

    for(auto iftype :flavorTypes) {
      for(unsigned int i0=1; i0<3; i0++){
	std::vector<float> vSF0; vSF0.clear();
        for(unsigned int i1=0; i1<(vSFL.at(0)).size(); i1++) {
          if(iftype.compare("Ms")==0) vSF0.push_back( (getSubJetSFs(iftype,iGens,iObjects, fSubJetreaders[j0].at(i0), fSubJetreaders[j0].at(i0+3))).at(i1) * (vSFL_nominal.at(2).at(i1)));
          if(iftype.compare("Bs")==0) vSF0.push_back( (getSubJetSFs(iftype,iGens,iObjects, fSubJetreaders[j0].at(i0), fSubJetreaders[j0].at(i0+3))).at(i1) * (vSFL_nominal.at(1).at(i1)));
        }
        vSFL.push_back(vSF0);
      }
    }

    // Fill SubJet btag
    for(unsigned int j1=0; j1<5; j1++){
      int lBase = j1*4+iN;
      fSubJetBTagVars[lBase+0] = getSubJetBtagEventReweight(iGens, 0,  iObjects, vSFL.at(j1));
      fSubJetBTagVars[lBase+1] = getSubJetBtagEventReweight(iGens, 1,  iObjects, vSFL.at(j1));
      fSubJetBTagVars[lBase+2] = getSubJetBtagEventReweight(iGens, -1, iObjects, vSFL.at(j1));
      fSubJetBTagVars[lBase+3] = getSubJetBtagEventReweight(iGens, 2,  iObjects, vSFL.at(j1));
    }
    iN += 20;
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
double VJetLoader::ddt(double iT1,double iT2,double iM,double iPt) {
  double lRho = log(iM*iM/iPt)*0.63;
  double lDDT = iT1/iT2 + lRho;
  return lDDT;
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
  for  (int i0 = 0; i0 < fVJets->GetEntriesFast(); i0++) {
    TJet *pFatJet = (TJet*)((*fVJets)[i0]);
    float pDEta = fabs(pFatJet->eta-iMatch->eta);
    float pDPhi = fabs(pFatJet->phi-iMatch->phi);
    if(pDPhi > 2.*TMath::Pi()-pDPhi) pDPhi =  2.*TMath::Pi()-pDPhi;
    if(sqrt(pDEta*pDEta+pDPhi*pDPhi) > 0.4) continue;
    lFatJet = pFatJet;
    break;
  }
  return lFatJet;
}
