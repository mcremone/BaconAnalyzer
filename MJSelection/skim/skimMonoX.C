//================================================================================================
//
//
//
//________________________________________________________________________________________________

//#if !defined(__CINT__) || defined(__MAKECINT__)
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

#include "../macros/CPlot.hh"                   // helper class for plots
#include "../macros/KStyle.hh"                  // style settings for drawing
#include "../macros/CSample.hh"                 // helper class to manage samples
#include "../macros/MonoXBitsLoader.hh"         // helper to load monoxbits
//#endif

using namespace std;

//Object Processors                                                                                                                                                                                      
MonoXBitsLoader       *fBits      = 0;

//=== MAIN MACRO =================================================================================================

void skimMonoX(const string preselection, const string selection, const string subsample, const string combo, TString algo, TString syst, TString bst15jetID = "jetT", TString bst8jetID = "jetT")
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  bool doBlind = false;
  //  if(subsample.compare("SR")==0)  doBlind = true;

  const string outfilename("monoxntuples/"+preselection+"-"+selection+"-"+subsample+"-"+combo+"-"+algo+"-"+syst+".root");

  //
  // samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;

  samplev.push_back(new CSample("data",0,0));
  if (preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0)  samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/MET.root");
  if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/SingleElectron.root");
  if (preselection.compare("Pho")==0)  samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/SinglePhoton.root");
  samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/QCD.root");
  if (preselection.compare("Pho")!=0) {
      samplev.push_back(new CSample("SingleTop",kRed - 9,kRed - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/T.root");
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/TZ.root");
      samplev.push_back(new CSample("ttbar",kOrange - 4,kOrange - 4));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/TT.root");
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/TTZ.root");
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/TTG.root");
      samplev.push_back(new CSample("WW",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/WW.root");
      samplev.push_back(new CSample("WZ",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/WZ.root");
      samplev.push_back(new CSample("ZZ",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZZ.root");
      samplev.push_back(new CSample("Wjets",kGreen - 10,kGreen - 10));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/WHF.root");
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/WLF.root");
      samplev.push_back(new CSample("ZnunuLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZHF.root");
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZLF.root");
      samplev.push_back(new CSample("ZllLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/DYHF.root");
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/DYLF.root");
      if(selection.find("MonoHbb")!=std::string::npos){
	samplev.push_back(new CSample("ZH", kRed - 9, kRed - 9));
	samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZH_amcatnlo.root");
      }
  }
  if (preselection.compare("Pho")==0){
      samplev.push_back(new CSample("Photon", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/GHF.root");
      samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/GLF.root");
  }
  if (subsample.compare("SR")==0 && selection.compare("BstMonoTop")==0){
    samplev.push_back(new CSample("Mres-1100_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S1_Mres_1100_Mchi_100_13TeV_madgraph_pythia8_mc.root");
    samplev.push_back(new CSample("Mres-1300_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S1_Mres_1300_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mres-1500_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S1_Mres_1500_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mres-1700_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S1_Mres_1700_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mres-1900_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S1_Mres_1900_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mres-2100_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S1_Mres_2100_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mres-900_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S1_Mres_900_Mchi_100_13TeV_madgraph_pythia8_mc.root");
    samplev.push_back(new CSample("Mchi-1100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S4_Mchi_1100_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mchi-1300", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S4_Mchi_1300_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mchi-1500", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S4_Mchi_1500_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mchi-300", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S4_Mchi_300_13TeV_madgraph_pythia8_mc.root");
    samplev.push_back(new CSample("Mchi-500", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S4_Mchi_500_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mchi-700", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S4_Mchi_700_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("Mchi-900", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/Monotop_S4_Mchi_900_13TeV_madgraph_pythia8_2_mc.root");
    samplev.push_back(new CSample("tHq", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/THQ.root");
  }
  if (subsample.find("SR")!=std::string::npos && selection.find("MonoHbb")!=std::string::npos){
    samplev.push_back(new CSample("MZ-1000_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1000_MA0_300_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1000_MA0-400", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1000_MA0_400_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1000_MA0-500", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1000_MA0_500_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1000_MA0-600", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1000_MA0_600_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1000_MA0-800", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1000_MA0_800_13TeV_madgraph_mc.root");
    samplev.push_back(new CSample("MZ-1200_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1200_MA0_300_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1200_MA0-500", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1200_MA0_500_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1200_MA0-600", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1200_MA0_600_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1200_MA0-700", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1200_MA0_700_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1200_MA0-800", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1200_MA0_800_13TeV_madgraph_mc.root");
    samplev.push_back(new CSample("MZ-1400_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1400_MA0_300_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1400_MA0-400", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1400_MA0_400_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1400_MA0-500", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1400_MA0_500_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1400_MA0-600", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1400_MA0_600_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1400_MA0-700", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1400_MA0_700_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1400_MA0-800", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1400_MA0_800_13TeV_madgraph_mc.root");
    samplev.push_back(new CSample("MZ-1700_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1700_MA0_300_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1700_MA0-400", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1700_MA0_400_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1700_MA0-500", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1700_MA0_500_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1700_MA0-600", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1700_MA0_600_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1700_MA0-700", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1700_MA0_700_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-1700_MA0-800", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_1700_MA0_800_13TeV_madgraph_mc.root");
    samplev.push_back(new CSample("MZ-2000_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2000_MA0_300_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-2000_MA0-400", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2000_MA0_400_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-2000_MA0-500", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2000_MA0_500_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2000_MA0-600", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2000_MA0_600_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2000_MA0-700", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2000_MA0_700_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2000_MA0-800", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2000_MA0_800_13TeV_madgraph_2_mc.root");
    samplev.push_back(new CSample("MZ-2500_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2500_MA0_300_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2500_MA0-400", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2500_MA0_400_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2500_MA0-500", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2500_MA0_500_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2500_MA0-600", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2500_MA0_600_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2500_MA0-700", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2500_MA0_700_13TeV_madgraph_2_mc.root");
    // samplev.push_back(new CSample("MZ-2500_MA0-800", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_2500_MA0_800_13TeV_madgraph_2_mc.root");
    samplev.push_back(new CSample("MZ-600_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_600_MA0_300_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-600_MA0-400", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_600_MA0_400_13TeV_madgraph_mc.root");
    samplev.push_back(new CSample("MZ-800_MA0-300", kBlue, kBlue));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_800_MA0_300_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-800_MA0-400", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_800_MA0_400_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-800_MA0-500", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_800_MA0_500_13TeV_madgraph_mc.root");
    // samplev.push_back(new CSample("MZ-800_MA0-600", kBlue, kBlue));
    // samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/monoxbits/ZprimeToA0hToA0chichihbb_2HDM_MZp_800_MA0_600_13TeV_madgraph_mc.root");
  }
  // integrated luminosity to scale MC
  const double LUMI = 2.32;
  
  // histograms for various corrections
  const string cmssw_base = getenv("CMSSW_BASE");
  
  //--------------------------------------------------------------------------------------------------------------
  // Main analysis code
  //==============================================================================================================

  TFile *outFile = new TFile(outfilename.c_str(),"RECREATE");

  //                                                                                                                                                                                       
  // Declare output TTrees                                                                                                                                                                 
  //                                                                                                                                                                                         

  float met_, metphi_, genVpt_, genVphi_, weight_, mt_, dR_;
  vector<TTree*> outtreesv;
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    string tname = samplev[isam]->label;
    if(subsample=="SR") tname = tname + string("_signal");
    if(subsample=="SR1") tname = tname + string("_signal1");
    if(subsample=="SR2") tname = tname + string("_signal2");
    if(subsample=="SR3") tname = tname + string("_signal3");
    if(subsample=="ZnunuHF") tname = tname + string("_znunuhf_control");
    if(subsample=="ZnunuLF") tname = tname + string("_znunulf_control");
    if(preselection=="Muo" && subsample=="TopCR") tname = tname + string("_single_muon_top_control");
    if(preselection=="Ele" && subsample=="TopCR") tname = tname + string("_single_electron_top_control");
    if(preselection=="Muo" && subsample=="WCR") tname = tname + string("_single_muon_w_control");
    if(preselection=="Ele" && subsample=="WCR") tname = tname + string("_single_electron_w_control");
    if(preselection=="Zmm" && subsample=="ZCR") tname = tname + string("_di_muon_control");
    if(preselection=="Zee" && subsample=="ZCR") tname = tname + string("_di_electron_control");
    if(preselection=="Pho" && subsample=="ZCR") tname = tname + string("_photon_control");
    if(syst=="BTAGUP") tname = tname + string("_btagUp");
    if(syst=="BTAGDO") tname = tname + string("_btagDown");
    if(syst=="MISTAGUP") tname = tname + string("_mistagUp");
    if(syst=="MISTAGDO") tname = tname + string("_mistagDown");
    if(syst=="SJBTAGUP") tname = tname + string("_sjbtagUp");
    if(syst=="SJBTAGDO") tname = tname + string("_sjbtagDown");
    if(syst=="SJMISTAGUP") tname = tname + string("_sjmistagUp");
    if(syst=="SJMISTAGDO") tname = tname + string("_sjmistagDown");
    if(syst=="DOUBLEBBTAGUP") tname = tname + string("_doublebtagUp");
    if(syst=="DOUBLEBBTAGDO") tname = tname + string("_doublebtagDown");
    if(syst=="DOUBLEBMISTAGUP") tname = tname + string("_doublebmistagUp");
    if(syst=="DOUBLEBMISTAGDO") tname = tname + string("_doublebmistagDown");
    if(syst=="GJETHFUP") tname = tname + string("_gjethfUp");
    if(syst=="GJETHFDO") tname = tname + string("_gjethfDown");
    if(syst=="WJETHFUP") tname = tname + string("_wjethfUp");
    if(syst=="WJETHFDO") tname = tname + string("_wjethfDown");
    if(syst=="ZJETHFUP") tname = tname + string("_zjethfUp");
    if(syst=="ZJETHFDO") tname = tname + string("_zjethfDown");
    outtreesv.push_back(new TTree(tname.c_str(), tname.c_str()));
    outtreesv.back()->Branch("met",      &met_,      "met/F");
    outtreesv.back()->Branch("metphi",   &metphi_,   "metphi/F");
    outtreesv.back()->Branch("genVpt",   &genVpt_,   "genVpt/F");
    outtreesv.back()->Branch("genVphi",  &genVphi_,  "genVphi/F");
    outtreesv.back()->Branch("weight",   &weight_,   "weight/F");
    outtreesv.back()->Branch("mt",       &mt_,       "mt/F");
    outtreesv.back()->Branch("dR",       &dR_,       "dR/F");
  }

  TFile *infile=0;
  TTree *intree=0;

  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    CSample *sample = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData   = (isam==0);
    bool isSignal = false;
    if(selection.compare("BstMonoTop")==0 && subsample.compare("SR")==0) isSignal  = (isam==samplev.size()-1 || isam==samplev.size()-2);
    if(((selection.compare("Bst15MonoHbb")==0) || (selection.compare("Bst8MonoHbb")==0) || (selection.compare("ResMonoHbb")==0) || (selection.compare("Bst8MonoHbbCMS")==0) || (selection.compare("ResMonoHbbCMS")==0))
       && subsample.find("SR")!=std::string::npos) isSignal  = (isam==samplev.size()-1 || isam==samplev.size()-2 || isam==samplev.size()-3 || isam==samplev.size()-4 || isam==samplev.size()-5 || isam==samplev.size()-6 || isam==samplev.size()-7 || isam==samplev.size()-8);
    
    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      intree = (TTree*)infile->Get("Events"); assert(intree);
      if(syst!="CENT" && syst!="BTAGUP" && syst!="BTAGDO" && syst!="MISTAGUP" && syst!="MISTAGDO" && syst!="SJBTAGUP" 
	 && syst!="SJBTAGDO" && syst!="SJMISTAGUP" && syst!="SJMISTAGDO" && syst!="DOUBLEBMISTAGUP" && syst!="DOUBLEBMISTAGDO") fBits     = new MonoXBitsLoader(intree,bst15jetID,bst8jetID,algo,"CENT",preselection,isData);
      else fBits   = new MonoXBitsLoader(intree,bst15jetID,bst8jetID,algo,syst,preselection,isData);

      double nevts=0; int noweight=0;

      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
        intree->GetEntry(ientry);
        if(!fBits->selectJetAlgoAndSize(selection,algo,bst15jetID,bst8jetID)) continue;
	// common selection
	if(fBits->metfilter!=0)                   continue;
	//preselection
	if(!fBits->passPreSelection(preselection)) continue;
	//selection
	float btagw=1;
	if(!fBits->passSelection(preselection,selection,subsample,combo,btagw,syst,isSignal)) continue;

	//	double wgt = fBits->getWgt(isData,algo,LUMI,btagw);
	double wgt = 1;
	if(!isData) {
          wgt *= LUMI*fBits->evtWeight*fBits->kfactor*btagw*fBits->eleSF1*fBits->eleSF2*fBits->muoSF1*fBits->muoSF2;
          if(preselection.compare("Had")!=0 && preselection.compare("Muo")!=0 && preselection.compare("Zmm")!=0) wgt *= fBits->triggerEff;
	  if(selection.compare("BstMonoTop")==0){
	    if(sample->label=="ttbar" && fBits->topSize15<0.8 && fBits->isHadronicTop15==1 &&fBits->topMatching15 <1.4 && fBits->topMatching15 > 0 && fBits->topSize15 > 0){
	      wgt *= fBits->ToptagSF;
	    }
	  }
	  if(subsample.find("SR")!=std::string::npos){
            if(isam==samplev.size()-8) wgt *= 0.01;  
            else if(isam==samplev.size()-7) wgt *= 0.01;
            else if(isam==samplev.size()-6) wgt *= 0.01;
            else if(isam==samplev.size()-5) wgt *= 0.01;
            else if(isam==samplev.size()-4) wgt *= 0.01;
            else if(isam==samplev.size()-3) wgt *= 0.01;
            else if(isam==samplev.size()-2) wgt *= 0.01;
            else if(isam==samplev.size()-1) wgt *= 0.01;
	    else wgt *=fBits->scale1fb;
          }
	  else wgt *=fBits->scale1fb;
	  // if(sample->label!="ttbar" || ifile!=0 || fBits->isHadronicTop15==0 || fBits->topSize15>=0.8 || fBits->topSize15<0 || fBits->topMatching15>=1.4 || fBits->topMatching15<0){
          //   wgt *= fBits->TopmistagSF;
          // }
	  // if(sample->label=="Wjets" || sample->label=="Photon" || sample->label=="ZnunuLO" || sample->label=="ZllLO" ){
	  //   if(subsample=="SR" || subsample=="TopCR") {
	  //     if(ifile==0) {
	  // 	wgt *= fBits->btagSF;
	  //     }
	  //     if(ifile==1) {
	  // 	wgt *= fBits->bmistagSF;
	  //     }
	  //   }
	  // } 
	  
	  if(sample->label=="Photon") {
	    if(ifile==0) { 
	      if(syst=="GJETHFUP") wgt *= 1.4;
              if(syst=="GJETHFDO") wgt *= 0.6;
	    } 
	    if(ifile==1) {
              if(syst=="GJETHFUP") wgt *= 0.88;
              if(syst=="GJETHFDO") wgt *= 1.12;
            }
	  }
          if(sample->label=="Wjets") {
            if(ifile==0) {
              if(syst=="WJETHFUP") wgt *= 1.22;
              if(syst=="WJETHFDO") wgt *= 0.78;
            }
            if(ifile==1) {
              if(syst=="WJETHFUP") wgt *= 0.925;
              if(syst=="WJETHFDO") wgt *= 1.075;
            }
          }	  
          if(sample->label=="ZllLO" || sample->label=="ZnunuLO") {
            if(ifile==0) {
              if(syst=="ZJETHFUP") wgt *= 1.15;
              if(syst=="ZJETHFDO") wgt *= 0.85;
            }
            if(ifile==1) {
              if(syst=="ZJETHFUP") wgt *= 0.96;
              if(syst=="ZJETHFDO") wgt *= 1.04;
            }
          }	  
	}
        nevts += wgt;
	noweight++;

        //                                                                                                                                                                                  
        // Fill tree only if requested category is passed and, if                                                                                                                          
        // in combination, no preceeding category has passed                                                                                                                               
        //
        met_     = fBits->getMET(preselection).Pt();
        metphi_  = fBits->getMET(preselection).Phi();
        weight_  = wgt;
	mt_      = fBits->transverse_mass(selection);
        dR_      = fBits->getdRsj0dR(selection);
	genVpt_  = fBits->genVpt;
	genVphi_ = fBits->genVphi;

	if(!isData || !doBlind) { outtreesv[isam]->Fill(); }
      }

      if(isData && doBlind) {
        cout << endl;
      } else {
	cout << nevts << " " << noweight  <<  endl;
      }
      delete infile;
      infile=0;
      intree=0;
    }
  }

  //--------------------------------------------------------------------------------------------------------------
  // Output
  //==============================================================================================================
   
  cout << "*" << endl;
  cout << "* SUMMARY" << endl;
  cout << "*--------------------------------------------------" << endl;
  cout << endl;

  outFile->Write();
  outFile->Close();

  cout << endl;
  cout << " <> Output saved in " << outfilename << endl;
  cout << endl; 
}
