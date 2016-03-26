#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm ../MonoXbits/QCD.root;  hadd  ../MonoXbits/QCD.root   ../MonoXbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    for x in `ls ../MonoXbits | grep Monotop | grep -v .root`; do
	rm ../MonoXbits/$x.root
	hadd ../MonoXbits/$x.root ../MonoXbits/$x/*.root
    done
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then rm ../MonoXbits/DY.root;    hadd  ../MonoXbits/DY.root     ../MonoXbits/*DYJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm ../MonoXbits/DYHF.root;    hadd  ../MonoXbits/DYHF.root     ../MonoXbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm ../MonoXbits/DYLF.root;    hadd  ../MonoXbits/DYLF.root     ../MonoXbits/*DYJets*_HT*mcdypluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYNLO") ]]; then rm ../MonoXbits/DYNLO.root;  hadd  ../MonoXbits/DYNLO.root   ../MonoXbits/*DYJetsToLL_M-50_MINIAOD*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Z") ]]; then rm ../MonoXbits/Z.root;    hadd  ../MonoXbits/Z.root     ../MonoXbits/*ZJetsToNuNu*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm ../MonoXbits/ZHF.root;    hadd  ../MonoXbits/ZHF.root     ../MonoXbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm ../MonoXbits/ZLF.root;    hadd  ../MonoXbits/ZLF.root     ../MonoXbits/*ZJets*_HT*mczpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZNLO") ]]; then rm ../MonoXbits/ZNLO.root;    hadd  ../MonoXbits/ZNLO.root     ../MonoXbits/*DYJetsToNuNu*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then rm ../MonoXbits/W.root;    hadd  ../MonoXbits/W.root     ../MonoXbits/*WJets*_HT*mcwjets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm ../MonoXbits/WHF.root;    hadd  ../MonoXbits/WHF.root     ../MonoXbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm ../MonoXbits/WLF.root;    hadd  ../MonoXbits/WLF.root     ../MonoXbits/*WJets*_HT*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WNLO") ]]; then rm ../MonoXbits/WNLO.root;    hadd  ../MonoXbits/WNLO.root     ../MonoXbits/Spring15_a25ns_WJetsToLNu_amcatnlo_MINIAOD*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm ../MonoXbits/T.root;    hadd  ../MonoXbits/T.root     ../MonoXbits/*_ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT1L") ]]; then rm ../MonoXbits/TT1L.root;   hadd  ../MonoXbits/TT1L.root    ../MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt1l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT2L") ]]; then rm ../MonoXbits/TT2L.root;   hadd  ../MonoXbits/TT2L.root    ../MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctt2l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTHAD") ]]; then rm ../MonoXbits/TTHAD.root;   hadd  ../MonoXbits/TTHAD.root    ../MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mctthad/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTBST") ]]; then rm ../MonoXbits/TTBST.root;   hadd  ../MonoXbits/TTBST.root    ../MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttbst/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTCOM") ]]; then rm ../MonoXbits/TTCOM.root;   hadd  ../MonoXbits/TTCOM.root    ../MonoXbits/Spring15_a25ns_TTJets_madgraph_MINIAOD*mcttcom/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm ../MonoXbits/WW.root;   hadd  ../MonoXbits/WW.root    ../MonoXbits/*WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm ../MonoXbits/WZ.root;   hadd  ../MonoXbits/WZ.root    ../MonoXbits/*WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm ../MonoXbits/ZZ.root;   hadd  ../MonoXbits/ZZ.root    ../MonoXbits/*ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "G") ]]; then rm ../MonoXbits/G.root;    hadd  ../MonoXbits/G.root     ../MonoXbits/*GJets*_HT*jets/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm ../MonoXbits/GHF.root;    hadd  ../MonoXbits/GHF.root     ../MonoXbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm ../MonoXbits/GLF.root;    hadd  ../MonoXbits/GLF.root     ../MonoXbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm ../MonoXbits/MET.root; hadd  ../MonoXbits/MET.root   ../MonoXbits/MET_*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm ../MonoXbits/SingleElectron.root; hadd  ../MonoXbits/SingleElectron.root   ../MonoXbits/SingleElectron_*MINIAOD_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then rm ../MonoXbits/SingleMuon.root; hadd  ../MonoXbits/SingleMuon.root   ../MonoXbits/SingleMuon_*MINIAOD_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm ../MonoXbits/SinglePhoton.root; hadd  ../MonoXbits/SinglePhoton.root   ../MonoXbits/SinglePhoton_*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwig1L") ]]; then rm ../MonoXbits/TTherwig1L.root;   hadd  ../MonoXbits/TTherwig1L.root    ../MonoXbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mctt1l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwig2L") ]]; then rm ../MonoXbits/TTherwig2L.root;   hadd  ../MonoXbits/TTherwig2L.root    ../MonoXbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mctt2l/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigHAD") ]]; then rm ../MonoXbits/TTherwigHAD.root;   hadd  ../MonoXbits/TTherwigHAD.root    ../MonoXbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mctthad/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigBST") ]]; then rm ../MonoXbits/TTherwigBST.root;   hadd  ../MonoXbits/TTherwigBST.root    ../MonoXbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mcttbst/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigCOM") ]]; then rm ../MonoXbits/TTherwigCOM.root;   hadd  ../MonoXbits/TTherwigCOM.root    ../MonoXbits/Spring15_a25ns_TT_powheg_herwig_MINIAOD*mcttcom/*.root; fi

#if [[ ($sample = "All") || ($sample != "All" && $sample = "TTDM") ]]; then rm ../MonoXbits/TTDM.root;   hadd  ../MonoXbits/TTDM.root ../MonoXbits/*TTbarDM*/*.root; fi
