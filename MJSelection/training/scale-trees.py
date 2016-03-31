import sys
import os, commands
import shutil
from ROOT import *
import ROOT
from optparse import OptionParser

argv = sys.argv
parser = OptionParser()

parser.add_option("-d", "--useDAS", dest="useDAS", default=False, action="store_true",
                              help="Use # gen events from DAS")

(opts, args) = parser.parse_args(argv) 

inDirName = '/afs/cern.ch/work/m/mcremone/private/BTV-code/CMSSW_7_4_0_pre9/src/TopTagging/BDT/trainingbits'
outDirName = '/afs/cern.ch/work/m/mcremone/private/BTV-code/CMSSW_7_4_0_pre9/src/TopTagging/BDT/trainingbits/qcd_merged'
inTreeName = 'Fjets'
histName = "h_multiplicity"
targetFile = "trainingbits_qcd_forTraining"
addcmd = "hadd -f %s/%s.root " %(outDirName,targetFile)
rmcmd = "rm "

n = 0 
xSec = 1
genEv = 1
for inFileName in os.listdir(inDirName):
  if inFileName.endswith(".root"):
    n += 1
    print "copying file %i" %n

    if inFileName.find("120to170") != -1:
      xSec = 486200.
      genEv = 2001453. #events in DAS
      shutil.copy2("%s/%s" %(inDirName, inFileName), "%s/%s"%(outDirName, inFileName))
      inFile = TFile.Open( "%s/%s" %(outDirName, inFileName), "update" )
    elif inFileName.find("170to300") != -1:
      xSec = 12030.
      genEv = 2001169. #events in DAS
      shutil.copy2("%s/%s" %(inDirName, inFileName), "%s/%s"%(outDirName, inFileName))
      inFile = TFile.Open( "%s/%s" %(outDirName, inFileName), "update" )
      print "processing", inFileName
    elif inFileName.find("300to470") != -1:
      xSec = 7475.
      genEv = 1986177. #events in DAS
      shutil.copy2("%s/%s" %(inDirName, inFileName), "%s/%s"%(outDirName, inFileName))
      inFile = TFile.Open( "%s/%s" %(outDirName, inFileName), "update" )
      print "processing", inFileName
#    elif inFileName.find("470to600") != -1:
#      xSec = 587.1
#      genEv = 2001071. #events in DAS
#    elif inFileName.find("600to800") != -1:
#      xSec = 167.0
#      genEv = 1997744. #events in DAS
#    elif inFileName.find("800to1000") != -1:  
#      xSec = 28.25
#      genEv = 1000065. #events in DAS
#    elif inFileName.find("1000to1400") != -1:
#      xSec = 8.195
#      genEv = 500550. #events in DAS
#    elif inFileName.find("1400to1800") != -1:
#      xSec = 0.7346
#      genEv = 199627.0 #events in DAS
    else:
      print " Cross section not defined! Exiting..."
      continue
#      sys.exit()
    if not opts.useDAS:
      print inFileName	
      genEv = inFile.Get(histName).GetEntries()
      print 'Not using gen events from DAS! Using %i events stored in %s' %(genEv,inFileName)
    weight = xSec/genEv
    
    myTree = inFile.Get( inTreeName )
    myTree.SetWeight(weight)
    myTree.AutoSave()

    addcmd+= ' %s/%s' %(outDirName, inFileName)
    rmcmd += ' %s/%s' %(outDirName, inFileName)

os.system(addcmd)
print "Removing temporary files..."
os.system(rmcmd)
inFile.Close()
del myTree
