#ifndef MONOXBITSLOADER_HH
#define MONOXBITSLOADER_HH

#include <TROOT.h>                    // access to gROOT, entry point to ROOT system
#include <TSystem.h>                  // interface to OS
#include <TStyle.h>                   // class to handle ROOT plotting styles
#include <TFile.h>                    // file handle class
#include <TTree.h>                    // class to access ntuples
#include <TH1D.h>                     // 1D histogram class
#include <TLorentzVector.h>           // 4-vector class
#include <vector>                     // STL vector class
#include <iostream>                   // standard I/O
#include <iomanip>                    // functions to format standard I/O
#include <fstream>                    // functions for file I/O
#include <string>                     // C++ string class
#include <cmath>                      // C++ math library
#include <cassert>

#include "CPlot.hh"                   // helper class for plots
#include "CSample.hh"                 // helper class to manage samples

using namespace std;

class MonoXBitsLoader {
public:
  MonoXBitsLoader(TTree *iTree=0,TString bst15jetID="jetT", TString bst8jetID="jetT", TString algo="PUPPI",TString syst="CENT", string preselection="", bool isData=false);		
  ~MonoXBitsLoader();
  bool selectJetAlgoAndSize(string selection, TString algo, TString bst15jetID, TString bst8jetID);
  bool isHad();
  bool isMuo();
  bool isZmm();
  bool isEle();
  bool isZee();
  bool isPho();
  bool passPreSelection(string preselection);
  TLorentzVector getMET(string preselection);
  TLorentzVector getTop();
  TLorentzVector getHiggs();
  bool passBoostedMonoTopPreselection(string preselection);
  bool passBoosted8MonoHbbPreselection(string preselection);
  bool passBoosted15MonoHbbPreselection(string preselection);
  bool passResolvedMonoHbbPreselection(string preselection);
  bool passBoosted8CMSMonoHbbPreselection(string preselection);
  bool passResolvedCMSMonoHbbPreselection(string preselection);

  bool passBoostedMonoTopSR(string preselection);
  bool passBoostedMonoTopTopCR(string preselection); 
  bool passBoostedMonoTopTopCRminusTau32(string preselection);
  bool passBoostedMonoTopTopCRminusMass(string preselection);
  bool passBoostedMonoTopTopCRminusBtag(string preselection);
  bool passBoostedMonoTopWCR(string preselection);
  bool passBoostedMonoTopZCR(string preselection);

  bool passBoosted15MonoHbbSR(string preselection, float csvb0 = 0.3, float csvb1 = 1000);
  bool passBoosted15MonoHbbTopCR(string preselection, float csvb0 = 0.3, float csvb1 = 1000);
  bool passBoosted15MonoHbbWCR(string preselection, float csvb0 = 0.3, float csvb1 = 1000);
  bool passBoosted15MonoHbbZCR(string preselection);

  bool passBoosted8MonoHbbSR(string preselection, float csvb0, float csvb1);
  bool passBoosted8MonoHbbTopCR(string preselection, float csvb0, float csvb1);
  bool passBoosted8MonoHbbWCR(string preselection, float csvb0, float csvb1);
  bool passBoosted8MonoHbbZCR(string preselection);

  bool passResolvedMonoHbbSR(string preselection);
  bool passResolvedMonoHbbTopCR(string preselection);
  bool passResolvedMonoHbbWCR(string preselection);
  bool passResolvedMonoHbbZCR(string preselection);

  bool passBoosted8CMSMonoHbbSR(string preselection, float csvb0, float csvb1);
  bool passResolvedCMSMonoHbbSR(string preselection);

  bool passSelection(string preselection, string selection, string subsample, string combo, float &btagw, TString syst, bool isSignal);
  int nfjets(string selection);
  float fjet_mass(string selection);
  float fjet_pt(string selection);
  float transverse_mass(string selection);
  float tau21(string selection);
  float tau32(string selection);
  float rho(string selection);
  float minsubcsv(string selection);
  float maxsubcsv(string selection);
  float doublecsv(string selection);
  float chf(string selection);
  float nhf(string selection);
  float nemf(string selection);
  float getDoublebWeight(TString syst, bool isSignal, string doublecsv, int NminBjets, float bstpt);
  double getWgt(bool isData, TString algo, double LUMI, float btagw);
  double tau32DDT(string selection);
  double tau21DDT(string selection);
  double getMsdSqPt(string selection);
  double getdRsj0dR(string selection);
  double getdRsj0dRpt(string selection);
  double getdPsj0dP(string selection);

