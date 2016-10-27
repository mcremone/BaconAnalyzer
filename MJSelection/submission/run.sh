#!/bin/bash

export SCRAM_ARCH=slc6_amd64_gcc481
source /cvmfs/cms.cern.ch/cmsset_default.sh
export JOBDIR=$PWD
cd /afs/cern.ch/work/q/qnguyen/public/BaconAnalyzer/CMSSW_8_0_10/src/BaconAnalyzer/MJSelection/production/
eval `scramv1 runtime -sh`
cd -

$1 $2 $3 $4 $5 $6 $7
