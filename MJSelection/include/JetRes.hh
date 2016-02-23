#ifndef JetRes_hh
#define JetRes_hh
#include <vector>
#include <string>
#include "TF1.h"
#include "TGraph.h"
#include "TRandom.h"

class JetRes { 
public:
  struct TRes { 
    TGraph *func;
    double etaMin;
    double etaMax;
    TRes(TGraph *iF,double iEtaMin,double iEtaMax) { 
      func   = iF;
      etaMin = iEtaMin;
      etaMax = iEtaMax;
    }
  };
  JetRes(std::string iFile="/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_7_4_7/src/BaconAnalyzer/MJSelection/Json/fitgraph_v4.root",bool iData=true);
  ~JetRes() {}
  double* getId(std::string iName);
  double res(double iCSV,double iPt,double iEta,double iSig=0.);
  double smear(double iCSV,double iPt,double iEta,double iSig=0.);
  double findSig(std::vector<TRes*> &iBase,std::vector<TRes*> &iSig1,std::vector<TRes*> &iSig2,double iPt,double iEta);
  TRes*  find(std::vector<TRes*> &iBase,double iEta);
protected:
  std::vector<TRes*> fBase;
  std::vector<TRes*> fHBase;
  std::vector<TRes*> fRec;
  std::vector<TRes*> fS1Base;
  std::vector<TRes*> fS1HBase;
  std::vector<TRes*> fS1Rec;
  std::vector<TRes*> fS2Base;
  std::vector<TRes*> fS2HBase;
  std::vector<TRes*> fS2Rec;
  TRandom * fRandom;
  bool      fData;
};
#endif
