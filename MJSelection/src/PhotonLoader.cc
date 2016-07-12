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
  fNPhotons      = 0; 
  fNPhotonsMedium = 0;
  fNPhotonsMVA = 0; 
  fphoMVA_pt = 0;
  fphoMVA_eta = 0;
  fphoMVA_phi = 0;

  fSelPhotons.clear();
  fSelPhotonsMVA.clear();
  for(unsigned int i0 = 0; i0 < fVars.size(); i0++) fVars[i0] = 0;
  for(unsigned int i0 = 0; i0 < fphoSFVars.size(); i0++) fphoSFVars[i0] = 1;
}
void PhotonLoader::setupTree(TTree *iTree) { 
  reset();
  fTree = iTree;
  fTree->Branch("npho",       &fNPhotons,      "fNPhotons/I");       // photon multiplicity 
  fTree->Branch("nphoMedium", &fNPhotonsMedium,"fNPhotonsMedium/I"); // medium photon multiplicity
  fTree->Branch("nphoMVA",    &fNPhotonsMVA,   "fNPhotonsMVA/I");    // MVA-based selection
  fTree->Branch("vpho0_iso",  &fIso,           "fIso/D");            // photon isolation
  fTree->Branch("vphoMVA_pt", &fphoMVA_pt,     "fphoMVA_pt/D"); 
  fTree->Branch("vphoMVA_eta",&fphoMVA_eta,    "fphoMVA_eta/D");
  fTree->Branch("vphoMVA_phi",&fphoMVA_phi,    "fphoMVA_phi/D");

  setupNtuple("vpho",iTree,fN,fVars);                                // pho0_pt,_eta,_phi (1*3=3)
  //setupNtuple("vphoMVA",iTree,fN,fVarsMVA);
  addSF      ("phoSF",iTree,fphoSFVars,1);                           // phoSF0
}
void PhotonLoader::load(int iEvent) { 
  fPhotons   ->Clear();
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

    lVeto.push_back(pPhoton);
    addPhoton(pPhoton,fSelPhotons);
    if(!photon || (pPhoton->pt > photon->pt))  photon = pPhoton;
  }
  if(photon) addVPhoton(photon,iPhotons,0.);

  fNPhotons = lCount;
  fNPhotonsMedium = lTCount;

  if(fVars.size() > 0) fillPhoton(fN,fSelPhotons,fVars);
  if(fSelPhotons.size() > 0) fIso = TMath::Max(fSelPhotons[0]->chHadIso  - iRho*phoEffArea(fSelPhotons[0]->scEta, 0), (double)0.);
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
  fNPhotons = lCount;
  fNPhotonsMVA = lMVACount;
  
}
