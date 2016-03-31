#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../baconbits/QCD.root;  hadd  ../baconbits/QCD.root   ../baconbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    for x in `ls ../baconbits | grep Monotop | grep -v .root`; do
	rm ../baconbits/$x.root
	hadd ../baconbits/$x.root ../baconbits/$x/*.root
    done
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then rm ../baconbits/DY.root;    hadd  ../baconbits/DY.root     ../baconbits/*DYJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm ../baconbits/DYHF.root;    hadd  ../baconbits/DYHF.root     ../baconbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm ../baconbits/DYLF.root;    hadd  ../baconbits/DYLF.root     ../baconbits/*DYJets*_HT*mcdypluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "DYNLO") ]]; then rm ../baconbits/DYNLO.root;  hadd  ../baconbits/DYNLO.root   ../baconbits/*DYJetsToLL_M-50_MINIAOD*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Z") ]]; then rm ../baconbits/Z.root;    hadd  ../baconbits/Z.root     ../baconbits/*ZJetsToNuNu*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm ../baconbits/ZHF.root;    hadd  ../baconbits/ZHF.root     ../baconbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm ../baconbits/ZLF.root;    hadd  ../baconbits/ZLF.root     ../baconbits/*ZJets*_HT*mczpluslf/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "ZNLO") ]]; then rm ../baconbits/ZNLO.root;    hadd  ../baconbits/ZNLO.root     ../baconbits/*DYJetsToNuNu*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then rm ../baconbits/W.root;    hadd  ../baconbits/W.root     ../baconbits/*WJets*_HT*mcwjets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm ../baconbits/WHF.root;    hadd  ../baconbits/WHF.root     ../baconbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm ../baconbits/WLF.root;    hadd  ../baconbits/WLF.root     ../baconbits/*WJets*_HT*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WNLO") ]]; then rm ../baconbits/WNLO.root;    hadd  ../baconbits/WNLO.root     ../baconbits/Spring15_a25ns_WJetsToLNu_amcatnlo_MINIAOD*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../baconbits/T.root;    hadd  ../baconbits/T.root     ../baconbits/*_ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT1L") ]]; then rm ../baconbits/TT1L.root;   hadd  ../baconbits/TT1L.root    ../baconbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt1l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT2L") ]]; then rm ../baconbits/TT2L.root;   hadd  ../baconbits/TT2L.root    ../baconbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt2l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTHAD") ]]; then rm ../baconbits/TTHAD.root;   hadd  ../baconbits/TTHAD.root    ../baconbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctthad/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTBST") ]]; then rm ../baconbits/TTBST.root;   hadd  ../baconbits/TTBST.root    ../baconbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttbst/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTCOM") ]]; then rm ../baconbits/TTCOM.root;   hadd  ../baconbits/TTCOM.root    ../baconbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttcom/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../baconbits/WW.root;   hadd  ../baconbits/WW.root    ../baconbits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../baconbits/WZ.root;   hadd  ../baconbits/WZ.root    ../baconbits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../baconbits/ZZ.root;   hadd  ../baconbits/ZZ.root    ../baconbits/*ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "G") ]]; then rm ../baconbits/G.root;    hadd  ../baconbits/G.root     ../baconbits/*GJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm ../baconbits/GHF.root;    hadd  ../baconbits/GHF.root     ../baconbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm ../baconbits/GLF.root;    hadd  ../baconbits/GLF.root     ../baconbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm ../baconbits/MET.root; hadd  ../baconbits/MET.root   ../baconbits/MET_*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm ../baconbits/SingleElectron.root; hadd  ../baconbits/SingleElectron.root   ../baconbits/SingleElectron_*MINIAOD_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then rm ../baconbits/SingleMuon.root; hadd  ../baconbits/SingleMuon.root   ../baconbits/SingleMuon_*MINIAOD_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm ../baconbits/SinglePhoton.root; hadd  ../baconbits/SinglePhoton.root   ../baconbits/SinglePhoton_*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwig1L") ]]; then rm ../baconbits/TTherwig1L.root;   hadd  ../baconbits/TTherwig1L.root    ../baconbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mctt1l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwig2L") ]]; then rm ../baconbits/TTherwig2L.root;   hadd  ../baconbits/TTherwig2L.root    ../baconbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mctt2l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigHAD") ]]; then rm ../baconbits/TTherwigHAD.root;   hadd  ../baconbits/TTherwigHAD.root    ../baconbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mctthad/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigBST") ]]; then rm ../baconbits/TTherwigBST.root;   hadd  ../baconbits/TTherwigBST.root    ../baconbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mcttbst/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigCOM") ]]; then rm ../baconbits/TTherwigCOM.root;   hadd  ../baconbits/TTherwigCOM.root    ../baconbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mcttcom/*.root; fi

#if [[ ($sample = "All") || ($sample != "All" && $sample = "TTDM") ]]; then rm ../baconbits/TTDM.root;   hadd  ../baconbits/TTDM.root ../baconbits/*TTbarDM*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTZ") ]]; then rm ../baconbits/TTZ.root;   hadd  ../baconbits/TTZ.root ../baconbits/*TTZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTG") ]]; then rm ../baconbits/TTG.root;   hadd  ../baconbits/TTG.root ../baconbits/*TTG*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TZ") ]]; then rm ../baconbits/TZ.root;   hadd  ../baconbits/TZ.root ../baconbits/*tZq*/*.root; fi