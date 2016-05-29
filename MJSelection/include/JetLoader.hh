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

// Razor utils
#include "RazorUtils.hh"

using namespace baconhep;

class JetLoader { 
public:
  JetLoader(TTree *iTree);
  ~JetLoader();
  void reset();
  void setupTree(TTree *iTree, std::string iJetLabel);
  void setupTreeDiJet(TTree *iTree, std::string iJetLabel);
  void setupTreeRazor(TTree *iTree);
  void load(int iEvent);
  void selectJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iVJets,std::vector<TLorentzVector> &iJets,float iMet,float iMetPhi,float iFMet,float iFMetPhi);
  void fillGoodJets(std::vector<TLorentzVector> &iVJets,std::vector<const TJet*> &iGoodJets);
  std::vector<TJet*> fSelJets;
  std::vector<const TJet*> fGoodJets;
  //Fillers
  void addOthers(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillOthers(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals);
  void addDijet(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillDiJet();
  void fillRazor(std::vector<TLorentzVector> iJets,float iMet, float iFMet);
  double correction(TJet &iJet,float iRho);

  const double CSVL = 0.460; // CSVv2 WP
  const double CSVM = 0.800;
  const double CSVT = 0.935;

  int           fNJets;
  int           fNJetsAbove80GeV;
  float         fMT;
  double        fMinDPhi;
  double        fMinDFPhi;
  float         fMR, fdeltaPhi;
  float         fHT, fMHT, fMT2;
  float         falphaT, fdPhiMin;
  float         fRsq; 

protected: 
  TClonesArray *fJets;
  TBranch      *fJetBr;
  TTree        *fTree;
  int           fNJetsdR2;
  int           fNBTags;
  int           fNBTagsL;
  int           fNBTagsM;
  int           fNBTagsT;
  int           fNBTagsLdR2;
  int           fNBTagsMdR2;
  int           fNBTagsTdR2;
  int           fN;
  std::vector<double>      fVars;
  FactorizedJetCorrector   *fJetCorr;
};
#endif
