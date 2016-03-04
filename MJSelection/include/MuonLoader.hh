#ifndef MuonLoader_H
#define MuonLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TMuon.hh"
#include "MonoXUtils.hh"

using namespace baconhep;

class MuonLoader { 
public:
  MuonLoader(TTree *iTree);
  ~MuonLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectMuons(std::vector<TLorentzVector> &iVetoes);
  void fillDiMuon(std::vector<TMuon*> lVeto, std::vector<TLorentzVector> &iVetoes);
  void addDiMuon(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase);
  std::vector<TMuon*> fSelMuons;
  int           fNMuons;
  const double MUON_MASS = 0.105658369;

protected: 
  TClonesArray *fMuons;
  TBranch      *fMuonBr;
  TTree        *fTree;
  std::vector<double> fVars;
  int           fN;
  int           fNMuonsTight;
};
#endif
