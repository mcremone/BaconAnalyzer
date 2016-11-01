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
#include "../macros/KStyle.hh"
#include "../macros/CSample.hh"
#include "../macros/ZprimeBitsLoader.hh"

//#endif

using namespace std;

//Object Processors                                                                                                                                                                                      
ZprimeBitsLoader       *fBits      = 0;

//=== FUNCTION DECLARATIONS ======================================================================================

// make "standard" plot
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy=false, const double legdx=0, const double legdy=0,
              const double ymin=-1, const double ymax=-1);
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind);
//=== MAIN MACRO =================================================================================================

void plotZprime(const string preselection,const string selection,const string subsample, const string algo, const string jet, float cut, float csv)
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

 // samplev.push_back(new CSample("data",0,0));
 // samplev.back()->fnamev.push_back("../monoxbits/SinglePhoton.root");
 // samplev.push_back(new CSample("VDJG100",kRed,kRed));
 // samplev.back()->fnamev.push_back("../zprimebits/VectorDiJetGamma100.root");
  samplev.push_back(new CSample("G+Jets(HF)",kMagenta - 10,kMagenta - 10));
  samplev.back()->fnamev.push_back("../monoxbits/GHF.root");
  samplev.push_back(new CSample("G+Jets(LF)",kMagenta - 6,kMagenta - 6));
  samplev.back()->fnamev.push_back("../monoxbits/oldbits/GLF.root");
  samplev.push_back(new CSample("QCD",kRed,kRed));
  samplev.back()->fnamev.push_back("../monoxbits/QCD.root");
  /*samplev.push_back(new CSample("W+jets",kGreen - 10,kGreen - 10));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/W.root");
  samplev.push_back(new CSample("Z+jets", kCyan - 9, kCyan - 9));
  samplev.back()->fnamev.push_back("/tmp/cmantill/DY.root");
  samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/T.root");
  samplev.push_back(new CSample("t#bar{t}",kOrange - 3,kOrange - 3));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/TT.root");
  samplev.push_back(new CSample("m_{Z'}=100 GeV",2,2));*/
  //samplev.back()->fnamev.push_back("../monoxbits/VectorDiJet20.root");
  //samplev.push_back(new CSample("m_{Z'}=20 GeV",4,4));
  //samplev.back()->fnamev.push_back("../monoxbits/VectorDiJet20.root");
  //samplev.push_back(new CSample("m_{Z'}=50 GeV",6,6));
  //samplev.back()->fnamev.push_back("../monoxbits/VectorDiJet50.root");
  //samplev.push_back(new CSample("m_{Z'}=75 GeV",7,7));
  //samplev.back()->fnamev.push_back("../monoxbits/VectorDiJet75.root");
  //samplev.push_back(new CSample("m_{Z'}=250 GeV",8,8));
 // samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M250_mc.root");
  //samplev.push_back(new CSample("m_{Z'}=300 GeV",3,3));
  //samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M300_mc.root");


  // integrated luminosity to scale MC
  const double LUMI = 12.89;
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
  vector<TH1D*> hFatJetMassv,hFatJetPtv,hFatJetPtLogv,hFatJetEtav, hFatJetTau21v, hFatJetTau21DDTv, hFatJetRhoDDTv, hFatJetRhoDDTlv, hFatJetMassNew;     
  vector<TH1D*> vpho0_ptv,vpho0_etav,vpho0_phiv,hFatJetPhiv,npv;
  vector<double> neventsv;
  double npvd;
  
  for(unsigned int isam=0; isam<3; isam++) {
    sprintf(hname,"hFatJetMass_%i",isam);     hFatJetMassv.push_back(new TH1D(hname,"",50,10,150));         hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetPt_%i",isam);       hFatJetPtv.push_back(new TH1D(hname,"",40,175,1200));        hFatJetPtv[isam]->Sumw2();
    sprintf(hname,"hFatJetPtLog_%i",isam);    hFatJetPtLogv.push_back(new TH1D(hname,"",40,150,1200));     hFatJetPtLogv[isam]->Sumw2();
    sprintf(hname,"hFatJetEta_%i",isam);      hFatJetEtav.push_back(new TH1D(hname,"",30,-4.5,4.5));       hFatJetEtav[isam]->Sumw2();  
    sprintf(hname,"hFatJetPhi_%i",isam);      hFatJetPhiv.push_back(new TH1D(hname,"",30,-3.14,3.14));       hFatJetPhiv[isam]->Sumw2();
    sprintf(hname,"hFatJetMassNew_%i",isam);  hFatJetMassNew.push_back(new TH1D(hname,"",10,60,120));      hFatJetMassNew[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21_%i",isam);    hFatJetTau21v.push_back(new TH1D(hname,"",25,0,1));        hFatJetTau21v[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21DDT_%i",isam); hFatJetTau21DDTv.push_back(new TH1D(hname,"",25,0,1));     hFatJetTau21DDTv[isam]->Sumw2();
    sprintf(hname,"hFatJetRhoDDT_%i",isam);   hFatJetRhoDDTv.push_back(new TH1D(hname,"",25,-1,6));     hFatJetRhoDDTv[isam]->Sumw2();
    sprintf(hname,"hFatJetRhoDDTl_%i",isam);  hFatJetRhoDDTlv.push_back(new TH1D(hname,"",25,-1,6));     hFatJetRhoDDTlv[isam]->Sumw2();
    sprintf(hname,"hnpv_%i",isam);            npv.push_back(new TH1D(hname,"",20,0,40));                npv[isam]->Sumw2();
    sprintf(hname,"vpho0_ptv_%i",isam);       vpho0_ptv.push_back(new TH1D(hname,"",40,150,1000));        vpho0_ptv[isam]->Sumw2();  
    sprintf(hname,"vpho0_etav_%i",isam);       vpho0_etav.push_back(new TH1D(hname,"",30,-4.5,4.5));        vpho0_etav[isam]->Sumw2();
    sprintf(hname,"vpho0_phiv_%i",isam);       vpho0_phiv.push_back(new TH1D(hname,"",30,-3.14,3.14));        vpho0_phiv[isam]->Sumw2();
    neventsv.push_back(0);
  }

  TH1D *hFatJetMassMC      = (TH1D*)hFatJetMassv[0]    ->Clone("hFatJetMassMC");
  TH1D *hFatJetMassNewMC   = (TH1D*)hFatJetMassNew[0]  ->Clone("hFatJetMassNewMC");
  TH1D *hFatJetTau21MC     = (TH1D*)hFatJetTau21v[0]   ->Clone("hFatJetTau21MC");
  TH1D *hFatJetTau21DDTMC  = (TH1D*)hFatJetTau21DDTv[0]->Clone("hFatJetTau21DDTMC");
  TH1D *hFatJetRhoDDTMC    = (TH1D*)hFatJetRhoDDTv[0]  ->Clone("hFatJetRhoDDTMC");
  TH1D *hFatJetRhoDDTlMC   = (TH1D*)hFatJetRhoDDTlv[0] ->Clone("hFatJetRhoDDTlMC");
  TH1D *hFatJetPtMC        = (TH1D*)hFatJetPtv[0]      ->Clone("hFatJetPtMC");
  TH1D *hFatJetPtLogMC     = (TH1D*)hFatJetPtLogv[0]   ->Clone("hFatJetPtLogMC");
  TH1D *npvMC              = (TH1D*)npv[0]            ->Clone("npvMC");
  TH1D *hFatJetEtaMC        = (TH1D*)hFatJetEtav[0]      ->Clone("hFatJetEtaMC");
  TH1D *hFatJetPhiMC        = (TH1D*)hFatJetPhiv[0]      ->Clone("hFatJetPhiMC");
  TH1D *vpho0_ptMC        = (TH1D*)vpho0_ptv[0]      ->Clone("vpho0_ptMC");
  TH1D *vpho0_etaMC        = (TH1D*)vpho0_etav[0]      ->Clone("vpho0_etaMC");
  TH1D *vpho0_phiMC        = (TH1D*)vpho0_phiv[0]      ->Clone("vpho0_phiMC");
  TH1D *hFatJetMassSig     = (TH1D*)hFatJetMassv[0]    ->Clone("hFatJetMassSig");

  double neventsMC;
  int debug=0;
  TString number;
  TFile *infile=0;
  TTree *intree=0;
  
  //TFile *f = new TFile("npvPullkfactor.root","READ");
  //TH1F *pull = (TH1F*)f->Get("npvPull");
  //TFile *f1 = new TFile("npvPullNLOkfactor.root","READ");
  //TH1F *pullNLO = (TH1F*)f1->Get("npvPull");
  // Loop over samples
  for(unsigned int isam=0; isam<3; isam++) {
    CSample *sample  = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    //bool isData    = (isam==0);
    bool isData    = false;
    //if(isam==1 || isam==0) number = "15";
    //else number = "8";
   
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

      fBits  = new ZprimeBitsLoader(intree,algo,jet,"8");

      double nevts=0;
      int noweight=0;
      double test=0;
      double binnumber=0;
      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
      // for(unsigned int ientry=0; ientry<100; ientry++) {
	// Blinding policy: keep just one fifth of the events
//	if(!doBlind && isData && ientry % 5 != 0) continue;
        intree->GetEntry(ientry);

	if(!fBits->selectJetAlgoAndSize(algo))   continue;
	if(fBits->metfilter!=0)                  continue;
        //if(isData && ((fBits->metfilter & 1) || (fBits->metfilter & 2) || (fBits->metfilter & 8) || (fBits->metfilter & 32) || 
	//		(fBits->metfilter & 1024) || (fBits->metfilter & 2048) || (fBits->metfilter & 32768))) continue;
        if(!fBits->passPreSelection(isData,preselection)) continue;
//	if(!fBits->passSelection(isData,selection,subsample,cut,csv)) continue;
	if(!fBits->passBoostedMonoTopPreselection()) continue;
	// Apply weigths
        double wgt = 1;
	wgt *= fBits->getWgt(isData,algo,LUMI);
        npvd = double (fBits->npv);
        /*if(!isData){
        test = npvd/2;
        binnumber = ceil(test);
        wgt *= pull->GetBinContent(binnumber);
        wgt *= pullNLO->GetBinContent(binnumber);}*/
	if (wgt == 0) debug=debug+1;
	nevts += wgt;
	noweight++;
	double bst_jet0_nhan = log(fBits->bst_jet0_msd*fBits->bst_jet0_msd/fBits->bst_jet0_pt); 
        neventsv[isam]+=wgt;

	hFatJetMassv[isam]     ->Fill(fBits->bst_jet0_msd,            wgt);
        hFatJetMassNew[isam]   ->Fill(fBits->bst_jet0_msd,            wgt);
	hFatJetTau21v[isam]    ->Fill(fBits->bst_jet0_tau21,          wgt);
        hFatJetTau21DDTv[isam] ->Fill(fBits->tau21DDT(),              wgt);
        hFatJetRhoDDTv[isam]   ->Fill(bst_jet0_nhan,              wgt);
        hFatJetRhoDDTlv[isam]   ->Fill(bst_jet0_nhan,              wgt);
        hFatJetPtv[isam]       ->Fill(fBits->bst_jet0_pt,          wgt);
        hFatJetEtav[isam]       ->Fill(fBits->bst_jet0_eta,          wgt);
        hFatJetPhiv[isam]       ->Fill(fBits->bst_jet0_phi,          wgt);
        hFatJetPtLogv[isam]      ->Fill(fBits->bst_jet0_pt,          wgt);
        vpho0_ptv[isam]         ->Fill(fBits->vpho0_pt,     wgt);
        vpho0_etav[isam]         ->Fill(fBits->vpho0_eta,     wgt);
        vpho0_phiv[isam]         ->Fill(fBits->vpho0_phi,     wgt);
        npv[isam]               ->Fill(npvd,                  wgt);
        //hSubjetBtagv[isam]     ->Fill(fBits->bst_jet0_minsubcsv,      wgt);
        //hFatjetBtagv[isam]     ->Fill(fBits->bst_jet0_doublecsv,      wgt);

	//if(isSignal1 || isSignal2 || isSignal3 || isSignal4 || isSignal5 || isSignal6){
	if(isam==2 || isam==3){ 
	  hFatJetMassSig         ->Fill(fBits->bst_jet0_msd,            wgt);
        }
	//}
      }

      if(isData && doBlind) {
        cout << endl;
      } else {
        cout << nevts << " " << noweight  <<  " " << fBits->scale1fb << "Current debug value: " << debug << endl;
      }
      delete infile;
      infile=0;
      intree=0;
    }
   

  }


  // 
  // QCD SF
  //
  double QCDSF=1.0;
 for(int i=0;i<3;i++){
  
//  QCDSF = 1/neventsv[i];
  hFatJetPtv[i]       ->Scale(QCDSF);
  hFatJetPtLogv[i]    ->Scale(QCDSF);
  hFatJetEtav[i]      ->Scale(QCDSF);
  hFatJetMassv[i]     ->Scale(QCDSF);
  hFatJetMassNew[i]   ->Scale(QCDSF);
  hFatJetTau21v[i]    ->Scale(QCDSF);
  hFatJetTau21DDTv[i] ->Scale(QCDSF);
  hFatJetRhoDDTv[i]   ->Scale(QCDSF);
  hFatJetRhoDDTlv[i]  ->Scale(QCDSF);
  npv[i]              ->Scale(QCDSF);
 }  

  for(unsigned int isam=0; isam<3; isam++) {
    cout << "Adding " << samplev[isam]->label <<" to MC"<<endl;
    hFatJetMassMC     ->Add(hFatJetMassv[isam]);
    hFatJetMassNewMC  ->Add(hFatJetMassNew[isam]);
    hFatJetTau21MC    ->Add(hFatJetTau21v[isam]);
    hFatJetTau21DDTMC ->Add(hFatJetTau21DDTv[isam]);
    hFatJetRhoDDTMC   ->Add(hFatJetRhoDDTv[isam]);
    hFatJetRhoDDTlMC  ->Add(hFatJetRhoDDTlv[isam]);
    hFatJetPtMC       ->Add(hFatJetPtv[isam]);
    hFatJetEtaMC       ->Add(hFatJetEtav[isam]);
    hFatJetPhiMC       ->Add(hFatJetPhiv[isam]);
    vpho0_ptMC        ->Add(vpho0_ptv[isam]);
    vpho0_etaMC        ->Add(vpho0_etav[isam]);
    vpho0_phiMC        ->Add(vpho0_phiv[isam]);
    hFatJetPtLogMC    ->Add(hFatJetPtLogv[isam]);
    npvMC             ->Add(npv[isam]);
  }
  //
  // Make pull histograms
  //
  
  TH1D *hFatJetMassPull     = makePullHist(hFatJetMassv[0],     hFatJetMassMC,     "hFatJetMassPull",      doBlind);
  TH1D *hFatJetMassNewPull  = makePullHist(hFatJetMassNew[0],   hFatJetMassNewMC,  "hFatJetMassNewPull",   doBlind);
  TH1D *hFatJetTau21Pull    = makePullHist(hFatJetTau21v[0],    hFatJetTau21MC,    "hFatJetTau21Pull",     doBlind);
  TH1D *hFatJetTau21DDTPull = makePullHist(hFatJetTau21DDTv[0], hFatJetTau21DDTMC, "hFatJetTau21DDTPull",  doBlind);
  TH1D *hFatJetRhoDDTPull   = makePullHist(hFatJetRhoDDTv[0],   hFatJetRhoDDTMC, "hFatJetRhoDDTPull",  doBlind);
  TH1D *hFatJetRhoDDTlPull  = makePullHist(hFatJetRhoDDTlv[0],  hFatJetRhoDDTlMC, "hFatJetRhoDDTlPull",  doBlind);
  TH1D *hFatJetPtPull       = makePullHist(hFatJetPtv[0],       hFatJetPtMC,      "hFatJetPtPull"    , doBlind);
  TH1D *hFatJetEtaPull       = makePullHist(hFatJetEtav[0],       hFatJetEtaMC,      "hFatJetEtaPull"    , doBlind);
  TH1D *hFatJetPhiPull       = makePullHist(hFatJetPhiv[0],       hFatJetPhiMC,      "hFatJetPhiPull"    , doBlind);
  TH1D *vpho0_ptPull       = makePullHist(vpho0_ptv[0],       vpho0_ptMC,      "vpho0_ptPull"    , doBlind);
  TH1D *vpho0_etaPull       = makePullHist(vpho0_etav[0],       vpho0_etaMC,      "vpho0_etaPull"    , doBlind);
  TH1D *vpho0_phiPull       = makePullHist(vpho0_phiv[0],       vpho0_phiMC,      "vpho0_phiPull"    , doBlind);
  TH1D *hFatJetPtLogPull    = makePullHist(hFatJetPtLogv[0],       hFatJetPtLogMC,      "hFatJetPtLogPull"    , doBlind);
  TH1D *npvPull             = makePullHist(npv[0],       npvMC,      "npvPull"    , doBlind);
  /*TFile *f6            = new TFile("Signal20m.root","RECREATE");
  hFatJetMassv[0]->Write();
  f6->Close();
  TFile *f7            = new TFile("Signal50m.root","RECREATE");
  hFatJetMassv[1]->Write();
  f7->Close();
  TFile *f8            = new TFile("Signal75m.root","RECREATE");
  hFatJetMassv[2]->Write();
  f8->Close();
  TFile *f9            = new TFile("Signal20p.root","RECREATE");
  hFatJetPtv[0]->Write();
  f9->Close();
  TFile *f10            = new TFile("Signal50p.root","RECREATE");
  hFatJetPtv[1]->Write();
  f10->Close();
  TFile *f11           = new TFile("Signal75p.root","RECREATE");
  hFatJetPtv[2]->Write();
  f11->Close();*/  
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
  for(unsigned int isam=0; isam<3; isam++) {
    txtfile << setw(35) << samplev[isam]->label;
    txtfile << setw(15) << neventsv[isam] << endl;
  }
  txtfile << "---------------------------------------------"  << endl;
  txtfile << setw(35) << "SM Expected:" << setw(15) << neventsMC << endl;
  if(!doBlind) { txtfile << setw(35) << "Observed:" << setw(15) << neventsv[0] << endl; }

  txtfile << "QCD Scale Factor:" << QCDSF << endl;
  txtfile << "---------------------------------------------"  << endl;
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
  c->cd(2)->SetTopMargin(0.1);
  c->cd(2)->SetBottomMargin(0.45);
  c->cd(2)->SetLeftMargin(0.15);
  c->cd(2)->SetRightMargin(0.07);
  c->cd(2)->SetTickx(1);
  c->cd(2)->SetTicky(1);

  char ylabel[100];

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "msd", "Soft Drop Mass [GeV]", ylabel, hFatJetMassv, samplev, hFatJetMassMC, hFatJetMassPull, doBlind, LUMI,false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())));
           0.1,2.0*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())));
           //0.1,100);
 sprintf(ylabel,"Events / GeV");
  makePlot(c, "fjpt", "Pt of Fat Jet [GeV]", ylabel, hFatJetPtv, samplev, hFatJetPtMC, hFatJetPtPull, doBlind, LUMI, false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
                      0.1,2.0*(hFatJetPtMC->GetBinContent(hFatJetPtMC->GetMaximumBin()))/(hFatJetPtMC->GetBinWidth(hFatJetPtMC->GetMaximumBin())));

