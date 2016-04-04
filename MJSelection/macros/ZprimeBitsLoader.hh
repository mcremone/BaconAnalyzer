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
  MonoXBitsLoader(TTree *iTree=0,TString jet="15",TString algo="PUPPI",TString syst="CENT", string preselection="");		
  ~MonoXBitsLoader();
  bool selectJetAlgoAndSize(string selection, TString algo);
  bool passPreSelection(string preselection);
  bool passBoostedPreselection(string preselection);
  bool passBoostedSelection(string preselection);
  bool passSelection(string preselection, string selection, string subsample, string combo);
  double getWgt(bool isData, TString algo, double LUMI);
  float fjet_mass(string selection);
  float nsubjet(string selection);
  float btag(string selection);
  
  //
  // variables to read in bacon bits
  //
  int metfilter;                                                                   // MET filter bits          
  unsigned int runNum, lumiSec, evtNum;                                            // event ID
  unsigned int triggerBits, selectBits;                                            // trigger and jet type bits
  double triggerEff;                                                               // trigger efficiency
  float evtWeight, puWeight;                                                       // pu and evt weight
  unsigned int npu, npv;                                                           // PU, PV multiplicity
  int njets, nfjets;                                                               // jet multiplicity 
  float scale1fb;                                                                  // cross section scale factor per 1/fb

  //
  // Jets with pT-ordering:
  //
  double           bst_jet0_pt,bst_jet0_eta,bst_jet0_phi,bst_jet0_mass;            // leading boosted jet
  double           bst_jet0_msd, bst_jet0_rho, bst_jet0_phil;                      // msd and msd/pt dependent variables
  double           bst_jet0_tau32, bst_jet0_tau21;                                 // boosted tagger variables                                                                                            
  double           bst_jet0_maxsubcsv, bst_jet0_minsubcsv;                         // subjet btag                            
  double           bst_jet0_CHF, bst_jet0_NHF, bst_jet0_NEMF;                      // boosted jet variables
  float            bst_mt;                                                         // mT

protected:

  const unsigned int kBOOSTED8 = 2;
};
#endif
