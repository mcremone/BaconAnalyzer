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

void plotMonoX(const string preselection, const string selection, const string subsample, const string combo = "ONLY", TString algo= "PUPPI", TString syst = "CENT", TString bst15jetID = "jetT", TString bst8jetID = "jetT")
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  const bool doBlind = false;
  bool isBacon = false;

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
    if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("/tmp/cmantill/SingleElectrontrig7.root");
    if (preselection.compare("Pho")==0)  samplev.back()->fnamev.push_back("/tmp/cmantill/SinglePhotontrig7.root");
    if (preselection.compare("Pho")!=0) {
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/tmp/cmantill/QCD80_2.root");
      samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/T80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/TZ80_2.root");
      samplev.push_back(new CSample("t#bar{t}",kOrange - 3,kOrange - 3));
      samplev.back()->fnamev.push_back("/tmp/cmantill/TT80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/TTZ80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/TTG80_2.root");
      samplev.push_back(new CSample("Diboson",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/WW80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/WZ80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/ZZ80_2.root");
      samplev.push_back(new CSample("W+jets",kGreen - 10,kGreen - 10));
      samplev.back()->fnamev.push_back("/tmp/cmantill/WHF.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/WLF.root");
      samplev.push_back(new CSample("Z+jets", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/ZHF80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/ZLF80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/DYHF80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/DYLF80_2.root");
    }
    if (preselection.compare("Pho")==0){
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/tmp/cmantill/SinglePhotontrig7.root");
      samplev.push_back(new CSample("#gamma+jets", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/GHF80_2.root");
      samplev.back()->fnamev.push_back("/tmp/cmantill/GLF80_2.root");
    }
    if (subsample.compare("SR")==0 && (selection.compare("Bst15MonoTop")==0  || selection.compare("Bst15SemMonoTop")==0|| selection.compare("Bst8MonoTop")==0)){   
      samplev.push_back(new CSample("M_{S} 1100, M#chi 100", kBlue, kBlue));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1300_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{V} 300 X 5", kGreen, kGreen));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S4_Mchi_300_13TeV_madgraph_pythia8_mc.root");
      samplev.push_back(new CSample("M_{S} 1300, M#chi 100", kTeal-1, kTeal-1));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1300_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{S} 1500, M#chi 100", kOrange+8, kOrange+8));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1500_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{S} 1700, M#chi 100", kViolet, kViolet));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1700_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{S} 1900, M#chi 100", kGray, kGray));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1900_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{V} 500 X 5", kRed-9, kRed-9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S4_Mchi_500_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{V} 700 X 5", kRed, kRed));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S4_Mchi_700_13TeV_madgraph_pythia8_2_mc.root");
    }
  }
  else{
    samplev.push_back(new CSample("data",0,0));
    if (preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0)  samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/MET.root");
    if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/SingleElectron.root");
    if (preselection.compare("Pho")==0) samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/SinglePhoton.root");
    if (preselection.compare("Pho")!=0) {
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/QCD.root");
      samplev.push_back(new CSample("SingleTop",kRed - 9,kRed - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/SingleTop.root");
      samplev.push_back(new CSample("ttbar",kOrange - 4,kOrange - 4));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/TTbar_Powheg.root");
      samplev.push_back(new CSample("Diboson",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/Diboson.root");
      samplev.push_back(new CSample("Wjets",kGreen - 10,kGreen - 10));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/WJets.root");
      samplev.push_back(new CSample("ZnunuLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/ZtoNuNu.root");
      samplev.push_back(new CSample("ZllLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/ZJets.root");
    }
    if (preselection.compare("Pho")==0){
      samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/SinglePhoton.root");
      samplev.push_back(new CSample("Photon", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("/afs/cern.ch/user/s/snarayan/work/skims/monotop_80_v8/GJets.root");
    }
    if (subsample.compare("SR")==0 && (selection.compare("Bst15MonoTop")==0  || selection.compare("Bst15SemMonoTop")==0|| selection.compare("Bst8MonoTop")==0)){
      samplev.push_back(new CSample("M_{S} 1100, M#chi 100", kBlue, kBlue));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1300_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{V} 300 X 5", kGreen, kGreen));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S4_Mchi_300_13TeV_madgraph_pythia8_mc.root");
      samplev.push_back(new CSample("M_{S} 1300, M#chi 100", kTeal-1, kTeal-1));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1300_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{S} 1500, M#chi 100", kOrange+8, kOrange+8));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1500_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{S} 1700, M#chi 100", kViolet, kViolet));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1700_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{S} 1900, M#chi 100", kGray, kGray));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S1_Mres_1900_Mchi_100_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{V} 500 X 5", kRed-9, kRed-9));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S4_Mchi_500_13TeV_madgraph_pythia8_2_mc.root");
      samplev.push_back(new CSample("M_{V} 700 X 5", kRed, kRed));
      samplev.back()->fnamev.push_back("/tmp/cmantill/Monotop_S4_Mchi_700_13TeV_madgraph_pythia8_2_mc.root");
    }
  }

  // integrated luminosity to scale MC
  const double LUMI = 13.1;
  
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
  vector<TH1D*> hFatJetMassv, hFatJetMassLv, hFatJetPtv, hFatJetTau32v;
  vector<TH1D*> hBtagv, hMaxSubJetcsvv;
  vector<TH1D*> hMinDPhiJetsMetv, hMinDPhiJetsMetLv, hMinDPhiFatJetMetv, hNFJetsv, hNJetsv, hNBJetsv;
  vector<double> neventsv;
 
  const Int_t NBINS = 5, NBINSMT = 3; // MonoTop
  Double_t edges[NBINS+1] = {250,300,350,400,500,1000};
  Double_t edgesMT[NBINSMT + 1] = {350,550,750,3000};

  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    sprintf(hname,"hMET_%i",isam);            hMETv.push_back(new TH1D(hname,"",NBINS,edges));                hMETv[isam]->Sumw2();
    sprintf(hname,"hMETLog_%i",isam);         hMETLogv.push_back(new TH1D(hname,"",NBINS,edges));             hMETLogv[isam]->Sumw2();
    sprintf(hname,"hFatJetMass_%i",isam);     hFatJetMassv.push_back(new TH1D(hname,"",20,0,300));            hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetMassL_%i",isam);    hFatJetMassLv.push_back(new TH1D(hname,"",20,0,300));           hFatJetMassLv[isam]->Sumw2();
    sprintf(hname,"hFatJetPt_%i",isam);       hFatJetPtv.push_back(new TH1D(hname,"",20,250,1000));           hFatJetPtv[isam]->Sumw2();
    sprintf(hname,"hTransverseMass_%i",isam); hTransverseMassv.push_back(new TH1D(hname,"",NBINSMT,edgesMT)); hTransverseMassv[isam]->Sumw2();
    sprintf(hname,"hTransverseMassL_%i",isam);hTransverseMassLv.push_back(new TH1D(hname,"",NBINSMT,edgesMT));hTransverseMassLv[isam]->Sumw2();
    sprintf(hname,"hFatJetTau32_%i",isam);    hFatJetTau32v.push_back(new TH1D(hname,"",15,0.2,1));           hFatJetTau32v[isam]->Sumw2();
    sprintf(hname,"hBtag_%i",isam);           hBtagv.push_back(new TH1D(hname,"",15,0.1,1.));                 hBtagv[isam]->Sumw2();
    sprintf(hname,"hMaxSubJetcsv_%i",isam);   hMaxSubJetcsvv.push_back(new TH1D(hname,"",15,0.1,1.));         hMaxSubJetcsvv[isam]->Sumw2();
    sprintf(hname,"hMinDPhiJetsMet_%i",isam); hMinDPhiJetsMetv.push_back(new TH1D(hname,"",20,0,3.14));       hMinDPhiJetsMetv[isam]->Sumw2();
    sprintf(hname,"hMinDPhiJetsMetL_%i",isam);hMinDPhiJetsMetLv.push_back(new TH1D(hname,"",20,0,3.14));      hMinDPhiJetsMetLv[isam]->Sumw2();
    sprintf(hname,"hNFJets_%i",isam);         hNFJetsv.push_back(new TH1D(hname,"",10,0,10));                 hNFJetsv[isam]->Sumw2();
    sprintf(hname,"hNJets_%i",isam);          hNJetsv.push_back(new TH1D(hname,"",10,0,10));                  hNJetsv[isam]->Sumw2();
    sprintf(hname,"hNBJets_%i",isam);         hNBJetsv.push_back(new TH1D(hname,"",10,0,10));                 hNBJetsv[isam]->Sumw2();
    neventsv.push_back(0);
  }

  TH1D *hMETMC             = (TH1D*)hMETv[0]            ->Clone("hMETMC");
  TH1D *hMETLogMC          = (TH1D*)hMETLogv[0]         ->Clone("hMETLogMC");
  TH1D *hFatJetMassMC      = (TH1D*)hFatJetMassv[0]     ->Clone("hFatJetMassMC");
  TH1D *hFatJetMassLMC     = (TH1D*)hFatJetMassLv[0]    ->Clone("hFatJetMassLMC");
  TH1D *hFatJetPtMC        = (TH1D*)hFatJetPtv[0]       ->Clone("hFatJetPtMC");
  TH1D *hTransverseMassMC  = (TH1D*)hTransverseMassv[0 ]->Clone("hTransverseMassMC");
  TH1D *hTransverseMassLMC = (TH1D*)hTransverseMassLv[0]->Clone("hTransverseMassLMC");
  TH1D *hFatJetTau32MC     = (TH1D*)hFatJetTau32v[0]    ->Clone("hFatJetTau32MC");
  TH1D *hBtagMC            = (TH1D*)hBtagv[0]           ->Clone("hBtagMC");
  TH1D *hMaxSubJetcsvMC    = (TH1D*)hMaxSubJetcsvv[0]   ->Clone("hMaxSubJetcsvMC");
  TH1D *hMinDPhiJetsMetMC  = (TH1D*)hMinDPhiJetsMetv[0] ->Clone("hMinDPhiJetsMetMC");
  TH1D *hMinDPhiJetsMetLMC = (TH1D*)hMinDPhiJetsMetLv[0]->Clone("hMinDPhiJetsMetLMC");
  TH1D *hNFJetsMC          = (TH1D*)hNJetsv[0]          ->Clone("hNFJetsMC");
  TH1D *hNJetsMC           = (TH1D*)hNJetsv[0]          ->Clone("hNJetsMC");
  TH1D *hNBJetsMC          = (TH1D*)hNBJetsv[0]         ->Clone("hNBJetsMC");
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
        isBacon = true;
      }
    }
    bool isSignal1 = (isam==samplev.size()-1);
    bool isSignal2 = (isam==samplev.size()-2);
    bool isSignal3 = (isam==samplev.size()-3);
    bool isSignal4 = (isam==samplev.size()-4);
    bool isSignal5 = (isam==samplev.size()-5);
    bool isSignal6 = (isam==samplev.size()-6);
    bool isSignal7 = (isam==samplev.size()-7);
    bool isSignal8 = (isam==samplev.size()-8);
    //if(preselection.compare("Pho")==0 && sample->label.compare("QCD")==0) isData=true;
 
    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      if(isBacon){ intree = (TTree*)infile->Get("Events"); assert(intree);}
      else{ intree = (TTree*)infile->Get("events"); assert(intree);}
      fBits     = new MonoXBitsLoader(intree,bst15jetID,bst8jetID,algo,syst,preselection,isData,isBacon);

      double nevts=0;
      int noweight=0;

      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
	//for(unsigned int ientry=0; ientry<10000; ientry++) {
        intree->GetEntry(ientry);
        if(isBacon){
          if(!fBits->selectJetAlgoAndSize(selection,algo,bst15jetID,bst8jetID)) continue;
	  if(isData && ((fBits->metfilter & 1) || (fBits->metfilter & 2) || (fBits->metfilter & 8) || (fBits->metfilter & 32) || 
			(fBits->metfilter & 1024) || (fBits->metfilter & 2048) || (fBits->metfilter & 32768))) continue;
        }
        else{
          if(isData && fBits->metfilter==0)                   continue;
	}
	//preselection
        if(!fBits->passPreSelection(preselection,isData,isBacon)) continue;
        //selection                                                                                                                                                                     
	float btagw=1;
        if(!fBits->passSelection(preselection,selection,subsample,combo,btagw,syst,isSignal,isBacon)) continue;
        double wgt = 1;
        if(isBacon && preselection.compare("Pho")==0 && isam==1) wgt *= fBits->getPhotonPurity();
	//if(!isBacon && preselection.compare("Pho")==0 && sample->label.compare("QCD")==0) wgt *=fBits->photonPurity;
	if(!isData) {
          if(isBacon){
	    wgt *= LUMI*fBits->evtWeight*fBits->kfactor*btagw*fBits->eleSF1*fBits->eleSF2*fBits->muoSF1*fBits->muoSF2*fBits->scale1fb;
            if(preselection.compare("Had")!=0 && preselection.compare("Muo")!=0 && preselection.compare("Zmm")!=0) wgt *= fBits->triggerEff;
            if(selection.compare("Bst15MonoTop")==0 || selection.compare("Bst8MonoTop")==0 || selection.compare("Bst15SemMonoTop")==0){
              if(sample->label=="ttbar" && fBits->topSize15<0.8 && fBits->isHadronicTop15==1 &&fBits->topMatching15 <1.4 && fBits->topMatching15 > 0 && fBits->topSize15 > 0){
                wgt *= 1.107;                                                                                                          
              }
              else if(sample->label=="ttbar" && (fBits->topSize15>=0.8 || fBits->isHadronicTop15!=1 || fBits->topMatching15 >1.4 || fBits->topMatching15 <= 0 || fBits->topSize15 <= 0)){
                wgt *= 0.966;
              }
	      else{
                wgt *= 0.966;
	      }
            }
          }
          else{
            if(preselection.compare("Pho")==0 && sample->label.compare("QCD")==0) wgt *=fBits->photonPurity;
	    else{
	    wgt *= LUMI*fBits->normalizedWeight*1000*fBits->sf_ewkZ*fBits->sf_qcdZ*fBits->sf_ewkW*fBits->sf_qcdW*fBits->sf_ewkA*fBits->sf_qcdA*fBits->sf_tt*fBits->sf_lep*btagw;
	    if(preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0) wgt *= fBits->sf_metTrig;
	    if(preselection.compare("Pho")==0) wgt *= fBits->sf_phoTrig;
	    if(preselection.compare("Ele")==0) wgt *= fBits->sf_eleTrig;
	    if(preselection.compare("Zee")==0) wgt *= fBits->sf_eleTrig*fBits->sf_phoTrig;
	    if(selection.compare("Bst15MonoTop")==0 || selection.compare("Bst15SemMonoTop")==0){
	      if(sample->label=="ttbar" && fBits->bst15_jet1_isMatched==1){
		wgt *= 1.107;
	      }
	      else if(sample->label=="ttbar" && fBits->bst15_jet1_isMatched!=1){
		wgt *= 0.966;
	      }
	      else{
		wgt *= 0.966;
	      }
	    }}
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
	hTransverseMassv[isam] ->Fill(fBits->transverse_mass(selection),      wgt);
        hTransverseMassLv[isam]->Fill(fBits->transverse_mass(selection),      wgt);
	hFatJetTau32v[isam]    ->Fill(fBits->tau32(selection,isBacon),                wgt);
        hBtagv[isam]           ->Fill(fBits->maxsubcsv(selection,isBacon),            wgt);
        hMaxSubJetcsvv[isam]   ->Fill(fBits->minsubcsv(selection),            wgt);
	hMinDPhiJetsMetv[isam] ->Fill(fBits->min_dphijetsmet,                 wgt);
        hMinDPhiJetsMetLv[isam]->Fill(fBits->min_dphijetsmet,                 wgt);
        hNFJetsv[isam]         ->Fill(fBits->nfjets(selection),               wgt);
        hNJetsv[isam]          ->Fill(fBits->njets,                           wgt);
        hNBJetsv[isam]         ->Fill(fBits->nbjetsLdR15,                     wgt);

	if((preselection.compare("Pho")==0 && sample->label.compare("QCD")==0) || (!isData && subsample.find("SR")==std::string::npos) || (!isData  && !isSignal && subsample.find("SR")!=std::string::npos)){ 
          neventsMC+=wgt;
          hMETMC            ->Fill(fBits->getMET(preselection,isBacon).Pt(),          wgt);
          hMETLogMC         ->Fill(fBits->getMET(preselection,isBacon).Pt(),          wgt);
	  hFatJetMassMC     ->Fill(fBits->fjet_mass(selection,isBacon),               wgt);
	  hFatJetMassLMC    ->Fill(fBits->fjet_mass(selection,isBacon),               wgt);
	  hFatJetPtMC       ->Fill(fBits->fjet_pt(selection,isBacon),                 wgt);
	  hTransverseMassMC ->Fill(fBits->transverse_mass(selection),         wgt);
          hTransverseMassLMC->Fill(fBits->transverse_mass(selection),         wgt);
	  hFatJetTau32MC    ->Fill(fBits->tau32(selection,isBacon),                   wgt);
	  hBtagMC           ->Fill(fBits->maxsubcsv(selection,isBacon),               wgt);
	  hMaxSubJetcsvMC   ->Fill(fBits->minsubcsv(selection),               wgt);
	  hMinDPhiJetsMetMC ->Fill(fBits->min_dphijetsmet,                    wgt);
          hMinDPhiJetsMetLMC->Fill(fBits->min_dphijetsmet,                    wgt);
          hNFJetsMC         ->Fill(fBits->nfjets(selection),                  wgt);
	  hNJetsMC          ->Fill(fBits->njets,                              wgt);
          hNBJetsMC         ->Fill(fBits->nbjetsLdR2,                         wgt);
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
  TH1D *hTransverseMassPull = makePullHist(hTransverseMassv[0], hTransverseMassMC, "hTransverseMassPull",  doBlind, selection);
  TH1D *hTransverseMassLPull= makePullHist(hTransverseMassLv[0],hTransverseMassLMC,"hTransverseMassLPull", doBlind, selection);
  TH1D *hFatJetTau32Pull    = makePullHist(hFatJetTau32v[0],    hFatJetTau32MC,    "hFatJetTau32Pull",     doBlind, selection);
  TH1D *hBtagPull           = makePullHist(hBtagv[0],           hBtagMC,           "hBtagPull",            doBlind, selection);
  TH1D *hMaxSubJetcsvPull   = makePullHist(hMaxSubJetcsvv[0],   hMaxSubJetcsvMC,   "hMaxSubJetcsvPull",    doBlind, selection);
  TH1D *hMinDPhiJetsMetPull = makePullHist(hMinDPhiJetsMetv[0], hMinDPhiJetsMetMC, "hMinDPhiJetsMetPull",  doBlind, selection);
  TH1D *hMinDPhiJetsMetLPull= makePullHist(hMinDPhiJetsMetLv[0],hMinDPhiJetsMetLMC,"hMinDPhiJetsMetLPull", doBlind, selection); 
  TH1D *hNFJetsPull         = makePullHist(hNFJetsv[0],         hNFJetsMC,         "hNFJetsPull",          doBlind, selection);
  TH1D *hNJetsPull          = makePullHist(hNJetsv[0],          hNJetsMC,          "hNJetsPull",           doBlind, selection);
  TH1D *hNBJetsPull         = makePullHist(hNBJetsv[0],         hNBJetsMC,         "hNBJetsPull",          doBlind, selection);


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
  std::cout << "metl" << std::endl;
  //sprintf(ylabel,"Events / GeV");
  //makePlot(c, "metl", "U [GeV]", ylabel, hMETv, samplev, hMETMC, hMETPull, doBlind, LUMI, false, 0.0, -0.03,
  //	   0.1, 2.1*(hMETMC->GetBinContent(hMETMC->GetMaximumBin()))/(hMETMC->GetBinWidth(hMETMC->GetMaximumBin())), selection, subsample);

  std::cout << "met" << std::endl;
  sprintf(ylabel,"Events / GeV");
  //makePlot(c, "met", "U [GeV]", ylabel, hMETLogv, samplev, hMETLogMC, hMETLogPull, doBlind, LUMI, true, 0.0, -0.03,
  //   2e-5*(hMETLogMC->GetBinContent(hMETLogMC->GetMaximumBin()))/(hMETLogMC->GetBinWidth(hMETLogMC->GetMaximumBin())),
  //	   4e2*(hMETLogMC->GetBinContent(hMETLogMC->GetMaximumBin()))/(hMETLogMC->GetBinWidth(hMETLogMC->GetMaximumBin())), selection, subsample);
  /*
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

  sprintf(ylabel,"Events / %.1f ",hMaxSubJetcsvv[0]->GetBinWidth(10));
  makePlot(c, "maxsubjet", "Max subjet csv", ylabel, hMaxSubJetcsvv, samplev, hMaxSubJetcsvMC, hMaxSubJetcsvPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hMaxSubJetcsvMC->GetBinContent(hMaxSubJetcsvMC->GetMaximumBin()))/(hMaxSubJetcsvMC->GetBinWidth(hMaxSubJetcsvMC->GetMaximumBin())), selection, subsample);

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
  */
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
  float max = samplev.size()-8;
  if (subsample.find("SR")!=std::string::npos) max = samplev.size()-8; 
  for(unsigned int i=1; i<max; i++) {
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }
  if (subsample.find("SR")!=std::string::npos){
    for(unsigned int i=max; i<histv.size(); i++) {
      plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
    }
  }

  // Add CMS label
  char lumitext[100];
  sprintf(lumitext,"%.1f fb^{-1} (13 TeV)",lumi);
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
