// #include <TROOT.h>                    // access to gROOT, entry point to ROOT system
// #include <TSystem.h>                  // interface to OS
// #include <TStyle.h>                   // class to handle ROOT plotting styles
// #include <TFile.h>                    // file handle class
// #include <TTree.h>                    // class to access ntuples
// #include <TH1D.h>                     // 1D histogram class
// #include <TLorentzVector.h>           // 4-vector class
// #include <vector>                     // STL vector class
// #include <iostream>                   // standard I/O
// #include <iomanip>                    // functions to format standard I/O
// #include <fstream>                    // functions for file I/O
// #include <string>                     // C++ string class
// #include <cmath>                      // C++ math library
// #include <cassert>

// #include "../include/CPlot.hh"                   // helper class for plots
// #include "../include/KStyle.hh"                  // style settings for drawing
// #include "../include/CSample.hh"                 // helper class to manage samples
#include "BitsLoader.hh"  
using namespace std;

BitsLoader::BitsLoader(TTree *iTree,TString algo,TString syst, string preselection) {
  //MET definition
  if(iTree){
    TString met = "puppet"; if (algo!="PUPPI") met = "pfmet";
    if(preselection.compare("Had")==0) iTree->SetBranchAddress("min_dphijets"+met,      &min_dphijetsmet);
    if(preselection.compare("Had")!=0) iTree->SetBranchAddress("min_dphijetsfake"+met,      &min_dphijetsmet);
    iTree->SetBranchAddress("runNum",     &runNum);
    iTree->SetBranchAddress("lumiSec",    &lumiSec);
    iTree->SetBranchAddress("evtNum",     &evtNum);
    iTree->SetBranchAddress("metfilter",  &metfilter);
    iTree->SetBranchAddress("triggerBits",  &triggerBits);
    iTree->SetBranchAddress("selectBits",  &selectBits);
    iTree->SetBranchAddress("triggerEff",  &triggerEff);
    iTree->SetBranchAddress("evtWeight",  &evtWeight);
    iTree->SetBranchAddress("puWeight",  &puWeight);
    iTree->SetBranchAddress("lepWeight",  &lepWeight);
    iTree->SetBranchAddress("topSize",  &topSize);
    iTree->SetBranchAddress("npv",        &npv);
    iTree->SetBranchAddress("npu",        &npu);
    iTree->SetBranchAddress("nmu",        &nmu);
    iTree->SetBranchAddress("nele",        &nele);
    iTree->SetBranchAddress("ntau",        &ntau);
    iTree->SetBranchAddress("npho",        &npho);
    iTree->SetBranchAddress("n"+algo+"jets",      &njets);
    iTree->SetBranchAddress("nf15"+algo+"jets",      &nf15jets);
    iTree->SetBranchAddress("nf8"+algo+"jets",      &nf8jets);
    iTree->SetBranchAddress("nb"+algo+"jetsL",     &nbjetsL);
    iTree->SetBranchAddress("nb"+algo+"jetsM",     &nbjetsM);
    iTree->SetBranchAddress("nb"+algo+"jetsLdR2",     &nbjetsLdR2);
    iTree->SetBranchAddress("nb"+algo+"jetsT",     &nbjetsT);
    iTree->SetBranchAddress("scale1fb",   &scale1fb);
    iTree->SetBranchAddress("nloKfactor_CENT",   &nloKfactor);
    iTree->SetBranchAddress("ewkCorr_CENT",   &ewkCorr);
    iTree->SetBranchAddress("res_"+algo+"btagwL0_"+syst,  &res_btagwL0);
    iTree->SetBranchAddress("res_"+algo+"btagwL1_"+syst,  &res_btagwL1);
    iTree->SetBranchAddress("res_"+algo+"btagwLminus1_"+syst, &res_btagwLminus1);
    iTree->SetBranchAddress("res_"+algo+"btagwL2_"+syst,  &res_btagwL2);
    iTree->SetBranchAddress(met,      &vmet);
    iTree->SetBranchAddress("fake"+met,      &vfakemet);
    iTree->SetBranchAddress("bst15_"+algo+"jet1", &bst15_jet1);
    iTree->SetBranchAddress("bst15_"+algo+"jet1msd",   &bst15_jet1msd);
    iTree->SetBranchAddress("bst15_"+algo+"jet1tau32",   &bst15_jet1tau32);
    iTree->SetBranchAddress("bst15_"+algo+"jet1tau21",   &bst15_jet1tau21);
    iTree->SetBranchAddress("bst15_"+algo+"genVpt",     &bst15_genVpt);
    iTree->SetBranchAddress("bst15_"+algo+"genVphi",     &bst15_genVphi);
    iTree->SetBranchAddress("bst15_"+algo+"jet1rho",     &bst15_jet1rho);
    iTree->SetBranchAddress("bst15_"+algo+"jet1phil",     &bst15_jet1phil);
    iTree->SetBranchAddress("bst15_"+algo+"mt",     &bst15_mt);
    iTree->SetBranchAddress("bst15_"+algo+"jet1CHF",     &bst15_jet1CHF);
    iTree->SetBranchAddress("bst15_"+algo+"jet1NHF",     &bst15_jet1NHF);
    iTree->SetBranchAddress("bst15_"+algo+"jet1NEMF",     &bst15_jet1NEMF);
    iTree->SetBranchAddress("bst15_"+algo+"jet1minsubcsv",   &bst15_jet1minsubcsv);
    iTree->SetBranchAddress("bst15_"+algo+"jet1maxsubcsv",   &bst15_jet1maxsubcsv);
    iTree->SetBranchAddress("bst8_"+algo+"jet1", &bst8_jet1);
    iTree->SetBranchAddress("bst8_"+algo+"jet1msd",   &bst8_jet1msd);
    iTree->SetBranchAddress("bst8_"+algo+"jet1tau32",   &bst8_jet1tau32);
    iTree->SetBranchAddress("bst8_"+algo+"jet1tau21",   &bst8_jet1tau21);
    iTree->SetBranchAddress("bst8_"+algo+"genVpt",     &bst8_genVpt);
    iTree->SetBranchAddress("bst8_"+algo+"genVphi",     &bst8_genVphi);
    iTree->SetBranchAddress("bst8_"+algo+"jet1rho",     &bst8_jet1rho);
    iTree->SetBranchAddress("bst8_"+algo+"jet1phil",     &bst8_jet1phil);
    iTree->SetBranchAddress("bst8_"+algo+"mt",     &bst8_mt);
    iTree->SetBranchAddress("bst8_"+algo+"jet1CHF",     &bst8_jet1CHF);
    iTree->SetBranchAddress("bst8_"+algo+"jet1NHF",     &bst8_jet1NHF);
    iTree->SetBranchAddress("bst8_"+algo+"jet1NEMF",     &bst8_jet1NEMF);
    iTree->SetBranchAddress("bst8_"+algo+"jet1minsubcsv",   &bst8_jet1minsubcsv);
    //    iTree->SetBranchAddress("bst8_"+algo+"jet1maxsubcsv",   &bst8_jet1maxsubcsv);
    iTree->SetBranchAddress("res_"+algo+"jet1",         &res_jet1);
    iTree->SetBranchAddress("res_"+algo+"genVpt",     &res_genVpt);
    iTree->SetBranchAddress("res_"+algo+"genVphi",     &res_genVphi);
    iTree->SetBranchAddress("res_"+algo+"jet1CHF",     &res_jet1CHF);
    iTree->SetBranchAddress("res_"+algo+"jet1NHF",     &res_jet1NHF);
    iTree->SetBranchAddress("res_"+algo+"jet1NEMF",     &res_jet1NEMF);
    iTree->SetBranchAddress("res_"+algo+"jet2",         &res_jet2);
    iTree->SetBranchAddress("res_"+algo+"jet3",         &res_jet3);
    iTree->SetBranchAddress("res_"+algo+"jet4",         &res_jet4);
    iTree->SetBranchAddress("res_"+algo+"mt",         &res_mt);
    iTree->SetBranchAddress("res_"+algo+"jetsm",         &res_jetsm);
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
  if((triggerBits & kMET) && nmu==1 && nele==0 && npho==0 && ntau==0 && (vfakemet->Pt()!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isZmm(){
  bool lPass = false;
  if((triggerBits & kMET) && nmu==2 && nele==0 && npho==0 && ntau==0 && (vfakemet->Pt()!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isEle(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==1 && npho==0 && ntau==0 && vmet->Pt()>50 && (vfakemet->Pt()!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isZee(){
  bool lPass = false;
  if(((triggerBits & kSingleElectron) || (triggerBits & kSinglePhoton)) && nmu==0 && nele==2 && npho==0 && ntau==0 && (vfakemet->Pt()!=0)) lPass = true;
  return lPass;
}
bool BitsLoader::isPho(){
  bool lPass = false;
  if((triggerBits & kSinglePhoton) && nmu==0 && nele==0 && npho==1 && ntau==0 && (vfakemet->Pt()!=0)) lPass = true;
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
  TLorentzVector v = (*vfakemet);
  if(preselection.compare("Had")==0) v = (*vmet);
  return v;
}
TLorentzVector BitsLoader::getTop(){
  return (*res_jet1) + (*res_jet2) + (*res_jet3);
}
// bool BitsLoader::passBoostedMonoTopPreselection(string preselection){
//   TLorentzVector vMET = getMET(preselection);
//   bool lPass = false;
//   if(vMET.Pt()>250 &&
//      nf15jets==1 && bst15_jet1->Pt()>250 &&
//      bst15_jet1tau32<0.61 && bst15_jet1msd>110 && bst15_jet1msd<210 && bst15_jet1maxsubcsv>0.66) lPass=true;
//   return lPass;
// }
bool BitsLoader::passBoostedMonoTopPreselection(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     nf15jets==1 && bst15_jet1->Pt()>250 &&
     bst15_jet1tau32<0.61 && bst15_jet1msd>110 && bst15_jet1msd<210) lPass=true;
  return lPass;
}
bool BitsLoader::passBoosted15MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>1.1 &&
     // bst15_jet1msd>40 &&
     nf15jets==1 && bst15_jet1->Pt()>250) lPass=true;// && 
  //     bst15_jet1CHF>0.4 && bst15_jet1NHF<0.26 && bst15_jet1NEMF<0.57) lPass=true;// && 
  return lPass;
}
bool BitsLoader::passBoosted8MonoX(string preselection){
  TLorentzVector vMET = getMET(preselection);
    bool lPass = false;
  if(vMET.Pt()>250 &&
     min_dphijetsmet>0.7 &&
     //	 bst8_jet1msd>40 &&
     nf8jets==1 && bst8_jet1->Pt()>250) lPass=true;// && 
  //	                         bst15_jet1CHF>0.2 && bst15_jet1NHF<0.7 && bst15_jet1NEMF<0.7);
  return lPass;
}
bool BitsLoader::passResolvedMonoTop(string preselection){
  TLorentzVector vMET = getMET(preselection);
    bool lPass = false;
  if(vMET.Pt() > 200 &&
     min_dphijetsmet>1.1 &&
     njets>2 &&
     res_jet1->Pt() > 60 &&
     res_jet2->Pt() > 60 &&
     res_jet3->Pt() > 40) lPass=true;
  return lPass;
}
bool BitsLoader::passResolvedMonoXbb(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt() > 200 &&
     min_dphijetsmet>0.7 &&
     njets>=2 &&
     res_jet1->Pt()>30 && res_jet2->Pt()>30) lPass = true;
  return lPass;
}
bool BitsLoader::passBoostedMonoTopSR(string preselection){ 
  //  return passBoosted15MonoX(preselection) & (bst15_jet1tau32<0.69) & (bst15_jet1msd>110) & (bst15_jet1msd<210) & (bst15_jet1maxsubcsv>0.66);// & (nbjetsM>0); 
  return passBoostedMonoTopPreselection(preselection) & (min_dphijetsmet>1.1) & (bst15_jet1maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopZnunuHFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst15_jet1tau32<0.78) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsL>0) & (nbjetsM==0);
}
bool BitsLoader::passBoostedMonoTopZnunuLFCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst15_jet1tau32<0.78) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsL==0);// & (bst15_jet1minsubcsv<=0.605);
}
bool BitsLoader::passBoostedMonoTopTopCR(string preselection){ 
  //  TLorentzVector vMET = getMET(preselection);
  //  return (vMET.Pt()>250) & (bst15_jet1tau32<0.78)& (bst15_jet1maxsubcsv>0.89) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsM>0);
  //  return passBoosted15MonoX(preselection) & (bst15_jet1tau32<0.78) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsM>0) & (nbjetsT==1); 
  //  return (vMET.Pt()>250) & (bst15_jet1tau32<0.78) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsT>0);
  //  return (vMET.Pt()>250) & (bst15_jet1tau32<0.69) & (bst15_jet1msd>110) & (bst15_jet1msd<210) & (bst15_jet1maxsubcsv>0.66) & (nbjetsM>0);
  return passBoostedMonoTopPreselection(preselection) & (bst15_jet1maxsubcsv>0.76) & (nbjetsLdR2>0);
}
bool BitsLoader::passBoostedMonoTopTopCRminusTau32(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	    nf15jets==1 && bst15_jet1->Pt()>250 &&
	    bst15_jet1msd>110 && bst15_jet1msd<210) & (bst15_jet1maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopTopCRminusMass(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250 &&
	  nf15jets==1 && bst15_jet1->Pt()>250 &&
	  bst15_jet1tau32<0.61 && bst15_jet1msd>40) & (bst15_jet1maxsubcsv>0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopTopCRminusBtag(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (nbjetsLdR2>0);
}
bool BitsLoader::passBoostedMonoTopWCR(string preselection){
  // TLorentzVector vMET = getMET(preselection);
  // return (vMET.Pt()>250) & (bst15_jet1tau32<0.69) & (bst15_jet1msd>110) & (bst15_jet1msd<210) & (bst15_jet1maxsubcsv>0.66) & (nbjetsM==0);
  //  return (bst15_jet1msd>150) & (bst15_jet1msd<240) & (bst15_jet1tau32<0.78) & (bst15_jet1maxsubcsv<=0.89);
  return passBoostedMonoTopPreselection(preselection) & (bst15_jet1maxsubcsv<0.76) & (nbjetsLdR2==0);
}
bool BitsLoader::passBoostedMonoTopWHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  //  return passBoosted15MonoX(preselection) & (bst15_jet1tau32<0.78)& (bst15_jet1maxsubcsv>0.605) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsM==0); 
  return (vMET.Pt()>250) & (bst15_jet1tau32<0.78) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsM>0) & (nbjetsT==0);
  //  return passBoosted15MonoX(preselection) & (bst15_jet1tau32<0.78) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsT==1) & (nbjetsM==0);
}
bool BitsLoader::passBoostedMonoTopWLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  //  return passBoosted15MonoX(preselection) & (bst15_jet1tau32<0.78)& (bst15_jet1maxsubcsv<=0.605) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsM==0);
  return (vMET.Pt()>250) & (bst15_jet1tau32<0.78) & (bst15_jet1msd>150) & (bst15_jet1msd<250) & (nbjetsM==0);  
}
bool BitsLoader::passBoostedMonoTopZCR(string preselection){
  //  return passBoosted15MonoX(preselection) & (bst15_jet1msd>150) & (bst15_jet1msd<240) & (bst15_jet1tau32<0.78);
  // TLorentzVector vMET = getMET(preselection);
  // return (vMET.Pt()>250) & (bst15_jet1tau32<0.69) & (bst15_jet1msd>110) & (bst15_jet1msd<210) & (bst15_jet1maxsubcsv>0.66);
  return passBoostedMonoTopPreselection(preselection);
}
bool BitsLoader::passBoostedMonoTopZHFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst15_jet1msd>150) & (bst15_jet1msd<240) & (bst15_jet1tau32<0.78) & (nbjetsM>0);
  //  return passBoosted15MonoX(preselection) & (bst15_jet1msd>150) & (bst15_jet1msd<240) & (bst15_jet1tau32<0.78) & (bst15_jet1maxsubcsv>0.89);
}
bool BitsLoader::passBoostedMonoTopZLFCR(string preselection){
  TLorentzVector vMET = getMET(preselection);
  return (vMET.Pt()>250) & (bst15_jet1msd>150) & (bst15_jet1msd<240) & (bst15_jet1tau32<0.78) & (nbjetsM==0);
  //  return passBoosted15MonoX(preselection) & (bst15_jet1msd>150) & (bst15_jet1msd<240) & (bst15_jet1tau32<0.78) & (bst15_jet1maxsubcsv<=0.89);
}
bool BitsLoader::passBoostedMonoHbbSR(string preselection){
  return passBoosted15MonoX(preselection) & (bst15_jet1msd>105) & (bst15_jet1msd<150) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35)) & (bst15_jet1minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoHbbTopCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst15_jet1msd>105) & (bst15_jet1msd<150) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35)) & (bst15_jet1minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoHbbWCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst15_jet1msd>105) & (bst15_jet1msd<150) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35)) & (bst15_jet1minsubcsv<=0.605);
}
bool BitsLoader::passBoostedMonoHbbZCR(string preselection){
  return passBoosted15MonoX(preselection) & (bst15_jet1msd>105) & (bst15_jet1msd<150) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35));
}
bool BitsLoader::passBoostedMonoZbbSR(string preselection){
  return passBoosted8MonoX(preselection) & (bst15_jet1msd>60) & (bst15_jet1msd<105) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35)) & (bst15_jet1minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoZbbTopCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst15_jet1msd>60) & (bst15_jet1msd<105) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35)) & (bst15_jet1minsubcsv>0.605);
}
bool BitsLoader::passBoostedMonoZbbWCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst15_jet1msd>60) & (bst15_jet1msd<105) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35)) & (bst15_jet1minsubcsv<=0.605);
}
bool BitsLoader::passBoostedMonoZbbZCR(string preselection){
  return passBoosted8MonoX(preselection) & (bst15_jet1msd>60) & (bst15_jet1msd<105) & (bst15_jet1tau21<(-0.07*bst15_jet1rho+0.35));
}	
bool BitsLoader::passResolvedMonoHbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 105) & (res_jetsm < 150) & (nbjetsM==2);
}
bool BitsLoader::passResolvedMonoHbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 105) & (res_jetsm < 150) & (nbjetsT==1);
}
bool BitsLoader::passResolvedMonoHbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 105) & (res_jetsm < 150) & (nbjetsT==0) & (nbjetsM==2);
}
bool BitsLoader::passResolvedMonoHbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 105) & (res_jetsm < 150);
}
bool BitsLoader::passResolvedMonoZbbSR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 60) & (res_jetsm < 105) & (nbjetsL==2);
}
bool BitsLoader::passResolvedMonoZbbTopCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 60) & (res_jetsm < 105) & (nbjetsT==1);
}
bool BitsLoader::passResolvedMonoZbbWCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 60) & (res_jetsm < 105) & (nbjetsT==0);
}
bool BitsLoader::passResolvedMonoZbbZCR(string preselection){
  return passResolvedMonoXbb(preselection) & (res_jetsm > 60) & (res_jetsm < 105);
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
      // if (subsample == "ZnunuHFCR" && passBoostedMonoTopZnunuHFCR(preselection)
      //     && (combo=="ONLY" || combo=="COMBO")) {btagw=bst15_btagwT0*bst15_btagwL2; lPass = true;}
      // if (subsample == "ZnunuLFCR" && passBoostedMonoTopZnunuLFCR(preselection)
      //     && (combo=="ONLY" || combo=="COMBO")) {btagw=bst15_btagwL0; lPass = true;}

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
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=bst15_btagwL2; lPass = true;}
      if (subsample == "TopCR" && passBoostedMonoHbbTopCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=bst15_btagwL2; lPass = true;}
      if (subsample == "WCR" && passBoostedMonoHbbWCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) {btagw=bst15_btagwL0; lPass = true;}
      if (subsample == "ZCR" && passBoostedMonoHbbZCR(preselection) 
	  && (combo=="ONLY" || combo=="COMBO")) lPass = true;
    }
  if (selection == "BstMonoZbb")
    {
      if (subsample == "SR" && passBoostedMonoHbbSR(preselection) 
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopSR(preselection) && !passBoostedMonoHbbSR(preselection)))) {btagw=bst8_btagwL2; lPass = true;}
      if (subsample == "TopCR" && passBoostedMonoHbbTopCR(preselection) 
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoHbbWCR(preselection)))) 
	{btagw=bst8_btagwL2; lPass = true;}
      if (subsample == "WCR" && passBoostedMonoHbbWCR(preselection) 
	  && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passBoostedMonoHbbTopCR(preselection) && !passBoostedMonoTopWCR(preselection) && !passBoostedMonoHbbWCR(preselection))))
	{btagw=bst8_btagwL0; lPass = true;}
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
    //	  if(isSignal) wgt *= 20;
    if (algo == "CHS") wgt *= puWeight;
    
    // if(isam==1) {
    //   if(ifile==1) { wgt *= 32.3/22.45; }
    //   if(ifile==2) { wgt *= 8.1/9.03; }
    // }
  }
  return wgt;
}
float BitsLoader::transverse_mass(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst15_mt; 
  else if(selection == "BstMonoZbb") return bst8_mt;
  else return res_mt;
}
float BitsLoader::fjet_mass(string selection){
  return bst15_jet1msd;
}
float BitsLoader::nsubjet(string selection){
  if(selection == "BstMonoTop" || selection == "ResMonoTop") return bst15_jet1tau32;
  else if(selection == "BstMonoHbb" || selection == "ResMonoHbb") return bst15_jet1tau21;
  else return bst8_jet1tau21;
}
float BitsLoader::btag(string selection){
  return bst15_jet1maxsubcsv;
}
float BitsLoader::chf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst15_jet1CHF;
  else if(selection == "BstMonoZHbb") return bst8_jet1CHF;
  else return res_jet1CHF; 
}
float BitsLoader::nhf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst15_jet1NHF;
  else if(selection == "BstMonoZHbb") return bst8_jet1NHF;
  else return res_jet1NHF;
}
float BitsLoader::nemf(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst15_jet1NEMF;
  else if(selection == "BstMonoZHbb") return bst8_jet1NEMF;
  else return res_jet1NEMF;
}
float BitsLoader::genvpt(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst15_genVpt;
  else if (selection == "BstMonoZHbb") return bst8_genVpt;
  else return res_genVpt;
}
float BitsLoader::genvphi(string selection){
  if(selection == "BstMonoTop" || selection == "BstMonoHbb") return bst15_genVphi;
  else if (selection == "BstMonoZHbb") return bst8_genVphi;
  else return res_genVphi;
}
