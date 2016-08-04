#ifndef MuonLoader_H
#define MuonLoader_H
#include "TH2D.h"
#include "TVector2.h"
#include "TTree.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "BaconAna/DataFormats/interface/TMuon.hh"
#include "MonoXUtils.hh"

using namespace baconhep;

class MuonLoader { 
public:
  MuonLoader(TTree *iTree,
	     std::string imuScaleFactorFilename="/afs/cern.ch/work/c/cmantill/public/Bacon/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/Json/scaleFactor_muon_looseid_12p9.root",
             std::string imuScaleFactorTightFilename="/afs/cern.ch/work/c/cmantill/public/Bacon/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/Json/scaleFactor_muon_tightid_12p9.root",
	     std::string imuScaleFactorTrackFilename="/afs/cern.ch/work/c/cmantill/public/Bacon/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/Json/scaleFactor_muon_track.root");
  ~MuonLoader();
  void reset();
  void setupTree(TTree *iTree);
  void load(int iEvent);
  void selectMuons(std::vector<TLorentzVector> &iVetoes, int &nLepLoose, int &islep0Tight, int &islep1Tight, int &lep0PdgId, int &lep1PdgId, float met, float metPhi);
  void fillDiMuon(std::vector<TMuon*> lVeto, std::vector<TLorentzVector> &iVetoes, int &isDimuon);
  void addDiMuon(std::string iHeader,TTree *iTree,int iN,std::vector<double> &iVals,int iBase);
  std::vector<TMuon*> fSelMuons;
  std::vector<double> fmuoSFVars;
  int           fNMuonsLoose;
  int           fismu0Tight;
  int           fisDimuon;
  double        fmuoSFTrack;

  TH2D         *fhMuLoose;
  TH2D         *fhMuTight;
  TH1D         *fhMuTrack;
  TVector2      fvMetNoMu;
  const double MUON_MASS = 0.105658369;

protected: 
  TClonesArray *fMuons;
  TBranch      *fMuonBr;
  TTree        *fTree;
  std::vector<double> fVars;
  int           fN;
  int           fNMuonsTight;
};
#endif
