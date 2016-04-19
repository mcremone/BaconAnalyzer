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

// B-tag scale factors
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "BTagCalibrationStandalone.h"
#include "BTagUnc.hh"

using namespace baconhep;

class JetLoader { 
public:
  JetLoader(TTree *iTree,std::string btagScaleFactorFilename = "/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconSkim/Utils/data/CSVv2.csv");
  ~JetLoader();
  void reset();
  void resetBTag();
  void setupTree(TTree *iTree, std::string iJetLabel);
  void setupTreeDiJet(TTree *iTree, std::string iJetLabel);
  void setupTreeBTag(TTree *iTree, std::string iJetLabel);
  void load(int iEvent);
  void selectJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iVJets,std::vector<TLorentzVector> &iJets,float iMetPhi,float iFMet,float iFMetPhi);
  std::vector<TJet*> fSelJets;
  std::vector<const TJet*> fGoodJets;
  //Fillers
  void addOthers(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillOthers(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals);
  void addDijet(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillDiJet();
  void addBTag(std::string iHeader,TTree *iTree,std::string iLabel,std::vector<std::string> &iLabels,int iN,std::vector<float> &iVals);
  void fillBTag(std::vector<const TJet*> iObjects);
  double correction(TJet &iJet,float iRho);

  const double CSVL = 0.605;
  const double CSVM = 0.89;
  const double CSVT = 0.97;
  int           fNJets;
  int           fNJetsAbove80GeV;
  float         fMT;
  double        fMinDPhi;
  double        fMinDFPhi;
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
  std::vector<std::string> fLabels = {"CENT", "MISTAGUP","MISTAGDO","BTAGUP","BTAGDO"};   // nominal, mistagup, mistagdown, btagup and btagdown
  std::vector<std::string> measurementTypes = {"mujets", "comb"};                         // measurements type
  std::vector<std::string> variationTypes = {"central", "up", "down"};                    // systematics type
  std::vector<std::string> flavorTypes = {"Ms", "Bs"};                                    // nominal, mistag and btag
  std::vector<std::string> wpTypes = {"L","M","T"};                                       // working points                           
  std::vector<double>      fVars;
  std::vector<float>       fBTagVars;
  FactorizedJetCorrector   *fJetCorr;
  BTagCalibration          *fJetCalib;
  std::vector<BTagCalibrationReader*> freadersL;
  std::vector<BTagCalibrationReader*> freadersM;
  std::vector<BTagCalibrationReader*> freadersT;
  std::vector<std::vector<BTagCalibrationReader*>> freaders;
};
#endif
