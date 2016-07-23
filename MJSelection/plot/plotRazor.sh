#!/bin/bash

preselection=$1
subsample=$2
combo=$3
algo=$4
syst=$5

root -b -q plotRazor.C+\(\"${preselection}\"\,\"${subsample}\"\,\"${combo}\"\,\"${algo}\"\,\"${syst}\"\)
