#ifndef TauLoader_H
#define TauLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TTau.hh"
#include "MonoXUtils.hh"

using namespace baconhep;

class TauLoader { 
public:
  TauLoader(TTree *iTree);
  ~TauLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  bool selectTaus(std::vector<TLorentzVector> &iVetoes);
  std::vector<TTau*> fSelTaus;

protected: 
  TClonesArray *fTaus;
  TBranch      *fTauBr;
  TTree        *fTree;
  int           fNTaus;
  std::vector<double> fVars;
  int           fN;
  double        fTauIso;
};
#endif
