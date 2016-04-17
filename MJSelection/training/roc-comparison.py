from ROOT import *
import math

def getPerformanceCurve(fFileS1, fFileB1, pTmin, pTmax, fXMin=0, fXMax=0):
    #get files and histograms
    file_S1 = TFile(fFileS1)
    file_B1 = TFile(fFileB1)
    ''' 
    file_S174 = TFile("/tmp/cmantill/validation_mcsig15PUPPI_mcsig15PUPPI.root")
    file_B174 = TFile("/tmp/cmantill/validation_QCD_mcsig15PUPPI_mcsig15PUPPI.root")
    '''   
    file_S174 = TFile("Training_with/validation/validation_Zprime_svmass_test_withptcut.root")
    file_B174 = TFile("Training_with/validation/validation_QCD_svmass_test_withptcut.root")

    h2_S_new = TH1F("hBDTGDisc_S","",100000,-1.,1.)
    h2_B_new = TH1F("hBDTGDisc_B","",100000,-1.,1.)
    h2_S_subjet = TH1F("hSubjetDisc_S","",100000,0.,1.)
    h2_B_subjet = TH1F("hSubjetDisc_B","",100000,0.,1.)
    
    h2_S_new74 = TH1F("hBDTGDisc_S74","",100000,-1.,1.)
    h2_B_new74 = TH1F("hBDTGDisc_B74","",100000,-1.,1.)
    h2_S_subjet74 = TH1F("hSubjetDisc_S74","",100000,0.,1.)
    h2_B_subjet74 = TH1F("hSubjetDisc_B74","",100000,0.,1.)
    
    treeS=file_S1.Get('tree') 
    treeB=file_B1.Get('tree') 
    Sentry = treeS.GetEntries() 
    Bentry = treeB.GetEntries() 
        
    for event in treeS:
      subjetcsv =event.maxsubjetcsv
      if(event.maxsubjetcsv < -1):
          subjetcsv = -1
      elif(event.maxsubjetcsv >1):
          subjetcsv = -1
      if (event.bst15_PUPPIjet0_pt > 250 and event.isHadronicTop==1 and event.topSize < 0.8):
        h2_S_subjet.Fill( subjetcsv )
        h2_S_new.Fill( event.BDTG )
    
    for event in treeB:
      subjetcsv =event.maxsubjetcsv
      if(event.maxsubjetcsv < -1):
          subjetcsv = -1
      elif(event.maxsubjetcsv >1):
          subjetcsv = -1
      if (event.bst15_PUPPIjet0_pt > 250):
          h2_B_subjet.Fill( subjetcsv )
          h2_B_new.Fill( event.BDTG )

    treeS74=file_S174.Get('tree')
    treeB74=file_B174.Get('tree')
    Sentry74 = treeS74.GetEntries()
    Bentry74 = treeB74.GetEntries()

    for event in treeS74:
      subjetcsv74 =event.maxsubjetcsv
      if(event.maxsubjetcsv < -1):
          subjetcsv74 = -1
      elif(event.maxsubjetcsv >1):
          subjetcsv74 = -1
      if (event.bst15_PUPPIjet0_pt > 250 and event.isHadronicTop==1 and event.topSize < 0.8):
          h2_S_subjet74.Fill( subjetcsv74 )
          h2_S_new74.Fill( event.BDTG )
          
    for event in treeB74:
      subjetcsv74 =event.maxsubjetcsv
      if(event.maxsubjetcsv < -1):
         subjetcsv74 = -1
      elif(event.maxsubjetcsv >1):
         subjetcsv74 = -1
      if (event.bst15_PUPPIjet0_pt > 250):
          h2_B_subjet74.Fill( subjetcsv74 )
          h2_B_new74.Fill( event.BDTG )

    mg = []    
    
    #total jet count for denominator of efficiency calculation
    denom_S_1 = float( h2_S_new.Integral(0,100000) )
    denom_B_1 = float( h2_B_new.Integral(0,100000) )

    g_new = TGraph(100000)
    for i in range(100000):
        num_S = float( h2_S_new.Integral(100000-i*1,100000) )
        num_B = float( h2_B_new.Integral(100000-i*1,100000) )
        g_new.SetPoint( i,(num_S/denom_S_1),(num_B/denom_B_1) )
    
    g_subjet = TGraph(100000)
    for i in range(100000):
        num_S = float( h2_S_subjet.Integral(100000-i*1,100000) )
        num_B = float( h2_B_subjet.Integral(100000-i*1,100000) )
        g_subjet.SetPoint( i,(num_S/denom_S_1),(num_B/denom_B_1) )

    mg.append(g_new)
    mg.append(g_subjet)
    
    denom_S_174 = float( h2_S_new74.Integral(0,100000) )
    denom_B_174 = float( h2_B_new74.Integral(0,100000) )
    
    g_new74 = TGraph(100000)
    for i in range(100000):
        num_S74 = float( h2_S_new74.Integral(100000-i*1,100000) )
        num_B74 = float( h2_B_new74.Integral(100000-i*1,100000) )
        g_new74.SetPoint( i,(num_S74/denom_S_174),(num_B74/denom_B_174) )

    g_subjet74 = TGraph(100000)
    for i in range(100000):
        num_S74 = float( h2_S_subjet74.Integral(100000-i*1,100000) )
        num_B74 = float( h2_B_subjet74.Integral(100000-i*1,100000) )
        g_subjet74.SetPoint( i,(num_S74/denom_S_174),(num_B74/denom_B_174) )

    mg.append(g_new74)
    mg.append(g_subjet74)
    
    return mg

