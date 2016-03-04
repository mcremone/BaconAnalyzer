#include "TFile.h"
#include "TMatrixD.h"
#include "../include/EvtLoader.hh"
#include <iostream>

using namespace baconhep;

EvtLoader::EvtLoader(TTree *iTree,std::string iName,std::string iHLTFile,std::string iPUWeight) { 
  const std::string cmssw_base = getenv("CMSSW_BASE");

  fEvt      = new TEventInfo();
  iTree->SetBranchAddress("Info",       &fEvt);
  fEvtBr    = iTree->GetBranch("Info");
  fTrigger  = new TTrigger(cmssw_base + iHLTFile); // iHLTFile with list of triggers 
  
  fVertices = new TClonesArray("baconhep::TVertex");
  iTree->SetBranchAddress("PV",       &fVertices);
  fVertexBr     = iTree->GetBranch("PV");
  
  TFile *lFile = new TFile(iPUWeight.c_str()); // puWgt
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
  fRun          = 0;
  fEvtV         = 0; 
  fLumi         = 0; 
  fRho          = 0; 
  fITrigger     = 0; 
  fEffTrigger   = 0;
  fselectBits   = 0;
  fNVtx         = 0; 
  fNPU          = 0;
  fPUWeight     = 0; 
  fevtWeight    = 0;

  fKfactor_CENT = 0;
  fEwkCorr_CENT = 0;
  fLepWeight    = 0;

  fMet          = 0; 
  fMetPhi       = 0; 
  fPuppEt       = 0; 
  fPuppEtPhi    = 0; 

  fFMet         = 0;
  fFMetPhi      = 0;
  fFPuppEt      = 0;
  fFPuppEtPhi   = 0;
}
void EvtLoader::setupTree(TTree *iTree,float iWeight) {
  reset();
  fTree = iTree;
  fTree->Branch("runNum"          ,&fRun            ,"fRun/i");
  fTree->Branch("lumiSec"         ,&fLumi           ,"fLumi/i");
  fTree->Branch("evtNum"          ,&fEvtV           ,"fEvtV/i");
  fTree->Branch("metfilter"       ,&fMetFilters     ,"fMetFilters/I");
  fTree->Branch("triggerBits"     ,&fITrigger       ,"fITrigger/i");
  fTree->Branch("selectBits"      ,&fselectBits     ,"fselectBits/i");
  fTree->Branch("triggerEff"      ,&fEffTrigger     ,"fEffTrigger/F");

  fTree->Branch("npu"             ,&fNPU            ,"fNPU/i");
  fTree->Branch("npv"             ,&fNVtx           ,"fNVtx/i");
  fTree->Branch("puWeight"        ,&fPUWeight       ,"fPUWeight/F");
  fTree->Branch("scale1fb"        ,&fScale          ,"fScale/F");  
  fTree->Branch("evtWeight"       ,&fevtWeight      ,"fevtWeight/F");
  fTree->Branch("rho"             ,&fRho            ,"fRho/F");

  fTree->Branch("nloKfactor_CENT" ,&fKfactor_CENT   ,"fKfactor_CENT/F");
  fTree->Branch("ewkCorr_CENT"    ,&fEwkCorr_CENT   ,"fEwkCorr_CENT/F");
  fTree->Branch("lepWeight"       ,&fLepWeight      ,"fLepWeight/F");

  fTree->Branch("pfmet"           ,&fMet            ,"fMet/F");
  fTree->Branch("pfmetphi"        ,&fMetPhi         ,"fMetPhi/F");
  fTree->Branch("puppet"          ,&fPuppEt         ,"fPuppEt/F");
  fTree->Branch("puppetphi"       ,&fPuppEtPhi      ,"fPuppEtPhi/F");

  fTree->Branch("fakepfmet"       ,&fFMet           ,"fFMet/F");
  fTree->Branch("fakepfmetphi"    ,&fFMetPhi        ,"fFMetPhi/F");
  fTree->Branch("fakepuppet"      ,&fFPuppEt        ,"fFPuppEt/F");
  fTree->Branch("fakepuppetphi"   ,&fFPuppEtPhi     ,"fFPuppEtPhi/F");
  fScale = iWeight;
}
void EvtLoader::load(int iEvent) { 
  fVertices ->Clear();
  fEvtBr    ->GetEntry(iEvent);
  fVertexBr ->GetEntry(iEvent);
}
bool EvtLoader::passTrigger(std::string iTrigger) {
  return fTrigger->pass(iTrigger,fEvt->triggerBits);
}
bool EvtLoader::passSkim() { 
  bool lMet    = fMet > 80;
  bool lFilter = fMetFilters % 2 == 0; 
  return (lMet && lFilter); 
}
void EvtLoader::fillEvent(unsigned int trigBit) { 
  reset();
  fNPU        = fEvt->nPUmean;
  fNVtx       = nVtx();
  fITrigger   = trigBit;
  fEffTrigger = pEff();
  fPUWeight   = puWeight(float(fNVtx)); 
  fevtWeight  = 1;
  fMetFilters = fEvt->metFilterFailBits;
  fRun        = fEvt->runNum;
  fLumi       = fEvt->lumiSec;
  fEvtV       = fEvt->evtNum;
  fRho        = fEvt->rhoIso;
  fMet        = fEvt->pfMETC;
  fMetPhi     = fEvt->pfMETCphi;
  fPuppEt      = fEvt->puppETC;
  fPuppEtPhi   = fEvt->puppETCphi;
  return;
}
// Fake MET
void  EvtLoader::fillModifiedMet(std::vector<TLorentzVector> &iVecCorr,std::vector<TLorentzVector> iPhotons) { 
  TLorentzVector lCorr;
  if(iVecCorr.size() > 0){
    for(unsigned int i0 =0; i0 < iVecCorr.size(); i0++) lCorr += iVecCorr[i0];
    fFMet        = fEvt->pfMETC;
    fFMetPhi     = fEvt->pfMETCphi;
    fFPuppEt      = fEvt->puppETC;
    fFPuppEtPhi   = fEvt->puppETCphi;
    correctMet(fFPuppEt     ,fFPuppEtPhi,     lCorr);
    correctMet(fFMet        ,fFMetPhi,        lCorr);
  }
  if(iPhotons.size() > 0){
    fFMet        = fEvt->pfMETC;
    fFMetPhi     = fEvt->pfMETCphi;
    fFPuppEt      = fEvt->puppETC;
    fFPuppEtPhi   = fEvt->puppETCphi;
    lCorr = iPhotons[0];
    correctMet(fFMet        ,fFMetPhi,        lCorr);
  }
  // check this
  //fMt                = mT(fFMet,        fFMetPhi,        lCorr);
  //fPuppEtMt          = mT(fFPuppEt,     fFPuppEtPhi,     lCorr);

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
//Met Filter
bool EvtLoader::passFilter() { 
  return (fEvt->metFilterFailBits == 0);
}
unsigned int EvtLoader::metFilter(unsigned int iMetFilter) { 
  unsigned int lWord = 0; 
  //Mapping of filters form Bacon to Bambu 
  lWord |=  (iMetFilter &  1)   << 0; //HBHE Noise
  lWord |=  (iMetFilter &  8)   << 1; //Ecal Dead Cell
  //lWord |=  (iMetFilter & 16)   << 2; //Tracking Failure
  lWord |=  (iMetFilter & 32)   << 3; //EEBadSc
  //lWord |=  (iMetFilter & 64)   << 4; //EcalLaser
  //lWord |=  (iMetFilter & 128)  << 5; //tkManyStrip
  //lWord |=  (iMetFilter & 256)  << 6; //tktooManyStrip
  //lWord |=  (iMetFilter & 512)  << 7; //tkLogError
  lWord |=  (iMetFilter & 2)    << 2; //CSCTight
  //CSCLoose Halo Filter missing from our bitset
  //lWord |=  (iMetFilter & 4)    << 10; //Hcal Laser
  return lWord;
}
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
float EvtLoader::pEff() {
  float lTriggerEff = ((0.975+(fEvt->pfMETC-200)*0.025*0.025)*(fEvt->pfMETC<240)+1*(fEvt->pfMETC>=240));
  return lTriggerEff;
}
float EvtLoader::puWeight(float iNPU) { 
  float lNPVW = Float_t(fPUWeightHist->GetBinContent(fPUWeightHist->FindBin(iNPU)));
  if(iNPU > 30) lNPVW = Float_t(fPUWeightHist->GetBinContent(fPUWeightHist->FindBin(30)));
  if(iNPU <  1) lNPVW = Float_t(fPUWeightHist->GetBinContent(fPUWeightHist->FindBin(0)));
  return lNPVW;
}
float  EvtLoader::mT(float &iMet,float &iMetPhi,TLorentzVector &iVec) { 
  float lDPhi = fabs(iMetPhi-iVec.Phi());
  if(fabs(lDPhi) > TMath::Pi()*2.-lDPhi) lDPhi = TMath::Pi()*2.-lDPhi;
  float lMt = sqrt(2.0*(iVec.Pt()*iMet*(1.0-cos(lDPhi))));
  return lMt;
}
void EvtLoader::fillVetoes(std::vector<TLorentzVector> iVetoes,std::vector<TLorentzVector> &lVetoes){
  for(unsigned int i0 = 0; i0 < iVetoes.size(); i0++)   lVetoes.push_back(iVetoes[i0]);
}
