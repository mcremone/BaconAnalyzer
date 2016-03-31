#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"

void massReweight(TString size="bst15", TString algo="PUPPI", TString name="mcsig15")
{
  std::string iName1="trainingbits/mcsig15PUPPI.root";
  std::string iName2="trainingbits/QCD_mcsig15PUPPI.root";
  TFile *lFile1 = new TFile(iName1.c_str());
  TTree *lTree1 = (TTree*) lFile1->FindObjectAny("Events");
  TFile *lFile2 = new TFile(iName2.c_str());
  TTree *lTree2 = (TTree*) lFile2->FindObjectAny("Events");

  TH1F * h_msd_signal = new TH1F("h_msd_"+size+algo+"signal","", 175,0.,350.); 
  TH1F * h_msd_qcd = new TH1F("h_msd_"+size+algo+"qcd","", 175,0.,350.); 

  float lMass =0;
  lTree1->SetBranchAddress(size+"_"+algo+"jet1msd",&lMass);
  for(int i0 = 0; i0 < lTree1->GetEntries(); i0++) {
    lTree1->GetEntry(i0);
    h_msd_signal->Fill(lMass);
  }
  lTree2->SetBranchAddress(size+"_"+algo+"jet1msd",&lMass);
  for(int i0 = 0; i0 < lTree2->GetEntries(); i0++) {
    lTree2->GetEntry(i0);
    h_msd_qcd->Fill(lMass);
  }

  TH1F * h_msd_weight = h_msd_signal;
  h_msd_weight->Divide(h_msd_qcd);

  Float_t lWeight    = 0;
  TFile *lFileq = new TFile(iName2.c_str(),"RECREATE");
  TTree *lTreeq = lTree2->CloneTree(0);
  lTree2->SetBranchAddress(size+"_"+algo+"jet1msd",&lMass);
  lTreeq->Branch(size+"_"+algo+"jet1weight",&lWeight,"lWeight/F");
  for(int i0 = 0; i0 < lTree2->GetEntries(); i0++) {
    lTree2->GetEntry(i0);
    lWeight = Float_t(h_msd_signal->GetBinContent(h_msd_signal->FindBin(lMass)));
    if (h_msd_qcd->GetBinContent(h_msd_qcd->FindBin(lMass))!=0) lWeight = Float_t(h_msd_weight->GetBinContent(h_msd_weight->FindBin(lMass)));
    lTreeq->Fill();
  }
  lFileq->cd();
  lFileq->Write();
  lFileq->Close();
  lFileq->Delete();
  TFile *lFiles = new TFile(iName1.c_str(),"RECREATE");
  TTree *lTrees = lTree1->CloneTree(0);
  lTrees->Branch(size+"_"+algo+"jet1weight",&lWeight,"lWeight/F");
  for(int i0 = 0; i0 < lTree1->GetEntries(); i0++) {
    lTree1->GetEntry(i0);
    lWeight = 1.;
    lTrees->Fill();
  }
  lFiles->cd();
  lFiles->Write();
  lFiles->Close();
  lFiles->Delete();
}
