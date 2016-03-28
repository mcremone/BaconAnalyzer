#include "BitsLoader.hh"  
using namespace std;

BitsLoader::BitsLoader(TTree *iTree,TString jet, TString algo,TString syst, string preselection) {
  if(iTree){
    TString met = "puppet"; if (algo!="PUPPI") met = "pfmet";
    if(preselection.compare("Had")==0){
      iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_mindPhi", &min_dphijetsmet);
    }
    else{
      iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_mindFPhi",&min_dphijetsmet);
    }
    iTree->SetBranchAddress("runNum",                            &runNum);
    iTree->SetBranchAddress("lumiSec",                           &lumiSec);
    iTree->SetBranchAddress("evtNum",                            &evtNum);
    iTree->SetBranchAddress("metfilter",                         &metfilter);
    iTree->SetBranchAddress("triggerBits",                       &triggerBits);
    iTree->SetBranchAddress("selectBits",                        &selectBits);
    iTree->SetBranchAddress("triggerEff",                        &triggerEff);
    iTree->SetBranchAddress("npu",                               &npu);
    iTree->SetBranchAddress("npv",                               &npv);
    iTree->SetBranchAddress("puWeight",                          &puWeight);
    iTree->SetBranchAddress("scale1fb",                          &scale1fb);
    iTree->SetBranchAddress("evtWeight",                         &evtWeight);
    iTree->SetBranchAddress("nloKfactor_CENT",                   &nloKfactor);
    iTree->SetBranchAddress("ewkCorr_CENT",                      &ewkCorr);
    iTree->SetBranchAddress(met,                                 &vmetpt);
    iTree->SetBranchAddress(met+"phi",                           &vmetphi);
    iTree->SetBranchAddress("fake"+met,                          &vfakemetpt);
    iTree->SetBranchAddress("fake"+met+"phi",                    &vfakemetphi);
    iTree->SetBranchAddress(met+"mT",                            &bst_mt);
    iTree->SetBranchAddress("n"+algo+"jets",                     &njets);
    iTree->SetBranchAddress("nfbst"+jet+"_"+algo+"jet",          &nfjets);
    iTree->SetBranchAddress("nbtags",                            &nbtags);
    iTree->SetBranchAddress("nb"+algo+"jetsL",                   &nbjetsL);
    iTree->SetBranchAddress("nb"+algo+"jetsM",                   &nbjetsM);
    iTree->SetBranchAddress("nb"+algo+"jetsLdR2",                &nbjetsLdR2);
    iTree->SetBranchAddress("nb"+algo+"jetsT",                   &nbjetsT);
    iTree->SetBranchAddress("res_"+algo+"jet0_pt",               &res_jet0_pt);
    iTree->SetBranchAddress("res_"+algo+"jet0_eta",              &res_jet0_eta);
    iTree->SetBranchAddress("res_"+algo+"jet0_phi",              &res_jet0_phi);
    iTree->SetBranchAddress("res_"+algo+"jet1_pt",               &res_jet1_pt);
    iTree->SetBranchAddress("res_"+algo+"jet1_eta",              &res_jet1_eta);
    iTree->SetBranchAddress("res_"+algo+"jet1_phi",              &res_jet1_phi);
    iTree->SetBranchAddress("res_"+algo+"jet2_pt",               &res_jet2_pt);
    iTree->SetBranchAddress("res_"+algo+"jet2_eta",              &res_jet2_eta);
    iTree->SetBranchAddress("res_"+algo+"jet2_phi",              &res_jet2_phi);
    iTree->SetBranchAddress("res_"+algo+"jet3_pt",               &res_jet3_pt);
    iTree->SetBranchAddress("res_"+algo+"jet3_eta",              &res_jet3_eta);
    iTree->SetBranchAddress("res_"+algo+"jet3_phi",              &res_jet3_phi);
    iTree->SetBranchAddress("res_"+algo+"jet0_mass",             &res_jet0_mass);
    iTree->SetBranchAddress("res_"+algo+"jet1_mass",             &res_jet1_mass);
    iTree->SetBranchAddress("res_"+algo+"jet2_mass",             &res_jet2_mass);
    iTree->SetBranchAddress("res_"+algo+"jet3_mass",             &res_jet3_mass);
    iTree->SetBranchAddress("res_"+algo+"jet0_CHF",              &res_jet0_CHF);
    iTree->SetBranchAddress("res_"+algo+"jet0_NHF",              &res_jet0_NHF);
    iTree->SetBranchAddress("res_"+algo+"jet0_NEMF",             &res_jet0_NEMF);
    iTree->SetBranchAddress("res_"+algo+"jet0_dphi",             &res_jet0_dphi);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL0_"+syst,      &res_btagwL0);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL1_"+syst,      &res_btagwL1);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwLminus1_"+syst, &res_btagwLminus1);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL2_"+syst,      &res_btagwL2);
    iTree->SetBranchAddress("topSizebst"+jet+"_"+algo+"jet",     &topSize);
    iTree->SetBranchAddress("nmu",                               &nmu);
    iTree->SetBranchAddress("nele",                              &nele);
    iTree->SetBranchAddress("ntau",                              &ntau);
    iTree->SetBranchAddress("npho",                              &npho);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_pt",        &bst_jet0_pt);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_eta",       &bst_jet0_eta);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_phi",       &bst_jet0_phi);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_mass",      &bst_jet0_mass);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_msd",       &bst_jet0_msd);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_tau32",     &bst_jet0_tau32);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_CHF",       &bst_jet0_CHF);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_NHF",       &bst_jet0_NHF);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_NEFM",      &bst_jet0_NEMF);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_minsubcsv", &bst_jet0_minsubcsv);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_maxsubcsv", &bst_jet0_maxsubcsv);
    iTree->SetBranchAddress("eleSF0",                            &eleSF0);
    iTree->SetBranchAddress("eleSF1",                            &eleSF1);
    iTree->SetBranchAddress("eleSF2",                            &eleSF2);
    iTree->SetBranchAddress("muoSF0",                            &muoSF0);
    iTree->SetBranchAddress("muoSF1",                            &muoSF1);
    iTree->SetBranchAddress("muoSF2",                            &muoSF2);
  }
}
BitsLoader::~BitsLoader(){}
bool BitsLoader::selectJetAlgoAndSize(string selection, TString algo){
  bool lPass = false;
  if((selectBits & kBOOSTED15PUPPI) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")!=0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kBOOSTED15CHS) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")!=0 && algo=="CHS") lPass = true;
  else if((selectBits & kBOOSTED8PUPPI) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")==0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kBOOSTED8CHS) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")==0 && algo=="CHS") lPass = true;
  else if((selectBits & kRESOLVEDPUPPI) && selection.find("Res")==0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kRESOLVEDCHS) && selection.find("Res")==0 && algo=="CHS") lPass = true;
  return lPass;
}
bool BitsLoader::isHad(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true;
  return lPass;
}
bool BitsLoader::isMuo(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==1 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isZmm(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==2 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isEle(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==1 && npho==0 && ntau==0 && vmetpt>50 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isZee(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==2 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isPho(){
  bool lPass = false;
  if((triggerBits & kSinglePhoton) && nmu==0 && nele==0 && npho==1 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::passPreSelection(string preselection){
  bool lPass = false;
  if(preselection.compare("Had")==0 && isHad()) lPass = true;
  if(preselection.compare("Muo")==0 && isMuo()) lPass = true;
  if(preselection.compare("Zmm")==0 && isZmm()) lPass = true;
  if(preselection.compare("Ele")==0 && isEle()) lPass = true;
  if(preselection.compare("Zee")==0 && isZee()) lPass = true;
  if(preselection.compare("Pho")==0 && isPho()) lPass = true;
  return lPass;
}
TLorentzVector BitsLoader::getMET(string preselection){
  TLorentzVector v;
  v.SetPtEtaPhiM(vfakemetpt,0,vfakemetphi,0);
  if(preselection.compare("Had")==0){v.SetPtEtaPhiM(vmetpt,0,vmetphi,0);};
  return v;
}
TLorentzVector BitsLoader::getTop(){
  TLorentzVector v;
  v.SetPtEtaPhiM(res_jet0_pt+res_jet1_pt+res_jet2_pt,res_jet0_eta+res_jet1_eta+res_jet2_eta,res_jet0_phi+res_jet1_phi+res_jet2_phi,res_jet0_mass+res_jet1_mass+res_jet2_mass);
  return v;
}
bool BitsLoader::passBoostedMonoTopPreselection(string preselection){
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
bool BitsLoader::passBoosted15MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>1.1 &&
     // bst15_jet0_msd>40 &&
     nfjets==1 && bst_jet0_pt>250) lPass=true;// && 
     // bst_jet0_CHF>0.4 && bst_jet0_NHF<0.26 && bst_jet0_NEMF<0.57) lPass=true;
  return lPass;
}
bool BitsLoader::passBoosted8MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>0.7 &&
     // bst_jet0_msd>40 &&
     // nfjets==1 &&
     bst_jet0_pt>250) lPass=true;
  return lPass;
}
bool BitsLoader::passResolvedMonoTop(string preselection){
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
bool BitsLoader::passResolvedMonoXbb(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt() > 200 &&
     min_dphijetsmet>0.7 &&
     njets>=2 &&
     res_jet0_pt>30 && res_jet1_pt>30) lPass = true;
  return lPass;
}
bool BitsLoader::passBoostedMonoTopSR(string preselection){ 
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66);// & (nbjetsM>0); 
  return passBoostedMonoTopPreselection(preselection) & (min_dphijetsmet>1.1) & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopZnunuHFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsL>0) & (nbjetsM==0);
}
bool BitsLoader::passBoostedMonoTopZnunuLFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsL==0);// & (bst_jet0_minsubcsv<=0.605);
}
bool BitsLoader::passBoostedMonoTopTopCR(string preselection){ 
  //  TLorentzVector vMET = getMET(preselection);
  //  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78)& (bst_jet0_maxsubcsv>0.89) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM>0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM>0) & (nbjetsT==1); 
  //  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsT>0);
  //  return (vMET.Pt()>250) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66) & (nbjetsM>0);
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2>0);
}
bool BitsLoader::passBoostedMonoTopTopCRminusTau32(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	  nf15jets==1 && bst_jet0_pt>250 &&
	  bst_jet0_msd>110 && bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopTopCRminusMass(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	  nf15jets==1 && bst_jet0_pt>250 &&
	  bst_jet0_tau32<0.61 && bst_jet0_msd>40) & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopTopCRminusBtag(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (nbjetsLdR2>0);
}
bool BitsLoader::passBoostedMonoTopWCR(string preselection){
  // TLorentzVector vMET = getMET(preselection);
  // return (vMET.Pt()>250) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66) & (nbjetsM==0);
  //  return (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (bst_jet0_maxsubcsv<=0.89);
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv<0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopWHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78)& (bst_jet0_maxsubcsv>0.605) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM==0); 
  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM>0) & (nbjetsT==0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsT==1) & (nbjetsM==0);
}
bool BitsLoader::passBoostedMonoTopWLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78)& (bst_jet0_maxsubcsv<=0.605) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM==0);
  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM==0);  
}
bool BitsLoader::passBoostedMonoTopZCR(string preselection){
  //  return passBoosted15MonoX(preselection) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78);
  // TLorentzVector vMET = getMET(preselection);
  // return (vMET.Pt()>250) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66);
  return passBoostedMonoTopPreselection(preselection);
}
bool BitsLoader::passBoostedMonoTopZHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (nbjetsM>0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (bst_jet0_maxsubcsv>0.89);
}
bool BitsLoader::passBoostedMonoTopZLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (nbjetsM==0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (bst_jet0_maxsubcsv<=0.89);
}
bool BitsLoader::passBoostedMonoHbbSR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoHbbTopCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoHbbWCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv<=0.605);
}
bool BitsLoader::passBoostedMonoHbbZCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35));
}
bool BitsLoader::passBoostedMonoZbbSR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoZbbTopCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoZbbWCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv<=0.605);
}
bool BitsLoader::passBoostedMonoZbbZCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35));
}	
bool BitsLoader::passResolvedMonoHbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsM==2);
}
bool BitsLoader::passResolvedMonoHbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsT==1);
}
bool BitsLoader::passResolvedMonoHbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsT==0) & (nbjetsM==2);
}
bool BitsLoader::passResolvedMonoHbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150);
}
bool BitsLoader::passResolvedMonoZbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsL==2);
}
bool BitsLoader::passResolvedMonoZbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsT==1);
}
bool BitsLoader::passResolvedMonoZbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsT==0);
}
bool BitsLoader::passResolvedMonoZbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105);
}
bool BitsLoader::passResolvedMonoTopSR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (nbjetsM==1) & (vTop.M() < 250);
}
bool BitsLoader::passResolvedMonoTopTopCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() < 250) & (nbjetsM==1);
}
bool BitsLoader::passResolvedMonoTopWCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() >= 250);
}
bool BitsLoader::passResolvedMonoTopZCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() < 250);
}
bool BitsLoader::passSelection(string preselection, string selection, string subsample, string combo, float &btagw){
  bool lPass = false;	
  btagw = 1;
  if (selection == "BstMonoTop")
    {
      if (subsample == "SR" && passBoostedMonoTopSR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0; lPass = true;}

      if (subsample == "TopCR" && passBoostedMonoTopTopCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1; lPass = true;}
      if (subsample == "minusTau32" && passBoostedMonoTopTopCRminusTau32(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1; lPass = true;}
      if (subsample == "minusMass" && passBoostedMonoTopTopCRminusMass(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1; lPass = true;}
      if (subsample == "minusBtag" && passBoostedMonoTopTopCRminusBtag(preselection)
          && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL1; lPass = true;}

      if (subsample == "WCR" && passBoostedMonoTopWCR(preselection) 
       	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0; lPass = true;}
      if (subsample == "WHFCR" && passBoostedMonoTopWHFCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwM1; lPass = true;}
      if (subsample == "WLFCR" && passBoostedMonoTopWLFCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwM0; lPass = true;}

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
double BitsLoader::getWgt(bool isData, TString algo, double LUMI, float btagw){
  float wgt = 1;
  if(!isData) {     
    wgt *= LUMI*scale1fb*nloKfactor*ewkCorr*btagw*triggerEff*evtWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
float BitsLoader::transverse_mass(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_mt; 
  else if(selection == "BstMonoZbb") return bst_mt;
  else return bst_mt;
}
float BitsLoader::fjet_mass(string selection){
  return bst_jet0_msd;
}
float BitsLoader::nsubjet(string selection){
  if(selection == "BstMonoTop" || selection == "ResMonoTop") return bst_jet0_tau32;
  else if(selection == "BstMonoHbb" || selection == "ResMonoHbb") return bst_jet0_tau21;
  else return bst_jet0_tau21;
}
float BitsLoader::btag(string selection){
  return bst_jet0_maxsubcsv;
}
float BitsLoader::chf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_CHF;
  else if(selection == "BstMonoZHbb") return bst_jet0_CHF;
  else return res_jet0_CHF; 
}
float BitsLoader::nhf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_NHF;
  else if(selection == "BstMonoZHbb") return bst_jet0_NHF;
  else return res_jet0_NHF;
}
float BitsLoader::nemf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_NEMF;
  else if(selection == "BstMonoZHbb") return bst_jet0_NEMF;
  else return res_jet0_NEMF;
}
float BitsLoader::genvpt(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_genVpt;
  else if (selection == "BstMonoZHbb") return bst_genVpt;
  else return res_genVpt;
}
float BitsLoader::genvphi(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_genVphi;
  else if (selection == "BstMonoZHbb") return bst_genVphi;
  else return res_genVphi;
}
