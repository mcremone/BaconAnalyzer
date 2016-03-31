from ROOT import *
import time

# gROOT.SetBatch(kTRUE)
gStyle.SetGridColor(kGray)
gStyle.SetOptStat(kFALSE)
gStyle.SetPadTopMargin(0.07)
gStyle.SetPadBottomMargin(0.13)
gStyle.SetPadLeftMargin(0.14)
gStyle.SetPadRightMargin(0.06)
gROOT.ForceStyle()
gROOT.Reset()
gStyle.SetOptStat(0)  # What is displayed in the stats box for each histo.
gStyle.SetOptTitle(0)


fRew =  TFile.Open('tmp_reweighted_rALL/TMVA_reweighted_rALL.root', 'READ') 
fUnw =  TFile.Open('tmp_unweighted_rALL/TMVA_unweighted_rALL.root', 'READ')

bdtcat8_rew=fRew.Get('Method_Category/BDTCat8/MVA_BDTCat8_rejBvsS') 
bdtg_rew=fRew.Get('Method_BDT/BDTG/MVA_BDTG_rejBvsS') 

bdtcat8_unw=fUnw.Get('Method_Category/BDTCat8/MVA_BDTCat8_rejBvsS')
bdtg_unw=fUnw.Get('Method_BDT/BDTG/MVA_BDTG_rejBvsS')

l = TLegend(0.21,0.2,0.42,0.36)
l.SetBorderSize(0)
l.SetFillColor(0)
l.SetFillStyle(0)
l.SetTextFont(42)
l.SetTextSize(0.021)

histos = []
for i in range(0,1):
  histos.append([])
  for j in range(0,4):
    hname = "histos%d_%d" % (i, j) # Each histogram must have a unique name
    htitle = "Histogram %d %d" % (i, j) # Give each its own title.
    if (j == 0):
      histos[i].append(bdtg_rew)
      histos[i][j].SetTitle("All     (reweighted)" )
    elif (j == 1):
      histos[i].append(bdtcat8_rew)  
      histos[i][j].SetTitle("Cat8 (reweighted)" )
    if (j == 2):
      histos[i].append(bdtg_unw)
      histos[i][j].SetTitle("All     (unweighted)" )
    elif (j == 3):
      histos[i].append(bdtcat8_unw)  
      histos[i][j].SetTitle("Cat8 (unweighted)" )
      
    histos[i][j].SetMinimum(0)
    histos[i][j].SetLineColor(j+1)
    if(j<2):
      histos[i][j].SetLineStyle(2)
    else:
      histos[i][j].SetLineStyle(3)     
    histos[i][j].SetLineWidth(2)
    # histos[i][j].GetXaxis().SetNdivisions(30509)
    histos[i][j].GetXaxis().SetLabelSize(0.06)
    # histos[i][j].GetXaxis().CenterTitle()
    histos[i][j].GetXaxis().SetTitleSize(0.05)
    histos[i][j].GetXaxis().SetTitle( "H#rightarrowb#bar{b} efficiency" )
    histos[i][j].SetTitleOffset(1.2,"X")
    histos[i][j].SetTitleOffset(1.5,"Y")
    # histos[i][j].GetYaxis().SetNdivisions(30510)
    histos[i][j].GetYaxis().SetLabelSize(0.06)
    # histos[i][j].GetYaxis().CenterTitle()
    histos[i][j].GetYaxis().SetTitleSize(0.05)
    histos[i][j].GetYaxis().SetTitle("1 - g#rightarrowb#bar{b} efficiency")
    l.AddEntry(histos[i][j],histos[i][j].GetTitle(),'l')
   

l1 = TLatex()
l1.SetTextAlign(13)
l1.SetTextFont(42)
l1.SetNDC()
l1.SetTextSize(0.04)
   
c = TCanvas("c", "",800,800)
c.cd()
histos[0][0].Draw("HIST")
histos[0][1].Draw("HISTsame")
histos[0][2].Draw("HISTsame")
histos[0][3].Draw("HISTsame")
l.Draw()
c.SetGridx()
c.SetGridy()

l1.DrawLatex(0.14+0.03,0.85, "R(0.8 TeV)")

l1.SetTextAlign(12)
l1.SetTextSize(0.045)
l1.SetTextFont(62)
l1.DrawLatex(0.72,0.96, "#sqrt{s} = 13 TeV")

l1.SetTextFont(42)
l1.SetTextSize(0.025)
l1.DrawLatex(0.2,0.42, "70 GeV < M_{j} < 200 GeV , p_{T} > 300 GeV")

rew_bdtcat8=fRew.Get('Method_Category/BDTCat8/MVA_BDTCat8_effB') 
rew_bdtcat8.SetTitle("rew cat8")
rew_bdtg=fRew.Get('Method_BDT/BDTG/MVA_BDTG_effB')
rew_bdtg.SetTitle("rew bdtg")

unw_bdtcat8=fUnw.Get('Method_Category/BDTCat8/MVA_BDTCat8_effB')
unw_bdtcat8.SetTitle("unw cat8" )
unw_bdtg=fUnw.Get('Method_BDT/BDTG/MVA_BDTG_effB') 
unw_bdtg.SetTitle("unw bdtg")

histos2 = []
for j in range(0,4):
  hname = "histos2_%d" % (j)
  htitle = "Histogram2 %d" % (j) # Give each its own title.
  if (j == 0):
    histos2.append(rew_bdtcat8)
  elif (j == 1):
    histos2.append(rew_bdtg)
  elif (j == 2):
    histos2.append(unw_bdtcat8)
  elif (j == 3):
    histos2.append(unw_bdtg)

mistag = 0.10
for h in histos2:
  bin = h.FindLastBinAbove(mistag,1)
  print "For %s :" %(h.GetTitle())
  print "Purity = %2f" %(1-h.GetBinContent(bin))
  print "Cut value = %3f" %h.GetBinCenter(bin)
  print "################################"
  # pT_weight = pT_reweight_2b->GetBinContent( bin );
time.sleep(100)
fRew.Close()
fUnw.Close()