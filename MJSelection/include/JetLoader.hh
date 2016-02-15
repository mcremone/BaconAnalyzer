#ifndef JetLoader_H
#define JetLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TJet.hh"
#include "MonoXUtils.hh"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

using namespace baconhep;

class JetLoader { 
public:
  JetLoader(TTree *iTree);
  ~JetLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  bool selectJets(std::vector<TLorentzVector> &iVetoes,double iMetPhi,double iRho);
  std::vector<TJet*> fSelJets;
  //Fillers
  void addOthers(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillOthers(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals,double iMetPhi,double iRho);
  void addDijet(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillDiJet();
  double correction(TJet &iJet,double iRho);
protected: 
  TClonesArray *fJets;
  TBranch      *fJetBr;
  TTree        *fTree;
  double        fMinDPhi;
  int           fNJets;
  int           fNFwd;
  int           fNBTags;
  std::vector<double> fVars;
  int           fN;
  double        fHT;
  FactorizedJetCorrector   *fJetCorr;
};
#endif
