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

inDirName="/shome/thaarres/HiggsTagger/"
files = []
  
for inFileName in os.listdir(inDirName):
  if inFileName.beginswith("validation_"):
     files.append(inFileName)

l = ROOT.TLegend(0.61,0.59,0.82,0.8,"","NDC")
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
  htitle = "Histogram %s" %(inFileName.replace(".root",""))
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

for f in files:
  mytree=f.Get('TrainTree') 
  nentry = mytree.GetEntries()
  
  if(f.GetName().find("reweighted") != -1):
    cutBDTCat4 = -0.035950
    cutBDTCat12 = -0.058187
    cutBDTG = -0.003619
  elif(f.GetName().find("unweighted") != -1):
    cutBDTCat4 = -0.160858
    cutBDTCat12 = -0.174253
    cutBDTG = -0.016775 
  
  print f.GetName()  
  print cutBDTCat4
  print cutBDTCat12
  print cutBDTG
  
  for event in mytree:
    histos[1].Fill( event.ptGroomed )
    if(event.BDTCat4>= cutBDTCat4):
      histos[9].Fill( event.ptGroomed )
    if(event.BDTCat12>= cutBDTCat12):
      histos[10].Fill( event.ptGroomed )
    if(event.BDTG>= cutBDTG):
      histos[11].Fill( event.ptGroomed )
    if event.classID==0:

      histos[4].Fill( event.ptGroomed )
      if(event.BDTCat4>= cutBDTCat4):
        histos[7].Fill( event.ptGroomed )
      if(event.BDTCat12>= cutBDTCat12):
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

   
can[0].cd(1)        
histos[0].Draw("HIST")   
histos[1].Draw("HISTsame")
l.Draw()
t.DrawLatex(.5,.4,"QCD")
t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
gPad.Update()
can[0].cd(2)
histos[4].Draw("HIST")   
histos[3].Draw("HISTsame")
l.Draw()
t.DrawLatex(.5,.4,"R(M800)")
t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
gPad.Update()
can[1].cd(1)
histos[5].Draw("LEGO1")  
# t.DrawLatex(.5,.4,"QCD")
# t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
gPad.Update()
can[1].cd(2)
histos[2].Draw("LEGO1")   
# t.DrawLatex(.5,.4,"R(M800)")
# t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
gPad.Update()


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

histos[7].Rebin(10)
histos[8].Rebin(10)
EffVsPtCat4 = ROOT.TGraphAsymmErrors()
EffVsPtCat4.Divide(histos[7],histos[4],"cl=0.683 b(1,1) mode")
EffVsPtCat4.SetTitle("")
EffVsPtCat4.GetXaxis().SetTitle("p_{T} [GeV]")
EffVsPtCat4.GetXaxis().SetLimits(300.,1500.)
EffVsPtCat4.GetYaxis().SetTitle("Efficiency")
EffVsPtCat4.GetYaxis().SetTitleOffset(1.16)
EffVsPtCat4.GetHistogram().SetMaximum(1.1)
EffVsPtCat4.GetHistogram().SetMinimum(0.)
EffVsPtCat4.SetMarkerStyle(20)
EffVsPtCat4.SetMarkerColor(3)

EffVsPtCat12 = ROOT.TGraphAsymmErrors()
EffVsPtCat12.Divide(histos[8],histos[4],"cl=0.683 b(1,1) mode")
EffVsPtCat12.SetTitle("")
EffVsPtCat12.GetXaxis().SetTitle("p_{T} [GeV]")
EffVsPtCat12.GetXaxis().SetLimits(300.,1500.)
EffVsPtCat12.GetYaxis().SetTitle("Efficiency")
EffVsPtCat12.GetYaxis().SetTitleOffset(1.16)
EffVsPtCat12.GetHistogram().SetMaximum(1.1)
EffVsPtCat12.GetHistogram().SetMinimum(0.)
EffVsPtCat12.SetMarkerStyle(20)
EffVsPtCat12.SetMarkerColor(4)

can[2].cd(1)
EffVsPt.Draw("AP")
EffVsPtCat4.Draw("Psame")
EffVsPtCat12.Draw("Psame")
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
l.AddEntry(EffVsPtCat4,"BDTCat4",'p')
l.AddEntry(EffVsPtCat12,"BDTCat12",'p')
l.Draw()
gPad.Update()


can[2].cd(2)
histos[11].Rebin(10)
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

histos[9].Rebin(10)
histos[10].Rebin(10)
bkg_EffVsPtCat4 = ROOT.TGraphAsymmErrors()
bkg_EffVsPtCat4.Divide(histos[9],histos[1],"cl=0.683 b(1,1) mode")
bkg_EffVsPtCat4.SetTitle("")
bkg_EffVsPtCat4.GetXaxis().SetTitle("p_{T} [GeV]")
bkg_EffVsPtCat4.GetXaxis().SetLimits(300.,1500.)
bkg_EffVsPtCat4.GetYaxis().SetTitle("Efficiency")
bkg_EffVsPtCat4.GetYaxis().SetTitleOffset(1.16)
bkg_EffVsPtCat4.GetHistogram().SetMaximum(1.1)
bkg_EffVsPtCat4.GetHistogram().SetMinimum(0.)
bkg_EffVsPtCat4.SetMarkerStyle(20)
bkg_EffVsPtCat4.SetMarkerColor(3)

bkg_EffVsPtCat12 = ROOT.TGraphAsymmErrors()
bkg_EffVsPtCat12.Divide(histos[10],histos[1],"cl=0.683 b(1,1) mode")
bkg_EffVsPtCat12.SetTitle("")
bkg_EffVsPtCat12.GetXaxis().SetTitle("p_{T} [GeV]")
bkg_EffVsPtCat12.GetXaxis().SetLimits(300.,1500.)
bkg_EffVsPtCat12.GetYaxis().SetTitle("Efficiency")
bkg_EffVsPtCat12.GetYaxis().SetTitleOffset(1.16)
bkg_EffVsPtCat12.GetHistogram().SetMaximum(1.1)
bkg_EffVsPtCat12.GetHistogram().SetMinimum(0.)
bkg_EffVsPtCat12.SetMarkerStyle(20)
bkg_EffVsPtCat12.SetMarkerColor(4)

bkg_EffVsPt.Draw("AP")
bkg_EffVsPtCat4.Draw("Psame")
bkg_EffVsPtCat12.Draw("Psame")
t.DrawLatex(.32,.4,"QCD")
l.Draw()
gPad.Update()


time.sleep(100)
del mytree
f.Close()