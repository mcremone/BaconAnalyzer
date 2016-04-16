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
  "bst15_PUPPIjet0_maxsubcsv",
  "bst15_PUPPIjet0_nTracks",
  "bst15_PUPPIjet0_nSV",
  "bst15_PUPPIjet0_trackSip2dSigAboveCharm_0",
  # "bst15_PUPPIjet0_trackSip2dSigAboveCharm_1",
  "bst15_PUPPIjet0_trackSip2dSigAboveBottom_0",
  # "bst15_PUPPIjet0_trackSip2dSigAboveBottom_1",
  # "bst15_PUPPIjet0_trackSip3dSig_3",
  "bst15_PUPPIjet0_trackSip3dSig_2",
  "bst15_PUPPIjet0_trackSip3dSig_1", 
  "bst15_PUPPIjet0_trackSip3dSig_0",
  # "bst15_PUPPIjet0_trackSip3dSig_3_1",
  # "bst15_PUPPIjet0_trackSip3dSig_2_1",
  # "bst15_PUPPIjet0_trackSip3dSig_1_1",
  # "bst15_PUPPIjet0_trackSip3dSig_0_1",
  # "bst15_PUPPIjet0_trackSip3dSig_3_2",
  # "bst15_PUPPIjet0_trackSip3dSig_2_2",
  # "bst15_PUPPIjet0_trackSip3dSig_1_2",
  # "bst15_PUPPIjet0_trackSip3dSig_0_2",
  # "bst15_PUPPIjet0_trackSip3dSig_3_3",
  # "bst15_PUPPIjet0_trackSip3dSig_2_3",
  # "bst15_PUPPIjet0_trackSip3dSig_1_3",
  # "bst15_PUPPIjet0_trackSip3dSig_0_3"
]

training_vars_svmass = [
  # "bst15_PUPPIjet0_tau_SVmass0_nSecondaryVertices", 
  "bst15_PUPPIjet0_tau_SVmass0_flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVmass0_vertexDeltaR", 
  "bst15_PUPPIjet0_tau_SVmass0_vertexNTracks",
  "bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_2", 
  "bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_1", 
  "bst15_PUPPIjet0_tau_SVmass0_trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVmass0_vertexMass", 
  "bst15_PUPPIjet0_tau_SVmass0_vertexMass_corrected",
  "bst15_PUPPIjet0_tau_SVmass0_zratio",
  # "bst15_PUPPIjet0_tau_SVmass1_nSecondaryVertices",
  "bst15_PUPPIjet0_tau_SVmass1_flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVmass1_vertexDeltaR",
  "bst15_PUPPIjet0_tau_SVmass1_vertexNTracks",
  "bst15_PUPPIjet0_tau_SVmass1_trackEtaRel_2",
  "bst15_PUPPIjet0_tau_SVmass1_trackEtaRel_1",
  "bst15_PUPPIjet0_tau_SVmass1_trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVmass1_vertexMass",
  "bst15_PUPPIjet0_tau_SVmass1_vertexMass_corrected",
  "bst15_PUPPIjet0_tau_SVmass1_zratio"
]

training_vars_svfd = [
  "bst15_PUPPIjet0_tau_SVfd0_nSecondaryVertices",
  "bst15_PUPPIjet0_tau_SVfd0flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVfd0vertexDeltaR",
  "bst15_PUPPIjet0_tau_SVfd0vertexNTracks",
  "bst15_PUPPIjet0_tau_SVfd0trackEtaRel_2",
  "bst15_PUPPIjet0_tau_SVfd0trackEtaRel_1",
  "bst15_PUPPIjet0_tau_SVfd0trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVfd0vertexEnergyRatio",
  "bst15_PUPPIjet0_tau_SVfd0vertexMass",
  "bst15_PUPPIjet0_tau_SVfd0vertexMass_corrected",
#  "bst15_PUPPIjet0_tau_SVfd0zratio"
  "bst15_PUPPIjet0_tau_SVfd1_nSecondaryVertices",
  "bst15_PUPPIjet0_tau_SVfd1flightDistance2dSig",
  "bst15_PUPPIjet0_tau_SVfd1vertexDeltaR",
  "bst15_PUPPIjet0_tau_SVfd1vertexNTracks",
  "bst15_PUPPIjet0_tau_SVfd1trackEtaRel_2",
  "bst15_PUPPIjet0_tau_SVfd1trackEtaRel_1",
  "bst15_PUPPIjet0_tau_SVfd1trackEtaRel_0",
  "bst15_PUPPIjet0_tau_SVfd1vertexEnergyRatio",
  "bst15_PUPPIjet0_tau_SVfd1vertexMass",
  "bst15_PUPPIjet0_tau_SVfd1vertexMass_corrected"
#  "bst15_PUPPIjet0_tau_SVfd1zratio"
]

