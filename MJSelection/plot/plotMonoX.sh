#!/bin/bash

preselection=$1
selection=$2
subsample=$3
combo=$4
algo=$5
syst=$6
bst15jetID=$7
bst8jetID=$8

root -b -q plotMonoX.C+\(\"${preselection}\"\,\"${selection}\"\,\"${subsample}\"\,\"${combo}\"\,\"${algo}\"\,\"${syst}\"\,\"${bst15jetID}\"\,\"${bst8jetID}\"\)
