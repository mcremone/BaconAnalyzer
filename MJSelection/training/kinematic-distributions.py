from ROOT import *
import time

files = []

# files.append('tmp_reweighted_r800/TMVA_reweighted_r800.root')
# files.append('tmp_unweighted_r800/TMVA_unweighted_r800.root')
files.append('tmp_reweighted_rALL/validation_r800_forTraining.root')
files.append('tmp_reweighted_rALL/validation_qcd_forTraining.root')
files.append('tmp_unweighted_rALL/validation_qcd_forTraining.root')
files.append('tmp_unweighted_rALL/validation_r800_forTraining.root')

gStyle.SetGridColor(kGray)
gStyle.SetOptStat(kFALSE)
gStyle.SetPadTopMargin(0.07)
gStyle.SetPadBottomMargin(0.13)
gStyle.SetPadLeftMargin(0.14)
gStyle.SetPadRightMargin(0.06)
gROOT.ForceStyle()

histos = []

for j in range(0,17):
  hname = "histos_%d" % (j) # Each histogram must have a unique name
  htitle = ""
  if(j<13):
    histos.append( TH1F(hname, htitle, 800, 300., 1500.) )
  else:
    histos.append( TH1F(hname, htitle, 800, 50., 250.) )  
    histos[j].GetXaxis().SetTitle( "M_{G}" )
    histos[j].GetYaxis().SetTitle( "A.U" )
    histos[j].SetLineColor(j-12)
    histos[j].SetLineStyle(2)
    histos[j].SetLineWidth(2)
          
    
for t in files:
  f = TFile(t,"read") 
  # mytree=f.Get('TrainTree')
  mytree=f.Get('tree') 
  nentry = mytree.GetEntries()

###################FOR 800#########################
# #########for bkg eff == 10%
#   if(f.GetName().find("reweighted") != -1):
#     cutBDTCat8 = -0.001165
#     cutBDTG = 0.140891
#   elif(f.GetName().find("unweighted") != -1):
#     cutBDTCat8 = 0.034502
#     cutBDTG = 0.146482

#########for sig eff == 80%  
  # if(f.GetName().find("reweighted") != -1):
  #   cutBDTCat8 = -0.181514
  #   cutBDTG = 0.007407
  # elif(f.GetName().find("unweighted") != -1):
  #   cutBDTCat8 = 0.073687
  #   cutBDTG = 0.274368
  
###################FOR ALL#########################
# #########for bkg eff == 10%
  # if(f.GetName().find("reweighted") != -1):
  #   cutBDTCat8 = 0.145586
  #   cutBDTG = 0.193462
  # elif(f.GetName().find("unweighted") != -1):
  #   cutBDTCat8 = 0.181967
  #   cutBDTG = 0.245460

# #########for sig eff == 80%
  if(f.GetName().find("reweighted") != -1):
    cutBDTCat8 = -0.199049
    cutBDTG = -0.007056
  elif(f.GetName().find("unweighted") != -1):
    # cutBDTCat8 =  -0.108776
#     cutBDTG = 0.000997
      cutBDTCat8 = -0.199049
      cutBDTG = -0.007056

      
  print f.GetName()  
  print cutBDTG
  print cutBDTCat8
  
  for event in mytree:
    # ptEtaWeight = event.weight
    
    if(f.GetName().find("reweighted") != -1): #SIGNAL CLASSID==0
      # if event.classID==0:
      if(f.GetName().find("r800") != -1):
        histos[0].Fill( event.ptGroomed )
        if(event.BDTCat8>= cutBDTCat8):
          histos[1].Fill(event.ptGroomed)
          histos[13].Fill(event.massGroomed)
        if(event.BDTG>= cutBDTG):
          histos[2].Fill( event.ptGroomed )
      # if event.classID==1:
      if(f.GetName().find("qcd") != -1):
        histos[3].Fill( event.ptGroomed )
        if(event.BDTCat8>= cutBDTCat8):
          histos[14].Fill(event.massGroomed)
          histos[4].Fill(event.ptGroomed)
        if(event.BDTG>= cutBDTG):
          histos[5].Fill( event.ptGroomed )
          
    if(f.GetName().find("unweighted") != -1):
      # if event.classID==0:
      if(f.GetName().find("r800") != -1):
        histos[6].Fill( event.ptGroomed )
        if(event.BDTCat8>= cutBDTCat8):
          histos[7].Fill(event.ptGroomed)
          histos[15].Fill(event.massGroomed)
        if(event.BDTG>= cutBDTG):
          histos[8].Fill(event.ptGroomed)
      # if event.classID==1:
      if(f.GetName().find("qcd") != -1):
        histos[9].Fill(event.ptGroomed)
        if(event.BDTCat8>= cutBDTCat8):
          histos[10].Fill(event.ptGroomed)
          histos[16].Fill(event.massGroomed)
        if(event.BDTG>= cutBDTG):
          histos[12].Fill(event.ptGroomed)

          
