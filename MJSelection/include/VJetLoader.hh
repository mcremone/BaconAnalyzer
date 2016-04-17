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
  VJetLoader(TTree *iTree,std::string iJet,std::string iAddJet);
  ~VJetLoader();
  void reset();
  void setupTree(TTree *iTree,std::string iJetLabel);
  void load(int iEvent);
  void selectVJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,std::vector<TLorentzVector> &iVJet, double dR); //,double iMetPhi,double iRho);
  void fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals); //,double iMetPhi,double iRho);
  void addBoson(TGenParticle *iBoson);
  TAddJet *getAddJet(TJet *iJet);
  int  trigger(TJet *iJet);
  float pullDot(float iY1,float iY2,float iPhi1,float iPhi2);
  TJet* getLargeJet(TJet *iMatch);
  std::vector<TJet*> fSelVJets;
  double ftopSize;
  int fisHadronicTop;
  float fVMT;
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
