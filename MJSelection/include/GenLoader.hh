#include "TTree.h"
#include "TBranch.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"
#include "BaconAna/DataFormats/interface/TGenEventInfo.hh"
#include "BaconAna/DataFormats/interface/TGenParticle.hh"

using namespace baconhep;

class GenLoader { 
public:
  GenLoader(TTree *iTree);
  ~GenLoader();
  void reset();
  void setupTree(TTree *iTree,float iXSIn);
  void load (int iEvent);
  void fillGenEvent();
  //Fill specific Gen Info
  void selectBoson(int iDMu);
  float lepmatched(int iId, std::vector<TLorentzVector> vec, double dR);
  int ismatchedJet(TLorentzVector jet0, double dR,double &top_size);
  //Helpers
  TGenParticle* getStatus1(int iId,bool iIsNeut);
  bool isNeutrino(TGenParticle *iPart);
  bool isGenParticle(int iId);
  int isttbarType();
  int getId(int iId,int iPId,bool iIsNeut);
  TGenParticle *fBoson;
  float frixione(TGenParticle *iPart);
  float computeTTbarCorr();
  TGenParticle* findDaughter(int iparent, int dauId);
  int findDaughterId(int iparent, int dauId);
  int findLastBoson(int iparent,int iId);
  int isHadronicTop(TGenParticle *genp,int j,TLorentzVector jet,double dR,double &topSize);
  void findBoson(int iId, int lOption);

  TClonesArray  *fGens;
  TBranch       *fGenBr;
  TGenEventInfo *fGenInfo;
  TBranch       *fGenInfoBr;

  float fWeight;
  float fBosonPt;
  float fBosonPhi;
protected: 
  TTree         *fTree;
  float fXS;
  float fXSIn;
  float fQ;
  float fPId1;
  float fX1;
  float fPdf1;
  float fPId2;
  float fX2;
  float fPdf2;

  float fVPt;
  float fVEta;
  float fVPhi;
  float fVM;
  int   fVId;
  float fVIso;
  
  float fPt1;
  float fEta1;
  float fPhi1;
  float fM1;
  int   fId1;

  float fPt2;
  float fEta2;
  float fPhi2;
  float fM2;
  int   fId2;

  float fHPt;
  float fHEta;
  float fHPhi;
  float fHM;
  int   fHId;
  
  float fHPt1;
  float fHEta1;
  float fHPhi1;
  float fHM1;
  int   fHId1;

  float fHPt2;
  float fHEta2;
  float fHPhi2;
  float fHM2;
  int   fHId2;

  float fDPt;
  float fDEta;
  float fDPhi;
  float fDM;
  int   fDId;
};