sprintf(ylabel,"Events / GeV");
  makePlot(c, "fjeta", "Eta of Fat Jet [GeV]", ylabel, hFatJetEtav, samplev, hFatJetEtaMC, hFatJetEtaPull, doBlind, LUMI, false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
                      0.1,2.0*(hFatJetEtaMC->GetBinContent(hFatJetEtaMC->GetMaximumBin()))/(hFatJetEtaMC->GetBinWidth(hFatJetEtaMC->GetMaximumBin())));

sprintf(ylabel,"Events / GeV");
  makePlot(c, "fjphi", "Phi of Fat Jet [GeV]", ylabel, hFatJetPhiv, samplev, hFatJetPhiMC, hFatJetPhiPull, doBlind, LUMI, false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
                      0.1,2.0*(hFatJetPhiMC->GetBinContent(hFatJetPhiMC->GetMaximumBin()))/(hFatJetPhiMC->GetBinWidth(hFatJetPhiMC->GetMaximumBin())));

sprintf(ylabel,"Events / GeV");
  makePlot(c, "pho_pt", "Pt of Photon [GeV]", ylabel, vpho0_ptv, samplev, vpho0_ptMC, vpho0_ptPull, doBlind, LUMI, false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
                      0.1,2.0*(vpho0_ptMC->GetBinContent(vpho0_ptMC->GetMaximumBin()))/(vpho0_ptMC->GetBinWidth(vpho0_ptMC->GetMaximumBin())));
