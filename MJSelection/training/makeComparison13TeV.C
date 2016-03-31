void makeComparisonBackground(TString var){

gROOT->SetStyle("Plain");
gStyle->SetPadGridX(0);
gStyle->SetPadGridY(0);
gStyle->SetOptStat(0);

TCanvas * c = new TCanvas("c","c", 700, 700);
TLegend *leg = new TLegend(0.65625,0.6321654,0.8765625,0.8603839,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.035);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);

TFile * f = new TFile("trainingbits/trainingbits_ZZ1000.root");//QCD8TeV_forTraining.root");//Signal8TeV_forTraining.root");//Signal_fat_forTraining.root");//R800_miniAOD_forTraining.root");//test_miniAOD_forTraining.root");
f->cd();
Fjets->Draw(var+">>h","ptGroomed>140 && ptGroomed<250 && tau3/tau2>0.25 && tau3/tau2<0.71");
h->SetLineColor(kBlue+2);
h->SetLineWidth(3);
h->GetXaxis()->SetTitle(var);
h->SetTitle("");
h->DrawNormalized("");
int nbin = h->GetXaxis()->GetNbins();
std::stringstream ss;
ss << nbin;
TString strNb = ss.str();
float low = h->GetXaxis()->GetXmin();
std::stringstream ss1;
ss1 << low;
TString strL=(ss1.str());
float max = h->GetXaxis()->GetXmax();
std::stringstream ss2;
ss2 << max;
TString strM= (ss2.str());
//std::cout<<nbin<< "  "<<low<<"  "<<max<<std::endl;
leg->AddEntry("h","Signal","l");
delete h;
TCanvas * d = new TCanvas("d","d");
d->cd();
TFile * fAOD = new TFile("trainingbits/trainingbits_qcd_forTraining.root");//R800_AOD_forTraining.root");//;test_AOD_forTraining.root");
fAOD->cd();
std::cout<<var+">>h1("+strNb+","+strL+","+strM+")"<<std::endl;
Fjets->Draw(var+">>h1("+strNb+","+strL+","+strM+")","ptGroomed>140 && ptGroomed<250 && tau3/tau2>0.25 && tau3/tau2<0.71");

h1->SetLineColor(kRed+2);
h1->SetLineWidth(3);
h1->GetXaxis()->SetTitle(var);
h1->SetTitle("");
c->cd();
h1->DrawNormalized("same");
leg->AddEntry("h1","Background","l");
leg->Draw();
if(var=="tau3/tau2") var = "sub";
c->Print(("plots/"+var+".png"));
delete h1;
delete d;
delete c;
//delete strL;


}
