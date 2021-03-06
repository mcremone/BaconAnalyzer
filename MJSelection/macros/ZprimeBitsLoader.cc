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
    iTree->SetBranchAddress("sf_phoTrig",                        &sf_phoTrig);
    iTree->SetBranchAddress("npu",                               &npu);
    iTree->SetBranchAddress("npv",                               &npv);
    iTree->SetBranchAddress("kfactor",                               &kfactor);
    iTree->SetBranchAddress("nmuLoose",                          &nmuLoose);
    iTree->SetBranchAddress("neleLoose",                         &neleLoose);
   // iTree->SetBranchAddress("ntau",                         &ntau);
    iTree->SetBranchAddress("nphoTight",                         &nphoTight);
    iTree->SetBranchAddress("puWeight",                          &puWeight);
    iTree->SetBranchAddress("scale1fb",                          &scale1fb);
    iTree->SetBranchAddress("evtWeight",                         &evtWeight);
    iTree->SetBranchAddress(met,                                 &vmetpt);
    iTree->SetBranchAddress(met+"phi",                           &vmetphi);
    iTree->SetBranchAddress("fake"+met,                          &vfakemetpt);
    iTree->SetBranchAddress("vpho0_pt",                           &vpho0_pt);
    iTree->SetBranchAddress("vpho0_eta",                          &vpho0_eta);
    iTree->SetBranchAddress("vpho0_phi",                           &vpho0_phi);
    iTree->SetBranchAddress("fake"+met+"phi",                    &vfakemetphi);
    iTree->SetBranchAddress("bst"+number+"_"+algo+"jets",                 &njets);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_pt",              &bst_jet0_pt);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_eta",             &bst_jet0_eta);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_phi",             &bst_jet0_phi);
    //iTree->SetBranchAddress("bst8_"+algo+jet+"_mass",           &bst_jet0_mass);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_msd",             &bst_jet0_msd);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_rho",             &bst_jet0_rho);
   // iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_phil",            &bst_jet0_phil);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_tau21",           &bst_jet0_tau21);
   // iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_CHF",             &bst_jet0_CHF);
   // iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_NHF",             &bst_jet0_NHF);
   // iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_NEMF",            &bst_jet0_NEMF);
   // iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_doublecsv",       &bst_jet0_doublecsv);
   // iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_minsubcsv",       &bst_jet0_minsubcsv);
   // iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_maxsubcsv",       &bst_jet0_maxsubcsv);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_vetoPhoton",       &bst_jet0_vetoPhoton);
    iTree->SetBranchAddress("bst"+number+"_"+algo+jet+"_tau32",         &bst_jet0_tau32);
  }
}
ZprimeBitsLoader::~ZprimeBitsLoader(){}
bool ZprimeBitsLoader::selectJetAlgoAndSize(TString algo){
  bool lPass = false;
  if((selectBits & kBOOSTED15PUPPI) && algo=="PUPPI") lPass = true;
  return lPass;
}
bool ZprimeBitsLoader::isPho(bool isData){
  bool lPass = false;
  if (nmuLoose==0 && neleLoose==0 && nphoTight==1   && vpho0_pt>200){
   if(isData){
    if(triggerBits & kSinglePhoton)  lPass = true;}
 //   lPass = true;}
   else{
    lPass = true;}
 }
 return lPass;
}

/*bool ZprimeBitsLoader::isHad(bool isData){
  bool lPass = false;
    if(nmu==0 && nele==0 && npho==0 && ntau==0 && met>175){
      if(isData){
        if((triggerBits & kMET)!=0)  lPass = true;
      }
      else{
       lPass = true;
      }
    }
   return lPass;
}*/

TLorentzVector ZprimeBitsLoader::getMET(){
   TLorentzVector v;
   v.SetPtEtaPhiM(vfakemetpt,0,vfakemetphi,0);
   return v;
}

bool ZprimeBitsLoader::passBoostedMonoTopPreselection(){
   TLorentzVector vMET = getMET();
   bool lPass = false;
   if(vMET.Pt()>200
   && njets>=1
     && bst_jet0_pt>200
     && bst_jet0_tau21 < 0.38 - 0.063*log((bst_jet0_msd)*(bst_jet0_msd)/bst_jet0_pt)
   //  && bst_jet0_msd>110
   //  && bst_jet0_msd<210
   //  && bst_jet0_tau32<0.61
     ) lPass=true;
  return lPass;
}



bool ZprimeBitsLoader::passBoostedZprimePreSelection(){
  //if((bst_jet0_msd>60) && (bst_jet0_msd<100)){ 
   return njets>0 & bst_jet0_pt>500;
  //  //else {return false;}
    }

bool ZprimeBitsLoader::passPreSelection(bool isData, string preselection){
  bool lPass = false;
 // if(preselection.compare("Had")==0 && isHad(isData)) lPass = true;
  if(preselection.compare("Pho")==0 && isPho(isData)) lPass = true;
  return lPass;
}

bool ZprimeBitsLoader::passBoostedGammaZprimeSelection(){
  //if((bst_jet0_msd>60) && (bst_jet0_msd<100)){ 
 return njets>0 & bst_jet0_pt>200;
 //else {return false;}
}

bool ZprimeBitsLoader::passBoostedGammaZprimeSR(float ddtcut){
  
//  return passBoostedGammaZprimeSelection();  
return passBoostedGammaZprimeSelection() & (bst_jet0_tau21 < (-0.063*bst_jet0_rho + ddtcut));
}



bool ZprimeBitsLoader::passBoostedZprimeSR(float ddtcut){
  
  return passBoostedZprimePreSelection() & (bst_jet0_tau21 < (-0.063*bst_jet0_rho + ddtcut));
}


bool ZprimeBitsLoader::passBoostedZprimeBTag(float csvcut){
  return passBoostedZprimePreSelection() & (bst_jet0_doublecsv > csvcut);
}


bool ZprimeBitsLoader::passSelection(bool isData,string selection,string subsample, float ddt,float csv1){
  bool lPass = false;
  if(selection=="BoostedZprimeGamma"){
   if((subsample=="SR") &&  passBoostedGammaZprimeSR(ddt)) lPass=true;
}
return lPass;
}


double ZprimeBitsLoader::getWgt(bool isData, TString algo, double LUMI){
  float wgt = 1;
  if(!isData) {     
    wgt *= LUMI*scale1fb*sf_phoTrig*puWeight;
    if (algo == "CHS") wgt *= puWeight;
  }
  return wgt;
}
double ZprimeBitsLoader::tau21DDT(){
  return bst_jet0_tau21 + 0.063*bst_jet0_rho;
}
