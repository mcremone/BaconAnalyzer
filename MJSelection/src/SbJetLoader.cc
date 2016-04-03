#include "../include/SbJetLoader.hh"
#include <cmath>
#include <iostream> 

#include <string>
#include <sstream>

using namespace baconhep;

SbJetLoader::SbJetLoader(TTree *iTree,std::string iJet,std::string iAddJet) { 
  fSbJets         = new TClonesArray("baconhep::TJet");
  fVAddJets      = new TClonesArray("baconhep::TAddJet");

  iTree->SetBranchAddress(iJet.c_str(),       &fSbJets);
  iTree->SetBranchAddress(iAddJet.c_str(),    &fVAddJets);
  fSbJetBr        = iTree->GetBranch(iJet.c_str());
  fVAddJetBr     = iTree->GetBranch(iAddJet.c_str());

  fN = 1;
}
SbJetLoader::~SbJetLoader() { 
  delete fSbJets;
  delete fSbJetBr;
  delete fVAddJets;
  delete fVAddJetBr;
}
void SbJetLoader::reset() { 
  fNSbJets = 0; 
  fVMT    = 0;
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
  fSbLabels.push_back("tau1_trackSip3dSig_0");
  fSbLabels.push_back("tau1_trackSip3dSig_1");
  for(auto i0 : trackTypes){
    fSbLabels.push_back("trackSip3dSig_3_"+i0);
    fSbLabels.push_back("trackSip3dSig_2_"+i0);
    fSbLabels.push_back("trackSip3dSig_1_"+i0);
    fSbLabels.push_back("trackSip3dSig_0_"+i0);
    fSbLabels.push_back("tau1_trackSip3dSig_0_"+i0);
    fSbLabels.push_back("tau1_trackSip3dSig_1_"+i0);
  }
  for(auto i0 : varTypes){
    fSbLabels.push_back("trackSip2dSigAboveCharm_"+i0);
    fSbLabels.push_back("trackSip2dSigAboveBottom_"+i0);
    for(auto itype : tauTypes){
      fSbLabels.push_back("tau_SV"+itype+i0+"_nSecondaryVertices");
      fSbLabels.push_back("tau_SV"+itype+i0+"flightDistance2dSig");
      fSbLabels.push_back("tau_SV"+itype+i0+"vertexDeltaR");
      fSbLabels.push_back("tau_SV"+itype+i0+"vertexNTracks");
      fSbLabels.push_back("tau_SV"+itype+i0+"trackEtaRel_2");
      fSbLabels.push_back("tau_SV"+itype+i0+"trackEtaRel_1");
      fSbLabels.push_back("tau_SV"+itype+i0+"trackEtaRel_0");
      fSbLabels.push_back("tau_SV"+itype+i0+"vertexEnergyRatio");
      fSbLabels.push_back("tau_SV"+itype+i0+"vertexMass");
      fSbLabels.push_back("tau_SV"+itype+i0+"vertexMass_corrected");
      fSbLabels.push_back("tau_SV"+itype+i0+"zratio");
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
}
void SbJetLoader::load(int iEvent) { 
  fSbJets       ->Clear();
  fSbJetBr      ->GetEntry(iEvent);
  fVAddJets    ->Clear();
  fVAddJetBr   ->GetEntry(iEvent);
}
void SbJetLoader::selectSbJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,double dR){
  reset(); 
  int lCount = 0; 
  for  (int i0 = 0; i0 < fSbJets->GetEntriesFast(); i0++) { 
    TJet *pSbJet = (TJet*)((*fSbJets)[i0]);
    if(pSbJet->pt        <=  200)                    continue;
    if(fabs(pSbJet->eta) >=  2.4)                    continue;
    if(passVeto(pSbJet->eta,pSbJet->phi,dR,iVetoes))  continue;
    if(!passJetLooseSel(pSbJet))                     continue;
    addVJet(pSbJet,iJets,pSbJet->mass);
    addJet(pSbJet,fSelSbJets);
    lCount++;
  }
  fNSbJets      = lCount;
  if(fSelSbJets.size()>0){
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
    fillVJet(fN,fSelSbJets,fVars);
    fillSbJet(fSelSbJets,fSbVars); 
    for (unsigned int i0 = 0; i0 < fSbVars.size(); i0++) {
      std::cout << fSbVars[i0] << std::endl;
    }
  }
}                  
void SbJetLoader::fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals){
  int lBase = 3.*fN;
  int lMin = iObjects.size();
  int lNLabel = int(fLabels.size());
  if(iN < lMin) lMin = iN;
  for(int i0 = 0; i0 < lMin; i0++) {
    TAddJet *pAddJet = getAddJet(iObjects[i0]);
    iVals[lBase+i0*lNLabel+0]  = iObjects[i0]->mass;
    iVals[lBase+i0*lNLabel+1]  = iObjects[i0]->csv;
    iVals[lBase+i0*lNLabel+2]  = iObjects[i0]->chHadFrac;
    iVals[lBase+i0*lNLabel+3]  = iObjects[i0]->neuHadFrac;
    iVals[lBase+i0*lNLabel+4]  = iObjects[i0]->neuEmFrac;
    iVals[lBase+i0*lNLabel+5]  = (pAddJet->tau2/pAddJet->tau1);
    iVals[lBase+i0*lNLabel+6]  = (pAddJet->tau3/pAddJet->tau2);
    iVals[lBase+i0*lNLabel+7]  = pAddJet     ->mass_sd0;
    iVals[lBase+i0*lNLabel+8]  = TMath::Min(pAddJet->sj1_csv,pAddJet->sj2_csv);
    iVals[lBase+i0*lNLabel+9]  = TMath::Max(TMath::Max(pAddJet->sj1_csv,pAddJet->sj2_csv),TMath::Max(pAddJet->sj3_csv,pAddJet->sj4_csv));
    iVals[lBase+i0*lNLabel+10] = pAddJet     ->doublecsv;
  }
}
void SbJetLoader::fillSbJet(std::vector<TJet*> &iObjects,std::vector<float> &iVals){ 
  int iN = 1;
  int lMin = iObjects.size();
  if(iN < lMin) lMin = iN;
  for(int i0 = 0; i0 < lMin; i0++) {
    TAddJet *pAddSbJet = getAddJet(iObjects[i0]);
    iVals[0]=pAddSbJet->nTracks;
    iVals[1]=pAddSbJet->nSV;
    std::cout << iVals[1] << std::endl;
    iVals.push_back(pAddSbJet->trackSip3dSig_3);
    iVals.push_back(pAddSbJet->trackSip3dSig_2);
    iVals.push_back(pAddSbJet->trackSip3dSig_1);
    iVals.push_back(pAddSbJet->trackSip3dSig_0);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_0);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_1);
    iVals.push_back(pAddSbJet->trackSip3dSig_3_1);
    iVals.push_back(pAddSbJet->trackSip3dSig_2_1);
    iVals.push_back(pAddSbJet->trackSip3dSig_1_1);
    iVals.push_back(pAddSbJet->trackSip3dSig_0_1);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_0_1);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_1_1);
    iVals.push_back(pAddSbJet->trackSip3dSig_3_2);
    iVals.push_back(pAddSbJet->trackSip3dSig_2_2);
    iVals.push_back(pAddSbJet->trackSip3dSig_1_2);
    iVals.push_back(pAddSbJet->trackSip3dSig_0_2);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_0_2);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_1_2);
    iVals.push_back(pAddSbJet->trackSip3dSig_3_3);
    iVals.push_back(pAddSbJet->trackSip3dSig_2_3);
    iVals.push_back(pAddSbJet->trackSip3dSig_1_3);
    iVals.push_back(pAddSbJet->trackSip3dSig_0_3);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_0_3);
    iVals.push_back(pAddSbJet->tau1_trackSip3dSig_1_3);
    iVals.push_back(pAddSbJet->trackSip2dSigAboveCharm_0);
    iVals.push_back(pAddSbJet->trackSip2dSigAboveBottom_0);
    iVals.push_back(pAddSbJet->tau_SVmass0_nSecondaryVertices);
    iVals.push_back(pAddSbJet->tau_SVmass0_flightDistance2dSig);
    iVals.push_back(pAddSbJet->tau_SVmass0_vertexDeltaR);
    iVals.push_back(pAddSbJet->tau_SVmass0_vertexNTracks);
    iVals.push_back(pAddSbJet->tau_SVmass0_trackEtaRel_2);
    iVals.push_back(pAddSbJet->tau_SVmass0_trackEtaRel_1);
    iVals.push_back(pAddSbJet->tau_SVmass0_trackEtaRel_0);
    iVals.push_back(pAddSbJet->tau_SVmass0_vertexEnergyRatio);
    iVals.push_back(pAddSbJet->tau_SVmass0_vertexMass);
    iVals.push_back(pAddSbJet->tau_SVmass0_vertexMass_corrected);
    iVals.push_back(pAddSbJet->tau_SVmass0_zratio);
    iVals.push_back(pAddSbJet->tau_SVfd0_nSecondaryVertices);
    iVals.push_back(pAddSbJet->tau_SVfd0_flightDistance2dSig);
    iVals.push_back(pAddSbJet->tau_SVfd0_vertexDeltaR);
    iVals.push_back(pAddSbJet->tau_SVfd0_vertexNTracks);
    iVals.push_back(pAddSbJet->tau_SVfd0_trackEtaRel_2);
    iVals.push_back(pAddSbJet->tau_SVfd0_trackEtaRel_1);
    iVals.push_back(pAddSbJet->tau_SVfd0_trackEtaRel_0);
    iVals.push_back(pAddSbJet->tau_SVfd0_vertexEnergyRatio);
    iVals.push_back(pAddSbJet->tau_SVfd0_vertexMass);
    iVals.push_back(pAddSbJet->tau_SVfd0_vertexMass_corrected);
    iVals.push_back(pAddSbJet->tau_SVfd0_zratio);
    iVals.push_back(pAddSbJet->trackSip2dSigAboveCharm_1);
    iVals.push_back(pAddSbJet->trackSip2dSigAboveBottom_1);
    iVals.push_back(pAddSbJet->tau_SVmass1_nSecondaryVertices);
    iVals.push_back(pAddSbJet->tau_SVmass1_flightDistance2dSig);
    iVals.push_back(pAddSbJet->tau_SVmass1_vertexDeltaR);
    iVals.push_back(pAddSbJet->tau_SVmass1_vertexNTracks);
    iVals.push_back(pAddSbJet->tau_SVmass1_trackEtaRel_2);
    iVals.push_back(pAddSbJet->tau_SVmass1_trackEtaRel_1);
    iVals.push_back(pAddSbJet->tau_SVmass1_trackEtaRel_0);
    iVals.push_back(pAddSbJet->tau_SVmass1_vertexEnergyRatio);
    iVals.push_back(pAddSbJet->tau_SVmass1_vertexMass);
    iVals.push_back(pAddSbJet->tau_SVmass1_vertexMass_corrected);
    iVals.push_back(pAddSbJet->tau_SVmass1_zratio);
    iVals.push_back(pAddSbJet->tau_SVfd1_nSecondaryVertices);
    iVals.push_back(pAddSbJet->tau_SVfd1_flightDistance2dSig);
    iVals.push_back(pAddSbJet->tau_SVfd1_vertexDeltaR);
    iVals.push_back(pAddSbJet->tau_SVfd1_vertexNTracks);
    iVals.push_back(pAddSbJet->tau_SVfd1_trackEtaRel_2);
    iVals.push_back(pAddSbJet->tau_SVfd1_trackEtaRel_1);
    iVals.push_back(pAddSbJet->tau_SVfd1_trackEtaRel_0);
    iVals.push_back(pAddSbJet->tau_SVfd1_vertexEnergyRatio);
    iVals.push_back(pAddSbJet->tau_SVfd1_vertexMass);
    iVals.push_back(pAddSbJet->tau_SVfd1_vertexMass_corrected);
    iVals.push_back(pAddSbJet->tau_SVfd1_zratio);
    iVals.push_back(pAddSbJet->nSM);
    iVals.push_back(pAddSbJet->nSE);
    iVals.push_back(pAddSbJet->PFMuon_pt);
    iVals.push_back(pAddSbJet->PFMuon_eta);
    iVals.push_back(pAddSbJet->PFMuon_phi);
    iVals.push_back(pAddSbJet->PFMuon_ptRel);
    iVals.push_back(pAddSbJet->PFMuon_ratio);
    iVals.push_back(pAddSbJet->PFMuon_ratioRel);
    iVals.push_back(pAddSbJet->PFMuon_IP);
    iVals.push_back(pAddSbJet->PFMuon_IP2D);
    iVals.push_back(pAddSbJet->PFElectron_pt);
    iVals.push_back(pAddSbJet->PFElectron_eta);
    iVals.push_back(pAddSbJet->PFElectron_phi);
    iVals.push_back(pAddSbJet->PFElectron_ptRel);
    iVals.push_back(pAddSbJet->PFElectron_ratio);
    iVals.push_back(pAddSbJet->PFElectron_ratioRel);
    iVals.push_back(pAddSbJet->PFElectron_IP);
    iVals.push_back(pAddSbJet->PFElectron_IP2D);
  }
}
TAddJet *SbJetLoader::getAddJet(TJet *iJet) { 
  int lIndex = -1;
  TAddJet *lJet = 0; 
  for(int i0 = 0; i0 < fSbJets->GetEntriesFast(); i0++) { 
    if((*fSbJets)[i0] == iJet) { lIndex = i0; break;}
  }
  if(lIndex == -1) return 0;
  for  (int i0 = 0; i0 < fVAddJets->GetEntriesFast(); i0++) { 
    TAddJet *pJet = (TAddJet*)((*fVAddJets)[i0]);
    if(pJet->index == fabs(lIndex)) { lJet = pJet; break;}
  }
  return lJet;
}
