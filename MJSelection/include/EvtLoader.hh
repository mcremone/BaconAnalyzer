#include "BaconAna/DataFormats/interface/TEventInfo.hh"
#include "BaconAna/DataFormats/interface/TVertex.hh"
#include "BaconAna/Utils/interface/TTrigger.hh"
#include "MonoXUtils.hh"

#include "TH1F.h"
#include "TH2D.h"
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
	    std::string iHLTFile="/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_8_0_10/src/BaconAna/DataFormats/data/HLTFile_25ns",
	    //std::string iHLTFile="/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAna/DataFormats/data/HLTFile_25ns_new",
	    std::string iPUWeight="/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_7_4_12_patch1/src/BaconAnalyzer/MJSelection/Json/puWeights_13TeV_25ns.root");
  ~EvtLoader(); 
  void reset();
  void setupTree  (TTree *iTree);
  void load (int iEvent);
  //Fillers
  void fillEvent(unsigned int trigBit, float lWeight);
  bool passSkim();
  TLorentzVector Met(int iOption);
  //Trigger
  bool passFilter();
  bool passTrigger(std::string iTrigger);
  void triggerEff(std::vector<TLorentzVector> iElectrons, std::vector<TLorentzVector> iPhotons);
  //PU
  float        puWeight(float iPU);
  unsigned int nVtx();
  bool         PV();
  //EWK and kFactor
  void computeCorr(float iPt,
		   std::string iHist0,
		   std::string iHist1,
		   std::string iHist2,
		   std::string iNLO,
                   std::string ikfactor="/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAna/DataFormats/data/kfactors.root");
  //MET
  void         correctMet(float &iMet,float &iMetPhi,TLorentzVector &iCorr);
  void         fillVetoes(std::vector<TLorentzVector> iVetoes,std::vector<TLorentzVector> &lVetoes);
  void         fillModifiedMet(std::vector<TLorentzVector> &iVecCorr,std::vector<TLorentzVector> iPhotons);
  void         fillmT(float iMet, float iMetPhi,float iFMet, float iFMetPhi, std::vector<TLorentzVector> &lCorr, float &fmT);
  float        metSig(float iMet,float iMetPhi,float iCov00,float iCov01,float iCov10,float iCov11);
  float        mT(float iMet,float iMetPhi,TLorentzVector &iVec);
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

  float fevtWeight;
  float fScale;

  float fkFactor_CENT;
  float fEwkCorr_CENT, fEwkCorr_UP, fEwkCorr_DO;
  float fkfactor;
  float fPDF, fPDF_UP, fPDF_DO;
  float fRenScale_UP, fRenScale_DO, fFacScale_UP, fFacScale_DO;

  double fEffTrigger;
  double fLepWeight;

  int fselectBits;
protected: 
  TBranch      *fEvtBr;

  TClonesArray *fVertices;
  TBranch      *fVertexBr;

  TTree        *fTree;
  TTrigger     *fTrigger;
  TH1F         *fPUWeightHist;

  TH1F         *fHist0;
  TH1F         *fHist1;
  TH1F         *fHist2;
  TH1F         *fHistPDF;
  TH1F         *fHistRUP;
  TH1F         *fHistRDO;
  TH1F         *fHistFUP;
  TH1F         *fHistFDO;

  std::vector<std::vector<std::string>> fTrigString;

  char*  fSample;
  unsigned int fITrigger;
  unsigned int fMetFilters;
  unsigned int fNVtx;
  unsigned int fNPU;
  unsigned int fNPUP;
  unsigned int fNPUM;

  float fPUWeight;
  float fMetSig;
};
