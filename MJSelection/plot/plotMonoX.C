//================================================================================================
//
// 
//
//________________________________________________________________________________________________

//#If !defined(__CINT__) || defined(__MAKECINT__)
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

#include "../macros/CPlot.hh"              // helper class for plots
#include "../macros/KStyle.hh"             // style settings for drawing
#include "../macros/CSample.hh"            // helper class to manage samples
#include "../macros/MonoXBitsLoader.hh"    // helper to load monoxbits
//#endif

using namespace std;

//Object Processors                                                                                                                                                                                      
MonoXBitsLoader       *fBits      = 0;

//=== FUNCTION DECLARATIONS ======================================================================================

// make "standard" plot
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy=false, const double legdx=0, const double legdy=0,
              const double ymin=-1, const double ymax=-1, const string selection="", const string subsample="");
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind, const string selection);
float CalcSig(TH1D*sig, TH1D*bkg);

//=== MAIN MACRO =================================================================================================

void plotMonoX(const string preselection, const string selection, const string subsample, const string combo = "ONLY", TString algo= "PUPPI", TString syst = "CENT")
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  const bool doBlind = false;
  bool isBacon = false;
  //bool isBacon = true;

  // Create output directory 
  const string outputDir("monoxplots/"+preselection+"_"+selection+"_"+subsample+"_"+combo+"_"+algo);
  gSystem->mkdir(outputDir.c_str(), true);
  CPlot::sOutDir = outputDir;
  
  //
  // Samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;
  if(isBacon){
    samplev.push_back(new CSample("data",0,0));
    if (preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0)  samplev.back()->fnamev.push_back("/tmp/cmantill/MET.root");
    if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("/tmp/cmantill/SingleElectron.root");
    if (preselection.compare("Pho")==0)  samplev.back()->fnamev.push_back("/tmp/cmantill/SinglePhoton.root");
    if (preselection.compare("Pho")!=0) {
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/tmp/cmantill/QCD.root");
      samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/SingleTop.root");
      samplev.push_back(new CSample("t#bar{t}",kOrange - 4,kOrange - 4));
      samplev.back()->fnamev.push_back("/tmp/cmantill/TTbar_Powheg.root");
      samplev.push_back(new CSample("Diboson",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Diboson.root");
      samplev.push_back(new CSample("W+jets",kGreen - 10,kGreen - 10));
      samplev.back()->fnamev.push_back("/tmp/cmantill/WJets.root");
      samplev.push_back(new CSample("Z+jets", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/ZJets.root");   
      samplev.back()->fnamev.push_back("/tmp/cmantill/ZtoNuNu.root");
    }
    if (preselection.compare("Pho")==0){
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/tmp/cmantill/SinglePhoton.root");
      samplev.push_back(new CSample("#gamma+jets", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/GJets.root");
    }
    if (subsample.compare("SR")==0 && (selection.compare("Bst15MonoTop")==0  || selection.compare("Bst15SemMonoTop")==0)){   
      samplev.push_back(new CSample("M_{med}=300 (FCNC)", kBlue, kBlue));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed300.root");
      samplev.push_back(new CSample("M_{med}=700 (FCNC)", kGreen, kGreen));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed700.root");
      samplev.push_back(new CSample("M_{med}=1100 (FCNC)", kTeal-1, kTeal-1));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed1100.root");
      samplev.push_back(new CSample("M_{med}=1300 (FCNC)", kOrange+8, kOrange+8));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed1300.root");
      samplev.push_back(new CSample("M_{med}=900 (res)", kViolet, kViolet));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed900.root");
      samplev.push_back(new CSample("M_{med}=1100 (res)", kGray, kGray));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed1100.root");
      samplev.push_back(new CSample("M_{med}=1300 (res)", kRed-9, kRed-9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed1300.root");
      samplev.push_back(new CSample("M_{med}=1900 (res) ", kRed, kRed));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed1900.root");
    }
  }
  else{
    samplev.push_back(new CSample("data",0,0));
    if (preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0)  samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/MET.root");
    if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/SingleElectron.root");
    if (preselection.compare("Pho")==0) samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/SinglePhoton.root");
    if (preselection.compare("Pho")!=0) {
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/QCD.root");
      samplev.push_back(new CSample("SingleTop",kRed - 9,kRed - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/SingleTop.root");
      samplev.push_back(new CSample("ttbar",kOrange - 4,kOrange - 4));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/TTbar_Powheg.root");
      samplev.push_back(new CSample("Diboson",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/Diboson.root");
      samplev.push_back(new CSample("Wjets",kGreen - 10,kGreen - 10));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/WJets.root");
      samplev.push_back(new CSample("ZnunuLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/ZtoNuNu.root");
      samplev.push_back(new CSample("ZllLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/ZJets.root");
    }
    if (preselection.compare("Pho")==0){
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/SinglePhoton.root");
      samplev.push_back(new CSample("Photon", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/GJets.root");
    }
    if (subsample.compare("SR")==0 && (selection.compare("Bst15MonoTop")==0  || selection.compare("Bst15SemMonoTop")==0)){
      samplev.push_back(new CSample("M_{med}=300 (FCNC)", kBlue, kBlue));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed300.root");
      samplev.push_back(new CSample("M_{med}=700 (FCNC)", kGreen, kGreen));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed700.root");
      samplev.push_back(new CSample("M_{med}=1100 (FCNC)", kTeal-1, kTeal-1));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed1100.root");
      samplev.push_back(new CSample("M_{med}=1300 (FCNC)", kOrange+8, kOrange+8));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_fcnc_mMed1300.root");
      samplev.push_back(new CSample("M_{med}=900 (res)", kViolet, kViolet));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed900.root");
      samplev.push_back(new CSample("M_{med}=1100 (res)", kGray, kGray));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed1100.root");
      samplev.push_back(new CSample("M_{med}=1300 (res)", kRed-9, kRed-9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed1300.root");
      samplev.push_back(new CSample("M_{med}=1900 (res) ", kRed, kRed));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v9/monotop_res_mMed1900.root");
    }
  }
  
  // integrated luminosity to scale MC
  const double LUMI = 12.9;
  
  // histograms for various corrections
  const string cmssw_base = getenv("CMSSW_BASE");

  //--------------------------------------------------------------------------------------------------------------
  // Main analysis code
  //==============================================================================================================
  
  //
  // Declare histograms
  //
  char hname[100];
  vector<TH1D*> hMETv, hMETLogv;
  vector<TH1D*> hTransverseMassv, hTransverseMassLv;
  vector<TH1D*> hFatJetMassv, hFatJetMassLv, hFatJetPtv, hFatJetTau32v, hdRv, hdRptv;
  vector<TH1D*> hvJetMassv, hvJetMassLv, hvJetPtv;
  vector<TH1D*> hFatJetTau21v, hFatJetTau21DDTv, hFatJetTau21DDTLv;
  vector<TH1D*> hBtagv, hMinSubJetcsvv;
  vector<TH1D*> hMinDPhiJetsMetv, hMinDPhiJetsMetLv, hNFJetsv, hNJetsv, hNBJetsv;
  vector<TH1D*> hJet1CHFv, hJet1NHFv, hJet1NEMFv;
  vector<TH1D*> hJet1Etav, hJet2Etav, hJet3Etav, hJet4Etav;
  vector<double> neventsv;
 
  const Int_t NBINS = 7, NBINSMT = 3; // MonoTop Binning
  Double_t edges[NBINS+1] = {250,280,310,350,400,450,600,1000};
  Double_t edgesMT[NBINSMT + 1] = {350,550,750,3000};
  
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    sprintf(hname,"hMET_%i",isam);            hMETv.push_back(new TH1D(hname,"",NBINS,edges));                hMETv[isam]->Sumw2();
    sprintf(hname,"hMETLog_%i",isam);         hMETLogv.push_back(new TH1D(hname,"",NBINS,edges));             hMETLogv[isam]->Sumw2();
    sprintf(hname,"hTransverseMass_%i",isam); hTransverseMassv.push_back(new TH1D(hname,"",NBINSMT,edgesMT)); hTransverseMassv[isam]->Sumw2();
    sprintf(hname,"hTransverseMassL_%i",isam);hTransverseMassLv.push_back(new TH1D(hname,"",NBINSMT,edgesMT));hTransverseMassLv[isam]->Sumw2();
    sprintf(hname,"hFatJetMass_%i",isam);     hFatJetMassv.push_back(new TH1D(hname,"",20,0,300));            hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetMassL_%i",isam);    hFatJetMassLv.push_back(new TH1D(hname,"",20,0,300));           hFatJetMassLv[isam]->Sumw2();
    sprintf(hname,"hFatJetPt_%i",isam);       hFatJetPtv.push_back(new TH1D(hname,"",20,250,1000));           hFatJetPtv[isam]->Sumw2();
    sprintf(hname,"hFatJetTau32_%i",isam);    hFatJetTau32v.push_back(new TH1D(hname,"",15,0.2,1));           hFatJetTau32v[isam]->Sumw2();
    sprintf(hname,"hdR_%i",isam);             hdRv.push_back(new TH1D(hname,"",10,0,1.5));                    hdRv[isam]->Sumw2();
    sprintf(hname,"hdRpt_%i",isam);           hdRptv.push_back(new TH1D(hname,"",20,0,40));                   hdRptv[isam]->Sumw2();
    sprintf(hname,"hvJetMass_%i",isam);       hvJetMassv.push_back(new TH1D(hname,"",20,0,300));              hvJetMassv[isam]->Sumw2();
    sprintf(hname,"hvJetMassL_%i",isam);      hvJetMassLv.push_back(new TH1D(hname,"",20,0,300));             hvJetMassLv[isam]->Sumw2();
    sprintf(hname,"hvJetPt_%i",isam);         hvJetPtv.push_back(new TH1D(hname,"",20,250,1000));             hvJetPtv[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21_%i",isam);    hFatJetTau21v.push_back(new TH1D(hname,"",25,0,1));             hFatJetTau21v[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21DDT_%i",isam); hFatJetTau21DDTv.push_back(new TH1D(hname,"",25,0,1));          hFatJetTau21DDTv[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21DDTL_%i",isam);hFatJetTau21DDTLv.push_back(new TH1D(hname,"",25,0,1));         hFatJetTau21DDTLv[isam]->Sumw2();
    sprintf(hname,"hBtag_%i",isam);           hBtagv.push_back(new TH1D(hname,"",15,0.1,1.));                 hBtagv[isam]->Sumw2();
    sprintf(hname,"hMinSubJetcsv_%i",isam);   hMinSubJetcsvv.push_back(new TH1D(hname,"",15,0.1,1.));         hMinSubJetcsvv[isam]->Sumw2();
    sprintf(hname,"hMinDPhiJetsMet_%i",isam); hMinDPhiJetsMetv.push_back(new TH1D(hname,"",20,0,3.14));       hMinDPhiJetsMetv[isam]->Sumw2();
    sprintf(hname,"hMinDPhiJetsMetL_%i",isam);hMinDPhiJetsMetLv.push_back(new TH1D(hname,"",20,0,3.14));      hMinDPhiJetsMetLv[isam]->Sumw2();
    sprintf(hname,"hNFJets_%i",isam);         hNFJetsv.push_back(new TH1D(hname,"",10,0,10));                 hNFJetsv[isam]->Sumw2();
    sprintf(hname,"hNJets_%i",isam);          hNJetsv.push_back(new TH1D(hname,"",10,0,10));                  hNJetsv[isam]->Sumw2();
    sprintf(hname,"hNBJets_%i",isam);         hNBJetsv.push_back(new TH1D(hname,"",10,0,10));                 hNBJetsv[isam]->Sumw2();
    sprintf(hname,"hJet1CHF_%i",isam);        hJet1CHFv.push_back(new TH1D(hname,"",30,0,1));                 hJet1CHFv[isam]->Sumw2();
    sprintf(hname,"hJet1NHF_%i",isam);        hJet1NHFv.push_back(new TH1D(hname,"",30,0,1));                 hJet1NHFv[isam]->Sumw2();
    sprintf(hname,"hJet1NEMF_%i",isam);       hJet1NEMFv.push_back(new TH1D(hname,"",30,0,1));                hJet1NEMFv[isam]->Sumw2();
    sprintf(hname,"hJet1Eta_%i",isam);        hJet1Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));            hJet1Etav[isam]->Sumw2();
    sprintf(hname,"hJet2Eta_%i",isam);        hJet2Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));            hJet2Etav[isam]->Sumw2();
    sprintf(hname,"hJet3Eta_%i",isam);        hJet3Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));            hJet3Etav[isam]->Sumw2();
    sprintf(hname,"hJet4Eta_%i",isam);        hJet4Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));            hJet4Etav[isam]->Sumw2();
    neventsv.push_back(0);
  }
  
  TH1D *hMETMC             = (TH1D*)hMETv[0]            ->Clone("hMETMC");
  TH1D *hMETLogMC          = (TH1D*)hMETLogv[0]         ->Clone("hMETLogMC");
  TH1D *hTransverseMassMC  = (TH1D*)hTransverseMassv[0 ]->Clone("hTransverseMassMC");
  TH1D *hTransverseMassLMC = (TH1D*)hTransverseMassLv[0]->Clone("hTransverseMassLMC");
  TH1D *hFatJetMassMC      = (TH1D*)hFatJetMassv[0]     ->Clone("hFatJetMassMC");
  TH1D *hFatJetMassLMC     = (TH1D*)hFatJetMassLv[0]    ->Clone("hFatJetMassLMC");
  TH1D *hFatJetPtMC        = (TH1D*)hFatJetPtv[0]       ->Clone("hFatJetPtMC");
  TH1D *hvJetMassMC        = (TH1D*)hvJetMassv[0]       ->Clone("hvJetMassMC");
  TH1D *hvJetMassLMC       = (TH1D*)hvJetMassLv[0]      ->Clone("hvJetMassLMC");
  TH1D *hvJetPtMC          = (TH1D*)hvJetPtv[0]         ->Clone("hvJetPtMC");
  TH1D *hFatJetTau32MC     = (TH1D*)hFatJetTau32v[0]    ->Clone("hFatJetTau32MC");
  TH1D *hdRMC              = (TH1D*)hdRv[0]             ->Clone("hdRMC");
  TH1D *hdRptMC            = (TH1D*)hdRptv[0]           ->Clone("hdRptMC");
  TH1D *hFatJetTau21MC     = (TH1D*)hFatJetTau21v[0]    ->Clone("hFatJetTau21MC");
  TH1D *hFatJetTau21DDTMC  = (TH1D*)hFatJetTau21DDTv[0] ->Clone("hFatJetTau21DDTMC");
  TH1D *hFatJetTau21DDTLMC = (TH1D*)hFatJetTau21DDTLv[0]->Clone("hFatJetTau21DDTLMC");
  TH1D *hBtagMC            = (TH1D*)hBtagv[0]           ->Clone("hBtagMC");
  TH1D *hMinSubJetcsvMC    = (TH1D*)hMinSubJetcsvv[0]   ->Clone("hMinSubJetcsvMC");
  TH1D *hMinDPhiJetsMetMC  = (TH1D*)hMinDPhiJetsMetv[0] ->Clone("hMinDPhiJetsMetMC");
  TH1D *hMinDPhiJetsMetLMC = (TH1D*)hMinDPhiJetsMetLv[0]->Clone("hMinDPhiJetsMetLMC");
  TH1D *hNFJetsMC          = (TH1D*)hNJetsv[0]          ->Clone("hNFJetsMC");
  TH1D *hNJetsMC           = (TH1D*)hNJetsv[0]          ->Clone("hNJetsMC");
  TH1D *hNBJetsMC          = (TH1D*)hNBJetsv[0]         ->Clone("hNBJetsMC");
  TH1D *hJet1CHFMC         = (TH1D*)hJet1CHFv[0]        ->Clone("hJet1CHFMC");
  TH1D *hJet1NHFMC         = (TH1D*)hJet1NHFv[0]        ->Clone("hJet1NHFMC");
  TH1D *hJet1NEMFMC        = (TH1D*)hJet1NEMFv[0]       ->Clone("hJet1NEMFMC");
  TH1D *hJet1EtaMC         = (TH1D*)hJet1Etav[0]        ->Clone("hJet1EtaMC");
  TH1D *hJet2EtaMC         = (TH1D*)hJet2Etav[0]        ->Clone("hJet2EtaMC");
  TH1D *hJet3EtaMC         = (TH1D*)hJet3Etav[0]        ->Clone("hJet3EtaMC");
  TH1D *hJet4EtaMC         = (TH1D*)hJet4Etav[0]        ->Clone("hJet4EtaMC");
  TH1D *hMETSig1           = (TH1D*)hMETv[0]            ->Clone("hMETSig1");
  TH1D *hMETSig2           = (TH1D*)hMETv[0]            ->Clone("hMETSig2");
  TH1D *hMETSig3           = (TH1D*)hMETv[0]            ->Clone("hMETSig3");
  TH1D *hMETSig4           = (TH1D*)hMETv[0]            ->Clone("hMETSig4");
  TH1D *hMETSig5           = (TH1D*)hMETv[0]            ->Clone("hMETSig5");
  TH1D *hMETSig6           = (TH1D*)hMETv[0]            ->Clone("hMETSig6");
  TH1D *hMETSig7           = (TH1D*)hMETv[0]            ->Clone("hMETSig7");
  TH1D *hMETSig8           = (TH1D*)hMETv[0]            ->Clone("hMETSig8");
  double neventsMC = 0;
  
  TFile *infile=0;
  TTree *intree=0;
  
  // Loop over samples
  
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    CSample *sample = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData = false;
    if(sample->label.compare("data")==0) isData=true;
    bool isSignal = false;
    if((selection.compare("Bst15MonoTop")==0 || selection.compare("Bst15SemMonoTop")==0) && subsample.compare("SR")==0){
      if (isam==samplev.size()-1 ||
          isam==samplev.size()-2 ||
          isam==samplev.size()-3 ||
          isam==samplev.size()-4 ||
          isam==samplev.size()-5 ||
          isam==samplev.size()-6 ||
          isam==samplev.size()-7 ||
          isam==samplev.size()-8){
        isSignal = true;
        isBacon = false;
      }
    }
    if(subsample.find("SR")!=std::string::npos && (isam==samplev.size()-1 || isam==samplev.size()-2 || isam==samplev.size()-3 || isam==samplev.size()-4 || isam==samplev.size()-5 || isam==samplev.size()-6 || isam==samplev.size()-7 || isam==samplev.size()-8)) isSignal = true;
    bool isSignal1 = (isam==samplev.size()-1);
    bool isSignal2 = (isam==samplev.size()-2);
    bool isSignal3 = (isam==samplev.size()-3);
    bool isSignal4 = (isam==samplev.size()-4);
    bool isSignal5 = (isam==samplev.size()-5);
    bool isSignal6 = (isam==samplev.size()-6);
    bool isSignal7 = (isam==samplev.size()-7);
    bool isSignal8 = (isam==samplev.size()-8);
 
    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      if(isBacon){ intree = (TTree*)infile->Get("Events"); assert(intree);}
      else{ intree = (TTree*)infile->Get("events"); assert(intree);}
      fBits     = new MonoXBitsLoader(intree,algo,syst,preselection,isData,isBacon);

      double nevts=0;
      int noweight=0;

      //std::cout << intree->GetEntries() << std::endl;
      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
        intree->GetEntry(ientry);
        if(isBacon){
          if(!fBits->selectJetAlgoAndSize(selection,algo)) continue;
          if(isData && ((fBits->metfilter & 1) || (fBits->metfilter & 2) || (fBits->metfilter & 8) || (fBits->metfilter & 32) ||
                        (fBits->metfilter & 1024) || (fBits->metfilter & 2048) || (fBits->metfilter & 32768))) continue;
        }
        else{
          if(isData && (fBits->metfilter==0 || fBits->newmetfilter==0))                   continue;
	}
	//preselection
        if(!fBits->passPreSelection(preselection,isData,isBacon)) continue;
        //selection                                                                                                                                                                     
	float btagw=1;
        if(!fBits->passSelection(preselection,selection,subsample,combo,btagw,syst,isSignal,isBacon)) continue;
        double wgt = 1;
	if(!isData) {
          if(isBacon){
            if(preselection.compare("Pho")==0 && sample->label.compare("QCD")==0) wgt *=fBits->getPhotonPurity();
	    else{
	      wgt *= LUMI*fBits->evtWeight*fBits->puWeight*fBits->kfactor*btagw*fBits->eleSF1*fBits->eleSF2*fBits->muoSF1*fBits->muoSF2*fBits->eleSFTrack*fBits->muoSFTrack;
	      if(preselection.compare("Had")!=0 && preselection.compare("Muo")!=0 && preselection.compare("Zmm")!=0) wgt *= fBits->sf_metTrig;
              if(subsample.compare("TopCR")==0 || subsample.compare("WCR")==0 || subsample.compare("ZCR")==0) wgt *= fBits->sf_lepTrack;
              if(preselection.compare("Pho")==0) wgt *= fBits->sf_phoTrig*0.93;
              if(preselection.compare("Ele")==0) wgt *= fBits->sf_eleTrig;
              if(preselection.compare("Zee")==0) wgt *= fBits->sf_eleTrig*fBits->sf_phoTrig;

	      if(selection.compare("Bst15MonoTop")==0 || selection.compare("Bst15SemMonoTop")==0){
		if(sample->label=="ttbar" && fBits->topSize15<0.8 && fBits->isHadronicTop15==1 &&fBits->topMatching15 <1.4 && fBits->topMatching15 > 0 && fBits->topSize15 > 0){
		  wgt *= 1.007;
		}
		else if(sample->label=="ttbar" && (fBits->topSize15>=0.8 || fBits->isHadronicTop15!=1 || fBits->topMatching15 >1.4 || fBits->topMatching15 <= 0 || fBits->topSize15 <= 0)){
		  wgt *= 1.02;
		}
		else{
		  wgt *= 1.02;
		}
	      }
	      wgt *=fBits->scale1fb;
	    }
          }
          else{
	    if(preselection.compare("Pho")==0 && sample->label.compare("QCD")==0){
	      if(fBits->metfilter==0 || fBits->newmetfilter==0) continue;
	      wgt *=fBits->photonPurity;
	    }
            else{
              wgt *= LUMI*fBits->normalizedWeight*1000*fBits->puWeight*fBits->sf_ewkZ*fBits->sf_qcdZ*fBits->sf_ewkW*fBits->sf_qcdW*fBits->sf_ewkA*fBits->sf_qcdA*fBits->sf_tt*fBits->sf_lep*btagw;
              if(preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0) wgt *= fBits->sf_metTrig;
	      if(subsample.compare("TopCR")==0 || subsample.compare("WCR")==0 || subsample.compare("ZCR")==0) wgt *= fBits->sf_lepTrack;
              if(preselection.compare("Pho")==0) wgt *= fBits->sf_phoTrig*0.93;
              if(preselection.compare("Ele")==0) wgt *= fBits->sf_eleTrig;
              if(preselection.compare("Zee")==0) wgt *= fBits->sf_eleTrig*fBits->sf_phoTrig;

              if(selection.compare("Bst15MonoTop")==0 || selection.compare("Bst15SemMonoTop")==0){
                if(sample->label=="ttbar" && fBits->bst15_jet1_isMatched==1){
                  wgt *= 1.007;
                }
                else if(sample->label=="ttbar" && fBits->bst15_jet1_isMatched!=1){
                  wgt *= 1.02;
                }
                else{
                  wgt *= 1.02;
                }
              }
            }
          }
	  
	}
	
	nevts += wgt;
	noweight++;

        neventsv[isam]+=wgt;
	
        hMETv[isam]            ->Fill(fBits->getMET(preselection,isBacon).Pt(),       wgt);
        hMETLogv[isam]         ->Fill(fBits->getMET(preselection,isBacon).Pt(),       wgt);
	hFatJetMassv[isam]     ->Fill(fBits->fjet_mass(selection,isBacon),            wgt);
	hFatJetMassLv[isam]    ->Fill(fBits->fjet_mass(selection,isBacon),            wgt);
	hFatJetPtv[isam]       ->Fill(fBits->fjet_pt(selection,isBacon),              wgt);
	hvJetMassv[isam]       ->Fill(fBits->getTopRes().M(),                         wgt);
        hvJetMassLv[isam]      ->Fill(fBits->getTopRes().M(),                         wgt);
        hvJetPtv[isam]         ->Fill(fBits->getTopRes().Pt(),                        wgt);
	hTransverseMassv[isam] ->Fill(fBits->transverse_mass(selection),              wgt);
        hTransverseMassLv[isam]->Fill(fBits->transverse_mass(selection),              wgt);
        hFatJetTau21v[isam]    ->Fill(fBits->tau21(selection),                        wgt);
        hFatJetTau21DDTv[isam] ->Fill(fBits->tau21DDT(selection),                     wgt);
        hFatJetTau21DDTLv[isam]->Fill(fBits->tau21DDT(selection),             wgt);
        hdRv[isam]             ->Fill(fBits->getdRsj0dR(selection),           wgt);
        hdRptv[isam]           ->Fill(fBits->getdRsj0dRpt(selection),         wgt);
        hBtagv[isam]           ->Fill(fBits->maxsubcsv(selection,isBacon),    wgt);
	hMinDPhiJetsMetv[isam] ->Fill(fBits->min_dphijetsmet,                 wgt);
        hMinDPhiJetsMetLv[isam]->Fill(fBits->min_dphijetsmet,                 wgt);
        hNFJetsv[isam]         ->Fill(fBits->nfjets(selection),               wgt);
        hNJetsv[isam]          ->Fill(fBits->njets,                           wgt);
        hNBJetsv[isam]         ->Fill(fBits->nbjetsLdR15,                     wgt);
	hJet1CHFv[isam]        ->Fill(fBits->chf(selection),                  wgt);
        hJet1NHFv[isam]        ->Fill(fBits->nhf(selection),                  wgt);
        hJet1NEMFv[isam]       ->Fill(fBits->nemf(selection),                 wgt);
	hJet1Etav[isam]        ->Fill(fBits->res_jet0_eta,                    wgt);
	hJet2Etav[isam]        ->Fill(fBits->res_jet1_eta,                    wgt);
	hJet3Etav[isam]        ->Fill(fBits->res_jet2_eta,                    wgt);
	hJet4Etav[isam]        ->Fill(fBits->res_jet3_eta,                    wgt);

	if((!isData && subsample.find("SR")==std::string::npos) || (!isData  && !isSignal && subsample.find("SR")!=std::string::npos)){ 
          neventsMC+=wgt;
          hMETMC            ->Fill(fBits->getMET(preselection,isBacon).Pt(),  wgt);
          hMETLogMC         ->Fill(fBits->getMET(preselection,isBacon).Pt(),  wgt);
	  hFatJetMassMC     ->Fill(fBits->fjet_mass(selection,isBacon),       wgt);
	  hFatJetMassLMC    ->Fill(fBits->fjet_mass(selection,isBacon),       wgt);
	  hFatJetPtMC       ->Fill(fBits->fjet_pt(selection,isBacon),         wgt);
	  hvJetMassMC       ->Fill(fBits->getTopRes().M(),                    wgt);
	  hvJetMassLMC      ->Fill(fBits->getTopRes().M(),                    wgt);
	  hvJetPtMC         ->Fill(fBits->getTopRes().Pt(),                   wgt);
	  hTransverseMassMC ->Fill(fBits->transverse_mass(selection),         wgt);
          hTransverseMassLMC->Fill(fBits->transverse_mass(selection),         wgt);
	  hFatJetTau21MC    ->Fill(fBits->tau21(selection),                   wgt);
	  hFatJetTau21DDTMC ->Fill(fBits->tau21DDT(selection),                wgt);
          hFatJetTau21DDTLMC->Fill(fBits->tau21DDT(selection),                wgt);
	  hdRMC             ->Fill(fBits->getdRsj0dR(selection),              wgt);
          hdRptMC           ->Fill(fBits->getdRsj0dRpt(selection),            wgt);
	  hBtagMC           ->Fill(fBits->maxsubcsv(selection,isBacon),       wgt);
	  hMinDPhiJetsMetMC ->Fill(fBits->min_dphijetsmet,                    wgt);
          hMinDPhiJetsMetLMC->Fill(fBits->min_dphijetsmet,                    wgt);
          hNFJetsMC         ->Fill(fBits->nfjets(selection),                  wgt);
	  hNJetsMC          ->Fill(fBits->njets,                              wgt);
          hNBJetsMC         ->Fill(fBits->nbjetsLdR2,                         wgt);
	  hJet1CHFMC        ->Fill(fBits->chf(selection),                     wgt);
	  hJet1NHFMC        ->Fill(fBits->nhf(selection),                     wgt);
	  hJet1NEMFMC       ->Fill(fBits->nemf(selection),                    wgt);
	  hJet1EtaMC        ->Fill(fBits->res_jet0_eta,                       wgt);
	  hJet2EtaMC        ->Fill(fBits->res_jet1_eta,                       wgt);
	  hJet3EtaMC        ->Fill(fBits->res_jet2_eta,                       wgt);
	  hJet4EtaMC        ->Fill(fBits->res_jet3_eta,                       wgt);
        }
	if(!isData){
	  if(isSignal1){
	    hMETSig1           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
	  }
	  if(isSignal2){ 
	    hMETSig2           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
	  }
          if(isSignal3){
            hMETSig3           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
          }
          if(isSignal4){
            hMETSig4           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
          }
          if(isSignal5){
            hMETSig5           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
          }
          if(isSignal6){
            hMETSig6           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
          }
          if(isSignal7){
            hMETSig7           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
          }
          if(isSignal8){
            hMETSig8           ->Fill(fBits->getMET(preselection).Pt(),       wgt);
          }
	}
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
  
  //
  // Make pull histograms
  //
  TH1D *hMETPull            = makePullHist(hMETv[0],            hMETMC,            "hMETPull",             doBlind, selection);
  TH1D *hMETLogPull         = makePullHist(hMETLogv[0],         hMETLogMC,         "hMETLogPull",          doBlind, selection);
  TH1D *hFatJetMassPull     = makePullHist(hFatJetMassv[0],     hFatJetMassMC,     "hFatJetMassPull",      doBlind, selection);
  TH1D *hFatJetMassLPull    = makePullHist(hFatJetMassLv[0],    hFatJetMassLMC,    "hFatJetMassLPull",     doBlind, selection);
  TH1D *hFatJetPtPull       = makePullHist(hFatJetPtv[0],       hFatJetPtMC,       "hFatJetPtPull",        doBlind, selection);
  TH1D *hvJetMassPull       = makePullHist(hvJetMassv[0],       hvJetMassMC,       "hvJetMassPull",        doBlind, selection);
  TH1D *hvJetMassLPull      = makePullHist(hvJetMassLv[0],      hvJetMassLMC,      "hvJetMassLPull",       doBlind, selection);
  TH1D *hvJetPtPull         = makePullHist(hvJetPtv[0],         hvJetPtMC,         "hvJetPtPull",          doBlind, selection);
  TH1D *hTransverseMassPull = makePullHist(hTransverseMassv[0], hTransverseMassMC, "hTransverseMassPull",  doBlind, selection);
  TH1D *hTransverseMassLPull= makePullHist(hTransverseMassLv[0],hTransverseMassLMC,"hTransverseMassLPull", doBlind, selection);
  TH1D *hFatJetTau32Pull    = makePullHist(hFatJetTau32v[0],    hFatJetTau32MC,    "hFatJetTau32Pull",     doBlind, selection);
  TH1D *hFatJetTau21Pull    = makePullHist(hFatJetTau21v[0],    hFatJetTau21MC,    "hFatJetTau21Pull",     doBlind, selection);
  TH1D *hFatJetTau21DDTPull = makePullHist(hFatJetTau21DDTv[0], hFatJetTau21DDTMC, "hFatJetTau21DDTPull",  doBlind, selection);
  TH1D *hFatJetTau21DDTLPull= makePullHist(hFatJetTau21DDTLv[0],hFatJetTau21DDTLMC,"hFatJetTau21DDTLPull", doBlind, selection);
  TH1D *hdRPull             = makePullHist(hdRv[0],             hdRMC,             "hdRPull",              doBlind, selection);
  TH1D *hdRptPull           = makePullHist(hdRptv[0],           hdRptMC,           "hdRptPull",            doBlind, selection);
  TH1D *hBtagPull           = makePullHist(hBtagv[0],           hBtagMC,           "hBtagPull",            doBlind, selection);
  TH1D *hMinSubJetcsvPull   = makePullHist(hMinSubJetcsvv[0],   hMinSubJetcsvMC,   "hMinSubJetcsvPull",    doBlind, selection);
  TH1D *hMinDPhiJetsMetPull = makePullHist(hMinDPhiJetsMetv[0], hMinDPhiJetsMetMC, "hMinDPhiJetsMetPull",  doBlind, selection);
  TH1D *hMinDPhiJetsMetLPull= makePullHist(hMinDPhiJetsMetLv[0],hMinDPhiJetsMetLMC,"hMinDPhiJetsMetLPull", doBlind, selection); 
  TH1D *hNFJetsPull         = makePullHist(hNFJetsv[0],         hNFJetsMC,         "hNFJetsPull",          doBlind, selection);
  TH1D *hNJetsPull          = makePullHist(hNJetsv[0],          hNJetsMC,          "hNJetsPull",           doBlind, selection);
  TH1D *hNBJetsPull         = makePullHist(hNBJetsv[0],         hNBJetsMC,         "hNBJetsPull",          doBlind, selection);
  TH1D *hJet1CHFPull        = makePullHist(hJet1CHFv[0],        hJet1CHFMC,        "hJet1CHFPull",         doBlind, selection);
  TH1D *hJet1NHFPull        = makePullHist(hJet1NHFv[0],        hJet1NHFMC,        "hJet1NHFPull",         doBlind, selection);
  TH1D *hJet1NEMFPull       = makePullHist(hJet1NEMFv[0],       hJet1NEMFMC,       "hJet1NEMFPull",        doBlind, selection);
  TH1D *hJet1EtaPull        = makePullHist(hJet1Etav[0],        hJet1EtaMC,        "hJet1EtaPull",         doBlind, selection);
  TH1D *hJet2EtaPull        = makePullHist(hJet2Etav[0],        hJet2EtaMC,        "hJet2EtaPull",         doBlind, selection);
  TH1D *hJet3EtaPull        = makePullHist(hJet3Etav[0],        hJet3EtaMC,        "hJet3EtaPull",         doBlind, selection);
  TH1D *hJet4EtaPull        = makePullHist(hJet4Etav[0],        hJet4EtaMC,        "hJet4EtaPull",         doBlind, selection);

  //                                                                                                                                                                                                    
  // Calculate significance                                                                                                                                                                               
  //                 
  vector<float> significance;
  significance.push_back(CalcSig(hMETSig1, hMETMC));
  significance.push_back(CalcSig(hMETSig2, hMETMC));
  significance.push_back(CalcSig(hMETSig3, hMETMC));
  significance.push_back(CalcSig(hMETSig4, hMETMC));
  significance.push_back(CalcSig(hMETSig5, hMETMC));
  significance.push_back(CalcSig(hMETSig6, hMETMC));
  significance.push_back(CalcSig(hMETSig7, hMETMC));
  significance.push_back(CalcSig(hMETSig8, hMETMC));

  isBacon = false;
  //--------------------------------------------------------------------------------------------------------------
  // Output
  //==============================================================================================================
   
  cout << "*" << endl;
  cout << "* SUMMARY" << endl;
  cout << "*--------------------------------------------------" << endl;
  cout << endl;

  ofstream txtfile;
  char txtfname[200];
  sprintf(txtfname,"%s/summary.txt",outputDir.c_str());
  txtfile.open(txtfname);
  txtfile << setprecision(6) << fixed;
  float max = samplev.size();
  if (subsample.find("SR")!=std::string::npos) max = samplev.size()-8;    
  for(unsigned int isam=1; isam<max; isam++) {
    txtfile << setw(35) << samplev[isam]->label;
    txtfile << setw(15) << neventsv[isam] << endl;
  }
  txtfile << "---------------------------------------------"  << endl;
  txtfile << setw(35) << "SM Expected:" << setw(15) << neventsMC << endl;
  if(!doBlind) { txtfile << setw(35) << "Observed:" << setw(15) << neventsv[0] << endl; }
  if(subsample.find("SR")!=std::string::npos){
    txtfile << "---------------------------------------------"  << endl;
    for(unsigned int isam=max; isam<samplev.size(); isam++) {
      txtfile << setw(35) << samplev[isam]->label;
      txtfile << setw(15) << neventsv[isam] << endl;
      txtfile << setw(35) << "Significance: ";
      txtfile << setw(15) << significance[samplev.size()-isam-1] << endl;
    }
  }
  txtfile.close();

   //--------------------------------------------------------------------------------------------------------------
  // Make plots
  //==============================================================================================================

  TCanvas *c = MakeCanvas("c","c",800,800);
  c->Divide(1,2,0,0);
  c->cd(1)->SetPad(0,0.3,1.0,1.0);
  c->cd(1)->SetTopMargin(0.1);
  c->cd(1)->SetBottomMargin(0);
  c->cd(1)->SetLeftMargin(0.15);
  c->cd(1)->SetRightMargin(0.07);
  c->cd(1)->SetTickx(1);
  c->cd(1)->SetTicky(1);
  c->cd(2)->SetPad(0,0,1.0,0.3);
  c->cd(2)->SetTopMargin(0);
  c->cd(2)->SetBottomMargin(0.45);
  c->cd(2)->SetLeftMargin(0.15);
  c->cd(2)->SetRightMargin(0.07);
  c->cd(2)->SetTickx(1);
  c->cd(2)->SetTicky(1);

  char ylabel[100];
  sprintf(ylabel,"Events / GeV");
  makePlot(c, "metl", "U [GeV]", ylabel, hMETv, samplev, hMETMC, hMETPull, doBlind, LUMI, false, 0.0, -0.03,
	   0.1, 2.1*(hMETMC->GetBinContent(hMETMC->GetMaximumBin()))/(hMETMC->GetBinWidth(hMETMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "met", "U [GeV]", ylabel, hMETLogv, samplev, hMETLogMC, hMETLogPull, doBlind, LUMI, true, 0.0, -0.03,
	   2e-5*(hMETLogMC->GetBinContent(hMETLogMC->GetMaximumBin()))/(hMETLogMC->GetBinWidth(hMETLogMC->GetMaximumBin())),
	   4e2*(hMETLogMC->GetBinContent(hMETLogMC->GetMaximumBin()))/(hMETLogMC->GetBinWidth(hMETLogMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / GeV/c^{2}");
  makePlot(c, "msd", "Soft Drop Mass [GeV/c^{2}]", ylabel, hFatJetMassv, samplev, hFatJetMassMC, hFatJetMassPull, doBlind, LUMI, false, -0.45, -0.03,
	   0.1, 2.1*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / GeV/c^{2}");
  makePlot(c, "msdl", "Soft Drop Mass [GeV/c^{2}]", ylabel, hFatJetMassLv, samplev, hFatJetMassLMC, hFatJetMassLPull, doBlind, LUMI, true, -0.45, -0.03,
	   2e-5*(hFatJetMassLMC->GetBinContent(hFatJetMassLMC->GetMaximumBin()))/(hFatJetMassLMC->GetBinWidth(hFatJetMassLMC->GetMaximumBin())),
	   4e2*(hFatJetMassLMC->GetBinContent(hFatJetMassLMC->GetMaximumBin()))/(hFatJetMassLMC->GetBinWidth(hFatJetMassLMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f GeV",hFatJetPtv[0]->GetBinWidth(1));
  makePlot(c, "fjpt", "Jet p_{T} [GeV]", ylabel, hFatJetPtv, samplev, hFatJetPtMC, hFatJetPtPull, doBlind, LUMI, false, 0.0, -0.03,
	   0.1, 2.1*(hFatJetPtMC->GetBinContent(hFatJetPtMC->GetMaximumBin()))/(hFatJetPtMC->GetBinWidth(hFatJetPtMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hBtagv[0]->GetBinWidth(10));
  makePlot(c, "btag", "Max subjet csv", ylabel, hBtagv, samplev, hBtagMC, hBtagPull, doBlind, LUMI, false, -0.4, -0.15,
	   0.1, 2.1*(hBtagMC->GetBinContent(hBtagMC->GetMaximumBin()))/(hBtagMC->GetBinWidth(hBtagMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hFatJetTau32v[0]->GetBinWidth(10));
  makePlot(c, "tau32", "#tau_{3}/#tau_{2}", ylabel, hFatJetTau32v, samplev, hFatJetTau32MC, hFatJetTau32Pull, doBlind, LUMI, false, -0.45, -0.03,
	   0.1, 2.1*(hFatJetTau32MC->GetBinContent(hFatJetTau32MC->GetMaximumBin()))/(hFatJetTau32MC->GetBinWidth(hFatJetTau32MC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hMinDPhiJetsMetv[0]->GetBinWidth(1));
  makePlot(c, "min_dphijetsmet", "Min #Delta#phi(MET,j_{i})", ylabel, hMinDPhiJetsMetv, samplev, hMinDPhiJetsMetMC, hMinDPhiJetsMetPull, doBlind, LUMI, false, -0.4, -0.15,0.1, 2.1*(hMinDPhiJetsMetMC->GetBinContent(hMinDPhiJetsMetMC->GetMaximumBin()))/(hMinDPhiJetsMetMC->GetBinWidth(hMinDPhiJetsMetMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events");
  makePlot(c, "min_dphijetsmetl", "Min #Delta#phi(MET,j_{i})", ylabel, hMinDPhiJetsMetLv, samplev, hMinDPhiJetsMetLMC, hMinDPhiJetsMetLPull, doBlind, LUMI, true, -0.4, -0.15, 2e-5*(hMinDPhiJetsMetLMC->GetBinContent(hMinDPhiJetsMetLMC->GetMaximumBin()))/(hMinDPhiJetsMetLMC->GetBinWidth(hMinDPhiJetsMetLMC->GetMaximumBin())), 4e2*(hMinDPhiJetsMetLMC->GetBinContent(hMinDPhiJetsMetLMC->GetMaximumBin()))/(hMinDPhiJetsMetLMC->GetBinWidth(hMinDPhiJetsMetLMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %i ",int(hNFJetsv[0]->GetBinWidth(1)));
  makePlot(c, "nfjets", "N^{fat}_{jets} (CA15)", "Events", hNFJetsv, samplev, hNFJetsMC, hNFJetsPull, doBlind, LUMI, false, 0.0, -0.03,
	   0.1, 2.1*(hNFJetsMC->GetBinContent(hNFJetsMC->GetMaximumBin()))/(hNFJetsMC->GetBinWidth(hNFJetsMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %i ",int(hNJetsv[0]->GetBinWidth(1)));
  makePlot(c, "njets", "N_{jets} (AK4)", "Events", hNJetsv, samplev, hNJetsMC, hNJetsPull, doBlind, LUMI, false, 0.0, -0.03,
	   0.1, 2.1*(hNJetsMC->GetBinContent(hNJetsMC->GetMaximumBin()))/(hNJetsMC->GetBinWidth(hNJetsMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %i ",int(hNBJetsv[0]->GetBinWidth(1)));
  makePlot(c, "nbjets", "N^{#Delta R(j,J)>2}_{b-jets} (AK4)", "Events", hNBJetsv, samplev, hNBJetsMC, hNBJetsPull, doBlind, LUMI, false, 0.0, -0.03,
	   0.1, 2.1*(hNBJetsMC->GetBinContent(hNBJetsMC->GetMaximumBin()))/(hNBJetsMC->GetBinWidth(hNBJetsMC->GetMaximumBin())), selection, subsample);

  cout << endl;
  cout << " <> Output saved in " << outputDir << endl;
  cout << endl; 
  
}

//=== FUNCTION DEFINITIONS ======================================================================================

//--------------------------------------------------------------------------------------------------
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy, const double legdx, const double legdy,
              const double ymin, const double ymax, const string selection, const string subsample)
{
  const int uncColor = kGray+3;

  // Should divide by bin width
  for (int iB=1; iB<hExp->GetNbinsX()+1; ++iB) {
    float currentVal = hExp->GetBinContent(iB);
    float currentErr = hExp->GetBinError(iB);
    float binWidth = hExp->GetBinWidth(iB);
    hExp->SetBinContent(iB,currentVal/binWidth);
    hExp->SetBinError(iB,currentErr/binWidth);
  }
  for(unsigned int i=0; i<histv.size(); i++) {
    for (int iB=1; iB<histv[i]->GetNbinsX()+1; ++iB) {
      float currentVal = histv[i]->GetBinContent(iB);
      float currentErr = histv[i]->GetBinError(iB);
      float binWidth = histv[i]->GetBinWidth(iB);
      histv[i]->SetBinContent(iB,currentVal/binWidth);
      histv[i]->SetBinError(iB,currentErr/binWidth);
    }
  }
  
  histv[0]->SetMarkerSize(0.9);
  
  CPlot plot(outname.c_str(),"",xlabel.c_str(),ylabel.c_str());  
  plot.AddHist1D(hExp,"E2",uncColor,1,3004);
  if(!doBlind) { plot.AddHist1D(histv[0],samplev[0]->label,"E"); }
  float max = samplev.size();
  if (subsample.find("SR")!=std::string::npos) max = samplev.size()-8; 
  //plot.AddToStack(histv[3],samplev[3]->label,samplev[3]->fillcolor,samplev[3]->linecolor);
  for(unsigned int i=1; i<max; i++) {
    //if(i ==3) continue;
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }

  if (subsample.find("SR")!=std::string::npos){
    for(unsigned int i=max; i<histv.size(); i++) {
      plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
    }
  }

  // Add CMS label
  char lumitext[100];
  sprintf(lumitext,"%.2f fb^{-1} (13 TeV)",lumi);
  plot.AddTextBox(lumitext,0.66,0.99,0.95,0.925,0,kBlack);
  plot.AddTextBox("CMS",0.18,0.88,0.30,0.82,0,kBlack,62);
  plot.AddTextBox("Preliminary",0.18,0.82,0.37,0.77,0,kBlack,52);
  plot.TransLegend(legdx, legdy);
  
  if(doLogy) plot.SetLogy();
  if(ymin!=ymax) plot.SetYRange(ymin,ymax);

  hPull->SetMarkerSize(0.8);
  const double xmin = histv[0]->GetXaxis()->GetBinLowEdge(1);
  const double xmax = histv[0]->GetXaxis()->GetBinUpEdge(histv[0]->GetNbinsX());
  TH1D *hExpPull = (TH1D*)hExp->Clone("hExpPull");
  for (int iB=1; iB<hExpPull->GetNbinsX()+1; ++iB) {
    float currentVal = hExpPull->GetBinContent(iB);
    float currentErr = hExpPull->GetBinError(iB);
    hExpPull->SetBinContent(iB,1.);
    hExpPull->SetBinError(iB,currentErr/currentVal);
  }

  CPlot plotPull(outname.c_str(),"",xlabel.c_str(),"Data/MC");
  plotPull.AddHist1D(hPull,"EX0",kBlack);
  plotPull.AddHist1D(hExpPull,"E2",uncColor,1,3004);
  plotPull.SetYRange(0.,2.);
  plotPull.AddLine(xmin,1,xmax,1,kBlack,3);

  plot.Draw(c,false,"png",1);
  plot.Draw(c,false,"pdf",1);
  plotPull.Draw(c,true,"png",2);
  plotPull.Draw(c,true,"pdf",2);
}

//--------------------------------------------------------------------------------------------------
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind, const string selection)
{
  const Int_t NBINS = 5, NBINSMT = 3; // MonoTop                                                                                                                                                           
  Double_t edges[NBINS+1] = {250,300,350,400,500,1000};
  Double_t edgesMT[NBINSMT + 1] = {350,550,750,3000};

  TH1D *hPull;
  if (name=="hMETPull" || name=="hMETLogPull"){
    hPull = new TH1D(name.c_str(),"",NBINS,edges);
  }
  else if (name=="hTransverseMassPull" || name=="hTransverseMassLPull"){
    hPull = new TH1D(name.c_str(),"",NBINSMT,edgesMT);
  }
  else{
    hPull = new TH1D(name.c_str(),"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  }
  for(int ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    double numer = hData->GetBinContent(ibin);
    double denom = hMC->GetBinContent(ibin);
    double pull  = (denom>0) ? numer/denom : 0;
    double err   = (denom>0) ? sqrt(hData->GetBinContent(ibin))/hMC->GetBinContent(ibin): 0;
    
    if(doBlind) {
      pull = 0;
      err  = 0;
    }

    hPull->SetBinContent(ibin,pull);
    hPull->SetBinError(ibin,err);
  }
  hPull->GetYaxis()->SetTitleOffset(0.42);
  hPull->GetYaxis()->SetTitleSize(0.13);
  hPull->GetYaxis()->SetLabelSize(0.10);
  hPull->GetYaxis()->SetNdivisions(5);
  hPull->GetYaxis()->CenterTitle();
  hPull->GetXaxis()->SetTitleOffset(1.2);
  hPull->GetXaxis()->SetTitleSize(0.13);
  hPull->GetXaxis()->SetLabelSize(0.12);

  return hPull;
}

//--------------------------------------------------------------------------------------------------                                                                                                      
float CalcSig(TH1D*sig, TH1D*bkg) {
  float fSig2 = 0;
  int nb = sig->GetNbinsX();
  for (int i = 0; i <= nb+1; i++) {
    if (sig->GetBinContent(i) > 0 && bkg->GetBinContent(i)>0) {
      fSig2 += pow(sig->GetBinContent(i),2)/bkg->GetBinContent(i);
    }
  }
  return sqrt(fSig2);
}
