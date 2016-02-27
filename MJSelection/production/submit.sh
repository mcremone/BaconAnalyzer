#!/bin/bash   

sample=$1
option1=$2
option2=$3
eos="/store/cmst3/group/monojet/production/07/"
if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then 
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT100to200_MINIAOD                27500000       $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT200to300_MINIAOD                 1735000       $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT300to500_MINIAOD                  367000       $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT500to700_MINIAOD                   29370       $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT700to1000_MINIAOD                   6524       $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT1000to1500_MINIAOD                  1064       $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT1500to2000_MINIAOD                 121.5       $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_QCD_HT2000toInf_MINIAOD                  25.42       $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then 
    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-100To200_MINIAOD      1343    $option1 $option2
    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-200To400_MINIAOD      359.6    $option1 $option2
    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-400To600_MINIAOD      48.85    $option1 $option2
    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-600ToInf_MINIAOD      18.91    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-600To800_MINIAOD_v2      15.74    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-800To1200_MINIAOD     6.470    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-1200To2500_MINIAOD    1.636    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-2500ToInf_MINIAOD_v2     0.03799  $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then 
    ./sub.sh mcwplushf $eos Spring15_a25ns_WJetsToLNu_HT-100To200_MINIAOD      1343    $option1 $option2
    ./sub.sh mcwplushf $eos Spring15_a25ns_WJetsToLNu_HT-200To400_MINIAOD      359.6    $option1 $option2
    ./sub.sh mcwplushf $eos Spring15_a25ns_WJetsToLNu_HT-400To600_MINIAOD      48.85    $option1 $option2
    ./sub.sh mcwplushf $eos Spring15_a25ns_WJetsToLNu_HT-600ToInf_MINIAOD      18.91    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-600To800_MINIAOD_v2      15.74    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-800To1200_MINIAOD     6.470    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-1200To2500_MINIAOD    1.636    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-2500ToInf_MINIAOD_v2     0.03799  $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then 
    ./sub.sh mcwpluslf $eos Spring15_a25ns_WJetsToLNu_HT-100To200_MINIAOD      1343    $option1 $option2
    ./sub.sh mcwpluslf $eos Spring15_a25ns_WJetsToLNu_HT-200To400_MINIAOD      359.6    $option1 $option2
    ./sub.sh mcwpluslf $eos Spring15_a25ns_WJetsToLNu_HT-400To600_MINIAOD      48.85    $option1 $option2
    ./sub.sh mcwpluslf $eos Spring15_a25ns_WJetsToLNu_HT-600ToInf_MINIAOD      18.91    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-600To800_MINIAOD_v2      15.74    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-800To1200_MINIAOD     6.470    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-1200To2500_MINIAOD    1.636    $option1 $option2
