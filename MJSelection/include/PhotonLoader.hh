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
  bool selectPhotons(float iRho,std::vector<TLorentzVector> &iVetoes);
  std::vector<TPhoton*> fSelPhotons;
  int           fNPhotons;
  int           fNPhotonsTight;

protected: 
  TClonesArray *fPhotons;
  TBranch      *fPhotonBr;
  TTree        *fTree;
  std::vector<double> fVars;
  int           fN;
  double        fIso;
};
#endif
