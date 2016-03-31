#!/usr/bin/env python                                                           
# -*- coding: utf-8 -*

from optparse import OptionParser
import sys
import ConfigParser
import ROOT
import os
import multiprocessing
import array

# External vars
vars = [
  "bst15_PUPPIjet0_tau32",
  "bst15_PUPPIjet0_logchi",
  "bst15_PUPPIjet0_groomedIso",
  "bst15_PUPPIjet0_sumsjqg",
  "bst15_PUPPIjet0_msd",
  "bst15_PUPPIjet0_maxsubcsv",
  "bst15_PUPPIjet0_doublecsv"
]
 
# tracks
training_vars_tracks = [
  "bst15_PUPPIjet0_nTracks".
  "bst15_PUPPIjet0_nSV".
  "bst15_PUPPIjet0_trackSip2dSigAboveCharm_0",
  "bst15_PUPPIjet0_trackSip2dSigAboveCharm_1",
  "bst15_PUPPIjet0_trackSip2dSigAboveBottom_0",
  "bst15_PUPPIjet0_trackSip2dSigAboveBottom_1",
  "bst15_PUPPIjet0_trackSip3dSig_3",
  "bst15_PUPPIjet0_trackSip3dSig_2",
  "bst15_PUPPIjet0_trackSip3dSig_1", 
  "bst15_PUPPIjet0_trackSip3dSig_0",
  "bst15_PUPPIjet0_trackSip3dSig_3_1",
  "bst15_PUPPIjet0_trackSip3dSig_2_1",
  "bst15_PUPPIjet0_trackSip3dSig_1_1",
  "bst15_PUPPIjet0_trackSip3dSig_0_1"
  "bst15_PUPPIjet0_trackSip3dSig_3_2",
  "bst15_PUPPIjet0_trackSip3dSig_2_2",
  "bst15_PUPPIjet0_trackSip3dSig_1_2",
  "bst15_PUPPIjet0_trackSip3dSig_0_2"
  "bst15_PUPPIjet0_trackSip3dSig_3_3",
  "bst15_PUPPIjet0_trackSip3dSig_2_3",
  "bst15_PUPPIjet0_trackSip3dSig_1_3",
  "bst15_PUPPIjet0_trackSip3dSig_0_3"
]

training_vars_svmass = [
  "bst15_PUPPIjet0_tau_SVmass0_nSecondaryVertices", 
  "bst15_PUPPIjet0_tau_SVmass0_flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVmass0_vertexDeltaR", 
  "bst15_PUPPIjet0_tau_SVmass0_vertexNTracks",
  "bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_2", 
  "bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_1", 
  "bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVmass0_vertexEnergyRatio", 
  "bst15_PUPPIjet0_tau_SVmass0_vertexMass", 
  "bst15_PUPPIjet0_tau_SVmass0_vertexMass_corrected",
  "bst15_PUPPIjet0_tau_SVmass0_zratio"
  "bst15_PUPPIjet0_tau_SVmass1_nSecondaryVertices",
  "bst15_PUPPIjet0_tau_SVmass1_flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVmass1_vertexDeltaR",
  "bst15_PUPPIjet0_tau_SVmass1_vertexNTracks",
  "bst15_PUPPIjet0_tau_SVmass1_trackEtaRel_2",
  "bst15_PUPPIjet0_tau_SVmass1_trackEtaRel_1",
  "bst15_PUPPIjet0_tau_SVmass1_trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVmass1_vertexEnergyRatio",
  "bst15_PUPPIjet0_tau_SVmass1_vertexMass",
  "bst15_PUPPIjet0_tau_SVmass1_vertexMass_corrected",
  "bst15_PUPPIjet0_tau_SVmass1_zratio"
]

training_vars_svfd = [
  "bst15_PUPPIjet0_tau_SVfd0_nSecondaryVertices",
  "bst15_PUPPIjet0_tau_SVfd0_flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVfd0_vertexDeltaR",
  "bst15_PUPPIjet0_tau_SVfd0_vertexNTracks",
  "bst15_PUPPIjet0_tau_SVfd0_trackEtaRel_2",
  "bst15_PUPPIjet0_tau_SVfd0_trackEtaRel_1",
  "bst15_PUPPIjet0_tau_SVfd0_trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVfd0_vertexEnergyRatio",
  "bst15_PUPPIjet0_tau_SVfd0_vertexMass",
  "bst15_PUPPIjet0_tau_SVfd0_vertexMass_corrected",
  "bst15_PUPPIjet0_tau_SVfd0_zratio"
  "bst15_PUPPIjet0_tau_SVfd1_nSecondaryVertices",
  "bst15_PUPPIjet0_tau_SVfd1_flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVfd1_vertexDeltaR",
  "bst15_PUPPIjet0_tau_SVfd1_vertexNTracks",
  "bst15_PUPPIjet0_tau_SVfd1_trackEtaRel_2",
  "bst15_PUPPIjet0_tau_SVfd1_trackEtaRel_1",
  "bst15_PUPPIjet0_tau_SVfd1_trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVfd1_vertexEnergyRatio",
  "bst15_PUPPIjet0_tau_SVfd1_vertexMass",
  "bst15_PUPPIjet0_tau_SVfd1_vertexMass_corrected",
  "bst15_PUPPIjet0_tau_SVfd1_zratio"
]

