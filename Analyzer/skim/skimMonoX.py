#!/usr/bin/env python
# -*- coding: utf-8 -*

import optparse

parser = optparse.OptionParser()
parser.add_option('-p', '--preselection', help='preselection',dest='preselection')
parser.add_option('-l', '--selection', help='selection',dest='selection')
parser.add_option('-b', '--subsample', help='subsample',dest='subsample')
parser.add_option('-c', '--combo', help='combo',dest='combo')
parser.add_option('-a', '--algo', help='algo',dest='algo')
parser.add_option('-s', '--syst', help='syst',dest='syst')
(options, args) = parser.parse_args()

file_output = open ("batch/" + options.preselection + "_" + options.selection + "_" + options.subsample + "_" + options.combo + "_" + options.algo + "_" + options.syst + ".sh", "wa")

print >> file_output,  "#!/bin/bash"
print >> file_output,  "cd /afs/cern.ch/work/m/mcremone/private/CMSSW_7_4_12_patch1/src/BaconSkim/MonoXSelection/skim"
print >> file_output,  "eval \`scramv1 runtime -sh\`"
print >> file_output,  "root -b -q skimMonoX.C+\(\\\""+options.preselection+"\\\"\,\\\""+options.selection+"\\\"\,\\\""+options.subsample+"\\\"\,\\\""+options.combo+"\\\"\,\\\""+options.algo+"\\\"\,\\\""+options.syst+"\\\"\)"