histos[0].Rebin(10)
histos[1].Rebin(10)
histos[2].Rebin(10)
EffVsPt_Rew_r800 =  TGraphAsymmErrors() 
EffVsPt_Rew_r800.Divide(histos[1],histos[0],"cl=0.683 b(1,1) mode") 
EffVsPt_Rew_r800.SetTitle("") 
EffVsPt_Rew_r800.GetXaxis().SetTitle("p_{T} [GeV]") 
EffVsPt_Rew_r800.GetXaxis().SetLimits(300.,1500.) 
EffVsPt_Rew_r800.GetYaxis().SetTitle("Tagging Efficiency (H#rightarrowb#bar{b})") 
EffVsPt_Rew_r800.GetYaxis().SetTitleOffset(1.16) 
EffVsPt_Rew_r800.GetHistogram().SetMaximum(1.1)       
EffVsPt_Rew_r800.GetHistogram().SetMinimum(0.)   
EffVsPt_Rew_r800.SetMarkerStyle(20) 
EffVsPt_Rew_r800.SetMarkerColor(46) 


histos[6].Rebin(10)
histos[7].Rebin(10)
histos[8].Rebin(10)
EffVsPt_Unw_r800 =  TGraphAsymmErrors() 
EffVsPt_Unw_r800.Divide(histos[7],histos[6],"cl=0.683 b(1,1) mode") 
EffVsPt_Unw_r800.SetTitle("") 
EffVsPt_Unw_r800.GetXaxis().SetTitle("p_{T} [GeV]") 
EffVsPt_Unw_r800.GetXaxis().SetLimits(300.,1500.) 
EffVsPt_Unw_r800.GetYaxis().SetTitle("Tagging Efficiency (H#rightarrowb#bar{b})") 
EffVsPt_Unw_r800.GetYaxis().SetTitleOffset(1.16) 
EffVsPt_Unw_r800.GetHistogram().SetMaximum(1.1)       
EffVsPt_Unw_r800.GetHistogram().SetMinimum(0.)   
EffVsPt_Unw_r800.SetMarkerStyle(20) 
EffVsPt_Unw_r800.SetMarkerColor(42) 


c = TCanvas("c", "",800,800)
c.cd()
EffVsPt_Rew_r800.Draw("AP")
EffVsPt_Unw_r800.Draw("Psame")
c.SetGridx()
c.SetGridy()

legend = TLegend(.7,.75,.86,.85)
# legend = TLegend(.16,.17,.3,.25)
legend.SetBorderSize(0)
legend.SetFillColor(0)
legend.SetFillStyle(0)
legend.SetTextFont(42)
legend.SetTextSize(0.021)
legend.AddEntry(EffVsPt_Rew_r800,"reweighted",'p')
legend.AddEntry(EffVsPt_Unw_r800,"unweighted",'p')
legend.Draw()

l1 = TLatex()
l1.SetTextAlign(13)
l1.SetTextFont(42)
l1.SetNDC()
l1.SetTextSize(0.04)

l1.DrawLatex(0.14+0.03,0.85, "R(0.8+1.0+1.6+2.0 TeV)")

l1.SetTextAlign(12)
l1.SetTextSize(0.045)
l1.SetTextFont(62)
l1.DrawLatex(0.72,0.96, "#sqrt{s} = 13 TeV")

l1.SetTextFont(42)
l1.SetTextSize(0.025)
l1.DrawLatex(0.17,0.31, "80 % signal efficiency")
l1.DrawLatex(0.17,0.28, "70 GeV < M_{j} < 200 GeV , p_{T} > 300 GeV")


