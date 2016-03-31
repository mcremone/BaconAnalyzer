import ROOT
from ROOT import *
import sys
import time
import gc
import math
import array

gROOT.Reset()
gStyle.SetOptStat(0)  # What is displayed in the stats box for each histo.
gStyle.SetStatH(0.3)   # Max height of stats box
gStyle.SetStatW(0.25)  # Max height of stats box
gStyle.SetPadLeftMargin(0.20)   # Left margin of the pads on the canvas.
gStyle.SetPadBottomMargin(0.20) # Bottom margin of the pads on the canvas.
gStyle.SetFrameFillStyle(0) # Keep the fill color of our pads white.

prefix = '/shome/thaarres/HiggsTagger/weighted_rootfiles'
# files = [ 'QCD1000-1400_forTraining.root',
#   'QCD1400-1800_forTraining.root',
#   'QCD170-300_forTraining.root',
#   'QCD300-470_forTraining.root',
#   'QCD470-600_forTraining.root',
#   'QCD600-800_forTraining.root',
#   'QCD800-1000_forTraining.root']

l = ROOT.TLegend(0.61,0.59,0.82,0.8,"","NDC")
l.SetLineWidth(2)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetTextFont(42)
l.SetTextSize(0.04)
l.SetTextAlign(12)

histos = []
for j in range(0,6):
  hname = "histos_%d" % (j)
  htitle = "Histogram %d" % (j) # Give each its own title.
  if (j == 0):
    htitle = "Background W"
    histos.append( TH1F(hname, htitle, 100, 0., 1500.) )
    
  elif (j == 1):
    htitle = "Background UW"
    histos.append( TH1F(hname, htitle, 100, 0., 1500.) )  
    
  elif (j == 2):
      htitle = "Background"
      histos.append(TH2F(hname,htitle,100, 0., 1500.,50, -2.5, 2.5))  
      
  elif (j == 3):
    htitle = "Signal W"
    histos.append( TH1F(hname, htitle, 100, 0., 1500.) )
    
  elif (j == 4):
    htitle = "Signal UW"
    histos.append( TH1F(hname, htitle, 100, 0., 1500.) )
      
  elif (j == 5):
      htitle = "Signal"
      histos.append(TH2F(hname,htitle,100, 0., 1500.,50, -2.5, 2.5))        
  if (j==0):
      l.AddEntry(histos[j],"weighted",'l')
  if (j==1):
    l.AddEntry(histos[j],"unweighted",'l')
  # histos[j].SetMinimum(0)
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
# histos[0][4].SetLineColor(3)
# histos[0][5].SetLineColor(3)
# histos[0][4].SetFillColor(1)
# histos[0][5].SetFillColor(1)
  
# n = 0
# print 'Starting event loop for %i files' %len(files)
# for f in files:
#   n += 1
#   print 'File %i/%i:' %(n,len(files))
#   infile = ROOT.TFile(prefix + '/' + f, 'read')
#   tree=infile.Get('Fjets')
#   nentry = tree.GetEntries()
#   print 'Looping over %i events in file %s' %(nentry,f)
#   for event in tree:
#     ptEtaWeight = event.weight_etaPt
#     # ptEtaWeight = 1.
#     histos[0].Fill( event.ptGroomed, ptEtaWeight)
#     histos[1].Fill( event.ptGroomed )
#     histos[2].Fill( event.ptGroomed, event.etaGroomed, ptEtaWeight )
fB = 'qcd_forTraining.root'
infileB = ROOT.TFile(prefix + '/' + fB, 'read')
treeB = infileB.Get('Fjets') 
print 'Starting event loop for file %s' %fB
for event in treeB:
  ptEtaWeight = event.weight_etaPt
  histos[0].Fill( event.ptGroomed, ptEtaWeight )
  histos[1].Fill( event.ptGroomed )
  histos[2].Fill( event.ptGroomed, event.etaGroomed )

fS = 'r800_forTraining.root'
infileS = ROOT.TFile(prefix + '/' + fS, 'read')
treeS = infileS.Get('Fjets') 
print 'Starting event loop for file %s' %fS
for event in treeS:
  ptEtaWeight = event.weight_etaPt
  histos[3].Fill( event.ptGroomed, ptEtaWeight )
  histos[4].Fill( event.ptGroomed )
  histos[5].Fill( event.ptGroomed, event.etaGroomed )  




for j in range(0,6):
  histos[j].Scale(1./(histos[j].Integral()))


# num_canvases = 2
# can = []
# for i in range(0, num_canvases):
#   name = "can%d" % (i)
#   title = "pT %d" % (i)
#   can.append(TCanvas( name, title, 10+10*i, 10+10*i, 1600, 800 ))
#   can[i].SetFillColor( 0 )
#   can[i].Divide(2 , 0 )
#
#
# t = ROOT.TLatex()
# t.SetNDC()
# t.SetTextAlign(12)
# t.SetTextSize(0.04)
#
#
# can[0].cd(1)
# histos[1].Draw("HIST")
# histos[0].Draw("HISTsame")
# l.Draw()
# t.DrawLatex(.5,.4,"QCD")
# # t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
# gPad.Update()
# can[0].cd(2)
# histos[4].Draw("HIST")
# histos[3].Draw("HISTsame")
# l.Draw()
# t.DrawLatex(.5,.4,"R(M800)")
# # t.DrawLatex(.5,.35,"80 GeV < M_{j} < 150 GeV")
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

fout = ROOT.TFile('etaPtCheck.root',"RECREATE")
for h in histos:
  h.Write()
fout.Close()

infileB.Close()
infileS.Close()
del treeS   
del treeB   
# time.sleep(100)
