#!/bin/bash

sample=$1
dir=$2

declare -a vmass=("50" "75" "100" "125" "150" "200" "250" "300" "400" "500")

if [[ ($sample = "All") || ($sample != "All" && $sample = "VectorDiJet") ]]
 then 
   for k in "${vmass[@]}"
    do 
      rm "$dir"/VectorDiJet"$k".root; hadd "$dir"/VectorDiJet1Jet_M"$k".root ../zprimebits/VectorDiJet1Jet_M"$k"_*/*.root     
    done
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm "$dir"/QCD.root; hadd  "$dir"/QCD.root ../zprimebits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then rm "$dir"/DY.root; hadd  "$dir"/DY.root ../zprimebits/*DYJets*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then rm "$dir"/W.root; hadd  "$dir"/W.root ../zprimebits/*WJetsToQQ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm "$dir"/TTbar_madgraphMLM.root; hadd "$dir"/TTbar_madgraphMLM.root ../zprimebits/*TTJets*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Diboson") ]]; then rm "$dir"/Diboson.root; hadd "$dir"/Diboson.root ../zprimebits/*WW*/*.root ../zprimebits/*WZ*/*.root ../zprimebits/*ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then rm "$dir"/JetHT.root; hadd "$dir"/JetHT.root ../zprimebits/JetHT*_data/*.root; fi

