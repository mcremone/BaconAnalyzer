#include "MonoXBitsLoader.hh"  
using namespace std;

MonoXBitsLoader::MonoXBitsLoader(TTree *iTree, TString algo,TString syst, string preselection, bool isData, bool isBacon) {
  if(iTree){
    if(isBacon){
      TString vmet = "puppet"; if (algo!="PUPPI") vmet = "pfmet";
      if(preselection.compare("Had")==0){
	iTree->SetBranchAddress("res_"+algo+"jetmindPhi",                       &min_dphijetsmet);
	if(isData){
	  iTree->SetBranchAddress("calomet",                                    &calomet);
	}
      }
      else{
	iTree->SetBranchAddress("res_"+algo+"jetmindFPhi",                      &min_dphijetsmet);
      }
      iTree->SetBranchAddress("runNum",                                         &runNum);
      iTree->SetBranchAddress("lumiSec",                                        &lumiSec);
      iTree->SetBranchAddress("evtNum",                                         &evtNum);
      iTree->SetBranchAddress("metfilter",                                      &metfilter);
      iTree->SetBranchAddress("triggerBits",                                    &triggerBits);
      iTree->SetBranchAddress("selectBits",                                     &selectBits);
      iTree->SetBranchAddress("sf_lep",                                         &fsf_lep);
      iTree->SetBranchAddress("sf_lepTrack",                                    &fsf_lepTrack);
      iTree->SetBranchAddress("sf_eleTrig",                                     &sf_eletrig);
      iTree->SetBranchAddress("sf_phoTrig",                                     &sf_photrig);
      iTree->SetBranchAddress("sf_metTrig",                                     &sf_mettrig);
      iTree->SetBranchAddress("npu",                                            &npu);
      iTree->SetBranchAddress("npv",                                            &npv);
      iTree->SetBranchAddress("puWeight",                                       &puWeight);
      iTree->SetBranchAddress("scale1fb",                                       &scale1fb);
      iTree->SetBranchAddress("evtWeight",                                      &evtWeight);
      iTree->SetBranchAddress("kfactor",                                        &kfactor);
      iTree->SetBranchAddress("pfmet",                                          &met);
      iTree->SetBranchAddress(vmet,                                             &vmetpt);
      iTree->SetBranchAddress(vmet+"phi",                                       &vmetphi);
      iTree->SetBranchAddress("fake"+vmet,                                      &vfakemetpt);
      iTree->SetBranchAddress("fake"+vmet+"phi",                                &vfakemetphi);
      iTree->SetBranchAddress("res_"+algo+"jets",                               &njets);
      iTree->SetBranchAddress("res_"+algo+"jetsdR15",                           &njetsdR15);
      iTree->SetBranchAddress("res_"+algo+"jetsLdR15",                          &nbjetsLdR15);
      iTree->SetBranchAddress("res_"+algo+"jetmT",                              &res_jet0_mT);
      iTree->SetBranchAddress("res_"+algo+"jet0_pt",                            &res_jet0_pt);
      iTree->SetBranchAddress("res_"+algo+"jet0_eta",                           &res_jet0_eta);
      iTree->SetBranchAddress("res_"+algo+"jet0_phi",                           &res_jet0_phi);
      iTree->SetBranchAddress("res_"+algo+"jet1_pt",                            &res_jet1_pt);
      iTree->SetBranchAddress("res_"+algo+"jet1_eta",                           &res_jet1_eta);
      iTree->SetBranchAddress("res_"+algo+"jet1_phi",                           &res_jet1_phi);
      iTree->SetBranchAddress("res_"+algo+"jet2_pt",                            &res_jet2_pt);
      iTree->SetBranchAddress("res_"+algo+"jet2_eta",                           &res_jet2_eta);
      iTree->SetBranchAddress("res_"+algo+"jet2_phi",                           &res_jet2_phi);
      iTree->SetBranchAddress("res_"+algo+"jet3_pt",                            &res_jet3_pt);
      iTree->SetBranchAddress("res_"+algo+"jet3_eta",                           &res_jet3_eta);
      iTree->SetBranchAddress("res_"+algo+"jet3_phi",                           &res_jet3_phi);
      iTree->SetBranchAddress("res_"+algo+"jet0_mass",                          &res_jet0_mass);
      iTree->SetBranchAddress("res_"+algo+"jet1_mass",                          &res_jet1_mass);
      iTree->SetBranchAddress("res_"+algo+"jet2_mass",                          &res_jet2_mass);
      iTree->SetBranchAddress("res_"+algo+"jet3_mass",                          &res_jet3_mass);
      iTree->SetBranchAddress("res_"+algo+"jet0_csv",                           &res_jet0_csv);
      iTree->SetBranchAddress("res_"+algo+"jet1_csv",                           &res_jet1_csv);
      iTree->SetBranchAddress("res_"+algo+"jet2_csv",                           &res_jet2_csv);
      iTree->SetBranchAddress("res_"+algo+"jet3_csv",                           &res_jet3_csv);
      
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL0_CENT",               &resbst15_btagwL0);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL0_BTAGUP",             &resbst15_btagwL0BTAGUP);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL0_BTAGDO",             &resbst15_btagwL0BTAGDO);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL0_MISTAGUP",           &resbst15_btagwL0MISTAGUP);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL0_MISTAGDO",           &resbst15_btagwL0MISTAGDO);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL1_CENT",               &resbst15_btagwL1);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL1_BTAGUP",             &resbst15_btagwL1BTAGUP);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL1_BTAGDO",             &resbst15_btagwL1BTAGDO);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL1_MISTAGUP",           &resbst15_btagwL1MISTAGUP);
      iTree->SetBranchAddress("res_"+algo+"jetbst15btagwL1_MISTAGDO",           &resbst15_btagwL1MISTAGDO);

      iTree->SetBranchAddress("nmuLoose",                                       &nLooseMuon);
      iTree->SetBranchAddress("nmuTight",                                       &nTightMuon);
      iTree->SetBranchAddress("ismu0Tight",                                     &ismu0Tight);
      iTree->SetBranchAddress("neleLoose",                                      &nLooseElectron);
      iTree->SetBranchAddress("neleTight",                                      &nTightElectron);
      iTree->SetBranchAddress("isele0Tight",                                    &isele0Tight);
      iTree->SetBranchAddress("islep0Tight",                                    &looseLep1IsTight);
      iTree->SetBranchAddress("nphoLoose",                                      &nLoosePhoton);
      iTree->SetBranchAddress("nphoTight",                                      &nTightPhoton);
      iTree->SetBranchAddress("ispho0Tight",                                    &loosePho1IsTight);
      iTree->SetBranchAddress("ntau",                                           &nTau);
      iTree->SetBranchAddress("vpho0_pt",                                       &vpho0_pt);

      iTree->SetBranchAddress("bst15_"+algo+"jet0_isHadronicTop",               &isHadronicTop15);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_topSize",                     &topSize15);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_topMatching",                 &topMatching15);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_isTightVJet",                 &bst15_jet1_isTight); 
      iTree->SetBranchAddress("bst15_"+algo+"jets",                             &nfjets15);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_mT",                          &bst15_jet0_mT);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_dR_sj0dR",                    &bst15_jet0_dRsj0dR);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_dPhiJRF_sj0dPhiJRF",          &bst15_jet0_dPhiJRFsj0dPhiJRF);
      if(isData){
	iTree->SetBranchAddress("bst15_"+algo+"jet0_pttrue",                      &bst15_jet0_pt);
      }
      else{
	iTree->SetBranchAddress("bst15_"+algo+"jet0_pttrueMC",                    &bst15_jet0_pt);
      }
      //iTree->SetBranchAddress("bst15_"+algo+"jet0_pt",                          &bst15_jet0_pt);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_eta",                         &bst15_jet0_eta);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_phi",                         &bst15_jet0_phi);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_mass",                        &bst15_jet0_mass);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_msd",                         &bst15_jet0_msd);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_rho",                         &bst15_jet0_rho);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_tau32",                       &bst15_jet0_tau32);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_tau21",                       &bst15_jet0_tau21);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_CHF",                         &bst15_jet0_CHF);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_NHF",                         &bst15_jet0_NHF);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_NEMF",                        &bst15_jet0_NEMF);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_minsubcsv",                   &bst15_jet0_minsubcsv);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_maxsubcsv",                   &bst15_jet0_maxsubcsv);
      iTree->SetBranchAddress("bst15_"+algo+"jet0_doublecsv",                   &bst15_jet0_doublecsv);

      iTree->SetBranchAddress("eleSF0",                                         &eleSF0);
      iTree->SetBranchAddress("eleSF1",                                         &eleSF1);
      iTree->SetBranchAddress("eleSF2",                                         &eleSF2);
      iTree->SetBranchAddress("muoSF0",                                         &muoSF0);
      iTree->SetBranchAddress("muoSF1",                                         &muoSF1);
      iTree->SetBranchAddress("muoSF2",                                         &muoSF2);
      iTree->SetBranchAddress("phoSF0",                                         &phoSF0);
      iTree->SetBranchAddress("eleSFTrack",                                     &eleSFTrack);
      iTree->SetBranchAddress("muoSFTrack",                                     &muoSFTrack);
      if(!isData) {
	iTree->SetBranchAddress("genVPt",                                       &genVpt);
	iTree->SetBranchAddress("genVPhi",                                      &genVphi);
      }

      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL0_CENT",          &bst15_btagwL0);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL0_BTAGUP",        &bst15_btagwL0BTAGUP);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL0_BTAGDO",        &bst15_btagwL0BTAGDO);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL0_MISTAGUP",      &bst15_btagwL0MISTAGUP);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL0_MISTAGDO",      &bst15_btagwL0MISTAGDO);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL1_CENT",          &bst15_btagwL1);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL1_BTAGUP",        &bst15_btagwL1BTAGUP);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL1_BTAGDO",        &bst15_btagwL1BTAGDO);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL1_MISTAGUP",      &bst15_btagwL1MISTAGUP);
      iTree->SetBranchAddress("bst15_"+algo+"jetbtagwL1_MISTAGDO",      &bst15_btagwL1MISTAGDO);
    }
    else{
      if(isData){
        iTree->SetBranchAddress("mcWeight",                                     &normalizedWeight);
      }
      else{
        iTree->SetBranchAddress("normalizedWeight",                             &normalizedWeight);
      }
      iTree->SetBranchAddress("runNumber",                                      &runNumber);
      iTree->SetBranchAddress("lumiNumber",                                     &lumiNumber);
      iTree->SetBranchAddress("metFilter",                                      &metfilter);
      iTree->SetBranchAddress("newMetFilter",                                   &newmetfilter);
      iTree->SetBranchAddress("trigger",                                        &trigger);
      iTree->SetBranchAddress("puWeight",                                       &puWeight);
      iTree->SetBranchAddress("photonPurityWeight",                             &photonPurity);
      iTree->SetBranchAddress("sf_ewkZ",                                        &sf_ewkZ);
      iTree->SetBranchAddress("sf_ewkW",                                        &sf_ewkW);
      iTree->SetBranchAddress("sf_ewkA",                                        &sf_ewkA);
      iTree->SetBranchAddress("sf_qcdZ",                                        &sf_qcdZ);
      iTree->SetBranchAddress("sf_qcdW",                                        &sf_qcdW);
      iTree->SetBranchAddress("sf_qcdA",                                        &sf_qcdA);
      iTree->SetBranchAddress("sf_tt",                                          &sf_tt);
      iTree->SetBranchAddress("sf_lep",                                         &sf_lep);
      iTree->SetBranchAddress("sf_lepTrack",                                    &sf_lepTrack);
      iTree->SetBranchAddress("sf_metTrig",                                     &sf_metTrig);
      iTree->SetBranchAddress("sf_phoTrig",                                     &sf_phoTrig);
      iTree->SetBranchAddress("sf_eleTrig",                                     &sf_eleTrig);
      iTree->SetBranchAddress("sf_btag0",                                       &sf_btag0);
      iTree->SetBranchAddress("sf_btag1",                                       &sf_btag1);
      iTree->SetBranchAddress("sf_btag0BUp",                                    &sf_btag0BUp);
      iTree->SetBranchAddress("sf_btag1BUp",                                    &sf_btag1BUp);
      iTree->SetBranchAddress("sf_btag0BDown",                                  &sf_btag0BDown);
      iTree->SetBranchAddress("sf_btag1BDown",                                  &sf_btag1BDown);
      iTree->SetBranchAddress("sf_btag0MUp",                                    &sf_btag0MUp);
      iTree->SetBranchAddress("sf_btag1MUp",                                    &sf_btag1MUp);
      iTree->SetBranchAddress("sf_btag0MDown",                                  &sf_btag0MDown);
      iTree->SetBranchAddress("sf_btag1MDown",                                  &sf_btag1MDown);
      iTree->SetBranchAddress("sf_sjbtag0",                                     &sf_sjbtag0);
      iTree->SetBranchAddress("sf_sjbtag1",                                     &sf_sjbtag1);
      iTree->SetBranchAddress("sf_sjbtag0BUp",                                  &sf_sjbtag0BUp);
      iTree->SetBranchAddress("sf_sjbtag1BUp",                                  &sf_sjbtag1BUp);
      iTree->SetBranchAddress("sf_sjbtag0BDown",                                &sf_sjbtag0BDown);
      iTree->SetBranchAddress("sf_sjbtag1BDown",                                &sf_sjbtag1BDown);
      iTree->SetBranchAddress("sf_sjbtag0MUp",                                  &sf_sjbtag0MUp);
      iTree->SetBranchAddress("sf_sjbtag1MUp",                                  &sf_sjbtag1MUp);
      iTree->SetBranchAddress("sf_sjbtag0MDown",                                &sf_sjbtag0MDown);
      iTree->SetBranchAddress("sf_sjbtag1MDown",                                &sf_sjbtag1MDown);
      iTree->SetBranchAddress("met",                                            &met);
      iTree->SetBranchAddress("puppimet",                                       &vmetpt);
      iTree->SetBranchAddress("puppimetphi",                                    &vmetphi);
      iTree->SetBranchAddress("UWmag",                                          &UWmag);
      iTree->SetBranchAddress("UWphi",                                          &UWphi);
      iTree->SetBranchAddress("UZmag",                                          &UZmag);
      iTree->SetBranchAddress("UZphi",                                          &UZphi);
      iTree->SetBranchAddress("UAmag",                                          &UAmag);
      iTree->SetBranchAddress("UAphi",                                          &UAphi);
      iTree->SetBranchAddress("dPhiPuppiMET",                                   &dPhiPuppiMET);
      iTree->SetBranchAddress("dPhiUW",                                         &dPhiUW);
      iTree->SetBranchAddress("dPhiUZ",                                         &dPhiUZ);
      iTree->SetBranchAddress("dPhiUA",                                         &dPhiUA);
      iTree->SetBranchAddress("genBosonPt",                                     &genVpt);
      iTree->SetBranchAddress("genBosonPhi",                                    &genVphi);
      iTree->SetBranchAddress("nJet",                                           &njets);
      iTree->SetBranchAddress("jetNBtags",                                      &nbtags);
      iTree->SetBranchAddress("jetNIsoBtags",                                   &nbjetsLdR15);
      iTree->SetBranchAddress("nCA15fj",                                        &nfjets15);
      iTree->SetBranchAddress("CA15fj1_tau2",                                   &bst15_jet1_tau2);
      iTree->SetBranchAddress("CA15fj1_tau3",                                   &bst15_jet1_tau3);
      iTree->SetBranchAddress("CA15fj1_mSD",                                    &bst15_jet1_msd);
      iTree->SetBranchAddress("CA15fj1_pt",                                     &bst15_jet1_pt);
      iTree->SetBranchAddress("CA15fj1_eta",                                    &bst15_jet1_eta);
      iTree->SetBranchAddress("CA15fj1_maxsjbtag",                              &bst15_jet1_maxsubcsv);
      iTree->SetBranchAddress("CA15fj1_minsjbtag",                              &bst15_jet1_minsubcsv);
      iTree->SetBranchAddress("CA15fj1_isMatched",                              &bst15_jet1_isMatched);
      iTree->SetBranchAddress("CA15fj1_isHF",                                   &bst15_jet1_isHF);
      if(preselection.compare("Had")==0){
	iTree->SetBranchAddress("CA15fj1_isTight",                              &bst15_jet1_isTight);
	iTree->SetBranchAddress("calomet",                                      &calomet);
      }
      iTree->SetBranchAddress("CA15fj1_rawPt",                                  &bst15_jet1_rawPt);
      iTree->SetBranchAddress("nLooseLep",                                      &nLooseLep);
      iTree->SetBranchAddress("nLooseElectron",                                 &nLooseElectron);
      iTree->SetBranchAddress("nTightLep",                                      &nTightLep);
      iTree->SetBranchAddress("nTightElectron",                                 &nTightElectron);
      iTree->SetBranchAddress("nLooseMuon",                                     &nLooseMuon);
      iTree->SetBranchAddress("nTightMuon",                                     &nTightMuon);
      iTree->SetBranchAddress("looseLep1IsTight",                               &looseLep1IsTight);
      iTree->SetBranchAddress("looseLep2IsTight",                               &looseLep2IsTight);
      iTree->SetBranchAddress("looseLep1PdgId",                                 &looseLep1PdgId);
      iTree->SetBranchAddress("looseLep2PdgId",                                 &looseLep2PdgId);
      iTree->SetBranchAddress("looseLep1Pt",                                    &looseLep1Pt);
      iTree->SetBranchAddress("looseLep2Pt",                                    &looseLep2Pt);
      iTree->SetBranchAddress("looseLep1Eta",                                   &looseLep1Eta);
      iTree->SetBranchAddress("looseLep2Eta",                                   &looseLep2Eta);
      iTree->SetBranchAddress("looseLep1Phi",                                   &looseLep1Phi);
      iTree->SetBranchAddress("looseLep2Phi",                                   &looseLep2Phi);
      iTree->SetBranchAddress("diLepMass",                                      &diLepMass);
      iTree->SetBranchAddress("nLoosePhoton",                                   &nLoosePhoton);
      iTree->SetBranchAddress("nTightPhoton",                                   &nTightPhoton);
      iTree->SetBranchAddress("loosePho1IsTight",                               &loosePho1IsTight);
      iTree->SetBranchAddress("loosePho1Pt",                                    &loosePho1Pt);
      iTree->SetBranchAddress("loosePho1Eta",                                   &loosePho1Eta);
      iTree->SetBranchAddress("loosePho1Phi",                                   &loosePho1Phi);
      iTree->SetBranchAddress("nTau",                                           &nTau);
    }
  }
}
MonoXBitsLoader::~MonoXBitsLoader(){}
bool MonoXBitsLoader::selectJetAlgoAndSize(string selection, TString algo){
  bool lPass = false;
  if((selectBits & kBOOSTED15PUPPI) && selection.find("Bst15")==0 && algo=="PUPPI") lPass = true;
  if((selectBits & kRESOLVEDPUPPI) && selection.find("Res")==0 && algo=="PUPPI") lPass = true;
  return lPass;
}
bool MonoXBitsLoader::isHad(bool isData, bool isBacon){
  bool lPass = false;
  if(isBacon){
    if(nLooseMuon==0 && nLooseElectron==0 && nLoosePhoton==0 && nTau==0 && met>175 && bst15_jet1_isTight==1){
      if(isData){
        if(fabs(met-calomet)/vmetpt<0.5 && (triggerBits & kMET)!=0) lPass = true;
      }
      else{
	lPass = true;
      }
    }
  }
  else{
    if((nLooseMuon+nLooseElectron+nLoosePhoton+nTau)==0){
      if(isData){
      	if((trigger & 1)!=0) lPass = true; 
      }
      else{
      lPass = true;
      }
    }
  }
  return lPass;
}
bool MonoXBitsLoader::isMuo(bool isData, bool isBacon){
  bool lPass = false;
  if(isBacon){
    if(nLooseMuon==1 && nLooseElectron==0 && nLoosePhoton==0 && nTau==0 && looseLep1IsTight==1){
      if(isData){
	lPass = true;  
        if((triggerBits & 2)!=0) lPass = true;
      }
      else{
	lPass = true;
      }
    }
  }
  else{
    if((nLooseElectron+nLoosePhoton+nTau)==0 && nLooseMuon==1 && looseLep1IsTight==1){
      if(isData){
        if((trigger & 1)) lPass = true;
      }
      else{
	lPass = true;
      }
    }
  }
  return lPass;
}
bool MonoXBitsLoader::isZmm(bool isData, bool isBacon){
  bool lPass = false;
  if(isBacon){
    if(nLooseMuon==2 && nLooseElectron==0 && nLoosePhoton==0 && nTau==0 && looseLep1IsTight==1){
      if(isData){
        if((triggerBits & 2)!=0) 
	lPass = true;
      }
      else{
        lPass = true;
      }
    }
  }
  else{
    if((nLooseElectron+nLoosePhoton+nTau)==0 && nLooseMuon==2 && looseLep1IsTight==1){
      if(isData){
        if((trigger & 1)) lPass = true;
      }
      else{
        lPass = true;
      }
    }
  }
  return lPass;
}
bool MonoXBitsLoader::isEle(bool isData, bool isBacon){
  bool lPass = false;
  if(isBacon){
    if(nLooseMuon==0 && nLooseElectron==1 && nLoosePhoton==0 && nTau==0 && vmetpt>40 && (vfakemetpt!=0)){    
      if(isData){
	if((triggerBits & 4)) lPass = true;
      }
      else{
	lPass = true;
      }
    }
  }
  else{
    if((nLooseMuon+nLoosePhoton+nTau)==0 && nLooseElectron==1 && looseLep1IsTight==1 && vmetpt>40){
      if(isData){
        if((trigger & 2)) lPass = true;
      }
      else{
        lPass = true;
      }
    }
  }
  return lPass;
}
bool MonoXBitsLoader::isZee(bool isData, bool isBacon){
  bool lPass = false;
  if(isBacon){
    if(nLooseMuon==0 && nLooseElectron==2 && nLoosePhoton==0 && nTau==0 && looseLep1IsTight==1 && (vfakemetpt!=0)){
      if(isData){
        if((triggerBits & 4) || (triggerBits & 8) || (triggerBits & 16)) lPass = true;
      } 
      else{
        lPass = true;
      }
    }
  }
  else{
    if((nLooseMuon+nLoosePhoton+nTau)==0 && nLooseElectron==2 && looseLep1IsTight==1){
      if(isData){
        if((trigger & 2) || (trigger & 4)) lPass = true;
      }
      else{
        lPass = true;
      }
    }
  }
  return lPass;
}
bool MonoXBitsLoader::isPho(bool isData, bool isBacon){
  bool lPass = false;
  if(isBacon){
    if(nLooseMuon==0 && nLooseElectron==0 && nLoosePhoton==1 && loosePho1IsTight==1 && nTau==0){
      if(isData){
        if(triggerBits & 8) lPass = true;
      }
      else{
	lPass = true;
      }
    }
  }
  else{
    if((nLooseMuon+nLooseElectron+nTau)==0 && nLoosePhoton==1 && loosePho1IsTight==1){
      if(isData){
        if((trigger & 4)) lPass = true;
      }
      else{
        lPass = true;
      }
    }
  }
  return lPass;
}
bool MonoXBitsLoader::passPreSelection(string preselection, bool isData, bool isBacon){
  bool lPass = false;
  if(preselection.compare("Had")==0 && isHad(isData,isBacon)) lPass = true;
  if(preselection.compare("Muo")==0 && isMuo(isData,isBacon)) lPass = true;
  if(preselection.compare("Zmm")==0 && isZmm(isData,isBacon)) lPass = true;
  if(preselection.compare("Ele")==0 && isEle(isData,isBacon)) lPass = true;
  if(preselection.compare("Zee")==0 && isZee(isData,isBacon)) lPass = true;
  if(preselection.compare("Pho")==0 && isPho(isData,isBacon)) lPass = true;
  return lPass;
}
TLorentzVector MonoXBitsLoader::getMET(string preselection,bool isBacon){
  TLorentzVector v;
  if(isBacon){
    v.SetPtEtaPhiM(vfakemetpt,0,vfakemetphi,0);
    if(preselection.compare("Had")==0){v.SetPtEtaPhiM(vmetpt,0,vmetphi,0);};
  }
  else{
    if(preselection.compare("Had")==0){v.SetPtEtaPhiM(vmetpt,0,vmetphi,0);};
    if(preselection.compare("Muo")==0 || preselection.compare("Ele")==0){v.SetPtEtaPhiM(UWmag,0,UWphi,0);};
    if(preselection.compare("Zee")==0 || preselection.compare("Zmm")==0){v.SetPtEtaPhiM(UZmag,0,UZphi,0);};
    if(preselection.compare("Pho")==0){v.SetPtEtaPhiM(UAmag,0,UAphi,0);};

  }
  return v;
}
TLorentzVector MonoXBitsLoader::getTop(){
  TLorentzVector v0; v0.SetPtEtaPhiM(res_jet0_pt,res_jet0_eta,res_jet0_phi,res_jet0_mass);
  TLorentzVector v1; v1.SetPtEtaPhiM(res_jet1_pt,res_jet1_eta,res_jet1_phi,res_jet1_mass);
  TLorentzVector v2; v2.SetPtEtaPhiM(res_jet2_pt,res_jet2_eta,res_jet2_phi,res_jet2_mass);
  TLorentzVector v; v = v0+v1+v2;
  return v;
}
TLorentzVector MonoXBitsLoader::getTopRes(){
  std::vector<TLorentzVector> vJets, v; std::vector<float> vCSVs;
  TLorentzVector vfj; vfj.SetPtEtaPhiM(bst15_jet0_pt, bst15_jet0_eta, bst15_jet0_phi, bst15_jet0_mass); 
  TLorentzVector v0; v0.SetPtEtaPhiM(res_jet0_pt,res_jet0_eta,res_jet0_phi,res_jet0_mass); vJets.push_back(v0); vCSVs.push_back(res_jet0_csv);
  TLorentzVector v1; v1.SetPtEtaPhiM(res_jet1_pt,res_jet1_eta,res_jet1_phi,res_jet1_mass); vJets.push_back(v1); vCSVs.push_back(res_jet1_csv);
  TLorentzVector v2; v2.SetPtEtaPhiM(res_jet2_pt,res_jet2_eta,res_jet2_phi,res_jet2_mass); vJets.push_back(v2); vCSVs.push_back(res_jet2_csv);
  TLorentzVector v3; v2.SetPtEtaPhiM(res_jet3_pt,res_jet3_eta,res_jet3_phi,res_jet3_mass); vJets.push_back(v3); vCSVs.push_back(res_jet3_csv);
  for(unsigned int i0 = 0; i0 < vJets.size(); i0++) { 
    if(vCSVs[i0] > CSVL && vJets[i0].Pt() > 0 && vfj.DeltaR(vJets[i0]) > 1.5) v.push_back(vJets[i0]);
  }
  if (v.size() == 0){ TLorentzVector vs; v.push_back(vs);}
  return v[0]+vfj;
}
TLorentzVector MonoXBitsLoader::getHiggs(){
  TLorentzVector v0; v0.SetPtEtaPhiM(res_jet0_pt,res_jet0_eta,res_jet0_phi,res_jet0_mass);
  TLorentzVector v1; v1.SetPtEtaPhiM(res_jet1_pt,res_jet1_eta,res_jet1_phi,res_jet1_mass);
  TLorentzVector v; v = v0+v1;
  return v;
}
bool MonoXBitsLoader::passBoostedMonoTopPreselection(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>250  
     && nfjets15==1 
     && bst15_jet0_pt>250 
     && bst15_jet0_msd>110 
     && bst15_jet0_msd<210
     && bst15_jet0_tau32<0.61
     ) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passSemiResolvedMonoTopPreselection(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>170
     && nfjets15==1
     && bst15_jet0_pt>110
     ) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passSemiResolvedMonoTopBambuPreselection(string preselection){
  bool lPass = false;
  int lMET = 0;
  if(preselection.compare("Had")==0 && vmetpt>170 && bst15_jet1_isTight==1) lMET = 1;
  if((preselection.compare("Ele")==0 || preselection.compare("Muo")==0) && UWmag>170) lMET = 1;
  if((preselection.compare("Zee")==0 || preselection.compare("Zmm")==0) && UZmag>170) lMET = 1;
  if(preselection.compare("Pho")==0 && UAmag>170) lMET = 1;
  if(lMET==1 && nfjets15==1 && bst15_jet1_pt>110 && TMath::Abs(bst15_jet1_eta)<2.4 && (bst15_jet1_msd>110)) lPass= true;
  return lPass;
}
bool MonoXBitsLoader::passBoostedMonoTopBambuPreselection(string preselection){
  bool lPass = false;
  int lMET = 0;
  if(preselection.compare("Had")==0 && vmetpt>250 && met>175 && bst15_jet1_isTight==1 && fabs(met-calomet)/vmetpt<0.5) lMET = 1;
  if((preselection.compare("Ele")==0 || preselection.compare("Muo")==0) && UWmag>250) lMET = 1;
  if((preselection.compare("Zee")==0 || preselection.compare("Zmm")==0) && UZmag>250) lMET = 1;
  if(preselection.compare("Pho")==0 && UAmag>250) lMET = 1;
  if(lMET==1 && nfjets15==1 && bst15_jet1_pt>250 && TMath::Abs(bst15_jet1_eta)<2.4 && (bst15_jet1_tau3/bst15_jet1_tau2)<0.61 && (bst15_jet1_msd>110) && (bst15_jet1_msd<210)) lPass= true;
  return lPass;
}
bool MonoXBitsLoader::passBoosted15MonoHbbPreselection(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>170
     && nfjets15==1 
     && bst15_jet0_pt>170 
     ) lPass=true;
  return lPass;
}
bool MonoXBitsLoader::passBoosted15MonoHbbBambuPreselection(string preselection){
  bool lPass = false;
  int lMET = 0;
  if(preselection.compare("Had")==0 && vmetpt>170 && bst15_jet1_isTight==1) lMET = 1;
  if((preselection.compare("Ele")==0 || preselection.compare("Muo")==0) && UWmag>170) lMET = 1;
  if((preselection.compare("Zee")==0 || preselection.compare("Zmm")==0) && UZmag>170) lMET = 1;
  if(preselection.compare("Pho")==0 && UAmag>170) lMET = 1;
  if(lMET==1 && nfjets15==1 && bst15_jet1_pt>170 && TMath::Abs(bst15_jet1_eta)<2.4 && (bst15_jet1_msd>90) && (bst15_jet1_msd<135)) lPass= true;
  return lPass;
}
bool MonoXBitsLoader::passResolvedMonoHbbPreselection(string preselection){
  TLorentzVector vMET = getMET(preselection);
  bool lPass = false;
  if(vMET.Pt()>170
     && njets>=2 
     && res_jet0_pt>30 && res_jet1_pt>30
     ) lPass=true;
  return lPass;
}
// MonoTop
// Bacon
bool MonoXBitsLoader::passBoostedMonoTopSR(string preselection){ 
  return passBoostedMonoTopPreselection(preselection) & (min_dphijetsmet>1.1) & (nbjetsLdR15==0) & (bst15_jet0_maxsubcsv>CSVL);
}
bool MonoXBitsLoader::passBoostedMonoTopTopCR(string preselection){ 
  return passBoostedMonoTopPreselection(preselection) & (nbjetsLdR15>0) & (bst15_jet0_maxsubcsv>CSVL);
}
bool MonoXBitsLoader::passBoostedMonoTopWCR(string preselection){
  return passBoostedMonoTopPreselection(preselection) & (nbjetsLdR15==0) & (bst15_jet0_maxsubcsv<CSVL); 
}
bool MonoXBitsLoader::passBoostedMonoTopZCR(string preselection){
  return passBoostedMonoTopPreselection(preselection);
}
//Bambu
bool MonoXBitsLoader::passBoostedMonoTopBambuSR(string preselection){
  return passBoostedMonoTopBambuPreselection(preselection) & (dPhiPuppiMET>1.1) & (bst15_jet1_maxsubcsv>0.46) & (nbjetsLdR15==0);
}
bool MonoXBitsLoader::passBoostedMonoTopBambuTopCR(string preselection){
  return passBoostedMonoTopBambuPreselection(preselection) & (bst15_jet1_maxsubcsv>0.46) & (nbjetsLdR15==1);
}
bool MonoXBitsLoader::passBoostedMonoTopBambuWCR(string preselection){
  return passBoostedMonoTopBambuPreselection(preselection) & (bst15_jet1_maxsubcsv<0.46) & (nbjetsLdR15==0);
}
bool MonoXBitsLoader::passBoostedMonoTopBambuZCR(string preselection){
  return passBoostedMonoTopBambuPreselection(preselection);
}
//SemiResolved
bool MonoXBitsLoader::passSemiResolvedMonoTopSR(string preselection){
  return passSemiResolvedMonoTopPreselection(preselection) & (nbjetsLdR15==1) & (bst15_jet0_msd>60) & (bst15_jet0_msd<160) & (min_dphijetsmet>0.5) & (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.7)) 
    & (getTopRes().M() <250) & (getTopRes().Pt()>170);
}
bool MonoXBitsLoader::passSemiResolvedMonoTopTopCR(string preselection){
  return passSemiResolvedMonoTopPreselection(preselection) & (nbjetsLdR15>0) & (bst15_jet0_msd>60) & (bst15_jet0_msd<120) & (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.7));
}
bool MonoXBitsLoader::passSemiResolvedMonoTopWCR(string preselection){
  return passSemiResolvedMonoTopPreselection(preselection) & (nbjetsLdR15==0) & (bst15_jet0_msd>60) & (bst15_jet0_msd<120) & (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.7));
}
bool MonoXBitsLoader::passSemiResolvedMonoTopZCR(string preselection){
  return passSemiResolvedMonoTopPreselection(preselection) & (bst15_jet0_msd>60) & (bst15_jet0_msd<120) & (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.7));
}
//Bambu
bool MonoXBitsLoader::passSemiResolvedMonoTopBambuSR(string preselection){
  return passSemiResolvedMonoTopBambuPreselection(preselection) & (dPhiPuppiMET>1.1) & (bst15_jet1_maxsubcsv>0.46) & (nbjetsLdR15==0);
}
bool MonoXBitsLoader::passSemiResolvedMonoTopBambuTopCR(string preselection){
  return passSemiResolvedMonoTopBambuPreselection(preselection) & (bst15_jet1_maxsubcsv>0.46) & (nbjetsLdR15==1);
}
bool MonoXBitsLoader::passSemiResolvedMonoTopBambuWCR(string preselection){
  return passSemiResolvedMonoTopBambuPreselection(preselection) & (bst15_jet1_maxsubcsv<0.46) & (nbjetsLdR15==0);
}
bool MonoXBitsLoader::passSemiResolvedMonoTopBambuZCR(string preselection){
  return passSemiResolvedMonoTopBambuPreselection(preselection);
}

