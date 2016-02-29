#!/bin/bash
# Job Number 0, running over 1 files 
touch /afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAnalyzer/MJSelection/MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt1l/sub_runMJ_job0.sh.run
cd /afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAnalyzer/MJSelection/production
eval `scramv1 runtime -sh`
cd -
mkdir -p scratch
cd scratch
mkdir -p /afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAnalyzer/MJSelection/production/../MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt1l
if ( runMJ  root://eoscms//eos/cms/store/cmst3/group/monojet/production/07/Spring15_a25ns_TTJets_madgraph_MINIAOD/Spring15_a25ns_TTJets_madgraph_MINIAOD_bacon_6.root   mctt1l  none  831.76  1.125596e+07 ; mv Output.root /afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAnalyzer/MJSelection/production/../MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt1l/Output.root_job0_file6.root;  ) then
	 rm -rf ./bacon ./Output_job* 
	 touch /afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAnalyzer/MJSelection/MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt1l/sub_runMJ_job0.sh.done
else
	 touch /afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAnalyzer/MJSelection/MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt1l/sub_runMJ_job0.sh.fail
fi
rm -f /afs/cern.ch/user/c/cmantill/work/public/Bacon/BaconProduction/CMSSW_7_4_14/src/BaconAnalyzer/MJSelection/MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt1l/sub_runMJ_job0.sh.run
