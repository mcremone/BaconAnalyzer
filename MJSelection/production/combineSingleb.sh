#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../singlebbits/QCD.root;  hadd  ../singlebbits/QCD.root   ../singlebbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Zprime") ]]; then ../singlebbits/Zprime.root;  hadd  ../singlebbits/Zprime.root   ../singlebbits/*Zprime*/*.root; fi
