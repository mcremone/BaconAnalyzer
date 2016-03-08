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
  void setupTree(TTree *iTree, std::string iJetLabel);
  void load(int iEvent);
  void selectJets(std::vector<TLorentzVector> &iVetoes,double iMetPhi,double iRho);
  std::vector<TJet*> fSelJets;
  std::vector<const TJet*> fGoodJets;
  //Fillers
  void addOthers(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillOthers(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals,double iMetPhi,double iRho);
  void addDijet(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals);
  void fillDiJet();
  void addBTag(std::string iHeader,TTree *iTree,std::string iLabel,std::vector<std::string> &iLabels,int iN,std::vector<float> &iVals);
  void fillBTag(std::vector<const TJet*> iObjects);
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
  std::vector<std::string> fLabels = {"CENT", "MISTAGUP","MISTAGDO","BTAGUP","BTAGDO"};   // nominal, mistagup, mistagdown, btagup and btagdown
  std::vector<std::string> measurementTypes = {"mujets", "comb"};                         // measurements type
  std::vector<std::string> variationTypes = {"central", "up", "down"};                    // systematics type
  std::vector<std::string> flavorTypes = {"nominal", "Ms", "Bs"};                         // nominal, mistag and btag
  std::vector<double>      fVars;
  std::vector<float>       fBTagVars;
  int           fN;
  double        fHT;
  FactorizedJetCorrector   *fJetCorr;
  BTagCalibration          *fJetCalib;
  std::vector<BTagCalibrationReader*> freadersL;
  std::vector<BTagCalibrationReader*> freadersM;
  std::vector<BTagCalibrationReader*> freadersT;
  std::vector<std::vector<BTagCalibrationReader*>> freaders;
};
#endif
