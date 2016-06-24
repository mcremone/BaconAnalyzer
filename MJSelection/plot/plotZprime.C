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

#include "/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/macros/CPlot.hh"         // helper class for plots
#include "/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/macros/KStyle.hh"        // style settings for drawing
#include "/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/macros/CSample.hh"       // helper class to manage samples
#include "/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/macros/ZprimeBitsLoader.hh"    // helper to load baconbits
//#endif

using namespace std;

//Object Processors                                                                                                                                                                                      
ZprimeBitsLoader       *fBits      = 0;

//=== FUNCTION DECLARATIONS ======================================================================================

// make "standard" plot
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy=false, const double legdx=0, const double legdy=0,
              const double ymin=-1, const double ymax=-1, const string selection="");
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind);
float CalcSig1(TH1D*sig1, TH1D*bkg1);
float CalcSig2(TH1D*sig2, TH1D*bkg2);
float CalcSig3(TH1D*sig3, TH1D*bkg3);
float CalcSig4(TH1D*sig, TH1D*bkg4);
//=== MAIN MACRO =================================================================================================

void plotZprime(const string selection, const string algo, const string jet, float cut, float csv)
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  const bool doBlind = false;

  // Create output directory 
  const string outputDir("ZprimePlots/"+selection+"_"+algo+"_"+jet);
  gSystem->mkdir(outputDir.c_str(), true);
  CPlot::sOutDir = outputDir;

  //
  // Samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;

  samplev.push_back(new CSample("data",0,0));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/JetHT.root");
  samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/QCD.root");
  samplev.push_back(new CSample("W+jets",kGreen - 10,kGreen - 10));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/Wcs.root");
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/Wlf.root");
  samplev.push_back(new CSample("Zlf", kCyan - 9, kCyan - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/DYlf.root");
  samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/T.root");
  samplev.push_back(new CSample("t#bar{t}",kOrange - 3,kOrange - 3));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/TT.root");
  samplev.push_back(new CSample("Diboson",kYellow - 9,kYellow - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/WW.root");
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/WZ.root");
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZZ.root");
  samplev.push_back(new CSample("Zbbcc", kCyan - 9, kCyan - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/DYbb.root");
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/DYcc.root");


  vector<string> mass;
  mass.push_back("50");
  mass.push_back("100");
  mass.push_back("150");
  mass.push_back("200");
  mass.push_back("250");
  mass.push_back("300");
  vector<string> vmass;
  vmass.push_back("10");
  vmass.push_back("25");
  vmass.push_back("50");
  vmass.push_back("75");
  vmass.push_back("100");
  vmass.push_back("125");
  vmass.push_back("150");
  vmass.push_back("200");
  vmass.push_back("250");
  vmass.push_back("300");
  vector<string> type;
  type.push_back("lf");
  type.push_back("cc");
  type.push_back("bb");

  for(int j=0;j<6;j++){
     for(int k=0;k<3;k++){

       samplev.push_back(new CSample("Zprime"+mass[j]+type[k],kRed,kRed));
       samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/Zprime"+mass[j]+type[k]+".root");

     }
  }

  for(int h=0;h<10;h++){
       samplev.push_back(new CSample("VectorDiJet"+vmass[h],kPink,kPink));
       samplev.back()->fnamev.push_back("/afs/cern.ch/work/r/rapte/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/VectorDiJet"+vmass[h]+".root");

  }


  /*
  samplev.push_back(new CSample("M_{Z'}=50 GeV",2,2));
  samplev.back()->fnamev.push_back("../zprimebits/VectorDiJet1Jet_M50_mc.root");
  samplev.push_back(new CSample("M_{Z'}=100 GeV",4,4));
  samplev.back()->fnamev.push_back("../zprimebits/VectorDiJet1Jet_M100_mc.root");
  samplev.push_back(new CSample("M_{Z'}=150 GeV",6,6));
  samplev.back()->fnamev.push_back("../zprimebits/VectorDiJet1Jet_M150_mc.root");
  samplev.push_back(new CSample("M_{Z'}=200 GeV",7,7));
  samplev.back()->fnamev.push_back("../zprimebits/VectorDiJet1Jet_M200_mc.root");
  samplev.push_back(new CSample("M_{Z'}=250 GeV",8,8));
  samplev.back()->fnamev.push_back("../zprimebits/VectorDiJet1Jet_M250_mc.root");
  samplev.push_back(new CSample("M_{Z'}=300 GeV",3,3));
  samplev.back()->fnamev.push_back("../zprimebits/VectorDiJet1Jet_M300_mc.root");
  */

  // integrated luminosity to scale MC
  const double LUMI = 0.44;
  //const double LUMI = 2.32;

  // histograms for various corrections
  const string cmssw_base = getenv("CMSSW_BASE");

  //--------------------------------------------------------------------------------------------------------------
  // Main analysis code
  //==============================================================================================================

  //
  // Declare histograms
  //
  char hname[100];
  vector<TH1D*> hFatJetPtv, hFatJetPtLogv, hFatJetEtav;
  vector<TH1D*> hFatJetMassv, hFatJetTau21v, hFatJetTau21DDTv, hFatJetRhoDDTv, hFatJetRhoDDTlv, hFatJetMassNew;              
  vector<TH1D*> hSubjetBtagv, hFatjetBtagv;  
  vector<double> neventsv;
  
  for(unsigned int isam=0; isam<8; isam++) {
    sprintf(hname,"hFatJetPt_%i",isam);       hFatJetPtv.push_back(new TH1D(hname,"",40,500,2000));        hFatJetPtv[isam]->Sumw2();
    sprintf(hname,"hFatJetPtLog_%i",isam);    hFatJetPtLogv.push_back(new TH1D(hname,"",40,500,2000));     hFatJetPtLogv[isam]->Sumw2();
    sprintf(hname,"hFatJetEta_%i",isam);      hFatJetEtav.push_back(new TH1D(hname,"",30,-4.5,4.5));       hFatJetEtav[isam]->Sumw2();
    sprintf(hname,"hFatJetMass_%i",isam);     hFatJetMassv.push_back(new TH1D(hname,"",40,0,400));         hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetMassNew_%i",isam);  hFatJetMassNew.push_back(new TH1D(hname,"",10,60,120));      hFatJetMassNew[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21_%i",isam);    hFatJetTau21v.push_back(new TH1D(hname,"",25,0,1));        hFatJetTau21v[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21DDT_%i",isam); hFatJetTau21DDTv.push_back(new TH1D(hname,"",25,0,1));     hFatJetTau21DDTv[isam]->Sumw2();
    sprintf(hname,"hFatJetRhoDDT_%i",isam);   hFatJetRhoDDTv.push_back(new TH1D(hname,"",25,-1,6));     hFatJetRhoDDTv[isam]->Sumw2();
    sprintf(hname,"hFatJetRhoDDTl_%i",isam);   hFatJetRhoDDTlv.push_back(new TH1D(hname,"",25,-1,6));     hFatJetRhoDDTlv[isam]->Sumw2();
    sprintf(hname,"hSubjetBtag_%i",isam);     hSubjetBtagv.push_back(new TH1D(hname,"",25,0,1));           hSubjetBtagv[isam]->Sumw2();
    sprintf(hname,"hFatjetBtag_%i",isam);     hFatjetBtagv.push_back(new TH1D(hname,"",50,-1,1));           hFatjetBtagv[isam]->Sumw2();
    neventsv.push_back(0);
  }

  TH1D *hFatJetPtMC        = (TH1D*)hFatJetPtv[0]      ->Clone("hFatJetPtMC");
  TH1D *hFatJetPtLogMC     = (TH1D*)hFatJetPtLogv[0]   ->Clone("hFatJetPtLogMC");
  TH1D *hFatJetEtaMC       = (TH1D*)hFatJetEtav[0]     ->Clone("hFatJetEtaMC");
  TH1D *hFatJetMassMC      = (TH1D*)hFatJetMassv[0]    ->Clone("hFatJetMassMC");
  TH1D *hFatJetMassNewMC   = (TH1D*)hFatJetMassNew[0]  ->Clone("hFatJetMassNewMC");
  TH1D *hFatJetTau21MC     = (TH1D*)hFatJetTau21v[0]   ->Clone("hFatJetTau21MC");
  TH1D *hFatJetTau21DDTMC  = (TH1D*)hFatJetTau21DDTv[0]->Clone("hFatJetTau21DDTMC");
  TH1D *hFatJetRhoDDTMC    = (TH1D*)hFatJetRhoDDTv[0]  ->Clone("hFatJetRhoDDTMC");
  TH1D *hFatJetRhoDDTlMC    = (TH1D*)hFatJetRhoDDTlv[0]  ->Clone("hFatJetRhoDDTlMC");
  TH1D *hSubjetBtagMC      = (TH1D*)hSubjetBtagv[0]    ->Clone("hSubjetBtagMC"); 
  TH1D *hFatJetMassSig     = (TH1D*)hFatJetMassv[0]    ->Clone("hFatJetMassSig");
  TH1D *hFatjetBtagMC      = (TH1D*)hFatjetBtagv[0]    ->Clone("hFatjetBtagMC");
  

  double neventsMC;

  TFile *infile=0;
  TTree *intree=0;

  // Loop over samples

  for(unsigned int isam=0; isam<8; isam++) {
    CSample *sample  = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData    = (isam==0);
    /*
    bool isSignal1 = (isam==samplev.size()-1);
    bool isSignal2 = (isam==samplev.size()-2);
    bool isSignal3 = (isam==samplev.size()-3);
    bool isSignal4 = (isam==samplev.size()-4);
    bool isSignal5 = (isam==samplev.size()-5);    
    bool isSignal6 = (isam==samplev.size()-6);  
    */
    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      intree = (TTree*)infile->Get("Events"); assert(intree);

      fBits  = new ZprimeBitsLoader(intree,algo,jet);

      double nevts=0;
      int noweight=0;

      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
      // for(unsigned int ientry=0; ientry<100; ientry++) {
	// Blinding policy: keep just one fifth of the events
	if(!doBlind && isData && ientry % 5 != 0) continue;
        intree->GetEntry(ientry);

	if(!fBits->selectJetAlgoAndSize(algo))   continue;
	if(fBits->metfilter!=0)                  continue;
	if(!fBits->passSelection(selection,cut,csv)) continue;

	// Apply weigths
        double wgt = 1;
	wgt *= fBits->getWgt(isData,algo,LUMI);
	
	nevts += wgt;
	noweight++;
	double bst_jet0_nhan = log(fBits->bst_jet0_msd*fBits->bst_jet0_msd/fBits->bst_jet0_pt); 
        neventsv[isam]+=wgt;
        hFatJetPtv[isam]       ->Fill(fBits->bst_jet0_pt,             wgt);
        hFatJetPtLogv[isam]    ->Fill(fBits->bst_jet0_pt,             wgt);
	hFatJetEtav[isam]      ->Fill(fBits->bst_jet0_eta,            wgt);
	hFatJetMassv[isam]     ->Fill(fBits->bst_jet0_msd,            wgt);
        hFatJetMassNew[isam]   ->Fill(fBits->bst_jet0_msd,            wgt);
	hFatJetTau21v[isam]    ->Fill(fBits->bst_jet0_tau21,          wgt);
        hFatJetTau21DDTv[isam] ->Fill(fBits->tau21DDT(),              wgt);
        hFatJetRhoDDTv[isam]   ->Fill(bst_jet0_nhan,              wgt);
        hFatJetRhoDDTlv[isam]   ->Fill(bst_jet0_nhan,              wgt);
        hSubjetBtagv[isam]     ->Fill(fBits->bst_jet0_minsubcsv,      wgt);
        hFatjetBtagv[isam]     ->Fill(fBits->bst_jet0_doublecsv,      wgt);
        
	//if(isSignal1 || isSignal2 || isSignal3 || isSignal4 || isSignal5 || isSignal6)
	
	if(isam==7){ 
	  hFatJetMassSig         ->Fill(fBits->bst_jet0_msd,            wgt);

        }
	//}
      }

      if(isData && doBlind) {
        cout << endl;
      } else {
        cout << nevts << " " << noweight  <<  " " << fBits->scale1fb << endl;
      }
      delete infile;
      infile=0;
      intree=0;
    }
   
  }


  // 
  // QCD SF
  //
  double QCDSF = 1.0;
  QCDSF = (neventsv[0]-(neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]+neventsv[6]+neventsv[7]))/neventsv[1];
  hFatJetPtv[1]       ->Scale(QCDSF);
  hFatJetPtLogv[1]    ->Scale(QCDSF);
  hFatJetEtav[1]      ->Scale(QCDSF);
  hFatJetMassv[1]     ->Scale(QCDSF);
  hFatJetMassNew[1]   ->Scale(QCDSF);
  hFatJetTau21v[1]    ->Scale(QCDSF);
  hFatJetTau21DDTv[1] ->Scale(QCDSF);
  hFatJetRhoDDTv[1] ->Scale(QCDSF);
  hFatJetRhoDDTlv[1] ->Scale(QCDSF);
  hSubjetBtagv[1]     ->Scale(QCDSF);
  hFatjetBtagv[1]     ->Scale(QCDSF);

  for(unsigned int isam=1; isam<7; isam++) {

    cout << "Adding " << samplev[isam]->label <<" to MC"<<endl;
    hFatJetPtMC       ->Add(hFatJetPtv[isam]);
    hFatJetPtLogMC    ->Add(hFatJetPtLogv[isam]);
    hFatJetEtaMC      ->Add(hFatJetEtav[isam]);
    hFatJetMassMC     ->Add(hFatJetMassv[isam]);
    hFatJetMassNewMC  ->Add(hFatJetMassNew[isam]);
    hFatJetTau21MC    ->Add(hFatJetTau21v[isam]);
    hFatJetTau21DDTMC ->Add(hFatJetTau21DDTv[isam]);
    hFatJetRhoDDTMC ->Add(hFatJetRhoDDTv[isam]);
    hFatJetRhoDDTlMC ->Add(hFatJetRhoDDTlv[isam]);
    hSubjetBtagMC     ->Add(hSubjetBtagv[isam]);
    hFatjetBtagMC     ->Add(hFatjetBtagv[isam]);
  }
  /*
  hFatJetRhoDDTv[7] ->Scale(100);
  hFatJetRhoDDTv[8] ->Scale(100);
  hFatJetRhoDDTv[9] ->Scale(100);
  hFatJetRhoDDTv[10] ->Scale(100);
  hFatJetRhoDDTv[11] ->Scale(100);
  hFatJetRhoDDTv[12] ->Scale(100);
  */
  neventsMC = neventsv[1]*QCDSF+neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]+neventsv[6]+neventsv[7];

  //
  // Make pull histograms
  //
  
  TH1D *hFatJetPtPull       = makePullHist(hFatJetPtv[0],       hFatJetPtMC,       "hFatJetPtPull",        doBlind);
  TH1D *hFatJetPtLogPull    = makePullHist(hFatJetPtLogv[0],    hFatJetPtLogMC,    "hFatJetPtLogPull",     doBlind);
  TH1D *hFatJetEtaPull      = makePullHist(hFatJetEtav[0],      hFatJetEtaMC,      "hFatJetEtaPull",       doBlind);
  TH1D *hFatJetMassPull     = makePullHist(hFatJetMassv[0],     hFatJetMassMC,     "hFatJetMassPull",      doBlind);
  TH1D *hFatJetMassNewPull  = makePullHist(hFatJetMassNew[0],   hFatJetMassNewMC,  "hFatJetMassNewPull",   doBlind);
  TH1D *hFatJetTau21Pull    = makePullHist(hFatJetTau21v[0],    hFatJetTau21MC,    "hFatJetTau21Pull",     doBlind);
  TH1D *hFatJetTau21DDTPull = makePullHist(hFatJetTau21DDTv[0], hFatJetTau21DDTMC, "hFatJetTau21DDTPull",  doBlind);
  TH1D *hFatJetRhoDDTPull   = makePullHist(hFatJetRhoDDTv[0],   hFatJetRhoDDTMC, "hFatJetRhoDDTPull",  doBlind);
  TH1D *hFatJetRhoDDTlPull  = makePullHist(hFatJetRhoDDTlv[0],  hFatJetRhoDDTlMC, "hFatJetRhoDDTlPull",  doBlind);
  TH1D *hBtagPull           = makePullHist(hSubjetBtagv[0],     hSubjetBtagMC,     "hBtagPull",            doBlind);
  
  //                                                                                                                                                                                                    
  // Calculate significance                                                                                                                                                                               
  //                 
  vector<float> significance;                                                                                                                                                                               
 significance.push_back(CalcSig1(hFatJetMassSig,  hFatJetMassMC));
 significance.push_back(CalcSig2(hFatJetMassSig,  hFatJetMassMC));
 significance.push_back(CalcSig3(hFatJetMassSig,  hFatJetMassMC));
 significance.push_back(CalcSig4(hFatJetMassSig,  hFatJetMassMC));
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
  txtfile.open(txtfname,std::ios_base::app);
  txtfile << setprecision(6) << fixed;
  float max = samplev.size();
  for(unsigned int isam=1; isam<8; isam++) {
    txtfile << setw(35) << samplev[isam]->label;
    txtfile << setw(15) << neventsv[isam] << endl;
  }
  txtfile << "---------------------------------------------"  << endl;
  txtfile << setw(35) << "SM Expected:" << setw(15) << neventsMC << endl;
  if(!doBlind) { txtfile << setw(35) << "Observed:" << setw(15) << neventsv[0] << endl; }

  txtfile << "QCD Scale Factor:" << QCDSF << endl;
  //  if(subsample.compare("SR")==0){
  txtfile << "---------------------------------------------"  << endl;
  //for(unsigned int isam=max; isam<samplev.size(); isam++) {
    //txtfile << setw(35) << samplev[isam]->label;
    //txtfile << setw(15) << neventsv[isam] << endl;
    //txtfile << setw(35) << "Significance: ";
    //txtfile << setw(15) << significance[samplev.size()-isam-1] << endl;
  //}
  txtfile << setw(15) << "DDT cut value is : "<< cut << endl;
  txtfile << setw(15) << "csv cut value is : "<< csv << endl;
  txtfile << setw(15) << "Type 1 Significance : "<< significance[0] << endl;
  txtfile << setw(15) << "Type 2 Significance : "<< significance[1] << endl;
  txtfile << setw(15) << "Type 3 Significance : "<< significance[2] << endl;
  txtfile << setw(15) << "Type 4 Significance : "<< significance[3] << endl;
  //  }
  //   txtfile << setw(35) << "S/sqrt(B)["+samplev[isam]->label+"]:" << setw(15) << neventsv[isam]/sqrt(neventsMC) << endl;

  txtfile.close();

   //--------------------------------------------------------------------------------------------------------------
  // Make plots
  //==============================================================================================================
/*
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

  sprintf(ylabel,"Events / %.1f GeV",hFatJetPtv[0]->GetBinWidth(1));
  makePlot(c, "fjpt", "Jet p_{T} [GeV]", ylabel, hFatJetPtv, samplev, hFatJetPtMC, hFatJetPtPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetPtMC->GetBinContent(hFatJetPtMC->GetMaximumBin()))/(hFatJetPtMC->GetBinWidth(hFatJetPtMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f GeV",hFatJetPtLogv[0]->GetBinWidth(1));
  makePlot(c, "fjptl", "Jet p_{T} [GeV/c^{2}]", ylabel, hFatJetPtLogv, samplev, hFatJetPtLogMC, hFatJetPtLogPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-5*(hFatJetPtLogMC->GetBinContent(hFatJetPtLogMC->GetMaximumBin()))/(hFatJetPtLogMC->GetBinWidth(hFatJetPtLogMC->GetMaximumBin())),
           4e2*(hFatJetPtLogMC->GetBinContent(hFatJetPtLogMC->GetMaximumBin()))/(hFatJetPtLogMC->GetBinWidth(hFatJetPtLogMC->GetMaximumBin())), selection);
  
  sprintf(ylabel,"Events /%.1f",hFatJetEtav[0]->GetBinWidth(1));
  makePlot(c, "fjeta", "Jet #eta", ylabel, hFatJetEtav, samplev, hFatJetEtaMC, hFatJetEtaPull, doBlind, LUMI, false, 0.05, -0.03,
           0.1, 3.5*(hFatJetEtaMC->GetBinContent(hFatJetEtaMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "msd", "Soft Drop Mass [GeV]", ylabel, hFatJetMassv, samplev, hFatJetMassMC, hFatJetMassPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
           4e2*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "msdnew", "Soft Drop Mass [GeV]", ylabel, hFatJetMassNew, samplev, hFatJetMassNewMC, hFatJetMassNewPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-5*(hFatJetMassNewMC->GetBinContent(hFatJetMassNewMC->GetMaximumBin()))/(hFatJetMassNewMC->GetBinWidth(hFatJetMassNewMC->GetMaximumBin())),
           4e2*(hFatJetMassNewMC->GetBinContent(hFatJetMassNewMC->GetMaximumBin()))/(hFatJetMassNewMC->GetBinWidth(hFatJetMassNewMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f ",hFatJetTau21v[0]->GetBinWidth(10));
  makePlot(c, "tau21", "#tau_{21}", ylabel, hFatJetTau21v, samplev, hFatJetTau21MC, hFatJetTau21Pull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetTau21MC->GetBinContent(hFatJetTau21MC->GetMaximumBin()))/(hFatJetTau21MC->GetBinWidth(hFatJetTau21MC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f",hFatJetTau21DDTv[0]->GetBinWidth(10));
  makePlot(c, "tau21DDT", "#tau_{21}^{DDT}", ylabel, hFatJetTau21DDTv, samplev, hFatJetTau21DDTMC, hFatJetTau21DDTPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetTau21DDTMC->GetBinContent(hFatJetTau21DDTMC->GetMaximumBin()))/(hFatJetTau21DDTMC->GetBinWidth(hFatJetTau21DDTMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f",hFatJetRhoDDTv[0]->GetBinWidth(10));
  makePlot(c, "rhoDDT", "#rho^{DDT}", ylabel, hFatJetRhoDDTv, samplev, hFatJetRhoDDTMC, hFatJetRhoDDTPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 1.5*(hFatJetRhoDDTMC->GetBinContent(hFatJetRhoDDTMC->GetMaximumBin()))/(hFatJetRhoDDTMC->GetBinWidth(hFatJetRhoDDTMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f",hFatJetRhoDDTlv[0]->GetBinWidth(10));
  makePlot(c, "rhoDDTl", "#rho^{DDT}", ylabel, hFatJetRhoDDTlv, samplev, hFatJetRhoDDTlMC, hFatJetRhoDDTlPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 1.4*(hFatJetRhoDDTlMC->GetBinContent(hFatJetRhoDDTlMC->GetMaximumBin()))/(hFatJetRhoDDTlMC->GetBinWidth(hFatJetRhoDDTlMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f",hSubjetBtagv[0]->GetBinWidth(10));
  makePlot(c, "btag", "Max subjet csv", ylabel, hSubjetBtagv, samplev, hSubjetBtagMC, hBtagPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hSubjetBtagMC->GetBinContent(hSubjetBtagMC->GetMaximumBin()))/(hSubjetBtagMC->GetBinWidth(hSubjetBtagMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f",hFatjetBtagv[0]->GetBinWidth(10));
  makePlot(c, "fjbtag", "Doublecsv", ylabel, hFatjetBtagv, samplev, hFatjetBtagMC, hBtagPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hFatjetBtagMC->GetBinContent(hFatjetBtagMC->GetMaximumBin()))/(hFatjetBtagMC->GetBinWidth(hFatjetBtagMC->GetMaximumBin())), selection);

  cout << endl;
  cout << " <> Output saved in " << outputDir << endl;
  cout << endl;
*/
}

//=== FUNCTION DEFINITIONS ======================================================================================

//--------------------------------------------------------------------------------------------------
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              bool doBlind, const double lumi, const bool doLogy, const double legdx, const double legdy,
              const double ymin, const double ymax, const string selection)
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
  float max = samplev.size();//-6;
  for(unsigned int i=max-1; i>=1; i--) {
  //for(unsigned int i=1; i<max; i++) {
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }
  /*
  for(unsigned int i=max; i<histv.size(); i++) {
    plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
  }
  */
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
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind)
{
  const Int_t NBINS = 5;
  Double_t edges[NBINS + 1] = {250,300,350,400,500,1000};
  TH1D *hPull = new TH1D(name.c_str(),"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  if (name=="hMETPull" || name=="hMETLogPull")
    hPull = new TH1D(name.c_str(),"",NBINS,edges);
  for(int ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    double numer = hData->GetBinContent(ibin);
    double denom = hMC->GetBinContent(ibin);
    double pull  = (denom>0) ? numer/denom : 0;
    double err   = (denom>0) ? sqrt(hData->GetBinContent(ibin))/hMC->GetBinContent(ibin) : 0;

    if(doBlind) {
      pull = 1;
      err  = 1;
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

float CalcSig1(TH1D*sig1, TH1D*bkg1) {
   float f1Sig2 = 0;
   int nb1 = sig1->GetNbinsX();
for (int i = 0; i <= nb1; i++) {
     if (sig1->GetBinContent(i) > 0 && bkg1->GetBinContent(i)>0) {
      f1Sig2 += pow(sig1->GetBinContent(i),2)/(bkg1->GetBinContent(i));
      }
    }

return sqrt(f1Sig2);
 }

float CalcSig2(TH1D*sig2, TH1D*bkg2) {
   float f2Sig2 = 0;
   int nb2 = sig2->GetNbinsX();
   //  std::cout << "nb = " << nb << std::endl;
    for (int i = 0; i <= nb2; i++) {
      if (sig2->GetBinContent(i) > 0 && bkg2->GetBinContent(i)>0) {
        f2Sig2 += pow(sig2->GetBinContent(i),2)/(sig2->GetBinContent(i)+bkg2->GetBinContent(i));
      }
    }
    return sqrt(f2Sig2);
 }
 
 float CalcSig3(TH1D*sig3, TH1D*bkg3) {
   int Syield3 = 0;
   int Byield3 = 0;
   float f3Sig = 0;
   int nb3 = sig3->GetNbinsX();
   for(int i=0; i<=nb3; i++){
     Syield3 = Syield3 + sig3->GetBinContent(i);
     }
   for(int i=0; i<=nb3; i++){
     Byield3 = Byield3 + bkg3->GetBinContent(i);
     }
   f3Sig = Syield3/sqrt(Byield3);
   return f3Sig;
 }
  
 float CalcSig4(TH1D*sig4, TH1D*bkg4) {
   int Syield4 = 0;
   int Byield4 = 0;
   float f4Sig = 0;
   int nb4 = sig4->GetNbinsX();
   for(int i=0; i<=nb4; i++){
     Syield4 = Syield4 + sig4->GetBinContent(i);
     }
   for(int i=0; i<=nb4; i++){
     Byield4 = Byield4 + bkg4->GetBinContent(i);
     }
   f4Sig = Syield4/sqrt(Syield4+Byield4);
   return f4Sig;
  }



