histos[3].Rebin(10)
histos[4].Rebin(10)
histos[5].Rebin(10)
EffVsPt_Rew_qcd =  TGraphAsymmErrors() 
EffVsPt_Rew_qcd.Divide(histos[4],histos[3],"cl=0.683 b(1,1) mode") 
EffVsPt_Rew_qcd.SetTitle("") 
EffVsPt_Rew_qcd.GetXaxis().SetTitle("p_{T} [GeV]") 
EffVsPt_Rew_qcd.GetXaxis().SetLimits(300.,1500.) 
EffVsPt_Rew_qcd.GetYaxis().SetTitle("Tagging Efficiency (g#rightarrowb#bar{b})") 
EffVsPt_Rew_qcd.GetYaxis().SetTitleOffset(1.16) 
EffVsPt_Rew_qcd.GetHistogram().SetMaximum(1.1)       
EffVsPt_Rew_qcd.GetHistogram().SetMinimum(0.)   
EffVsPt_Rew_qcd.SetMarkerStyle(20) 
EffVsPt_Rew_qcd.SetMarkerColor(46) 


histos[9].Rebin(10)
histos[10].Rebin(10)
histos[11].Rebin(10)
EffVsPt_Unw_qcd =  TGraphAsymmErrors() 
EffVsPt_Unw_qcd.Divide(histos[10],histos[9],"cl=0.683 b(1,1) mode") 
EffVsPt_Unw_qcd.SetTitle("") 
EffVsPt_Unw_qcd.GetXaxis().SetTitle("p_{T} [GeV]") 
EffVsPt_Unw_qcd.GetXaxis().SetLimits(300.,1500.) 
EffVsPt_Unw_qcd.GetYaxis().SetTitle("Tagging Efficiency (g#rightarrowb#bar{b})") 
EffVsPt_Unw_qcd.GetYaxis().SetTitleOffset(1.16) 
EffVsPt_Unw_qcd.GetHistogram().SetMaximum(1.1)       
EffVsPt_Unw_qcd.GetHistogram().SetMinimum(0.)   
EffVsPt_Unw_qcd.SetMarkerStyle(20) 
EffVsPt_Unw_qcd.SetMarkerColor(42) 

c2 = TCanvas("c2", "",800,800)
c2.cd()
EffVsPt_Rew_qcd.Draw("AP")
EffVsPt_Unw_qcd.Draw("Psame")
c2.SetGridx()
c2.SetGridy()
legend.Draw()
l1.SetTextAlign(13)
l1.SetTextFont(42)
l1.SetNDC()
l1.SetTextSize(0.04)

l1.SetTextAlign(13)
l1.SetTextFont(42)
l1.SetNDC()
l1.SetTextSize(0.04)

l1.DrawLatex(0.47+0.03,0.55, "R(0.8+1.0+1.6+2.0 TeV)")

l1.SetTextAlign(12)
l1.SetTextSize(0.045)
l1.SetTextFont(62)
l1.DrawLatex(0.72,0.96, "#sqrt{s} = 13 TeV")

l1.SetTextFont(42)
l1.SetTextSize(0.025)
l1.DrawLatex(0.53,0.91, "80 % signal efficiency")
l1.DrawLatex(0.53,0.87, "70 GeV < M_{j} < 200 GeV , p_{T} > 300 GeV")


for j in range(13,17):
  histos[j].Rebin(10)
  histos[j].Scale(1./(histos[j].Integral()))

c3 = TCanvas("c3", "",800,800)
c3.cd()
histos[13].Draw("HIST")
histos[14].Draw("HISTsame")
histos[15].Draw("HISTsame")
histos[16].Draw("HISTsame")
c3.SetGridx()
c3.SetGridy()

l1.SetTextAlign(13)
l1.SetTextFont(42)
l1.SetNDC()
l1.SetTextSize(0.04)

l1.DrawLatex(0.47+0.03,0.55, "R(0.8+1.0+1.6+2.0 TeV)")

l1.SetTextAlign(12)
l1.SetTextSize(0.045)
l1.SetTextFont(62)
l1.DrawLatex(0.72,0.96, "#sqrt{s} = 13 TeV")

l1.SetTextFont(42)
l1.SetTextSize(0.025)
l1.DrawLatex(0.53,0.91, "80 % signal efficiency")
l1.DrawLatex(0.53,0.87, "70 GeV < M_{j} < 200 GeV , p_{T} > 300 GeV")

legend2 = TLegend(.7,.75,.86,.85)
legend2.SetBorderSize(0)
legend2.SetFillColor(0)
legend2.SetFillStyle(0)
legend2.SetTextFont(42)
legend2.SetTextSize(0.021)
legend2.AddEntry(histos[13],"signal (reweighted)",'l')
legend2.AddEntry(histos[14],"bkg.   (reweighted)",'l')
legend2.AddEntry(histos[15],"signal (unweighted)",'l')
legend2.AddEntry(histos[16],"bkg.   (unweighted)",'l')
legend2.Draw()


time.sleep(200)
f.Close()