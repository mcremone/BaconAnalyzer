//================================================================================================
//
// Plot distributions in signal region with hadronic resoved selection (from B2G-12-022 selection)
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

#include "CPlot.hh"                   // helper class for plots
#include "KStyle.hh"                  // style settings for drawing
#include "CSample.hh"                 // helper class to manage samples
//#endif

using namespace std;


//=== FUNCTION DECLARATIONS ======================================================================================

// make "standard" plot
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy=false, const double legdx=0, const double legdy=0,
              const double ymin=-1, const double ymax=-1, const string selection="", const string subsample="");

TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind);

float DeltaR(float eta1,float phi1,float eta2,float phi2);

float CalcSig(TH1D*sig, TH1D*bkg);


//=== MAIN MACRO =================================================================================================

void plot(const string selection, const string subsample, const string algo)
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  const bool doBlind = false;

  const string outputDir("ZbbPlots/"+selection+"_"+subsample+"_"+algo);

  // Create output directory 
  gSystem->mkdir(outputDir.c_str(), true);
  CPlot::sOutDir = outputDir;

  //
  // samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;

  samplev.push_back(new CSample("data",0,0));
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/Data.root");
  samplev.push_back(new CSample("QCD", kMagenta -10, kMagenta -10)); //-10
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/QCD.root");
  //samplev.push_back(new CSample("Single Top",kRed - 9,kRed - 9));
  //samplev.back()->fnamev.push_back("../baconbits/Zbb_old/T.root").
  samplev.push_back(new CSample("t#bar{t}",kOrange -4,kOrange -4));//-4
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/TT.root");
  samplev.push_back(new CSample("Diboson",kYellow -9,kYellow -9));// -9
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/WW.root");
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/WZ.root");
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/ZZ.root");
  samplev.push_back(new CSample("W+jets",kGreen -10,kGreen -10));// -10
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/Wcs.root");
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/Wlf.root");
  samplev.push_back(new CSample("Zcc",  kAzure +1, kAzure +1));
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/Zcc.root");
  samplev.push_back(new CSample("Zlf", kRed -9, kRed -9));
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/Zlf.root");
  samplev.push_back(new CSample("Zbb", kCyan -9, kCyan -9 ));// -9                                                                                                                                                               
  samplev.back()->fnamev.push_back("../baconbits/Zbb_old/Zbb.root");
  //samplev.back()->fnamev.push_back("../baconbits/Zbb_old/ZLObb.root");
  //samplev.back()->fnamev.push_back("../baconbits/Zbb_old/ZLOcc.root");
  //samplev.back()->fnamev.push_back("../baconbits/Zbb_old/ZLOlf.root");
  
  // integrated luminosity to scale MC
  const double LUMI = 2.11; 
  
  // histograms for various corrections
  const string cmssw_base = getenv("CMSSW_BASE");
  // const string puWeightFilename = cmssw_base + string("/src/DMSAna/Utils/data/PUWeights_2012.root"); //no PU for phys14 
  

  //--------------------------------------------------------------------------------------------------------------
  // Main analysis code
  //==============================================================================================================

  //
  // Declare histograms
  //
  char hname[100];
  /*
  vector<TH1D*> hFatJetMassv, hNSubjetinessv;
  vector<TH1D*> hSubjetBtagv;
  */
  vector<TH1D*> hFatJetPtv;
  vector<double> neventsv;

  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    sprintf(hname,"hFatJetPt_%i",isam); hFatJetPtv.push_back(new TH1D(hname,"",25,360,1000)); hFatJetPtv[isam]->Sumw2();
    /*
    sprintf(hname,"hFatJetMass_%i",isam); hFatJetMassv.push_back(new TH1D(hname,"",25,30,120)); hFatJetMassv[isam]->Sumw2();
    sprintf(hname,"hNSubjetiness_%i",isam); hNSubjetinessv.push_back(new TH1D(hname,"",15,0.2,1)); hNSubjetinessv[isam]->Sumw2();
    sprintf(hname,"hSubjetBtag_%i",isam); hSubjetBtagv.push_back(new TH1D(hname,"",15,0,1)); hSubjetBtagv[isam]->Sumw2();
    */
    neventsv.push_back(0);
  }
  TH1D *hFatJetPtMC  = (TH1D*)hFatJetPtv[0]->Clone("hFatJetPtMC");
  /*
  TH1D *hFatJetMassMC  = (TH1D*)hFatJetMassv[0]->Clone("hFatJetMassMC");
  TH1D *hNSubjetinessMC  = (TH1D*)hNSubjetinessv[0]->Clone("hNSubjetinessMC");
  TH1D *hSubjetBtagMC  = (TH1D*)hSubjetBtagv[0]->Clone("hSubjetBtagMC");
  */
  TH1D *hFatJetPtSigZbb  = (TH1D*)hFatJetPtv[0]->Clone("hFatJetPtMC");
  TH1D *hFatJetPtSigVJets  = (TH1D*)hFatJetPtv[0]->Clone("hFatJetPtMC");
  TH1D *hFatJetPtBkgZbb  = (TH1D*)hFatJetPtv[0]->Clone("hFatJetPtMC");
  TH1D *hFatJetPtBkgVJets  = (TH1D*)hFatJetPtv[0]->Clone("hFatJetPtMC");
  /*
  TH1D *hFatJetMassSigZbb  = (TH1D*)hFatJetMassv[0]->Clone("hFatJetMassMC");
  TH1D *hFatJetMassSigVJets  = (TH1D*)hFatJetMassv[0]->Clone("hFatJetMassMC");
  TH1D *hFatJetMassBkgZbb  = (TH1D*)hFatJetMassv[0]->Clone("hFatJetMassMC");
  TH1D *hFatJetMassBkgVJets  = (TH1D*)hFatJetMassv[0]->Clone("hFatJetMassMC");
  */
  double neventsMC=0;
  double neventsBkgZbb=0;
  double neventsSigZbb=0;
  double neventsBkgVJets=0;
  double neventsSigVJets=0;
  
  //
  // variables to read in bacon bits
  //
  unsigned int metfilter;                        // MET filter bits
  float npu;                                     // mean expected PU
  unsigned int nf8PUPPIjets;         // PUPPIjet multiplicity
  unsigned int nf8CHSjets;         // CHSjet multiplicity
  float scale1fb;                                // cross section scale factor per 1/fb
  
  // boosted 0.8 cone variables                                                                                                                                                                            
  float           bst8_PUPPIjet1tau21;
  float           bst8_PUPPIjet1msd;
  float           bst8_PUPPIjet1minsubcsv;
  float           bst8_PUPPIjet1maxsubcsv;
  TLorentzVector           *bst8_PUPPIjet1=0;

  float           bst8_CHSjet1tau21;
  float           bst8_CHSjet1msd;
  float           bst8_CHSjet1minsubcsv;
  float           bst8_CHSjet1maxsubcsv;
  TLorentzVector           *bst8_CHSjet1=0;
  
  // TFile puWeightFile(puWeightFilename.c_str());
  // TH1D *hPUWeights = (TH1D*)puWeightFile.Get("pileup");
  // hPUWeights->SetDirectory(0);
  // puWeightFile.Close();
  
  TFile *infile=0;
  TTree *intree=0;
  
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    CSample *sample = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData   = (isam==0);
    bool isSigZbb = (isam==7);
    bool isSigVJets = (isam==4 || isam==5 || isam==6 || isam==7);

    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      intree = (TTree*)infile->Get("Events"); assert(intree);

      intree->SetBranchAddress("metfilter",    &metfilter);
      intree->SetBranchAddress("npu",          &npu);
      intree->SetBranchAddress("nf8PUPPIjets", &nf8PUPPIjets);
      intree->SetBranchAddress("nf8CHSjets",   &nf8CHSjets);
      intree->SetBranchAddress("scale1fb",     &scale1fb);
      
      // boosted 0.8 cone variables                                                                                                                                                                             
      intree->SetBranchAddress("bst8_PUPPIjet1tau21",      &bst8_PUPPIjet1tau21);
      intree->SetBranchAddress("bst8_PUPPIjet1msd",        &bst8_PUPPIjet1msd);
      intree->SetBranchAddress("bst8_PUPPIjet1minsubcsv",  &bst8_PUPPIjet1minsubcsv);
      intree->SetBranchAddress("bst8_PUPPIjet1maxsubcsv",  &bst8_PUPPIjet1maxsubcsv);
      intree->SetBranchAddress("bst8_PUPPIjet1",           &bst8_PUPPIjet1);
      intree->SetBranchAddress("bst8_CHSjet1tau21",        &bst8_CHSjet1tau21);
      intree->SetBranchAddress("bst8_CHSjet1msd",          &bst8_CHSjet1msd);
      intree->SetBranchAddress("bst8_CHSjet1minsubcsv",    &bst8_CHSjet1minsubcsv);
      intree->SetBranchAddress("bst8_CHSjet1maxsubcsv",    &bst8_CHSjet1maxsubcsv);
      intree->SetBranchAddress("bst8_CHSjet1",             &bst8_CHSjet1);
      
      double nevts=0;
      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
        intree->GetEntry(ientry);

	// common selection
	if(metfilter!=0)                   continue;

	// variable definition
	unsigned int    nf8jets;                               
	float           bst8_jet1tau21;
	float           bst8_jet1msd;
	float           bst8_jet1minsubcsv;
	float           bst8_jet1maxsubcsv;
	float           bst8_jet1pt;
	TLorentzVector           *bst8_jet1=0;

	if(algo=="PUPPI")
	  {
	    nf8jets = nf8PUPPIjets;
	    bst8_jet1msd = bst8_PUPPIjet1msd;
	    bst8_jet1tau21 = bst8_PUPPIjet1tau21;
	    bst8_jet1minsubcsv = bst8_PUPPIjet1minsubcsv;
            bst8_jet1maxsubcsv = bst8_PUPPIjet1maxsubcsv;
	    bst8_jet1pt = bst8_PUPPIjet1->Pt();
	  }
        if(algo=="CHS")
          {
            nf8jets = nf8CHSjets;
            bst8_jet1msd = bst8_CHSjet1msd;
            bst8_jet1tau21 = bst8_CHSjet1tau21;
            bst8_jet1minsubcsv = bst8_CHSjet1minsubcsv;
            bst8_jet1maxsubcsv = bst8_CHSjet1maxsubcsv;
            bst8_jet1pt = bst8_CHSjet1->Pt();
          }

	bool passZbbNoCutPtMassBtaggingTau21 = (nf8jets>0);

	//
	//Apply the selection
	//
	
        double wgt_Sig = 1;
	double QCD = 1;
	//Zbb - more cuts can be added here
	if (selection == "Zbb")
	  {
            if (subsample == "NoCutPtMassBtaggingTau21") if (!passZbbNoCutPtMassBtaggingTau21) continue;
	  }

	double wgt = 1;
        if(!isData) {     
	  wgt *= LUMI*scale1fb;
	  wgt_Sig *= LUMI*scale1fb;
	  if (isam==1) { wgt_Sig *= QCD;}
        }
        nevts += wgt;

	float fjet_pt = bst8_jet1pt;
	float fjet_mass = bst8_jet1msd;
	float nsubjet = bst8_jet1tau21;
	float subjetbtag = bst8_jet1maxsubcsv;

        neventsv[isam]+=wgt;
        hFatJetPtv[isam]     ->Fill(fjet_pt,       wgt);
	/*
	hFatJetMassv[isam]     ->Fill(fjet_mass,       wgt);
	hNSubjetinessv[isam]     ->Fill(nsubjet,       wgt);
	hSubjetBtagv[isam]    ->Fill(subjetbtag,       wgt);
	*/
        if(!isData){ 
	  neventsMC+=wgt;
	  hFatJetPtMC    ->Fill(fjet_pt,       wgt);
	  /*
	  hFatJetMassMC    ->Fill(fjet_mass,       wgt);
	  hNSubjetinessMC    ->Fill(nsubjet,       wgt);
	  hSubjetBtagMC    ->Fill(subjetbtag,       wgt);
	  */
        }
	
	if(!isData){
	  if(!isSigZbb) {
	    neventsBkgZbb+=wgt;
            hFatJetPtBkgZbb ->Fill(fjet_pt,       wgt_Sig);
	    //hFatJetMassBkgZbb ->Fill(fjet_mass,       wgt_Sig);
	  } else {
	    neventsSigZbb+=wgt;
            hFatJetPtSigZbb ->Fill(fjet_pt,       wgt_Sig);
	    //hFatJetMassSigZbb ->Fill(fjet_mass,       wgt_Sig);
	  }
	  if(!isSigVJets) {
	    neventsBkgVJets+=wgt;
            hFatJetPtBkgVJets ->Fill(fjet_pt,       wgt_Sig);
            //hFatJetMassBkgVJets ->Fill(fjet_mass,       wgt_Sig);
          } else {
            neventsSigVJets+=wgt;
            hFatJetPtSigVJets ->Fill(fjet_pt,       wgt_Sig);
            //hFatJetMassSigVJets ->Fill(fjet_mass,       wgt_Sig);
          }
	}
	
      }

      if(isData && doBlind) {
        cout << endl;
      } else {
	cout << nevts << " " << scale1fb << endl;
      }
      delete infile;
      infile=0;
      intree=0;
    }
  }

  //
  // QCD Scale Factor
  //
  double QCDSF = 1.0;
  QCDSF = (neventsv[0]-(neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]+neventsv[6]+neventsv[7]))/neventsv[1];
  hFatJetPtv[1]->Scale(QCDSF);
  /*
  hFatJetMassv[1]->Scale(QCDSF);
  hNSubjetinessv[1]->Scale(QCDSF);
  hSubjetBtagv[1]->Scale(QCDSF);
  */

  //
  // Normalize histograms
  //
  /*
    hNSubjetinessv[0]->Scale(1/hNSubjetinessv[0]->Integral());
    hNSubjetinessv[1]->Scale(1/hNSubjetinessv[1]->Integral());
    hNSubjetinessMC->Scale(1/hNSubjetinessMC->Integral());
    hSubjetBtagMC->Scale(1/hSubjetBtagMC->Integral());
    hSubjetBtagv[0]->Scale(1/hSubjetBtagv[0]->Integral());
    hSubjetBtagv[1]->Scale(1/hSubjetBtagv[1]->Integral());
  */
  
  //
  // Make pull histograms
  //
  TH1D *hFatJetPtPull = makePullHist(hFatJetPtv[0], hFatJetPtMC, "hFatJetPtPull",  doBlind);
  /*
  TH1D *hFatJetMassPull = makePullHist(hFatJetMassv[0], hFatJetMassMC, "hFatJetMassPull",  doBlind);
  TH1D *hNSubjetinessPull = makePullHist(hNSubjetinessv[0], hNSubjetinessMC, "hNSubjetinessPull",  doBlind);
  TH1D *hSubjetBtagPull = makePullHist(hSubjetBtagv[0], hSubjetBtagMC, "hSubjetBtagPull",  doBlind);
  */
  //
  // Calculate significance
  //
  float CalcSigZbb = CalcSig(hFatJetPtSigZbb, hFatJetPtBkgZbb);
  float CalcSigVJets = CalcSig(hFatJetPtSigVJets, hFatJetPtBkgVJets);

  float SqrtBkgZbb = neventsv[7]/sqrt(neventsv[1]*QCDSF+neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]+neventsv[6]);
  float SqrtBkgVJets = (neventsv[4]+neventsv[5]+neventsv[6]+neventsv[7])/sqrt(neventsv[1]*QCDSF+neventsv[2]+neventsv[3]);
  /*
  float CalcSigZbb = CalcSig(hFatJetMassSigZbb, hFatJetMassBkgZbb);
  float CalcSigVJets = CalcSig(hFatJetMassSigVJets, hFatJetMassBkgVJets);
  
  float SqrtBkgZbb = neventsv[7]/sqrt(neventsv[1]*QCDSF+neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5]+neventsv[6]);
  float SqrtBkgVJets = (neventsv[4]+neventsv[5]+neventsv[6]+neventsv[7])/sqrt(neventsv[1]*QCDSF+neventsv[2]+neventsv[3]);
  */
  //--------------------------------------------------------------------------------------------------------------
  // Output
  //==============================================================================================================
   
  cout << "*" << endl;
  cout << "* SUMMARY" << endl;
  cout << "*--------------------------------------------------" << endl;
  cout << "Zbb significance: " << CalcSigZbb << endl;
  cout << "Zbb signal/sqrt(B): " << SqrtBkgZbb << endl;
  cout << "VJets significance: " << CalcSigVJets << endl;
  cout << "VJets signal/sqrt(B): " << SqrtBkgVJets << endl;
  cout << "QCDSF:"<< QCDSF << endl;
  cout << "*--------------------------------------------------" << endl;
  cout << endl;

  ofstream txtfile;
  char txtfname[200];
  sprintf(txtfname,"%s/summary_%s.txt",outputDir.c_str(),subsample.c_str());
  txtfile.open(txtfname);
  txtfile << setprecision(2) << fixed;
  for(unsigned int isam=1; isam<samplev.size(); isam++) {
    if(isam == 1) neventsv[isam] = QCDSF*neventsv[isam];
    //if(isam == 0) neventsv[isam] = (1/hSubjetBtagv[0]->Integral())*neventsv[isam];
    //if(isam == 1) neventsv[isam] = (1/hSubjetBtagv[1]->Integral())*neventsv[isam];
    txtfile << setw(35) << samplev[isam]->label;
    txtfile << setw(15) << neventsv[isam] << endl;
  }
  txtfile << "---------------------------------------------"  << endl;
  txtfile << setw(35) << "SM Expected:" << setw(15) << neventsv[1]+neventsv[2]+neventsv[3]+neventsv[4]+neventsv[5] << endl;
  if(!doBlind) { txtfile << setw(35) << "Observed:" << setw(15) << neventsv[0] << endl; }
  txtfile << "QCD Scale Factor:" << QCDSF << endl;
  txtfile << "Zbb significance: " << CalcSigZbb << endl;
  txtfile << "Zbb signal/sqrt(B): " << SqrtBkgZbb << endl;
  txtfile << "VJets significance: " << CalcSigVJets << endl;
  txtfile << "VJets signal/sqrt(B): " << SqrtBkgVJets << endl;
  txtfile.close();

   //--------------------------------------------------------------------------------------------------------------
  // Make plots
  //==============================================================================================================

  TCanvas *c = MakeCanvas("c","c",800,800);
  // c->Divide(1,2,0,0);
  // c->cd(1)->SetPad(0,0.3,1.0,1.0);
  // c->cd(1)->SetTopMargin(0.1);
  // c->cd(1)->SetBottomMargin(0);
  // c->cd(1)->SetLeftMargin(0.15);
  // c->cd(1)->SetRightMargin(0.07);
  // c->cd(1)->SetTickx(1);
  // c->cd(1)->SetTicky(1);

  // c->cd(2)->SetPad(0,0,1.0,0.3);
  // c->cd(2)->SetTopMargin(0);
  // c->cd(2)->SetBottomMargin(0.45);
  // c->cd(2)->SetLeftMargin(0.15);
  // c->cd(2)->SetRightMargin(0.07);
  // c->cd(2)->SetTickx(1);
  // c->cd(2)->SetTicky(1);

  //  c->SetPad(0,0.3,1.0,1.0);
  c->SetTopMargin(0.1);
  c->SetBottomMargin(0.15);
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.07);
  c->SetTickx(1);
  c->SetTicky(1);

  char ylabel[100];
  
  sprintf(ylabel,"Events / %i GeV/c^{2}",int(hFatJetPtv[0]->GetBinWidth(10)));
  makePlot(c, "Pt_"+subsample, "Fat Jet Pt [GeV]", ylabel, hFatJetPtv, samplev, hFatJetPtMC, hFatJetPtPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.2*(hFatJetPtMC->GetBinContent(hFatJetPtMC->GetMaximumBin())), selection, subsample);
  /*
  sprintf(ylabel,"Events / %i ",int(hNSubjetinessv[0]->GetBinWidth(10)));
  makePlot(c, "tau21_"+subsample, "#tau_{2}/#tau_{1}", ylabel, hNSubjetinessv, samplev, hNSubjetinessMC, hNSubjetinessPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hNSubjetinessMC->GetBinContent(hNSubjetinessMC->GetMaximumBin())), selection, subsample);

  sprintf(ylabel,"Events / %i GeV/c^{2}",int(hFatJetMassv[0]->GetBinWidth(10)));
  makePlot(c, "msd_"+subsample, "Soft Drop Mass [GeV/c^{2}]", ylabel, hFatJetMassv, samplev, hFatJetMassMC, hFatJetMassPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.2*(hFatJetMassMC->GetBinContent(hFatJetMassMC->GetMaximumBin())), selection, subsample);
  //0.0,-0.03  
  
  sprintf(ylabel,"Events / %i ",int(hSubjetBtagv[0]->GetBinWidth(10)));
  makePlot(c, "subjetbtag_"+subsample, "Max Subjet b-Tag Score", ylabel, hSubjetBtagv, samplev, hSubjetBtagMC, hSubjetBtagPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 1.5*(hSubjetBtagMC->GetBinContent(hSubjetBtagMC->GetMaximumBin())), selection, subsample);
  */
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
  
  histv[0]->SetMarkerSize(0.9);
  
  //gPad->SetLeftMargin(0.15); //left margin is 15 per cent of the pad width
  //histv[0]->GetYaxis()->SetTitleOffset(2);

  CPlot plot(outname.c_str(),"",xlabel.c_str(),ylabel.c_str());  
  //  plot.AddHist1D(hExp,"E2",uncColor,1,3004);
  if(!doBlind) { plot.AddHist1D(histv[0],samplev[0]->label,"E"); }
  for(unsigned int i=1; i<histv.size(); i++) {
    //for(unsigned int i=0; i<histv.size(); i++) {
    //plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }
    
  char lumitext[100];
  sprintf(lumitext,"%.1f fb^{-1} (13 TeV)",lumi);
  plot.AddTextBox(lumitext,0.66,0.99,0.95,0.925,0,kBlack);
  plot.AddTextBox("CMS",0.18,0.88,0.30,0.82,0,kBlack,62);
  plot.AddTextBox("Preliminary",0.18,0.82,0.37,0.77,0,kBlack,52);
  const double xmin = histv[0]->GetXaxis()->GetBinLowEdge(1);
  const double xmax = histv[0]->GetXaxis()->GetBinUpEdge(histv[0]->GetNbinsX());

  plot.AddLine(xmin,0,xmax,0,kBlack,3);

  plot.TransLegend(legdx, legdy);
  
  if(doLogy) {
    plot.SetLogy();
  }
  
  if(ymin!=ymax) {
    plot.SetYRange(ymin,ymax);
  }

  hPull->SetMarkerSize(0.8);
  // const double xmin = histv[0]->GetXaxis()->GetBinLowEdge(1);
  // const double xmax = histv[0]->GetXaxis()->GetBinUpEdge(histv[0]->GetNbinsX());
  CPlot plotPull(outname.c_str(),"",xlabel.c_str(),"Pull");
  plotPull.AddHist1D(hPull,"EX0",kBlack);
  plotPull.SetYRange(-5.9,5.9);
  plotPull.AddLine(xmin,0,xmax,0,kBlack,3);

  plot.Draw(c,true,"png");
  //plotPull.Draw(c,true,"png",2);
  //plotPull.Draw(c,true,"pdf",2);
}

