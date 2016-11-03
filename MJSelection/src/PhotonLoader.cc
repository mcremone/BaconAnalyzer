#include "../include/PhotonLoader.hh"
#include <cmath>
#include <iostream> 

using namespace baconhep;

PhotonLoader::PhotonLoader(TTree *iTree) { 
  fPhotons  = new TClonesArray("baconhep::TPhoton");
  iTree->SetBranchAddress("Photon",       &fPhotons);
  fPhotonBr  = iTree->GetBranch("Photon");
  fN = 1;
  for(int i0 = 0; i0 < fN*3.; i0++) {double pVar = 0; fVars.push_back(pVar);}
  for(int i0 = 0; i0 <     1; i0++) {double pVar = 1; fphoSFVars.push_back(pVar);}
}
PhotonLoader::~PhotonLoader() { 
  delete fPhotons;
  delete fPhotonBr;
}
void PhotonLoader::reset() { 
  fNPhotonsLoose  = 0; 
  fNPhotonsTight  = 0;
  fNPhotonsMVA    = 0; 
  fispho0Tight    = 0;
  fphoMVA_pt      = 0;
  fphoMVA_eta     = 0;
  fphoMVA_phi     = 0;

  fSelPhotons.clear();
  fSelPhotonsMVA.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  for(unsigned int i0 = 0; i0 < fphoSFVars.size(); i0++) fphoSFVars[i0] = 1;
}
void PhotonLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
//  fTree->Branch("nphoLoose",   &fNPhotonsLoose, "fNPhotonsLoose/I");  // loose photon multiplicity 
//  fTree->Branch("nphoTight",   &fNPhotonsTight, "fNPhotonsTight/I");  // medium(tight) photon multiplicity
//  fTree->Branch("nphoMVA",     &fNPhotonsMVA,   "fNPhotonsMVA/I");    // MVA-based selection
//  fTree->Branch("ispho0Tight", &fispho0Tight,   "fispho0Tight/I"); 
//  fTree->Branch("vphoMVA_pt",  &fphoMVA_pt,     "fphoMVA_pt/D"); 
//  fTree->Branch("vphoMVA_eta", &fphoMVA_eta,    "fphoMVA_eta/D");
//  fTree->Branch("vphoMVA_phi", &fphoMVA_phi,    "fphoMVA_phi/D");
//  setupNtuple("vpho",iTree,fN,fVars);                                 // pho0_pt,_eta,_phi (1*3=3)
//  addSF      ("phoSF",iTree,fphoSFVars,1);                            // phoSF0
}
void PhotonLoader::load(int iEvent) { 
  fPhotons  ->Clear();
  fPhotonBr ->GetEntry(iEvent);
}
void PhotonLoader::selectPhotons(double iRho,std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iPhotons) {
  reset();
  int lCount(0), lTCount(0);
  std::vector<TPhoton*> lVeto;
  TPhoton* photon = 0;  
  for  (int i0 = 0; i0 < fPhotons->GetEntriesFast(); i0++) {
    TPhoton *pPhoton = (TPhoton*)((*fPhotons)[i0]);

    if(pPhoton->pt        <=  15)                       continue;
    if(fabs(pPhoton->eta) >=  2.5)                      continue;
    if(passVeto(pPhoton->eta,pPhoton->phi,0.4,iVetoes)) continue;
    if(!passPhoLooseSel(pPhoton,iRho))                  continue;
    lCount++;

    if(pPhoton->pt        <= 175)                       continue;
    if(fabs(pPhoton->eta) >= 1.4442)                    continue;
    if(!passPhoMediumSel(pPhoton, iRho))                continue;
    lTCount++;

    if(lCount ==1) fispho0Tight = 1;
    lVeto.push_back(pPhoton);
    addPhoton(pPhoton,fSelPhotons);
    if(!photon || (pPhoton->pt > photon->pt))  photon = pPhoton;
  }
  if(photon) addVPhoton(photon,iPhotons,0.);

  fNPhotonsLoose = lCount;
  fNPhotonsTight = lTCount;

  if(fVars.size() > 0) fillPhoton(fN,fSelPhotons,fVars);
}
void PhotonLoader::selectPhotonsMVA(double iRho,std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iPhotons) {
  //reset(); 
  int lCount(0), lMVACount(0);
  std::vector<TPhoton*> lVeto; 
  TPhoton* photonMVA =0;
  for  (int i0 = 0; i0 < fPhotons->GetEntriesFast(); i0++) { 
    TPhoton *pPhoton = (TPhoton*)((*fPhotons)[i0]);

    if(pPhoton->pt        <=  15)                       continue;
    if(fabs(pPhoton->eta) >=  2.5)                      continue;
    if(passVeto(pPhoton->eta,pPhoton->phi,0.4,iVetoes)) continue;
    if(!passPhoLooseSel(pPhoton,iRho))                  continue;
    lCount++;

    if(pPhoton->mva <= 0.374)                              continue;
    if(pPhoton->pt <= 180)                                 continue;
    lMVACount++;

    lVeto.push_back(pPhoton);
    addPhoton(pPhoton,fSelPhotonsMVA);
    if(!photonMVA || (pPhoton->pt > photonMVA->pt))  photonMVA = pPhoton;
  }
  if(photonMVA){
    addVPhoton(photonMVA,iPhotons,0.);
    fphoMVA_pt = photonMVA->pt;
    fphoMVA_eta = photonMVA->eta;
    fphoMVA_phi = photonMVA->phi;
  }
  fNPhotonsLoose = lCount;
  fNPhotonsMVA   = lMVACount;
  
}
