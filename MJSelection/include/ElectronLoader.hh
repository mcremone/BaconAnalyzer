
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
  ElectronLoader(TTree *iTree,std::string ieleScaleFactorFilename="/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/Json/scalefactors_ele_80x_UCSD.root");
  ~ElectronLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectElectrons(double iRho,std::vector<TLorentzVector> &iVetoes);
  void addDiElectron(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase);
  void fillDiElectron(double iRho,std::vector<TElectron*> lVeto, std::vector<TLorentzVector> &iVetoes, int & isDiele);
  std::vector<TElectron*> fSelElectrons;
  std::vector<double>     feleSFVars;
  TH2D         *fhEleVeto;
  TH2D         *fhEleTight;
  int           fNElectrons;
  int           fNElectronsTight;
  int           fisDiele;

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
