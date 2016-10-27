#!/bin/bash

analyzer='runMonojet_split'
dir='monojet'

python create.py -a $analyzer -t mc -d $dir -n 50000 -c DYJetsToLL_M_50_HT_100to200_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c DYJetsToLL_M_50_HT_200to400_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c DYJetsToLL_M_50_HT_400to600_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c DYJetsToLL_M_50_HT_600toInf_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c DYJetsToLL_M_50_HT_600toInf_13TeV_ext

python create.py -a $analyzer -t mc -d $dir -n 50000 -c GJets_HT_100To200_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c GJets_HT_200To400_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c GJets_HT_400To600_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c GJets_HT_40To100_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c GJets_HT_600ToInf_13TeV

python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT1000to1500_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT1000to1500_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT100to200_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT1500to2000_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT1500to2000_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT2000toInf_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT2000toInf_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT200to300_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT200to300_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT300to500_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT300to500_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT500to700_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT500to700_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT700to1000_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c QCD_HT700to1000_13TeV_ext

python create.py -a $analyzer -t mc -d $dir -n 50000 -c ST_t-channel_antitop_4f_inclusiveDecays_13TeV_powheg
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ST_t-channel_top_4f_inclusiveDecays_13TeV_powheg
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ST_tW_antitop_5f_inclusiveDecays_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ST_tW_top_5f_inclusiveDecays_13TeV

python create.py -a $analyzer -t mc -d $dir -n 50000 -c TTJets_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c TTJets_13TeV_amcatnloFXFX_pythia8
python create.py -a $analyzer -t mc -d $dir -n 50000 -c TTTo2L2Nu_13TeV_powheg
python create.py -a $analyzer -t mc -d $dir -n 50000 -c TTToSemiLeptonic_13TeV_powheg
python create.py -a $analyzer -t mc -d $dir -n 50000 -c TT_13TeV_powheg_ext3
python create.py -a $analyzer -t mc -d $dir -n 50000 -c TT_13TeV_powheg_ext4
python create.py -a $analyzer -t mc -d $dir -n 50000 -c TT_13TeV_powheg_herwigpp
python create.py -a $analyzer -t mc -d $dir -n 50000 -c TT_13TeV_powheg_pythia8_ext

python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_100To200_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_1200To2500_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_1200To2500_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_200To400_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_200To400_13TeV_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_2500ToInf_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_400To600_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_600To800_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_800To1200_13TeV
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WJetsToLNu_HT_800To1200_13TeV_ext

python create.py -a $analyzer -t mc -d $dir -n 50000 -c WWTo1L1Nu2Q_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WWTo4Q_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WWToLNuQQ_13TeV_powheg
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WWToLNuQQ_13TeV_powheg_ext1
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WZTo1L1Nu2Q_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WZTo1L3Nu_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WZTo2L2Q_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c WZTo3LNu_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZZTo2L2Nu_13TeV_powheg
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZZTo2L2Q_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZZTo2Q2Nu_13TeV_amcatnlo
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZZTo4L_13TeV_powheg
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZZTo4Q_13TeV_amcatnlo

python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_100To200_13TeV_madgraph_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_1200To2500_13TeV_madgraph
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_1200To2500_13TeV_madgraph_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_200To400_13TeV_madgraph_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_2500ToInf_13TeV_madgraph
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_400To600_13TeV_madgraph
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_400To600_13TeV_madgraph_ext
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_600To800_13TeV_madgraph
python create.py -a $analyzer -t mc -d $dir -n 50000 -c ZJetsToNuNu_HT_800To1200_13TeV_madgraph
