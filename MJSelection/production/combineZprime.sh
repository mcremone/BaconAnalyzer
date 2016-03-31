#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../Zprimebits/QCD.root;  hadd  ../Zprimebits/QCD.root   ../Zprimebits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then rm ../Zprimebits/DY.root;    hadd  ../Zprimebits/DY.root     ../Zprimebits/*DYJets*_HT*jets/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "Z") ]]; then rm ../Zprimebits/Z.root;    hadd  ../Zprimebits/Z.root     ../Zprimebits/*ZJetsToNuNu*jets/*.root; fi
    rm ../baconbits/$selection/Zbb.root;    hadd ../baconbits/$selection/Zbb.root     ../baconbits/$selection/*ZJets*_HT*zbb/*.root
    rm ../baconbits/$selection/Zcc.root;    hadd ../baconbits/$selection/Zcc.root     ../baconbits/$selection/*ZJets*_HT*zcc/*.root
    rm ../baconbits/$selection/Zlf.root;    hadd ../baconbits/$selection/Zlf.root     ../baconbits/$selection/*ZJets*_HT*vlf/*.root
    rm ../baconbits/$selection/Wcs.root;    hadd ../baconbits/$selection/Wcs.root     ../baconbits/$selection/*WJets*_HT*wcs/*.root
    rm ../baconbits/$selection/Wlf.root;    hadd ../baconbits/$selection/Wlf.root     ../baconbits/$selection/*WJets*_HT*vlf/*.root

if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then rm ../Zprimebits/W.root;    hadd  ../Zprimebits/W.root     ../Zprimebits/*WJets*_HT*mcwjets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../Zprimebits/T.root;    hadd  ../Zprimebits/T.root     ../Zprimebits/*_ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../Zprimebits/TT.root;   hadd  ../Zprimebits/TT.root    ../Zprimebits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../Zprimebits/WW.root;   hadd  ../Zprimebits/WW.root    ../Zprimebits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../Zprimebits/WZ.root;   hadd  ../Zprimebits/WZ.root    ../Zprimebits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../Zprimebits/ZZ.root;   hadd  ../Zprimebits/ZZ.root    ../Zprimebits/*ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then rm ../Zprimebits/JetHT.root; hadd  ../Zprimebits/JetHT.root   ../Zprimebits/MET_*_data/*.root; fi


 rm ../baconbits/$selection/T.root;    hadd ../baconbits/$selection/T.root     ../baconbits/$selection/*_ST_*/*.root
    rm ../baconbits/$selection/TT.root;   hadd ../baconbits/$selection/TT.root    ../baconbits/$selection/Spring15_a25ns_TTJets_amcatnlo_MINIAOD*/*.root
    rm ../baconbits/$selection/WW.root;   hadd ../baconbits/$selection/WW.root    ../baconbits/$selection/*WW*/*.root
    rm ../baconbits/$selection/WZ.root;   hadd ../baconbits/$selection/WZ.root    ../baconbits/$selection/*WZ*/*.root
    rm ../baconbits/$selection/ZZ.root;   hadd ../baconbits/$selection/ZZ.root    ../baconbits/$selection/*ZZ*/*.root
    rm ../baconbits/$selection/QCD.root;  hadd ../baconbits/$selection/QCD.root   ../baconbits/$selection/*QCD*/*.root
    rm ../baconbits/$selection/ZLObb.root;    hadd ../baconbits/$selection/ZLObb.root     ../baconbits/$selection/*DYJets*_HT*zbb/*.root
    rm ../baconbits/$selection/ZLOcc.root;    hadd ../baconbits/$selection/ZLOcc.root     ../baconbits/$selection/*DYJets*_HT*zcc/*.root
    rm ../baconbits/$selection/ZLOlf.root;    hadd ../baconbits/$selection/ZLOlf.root     ../baconbits/$selection/*DYJets*_HT*vlf/*.root
    rm ../baconbits/$selection/Zbb.root;    hadd ../baconbits/$selection/Zbb.root     ../baconbits/$selection/*ZJets*_HT*zbb/*.root
    rm ../baconbits/$selection/Zcc.root;    hadd ../baconbits/$selection/Zcc.root     ../baconbits/$selection/*ZJets*_HT*zcc/*.root
    rm ../baconbits/$selection/Zlf.root;    hadd ../baconbits/$selection/Zlf.root     ../baconbits/$selection/*ZJets*_HT*vlf/*.root
    rm ../baconbits/$selection/Wcs.root;    hadd ../baconbits/$selection/Wcs.root     ../baconbits/$selection/*WJets*_HT*wcs/*.root
    rm ../baconbits/$selection/Wlf.root;    hadd ../baconbits/$selection/Wlf.root     ../baconbits/$selection/*WJets*_HT*vlf/*.root
    rm ../baconbits/$selection/Data.root; hadd ../baconbits/$selection/Data.root   ../baconbits/$selection/JetHT_*v*/*.root
