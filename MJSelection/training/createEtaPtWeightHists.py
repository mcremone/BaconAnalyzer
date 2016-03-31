import sys
sys.argv.append( '-b-' )
import os
from ROOT import *
from array import array
import time
import multiprocessing
import thread
import subprocess


def processNtuple(inFileName, inDirName, outDirName,category):
  
  print "Starting to process %s" %inFileName
  # retrieve the ntuple of interest
  inFile = TFile( "%s/%s" %(inDirName, inFileName) )
  inTreeName = "Fjets"
  #inTreeName = category
  mychain = gDirectory.Get( inTreeName )
  
  # output
  outFileName = "%s/%s_EtaPtWeightHisto.root" %(outDirName, inFileName.replace("_forTraining", "").rsplit(".",1)[0])
  print "Writing to %s" %outFileName
  outFile = TFile( outFileName, 'recreate' )

  histo = TH2D("jets", "jets", 50, -2.5, 2.5, 40, 4.17438727, 6.95654544315); # pt starting from 15 and until 1000
  #mychain.Draw("log(ptGroomed+50):etaGroomed >> +jets", "", "Lego goff");
  mychain.Draw("log(ptGroomed+50):etaGroomed >> +jets", "", "Lego goff");   #after adding normalization and category weight branches
  histo_lin = TH2D("jets_lin", "jets_lin", 50, -2.5, 2.5, 100, 0., 1500.); # pt starting from 15 and until 1000  , default nbins was 40
  #mychain.Draw("ptGroomed:etaGroomed >> +jets_lin", "","Lego goff")
  mychain.Draw("ptGroomed:etaGroomed >> +jets_lin", "", "Lego goff")  # after adding normalization and category weight branches

  outFile.cd()
  histo.Write()
  histo_lin.Write()
  outFile.Close()
  inFile.Close()

def main():

  ROOT.gROOT.SetBatch(True)
  parallelProcesses = multiprocessing.cpu_count()
  # create Pool
  p = multiprocessing.Pool(parallelProcesses)
  print "Using %i parallel processes" %parallelProcesses
  
  outDirName = '/shome/thaarres/HiggsTagger/EtaPtWeights'     # for individual category histograms
  combDirName = '/shome/thaarres/HiggsTagger/EtaPtWeights'    # for combined histograms
  inDirName = "/shome/thaarres/HiggsTagger/rootfiles/signal"
  
  flavourCategoryDict = {}

  for inFileName in os.listdir(inDirName):
    if inFileName.endswith(".root"):
      # processNtuple(inFileName, inDirName, outDirName)
      # break
      sample = inFileName.replace("_forTraining", "").split("_",1)[0]
      sample = sample.replace(".root","")
      print sample
      key = "%s" %(sample)
      if key not in flavourCategoryDict:
        flavourCategoryDict[key] = []
      flavourCategoryDict[key].append(inFileName.replace(".root", "_EtaPtWeightHisto.root"))
      p.apply_async(processNtuple, args = (inFileName, inDirName, outDirName, sample))

  p.close()
  p.join()

  # # loop over all output files of one category and flavour and hadd them
  # outDirName = os.path.join(os.path.abspath(sys.path[0]), outDirName) # absolute path to be safe


if __name__ == "__main__":
  main()