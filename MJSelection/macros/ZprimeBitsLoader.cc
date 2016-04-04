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
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_rho",       &bst_jet0_rho);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_phil",      &bst_jet0_phil);
    iTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_tau21",     &bst_jet0_tau21);
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
  if((selectBits & kBOOSTED8) && selection.find("Bst")==0 && selection.compare("BstZprime")==0 && algo=="PUPPI") lPass = true;
  else if((selectBits & kBOOSTED8) && selection.find("Bst")==0 && selection.compare("BstZprime")==0 && algo=="CHS") lPass = true;
  return lPass;
}

bool ZprimeBitsLoader::passBoostedPreselection(string preselection){
  bool lPass = false;
  if(nfjets>0) lPass=true;
  return lPass;
}
bool ZprimeBitsLoader::passBoostedSelection(string preselection){
  return passBoostedPreselection(preselection) & nf8jets>0 & bst8_jet1pt>400;
}
bool ZprimeBitsLoader::passSelection(string preselection, string selection, string subsample, string combo){
  bool lPass = false;	
  if (subsample == "SR" && passBoostedSelection(preselection) && (combo=="ONLY" || combo=="COMBO")) {lPass = true;}
  return lPass;
}
double ZprimeBitsLoader::getWgt(bool isData, TString algo, double LUMI){
  float wgt = 1;
  if(!isData) {     
    wgt *= LUMI*scale1fb*triggerEff*evtWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
float ZprimeBitsLoader::fjet_mass(string selection){
  return bst_jet0_msd;
}
float ZprimeBitsLoader::nsubjet(string selection){
  return bst_jet0_tau21;
}
float ZprimeBitsLoader::btag(string selection){
  return bst_jet0_maxsubcsv;
}