// MonoH
// 15 cone jet
bool MonoXBitsLoader::passBoosted15MonoHbbSR(string preselection, float csvb0, float csvb1){
  return passBoosted15MonoHbbPreselection(preselection) & (nbjetsLdR15==0) & (bst15_jet0_msd>90) & (bst15_jet0_msd<135) & (min_dphijetsmet>0.4) & (bst15_jet0_minsubcsv>csvb0) & (bst15_jet0_minsubcsv<csvb1) & (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.83));
}
bool MonoXBitsLoader::passBoosted15MonoHbbTopCR(string preselection, float csvb0, float csvb1){
  return passBoosted15MonoHbbPreselection(preselection) & (nbjetsLdR15>0) & (bst15_jet0_msd>90) & (bst15_jet0_msd<135) & (bst15_jet0_maxsubcsv>csvb0) & (bst15_jet0_maxsubcsv<csvb1); //& (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.8))
}
bool MonoXBitsLoader::passBoosted15MonoHbbWCR(string preselection, float csvb0, float csvb1){
  return passBoosted15MonoHbbPreselection(preselection) & (nbjetsLdR15==0) & (bst15_jet0_msd>90) & (bst15_jet0_msd<135) & ((bst15_jet0_maxsubcsv<=csvb0) || (bst15_jet0_maxsubcsv>=csvb1));// & (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.8))
}
bool MonoXBitsLoader::passBoosted15MonoHbbZCR(string preselection){
  return passBoosted15MonoHbbPreselection(preselection) & (bst15_jet0_msd>90) & (bst15_jet0_msd<135);// & (bst15_jet0_tau21 < (-0.063*bst15_jet0_rho + 0.8));
}
// Resolved
bool MonoXBitsLoader::passResolvedMonoHbbSR(string preselection){
  TLorentzVector vHiggs = getHiggs();
  return passResolvedMonoHbbPreselection(preselection) & (min_dphijetsmet>0.4) & (vHiggs.Pt()>150) & (vHiggs.M() > 100) & (vHiggs.M() < 150) & (njets==2) & (njets<4) & (nbjetsM==2);
}
bool MonoXBitsLoader::passResolvedMonoHbbTopCR(string preselection){
  TLorentzVector vHiggs = getHiggs();
  return passResolvedMonoHbbPreselection(preselection) & (vHiggs.Pt()>150) & (nbjetsM==2) & (njets > 2) ;
}
bool MonoXBitsLoader::passResolvedMonoHbbWCR(string preselection){
  TLorentzVector vHiggs = getHiggs();
  return passResolvedMonoHbbPreselection(preselection) & (vHiggs.Pt()>150) & (nbjetsL>1) & (nbjetsT==0) & (njets==2);
}
bool MonoXBitsLoader::passResolvedMonoHbbZCR(string preselection){
  TLorentzVector vHiggs = getHiggs();
  if(preselection.compare("Zee")==0 || preselection.compare("Zmm")==0) return passResolvedMonoHbbPreselection(preselection) & (vHiggs.Pt()>150)  & (njets==2) & (nbjetsT==0);
  else return passResolvedMonoHbbPreselection(preselection) & (vHiggs.Pt()>150) & (njets==2); 
}
// Bambu
bool MonoXBitsLoader::passBoosted15MonoHbbBambuSR(string preselection, float csvb0, float csvb1){
  return passBoosted15MonoHbbBambuPreselection(preselection) & (nbjetsLdR15==0) & (dPhiPuppiMET>0.4) & (bst15_jet0_minsubcsv>csvb0) & (bst15_jet0_minsubcsv<csvb1);
}
bool MonoXBitsLoader::passBoosted15MonoHbbBambuTopCR(string preselection, float csvb0, float csvb1){
  return passBoosted15MonoHbbBambuPreselection(preselection) & (nbjetsLdR15>0) & (bst15_jet0_maxsubcsv>csvb0) & (bst15_jet0_maxsubcsv<csvb1);
}
bool MonoXBitsLoader::passBoosted15MonoHbbBambuWCR(string preselection, float csvb0, float csvb1){
  return passBoosted15MonoHbbBambuPreselection(preselection) & (nbjetsLdR15==0) & ((bst15_jet0_maxsubcsv<=csvb0) || (bst15_jet0_maxsubcsv>=csvb1));
}
bool MonoXBitsLoader::passBoosted15MonoHbbBambuZCR(string preselection){
  return passBoosted15MonoHbbBambuPreselection(preselection);
}

