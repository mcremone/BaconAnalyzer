#include "MonoXBitsLoader.hh"  
using namespace std;

MonoXBitsLoader::MonoXBitsLoader(TTree *iTree,TString jet, TString algo,TString syst, string preselection) {
  if(iTree){
    TString met = "puppet"; if (algo!="PUPPI") met = "pfmet";
    if(preselection.compare("Had")==0){
      iTree->SetBranchAddress("mindPhi",                                &min_dphijetsmet);
    }
    else{
      iTree->SetBranchAddress("mindFPhi",                               &min_dphijetsmet);
    }
    iTree->SetBranchAddress("runNum",                                   &runNum);
    iTree->SetBranchAddress("lumiSec",                                  &lumiSec);
    iTree->SetBranchAddress("evtNum",                                   &evtNum);
    iTree->SetBranchAddress("metfilter",                                &metfilter);
    iTree->SetBranchAddress("triggerBits",                              &triggerBits);
    iTree->SetBranchAddress("selectBits",                               &selectBits);
    iTree->SetBranchAddress("triggerEff",                               &triggerEff);
    iTree->SetBranchAddress("npu",                                      &npu);
    iTree->SetBranchAddress("npv",                                      &npv);
    iTree->SetBranchAddress("puWeight",                                 &puWeight);
    iTree->SetBranchAddress("scale1fb",                                 &scale1fb);
    iTree->SetBranchAddress("evtWeight",                                &evtWeight);
    iTree->SetBranchAddress("kfactor",                                  &kfactor);
    iTree->SetBranchAddress(met,                                        &vmetpt);
    iTree->SetBranchAddress(met+"phi",                                  &vmetphi);
    iTree->SetBranchAddress("fake"+met,                                 &vfakemetpt);
    iTree->SetBranchAddress("fake"+met+"phi",                           &vfakemetphi);
    iTree->SetBranchAddress("n"+algo+"jets",                            &njets);
    iTree->SetBranchAddress("nbtags",                                   &nbtags);
    iTree->SetBranchAddress("nb"+algo+"jetsL",                          &nbjetsL);
    iTree->SetBranchAddress("nb"+algo+"jetsM",                          &nbjetsM);
    iTree->SetBranchAddress("nb"+algo+"jetsLdR2",                       &nbjetsLdR2);
    iTree->SetBranchAddress("nb"+algo+"jetsT",                          &nbjetsT);
    iTree->SetBranchAddress("res_"+algo+"jetmT",                        &res_mt);
    iTree->SetBranchAddress("res_"+algo+"jet0_pt",                      &res_jet0_pt);
    iTree->SetBranchAddress("res_"+algo+"jet0_eta",                     &res_jet0_eta);
    iTree->SetBranchAddress("res_"+algo+"jet0_phi",                     &res_jet0_phi);
    iTree->SetBranchAddress("res_"+algo+"jet1_pt",                      &res_jet1_pt);
    iTree->SetBranchAddress("res_"+algo+"jet1_eta",                     &res_jet1_eta);
    iTree->SetBranchAddress("res_"+algo+"jet1_phi",                     &res_jet1_phi);
    iTree->SetBranchAddress("res_"+algo+"jet2_pt",                      &res_jet2_pt);
    iTree->SetBranchAddress("res_"+algo+"jet2_eta",                     &res_jet2_eta);
    iTree->SetBranchAddress("res_"+algo+"jet2_phi",                     &res_jet2_phi);
    iTree->SetBranchAddress("res_"+algo+"jet3_pt",                      &res_jet3_pt);
    iTree->SetBranchAddress("res_"+algo+"jet3_eta",                     &res_jet3_eta);
    iTree->SetBranchAddress("res_"+algo+"jet3_phi",                     &res_jet3_phi);
    iTree->SetBranchAddress("res_"+algo+"jet0_mass",                    &res_jet0_mass);
    iTree->SetBranchAddress("res_"+algo+"jet1_mass",                    &res_jet1_mass);
    iTree->SetBranchAddress("res_"+algo+"jet2_mass",                    &res_jet2_mass);
    iTree->SetBranchAddress("res_"+algo+"jet3_mass",                    &res_jet3_mass);
    iTree->SetBranchAddress("res_"+algo+"jet0_CHF",                     &res_jet0_CHF);
    iTree->SetBranchAddress("res_"+algo+"jet0_NHF",                     &res_jet0_NHF);
    iTree->SetBranchAddress("res_"+algo+"jet0_NEMF",                    &res_jet0_NEMF);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL0_"+syst,             &res_btagwL0);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL1_"+syst,             &res_btagwL1);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwLminus1_"+syst,        &res_btagwLminus1);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL2_"+syst,             &res_btagwL2);
    iTree->SetBranchAddress("nmu",                                      &nmu);
    iTree->SetBranchAddress("nele",                                     &nele);
    iTree->SetBranchAddress("ntau",                                     &ntau);
    iTree->SetBranchAddress("npho",                                     &npho);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_isHadronicTop",    &isHadronicTop);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_topSize",          &topSize);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_topMatching",      &topMatching);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jets",                  &nfjets);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_mT",               &bst_mt);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_pt",               &bst_jet0_pt);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_eta",              &bst_jet0_eta);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_phi",              &bst_jet0_phi);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_mass",             &bst_jet0_mass);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_msd",              &bst_jet0_msd);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_tau32",            &bst_jet0_tau32);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_CHF",              &bst_jet0_CHF);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_NHF",              &bst_jet0_NHF);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_NEFM",             &bst_jet0_NEMF);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_minsubcsv",        &bst_jet0_minsubcsv);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_maxsubcsv",        &bst_jet0_maxsubcsv);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_doublecsv",        &bst_jet0_doublecsv);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jetbtagwM0_"+syst,      &bst_btagwM0);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jetbtagwM1_"+syst,      &bst_btagwM1);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jetbtagwMminus1_"+syst, &bst_btagwMminus1);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jetbtagwM2_"+syst,      &bst_btagwM2);
    iTree->SetBranchAddress("eleSF0",                                   &eleSF0);
    iTree->SetBranchAddress("eleSF1",                                   &eleSF1);
    iTree->SetBranchAddress("eleSF2",                                   &eleSF2);
    iTree->SetBranchAddress("muoSF0",                                   &muoSF0);
    iTree->SetBranchAddress("muoSF1",                                   &muoSF1);
    iTree->SetBranchAddress("muoSF2",                                   &muoSF2);
    iTree->SetBranchAddress("phoSF0",                                   &phoSF0);
  }
}
MonoXBitsLoader::~MonoXBitsLoader(){}
bool MonoXBitsLoader::selectJetAlgoAndSize(string selection, TString algo){
  bool lPass = false;
  if((selectBits & kBOOSTED15PUPPI) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")!=0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kRESOLVEDPUPPI) && selection.find("Res")==0 && algo=="PUPPI") lPass = true;
  return lPass;
}
bool MonoXBitsLoader::isHad(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true;
  return lPass;
}
bool MonoXBitsLoader::isMuo(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==1 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool MonoXBitsLoader::isZmm(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==2 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool MonoXBitsLoader::isEle(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==1 && npho==0 && ntau==0 && vmetpt>50 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool MonoXBitsLoader::isZee(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==2 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool MonoXBitsLoader::isPho(){
  bool lPass = false;
  if((triggerBits & kSinglePhoton) && nmu==0 && nele==0 && npho==1 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool MonoXBitsLoader::passPreSelection(string preselection){
  bool lPass = false;
  if(preselection.compare("Had")==0 && isHad()) lPass = true;
  if(preselection.compare("Muo")==0 && isMuo()) lPass = true;
  if(preselection.compare("Zmm")==0 && isZmm()) lPass = true;
  if(preselection.compare("Ele")==0 && isEle()) lPass = true;
  if(preselection.compare("Zee")==0 && isZee()) lPass = true;
  if(preselection.compare("Pho")==0 && isPho()) lPass = true;
  return lPass;
}
TLorentzVector MonoXBitsLoader::getMET(string preselection){
  TLorentzVector v;
  v.SetPtEtaPhiM(vfakemetpt,0,vfakemetphi,0);
  if(preselection.compare("Had")==0){v.SetPtEtaPhiM(vmetpt,0,vmetphi,0);};
  return v;
}
TLorentzVector MonoXBitsLoader::getTop(){
  TLorentzVector v;
  v.SetPtEtaPhiM(res_jet0_pt+res_jet1_pt+res_jet2_pt,res_jet0_eta+res_jet1_eta+res_jet2_eta,res_jet0_phi+res_jet1_phi+res_jet2_phi,res_jet0_mass+res_jet1_mass+res_jet2_mass);
  return v;
}
bool MonoXBitsLoader::passMetPreselection(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     nfjets==1 && 
     bst_jet0_pt>250 &&
     bst_jet0_tau32<0.61 && 
     bst_jet0_msd>110 && 
     bst_jet0_msd<210){
    lPass=true;
  }
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection1(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection2(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     nfjets==1 && bst_jet0_pt>250) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection3(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     nfjets==1 && bst_jet0_pt>250 &&
     bst_jet0_tau32<0.61) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection4(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>1.1 &&
     nfjets==1 && bst_jet0_pt>250) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection5(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>1.1 &&
     nfjets==1 && bst_jet0_pt>250 &&
     bst_jet0_msd>110 && bst_jet0_msd<210) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection6(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>1.1 &&
     nfjets==1 && bst_jet0_pt>250 &&
     bst_jet0_msd>110 && bst_jet0_msd<210 &&
     bst_jet0_tau32<0.61) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoosted15MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>1.1 &&
     nfjets==1 && bst_jet0_pt>250) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoosted8MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>0.7 &&
     bst_jet0_pt>250) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passResolvedMonoTop(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt() > 200 &&
     min_dphijetsmet>1.1 &&
     njets>2 &&
     res_jet0_pt > 60 &&
     res_jet1_pt > 60 &&
     res_jet2_pt > 40) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passResolvedMonoXbb(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt() > 200 &&
     min_dphijetsmet>0.7 &&
     njets>=2 &&
     res_jet0_pt>30 && res_jet1_pt>30) lPass = true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopSR(string preselection){ 
  return passBoostedMonoTopPreselection(preselection) & (min_dphijetsmet>1.1) & (bst_jet0_maxsubcsv>CSVM) & (nbjetsLdR2==0);
}
bool MonoXBitsLoader::passBoostedMonoTopSR1(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv>CSVM) & (nbjetsLdR2==0);
}
bool MonoXBitsLoader::passBoostedMonoTopSR2(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv>CSVM);
}
bool MonoXBitsLoader::passBoostedMonoTopSR3(string preselection){
  return passBoostedMonoTopPreselection(preselection);
}
bool MonoXBitsLoader::passBoostedMonoTopSR4(string preselection){
  return passBoostedMonoTopPreselection3(preselection);
}
bool MonoXBitsLoader::passBoostedMonoTopSR5(string preselection){
  return passBoostedMonoTopPreselection2(preselection);
}
bool MonoXBitsLoader::passBoostedMonoTopSR6(string preselection){
  return passBoostedMonoTopPreselection1(preselection);
}

bool MonoXBitsLoader::passBoostedMonoTopSR7(string preselection){
  return passBoostedMonoTopPreselection6(preselection) & (bst_jet0_maxsubcsv>CSVM) & (nbjetsLdR2==0);
}
bool MonoXBitsLoader::passBoostedMonoTopSR8(string preselection){
  return passBoostedMonoTopPreselection6(preselection) & (bst_jet0_maxsubcsv>CSVM);
}
bool MonoXBitsLoader::passBoostedMonoTopSR9(string preselection){
  return passBoostedMonoTopPreselection6(preselection);
}
bool MonoXBitsLoader::passBoostedMonoTopSR10(string preselection){
  return passBoostedMonoTopPreselection5(preselection);
}
bool MonoXBitsLoader::passBoostedMonoTopSR11(string preselection){
  return passBoostedMonoTopPreselection4(preselection);
}
bool MonoXBitsLoader::passBoostedMonoTopSR12(string preselection){
  return passBoostedMonoTopPreselection1(preselection) & (min_dphijetsmet>1.1);
}

bool MonoXBitsLoader::passBoostedMonoTopQCDCR(string preselection){
  return passMetPreselection(preselection) & (min_dphijetsmet<0.1);
}
bool MonoXBitsLoader::passBoostedMonoTopZnunuHFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsL>0) & (nbjetsM==0);
}
bool MonoXBitsLoader::passBoostedMonoTopZnunuLFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsL==0);
}
bool MonoXBitsLoader::passBoostedMonoTopTopCR(string preselection){ 
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv>CSVM) & (nbjetsLdR2>0);
}
bool MonoXBitsLoader::passBoostedMonoTopTopCRminusTau32(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	  nf15jets==1 && bst_jet0_pt>250 &&
	  bst_jet0_msd>110 && bst_jet0_msd<210) & (bst_jet0_maxsubcsv>CSVM) & (nbjetsLdR2==0);
}
bool MonoXBitsLoader::passBoostedMonoTopTopCRminusMass(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	  nf15jets==1 && bst_jet0_pt>250 &&
	  bst_jet0_tau32<0.61 && bst_jet0_msd>40) & (bst_jet0_maxsubcsv>CSVM) & (nbjetsLdR2==0);
}
bool MonoXBitsLoader::passBoostedMonoTopTopCRminusBtag(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (nbjetsLdR2>0);
}
bool MonoXBitsLoader::passBoostedMonoTopWCR(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv<CSVM) & (nbjetsLdR2==0);
}
bool MonoXBitsLoader::passBoostedMonoTopWHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM>0) & (nbjetsT==0);
}
bool MonoXBitsLoader::passBoostedMonoTopWLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM==0);  
}
bool MonoXBitsLoader::passBoostedMonoTopZCR(string preselection){
  return passBoostedMonoTopPreselection(preselection);
}
bool MonoXBitsLoader::passBoostedMonoTopZHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (nbjetsM>0);
}
bool MonoXBitsLoader::passBoostedMonoTopZLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (nbjetsM==0);
}
bool MonoXBitsLoader::passBoostedMonoHbbSR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>CSVL);
}
bool MonoXBitsLoader::passBoostedMonoHbbTopCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>CSVL);
}
bool MonoXBitsLoader::passBoostedMonoHbbWCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv<=CSVL);
}
bool MonoXBitsLoader::passBoostedMonoHbbZCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35));
}
bool MonoXBitsLoader::passBoostedMonoZbbSR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>CSVL);
}
bool MonoXBitsLoader::passBoostedMonoZbbTopCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>CSVL);
}
bool MonoXBitsLoader::passBoostedMonoZbbWCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv<=CSVL);
}
bool MonoXBitsLoader::passBoostedMonoZbbZCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35));
}	
bool MonoXBitsLoader::passResolvedMonoHbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsM==2);
}
bool MonoXBitsLoader::passResolvedMonoHbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsT==1);
}
bool MonoXBitsLoader::passResolvedMonoHbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsT==0) & (nbjetsM==2);
}
bool MonoXBitsLoader::passResolvedMonoHbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150);
}
bool MonoXBitsLoader::passResolvedMonoZbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsL==2);
}
bool MonoXBitsLoader::passResolvedMonoZbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsT==1);
}
bool MonoXBitsLoader::passResolvedMonoZbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsT==0);
}
bool MonoXBitsLoader::passResolvedMonoZbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105);
}
bool MonoXBitsLoader::passResolvedMonoTopSR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (nbjetsM==1) & (vTop.M() < 250);
}
bool MonoXBitsLoader::passResolvedMonoTopTopCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() < 250) & (nbjetsM==1);
}
bool MonoXBitsLoader::passResolvedMonoTopWCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() >= 250);
}
bool MonoXBitsLoader::passResolvedMonoTopZCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() < 250);
}
bool MonoXBitsLoader::passSelection(string preselection, string selection, string subsample, string combo, float &btagw){
  bool lPass = false;	
  btagw = 1;
  if (selection == "BstMonoTop")
    {
      if (subsample == "SR" && passBoostedMonoTopSR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0*bst_btagwM1; lPass = true;}

      if (subsample == "SR1" && passBoostedMonoTopSR1(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0*bst_btagwM1; lPass = true;}
      if (subsample == "SR2" && passBoostedMonoTopSR2(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR3" && passBoostedMonoTopSR3(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR4" && passBoostedMonoTopSR4(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR5" && passBoostedMonoTopSR5(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR6" && passBoostedMonoTopSR6(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}

      if (subsample == "SR7" && passBoostedMonoTopSR7(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0*bst_btagwM1; lPass = true;}
      if (subsample == "SR8" && passBoostedMonoTopSR8(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR9" && passBoostedMonoTopSR9(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR10" && passBoostedMonoTopSR10(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR11" && passBoostedMonoTopSR11(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
      if (subsample == "SR12" && passBoostedMonoTopSR12(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}

      if (subsample == "QCDCR" && passBoostedMonoTopQCDCR(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}

      if (subsample == "TopCR" && passBoostedMonoTopTopCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1*bst_btagwM1; lPass = true;}
      if (subsample == "minusTau32" && passBoostedMonoTopTopCRminusTau32(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1*bst_btagwM1; lPass = true;}
      if (subsample == "minusMass" && passBoostedMonoTopTopCRminusMass(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1*bst_btagwM1; lPass = true;}
      if (subsample == "minusBtag" && passBoostedMonoTopTopCRminusBtag(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1*bst_btagwM1; lPass = true;}

      if (subsample == "WCR" && passBoostedMonoTopWCR(preselection) 
       	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0*bst_btagwM0; lPass = true;}
      if (subsample == "WHFCR" && passBoostedMonoTopWHFCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwM1*bst_btagwM0; lPass = true;}
      if (subsample == "WLFCR" && passBoostedMonoTopWLFCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwM0*bst_btagwM0; lPass = true;}

      if (subsample == "ZCR" && passBoostedMonoTopZCR(preselection) 
 	  && (combo=="ONLY" || combo=="COMBO")) lPass = true;
      if (subsample == "ZHFCR" && passBoostedMonoTopZHFCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwLminus1; lPass = true;}
      if (subsample == "ZLFCR" && passBoostedMonoTopZLFCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0; lPass = true;}
    }
  if (selection == "BstMonoHbb")
    {
      if (subsample == "SR" && passBoostedMonoHbbSR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL2; lPass = true;}
      if (subsample == "TopCR" && passBoostedMonoHbbTopCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL2; lPass = true;}
      if (subsample == "WCR" && passBoostedMonoHbbWCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0; lPass = true;}
      if (subsample == "ZCR" && passBoostedMonoHbbZCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) lPass = true;
    }
  if (selection == "BstMonoZbb")
    {
      if (subsample == "SR" && passBoostedMonoHbbSR(preselection) 
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopSR(preselection) && !passBoostedMonoHbbSR(preselection)))) {btagw=res_btagwL2; lPass = true;}
      if (subsample == "TopCR" && passBoostedMonoHbbTopCR(preselection) 
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoHbbWCR(preselection)))) 
	{btagw=res_btagwL2; lPass = true;}
      if (subsample == "WCR" && passBoostedMonoHbbWCR(preselection) 
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoHbbWCR(preselection))))
	{btagw=res_btagwL0; lPass = true;}
      if (subsample == "ZCR" && passBoostedMonoHbbZCR(preselection) 
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopZCR(preselection) && !passBoostedMonoHbbZCR(preselection)))) lPass = true;
    }
  if (selection == "ResMonoTop")
    {
      if (subsample == "SR" && passResolvedMonoTopSR(preselection) && !passBoostedMonoTopSR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoHbbSR(preselection) && !passBoostedMonoZbbSR(preselection)))) {btagw=res_btagwMminus1; lPass = true;}
      if (subsample == "TopCR" && passResolvedMonoTopTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoTopTopCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoZbbTopCR(preselection) && !passBoostedMonoHbbWCR(preselection) && !passBoostedMonoZbbWCR(preselection))))
	{btagw=res_btagwMminus1; lPass = true;}
      if (subsample == "WCR" && passResolvedMonoTopWCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoTopTopCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoZbbTopCR(preselection) && !passBoostedMonoHbbWCR(preselection) && !passBoostedMonoZbbWCR(preselection)))) lPass = true;
      if (subsample == "ZCR" && passResolvedMonoTopZCR(preselection) && !passBoostedMonoTopZCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoZbbZCR(preselection) && !passBoostedMonoHbbZCR(preselection)))) lPass = true;
    }
  if (selection == "ResMonoHbb")
    {
      if (subsample == "SR" && passResolvedMonoHbbSR(preselection) && !passBoostedMonoHbbSR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopSR(preselection) && !passBoostedMonoZbbSR(preselection))))
	{btagw=res_btagwM2; lPass = true;}
      if (subsample == "TopCR" && passResolvedMonoHbbTopCR(preselection) && !passBoostedMonoHbbWCR(preselection) && !passBoostedMonoHbbTopCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoZbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoZbbWCR(preselection))))
	{btagw=res_btagwTminus1; lPass = true;}
      if (subsample == "WCR" && passResolvedMonoHbbWCR(preselection) && !passBoostedMonoHbbWCR(preselection) && !passBoostedMonoHbbTopCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoZbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoZbbWCR(preselection))))
	{btagw=res_btagwT0; lPass = true;}
      if (subsample == "ZCR" && passResolvedMonoHbbZCR(preselection) && !passBoostedMonoHbbZCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoZbbZCR(preselection) && !passBoostedMonoTopZCR(preselection)))) lPass = true;
    }
  if (selection == "ResMonoZbb")
    {
      if (subsample == "SR" && passResolvedMonoZbbSR(preselection) && !passBoostedMonoZbbSR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopSR(preselection) && !passBoostedMonoHbbSR(preselection)))) {btagw=res_btagwL2; lPass = true;}
      if (subsample == "TopCR" && passResolvedMonoZbbTopCR(preselection) && !passBoostedMonoZbbWCR(preselection) && !passBoostedMonoZbbTopCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoHbbWCR(preselection))))
	{btagw=res_btagwTminus1; lPass = true;}
      if (subsample == "WCR" && passResolvedMonoZbbWCR(preselection) && !passBoostedMonoZbbWCR(preselection) && !passBoostedMonoZbbTopCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoHbbWCR(preselection))))
	{btagw=res_btagwT0; lPass = true;}
      if (subsample == "ZCR" && passResolvedMonoZbbZCR(preselection) && !passBoostedMonoZbbZCR(preselection)
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoHbbZCR(preselection) && !passBoostedMonoTopZCR(preselection)))) lPass = true;
    }
  return lPass;
}
double MonoXBitsLoader::getWgt(bool isData, TString algo, double LUMI, float btagw){
  float wgt = 1;
  if(!isData) {     
    wgt *= LUMI*scale1fb*kfactor*btagw*triggerEff*evtWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
float MonoXBitsLoader::transverse_mass(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_mt;
  else if(selection == "BstMonoZbb") return bst_mt;
  else return res_mt;
}
float MonoXBitsLoader::fjet_mass(string selection){
  return bst_jet0_msd;
}
float MonoXBitsLoader::nsubjet(string selection){
  if(selection == "BstMonoTop" || selection == "ResMonoTop") return bst_jet0_tau32;
  else if(selection == "BstMonoHbb" || selection == "ResMonoHbb") return bst_jet0_tau21;
  else return bst_jet0_tau21;
}
float MonoXBitsLoader::btag(string selection){
  return bst_jet0_maxsubcsv;
}
float MonoXBitsLoader::chf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_CHF;
  else if(selection == "BstMonoZHbb") return bst_jet0_CHF;
  else return res_jet0_CHF; 
}
float MonoXBitsLoader::nhf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_NHF;
  else if(selection == "BstMonoZHbb") return bst_jet0_NHF;
  else return res_jet0_NHF;
}
float MonoXBitsLoader::nemf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_NEMF;
  else if(selection == "BstMonoZHbb") return bst_jet0_NEMF;
  else return res_jet0_NEMF;
}
