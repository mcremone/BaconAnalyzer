#ifndef TFitMetZero_hh
#define TFitMetZero_hh

#include "PhysicsTools/KinFitter/interface/TAbsFitConstraint.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleMCCart.h"
#include <vector>

#include "TMatrixD.h"

class TAbsFitParticle;

class TFitMetZero: public TAbsFitConstraint {

public :

  TFitMetZero();
  TFitMetZero(double iMet);
  virtual ~TFitMetZero();
  void setMetConstraint(Double_t iMet) { fConstraint = iMet; }
  void addParticles( std::vector<TFitParticleMCCart*> iParts);
  virtual TMatrixD* getDerivative( TAbsFitParticle* particle );
  virtual Double_t getInitValue();
  virtual Double_t getCurrentValue();
  Double_t met(std::vector<TAbsFitParticle*>* List, Bool_t IniVal);

protected :
  
  std::vector<TAbsFitParticle*> fParts;
  Double_t fConstraint;
  
};

#endif
