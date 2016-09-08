import optparse
import os,sys
import json
import ROOT
import math
import pickle

from TopLJets2015.TopAnalysis.rounding import *


"""
A wrapper to store data and MC histograms for comparison
"""
class Plot(object):

    def __init__(self,name):
        self.name = name
        self.wideCanvas = True if 'ratevsrun' in self.name else False
        self.mc = {}
        self.dataH = None
        self.data = None
        self._garbageList = []
        self.plotformats = ['pdf','png']
        self.savelog = False
        self.ratiorange = (0.76,1.24)

    def add(self, h, title, color, isData):
        h.SetTitle(title)
        if isData:
            try:
                self.dataH.Add(h)
            except:
                self.dataH=h
                self.dataH.SetDirectory(0)
                self.dataH.SetMarkerStyle(20)
                self.dataH.SetMarkerSize(1.4)
                self.dataH.SetMarkerColor(color)
                self.dataH.SetLineColor(ROOT.kBlack)
                self.dataH.SetLineWidth(2)
                self.dataH.SetFillColor(0)
                self.dataH.SetFillStyle(0)
                self._garbageList.append(h)
        else:
            try:
                self.mc[title].Add(h)
            except:
                self.mc[title]=h
                self.mc[title].SetName('%s_%s' % (self.mc[title].GetName(), title ) )
                self.mc[title].SetDirectory(0)
                self.mc[title].SetMarkerStyle(1)
                self.mc[title].SetMarkerColor(color)
                self.mc[title].SetLineColor(ROOT.kBlack)
                self.mc[title].SetLineWidth(1)
                self.mc[title].SetFillColor(color)
                self.mc[title].SetFillStyle(1001)
                self._garbageList.append(h)

    def finalize(self):
        self.data = convertToPoissonErrorGr(self.dataH)

    def appendTo(self,outUrl):
        outF = ROOT.TFile.Open(outUrl,'UPDATE')
        if not outF.cd(self.name):
            outDir = outF.mkdir(self.name)
            outDir.cd()
        for m in self.mc :
            self.mc[m].Write(self.mc[m].GetName(), ROOT.TObject.kOverwrite)
        if self.dataH :
            self.dataH.Write(self.dataH.GetName(), ROOT.TObject.kOverwrite)
        if self.data :
            self.data.Write(self.data.GetName(), ROOT.TObject.kOverwrite)
        outF.Close()

    def reset(self):
        for o in self._garbageList:
            try:
                o.Delete()
            except:
                pass

    def show(self, outDir,lumi,noStack=False,saveTeX=False):

        if len(self.mc)<2 and self.dataH is None:
            print '%s has 0 or 1 MC!' % self.name
            return

        if len(self.mc)>0 and self.mc.values()[0].InheritsFrom('TH2') :
            print 'Skipping TH2'
            return

        cwid=1000 if self.wideCanvas else 500
        c = ROOT.TCanvas('c','c',cwid,500)
        c.SetBottomMargin(0.0)
        c.SetLeftMargin(0.0)
        c.SetTopMargin(0)
        c.SetRightMargin(0.00)

        #holds the main plot
        c.cd()
        p1 = None
        if self.dataH:
            p1=ROOT.TPad('p1','p1',0.0,0.2,1.0,1.0) if cwid!=1000 else ROOT.TPad('p1','p1',0.0,0.0,1.0,1.0)
            p1.SetRightMargin(0.05)
            p1.SetLeftMargin(0.12)
            p1.SetTopMargin(0.01)
            p1.SetBottomMargin(0.01)
        else:
            p1=ROOT.TPad('p1','p1',0.0,0.0,1.0,1.0)
            p1.SetRightMargin(0.05)
            p1.SetLeftMargin(0.12)
            p1.SetTopMargin(0.1)
            p1.SetBottomMargin(0.12)
        p1.Draw()

        p1.SetGridx(False)
        p1.SetGridy(False) #True)
        self._garbageList.append(p1)
        p1.cd()

        # legend
        iniy=0.9 if self.wideCanvas or noStack else 0.85
        dy=0.1 if noStack else 0.02
        ndy=len(self.mc) if noStack else max(len(self.mc)-2,0)
        leg = ROOT.TLegend(0.45, iniy-dy*ndy, 0.95, iniy+0.05)

        leg.SetBorderSize(0)
        leg.SetFillStyle(0)        
        leg.SetTextFont(43)
        leg.SetTextSize(12)
        nlegCols = 0

        if self.dataH is not None:
            if self.data is None: self.finalize()
            leg.AddEntry( self.data, self.data.GetTitle(),'p')
            nlegCols += 1
        for h in self.mc:
            
            #compare
            if noStack:
                refH=self.mc.values()[0]
                if refH!=self.mc[h]:
                    chi2=refH.Chi2Test( self.mc[h], 'WW CHI2')
                    pval=refH.Chi2Test( self.mc[h], 'WW')     
                    self.mc[h].SetTitle('#splitline{%s}{#chi^{2}=%3.1f (p-val: %3.3f)}'%(self.mc[h].GetTitle(),chi2,pval))
                else:
                    refH.SetLineWidth(2)

            leg.AddEntry(self.mc[h], self.mc[h].GetTitle(), 'f')
            nlegCols += 1
        if nlegCols ==0 :
            print '%s is empty'%self.name
            return

        if not noStack:
            leg.SetNColumns(ROOT.TMath.Min(nlegCols/2,3))

        # Build the stack to plot from all backgrounds
        totalMC = None
        stack = ROOT.THStack('mc','mc')
        for h in self.mc:

            if noStack:
                self.mc[h].SetFillStyle(0)
                self.mc[h].SetLineColor(self.mc[h].GetFillColor())
                
            stack.Add(self.mc[h],'hist')
            
            try:
                totalMC.Add(self.mc[h])
            except:
                totalMC = self.mc[h].Clone('totalmc')
                self._garbageList.append(totalMC)
                totalMC.SetDirectory(0)

        #test for null plots
        if totalMC :
            if totalMC.Integral()==0:
                if self.dataH is None : return
                if self.dataH.Integral()==0: return
        elif self.dataH is None : return
        elif self.dataH.Integral()==0 : return 


        frame = totalMC.Clone('frame') if totalMC is not None else self.dataH.Clone('frame')
        frame.Reset('ICE')
        if noStack:
            maxY=stack.GetStack().At(0).GetMaximum()/1.25
        elif totalMC:
            maxY = totalMC.GetMaximum() 
            if self.dataH:
                if maxY<self.dataH.GetMaximum():
                    maxY=self.dataH.GetMaximum()
        else:
            maxY=self.dataH.GetMaximum()

        frame.GetYaxis().SetRangeUser(0.1,maxY*1.45)

        frame.SetDirectory(0)
        frame.Reset('ICE')
        self._garbageList.append(frame)
        frame.GetYaxis().SetTitleSize(0.045)
        frame.GetYaxis().SetLabelSize(0.04)
        frame.GetYaxis().SetNoExponent()
        frame.GetYaxis().SetTitleOffset(1.3)
        frame.GetXaxis().SetTitleSize(0.0)
        frame.GetXaxis().SetLabelSize(0.0)
        frame.Draw()
        if totalMC is not None   : 
            if noStack: stack.Draw('nostack same')
            else      : stack.Draw('hist same')
        if self.data is not None : self.data.Draw('p')


        leg.Draw()
        txt=ROOT.TLatex()
        txt.SetNDC(True)
        txt.SetTextFont(43)
        txt.SetTextSize(16)
        txt.SetTextAlign(12)
        iniy=0.9 if self.wideCanvas else 0.95
        inix=0.12 if noStack else 0.18
        if lumi<100:
            txt.DrawLatex(inix,iniy,'#bf{CMS} #it{Preliminary} %3.1f pb^{-1} (13 TeV)' % (lumi) )
        else:
            txt.DrawLatex(inix,iniy,'#bf{CMS} #it{Preliminary} %3.1f fb^{-1} (13 TeV)' % (lumi/1000.) )

        #holds the ratio
        c.cd()
        if len(self.mc)>0 and self.dataH:
            p2 = ROOT.TPad('p2','p2',0.0,0.0,1.0,0.2)
            p2.Draw()
            p2.SetBottomMargin(0.4)
            p2.SetRightMargin(0.05)
            p2.SetLeftMargin(0.12)
            p2.SetTopMargin(0.01)
            p2.SetGridx(False)
            p2.SetGridy(True)
            self._garbageList.append(p2)
            p2.cd()
            ratioframe=frame.Clone('ratioframe')
            ratioframe.GetYaxis().SetTitle('Ratio')
            ratioframe.GetYaxis().SetRangeUser(self.ratiorange[0], self.ratiorange[1])
            self._garbageList.append(frame)
            ratioframe.GetYaxis().SetNdivisions(5)
            ratioframe.GetYaxis().SetLabelSize(0.18)        
            ratioframe.GetYaxis().SetTitleSize(0.2)
            ratioframe.GetYaxis().SetTitleOffset(0.25)
            ratioframe.GetXaxis().SetLabelSize(0.15)
            ratioframe.GetXaxis().SetTitleSize(0.2)
            ratioframe.GetXaxis().SetTitleOffset(0.8)
            ratioframe.Draw()

            try:
                ratio=self.dataH.Clone('ratio')
                ratio.SetDirectory(0)
                self._garbageList.append(ratio)
                ratio.Divide(totalMC)
                gr=ROOT.TGraphAsymmErrors(ratio)
                gr.SetMarkerStyle(self.data.GetMarkerStyle())
                gr.SetMarkerSize(self.data.GetMarkerSize())
                gr.SetMarkerColor(self.data.GetMarkerColor())
                gr.SetLineColor(self.data.GetLineColor())
                gr.SetLineWidth(self.data.GetLineWidth())
                gr.Draw('p')
            except:
                pass

        #all done
        c.cd()
        c.Modified()
        c.Update()

        #save
        for ext in self.plotformats : c.SaveAs(os.path.join(outDir, self.name+'.'+ext))
        if self.savelog:
            p1.cd()
            frame.GetYaxis().SetRangeUser(1,maxY*50)
            p1.SetLogy()
            c.cd()
            c.Modified()
            c.Update()
            for ext in self.plotformats : c.SaveAs(os.path.join(outDir, self.name+'_log.'+ext))

        if saveTeX : self.convertToTeX(outDir=outDir)


    def convertToTeX(self, outDir):
        if len(self.mc)==0:
            print '%s is empty' % self.name
            return

        f = open(outDir+'/'+self.name+'.dat','w')
        f.write('------------------------------------------\n')
        f.write("Process".ljust(20),)
        f.write("Events after each cut\n")
        f.write('------------------------------------------\n')

        tot ={}
        err = {}
        f.write(' '.ljust(20),)
        try:
            for xbin in xrange(1,self.mc.values()[0].GetXaxis().GetNbins()+1):
                pcut=self.mc.values()[0].GetXaxis().GetBinLabel(xbin)
                f.write(pcut.ljust(40),)
                tot[xbin]=0
                err[xbin]=0
        except:
            pass
        f.write('\n')
        f.write('------------------------------------------\n')

        for pname in self.mc:
            h = self.mc[pname]
            f.write(pname.ljust(20),)

            for xbin in xrange(1,h.GetXaxis().GetNbins()+1):
                itot=h.GetBinContent(xbin)
                ierr=h.GetBinError(xbin)
                pval=' & %s'%toLatexRounded(itot,ierr)
                f.write(pval.ljust(40),)
                tot[xbin] = tot[xbin]+itot
                err[xbin] = err[xbin]+ierr*ierr
            f.write('\n')

        f.write('------------------------------------------\n')
        f.write('Total'.ljust(20),)
        for xbin in tot:
            pval=' & %s'%toLatexRounded(tot[xbin],math.sqrt(err[xbin]))
            f.write(pval.ljust(40),)
        f.write('\n')

        if self.dataH is None: return
        f.write('------------------------------------------\n')
        f.write('Data'.ljust(20),)
        for xbin in xrange(1,self.dataH.GetXaxis().GetNbins()+1):
            itot=self.dataH.GetBinContent(xbin)
            pval=' & %d'%itot
            f.write(pval.ljust(40))
        f.write('\n')
        f.write('------------------------------------------\n')
        f.close()



