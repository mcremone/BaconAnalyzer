#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../monoxbits/QCD.root;  hadd  ../monoxbits/QCD.root   ../monoxbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    for x in `ls ../monoxbits | grep Monotop | grep -v .root`; do
	rm ../monoxbits/$x.root
	hadd ../monoxbits/$x.root ../monoxbits/$x/*.root
    done
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm ../monoxbits/DYHF.root;    hadd  ../monoxbits/DYHF.root     ../monoxbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm ../monoxbits/DYLF.root;    hadd  ../monoxbits/DYLF.root     ../monoxbits/*DYJets*_HT*mcdypluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm ../monoxbits/ZHF.root;    hadd  ../monoxbits/ZHF.root     ../monoxbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm ../monoxbits/ZLF.root;    hadd  ../monoxbits/ZLF.root     ../monoxbits/*ZJets*_HT*mczpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm ../monoxbits/WHF.root;    hadd  ../monoxbits/WHF.root     ../monoxbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm ../monoxbits/WLF.root;    hadd  ../monoxbits/WLF.root     ../monoxbits/*WJets*_HT*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../monoxbits/T.root;    hadd  ../monoxbits/T.root     ../monoxbits/ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TZ") ]]; then rm ../monoxbits/TZ.root;   hadd  ../monoxbits/TZ.root ../monoxbits/tZq*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../monoxbits/TT.root;    hadd  ../monoxbits/TT.root     ../monoxbits/TTJets_13TeV_amcatnloFXFX_pythia8_2_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTZ") ]]; then rm ../monoxbits/TTZ.root;   hadd  ../monoxbits/TTZ.root ../monoxbits/*TTZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTG") ]]; then rm ../monoxbits/TTG.root;   hadd  ../monoxbits/TTG.root ../monoxbits/*TTG*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../monoxbits/WW.root;   hadd  ../monoxbits/WW.root    ../monoxbits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../monoxbits/WZ.root;   hadd  ../monoxbits/WZ.root    ../monoxbits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../monoxbits/ZZ.root;   hadd  ../monoxbits/ZZ.root    ../monoxbits/*ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm ../monoxbits/GHF.root;    hadd  ../monoxbits/GHF.root     ../monoxbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm ../monoxbits/GLF.root;    hadd  ../monoxbits/GLF.root     ../monoxbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm ../monoxbits/MET.root; hadd  ../monoxbits/MET.root   ../monoxbits/MET*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm ../monoxbits/SingleElectron.root; hadd  ../monoxbits/SingleElectron.root   ../monoxbits/SingleElectron*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm ../monoxbits/SinglePhoton.root; hadd  ../monoxbits/SinglePhoton.root   ../monoxbits/SinglePhoton*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then rm ../monoxbits/SingleMuon.root; hadd  ../monoxbits/SingleMuon.root   ../monoxbits/SingleMuon*_data/*.root; fi