argv = sys.argv
parser = OptionParser()
parser.add_option("-d", "--dstype", dest="dstype", default="mcsig15PUPPI", 
                              help="type of signal sample: mcsig15PUPPI,mcsig8PUPPI,mcsig15CHS,mcsig8CHS")                       
parser.add_option("-f", "--file", dest="filename", default="mcsig15PUPPI",
                  help="write to FILE", metavar="FILE")                                                                                                                                                                               			      			      			      			      
(opts, args) = parser.parse_args(argv)  

"""
train
"""
def train():
  
  # Output file
  outFile = ROOT.TFile('tmva_output/TMVA_%s.root'%opts.filename, 'RECREATE')
  print "Printing output to %s" %outFile.GetName()

  # Declare factory
  factory = ROOT.TMVA.Factory("TMVAClassification", 
                               outFile, 
                               "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification"
                             )
  TMVA_tools = ROOT.TMVA.Tools.Instance()

  # Declare trees
  treeS = ROOT.TChain('Events')
  treeB = ROOT.TChain('Events')
  treeS.Add('../singlebbits/Zprime.root')    
  treeB.Add('../singlebbits/QCD.root')
  
  # Signal and Background selection
  tag ='bst15_PUPPI'
  training_vars = training_vars_mcsig15PUPPI

    #signal_selection = '%sjet1sumsjqg>0 && %sjet1sumsjqg<1'%(tag,tag)
    #background_selection = '%sjet1sumsjqg>0 && %sjet1sumsjqg<1'%(tag,tag) # abs(flavour)!=5 no b? Ask Matteo                   
  signal_selection = '%sjet1nSV>-1 && %sjet1tau_SVfd_nSecondaryVertices>-1. && %sjet1tau_SVmass_nSecondaryVertices>-1. && %sjet1tau_SVfd_trackEtaRel_0 >-1. && %sjet1tau_SVfd_trackEtaRel_1 >-1. && %sjet1tau_SVfd_trackEtaRel_2>-1. && %sjet1tau_SVmass_trackEtaRel_0 >-1. && %sjet1tau_SVmass_trackEtaRel_1 >-1. && %sjet1tau_SVmass_trackEtaRel_2>-1. && %sjet1tau_SVfd_vertexNTracks>-1. && %sjet1tau_SVmass_vertexNTracks >-1. && %sjet1tau_SVfd_vertexDeltaR >-1. && %sjet1tau_SVmass_vertexDeltaR >-1. && %sjet1tau_SVfd_zratio > -1. && %sjet1tau_SVmass_zratio > -1. && %sjet1nTracks > -1. && %sjet1tau_SVfd_vertexEnergyRatio>-1. && %sjet1tau_SVmass_vertexEnergyRatio>-1. && %sjet1tau_SVfd_vertexEnergyRatio<20. && %sjet1tau_SVmass_vertexEnergyRatio<20. && %sjet1trackSip2dSigAboveBottom>-1 && %sjet1trackSip2dSigAboveCharm >-1. && %sjet1trackSip3dSig_0>-1. && %sjet1trackSip3dSig_1>-1. && %sjet1trackSip3dSig_2>-1. && %sjet1trackSip3dSig_3>-1. && %sjet1tau1_trackSip3dSig_0>-1. && %sjet1tau1_trackSip3dSig_1>-1. && %sjet1tau_SVfd_flightDistance2dSig>-1. && %sjet1tau_SVmass_flightDistance2dSig>-1.'%(tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag,tag)
  background_selection = signal_selection

  print "Signal selection = %s" %signal_selection
  print "Bkg selection = %s" %background_selection

  # Number of entries
  num_pass = treeS.GetEntries(signal_selection)
  num_fail = treeB.GetEntries(background_selection)
  print 'N events signal', num_pass
  print 'N events background', num_fail

  # Adding variables
  for var in training_vars:
    print "Adding variable: %s" %var
    factory.AddVariable(var, 'F')
  
  # Add Signal + Background
  factory.SetWeightExpression('1.')
  #factory.SetBackgroundWeightExpression("%sjet1weight"%tag)
  factory.AddSignalTree(treeS, 1.)
  factory.AddBackgroundTree(treeB, 1.)

  # Training
  factory.PrepareTrainingAndTestTree( ROOT.TCut(signal_selection), ROOT.TCut(background_selection), 
      "nTrain_Signal=0::nTest_Signal=0:nTrain_Background=0:nTest_Background=0:SplitMode=Random:!V" )
      # "nTrain_Signal=30000:nTest_Signal=12000:nTrain_Background=30000:nTest_Background=50000:SplitMode=Random:!V" )
  #factory.BookMethod( ROOT.TMVA.Types.kBDT,
  #                    "BDTG","!H:!V:NTrees=400:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.2:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=30:MaxDepth=3:PruneMethod=CostComplexity:PruneStrength=3")
  #factory.BookMethod( ROOT.TMVA.Types.kBDT,
  #                    "BDTG","!H:!V:NTrees=400:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=30")
  factory.BookMethod( ROOT.TMVA.Types.kBDT,
                      "BDTG","!H:!V:NTrees=400:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.2:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=30:MaxDepth=3:PruneMethod=CostComplexity:PruneStrength=3")
  factory.TrainAllMethods()
  # factory.OptimizeAllMethods()
  factory.TestAllMethods()
  factory.EvaluateAllMethods()

  outFile.Close()
 
  #ROOT.gROOT.LoadMacro('$ROOTSYS/include/tmva/test/TMVAGui.C')
  #ROOT.gROOT.LoadMacro('../TMVAGui.C')
  #ROOT.TMVAGui('tmva_output/TMVA_mcsig15PUPPI.root')
  #ROOT.TMVA.TMVAGui('TMVA_mcsig15PUPPI.root')
  #raw_input("Press Enter to continue...")

