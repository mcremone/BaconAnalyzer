#!/bin/bash

selection=$1
algo=$2
jet=$3

root -b -q plotZprime.C+\(\"${selection}\"\,\"${algo}\"\,\"${jet}\"\)
