#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm /tmp/cmantill/QCD.root;  hadd  /tmp/cmantill/QCD.root   ../monoxbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
   for x in `ls ../monoxbits | grep Monotop | grep -v .root`; do
 	rm /tmp/cmantill/$x.root
 	hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
    done
fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
#     for x in `ls ../monoxbits | grep ZprimeToA0hToA0chichihbb_2HDM_MZp_ | grep -v .root`; do
#         rm /tmp/cmantill/$x.root
#         hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
#     done
# fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ZtoNuNu") ]]; then rm /tmp/cmantill/ZtoNuNu.root;    hadd  /tmp/cmantill/ZtoNuNu.root     ../monoxbits/*DYJets*_HT*mcdyplushf/*.root ../monoxbits/*DYJets*_HT*mcdypluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZJets") ]]; then rm /tmp/cmantill/ZJets.root;    hadd  /tmp/cmantill/ZJets.root     ../monoxbits/*ZJets*_HT*mczplushf/*.root ../monoxbits/*ZJets*_HT*mczpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WJets") ]]; then rm /tmp/cmantill/WJets.root;    hadd  /tmp/cmantill/WJets.root     ../monoxbits/*WJets*_HT*mcwplushf/*.root ../monoxbits/*WJets*_HT*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm /tmp/cmantill/SingleTop.root;    hadd  /tmp/cmantill/SingleTop.root     ../monoxbits/ST_*/*.root ../monoxbits/tZq*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm /tmp/cmantill/TTbar_Powheg;    hadd  /tmp/cmantill/TTbar_Powheg.root     ../monoxbits/TT_13TeV_powheg_pythia8_ext_trig_mctt/*.root ../monoxbits/*ttZ*/*.root ../monoxbits/*TTG*/*.root;fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Diboson") ]]; then rm /tmp/cmantill/Diboson.root;   hadd  /tmp/cmantill/Diboson.root    ../monoxbits/WW*/*.root ../monoxbits/WZ*/*.root ../monoxbits/ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GJets") ]]; then rm /tmp/cmantill/GJets.root;    hadd  /tmp/cmantill/GJets.root     ../monoxbits/*GJets*_HT*mcgplushf/*.root ../monoxbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm /tmp/cmantill/MET.root; hadd  /tmp/cmantill/MET.root  ../monoxbits/METRun2016B_PromptReco_v1_trig_data/*.root ../monoxbits/METRun2016B_PromptReco_v2_trig_July9_data/*.root ../monoxbits/METRun2016C_PromptReco_v2_trig_data/*.root ../monoxbits/METRun2016D_PromptReco_v2_trig_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm /tmp/cmantill/SingleElectron.root; hadd  /tmp/cmantill/SingleElectron.root  ../monoxbits/SingleElectronRun2016B_PromptReco_v1_trig_data/*.root ../monoxbits/SingleElectronRun2016B_PromptReco_v2_trig_July9_data/*.root ../monoxbits/SingleElectronRun2016C_PromptReco_v2_trig_data/*.root ../monoxbits/SingleElectronRun2016D_PromptReco_v2_trig_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm /tmp/cmantill/SinglePhoton.root; hadd  /tmp/cmantill/SinglePhoton.root  ../monoxbits/SinglePhotonRun2016B_PromptReco_v1_trig_data/*.root ../monoxbits/SinglePhotonRun2016B_PromptReco_v2_trig_July9_data/*.root ../monoxbits/SinglePhotonRun2016C_PromptReco_v2_trig_data/*.root ../monoxbits/SinglePhotonRun2016D_PromptReco_v2_trig_data/*.root; fi