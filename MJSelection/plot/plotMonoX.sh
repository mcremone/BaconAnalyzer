#!/bin/bash

#void plotMonoX(const string preselection, const string selection, const string subsample, const string combo, const string algo)
preselection=$1
selection=$2
subsample=$3
combo=$4
algo=$5
syst=$6

root -b -q plotMonoX.C+\(\"${preselection}\"\,\"${selection}\"\,\"${subsample}\"\,\"${combo}\"\,\"${algo}\"\,\"${syst}\"\)
