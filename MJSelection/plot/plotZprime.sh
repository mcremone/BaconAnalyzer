#!/bin/bash

selection=$1
algo=$2

root -b -q plotZprime.C+\(\"${selection}\"\,\"${algo}\"\)
