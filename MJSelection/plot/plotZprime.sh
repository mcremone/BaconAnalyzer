#!/bin/bash

preselection=$1
selection=$2
subsample=$3
combo=$4
algo=$5
syst=$6

root -b -q plotZprime.C+\(\"${preselection}\"\,\"${selection}\"\,\"${subsample}\"\,\"${combo}\"\,\"${algo}\"\,\"${syst}\"\)
