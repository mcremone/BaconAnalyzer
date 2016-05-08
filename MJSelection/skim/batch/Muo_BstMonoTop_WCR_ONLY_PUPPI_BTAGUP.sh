#!/bin/bash
cd /afs/cern.ch/work/m/mcremone/private/CMSSW_7_4_12_patch1/src/BaconSkim/MonoXSelection/skim
eval \`scramv1 runtime -sh\`
root -b -q skimMonoX.C+\(\"Muo\"\,\"BstMonoTop\"\,\"WCR\"\,\"ONLY\"\,\"PUPPI\"\,\"BTAGUP\"\)