sprintf(ylabel,"Events / GeV");
  makePlot(c, "pho_eta", "Eta of Photon [GeV]", ylabel, vpho0_etav, samplev, vpho0_etaMC, vpho0_etaPull, doBlind, LUMI, false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
                      0.1,2.0*(vpho0_etaMC->GetBinContent(vpho0_etaMC->GetMaximumBin()))/(vpho0_etaMC->GetBinWidth(vpho0_etaMC->GetMaximumBin())));

sprintf(ylabel,"Events / GeV");
  makePlot(c, "pho_phi", "Phi of Photon [GeV]", ylabel, vpho0_phiv, samplev, vpho0_phiMC, vpho0_phiPull, doBlind, LUMI, false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
                                 0.1,2.0*(vpho0_phiMC->GetBinContent(vpho0_phiMC->GetMaximumBin()))/(vpho0_phiMC->GetBinWidth(vpho0_phiMC->GetMaximumBin())));
           
sprintf(ylabel,"Events / GeV");
  makePlot(c, "fjptlog", "Log Pt of Fat Jet [GeV]", ylabel, hFatJetPtLogv, samplev, hFatJetPtLogMC, hFatJetPtLogPull, doBlind, LUMI,true, 0.0, -0.03,
           2e-5*(hFatJetPtLogMC->GetBinContent(hFatJetPtLogMC->GetMaximumBin()))/(hFatJetPtLogMC->GetBinWidth(hFatJetPtLogMC->GetMaximumBin())));
           //           0.1,2.0*(hFatJetPtLogMC->GetBinContent(hFatJetPtLogMC->GetMaximumBin()))/(hFatJetPtLogMC->GetBinWidth(hFatJetPtLogMC->GetMaximumBin())));