def formatGraph(graph, graphNum):
    #colors = [ kBlue+1, kAzure+1, kAzure+2, kBlack, kRed+2, kGreen+3, kCyan ]
    #style= [1,2,3,4,1,1,1]	
    colors = [ kBlue+1, kRed+2, kGreen+3, kCyan ]
    style= [1,1,1,1]
	
    graphColor = colors[graphNum % 7]
    lineStyle = style[graphNum % 7]
    graph.SetLineColor(graphColor)
    graph.SetLineStyle(lineStyle)
    graph.SetLineWidth(2)

def plotPerformanceCurves(graphs, ordering, fTitle, fXAxisTitle, fYAxisTitle, fExtraInfo, fOutputFile, fXmin, fXmax, fYmin, fYmax, fLogy=0):

    # gROOT.SetBatch(kTRUE)
    gStyle.SetGridColor(kGray)
    gStyle.SetOptStat(kFALSE)
    gStyle.SetPadTopMargin(0.07)
    gStyle.SetPadBottomMargin(0.13)
    gStyle.SetPadLeftMargin(0.14)
    gStyle.SetPadRightMargin(0.06)
    gROOT.ForceStyle()

    c = TCanvas("c", "",800,800)
    c.cd()
    bkg = TH2D("bkg","",100,fXmin,fXmax,100,fYmin,fYmax)
    bkg.GetXaxis().SetTitle(fXAxisTitle)
    bkg.GetYaxis().SetTitle(fYAxisTitle)
    bkg.SetTitleOffset(1.2,"X")
    bkg.SetTitleOffset(1.5,"Y")
    bkg.Draw()
    c.SetGridx()
    c.SetGridy()

    legend = TLegend(.16,.74,.36,.93)
    legend.SetBorderSize(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.031)

    graphCounter = 0
    for g in range(0,len(ordering)):
        graph = graphs[g]
        legend.AddEntry(graph, ordering[g],"l")
        formatGraph(graph,graphCounter)
        graph.Draw("L")
        graphCounter += 1

    if (fLogy):
        c.SetLogy()
    legend.Draw()
    l1 = TLatex()
    l1.SetTextAlign(13)
    l1.SetTextFont(42)
    l1.SetNDC()
    l1.SetTextSize(0.04)
    l1.DrawLatex(0.14+0.03,0.25, fTitle)

    l1.SetTextAlign(12)
    l1.SetTextSize(0.035)
    l1.SetTextFont(42)
    l1.DrawLatex(0.72,0.96, "(13 TeV)")
    
    l1.SetTextAlign(12)
    l1.SetTextSize(0.035)
    l1.SetTextFont(61)
    l1.DrawLatex(0.14,0.96, "CMS")
    l1.SetTextSize(0.03)
    l1.SetTextFont(52)
    l1.DrawLatex(0.22,0.955, "Simulation Preliminary")

    l1.SetTextFont(42)
    l1.SetTextSize(0.025)
    l1.DrawLatex(0.2,0.62, fExtraInfo)

    c.SaveAs(fOutputFile)
    name = fOutputFile+".root"
    f = TFile(name,"UPDATE");
    c.Write()
    f.Close()


