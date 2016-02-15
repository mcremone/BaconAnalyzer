#include "../include/RBZero.hh"
#include "../include/TFitMetZero.hh"
#include "PhysicsTools/RecoUtils/interface/CandMassKinFitter.h"
#include "PhysicsTools/KinFitter/interface/TKinFitter.h"
#include "DataFormats/RecoCandidate/interface/RecoCandidate.h"
#include "PhysicsTools/KinFitter/interface/TFitParticleMCCart.h"
#include "TMatrixD.h"
#include <iostream>

RBZero::RBZero(bool iData) { 
  fRandom = new TRandom2(0xDEADBEEF);
  //fCorrector = new RecoilCorrector("files/recoilfit_zmmData_pf_v1.root");
  std::string lName = "/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_7_4_7/src/BaconAnalyzer/MJSelection/prod/files/";
  if( iData) lName += "recoilfit_zmmData_pf_v2.root";
  if(!iData) lName += "recoilfit_zmmMC_pf_v2.root";
  fCorrector = new RecoilCorrector(lName);
  std::string lRes = "/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_7_4_7/src/BaconAnalyzer/MJSelection/Json/fitgraph_v4.root";
  lRes = "/afs/cern.ch/user/p/pharris/pharris/public/bacon/prod/CMSSW_7_4_7/src/BaconAnalyzer/MJSelection/Json/";
  if(iData)  lRes += "fitgraph_v6_vtx.root";
  if(!iData) lRes += "fitgraph_v4.root";
  std::cout << " Recoil " << lName << std::endl;
  std::cout << " Recoil " << lRes  << std::endl;
  fJetRes = new JetRes(lRes,iData);
  setupSmear();
  fMetOut = 0;
}
RBZero::~RBZero() { }
reco::FitQuality RBZero::set(std::vector<TLorentzVector> &iCands,TLorentzVector &iMet,std::vector<double> &iCSV,double &iHT) {
  TKinFitter fitter("CandMassFit", "CandMassFit");
  TString name("dau0");
  int lNCands = iCands.size();
  TLorentzVector lSum; lSum.SetPtEtaPhiM(0,0,0,0);
  std::vector<TMatrixD> lErrors(lNCands+2, TMatrix(3,3));
  std::vector<TVector3> lMomenta(lNCands+2);
  std::vector<TFitParticleMCCart *> lParticles(lNCands+2, 0);
  TFitMetZero lConstraint(0);
  for (int i0 = 0; i0 < lNCands; i0++ ) {
    TLorentzVector pVec = iCands  [i0];
    TMatrixD      &pErr = lErrors [i0];
    TVector3      &pMom = lMomenta[i0];
    lSum += pVec;
    pMom = TVector3( pVec.Px(), pVec.Py(), pVec.Pz() );
    covMatrix(pErr,pVec.P(),pVec.Pt(),pVec.Eta(),pVec.Phi(),iCSV[i0]);
    fitter.addMeasParticle( lParticles[i0] = new TFitParticleMCCart( name, name, &pMom, pVec.M(), &pErr ) );
    name[3]++;
  }
  TLorentzVector lU = iMet+lSum;
  lU.RotateZ(TMath::Pi());
  iHT += lU.Pt();
  TMatrixD      &lErr  = lErrors [lNCands];
  TMatrixD      &lErr2 = lErrors [lNCands+1];
  TVector3      &lMom  = lMomenta[lNCands];
  TVector3      &lMom2 = lMomenta[lNCands+1];
  lMom  = TVector3( 2.0*(lU.Px()), 2.0*(lU.Py()),  0.01 );
  lMom2 = TVector3(-1.0*(lU.Px()),-1.0*(lU.Py()), -0.01 );
  //fCorrector->covMatrix(lErr,lU.Pt(),lU.Phi(),0.);
  covMatrix(lErr, lMom .Mag(),lMom .Pt(),0.,lMom .Phi(),-100.);
  //lErr *= 100.;
  covMatrix(lErr2,lMom2.Mag(),lMom2.Pt(),0.,lMom2.Phi(),-100.);
  fitter.addMeasParticle( lParticles[lNCands]   = new TFitParticleMCCart( name, name, &lMom,  0., &lErr ) );
  fitter.addMeasParticle( lParticles[lNCands+1] = new TFitParticleMCCart( name, name, &lMom2, 0., &lErr2 ) );
  lConstraint.addParticles(lParticles);
  fitter.addConstraint(&lConstraint);
  fitter.setMaxNbIter( 30 );
  fitter.setMaxDeltaS( 1e-2 );
  fitter.setMaxF( 1e-1 );
  fitter.setVerbosity( 0 );			
  if(iCands.size() > 0) fitter.fit();
  lSum.SetPtEtaPhiM( 0, 0, 0, 0 );
  fMetOut = 0;
  fOutput.clear();
  fCSV   .clear();
  for(int i0 = 0; i0 < lNCands+2; i0++) {
    const TLorentzVector * pVec =  lParticles[i0]->getCurr4Vec();
    double pM = 0; if(i0 < lNCands) pM = iCands[i0].M();
    TLorentzVector lVec; lVec .SetPtEtaPhiM(pVec->Pt(),pVec->Eta(),pVec->Phi(),pM);
    //if(i0  <  lNCands) lVec .SetPtEtaPhiM(iGenCands[i0].Pt(),iGenCands[i0].Eta(),iGenCands[i0].Phi(),iGenCands[i0].Phi());
    if(i0 == lNCands+1) fOutput[i0-1] += lVec;
    if(i0  < lNCands+1) fOutput.push_back(lVec);
    lSum -= lVec;
    //if(i0 < lNCands) std::cout << " ----> " << lVec.Pt() << " -- " << lVec.Eta() << " -- " << iCands[i0].Pt() << " -- " << iCands[i0].Eta() << std::endl;
    if(i0 < lNCands) fCSV.push_back(iCSV[i0]);
    if(i0 == lNCands) fCSV.push_back(-100);
    delete lParticles[i0];
  }
  fMetOut = lSum.Pt();
  //std::cout << " Before : " << iMet.Pt() << " ---> " << fMetOut << " -- " << fitter.getS() << " -- " << fitter.getStatus() << std::endl;
  return reco::FitQuality( fitter.getS(), fitter.getNDF());
}
void RBZero::setSmear(int iBin) {
  fPtSmear->SetParameter(0,fPtPar0[iBin]);
  fPtSmear->SetParameter(1,fPtPar1[iBin]);
  fPtSmear->SetParameter(2,fPtPar2[iBin]);
  fPtSmear->SetParameter(3,fPtPar3[iBin]);

  fPhiSmear->SetParameter(0,fPhiPar0[iBin]);
  fPhiSmear->SetParameter(1,fPhiPar1[iBin]);
  fPhiSmear->SetParameter(2,fPhiPar2[iBin]);
  fPhiSmear->SetParameter(3,fPhiPar3[iBin]);
  fPhiSmear->SetParameter(4,fPhiPar4[iBin]);

  fEtaSmear->SetParameter(0,fEtaPar0[iBin]);
  fEtaSmear->SetParameter(1,fEtaPar1[iBin]);
  fEtaSmear->SetParameter(2,fEtaPar2[iBin]);
  fEtaSmear->SetParameter(3,fEtaPar3[iBin]);
  fEtaSmear->SetParameter(4,fEtaPar4[iBin]);
}
void RBZero::covMatrix(TMatrixD &iErr,float iJP,float iJPt,float iJEta,float iJPhi,double iCSV) {
  int iBin = 9-int(fabs(iJEta)*2.);
  if(iBin < 0) iBin = 0;
  setSmear(iBin);
  double lSigma    = fJetRes->res(iCSV,iJPt,iJEta);//*1.2;//fPtSmear ->Eval(iJPt)*iJPt;
  double lSigmaEta = fEtaSmear->Eval(iJPt);//*iJPt;
  double lSigmaPhi = fPhiSmear->Eval(iJPt);//*iJPt;
  double lTheta    = 2*atan(exp(-1*iJEta));
  double lSigmaTheta = sin(lTheta)*lSigmaEta;
  //build Jacobian
  TMatrixD lJacobi(3,3);
  lJacobi(0,0) =  sin(lTheta)*cos(iJPhi);
  lJacobi(1,0) =  sin(lTheta)*sin(iJPhi);
  lJacobi(2,0) =  cos(lTheta);
  lJacobi(0,1) =  iJP*cos(lTheta)*cos(iJPhi);
  lJacobi(1,1) =  iJP*cos(lTheta)*sin(iJPhi);
  lJacobi(2,1) = -iJP*sin(lTheta);
  lJacobi(0,2) = -iJP*sin(lTheta)*sin(iJPhi);
  lJacobi(1,2) =  iJP*sin(lTheta)*cos(iJPhi);
  lJacobi(2,2) =  0.;
  TMatrixD  lJT = lJacobi.Transpose(lJacobi);
  lJacobi.Transpose(lJacobi);
  TMatrixD  lErr(3,3);
  lErr(0,0)    = lSigma*lSigma;
  lErr(1,1)    = lSigmaTheta*lSigmaTheta;
  lErr(2,2)    = lSigmaPhi*lSigmaPhi;
  iErr = lJacobi*lErr*lJT;
  return;
  std::cout << "start" << std::endl;
  lErr.Print();
  std::cout << "jacobi" << std::endl;
  lJacobi.Print();
  std::cout << "jt" << std::endl;
  lJT.Print();
  std::cout << "cov" << std::endl;
   iErr.Print();
}
void RBZero::setupSmear() {
  //Smear in Pt
  fPtSmear = new TF1("JetPt","sqrt(((TMath::Sign(1,[0])*sq([0]/x))+(sq([1])*(x^([3]-1))))+sq([2]))");
  fPtPar0 = new double[10];
  fPtPar1 = new double[10];
  fPtPar2 = new double[10];
  fPtPar3 = new double[10];
  //9 Eta Bins
  fPtPar0[0] =  1.41584;  fPtPar1[0] = 0.209477; fPtPar2[0] = 0; fPtPar3[0] =  0.588872;
  fPtPar0[1] =  1.41584;  fPtPar1[1] = 0.209477; fPtPar2[1] = 0; fPtPar3[1] =  0.588872;
  fPtPar0[2] =  1.65966;  fPtPar1[2] = 0.223683; fPtPar2[2] = 0; fPtPar3[2] =  0.60873;
  fPtPar0[3] =  2.81978;  fPtPar1[3] = 0.272373; fPtPar2[3] = 0; fPtPar3[3] =  0.579396;
  fPtPar0[4] =  2.56933;  fPtPar1[4] = 0.305802; fPtPar2[4] = 0; fPtPar3[4] =  0.398929;
  fPtPar0[5] =  1.04792;  fPtPar1[5] = 0.466763; fPtPar2[5] = 0; fPtPar3[5] =  0.193137;
  fPtPar0[6] = -1.12329;  fPtPar1[6] = 0.657891; fPtPar2[6] = 0; fPtPar3[6] =  0.139595;
  fPtPar0[7] = -0.561649; fPtPar1[7] = 0.420293; fPtPar2[7] = 0; fPtPar3[7] =  0.392398;
  fPtPar0[8] = -0.499735; fPtPar1[8] = 0.336391; fPtPar2[8] = 0; fPtPar3[8] =  0.430689;
  fPtPar0[9] = -0.349206; fPtPar1[9] = 0.297831; fPtPar2[9] = 0; fPtPar3[9] =  0.471121;
  //Smear in Eta
  fEtaSmear = new TF1("JetEta","(sqrt((sq([0]/x)+(sq([1])/x))+sq([2]))+([3]/x))+(([4]/x)/sqrt(x))");
  fEtaPar0 = new double[10];
  fEtaPar1 = new double[10];
  fEtaPar2 = new double[10];
  fEtaPar3 = new double[10];
  fEtaPar4 = new double[10];
  //9 bins again
  fEtaPar0[0] = 0.710478; fEtaPar1[0] = 0.143847;     fEtaPar2[0] = -2.52411e-05; fEtaPar3[0] = 0.77394;  fEtaPar4[0] = -1.89622;
  fEtaPar0[1] = 527.518;  fEtaPar1[1] = -0.0143625;   fEtaPar2[1] = 0.316441;     fEtaPar3[1] =-526.599;  fEtaPar4[1] =  0.244142;
  fEtaPar0[2] = 0.494977; fEtaPar1[2] =  1.48277e-06; fEtaPar2[2] = 0.0171135;    fEtaPar3[2] = 0.354901; fEtaPar4[2] =  0.554065;
  fEtaPar0[3] =  2.88983; fEtaPar1[3] = -1.71576e-06; fEtaPar2[3] = 0.0402796;    fEtaPar3[3] = -1.72649; fEtaPar4[3] = -0.124126;
  fEtaPar0[4] = 0.851656; fEtaPar1[4] =  4.56968e-07; fEtaPar2[4] = 0.0441276;    fEtaPar3[4] =-0.101993; fEtaPar4[4] =  0.773812;
  fEtaPar0[5] =  9.64435; fEtaPar1[5] =  0.458594 ;   fEtaPar2[5] = 1.92485e-08;  fEtaPar3[5] = -8.67043; fEtaPar4[5] = -0.0541106;
  fEtaPar0[6] = 0.343262; fEtaPar1[6] = -3.39452e-07; fEtaPar2[6] = 0.00849674;   fEtaPar3[6] =  1.05358; fEtaPar4[6] = -1.24367;
  fEtaPar0[7] = 0.572596; fEtaPar1[7] = -1.09687e-07; fEtaPar2[7] = 0.0094876;    fEtaPar3[7] = 0.799819; fEtaPar4[7] = -1.23444;
  fEtaPar0[8] = 0.622981; fEtaPar1[8] =  0.100943;    fEtaPar2[8] = 0.00744374;   fEtaPar3[8] = 0.317454; fEtaPar4[8] = -0.324557;
  fEtaPar0[9] =  355.708; fEtaPar1[9] =  2.20794;     fEtaPar2[9] = 0.032666;     fEtaPar3[9] = -354.691; fEtaPar4[9] = -0.857295;
  //No I'm going to kill myself
  fPhiSmear = new TF1("JetPhi","(sqrt((sq([0]/x)+(sq([1])/x))+sq([2]))+([3]/x))+(([4]/x)/sqrt(x))");
  fPhiPar0  = new double[10];
  fPhiPar1  = new double[10];
  fPhiPar2  = new double[10];
  fPhiPar3  = new double[10];
  fPhiPar4  = new double[10];
  //10 bins again
  fPhiPar0[0] = 259.189 ;    fPhiPar1[0] =  0.00132792;  fPhiPar2[0] = -0.311411;     fPhiPar3[0] = -258.647; fPhiPar4[0] =   0;
  fPhiPar0[1] = 0.765787;    fPhiPar1[1] = -3.90638e-06; fPhiPar2[1] = -4.70224e-08;  fPhiPar3[1] = 0.11831;  fPhiPar4[1] =  -1.4675;
  fPhiPar0[2] = 2.11446;     fPhiPar1[2] =  0.203329;    fPhiPar2[2] = -0.0175832;    fPhiPar3[2] = -1.67946; fPhiPar4[2] =  -0.00853474;
  fPhiPar0[3] = 1.9027;      fPhiPar1[3] = -4.56986e-06; fPhiPar2[3] = 0.0304793;     fPhiPar3[3] = -1.09124; fPhiPar4[3] =  -0.136402;
  fPhiPar0[4] = 11.1957;     fPhiPar1[4] =  0.643236;    fPhiPar2[4] = 0.00711422;    fPhiPar3[4] = -10.7613; fPhiPar4[4] =   0.280927;
  fPhiPar0[5] = 0.00336639;  fPhiPar1[5] =  0.0880209;   fPhiPar2[5] = -0.0023084;    fPhiPar3[5] = 0.214304; fPhiPar4[5] =  -0.416353;
  fPhiPar0[6] = 2.92001e-07; fPhiPar1[6] =  0.0718389;   fPhiPar2[6] = -0.00385579;   fPhiPar3[6] = 0.403668; fPhiPar4[6] =  -0.62698;
  fPhiPar0[7] = 0.38469 ;    fPhiPar1[7] =  0.0755727;   fPhiPar2[7] = -0.0044353;    fPhiPar3[7] = 0.453887; fPhiPar4[7] =  -1.8947;
  fPhiPar0[8] = 3.32512e-06; fPhiPar1[8] =  0.063941;    fPhiPar2[8] = -0.00387593;   fPhiPar3[8] = 0.301932; fPhiPar4[8] =  -0.825352;
  fPhiPar0[9] = 926.978;     fPhiPar1[9] =  2.52747;     fPhiPar2[9] = 0.0304001;     fPhiPar3[9] = -926.224; fPhiPar4[9] =  -1.94117;
}
std::vector<TLorentzVector> RBZero::smearParticles(double iSig) { 
  std::vector<TLorentzVector> lSmeared; 
  for(unsigned int i0 = 0; i0 < fOutput.size()-1; i0++) {
    TLorentzVector pVec = smearedJet(fOutput[i0],fCSV[i0],iSig);
    lSmeared.push_back(pVec);
  }
  //return lSmeared;
  double lMet    = fOutput[fOutput.size()-1].Pt();
  double lMetPhi = fOutput[fOutput.size()-1].Phi();
  double lU1 =0,lU2=0;
  int lNCand = 0.;
  fCorrector->CorrectAll(lMet,lMetPhi,fOutput[fOutput.size()-1].Pt(),fOutput[fOutput.size()-1].Phi(),0,0,lU1,lU2,0,0,lNCand);
  // TLorentzVector pVec = smearedJet(fOutput[fOutput.size()-1],-100.,iSig);
  TLorentzVector lVec; lVec.SetPtEtaPhiM(lMet,0,lMetPhi,0); //lVec.RotateZ(TMath::Pi());
  lSmeared.push_back(lVec);
  return lSmeared;
}
TLorentzVector RBZero::smearedJet(TLorentzVector &iVec,double iCSV,double iSig) { 
  int iBin = 9-int(fabs(iVec.Eta())*2.);
  if(iBin < 0) iBin = 0;
  setSmear(iBin);
  //double lSigma    = fPtSmear ->Eval(iVec.Pt())*iVec.Pt();
  //double lSigmaEta = fEtaSmear->Eval(iVec.Pt());
  //double lSigmaPhi = fPhiSmear->Eval(iVec.Pt());
  double lOldJPt   = iVec.Pt();
  double lJPt      = fJetRes->smear(iCSV,iVec.Pt(),iVec.Eta(),iSig);//fRandom->Gaus(iVec.Pt() , lSigma);
  double lJEta     = iVec.Eta();//fRandom->Gaus(iVec.Eta(),lSigmaEta);
  double lJPhi     = iVec.Phi();//fRandom->Gaus(iVec.Phi(),lSigmaPhi);
  double lJM       = (iVec.Pt()/lOldJPt) * iVec.M();
  TLorentzVector lVec;
  lVec.SetPtEtaPhiM(lJPt,lJEta,lJPhi,lJM);
  return lVec;
}
