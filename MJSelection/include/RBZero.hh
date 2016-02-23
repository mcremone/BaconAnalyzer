#ifndef RBZero_hh
#define RBZero_hh
#include <vector>
#include "RecoilCorrector.hh"
#include "TF1.h"
#include "TLorentzVector.h"
#include "TRandom2.h"
#include "TMatrixD.h"
#include "JetRes.hh"
#include "DataFormats/RecoCandidate/interface/FitQuality.h"

class RBZero {
public:
  RBZero(bool isData);
  ~RBZero();
  reco::FitQuality set(std::vector<TLorentzVector> &iCands,TLorentzVector &iMet,std::vector<double> &iCSV,double &iHT);
  void setSmear(int iBin);
  void setupSmear(); 
  void covMatrix(TMatrixD &iErr,float iJP,float iJPt,float iJEta,float iJPhi,double iCSV);
  std::vector<TLorentzVector> particles() { return fOutput;} 
  std::vector<TLorentzVector> smearParticles(double iSig=0.);
  TLorentzVector smearedJet(TLorentzVector &iVec,double iCSV,double iSig);
private:
  JetRes*          fJetRes;
  TRandom2*        fRandom;
  RecoilCorrector *fCorrector;
  TF1* fPtSmear;
  TF1* fEtaSmear;
  TF1* fPhiSmear;
  double *fPtPar0;
  double *fPtPar1;
  double *fPtPar2;
  double *fPtPar3;;
  double *fEtaPar0;
  double *fEtaPar1;
  double *fEtaPar2;
  double *fEtaPar3;
  double *fEtaPar4;
  double *fPhiPar0;
  double *fPhiPar1;
  double *fPhiPar2;
  double *fPhiPar3;
  double *fPhiPar4;
  float   fMetOut;
  std::vector<TLorentzVector> fOutput;
  std::vector<double> fCSV;
};

#endif
