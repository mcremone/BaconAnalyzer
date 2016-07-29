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
#include "../macros/RazorBitsLoader.hh"    // helper to load razorbits
//#endif

using namespace std;

//Object Processors                                                                                                                                                                                      
RazorBitsLoader       *fBits      = 0;

//=== FUNCTION DECLARATIONS ======================================================================================

// make "standard" plot
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              const bool doBlind, const double lumi, const bool doLogy=false, const double legdx=0, const double legdy=0,
              const double ymin=-1, const double ymax=-1, const string subsample="");
TH1D* makePullHist(TH1D* hData, TH1D* hMC, const string name, const bool doBlind);
float CalcSig(TH1D*sig, TH1D*bkg);

//=== MAIN MACRO =================================================================================================

void plotRazor(const string preselection, const string subsample, const string combo, TString algo, TString syst)
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  const bool doBlind = true;

  // Create output directory 
  const string outputDir("razorplots/"+preselection+"_"+subsample+"_"+combo+"_"+algo);
  gSystem->mkdir(outputDir.c_str(), true);
  CPlot::sOutDir = outputDir;

  //
  // Samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;
  //cout <<"preselection = " <<  preselection.c_str() << endl;
  samplev.push_back(new CSample("data",0,0));
  if (preselection.compare("Had")==0) samplev.back()->fnamev.push_back("../razorbits/JetHT.root");
  if (preselection.compare("MET")==0) samplev.back()->fnamev.push_back("../razorbits/MET.root"); 
  if (preselection.compare("Muo")==0 || preselection.compare("Zmm")==0)  samplev.back()->fnamev.push_back("../razorbits/SingleMuon.root");
  if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("../razorbits/SingleElectron.root");
  if (preselection.compare("Pho")==0) { samplev.back()->fnamev.push_back("../razorbits/SinglePhoton.root");
  samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
  samplev.back()->fnamev.push_back("../razorbits/QCD.root");
  }
  if (preselection.compare("Pho")!=0) {
    samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
    samplev.back()->fnamev.push_back("../razorbits/QCD.root");
    samplev.push_back(new CSample("Single Top",kBlue - 2,kBlue - 2));
    samplev.back()->fnamev.push_back("../razorbits/T.root");
    samplev.push_back(new CSample("t#bar{t}",kPink - 2,kPink - 2));
    samplev.back()->fnamev.push_back("../razorbits/TT.root");
    samplev.push_back(new CSample("Diboson",kRed - 2,kRed - 2));
    samplev.back()->fnamev.push_back("../razorbits/WW.root");
    samplev.back()->fnamev.push_back("../razorbits/WZ.root");
    samplev.back()->fnamev.push_back("../razorbits/ZZ.root");
    samplev.push_back(new CSample("W+jets",kGreen - 2,kGreen - 2));
    samplev.back()->fnamev.push_back("../razorbits/WHF.root");
    samplev.back()->fnamev.push_back("../razorbits/WLF.root");
    samplev.push_back(new CSample("Z+jets", kAzure - 2, kAzure - 2));
    samplev.back()->fnamev.push_back("../razorbits/ZHF.root");   
    samplev.back()->fnamev.push_back("../razorbits/ZLF.root");
    samplev.back()->fnamev.push_back("../razorbits/DYHF.root");
    samplev.back()->fnamev.push_back("../razorbits/DYLF.root");
  }
  if (preselection.compare("Pho")==0){
    samplev.push_back(new CSample("#gamma+jets", kAzure + 7, kAzure + 7));
    samplev.back()->fnamev.push_back("../razorbits/GHF.root");
    samplev.back()->fnamev.push_back("../razorbits/GLF.root");
  }
  // if (subsample.compare("SR")==0){   
  //   samplev.push_back(new CSample("????", kBlue, kBlue));
  //   samplev.back()->fnamev.push_back("../razorbits/????.root");
  // }

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
  vector<TH1D*> hHTv, hMHTv;
  vector<TH1D*> hNJetsv;
  vector<TH1D*> hMRv, hRsqv, hdeltaPhiv;
  vector<double> neventsv;
  const Int_t NBINS = 5;
  Double_t edges[NBINS + 1] = {250,300,350,400,500,1000};
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    sprintf(hname,"hMET_%i",isam);            hMETv.push_back(new TH1D(hname,"",NBINS,edges));            hMETv[isam]->Sumw2();
    sprintf(hname,"hMETLog_%i",isam);         hMETLogv.push_back(new TH1D(hname,"",NBINS,edges));         hMETLogv[isam]->Sumw2();
    sprintf(hname,"hHT_%i",isam);             hHTv.push_back(new TH1D(hname,"",20,100,600));              hHTv[isam]->Sumw2();
    sprintf(hname,"hMHT_%i",isam);            hMHTv.push_back(new TH1D(hname,"",30,300,2000));            hMHTv[isam]->Sumw2();
    sprintf(hname,"hNJets_%i",isam);          hNJetsv.push_back(new TH1D(hname,"",10,0,10));              hNJetsv[isam]->Sumw2();
    ///sprintf(hname,"halphaT_%i",isam);         halphaTv.push_back(new TH1D(hname,"",20,0,2.5));            halphaTv[isam]->Sumw2();
    //sprintf(hname,"hmindFPhi_%i",isam);       hmindFPhiv.push_back(new TH1D(hname,"",20,0,3.14));         hmindFPhiv[isam]->Sumw2();
    sprintf(hname,"hMR_%i",isam);             hMRv.push_back(new TH1D(hname,"",50,200.,3000.));             hMRv[isam]->Sumw2();
    sprintf(hname,"hRsq_%i",isam);            hRsqv.push_back(new TH1D(hname,"",20,0.2,1.2));             hRsqv[isam]->Sumw2();
    sprintf(hname,"hdeltaPhi_%i",isam);       hdeltaPhiv.push_back(new TH1D(hname,"",20,0,3.14));         hdeltaPhiv[isam]->Sumw2();

    neventsv.push_back(0);
  }

  TH1D *hMETMC             = (TH1D*)hMETv[0]->Clone("hMETMC");
  TH1D *hMETLogMC          = (TH1D*)hMETLogv[0]->Clone("hMETLogMC");
  TH1D *hHTMC              = (TH1D*)hHTv[0]->Clone("hHTMC");
  TH1D *hMHTMC             = (TH1D*)hMHTv[0]->Clone("hMHTMC");
  TH1D *hNJetsMC           = (TH1D*)hNJetsv[0]->Clone("hNJetsMC");
  //TH1D *halphaTMC          = (TH1D*)halphaTv[0]->Clone("halphaTMC");
  //TH1D *hmindFPhiMC        = (TH1D*)hmindFPhiv[0]->Clone("hmindFPhiMC");
  TH1D *hMRMC              = (TH1D*)hMRv[0]->Clone("hMRMC");
  TH1D *hRsqMC             = (TH1D*)hRsqv[0]->Clone("hRsqMC");
  TH1D *hdeltaPhiMC        = (TH1D*)hdeltaPhiv[0]->Clone("hdeltaPhiMC");

  // TH1D *hMETSig1           = (TH1D*)hMETv[0]->Clone("hMETSig1");
  // TH1D *hMETSig2           = (TH1D*)hMETv[0]->Clone("hMETSig2");
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
    // bool isSignal  = (isam==samplev.size()-1 || isam==samplev.size()-2);
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
      infile->ls();
      intree = (TTree*)infile->Get("Events"); assert(intree);
      fBits  = new RazorBitsLoader(intree,algo,syst,preselection);
      double nevts=0;
      int noweight=0;
      double wgt = 0;
      std::cout << intree->GetEntries() << std::endl;
      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
        intree->GetEntry(ientry);
	if(!doBlind && subsample.compare("SR")==0 && ientry % 5 != 0) continue;
	if(!fBits->selectJetAlgoAndSize(algo)) continue;
	// common selection
	if(fBits->metfilter!=0)                   continue;
	//preselection
	if(!fBits->passPreSelection(preselection)) continue;
	//selection
	//if(!fBits->passRazorSR(preselection, isData)) continue;
	if(!fBits->passSelection(preselection, subsample, combo, isData)) continue;

	// Apply weigths                                                                                                                                                                            
        wgt = 1;
        wgt *= fBits->getWgt(isData,algo,LUMI);

	nevts += wgt;
	noweight++;
	
        neventsv[isam]+=wgt;
        hMETv[isam]            ->Fill(fBits->vmetpt,       wgt);
        hMETLogv[isam]         ->Fill(fBits->vmetpt,       wgt);
        hHTv[isam]             ->Fill(fBits->HT,                              wgt);
        hMHTv[isam]            ->Fill(fBits->MHT,                             wgt);
        hNJetsv[isam]          ->Fill(fBits->njets,                           wgt);
       // halphaTv[isam]         ->Fill(fBits->alphaT,                          wgt);
       // hmindFPhiv[isam]       ->Fill(fBits->mindFPhi,                        wgt);
        hMRv[isam]             ->Fill(fBits->MR,                              wgt);
        hRsqv[isam]            ->Fill(fBits->Rsq,                             wgt);
        hdeltaPhiv[isam]       ->Fill(fBits->deltaPhi,                        wgt);
	//	if((!isData && subsample.compare("SR")!=0) || (!isData  && !isSignal && subsample.compare("SR")==0)){
	if(!isData){
          neventsMC+=wgt;
          hMETMC            ->Fill(fBits->vmetpt,       wgt);
          hMETLogMC         ->Fill(fBits->vmetpt,       wgt);
	  hHTMC             ->Fill(fBits->HT,                              wgt);
	  hMHTMC             ->Fill(fBits->MHT,                             wgt);
	  hNJetsMC          ->Fill(fBits->njets,                           wgt);
	  //halphaTMC         ->Fill(fBits->alphaT,                          wgt);
	 // hmindFPhiMC       ->Fill(fBits->mindFPhi,                        wgt);
	  hMRMC             ->Fill(fBits->MR,                              wgt);
	  hRsqMC            ->Fill(fBits->Rsq,                             wgt);
	  hdeltaPhiMC       ->Fill(fBits->deltaPhi,                        wgt);
        }
	// if(!isData){
	//   if(isSignal1) hMETSig1->Fill(fBits->vmetpt,       wgt);
	//   if(isSignal2) hMETSig2->Fill(fBits->vmetpt,       wgt);
	//   // if(isSignal3) hMETSig3->Fill(fBits->vmetpt,       wgt);
	//   // if(isSignal4) hMETSig4->Fill(fBits->vmetpt,       wgt);
	//   // if(isSignal5) hMETSig5->Fill(fBits->vmetpt,       wgt);
        //   // if(isSignal6) hMETSig6->Fill(fBits->vmetpt,       wgt);
	// }

      }
      if (!isData && doBlind) 
      {
        cout << nevts << " " << noweight  << " " << wgt << endl;
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
  TH1D *hHTPull             = makePullHist(hHTv[0],             hHTMC,             "hHTPull",              doBlind);
  TH1D *hMHTPull            = makePullHist(hMHTv[0],            hMHTMC,            "hMHTPull",             doBlind);
  TH1D *hNJetsPull          = makePullHist(hNJetsv[0],          hNJetsMC,          "hNJetsPull",           doBlind);
 // TH1D *halphaTPull         = makePullHist(halphaTv[0],         halphaTMC,         "halphaTPull",          doBlind);
 // TH1D *hmindFPhiPull       = makePullHist(hmindFPhiv[0],       hmindFPhiMC,       "hmindFPhiPull",        doBlind);
  TH1D *hMRPull             = makePullHist(hMRv[0],             hMRMC,             "hMRPull",              doBlind);
  TH1D *hRsqPull            = makePullHist(hRsqv[0],            hRsqMC,            "hRsqPull",             doBlind);
  TH1D *hdeltaPhiPull       = makePullHist(hdeltaPhiv[0],       hdeltaPhiMC,       "hdeltaPhiPull",        doBlind);

  //                                                                                                                                                                                                    
  // Calculate significance                                                                                                                                                                               
  //                 
  // vector<float> significance;                                                                                                                                                                                
  // significance.push_back(CalcSig(hMETSig1, hMETMC));
  // significance.push_back(CalcSig(hMETSig2, hMETMC));
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
      //txtfile << setw(15) << significance[samplev.size()-isam-1] << endl;
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
           0.1, 2.1*(hMETMC->GetBinContent(hMETMC->GetMaximumBin()))/(hMETMC->GetBinWidth(hMETMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "met", "U [GeV]", ylabel, hMETLogv, samplev, hMETLogMC, hMETLogPull, doBlind, LUMI, true, 0.0, -0.03,
           2e-5*(hMETLogMC->GetBinContent(hMETLogMC->GetMaximumBin()))/(hMETLogMC->GetBinWidth(hMETLogMC->GetMaximumBin())), 
	   4e2*(hMETLogMC->GetBinContent(hMETLogMC->GetMaximumBin()))/(hMETLogMC->GetBinWidth(hMETLogMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "ht", "H_{T} [GeV]", ylabel, hHTv, samplev, hHTMC, hHTPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hHTMC->GetBinContent(hHTMC->GetMaximumBin()))/(hHTMC->GetBinWidth(hHTMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / GeV");
  makePlot(c, "mht", "H_{T}^{miss} [GeV]", ylabel, hMHTv, samplev, hMHTMC, hMHTPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hMHTMC->GetBinContent(hMHTMC->GetMaximumBin()))/(hMHTMC->GetBinWidth(hHTMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / %i ",int(hNJetsv[0]->GetBinWidth(1)));
  makePlot(c, "njets", "N_{jets} (AK4)", "Events", hNJetsv, samplev, hNJetsMC, hNJetsPull, doBlind, LUMI, false, 0.0, -0.03,
           0.1, 2.1*(hNJetsMC->GetBinContent(hNJetsMC->GetMaximumBin()))/(hNJetsMC->GetBinWidth(hNJetsMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / GeV");
//  makePlot(c, "alphat", "#alpha_{T} [GeV]", ylabel, halphaTv, samplev, halphaTMC, halphaTPull, doBlind, LUMI, false, 0.0, -0.03,
 //          0.1, 2.1*(halphaTMC->GetBinContent(halphaTMC->GetMaximumBin()))/(halphaTMC->GetBinWidth(halphaTMC->GetMaximumBin())), subsample);

//  sprintf(ylabel,"Events / %.1f ",hmindFPhiv[0]->GetBinWidth(1));
//  makePlot(c, "mindfphi", "#Delta#phi*_{min}", ylabel, hmindFPhiv, samplev, hmindFPhiMC, hmindFPhiPull, doBlind, LUMI, false, -0.4, -0.15,
//           0.1, 2.1*(hmindFPhiMC->GetBinContent(hmindFPhiMC->GetMaximumBin()))/(hmindFPhiMC->GetBinWidth(hmindFPhiMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / %.1f ",hMRv[0]->GetBinWidth(1));
  makePlot(c, "mr", "M_{R} [GeV]", ylabel, hMRv, samplev, hMRMC, hMRPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hMRMC->GetBinContent(hMRMC->GetMaximumBin()))/(hMRMC->GetBinWidth(hMRMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / %.1f ",hRsqv[0]->GetBinWidth(1));
  makePlot(c, "rsq", "R^{2}", ylabel, hRsqv, samplev, hRsqMC, hRsqPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hRsqMC->GetBinContent(hRsqMC->GetMaximumBin()))/(hRsqMC->GetBinWidth(hRsqMC->GetMaximumBin())), subsample);

  sprintf(ylabel,"Events / %.1f ",hdeltaPhiv[0]->GetBinWidth(1));
  makePlot(c, "deltaphi", "#Delta#phi*", ylabel, hdeltaPhiv, samplev, hdeltaPhiMC, hdeltaPhiPull, doBlind, LUMI, false, -0.4, -0.15,
           0.1, 2.1*(hdeltaPhiMC->GetBinContent(hdeltaPhiMC->GetMaximumBin()))/(hdeltaPhiMC->GetBinWidth(hdeltaPhiMC->GetMaximumBin())), subsample);

  cout << endl;
  cout << " <> Output saved in " << outputDir << endl;
  cout << endl; 
}

//=== FUNCTION DEFINITIONS ======================================================================================

//--------------------------------------------------------------------------------------------------
void makePlot(TCanvas *c, const string outname, const string xlabel, const string ylabel,
              const vector<TH1D*>& histv, const vector<CSample*>& samplev, TH1D* hExp, TH1D* hPull,
              bool doBlind, const double lumi, const bool doLogy, const double legdx, const double legdy,
              const double ymin, const double ymax, const string subsample)
{
  const int uncColor = kGray+3;
  // should divide by bin width
  for (int iB=1; iB<hExp->GetNbinsX()+1; ++iB) {
    float currentVal = hExp->GetBinContent(iB);
    float currentErr = hExp->GetBinError(iB);
    float binWidth = hExp->GetBinWidth(iB);
    hExp->SetBinContent(iB,currentVal/binWidth);
    //hExp->SetBinContent(iB,currentVal);
    hExp->SetBinError(iB,currentErr/binWidth);
    //hExp->SetBinError(iB,currentErr);
  }
  for(unsigned int i=0; i<histv.size(); i++) {
    for (int iB=1; iB<histv[i]->GetNbinsX()+1; ++iB) {
      float currentVal = histv[i]->GetBinContent(iB);
      float currentErr = histv[i]->GetBinError(iB);
      float binWidth = histv[i]->GetBinWidth(iB);
      histv[i]->SetBinContent(iB,currentVal/binWidth);
      //histv[i]->SetBinContent(iB,currentVal);
      histv[i]->SetBinError(iB,currentErr/binWidth);
      //histv[i]->SetBinError(iB,currentErr);
    }
  }
  
  histv[0]->SetMarkerSize(0.9);
  
  CPlot plot(outname.c_str(),"",xlabel.c_str(),ylabel.c_str());  
  plot.AddHist1D(hExp,"E2",uncColor,1,3004);
  if(!doBlind) { plot.AddHist1D(histv[0],samplev[0]->label,"E"); }
  float max = samplev.size();
  if (subsample.compare("SR")==0) max = samplev.size(); 
  for(unsigned int i=1; i<max; i++) {
    plot.AddToStack(histv[i],samplev[i]->label,samplev[i]->fillcolor,samplev[i]->linecolor);
  }
  if (subsample.compare("SR")==0){
    for(unsigned int i=max; i<histv.size(); i++) {
      plot.AddHist1D(histv[i],samplev[i]->label,"hist",samplev[i]->fillcolor,samplev[i]->linecolor);
    }
  }
  char lumitext[100];
  sprintf(lumitext,"%.2f fb^{-1} (13 TeV)",lumi);
  // plot.AddTextBox(lumitext,0.66,0.99,0.95,0.925,0,kBlack);
  // plot.AddTextBox("CMS",0.68,0.88,0.80,0.82,0,kBlack,62);
  // plot.AddTextBox("Preliminary",0.68,0.82,0.87,0.77,0,kBlack,52);
  plot.AddTextBox(lumitext,0.66,0.99,0.95,0.925,0,kBlack);
  plot.AddTextBox("CMS",0.18,0.88,0.30,0.82,0,kBlack,62);
  plot.AddTextBox("Preliminary",0.18,0.82,0.37,0.77,0,kBlack,52);
  //plot.AddTextBox("Work In Progress",0.18,0.82,0.37,0.77,0,kBlack,52);   

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
  CPlot plotPull(outname.c_str(),"",xlabel.c_str(),"Data / Pred.");
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
    // double numer = hData->GetBinContent(ibin) - hMC->GetBinContent(ibin);
    // double denom = sqrt((hData->GetBinError(ibin))*(hData->GetBinError(ibin)) + (hMC->GetBinError(ibin))*(hMC->GetBinError(ibin)));
    // double pull  = (denom>0) ? numer/denom : 0;
    // double err   = (denom>0) ? 1 : 0;

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
  //hPull->GetXaxis()->CenterTitle();

  return hPull;
}

//--------------------------------------------------------------------------------------------------
void makeHTML(const string outputDir)
{
  enum { kBST_ONLY=0, kRES_ONLY, kMJ_ONLY, kBST_COMBO, kRES_COMBO, kMJ_COMBO, kBST_PRE, kRES_PRE, kMJ_PRE };

  ofstream htmlfile;
  char htmlfname[200];
  sprintf(htmlfname,"%s/plots.html",outputDir.c_str());
  htmlfile.open(htmlfname);
  htmlfile << "<!DOCTYPE html" << endl;
  htmlfile << " PUBLIC \"-//W3C//DTD HTML 3.2//EN\">" << endl;
  htmlfile << "<html>" << endl;
  htmlfile << "<head><title>B2G Selection</title></head>" << endl;
  htmlfile << "<body bgcolor=\"EEEEEE\">" << endl;

  htmlfile << "<table border=\"0\" cellspacing=\"5\" width=\"100%\">" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"met.png\"><img src=\"met.png\" alt=\"met.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"metlog.png\"><img src=\"metlog.png\" alt=\"metlog.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"njets.png\"><img src=\"njets.png\" alt=\"njets.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"nbjets.png\"><img src=\"nbjets.png\" alt=\"nbjets.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "</table>" << endl;

  htmlfile << "<table border=\"0\" cellspacing=\"5\" width=\"100%\">" << endl;
  htmlfile << "<tr>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet1pt.png\"><img src=\"jet1pt.png\" alt=\"jet1pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet1eta.png\"><img src=\"jet1eta.png\" alt=\"jet1eta.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet1phi.png\"><img src=\"jet1phi.png\" alt=\"jet1phi.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet2pt.png\"><img src=\"jet2pt.png\" alt=\"jet2pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet2eta.png\"><img src=\"jet2eta.png\" alt=\"jet2eta.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet2phi.png\"><img src=\"jet2phi.png\" alt=\"jet2phi.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet3pt.png\"><img src=\"jet3pt.png\" alt=\"jet3pt.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet3eta.png\"><img src=\"jet3eta.png\" alt=\"jet3eta.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"><a target=\"_blank\" href=\"jet3phi.png\"><img src=\"jet3phi.png\" alt=\"jet3phi.png\" width=\"100%\"></a></td>" << endl;
  htmlfile << "<td width=\"25%\"></td>" << endl;
  htmlfile << "</tr>" << endl;
  htmlfile << "</table>" << endl;
  htmlfile << "<hr />" << endl;

  htmlfile << "</body>" << endl;
  htmlfile << "</html>" << endl;
  htmlfile.close(); 
}
//--------------------------------------------------------------------------------------------------                                                                                                      
float CalcSig(TH1D*sig, TH1D*bkg) {
  float fSig2 = 0;
  int nb = sig->GetNbinsX();
  //  std::cout << "nb = " << nb << std::endl;
  for (int i = 0; i <= nb+1; i++) {
    if (sig->GetBinContent(i) > 0 && bkg->GetBinContent(i)>0) {
      fSig2 += pow(sig->GetBinContent(i),2)/bkg->GetBinContent(i);
    }
  }
  return sqrt(fSig2);
}
