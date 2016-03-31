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

f = ROOT.TFile('TMVA_classification.root', 'read') 
mytree=f.Get('TrainTree') 
nentry = mytree.GetEntries() 

l = ROOT.TLegend(0.71,0.59,0.89,0.86,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)

histos = []
for i in range(0,1):
  histos.append([])
  for j in range(0,4):
    hname = "histos%d_%d" % (i, j) # Each histogram must have a unique name
    htitle = "Histogram %d %d" % (i, j) # Give each its own title.
    if (j == 0):
      htitle = "BKG"
      histos[i].append( TH1F(hname, htitle, 500, 0., 1500.) )
    elif (j == 1):
      htitle = "BKG"
      histos[i].append( TH1F(hname, htitle, 500, 0., 1500.) )
    elif (j == 3):
      htitle = "Signal"
      histos[i].append( TH1F(hname, htitle, 500, 0., 1500.) )
    else:
      htitle = "Signal"
      histos[i].append( TH1F(hname, htitle, 500, 0., 1500.) )
    
    if (j==0):  
      l.AddEntry(histos[i][j],"Weighted",'f')
    if (j==1):  
      l.AddEntry(histos[i][j],"Unweighted",'f')  
    histos[i][j].SetMinimum(0)
    histos[i][j].GetXaxis().SetNdivisions(6)
    histos[i][j].GetXaxis().SetLabelSize(0.06)
    histos[i][j].GetXaxis().CenterTitle()
    histos[i][j].GetXaxis().SetTitleSize(0.09)
    histos[i][j].GetXaxis().SetTitleOffset(0.8)
    histos[i][j].GetXaxis().SetTitle( "p_{T}" )

    histos[i][j].GetYaxis().SetNdivisions(4)
    histos[i][j].GetYaxis().SetLabelSize(0.06)
    histos[i][j].GetYaxis().CenterTitle()
    histos[i][j].GetYaxis().SetTitleSize(0.09)
    histos[i][j].GetYaxis().SetTitleOffset(1.1)
    histos[i][j].GetYaxis().SetTitle("A.U")
    


histos[0][1].SetLineColor(3)
histos[0][3].SetLineColor(3)
for event in mytree:
  if event.classID==0:
    histos[0][0].Fill( event.ptGroomed, event.weight )
    histos[0][1].Fill( event.ptGroomed )
  if event.classID==1:
    histos[0][2].Fill( event.ptGroomed, event.weight )
    histos[0][3].Fill( event.ptGroomed )
    
for i in range(0,1):
  for j in range(0,4):
    histos[i][j].Scale(1./(histos[i][j].Integral()))

num_canvases = 1
can = []
for i in range(0, num_canvases):
  name = "can%d" % (i) 
  title = "pT %d" % (i) 
  can.append(TCanvas( name, title, 10+10*i, 10+10*i, 800, 800 ))
  can[i].SetFillColor( 0 )
  can[i].Divide(0 , 2 ) 

can[0].cd(1)        
histos[0][0].Draw("HIST")   
histos[0][1].Draw("HISTsame")
l.Draw()
gPad.Update()
can[0].cd(2)
histos[0][2].Draw("HIST")   
histos[0][3].Draw("HISTsame")
l.Draw()
gPad.Update()

time.sleep(10)
del mytree
f.Close()