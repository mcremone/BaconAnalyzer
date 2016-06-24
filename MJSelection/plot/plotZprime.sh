#!/bin/bash

selection=$1
algo=$2
jet=$3


root -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.38,0.3\)


#root -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.25\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.30\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.35\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.40\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.45\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.50\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.55\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.60\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.65\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.70\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.75\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.80\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.85\) -b  plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\",0.90\) 


