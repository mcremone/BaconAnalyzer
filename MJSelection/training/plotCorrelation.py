from ROOT import *
import math

def get2DPlot(fFileS1, fFileB1, pTmin, pTmax, fXMin=0, fXMax=0):
    #get files and histograms
    file_S1 = TFile(fFileS1)
    file_B1 = TFile(fFileB1)

    h1_S_new = TH2D("hBDTGDiscvsPt_S","",30,0,200,30,-1.,1.)
    h1_B_new = TH2D("hBDTGDiscvsPt_B","",30,0,200,30,-1.,1.)
    #hprofilept = TProfile("hprofilept","BDTG vs Pt",20,0,2000,-1.,1.);
    hprofilemaxsubjetcsv = TProfile("hprofilemaxsubjetcsv","maxsubjetcsv vs Pt",20,0,2000,0,1.);

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
      if (event.bst15_PUPPIjet0_pt > 250 and event.bst15_PUPPIjet0_pt < 2000 and event.isHadronicTop==1 and event.topSize < 0.8):
        # h1_S_new.Fill( event.bst15_PUPPIjet0_pt, event.BDTG)
        # h1_S_new.Fill( event.bst15_PUPPIjet0_msd, event.BDTG)
          hprofilemaxsubjetcsv.Fill( event.bst15_PUPPIjet0_pt, subjetcsv)
    '''
    for event in treeB:
      subjetcsv =event.maxsubjetcsv
      if(event.maxsubjetcsv < -1):
          subjetcsv = -1
      elif(event.maxsubjetcsv >1):
          subjetcsv = -1
      if (event.bst15_PUPPIjet0_pt > 250 and event.bst15_PUPPIjet0_pt < 2000):
        #  h1_B_new.Fill( event.bst15_PUPPIjet0_pt, event.BDTG )
          h1_B_new.Fill( event.bst15_PUPPIjet0_msd, event.BDTG )
          '''
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

    #fpt = TF1("fpt","pol1", 200, 600)
    #hprofilept.Fit("fpt","R");

    fmaxsubjetcsv = TF1("fmaxsubjetcsv","pol1", 250, 2000)
    hprofilemaxsubjetcsv.Fit("fmaxsubjetcsv","R");

    hprofilemaxsubjetcsv.GetXaxis().SetTitle("Pt")
    hprofilemaxsubjetcsv.GetYaxis().SetTitle("Maxsubjetcsv")
    hprofilemaxsubjetcsv.SetTitleOffset(1.2,"X")
    hprofilemaxsubjetcsv.SetTitleOffset(1.5,"Y")
    hprofilemaxsubjetcsv.Draw("colz")
    c.SetGridx()
    c.SetGridy()

    c.SaveAs("maxsubjetcsvvsPt_prof_S.png")


def makePlots():

    # get2DPlot("Training_without/validation/validation_Zprime_svmass_test_withptcut_withoutmaxsubjetcsv.root","Training_without/validation/validation_QCD_svmass_test_withptcut_withoutmaxsubjetcsv.root",300.,2000.)
    # get2DPlot("Training_without/validation/validation_Zprime_includerho.root","Training_without/validation/validation_QCD_includerho.root",300.,2000.)
    get2DPlot("Training_with/validation/validation_Zprime_again.root","Training_with/validation/validation_QCD_again.root",300.,2000.)

if __name__ == "__main__":
    makePlots()
