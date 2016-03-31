from ROOT import *

def getPerformanceCurve(fFileS1, fFileB1, fPlotS1, fPlotB1, fXMin=0, fXMax=0):
    #get files and histograms
    file_S1 = TFile(fFileS1)
    file_B1 = TFile(fFileB1)

    h2_S_1 = file_S1.Get(fPlotS1)
    h2_B_1 = file_B1.Get(fPlotB1)

    #total jet count for denominator of efficiency calculation
    denom_S_1 = float( h2_S_1.Integral(380,610) )
    denom_B_1 = float( h2_B_1.Integral(380,610) )

    g_eff_1 = TGraph(49)

    for i in range(5):
        num_S = float( h2_S_1.Integral(602-i,602) )
        num_B = float( h2_B_1.Integral(602-i,602) )
        g_eff_1.SetPoint( i,(num_S/denom_S_1),1-(num_B/denom_B_1) )
        # g_eff_1.SetPoint( i,(num_B/denom_B_1),(num_S/denom_S_1) )

    for i in range(1,40):
        num_S = float( h2_S_1.Integral(602-(i*5),602) )
        num_B = float( h2_B_1.Integral(602-(i*5),602) )
        g_eff_1.SetPoint( i+4,(num_S/denom_S_1),1-(num_B/denom_B_1) )
        # g_eff_1.SetPoint(i+4,(num_B/denom_B_1),(num_S/denom_S_1) )
    for i in range(1,6):
        num_S = float( h2_S_1.Integral(407-i,602) )
        num_B = float( h2_B_1.Integral(407-i,602) )
        g_eff_1.SetPoint(i+43,(num_S/denom_S_1),1-(num_B/denom_B_1))
        # g_eff_1.SetPoint(i+43,(num_B/denom_B_1),(num_S/denom_S_1) )

    return g_eff_1

def formatGraph(graph, graphNum):
    colors = [ kGreen+2, kRed, kBlue, kBlack, kMagenta, kOrange+2, kCyan ]
    graphColor = colors[graphNum % 7]
    lineStyle = (graphNum % 11) + 1
    graph.SetLineColor(graphColor)
    graph.SetLineStyle(lineStyle)
    graph.SetLineWidth(2)

def plotPerformanceCurves(graphs, ordering, fTitle, fXAxisTitle, fYAxisTitle, fExtraInfo, fOutputFile, fXmin, fXmax, fYmin, fYmax, fLogy=0):

    gROOT.SetBatch(kTRUE)
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

    legend = TLegend(.16,.64,.36,.77)
    legend.SetBorderSize(0)
    legend.SetFillColor(0)
    legend.SetFillStyle(0)
    legend.SetTextFont(42)
    legend.SetTextSize(0.021)

    graphCounter = 0
    for g in ordering:
        graph = graphs[g]
        legend.AddEntry(graph, g,"l")
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
    l1.DrawLatex(0.14+0.03,0.85, fTitle)

    l1.SetTextAlign(12)
    l1.SetTextSize(0.045)
    l1.SetTextFont(62)
    l1.DrawLatex(0.72,0.96, "#sqrt{s} = 13 TeV")

    l1.SetTextFont(42)
    l1.SetTextSize(0.025)
    l1.DrawLatex(0.2,0.42, fExtraInfo)

    c.SaveAs(fOutputFile)


def makePlots():
    # for multiple plots on the same canvas

    #-------------------------------
    # # BB vs GSP: r800 validation
    ordering = [] # vectors storing the order of legend entries
    graphMap = {} # maps to hold legend entries and TGraph*s

    # graphMap["All_reweighted_r800"]    = getPerformanceCurve("tmp_reweighted_r800/validation2_r800_forTraining.root","tmp_reweighted_r800/validation2_qcd_forTraining.root","hBDTGDisc","hBDTGDisc")
    graphMap["1 MP (reweighted)"]   = getPerformanceCurve("tmp_reweighted_r800/validation2_r800_forTraining.root","tmp_reweighted_r800/validation2_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")
    graphMap["1 MP (unweighted)"]   = getPerformanceCurve("tmp_unweighted_r800/validation2_r800_forTraining.root","tmp_unweighted_r800/validation2_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")
    graphMap["All (reweighted)"]   = getPerformanceCurve("tmp_reweighted_rALL/validation_r800_forTraining.root","tmp_reweighted_rALL/validation_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")
    graphMap["All (unweighted)"]   = getPerformanceCurve("tmp_unweighted_rALL/validation_r800_forTraining.root","tmp_unweighted_rALL/validation_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")

    ordering.append("1 MP (reweighted)")
    ordering.append("1 MP (unweighted)")
    ordering.append("All (reweighted)")
    ordering.append("All (unweighted)")

    plotPerformanceCurves(graphMap,ordering,"R=(0.8 TeV)","Tagging efficiency (H#rightarrowb#bar{b})","1 - mistagging efficiency (g#rightarrowb#bar{b})","70 GeV < M_{p} < 200 GeV , p_{T} > 300 GeV","tmvacomp_r800validation.pdf",0, 1, 1E-3, 1, 0)

    #-------------------------------
    
    # #-------------------------------
    # BB vs GSP: r2000 validation
    # ordering = [] # vectors storing the order of legend entries
 #    graphMap = {} # maps to hold legend entries and TGraph*s
 #
 #    graphMap["1 MP (reweighted)"]   = getPerformanceCurve("tmp_reweighted_r800/validation2_r2000_forTraining.root","tmp_reweighted_r800/validation2_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")
 #    graphMap["1 MP (unweighted)"]   = getPerformanceCurve("tmp_unweighted_r800/validation2_r2000_forTraining.root","tmp_unweighted_r800/validation2_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")
 #    graphMap["All (reweighted)"]   = getPerformanceCurve("tmp_reweighted_rALL/validation_r2000_forTraining.root","tmp_reweighted_rALL/validation_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")
 #    graphMap["All (unweighted)"]   = getPerformanceCurve("tmp_unweighted_rALL/validation_r2000_forTraining.root","tmp_unweighted_rALL/validation_qcd_forTraining.root","hBDTCat8Disc","hBDTCat8Disc")
 #
 #    ordering.append("1 MP (reweighted)")
 #    ordering.append("1 MP (unweighted)")
 #    ordering.append("All (reweighted)")
 #    ordering.append("All (unweighted)")
 #
 #    plotPerformanceCurves(graphMap,ordering,"R=(2.0 TeV)","Tagging efficiency (H#rightarrowb#bar{b})","1 - mistagging efficiency (g#rightarrowb#bar{b})","70 GeV < M_{p} < 200 GeV , p_{T} > 300 GeV","tmvacomp_r2000validation.pdf",0, 1, 1E-3, 1, 0)
 #

if __name__ == "__main__":
    makePlots()
