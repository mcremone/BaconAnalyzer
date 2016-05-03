#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../razorbits/QCD.root;  hadd  ../razorbits/QCD.root   ../razorbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    for x in `ls ../razorbits | grep Monotop | grep -v .root`; do
	rm ../razorbits/$x.root
	hadd ../razorbits/$x.root ../razorbits/$x/*.root
    done
fi

# if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then rm ../razorbits/DY.root;    hadd  ../razorbits/DY.root     ../razorbits/*DYJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm ../razorbits/DYHF.root;    hadd  ../razorbits/DYHF.root     ../razorbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm ../razorbits/DYLF.root;    hadd  ../razorbits/DYLF.root     ../razorbits/*DYJets*_HT*mcdypluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "DYNLO") ]]; then rm ../razorbits/DYNLO.root;  hadd  ../razorbits/DYNLO.root   ../razorbits/*DYJetsToLL_M-50_MINIAOD*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "Z") ]]; then rm ../razorbits/Z.root;    hadd  ../razorbits/Z.root     ../razorbits/*ZJetsToNuNu*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm ../razorbits/ZHF.root;    hadd  ../razorbits/ZHF.root     ../razorbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm ../razorbits/ZLF.root;    hadd  ../razorbits/ZLF.root     ../razorbits/*ZJets*_HT*mczpluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "ZNLO") ]]; then rm ../razorbits/ZNLO.root;    hadd  ../razorbits/ZNLO.root     ../razorbits/*DYJetsToNuNu*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then rm ../razorbits/W.root;    hadd  ../razorbits/W.root     ../razorbits/*WJets*_HT*mcwjets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm ../razorbits/WHF.root;    hadd  ../razorbits/WHF.root     ../razorbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm ../razorbits/WLF.root;    hadd  ../razorbits/WLF.root     ../razorbits/*WJets*_HT*mcwpluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "WNLO") ]]; then rm ../razorbits/WNLO.root;    hadd  ../razorbits/WNLO.root     ../razorbits/Spring15_a25ns_WJetsToLNu_amcatnlo_MINIAOD*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../razorbits/T.root;    hadd  ../razorbits/T.root     ../razorbits/*_ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TZ") ]]; then rm ../razorbits/TZ.root;   hadd  ../razorbits/TZ.root ../razorbits/*tZq*/*.root; fi
#if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../razorbits/TT.root;    hadd  ../razorbits/TT.root     ../razorbits/Spring15_a25ns_TTJets_madgraph_MINIAOD_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm ../razorbits/TT.root;    hadd  ../razorbits/TT.root     ../razorbits/TTJets_13TeV_amcatnloFXFX_pythia8_2_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTZ") ]]; then rm ../razorbits/TTZ.root;   hadd  ../razorbits/TTZ.root ../razorbits/*TTZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTG") ]]; then rm ../razorbits/TTG.root;   hadd  ../razorbits/TTG.root ../razorbits/*TTG*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TT1L") ]]; then rm ../razorbits/TT1L.root;   hadd  ../razorbits/TT1L.root    ../razorbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt1l/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TT2L") ]]; then rm ../razorbits/TT2L.root;   hadd  ../razorbits/TT2L.root    ../razorbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt2l/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TTHAD") ]]; then rm ../razorbits/TTHAD.root;   hadd  ../razorbits/TTHAD.root    ../razorbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctthad/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TTBST") ]]; then rm ../razorbits/TTBST.root;   hadd  ../razorbits/TTBST.root    ../razorbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttbst/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TTCOM") ]]; then rm ../razorbits/TTCOM.root;   hadd  ../razorbits/TTCOM.root    ../razorbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttcom/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../razorbits/WW.root;   hadd  ../razorbits/WW.root    ../razorbits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../razorbits/WZ.root;   hadd  ../razorbits/WZ.root    ../razorbits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../razorbits/ZZ.root;   hadd  ../razorbits/ZZ.root    ../razorbits/*ZZ*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "G") ]]; then rm ../razorbits/G.root;    hadd  ../razorbits/G.root     ../razorbits/*GJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm ../razorbits/GHF.root;    hadd  ../razorbits/GHF.root     ../razorbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm ../razorbits/GLF.root;    hadd  ../razorbits/GLF.root     ../razorbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm ../razorbits/MET.root; hadd  ../razorbits/MET.root   ../razorbits/MET_*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm ../razorbits/SingleElectron.root; hadd  ../razorbits/SingleElectron.root   ../razorbits/SingleElectron_*MINIAOD_data/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then rm ../razorbits/SingleMuon.root; hadd  ../razorbits/SingleMuon.root   ../razorbits/SingleMuon_*MINIAOD_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm ../razorbits/SinglePhoton.root; hadd  ../razorbits/SinglePhoton.root   ../razorbits/SinglePhoton_*_data/*.root; fi
