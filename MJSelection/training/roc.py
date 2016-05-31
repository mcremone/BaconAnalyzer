from ROOT import *
import math

def getPerformanceCurve(fFileS1, fFileB1, pTmin, pTmax, fXMin=0, fXMax=0):
    #get files and histograms
    file_S1 = TFile(fFileS1)
    file_B1 = TFile(fFileB1)

    file_S1w = TFile("Training_with/validation/validation_Zprime_75_s_svmass_QCD025Zprime075_wsj.root")
    file_B1w = TFile("Training_with/validation/validation_QCD_25_svmass_QCD025Zprime075_wsj.root")  
 
    file_S1wfj = TFile("Training_withfj/validation/validation_Zprime_75_s_svmass_QCD25Zprime75wfj.root")
    file_B1wfj = TFile("Training_withfj/validation/validation_QCD_25_svmass_QCD25Zprime75wfj.root")

    #file_S174 = TFile("/tmp/cmantill/validation_mcsig15PUPPI_svmass_test.root")
    #file_B174 = TFile("/tmp/cmantill/validation_QCD_mcsig15PUPPI_svmass_test.root")

    h2_S_new = TH1F("hBDTGDisc_S","",1000,-1.,1.)
    h2_B_new = TH1F("hBDTGDisc_B","",1000,-1.,1.)
    h2_S_subjet = TH1F("hSubjetDisc_S","",1000,0.,1.)
    h2_B_subjet = TH1F("hSubjetDisc_B","",1000,0.,1.)
    h2_S_fatjet = TH1F("hFatjetDisc_S","",1000,0.,1.)
    h2_B_fatjet = TH1F("hFatjetDisc_B","",1000,0.,1.)
    h2_S_doublecsv = TH1F("hDoublecsvDisc_S","",1000,0.,1.)
    h2_B_doublecsv = TH1F("hDoublecsvDisc_B","",1000,0.,1.)

    h2_S_neww = TH1F("hBDTGDisc_Sw","",1000,-1.,1.)
    h2_B_neww = TH1F("hBDTGDisc_Bw","",1000,-1.,1.)
    #h2_S_subjetw = TH1F("hSubjetDisc_Sw","",1000,0.,1.)
    #h2_B_subjetw = TH1F("hSubjetDisc_Bw","",1000,0.,1.)
    #h2_S_fatjetw = TH1F("hFatjetDisc_Sw","",1000,0.,1.)
    #h2_B_fatjetw = TH1F("hFatjetDisc_Bw","",1000,0.,1.)

    h2_S_newwfj = TH1F("hBDTGDisc_Swfj","",1000,-1.,1.)
    h2_B_newwfj = TH1F("hBDTGDisc_Bwfj","",1000,-1.,1.)
    #h2_S_subjetwfj = TH1F("hSubjetDisc_Swfj","",1000,0.,1.)
    #h2_B_subjetwfj = TH1F("hSubjetDisc_Bwfj","",1000,0.,1.)
    #h2_S_fatjetwfj = TH1F("hFatjetDisc_Swfj","",1000,0.,1.)
    #h2_B_fatjetwfj = TH1F("hFatjetDisc_Bwfj","",1000,0.,1.)
    '''
    h2_S_new74 = TH1F("hBDTGDisc_S74","",1000,-1.,1.)
    h2_B_new74 = TH1F("hBDTGDisc_B74","",1000,-1.,1.)
    h2_S_subjet74 = TH1F("hSubjetDisc_S74","",1000,0.,1.)
    h2_B_subjet74 = TH1F("hSubjetDisc_B74","",1000,0.,1.)
    '''
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
        if (event.bst15_PUPPIjet0_pt > 250 and event.isHadronicTop==1 and event.topSize < 0.8 and event.topMatching < 1.4 and event.topSize >0 and event.topMatching > 0):
            h2_S_subjet.Fill( subjetcsv )
            h2_S_new.Fill( event.BDTG )
            h2_S_fatjet.Fill( event.bst15_PUPPIjet0_fatjetcsv )
            h2_S_doublecsv.Fill( event.bst15_PUPPIjet0_doublecsv )
    
    for event in treeB:
        subjetcsv =event.maxsubjetcsv
        if(event.maxsubjetcsv < -1):
            subjetcsv = -1
        elif(event.maxsubjetcsv >1):
            subjetcsv = -1
        if (event.bst15_PUPPIjet0_pt > 250):
            h2_B_subjet.Fill( subjetcsv )
            h2_B_new.Fill( event.BDTG )
            h2_B_fatjet.Fill( event.bst15_PUPPIjet0_fatjetcsv )
            h2_B_doublecsv.Fill( event.bst15_PUPPIjet0_doublecsv )

    treeSw=file_S1w.Get('tree')
    treeBw=file_B1w.Get('tree')
    Sentryw = treeSw.GetEntries()
    Bentryw = treeBw.GetEntries()

    for event in treeSw:
        subjetcsvw =event.maxsubjetcsv
        if(event.maxsubjetcsv < -1):
            subjetcsvw = -1
        elif(event.maxsubjetcsv >1):
            subjetcsvw = -1
        if (event.bst15_PUPPIjet0_pt > 250 and event.isHadronicTop==1 and event.topSize < 0.8 and event.topMatching < 1.4 and event.topSize >0 and event.topMatching > 0):
            #h2_S_subjetw.Fill( subjetcsvw )
            h2_S_neww.Fill( event.BDTG )
            #h2_S_fatjetw.Fill( event.bst15_PUPPIjet0_fatjetcsv )

    for event in treeBw:
        subjetcsvw =event.maxsubjetcsv
        if(event.maxsubjetcsv < -1):
            subjetcsvw = -1
        elif(event.maxsubjetcsv >1):
            subjetcsvw = -1
        if (event.bst15_PUPPIjet0_pt > 250):
            #h2_B_subjetw.Fill( subjetcsvw )
            h2_B_neww.Fill( event.BDTG )
            #h2_B_fatjetw.Fill( event.bst15_PUPPIjet0_fatjetcsv )

    treeSwfj=file_S1wfj.Get('tree')
    treeBwfj=file_B1wfj.Get('tree')
    Sentrywfj = treeSwfj.GetEntries()
    Bentrywfj = treeBwfj.GetEntries()

    for event in treeSwfj:
        subjetcsvwfj =event.maxsubjetcsv
        if(event.maxsubjetcsv < -1):
            subjetcsvwfj = -1
        elif(event.maxsubjetcsv >1):
            subjetcsvwfj = -1
        if (event.bst15_PUPPIjet0_pt > 250 and event.isHadronicTop==1 and event.topSize < 0.8 and event.topMatching < 1.4 and event.topSize >0 and event.topMatching > 0):
            #h2_S_subjetwfj.Fill( subjetcsvwfj )
            h2_S_newwfj.Fill( event.BDTG )
            #h2_S_fatjetw.Fill( event.bst15_PUPPIjet0_fatjetcsv )

    for event in treeBwfj:
        subjetcsvwfj =event.maxsubjetcsv
        if(event.maxsubjetcsv < -1):
            subjetcsvwfj = -1
        elif(event.maxsubjetcsv >1):
            subjetcsvwfj = -1
        if (event.bst15_PUPPIjet0_pt > 250):
            #h2_B_subjetwfj.Fill( subjetcsvwfj )
            h2_B_newwfj.Fill( event.BDTG )
            #h2_B_fatjetwfj.Fill( event.bst15_PUPPIjet0_fatjetcsv )
    '''
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
        if (event.bst15_PUPPIjet1pt > 250):
            h2_S_subjet74.Fill( subjetcsv74 )
            h2_S_new74.Fill( event.BDTG )

    for event in treeB74:
        subjetcsv74 =event.maxsubjetcsv
        if(event.maxsubjetcsv < -1):
            subjetcsv74 = -1
        elif(event.maxsubjetcsv >1):
            subjetcsv74 = -1
        if (event.bst15_PUPPIjet1pt > 250):
            h2_B_subjet74.Fill( subjetcsv74 )
            h2_B_new74.Fill( event.BDTG )
    '''
    mg = []    
    
    #total jet count for denominator of efficiency calculation
    denom_S_1 = float( h2_S_new.Integral(0,1000) )
    denom_B_1 = float( h2_B_new.Integral(0,1000) )

    g_new = TGraph(1000)
    for i in range(1000):
        num_S = float( h2_S_new.Integral(1000-i*1,1000) )
        num_B = float( h2_B_new.Integral(1000-i*1,1000) )
        g_new.SetPoint( i,(num_S/denom_S_1),(num_B/denom_B_1) )
    
    g_subjet = TGraph(1000)
    for i in range(1000):
        num_S = float( h2_S_subjet.Integral(1000-i*1,1000) )
        num_B = float( h2_B_subjet.Integral(1000-i*1,1000) )
        g_subjet.SetPoint( i,(num_S/denom_S_1),(num_B/denom_B_1) )

    g_fatjet = TGraph(1000)
    for i in range(1000):
        num_S = float( h2_S_fatjet.Integral(1000-i*1,1000) )
        num_B = float( h2_B_fatjet.Integral(1000-i*1,1000) )
        g_fatjet.SetPoint( i,(num_S/denom_S_1),(num_B/denom_B_1) )

    g_doublecsv = TGraph(1000)
    for i in range(1000):
        num_S = float( h2_S_doublecsv.Integral(1000-i*1,1000) )
        num_B = float( h2_B_doublecsv.Integral(1000-i*1,1000) )
        g_doublecsv.SetPoint( i,(num_S/denom_S_1),(num_B/denom_B_1) )

    print 'Denom S1 %3.2f'%denom_S_1
    print 'Denom B1 %3.2f'%denom_B_1

    mg.append(g_new)
    mg.append(g_subjet)
    mg.append(g_fatjet)
    mg.append(g_doublecsv)

    denom_S_1w = float( h2_S_neww.Integral(0,1000) )
    denom_B_1w = float( h2_B_neww.Integral(0,1000) )

    g_neww = TGraph(1000)
    for i in range(1000):
        num_Sw = float( h2_S_neww.Integral(1000-i*1,1000) )
        num_Bw = float( h2_B_neww.Integral(1000-i*1,1000) )
        g_neww.SetPoint( i,(num_Sw/denom_S_1w),(num_Bw/denom_B_1w) )
    '''
    g_subjetw = TGraph(1000)
    for i in range(1000):
        num_Sw = float( h2_S_subjetw.Integral(1000-i*1,1000) )
        num_Bw = float( h2_B_subjetw.Integral(1000-i*1,1000) )
        g_subjetw.SetPoint( i,(num_Sw/denom_S_1w),(num_Bw/denom_B_1w) )
     
    g_fatjetw = TGraph(1000)
    for i in range(1000):
        num_Sw = float( h2_S_fatjetw.Integral(1000-i*1,1000) )
        num_Bw = float( h2_B_fatjetw.Integral(1000-i*1,1000) )
        g_fatjetw.SetPoint( i,(num_Sw/denom_S_1w),(num_Bw/denom_B_1w) )
    '''
    mg.append(g_neww)
    #mg.append(g_subjetw)
    #mg.append(g_fatjetw)

    print 'Denom S1w %3.2f'%denom_S_1w
    print 'Denom B1w %3.2f'%denom_B_1w

    denom_S_1wfj = float( h2_S_newwfj.Integral(0,1000) )
    denom_B_1wfj = float( h2_B_newwfj.Integral(0,1000) )

    g_newwfj = TGraph(1000)
    for i in range(1000):
        num_Swfj = float( h2_S_newwfj.Integral(1000-i*1,1000) )
        num_Bwfj = float( h2_B_newwfj.Integral(1000-i*1,1000) )
        g_newwfj.SetPoint( i,(num_Swfj/denom_S_1wfj),(num_Bwfj/denom_B_1wfj) )
    '''
    g_subjetwfj = TGraph(1000)
    for i in range(1000):
        num_Swfj = float( h2_S_subjetwfj.Integral(1000-i*1,1000) )
        num_Bwfj = float( h2_B_subjetwfj.Integral(1000-i*1,1000) )
        g_subjetwfj.SetPoint( i,(num_Swfj/denom_S_1wfj),(num_Bwfj/denom_B_1wfj) )
    
    g_fatjetwfj = TGraph(1000)
    for i in range(1000):
        num_Swfj = float( h2_S_fatjetw.Integral(1000-i*1,1000) )
        num_Bwfj = float( h2_B_fatjetw.Integral(1000-i*1,1000) )
        g_fatjetwfj.SetPoint( i,(num_Swfj/denom_S_1wfj),(num_Bwfj/denom_B_1wfj) )
        '''
    mg.append(g_newwfj)
    #mg.append(g_subjetwfj)
    #mg.append(g_fatjetwfj)

    print 'Denom S1wfj %3.2f'%denom_S_1wfj
    print 'Denom B1wfj %3.2f'%denom_B_1wfj
    """
    denom_S_174 = float( h2_S_new74.Integral(0,1000) )
    denom_B_174 = float( h2_B_new74.Integral(0,1000) )
    
    g_new74 = TGraph(1000)
    for i in range(1000):
        num_S74 = float( h2_S_new74.Integral(1000-i*1,1000) )
        num_B74 = float( h2_B_new74.Integral(1000-i*1,1000) )
        g_new74.SetPoint( i,(num_S74/denom_S_174),(num_B74/denom_B_174) )

    g_subjet74 = TGraph(1000)
    for i in range(1000):
        num_S74 = float( h2_S_subjet74.Integral(1000-i*1,1000) )
        num_B74 = float( h2_B_subjet74.Integral(1000-i*1,1000) )
        g_subjet74.SetPoint( i,(num_S74/denom_S_174),(num_B74/denom_B_174) )

    mg.append(g_new74)
    mg.append(g_subjet74)
    
    print 'Denom S174 %3.2f'%denom_S_174
    print 'Denom B174 %3.2f'%denom_B_174
    """
    return mg

