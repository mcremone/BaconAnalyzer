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

#include "../macros/CPlot.hh"         // helper class for plots
#include "../macros/KStyle.hh"        // style settings for drawing
#include "../macros/CSample.hh"       // helper class to manage samples
#include "../macros/RazorBitsLoader.hh"    // helper to load monoxbits
//#endif

using namespace std;

//Object Processors                                                                                                                                                                                      
RazorBitsLoader       *fBits      = 0;

//=== FUNCTION DECLARATIONS ======================================================================================

// make "standard" plot
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy=false, const double legdx=0, const double legdy=0,
              const double ymin=-1, const double ymax=-1, const string selection="", const string subsample="");
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind);
float CalcSig(TH1D*sig, TH1D*bkg);

//=== MAIN MACRO =================================================================================================

void plotRazor(const string preselection, const string selection, const string subsample, const string combo, TString algo, TString syst)
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  const bool doBlind = false;

  // Create output directory 
  const string outputDir("razorplots/"+preselection+"_"+selection+"_"+subsample+"_"+combo+"_"+algo);
  gSystem->mkdir(outputDir.c_str(), true);
  CPlot::sOutDir = outputDir;

  //
  // Samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;

  samplev.push_back(new CSample("data",0,0));
  if (preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0)  samplev.back()->fnamev.push_back("../razorbits/MET.root");
  if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("../razorbits/SingleElectron.root");
  if (preselection.compare("Pho")==0)  samplev.back()->fnamev.push_back("../razorbits/SinglePhoton.root");
  samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
  samplev.back()->fnamev.push_back("../razorbits/QCD.root");
  if (preselection.compare("Pho")!=0) {
    samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
    samplev.back()->fnamev.push_back("../razorbits/T.root");
    samplev.back()->fnamev.push_back("../razorbits/TZ.root");
    samplev.push_back(new CSample("t#bar{t}",kOrange - 3,kOrange - 3));
    // samplev.back()->fnamev.push_back("../razorbits/TT1L.root");
    // samplev.back()->fnamev.push_back("../razorbits/TT2L.root");
    // samplev.back()->fnamev.push_back("../razorbits/TTHAD.root");
    samplev.back()->fnamev.push_back("../razorbits/TT.root");
    samplev.back()->fnamev.push_back("../razorbits/TTZ.root");
    samplev.back()->fnamev.push_back("../razorbits/TTG.root");
    samplev.push_back(new CSample("Diboson",kYellow - 9,kYellow - 9));
    samplev.back()->fnamev.push_back("../razorbits/WW.root");
    samplev.back()->fnamev.push_back("../razorbits/WZ.root");
    samplev.back()->fnamev.push_back("../razorbits/ZZ.root");
    samplev.push_back(new CSample("W+jets",kGreen - 10,kGreen - 10));
    // samplev.back()->fnamev.push_back("../razorbits/W.root");
    samplev.back()->fnamev.push_back("../razorbits/WHF.root");
    // samplev.push_back(new CSample("W+LF",kGreen - 7,kGreen - 7));
    samplev.back()->fnamev.push_back("../razorbits/WLF.root");
    samplev.push_back(new CSample("Z+jets", kCyan - 9, kCyan - 9));
    // samplev.back()->fnamev.push_back("../razorbits/Z.root");
    samplev.back()->fnamev.push_back("../razorbits/ZHF.root");   
    samplev.back()->fnamev.push_back("../razorbits/ZLF.root");
    samplev.back()->fnamev.push_back("../razorbits/DYHF.root");
    samplev.back()->fnamev.push_back("../razorbits/DYLF.root");
    // samplev.push_back(new CSample("t#bar{t} comb.",kOrange - 3,kOrange - 3));
    // samplev.back()->fnamev.push_back("../razorbits/TT1L.root");
    // samplev.back()->fnamev.push_back("../razorbits/TT2L.root");
    // samplev.back()->fnamev.push_back("../razorbits/TTHAD.root");
    // samplev.back()->fnamev.push_back("../razorbits/TTBST.root");
    // samplev.back()->fnamev.push_back("../razorbits/TTCOM.root");
    // samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
    // samplev.back()->fnamev.push_back("../razorbits/T.root");
    // samplev.back()->fnamev.push_back("../razorbits/TZ.root");
    // samplev.push_back(new CSample("t#bar{t} merged",kOrange - 4,kOrange - 4));
    // samplev.back()->fnamev.push_back("../razorbits/TTBST.root");
  }
  if (preselection.compare("Pho")==0){
    samplev.push_back(new CSample("#gamma+jets", kCyan - 9, kCyan - 9));
    //    samplev.back()->fnamev.push_back("../razorbits/G.root");
    samplev.back()->fnamev.push_back("../razorbits/GHF.root");
    samplev.back()->fnamev.push_back("../razorbits/GLF.root");
  }
  if (subsample.compare("SR")==0){   
    samplev.push_back(new CSample("M_{S} 1100, M#chi 100", kBlue, kBlue));
    samplev.back()->fnamev.push_back("../razorbits/Spring15_a25ns_Monotop_S1_Mres-1100_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("M_{V} 300 X 5", kRed, kRed));
    samplev.back()->fnamev.push_back("../razorbits/Spring15_a25ns_Monotop_S4_Mchi-300_MINIAOD_mc.root");
    // samplev.push_back(new CSample("Mres-1300_Mchi-100", kBlack, kBlack));
    // samplev.back()->fnamev.push_back("../razorbits/Spring15_a25ns_DMJetsMonotop_S1_Mres-1300_Mchi-100_13TeV-madgraph-pythia8_mc.root");
    // samplev.push_back(new CSample("Mchi-500", kGreen, kGreen));
    // samplev.back()->fnamev.push_back("../razorbits/Spring15_a25ns_DMJetsMonotop_S4_Mchi-500_13TeV-madgraph-pythia8_mc.root");
    // samplev.push_back(new CSample("Mres-900_Mchi-100", kMagenta, kMagenta));
    // samplev.back()->fnamev.push_back("../razorbits/Spring15_a25ns_DMJetsMonotop_S1_Mres-900_Mchi-100_13TeV-madgraph-pythia8_mc.root");
    // samplev.push_back(new CSample("Mchi-900", kCyan, kCyan));
    // samplev.back()->fnamev.push_back("../razorbits/Spring15_a25ns_DMJetsMonotop_S4_Mchi-900_13TeV-madgraph-pythia8_mc.root");
    // samplev.push_back(new CSample("TTDM", kMagenta - 10, kMagenta - 10));
    // samplev.back()->fnamev.push_back("../razorbits/TTDM.root");  
  }

  // integrated luminosity to scale MC
  const double LUMI = 2.32;
  
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
  vector<TH1D*> hTransverseMassv;
  vector<TH1D*> hFatJetMassv, hFatJetPtv, hFatJetTau32v, hBtagv;
  vector<TH1D*> hMinDPhiJetsMetv, hMinDPhiFatJetMetv, hNJetsv, hNBJetsv;
  vector<TH1D*> hJet1CHFv, hJet1NHFv, hJet1NEMFv;
  vector<TH1D*> hJet1Etav, hJet2Etav, hJet3Etav, hJet4Etav;
  vector<double> neventsv;
  const Int_t NBINS = 5;
  Double_t edges[NBINS + 1] = {250,300,350,400,500,1000};
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    sprintf(hname,"hMET_%i",isam);            hMETv.push_back(new TH1D(hname,"",NBINS,edges));            hMETv[isam]->Sumw2();
    sprintf(hname,"hMETLog_%i",isam);         hMETLogv.push_back(new TH1D(hname,"",NBINS,edges));         hMETLogv[isam]->Sumw2();
    sprintf(hname,"hFatJetMass_%i",isam);     hFatJetMassv.push_back(new TH1D(hname,"",20,0,300));        hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetPt_%i",isam);       hFatJetPtv.push_back(new TH1D(hname,"",20,250,1000));       hFatJetPtv[isam]->Sumw2();
    sprintf(hname,"hTransverseMass_%i",isam); hTransverseMassv.push_back(new TH1D(hname,"",30,300,2000)); hTransverseMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetTau32_%i",isam);    hFatJetTau32v.push_back(new TH1D(hname,"",15,0.2,1));       hFatJetTau32v[isam]->Sumw2();
    sprintf(hname,"hBtag_%i",isam);           hBtagv.push_back(new TH1D(hname,"",15,0.1,1.));             hBtagv[isam]->Sumw2();
    sprintf(hname,"hMinDPhiJetsMet_%i",isam); hMinDPhiJetsMetv.push_back(new TH1D(hname,"",20,0,3.14));   hMinDPhiJetsMetv[isam]->Sumw2();
    sprintf(hname,"hNJets_%i",isam);          hNJetsv.push_back(new TH1D(hname,"",10,0,10));              hNJetsv[isam]->Sumw2();
    sprintf(hname,"hNBJets_%i",isam);         hNBJetsv.push_back(new TH1D(hname,"",10,0,10));             hNBJetsv[isam]->Sumw2();
    sprintf(hname,"hJet1CHF_%i",isam);        hJet1CHFv.push_back(new TH1D(hname,"",30,0,1));             hJet1CHFv[isam]->Sumw2();
    sprintf(hname,"hJet1NHF_%i",isam);        hJet1NHFv.push_back(new TH1D(hname,"",30,0,1));             hJet1NHFv[isam]->Sumw2();
    sprintf(hname,"hJet1NEMF_%i",isam);       hJet1NEMFv.push_back(new TH1D(hname,"",30,0,1));            hJet1NEMFv[isam]->Sumw2();
    sprintf(hname,"hJet1Eta_%i",isam);        hJet1Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));        hJet1Etav[isam]->Sumw2();
    sprintf(hname,"hJet2Eta_%i",isam);        hJet2Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));        hJet2Etav[isam]->Sumw2();
    sprintf(hname,"hJet3Eta_%i",isam);        hJet3Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));        hJet3Etav[isam]->Sumw2();
    sprintf(hname,"hJet4Eta_%i",isam);        hJet4Etav.push_back(new TH1D(hname,"",30,-4.5,4.5));        hJet4Etav[isam]->Sumw2();
    neventsv.push_back(0);
  }

  TH1D *hMETMC             = (TH1D*)hMETv[0]->Clone("hMETMC");
  TH1D *hMETLogMC          = (TH1D*)hMETLogv[0]->Clone("hMETLogMC");
  TH1D *hFatJetMassMC      = (TH1D*)hFatJetMassv[0]->Clone("hFatJetMassMC");
  TH1D *hFatJetPtMC        = (TH1D*)hFatJetPtv[0]->Clone("hFatJetPtMC");
  TH1D *hTransverseMassMC  = (TH1D*)hTransverseMassv[0]->Clone("hTransverseMassMC");
  TH1D *hFatJetTau32MC     = (TH1D*)hFatJetTau32v[0]->Clone("hFatJetTau32MC");
  TH1D *hBtagMC            = (TH1D*)hBtagv[0]->Clone("hBtagMC");
  TH1D *hMinDPhiJetsMetMC  = (TH1D*)hMinDPhiJetsMetv[0]->Clone("hMinDPhiJetsMetMC");
  TH1D *hNJetsMC           = (TH1D*)hNJetsv[0]->Clone("hNJetsMC");
  TH1D *hNBJetsMC          = (TH1D*)hNBJetsv[0]->Clone("hNBJetsMC");
  TH1D *hJet1CHFMC         = (TH1D*)hJet1CHFv[0]->Clone("hJet1CHFMC");
  TH1D *hJet1NHFMC         = (TH1D*)hJet1NHFv[0]->Clone("hJet1NHFMC");
  TH1D *hJet1NEMFMC        = (TH1D*)hJet1NEMFv[0]->Clone("hJet1NEMFMC");
  TH1D *hJet1EtaMC         = (TH1D*)hJet1Etav[0]->Clone("hJet1EtaMC");
  TH1D *hJet2EtaMC         = (TH1D*)hJet2Etav[0]->Clone("hJet2EtaMC");
  TH1D *hJet3EtaMC         = (TH1D*)hJet3Etav[0]->Clone("hJet3EtaMC");
  TH1D *hJet4EtaMC         = (TH1D*)hJet4Etav[0]->Clone("hJet4EtaMC");
  TH1D *hMETSig1           = (TH1D*)hMETv[0]->Clone("hMETSig1");
  TH1D *hMETSig2           = (TH1D*)hMETv[0]->Clone("hMETSig2");
  // TH1D *hMETSig3           = (TH1D*)hMETv[0]->Clone("hMETSig3");
  // TH1D *hMETSig4           = (TH1D*)hMETv[0]->Clone("hMETSig4");                                                                                                                                                 
  // TH1D *hMETSig5           = (TH1D*)hMETv[0]->Clone("hMETSig5");                                                                                                                                      
  // TH1D *hMETSig6           = (TH1D*)hMETv[0]->Clone("hMETSig6"); 

  double neventsMC = 0;

  TFile *infile=0;
  TTree *intree=0;

  // Loop over samples

  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    CSample *sample = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData    = (isam==0);
    bool isSignal  = (isam==samplev.size()-1 || isam==samplev.size()-2);
    bool isSignal1 = (isam==samplev.size()-1);
    bool isSignal2 = (isam==samplev.size()-2);
    // bool isSignal3 = (isam==samplev.size()-3);
    // bool isSignal4 = (isam==samplev.size()-4);
    // bool isSignal5 = (isam==samplev.size()-5);
    // bool isSignal6 = (isam==samplev.size()-6);
 
    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      intree = (TTree*)infile->Get("Events"); assert(intree);
      fBits  = new RazorBitsLoader(intree,algo,syst,preselection);
      double nevts=0;
      int noweight=0;

      std::cout << intree->GetEntries() << std::endl;
      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
        intree->GetEntry(ientry);
	// if(!doBlind && subsample.compare("SR")==0 && ientry % 5 != 0) continue;
	if(!fBits->selectJetAlgoAndSize(selection,algo)) continue;
	// common selection
	if(fBits->metfilter!=0)                   continue;
	//preselection
	if(!fBits->passPreSelection(preselection)) continue;
	
	//selection
	float btagw=1;
	if(!fBits->passSelection(preselection,selection,subsample,combo,btagw)) continue;

        double wgt = 1;
	if(!isData) {
	  wgt *= LUMI*fBits->scale1fb*fBits->kfactor*btagw*fBits->triggerEff*fBits->evtWeight*fBits->eleSF0*fBits->eleSF1*fBits->eleSF2*fBits->muoSF0*fBits->muoSF1*fBits->muoSF2;
	  if(sample->label=="t#bar{t}" && ifile==0 && fBits->topSize<0.8 && fBits->isHadronicTop==1){
	     wgt *= fBits->ToptagSF;
	  }
	  if(sample->label!="t#bar{t}" || ifile!=0 || fBits->isHadronicTop==0 || fBits->topSize>=0.8){
	     wgt *= fBits->TopmistagSF;
	  }

	  // if(sample->label=="t#bar{t} merged" && ifile==0 && fBits->topSize<1.2){ 
	  //   wgt *= fBits->ToptagSF;
	  // }
	  // if(sample->label=="t#bar{t} merged" && ifile==0 && fBits->topSize>=1.2){                                                                                                                 
	  //   wgt *= 0;                                                                                                                                                                             
	  // }                                                                                                                                                                                        
	  // if(sample->label=="t#bar{t} comb." && ifile==0 && fBits->topSize<1.2){                                                                                                      
	  //   wgt *= 0;                                                                                                                                                                         
	  // }   
	  // if(sample->label!="t#bar{t} merged" || ifile!=0 || fBits->topSize>=1.2){
	  //   wgt *= fBits->TopmistagSF;
	  // }
	  
	  if(sample->label=="W+jets" || sample->label=="Z+jets" || sample->label=="#gamma+jets"){
	    if(subsample=="SR" || subsample=="TopCR" || subsample=="minusMass" || subsample=="minusTau32"){
	      if(ifile==0 || ifile==2) {
		wgt *= fBits->btagSF;
	      }
	      if(ifile==1 || ifile==3) {
		wgt *= fBits->bmistagSF;
	      }
	    }
	  }
	}
	//else{
	//  std::cout << fBits->min_dphijetsmet << " " << fBits->evtNum << " " << fBits->vmetpt << " " << " " << fBits->vmetphi << " " << fBits->vfakemetpt << " " << fBits->vfakemetphi << " " << fBits->njets << std::endl;
	//}
	nevts += wgt;
	noweight++;
	
        neventsv[isam]+=wgt;
        hMETv[isam]            ->Fill(fBits->getMET(preselection).Pt(),       wgt);
        hMETLogv[isam]         ->Fill(fBits->getMET(preselection).Pt(),       wgt);
	hFatJetMassv[isam]     ->Fill(fBits->fjet_mass(selection),       wgt);
	hFatJetPtv[isam]       ->Fill(fBits->bst_jet0_pt,       wgt);
	hTransverseMassv[isam] ->Fill(fBits->transverse_mass(selection),       wgt);
	hFatJetTau32v[isam]    ->Fill(fBits->nsubjet(selection),       wgt);
        hBtagv[isam]           ->Fill(fBits->btag(selection),       wgt);
	hMinDPhiJetsMetv[isam] ->Fill(fBits->min_dphijetsmet,       wgt);
        hNJetsv[isam]          ->Fill(fBits->njets,       wgt);
        hNBJetsv[isam]         ->Fill(fBits->nbjetsLdR2,       wgt);
	hJet1CHFv[isam]        ->Fill(fBits->chf(selection),       wgt);
        hJet1NHFv[isam]        ->Fill(fBits->nhf(selection),       wgt);
        hJet1NEMFv[isam]       ->Fill(fBits->nemf(selection),       wgt);
	hJet1Etav[isam]        ->Fill(fBits->res_jet0_eta, wgt);
	hJet2Etav[isam]        ->Fill(fBits->res_jet1_eta, wgt);
	hJet3Etav[isam]        ->Fill(fBits->res_jet2_eta, wgt);
	hJet4Etav[isam]        ->Fill(fBits->res_jet3_eta, wgt);

	if((!isData && subsample.compare("SR")!=0) || (!isData  && !isSignal && subsample.compare("SR")==0)){ // && !isSignal
          neventsMC+=wgt;
          hMETMC            ->Fill(fBits->getMET(preselection).Pt(),       wgt);
          hMETLogMC         ->Fill(fBits->getMET(preselection).Pt(),       wgt);
	  hFatJetMassMC     ->Fill(fBits->fjet_mass(selection),       wgt);
	  hFatJetPtMC       ->Fill(fBits->bst_jet0_pt,       wgt);
	  hTransverseMassMC ->Fill(fBits->transverse_mass(selection),       wgt);
	  hFatJetTau32MC    ->Fill(fBits->nsubjet(selection),       wgt);
	  hBtagMC           ->Fill(fBits->btag(selection),       wgt);
	  hMinDPhiJetsMetMC ->Fill(fBits->min_dphijetsmet,       wgt);
	  hNJetsMC          ->Fill(fBits->njets,       wgt);
          hNBJetsMC         ->Fill(fBits->nbjetsLdR2,       wgt);
	  hJet1CHFMC        ->Fill(fBits->chf(selection),       wgt);
	  hJet1NHFMC        ->Fill(fBits->nhf(selection),       wgt);
	  hJet1NEMFMC       ->Fill(fBits->nemf(selection),       wgt);
	  hJet1EtaMC        ->Fill(fBits->res_jet0_eta, wgt);
	  hJet2EtaMC        ->Fill(fBits->res_jet1_eta, wgt);
	  hJet3EtaMC        ->Fill(fBits->res_jet2_eta, wgt);
	  hJet4EtaMC        ->Fill(fBits->res_jet3_eta, wgt);
        }
	if(!isData){
	  if(isSignal1) hMETSig1->Fill(fBits->getMET(preselection).Pt(),       wgt);
	  if(isSignal2) hMETSig2->Fill(fBits->getMET(preselection).Pt(),       wgt);
	  // if(isSignal3) hMETSig3->Fill(fBits->getMET(preselection).Pt(),       wgt);
	  // if(isSignal4) hMETSig4->Fill(fBits->getMET(preselection).Pt(),       wgt);
	  // if(isSignal5) hMETSig5->Fill(fBits->getMET(preselection).Pt(),       wgt);
          // if(isSignal6) hMETSig6->Fill(fBits->getMET(preselection).Pt(),       wgt);
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
  TH1D *hMETPull            = makePullHist(hMETv[0],            hMETMC,            "hMETPull",             doBlind);
  TH1D *hMETLogPull         = makePullHist(hMETLogv[0],         hMETLogMC,         "hMETLogPull",          doBlind);
  TH1D *hFatJetMassPull     = makePullHist(hFatJetMassv[0],     hFatJetMassMC,     "hFatJetMassPull",      doBlind);
  TH1D *hFatJetPtPull       = makePullHist(hFatJetPtv[0],       hFatJetPtMC,       "hFatJetPtPull",        doBlind);
  TH1D *hTransverseMassPull = makePullHist(hTransverseMassv[0], hTransverseMassMC, "hTransverseMassPull",  doBlind);
  TH1D *hFatJetTau32Pull    = makePullHist(hFatJetTau32v[0],    hFatJetTau32MC,    "hFatJetTau32Pull",     doBlind);
  TH1D *hBtagPull           = makePullHist(hBtagv[0],           hBtagMC,           "hBtagPull",            doBlind);
  TH1D *hMinDPhiJetsMetPull = makePullHist(hMinDPhiJetsMetv[0], hMinDPhiJetsMetMC, "hMinDPhiJetsMetPull",  doBlind);
  TH1D *hNJetsPull          = makePullHist(hNJetsv[0],          hNJetsMC,          "hNJetsPull",           doBlind);
  TH1D *hNBJetsPull         = makePullHist(hNBJetsv[0],         hNBJetsMC,         "hNBJetsPull",          doBlind);
  TH1D *hJet1CHFPull        = makePullHist(hJet1CHFv[0],        hJet1CHFMC,        "hJet1CHFPull",         doBlind);
  TH1D *hJet1NHFPull        = makePullHist(hJet1NHFv[0],        hJet1NHFMC,        "hJet1NHFPull",         doBlind);
  TH1D *hJet1NEMFPull       = makePullHist(hJet1NEMFv[0],       hJet1NEMFMC,       "hJet1NEMFPull",        doBlind);
  TH1D *hJet1EtaPull        = makePullHist(hJet1Etav[0],        hJet1EtaMC,        "hJet1EtaPull",         doBlind);
  TH1D *hJet2EtaPull        = makePullHist(hJet2Etav[0],        hJet2EtaMC,        "hJet2EtaPull",         doBlind);
  TH1D *hJet3EtaPull        = makePullHist(hJet3Etav[0],        hJet3EtaMC,        "hJet3EtaPull",         doBlind);
  TH1D *hJet4EtaPull        = makePullHist(hJet4Etav[0],        hJet4EtaMC,        "hJet4EtaPull",         doBlind);

  //                                                                                                                                                                                                    
  // Calculate significance                                                                                                                                                                               
  //                 
  vector<float> significance;                                                                                                                                                                                
  significance.push_back(CalcSig(hMETSig1, hMETMC));
  significance.push_back(CalcSig(hMETSig2, hMETMC));
  // significance.push_back(CalcSig(hMETSig3, hMETMC));
  // significance.push_back(CalcSig(hMETSig4, hMETMC));
  // significance.push_back(CalcSig(hMETSig5, hMETMC));
  // significance.push_back(CalcSig(hMETSig6, hMETMC));

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
  txtfile << setprecision(2) << fixed;
  float max = samplev.size();
  if (subsample.compare("SR")==0) max = samplev.size()-2;    
  for(unsigned int isam=1; isam<max; isam++) {
    txtfile << setw(35) << samplev[isam]->label;
    txtfile << setw(15) << neventsv[isam] << endl;
  }
  txtfile << "---------------------------------------------"  << endl;
  txtfile << setw(35) << "SM Expected:" << setw(15) << neventsMC << endl;
  if(!doBlind) { txtfile << setw(35) << "Observed:" << setw(15) << neventsv[0] << endl; }
  if(subsample.compare("SR")==0){
    txtfile << "---------------------------------------------"  << endl;
    for(unsigned int isam=max; isam<samplev.size(); isam++) {
      txtfile << setw(35) << samplev[isam]->label;
      txtfile << setw(15) << neventsv[isam] << endl;
      txtfile << setw(35) << "Significance: ";
      txtfile << setw(15) << significance[samplev.size()-isam-1] << endl;
    }
  }
  //   txtfile << setw(35) << "S/sqrt(B)["+samplev[isam]->label+"]:" << setw(15) << neventsv[isam]/sqrt(neventsMC) << endl;
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

  // c->SetTopMargin(0.1);
  // c->SetBottomMargin(0.15);
  // c->SetLeftMargin(0.15);
  // c->SetRightMargin(0.07);
  // c->SetTickx(1);
  // c->SetTicky(1);

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

  sprintf(ylabel,"Events / %.1f GeV/c^{2}",hFatJetPtv[0]->GetBinWidth(1));
  makePlot(c, "fjpt", "Jet p_{T} [GeV/c^{2}]", ylabel, hFatJetPtv, samplev, hFatJetPtMC, hFatJetPtPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetPtMC->GetBinContent(hFatJetPtMC->GetMaximumBin()))/(hFatJetPtMC->GetBinWidth(hFatJetPtMC->GetMaximumBin())), selection, subsample);

  // sprintf(ylabel,"Events / %.1f GeV/c^{2}",hTransverseMassv[0]->GetBinWidth(1));
  // makePlot(c, "mt", "Transverse Mass [GeV/c^{2}]", ylabel, hTransverseMassv, samplev, hTransverseMassMC, hTransverseMassPull, doBlind, LUMI, false, 0.0, -0.03,
  //         0.1, 2.1*(hTransverseMassMC->GetBinContent(hTransverseMassMC->GetMaximumBin()))/(hTransverseMassMC->GetBinWidth(hTransverseMassMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hFatJetTau32v[0]->GetBinWidth(10));
  makePlot(c, "tau32", "#tau_{3}/#tau_{2}", ylabel, hFatJetTau32v, samplev, hFatJetTau32MC, hFatJetTau32Pull, doBlind, LUMI, false, -0.45, -0.03,
           0.1, 2.1*(hFatJetTau32MC->GetBinContent(hFatJetTau32MC->GetMaximumBin()))/(hFatJetTau32MC->GetBinWidth(hFatJetTau32MC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hBtagv[0]->GetBinWidth(10));
  makePlot(c, "btag", "Max subjet csv", ylabel, hBtagv, samplev, hBtagMC, hBtagPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hBtagMC->GetBinContent(hBtagMC->GetMaximumBin()))/(hBtagMC->GetBinWidth(hBtagMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hMinDPhiJetsMetv[0]->GetBinWidth(1));
  makePlot(c, "min_dphijetsmet", "Min #Delta#phi(MET,j_{i})", ylabel, hMinDPhiJetsMetv, samplev, hMinDPhiJetsMetMC, hMinDPhiJetsMetPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hMinDPhiJetsMetMC->GetBinContent(hMinDPhiJetsMetMC->GetMaximumBin()))/(hMinDPhiJetsMetMC->GetBinWidth(hMinDPhiJetsMetMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %i ",int(hNJetsv[0]->GetBinWidth(1)));
  makePlot(c, "njets", "N_{jets} (AK4)", "Events", hNJetsv, samplev, hNJetsMC, hNJetsPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hNJetsMC->GetBinContent(hNJetsMC->GetMaximumBin()))/(hNJetsMC->GetBinWidth(hNJetsMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %i ",int(hNBJetsv[0]->GetBinWidth(1)));
  makePlot(c, "nbjets", "N^{#Delta R(j,J)>2}_{b-jets} (AK4)", "Events", hNBJetsv, samplev, hNBJetsMC, hNBJetsPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hNBJetsMC->GetBinContent(hNBJetsMC->GetMaximumBin()))/(hNBJetsMC->GetBinWidth(hNBJetsMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hJet1CHFv[0]->GetBinWidth(1));
  makePlot(c, "chf", "CHF", "Events", hJet1CHFv, samplev, hJet1CHFMC, hJet1CHFPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-4*(hJet1CHFMC->GetBinContent(hJet1CHFMC->GetMaximumBin()))/(hJet1CHFMC->GetBinWidth(hJet1CHFMC->GetMaximumBin())), 
	   2e3*(hJet1CHFMC->GetBinContent(hJet1CHFMC->GetMaximumBin()))/(hJet1CHFMC->GetBinWidth(hJet1CHFMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hJet1NHFv[0]->GetBinWidth(1));
  makePlot(c, "nhf", "NHF", "Events", hJet1NHFv, samplev, hJet1NHFMC, hJet1NHFPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-4*(hJet1NHFMC->GetBinContent(hJet1NHFMC->GetMaximumBin()))/(hJet1NHFMC->GetBinWidth(hJet1NHFMC->GetMaximumBin())), 
	   2e3*(hJet1NHFMC->GetBinContent(hJet1NHFMC->GetMaximumBin()))/(hJet1NHFMC->GetBinWidth(hJet1NHFMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f ",hJet1NEMFv[0]->GetBinWidth(1));
  makePlot(c, "nemf", "NEMF", "Events", hJet1NEMFv, samplev, hJet1NEMFMC, hJet1NEMFPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-4*(hJet1NEMFMC->GetBinContent(hJet1NEMFMC->GetMaximumBin()))/(hJet1NEMFMC->GetBinWidth(hJet1NEMFMC->GetMaximumBin())), 
	   2e3*(hJet1NEMFMC->GetBinContent(hJet1NEMFMC->GetMaximumBin()))/(hJet1NEMFMC->GetBinWidth(hJet1NEMFMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f",hJet1Etav[0]->GetBinWidth(1));
  makePlot(c, "jet1eta", "jet1 #eta", ylabel, hJet1Etav, samplev, hJet1EtaMC, hJet1EtaPull, doBlind, LUMI, false, 0.05, -0.03,
           0.1, 1.6*(hJet1EtaMC->GetBinContent(hJet1EtaMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f",hJet2Etav[0]->GetBinWidth(1));
  makePlot(c, "jet2eta", "jet2 #eta", ylabel, hJet2Etav, samplev, hJet2EtaMC, hJet2EtaPull, doBlind, LUMI, false, 0.05, -0.03,
           0.1, 1.6*(hJet2EtaMC->GetBinContent(hJet2EtaMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f",hJet3Etav[0]->GetBinWidth(1));
  makePlot(c, "jet3eta", "jet3 #eta", ylabel, hJet3Etav, samplev, hJet3EtaMC, hJet3EtaPull, doBlind, LUMI, false, 0.05, -0.03,
           0.1, 1.6*(hJet3EtaMC->GetBinContent(hJet3EtaMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %.1f",hJet4Etav[0]->GetBinWidth(1));
  makePlot(c, "jet4eta", "jets #eta", ylabel, hJet4Etav, samplev, hJet4EtaMC, hJet4EtaPull, doBlind, LUMI, false, 0.05, -0.03,
           0.1, 1.6*(hJet4EtaMC->GetBinContent(hJet4EtaMC->GetMaximumBin())), selection, subsample);

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
  if (subsample.compare("SR")==0) max = samplev.size()-2; 
  for(unsigned int i=1; i<max; i++) {
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }

  if (subsample.compare("SR")==0){
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
  // const double xmin = histv[0]->GetXaxis()->GetBinLowEdge(1);
  // const double xmax = histv[0]->GetXaxis()->GetBinUpEdge(histv[0]->GetNbinsX());
  // plot.AddLine(xmin,0,xmax,0,kBlack,3);

  plot.TransLegend(legdx, legdy);
  
  if(doLogy) {
    plot.SetLogy();
  }
  
  if(ymin!=ymax) {
    plot.SetYRange(ymin,ymax);
  }

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
  CPlot plotPull(outname.c_str(),"",xlabel.c_str(),"Pull");
  plotPull.AddHist1D(hExpPull,"E2",uncColor,1,3004);
  plotPull.AddHist1D(hPull,"EX0",kBlack);
  plotPull.SetYRange(0.,2.);
  plotPull.AddLine(xmin,1,xmax,1,kBlack,3);

  plot.Draw(c,false,"png",1);
  plot.Draw(c,false,"pdf",1);
  plotPull.Draw(c,true,"png",2);
  plotPull.Draw(c,true,"pdf",2);
}

//--------------------------------------------------------------------------------------------------
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind)
{
  const Int_t NBINS = 5;
  Double_t edges[NBINS + 1] = {250,300,350,400,500,1000};
  TH1D *hPull = new TH1D(name.c_str(),"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  if (name=="hMETPull" || name=="hMETLogPull")
    hPull = new TH1D(name.c_str(),"",NBINS,edges);
  for(int ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    // double numer = hData->GetBinContent(ibin) - hMC->GetBinContent(ibin);
    // double denom = sqrt((hData->GetBinError(ibin))*(hData->GetBinError(ibin)) + (hMC->GetBinError(ibin))*(hMC->GetBinError(ibin)));
    // double pull  = (denom>0) ? numer/denom : 0;
    // double err   = (denom>0) ? 1 : 0;

    double numer = hData->GetBinContent(ibin);
    double denom = hMC->GetBinContent(ibin);
    double pull  = (denom>0) ? numer/denom : 0;
    double err   = (denom>0) ? sqrt(hData->GetBinContent(ibin))/hMC->GetBinContent(ibin): 0;
    
    if(doBlind) {
      pull = 0;
      err  = 1;
    }

    hPull->SetBinContent(ibin,pull);
    hPull->SetBinError(ibin,err);
  }
  hPull->GetYaxis()->SetTitleOffset(0.42);
  hPull->GetYaxis()->SetTitleSize(0.13);
  hPull->GetYaxis()->SetLabelSize(0.10);
  hPull->GetYaxis()->SetNdivisions(104);
  hPull->GetYaxis()->CenterTitle();
  hPull->GetXaxis()->SetTitleOffset(1.2);
  hPull->GetXaxis()->SetTitleSize(0.13);
  hPull->GetXaxis()->SetLabelSize(0.12);
  //hPull->GetXaxis()->CenterTitle();

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
