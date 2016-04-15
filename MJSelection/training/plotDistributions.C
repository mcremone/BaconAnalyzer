#include "TTree.h"
#include "TString.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"

void plotDistributions(TTree *tSig76, TTree *tBg76,TTree *tSig74, TTree *tBg74,TString varName76="", TString varName74="",int nBins=10,float lowX=-1,float highX=10) {
  tSig76->Draw(TString::Format("%s>>hSig76(%i,%f,%f)",varName76.Data(),nBins,lowX,highX).Data(),"isHadronicTop == 1 && topSize<1.5","hist");
  TH1F *hSig76 = (TH1F*)gPad->GetPrimitive("hSig76");
  hSig76->SetName("hSig76");
  tSig74->Draw(TString::Format("%s>>hSig74(%i,%f,%f)",varName74.Data(),nBins,lowX,highX).Data(),"","hist");
  TH1F *hSig74 = (TH1F*)gPad->GetPrimitive("hSig74");
  hSig74->SetName("hSig74");

  tBg76->Draw(TString::Format("%s>>hBg76(%i,%f,%f)",varName76.Data(),nBins,lowX,highX).Data(),"","hist");
  TH1F *hBg76 = (TH1F*)gPad->GetPrimitive("hBg76");
  hBg76->SetName("hBg76");
  tBg74->Draw(TString::Format("%s>>hBg74(%i,%f,%f)",varName74.Data(),nBins,lowX,highX).Data(),"","hist");
  TH1F *hBg74 = (TH1F*)gPad->GetPrimitive("hBg74");
  hBg74->SetName("hBg74");
 
  float nSig76 = hSig76->GetEntries(); hSig76->Scale(nSig76/hSig76->Integral());
  float nBg76 = hBg76->GetEntries(); hBg76->Scale(nBg76/hBg76->Integral());
  float nSig74 = hSig74->GetEntries(); hSig74->Scale(nSig74/hSig74->Integral());
  float nBg74 = hBg74->GetEntries(); hBg74->Scale(nBg74/hBg74->Integral());
  hBg76->SetLineWidth(2); hBg76->SetLineColor(9);  hBg76->SetStats(0); hBg76->SetXTitle(varName76); hBg76->SetTitle("");
  hSig76->SetLineWidth(2); hSig76->SetLineColor(2);   hSig76->SetStats(0); hSig76->SetXTitle(varName76); hSig76->SetTitle("");
  hBg74->SetLineWidth(2); hBg74->SetLineColor(38);  hBg74->SetStats(0); hBg74->SetXTitle(varName74); hBg74->SetTitle("");
  hSig74->SetLineWidth(2); hSig74->SetLineColor(46);   hSig74->SetStats(0); hSig74->SetXTitle(varName74); hSig74->SetTitle("");

  TCanvas *c = new TCanvas("c","c",700,600);
  c->cd();
  c->SetBottomMargin(0.1);
  //if (setLog!=0) c->SetLogy();
  hBg76->SetNormFactor(); hSig76->SetNormFactor(); hBg74->SetNormFactor(); hSig74->SetNormFactor();
  hBg76->SetMaximum(hBg76->GetMaximum()*1.5);
  hSig76->SetMaximum(hSig76->GetMaximum()*1.5);
  hBg74->SetMaximum(hBg74->GetMaximum()*1.5);
  hSig74->SetMaximum(hSig74->GetMaximum()*1.5);
  if (hBg76->GetMaximum()/hBg76->Integral() > hSig76->GetMaximum()/hSig76->Integral()) {
    hBg76->Draw("hist");
    hSig76->Draw("same hist");
    hBg74->Draw("same hist");
    hSig74->Draw("same hist");
  } else {
    hSig76->Draw("hist");
    hBg76->Draw("same hist");
    hSig74->Draw("same hist");
    hBg74->Draw("same hist");
  }

  TLegend *l = new TLegend(0.7,0.7,.9,.9);
  l->AddEntry(hSig76,"Zprime 76");
  l->AddEntry(hBg76,"QCD 76");
  l->AddEntry(hSig74,"Zprime 74");
  l->AddEntry(hBg74,"QCD 74");
  l->Draw();

  c->SaveAs(varName76+".pdf");
  c->SaveAs(varName76+".png");

  l->Delete(); hSig76->Delete(); hBg76->Delete();  hSig74->Delete(); hBg74->Delete();
  delete c;
  delete gPad;
  // return c;
}
