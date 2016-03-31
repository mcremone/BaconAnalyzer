#include <TString.h>
#include <TFile.h>
#include <TCanvas.h>


void plotROC(TString input1, TString label1, TString input2 , TString label2,  TString input3,  TString label3, TString input4, TString label4,  TString input5,  TString label5  ){


	gROOT->SetStyle("Plain");
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptStat(0);
	TCanvas *cROC = new TCanvas("cROC","cROC", 700, 700);

	cROC->SetTickx(1);
	cROC->SetTicky(1);
	TLegend *leg = new TLegend(0.15625,0.321654,0.4765625,0.603839,NULL,"brNDC");
	leg->SetBorderSize(0);
	leg->SetTextSize(0.035);
	leg->SetLineColor(1);
	leg->SetLineStyle(1);
	leg->SetLineWidth(1);
	leg->SetFillColor(0);
	leg->SetFillStyle(0);




	//TFile * _file0 = new TFile("TMVA_sL_optimized.root");
	//TFile * _file1 = new TFile ("TMVA_QCD_BBvsGSP_fat.root");
	TFile * file1 = new TFile(input1);
	file1->cd();
	TDirectoryFile * d = (TDirectoryFile *)file1->Get("Method_BDT/BDTG");
	d->cd();
	//cROC->cd();
	MVA_BDTG_rejBvsS->SetTitle("");
	MVA_BDTG_rejBvsS->SetLineColor(kBlue+1);
        MVA_BDTG_rejBvsS->SetLineWidth(3);
        MVA_BDTG_rejBvsS->Draw();
	leg->AddEntry(MVA_BDTG_rejBvsS, label1);
	if(input2!=""){
		TFile * file2 = new TFile(input2);
		file2->cd();
		TDirectoryFile * d2 = file2->Get("Method_BDT/BDTG");
		d2->cd();
		MVA_BDTG_rejBvsS->SetLineColor(kGreen+2);
		MVA_BDTG_rejBvsS->SetLineWidth(3);
		MVA_BDTG_rejBvsS->Draw("same");
		leg->AddEntry(MVA_BDTG_rejBvsS, label2);

	}
	if(input3!=""){
		TFile * file3 = new TFile(input3);
		file3->cd();
		TDirectoryFile * d3 = file3->Get("Method_BDT/BDTG");
		d3->cd();
		MVA_BDTG_rejBvsS->SetLineColor(kRed+2);
		MVA_BDTG_rejBvsS->SetLineWidth(3);
		MVA_BDTG_rejBvsS->Draw("same");
		leg->AddEntry(MVA_BDTG_rejBvsS, label3);
	
	}
	if(input4!=""){
		TFile * file4 = new TFile(input4);
		file4->cd();
		TDirectoryFile * d4 = file4->Get("Method_BDT/BDTG");
		d4->cd();
		MVA_BDTG_rejBvsS->SetLineColor(kOrange+2);
		MVA_BDTG_rejBvsS->SetLineWidth(3);
		MVA_BDTG_rejBvsS->Draw("same");
		leg->AddEntry(MVA_BDTG_rejBvsS, label4);
	
	}
	if(input5!=""){
		TFile * file5 = new TFile(input5);
		file5->cd();
		MVA_BDTG_rejBvsS->SetLineColor(kPink+2);
		MVA_BDTG_rejBvsS->SetLineWidth(3);	
		TDirectoryFile * d5 = file5->Get("Method_BDT/BDTG");
		d5->cd();
		MVA_BDTG_rejBvsS->Draw("same");
		leg->AddEntry(MVA_BDTG_rejBvsS, label5);

	}
	leg->Draw();
	cROC->Print("roc_.png");
}