//--------------------------------------------------------------------------------------------------
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind)
{
  TH1D *hPull = new TH1D(name.c_str(),"",hData->GetNbinsX(),hData->GetXaxis()->GetXmin(),hData->GetXaxis()->GetXmax());
  for(int ibin=1; ibin<=hData->GetNbinsX(); ibin++) {
    double numer = hData->GetBinContent(ibin) - hMC->GetBinContent(ibin);
    double denom = sqrt((hData->GetBinError(ibin))*(hData->GetBinError(ibin)) + (hMC->GetBinError(ibin))*(hMC->GetBinError(ibin)));
    double pull  = (denom>0) ? numer/denom : 0;
    double err   = (denom>0) ? 1 : 0;

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
float DeltaR(float eta1,float phi1,float eta2,float phi2)
{
  float deltaPhi = TMath::Abs(phi1-phi2);
  float deltaEta = eta1-eta2;
  if(deltaPhi > TMath::Pi())
    deltaPhi = TMath::TwoPi() - deltaPhi;
  return TMath::Sqrt(deltaEta*deltaEta + deltaPhi*deltaPhi);
}

//-------------------------------------------------------------------------------------------------- 
float CalcSig(TH1D*sig, TH1D*bkg) {
  float fSig2 = 0;
  int nb = sig->GetNbinsX();
  std::cout << "nb = " << nb << std::endl;                                                                                                                                                          
  for (int i = 0; i <= nb+1; i++) {
    if (sig->GetBinContent(i) > 0 && bkg->GetBinContent(i)>0) {
      //cout << "bin:" << i << endl;
      //cout << "bkg_i = " << bkg->GetBinContent(i) << endl;                                                                                                                                                        
      //cout << "sig_i = " << sig->GetBinContent(i) << endl;
      fSig2 += pow(sig->GetBinContent(i),2)/bkg->GetBinContent(i);
      //cout << "fSig2 = " << fSig2 << endl;
      //cout << "signal/sqrt(bkg) = "<< sig->GetBinContent(i)/sqrt(bkg->GetBinContent(i)) << endl;
    }
  }
  //cout << "fTotal = " << fSig2 <<endl;
  return sqrt(fSig2);
}
