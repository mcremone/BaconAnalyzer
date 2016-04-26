#include "ZprimeBitsLoader.hh"  
using namespace std;

ZprimeBitsLoader::ZprimeBitsLoader(TTree *iTree,TString algo) {
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
    iTree->SetBranchAddress("bst8_"+algo+"jets",                 &njets);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_pt",        &bst_jet0_pt);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_eta",       &bst_jet0_eta);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_phi",       &bst_jet0_phi);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_mass",      &bst_jet0_mass);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_msd",       &bst_jet0_msd);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_rho",       &bst_jet0_rho);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_phil",      &bst_jet0_phil);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_tau21",     &bst_jet0_tau21);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_CHF",       &bst_jet0_CHF);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_NHF",       &bst_jet0_NHF);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_NEFM",      &bst_jet0_NEMF);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_minsubcsv", &bst_jet0_minsubcsv);
    iTree->SetBranchAddress("bst8_"+algo+"jet0_maxsubcsv", &bst_jet0_maxsubcsv);
  }
}
ZprimeBitsLoader::~ZprimeBitsLoader(){}
bool ZprimeBitsLoader::selectJetAlgoAndSize(TString algo){
  bool lPass = false;
  if((selectBits & kBOOSTED8PUPPI) && algo=="PUPPI") lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::passBoostedZprimePreselection(){
  return njets>0 & bst_jet0_pt>500;  
}
bool ZprimeBitsLoader::passBoostedZprimeSR(){
  return passBoostedZprimePreselection() & (bst_jet0_tau21 < (-0.063*bst_jet0_rho + RHO_CUT));
}
bool ZprimeBitsLoader::passSelection(string selection){
  bool lPass = false;	
  if (selection.find("PreSel")==0 && passBoostedZprimePreselection()) {lPass = true;}
  if (selection.find("SR")==0 && passBoostedZprimeSR()) {lPass = true;}
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
