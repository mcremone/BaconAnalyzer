#!/bin/bash

sample=$1

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then rm /tmp/cmantill/QCD80.root;  hadd  /tmp/cmantill/QCD80.root   ../monoxbits/*QCD*mc/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
   for x in `ls ../monoxbits | grep Monotop | grep -v .root`; do
	rm /tmp/cmantill/$x.root
	hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
   done
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
    for x in `ls ../monoxbits | grep ZprimeToA0hToA0chichihbb_2HDM_MZp_ | grep -v .root`; do
        rm /tmp/cmantill/$x.root
        hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
    done
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTDM") ]]; then
    for x in `ls ../monoxbits | grep TTbarDMJets_pseudoscalar_Mchi_ | grep -v .root`; do
	rm /tmp/cmantill/$x.root
        hadd /tmp/cmantill/$x.root ../monoxbits/$x/*.root
    done
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then rm /tmp/cmantill/DYHF.root;    hadd  /tmp/cmantill/DYHF.root     ../monoxbits/*DYJets*_HT*mcdyplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then rm /tmp/cmantill/DYLF.root;    hadd  /tmp/cmantill/DYLF.root     ../monoxbits/*DYJets*_HT*mcdypluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then rm /tmp/cmantill/ZHF80.root;    hadd  /tmp/cmantill/ZHF80.root     ../monoxbits/*ZJets*_HT*mczplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then rm /tmp/cmantill/ZLF80.root;    hadd  /tmp/cmantill/ZLF80.root     ../monoxbits/*ZJets*_HT*mczpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then rm /tmp/cmantill/WHF.root;    hadd  /tmp/cmantill/WHF.root     ../monoxbits/*WJets*_HT*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then rm /tmp/cmantill/WLF.root;    hadd  /tmp/cmantill/WLF.root     ../monoxbits/*WJets*_HT*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHFinc") ]]; then rm /tmp/cmantill/WHFinc.root;    hadd  /tmp/cmantill/WHFinc.root     ../monoxbits/*WJets*mcwplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLFinc") ]]; then rm /tmp/cmantill/WLFinc.root;    hadd  /tmp/cmantill/WLFinc.root     ../monoxbits/*WJets*mcwpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then rm /tmp/cmantill/T.root;    hadd  /tmp/cmantill/T.root     ../monoxbits/ST_*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TZ") ]]; then rm /tmp/cmantill/TZ.root;   hadd  /tmp/cmantill/TZ.root ../monoxbits/tZq*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then rm /tmp/cmantill/TT.root;    hadd  /tmp/cmantill/TT.root     ../monoxbits/TTJets_13TeV_amcatnloFXFX_pythia8_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTFXFX") ]]; then rm /tmp/cmantill/TTFXFXtrig.root;    hadd  /tmp/cmantill/TTFXFXtrig.root     ../monoxbits/TTJets_13TeV_amcatnloFXFX_pythia8_trig_mctt/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTZ") ]]; then rm /tmp/cmantill/TTZ.root;   hadd  /tmp/cmantill/TTZ.root ../monoxbits/*ttZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTG") ]]; then rm /tmp/cmantill/TTG.root;   hadd  /tmp/cmantill/TTG.root ../monoxbits/*TTG*/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "THQ") ]]; then rm /tmp/cmantill/THQ.root;   hadd  /tmp/cmantill/THQ.root ../monoxbits/*THQ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then rm /tmp/cmantill/WW.root;   hadd  /tmp/cmantill/WW.root    ../monoxbits/WW*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then rm /tmp/cmantill/WZ.root;   hadd  /tmp/cmantill/WZ.root    ../monoxbits/WZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then rm /tmp/cmantill/ZZ.root;   hadd  /tmp/cmantill/ZZ.root    ../monoxbits/ZZ*/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then rm /tmp/cmantill/GHF.root;    hadd  /tmp/cmantill/GHF.root     ../monoxbits/*GJets*_HT*mcgplushf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then rm /tmp/cmantill/GLF.root;    hadd  /tmp/cmantill/GLF.root     ../monoxbits/*GJets*_HT*mcgpluslf/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then rm /tmp/cmantill/METtrig.root; hadd  /tmp/cmantill/METtrig.root   ../monoxbits/MET*trig_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then rm /tmp/cmantill/SingleElectrontrig.root; hadd  /tmp/cmantill/SingleElectrontrig.root   ../monoxbits/SingleElectron*trig_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then rm /tmp/cmantill/SinglePhotontrig.root; hadd  /tmp/cmantill/SinglePhotontrig.root   ../monoxbits/SinglePhoton*trig_data/*.root; fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then rm /tmp/cmantill/SingleMuon.root; hadd  /tmp/cmantill/SingleMuon.root   ../monoxbits/SingleMuon*_data/*.root; fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZH") ]]; then rm /tmp/cmantill/ZH_amcatnlo.root; hadd  /tmp/cmantill/ZH_amcatnlo.root   ../monoxbits/ZH_HToBB_ZToNuNu_M125_13TeV_amcatnloFXFX_madspin_pythia8_mc/*.root; fi
