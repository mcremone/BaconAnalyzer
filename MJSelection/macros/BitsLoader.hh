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
#include "CSample.hh"                 // helper class to manage samples

using namespace std;

class BitsLoader {
public:
  BitsLoader(TTree *iTree=0,TString jet="15",TString algo="PUPPI",TString syst="CENT", string preselection="");		
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
  bool passMetPreselection(string preselection);
  bool passBoostedMonoTopPreselection(string preselection);
  bool passBoosted15MonoX(string preselection);
  bool passBoosted8MonoX(string preselection);
  bool passResolvedMonoTop(string preselection);
  bool passResolvedMonoXbb(string preselection);
  bool passBoostedMonoTopSR(string preselection); 
  bool passBoostedMonoTopQCDCR(string preselection);
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
  // float genvpt(string selection);
  // float genvphi(string selection);

  //
  // variables to read in bacon bits
  //
  int metfilter;                                                                   // MET filter bits          
  unsigned int runNum, lumiSec, evtNum;                                            // event ID
  unsigned int triggerBits, selectBits;                                            // trigger and jet type bits
  double triggerEff;                                                               // trigger efficiency
  float evtWeight, puWeight;                                                       // pu and evt weight
  double eleSF0, eleSF1, eleSF2, muoSF0, muoSF1, muoSF2;                           // weights
  double topSize;                                                                  // topSize
  int isHadronicTop;                                                               // hadronic Top requirement
  unsigned int npu, npv;                                                           // PU, PV multiplicity
  int nmu, nele, ntau, npho;                                                       // object multiplicity
  int njets, nfjets, nf15jets;                                                     // jet multiplicity 
  int nbtags, nbjetsL, nbjetsM, nbjetsT, nbjetsMdR2, nbjetsLdR2;                   // b-jet multiplicity
  float scale1fb;                                                                  // cross section scale factor per 1/fb
  float kfactor;                                                                   // kFactor and EWK correction
  float res_btagwL0, res_btagwL1, res_btagwLminus1, res_btagwL2;                   // btag SF
  float res_btagwM0, res_btagwM1, res_btagwMminus1, res_btagwM2 ;
  float res_btagwT0, res_btagwT1, res_btagwTminus1, res_btagwT2;
  float vmetpt,vmetphi,vfakemetpt,vfakemetphi;                                     // MET
  double min_dphijetsmet;                                                          // min delta phi between MET and narrow jets

  //
  // Jets with pT-ordering:
  //
  double           res_jet0_pt, res_jet0_eta, res_jet0_phi, res_jet0_mass;         // 4 leading resolved jets
  double           res_jet1_pt, res_jet1_eta, res_jet1_phi, res_jet1_mass; 
  double           res_jet2_pt, res_jet2_eta, res_jet2_phi, res_jet2_mass;
  double           res_jet3_pt, res_jet3_eta, res_jet3_phi, res_jet3_mass;
  double           res_jet0_CHF, res_jet0_NHF, res_jet0_NEMF;                      // res jet variables
  float            res_mt;                                                         // res jet mT

  double           bst_jet0_pt,bst_jet0_eta,bst_jet0_phi,bst_jet0_mass;            // leading boosted jet
  double           bst_jet0_msd, bst_jet0_tau32, bst_jet0_tau21;                   // boosted tagger variables                                                                                            
  double           bst_jet0_maxsubcsv, bst_jet0_minsubcsv;                         // subjet btag                                                                                            
  float            bst_jet0_rho, bst_jet0_phil;                                    // msd and pt dependent variables
  double           bst_jet0_CHF, bst_jet0_NHF, bst_jet0_NEMF;                      // boosted jet variables
  float            bst_mt;                                                         // bst jet mT

  // float            genVpt, genVphi;                                                // jet at gen level

  const float ToptagSF     = 1.1318;                                               // ToptagSF
  const float TopmistagSF  = 1.1639;                                               // TopmistagSF 
  const float btagSF       = 0.9851;                                               // btagSF
  const float bmistagSF    = 0.8853;                                               // bmistagSF

protected:

  const unsigned int kMET  = 2;
  const unsigned int kSingleElectron = 4;
  const unsigned int kSinglePhoton  = 8;
  const unsigned int kBOOSTED15PUPPI = 2;
  const unsigned int kRESOLVEDPUPPI = 4;
};
#endif
