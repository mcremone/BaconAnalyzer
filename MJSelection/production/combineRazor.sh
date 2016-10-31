#!/bin/bash

sample=$1

if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../razorbits/QCD.root;  hadd -k  ../razorbits/QCD.root   ../razorbits/*QCD*mc/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm ../razorbits/DYHF.root;    hadd -k  ../razorbits/DYHF.root     ../razorbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm ../razorbits/DYLF.root;    hadd -k  ../razorbits/DYLF.root     ../razorbits/*DYJets*_HT*mcdypluslf/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm ../razorbits/ZHF.root;    hadd -k  ../razorbits/ZHF.root     ../razorbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm ../razorbits/ZLF.root;    hadd -k  ../razorbits/ZLF.root     ../razorbits/*ZJets*_HT*mczpluslf/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm ../razorbits/WHF.root;    hadd -k  ../razorbits/WHF.root     ../razorbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm ../razorbits/WLF.root;    hadd -k  ../razorbits/WLF.root     ../razorbits/*WJets*_HT*mcwpluslf/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../razorbits/T.root;    hadd -k  ../razorbits/T.root     ../razorbits/*ST_*/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../razorbits/TT.root;    hadd -k  ../razorbits/TT.root     ../razorbits/TTJets*/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../razorbits/WW.root;   hadd -k  ../razorbits/WW.root    ../razorbits/*WW*/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../razorbits/WZ.root;   hadd -k  ../razorbits/WZ.root    ../razorbits/*WZ*/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../razorbits/ZZ.root;   hadd -k  ../razorbits/ZZ.root    ../razorbits/*ZZ*/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm ../razorbits/GHF.root;    hadd -k  ../razorbits/GHF.root     ../razorbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "Bkg") ||  ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm ../razorbits/GLF.root;    hadd -k  ../razorbits/GLF.root     ../razorbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm ../razorbits/MET.root; hadd -k  ../razorbits/MET.root   ../razorbits/MET*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm ../razorbits/SingleElectron.root; hadd -k  ../razorbits/SingleElectron.root   ../razorbits/SingleElectron*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then rm ../razorbits/JetHT.root; hadd -k  ../razorbits/JetHT.root   ../razorbits/JetHT*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "HTMHT") ]]; then rm ../razorbits/HTMHT.root; hadd -k  ../razorbits/HTMHT.root   ../razorbits/HTMHT*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm ../razorbits/SinglePhoton.root; hadd -k  ../razorbits/SinglePhoton.root   ../razorbits/SinglePhoton*_data/*.root; fi