argv = sys.argv
parser = OptionParser()
parser.add_option("-g", "--gluonsplitting", dest="gluonsplitting", default=False, action="store_true",
                              help="train b vs. gsp")
parser.add_option("-C", "--charm", dest="charm", default=False, action="store_true",
                              help="train b vs. charm")
parser.add_option("-m", "--svmass", dest="svmass", default=True, action="store_true", 
                              help="svmass vars")
parser.add_option("-s", "--svfd", dest="svfd", default=False, action="store_true",
                              help="svmd vars")                       
parser.add_option("-f", "--file", dest="filename", default="PUPPI",
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
  #treeS.Add('trainingbits/Zprime.root')    
  treeS.Add('../singlebbits/Zprime.root')
  treeB.Add('../singlebbits/QCD.root')
  # treeB.Add('trainingbits/QCD.root')

  # Signal and Background selection
  tag ='bst15_PUPPIjet0'
  if(opts.svmass):
    training_vars = training_vars_tracks + training_vars_svmass
    tagsv = 'mass'
  elif(opts.svfd):
    training_vars = training_vars_tracks + training_vars_svfd
    tagsv = 'fd'
  else:
    training_vars = training_vars_tracks 

  signal_selection = 'bst15_PUPPIjet0_pt > 250 && isHadronicTop == 1 && topSize<0.8'#+' && nbHadrons>0 && abs(partonFlavor)==5' 
  print "Signal selection = %s" %signal_selection

  if(opts.gluonsplitting):
    background_selection = 'abs(partonFlavor==5) && nbHadrons>1' 
  elif(opts.charm):
    background_selection = 'abs(partonFlavor==4)'
  else:
    background_selection = 'bst15_PUPPIjet0_pt > 250' #+'&& nbHadrons<2 && abs(partonFlavor)!=5' # && isHadronicTop != 1 && topSize>=0.8 '#+'(partonFlavor==5||partonFlavor==-5)' #&& nbHadrons<2' # no b  abs(partonFlavor)!=5

  print "Bkg selection = %s" %background_selection
  
  #Number of entries
  num_pass = treeS.GetEntries(signal_selection)
  num_fail = treeB.GetEntries(background_selection)
  print 'N events signal', num_pass
  print 'N events background', num_fail

  # Adding variables
  for var in training_vars:
    print "Adding variable: %s" %var
    factory.AddVariable(var, 'F')

  #factory.AddVariable( '%s_tau_SV%s0_vertexEnergyRatio := (%s_tau_SV%s0_vertexEnergyRatio==%s_tau_SV%s0_vertexEnergyRatio) ? %s_tau_SV%s0_vertexEnergyRatio : -1'%(tag,tagsv,tag,tagsv,tag,tagsv,tag,tagsv), 'F')
  #factory.AddVariable( '%s_tau_SV%s1_vertexEnergyRatio := (%s_tau_SV%s1_vertexEnergyRatio==%s_tau_SV%s1_vertexEnergyRatio) ? %s_tau_SV%s1_vertexEnergyRatio : -1'%(tag,tagsv,tag,tagsv,tag,tagsv,tag,tagsv), 'F')
  factory.AddVariable( '%s_trackSip3dSig_3 := (%s_trackSip3dSig_3==%s_trackSip3dSig_3) ? %s_trackSip3dSig_3 : -1'%(tag,tag,tag,tag), 'F')

  factory.AddSpectator("bst15_PUPPIjet0_pt")
  factory.AddSpectator("topSize")
  factory.AddSpectator("isHadronicTop")
  
  # Add Signal + Background
  factory.SetWeightExpression('1.')
  factory.AddSignalTree(treeS, 1.)
  factory.AddBackgroundTree(treeB, 1.)

  # Training
  factory.PrepareTrainingAndTestTree( ROOT.TCut(signal_selection), ROOT.TCut(background_selection), 
      "nTrain_Signal=0::nTest_Signal=0:nTrain_Background=0:nTest_Background=0:SplitMode=Random:!V" )
  factory.BookMethod( ROOT.TMVA.Types.kBDT,
                      "BDTG","!H:!V:NTrees=400:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.2:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=30:MaxDepth=3:PruneMethod=CostComplexity:PruneStrength=3")

  factory.TrainAllMethods()
  # factory.OptimizeAllMethods()
  factory.TestAllMethods()
  factory.EvaluateAllMethods()

  outFile.Close()

def read(inDirName, inFileName):
  tag ='bst15_PUPPIjet0'
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

  bst15_PUPPIjet0_pt = array.array('f',[0])
  isHadronicTop = array.array('f',[0])
  topSize = array.array('f',[0])

  reader.AddSpectator("bst15_PUPPIjet0_pt", bst15_PUPPIjet0_pt)
  reader.AddSpectator("topSize", topSize)
  reader.AddSpectator("isHadronicTop", isHadronicTop)

  # select variables to add
  training_vars = []
  if(opts.svmass):
    training_vars = training_vars_tracks + training_vars_svmass
  elif(opts.svfd):
    training_vars = training_vars_tracks + training_vars_svfd
  else:
    training_vars = training_vars_tracks 

  varDict = {}
  for var in training_vars:
    varDict[var] = array.array('f',[0])
    reader.AddVariable(var, varDict[var])

  varDict['%s_trackSip3dSig_3'%tag] = array.array('f',[0])
  reader.AddVariable( '(bst15_PUPPIjet0_trackSip3dSig_3==bst15_PUPPIjet0_trackSip3dSig_3)?bst15_PUPPIjet0_trackSip3dSig_3:-1', varDict['%s_trackSip3dSig_3'%tag])

  reader.BookMVA("BDTG","weights/TMVAClassification_BDTG.weights.xml")

  bdtOuts             = []
  maxsubjetcsvs       = []
  bst15_PUPPIjet0_pts = []
  topSizes            = []
  isHadronicTops      = []
  
  hBDTGDisc = ROOT.TH1F("hBDTGDisc","",1000,-5,5)

  for jentry in xrange(tree.GetEntries()):
    ientry = tree.LoadTree(jentry)
    nb = tree.GetEntry(jentry)
    for var in varDict:
      varDict[var][0] = getattr(tree, var)
    bdtOutput = reader.EvaluateMVA("BDTG")
    bdtOuts.append(bdtOutput)
    maxsubjetcsvs.append(tree.bst15_PUPPIjet0_maxsubcsv)
    bst15_PUPPIjet0_pts.append(tree.bst15_PUPPIjet0_pt)
    topSizes.append(tree.topSize)
    isHadronicTops.append(tree.isHadronicTop)

    hBDTGDisc.Fill(bdtOutput)

  writeSmallTree = True

  if writeSmallTree:
    print "Writing small tree"
    BDTG               = array.array('f',[0])
    maxsubjetcsv       = array.array('f',[0])
    bst15_PUPPIjet0_pt = array.array('f',[0])
    topSize            = array.array('f',[0])
    isHadronicTop      = array.array('f',[0])

    fout = ROOT.TFile('validation/validation_%s_%s.root'%(inFileName.replace(".root",""),opts.filename), 'RECREATE')
    outTree = ROOT.TTree( 'tree', 'b-tagging training tree' )
    outTree.Branch('BDTG', BDTG, 'BDTG/F')
    outTree.Branch('maxsubjetcsv', maxsubjetcsv, 'maxsubjetcsv/F')
    outTree.Branch('bst15_PUPPIjet0_pt', bst15_PUPPIjet0_pt, 'pt/F')
    outTree.Branch('isHadronicTop', isHadronicTop, 'pt/F')
    outTree.Branch('topSize', topSize, 'pt/F')

    for i in range(len((bdtOuts))):
      BDTG[0]               = bdtOuts[i]
      maxsubjetcsv[0]       = maxsubjetcsvs[i]
      bst15_PUPPIjet0_pt[0] = bst15_PUPPIjet0_pts[i]
      topSize[0]            = topSizes[i]
      isHadronicTop[0]      = isHadronicTops[i]
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

  inDirName="/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/singlebbits/"
  files = ['QCD.root','Zprime.root']
  # create Pool
  p = multiprocessing.Pool(parallelProcesses)
  print "Using %i parallel processes" %parallelProcesses

  for f in files:
    read(inDirName, f)
  # run jobs
  p.apply_async(read, args = ("/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/singlebbits/", 'QCD.root',))
  p.apply_async(read, args = ("/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/singlebbits/", 'Zprime.root',))

  p.close()
  p.join()

if __name__ == '__main__':
    #train()
    inDirName="/afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_6_2/src/BaconAnalyzer/MJSelection/singlebbits/"
    files = ['QCD.root','Zprime.root']
    for f in files:
      read(inDirName, f)
    #readParallel()

