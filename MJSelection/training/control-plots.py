from optparse import OptionParser
from ROOT import *
import ROOT
import sys
import time
import gc
import math
import array

gROOT.Reset()
gStyle.SetOptStat(0)  # What is displayed in the stats box for each histo.
gStyle.SetStatH(0.3);   # Max height of stats box
gStyle.SetStatW(0.25);  # Max height of stats box
gStyle.SetPadLeftMargin(0.20)   # Left margin of the pads on the canvas.
gStyle.SetPadBottomMargin(0.20) # Bottom margin of the pads on the canvas.
gStyle.SetFrameFillStyle(0) # Keep the fill color of our pads white.

f = ROOT.TFile('tmp_reweighted_r800/TMVA_reweighted_r800.root', 'read') 
mytree=f.Get('TrainTree') 
nentry = mytree.GetEntries() 

l = ROOT.TLegend(0.61,0.59,0.82,0.8)
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)



histos = []

for j in range(0,12):
  hname = "histos_%d" % (j) # Each histogram must have a unique name
  htitle = "Histogram %d" % (j) # Give each its own title.
  if (j == 0):
    htitle = "Background"
    histos.append( TH1F(hname, htitle, 800, 300., 1500.) )
  elif (j == 1):
    htitle = "Background"
    histos.append( TH1F(hname, htitle, 800, 300., 1500.) )
  elif (j == 2):
    htitle = "Background"
    histos.append(TH2F(hname,htitle, 800, 300., 1500.,250, -2.5, 2.5))
  elif (j == 3):
    htitle = "Signal"
    histos.append( TH1F(hname, htitle, 800, 300., 1500.) )
  elif (j == 4):
    htitle = "Signal"
    histos.append( TH1F(hname, htitle, 800, 300., 1500.) )
  elif (j == 5):
    htitle = "Signal"
    histos.append(TH2F(hname,htitle,800, 300., 1500.,250, -2.5, 2.5))
  else:
    htitle = "Signal eff vs. pt"
    histos.append( TH1F(hname, htitle, 800, 300., 1500.) )         
  if (j==0):  
    l.AddEntry(histos[j],"weighted",'l')
  if (j==1):  
    l.AddEntry(histos[j],"unweighted",'l')  
  histos[j].SetMinimum(0)
  histos[j].GetXaxis().SetNdivisions(6)
  histos[j].GetXaxis().SetLabelSize(0.06)
  histos[j].GetXaxis().CenterTitle()
  histos[j].GetXaxis().SetTitleSize(0.09)
  histos[j].GetXaxis().SetTitleOffset(1.1)
  histos[j].GetXaxis().SetTitle( "p_{T}" )

  histos[j].GetYaxis().SetNdivisions(4)
  histos[j].GetYaxis().SetLabelSize(0.06)
  histos[j].GetYaxis().CenterTitle()
  histos[j].GetYaxis().SetTitleSize(0.09)
  histos[j].GetYaxis().SetTitleOffset(1.1)
  if (j==2 or j==5):
    histos[j].GetYaxis().SetTitle("#eta")
  else:
    histos[j].GetYaxis().SetTitle("A.U")


histos[0].SetLineColor(3)
histos[3].SetLineColor(3)
# histos[4].SetLineColor(3)
# histos[5].SetLineColor(3)
# histos[4].SetFillColor(1)
# histos[5].SetFillColor(1)

if(f.GetName().find("reweighted") != -1):
  cutBDTCat8 = -0.001165
  cutBDTG = 0.140891
elif(f.GetName().find("unweighted") != -1):
  cutBDTCat8 = 0.034502
  cutBDTG = 0.146482 
  
print f.GetName()  
print cutBDTG
print cutBDTCat8
  
for event in mytree:
  ptEtaWeight = event.weight
  # ptEtaWeight = 1.
  if event.classID==1:
    # histos[0].Fill( event.ptGroomed, event.weight )
    histos[1].Fill( event.ptGroomed )
    # histos[2].Fill( event.ptGroomed, event.etaGroomed, ptEtaWeight )
    if(event.BDTCat8>= cutBDTCat8):
        histos[10].Fill( event.ptGroomed )
    if(event.BDTG>= cutBDTG):
      histos[11].Fill( event.ptGroomed )
  if event.classID==0:
    # histos[3].Fill( event.ptGroomed, event.weight )
    histos[4].Fill( event.ptGroomed )
    # histos[5].Fill( event.ptGroomed, event.etaGroomed, ptEtaWeight )
    # if(event.BDTCat4>= cutBDTCat4):
    #    histos[7].Fill( event.ptGroomed )
    if(event.BDTCat8>= cutBDTCat8):
        histos[8].Fill( event.ptGroomed )
    if(event.BDTG>= cutBDTG):
      histos[6].Fill( event.ptGroomed )
    
# for i in range(0,1):
#   for j in range(0,6):
#     histos[j].Scale(1./(histos[j].Integral()))


num_canvases = 3
can = []
for i in range(0, num_canvases):
  name = "can%d" % (i) 
  title = "pT %d" % (i) 
  can.append(TCanvas( name, title, 10+10*i, 10+10*i, 1600, 800 ))
  can[i].SetFillColor( 0 )
  can[i].Divide(2 , 0 ) 


