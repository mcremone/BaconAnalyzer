#ifndef RAZORBITSLOADER_HH
#define RAZORBITSLOADER_HH

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

class RazorBitsLoader {
public:
  RazorBitsLoader(TTree *iTree=0,TString algo="PUPPI",TString syst="CENT", string preselection=" ");		
  ~RazorBitsLoader();
  bool selectJetAlgoAndSize(TString algo);
  bool isMET();
  bool isHad();
  bool isMuo();
  bool isZmm();
  bool isEle();
  bool isZee();
  bool isPho();
  bool passPreSelection(string preselection);
  bool passRazorPreselection();
  bool passRazorSR(string preselection);
  bool passRazorCR(string preselection);
  bool passRazorWCR(string preselection);
  bool passRazorZCR(string preselection);
  
  bool passSelection(string preselection, string subsample, string combo);

  double getWgt(bool isData, TString algo, double LUMI);
  
  //
  // variables to read in bacon bits
  //
  int metfilter;                                                                   // MET filter bits          
  unsigned int runNum, lumiSec, evtNum;                                            // event ID
  unsigned int triggerBits, selectBits;                                            // trigger and jet type bits
  double triggerEff;                                                               // trigger efficiency
  double eleSF0, eleSF1, eleSF2, muoSF0, muoSF1, muoSF2;                           // lepton SFs    
  float evtWeight, puWeight;                                                       // pu and evt weight
  unsigned int npu, npv;                                                           // PU, PV multiplicity
  int njets;                                                                       // jet multiplicity 
  int nbjetsL, nbjetsM, nbjetsT, nbjetsMdR2, nbjetsLdR2;                   // b-jet multiplicity
  int nmu, nele, ntau, npho;                                                       // object multiplicity
  float scale1fb;                                                                  // cross section scale factor per 1/fb
  float kfactor;                                                                   // kFactor and EWK correction
  float res_btagwL0, res_btagwL1, res_btagwLminus1, res_btagwL2;                   // btag SF
  float res_btagwM0, res_btagwM1, res_btagwMminus1, res_btagwM2;
  float res_btagwT0, res_btagwT1, res_btagwTminus1, res_btagwT2;
  float vmetpt,vmetphi,vfakemetpt,vfakemetphi;                                     // MET
  double min_dphijetsmet;                                                          // min delta phi between MET and narrow jets

  //
  // Jets with pT-ordering:
  //
  double           res_jet0_pt, res_jet0_eta, res_jet0_phi, res_jet0_mass;         // narrow jets
  double           res_jet1_pt, res_jet1_eta, res_jet1_phi, res_jet1_mass;
  double           res_jet2_pt, res_jet2_eta, res_jet2_phi, res_jet2_mass; 
  double           res_jet3_pt, res_jet3_eta, res_jet3_phi, res_jet3_mass;
  double           res_jet0_CHF, res_jet0_NHF, res_jet0_NEMF;                      // jet variables
  float            res_mt;                                                         // mT
  float            MR, Rsq, deltaPhi;                                           // razor variables
  int              nJetsAbove80GeV;
  float            HT, MHT;                                                        // HT and MHT

protected:

  const unsigned int kRESOLVEDPUPPI = 2;
  const unsigned int kRESOLVEDCHS = 4;
  const unsigned int kMET  = 2;
  const unsigned int kSingleElectron = 4;
  const unsigned int kSingleMuon = 8;
  const unsigned int kSinglePhoton  = 16;
  const unsigned int kRazor  = 32;

};
#endif
