#ifndef BITSLOADER_HH
#define BITSLOADER_HH

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
//#include "KStyle.hh"                  // style settings for drawing
#include "CSample.hh"                 // helper class to manage samples

using namespace std;

class BitsLoader {
public:
  BitsLoader(TTree *iTree=0,TString algo="",TString syst="", string preselection="");		
  ~BitsLoader();
  bool selectJetAlgoAndSize(string selection, TString algo);
  bool isHad();
  bool isMuo();
  bool isZmm();
  bool isEle();
  bool isZee();
  bool isPho();
  bool passPreSelection(string preselection);
  TLorentzVector getMET(string preselection);
  TLorentzVector getTop();
  bool passBoostedMonoTopPreselection(string preselection);
  bool passBoosted15MonoX(string preselection);
  bool passBoosted8MonoX(string preselection);
  bool passResolvedMonoTop(string preselection);
  bool passResolvedMonoXbb(string preselection);
  bool passBoostedMonoTopSR(string preselection); 
  bool passBoostedMonoTopZnunuHFCR(string preselection);
  bool passBoostedMonoTopZnunuLFCR(string preselection);
  bool passBoostedMonoTopTopCR(string preselection); 
  bool passBoostedMonoTopWCR(string preselection);
  bool passBoostedMonoTopWHFCR(string preselection);
  bool passBoostedMonoTopWLFCR(string preselection);
  bool passBoostedMonoTopZCR(string preselection);
  bool passBoostedMonoTopZHFCR(string preselection);
  bool passBoostedMonoTopZLFCR(string preselection);
  bool passBoostedMonoHbbSR(string preselection);
  bool passBoostedMonoHbbTopCR(string preselection);
  bool passBoostedMonoHbbWCR(string preselection);
  bool passBoostedMonoHbbZCR(string preselection);
  bool passBoostedMonoZbbSR(string preselection);
  bool passBoostedMonoZbbTopCR(string preselection);
  bool passBoostedMonoZbbWCR(string preselection);
  bool passBoostedMonoZbbZCR(string preselection);
  bool passResolvedMonoHbbSR(string preselection);
  bool passResolvedMonoHbbTopCR(string preselection);
  bool passResolvedMonoHbbWCR(string preselection);
  bool passResolvedMonoHbbZCR(string preselection);
  bool passResolvedMonoZbbSR(string preselection);
  bool passResolvedMonoZbbTopCR(string preselection);
  bool passResolvedMonoZbbWCR(string preselection);
  bool passResolvedMonoZbbZCR(string preselection);
  bool passResolvedMonoTopSR(string preselection);
  bool passResolvedMonoTopTopCR(string preselection);
  bool passResolvedMonoTopWCR(string preselection);
  bool passResolvedMonoTopZCR(string preselection);
  bool passBoostedMonoTopTopCRminusTau32(string preselection);
  bool passBoostedMonoTopTopCRminusMass(string preselection);
  bool passBoostedMonoTopTopCRminusBtag(string preselection);
  bool passSelection(string preselection, string selection, string subsample, string combo, float &btagw);
  double getWgt(bool isData, TString algo, double LUMI, float btagw);
  float transverse_mass(string selection);
  float fjet_mass(string selection);
  float nsubjet(string selection);
  float btag(string selection);
  float chf(string selection);
  float nhf(string selection);
  float nemf(string selection);
  float genvpt(string selection);
  float genvphi(string selection);

  unsigned int metfilter;                 // MET filter bits
  //
  // variables to read in bacon bits
  //
  unsigned int runNum, lumiSec, evtNum;   // event ID
  unsigned int triggerBits, selectBits;               // trigger bits
  float triggerEff;                // trigger efficiency
  float evtWeight, puWeight, lepWeight;
  float topSize;
  float npu;                  // number of PU
  float npv;           // number of PV
  unsigned int nmu, nele, ntau, npho;
  unsigned int njets, nf15jets, nf8jets, nbjetsL, nbjetsM, nbjetsT, nbjetsMdR2, nbjetsLdR2;             // jet multiplicity
  float scale1fb;                         // cross section scale factor per 1/fb
  float nloKfactor, ewkCorr;
  float res_btagwL0, res_btagwL1, res_btagwLminus1, res_btagwL2; //btag SF
  float res_btagwM0, res_btagwM1, res_btagwMminus1, res_btagwM2;
  float res_btagwT0, res_btagwT1, res_btagwTminus1, res_btagwT2;
  float bst15_btagwL0, bst15_btagwL1, bst15_btagwLminus1, bst15_btagwL2; //btag SF                                                
  float bst15_btagwM0, bst15_btagwM1, bst15_btagwMminus1, bst15_btagwM2;
  float bst15_btagwT0, bst15_btagwT1, bst15_btagwTminus1, bst15_btagwT2;
  float bst8_btagwL0, bst8_btagwL1, bst8_btagwLminus1, bst8_btagwL2; //btag SF                                               
  float bst8_btagwM0, bst8_btagwM1, bst8_btagwMminus1, bst8_btagwM2;
  float bst8_btagwT0, bst8_btagwT1, bst8_btagwTminus1, bst8_btagwT2;

  TLorentzVector *vmet=0, *vfakemet=0;                  // MET
  float min_dphijetsmet;                // min delta phi between MET and narrow jets

  //
  // Jets with pT-ordering:
  //
  TLorentzVector *res_jet1=0,        *res_jet2=0,        *res_jet3=0,        *res_jet4=0;        // jet 4-vector
  float           res_genVpt, res_genVphi;
  float           res_jet1CHF;
  float           res_jet1NHF;
  float           res_jet1NEMF;
  float           res_jetsm;
  float           res_mt;

  TLorentzVector *bst15_jet1=0;
  float           bst15_jet1msd, bst15_jet1tau32, bst15_jet1tau21; //boosted tagger variables                                                                                            
  float           bst15_jet1maxsubcsv, bst15_jet1minsubcsv; //subjet btag                                                                                            
  float           bst15_genVpt, bst15_genVphi;
  float           bst15_jet1rho, bst15_jet1phil;
  float           bst15_jet1CHF;
  float           bst15_jet1NHF;
  float           bst15_jet1NEMF;
  float           bst15_mt;

  TLorentzVector *bst8_jet1=0;
  float           bst8_jet1msd, bst8_jet1tau32, bst8_jet1tau21; //boosted tagger variables                                                                                            
  float           bst8_jet1maxsubcsv, bst8_jet1minsubcsv; //subjet btag                                                                                            
  float           bst8_genVpt, bst8_genVphi;
  float           bst8_jet1rho, bst8_jet1phil;
  float           bst8_jet1CHF;
  float           bst8_jet1NHF;
  float           bst8_jet1NEMF;
  float           bst8_mt;

  const float ToptagSF     = 1.1318;
  const float TopmistagSF = 1.1639;
  const float btagSF       = 0.9851;
  const float bmistagSF   = 0.8853;

protected:

  const unsigned int kMET  = 2;
  const unsigned int kSingleElectron = 4;
  const unsigned int kSinglePhoton  = 8;
  const unsigned int kBOOSTED15PUPPI = 2;
  const unsigned int kBOOSTED15CHS = 4;
  const unsigned int kBOOSTED8PUPPI = 8;
  const unsigned int kBOOSTED8CHS = 16;
  const unsigned int kRESOLVEDPUPPI = 32;
  const unsigned int kRESOLVEDCHS = 64;
};
#endif
