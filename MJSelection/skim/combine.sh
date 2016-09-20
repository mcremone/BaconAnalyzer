#!/bin/bash                                                                                                                                                                                              

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then 
#     rm monotop-boosted-only-jun30.root; hadd monotop-boosted-only-jun30.root monoxntuples/*Bst15MonoTop*ONLY*; 
    rm monotop-semiboosted-combo-jul01.root; hadd monotop-semiboosted-combo-jul01.root monoxntuples/*Bst15SemMonoTop*COMBO*
#    rm monotop-boosted-combo-up.root; hadd monotop-boosted-combo-up.root monoxntuples/*BstMonoTop*-UP*;
#    rm monotop-boosted-combo-down.root; hadd monotop-boosted-combo-down.root monoxntuples/*BstMonoTop*DOWN*;
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
    #rm monohbb-boosted-combo-may27_bst15.root; hadd monohbb-boosted-combo-may27_bst15.root monoxntuples/*Bst15MonoHbb*COMBO*;
    #rm monohbb-resolved-combo-jun02_res.root; hadd monohbb-resolved-combo-jun02_res.root monoxntuples/*ResMonoHbb*COMBO*;
    #rm monohbb-boosted-only-may25_bst8.root; hadd monohbb-boosted-only-may25_bst8.root monoxntuples/*Bst8MonoHbb*ONLY*;
    #rm monohbb-resolved-only-may27_res.root; hadd monohbb-resolved-only-may27_res.root monoxntuples/*ResMonoHbb*ONLY*;
    rm monohbb-boosted-only-jun08_550750_bst15.root; hadd monohbb-boosted-only-jun08_550750_bst15.root monoxntuples/*Bst15MonoHbb*ONLY*;
fi
