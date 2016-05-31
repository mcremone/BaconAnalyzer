#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TLegend.h"
#include "TMath.h"

void profileDDT()
{
  std::string iName="/afs/cern.ch/work/m/mcremone/public/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/zprimebits/QCD.root";
  TFile *lFile = new TFile(iName.c_str());
  TTree *lTree = (TTree*) lFile->FindObjectAny("Events");
  //TProfile  *hprofilemsd   = new TProfile("hprofilemsd"," m_{SD} vs sqrt(p_{T}) QCD",20,0,40,0,300);
  //TH2D *hmsd = new TH2D("hmsd","m_{SD} vs p_{T} QCD",20.,0.,1000.,20.,0.,300.);
  // TProfile  *hprofilerho   = new TProfile("hprofilerho","#tau_{3}/#tau_{2} vs #rho QCD",20,-5,0,0,1);
  // TProfile  *hprofilephil  = new TProfile("hprofilephil","#tau_{3}/#tau_{2} vs #phil SD} QCD",20,0,30,0,1);
  TProfile  *hprofilenhan  = new TProfile("hprofilenhan","#tau_{2}/#tau_{1} vs #rho^{DDT} QCD",20,-5,6,0,1);

  // variables to read in baconbits
  int metfilter;
  float evtWeight, puWeight, scale1fb;
  int njets;
  double bst_jet0_pt,bst_jet0_eta,bst_jet0_phi,bst_jet0_mass;
  double bst_jet0_msd, bst_jet0_rho, bst_jet0_phil;
  double bst_jet0_minsubcsv, bst_jet0_tau21, bst_jet0_tau32;
  const double LUMI = 2.32;

  // read variables
  TString jet = "8"; 
  TString algo = "PUPPI";
  lTree->SetBranchAddress("metfilter",                         &metfilter);
  lTree->SetBranchAddress("puWeight",                          &puWeight);
  lTree->SetBranchAddress("scale1fb",                          &scale1fb);
  lTree->SetBranchAddress("evtWeight",                         &evtWeight);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_pt",        &bst_jet0_pt);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_eta",       &bst_jet0_eta);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_phi",       &bst_jet0_phi);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_mass",      &bst_jet0_mass);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_msd",       &bst_jet0_msd);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_rho",       &bst_jet0_rho);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_phil",      &bst_jet0_phil);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_tau21",     &bst_jet0_tau21);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_tau32",     &bst_jet0_tau32);
  lTree->SetBranchAddress("bst"+jet+"_"+algo+"jet0_minsubcsv", &bst_jet0_minsubcsv);

  // fill profile plots
  for(int i0 = 0; i0 < lTree->GetEntries(); i0++) {
    lTree->GetEntry(i0);
    if(metfilter!=0)    continue;
    if(bst_jet0_pt<500) continue; 
    double wgt=1; 
    wgt *= LUMI*scale1fb;
    double bst_jet0_nhan = log(bst_jet0_msd*bst_jet0_msd/bst_jet0_pt);
    //hprofilemsd->Fill(bst_jet0_pt, bst_jet0_msd, wgt);
    //hprofilemsd->Fill(sqrt(bst_jet0_pt), bst_jet0_msd, wgt);
    //hprofilerho->Fill(bst_jet0_rho, bst_jet0_tau32, wgt);
    //hprofilephil->Fill(bst_jet0_phil, bst_jet0_tau32, wgt);
    hprofilenhan->Fill(bst_jet0_nhan, bst_jet0_tau21, wgt);
  }
  /*
  // fit dependence and plot
  TCanvas *c1 = new TCanvas("c1","");
  gStyle->SetOptStat(kFALSE);

  TF1 *fmsd = new TF1("fmsd","pol3", 20, 40);
  hprofilemsd->Fit("fmsd","R");
  
  hprofilenhan->SetLineColor(4);
  hprofilenhan->SetMarkerStyle(22);
  hprofilenhan->SetMarkerSize(1);
  hprofilenhan->Draw("");
  hprofilenhan->GetXaxis()->SetTitle("log(m_{SD}^2/p_{T})");
  hprofilenhan->GetYaxis()->SetTitle("#tau_{3}/#tau_{2}");
  hprofilemsd->SetLineColor(4);
  hprofilemsd->SetMarkerStyle(22);  
  hprofilemsd->SetMarkerSize(1);
  hprofilemsd->Draw("");
  //hmsd->Draw("COLZ"); 
  hprofilemsd->GetXaxis()->SetTitle("sqrt(p_{T}) [Gev]");
  hprofilemsd->GetYaxis()->SetTitle("m_{SD} [Gev]"); 
  gPad->RedrawAxis();
  c1->Update();
  c1->SaveAs("hprofilemsd_QCD_msdvssqpt.png");
  c1->SaveAs("hprofilemsd_QCD_msdvssqpt.pdf");
  */
  TFile f("histos.root","new");
  hprofilenhan->Write();
  f.Close();
}
