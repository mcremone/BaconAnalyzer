#ifndef MuonLoader_H
#define MuonLoader_H
#include "TH2D.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TMuon.hh"
#include "MonoXUtils.hh"

using namespace baconhep;

class MuonLoader { 
public:
  MuonLoader(TTree *iTree,std::string imuScaleFactorFilename="/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconSkim/Utils/data/scalefactors_mu_74x_2016-03-09.root");
  ~MuonLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectMuons(std::vector<TLorentzVector> &iVetoes);
  void fillDiMuon(std::vector<TMuon*> lVeto, std::vector<TLorentzVector> &iVetoes);
  void addDiMuon(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase);
  std::vector<TMuon*> fSelMuons;
  std::vector<double> fmuoSFVars;
  int           fNMuons;
  const double MUON_MASS = 0.105658369;

  TH2D         *fhMuLoose;
  TH2D         *fhMuTight;

protected: 
  TClonesArray *fMuons;
  TBranch      *fMuonBr;
  TTree        *fTree;
  std::vector<double> fVars;
  int           fN;
  int           fNMuonsTight;
};
#endif
