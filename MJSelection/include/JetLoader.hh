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
  void setupTree(TTree *iTree, std::string iJetLabel);
  void load(int iEvent);
  void selectJets(std::vector<TLorentzVector> &iVetoes,double iMetPhi,double iRho);
  std::vector<TJet*> fSelJets;
  //Fillers
  void addOthers(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillOthers(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals,double iMetPhi,double iRho);
  void addDijet(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillDiJet();
  double correction(TJet &iJet,double iRho);
  //Constants
  const double CSVL = 0.605;
  const double CSVM = 0.89;
  const double CSVT = 0.97;
protected: 
  TClonesArray *fJets;
  TBranch      *fJetBr;
  TTree        *fTree;
  double        fMinDPhi;
  int           fNJets;
  int           fNFwd;
  int           fNBTags;
  int           fNBTagsL;
  int           fNBTagsM;
  int           fNBTagsT;
  int           fNBTagsLdR2;
  std::vector<double> fVars;
  int           fN;
  double        fHT;
  FactorizedJetCorrector   *fJetCorr;
};
#endif
