#include "../include/SbJetLoader.hh"
#include <cmath>
#include <iostream> 

#include <string>
#include <sstream>

using namespace baconhep;

SbJetLoader::SbJetLoader(TTree *iTree,std::string iJet,std::string iAddJet) { 
  fSbJets         = new TClonesArray("baconhep::TJet");
  fSbAddJets      = new TClonesArray("baconhep::TAddJet");

  iTree->SetBranchAddress(iJet.c_str(),       &fSbJets);
  iTree->SetBranchAddress(iAddJet.c_str(),    &fSbAddJets);
  fSbJetBr        = iTree->GetBranch(iJet.c_str());
  fSbAddJetBr     = iTree->GetBranch(iAddJet.c_str());

  fN = 1;
}
SbJetLoader::~SbJetLoader() { 
  delete fSbJets;
  delete fSbJetBr;
  delete fSbAddJets;
  delete fSbAddJetBr;
}
void SbJetLoader::reset() { 
  fNSbJets       = 0; 
  fVMT           = 0;
  ftopSize       = 999;
  ftopMatching   = 999;
  fisHadronicTop = 0;
  fSelSbJets.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  for(unsigned int i0 = 0; i0 < fSbVars.size(); i0++) fSbVars[i0] = 0;
}
void SbJetLoader::setupTree(TTree *iTree, std::string iJetLabel) { 
  reset();
  fLabels.clear();
  fLabels.push_back("mass");
  fLabels.push_back("csv");
  fLabels.push_back("CHF");
  fLabels.push_back("NHF");
  fLabels.push_back("NEFM");
  fLabels.push_back("tau21");
  fLabels.push_back("tau32");
  fLabels.push_back("msd");
  fLabels.push_back("minsubcsv");
  fLabels.push_back("maxsubcsv");
  fLabels.push_back("doublecsv");

  fSbLabels.clear();
  fSbLabels.push_back("nTracks");
  fSbLabels.push_back("nSV");
  fSbLabels.push_back("trackSip3dSig_3");
  fSbLabels.push_back("trackSip3dSig_2");
  fSbLabels.push_back("trackSip3dSig_1");
  fSbLabels.push_back("trackSip3dSig_0");
  for(auto i0 : trackTypes){
    fSbLabels.push_back("trackSip3dSig_3_"+i0);
    fSbLabels.push_back("trackSip3dSig_2_"+i0);
    fSbLabels.push_back("trackSip3dSig_1_"+i0);
    fSbLabels.push_back("trackSip3dSig_0_"+i0);
  }
  for(auto i0 : varTypes){
    fSbLabels.push_back("trackSip2dSigAboveCharm_"+i0);
    fSbLabels.push_back("trackSip2dSigAboveBottom_"+i0);
    for(auto itype : tauTypes){
      fSbLabels.push_back("tau_SV"+itype+i0+"_nSecondaryVertices");
      fSbLabels.push_back("tau_SV"+itype+i0+"_flightDistance2dSig");
      fSbLabels.push_back("tau_SV"+itype+i0+"_vertexDeltaR");
      fSbLabels.push_back("tau_SV"+itype+i0+"_vertexNTracks");
      fSbLabels.push_back("tau_SV"+itype+i0+"_trackEtaRel_2");
      fSbLabels.push_back("tau_SV"+itype+i0+"_trackEtaRel_1");
      fSbLabels.push_back("tau_SV"+itype+i0+"_trackEtaRel_0");
      fSbLabels.push_back("tau_SV"+itype+i0+"_vertexEnergyRatio");
      fSbLabels.push_back("tau_SV"+itype+i0+"_vertexMass");
      fSbLabels.push_back("tau_SV"+itype+i0+"_vertexMass_corrected");
      fSbLabels.push_back("tau_SV"+itype+i0+"_zratio");
    }
  }
  fSbLabels.push_back("nSM");
  fSbLabels.push_back("nSE");
  for(auto iSL : SLTypes) {
    fSbLabels.push_back("PF"+iSL+"_pt");
    fSbLabels.push_back("PF"+iSL+"_eta");
    fSbLabels.push_back("PF"+iSL+"_phi");
    fSbLabels.push_back("PF"+iSL+"_ptRel");
    fSbLabels.push_back("PF"+iSL+"_ratio");
    fSbLabels.push_back("PF"+iSL+"_ratioRel");
    fSbLabels.push_back("PF"+iSL+"_deltaR");
    fSbLabels.push_back("PF"+iSL+"_IP");
    fSbLabels.push_back("PF"+iSL+"_IP2D");
  }
  fTree = iTree;
  for(int i0 = 0; i0 < fN*3.;                    i0++) {double pVar = 0; fVars.push_back(pVar);}
  for(int i0 = 0; i0 < fN*(int(fLabels.size())); i0++) {double pVar = 0; fVars.push_back(pVar);} 
  for(int i0 = 0; i0 < fN*(int(fSbLabels.size())); i0++) {float pVar = 0; fSbVars.push_back(pVar);} 
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars);          
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars,fN*3,fLabels);
  setupNtuple(iJetLabel.c_str(),iTree,fN,fSbVars,fSbLabels);
  fTree->Branch("nfjets"          ,&fNSbJets          ,"fNSbJets/I");
  fTree->Branch("partonFlavor"    ,&fpartonFlavor     ,"fpartonFlavor/I");
  fTree->Branch("hadronFlavor"    ,&fhadronFlavor     ,"fhadronFlavor/I");
  fTree->Branch("nbHadrons"       ,&fnbHadrons        ,"fnbHadrons/I");
  fTree->Branch("ncHadrons"       ,&fncHadrons        ,"fncHadrons/I");
  fTree->Branch("topSize"         ,&ftopSize          ,"ftopSize/D");
  fTree->Branch("topMatching"     ,&ftopMatching      ,"ftopMatching/D");
  fTree->Branch("isHadronicTop"   ,&fisHadronicTop    ,"fisHadronicTop/I");
}
void SbJetLoader::load(int iEvent) { 
  fSbJets       ->Clear();
  fSbJetBr      ->GetEntry(iEvent);
  fSbAddJets    ->Clear();
  fSbAddJetBr   ->GetEntry(iEvent);
}
void SbJetLoader::selectSbJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,double dR){
  reset(); 
  int lCount = 0; 
  for  (int i0 = 0; i0 < fSbJets->GetEntriesFast(); i0++) { 
    TJet *pSbJet = (TJet*)((*fSbJets)[i0]);
    if(pSbJet->pt        <=  200)                    continue;
    if(fabs(pSbJet->eta) >=  2.4)                    continue;
    if(!passJetLooseSel(pSbJet))                     continue;
    addJet(pSbJet,fSelSbJets);
    lCount++;
  }
  fNSbJets      = lCount;
  if(fSelSbJets.size()>0){
    addVJet(fSelSbJets[0],iJets,fSelSbJets[0]->mass);
    fpartonFlavor   = fSelSbJets[0]->partonFlavor;
    fhadronFlavor   = fSelSbJets[0]->hadronFlavor;
    fnbHadrons      = fSelSbJets[0]->nbHadrons;
    fncHadrons      = fSelSbJets[0]->ncHadrons;
    // fnchHadCharged  = fSelSbJets[0]->nchHadCharged;
    // fnneuHadCharged = fSelSbJets[0]->nneuHadCharged;
    // fnCharged       = fSelSbJets[0]->nCharged;
    // fnNeutrals      = fSelSbJets[0]->nNeutrals;
    // fnParticles     = fSelSbJets[0]->nParticles;
    fillJet(fN,fSelSbJets,fVars);
    fillVJet(fN,fSelSbJets,fVars,fSbVars); 
  }
}                  
void SbJetLoader::fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals,std::vector<float> &iSbVals){
  int lBase = 3.*fN;
  int lMin = iObjects.size();
  int lNLabel = int(fLabels.size());
  if(iN < lMin) lMin = iN;
  for(int i0 = 0; i0 < lMin; i0++) {
    TAddJet *pAddJet = getAddJet(iObjects[i0]);
    iVals[lBase+i0*lNLabel+0]   = iObjects[i0]->mass;
    iVals[lBase+i0*lNLabel+1]   = iObjects[i0]->csv;
    iVals[lBase+i0*lNLabel+2]   = iObjects[i0]->chHadFrac;
    iVals[lBase+i0*lNLabel+3]   = iObjects[i0]->neuHadFrac;
    iVals[lBase+i0*lNLabel+4]   = iObjects[i0]->neuEmFrac;
    iVals[lBase+i0*lNLabel+5]   = (pAddJet->tau2/pAddJet->tau1);
    iVals[lBase+i0*lNLabel+6]   = (pAddJet->tau3/pAddJet->tau2);
    iVals[lBase+i0*lNLabel+7]   = pAddJet     ->mass_sd0;
    iVals[lBase+i0*lNLabel+8]   = TMath::Min(pAddJet->sj1_csv,pAddJet->sj2_csv);
    iVals[lBase+i0*lNLabel+9]   = TMath::Max(TMath::Max(pAddJet->sj1_csv,pAddJet->sj2_csv),TMath::Max(pAddJet->sj3_csv,pAddJet->sj4_csv));
    iVals[lBase+i0*lNLabel+10]  = pAddJet     ->doublecsv;
    iSbVals[i0*lNLabel+0]       = pAddJet     ->nTracks;
    iSbVals[i0*lNLabel+1]       = pAddJet     ->nSV;
    iSbVals[i0*lNLabel+2]       = pAddJet     ->trackSip3dSig_3;
    iSbVals[i0*lNLabel+3]       = pAddJet     ->trackSip3dSig_2;
    iSbVals[i0*lNLabel+4]       = pAddJet     ->trackSip3dSig_1;
    iSbVals[i0*lNLabel+5]       = pAddJet     ->trackSip3dSig_0;
    iSbVals[i0*lNLabel+6]       = pAddJet     ->trackSip3dSig_3_1;
    iSbVals[i0*lNLabel+7]       = pAddJet     ->trackSip3dSig_2_1;
    iSbVals[i0*lNLabel+8]       = pAddJet     ->trackSip3dSig_1_1;
    iSbVals[i0*lNLabel+9]       = pAddJet     ->trackSip3dSig_0_1;
    iSbVals[i0*lNLabel+10]      = pAddJet     ->trackSip3dSig_3_2;
    iSbVals[i0*lNLabel+11]      = pAddJet     ->trackSip3dSig_2_2;
    iSbVals[i0*lNLabel+12]      = pAddJet     ->trackSip3dSig_1_2;
    iSbVals[i0*lNLabel+13]      = pAddJet     ->trackSip3dSig_0_2;
    iSbVals[i0*lNLabel+14]      = pAddJet     ->trackSip3dSig_3_3;
    iSbVals[i0*lNLabel+15]      = pAddJet     ->trackSip3dSig_2_3;
    iSbVals[i0*lNLabel+16]      = pAddJet     ->trackSip3dSig_1_3;
    iSbVals[i0*lNLabel+17]      = pAddJet     ->trackSip3dSig_0_3;
    iSbVals[i0*lNLabel+18]      = pAddJet     ->trackSip2dSigAboveCharm_0;
    iSbVals[i0*lNLabel+19]      = pAddJet     ->trackSip2dSigAboveBottom_0;
    iSbVals[i0*lNLabel+20]      = pAddJet     ->tau_SVmass0_nSecondaryVertices;
    iSbVals[i0*lNLabel+21]      = pAddJet     ->tau_SVmass0_flightDistance2dSig;
    iSbVals[i0*lNLabel+22]      = pAddJet     ->tau_SVmass0_vertexDeltaR;
    iSbVals[i0*lNLabel+23]      = pAddJet     ->tau_SVmass0_vertexNTracks;
    iSbVals[i0*lNLabel+24]      = pAddJet     ->tau_SVmass0_trackEtaRel_2;
    iSbVals[i0*lNLabel+25]      = pAddJet     ->tau_SVmass0_trackEtaRel_1;
    iSbVals[i0*lNLabel+26]      = pAddJet     ->tau_SVmass0_trackEtaRel_0;
    iSbVals[i0*lNLabel+27]      = pAddJet     ->tau_SVmass0_vertexEnergyRatio;
    iSbVals[i0*lNLabel+28]      = pAddJet     ->tau_SVmass0_vertexMass;
    iSbVals[i0*lNLabel+29]      = pAddJet     ->tau_SVmass0_vertexMass_corrected;
    iSbVals[i0*lNLabel+30]      = pAddJet     ->tau_SVmass0_zratio;
    iSbVals[i0*lNLabel+31]      = pAddJet     ->tau_SVfd0_nSecondaryVertices;
    iSbVals[i0*lNLabel+32]      = pAddJet     ->tau_SVfd0_flightDistance2dSig;
    iSbVals[i0*lNLabel+33]      = pAddJet     ->tau_SVfd0_vertexDeltaR;
    iSbVals[i0*lNLabel+34]      = pAddJet     ->tau_SVfd0_vertexNTracks;
    iSbVals[i0*lNLabel+35]      = pAddJet     ->tau_SVfd0_trackEtaRel_2;
    iSbVals[i0*lNLabel+36]      = pAddJet     ->tau_SVfd0_trackEtaRel_1;
    iSbVals[i0*lNLabel+37]      = pAddJet     ->tau_SVfd0_trackEtaRel_0;
    iSbVals[i0*lNLabel+38]      = pAddJet     ->tau_SVfd0_vertexEnergyRatio;
    iSbVals[i0*lNLabel+39]      = pAddJet     ->tau_SVfd0_vertexMass;
    iSbVals[i0*lNLabel+40]      = pAddJet     ->tau_SVfd0_vertexMass_corrected;
    iSbVals[i0*lNLabel+41]      = pAddJet     ->tau_SVfd0_zratio;
    iSbVals[i0*lNLabel+42]      = pAddJet     ->trackSip2dSigAboveCharm_1;
    iSbVals[i0*lNLabel+43]      = pAddJet     ->trackSip2dSigAboveBottom_1;
    iSbVals[i0*lNLabel+44]      = pAddJet     ->tau_SVmass1_nSecondaryVertices;
    iSbVals[i0*lNLabel+45]      = pAddJet     ->tau_SVmass1_flightDistance2dSig;
    iSbVals[i0*lNLabel+46]      = pAddJet     ->tau_SVmass1_vertexDeltaR;
    iSbVals[i0*lNLabel+47]      = pAddJet     ->tau_SVmass1_vertexNTracks;
    iSbVals[i0*lNLabel+48]      = pAddJet     ->tau_SVmass1_trackEtaRel_2;
    iSbVals[i0*lNLabel+49]      = pAddJet     ->tau_SVmass1_trackEtaRel_1;
    iSbVals[i0*lNLabel+50]      = pAddJet     ->tau_SVmass1_trackEtaRel_0;
    iSbVals[i0*lNLabel+51]      = pAddJet     ->tau_SVmass1_vertexEnergyRatio;
    iSbVals[i0*lNLabel+52]      = pAddJet     ->tau_SVmass1_vertexMass;
    iSbVals[i0*lNLabel+53]      = pAddJet     ->tau_SVmass1_vertexMass_corrected;
    iSbVals[i0*lNLabel+54]      = pAddJet     ->tau_SVmass1_zratio;
    iSbVals[i0*lNLabel+55]      = pAddJet     ->tau_SVfd1_nSecondaryVertices;
    iSbVals[i0*lNLabel+56]      = pAddJet     ->tau_SVfd1_flightDistance2dSig;
    iSbVals[i0*lNLabel+57]      = pAddJet     ->tau_SVfd1_vertexDeltaR;
    iSbVals[i0*lNLabel+58]      = pAddJet     ->tau_SVfd1_vertexNTracks;
    iSbVals[i0*lNLabel+59]      = pAddJet     ->tau_SVfd1_trackEtaRel_2;
    iSbVals[i0*lNLabel+60]      = pAddJet     ->tau_SVfd1_trackEtaRel_1;
    iSbVals[i0*lNLabel+61]      = pAddJet     ->tau_SVfd1_trackEtaRel_0;
    iSbVals[i0*lNLabel+62]      = pAddJet     ->tau_SVfd1_vertexEnergyRatio;
    iSbVals[i0*lNLabel+63]      = pAddJet     ->tau_SVfd1_vertexMass;
    iSbVals[i0*lNLabel+64]      = pAddJet     ->tau_SVfd1_vertexMass_corrected;
    iSbVals[i0*lNLabel+65]      = pAddJet     ->tau_SVfd1_zratio;
    iSbVals[i0*lNLabel+66]      = pAddJet     ->nSM;
    iSbVals[i0*lNLabel+67]      = pAddJet     ->nSE;
    iSbVals[i0*lNLabel+68]      = pAddJet     ->PFMuon_pt;
    iSbVals[i0*lNLabel+69]      = pAddJet     ->PFMuon_eta;
    iSbVals[i0*lNLabel+70]      = pAddJet     ->PFMuon_phi;
    iSbVals[i0*lNLabel+71]      = pAddJet     ->PFMuon_ptRel;
    iSbVals[i0*lNLabel+72]      = pAddJet     ->PFMuon_ratio;
    iSbVals[i0*lNLabel+73]      = pAddJet     ->PFMuon_ratioRel;
    iSbVals[i0*lNLabel+74]      = pAddJet     ->PFMuon_IP;
    iSbVals[i0*lNLabel+75]      = pAddJet     ->PFMuon_IP2D;
    iSbVals[i0*lNLabel+76]      = pAddJet     ->PFElectron_pt;
    iSbVals[i0*lNLabel+77]      = pAddJet     ->PFElectron_eta;
    iSbVals[i0*lNLabel+78]      = pAddJet     ->PFElectron_phi;
    iSbVals[i0*lNLabel+79]      = pAddJet     ->PFElectron_ptRel;
    iSbVals[i0*lNLabel+80]      = pAddJet     ->PFElectron_ratio;
    iSbVals[i0*lNLabel+81]      = pAddJet     ->PFElectron_ratioRel;
    iSbVals[i0*lNLabel+82]      = pAddJet     ->PFElectron_IP;
    iSbVals[i0*lNLabel+83]      = pAddJet     ->PFElectron_IP2D;
  }
}
TAddJet *SbJetLoader::getAddJet(TJet *iJet) { 
  int lIndex = -1;
  TAddJet *lJet = 0; 
  for(int i0 = 0; i0 < fSbJets->GetEntriesFast(); i0++) { 
    if((*fSbJets)[i0] == iJet) { lIndex = i0; break;}
  }
  if(lIndex == -1) return 0;
  for  (int i0 = 0; i0 < fSbAddJets->GetEntriesFast(); i0++) { 
    TAddJet *pJet = (TAddJet*)((*fSbAddJets)[i0]);
    if(pJet->index == fabs(lIndex)) { lJet = pJet; break;}
  }
  return lJet;
}
