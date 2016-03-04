
#ifndef ElectronLoader_H
#define ElectronLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TElectron.hh"
#include "MonoXUtils.hh"

using namespace baconhep;

class ElectronLoader { 
public:
  ElectronLoader(TTree *iTree);
  ~ElectronLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectElectrons(double iRho,std::vector<TLorentzVector> &iVetoes);
  std::vector<TElectron*> fSelElectrons;
  void addDiElectron(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase);
  void fillDiElectron(double iRho,std::vector<TElectron*> lVeto, std::vector<TLorentzVector> &iVetoes);
  void setDiElectron(TLorentzVector &iVec);
  int           fNElectrons;
  int           fNElectronsTight;

protected: 
  TClonesArray *fElectrons;
  TBranch      *fElectronBr;
  TTree        *fTree;
  std::vector<double> fVars;
  int           fN;
  double        fIso1;
  double        fIso2;
};
#endif
