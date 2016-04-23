#ifndef VJetLoader_H
#define VJetLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TGenParticle.hh"
#include "BaconAna/DataFormats/interface/TJet.hh"
#include "BaconAna/DataFormats/interface/TAddJet.hh"
#include "BaconAna/Utils/interface/TTrigger.hh"
#include "MonoXUtils.hh"

// B-tag scale factors
#include "BTagUnc.hh"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "BTagCalibrationStandalone.h"

using namespace baconhep;

class VJetLoader { 
public:
  VJetLoader(TTree *iTree,std::string iJet,std::string iAddJet,std::string subjetbtagScaleFactorFilename ="CSVv2_subjets.csv");
  ~VJetLoader();
  void reset();
  void resetSubJetBTag();
  void setupTree(TTree *iTree,std::string iJetLabel);
  void setupTreeSubJetBTag(TTree *iTree, std::string iJetLabel);
  void load(int iEvent);
  void selectVJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,std::vector<TLorentzVector> &iVJet, double dR);
  void fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals);
  std::vector<TJet*> fSelVJets;
  std::vector<TLorentzVector> fGoodVSubJets;
  void addBoson(TGenParticle *iBoson);
  void addSubJetBTag(std::string iHeader,TTree *iTree,std::string iLabel,std::vector<std::string> &iLabels,int iN,std::vector<float> &iVals);
  void fillSubJetBTag(const TClonesArray* iGens, std::vector<TLorentzVector> iObjects);
  TAddJet *getAddJet(TJet *iJet);
  int  trigger(TJet *iJet);
  float pullDot(float iY1,float iY2,float iPhi1,float iPhi2);
  TJet* getLargeJet(TJet *iMatch);

  double ftopSize, ftopMatching;
  int fisHadronicTop;
  float fVMT;

  const double CSVL = 0.460; // CSVv2SubJet WP 
  const double CSVM = 0.800;

protected: 
  TClonesArray *fVJets;
  TBranch      *fVJetBr;
  TClonesArray *fVAddJets;
  TBranch      *fVAddJetBr;
  TClonesArray *fFatJets;
  TBranch      *fFatJetBr;
  TTrigger     *fTrigger;
  TTree        *fTree;
  int           fNVJets;
  std::vector<std::string> fBtagLabels = {"CENT", "MISTAGUP","MISTAGDO","BTAGUP","BTAGDO"};  // nominal, mistagup, mistagdown, btagup and btagdown
  std::vector<std::string> measurementTypes = {"mujets", "comb"};                            // measurements type
  std::vector<std::string> variationTypes = {"central", "up", "down"};                       // systematics type 
  std::vector<std::string> flavorTypes = {"Ms", "Bs"};                                       // nominal, mistag and btag
  std::vector<std::string> wpTypes = {"L","M"};                                              // working points 
  std::vector<double> fVars;
  std::vector<float>  fSubJetBTagVars;
  std::vector<std::string> fLabels;
  std::vector<std::string> fTrigString;

  BTagCalibration          *fSubJetCalib;
  std::vector<BTagCalibrationReader*> fSubJetreadersL;
  std::vector<BTagCalibrationReader*> fSubJetreadersM;
  std::vector<std::vector<BTagCalibrationReader*>> fSubJetreaders;

  int           fN;
};
#endif
