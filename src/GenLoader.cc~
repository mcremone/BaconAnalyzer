#include <iostream>
#include <assert.h>  
#include "../include/GenLoader.hh"

using namespace baconhep;

GenLoader::GenLoader(TTree *iTree) { 
  fGenInfo  = new TGenEventInfo();
  iTree->SetBranchAddress("GenEvtInfo",       &fGenInfo);
  fGenInfoBr  = iTree->GetBranch("GenEvtInfo");

  fGens  = new TClonesArray("baconhep::TGenParticle");
  iTree->SetBranchAddress("GenParticle",       &fGens);
  fGenBr  = iTree->GetBranch("GenParticle");
  fBoson = 0;
}
GenLoader::~GenLoader() { 
  delete fGenInfo;
  delete fGenInfoBr;

  delete fGens;
  delete fGenBr;
}
void GenLoader::reset() { 
  fQ     = 0;
  fPId1  = 0;
  fX1    = 0;
  fPdf1  = 0;
  fPId2  = 0;
  fX2    = 0;
  fPdf2  = 0;

  fVPt   = 0; 
  fVEta  = 0; 
  fVPhi  = 0; 
  fVM    = 0; 
  fVId   = 0; 
  fVIso  = 0;

  fPt1   = 0; 
  fEta1  = 0; 
  fPhi1  = 0; 
  fM1    = 0; 
  fId1   = 0; 

  fPt2   = 0; 
  fEta2  = 0; 
  fPhi2  = 0; 
  fM2    = 0; 
  fId2   = 0; 

  fHPt   = 0; 
  fHEta  = 0; 
  fHPhi  = 0; 
  fHM    = 0; 
  fHId   = 0; 
  
  fHPt1   = 0; 
  fHEta1  = 0; 
  fHPhi1  = 0; 
  fHM1    = 0; 
  fHId1   = 0; 

  fHPt2   = 0; 
  fHEta2  = 0; 
  fHPhi2  = 0; 
  fHM2    = 0; 
  fHId2   = 0; 

  fDPt    = 0; 
  fDEta   = 0; 
  fDPhi   = 0; 
  fDM     = 0; 
  fDId    = 0; 
}
void GenLoader::setupTree(TTree *iTree,float iXSIn) { 
  reset();
  fTree = iTree;
  //fTree->Branch("processId", &processId_ , "processId/I");
  iTree->Branch("mcweight"   ,&fWeight    ,"fWeight/F"); // gen related variables
  iTree->Branch("xs"         ,&fXS        ,"fXS/F");
  iTree->Branch("xsin"         ,&fXSIn        ,"fXSIn/F"); fXSIn = iXSIn;
  fTree->Branch("Q"          ,&fQ   , "fQ/F");
  fTree->Branch("id1"        ,&fPId1, "fPId1/F");
  fTree->Branch("x1"         ,&fX1  , "fX1/F");
  fTree->Branch("pdf1"       ,&fPdf1, "fPdf1/F");
  fTree->Branch("id2"        ,&fPId2, "fPId2/F");
  fTree->Branch("x2"         ,&fX2  , "fX2/F");
  fTree->Branch("pdf2"       ,&fPdf2, "fPdf2/F");
 
  fTree->Branch("genvpt"   ,&fVPt  ,"fVPt/F");
  fTree->Branch("genveta"  ,&fVEta ,"fVEta/F");
  fTree->Branch("genvphi"  ,&fVPhi ,"fVPhi/F");
  fTree->Branch("genvm"    ,&fVM   ,"fVM/F");
  fTree->Branch("genvid"   ,&fVId  ,"fVId/I");
  fTree->Branch("genviso"  ,&fVIso ,"fVIso/F");

  fTree->Branch("genhpt"   ,&fHPt  ,"fHPt/F");
  fTree->Branch("genheta"  ,&fHEta ,"fHEta/F");
  fTree->Branch("genhphi"  ,&fHPhi ,"fHPhi/F");
  fTree->Branch("genhm"    ,&fHM   ,"fHM/F");
  fTree->Branch("genhid"   ,&fHId  ,"fHId/I");

  fTree->Branch("genpt_1"  ,&fPt1 ,"fPt1/F");
  fTree->Branch("geneta_1" ,&fEta1,"fEta1/F");
  fTree->Branch("genphi_1" ,&fPhi1,"fPhi1/F");
  fTree->Branch("genm_1"   ,&fM1  ,"fM1/F");
  fTree->Branch("genid_1"  ,&fId1 ,"fId1/I");

  fTree->Branch("genpt_2"  ,&fPt2 ,"fPt2/F");
  fTree->Branch("geneta_2" ,&fEta2,"fEta2/F");
  fTree->Branch("genphi_2" ,&fPhi2,"fPhi2/F");
  fTree->Branch("genm_2"   ,&fM2  ,"fM2/F");
  fTree->Branch("genid_2"  ,&fId2 ,"fId2/I");

  fTree->Branch("genhpt_1"  ,&fHPt1 ,"fHPt1/F");
  fTree->Branch("genheta_1" ,&fHEta1,"fHEta1/F");
  fTree->Branch("genhphi_1" ,&fHPhi1,"fHPhi1/F");
  fTree->Branch("genhm_1"   ,&fHM1  ,"fHM1/F");
  fTree->Branch("genhid_1"  ,&fHId1 ,"fHId1/I");

  fTree->Branch("genhpt_2"  ,&fHPt2 ,"fHPt2/F");
  fTree->Branch("genheta_2" ,&fHEta2,"fHEta2/F");
  fTree->Branch("genhphi_2" ,&fHPhi2,"fHPhi2/F");
  fTree->Branch("genhm_2"   ,&fHM2  ,"fHM2/F");
  fTree->Branch("genhid_2"  ,&fHId2 ,"fHId2/I");

  fTree->Branch("gendmpt"  ,&fDPt ,"fDPt/F");
  fTree->Branch("gendmeta" ,&fDEta,"fDEta/F");
  fTree->Branch("gendmphi" ,&fDPhi,"fDPhi/F");
  fTree->Branch("gendmm"   ,&fDM  ,"fDM/F");
  fTree->Branch("gendmid"  ,&fDId ,"fDId/I");
}
void GenLoader::load(int iEvent) { 
  fGens     ->Clear();
  fGenBr    ->GetEntry(iEvent);
  fGenInfoBr->GetEntry(iEvent);
}
void GenLoader::fillGenEvent() { 
  fQ    = fGenInfo->scalePDF; 
  fX1   = fGenInfo->x_1; 
  fX2   = fGenInfo->x_2; 
  fPId1 = fGenInfo->id_1; 
  fPId2 = fGenInfo->id_2; 
  fXS     = fGenInfo->xs;
  fWeight = fGenInfo->weight;
}
void GenLoader::selectBoson(int iDMu) {
  reset(); 
  TGenParticle *lHBoson  = 0; 
  TGenParticle *lLep1    = 0; 
  TGenParticle *lLep2    = 0; 
  TGenParticle *lHLep1   = 0; 
  TGenParticle *lHLep2   = 0; 
  int   lBosonId         = -10; 
  int   lHBosonId        = -10; 
  int lDMCount           = 0; 
  int lId1  = 0; 
  int lId2  = 0; 
  int lHId1 = 0; 
  int lHId2 = 0; 
  TLorentzVector lDM; 
  for  (int i0 = 0; i0 < fGens->GetEntriesFast(); i0++) { 
    TGenParticle *pGen = (TGenParticle*)((*fGens)[i0]);
    if(fabs(pGen->pdgId) == 23 ||   // Select Z or
       fabs(pGen->pdgId) == 24) { 
      fBoson   = pGen;
      lBosonId = i0;
    }
    if(fabs(pGen->pdgId) == 25) {   // Select Higgs
      lHBoson   = pGen;
      lHBosonId = i0;
    }
    if(iDMu < 0 && fabs(pGen->pdgId) == 22 && fBoson == 0) {   // Select Higgs
      fBoson   = pGen;
      lBosonId = i0;
    }
    if(pGen->parent == lBosonId) { //All of these guys have two daughters
      //!!!Note this will not work for taus
      if(pGen->status == 1 && lLep1 != 0) lLep2 = pGen;
      if(pGen->status == 1 && lLep1 == 0) lLep1 = pGen;
      
      if(pGen->status != 1 && lLep1 != 0) lId2  = getId     (i0,pGen->pdgId,isNeutrino(pGen)); 
      if(pGen->status != 1 && lLep1 == 0) lId1  = getId     (i0,pGen->pdgId,isNeutrino(pGen));
      
      if(pGen->status != 1 && lLep1 != 0) lLep2 = getStatus1(i0,isNeutrino(pGen));  //Obtain the simulation level if not already
      if(pGen->status != 1 && lLep1 == 0) lLep1 = getStatus1(i0,isNeutrino(pGen)); 
    } 
    if(pGen->parent == lHBosonId) { //All of these guys have two daughters
      //!!!Note this will not work for taus
      if(pGen->status == 1 && lHLep1 != 0) lHLep2 = pGen;
      if(pGen->status == 1 && lHLep1 == 0) lHLep1 = pGen;
      
      if(pGen->status != 1 && lHLep1 != 0) lHId2  = getId     (i0,pGen->pdgId,isNeutrino(pGen)); 
      if(pGen->status != 1 && lHLep1 == 0) lHId1  = getId     (i0,pGen->pdgId,isNeutrino(pGen));
      
      if(pGen->status != 1 && lHLep1 != 0) lHLep2 = getStatus1(i0,isNeutrino(pGen));  //Obtain the simulation level if not already
      if(pGen->status != 1 && lHLep1 == 0) lHLep1 = getStatus1(i0,isNeutrino(pGen)); 
    } 
    if(pGen->status   == 1 && fabs(pGen->pdgId) == 1000022) { 
      TLorentzVector pVec; pVec.SetPtEtaPhiM(pGen->pt,pGen->eta,pGen->phi,pGen->mass);
      lDM += pVec;
      lDMCount++;
    }
  }
  if(fBoson != 0) { 
    fVPt  = fBoson->pt;
    fVEta = fBoson->eta;
    fVPhi = fBoson->phi;
    fVM   = fBoson->mass;
    fVId  = fBoson->pdgId;
    if(fVId == 22) fVIso = frixione(fBoson);
  }
  if(lHBoson != 0) {
    fHPt  = lHBoson->pt;
    fHEta = lHBoson->eta;
    fHPhi = lHBoson->phi;
    fHM   = lHBoson->mass;
    fHId  = lHBoson->pdgId;
  }
  if(lLep1 != 0 && lLep2 != 0) {
    if(lLep2->pt > lLep1->pt || !isNeutrino(lLep2)) {  
      TGenParticle *lLep = 0; 
      lLep = lLep1; 
      //Swaps
      lLep1 = lLep2;
      lLep2 = lLep;
    }
    fPt1  = lLep1->pt;
    fEta1 = lLep1->eta;
    fPhi1 = lLep1->phi;
    fM1   = lLep1->mass;
    fId1  = lId1;//lLep1->pdgId;
    
    fPt2  = lLep2->pt;
    fEta2 = lLep2->eta;
    fPhi2 = lLep2->phi;
    fM2   = lLep2->mass;
    fId2  = lId2;//lLep2->pdgId;
  }
  if(lHLep1 != 0 && lHLep2 != 0) {
    if(lHLep2->pt > lHLep1->pt || !isNeutrino(lHLep2)) {  
      TGenParticle *lHLep = 0; 
      lHLep = lHLep1; 
      //Swaps
      lHLep1 = lHLep2;
      lHLep2 = lHLep;
    }
    fHPt1  = lHLep1->pt;
    fHEta1 = lHLep1->eta;
    fHPhi1 = lHLep1->phi;
    fHM1   = lHLep1->mass;
    fHId1  = lHId1;//lLep1->pdgId;
    
    fHPt2  = lHLep2->pt;
    fHEta2 = lHLep2->eta;
    fHPhi2 = lHLep2->phi;
    fHM2   = lHLep2->mass;
    fHId2  = lHId2;//lLep2->pdgId;
  }
  if(lDMCount == 0) return;
  fDPt  = lDM.Pt();
  fDEta = lDM.Eta();
  fDPhi = lDM.Phi();
  fDM   = lDM.M();
  fDId  = 1000022;
}
TGenParticle* GenLoader::getStatus1(int iId,bool iIsNeut) { 
  int lId = iId;
  TGenParticle *lGen = 0; 
  for  (int i0 = 0; i0 < fGens->GetEntriesFast(); i0++) { 
    TGenParticle *pGen = (TGenParticle*)((*fGens)[i0]);
    if(pGen->parent == lId && !(isNeutrino(pGen) && !iIsNeut)  ) { 
      lGen = pGen;
      if(pGen->status == 1) break; 
      lId = i0;  //Keep searching down the chain for status 1 !!! Assumes gen particle list is ordered
    }
  }    
  //assert(lGen); 
  //assert(lGen->status == 1); ===> commented out to fix issues with taus 
  return lGen;
}
bool GenLoader::isNeutrino(TGenParticle *iPart) { 
  if(fabs(iPart->pdgId) == 12) return true; 
  if(fabs(iPart->pdgId) == 14) return true; 
  if(fabs(iPart->pdgId) == 16) return true; 
  return false;
}
int GenLoader::getId(int iId,int iPId,bool iIsNeut) { 
  int lId   = iId;
  TGenParticle *lGen = 0; 
  for  (int i0 = 0; i0 < fGens->GetEntriesFast(); i0++) { 
    TGenParticle *pGen = (TGenParticle*)((*fGens)[i0]);
    if(pGen->parent == lId && !(isNeutrino(pGen) && !iIsNeut)  ) { 
      lGen = pGen;
      lId = i0;  //Keep searching down the chain for status 1 !!! Assumes gen particle list is ordered
      if(pGen->status == 1) break; 
    }
  }    
  if(lGen == 0) return -1;
  if(fabs(iPId) != 15)                            return lGen->pdgId;
  if(fabs(iPId) == 15 && fabs(lGen->pdgId) == 11) return 16*(fabs(lGen->pdgId)/(lGen->pdgId));
  if(fabs(iPId) == 15 && fabs(lGen->pdgId) == 13) return 17*(fabs(lGen->pdgId)/(lGen->pdgId));
  return 18*(fabs(lGen->pdgId)/(lGen->pdgId));
}
float GenLoader::frixione(TGenParticle *iPart) { 
  float lMax = -1; 
  for  (int i0 = 0; i0 < fGens->GetEntriesFast(); i0++) { 
    TGenParticle *pGen = (TGenParticle*)((*fGens)[i0]);
    if(i0 != iPart->parent) continue;
    TLorentzVector lParent; lParent.SetPtEtaPhiM(pGen ->pt,pGen ->eta,pGen ->phi,pGen ->mass);
    TLorentzVector lPart  ; lPart  .SetPtEtaPhiM(iPart->pt,iPart->eta,iPart->phi,iPart->mass);
    TLorentzVector lOther = lParent-lPart;
    float pDEta = fabs(lOther.Eta() - iPart->eta); 
    float pDPhi = fabs(lOther.Phi() - iPart->phi); 
    if(2.*TMath::Pi()-pDPhi < pDPhi) pDPhi = 2.*TMath::Pi()-pDPhi;
    float pDR = sqrt(pDEta*pDEta + pDPhi*pDPhi);
    if(pDR > 0.4) continue;
    float pMax = lOther.Pt()/((1-cos(pDR))/(1-cos(0.4)));
    if(lMax > pMax) continue;
    lMax = pMax;
    std::cout << "F===> " << pDR << " -- " << i0 << " -- " << iPart->parent << " -- " << pGen->pt << " -- " << pGen->pdgId << " -- " << " -- " << pMax << std::endl;
  }
  return lMax;
}
