#include "TFile.h"
#include "TMatrixD.h"
#include "../include/EvtLoader.hh"
#include <iostream>

// B-tag calibration and SF headers 
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "BaconSkim/Utils/bin/BTagCalibrationStandalone.h"

using namespace baconhep;

EvtLoader::EvtLoader(TTree *iTree,std::string iName,std::string iHLTFile,std::string iPUWeight,std::string ikFactorsFilename,std::string ieleScaleFactorFilename,std::string imuScaleFactorFilename,std::string btagScaleFactorFilename) { 
  fEvt      = new TEventInfo();
  iTree->SetBranchAddress("Info",       &fEvt);
  fEvtBr    = iTree->GetBranch("Info");
  fTrigger  = new TTrigger(iHLTFile); // iHLTFile with list of triggers 
  
  fVertices = new TClonesArray("baconhep::TVertex");
  iTree->SetBranchAddress("PV",       &fVertices);
  fVertexBr     = iTree->GetBranch("PV");
  
  TFile *lFile = new TFile(iPUWeight.c_str()); // puWgt
  fPUWeightHist =  (TH1F*) lFile->Get("puWeights");
  fPUWeightHist->SetDirectory(0);
  lFile->Close();
  fSample = (char*) (iName.c_str());

  TFile *kFactorFile = new TFile(ikFactorsFilename.c_str()); // kFactors
  gH0 =  (TH1F*) kFactorFile->Get("anlo1/anlo1_nominal");
  gH0->SetDirectory(0);
  gH1 =  (TH1F*) kFactorFile->Get("alo/alo_nominal");
  gH1->SetDirectory(0);
  gH2 =  (TH1F*) kFactorFile->Get("a_ewkcorr/a_ewkcorr");
  gH2->SetDirectory(0);
  zH0 =  (TH1F*) kFactorFile->Get("znlo012/znlo012_nominal");
  zH0->SetDirectory(0);
  zH1 =  (TH1F*) kFactorFile->Get("zlo/zlo_nominal");
  zH1->SetDirectory(0);
  zH2 =  (TH1F*) kFactorFile->Get("z_ewkcorr/z_ewkcorr");
  zH2->SetDirectory(0);
  wH0 =  (TH1F*) kFactorFile->Get("wnlo012/wnlo012_nominal");
  wH0->SetDirectory(0);
  wH1 =  (TH1F*) kFactorFile->Get("wlo/wlo_nominal");
  wH1->SetDirectory(0);
  wH2 =  (TH1F*) kFactorFile->Get("w_ewkcorr/w_ewkcorr");
  wH2->SetDirectory(0);

  kFactorFile->Close();

  TFile *EleSFFile = new TFile(ieleScaleFactorFilename.c_str()); // EleSF 
  hEleVeto =  (TH2D*) EleSFFile->Get("factorized_scalefactors_Veto_ele");
  hEleVeto->SetDirectory(0);
  //hEleLoose =  (TH2D*) EleSFFile->Get("unfactorized_scalefactors_Loose_ele");
  //hEleLoose->SetDirectory(0);
  //hEleMedium =  (TH2D*) EleSFFile->Get("unfactorized_scalefactors_Medium_ele");
  //hEleMedium->SetDirectory(0);
  hEleTight =  (TH2D*) EleSFFile->Get("factorized_scalefactors_Tight_ele");
  hEleTight->SetDirectory(0);
  EleSFFile->Close();

  TFile *MuSFFile = new TFile(imuScaleFactorFilename.c_str()); // MuSF
  hMuLoose =  (TH2D*) MuSFFile->Get("unfactorized_scalefactors_Loose_mu");
  hMuLoose->SetDirectory(0);
  //hMuMedium =  (TH2D*) MuSFFile->Get("unfactorized_scalefactors_Medium_mu");
  //hMuMedium->SetDirectory(0);
  hMuTight =  (TH2D*) MuSFFile->Get("unfactorized_scalefactors_Tight_mu");
  hMuTight->SetDirectory(0);
  MuSFFile->Close();

  gH0->Divide(gH1);
  zH0->Divide(zH1);
  wH0->Divide(wH1);
  //wH2->Multiply(wH0);
  //zH2->Multiply(zH0);                                                                                                                                                   
  //gH2->Multiply(gH0);

  BTagCalibration calib("csvv2",btagScaleFactorFilename);  // btagScaleFactorFilename is the local SF file
  BTagCalibrationReader HFreaderM(&calib, BTagEntry::OP_MEDIUM, "mujets", "central");   // systematics type
  BTagCalibrationReader HFreader_upM(&calib, BTagEntry::OP_MEDIUM, "mujets", "up");     // sys up
  BTagCalibrationReader HFreader_downM(&calib, BTagEntry::OP_MEDIUM, "mujets", "down"); // sys down
  BTagCalibrationReader LFreaderM(&calib, BTagEntry::OP_MEDIUM, "comb", "central");   // systematics type 
  BTagCalibrationReader LFreader_upM(&calib, BTagEntry::OP_MEDIUM, "comb", "up");     // sys up                                                                                                                         
  BTagCalibrationReader LFreader_downM(&calib, BTagEntry::OP_MEDIUM, "comb", "down"); // sys down

  BTagCalibrationReader HFreaderL(&calib, BTagEntry::OP_LOOSE, "mujets", "central");   // systematics type
  BTagCalibrationReader HFreader_upL(&calib, BTagEntry::OP_LOOSE, "mujets", "up");     // sys up
  BTagCalibrationReader HFreader_downL(&calib, BTagEntry::OP_LOOSE, "mujets", "down"); // sys down
  BTagCalibrationReader LFreaderL(&calib, BTagEntry::OP_LOOSE, "comb", "central");   // systematics type
  BTagCalibrationReader LFreader_upL(&calib, BTagEntry::OP_LOOSE, "comb", "up");     // sys up
  BTagCalibrationReader LFreader_downL(&calib, BTagEntry::OP_LOOSE, "comb", "down"); // sys down

  BTagCalibrationReader HFreaderT(&calib, BTagEntry::OP_TIGHT, "mujets", "central");   // systematics type
  BTagCalibrationReader HFreader_upT(&calib, BTagEntry::OP_TIGHT, "mujets", "up");     // sys up 
  BTagCalibrationReader HFreader_downT(&calib, BTagEntry::OP_TIGHT, "mujets", "down"); // sys down
  BTagCalibrationReader LFreaderT(&calib, BTagEntry::OP_TIGHT, "comb", "central");   // systematics type 
  BTagCalibrationReader LFreader_upT(&calib, BTagEntry::OP_TIGHT, "comb", "up");     // sys up
  BTagCalibrationReader LFreader_downT(&calib, BTagEntry::OP_TIGHT, "comb", "down"); // sys down

}
EvtLoader::~EvtLoader() { 
  delete  fEvt;
  delete  fEvtBr;
  delete  fVertices;
  delete  fVertexBr;
}
void EvtLoader::reset() { 
  fRun       = 0;
  fEvtV      = 0; 
  fLumi      = 0; 
  fRho       = 0; 
  fITrigger  = 0; 
  fEffTrigger= 0;
  fHLTMatch  = 0; 
  fNVtx      = 0; 
  fNPU       = 0;
  fNPUP      = 0;
  fNPUM      = 0;
  fPUWeight  = 0; 
  
  fMet       = 0; 
  fMetPhi    = 0; 
  fMetSig    = 0;

  fMetRaw    = 0; 
  fMetRawPhi = 0; 
  fTKMet     = 0; 
  fTKMetPhi  = 0; 

  fMVAMet    = 0; 
  fMVAMetPhi = 0; 
  fMVAMetSig = 0;
  
  fPuppEt    = 0; 
  fPuppEtPhi = 0; 

  fRMet       = 0; 
  fRMetPhi    = 0; 
  fRMetRaw    = 0; 
  fRMetRawPhi = 0; 
  fRTKMet     = 0; 
  fRTKMetPhi  = 0; 
  fRMVAMet    = 0; 
  fRMVAMetPhi = 0; 
  fRPuppEt    = 0; 
  fRPuppEtPhi = 0; 

  fMt        = 0;
  fRawMt     = 0;
  fTKMt      = 0;
  fMVAMt     = 0;
  fPuppEtMt  = 0;
}
void EvtLoader::setupTree(TTree *iTree,float iWeight,bool iCondense) {  //iCondense is True if not stated otherwise
  reset();
  fTree = iTree;
  if(iCondense) fTree->Branch("sample"        ,fSample         ,"fSample/C",1024);
  fTree->Branch("runNum"        ,&fRun           ,"fRun/i");
  fTree->Branch("lumiSec"       ,&fLumi          ,"fLumi/i");
  fTree->Branch("evtNum"        ,&fEvtV          ,"fEvtV/i");
  fTree->Branch("triggerBits"   ,&fITrigger      ,"fITrigger/i");
  //METFilters?
  //fTree->Branch("metfilter"     ,&fMetFilter     ,"fMetFilter/i");
  //selectBits?
  //fTree->Branch("selectBits"   ,&fSelTrigger    ,"fSelTrigger/i");
  fTree->Branch("triggerEff"    ,&fEffTrigger    ,"triggerEff/F");
  fTree->Branch("hltmatch"      ,&fHLTMatch      ,"fHLTMatch/i"); //selectBits?

  //fTree->Branch("nloKfactor_CENT",  &nloKfactor_CENT,  "nloKfactor_CENT/F");
  //fTree->Branch("ewkCorr_CENT",  &ewkCorr_CENT,  "ewkCorr_CENT/F");
  //fTree->Branch("lepWeight",  &lepWeight,  "lepWeight/F");
  //fTree->Branch("topSize",&topSize,"topSize/F");

  fTree->Branch("puWeight"      ,&fPUWeight      ,"fPUWeight/F");
  fTree->Branch("npu"           ,&fNPU           ,"fNPU/i");
  fTree->Branch("npuPlusOne"    ,&fNPUP          ,"fNPUP/i");
  fTree->Branch("npuMinusOne"   ,&fNPUM          ,"fNPUM/i");
  fTree->Branch("nvtx"          ,&fNVtx          ,"fNVtx/i");
  fTree->Branch("metFiltersWord",&fMetFilters    , "fMetFilters/I");
  fTree->Branch("scale1fb"      ,&fScale         ,"fScale/F");  
  fTree->Branch("rho"           ,&fRho           ,"fRho/F");
  //fTree->Branch("sumet"         ,&fRawSumEt      ,"fRawSumEt/F");

  if(iCondense) fTree->Branch("metRaw"        ,&fMetRaw        ,"fMetRaw/F");
  if(iCondense) fTree->Branch("metRawPhi"     ,&fMetRawPhi     ,"fMetRawPhi/F");
  fTree->Branch("met"           ,&fMet           ,"fMet/F");
  fTree->Branch("metphi"        ,&fMetPhi        ,"fMetPhi/F");
  if(iCondense) fTree->Branch("tkmet"         ,&fTKMet         ,"fTKMet/F");
  if(iCondense) fTree->Branch("tkmetphi"      ,&fTKMetPhi      ,"fTKMetPhi/F");
  if(iCondense) fTree->Branch("mvamet"        ,&fMVAMet        ,"fMVAMet/F");
  if(iCondense) fTree->Branch("mvametphi"     ,&fMVAMetPhi     ,"fMVAMetPhi/F");
  fTree->Branch("puppet"        ,&fPuppEt        ,"fPuppEt/F");
  fTree->Branch("puppetphi"     ,&fPuppEtPhi     ,"fPuppEtPhi/F");

  if(iCondense) fTree->Branch("cmetRaw"        ,&fRMetRaw        ,"fRMetRaw/F");
  if(iCondense) fTree->Branch("cmetRawPhi"     ,&fRMetRawPhi     ,"fRMetRawPhi/F");
  if(iCondense) fTree->Branch("cmet"           ,&fRMet           ,"fRMet/F");
  if(iCondense) fTree->Branch("cmetphi"        ,&fRMetPhi        ,"fRMetPhi/F");
  if(iCondense) fTree->Branch("ctkmet"         ,&fRTKMet         ,"fRTKMet/F");
  if(iCondense) fTree->Branch("ctkmetphi"      ,&fRTKMetPhi      ,"fRTKMetPhi/F");
  if(iCondense) fTree->Branch("cmvamet"        ,&fRMVAMet        ,"fRMVAMet/F");
  if(iCondense) fTree->Branch("cmvametphi"     ,&fRMVAMetPhi     ,"fRMVAMetPhi/F");
  if(iCondense) fTree->Branch("cpuppet"        ,&fRPuppEt        ,"fRPuppEt/F");
  if(iCondense) fTree->Branch("cpuppetphi"     ,&fRPuppEtPhi     ,"fRPuppEtPhi/F");

  if(iCondense) fTree->Branch("mt"             ,&fMt            ,"fMt/F");
  if(iCondense) fTree->Branch("rawmt"          ,&fRawMt         ,"fRawMt/F");
  if(iCondense) fTree->Branch("tkmt"           ,&fTKMt          ,"fTKMt/F");
  if(iCondense) fTree->Branch("mvamt"          ,&fMVAMt         ,"fMVAMt/F");
  if(iCondense) fTree->Branch("puppetmt"       ,&fPuppEtMt      ,"fPuppEt/F");
  if(iCondense) fTree->Branch("metSig"        ,&fMetSig        ,"fMetSig/F");
  if(iCondense) fTree->Branch("mvaMetSig"     ,&fMVAMetSig     ,"fMVAMetSig/F");
  fScale = iWeight;
}
void EvtLoader::load(int iEvent) { 
  fVertices ->Clear();
  fEvtBr    ->GetEntry(iEvent);
  fVertexBr ->GetEntry(iEvent);
}
void EvtLoader::addTrigger(std::string iName) { 
  fTrigString.push_back(iName);
}
bool EvtLoader::passTrigger() {
  bool lPass = false;
  for(unsigned int i0 = 0; i0 < fTrigString.size(); i0++) { 
    if(fTrigger->pass(fTrigString[i0],fEvt->triggerBits)) lPass = true;
  }
  return lPass;
}
bool EvtLoader::passTrigger(std::string iTrigger) { 
  return fTrigger->pass(iTrigger,fEvt->triggerBits);
}
unsigned int EvtLoader::triggerBit(float &pEff) {
  unsigned int lBit = 0;
  unsigned int lId = 0; 
  //unsigned int trigbits=1;
  for(unsigned int i0 = 0; i0 < fTrigString.size(); i0++) { 
    if(fTrigger->pass(fTrigString[i0],fEvt->triggerBits))  lBit |= 1 << lId;
    //if(lOption == 0 || lOption > 1) trigbits= trigbits | 2;
    //if(lOption == 1)      trigbits= trigbits | 4;
    //if(lOption < 0)    trigbits= trigbits | 8;
    //std::cout << "Trig" << fTrigger->pass(fTrigString[i0],fEvt->triggerBits) << std::endl;

    //if(trigbits==1) continue;                                                                                                                                                        
 
    //pEff = ((0.975+(info->pfMETC-200)*0.025*0.025)*(info->pfMETC<240)+1*(info->pfMETC>=240));
    //Electrons
    // if(trigbits & 4) pEff = 0.98*(fabs(vEle.Eta())<1.4442)+0.91*(fabs(vEle.Eta())>1.566);
    // if(!(trigbits & 4) && (trigbits & 8)) pEff = 1;
    // DiEle
    //if(trigbits & 4) pEff = 0.98*(fabs(vEle1.Eta())<1.4442)+0.91*(fabs(vEle1.Eta())>1.566);
    //if(!(trigbits & 4) && (trigbits & 8)) pEff = 1.;
    // Photon
    //if(trigbits & 8) pEff = 1.;

    lId++;
    if(i0 == 0) lId--;
  }
  return lBit;
}
bool EvtLoader::passSkim() { 
  bool lMet    = fMet > 80;
  bool lFilter = fMetFilters % 2 == 0; 
  return (lMet && lFilter); 
}

