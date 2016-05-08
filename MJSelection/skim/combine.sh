#!/bin/bash                                                                                                                                                                                              

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then 
    rm monotop-boosted-combo-apr6.root; hadd monotop-boosted-combo-apr6.root MonoXNtuples/*BstMonoTop*; 
#    rm monotop-boosted-combo-up.root; hadd monotop-boosted-combo-up.root MonoXNtuples/*BstMonoTop*-UP*;
#    rm monotop-boosted-combo-down.root; hadd monotop-boosted-combo-down.root MonoXNtuples/*BstMonoTop*DOWN*;
#    rm monotop-resolved-combo-cent.root; hadd monotop-resolved-combo-cent.root MonoXNtuples/*ResMonoTop*CENT*; 
#    rm monotop-resolved-combo-up.root; hadd monotop-resolved-combo-up.root MonoXNtuples/*ResMonoTop*-UP*;
#    rm monotop-resolved-combo-down.root; hadd monotop-resolved-combo-down.root MonoXNtuples/*ResMonoTop*DOWN*;
fi