def makePlots():

   ordering = [] # vectors storing the order of legend entries
   mg = [] # maps to hold legend entries and TGraph*s

   #mg15PUPPI = getPerformanceCurve("validation/validation_Zprime_svmass_ptcut_maxsubjetcsv_corrected.root","validation/validation_QCD_svmass_ptcut_maxsubjetcsv_corrected.root",300.,2000.)
   #mg15PUPPI = getPerformanceCurve("Training_with/validation/validation_Zprime_svmass_test_withptcut.root","Training_with/validation/validation_QCD_svmass_test_withptcut.root",300.,2000.)
   #mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_svmass_test_withptcut_withoutmaxsubjetcsv.root","Training_without/validation/validation_QCD_svmass_test_withptcut_withoutmaxsubjetcsv.root",300.,2000.)
   mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_svmass_test_withptcut_withoutmaxsubjetcsv.root","Training_without/validation/validation_QCD_svmass_test_withptcut_withoutmaxsubjetcsv.root",300.,2000.)
   #mg15CHS = getPerformanceCurve("validation/validation_mcsig15CHS_mcsig15CHS.root","validation/validation_QCD_mcsig15CHS_mcsig15CHS.root",300.,2000.)
   #mg8PUPPI = getPerformanceCurve("validation/validation_mcsig8PUPPI_mcsig8PUPPI.root","validation/validation_QCD_mcsig8PUPPI_mcsig8PUPPI.root",300.,2000.)
   #mg8CHS = getPerformanceCurve("validation/validation_mcsig8CHS_mcsig8CHS.root","validation/validation_QCD_mcsig8CHS_mcsig8CHS.root",300.,2000.)
   
   ordering.append("single-b-tag 76 without subjet")
   ordering.append("Subjet CSVv2 76")
   ordering.append("single-b-tag 74 without subjet")
   ordering.append("Subjet CSVv2 74")

   plotPerformanceCurves(mg15PUPPI,ordering,"","Tagging efficiency (Singleb)","Mistagging efficiency","CA15 PUPPI Pt > 250","comparison_withandwithout_single_bst15PUPPI_pt250.pdf",0, 1, 1E-3, 1, 1)
   #plotPerformanceCurves(mg15CHS,ordering,"","Tagging efficiency (Singleb)","Mistagging efficiency","CA15 CHS","singleb_subjet_bst15CHS.pdf",0, 1, 1E-3, 1, 1)
   #plotPerformanceCurves(mg8PUPPI,ordering,"","Tagging efficiency (Singleb)","Mistagging efficiency","AK8 PUPPI","singleb_subjet_bst8PUPPI.pdf",0, 1, 1E-3, 1, 1)
   #plotPerformanceCurves(mg8CHS,ordering,"","Tagging efficiency (Singleb)","Mistagging efficiency","AK8 CHS","singleb_subjet_bst8CHS.pdf",0, 1, 1E-3, 1, 1)


if __name__ == "__main__":
    makePlots()
