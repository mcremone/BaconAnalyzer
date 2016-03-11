#!/bin/bash
cd /afs/cern.ch/work/m/mcremone/private/CMSSW_7_4_12_patch1/src/BaconSkim/MonoXSelection/plot
eval \`scramv1 runtime -sh\`
root -b -q plotMonoX.C+\(\"Zee\"\,\"BstMonoTop\"\,\"ZHFCR\"\,\"ONLY\"\,\"PUPPI\"\,\"CENT\"\)
