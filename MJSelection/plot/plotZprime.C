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
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/JetHTsilverv2.root");
  samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
  samplev.back()->fnamev.push_back("/tmp/cmantill/QCD.root");
  samplev.push_back(new CSample("W+jets",kGreen - 10,kGreen - 10));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/W.root");
  samplev.push_back(new CSample("Z+jets", kCyan - 9, kCyan - 9));
  samplev.back()->fnamev.push_back("/tmp/cmantill/DY.root");
  samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/T.root");
  samplev.push_back(new CSample("t#bar{t}",kOrange - 3,kOrange - 3));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/TT.root");
  samplev.push_back(new CSample("m_{Z'}=100 GeV",2,2));
  samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M100_mc.root");
  samplev.push_back(new CSample("m_{Z'}=125 GeV",4,4));
  samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M125_mc.root");
  samplev.push_back(new CSample("m_{Z'}=150 GeV",6,6));
  samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M150_mc.root");
  samplev.push_back(new CSample("m_{Z'}=200 GeV",7,7));
  samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M200_mc.root");
  samplev.push_back(new CSample("m_{Z'}=250 GeV",8,8));
  samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M250_mc.root");
  samplev.push_back(new CSample("m_{Z'}=300 GeV",3,3));
  samplev.back()->fnamev.push_back("/tmp/cmantill/VectorDiJet1Jet_M300_mc.root");


  // integrated luminosity to scale MC
  const double LUMI = 2.7;
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
  vector<TH1D*> hFatJetMassv, hFatJetTau21v, hFatJetTau21DDTv, hFatJetRhoDDTv, hFatJetRhoDDTlv, hFatJetMassNew;     
  vector<double> neventsv;
  
  for(unsigned int isam=0; isam<8; isam++) {
    sprintf(hname,"hFatJetMass_%i",isam);     hFatJetMassv.push_back(new TH1D(hname,"",40,0,400));         hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetMassNew_%i",isam);  hFatJetMassNew.push_back(new TH1D(hname,"",10,60,120));      hFatJetMassNew[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21_%i",isam);    hFatJetTau21v.push_back(new TH1D(hname,"",25,0,1));        hFatJetTau21v[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21DDT_%i",isam); hFatJetTau21DDTv.push_back(new TH1D(hname,"",25,0,1));     hFatJetTau21DDTv[isam]->Sumw2();
    sprintf(hname,"hFatJetRhoDDT_%i",isam);   hFatJetRhoDDTv.push_back(new TH1D(hname,"",25,-1,6));     hFatJetRhoDDTv[isam]->Sumw2();
    sprintf(hname,"hFatJetRhoDDTl_%i",isam);   hFatJetRhoDDTlv.push_back(new TH1D(hname,"",25,-1,6));     hFatJetRhoDDTlv[isam]->Sumw2();
    neventsv.push_back(0);
  }

  TH1D *hFatJetMassMC      = (TH1D*)hFatJetMassv[0]    ->Clone("hFatJetMassMC");
  TH1D *hFatJetMassNewMC   = (TH1D*)hFatJetMassNew[0]  ->Clone("hFatJetMassNewMC");
  TH1D *hFatJetTau21MC     = (TH1D*)hFatJetTau21v[0]   ->Clone("hFatJetTau21MC");
  TH1D *hFatJetTau21DDTMC  = (TH1D*)hFatJetTau21DDTv[0]->Clone("hFatJetTau21DDTMC");
  TH1D *hFatJetRhoDDTMC    = (TH1D*)hFatJetRhoDDTv[0]  ->Clone("hFatJetRhoDDTMC");
  TH1D *hFatJetRhoDDTlMC    = (TH1D*)hFatJetRhoDDTlv[0]  ->Clone("hFatJetRhoDDTlMC");

  double neventsMC=0;

  TFile *infile=0;
  TTree *intree=0;
  
  // Loop over samples
 
  for(unsigned int isam=0; isam<11; isam++) {
    CSample *sample  = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData    = (isam==0);

    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      if(isam ==2 || isam == 3 || isam == 6 || isam == 7 || isam == 8 || isam == 9 || isam ==10){ 
	intree = (TTree*)infile->Get("otree"); assert(intree);
      }
      else{
	intree = (TTree*)infile->Get("Events"); assert(intree);
      }
      fBits  = new ZprimeBitsLoader(intree,algo,jet);

      double nevts=0;
      int noweight=0;

      //for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
      for(unsigned int ientry=0; ientry<50000; ientry++) {

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

	hFatJetMassv[isam]     ->Fill(fBits->bst_jet0_msd,            wgt);
        hFatJetMassNew[isam]   ->Fill(fBits->bst_jet0_msd,            wgt);
	hFatJetTau21v[isam]    ->Fill(fBits->bst_jet0_tau21,          wgt);
        hFatJetTau21DDTv[isam] ->Fill(fBits->tau21DDT(),              wgt);
        hFatJetRhoDDTv[isam]   ->Fill(bst_jet0_nhan,              wgt);
        hFatJetRhoDDTlv[isam]   ->Fill(bst_jet0_nhan,              wgt);
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
  QCDSF = (neventsv[0]-(neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]))/neventsv[1];
  std::cout << "QCDSF" << QCDSF << std::endl;


  hFatJetMassv[1]     ->Scale(QCDSF);
  hFatJetMassNew[1]   ->Scale(QCDSF);
  hFatJetTau21v[1]    ->Scale(QCDSF);
  hFatJetTau21DDTv[1] ->Scale(QCDSF);
  hFatJetRhoDDTv[1]   ->Scale(QCDSF);
  hFatJetRhoDDTlv[1]  ->Scale(QCDSF);


  for(unsigned int isam=1; isam<6; isam++) {
    cout << "Adding " << samplev[isam]->label <<" to MC"<<endl;
    hFatJetMassMC     ->Add(hFatJetMassv[isam]);
    hFatJetMassNewMC  ->Add(hFatJetMassNew[isam]);
    hFatJetTau21MC    ->Add(hFatJetTau21v[isam]);
    hFatJetTau21DDTMC ->Add(hFatJetTau21DDTv[isam]);
    hFatJetRhoDDTMC   ->Add(hFatJetRhoDDTv[isam]);
    hFatJetRhoDDTlMC  ->Add(hFatJetRhoDDTlv[isam]);
  }
  
  hFatJetTau21DDTv[6] ->Scale(100);
  hFatJetTau21DDTv[7] ->Scale(100);
  hFatJetTau21DDTv[8] ->Scale(100);
  hFatJetTau21DDTv[9] ->Scale(100);
  hFatJetTau21DDTv[10] ->Scale(100);
  hFatJetTau21DDTv[11] ->Scale(100);
  
  hFatJetMassv[6] ->Scale(100);
  hFatJetMassv[7] ->Scale(100);
  hFatJetMassv[8] ->Scale(100);
  hFatJetMassv[9] ->Scale(100);
  hFatJetMassv[10] ->Scale(100);
  hFatJetMassv[11] ->Scale(100);

  hFatJetMassNew[6] ->Scale(100);
  hFatJetMassNew[7] ->Scale(100);
  hFatJetMassNew[8] ->Scale(100);
  hFatJetMassNew[9] ->Scale(100);
  hFatJetMassNew[10] ->Scale(100);
  hFatJetMassNew[11] ->Scale(100);

  neventsMC = neventsv[1]*QCDSF+neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5];
  std::cout << neventsMC << std::endl;
  //
  // Make pull histograms
  //
  
  TH1D *hFatJetMassPull     = makePullHist(hFatJetMassv[0],     hFatJetMassMC,     "hFatJetMassPull",      doBlind);
  TH1D *hFatJetMassNewPull  = makePullHist(hFatJetMassNew[0],   hFatJetMassNewMC,  "hFatJetMassNewPull",   doBlind);
  TH1D *hFatJetTau21Pull    = makePullHist(hFatJetTau21v[0],    hFatJetTau21MC,    "hFatJetTau21Pull",     doBlind);
  TH1D *hFatJetTau21DDTPull = makePullHist(hFatJetTau21DDTv[0], hFatJetTau21DDTMC, "hFatJetTau21DDTPull",  doBlind);
  TH1D *hFatJetRhoDDTPull   = makePullHist(hFatJetRhoDDTv[0],   hFatJetRhoDDTMC, "hFatJetRhoDDTPull",  doBlind);
  TH1D *hFatJetRhoDDTlPull  = makePullHist(hFatJetRhoDDTlv[0],  hFatJetRhoDDTlMC, "hFatJetRhoDDTlPull",  doBlind);
  
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
  makePlot(c, "msd", "Soft Drop Mass [GeV]", ylabel, hFatJetMassv, samplev, hFatJetMassMC, hFatJetMassPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-5*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())),
           4e2*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())));

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
  float max = samplev.size()-6;
  for(unsigned int i=max-1; i>=1; i--) {
  //for(unsigned int i=1; i<max; i++) {
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }
  
  for(unsigned int i=max; i<histv.size(); i++) {
    plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
  }
  
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


