  //
  // variables to read in bacon bits
  //
  int metfilter;                                                                     // MET filter bits          
  unsigned int runNum, lumiSec, evtNum;                                              // event ID
  unsigned int triggerBits, selectBits;                                              // trigger and jet type bits
  double triggerEff;                                                                 // trigger efficiency
  float evtWeight, puWeight;                                                         // pu and evt weight
  double eleSF0, eleSF1, eleSF2, muoSF0, muoSF1, muoSF2, phoSF0;                     // weights
  double topSize15, vSize15, topSize8, vSize8;                                       // topSize and vSize
  double topMatching15, vMatching15, topMatching8, vMatching8;                       // topMatching and vMatching
  int isHadronicTop15, isHadronicV15, isHadronicTop8, isHadronicV8;                  // hadronic Top and hadronic Boson requirement
  unsigned int npu, npv;                                                             // PU, PV multiplicity
  int nmu, nele, ntau, npho;                                                         // object multiplicity
  int njets, njetsdR2, njetsdR15, nfjets15, nfjets8, nfjets15T, nfjets8T;            // jet multiplicity 
  int nbtags, nbjetsL, nbjetsM, nbjetsT, nbjetsMdR2, nbjetsLdR2, nbjetsLdR15;        // b-jet multiplicity
  float scale1fb;                                                                    // cross section scale factor per 1/fb
  float kfactor;                                                                     // kFactor and EWK correction
  float res_btagwL0, res_btagwL1, res_btagwLminus1, res_btagwL2;                     // btag SF
  float res_btagwM0, res_btagwM1, res_btagwMminus1, res_btagwM2;
  float res_btagwT0, res_btagwT1, res_btagwTminus1, res_btagwT2;
  float resbst15_btagwL0, resbst15_btagwL1, resbst15_btagwLminus1, resbst15_btagwL2; // btag SF for dR(jets,bst15)>2
  float resbst15_btagwM0, resbst15_btagwM1, resbst15_btagwMminus1, resbst15_btagwM2;
  float resbst15_btagwT0, resbst15_btagwT1, resbst15_btagwTminus1, resbst15_btagwT2;
  float resbst8_btagwL0, resbst8_btagwL1, resbst8_btagwLminus1, resbst8_btagwL2;     // btag SF for dR(jets,bst8)>2 
  float resbst8_btagwM0, resbst8_btagwM1, resbst8_btagwMminus1, resbst8_btagwM2;
  float resbst8_btagwT0, resbst8_btagwT1, resbst8_btagwTminus1, resbst8_btagwT2;

  float bst15_btagwL0, bst15_btagwL1, bst15_btagwLminus1, bst15_btagwL2;             // subjet btag SF 
  float bst15_btagwM0, bst15_btagwM1, bst15_btagwMminus1, bst15_btagwM2;
  float bst15_btagwT0, bst15_btagwT1, bst15_btagwTminus1, bst15_btagwT2;
  float bst8_btagwL0, bst8_btagwL1, bst8_btagwLminus1, bst8_btagwL2;                 // subjet btag SF 08
  float bst8_btagwM0, bst8_btagwM1, bst8_btagwMminus1, bst8_btagwM2;
  float bst8_btagwT0, bst8_btagwT1, bst8_btagwTminus1, bst8_btagwT2;

  float bst15_btagwL0T, bst15_btagwL1T, bst15_btagwLminus1T, bst15_btagwL2T;         // subjet btag SF TightJetID
  float bst15_btagwM0T, bst15_btagwM1T, bst15_btagwMminus1T, bst15_btagwM2T;
  float bst15_btagwT0T, bst15_btagwT1T, bst15_btagwTminus1T, bst15_btagwT2T;
  float bst8_btagwL0T, bst8_btagwL1T, bst8_btagwLminus1T, bst8_btagwL2T;             // subjet btag SF 08 TightJetID
  float bst8_btagwM0T, bst8_btagwM1T, bst8_btagwMminus1T, bst8_btagwM2T;
  float bst8_btagwT0T, bst8_btagwT1T, bst8_btagwTminus1T, bst8_btagwT2T;

