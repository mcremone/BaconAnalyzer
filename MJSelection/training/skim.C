#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"

void skim()
{
  std::string iName1="trainingbits/Zprime.root";
  TFile *lFile1 = new TFile(iName1.c_str());
  TTree *lTree1 = (TTree*) lFile1->FindObjectAny("Events");

  TFile *lFiles = new TFile(iName1.c_str(),"RECREATE");
  TTree *lTrees = lTree1->CloneTree(0);
  int ent = int(lTree1->GetEntries()*0.5);
  for(int i0 = 0; i0 < ent; i0++) {
    lTree1->GetEntry(i0);
    lTrees->Fill();
  }
  lFiles->cd();
  lFiles->Write();
  lFiles->Close();
  lFiles->Delete();
}
