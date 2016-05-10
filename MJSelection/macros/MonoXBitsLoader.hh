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
  MonoXBitsLoader(TTree *iTree=0,TString jetID="jet", TString algo="PUPPI",TString syst="CENT", string preselection="", bool isData=false);		
  ~MonoXBitsLoader();
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
  bool passBoostedMonoXPreselection(string preselection);

  bool passBoostedMonoTopSR(string preselection);
  bool passBoostedMonoTopQCDCR(string preselection); 
  bool passBoostedMonoTopTopCR2(string preselection);
  bool passBoostedMonoTopTopCR(string preselection); 
  bool passBoostedMonoTopTTbarCR(string preselection);
  bool passBoostedMonoTopRhoTau32DDTCR(string preselection);
  bool passBoostedMonoTopMsdPtTau32DDTCR(string preselection, float MSDSQPT_CUT);
  bool passBoostedMonoTopTopCRminusTau32(string preselection);
  bool passBoostedMonoTopTopCRminusMass(string preselection);
  bool passBoostedMonoTopTopCRminusBtag(string preselection);
  bool passBoostedMonoTopWCR(string preselection);
  bool passBoostedMonoTopZCR(string preselection);

  bool passBoostedMonoHbbSR(string preselection);
  bool passBoostedMonoHbbTopCR(string preselection);
  bool passBoostedMonoHbbWCR(string preselection);
  bool passBoostedMonoHbbZCR(string preselection);

  bool passSelection(string preselection, string selection, string subsample, string combo, float &btagw, TString syst);
  float transverse_mass(string selection);
  float fjet_mass(string selection);
  float nsubjet(string selection);
  float btag(string selection);
  float chf(string selection);
  float nhf(string selection);
  float nemf(string selection);
  void getDoublebWeight(TString syst, float &doublebw_L0, float &doublebw_L1);
  double getWgt(bool isData, TString algo, double LUMI, float btagw);
  double tau32DDT();
  double tau21DDT();
  double getMsdSqPt();

  //
  // variables to read in bacon bits
  //
  int metfilter;                                                                   // MET filter bits          
  unsigned int runNum, lumiSec, evtNum;                                            // event ID
  unsigned int triggerBits, selectBits;                                            // trigger and jet type bits
  double triggerEff;                                                               // trigger efficiency
  float evtWeight, puWeight;                                                       // pu and evt weight
  double eleSF0, eleSF1, eleSF2, muoSF0, muoSF1, muoSF2, phoSF0;                   // weights
  double topSize15, topMatching15;                                                 // topSize and topMatching
  int isHadronicTop15;                                                             // hadronic Top requirement
  unsigned int npu, npv;                                                           // PU, PV multiplicity
  int nmu, nele, ntau, npho;                                                       // object multiplicity
  int njets, nfjets15;                                                             // jet multiplicity 
  int nbtags, nbjetsL, nbjetsM, nbjetsT, nbjetsMdR2, nbjetsLdR2;                   // b-jet multiplicity
  float scale1fb;                                                                  // cross section scale factor per 1/fb
  float kfactor;                                                                   // kFactor and EWK correction
  float res_btagwL0, res_btagwL1, res_btagwLminus1, res_btagwL2;                   // btag SF
  float res_btagwM0, res_btagwM1, res_btagwMminus1, res_btagwM2 ;
  float res_btagwT0, res_btagwT1, res_btagwTminus1, res_btagwT2;
  float bst15_btagwL0, bst15_btagwL1, bst15_btagwLminus1, bst15_btagwL2;           // subjet btag SF 
  float bst15_btagwM0, bst15_btagwM1, bst15_btagwMminus1, bst15_btagwM2 ;
  float bst15_btagwT0, bst15_btagwT1, bst15_btagwTminus1, bst15_btagwT2;
  float genVpt, genVphi;                                                           // gen boson
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

  double           bst15_jet0_pt,bst15_jet0_eta,bst15_jet0_phi,bst15_jet0_mass;    // leading boosted jet
  double           bst15_jet0_msd, bst15_jet0_tau32, bst15_jet0_tau21;             // boosted tagger variables                                                                                            
  double           bst15_jet0_maxsubcsv, bst15_jet0_minsubcsv;                     // subjet btag
  double           bst15_jet0_doublecsv;                                           // double btag                            
  double           bst15_jet0_rho, bst15_jet0_phil;                                // msd and pt dependent variables
  double           bst15_jet0_CHF, bst15_jet0_NHF, bst15_jet0_NEMF;                // boosted jet variables
  float            bst15_mt;                                                       // bst jet mT

  const float ToptagSF     = 1.1318;                                               // ToptagSF
  const float TopmistagSF  = 1.1639;                                               // TopmistagSF 
  const float btagSF       = 0.9851;                                               // btagSF
  const float bmistagSF    = 0.8853;                                               // bmistagSF

  const float CSVL = 0.460;                                                        // CSVL - WPs for 76x
  const float CSVM = 0.800;                                                        // CSVM
  const float CSVT = 0.935;                                                        // CSVT

  const float CSVbL = 0.3;                                                         // CSVbL - WPs for Doubleb
  const float CSVbM = 0.6;                                                         // CSVbM
  const float CSVbT = 0.9;                                                         // CSVbT 

  float doublebw_L0=1;
  float doublebw_L1=1;

  std::vector<float> doubleb_ptbin_eff, SF;
  std::vector<float> ptbinlow, ptbinhigh;

  float mcTag = 1.;
  float mcNoTag = 0.;
  float dataTag = 1.;
  float dataNoTag = 0.;

protected:

  const unsigned int kMET  = 2;
  const unsigned int kSingleElectron27 = 4;
  const unsigned int kSingleElectron23 = 8;
  const unsigned int kSinglePhoton  = 16;
  const unsigned int kBOOSTED15PUPPI = 2;
  const unsigned int kRESOLVEDPUPPI = 4;
  
  const float RHO_CUT = 0.72;

};
#endif
