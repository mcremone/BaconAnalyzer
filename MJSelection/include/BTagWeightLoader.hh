#ifndef BTagWeightLoader_H
#define BTagWeightLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TJet.hh"
#include "MonoXUtils.hh"
// B-tag scale factors
#include "BTagUnc.hh"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "BTagCalibrationStandalone.h"

using namespace baconhep;

class BTagWeightLoader { 
public:
  BTagWeightLoader(TTree *iTree,std::string btagScaleFactorFilename = "/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/include/CSVv2.csv");
  ~BTagWeightLoader();
  void reset();
  void setupTree(TTree *iTree, std::string iJetLabel);
  void addBTag(std::string iHeader,TTree *iTree,std::string iLabel,std::vector<std::string> iLabels,int iN,float &iVals);
  void fillBTag(std::vector<const TJet*> iObjects);

  const double CSVL = 0.460; // CSVv2 WP
  const double CSVM = 0.800;
  const double CSVT = 0.935;

  float fBTagVars[60];
  BTagCalibration          *fJetCalib;
  std::vector<BTagCalibrationReader*> freadersL;
  std::vector<BTagCalibrationReader*> freadersM;
  std::vector<BTagCalibrationReader*> freadersT;
  std::vector<std::vector<BTagCalibrationReader*>> freaders;

protected: 

};
#endif
