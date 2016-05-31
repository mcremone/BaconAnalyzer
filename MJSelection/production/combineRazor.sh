#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../razorbits/QCD.root;  hadd  ../razorbits/QCD.root   ../razorbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    for x in `ls ../razorbits | grep Monotop | grep -v .root`; do
	rm ../razorbits/$x.root
	hadd ../razorbits/$x.root ../razorbits/$x/*.root
    done
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm ../razorbits/DYHF.root;    hadd  ../razorbits/DYHF.root     ../razorbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm ../razorbits/DYLF.root;    hadd  ../razorbits/DYLF.root     ../razorbits/*DYJets*_HT*mcdypluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm ../razorbits/ZHF.root;    hadd  ../razorbits/ZHF.root     ../razorbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm ../razorbits/ZLF.root;    hadd  ../razorbits/ZLF.root     ../razorbits/*ZJets*_HT*mczpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm ../razorbits/WHF.root;    hadd  ../razorbits/WHF.root     ../razorbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm ../razorbits/WLF.root;    hadd  ../razorbits/WLF.root     ../razorbits/*WJets*_HT*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../razorbits/T.root;    hadd  ../razorbits/T.root     ../razorbits/*_ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TZ") ]]; then rm ../razorbits/TZ.root;   hadd  ../razorbits/TZ.root ../razorbits/*tZq*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../razorbits/TT.root;    hadd  ../razorbits/TT.root     ../razorbits/TTJets_13TeV_amcatnloFXFX_pythia8_2_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTZ") ]]; then rm ../razorbits/TTZ.root;   hadd  ../razorbits/TTZ.root ../razorbits/*TTZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTG") ]]; then rm ../razorbits/TTG.root;   hadd  ../razorbits/TTG.root ../razorbits/*TTG*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../razorbits/WW.root;   hadd  ../razorbits/WW.root    ../razorbits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../razorbits/WZ.root;   hadd  ../razorbits/WZ.root    ../razorbits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../razorbits/ZZ.root;   hadd  ../razorbits/ZZ.root    ../razorbits/*ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm ../razorbits/GHF.root;    hadd  ../razorbits/GHF.root     ../razorbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm ../razorbits/GLF.root;    hadd  ../razorbits/GLF.root     ../razorbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm ../razorbits/MET.root; hadd  ../razorbits/MET.root   ../razorbits/MET_*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm ../razorbits/SingleElectron.root; hadd  ../razorbits/SingleElectron.root   ../razorbits/SingleElectron_*MINIAOD_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm ../razorbits/SinglePhoton.root; hadd  ../razorbits/SinglePhoton.root   ../razorbits/SinglePhoton_*_data/*.root; fi
