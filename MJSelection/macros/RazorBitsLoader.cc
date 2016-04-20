#include "RazorBitsLoader.hh"  
using namespace std;

RazorBitsLoader::RazorBitsLoader(TTree *iTree,TString algo,TString syst, string preselection) {
  if(iTree){
    TString met = "puppet"; if (algo!="PUPPI") met = "pfmet";
    if(preselection.compare("Had")==0){
      iTree->SetBranchAddress("mindPhi",                             &min_dphijetsmet);
    }
    else{
      iTree->SetBranchAddress("mindFPhi",                            &min_dphijetsmet);
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
    iTree->SetBranchAddress("kfactor",                           &kfactor);
    iTree->SetBranchAddress(met,                                 &vmetpt);
    iTree->SetBranchAddress(met+"phi",                           &vmetphi);
    iTree->SetBranchAddress("fake"+met,                          &vfakemetpt);
    iTree->SetBranchAddress("fake"+met+"phi",                    &vfakemetphi);
    iTree->SetBranchAddress("n"+algo+"jets",                     &njets);
    iTree->SetBranchAddress("nbtags"                             &nbtags);
    iTree->SetBranchAddress("nb"+algo+"jetsL",                   &nbjetsL);
    iTree->SetBranchAddress("nb"+algo+"jetsM",                   &nbjetsM);
    iTree->SetBranchAddress("nb"+algo+"jetsLdR2",                &nbjetsLdR2);
    iTree->SetBranchAddress("nb"+algo+"jetsT",                   &nbjetsT);
    iTree->SetBranchAddress("res_"+algo+"jetmT",                 &res_mt);
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
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL0_"+syst,      &res_btagwL0);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL1_"+syst,      &res_btagwL1);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwLminus1_"+syst, &res_btagwLminus1);
    iTree->SetBranchAddress("res_"+algo+"jetbtagwL2_"+syst,      &res_btagwL2);
    iTree->SetBranchAddress("nmu",                               &nmu);
    iTree->SetBranchAddress("nele",                              &nele);
    iTree->SetBranchAddress("ntau",                              &ntau);
    iTree->SetBranchAddress("npho",                              &npho);
    iTree->SetBranchAddress("eleSF0",                            &eleSF0);
    iTree->SetBranchAddress("eleSF1",                            &eleSF1);
    iTree->SetBranchAddress("eleSF2",                            &eleSF2);
    iTree->SetBranchAddress("muoSF0",                            &muoSF0);
    iTree->SetBranchAddress("muoSF1",                            &muoSF1);
    iTree->SetBranchAddress("muoSF2",                            &muoSF2);
    iTree->SetBranchAddress("alphaT",                            &alphaT);
    iTree->SetBranchAddress("mindFPhi",                          &dPhiMin);
    iTree->SetBranchAddress("MR",                                &MR);
    iTree->SetBranchAddress("Rsq",                               &Rsq);
    iTree->SetBranchAddress("deltaPhi",                          &deltaPhi);
    iTree->SetBranchAddress("HT",                                &HT);
    iTree->SetBranchAddress("MHT",                               &MHT);
  }
}
RazorBitsLoader::~RazorBitsLoader(){}
bool RazorBitsLoader::selectJetAlgoAndSize(string selection, TString algo){
  bool lPass = false;
  if((selectBits & kRESOLVEDPUPPI) && selection.find("Res")==0 && algo=="PUPPI") lPass = true;
  return lPass;
}
bool RazorBitsLoader::isHad(){
  bool lPass = false;
  //  if((triggerBits & kHad) && nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true;
  if nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true; 
  return lPass;
}
bool RazorBitsLoader::isMET(){
  bool lPass = false;
  //  if((triggerBits & kMET) && nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true;
  if nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true; 
  return lPass;
}
bool RazorBitsLoader::isMuo(){
  bool lPass = false;
  //  if((triggerBits & kSingleMuon) && nmu==1 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  if nmu==1 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;   
  return lPass;
}
bool RazorBitsLoader::isZmm(){
  bool lPass = false;
  //  if((triggerBits & kSingleMuon) && nmu==2 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  if nmu==2 && nele==0 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool RazorBitsLoader::isEle(){
  bool lPass = false;
  //  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==1 && npho==0 && ntau==0 && vmetpt>50 && (vfakemetpt!=0)) lPass = true;
  if nmu==0 && nele==1 && npho==0 && ntau==0 && vmetpt>50 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool RazorBitsLoader::isZee(){
  bool lPass = false;
  //  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==2 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  if nmu==0 && nele==2 && npho==0 && ntau==0 && (vfakemetpt!=0)) lPass = true; 
  return lPass;
}
bool RazorBitsLoader::isPho(){
  bool lPass = false;
  //  if((triggerBits & kSinglePhoton) && nmu==0 && nele==0 && npho==1 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  if nmu==0 && nele==0 && npho==1 && ntau==0 && (vfakemetpt!=0)) lPass = true;
  return lPass;
}
bool RazorBitsLoader::passPreSelection(string preselection){
  bool lPass = false;
  if(preselection.compare("Had")==0 && isHad()) lPass = true;
  if(preselection.compare("MET")==0 && isMET()) lPass = true;
  if(preselection.compare("Muo")==0 && isMuo()) lPass = true;
  if(preselection.compare("Zmm")==0 && isZmm()) lPass = true;
  if(preselection.compare("Ele")==0 && isEle()) lPass = true;
  if(preselection.compare("Zee")==0 && isZee()) lPass = true;
  if(preselection.compare("Pho")==0 && isPho()) lPass = true;
  return lPass;
}
bool RazorBitsLoader::passRazorPreselection(){
  bool lPass = false;
  return lPass;
}
bool RazorBitsLoader::passRazorSR(){ 
  return passRazorPreselection();
}
bool RazorBitsLoader::passSelection(string preselection, string subsample, string combo){
  bool lPass = false;	
  if (subsample == "SR" && passBoostedMonoTopSR(preselection) 
      && (combo=="ONLY" || combo=="COMBO")) {btagw=res_btagwL0; lPass = true;}

  if (subsample == "QCDCR" && passBoostedMonoTopQCDCR(preselection)
      && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}

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
  return lPass;
}
double RazorBitsLoader::getWgt(bool isData, TString algo, double LUMI, float btagw){
  float wgt = 1;
  if(!isData) {     
    wgt *= LUMI*scale1fb*kfactor*res_btagwL0*triggerEff*evtWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