def formatGraph(graph, graphNum):
    colors = [ kBlue+1, kAzure+1, kAzure-3, kBlack, kRed+2, kGreen+3, kCyan, kGreen, kOrange, kRed]
    style= [1,2,3,4,1,1,1,1,1,1]	
    #colors = [ kBlue+1, kRed+2, kGreen+3, kCyan ]
    #style= [1,1,1,1]
	
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
    bkg = TH2D("bkg","",10000,fXmin,fXmax,10000,fYmin,fYmax)
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

   # mg15PUPPI = getPerformanceCurve("validation/validation_Zprime_svmass_ptcut_maxsubjetcsv_corrected.root","validation/validation_QCD_svmass_ptcut_maxsubjetcsv_corrected.root",300.,2000.)
   # mg15PUPPI = getPerformanceCurve("Training_with/validation/validation_Zprime_svmass_test_withptcut.root","Training_with/validation/validation_QCD_svmass_test_withptcut.root",300.,2000.)
   # mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_svmass_test_withptcut_withoutmaxsubjetcsv.root","Training_without/validation/validation_QCD_svmass_test_withptcut_withoutmaxsubjetcsv.root",300.,2000.)
   # mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_svmass_test_withptcut_withoutmaxsubjetcsv.root","Training_without/validation/validation_QCD_svmass_test_withptcut_withoutmaxsubjetcsv.root",300.,2000.)
   # mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_includerho.root","Training_without/validation/validation_QCD_includerho.root",300.,2000.)
   # mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_033_1_svmass_topS08topM14Pt250_033.root","Training_without/validation/validation_QCD_033_1_svmass_topS08topM14Pt250_033.root",300.,2000.)
   # mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_something_1_svmass_topS08topM14Pt250_040_6000.root","Training_without/validation/validation_QCD_something_1_svmass_topS08topM14Pt250_040_6000.root",300.,2000.)
   # mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_2_svmass_Zprime075QCD025.root","Training_without/validation/validation_QCD_even_2_svmass_Zprime075QCD025.root",300.,2000.)
   mg15PUPPI = getPerformanceCurve("Training_without/validation/validation_Zprime_75_s_svmass_Signal25.root","Training_without/validation/validation_QCD_25_svmass_Signal25.root",300.,2000.)

   ordering.append("BDTG 76")
   ordering.append("Subjet CSVv2 76")
   ordering.append("Fatjet CSVv2 76")
   ordering.append("Double b")
   ordering.append("BDTG 76 with subj")
   #ordering.append("Subjet CSVv2 76 with subj")
   #ordering.append("Fatjet CSVv2 76 with subj")
   ordering.append("BDTG 76 with subj+fj")
   #ordering.append("Subjet CSVv2 76 with subj+fj")
   #ordering.append("Fatjet CSVv2 76 with subj+fj")
   #ordering.append("BDTG 74")
   #ordering.append("Subjet CSVv2 74")

   plotPerformanceCurves(mg15PUPPI,ordering,"","Tagging efficiency (Singleb)","Mistagging efficiency","CA15 PUPPI Pt > 250","roc7476_fj.pdf",0, 1, 1E-3, 1, 1)

if __name__ == "__main__":
    makePlots()
