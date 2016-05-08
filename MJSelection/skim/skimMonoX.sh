#!/bin/bash

#void skimMonoX(const string preselection, const string selection, const string subsample, const string combo, const string algo)
preselection=$1
selection=$2
subsample=$3
combo=$4
algo=$5
syst=$6

root -b -q skimMonoX.C+\(\"${preselection}\"\,\"${selection}\"\,\"${subsample}\"\,\"${combo}\"\,\"${algo}\"\,\"${syst}\"\)