  float genVpt, genVphi;                                                             // gen boson
  float vmetpt,vmetphi,vfakemetpt,vfakemetphi;                                       // MET
  double min_dphijetsmet;                                                            // min delta phi between MET and narrow jets

  //
  // Jets with pT-ordering:
  //
  double           res_jet0_pt, res_jet0_eta, res_jet0_phi, res_jet0_mass;           // 4 leading resolved jets
  double           res_jet1_pt, res_jet1_eta, res_jet1_phi, res_jet1_mass; 
  double           res_jet2_pt, res_jet2_eta, res_jet2_phi, res_jet2_mass;
  double           res_jet3_pt, res_jet3_eta, res_jet3_phi, res_jet3_mass;
  double           res_jet0_CHF, res_jet0_NHF, res_jet0_NEMF;                        // res jet variables
  float            res_jet0_mT;                                                      // res jet mT

  double           bst15_jet0_pt,bst15_jet0_eta,bst15_jet0_phi,bst15_jet0_mass;      // leading boosted jet
  double           bst15_jet0_msd, bst15_jet0_tau32, bst15_jet0_tau21;               // boosted tagger variables                                                                                            
  double           bst15_jet0_maxsubcsv, bst15_jet0_minsubcsv;                       // subjet btag
  double           bst15_jet0_doublecsv;                                             // double btag                            
  double           bst15_jet0_rho, bst15_jet0_phil;                                  // msd and pt dependent variables
  double           bst15_jet0_CHF, bst15_jet0_NHF, bst15_jet0_NEMF;                  // boosted jet variables
  float            bst15_jet0_mT;                                                    // bst jet mT
  float            bst15_jet0_dRsj0dR, bst15_jet0_dPhiJRFsj0dPhiJRF;                 // dRs and dPhis

  double           bst8_jet0_pt,bst8_jet0_eta,bst8_jet0_phi,bst8_jet0_mass;          // leading boosted jet
  double           bst8_jet0_msd, bst8_jet0_tau32, bst8_jet0_tau21;                  // boosted tagger variables
  double           bst8_jet0_maxsubcsv, bst8_jet0_minsubcsv;                         // subjet btag
  double           bst8_jet0_doublecsv;                                              // double btag
  double           bst8_jet0_rho, bst8_jet0_phil;                                    // msd and pt dependent variables
  double           bst8_jet0_CHF, bst8_jet0_NHF, bst8_jet0_NEMF;                     // boosted jet variables
  float            bst8_jet0_mT;                                                     // bst jet mT
  float            bst8_jet0_dRsj0dR,bst8_jet0_dPhiJRFsj0dPhiJRF;                    // dRs and dPhis                                                                                         

  const float ToptagSF     = 1.1318;                                                 // ToptagSF
  const float TopmistagSF  = 1.1639;                                                 // TopmistagSF 
  const float btagSF       = 0.9851;                                                 // btagSF
  const float bmistagSF    = 0.8853;                                                 // bmistagSF

  const float CSVL = 0.460;                                                          // CSVL - WPs for 76x
  const float CSVM = 0.800;                                                          // CSVM
  const float CSVT = 0.935;                                                          // CSVT

  const float CSVbL = 0.3;                                                           // CSVbL - WPs for Doubleb
  const float CSVbM = 0.6;                                                           // CSVbM
  const float CSVbT = 0.9;                                                           // CSVbT 

  std::vector<float> doubleb_eff, doubleb_mistag_eff, doublebSF, mistagdoublebSF;
  std::vector<float> ptbinlow, ptbinhigh;

  float mcTag = 1.;
  float mcNoTag = 1.;
  float dataTag = 1.;
  float dataNoTag = 1.;

protected:

  const unsigned int kMET  = 2;
  const unsigned int kSingleElectron27 = 4;
  const unsigned int kSingleElectron23 = 8;
  const unsigned int kSinglePhoton  = 16;
  const unsigned int kBOOSTED15PUPPI = 2;
  const unsigned int kBOOSTED15CHS = 4;
  const unsigned int kBOOSTED8PUPPIT = 8;
  const unsigned int kBOOSTED8CHS = 16;
  const unsigned int kRESOLVEDPUPPI = 32;
  const unsigned int kRESOLVEDCHS = 64;
  
  const float RHO_CUT = 0.72;

};
#endif
