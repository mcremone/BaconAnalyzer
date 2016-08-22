#ifndef FatJetLoader_H
#define FatJetLoader_H
#include "TTree.h"
#include "TLorentzVector.h"
#include "TLorentzRotation.h"
#include "TVector3.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TGenParticle.hh"
#include "BaconAna/DataFormats/interface/TJet.hh"
#include "BaconAna/DataFormats/interface/TAddJet.hh"
#include "BaconAna/Utils/interface/TTrigger.hh"
#include "MonoXUtils.hh"

// B-tag scale factors
#include "SJBTagUnc.hh"
#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "BTagCalibrationStandalone.h"

// JEC
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"

using namespace baconhep;

class FatJetLoader { 
public:
  FatJetLoader(TTree *iTree,std::string iJet,std::string iAddJet,int iN=1, std::string subjetbtagScaleFactorFilename ="/afs/cern.ch/work/c/cmantill/public/Bacon/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/include/subjet_CSVv2_ichep.csv");
  ~FatJetLoader();
  double correction(TJet &iJet,double iRho);
  void reset();
  void resetSubJetBTag();
  void setupTree(TTree *iTree,std::string iJetLabel);
  void setupTreeSubJetBTag(TTree *iTree, std::string iJetLabel);
  void load(int iEvent);
  void selectVJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,std::vector<TLorentzVector> &iVJet, double dR, double iRho, std::vector<TLorentzVector> &iPhotons, std::vector<TLorentzVector> &iPhotonsMVA, std::string iJetID="looseJetID");
  void fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals, double iRho = 0);
  std::vector<TJet*> fSelVJets;
  std::vector<TLorentzVector> fGoodVSubJets;
  void addBoson(TGenParticle *iBoson);
  void addSubJetBTag(std::string iHeader,TTree *iTree,std::string iLabel,std::vector<std::string> &iLabels,int iN,std::vector<float> &iVals);
  void fillSubJetBTag(const TClonesArray* iGens, std::vector<TLorentzVector> iObjects);
  TAddJet *getAddJet(TJet *iJet);
  double ddt(double iT1,double iT2,double iM,double iPt);
  int  trigger(TJet *iJet);
  float pullDot(float iY1,float iY2,float iPhi1,float iPhi2);
  TJet* getLargeJet(TJet *iMatch);
  double dPhi(TLorentzVector v1, TLorentzVector v2, TLorentzVector v3);

  double ftopSize, ftopMatching, fvSize, fvMatching;
  int fisHadronicTop, fisHadronicV;
  int fisTightVJet;
  int fvetoPhoton;
  float fVMT,fdR_sj0dR,fdPhi_sj0dPhi, fdPhiJRF_sj0dPhiJRF;

  const double CSVL = 0.460; // CSVv2SubJet WP 
  const double CSVM = 0.800;

protected: 
  TClonesArray *fVJets;
  TBranch      *fVJetBr;
  TClonesArray *fVAddJets;
  TBranch      *fVAddJetBr;
  //TClonesArray *fFatJets;
  //TBranch      *fFatJetBr;
  TTrigger     *fTrigger;
  TTree        *fTree;
  int           fNVJets;

  std::vector<std::string> fBtagLabels = {"CENT", "MISTAGUP","MISTAGDO","BTAGUP","BTAGDO"};  // nominal, mistagup, mistagdown, btagup and btagdown
  std::vector<std::string> measurementTypes = {"lt", "incl"};                                // measurements type
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

  FactorizedJetCorrector   *fJetCorr;

  int           fN;
};
#endif
