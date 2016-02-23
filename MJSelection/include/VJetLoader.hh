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

using namespace baconhep;

class VJetLoader { 
public:
  VJetLoader(TTree *iTree,
	     std::string iHLTFile="/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_7_4_7/src/BaconAna/DataFormats/data/HLTFile_50ns");
  ~VJetLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  bool selectVJets(std::vector<TLorentzVector> &iVetoes,bool iVeto=true);
  std::vector<TJet*> fSelVJets;
  void fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals);
  void addBoson(TGenParticle *iBoson);
  TAddJet *getAddJet(TJet *iJet);
  int  trigger(TJet *iJet);
  float pullDot(float iY1,float iY2,float iPhi1,float iPhi2);
  TJet* getLargeJet(TJet *iMatch);
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
  std::vector<double> fVars;
  std::vector<std::string> fLabels;
  std::vector<std::string> fTrigString;
  int           fN;
};
#endif
