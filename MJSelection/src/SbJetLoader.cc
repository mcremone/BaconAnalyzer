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
  fLabels.push_back("doublecsv");
  fLabels.push_back("maxsubcsv");
  fLabels.push_back("nTracks");
  fLabels.push_back("nSV");
  fLabels.push_back("trackSip3dSig_3");
  fLabels.push_back("trackSip3dSig_2");
  fLabels.push_back("trackSip3dSig_1");
  fLabels.push_back("trackSip3dSig_0");
  fLabels.push_back("tau1_trackSip3dSig_0");
  fLabels.push_back("tau1_trackSip3dSig_1");
  for(auto i0 : trackTypes){
    fLabels.push_back("trackSip3dSig_3_"+i0);
    fLabels.push_back("trackSip3dSig_2_"+i0);
    fLabels.push_back("trackSip3dSig_1_"+i0);
    fLabels.push_back("trackSip3dSig_0_"+i0);
    fLabels.push_back("tau1_trackSip3dSig_0_"+i0);
    fLabels.push_back("tau1_trackSip3dSig_1_"+i0);
  }
  for(auto i0 : varTypes){
    fLabels.push_back("trackSip2dSigAboveCharm_"+i0);
    fLabels.push_back("trackSip2dSigAboveBottom_"+i0);
    for(auto itype : tauTypes){
      fLabels.push_back("tau_SV"+itype+i0+"_nSecondaryVertices");
      fLabels.push_back("tau_SV"+itype+i0+"flightDistance2dSig");
      fLabels.push_back("tau_SV"+itype+i0+"vertexDeltaR");
      fLabels.push_back("tau_SV"+itype+i0+"vertexNTracks");
      fLabels.push_back("tau_SV"+itype+i0+"trackEtaRel_2");
      fLabels.push_back("tau_SV"+itype+i0+"trackEtaRel_1");
      fLabels.push_back("tau_SV"+itype+i0+"trackEtaRel_0");
      fLabels.push_back("tau_SV"+itype+i0+"vertexEnergyRatio");
      fLabels.push_back("tau_SV"+itype+i0+"vertexMass");
      fLabels.push_back("tau_SV"+itype+i0+"vertexMass_corrected");
      fLabels.push_back("tau_SV"+itype+i0+"zratio");
    }
  }
  fLabels.push_back("nSM");
  fLabels.push_back("nSE");
  for(auto iSL : SLTypes) {
    fLabels.push_back("PF"+iSL+"_pt");
    fLabels.push_back("PF"+iSL+"_eta");
    fLabels.push_back("PF"+iSL+"_phi");
    fLabels.push_back("PF"+iSL+"_ptRel");
    fLabels.push_back("PF"+iSL+"_ratio");
    fLabels.push_back("PF"+iSL+"_ratioRel");
    fLabels.push_back("PF"+iSL+"_deltaR");
    fLabels.push_back("PF"+iSL+"_IP");
    fLabels.push_back("PF"+iSL+"_IP2D");
  }
  fTree = iTree;
  for(int i0 = 0; i0 < fN*4.;                    i0++) {double pVar = 0; fVars.push_back(pVar);} 
  for(int i0 = 0; i0 < fN*(int(fLabels.size())); i0++) {double pVar = 0; fVars.push_back(pVar);} 
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars);                                                 
  setupNtuple(iJetLabel.c_str(),iTree,fN,fVars,fN*1,fLabels);
  fTree->Branch("nfjets"          ,&fNSbJets          ,"fNSbJets/I");
  fTree->Branch("partonFlavor"    ,&fpartonFlavor     ,"fpartonFlavor/I");
  fTree->Branch("hadronFlavor"    ,&fhadronFlavor     ,"fhadronFlavor/I");
  fTree->Branch("nbHadrons"       ,&fnbHadrons        ,"fnbHadrons/I");
  fTree->Branch("ncHadrons"       ,&fncHadrons        ,"fncHadrons/I");
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
  fpartonFlavor   = fSelSbJets[0]->partonFlavor;
  fhadronFlavor   = fSelSbJets[0]->hadronFlavor;
  fnbHadrons      = fSelSbJets[0]->nbHadrons;
  fncHadrons      = fSelSbJets[0]->ncHadrons;
  // fnchHadCharged  = fSelSbJets[0]->nchHadCharged;
  // fnneuHadCharged = fSelSbJets[0]->nneuHadCharged;
  // fnCharged       = fSelSbJets[0]->nCharged;
  // fnNeutrals      = fSelSbJets[0]->nNeutrals;
  // fnParticles     = fSelSbJets[0]->nParticles;
  fillJet( fN,fSelSbJets,fVars);
  fillSbJet(fN,fSelSbJets,fVars); 
}                  
void SbJetLoader::fillSbJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals){ 
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
    iVals[lBase+i0*lNLabel+7]  = pAddJet->mass_sd0;
    iVals[lBase+i0*lNLabel+8]  = pAddJet->doublecsv;
    iVals[lBase+i0*lNLabel+9]  = TMath::Max(TMath::Max(pAddJet->sj1_csv,pAddJet->sj2_csv),TMath::Max(pAddJet->sj3_csv,pAddJet->sj4_csv));
    iVals[lBase+i0*lNLabel+10] = pAddJet->nTracks;
    iVals[lBase+i0*lNLabel+11] = pAddJet->nSV;
    iVals[lBase+i0*lNLabel+12] = pAddJet->nTracks;
    iVals[lBase+i0*lNLabel+13] = pAddJet->trackSip3dSig_3;
    iVals[lBase+i0*lNLabel+14] = pAddJet->trackSip3dSig_2;
    iVals[lBase+i0*lNLabel+15] = pAddJet->trackSip3dSig_1;
    iVals[lBase+i0*lNLabel+16] = pAddJet->trackSip3dSig_0;
    iVals[lBase+i0*lNLabel+17] = pAddJet->tau1_trackSip3dSig_0;
    iVals[lBase+i0*lNLabel+18] = pAddJet->tau1_trackSip3dSig_1;
    iVals[lBase+i0*lNLabel+19] = pAddJet->trackSip3dSig_3_1;
    iVals[lBase+i0*lNLabel+20] = pAddJet->trackSip3dSig_2_1;
    iVals[lBase+i0*lNLabel+21] = pAddJet->trackSip3dSig_1_1;
    iVals[lBase+i0*lNLabel+22] = pAddJet->trackSip3dSig_0_1;
    iVals[lBase+i0*lNLabel+23] = pAddJet->tau1_trackSip3dSig_0_1;
    iVals[lBase+i0*lNLabel+24] = pAddJet->tau1_trackSip3dSig_1_1;
    iVals[lBase+i0*lNLabel+25] = pAddJet->trackSip3dSig_3_2;
    iVals[lBase+i0*lNLabel+26] = pAddJet->trackSip3dSig_2_2;
    iVals[lBase+i0*lNLabel+27] = pAddJet->trackSip3dSig_1_2;
    iVals[lBase+i0*lNLabel+28] = pAddJet->trackSip3dSig_0_2;
    iVals[lBase+i0*lNLabel+29] = pAddJet->tau1_trackSip3dSig_0_2;
    iVals[lBase+i0*lNLabel+30] = pAddJet->tau1_trackSip3dSig_1_2;
    iVals[lBase+i0*lNLabel+31] = pAddJet->trackSip3dSig_3_3;
    iVals[lBase+i0*lNLabel+32] = pAddJet->trackSip3dSig_2_3;
    iVals[lBase+i0*lNLabel+33] = pAddJet->trackSip3dSig_1_3;
    iVals[lBase+i0*lNLabel+34] = pAddJet->trackSip3dSig_0_3;
    iVals[lBase+i0*lNLabel+35] = pAddJet->tau1_trackSip3dSig_0_3;
    iVals[lBase+i0*lNLabel+36] = pAddJet->tau1_trackSip3dSig_1_3;
    iVals[lBase+i0*lNLabel+37] = pAddJet->trackSip2dSigAboveCharm_0;
    iVals[lBase+i0*lNLabel+38] = pAddJet->trackSip2dSigAboveBottom_0;
    iVals[lBase+i0*lNLabel+39] = pAddJet->tau_SVmass0_nSecondaryVertices;
    iVals[lBase+i0*lNLabel+40] = pAddJet->tau_SVmass0_flightDistance2dSig;
    iVals[lBase+i0*lNLabel+41] = pAddJet->tau_SVmass0_vertexDeltaR;
    iVals[lBase+i0*lNLabel+42] = pAddJet->tau_SVmass0_vertexNTracks;
    iVals[lBase+i0*lNLabel+43] = pAddJet->tau_SVmass0_trackEtaRel_2;
    iVals[lBase+i0*lNLabel+44] = pAddJet->tau_SVmass0_trackEtaRel_1;
    iVals[lBase+i0*lNLabel+45] = pAddJet->tau_SVmass0_trackEtaRel_0;
    iVals[lBase+i0*lNLabel+46] = pAddJet->tau_SVmass0_vertexEnergyRatio;
    iVals[lBase+i0*lNLabel+47] = pAddJet->tau_SVmass0_vertexMass;
    iVals[lBase+i0*lNLabel+48] = pAddJet->tau_SVmass0_vertexMass_corrected;
    iVals[lBase+i0*lNLabel+49] = pAddJet->tau_SVmass0_zratio;
    iVals[lBase+i0*lNLabel+50] = pAddJet->tau_SVfd0_nSecondaryVertices;
    iVals[lBase+i0*lNLabel+51] = pAddJet->tau_SVfd0_flightDistance2dSig;
    iVals[lBase+i0*lNLabel+52] = pAddJet->tau_SVfd0_vertexDeltaR;
    iVals[lBase+i0*lNLabel+53] = pAddJet->tau_SVfd0_vertexNTracks;
    iVals[lBase+i0*lNLabel+54] = pAddJet->tau_SVfd0_trackEtaRel_2;
    iVals[lBase+i0*lNLabel+55] = pAddJet->tau_SVfd0_trackEtaRel_1;
    iVals[lBase+i0*lNLabel+56] = pAddJet->tau_SVfd0_trackEtaRel_0;
    iVals[lBase+i0*lNLabel+57] = pAddJet->tau_SVfd0_vertexEnergyRatio;
    iVals[lBase+i0*lNLabel+58] = pAddJet->tau_SVfd0_vertexMass;
    iVals[lBase+i0*lNLabel+59] = pAddJet->tau_SVfd0_vertexMass_corrected;
    iVals[lBase+i0*lNLabel+60] = pAddJet->tau_SVfd0_zratio;
    iVals[lBase+i0*lNLabel+61] = pAddJet->trackSip2dSigAboveCharm_1;
    iVals[lBase+i0*lNLabel+62] = pAddJet->trackSip2dSigAboveBottom_1;
    iVals[lBase+i0*lNLabel+63] = pAddJet->tau_SVmass1_nSecondaryVertices;
    iVals[lBase+i0*lNLabel+64] = pAddJet->tau_SVmass1_flightDistance2dSig;
    iVals[lBase+i0*lNLabel+65] = pAddJet->tau_SVmass1_vertexDeltaR;
    iVals[lBase+i0*lNLabel+66] = pAddJet->tau_SVmass1_vertexNTracks;
    iVals[lBase+i0*lNLabel+67] = pAddJet->tau_SVmass1_trackEtaRel_2;
    iVals[lBase+i0*lNLabel+68] = pAddJet->tau_SVmass1_trackEtaRel_1;
    iVals[lBase+i0*lNLabel+69] = pAddJet->tau_SVmass1_trackEtaRel_0;
    iVals[lBase+i0*lNLabel+70] = pAddJet->tau_SVmass1_vertexEnergyRatio;
    iVals[lBase+i0*lNLabel+71] = pAddJet->tau_SVmass1_vertexMass;
    iVals[lBase+i0*lNLabel+72] = pAddJet->tau_SVmass1_vertexMass_corrected;
    iVals[lBase+i0*lNLabel+73] = pAddJet->tau_SVmass1_zratio;
    iVals[lBase+i0*lNLabel+74] = pAddJet->tau_SVfd1_nSecondaryVertices;
    iVals[lBase+i0*lNLabel+75] = pAddJet->tau_SVfd1_flightDistance2dSig;
    iVals[lBase+i0*lNLabel+76] = pAddJet->tau_SVfd1_vertexDeltaR;
    iVals[lBase+i0*lNLabel+77] = pAddJet->tau_SVfd1_vertexNTracks;
    iVals[lBase+i0*lNLabel+78] = pAddJet->tau_SVfd1_trackEtaRel_2;
    iVals[lBase+i0*lNLabel+79] = pAddJet->tau_SVfd1_trackEtaRel_1;
    iVals[lBase+i0*lNLabel+80] = pAddJet->tau_SVfd1_trackEtaRel_0;
    iVals[lBase+i0*lNLabel+81] = pAddJet->tau_SVfd1_vertexEnergyRatio;
    iVals[lBase+i0*lNLabel+82] = pAddJet->tau_SVfd1_vertexMass;
    iVals[lBase+i0*lNLabel+83] = pAddJet->tau_SVfd1_vertexMass_corrected;
    iVals[lBase+i0*lNLabel+84] = pAddJet->tau_SVfd1_zratio;
    iVals[lBase+i0*lNLabel+85] = pAddJet->nSM;
    iVals[lBase+i0*lNLabel+86] = pAddJet->nSE;
    iVals[lBase+i0*lNLabel+87] = pAddJet->PFMuon_pt;
    iVals[lBase+i0*lNLabel+88] = pAddJet->PFMuon_eta;
    iVals[lBase+i0*lNLabel+89] = pAddJet->PFMuon_phi;
    iVals[lBase+i0*lNLabel+90] = pAddJet->PFMuon_ptRel;
    iVals[lBase+i0*lNLabel+91] = pAddJet->PFMuon_ratio;
    iVals[lBase+i0*lNLabel+92] = pAddJet->PFMuon_ratioRel;
    iVals[lBase+i0*lNLabel+93] = pAddJet->PFMuon_deltaR;
    iVals[lBase+i0*lNLabel+94] = pAddJet->PFMuon_IP;
    iVals[lBase+i0*lNLabel+95] = pAddJet->PFMuon_IP2D;
    iVals[lBase+i0*lNLabel+96] = pAddJet->PFElectron_pt;
    iVals[lBase+i0*lNLabel+97] = pAddJet->PFElectron_eta;
    iVals[lBase+i0*lNLabel+98] = pAddJet->PFElectron_phi;
    iVals[lBase+i0*lNLabel+99] = pAddJet->PFElectron_ptRel;
    iVals[lBase+i0*lNLabel+100]= pAddJet->PFElectron_ratio;
    iVals[lBase+i0*lNLabel+101]= pAddJet->PFElectron_ratioRel;
    iVals[lBase+i0*lNLabel+102]= pAddJet->PFElectron_deltaR;
    iVals[lBase+i0*lNLabel+103]= pAddJet->PFElectron_IP;
    iVals[lBase+i0*lNLabel+104]= pAddJet->PFElectron_IP2D;
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
