#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../monoxbits/QCD.root;  hadd  ../monoxbits/QCD.root   ../monoxbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    for x in `ls ../monoxbits | grep Monotop | grep -v .root`; do
	rm ../monoxbits/$x.root
	hadd ../monoxbits/$x.root ../monoxbits/$x/*.root
    done
fi

# if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then rm ../monoxbits/DY.root;    hadd  ../monoxbits/DY.root     ../monoxbits/*DYJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm ../monoxbits/DYHF.root;    hadd  ../monoxbits/DYHF.root     ../monoxbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm ../monoxbits/DYLF.root;    hadd  ../monoxbits/DYLF.root     ../monoxbits/*DYJets*_HT*mcdypluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "DYNLO") ]]; then rm ../monoxbits/DYNLO.root;  hadd  ../monoxbits/DYNLO.root   ../monoxbits/*DYJetsToLL_M-50_MINIAOD*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "Z") ]]; then rm ../monoxbits/Z.root;    hadd  ../monoxbits/Z.root     ../monoxbits/*ZJetsToNuNu*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm ../monoxbits/ZHF.root;    hadd  ../monoxbits/ZHF.root     ../monoxbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm ../monoxbits/ZLF.root;    hadd  ../monoxbits/ZLF.root     ../monoxbits/*ZJets*_HT*mczpluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "ZNLO") ]]; then rm ../monoxbits/ZNLO.root;    hadd  ../monoxbits/ZNLO.root     ../monoxbits/*DYJetsToNuNu*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then rm ../monoxbits/W.root;    hadd  ../monoxbits/W.root     ../monoxbits/*WJets*_HT*mcwjets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm ../monoxbits/WHF.root;    hadd  ../monoxbits/WHF.root     ../monoxbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm ../monoxbits/WLF.root;    hadd  ../monoxbits/WLF.root     ../monoxbits/*WJets*_HT*mcwpluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "WNLO") ]]; then rm ../monoxbits/WNLO.root;    hadd  ../monoxbits/WNLO.root     ../monoxbits/Spring15_a25ns_WJetsToLNu_amcatnlo_MINIAOD*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../monoxbits/T.root;    hadd  ../monoxbits/T.root     ../monoxbits/*_ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TZ") ]]; then rm ../monoxbits/TZ.root;   hadd  ../monoxbits/TZ.root ../monoxbits/*tZq*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../monoxbits/TT.root;    hadd  ../monoxbits/TT.root     ../monoxbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTZ") ]]; then rm ../monoxbits/TTZ.root;   hadd  ../monoxbits/TTZ.root ../monoxbits/*TTZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTG") ]]; then rm ../monoxbits/TTG.root;   hadd  ../monoxbits/TTG.root ../monoxbits/*TTG*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TT1L") ]]; then rm ../monoxbits/TT1L.root;   hadd  ../monoxbits/TT1L.root    ../monoxbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt1l/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TT2L") ]]; then rm ../monoxbits/TT2L.root;   hadd  ../monoxbits/TT2L.root    ../monoxbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt2l/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TTHAD") ]]; then rm ../monoxbits/TTHAD.root;   hadd  ../monoxbits/TTHAD.root    ../monoxbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctthad/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TTBST") ]]; then rm ../monoxbits/TTBST.root;   hadd  ../monoxbits/TTBST.root    ../monoxbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttbst/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TTCOM") ]]; then rm ../monoxbits/TTCOM.root;   hadd  ../monoxbits/TTCOM.root    ../monoxbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttcom/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../monoxbits/WW.root;   hadd  ../monoxbits/WW.root    ../monoxbits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../monoxbits/WZ.root;   hadd  ../monoxbits/WZ.root    ../monoxbits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../monoxbits/ZZ.root;   hadd  ../monoxbits/ZZ.root    ../monoxbits/*ZZ*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "G") ]]; then rm ../monoxbits/G.root;    hadd  ../monoxbits/G.root     ../monoxbits/*GJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm ../monoxbits/GHF.root;    hadd  ../monoxbits/GHF.root     ../monoxbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm ../monoxbits/GLF.root;    hadd  ../monoxbits/GLF.root     ../monoxbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm ../monoxbits/MET.root; hadd  ../monoxbits/MET.root   ../monoxbits/MET_*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm ../monoxbits/SingleElectron.root; hadd  ../monoxbits/SingleElectron.root   ../monoxbits/SingleElectron_*MINIAOD_data/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then rm ../monoxbits/SingleMuon.root; hadd  ../monoxbits/SingleMuon.root   ../monoxbits/SingleMuon_*MINIAOD_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm ../monoxbits/SinglePhoton.root; hadd  ../monoxbits/SinglePhoton.root   ../monoxbits/SinglePhoton_*_data/*.root; fi
