#!/bin/bash

preselection=$1
selection=$2
subsample=$3
algo=$4
jet=$5

root -b plotZprime.C+\(\"Pho\"\,\"BoostedZprimeGamma\"\,\"SR\"\,\"PUPPI\"\,\"jet0\"\,0.6,0.3\)

#root -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.38,0.3\)

#root -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.25\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.30\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.35\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.40\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.45\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.50\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.55\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.60\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.65\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.70\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.75\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.80\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.85\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.90\) 


