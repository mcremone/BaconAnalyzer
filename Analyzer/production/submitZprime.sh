#!/bin/bash   

sample=$1
option1=$2
option2=$3
dir="zprimebits"
eos="/store/cmst3/group/monojet/production/10/"
exec="runZprime"
if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then
    ./sub.sh mc $eos QCD_HT100to200_13TeV                                                                    27500000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT200to300_13TeV                                                                     1735000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT200to300_13TeV_ext                                                                 1735000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT300to500_13TeV                                                                      367000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT300to500_13TeV_ext                                                                  367000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT500to700_13TeV                                                                       29370  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT500to700_13TeV_ext                                                                   29370  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT700to1000_13TeV                                                                       6524  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT700to1000_13TeV_ext                                                                   6524  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1000to1500_13TeV                                                                      1064  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1000to1500_13TeV_ext                                                                  1064  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1500to2000_13TeV                                                                     121.5  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1500to2000_13TeV_ext                                                                 121.5  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT2000toInf_13TeV                                                                      25.42  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then
#     ./sub.sh mc $eos TT_13TeV_powheg_pythia8_ext                                                               831.76  $dir $exec $option1 $option2; 
    ./sub.sh mc $eos TTJets_13TeV                                                                              831.76  $dir $exec $option1 $option2;
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Diboson") ]]; then
    ./sub.sh mc $eos WW_13TeV_pythia8                                                                           118.7  $dir $exec $option1 $option2; 
    ./sub.sh mc $eos WZ_13TeV_pythia8                                                                            47.2  $dir $exec $option1 $option2; 
    ./sub.sh mc $eos ZZ_13TeV_pythia8                                                                            31.8  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleTop") ]]; then
#   ./sub.sh mc $eos ST_t_channel_antitop_4f_inclusiveDecays_13TeV_powhegV2_madspin_pythia8_TuneCUETP8M1       44.0802  $dir $exec $option1 $option2
#   ./sub.sh mc $eos ST_t_channel_top_4f_inclusiveDecays_13TeV_powhegV2_madspin_pythia8_TuneCUETP8M1           26.2343  $dir $exec $option1 $option2
   ./sub.sh mc $eos ST_tW_antitop_5f_inclusiveDecays_13TeV_powheg_pythia8_TuneCUETP8M1                           35.6  $dir $exec $option1 $option2
   ./sub.sh mc $eos ST_tW_top_5f_inclusiveDecays_13TeV_powheg_pythia8_TuneCUETP8M1                               35.6  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then
    ./sub.sh mc $eos WJetsToQQ_HT_600ToInf_13TeV                                                                95.14  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then
    ./sub.sh mc $eos DYJetsToQQ_HT180_13TeV                                                                   1338.95  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then
    ./sub.sh data $eos JetHTRun2016B_PromptReco_v2                                                                  1  $dir $exec $option1 $option2
    ./sub.sh data $eos JetHTRun2016C_PromptReco_v2                                                                  1  $dir $exec $option1 $option2
    ./sub.sh data $eos JetHTRun2016D_PromptReco_v2                                                                  1  $dir $exec $option1 $option2
#     ./sub.sh data $eos JetHTRun2016D_PromptReco_v3                                                                  1  $dir $exec $option1 $option2
#     ./sub.sh data $eos JetHTRun2016D_PromptReco_v4                                                                  1  $dir $exec $option1 $option2
    ./sub.sh data $eos JetHTRun2016E_PromptReco_v2                                                                  1  $dir $exec $option1 $option2
    ./sub.sh data $eos JetHTRun2016F_PromptReco_v1                                                                  1  $dir $exec $option1 $option2
#     ./sub.sh data $eos JetHTRun2016G_PromptReco_v1                                                                  1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "VectorDiJet") ]]; then
    ./sub.sh mc $eos VectorDiJet1Jet_M50                                                                            1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M75                                                                            1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M100                                                                           1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M125                                                                           1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M150                                                                           1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M200                                                                           1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M250                                                                           1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M300                                                                           1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M400                                                                           1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M500                                                                           1  $dir $exec $option1 $option2
fi