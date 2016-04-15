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
#include "../macros/ZprimeBitsLoader.hh"    // helper to load baconbits
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
float CalcSig(TH1D*sig, TH1D*bkg);

//=== MAIN MACRO =================================================================================================

void plotZprime(const string selection, const string algo)
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  const bool doBlind = false;

  // Create output directory 
  const string outputDir("ZprimePlots/"+selection+"_"+algo);
  gSystem->mkdir(outputDir.c_str(), true);
  CPlot::sOutDir = outputDir;

  //
  // Samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;

  samplev.push_back(new CSample("data",0,0));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/JetHT.root");
  samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/QCD.root");
  samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/T.root");
  samplev.push_back(new CSample("t#bar{t}",kOrange - 3,kOrange - 3));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/TT.root");
  samplev.push_back(new CSample("Diboson",kYellow - 9,kYellow - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/WW.root");
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/WZ.root");
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZZ.root");
  samplev.push_back(new CSample("W+jets",kGreen - 10,kGreen - 10));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/W.root");
  samplev.push_back(new CSample("Z+jets", kCyan - 9, kCyan - 9));
  samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/DY.root");

  // samplev.push_back(new CSample("Zprime50",kOrange - 3,kOrange - 3));
  // samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZPrimeToQQ_50GeV_v4_mc.root");
  // samplev.push_back(new CSample("Zprime100",kOrange - 4,kOrange - 4));
  // samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZPrimeToQQ_100GeV_v4_mc.root");
  // samplev.push_back(new CSample("Zprime150",kOrange + 6,kOrange + 6));
  // samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZPrimeToQQ_150GeV_v4_mc.root");
  // samplev.push_back(new CSample("Zprime200",kOrange + 8,kOrange + 8));
  // samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZPrimeToQQ_200GeV_v4_mc.root");
  // samplev.push_back(new CSample("Zprime250",kOrange + 7,kOrange + 7));
  // samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZPrimeToQQ_250GeV_v4_mc.root");
  // samplev.push_back(new CSample("Zprime300",kOrange + 9,kOrange + 9));
  // samplev.back()->fnamev.push_back("/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/ZPrimeToQQ_300GeV_v4_mc.root");

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
  vector<TH1D*> hFatJetPtv;
  vector<TH1D*> hFatJetMassv, hFatJetTau21v;              
  vector<TH1D*> hSubjetBtagv; 
  vector<double> neventsv;
  
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    sprintf(hname,"hFatJetPt_%i",isam);       hFatJetPtv.push_back(new TH1D(hname,"",20,360,1000));        hFatJetPtv[isam]->Sumw2();
    sprintf(hname,"hFatJetMass_%i",isam);     hFatJetMassv.push_back(new TH1D(hname,"",20,40,120));        hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hFatJetTau21_%i",isam);    hFatJetTau21v.push_back(new TH1D(hname,"",15,0.2,1));        hFatJetTau21v[isam]->Sumw2();
    sprintf(hname,"hSubjetBtag_%i",isam);     hSubjetBtagv.push_back(new TH1D(hname,"",15,0,1));           hSubjetBtagv[isam]->Sumw2();
    neventsv.push_back(0);
  }

  TH1D *hFatJetPtMC        = (TH1D*)hFatJetPtv[0]   ->Clone("hFatJetPtMC");
  TH1D *hFatJetMassMC      = (TH1D*)hFatJetMassv[0] ->Clone("hFatJetMassMC");
  TH1D *hFatJetTau21MC     = (TH1D*)hFatJetTau21v[0]->Clone("hFatJetTau21MC");
  TH1D *hSubjetBtagMC      = (TH1D*)hSubjetBtagv[0] ->Clone("hSubjetBtagMC"); 
  TH1D *hFatJetMassSig     = (TH1D*)hFatJetMassv[0] ->Clone("hFatJetMassSig");

  double neventsMC;

  TFile *infile=0;
  TTree *intree=0;

  // Loop over samples
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    CSample *sample  = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData    = (isam==0);
    // bool isSignal1 = (isam==samplev.size()-1);
    // bool isSignal2 = (isam==samplev.size()-2);
    // bool isSignal3 = (isam==samplev.size()-3);                                                                                                                                    
    // bool isSignal4 = (isam==samplev.size()-4);                                                                                                                                    
    // bool isSignal5 = (isam==samplev.size()-5);    
    // bool isSignal6 = (isam==samplev.size()-6);  
 
    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      intree = (TTree*)infile->Get("Events"); assert(intree);
      // Load variables for jet size e.g. "15" "PUPPI"
      fBits  = new ZprimeBitsLoader(intree,"8",algo);

      double nevts=0;
      int noweight=0;

      std::cout << intree->GetEntries() << std::endl;
      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
	// for(unsigned int ientry=0; ientry<600000; ientry++) {

        intree->GetEntry(ientry);
	if(!fBits->selectJetAlgoAndSize(selection,algo)) continue;
	// Common selection
	if(fBits->metfilter!=0)                          continue;
	if(!fBits->passSelection(selection))             continue;

	// Apply weigths
        double wgt = 1;

	if(!isData) {
          wgt *= LUMI*fBits->scale1fb;
        }
        nevts += wgt;
	noweight++;
	
        neventsv[isam]+=wgt;
        hFatJetPtv[isam]       ->Fill(fBits->bst_jet0_pt,             wgt);
	hFatJetMassv[isam]     ->Fill(fBits->fjet_mass(selection),    wgt);
	hFatJetTau21v[isam]    ->Fill(fBits->nsubjet(selection),      wgt);
        hSubjetBtagv[isam]     ->Fill(fBits->btag(selection),         wgt);

	//if(isSignal1 || isSignal2 || isSignal3 || isSignal4 || isSignal5 || isSignal6){
	hFatJetMassSig       ->Fill(fBits->fjet_mass(selection),    wgt);
	//}
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
  // QCD SF
  //
  double QCDSF = 1.0;
  QCDSF = (neventsv[0]-(neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]+neventsv[6]))/neventsv[1];
  hFatJetPtv[1]    ->Scale(QCDSF);
  hFatJetMassv[1]  ->Scale(QCDSF);
  hFatJetTau21v[1] ->Scale(QCDSF);
  hSubjetBtagv[1]  ->Scale(QCDSF);

  for(unsigned int isam=1; isam<samplev.size(); isam++) {
    hFatJetPtMC    ->Add(hFatJetPtv[isam]);
    hFatJetMassMC  ->Add(hFatJetMassv[isam]);
    hFatJetTau21MC ->Add(hFatJetTau21v[isam]);
    hSubjetBtagMC  ->Add(hSubjetBtagv[isam]);
  }

  neventsMC = neventsv[1]*QCDSF+neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]+neventsv[6];

  //
  // Make pull histograms
  //
  TH1D *hFatJetPtPull       = makePullHist(hFatJetPtv[0],       hFatJetPtMC,       "hFatJetPtPull",        doBlind);
  TH1D *hFatJetMassPull     = makePullHist(hFatJetMassv[0],     hFatJetMassMC,     "hFatJetMassPull",      doBlind);
  TH1D *hFatJetTau21Pull    = makePullHist(hFatJetTau21v[0],    hFatJetTau21MC,    "hFatJetTau21Pull",     doBlind);
  TH1D *hBtagPull           = makePullHist(hSubjetBtagv[0],     hSubjetBtagMC,     "hBtagPull",            doBlind);

  //                                                                                                                                                                                                    
  // Calculate significance                                                                                                                                                                               
  //                 
  vector<float> significance;                                                                                                                                                                                
  significance.push_back(CalcSig(hFatJetMassSig,  hFatJetMassMC));

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
  //  if (subsample.compare("SR")==0) max = samplev.size()-2;    
  txtfile << setw(35) << samplev[1]->label;
  txtfile << setw(15) << neventsv[1]*QCDSF << endl;
  for(unsigned int isam=2; isam<max; isam++) {
    txtfile << setw(35) << samplev[isam]->label;
    txtfile << setw(15) << neventsv[isam] << endl;
  }
  txtfile << "---------------------------------------------"  << endl;
  txtfile << setw(35) << "SM Expected:" << setw(15) << neventsMC << endl;
  if(!doBlind) { txtfile << setw(35) << "Observed:" << setw(15) << neventsv[0] << endl; }
  txtfile << "QCD Scale Factor:" << QCDSF << endl;
  //  if(subsample.compare("SR")==0){
  txtfile << "---------------------------------------------"  << endl;
  for(unsigned int isam=max; isam<samplev.size(); isam++) {
    txtfile << setw(35) << samplev[isam]->label;
    txtfile << setw(15) << neventsv[isam] << endl;
    txtfile << setw(35) << "Significance: ";
    txtfile << setw(15) << significance[samplev.size()-isam-1] << endl;
  }
  //  }
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

  sprintf(ylabel,"Events / %.1f GeV/c^{2}",hFatJetPtv[0]->GetBinWidth(1));
  makePlot(c, "fjpt", "Jet p_{T} [GeV/c^{2}]", ylabel, hFatJetPtv, samplev, hFatJetPtMC, hFatJetPtPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetPtMC->GetBinContent(hFatJetPtMC->GetMaximumBin()))/(hFatJetPtMC->GetBinWidth(hFatJetPtMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / GeV/c^{2}");
  makePlot(c, "msd", "Soft Drop Mass [GeV/c^{2}]", ylabel, hFatJetMassv, samplev, hFatJetMassMC, hFatJetMassPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin()))/(hFatJetMassMC->GetBinWidth(hFatJetMassMC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f ",hFatJetTau21v[0]->GetBinWidth(10));
  makePlot(c, "tau21", "#tau_{2}/#tau_{1}", ylabel, hFatJetTau21v, samplev, hFatJetTau21MC, hFatJetTau21Pull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hFatJetTau21MC->GetBinContent(hFatJetTau21MC->GetMaximumBin()))/(hFatJetTau21MC->GetBinWidth(hFatJetTau21MC->GetMaximumBin())), selection);

  sprintf(ylabel,"Events / %.1f ",hSubjetBtagv[0]->GetBinWidth(10));
  makePlot(c, "btag", "Max subjet csv", ylabel, hSubjetBtagv, samplev, hSubjetBtagMC, hBtagPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hSubjetBtagMC->GetBinContent(hSubjetBtagMC->GetMaximumBin()))/(hSubjetBtagMC->GetBinWidth(hSubjetBtagMC->GetMaximumBin())), selection);

  cout << endl;
  cout << " <> Output saved in " << outputDir << endl;
  cout << endl; 
}

//=== FUNCTION DEFINITIONS ======================================================================================

//--------------------------------------------------------------------------------------------------
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy, const double legdx, const double legdy,
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
  float max = samplev.size();
  //  if (subsample.compare("SR")==0) max = samplev.size()-2; 
  for(unsigned int i=1; i<max; i++) {
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }

  //if (subsample.compare("SR")==0){
  // for(unsigned int i=max; i<histv.size(); i++) {
  //  plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
  // }
  // }

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
