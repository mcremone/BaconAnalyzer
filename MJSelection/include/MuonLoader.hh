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
  MuonLoader(TTree *iTree,std::string imuScaleFactorFilename="/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/Json/scalefactors_mu_80x.root");
  ~MuonLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectMuons(std::vector<TLorentzVector> &iVetoes);
  void fillDiMuon(std::vector<TMuon*> lVeto, std::vector<TLorentzVector> &iVetoes, int &isDimuon);
  void addDiMuon(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase);
  std::vector<TMuon*> fSelMuons;
  std::vector<double> fmuoSFVars;
  int           fNMuons;
  int           fisDimuon;
  TH2D         *fhMuLoose;
  TH2D         *fhMuTight;
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
