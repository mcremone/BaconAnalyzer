#include "../macros/ZprimeBitsLoader.hh"  
using namespace std;

ZprimeBitsLoader::ZprimeBitsLoader(TTree *iTree,TString algo,TString jet,TString number) {
  if(iTree){
    TString met = "puppet"; if (algo!="PUPPI") met = "pfmet";
    iTree->SetBranchAddress("runNum",                            &runNum);
    iTree->SetBranchAddress("lumiSec",                           &lumiSec);
    iTree->SetBranchAddress("evtNum",                            &evtNum);
    iTree->SetBranchAddress("metfilter",                         &metfilter);
    iTree->SetBranchAddress("triggerBits",                       &triggerBits);
    iTree->SetBranchAddress("selectBits",                        &selectBits);
    iTree->SetBranchAddress("triggerEff",                        &triggerEff);
    iTree->SetBranchAddress("npu",                               &npu);
    iTree->SetBranchAddress("npv",                               &npv);
    iTree->SetBranchAddress("nmu",                               &nmu);
    iTree->SetBranchAddress("nele",                              &nele);
    iTree->SetBranchAddress("ntau",                              &ntau);
    iTree->SetBranchAddress("npho",                              &npho);
    iTree->SetBranchAddress("puWeight",                          &puWeight);
    iTree->SetBranchAddress("scale1fb",                          &scale1fb);
    iTree->SetBranchAddress("evtWeight",                         &evtWeight);
    iTree->SetBranchAddress(met,                                 &vmetpt);
    iTree->SetBranchAddress(met+"phi",                           &vmetphi);
    iTree->SetBranchAddress("fake"+met,                          &vfakemetpt);
    iTree->SetBranchAddress("fake"+met+"phi",                    &vfakemetphi);
    iTree->SetBranchAddress("bst"+number+"_"+algo+"jets",                 &njets);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_pt",              &bst_jet0_pt);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_eta",             &bst_jet0_eta);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_phi",             &bst_jet0_phi);
    //iTree->SetBranchAddress("bst8_"+algo+jet+"_mass",           &bst_jet0_mass);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_msd",             &bst_jet0_msd);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_rho",             &bst_jet0_rho);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_phil",            &bst_jet0_phil);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_tau21",           &bst_jet0_tau21);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_CHF",             &bst_jet0_CHF);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_NHF",             &bst_jet0_NHF);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_NEMF",            &bst_jet0_NEMF);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_doublecsv",       &bst_jet0_doublecsv);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_minsubcsv",       &bst_jet0_minsubcsv);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_maxsubcsv",       &bst_jet0_maxsubcsv);
  }
}
ZprimeBitsLoader::~ZprimeBitsLoader(){}
bool ZprimeBitsLoader::selectJetAlgoAndSize(TString algo){
  bool lPass = false;
  if((selectBits & kBOOSTED8PUPPI) && algo=="PUPPI") lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isPho(bool isData){
  bool lPass = false;
  if (nmu==0 && nele==0 && npho==1 && ntau==0){
   if(isData){
    if((triggerBits & kSinglePhoton) ) lPass = true;}
   else{
    lPass = true;}
 }
 return lPass;
}
bool ZprimeBitsLoader::isHad(bool isData){
  bool lPass = false;
    if(nmu==0 && nele==0 && npho==0 && ntau==0 && met>175){
      if(isData){
        if((triggerBits & kMET)!=0) lPass = true;
      }
      else{
      lPass = true;
      }
    }
   return lPass;
}

bool ZprimeBitsLoader::passBoostedZprimePreselection(){
  //if((bst_jet0_msd>60) && (bst_jet0_msd<100)){ 
   return njets>0 & bst_jet0_pt>500;
  //  //else {return false;}
    }

bool ZprimeBitsLoader::passPreSelection(string preselection, bool isData){
  bool lPass = false;
  if(preselection.compare("Had")==0 && isHad(isData)) lPass = true;
  if(preselection.compare("Pho")==0 && isPho(isData)) lPass = true;
  return lPass;
}

bool ZprimeBitsLoader::passBoostedGammaZprimePreselection(){
  //if((bst_jet0_msd>60) && (bst_jet0_msd<100)){ 
 return njets>0 & bst_jet0_pt>175;
 //else {return false;}
}

bool ZprimeBitsLoader::passBoostedGammaZprimeSR(float ddtcut){
  
  return passBoostedGammaZprimePreselection() & (bst_jet0_tau21 < (-0.063*bst_jet0_rho + ddtcut));
}



bool ZprimeBitsLoader::passBoostedZprimeSR(float ddtcut){
  
  return passBoostedZprimePreselection() & (bst_jet0_tau21 < (-0.063*bst_jet0_rho + ddtcut));
}
bool ZprimeBitsLoader::passBoostedZprimeBTag(float csvcut){
  return passBoostedZprimePreselection() & (bst_jet0_doublecsv > csvcut);
}
bool ZprimeBitsLoader::passSelection(bool isData,string selection,float ddt,float csv1){
  bool lPass = false;	
  if (selection.compare("Pho")==0 && isPho(isData)) lPass = true;
  if (selection.find("PreSel")==0 && passBoostedZprimePreselection()){ lPass = true;}
  if (selection.find("Sr")==0 && passBoostedZprimeSR(ddt)) {lPass = true;}
  if (selection.find("B")==0 && passBoostedZprimeBTag(csv1)) {lPass = true;}
  if (selection.find("SRB")==0)
     {   
       if (passBoostedZprimeSR(ddt) && passBoostedZprimeBTag(csv1)) {lPass = true;}
     }
  return lPass;
}
double ZprimeBitsLoader::getWgt(bool isData, TString algo, double LUMI){
  float wgt = 1;
  if(!isData) {     
    wgt *= LUMI*scale1fb*evtWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
double ZprimeBitsLoader::tau21DDT(){
  return bst_jet0_tau21 + 0.063*bst_jet0_rho;
}
