#include <TROOT.h>                    // access to gROOT, entry point to ROOT system
#include <TCanvas.h>
#include <TSystem.h>                  // interface to OS
#include <TStyle.h>                   // class to handle ROOT plotting styles
#include <TFile.h>                    // file handle class
#include <TTree.h>                    // class to access ntuples
#include <TH1D.h>                     // 1D histogram class
#include <TLorentzVector.h>           // 4-vector class
#include <vector>                     // STL vector class
#include <THStack.h>
#include <iostream>                   // standard I/O
#include <iomanip>                    // functions to format standard I/O
#include <fstream>                    // functions for file I/O
#include <sstream>
#include <string>                     // C++ string class
#include <cmath>                      // C++ math library
#include <cassert>
#include <TH2Poly.h>
#include "../../macros/CSample.hh"       // helper class to manage samples

void plot()
{
    TFile *infile;
    TTree *intree;
    vector<CSample*> samplev;
    vector<TH1D*> hMETv, hHTv, hMHTv, hNJetsv, hMRv, hRsqv, hdeltaPhiv;
    TH1D *hMET, *hHT, *hMHT, *hNJets, *hMR, *hRsq, *hdeltaPhi;

    // Variables to read baconbits
    int metfilter;                                                                   // MET filter bits          
    unsigned int runNum, lumiSec, evtNum;                                            // event ID
    unsigned int triggerBits, selectBits;                                            // trigger and jet type bits
    double triggerEff;                                                               // trigger efficiency
    float evtWeight, puWeight;                                                       // pu and evt weight
    unsigned int npu, npv;                                                           // PU, PV multiplicity
    int njets;                                                                       // jet multiplicity 
    float weight;                                                                  // cross section scale factor per 1/fb
    float kfactor;                                                                   // kFactor and EWK correction
    float vmetpt,vmetphi,vfakemetpt,vfakemetphi;                                     // MET
    double min_dphijetsmet;                                                          // min delta phi between MET and narrow jets

    double           res_jet0_pt, res_jet0_eta, res_jet0_phi, res_jet0_mass;         // narrow jets
    double           res_jet1_pt, res_jet1_eta, res_jet1_phi, res_jet1_mass;
    double           res_jet0_CHF, res_jet0_NHF, res_jet0_NEMF;                      // jet variables
    double           res_jet0_HadFlavor, res_jet1_HadFlavor, res_jet2_HadFlavor, res_jet3_HadFlavor;
    float            res_mt;                                                         // mT
    float            MR, Rsq, deltaPhi;                                           // razor variables
    int              nJetsAbove80GeV;
    float            HT, MHT;                                                        // HT and MHT

//    samplev.push_back(new CSample("QCD", kMagenta - 10, kMagenta - 10));
//    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/QCD.root");
    samplev.push_back(new CSample("Top Quark",kBlue - 2,kBlue - 2));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/ST.root");
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/TT.root");
    samplev.push_back(new CSample("Diboson",kRed - 2,kRed - 2));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/Diboson.root");
    samplev.push_back(new CSample("W+jets",kGreen - 2,kGreen - 2));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/WHF.root");
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/WLF.root");
    samplev.push_back(new CSample("Z+jets", kAzure - 2, kAzure - 2));
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/ZHF.root");   
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/ZLF.root");
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/DYHF.root");
    samplev.back()->fnamev.push_back("/afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/submission/monojet/Final/DYLF.root");
     
    const double LUMI = 12.9;
    
    for(unsigned int isam=0; isam<samplev.size(); isam++) 
    {
        CSample *sample = samplev[isam];
        cout << "Sample: " << sample->label << endl;
        hMET = new TH1D(sample->label.c_str(), sample->label.c_str(), 70,200,1200);
        hMET->SetFillColor(sample->fillcolor);


        for (unsigned int ifile=0; ifile<sample->fnamev.size(); ifile++) 
        {
            string infilename = sample->fnamev[ifile];
            cout << " ==> Processing " << infilename << "... "; cout.flush();
            infile = TFile::Open(infilename.c_str()); assert(infile);
            infile->ls();
            intree = (TTree*)infile->Get("Events"); assert(intree);
            
            intree->SetBranchAddress("res_CHSjetmindPhi",          &min_dphijetsmet);
            intree->SetBranchAddress("runNum",                          &runNum);
            intree->SetBranchAddress("lumiSec",                         &lumiSec);
            intree->SetBranchAddress("evtNum",                          &evtNum);
            intree->SetBranchAddress("metfilter",                       &metfilter);
            intree->SetBranchAddress("triggerBits",                     &triggerBits);
            intree->SetBranchAddress("selectBits",                      &selectBits);
            intree->SetBranchAddress("puWeight",                        &puWeight);
            intree->SetBranchAddress("weight",                          &weight);
            intree->SetBranchAddress("kfactor",                         &kfactor);
            intree->SetBranchAddress("pfmet",                           &vmetpt);
            intree->SetBranchAddress("pfmetphi",                         &vmetphi);
            intree->SetBranchAddress("res_CHSjets",                &njets);
            intree->SetBranchAddress("res_CHSjet0_pt",             &res_jet0_pt);
            intree->SetBranchAddress("res_CHSjet0_eta",            &res_jet0_eta);
            intree->SetBranchAddress("res_CHSjet0_CHF",            &res_jet0_CHF);
            intree->SetBranchAddress("res_CHSjet0_NHF",            &res_jet0_NHF);
            intree->SetBranchAddress("res_CHSjetsAbove80GeV",      &nJetsAbove80GeV);
            intree->SetBranchAddress("res_CHSjetMR",               &MR);
            intree->SetBranchAddress("res_CHSjetRsq",              &Rsq);
            intree->SetBranchAddress("res_CHSjetdeltaPhi",         &deltaPhi);
            intree->SetBranchAddress("res_CHSjetHT",               &HT);
            intree->SetBranchAddress("res_CHSjetMHT",              &MHT);

            for (unsigned int i = 0; i < intree->GetEntries(); i++)
            {
                intree->GetEntry(i);
                double wgt = 12.9*1000*weight*kfactor*puWeight;
                if (min_dphijetsmet > 0.5 && res_jet0_pt > 100 && vmetpt > 200 && fabs(res_jet0_eta) < 2.5 && res_jet0_CHF > 0.1 && res_jet0_NHF < 0.8)     hMET->Fill(vmetpt,wgt/(hMET->GetBinWidth(1)));
            }
            infile->Close();
        }
        hMETv.push_back(hMET);

    }
    TCanvas *c1 = new TCanvas();
    THStack *hMETst = new THStack("hMETst","");
    for (unsigned int isam = 0; isam < samplev.size(); isam++)
    {
        hMETst->Add(hMETv[isam]);
    }
    hMETst->Draw("hist");
    hMETst->SetTitle("; E_{T}^{miss} [GeV]; Events / GeV");
    hMETst->SetMinimum(1e-2);
    hMETst->SetMaximum(1e5);
    c1->Modified();
    gPad->BuildLegend();
}
