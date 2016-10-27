#!/bin/bash
# Usage: source submit.sh All to submit
# source submit.sh All --dryRun to test

analyzer='runMonojet_split'
dir='monojet'
sample=$1
dryRun=$2

if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then 
    python create.py -a $analyzer -t mcdyplushf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_100to200_13TeV_ext
    python create.py -a $analyzer -t mcdyplushf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_200to400_13TeV_ext
    python create.py -a $analyzer -t mcdyplushf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_400to600_13TeV_ext
    python create.py -a $analyzer -t mcdyplushf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_600toInf_13TeV
    python create.py -a $analyzer -t mcdyplushf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_600toInf_13TeV_ext
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then 
    python create.py -a $analyzer -t mcdypluslf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_100to200_13TeV_ext
    python create.py -a $analyzer -t mcdypluslf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_200to400_13TeV_ext
    python create.py -a $analyzer -t mcdypluslf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_400to600_13TeV_ext
    python create.py -a $analyzer -t mcdypluslf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_600toInf_13TeV
    python create.py -a $analyzer -t mcdypluslf -d $dir -n 50000 $dryRun -c DYJetsToLL_M_50_HT_600toInf_13TeV_ext
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then 
    python create.py -a $analyzer -t mcgplushf -d $dir -n 50000 $dryRun -c GJets_HT_100To200_13TeV
    python create.py -a $analyzer -t mcgplushf -d $dir -n 50000 $dryRun -c GJets_HT_200To400_13TeV
    python create.py -a $analyzer -t mcgplushf -d $dir -n 50000 $dryRun -c GJets_HT_400To600_13TeV
    python create.py -a $analyzer -t mcgplushf -d $dir -n 50000 $dryRun -c GJets_HT_40To100_13TeV
    python create.py -a $analyzer -t mcgplushf -d $dir -n 50000 $dryRun -c GJets_HT_600ToInf_13TeV
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then 
    python create.py -a $analyzer -t mcgpluslf -d $dir -n 50000 $dryRun -c GJets_HT_100To200_13TeV
    python create.py -a $analyzer -t mcgpluslf -d $dir -n 50000 $dryRun -c GJets_HT_200To400_13TeV
    python create.py -a $analyzer -t mcgpluslf -d $dir -n 50000 $dryRun -c GJets_HT_400To600_13TeV
    python create.py -a $analyzer -t mcgpluslf -d $dir -n 50000 $dryRun -c GJets_HT_40To100_13TeV
    python create.py -a $analyzer -t mcgpluslf -d $dir -n 50000 $dryRun -c GJets_HT_600ToInf_13TeV
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then 
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT1000to1500_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT1000to1500_13TeV_ext
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT100to200_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT1500to2000_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT1500to2000_13TeV_ext
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT2000toInf_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT2000toInf_13TeV_ext
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT200to300_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT200to300_13TeV_ext
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT300to500_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT300to500_13TeV_ext
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT500to700_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT500to700_13TeV_ext
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT700to1000_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c QCD_HT700to1000_13TeV_ext
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ST") ]]; then 
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ST_t-channel_antitop_4f_inclusiveDecays_13TeV_powheg
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ST_t-channel_top_4f_inclusiveDecays_13TeV_powheg
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ST_tW_antitop_5f_inclusiveDecays_13TeV
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ST_tW_top_5f_inclusiveDecays_13TeV
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ST") ]]; then 
    python create.py -a $analyzer -t mctt -d $dir -n 50000 $dryRun -c TT_13TeV_powheg_ext3
    python create.py -a $analyzer -t mctt -d $dir -n 50000 $dryRun -c TT_13TeV_powheg_ext4
    python create.py -a $analyzer -t mctt -d $dir -n 50000 $dryRun -c TT_13TeV_powheg_pythia8_ext
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then 
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_100To200_13TeV_ext
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_1200To2500_13TeV
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_1200To2500_13TeV_ext
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_200To400_13TeV
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_200To400_13TeV_ext
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_2500ToInf_13TeV
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_400To600_13TeV
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_600To800_13TeV
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_800To1200_13TeV
    python create.py -a $analyzer -t mcwplushf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_800To1200_13TeV_ext
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then 
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_100To200_13TeV_ext
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_1200To2500_13TeV
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_1200To2500_13TeV_ext
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_200To400_13TeV
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_200To400_13TeV_ext
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_2500ToInf_13TeV
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_400To600_13TeV
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_600To800_13TeV
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_800To1200_13TeV
    python create.py -a $analyzer -t mcwpluslf -d $dir -n 50000 $dryRun -c WJetsToLNu_HT_800To1200_13TeV_ext
fi

if [[ ($sample = "All") || ($sample = "Diboson") ]]; then
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WWTo1L1Nu2Q_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WWTo4Q_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WWToLNuQQ_13TeV_powheg
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WWToLNuQQ_13TeV_powheg_ext1
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WZTo1L1Nu2Q_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WZTo1L3Nu_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WZTo2L2Q_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c WZTo3LNu_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ZZTo2L2Nu_13TeV_powheg
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ZZTo2L2Q_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ZZTo2Q2Nu_13TeV_amcatnlo
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ZZTo4L_13TeV_powheg
    python create.py -a $analyzer -t mc -d $dir -n 50000 $dryRun -c ZZTo4Q_13TeV_amcatnlo
fi

if [[ ($sample = "All") || ($sample = "ZHF") ]]; then
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_100To200_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_1200To2500_13TeV_madgraph
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_1200To2500_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_200To400_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_2500ToInf_13TeV_madgraph
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_400To600_13TeV_madgraph
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_400To600_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_600To800_13TeV_madgraph
    python create.py -a $analyzer -t mczplushf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_800To1200_13TeV_madgraph
fi

if [[ ($sample = "All") || ($sample = "ZLF") ]]; then
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_100To200_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_1200To2500_13TeV_madgraph
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_1200To2500_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_200To400_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_2500ToInf_13TeV_madgraph
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_400To600_13TeV_madgraph
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_400To600_13TeV_madgraph_ext
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_600To800_13TeV_madgraph
    python create.py -a $analyzer -t mczpluslf -d $dir -n 50000 $dryRun -c ZJetsToNuNu_HT_800To1200_13TeV_madgraph
fi
