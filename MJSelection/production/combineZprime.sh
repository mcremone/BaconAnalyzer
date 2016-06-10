#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "Zprime") ]]; then
    for x in `ls ../zprimebits | grep ZPrimeToQQ | grep -v .root`; do
	rm ../zprimebits/$x.root
	hadd ../zprimebits//$x.root ../zprimebits/$x/*.root
    done
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "VectorDiJet") ]]; then
    for x in `ls ../zprimebits | grep VectorDiJet | grep -v .root`; do
        rm ../zprimebits/$x.root
        hadd ../zprimebits//$x.root ../zprimebits/$x/*.root
    done
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../zprimebits/QCD.root;     hadd  ../zprimebits/QCD.root    ../zprimebits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then rm ../zprimebits/DY.root;       hadd  ../zprimebits/DY.root     ../zprimebits/*DYJets*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYbb") ]]; then rm ../zprimebits/DYbb.root;   hadd  ../zprimebits/DYbb.root   ../zprimebits/DYJetsToQQ*mczbb/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYcc") ]]; then rm ../zprimebits/DYcc.root;   hadd  ../zprimebits/DYcc.root   ../zprimebits/DYJetsToQQ*mczcc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYlf") ]]; then rm ../zprimebits/DYlf.root;   hadd  ../zprimebits/DYlf.root   ../zprimebits/DYJetsToQQ*mczlf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then rm ../zprimebits/W.root;         hadd  ../zprimebits/W.root      ../zprimebits/*WJetsToQQ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Wcs") ]]; then rm ../zprimebits/Wcs.root;     hadd  ../zprimebits/Wcs.root    ../zprimebits/WJetsToQQ*mcwcs/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Wlf") ]]; then rm ../zprimebits/Wlf.root;     hadd  ../zprimebits/Wlf.root    ../zprimebits/WJetsToQQ*mcwlf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../zprimebits/T.root;         hadd  ../zprimebits/T.root      ../zprimebits/ST*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../zprimebits/TT.root;       hadd  ../zprimebits/TT.root     ../zprimebits/*TTJets*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../zprimebits/WW.root;       hadd  ../zprimebits/WW.root     ../zprimebits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../zprimebits/WZ.root;       hadd  ../zprimebits/WZ.root     ../zprimebits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../zprimebits/ZZ.root;       hadd  ../zprimebits/ZZ.root     ../zprimebits/*ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then rm ../zprimebits/JetHT.root; hadd  ../zprimebits/JetHT.root  ../zprimebits/JetHT*_data/*.root; fi
