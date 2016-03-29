
#ifndef ElectronLoader_H
#define ElectronLoader_H
#include "TH2D.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TElectron.hh"
#include "MonoXUtils.hh"

using namespace baconhep;

class ElectronLoader { 
public:
  ElectronLoader(TTree *iTree,std::string ieleScaleFactorFilename="/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconSkim/Utils/data/scalefactors_ele_74x_2016-03-09.root");
  ~ElectronLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectElectrons(double iRho,std::vector<TLorentzVector> &iVetoes);
  void addDiElectron(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase);
  void fillDiElectron(double iRho,std::vector<TElectron*> lVeto, std::vector<TLorentzVector> &iVetoes);
  std::vector<TElectron*> fSelElectrons;
  std::vector<double>     feleSFVars;
  TH2D         *fhEleVeto;
  TH2D         *fhEleTight;
  int           fNElectrons;
  int           fNElectronsTight;

protected: 
  TClonesArray *fElectrons;
  TBranch      *fElectronBr;
  TTree        *fTree;
  std::vector<double>     fVars;
  int           fN;
  double        fIso1;
  double        fIso2;
};
#endif