// Selection
bool MonoXBitsLoader::passSelection(string preselection, string selection, string subsample, string combo, float &btagw, TString syst, bool isSignal, bool isBacon){
  bool lPass = false;	
  btagw = 1;
  if(isBacon){
    if (selection == "Bst15MonoTop")
      {
	if (subsample == "SR" && passBoostedMonoTopSR(preselection) 
	    && (combo=="ONLY" || combo=="COMBO")) {
          if(syst=="CENT"){btagw=resbst15_btagwL0*bst15_btagwL1; }
          if(syst=="BTAGUP"){btagw=resbst15_btagwL0BTAGUP*bst15_btagwL1; }
          if(syst=="BTAGDO"){btagw=resbst15_btagwL0BTAGDO*bst15_btagwL1; }
          if(syst=="MISTAGUP"){btagw=resbst15_btagwL0MISTAGUP*bst15_btagwL1;}
          if(syst=="MISTAGDO"){btagw=resbst15_btagwL0MISTAGDO*bst15_btagwL1; }
          if(syst=="SJBTAGUP"){btagw=resbst15_btagwL0*bst15_btagwL1BTAGUP; }
          if(syst=="SJBTAGDO"){btagw=resbst15_btagwL0*bst15_btagwL1BTAGDO; }
          if(syst=="SJMISTAGUP"){btagw=resbst15_btagwL0*bst15_btagwL1MISTAGUP;}
          if(syst=="SJMISTAGDO"){btagw=resbst15_btagwL0*bst15_btagwL1MISTAGDO;}
	  lPass = true;
	}
	if (subsample == "TopCR" && passBoostedMonoTopTopCR(preselection) 
	    && (combo=="ONLY" || combo=="COMBO")) {
	  btagw=resbst15_btagwL1*bst15_btagwL1;  
          if(syst=="CENT"){btagw=resbst15_btagwL1*bst15_btagwL1; }
          if(syst=="BTAGUP"){btagw=resbst15_btagwL1BTAGUP*bst15_btagwL1; }
          if(syst=="BTAGDO"){btagw=resbst15_btagwL1BTAGDO*bst15_btagwL1; }
          if(syst=="MISTAGUP"){btagw=resbst15_btagwL1MISTAGUP*bst15_btagwL1;}
          if(syst=="MISTAGDO"){btagw=resbst15_btagwL1MISTAGDO*bst15_btagwL1; }
          if(syst=="SJBTAGUP"){btagw=resbst15_btagwL1*bst15_btagwL1BTAGUP; }
          if(syst=="SJBTAGDO"){btagw=resbst15_btagwL1*bst15_btagwL1BTAGDO; }
          if(syst=="SJMISTAGUP"){btagw=resbst15_btagwL1*bst15_btagwL1MISTAGUP;}
          if(syst=="SJMISTAGDO"){btagw=resbst15_btagwL1*bst15_btagwL1MISTAGDO;}
	  lPass = true;}
	if (subsample == "WCR" && passBoostedMonoTopWCR(preselection) 
	    && (combo=="ONLY" || combo=="COMBO")) {
          if(syst=="CENT"){btagw=resbst15_btagwL0*bst15_btagwL0; }
          if(syst=="BTAGUP"){btagw=resbst15_btagwL0BTAGUP*bst15_btagwL0; }
          if(syst=="BTAGDO"){btagw=resbst15_btagwL0BTAGDO*bst15_btagwL0; }
          if(syst=="MISTAGUP"){btagw=resbst15_btagwL0MISTAGUP*bst15_btagwL0;}
          if(syst=="MISTAGDO"){btagw=resbst15_btagwL0MISTAGDO*bst15_btagwL0; }
          if(syst=="SJBTAGUP"){btagw=resbst15_btagwL0*bst15_btagwL0BTAGUP; }
          if(syst=="SJBTAGDO"){btagw=resbst15_btagwL0*bst15_btagwL0BTAGDO; }
          if(syst=="SJMISTAGUP"){btagw=resbst15_btagwL0*bst15_btagwL0MISTAGUP;}
          if(syst=="SJMISTAGDO"){btagw=resbst15_btagwL0*bst15_btagwL0MISTAGDO;} 
	  lPass = true;}
	if (subsample == "ZCR" && passBoostedMonoTopZCR(preselection) 
	    && (combo=="ONLY" || combo=="COMBO")) lPass = true;
      }
    if (selection == "Bst15SemMonoTop")
      {
	if (subsample == "SR" && passSemiResolvedMonoTopSR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopSR(preselection)))) {
          if(syst=="CENT"){btagw=resbst15_btagwL1; }
          if(syst=="BTAGUP"){btagw=resbst15_btagwL1BTAGUP; }
          if(syst=="BTAGDO"){btagw=resbst15_btagwL1BTAGDO; }
          if(syst=="MISTAGUP"){btagw=resbst15_btagwL1MISTAGUP;}
          if(syst=="MISTAGDO"){btagw=resbst15_btagwL1MISTAGDO; }
	  lPass = true;
	}
	if (subsample == "TopCR" && passSemiResolvedMonoTopTopCR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopTopCR(preselection) && !passSemiResolvedMonoTopWCR(preselection)))) {
          if(syst=="CENT"){btagw=resbst15_btagwL1; }
          if(syst=="BTAGUP"){btagw=resbst15_btagwL1BTAGUP; }
          if(syst=="BTAGDO"){btagw=resbst15_btagwL1BTAGDO; }
          if(syst=="MISTAGUP"){btagw=resbst15_btagwL1MISTAGUP;}
          if(syst=="MISTAGDO"){btagw=resbst15_btagwL1MISTAGDO; } 
	  lPass = true;
	}
	if (subsample == "WCR" && passSemiResolvedMonoTopWCR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopWCR(preselection) && !passSemiResolvedMonoTopTopCR(preselection)))) {
          if(syst=="CENT"){btagw=resbst15_btagwL0; }
          if(syst=="BTAGUP"){btagw=resbst15_btagwL0BTAGUP; }
          if(syst=="BTAGDO"){btagw=resbst15_btagwL0BTAGDO; }
          if(syst=="MISTAGUP"){btagw=resbst15_btagwL0MISTAGUP;}
          if(syst=="MISTAGDO"){btagw=resbst15_btagwL0MISTAGDO; }
	  lPass = true;}
	if (subsample == "ZCR" && passSemiResolvedMonoTopZCR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopZCR(preselection)))){
	  lPass = true;}
      }
    if (selection == "Bst15MonoHbb")
      { 
	if (subsample == "SR" && passBoosted15MonoHbbSR(preselection,CSVM,1000)
	    && (combo=="ONLY" || combo=="COMBO")) {
	  if(syst=="CENT"){btagw=resbst15_btagwL0*bst15_btagwM2; }
	  if(syst=="BTAGUP"){btagw=resbst15_btagwL0BTAGUP*bst15_btagwM2; }
	  if(syst=="BTAGDO"){btagw=resbst15_btagwL0BTAGDO*bst15_btagwM2; }
	  if(syst=="MISTAGUP"){btagw=resbst15_btagwL0MISTAGUP*bst15_btagwM2;}
	  if(syst=="MISTAGDO"){btagw=resbst15_btagwL0MISTAGDO*bst15_btagwM2; }
	  if(syst=="SJBTAGUP"){btagw=resbst15_btagwL0*bst15_btagwM2BTAGUP; }
	  if(syst=="SJBTAGDO"){btagw=resbst15_btagwL0*bst15_btagwM2BTAGDO; }
	  if(syst=="SJMISTAGUP"){btagw=resbst15_btagwL0*bst15_btagwM2MISTAGUP;}
	  if(syst=="SJMISTAGDO"){btagw=resbst15_btagwL0*bst15_btagwM2MISTAGDO;}
	  lPass = true;}
	if (subsample == "TopCR" && passBoosted15MonoHbbTopCR(preselection,CSVL,1000) 
	    && (combo=="ONLY" || combo=="COMBO")) {
	  if(syst=="CENT"){btagw=resbst15_btagwL1*bst15_btagwL1; }
	  if(syst=="BTAGUP"){btagw=resbst15_btagwL1BTAGUP*bst15_btagwL1; }
	  if(syst=="BTAGDO"){btagw=resbst15_btagwL1BTAGDO*bst15_btagwL1; }
	  if(syst=="MISTAGUP"){btagw=resbst15_btagwL1MISTAGUP*bst15_btagwL1;}
	  if(syst=="MISTAGDO"){btagw=resbst15_btagwL1MISTAGDO*bst15_btagwL1; }
	  if(syst=="SJBTAGUP"){btagw=resbst15_btagwL1*bst15_btagwL1BTAGUP; }
	  if(syst=="SJBTAGDO"){btagw=resbst15_btagwL1*bst15_btagwL1BTAGDO; }
	  if(syst=="SJMISTAGUP"){btagw=resbst15_btagwL1*bst15_btagwL1MISTAGUP;}
	  if(syst=="SJMISTAGDO"){btagw=resbst15_btagwL1*bst15_btagwL1MISTAGDO;}
	  lPass = true;}
	if (subsample == "WCR" && passBoosted15MonoHbbWCR(preselection,CSVL,1000) 
	    && (combo=="ONLY" || combo=="COMBO")) {
	  if(syst=="CENT"){btagw=resbst15_btagwL0*bst15_btagwL0; }
	  if(syst=="BTAGUP"){btagw=resbst15_btagwL0BTAGUP*bst15_btagwL0; }
	  if(syst=="BTAGDO"){btagw=resbst15_btagwL0BTAGDO*bst15_btagwL0; }
	  if(syst=="MISTAGUP"){btagw=resbst15_btagwL0MISTAGUP*bst15_btagwL0;}
	  if(syst=="MISTAGDO"){btagw=resbst15_btagwL0MISTAGDO*bst15_btagwL0; }
	  if(syst=="SJBTAGUP"){btagw=resbst15_btagwL0*bst15_btagwL0BTAGUP; }
	  if(syst=="SJBTAGDO"){btagw=resbst15_btagwL0*bst15_btagwL0BTAGDO; }
	  if(syst=="SJMISTAGUP"){btagw=resbst15_btagwL0*bst15_btagwL0MISTAGUP;}
	  if(syst=="SJMISTAGDO"){btagw=resbst15_btagwL0*bst15_btagwL0MISTAGDO;}
	  lPass = true;}
	if (subsample == "ZCR" && passBoosted15MonoHbbZCR(preselection) 
	    && (combo=="ONLY" || combo=="COMBO"))
	  lPass = true;
      }
    if (selection == "ResMonoHbb")
      {
	if (subsample == "SR" && passResolvedMonoHbbSR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoosted15MonoHbbSR(preselection,CSVM,1000)))) {
	  if(syst=="CENT"){btagw=resbst15_btagwM2; }
	  if(syst=="BTAGUP"){btagw=resbst15_btagwM2BTAGUP; }
	  if(syst=="BTAGDO"){btagw=resbst15_btagwM2BTAGDO; }
	  if(syst=="MISTAGUP"){btagw=resbst15_btagwM2MISTAGUP;}
	  if(syst=="MISTAGDO"){btagw=resbst15_btagwM2MISTAGDO; }
	  lPass = true;}
	if (subsample == "TopCR" && passResolvedMonoHbbTopCR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoosted15MonoHbbTopCR(preselection,CSVL,1000) && !passBoosted15MonoHbbWCR(preselection,CSVL,1000)))) {
	  if(syst=="CENT"){btagw=resbst15_btagwM2; }
	  if(syst=="BTAGUP"){btagw=resbst15_btagwM2BTAGUP; }
	  if(syst=="BTAGDO"){btagw=resbst15_btagwM2BTAGDO; }
	  if(syst=="MISTAGUP"){btagw=resbst15_btagwM2MISTAGUP; }
	  if(syst=="MISTAGDO"){btagw=resbst15_btagwM2MISTAGDO; }
	  lPass = true;}
	if (subsample == "WCR" && passResolvedMonoHbbWCR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoosted15MonoHbbTopCR(preselection,CSVL,1000) && !passBoosted15MonoHbbWCR(preselection,CSVL,1000)))) {
	  if(syst=="CENT"){btagw=resbst15_btagwL1*bst15_btagwT0; }
	  if(syst=="BTAGUP"){btagw=resbst15_btagwL1BTAGUP*bst15_btagwT0; }
	  if(syst=="BTAGDO"){btagw=resbst15_btagwL1BTAGDO*bst15_btagwT0; }
	  if(syst=="MISTAGUP"){btagw=resbst15_btagwL1MISTAGUP*bst15_btagwT0;}
	  if(syst=="MISTAGDO"){btagw=resbst15_btagwL1MISTAGDO*bst15_btagwT0; }
	  if(syst=="SJBTAGUP"){btagw=resbst15_btagwL1*bst15_btagwT0BTAGUP; }
	  if(syst=="SJBTAGDO"){btagw=resbst15_btagwL1*bst15_btagwT0BTAGDO; }
	  if(syst=="SJMISTAGUP"){btagw=resbst15_btagwL1*bst15_btagwT0MISTAGUP;}
	  if(syst=="SJMISTAGDO"){btagw=resbst15_btagwL1*bst15_btagwT0MISTAGDO;}
	  lPass = true;}
	if (subsample == "ZCR" && passResolvedMonoHbbZCR(preselection)
	    && (combo=="ONLY" || (combo=="COMBO" && !passBoosted15MonoHbbZCR(preselection)))) {
	  if(preselection.compare("Zee")==0 || preselection.compare("Zmm")==0){
            if(syst=="CENT"){btagw=resbst15_btagwT0; }
            if(syst=="BTAGUP"){btagw=resbst15_btagwT0BTAGUP; }
            if(syst=="BTAGDO"){btagw=resbst15_btagwT0BTAGDO; }
            if(syst=="MISTAGUP"){btagw=resbst15_btagwT0MISTAGUP; }
            if(syst=="MISTAGDO"){btagw=resbst15_btagwT0MISTAGDO; }
	  }
	  else{ btagw=1;} 
	  lPass = true;}
      }
  }
  else{
    if (selection == "Bst15MonoTop")
      {
        if (subsample == "SR" && passBoostedMonoTopBambuSR(preselection)
            && (combo=="ONLY" || combo=="COMBO")) {
	  if(syst=="CENT"){btagw=sf_btag0*sf_sjbtag1; }
          if(syst=="BTAGUP"){btagw=sf_btag0BUp*sf_sjbtag1; }
          if(syst=="BTAGDO"){btagw=sf_btag0BDown*sf_sjbtag1;}
          if(syst=="MISTAGUP"){btagw=sf_btag0MUp*sf_sjbtag1;}
          if(syst=="MISTAGDO"){btagw=sf_btag0MDown*sf_sjbtag1;}
          if(syst=="SJBTAGUP"){btagw=sf_btag0*sf_sjbtag1BUp;}
          if(syst=="SJBTAGDO"){btagw=sf_btag0*sf_sjbtag1BDown;}
          if(syst=="SJMISTAGUP"){btagw=sf_btag0*sf_sjbtag1MUp;}
          if(syst=="SJMISTAGDO"){btagw=sf_btag0*sf_sjbtag1MDown;}
	  lPass = true;
	}
        if (subsample == "TopCR" && passBoostedMonoTopBambuTopCR(preselection)
            && (combo=="ONLY" || combo=="COMBO")) {
          if(syst=="CENT"){btagw=sf_btag1*sf_sjbtag1;}
          if(syst=="BTAGUP"){btagw=sf_btag1BUp*sf_sjbtag1;}
          if(syst=="BTAGDO"){btagw=sf_btag1BDown*sf_sjbtag1;}
          if(syst=="MISTAGUP"){btagw=sf_btag1MUp*sf_sjbtag1;}
          if(syst=="MISTAGDO"){btagw=sf_btag1MDown*sf_sjbtag1;}
          if(syst=="SJBTAGUP"){btagw=sf_btag1*sf_sjbtag1BUp;}
          if(syst=="SJBTAGDO"){btagw=sf_btag1*sf_sjbtag1BDown;}
          if(syst=="SJMISTAGUP"){btagw=sf_btag1*sf_sjbtag1MUp;}
          if(syst=="SJMISTAGDO"){btagw=sf_btag1*sf_sjbtag1MDown;}
	  lPass = true;
	}
        if (subsample == "WCR" && passBoostedMonoTopBambuWCR(preselection)
            && (combo=="ONLY" || combo=="COMBO")) {
          if(syst=="CENT"){btagw=sf_btag0*sf_sjbtag0;}
          if(syst=="BTAGUP"){btagw=sf_btag0BUp*sf_sjbtag0;}
          if(syst=="BTAGDO"){btagw=sf_btag0BDown*sf_sjbtag0;}
          if(syst=="MISTAGUP"){btagw=sf_btag0MUp*sf_sjbtag0;}
          if(syst=="MISTAGDO"){btagw=sf_btag0MDown*sf_sjbtag0;}
          if(syst=="SJBTAGUP"){btagw=sf_btag0*sf_sjbtag0BUp;}
          if(syst=="SJBTAGDO"){btagw=sf_btag0*sf_sjbtag0BDown;}
          if(syst=="SJMISTAGUP"){btagw=sf_btag0*sf_sjbtag0MUp;}
          if(syst=="SJMISTAGDO"){btagw=sf_btag0*sf_sjbtag0MDown;}
	  lPass = true;}
        if (subsample == "ZCR" && passBoostedMonoTopBambuZCR(preselection)
            && (combo=="ONLY" || combo=="COMBO")) lPass = true;
      }
    if (selection == "Bst15SemMonoTop")
      {
        if (subsample == "SR" && passSemiResolvedMonoTopBambuSR(preselection)
            && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopBambuSR(preselection)))) {
          if(syst=="CENT"){btagw=sf_btag1; }
          if(syst=="BTAGUP"){btagw=sf_btag1BUp; }
          if(syst=="BTAGDO"){btagw=sf_btag1BDown; }
          if(syst=="MISTAGUP"){btagw=sf_btag1MUp;}
          if(syst=="MISTAGDO"){btagw=sf_btag1MDown; }
          lPass = true;
        }
        if (subsample == "TopCR" && passSemiResolvedMonoTopBambuTopCR(preselection)
            && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopBambuTopCR(preselection) && !passSemiResolvedMonoTopBambuWCR(preselection)))) {
          if(syst=="CENT"){btagw=sf_btag1; }
          if(syst=="BTAGUP"){btagw=sf_btag1BUp; }
          if(syst=="BTAGDO"){btagw=sf_btag1BDown; }
          if(syst=="MISTAGUP"){btagw=sf_btag1MUp;}
          if(syst=="MISTAGDO"){btagw=sf_btag1MDown;}
          lPass = true;
        }
        if (subsample == "WCR" && passSemiResolvedMonoTopBambuWCR(preselection)
            && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopBambuWCR(preselection) && !passSemiResolvedMonoTopBambuTopCR(preselection)))) {
          if(syst=="CENT"){btagw=sf_btag0; }
          if(syst=="BTAGUP"){btagw=sf_btag0BUp; }
          if(syst=="BTAGDO"){btagw=sf_btag0BDown; }
          if(syst=="MISTAGUP"){btagw=sf_btag0MUp;}
          if(syst=="MISTAGDO"){btagw=sf_btag0MDown;}
          lPass = true;}
        if (subsample == "ZCR" && passSemiResolvedMonoTopBambuZCR(preselection)
            && (combo=="ONLY" || (combo=="COMBO" && !passBoostedMonoTopBambuZCR(preselection)))){
          lPass = true;}
      }
    if (selection == "Bst15MonoHbb")
      {
        if (subsample == "SR" && passBoosted15MonoHbbBambuSR(preselection,CSVM,1000)
            && (combo=="ONLY" || combo=="COMBO")) {
          if(syst=="CENT"){btagw=sf_btag0*sf_sjbtag0;}
          if(syst=="BTAGUP"){btagw=sf_btag0BUp*sf_sjbtag0;}
          if(syst=="BTAGDO"){btagw=sf_btag0BDown*sf_sjbtag0;}
          if(syst=="MISTAGUP"){btagw=sf_btag0MUp*sf_sjbtag0;}
          if(syst=="MISTAGDO"){btagw=sf_btag0MDown*sf_sjbtag0;}
          if(syst=="SJBTAGUP"){btagw=sf_btag0*sf_sjbtag0BUp;}
          if(syst=="SJBTAGDO"){btagw=sf_btag0*sf_sjbtag0BDown;}
          if(syst=="SJMISTAGUP"){btagw=sf_btag0*sf_sjbtag0MUp;}
          if(syst=="SJMISTAGDO"){btagw=sf_btag0*sf_sjbtag0MDown;}
          lPass = true;}
        if (subsample == "TopCR" && passBoosted15MonoHbbBambuTopCR(preselection,CSVL,1000)
            && (combo=="ONLY" || combo=="COMBO")) {
          if(syst=="CENT"){btagw=sf_btag0*sf_sjbtag0;}
          if(syst=="BTAGUP"){btagw=sf_btag0BUp*sf_sjbtag0;}
          if(syst=="BTAGDO"){btagw=sf_btag0BDown*sf_sjbtag0;}
          if(syst=="MISTAGUP"){btagw=sf_btag0MUp*sf_sjbtag0;}
          if(syst=="MISTAGDO"){btagw=sf_btag0MDown*sf_sjbtag0;}
          if(syst=="SJBTAGUP"){btagw=sf_btag0*sf_sjbtag0BUp;}
          if(syst=="SJBTAGDO"){btagw=sf_btag0*sf_sjbtag0BDown;}
          if(syst=="SJMISTAGUP"){btagw=sf_btag0*sf_sjbtag0MUp;}
          if(syst=="SJMISTAGDO"){btagw=sf_btag0*sf_sjbtag0MDown;}
          lPass = true;}
        if (subsample == "WCR" && passBoosted15MonoHbbBambuWCR(preselection,CSVL,1000)
            && (combo=="ONLY" || combo=="COMBO")) {
          if(syst=="CENT"){btagw=sf_btag0*sf_sjbtag0;}
          if(syst=="BTAGUP"){btagw=sf_btag0BUp*sf_sjbtag0;}
          if(syst=="BTAGDO"){btagw=sf_btag0BDown*sf_sjbtag0;}
          if(syst=="MISTAGUP"){btagw=sf_btag0MUp*sf_sjbtag0;}
          if(syst=="MISTAGDO"){btagw=sf_btag0MDown*sf_sjbtag0;}
          if(syst=="SJBTAGUP"){btagw=sf_btag0*sf_sjbtag0BUp;}
          if(syst=="SJBTAGDO"){btagw=sf_btag0*sf_sjbtag0BDown;}
          if(syst=="SJMISTAGUP"){btagw=sf_btag0*sf_sjbtag0MUp;}
          if(syst=="SJMISTAGDO"){btagw=sf_btag0*sf_sjbtag0MDown;}
          lPass = true;}
        if (subsample == "ZCR" && passBoosted15MonoHbbBambuZCR(preselection)
            && (combo=="ONLY" || combo=="COMBO"))
          lPass = true;
      }
  }
  return lPass;
}
int MonoXBitsLoader::nfjets(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return nfjets15;
  else return nfjets15;
}
float MonoXBitsLoader::fjet_mass(string selection, bool isBacon){
  if(isBacon){
    if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return float(bst15_jet0_msd);
    else return float(bst15_jet0_msd);
  }
  else{
    return bst15_jet1_msd;
  }
}
float MonoXBitsLoader::fjet_pt(string selection,bool isBacon){
  if(isBacon){
    if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return float(bst15_jet0_pt);
    else return float(bst15_jet0_pt);
  }
  else{
    return bst15_jet1_pt;
  }
}
float MonoXBitsLoader::transverse_mass(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return float(bst15_jet0_mT);
  else{
    TLorentzVector v0; v0.SetPtEtaPhiM(res_jet0_pt,res_jet0_eta,res_jet0_phi,res_jet0_mass);
    TLorentzVector v1; v1.SetPtEtaPhiM(res_jet1_pt,res_jet1_eta,res_jet1_phi,res_jet1_mass);
    TLorentzVector lVecCorr = v0+v1;
    float lDPhi = fabs(vmetphi-lVecCorr.Phi());
    return sqrt(2.0*(lVecCorr.Pt()*vmetpt*(1.0-cos(lDPhi))));
  }
}
float MonoXBitsLoader::tau21(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_tau21;
  else return bst15_jet0_tau21;
}
float MonoXBitsLoader::tau32(string selection,bool isBacon){
  if(isBacon){
    if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_tau32;
    else return bst15_jet0_tau32;
  }
  else{
    return bst15_jet1_tau3/bst15_jet1_tau2;
  }
}
float MonoXBitsLoader::rho(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_rho;
  else return bst15_jet0_rho;
}
float MonoXBitsLoader::maxsubcsv(string selection,bool isBacon){
  if(isBacon){
    if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return float(bst15_jet0_maxsubcsv);
    else return bst15_jet0_maxsubcsv;
  }
  else{
    return bst15_jet1_maxsubcsv;
  }
}
float MonoXBitsLoader::minsubcsv(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return float(bst15_jet0_minsubcsv);
  else return bst15_jet0_minsubcsv;
}
float MonoXBitsLoader::doublecsv(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return float(bst15_jet0_doublecsv);
  else return bst15_jet0_doublecsv;
}
float MonoXBitsLoader::chf(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_CHF;
  else return bst15_jet0_CHF;
}
float MonoXBitsLoader::nhf(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_NHF;
  else return res_jet0_NHF;
}
float MonoXBitsLoader::nemf(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_NEMF;
  else return res_jet0_NEMF;
}
double MonoXBitsLoader::tau21DDT(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_tau21 + 0.063*bst15_jet0_rho;
  return bst15_jet0_tau21 + 0.063*bst15_jet0_rho;
}
double MonoXBitsLoader::getdRsj0dR(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_dRsj0dR;
  return bst15_jet0_dRsj0dR;
}
double MonoXBitsLoader::getdRsj0dRpt(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_dRsj0dR*bst15_jet0_dRsj0dR*(bst15_jet0_pt/bst15_jet0_msd);
  return (bst15_jet0_dRsj0dR*bst15_jet0_dRsj0dR)*(bst15_jet0_pt/bst15_jet0_msd);
}
double MonoXBitsLoader::getdPsj0dP(string selection){
  if(selection == "Bst15MonoTop" || selection == "Bst15MonoHbb") return bst15_jet0_dPhiJRFsj0dPhiJRF;
  return bst15_jet0_dPhiJRFsj0dPhiJRF;
}
float MonoXBitsLoader::getPhotonPurity(){
  if (vpho0_pt>=175 && vpho0_pt<200) return 0.04802;
  else if (vpho0_pt>=200 && vpho0_pt<250) return 0.04241;
  else if (vpho0_pt>=250 && vpho0_pt<300) return 0.03641;
  else if (vpho0_pt>=300 && vpho0_pt<350) return 0.0333;
  else if (vpho0_pt>=350)                 return 0.02544;
  else return 1;
}
