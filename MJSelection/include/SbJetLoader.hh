#ifndef SbJetLoader_H
#define SbJetLoader_H
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

class SbJetLoader { 
public:
  SbJetLoader(TTree *iTree,std::string iJet,std::string iAddJet);
  ~SbJetLoader();
  void reset();
  void setupTree(TTree *iTree,std::string iJetLabel);
  void load(int iEvent);
  void selectSbJets(std::vector<TLorentzVector> &iVetoes,std::vector<TLorentzVector> &iJets,double dR);
  void fillVJet(int iN,std::vector<TJet*> &iObjects,std::vector<double> &iVals,std::vector<float> &iSbVals);
  TAddJet *getAddJet(TJet *iJet);
  std::vector<TJet*> fSelSbJets;
  double ftopSize, ftopMatching;
  int fisHadronicTop;
  float fVMT;
protected: 
  TClonesArray *fSbJets;
  TBranch      *fSbJetBr;
  TClonesArray *fSbAddJets;
  TBranch      *fSbAddJetBr;
  TClonesArray *fFatJets;
  TBranch      *fFatJetBr;
  TTrigger     *fTrigger;
  TTree        *fTree;
  int           fNSbJets;
  std::vector<double> fVars;
  std::vector<float> fSbVars;
  std::vector<std::string> fLabels;
  std::vector<std::string> fSbLabels;
  std::vector<std::string> fTrigString;
  std::vector<std::string> tauTypes = {"mass","fd"}; 
  std::vector<std::string> varTypes = {"0","1"};
  std::vector<std::string> trackTypes = {"1","2","3"};
  std::vector<std::string> SLTypes = {"Muon","Electron"};
  int           fN;
  int           fpartonFlavor, fhadronFlavor;
  int           fnbHadrons, fncHadrons;
  // unsigned int  fnchHadCharged, fnneuHadCharged;
  // unsigned int  fnCharged, fnNeutrals, fnParticles;  
};
#endif
