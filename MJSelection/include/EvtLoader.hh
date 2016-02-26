#include "BaconAna/DataFormats/interface/TEventInfo.hh"
#include "BaconAna/DataFormats/interface/TVertex.hh"
#include "BaconAna/Utils/interface/TTrigger.hh"

#include "TH1F.h"
#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

#include <string>
#include <vector>

using namespace baconhep;

class EvtLoader { 
public:
  EvtLoader(TTree *iTree,std::string iName,
            std::string iHLTFile="/src/BaconAna/DataFormats/data/HLTFile_25ns_new",
	    std::string iPUWeight="/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_7_4_12_patch1/src/BaconAnalyzer/MJSelection/Json/puWeights_13TeV_25ns.root");//,
  ~EvtLoader(); 
  void reset();
  void setupTree  (TTree *iTree,float iWeight);
  void load (int iEvent);
  //Fillers
  void fillEvent();
  bool passSkim();
  TLorentzVector Met(int iOption);
  //Trigger Related Stuff
  void addTrigger(std::string iName);
  bool passFilter();
  bool passTrigger();
  bool passTrigger(std::string iTrigger);
  unsigned int triggerBit();
  float pEff();
  //PU relates stuff
  float        puWeight(float iPU);
  unsigned int nVtx();
  bool         PV();
  void  correctMet(float &iMet,float &iMetPhi,TLorentzVector &iCorr);
  //Met Stuff
  void         fillModifiedMet(std::vector<TLorentzVector> &iVecCorr);
  float        metSig(float iMet,float iMetPhi,float iCov00,float iCov01,float iCov10,float iCov11);
  unsigned int metFilter(unsigned int iMetFilter);
  float        mT(float &iMet,float &iMetPhi,TLorentzVector &iVec);
  //Vars
  float fRho;
  float fMetPhi;
  float fMet;
  float fPuppEtPhi;
  float fPuppEt;

  float fFMetPhi;
  float fFMet;
  float fFPuppEtPhi;
  float fFPuppEt;

  unsigned int fRun;
  unsigned int fEvtV;
  unsigned int fLumi;
  TEventInfo   *fEvt;

protected: 
  TBranch      *fEvtBr;

  TClonesArray *fVertices;
  TBranch      *fVertexBr;

  TTree        *fTree;
  TTrigger     *fTrigger;
  TH1F         *fPUWeightHist;
  
  std::vector<std::string>   fTrigString;
  char*  fSample;
  unsigned int fITrigger;
  unsigned int fMetFilters;
  unsigned int fNVtx;
  unsigned int fNPU;
  unsigned int fNPUP;
  unsigned int fNPUM;
  float        fPUWeight;
  float        fScale;

  float fMt;
  float fPuppEtMt;
  float fMetSig;

  float fEffTrigger;
  float fKfactor_CENT;
  float fEwkCorr_CENT;
  float fLepWeight;
};