#    ./sub.sh mcwjets $eos Spring15_a25ns_WJetsToLNu_HT-2500ToInf_MINIAOD_v2     0.03799  $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then 
    ./sub.sh mcdyjets $eos Spring15_a25ns_DYJetsToLL_M-50_HT-100to200_MINIAOD 148.0  $option1 $option2 
    ./sub.sh mcdyjets $eos Spring15_a25ns_DYJetsToLL_M-50_HT-200to400_MINIAOD 40.94  $option1 $option2 
    ./sub.sh mcdyjets $eos Spring15_a25ns_DYJetsToLL_M-50_HT-400to600_MINIAOD 5.497  $option1 $option2 
    ./sub.sh mcdyjets $eos Spring15_a25ns_DYJetsToLL_M-50_HT-600toInf_MINIAOD 2.193  $option1 $option2 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then 
    ./sub.sh mcdyplushf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-100to200_MINIAOD 148.0  $option1 $option2 
    ./sub.sh mcdyplushf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-200to400_MINIAOD 40.94  $option1 $option2 
    ./sub.sh mcdyplushf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-400to600_MINIAOD 5.497  $option1 $option2 
    ./sub.sh mcdyplushf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-600toInf_MINIAOD 2.193  $option1 $option2 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then 
    ./sub.sh mcdypluslf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-100to200_MINIAOD 148.0  $option1 $option2 
    ./sub.sh mcdypluslf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-200to400_MINIAOD 40.94  $option1 $option2 
    ./sub.sh mcdypluslf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-400to600_MINIAOD 5.497  $option1 $option2 
    ./sub.sh mcdypluslf $eos Spring15_a25ns_DYJetsToLL_M-50_HT-600toInf_MINIAOD 2.193  $option1 $option2 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Z") ]]; then
    ./sub.sh mczjets $eos Spring15_a25ns_ZJetsToNuNu_HT-100To200_MINIAOD    280.5       $option1 $option2
    ./sub.sh mczjets $eos Spring15_a25ns_ZJetsToNuNu_HT-200To400_MINIAOD     77.7       $option1 $option2
    ./sub.sh mczjets $eos Spring15_a25ns_ZJetsToNuNu_HT-400To600_MINIAOD     10.71      $option1 $option2
    ./sub.sh mczjets $eos Spring15_a25ns_ZJetsToNuNu_HT-600ToInf_MINIAOD   4.098     $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then
    ./sub.sh mczplushf $eos Spring15_a25ns_ZJetsToNuNu_HT-100To200_MINIAOD    280.5       $option1 $option2
    ./sub.sh mczplushf $eos Spring15_a25ns_ZJetsToNuNu_HT-200To400_MINIAOD     77.7       $option1 $option2
    ./sub.sh mczplushf $eos Spring15_a25ns_ZJetsToNuNu_HT-400To600_MINIAOD     10.71      $option1 $option2
    ./sub.sh mczplushf $eos Spring15_a25ns_ZJetsToNuNu_HT-600ToInf_MINIAOD   4.098     $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then
    ./sub.sh mczpluslf $eos Spring15_a25ns_ZJetsToNuNu_HT-100To200_MINIAOD    280.5       $option1 $option2
    ./sub.sh mczpluslf $eos Spring15_a25ns_ZJetsToNuNu_HT-200To400_MINIAOD     77.7       $option1 $option2
    ./sub.sh mczpluslf $eos Spring15_a25ns_ZJetsToNuNu_HT-400To600_MINIAOD     10.71      $option1 $option2
    ./sub.sh mczpluslf $eos Spring15_a25ns_ZJetsToNuNu_HT-600ToInf_MINIAOD   4.098     $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then 
    ./sub.sh mc $eos Spring15_a25ns_ST_t-channel_antitop_4f_leptonDecays_MINIAOD 44.0802      $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_ST_t-channel_top_4f_leptonDecays_MINIAOD     26.2343      $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_ST_tW_antitop_5f_inclusiveDecays_MINIAOD 35.6 $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_ST_tW_top_5f_inclusiveDecays_MINIAOD     35.6 $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT1L") ]]; then
    ./sub.sh mctt1l $eos Spring15_a25ns_TTJets_madgraph_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT2L") ]]; then
    ./sub.sh mctt2l $eos Spring15_a25ns_TTJets_madgraph_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTHAD") ]]; then
    ./sub.sh mctthad $eos Spring15_a25ns_TTJets_madgraph_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTBST") ]]; then
    ./sub.sh mcbst $eos Spring15_a25ns_TTJets_madgraph_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTCOM") ]]; then
    ./sub.sh mccom $eos Spring15_a25ns_TTJets_madgraph_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then
    ./sub.sh mc $eos Spring15_a25ns_WW_MINIAOD                              118.7        $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then
    ./sub.sh mc $eos Spring15_a25ns_WZ_MINIAOD                               47.2        $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then
    ./sub.sh mc $eos Spring15_a25ns_ZZ_MINIAOD                               31.8        $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then 
    ./sub.sh data $eos MET_Run2015D_PrReco_05Oct_MINIAOD_v3                  1        $option1 $option2
    ./sub.sh data $eos MET_Run2015D_PrReco_v4_MINIAOD_v3                  1        $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "G") ]]; then 
    ./sub.sh mcgjets $eos Spring15_a25ns_GJets_HT_100To200_MINIAOD                 9235       $option1 $option2
    ./sub.sh mcgjets $eos Spring15_a25ns_GJets_HT_200To400_MINIAOD                 2298       $option1 $option2
    ./sub.sh mcgjets $eos Spring15_a25ns_GJets_HT_400To600_MINIAOD                 277.6      $option1 $option2
    ./sub.sh mcgjets $eos Spring15_a25ns_GJets_HT_600ToInf_MINIAOD                 93.47      $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then 
    ./sub.sh mcgplushf $eos Spring15_a25ns_GJets_HT_100To200_MINIAOD                 9235       $option1 $option2
    ./sub.sh mcgplushf $eos Spring15_a25ns_GJets_HT_200To400_MINIAOD                 2298       $option1 $option2
    ./sub.sh mcgplushf $eos Spring15_a25ns_GJets_HT_400To600_MINIAOD                 277.6      $option1 $option2
    ./sub.sh mcgplushf $eos Spring15_a25ns_GJets_HT_600ToInf_MINIAOD                 93.47      $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then 
    ./sub.sh mcgpluslf $eos Spring15_a25ns_GJets_HT_100To200_MINIAOD                 9235       $option1 $option2
    ./sub.sh mcgpluslf $eos Spring15_a25ns_GJets_HT_200To400_MINIAOD                 2298       $option1 $option2
    ./sub.sh mcgpluslf $eos Spring15_a25ns_GJets_HT_400To600_MINIAOD                 277.6      $option1 $option2
    ./sub.sh mcgpluslf $eos Spring15_a25ns_GJets_HT_600ToInf_MINIAOD                 93.47      $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then
    ./sub.sh data $eos SinglePhoton_Run2015D_PrReco_05Oct_MINIAOD_v3                  1        $option1 $option2
    ./sub.sh data $eos SinglePhoton_Run2015D_PrReco_v4_MINIAOD_v3                  1        $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTDM") ]]; then    ./sub.sh mc $eos Spring15_a25ns_TTbarDMJets_pseudoscalar_Mchi-1_Mphi-100_MINIAOD 1.  $option1 $option2; fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S1_Mres-1100_Mchi-100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S1_Mres-1300_Mchi-100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S1_Mres-1500_Mchi-100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S1_Mres-1700_Mchi-100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S1_Mres-1900_Mchi-100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S1_Mres-2100_Mchi-100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S1_Mres-900_Mchi-100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S4_Mchi-1100_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S4_Mchi-1300_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S4_Mchi-1500_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S4_Mchi-300_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S4_Mchi-500_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S4_Mchi-700_13TeV-madgraph-pythia8     1    $option1 $option2
    ./sub.sh mc $eos Spring15_a25ns_DMJetsMonotop_S4_Mchi-900_13TeV-madgraph-pythia8     1    $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then
    ./sub.sh data $eos SingleElectron_Run2015D_PrReco_v4_MINIAOD                 1        $option1 $option2   
    ./sub.sh data $eos SingleElectron_Run2015D_PrReco_05Oct_MINIAOD                  1        $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleMuon") ]]; then
    ./sub.sh data $eos SingleMuon_Run2015D_PrReco_05Oct_MINIAOD                 1        $option1 $option2
    ./sub.sh data $eos SingleMuon_Run2015D_PrReco_v4_MINIAOD                  1        $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwig1L") ]]; then
    ./sub.sh mctt1l $eos Spring15_a25ns_TT_powheg_herwig_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwig2L") ]]; then
    ./sub.sh mctt2l $eos Spring15_a25ns_TT_powheg_herwig_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigHAD") ]]; then
    ./sub.sh mctthad $eos Spring15_a25ns_TT_powheg_herwig_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigBST") ]]; then
    ./sub.sh mcbst $eos Spring15_a25ns_TT_powheg_herwig_MINIAOD         831.76       $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TTherwigCOM") ]]; then
    ./sub.sh mccom $eos Spring15_a25ns_TT_powheg_herwig_MINIAOD         831.76       $option1 $option2; 
fi