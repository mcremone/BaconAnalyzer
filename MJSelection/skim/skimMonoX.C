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
#include "../macros/BitsLoader.hh" 
//#endif

using namespace std;

//Object Processors                                                                                                                                                                                      
BitsLoader       *fBits      = 0;

//=== MAIN MACRO =================================================================================================

void skimMonoX(const string preselection, const string selection, const string subsample, const string combo, TString algo, TString syst)
{
  //--------------------------------------------------------------------------------------------------------------
  // Settings
  //==============================================================================================================

  bool doBlind = false;
  //  if(subsample.compare("SR")==0)  doBlind = true;

  const string outfilename("MonoXNtuples/"+preselection+"-"+selection+"-"+subsample+"-"+combo+"-"+algo+"-"+syst+".root");

  //
  // samples
  // Note: macro assumes samplev[0] is data
  //
  vector<CSample*> samplev;

  samplev.push_back(new CSample("data",0,0));
  if (preselection.compare("Had")==0 || preselection.compare("Muo")==0 || preselection.compare("Zmm")==0)  samplev.back()->fnamev.push_back("../baconbits/MET.root");
  if (preselection.compare("Ele")==0 || preselection.compare("Zee")==0)  samplev.back()->fnamev.push_back("../baconbits/SingleElectron.root");
  if (preselection.compare("Pho")==0)  samplev.back()->fnamev.push_back("../baconbits/SinglePhoton.root");
  samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
  samplev.back()->fnamev.push_back("../baconbits/QCD.root");
  if (preselection.compare("Pho")!=0) {
      samplev.push_back(new CSample("SingleTop",kRed - 9,kRed - 9));
      samplev.back()->fnamev.push_back("../baconbits/T.root");
      samplev.back()->fnamev.push_back("../baconbits/TZ.root");
      samplev.push_back(new CSample("ttbar",kOrange - 4,kOrange - 4));
      //      samplev.back()->fnamev.push_back("../baconbits/TTDM.root");  
      // samplev.back()->fnamev.push_back("../baconbits/TT1L.root");
      // samplev.back()->fnamev.push_back("../baconbits/TT2L.root");
      // samplev.back()->fnamev.push_back("../baconbits/TTHAD.root");
      samplev.back()->fnamev.push_back("../baconbits/TTBST.root");
      samplev.back()->fnamev.push_back("../baconbits/TTCOM.root");
      samplev.back()->fnamev.push_back("../baconbits/TTZ.root");
      samplev.back()->fnamev.push_back("../baconbits/TTG.root");
      samplev.push_back(new CSample("WW",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("../baconbits/WW.root");
      samplev.push_back(new CSample("WZ",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("../baconbits/WZ.root");
      samplev.push_back(new CSample("ZZ",kYellow - 9,kYellow - 9));
      samplev.back()->fnamev.push_back("../baconbits/ZZ.root");
      samplev.push_back(new CSample("Wjets",kGreen - 10,kGreen - 10));
      samplev.back()->fnamev.push_back("../baconbits/WHF.root");
      //      samplev.push_back(new CSample("WjetsLF",kGreen - 10,kGreen - 10));
      samplev.back()->fnamev.push_back("../baconbits/WLF.root");
      samplev.push_back(new CSample("ZnunuLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("../baconbits/ZHF.root");
      //      samplev.push_back(new CSample("ZnunuLF", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("../baconbits/ZLF.root");
      samplev.push_back(new CSample("ZllLO", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("../baconbits/DYHF.root");
      //      samplev.push_back(new CSample("ZllLF", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("../baconbits/DYLF.root");
      //      samplev.back()->fnamev.push_back("../baconbits/DYNLO.root");  
  }
  if (preselection.compare("Pho")==0){
      samplev.push_back(new CSample("Photon", kCyan - 9, kCyan - 9));
      samplev.back()->fnamev.push_back("../baconbits/GHF.root");
      samplev.back()->fnamev.push_back("../baconbits/GLF.root");
  }
  if (subsample.compare("SR")==0){
    samplev.push_back(new CSample("Mres-1100_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S1_Mres-1100_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mres-1300_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S1_Mres-1300_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mres-1500_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S1_Mres-1500_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mres-1700_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S1_Mres-1700_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mres-1900_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S1_Mres-1900_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mres-2100_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S1_Mres-2100_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mres-900_Mchi-100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S1_Mres-900_Mchi-100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mchi-1100", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S4_Mchi-1100_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mchi-1300", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S4_Mchi-1300_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mchi-1500", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S4_Mchi-1500_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mchi-300", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S4_Mchi-300_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mchi-500", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S4_Mchi-500_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mchi-700", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S4_Mchi-700_MINIAOD_mc.root");
    samplev.push_back(new CSample("Mchi-900", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/Spring15_a25ns_Monotop_S4_Mchi-900_MINIAOD_mc.root");
    samplev.push_back(new CSample("tHq", kCyan - 9, kCyan - 9));
    samplev.back()->fnamev.push_back("../baconbits/THQ.root");
  }

  // integrated luminosity to scale MC
  const double LUMI = 2.318;
  
  // histograms for various corrections
  const string cmssw_base = getenv("CMSSW_BASE");
  
  //--------------------------------------------------------------------------------------------------------------
  // Main analysis code
  //==============================================================================================================

  TFile *outFile = new TFile(outfilename.c_str(),"RECREATE");

  //                                                                                                                                                                                       
  // Declare output TTrees                                                                                                                                                                 
  //                                                                                                                                                                                         

  float met_, metphi_, genVpt_, genVphi_, weight_, mt_;
  vector<TTree*> outtreesv;
  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    string tname = samplev[isam]->label;
    if(subsample=="SR") tname = tname + string("_signal");
    if(subsample=="ZnunuHF") tname = tname + string("_znunuhf_control");
    if(subsample=="ZnunuLF") tname = tname + string("_znunulf_control");
    if(preselection=="Muo" && subsample=="TopCR") tname = tname + string("_single_muon_top_control");
    if(preselection=="Ele" && subsample=="TopCR") tname = tname + string("_single_electron_top_control");
    if(preselection=="Muo" && subsample=="WCR") tname = tname + string("_single_muon_w_control");
    if(preselection=="Ele" && subsample=="WCR") tname = tname + string("_single_electron_w_control");
    if(preselection=="Muo" && subsample=="WHFCR") tname = tname + string("_single_muon_whf_control");
    if(preselection=="Ele" && subsample=="WHFCR") tname = tname + string("_single_electron_whf_control");
    if(preselection=="Muo" && subsample=="WLFCR") tname = tname + string("_single_muon_wlf_control");
    if(preselection=="Ele" && subsample=="WLFCR") tname = tname + string("_single_electron_wlf_control");
    if(preselection=="Zmm" && subsample=="ZCR") tname = tname + string("_di_muon_control");
    if(preselection=="Zee" && subsample=="ZCR") tname = tname + string("_di_electron_control");
    if(preselection=="Pho" && subsample=="ZCR") tname = tname + string("_photon_control");
    if(preselection=="Zmm" && subsample=="ZHFCR") tname = tname + string("_di_muon_zhf_control");
    if(preselection=="Zee" && subsample=="ZHFCR") tname = tname + string("_di_electron_zhf_control");
    if(preselection=="Pho" && subsample=="ZHFCR") tname = tname + string("_photon_zhf_control");
    if(preselection=="Zmm" && subsample=="ZLFCR") tname = tname + string("_di_muon_zlf_control");
    if(preselection=="Zee" && subsample=="ZLFCR") tname = tname + string("_di_electron_zlf_control");
    if(preselection=="Pho" && subsample=="ZLFCR") tname = tname + string("_photon_zlf_control");
    if(syst=="BTAGUP") tname = tname + string("_btagUp");
    if(syst=="BTAGDO") tname = tname + string("_btagDown");
    if(syst=="MISTAGUP") tname = tname + string("_mistagUp");
    if(syst=="MISTAGDO") tname = tname + string("_mistagDown");
    if(syst=="GJETHFUP") tname = tname + string("_gjethfUp");
    if(syst=="GJETHFDO") tname = tname + string("_gjethfDown");
    if(syst=="WJETHFUP") tname = tname + string("_wjethfUp");
    if(syst=="WJETHFDO") tname = tname + string("_wjethfDown");
    if(syst=="ZJETHFUP") tname = tname + string("_zjethfUp");
    if(syst=="ZJETHFDO") tname = tname + string("_zjethfDown");
    outtreesv.push_back(new TTree(tname.c_str(), tname.c_str()));
    outtreesv.back()->Branch("met",   &met_,   "met/F");
    outtreesv.back()->Branch("metphi",&metphi_,"metphi/F");
    outtreesv.back()->Branch("genVpt",   &genVpt_,   "genVpt/F");
    outtreesv.back()->Branch("genVphi",  &genVphi_,  "genVphi/F");
    outtreesv.back()->Branch("weight",   &weight_,   "weight/F");
    outtreesv.back()->Branch("mt",       &mt_,       "mt/F");
  }

  TFile *infile=0;
  TTree *intree=0;

  for(unsigned int isam=0; isam<samplev.size(); isam++) {
    CSample *sample = samplev[isam];
    cout << "Sample: " << sample->label << endl;
    bool isData   = (isam==0);
 
    for(unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) {
      string infilename = sample->fnamev[ifile];
      cout << " ==> Processing " << infilename << "... "; cout.flush();
      infile = new TFile(infilename.c_str()); assert(infile);
      intree = (TTree*)infile->Get("Events"); assert(intree);
      if(syst!="CENT" && syst!="BTAGDO" && syst!="BTAGUP" && syst!="MISTAGDO" && syst!="MISTAGUP") fBits     = new BitsLoader(intree,algo,"CENT",preselection);
      else fBits     = new BitsLoader(intree,algo,syst,preselection);
      double nevts=0;
      int noweight=0;

      for(unsigned int ientry=0; ientry<intree->GetEntries(); ientry++) {
        intree->GetEntry(ientry);
	if(!fBits->selectJetAlgoAndSize(selection,algo)) continue;
	// common selection
	if(fBits->metfilter!=0)                   continue;
	//preselection
	if(!fBits->passPreSelection(preselection)) continue;
	//selection
	float btagw=1;
	if(!fBits->passSelection(preselection,selection,subsample,combo,btagw)) continue;

	//	double wgt = fBits->getWgt(isData,algo,LUMI,btagw);
	double wgt = 1;
	//	if(!isData) {wgt = fBits->scale1fb*LUMI*btagw*fBits->triggerEff*fBits->evtWeight;}
	if(!isData) {
	  //	  wgt *= LUMI*fBits->scale1fb*fBits->nloKfactor*fBits->ewkCorr*btagw*fBits->triggerEff*fBits->evtWeight*fBits->lepWeight;
	  wgt *= LUMI*fBits->scale1fb*fBits->ewkCorr*btagw*fBits->triggerEff*fBits->evtWeight*fBits->lepWeight;
	  if(sample->label=="ttbar" && ifile==0 && fBits->topSize<1.2){
	    wgt *= fBits->ToptagSF;
	  }
	  if(sample->label!="ttbar" || ifile!=0 || fBits->topSize>=1.2){
            wgt *= fBits->TopmistagSF;
          }
	  if(sample->label=="Wjets" || sample->label=="Photon" || sample->label=="ZnunuLO" || sample->label=="ZllLO" ){
	    if(subsample=="SR" || subsample=="TopCR") {
	      if(ifile==0) {
		wgt *= fBits->btagSF;
	      }
	      if(ifile==1) {
		wgt *= fBits->bmistagSF;
	      }
	    }
	  }
	  
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

        met_    = fBits->getMET(preselection).Pt();
        metphi_ = fBits->getMET(preselection).Phi();
        weight_    = wgt;
	mt_ = fBits->transverse_mass(selection);
	//	genVpt_   = fBits->genvpt(selection);
	genVpt_   = fBits->bst15_genVpt;
	genVphi_  = fBits->genvphi(selection);

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