t = ROOT.TLatex()
t.SetNDC()
t.SetTextAlign(12)
t.SetTextSize(0.04)

   
# can[0].cd(1)
# histos[0].Draw("HIST")
# histos[1].Draw("HISTsame")
# l.Draw()
# t.DrawLatex(.5,.4,"QCD")
# t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
# gPad.Update()
# can[0].cd(2)
# histos[4].Draw("HIST")
# histos[3].Draw("HISTsame")
# l.Draw()
# t.DrawLatex(.5,.4,"R(M800)")
# t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
# gPad.Update()
# can[1].cd(1)
# histos[5].Draw("LEGO1")
# # t.DrawLatex(.5,.4,"QCD")
# # t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
# gPad.Update()
# can[1].cd(2)
# histos[2].Draw("LEGO1")
# # t.DrawLatex(.5,.4,"R(M800)")
# # t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
# gPad.Update()

histos[8].Rebin(10)
histos[6].Rebin(10)
histos[4].Rebin(10)
EffVsPt = ROOT.TGraphAsymmErrors() 
EffVsPt.Divide(histos[6],histos[4],"cl=0.683 b(1,1) mode") 
EffVsPt.SetTitle("") 
EffVsPt.GetXaxis().SetTitle("p_{T} [GeV]") 
EffVsPt.GetXaxis().SetLimits(300.,1500.) 
EffVsPt.GetYaxis().SetTitle("Efficiency") 
EffVsPt.GetYaxis().SetTitleOffset(1.16) 
EffVsPt.GetHistogram().SetMaximum(1.1)       
EffVsPt.GetHistogram().SetMinimum(0.)   
EffVsPt.SetMarkerStyle(20) 
EffVsPt.SetMarkerColor(46) 

# histos[7].Rebin(10)
# histos[8].Rebin(10)
# EffVsPtCat4 = ROOT.TGraphAsymmErrors()
# EffVsPtCat4.Divide(histos[7],histos[4],"cl=0.683 b(1,1) mode")
# EffVsPtCat4.SetTitle("")
# EffVsPtCat4.GetXaxis().SetTitle("p_{T} [GeV]")
# EffVsPtCat4.GetXaxis().SetLimits(300.,1500.)
# EffVsPtCat4.GetYaxis().SetTitle("Efficiency")
# EffVsPtCat4.GetYaxis().SetTitleOffset(1.16)
# EffVsPtCat4.GetHistogram().SetMaximum(1.1)
# EffVsPtCat4.GetHistogram().SetMinimum(0.)
# EffVsPtCat4.SetMarkerStyle(20)
# EffVsPtCat4.SetMarkerColor(3)

EffVsPtCat8 = ROOT.TGraphAsymmErrors()
EffVsPtCat8.Divide(histos[8],histos[4],"cl=0.683 b(1,1) mode")
EffVsPtCat8.SetTitle("")
EffVsPtCat8.GetXaxis().SetTitle("p_{T} [GeV]")
EffVsPtCat8.GetXaxis().SetLimits(300.,1500.)
EffVsPtCat8.GetYaxis().SetTitle("Efficiency")
EffVsPtCat8.GetYaxis().SetTitleOffset(1.16)
EffVsPtCat8.GetHistogram().SetMaximum(1.1)
EffVsPtCat8.GetHistogram().SetMinimum(0.)
EffVsPtCat8.SetMarkerStyle(20)
EffVsPtCat8.SetMarkerColor(4)

can[2].cd(1)
EffVsPt.Draw("AP")
EffVsPtCat8.Draw("Psame")
t.DrawLatex(.32,.4,"R(M800)")
# t.DrawLatex(.22,.35,"p_{T}-#eta reweighted")

l = ROOT.TLegend(0.65,0.75,0.80,0.89,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)
l.AddEntry(EffVsPt,"BDT",'p')
l.AddEntry(EffVsPtCat8,"BDTCat8",'p')
l.Draw()
gPad.Update()


can[2].cd(2)
histos[11].Rebin(10)
histos[10].Rebin(10)
histos[1].Rebin(10)
bkg_EffVsPt = ROOT.TGraphAsymmErrors() 
bkg_EffVsPt.Divide(histos[11],histos[1],"cl=0.683 b(1,1) mode") 
bkg_EffVsPt.SetTitle("") 
bkg_EffVsPt.GetXaxis().SetTitle("p_{T} [GeV]") 
bkg_EffVsPt.GetXaxis().SetLimits(300.,1500.) 
bkg_EffVsPt.GetYaxis().SetTitle("Efficiency") 
bkg_EffVsPt.GetYaxis().SetTitleOffset(1.16) 
bkg_EffVsPt.GetHistogram().SetMaximum(1.1)       
bkg_EffVsPt.GetHistogram().SetMinimum(0.)   
bkg_EffVsPt.SetMarkerStyle(20) 
bkg_EffVsPt.SetMarkerColor(46) 

bkg_EffVsPtCat8 = ROOT.TGraphAsymmErrors()
bkg_EffVsPtCat8.Divide(histos[10],histos[1],"cl=0.683 b(1,1) mode")
bkg_EffVsPtCat8.SetTitle("")
bkg_EffVsPtCat8.GetXaxis().SetTitle("p_{T} [GeV]")
bkg_EffVsPtCat8.GetXaxis().SetLimits(300.,1500.)
bkg_EffVsPtCat8.GetYaxis().SetTitle("Efficiency")
bkg_EffVsPtCat8.GetYaxis().SetTitleOffset(1.16)
bkg_EffVsPtCat8.GetHistogram().SetMaximum(1.1)
bkg_EffVsPtCat8.GetHistogram().SetMinimum(0.)
bkg_EffVsPtCat8.SetMarkerStyle(20)
bkg_EffVsPtCat8.SetMarkerColor(4)

bkg_EffVsPt.Draw("AP")
bkg_EffVsPtCat8.Draw("Psame")
t.DrawLatex(.32,.4,"QCD")
l.Draw()
gPad.Update()


time.sleep(100)
del mytree
f.Close()