sprintf(ylabel,"Events / GeV");
  makePlot(c, "npv", "Number of PV", ylabel, npv, samplev, npvMC, npvPull, doBlind, LUMI, false, 0.0, -0.03,
           //2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
                      0.1,2.0*(npvMC->GetBinContent(npvMC->GetMaximumBin()))/(npvMC->GetBinWidth(npvMC->GetMaximumBin())));

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "msdnew", "Soft Drop Mass [GeV]", ylabel, hFatJetMassNew, samplev, hFatJetMassNewMC, hFatJetMassNewPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-5*(hFatJetMassNewMC->GetBinContent(hFatJetMassNewMC->GetMaximumBin()))/(hFatJetMassNewMC->GetBinWidth(hFatJetMassNewMC->GetMaximumBin())),
           4e2*(hFatJetMassNewMC->GetBinContent(hFatJetMassNewMC->GetMaximumBin()))/(hFatJetMassNewMC->GetBinWidth(hFatJetMassNewMC->GetMaximumBin())));

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "tau21DDT", "#tau_{21}^{DDT}", ylabel, hFatJetTau21DDTv, samplev, hFatJetTau21DDTMC, hFatJetTau21DDTPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetTau21DDTMC->GetBinContent(hFatJetTau21DDTMC->GetMaximumBin()))/(hFatJetTau21DDTMC->GetBinWidth(hFatJetTau21DDTMC->GetMaximumBin())));

  sprintf(ylabel,"Events / %.1f",hFatJetRhoDDTv[0]->GetBinWidth(10));
  makePlot(c, "rhoDDT", "#rho^{DDT}", ylabel, hFatJetRhoDDTv, samplev, hFatJetRhoDDTMC, hFatJetRhoDDTPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 1.5*(hFatJetRhoDDTMC->GetBinContent(hFatJetRhoDDTMC->GetMaximumBin()))/(hFatJetRhoDDTMC->GetBinWidth(hFatJetRhoDDTMC->GetMaximumBin())));

  sprintf(ylabel,"Events / %.1f",hFatJetRhoDDTlv[0]->GetBinWidth(10));
  makePlot(c, "rhoDDTl", "#rho^{DDT}", ylabel, hFatJetRhoDDTlv, samplev, hFatJetRhoDDTlMC, hFatJetRhoDDTlPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 1.4*(hFatJetRhoDDTlMC->GetBinContent(hFatJetRhoDDTlMC->GetMaximumBin()))/(hFatJetRhoDDTlMC->GetBinWidth(hFatJetRhoDDTlMC->GetMaximumBin())));

  cout << endl;
  cout << " <> Output saved in " << outputDir << endl;
  cout << endl;


}

//=== FUNCTION DEFINITIONS ======================================================================================

//--------------------------------------------------------------------------------------------------
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              bool doBlind, const double lumi, const bool doLogy, const double legdx, const double legdy,
              const double ymin, const double ymax)
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
  int max = 2;//-6;
  for( int i=max; i>=0; i--) {
  
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }
  
 /* for(unsigned int i=max; i>histv.size(); i--) {
    plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
  }*/
  
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


















