#ifndef PhotonLoader_H
#define PhotonLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TPhoton.hh"
#include "MonoXUtils.hh"

using namespace baconhep;

class PhotonLoader { 
public:
  PhotonLoader(TTree *iTree);
  ~PhotonLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectPhotons(double iRho,std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iPhotons);
  void selectPhotonsMVA(double iRho,std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iPhotons);

  std::vector<TPhoton*> fSelPhotons, fSelPhotonsMVA;
  std::vector<double>   fphoSFVars;
  int           fNPhotonsLoose;
  int           fNPhotonsTight;
  int           fNPhotonsMVA;
  int           fispho0Tight;

protected: 
  TClonesArray *fPhotons;
  TBranch      *fPhotonBr;
  TTree        *fTree;
  
  std::vector<double> fVars;
  int           fN;
  double        fIso;
  double        fphoMVA_pt, fphoMVA_eta, fphoMVA_phi;
};
#endif
