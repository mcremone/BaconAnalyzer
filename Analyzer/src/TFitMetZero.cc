#include "../include/TFitMetZero.hh"
#include <iostream>
#include <iomanip>
#include "TLorentzVector.h"
#include "TClass.h"

TFitMetZero::TFitMetZero() : TAbsFitConstraint() 
  ,fParts(0)
  ,fConstraint(0)
{}
TFitMetZero::~TFitMetZero() {}

TFitMetZero::TFitMetZero(Double_t iMet): TAbsFitConstraint() 
  ,fParts(0) {
  fConstraint = iMet;
}
void TFitMetZero::addParticles( std::vector<TFitParticleMCCart*> iParts) {
  for(unsigned int i0 = 0; i0 < iParts.size(); i0++) fParts.push_back(iParts[i0]);
}
TMatrixD* TFitMetZero::getDerivative( TAbsFitParticle* particle ) {
  // returns derivative df/dP with P=(p,E) and f the constraint (f=0).
  // The matrix contains one row (df/dp, df/dE).

  TMatrixD* DerivativeMatrix = new TMatrixD(1,4);
  (*DerivativeMatrix) *= 0.;

  // Pf[4] is the 4-Mom (p,E) of the sum of particles on 
  // the list particle is part of 
  
  Double_t Factor = 0.;
  TLorentzVector Pf(0., 0., 0., 0.);

  UInt_t Npart = fParts.size();
  for (unsigned int i=0; i<Npart; i++) {
    const TLorentzVector* FourVec = (fParts[i])->getCurr4Vec();
    Pf += (*FourVec);
  }
  Factor = 1./ Pf.Pt();
  
  (*DerivativeMatrix)(0,0) = Pf[0] ;
  (*DerivativeMatrix)(0,1) = Pf[1];
  (*DerivativeMatrix)(0,2) = 0;
  (*DerivativeMatrix)(0,3) = 0;
  (*DerivativeMatrix) *= Factor;

  return DerivativeMatrix;
}
Double_t TFitMetZero::getInitValue() {
  Double_t InitValue(0) ;   
  InitValue = met(&fParts,true) - fConstraint ;
  return InitValue;
}
Double_t TFitMetZero::getCurrentValue() {
  Double_t CurrentValue(0);
  CurrentValue = met(&fParts,false) - fConstraint;
  return CurrentValue;
}
Double_t TFitMetZero::met(std::vector<TAbsFitParticle*>* List, Bool_t IniVal) {
  // Calculates initial/current invariant mass of provided list of particles
  TLorentzVector P(0., 0., 0., 0.);
  UInt_t Npart = List->size();
  for (unsigned int i=0;i<Npart;i++) {
    const TLorentzVector* FourVec = 0;
    if (IniVal)
      FourVec = ((*List)[i])->getIni4Vec();
    else      
      FourVec = ((*List)[i])->getCurr4Vec();
    TLorentzVector pVec; pVec.SetPtEtaPhiM(FourVec->Pt(),0,FourVec->Phi(),0);
    P -= pVec;
  }
  return P.Pt();
}