// trigger efficiency
//float pEff = ((0.975+(fRMet-200)*0.025*0.025)*(fRMet<240)+1*(fRMet>=240)); 
//                                                                                                                                                                                                                            
// MET and fake MET                                                                                                                                                                                                           
//                                                                                                                                                                                                                            
//TLorentzVector vPFMET, vFakePFMET, vPUPPET, vFakePUPPET, vMuo, vMuo1, vMuo2, vEle, vEle1, vEle2;
//vPUPPET.SetPtEtaPhiM(info->puppETC,0,info->puppETCphi,0);
//vPFMET.SetPtEtaPhiM(info->pfMETC,0,info->pfMETCphi,0);
//vFakePUPPET.SetPtEtaPhiM(0,0,0,0);
//vFakePFMET.SetPtEtaPhiM(0,0,0,0);

void EvtLoader::fillEvent() { 
  reset();

  //
  // Primary vertex requirement
  //
  //if(!(fEvt->hasGoodPV)) continue;
 
  float pEff = 1;
  //fSample     = iSample;
  fNPU        = fEvt->nPUmean;
  fNPUM       = fEvt->nPUmeanm;
  fNPUP       = fEvt->nPUmeanp;
  fNVtx       = nVtx();
  fITrigger   = triggerBit(pEff);
  fEffTrigger = pEff;
  fPUWeight   = puWeight(float(fNVtx)); 
  fMetFilters = metFilter(fEvt->metFilterFailBits);
  fRun        = fEvt->runNum;
  fLumi       = fEvt->lumiSec;
  fEvtV       = fEvt->evtNum;
  fRho        = fEvt->rhoJet;
  //fRawSumEt   = fEvt->pfSumET;
  fMet        = fEvt->pfMETC;
  fMetPhi     = fEvt->pfMETCphi;
  fMetRaw     = fEvt->pfMET;
  fMetRawPhi  = fEvt->pfMETphi;
  //fMetSig     = metSig(fMet,fMetPhi,fEvt->pfMETCov00,fEvt->pfMETCov01,fEvt->pfMETCov01,fEvt->pfMETCov11);

  fTKMet      = fEvt->trkMET;
  fTKMetPhi   = fEvt->trkMETphi;
  fMVAMet     = fEvt->mvaMET30;
  fMVAMetPhi  = fEvt->mvaMET30phi;
  //fMVAMetSig   = metSig(fMVAMet,fMVAMetPhi,fEvt->mvaMETCov00,fEvt->mvaMETCov01,fEvt->mvaMETCov01,fEvt->mvaMETCov11);
  fPuppEt      = fEvt->puppETC30;
  fPuppEtPhi   = fEvt->puppETC30phi;

  fRMet        = fEvt->pfMETC;
  fRMetPhi     = fEvt->pfMETCphi;
  fRMetRaw     = fEvt->pfMET;
  fRMetRawPhi  = fEvt->pfMETphi;
  //fMetSig     = metSig(fMet,fMetPhi,fEvt->pfMETCov00,fEvt->pfMETCov01,fEvt->pfMETCov01,fEvt->pfMETCov11);

  fRTKMet      = fEvt->trkMET;
  fRTKMetPhi   = fEvt->trkMETphi;
  fRMVAMet     = fEvt->mvaMET30;
  fRMVAMetPhi  = fEvt->mvaMET30phi;
  //fMVAMetSig   = metSig(fMVAMet,fMVAMetPhi,fEvt->mvaMETCov00,fEvt->mvaMETCov01,fEvt->mvaMETCov01,fEvt->mvaMETCov11);
  fRPuppEt      = fEvt->puppETC30;
  fRPuppEtPhi   = fEvt->puppETC30phi;

  return;
}
void  EvtLoader::fillModifiedMet(std::vector<TLorentzVector> &iVecCorr) { 
  TLorentzVector lCorr(0,0,0,0);
  for(unsigned int i0 =0; i0 < iVecCorr.size(); i0++) { 
    TLorentzVector pVec; pVec.SetPtEtaPhiM(iVecCorr[i0].Pt(),0,iVecCorr[i0].Phi(),0);
    lCorr += pVec;
  }
  fMt                = mT(fMet,        fMetPhi,        lCorr);
  fRawMt             = mT(fMetRaw,     fMetRawPhi,     lCorr);
  fTKMt              = mT(fTKMet,      fTKMetPhi,      lCorr);
  fMVAMt             = mT(fMVAMet,     fMVAMetPhi,     lCorr);
  fPuppEtMt          = mT(fPuppEt,     fPuppEtPhi,     lCorr);

  //Apply Corrections to the MET 
  if(iVecCorr.size() > 0) { 
    correctMet(fMet        ,fMetPhi,        lCorr);
    correctMet(fMetRaw     ,fMetRawPhi,     lCorr);
    correctMet(fTKMet      ,fTKMetPhi,      lCorr);
    correctMet(fMVAMet     ,fMVAMetPhi,     lCorr);
    correctMet(fPuppEt     ,fPuppEtPhi,     lCorr);
    //fMetSig               = metSig(fMet,fMetPhi,fEvt->pfMETCov00,fEvt->pfMETCov01,fEvt->pfMETCov01,fEvt->pfMETCov11);
    //fMVAMetSig            = metSig(fMVAMet,fMVAMetPhi,fEvt->mvaMETCov00,fEvt->mvaMETCov01,fEvt->mvaMETCov01,fEvt->mvaMETCov11);
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
float EvtLoader::puWeight(float iNPU) { 
  //double puWgt = hPUWeights->GetBinContent(hPUWeights->FindBin(info->nPUmean))
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
