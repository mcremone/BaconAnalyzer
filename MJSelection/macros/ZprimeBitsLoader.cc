#include "MonoXBitsLoader.hh"  
using namespace std;

ZprimeBitsLoader::ZprimeBitsLoader(TTree *iTree,TString jet, TString algo,TString syst, string preselection) {
  if(iTree){
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
    iTree->SetBranchAddress("n"+algo+"jets",                     &njets);
    iTree->SetBranchAddress("nfbst"+jet+"_"+algo+"jet",            &nf15jets);
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
  }
}
ZprimeBitsLoader::~ZprimeBitsLoader(){}
bool ZprimeBitsLoader::selectJetAlgoAndSize(string selection, TString algo){
  bool lPass = false;
  // std::cout << nfjets << std::endl;
  if(nfjets > 0 && selection.find("Bst")==0 && selection.compare("BstMonoZbb")!=0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kBOOSTED15CHS) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")!=0 && algo=="CHS") lPass = true;
  else if((selectBits & kBOOSTED8PUPPI) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")==0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kBOOSTED8CHS) && selection.find("Bst")==0 && selection.compare("BstMonoZbb")==0 && algo=="CHS") lPass = true;
  else if((selectBits & kRESOLVEDPUPPI) && selection.find("Res")==0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kRESOLVEDCHS) && selection.find("Res")==0 && algo=="CHS") lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isHad(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isMuo(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==1 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isZmm(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==2 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isEle(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==1 && npho==0 && ntau==0 && vmetpt>50 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isZee(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==2 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isPho(){
  bool lPass = false;
  if((triggerBits & kSinglePhoton) && nmu==0 && nele==0 && npho==1 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::passPreSelection(string preselection){
  bool lPass = false;
  if(preselection.compare("Had")==0 && isHad()) lPass = true;
  if(preselection.compare("Muo")==0 && isMuo()) lPass = true;
  if(preselection.compare("Zmm")==0 && isZmm()) lPass = true;
  if(preselection.compare("Ele")==0 && isEle()) lPass = true;
  if(preselection.compare("Zee")==0 && isZee()) lPass = true;
  if(preselection.compare("Pho")==0 && isPho()) lPass = true;
  return lPass;
}
TLorentzVector ZprimeBitsLoader::getMET(string preselection){
  TLorentzVector v;
  v.SetPtEtaPhiM(vfakemetpt,0,vfakemetphi,0);
  if(preselection.compare("Had")==0){v.SetPtEtaPhiM(vmetpt,0,vmetphi,0);};
  return v;
}
TLorentzVector ZprimeBitsLoader::getTop(){
  TLorentzVector v;
  v.SetPtEtaPhiM(res_jet0_pt+res_jet1_pt+res_jet2_pt,res_jet0_eta+res_jet1_eta+res_jet2_eta,res_jet0_phi+res_jet1_phi+res_jet2_phi,res_jet0_mass+res_jet1_mass+res_jet2_mass);
  return v;
}
bool ZprimeBitsLoader::passBoostedMonoTopPreselection(string preselection){
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
bool ZprimeBitsLoader::passBoosted15MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>1.1 &&
     // bst15_jet0_msd>40 &&
     nfjets==1 && bst_jet0_pt>250) lPass=true;// && 
     // bst_jet0_CHF>0.4 && bst_jet0_NHF<0.26 && bst_jet0_NEMF<0.57) lPass=true;
  return lPass;
}
bool ZprimeBitsLoader::passBoosted8MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>0.7 &&
     // bst_jet0_msd>40 &&
     // nfjets==1 &&
     bst_jet0_pt>250) lPass=true;
  return lPass;
}
bool ZprimeBitsLoader::passResolvedMonoTop(string preselection){
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
bool ZprimeBitsLoader::passResolvedMonoXbb(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt() > 200 &&
     min_dphijetsmet>0.7 &&
     njets>=2 &&
     res_jet0_pt>30 && res_jet1_pt>30) lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::passBoostedMonoTopSR(string preselection){ 
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66);// & (nbjetsM>0); 
  return passBoostedMonoTopPreselection(preselection) //& (min_dphijetsmet>1.1) 
    & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool ZprimeBitsLoader::passBoostedMonoTopZnunuHFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsL>0) & (nbjetsM==0);
}
bool ZprimeBitsLoader::passBoostedMonoTopZnunuLFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsL==0);// & (bst_jet0_minsubcsv<=0.605);
}
bool ZprimeBitsLoader::passBoostedMonoTopTopCR(string preselection){ 
  //  TLorentzVector vMET = getMET(preselection);
  //  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78)& (bst_jet0_maxsubcsv>0.89) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM>0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM>0) & (nbjetsT==1); 
  //  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsT>0);
  //  return (vMET.Pt()>250) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66) & (nbjetsM>0);
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2>0);
}
bool ZprimeBitsLoader::passBoostedMonoTopTopCRminusTau32(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	  nf15jets==1 && bst_jet0_pt>250 &&
	  bst_jet0_msd>110 && bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool ZprimeBitsLoader::passBoostedMonoTopTopCRminusMass(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	  nf15jets==1 && bst_jet0_pt>250 &&
	  bst_jet0_tau32<0.61 && bst_jet0_msd>40) & (bst_jet0_maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool ZprimeBitsLoader::passBoostedMonoTopTopCRminusBtag(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (nbjetsLdR2>0);
}
bool ZprimeBitsLoader::passBoostedMonoTopWCR(string preselection){
  // TLorentzVector vMET = getMET(preselection);
  // return (vMET.Pt()>250) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66) & (nbjetsM==0);
  //  return (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (bst_jet0_maxsubcsv<=0.89);
  return passBoostedMonoTopPreselection(preselection) & (bst_jet0_maxsubcsv<0.76) & (nbjetsLdR2==0);
}
bool ZprimeBitsLoader::passBoostedMonoTopWHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78)& (bst_jet0_maxsubcsv>0.605) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM==0); 
  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM>0) & (nbjetsT==0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsT==1) & (nbjetsM==0);
}
bool ZprimeBitsLoader::passBoostedMonoTopWLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_tau32<0.78)& (bst_jet0_maxsubcsv<=0.605) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM==0);
  return (vMET.Pt()>250) & (bst_jet0_tau32<0.78) & (bst_jet0_msd>150) & (bst_jet0_msd<250) & (nbjetsM==0);  
}
bool ZprimeBitsLoader::passBoostedMonoTopZCR(string preselection){
  //  return passBoosted15MonoX(preselection) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78);
  // TLorentzVector vMET = getMET(preselection);
  // return (vMET.Pt()>250) & (bst_jet0_tau32<0.69) & (bst_jet0_msd>110) & (bst_jet0_msd<210) & (bst_jet0_maxsubcsv>0.66);
  return passBoostedMonoTopPreselection(preselection);
}
bool ZprimeBitsLoader::passBoostedMonoTopZHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (nbjetsM>0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (bst_jet0_maxsubcsv>0.89);
}
bool ZprimeBitsLoader::passBoostedMonoTopZLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (nbjetsM==0);
  //  return passBoosted15MonoX(preselection) & (bst_jet0_msd>150) & (bst_jet0_msd<240) & (bst_jet0_tau32<0.78) & (bst_jet0_maxsubcsv<=0.89);
}
bool ZprimeBitsLoader::passBoostedMonoHbbSR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool ZprimeBitsLoader::passBoostedMonoHbbTopCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool ZprimeBitsLoader::passBoostedMonoHbbWCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv<=0.605);
}
bool ZprimeBitsLoader::passBoostedMonoHbbZCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst_jet0_msd>105) & (bst_jet0_msd<150) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35));
}
bool ZprimeBitsLoader::passBoostedMonoZbbSR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool ZprimeBitsLoader::passBoostedMonoZbbTopCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv>0.605);
}
bool ZprimeBitsLoader::passBoostedMonoZbbWCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35)) & (bst_jet0_minsubcsv<=0.605);
}
bool ZprimeBitsLoader::passBoostedMonoZbbZCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst_jet0_msd>60) & (bst_jet0_msd<105) & (bst_jet0_tau21<(-0.07*bst_jet0_rho+0.35));
}	
bool ZprimeBitsLoader::passResolvedMonoHbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsM==2);
}
bool ZprimeBitsLoader::passResolvedMonoHbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsT==1);
}
bool ZprimeBitsLoader::passResolvedMonoHbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150) & (nbjetsT==0) & (nbjetsM==2);
}
bool ZprimeBitsLoader::passResolvedMonoHbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 105) & (res_jet0_mass < 150);
}
bool ZprimeBitsLoader::passResolvedMonoZbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsL==2);
}
bool ZprimeBitsLoader::passResolvedMonoZbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsT==1);
}
bool ZprimeBitsLoader::passResolvedMonoZbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105) & (nbjetsT==0);
}
bool ZprimeBitsLoader::passResolvedMonoZbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jet0_mass > 60) & (res_jet0_mass < 105);
}
bool ZprimeBitsLoader::passResolvedMonoTopSR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (nbjetsM==1) & (vTop.M() < 250);
}
bool ZprimeBitsLoader::passResolvedMonoTopTopCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() < 250) & (nbjetsM==1);
}
bool ZprimeBitsLoader::passResolvedMonoTopWCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() >= 250);
}
bool ZprimeBitsLoader::passResolvedMonoTopZCR(string preselection){
  TLorentzVector vTop = getTop();
  return passResolvedMonoTop(preselection) & (vTop.M() < 250);
}
bool ZprimeBitsLoader::passSelection(string preselection, string selection, string subsample, string combo, float &btagw){
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
double ZprimeBitsLoader::getWgt(bool isData, TString algo, double LUMI, float btagw){
  float wgt = 1;
  if(!isData) {     
    wgt *= LUMI*scale1fb*kfactor*btagw*triggerEff*evtWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
// float ZprimeBitsLoader::transverse_mass(string selection){
//   if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_mt; 
//   else if(selection == "BstMonoZbb") return bst_mt;
//   else return bst_mt;
// }
float ZprimeBitsLoader::fjet_mass(string selection){
  return bst_jet0_msd;
}
float ZprimeBitsLoader::nsubjet(string selection){
  if(selection == "BstMonoTop" || selection == "ResMonoTop") return bst_jet0_tau32;
  else if(selection == "BstMonoHbb" || selection == "ResMonoHbb") return bst_jet0_tau21;
  else return bst_jet0_tau21;
}
float ZprimeBitsLoader::btag(string selection){
  return bst_jet0_maxsubcsv;
}
float ZprimeBitsLoader::chf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_CHF;
  else if(selection == "BstMonoZHbb") return bst_jet0_CHF;
  else return res_jet0_CHF; 
}
float ZprimeBitsLoader::nhf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_NHF;
  else if(selection == "BstMonoZHbb") return bst_jet0_NHF;
  else return res_jet0_NHF;
}
float ZprimeBitsLoader::nemf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_jet0_NEMF;
  else if(selection == "BstMonoZHbb") return bst_jet0_NEMF;
  else return res_jet0_NEMF;
}
float ZprimeBitsLoader::genvpt(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_genVpt;
  else if (selection == "BstMonoZHbb") return bst_genVpt;
  else return res_genVpt;
}
float ZprimeBitsLoader::genvphi(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst_genVphi;
  else if (selection == "BstMonoZHbb") return bst_genVphi;
  else return res_genVphi;
}
