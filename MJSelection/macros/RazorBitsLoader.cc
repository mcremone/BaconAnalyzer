#include "RazorBitsLoader.hh"  
#include "BTagWeightCalculation.hh"
using namespace std;

RazorBitsLoader::RazorBitsLoader(TTree *iTree,TString algo,TString syst, string preselection) {
  syst="CENT";
  if(iTree){
    TString met = "puppet"; if (algo!="PUPPI") met = "pfmet";
    if(preselection.compare("Had")==0 || preselection.compare("MET")==0){
      iTree->SetBranchAddress("mindPhi",                             &min_dphijetsmet);
    }
    else{
      iTree->SetBranchAddress("mindPhi",                            &min_dphijetsmet);
    }
    iTree->SetBranchAddress("runNum",                            &runNum);
    iTree->SetBranchAddress("lumiSec",                           &lumiSec);
    iTree->SetBranchAddress("evtNum",                            &evtNum);
    iTree->SetBranchAddress("metfilter",                         &metfilter);
    iTree->SetBranchAddress("triggerBits",                       &triggerBits);
    iTree->SetBranchAddress("selectBits",                        &selectBits);
//    iTree->SetBranchAddress("triggerEff",                        &triggerEff);
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
    iTree->SetBranchAddress("res_"+algo+"jets",                     &njets);
    iTree->SetBranchAddress("res_"+algo+"jetsbtagL",                   &nbjetsL);
    iTree->SetBranchAddress("res_"+algo+"jetsbtagM",                   &nbjetsM);
    iTree->SetBranchAddress("res_"+algo+"jetsbtagT",                   &nbjetsT);
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
    /*
    iTree->SetBranchAddress("res_"+algo+"jet0_mass",             &res_jet0_mass);
    iTree->SetBranchAddress("res_"+algo+"jet1_mass",             &res_jet1_mass);
    iTree->SetBranchAddress("res_"+algo+"jet2_mass",             &res_jet2_mass);
    iTree->SetBranchAddress("res_"+algo+"jet3_mass",             &res_jet3_mass);
    */
    iTree->SetBranchAddress("res_"+algo+"jet0_CHF",              &res_jet0_CHF);
    iTree->SetBranchAddress("res_"+algo+"jet0_NHF",              &res_jet0_NHF);
    iTree->SetBranchAddress("res_"+algo+"jet0_NEMF",             &res_jet0_NEMF);
    iTree->SetBranchAddress("res_"+algo+"jet0_HadFlavor",             &res_jet0_HadFlavor);
    iTree->SetBranchAddress("res_"+algo+"jet1_HadFlavor",             &res_jet1_HadFlavor);
    iTree->SetBranchAddress("res_"+algo+"jet2_HadFlavor",             &res_jet2_HadFlavor);
    iTree->SetBranchAddress("res_"+algo+"jet3_HadFlavor",             &res_jet3_HadFlavor);
    /*
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
    */
    iTree->SetBranchAddress("res_"+algo+"jetsAbove80GeV",                            &nJetsAbove80GeV);
    iTree->SetBranchAddress("res_"+algo+"jetMR",                                &MR);
    iTree->SetBranchAddress("res_"+algo+"jetRsq",                               &Rsq);
    iTree->SetBranchAddress("res_"+algo+"jetdeltaPhi",                          &deltaPhi);
    iTree->SetBranchAddress("res_"+algo+"jetHT",                                &HT);
    iTree->SetBranchAddress("res_"+algo+"jetMHT",                               &MHT);
  }
}
RazorBitsLoader::~RazorBitsLoader(){}
bool RazorBitsLoader::selectJetAlgoAndSize(TString algo){
  bool lPass = false;
    if((selectBits & kRESOLVEDPUPPI) && algo=="PUPPI") lPass = true;
    if((selectBits & kRESOLVEDCHS) && algo=="CHS") lPass = true;
  return lPass;
}
bool RazorBitsLoader::isHad(){
  bool lPass = false;
  //  if((triggerBits & kHad) && nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true;
   // if (nmu==0 && nele==0 && npho==0 && ntau==0) 
   lPass = true; 
  return lPass;
}
bool RazorBitsLoader::isMET(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==0 && nele==0 && npho==0 && ntau==0) lPass = true;
  return lPass;
}
bool RazorBitsLoader::isMuo(){
  bool lPass = false;
  if((triggerBits & kSingleMuon) && nmu==1 && nele==0 && npho==0 && ntau==0) lPass = true;
  return lPass;
}
bool RazorBitsLoader::isZmm(){
  bool lPass = false;
  if((triggerBits & kSingleMuon) && nmu==2 && nele==0 && npho==0 && ntau==0) lPass = true;
  return lPass;
}
bool RazorBitsLoader::isEle(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==1 && npho==0 && ntau==0 && vmetpt>50) lPass = true;
  return lPass;
}
bool RazorBitsLoader::isZee(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==2 && npho==0 && ntau==0) lPass = true;
  return lPass;
}
bool RazorBitsLoader::isPho(){
  bool lPass = false;
  if((triggerBits & kSinglePhoton) && nmu==0 && nele==0 && npho==1 && ntau==0) lPass = true;
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

bool RazorBitsLoader::passMonojetSelection()
{
    //(met > 200)*(j0_pt > 100)*(nbtags == 0)*(j0_chf > 0.1 && j0_nhf < 0.8)*(trigger > 0)*(mindphi > 0.5)*(metFiltersWord ==0)
    bool lPass = false;
    if (vmetpt > 200 && 
            res_jet0_pt > 100 && 
            nbjetsL == 0 && 
            res_jet0_CHF > 0.1 && 
            res_jet0_NHF < 0.8  &&
            min_dphijetsmet > 0.5 &&
            metfilter == 0)
    lPass = true;
    return lPass;
    // TODO: need to understand what trigger Phil use that > 0.
}
bool RazorBitsLoader::passRazorPreselection(bool isData){
  bool lPass = false;
       if (isData &&
          (triggerBits & kRazor) && 
          MR > 200. && 
          Rsq > 0.35 && 
          nJetsAbove80GeV > 1 && 
          deltaPhi < 2.5) lPass = true;
       else if  (!isData &&
  //        MR > 200. && 
    //      Rsq > 0.35 && 
          nJetsAbove80GeV > 1 && 
          deltaPhi < 2.5) 
          lPass = true;
  return lPass;
}
bool RazorBitsLoader::passRazorCR(string preselection, bool isData){ 
  return passPreSelection(preselection) & passRazorPreselection(isData) & (nbjetsL == 0); // temporary
}
bool RazorBitsLoader::passRazorSR(string preselection, bool isData){ 
  return passPreSelection(preselection) & passRazorPreselection(isData) & (nbjetsL == 0); 
}
bool RazorBitsLoader::passSelection(string preselection, string subsample, string combo, bool isData){
  bool lPass = false;	
  if (subsample == "SR" && passRazorSR(preselection, isData) 
      && (combo=="ONLY" || (combo=="COMBO" && !passRazorSR(preselection, isData)))) lPass = true;
  if (subsample == "CR" && passRazorCR(preselection, isData) 
      && (combo=="ONLY" || (combo=="COMBO" && !passRazorCR(preselection, isData)))) lPass = true;
  return lPass;
}


double RazorBitsLoader::getWgt(bool isData, TString algo, double LUMI){
  float wgt = 1;
  if(!isData) {
    std::vector<double> jetPt, jetEta, jetFlavor;
    jetPt.push_back(res_jet0_pt);
    jetEta.push_back(res_jet0_eta);
    jetFlavor.push_back(res_jet0_HadFlavor);
    jetPt.push_back(res_jet1_pt);
    jetEta.push_back(res_jet1_eta);
    jetFlavor.push_back(res_jet1_HadFlavor);
    jetPt.push_back(res_jet2_pt);
    jetEta.push_back(res_jet2_eta);
    jetFlavor.push_back(res_jet2_HadFlavor);
    jetPt.push_back(res_jet3_pt);
    jetEta.push_back(res_jet3_eta);
    jetFlavor.push_back(res_jet3_HadFlavor);
    //wgt *= LUMI*scale1fb*kfactor*res_btagwL0*triggerEff*evtWeight;
    std::string wp = "L"; 
    std::string variationType, flavor;
    if (syst.compare("CENT")==0)  variationType = "central"; 
    else {
            if (syst.find("UP")!=std::string::npos) variationType = "up";
            if (syst.find("DO")!=std::string::npos) variationType = "down";
            if (syst.find("BTAG")!=std::string::npos) flavor = "Bs";
            if (syst.find("MISTAG")!=std::string::npos) flavor = "Ms";
         }

    std::vector<double> SFv = SFCalculation(flavor, btagScaleFactorFilename, variationType, wp, jetPt, jetEta, jetFlavor);    
    
    double btagW = getBTagEventReweight(NminBjets, jetPt, jetEta, jetFlavor, SFv);

    wgt *= LUMI*scale1fb*kfactor*btagW*evtWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