def read(inDirName, inFileName):
  print "Reading", inFileName
  print "################################"

  TMVA_tools = ROOT.TMVA.Tools.Instance()

  tree = ROOT.TChain('Events')
  tree.Add('%s%s' %(inDirName,inFileName))
  print '%s%s' %(inDirName,inFileName)
  print "################################"
  print "################################"
  print "################################"
  reader = ROOT.TMVA.Reader('TMVAClassification_BDTG')

  # select variables to add
  training_vars = []
  if opts.dstype == 'mcsig8CHS':
    training_vars = training_vars_mcsig8CHS
  if opts.dstype == 'mcsig8PUPPI':
    training_vars = training_vars_mcsig8PUPPI
  if opts.dstype == 'mcsig15CHS':
    training_vars = training_vars_mcsig15CHS
  if opts.dstype == 'mcsig15PUPPI':
    training_vars = training_vars_mcsig15PUPPI

  varDict = {}
  for var in training_vars:
    varDict[var] = array.array('f',[0])
    reader.AddVariable(var, varDict[var])
    
  reader.BookMVA("BDTG","weights/TMVAClassification_BDTG.weights.xml")

  bdtOuts = []
  maxsubjetcsvs = []

  hBDTGDisc = ROOT.TH1F("hBDTGDisc","",1000,-5,5)

  for jentry in xrange(tree.GetEntries()):
    ientry = tree.LoadTree(jentry)
    nb = tree.GetEntry(jentry)
    for var in varDict:
      varDict[var][0] = getattr(tree, var)
    bdtOutput = reader.EvaluateMVA("BDTG")
    bdtOuts.append(bdtOutput)
    if opts.dstype == 'mcsig8CHS':
      maxsubjetcsvs.append(tree.bst8_CHSjet1maxsubcsv)
    elif opts.dstype == 'mcsig8PUPPI':
      maxsubjetcsvs.append(tree.bst8_PUPPIjet1maxsubcsv)
    elif opts.dstype == 'mcsig15CHS':
      maxsubjetcsvs.append(tree.bst15_CHSjet1maxsubcsv)
    elif opts.dstype == 'mcsig15PUPPI':
      maxsubjetcsvs.append(tree.bst15_PUPPIjet1maxsubcsv)
    hBDTGDisc.Fill(bdtOutput)

    if jentry%10000 == 0:
      print jentry, bdtOutput

  writeSmallTree = True

  if writeSmallTree:
    print "Writing small tree"
    BDTG = array.array('f',[0])
    maxsubjetcsv = array.array('f',[0])

    fout = ROOT.TFile('validation/validation_%s_%s.root'%(inFileName.replace(".root",""),opts.filename), 'RECREATE')
    outTree = ROOT.TTree( 'tree', 'b-tagging training tree' )
    outTree.Branch('BDTG', BDTG, 'BDTG/F')
    outTree.Branch('maxsubjetcsv', maxsubjetcsv, 'maxsubjetcsv/F')

    for i in range(len((bdtOuts))):
      BDTG[0] = bdtOuts[i]
      maxsubjetcsv[0] = maxsubjetcsvs[i]
      if i%10000==0:
        print i, bdtOuts[i],maxsubjetcsvs[i]
      outTree.Fill()
      
    fout.Write()
    hBDTGDisc.Write()
    del hBDTGDisc
    fout.Close()
  print "done", inFileName

def readParallel():

  print "start readParallel()"
  ROOT.gROOT.SetBatch(True)
  parallelProcesses = multiprocessing.cpu_count()

  inDirName="trainingbits/rootfiles/"
  files = ['qcd_forTraining.root']

  # create Pool
  p = multiprocessing.Pool(parallelProcesses)
  print "Using %i parallel processes" %parallelProcesses

  for f in files:
    read(inDirName, f)
    # run jobs
    #p.apply_async(read, args = (inDirName, f,))

  p.close()
  p.join()

if __name__ == '__main__':
    train()
    inDirName="/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconSkim/BDTSelection/training/"
    files = ['QCD.root','Zprime.root']
    for f in files:
      read(inDirName, f)
# readParallel()

