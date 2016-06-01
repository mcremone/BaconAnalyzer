#include "TFile.h"
#include "TMatrixD.h"
#include "../include/EvtLoader.hh"
#include <iostream>
#include <sstream>

#include "../include/LeptonTrigUtils.hh"

using namespace baconhep;

EvtLoader::EvtLoader(TTree *iTree,std::string iName,std::string iHLTFile,std::string iPUWeight) { 
  const std::string cmssw_base = getenv("CMSSW_BASE");

  fEvt      = new TEventInfo();
  iTree->SetBranchAddress("Info",       &fEvt);
  fEvtBr    = iTree->GetBranch("Info");
  fTrigger  = new TTrigger(cmssw_base + iHLTFile);
  
  fVertices = new TClonesArray("baconhep::TVertex");
  iTree->SetBranchAddress("PV",       &fVertices);
  fVertexBr     = iTree->GetBranch("PV");
  
  TFile *lFile = new TFile(iPUWeight.c_str()); 
  fPUWeightHist =  (TH1F*) lFile->Get("puWeights");
  fPUWeightHist->SetDirectory(0);
  lFile->Close();
  fSample = (char*) (iName.c_str());
}
EvtLoader::~EvtLoader() { 
  delete  fEvt;
  delete  fEvtBr;
  delete  fVertices;
  delete  fVertexBr;
}
void EvtLoader::reset() { 
  fEvtV         = 0; 
  fRho          = 0; 
  fITrigger     = 0; 
  fEffTrigger   = 0;
  fselectBits   = 0;
  fNVtx         = 0; 
  fNPU          = 0;
  fPUWeight     = 0; 
  fScale        = 1;
  fevtWeight    = 0;
  fkfactor      = 0;
  fkFactor_CENT = 0;
  fEwkCorr_CENT = 0;

  fRenScale_UP  = 0;
  fRenScale_DO  = 0;
  fFacScale_UP  = 0;
  fFacScale_DO  = 0;

  fMet          = 0; 
  fMetPhi       = 0; 
  fPuppEt       = 0; 
  fPuppEtPhi    = 0; 

  fFMet         = 0;
  fFMetPhi      = 0;
  fFPuppEt      = 0;
  fFPuppEtPhi   = 0;
}
void EvtLoader::setupTree(TTree *iTree) {
  reset();
  fTree = iTree;
  fTree->Branch("runNum"          ,&fRun            ,"fRun/i");
  fTree->Branch("lumiSec"         ,&fLumi           ,"fLumi/i");
  fTree->Branch("evtNum"          ,&fEvtV           ,"fEvtV/i");
  fTree->Branch("metfilter"       ,&fMetFilters     ,"fMetFilters/I");
  fTree->Branch("triggerBits"     ,&fITrigger       ,"fITrigger/i");
  fTree->Branch("selectBits"      ,&fselectBits     ,"fselectBits/i");
  fTree->Branch("triggerEff"      ,&fEffTrigger     ,"fEffTrigger/D");

  fTree->Branch("npu"             ,&fNPU            ,"fNPU/i");
  fTree->Branch("npv"             ,&fNVtx           ,"fNVtx/i");
  fTree->Branch("puWeight"        ,&fPUWeight       ,"fPUWeight/F");
  fTree->Branch("scale1fb"        ,&fScale          ,"fScale/F");  
  fTree->Branch("evtWeight"       ,&fevtWeight      ,"fevtWeight/F");
  fTree->Branch("rho"             ,&fRho            ,"fRho/F");
  fTree->Branch("kfactor"         ,&fkfactor        ,"fkfactor/F");

  fTree->Branch("RenScale_UP"     ,&fRenScale_UP    ,"fRenScale_UP/F");
  fTree->Branch("RenScale_DO"     ,&fRenScale_DO    ,"fRenScale_DO/F");
  fTree->Branch("FacScale_UP"     ,&fFacScale_UP    ,"fFacScale_UP/F");
  fTree->Branch("FacScale_DO"     ,&fFacScale_DO    ,"fFacScale_DO/F");

  fTree->Branch("pfmet"           ,&fMet            ,"fMet/F");
  fTree->Branch("pfmetphi"        ,&fMetPhi         ,"fMetPhi/F");
  fTree->Branch("puppet"          ,&fPuppEt         ,"fPuppEt/F");
  fTree->Branch("puppetphi"       ,&fPuppEtPhi      ,"fPuppEtPhi/F");

  fTree->Branch("fakepfmet"       ,&fFMet           ,"fFMet/F");
  fTree->Branch("fakepfmetphi"    ,&fFMetPhi        ,"fFMetPhi/F");
  fTree->Branch("fakepuppet"      ,&fFPuppEt        ,"fFPuppEt/F");
  fTree->Branch("fakepuppetphi"   ,&fFPuppEtPhi     ,"fFPuppEtPhi/F");

  fRun   = 0;
  fLumi  = 0;
}
void EvtLoader::load(int iEvent) { 
  fVertices ->Clear();
  fEvtBr    ->GetEntry(iEvent);
  fVertexBr ->GetEntry(iEvent);
  fRun   = fEvt->runNum;
  fLumi  = fEvt->lumiSec;
}
bool EvtLoader::passTrigger(std::string iTrigger) {
  return fTrigger->pass(iTrigger,fEvt->triggerBits);
}
bool EvtLoader::passSkim() { 
  bool lMet    = fMet > 80;
  bool lFilter = fMetFilters % 2 == 0; 
  return (lMet && lFilter); 
}
void EvtLoader::fillEvent(unsigned int trigBit,float lWeight) { 
  reset();
  fRun          = fEvt->runNum;
  fLumi         = fEvt->lumiSec;
  fNPU          = fEvt->nPUmean;
  fNVtx         = nVtx();
  fITrigger     = trigBit;
  fselectBits   = 1;
  fPUWeight     = puWeight(float(fNVtx)); 
  fScale        = lWeight;
  fevtWeight    = 1;
  fMetFilters   = fEvt->metFilterFailBits;
  fEvtV         = fEvt->evtNum;
  fRho          = fEvt->rhoIso;
  fkfactor      = 1;
  fMet          = fEvt->pfMETC;
  fMetPhi       = fEvt->pfMETCphi;
  fPuppEt       = fEvt->puppETC;
  fPuppEtPhi    = fEvt->puppETCphi;
  return;
}
// Fake MET
void  EvtLoader::fillModifiedMet(std::vector<TLorentzVector> &iVecCorr,std::vector<TLorentzVector> iPhotons) { 
  if(iVecCorr.size() > 0){
    TLorentzVector lCorr0;
    for(unsigned int i0 =0; i0 < iVecCorr.size(); i0++) lCorr0 += iVecCorr[i0];
    fFMet         = fEvt->pfMETC;
    fFMetPhi      = fEvt->pfMETCphi;
    fFPuppEt      = fEvt->puppETC;
    fFPuppEtPhi   = fEvt->puppETCphi;
    correctMet(fFPuppEt     ,fFPuppEtPhi,     lCorr0);
    correctMet(fFMet        ,fFMetPhi,        lCorr0);
  }
  if(iPhotons.size() > 0){
    fFMet         = fEvt->pfMETC;
    fFMetPhi      = fEvt->pfMETCphi;
    fFPuppEt      = fEvt->puppETC;
    fFPuppEtPhi   = fEvt->puppETCphi;
    correctMet(fFPuppEt     ,fFPuppEtPhi,     iPhotons[0]);
    correctMet(fFMet        ,fFMetPhi,        iPhotons[0]);
  }
}
void  EvtLoader::correctMet(float &iMet,float &iMetPhi,TLorentzVector &iCorr) { 
  TLorentzVector lVec;  lVec.SetPtEtaPhiM(iMet,0,iMetPhi,0);
  //Add back the correction vector
  lVec += iCorr;
  iMet    = lVec.Pt();
  iMetPhi = lVec.Phi();
}
float EvtLoader::metSig(float iMet,float iMetPhi,float iCov00,float iCov01,float iCov10,float iCov11) { 
  TMatrixD lInv(2,2);
  TLorentzVector lUVec; lUVec.SetPtEtaPhiM(iMet,0,iMetPhi,0);
  lInv(0,0) = iCov00; lInv(1,1) = iCov11; lInv(1,0) = iCov10; lInv(0,1) = iCov01;
  if(lInv.Determinant() != 0) lInv.Invert();
  double lSignificance = TMath::Sqrt(lUVec.Px()*lUVec.Px()*(lInv)(0,0) + 2.*lUVec.Px()*lUVec.Py()*(lInv)(1,0) + lUVec.Py()*lUVec.Py()*(lInv)(1,1));
  return lSignificance;
}
// Met Filter
bool EvtLoader::passFilter() { 
  return (fEvt->metFilterFailBits == 0);
}
// Vtx
unsigned int EvtLoader::nVtx() { 
  unsigned int lNVertex = 0; 
  for(int i0 = 0; i0 < fVertices->GetEntries(); i0++) { 
    TVertex *pVertex = (TVertex*) ((*fVertices)[i0]);
    if(fabs(pVertex->z) > 24) continue;
    if(pVertex->ndof    <  4) continue;
    float pX = pVertex->x;
    float pY = pVertex->y;
    float pRho  = sqrt(pX*pX+pY*pY);
    if(pRho             > 2.) continue;
    lNVertex++;
  }
  return lNVertex;
}
bool EvtLoader::PV(){
  return fEvt->hasGoodPV;
}
// Trigger Efficiency
void EvtLoader::triggerEff(std::vector<TLorentzVector> iElectrons, std::vector<TLorentzVector> iPhotons) {
  fEffTrigger = ((0.975+(fEvt->pfMETC-200)*0.025*0.025)*(fEvt->pfMETC<240)+1*(fEvt->pfMETC>=240));
  if(iElectrons.size() > 0){
    if(fITrigger & 4)                                            fEffTrigger = getEle27TriggerSF(iElectrons[0].Pt(),iElectrons[0].Eta());
    if(!(fITrigger & 4) && (fITrigger & 8))                      fEffTrigger = getEle23TriggerSF(iElectrons[0].Pt(),iElectrons[0].Eta());
    if(!(fITrigger & 4) && !(fITrigger & 8) && (fITrigger & 16)) fEffTrigger = 1;
  }
  if(iPhotons.size()   > 0){
    if(fITrigger & 16)                                           fEffTrigger = 1;
  }
}
// puWeight
float EvtLoader::puWeight(float iNPU) { 
  float lNPVW = Float_t(fPUWeightHist->GetBinContent(fPUWeightHist->FindBin(iNPU)));
  if(iNPU > 30) lNPVW = Float_t(fPUWeightHist->GetBinContent(fPUWeightHist->FindBin(30)));
  if(iNPU <  1) lNPVW = Float_t(fPUWeightHist->GetBinContent(fPUWeightHist->FindBin(0)));
  return lNPVW;
}
// mT
float  EvtLoader::mT(float iMet,float iMetPhi,TLorentzVector &iVec) { 
  float lDPhi = fabs(iMetPhi-iVec.Phi());
  // if(fabs(lDPhi) > TMath::Pi()*2.-lDPhi) lDPhi = TMath::Pi()*2.-lDPhi;
  float lMt = sqrt(2.0*(iVec.Pt()*iMet*(1.0-cos(lDPhi))));
  return lMt;
}
void  EvtLoader::fillmT(float iMet, float iMetPhi,float iFMet, float iFMetPhi, std::vector<TLorentzVector> &lCorr, float &fmT) {
  if(lCorr.size()>0){
    TLorentzVector lVecCorr;
    for(unsigned int i0 =0; i0 < lCorr.size(); i0++) lVecCorr += lCorr[i0];
    fmT = (lVecCorr.Pt()>0) ?  mT(iMet,     iMetPhi,     lVecCorr): -999;
    if(iFMet>0) fmT = (lVecCorr.Pt()>0) ? mT(iFMet,     iFMetPhi,     lVecCorr): -999;
  }
}
void EvtLoader::fillVetoes(std::vector<TLorentzVector> iVetoes,std::vector<TLorentzVector> &lVetoes){
  for(unsigned int i0 = 0; i0 < iVetoes.size(); i0++)   lVetoes.push_back(iVetoes[i0]);
}
// kFactor and EWK
void EvtLoader::computeCorr(float iPt,std::string iHist0,std::string iHist1,std::string iHist2,std::string iNLO,std::string ikfactor){
  std::string isuffix = "";
  if(iNLO.find("G")!=std::string::npos) isuffix ="_G";
  std::stringstream pRUP,pRDO,pFUP,pFDO;
  pRUP << iNLO << "/ren_up" << isuffix;
  pRDO << iNLO << "/ren_down" << isuffix;
  pFUP << iNLO << "/fact_up" << isuffix;
  pFDO << iNLO << "/fact_down" << isuffix;

  TFile *lFile = new TFile(ikfactor.c_str());
  fHist0 =  (TH1F*) lFile->Get(iHist0.c_str()); // NLO
  fHist0->SetDirectory(0);
  fHist1 =  (TH1F*) lFile->Get(iHist1.c_str()); // LO
  fHist1->SetDirectory(0);
  fHist2 =  (TH1F*) lFile->Get(iHist2.c_str()); // EWK
  fHist2->SetDirectory(0);
  fHistRUP = (TH1F*) lFile->Get(pRUP.str().c_str());
  fHistRUP->SetDirectory(0);
  fHistRDO = (TH1F*) lFile->Get(pRDO.str().c_str());
  fHistRDO->SetDirectory(0);
  fHistFUP = (TH1F*) lFile->Get(pFUP.str().c_str());
  fHistFUP->SetDirectory(0);
  fHistFDO = (TH1F*) lFile->Get(pFDO.str().c_str());
  fHistFDO->SetDirectory(0);
  lFile->Close();

  fHist2->Divide(fHist1);
  fHist0->Divide(fHist1);

  fkFactor_CENT = Float_t(fHist0->GetBinContent(fHist0->FindBin(iPt)));
  if(iPt > 700) fkFactor_CENT = Float_t(fHist0->GetBinContent(fHist0->FindBin(700)));
  if(iPt < 100) fkFactor_CENT = Float_t(fHist0->GetBinContent(fHist0->FindBin(100)));
  
  fEwkCorr_CENT = Float_t(fHist2->GetBinContent(fHist2->FindBin(iPt)));
  if(iPt > 700) fEwkCorr_CENT = Float_t(fHist2->GetBinContent(fHist2->FindBin(700)));
  if(iPt < 100) fEwkCorr_CENT = Float_t(fHist2->GetBinContent(fHist2->FindBin(100)));

  fkfactor = fEwkCorr_CENT; //(NLO*ewk/LO)

  fRenScale_UP = Float_t(fHistRUP->GetBinContent(fHistRUP->FindBin(iPt)));
  if(iPt > 700) fRenScale_UP = Float_t(fHistRUP->GetBinContent(fHistRUP->FindBin(700)));
  if(iPt < 100) fRenScale_UP = Float_t(fHistRUP->GetBinContent(fHistRUP->FindBin(100)));
  fRenScale_DO = Float_t(fHistRDO->GetBinContent(fHistRDO->FindBin(iPt)));
  if(iPt > 700) fRenScale_DO = Float_t(fHistRDO->GetBinContent(fHistRDO->FindBin(700)));
  if(iPt < 100) fRenScale_DO = Float_t(fHistRDO->GetBinContent(fHistRDO->FindBin(100)));
  fFacScale_UP = Float_t(fHistFUP->GetBinContent(fHistFUP->FindBin(iPt)));
  if(iPt > 700) fFacScale_UP = Float_t(fHistFUP->GetBinContent(fHistFUP->FindBin(700)));
  if(iPt < 100) fFacScale_UP = Float_t(fHistFUP->GetBinContent(fHistFUP->FindBin(100)));
  fFacScale_DO = Float_t(fHistFDO->GetBinContent(fHistFDO->FindBin(iPt)));
  if(iPt > 700) fFacScale_DO = Float_t(fHistFDO->GetBinContent(fHistFDO->FindBin(700)));
  if(iPt < 100) fFacScale_DO = Float_t(fHistFDO->GetBinContent(fHistFDO->FindBin(100)));

}
