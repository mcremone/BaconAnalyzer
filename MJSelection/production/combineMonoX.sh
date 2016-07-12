#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm /tmp/cmantill/QCD80_2.root;  hadd  /tmp/cmantill/QCD80_2.root   ../monoxbits/*QCD*mc/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
#    for x in `ls ../monoxbits | grep Monotop | grep -v .root`; do
# 	rm /tmp/cmantill/$x.root
# 	hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
#    done
# fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
#     for x in `ls ../monoxbits | grep ZprimeToA0hToA0chichihbb_2HDM_MZp_ | grep -v .root`; do
#         rm /tmp/cmantill/$x.root
#         hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
#     done
# fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "TTDM") ]]; then
#     for x in `ls ../monoxbits | grep TTbarDMJets_pseudoscalar_Mchi_ | grep -v .root`; do
# 	rm /tmp/cmantill/$x.root
#         hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
#     done
# fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm /tmp/cmantill/DYHF80_2.root;    hadd  /tmp/cmantill/DYHF80_2.root     ../monoxbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm /tmp/cmantill/DYLF80_2.root;    hadd  /tmp/cmantill/DYLF80_2.root     ../monoxbits/*DYJets*_HT*mcdypluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm /tmp/cmantill/ZHF80_2.root;    hadd  /tmp/cmantill/ZHF80_2.root     ../monoxbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm /tmp/cmantill/ZLF80_2.root;    hadd  /tmp/cmantill/ZLF80_2.root     ../monoxbits/*ZJets*_HT*mczpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm /tmp/cmantill/WHF_2.root;    hadd  /tmp/cmantill/WHF.root     ../monoxbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm /tmp/cmantill/WLF_2.root;    hadd  /tmp/cmantill/WLF.root     ../monoxbits/*WJets*_HT*mcwpluslf/*.root; fi
#if [[ ($sample = "All") || ($sample != "All" && $sample = "WHFinc") ]]; then rm /tmp/cmantill/WHFinc.root;    hadd  /tmp/cmantill/WHFinc.root     ../monoxbits/*WJets*mcwplushf/*.root; fi
#if [[ ($sample = "All") || ($sample != "All" && $sample = "WLFinc") ]]; then rm /tmp/cmantill/WLFinc.root;    hadd  /tmp/cmantill/WLFinc.root     ../monoxbits/*WJets*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm /tmp/cmantill/T80_2.root;    hadd  /tmp/cmantill/T80_2.root     ../monoxbits/ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TZ") ]]; then rm /tmp/cmantill/TZ80_2.root;   hadd  /tmp/cmantill/TZ80_2.root ../monoxbits/tZq*/*.root; fi
#if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm /tmp/cmantill/TT80_2.root;    hadd  /tmp/cmantill/TT80_2.root     ../monoxbits/TTJets_13TeV_amcatnloFXFX_pythia8_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTFXFX") ]]; then rm /tmp/cmantill/TTFXFXtrig80_2.root;    hadd  /tmp/cmantill/TTFXFXtrig80_2.root     ../monoxbits/TTJets_13TeV_amcatnloFXFX_pythia8_trig_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTZ") ]]; then rm /tmp/cmantill/TTZ80_2.root;   hadd  /tmp/cmantill/TTZ80_2.root ../monoxbits/*ttZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTG") ]]; then rm /tmp/cmantill/TTG80_2.root;   hadd  /tmp/cmantill/TTG80_2.root ../monoxbits/*TTG*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "THQ") ]]; then rm /tmp/cmantill/THQ.root;   hadd  /tmp/cmantill/THQ.root ../monoxbits/*THQ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm /tmp/cmantill/WW80_2.root;   hadd  /tmp/cmantill/WW80_2.root    ../monoxbits/WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm /tmp/cmantill/WZ80_2.root;   hadd  /tmp/cmantill/WZ80_2.root    ../monoxbits/WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm /tmp/cmantill/ZZ80_2.root;   hadd  /tmp/cmantill/ZZ80_2.root    ../monoxbits/ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm /tmp/cmantill/GHF80_2.root;    hadd  /tmp/cmantill/GHF80_2.root     ../monoxbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm /tmp/cmantill/GLF80_2.root;    hadd  /tmp/cmantill/GLF80_2.root     ../monoxbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm /tmp/cmantill/METtrig4.root; hadd  /tmp/cmantill/METtrig4.root   ../monoxbits/MET*trig_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm /tmp/cmantill/SingleElectrontrig4.root; hadd  /tmp/cmantill/SingleElectrontrig4.root   ../monoxbits/SingleElectron*trig_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm /tmp/cmantill/SinglePhotontrig4.root; hadd  /tmp/cmantill/SinglePhotontrig4.root   ../monoxbits/SinglePhoton*trig_data/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then rm /tmp/cmantill/SingleMuon.root; hadd  /tmp/cmantill/SingleMuon.root   ../monoxbits/SingleMuon*_data/*.root; fi
#if [[ ($sample = "All") || ($sample != "All" && $sample = "ZH") ]]; then rm /tmp/cmantill/ZH_amcatnlo.root; hadd  /tmp/cmantill/ZH_amcatnlo.root   ../monoxbits/ZH_HToBB_ZToNuNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_mc/*.root; fi
