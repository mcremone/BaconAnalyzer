#!/bin/bash                                                                                                                                                                                              

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then 
    rm monotop-boosted-combo-may8.root; hadd monotop-boosted-combo-may8.root monoxntuples/*BstMonoTop*; 
#    rm monotop-boosted-combo-up.root; hadd monotop-boosted-combo-up.root monoxntuples/*BstMonoTop*-UP*;
#    rm monotop-boosted-combo-down.root; hadd monotop-boosted-combo-down.root monoxntuples/*BstMonoTop*DOWN*;
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
    rm monohbb-boosted-combo-may8.root; hadd monohbb-boosted-combo-may8.root monoxntuples/*BstMonoHbb*;
fi