"""
converts a histogram to a graph with Poisson error bars
"""
def convertToPoissonErrorGr(h):

    htype=h.ClassName()
    if htype.find('TH1')<0 : return None

    #check https://twiki.cern.ch/twiki/bin/view/CMS/PoissonErrorBars
    alpha = 1 - 0.6827;
    grpois = ROOT.TGraphAsymmErrors(h);
    for i in xrange(0,grpois.GetN()+1) :
        N = grpois.GetY()[i]
        if N<200 :
            L = 0
            if N>0 : L = ROOT.Math.gamma_quantile(alpha/2,N,1.)
            U = ROOT.Math.gamma_quantile_c(alpha/2,N+1,1)
            grpois.SetPointEYlow(i, N-L)
            grpois.SetPointEYhigh(i, U-N)
        else:
            grpois.SetPointEYlow(i, math.sqrt(N))
            grpois.SetPointEYhigh(i,math.sqrt(N))
    return grpois


def setTDRStyle():
    """
    Loads TDR style
    """
    tdrStyle = ROOT.TStyle("tdrStyle","Style for P-TDR")
    # For the canvas:
    tdrStyle.SetCanvasBorderMode(0)
    tdrStyle.SetCanvasColor(ROOT.kWhite)
    tdrStyle.SetCanvasDefH(928) #Height of canvas
    tdrStyle.SetCanvasDefW(904) #Width of canvas
    tdrStyle.SetCanvasDefX(1320)   #POsition on screen
    tdrStyle.SetCanvasDefY(0)

    # For the Pad:
    tdrStyle.SetPadBorderMode(0)
    # tdrStyle.SetPadBorderSize(Width_t size = 1)
    tdrStyle.SetPadColor(ROOT.kWhite)
    tdrStyle.SetPadGridX(False)
    tdrStyle.SetPadGridY(False)
    tdrStyle.SetGridColor(0)
    tdrStyle.SetGridStyle(3)
    tdrStyle.SetGridWidth(1)

    # For the frame:
    tdrStyle.SetFrameBorderMode(0)
    tdrStyle.SetFrameBorderSize(1)
    tdrStyle.SetFrameFillColor(0)
    tdrStyle.SetFrameFillStyle(0)
    tdrStyle.SetFrameLineColor(1)
    tdrStyle.SetFrameLineStyle(1)
    tdrStyle.SetFrameLineWidth(1)

    # For the histo:
    # tdrStyle.SetHistFillColor(1)
    # tdrStyle.SetHistFillStyle(0)
    tdrStyle.SetHistLineColor(1)
    tdrStyle.SetHistLineStyle(0)
    tdrStyle.SetHistLineWidth(1)
    # tdrStyle.SetLegoInnerR(Float_t rad = 0.5)
    # tdrStyle.SetNumberContours(Int_t number = 20)

    tdrStyle.SetEndErrorSize(2)
    #  tdrStyle.SetErrorMarker(20)
    tdrStyle.SetErrorX(0.)

    tdrStyle.SetMarkerStyle(20)

    # For the fit/function:
    tdrStyle.SetOptFit(1)
    tdrStyle.SetFitFormat("5.4g")
    tdrStyle.SetFuncColor(2)
    tdrStyle.SetFuncStyle(1)
    tdrStyle.SetFuncWidth(1)

    #For the date:
    tdrStyle.SetOptDate(0)

    # For the statistics box:
    tdrStyle.SetOptFile(0)
    tdrStyle.SetOptStat(0) # To display the mean and RMS:   SetOptStat("mr")
    tdrStyle.SetStatColor(ROOT.kWhite)
    tdrStyle.SetStatFont(42)
    tdrStyle.SetStatFontSize(0.025)
    tdrStyle.SetStatTextColor(1)
    tdrStyle.SetStatFormat("6.4g")
    tdrStyle.SetStatBorderSize(1)
    tdrStyle.SetStatH(0.1)
    tdrStyle.SetStatW(0.15)

    # Margins:
    tdrStyle.SetPadTopMargin(0.07)
    tdrStyle.SetPadBottomMargin(0.13)
    tdrStyle.SetPadLeftMargin(0.17)
    tdrStyle.SetPadRightMargin(0.03)

    # For the Global title:
    tdrStyle.SetOptTitle(0)
    tdrStyle.SetTitleFont(42)
    tdrStyle.SetTitleColor(1)
    tdrStyle.SetTitleTextColor(1)
    tdrStyle.SetTitleFillColor(10)
    tdrStyle.SetTitleFontSize(0.065)
    tdrStyle.SetTitleH(0.07) # Set the height of the title box
    tdrStyle.SetTitleW(0.80) # Set the width of the title box
    tdrStyle.SetTitleX(0.15) # Set the position of the title box
    tdrStyle.SetTitleY(1.00) # Set the position of the title box
    tdrStyle.SetTitleBorderSize(1)

    # For the axis titles:
    tdrStyle.SetTitleColor(1, "XYZ")
    tdrStyle.SetTitleFont(42, "XYZ")
    tdrStyle.SetTitleSize(0.06, "XYZ")
    # tdrStyle.SetTitleXSize(Float_t size = 0.02) # Another way to set the size?
    # tdrStyle.SetTitleYSize(Float_t size = 0.02)
    tdrStyle.SetTitleXOffset(0.95)
    tdrStyle.SetTitleYOffset(1.3)
    # tdrStyle.SetTitleOffset(1.1, "Y") # Another way to set the Offset

    # For the axis labels:
    tdrStyle.SetLabelColor(1, "XYZ")
    tdrStyle.SetLabelFont(42, "XYZ")
    tdrStyle.SetLabelOffset(0.007, "XYZ")
    tdrStyle.SetLabelSize(0.044, "XYZ")

    # For the axis:
    tdrStyle.SetAxisColor(1, "XYZ")
    tdrStyle.SetStripDecimals(True)
    tdrStyle.SetTickLength(0.03, "XYZ")
    tdrStyle.SetNdivisions(510, "XYZ")
    tdrStyle.SetPadTickX(1)  # To get tick marks on the opposite side of the frame
    tdrStyle.SetPadTickY(1)

    # Change for log plots:
    tdrStyle.SetOptLogx(0)
    tdrStyle.SetOptLogy(0)
    tdrStyle.SetOptLogz(0)

    # Postscript options:
    tdrStyle.SetPaperSize(20.,20.)
    tdrStyle.cd()
