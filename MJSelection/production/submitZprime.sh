#!/bin/bash   

sample=$1
option1=$2
option2=$3
dir="Zprimebits"
eos="/store/cmst3/group/monojet/production/08/"
if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then 
    ./sub.sh mc $eos QCD_HT100to200_13TeVRunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12_v1      27500000  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT200to300_13TeVRunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12_v1       1735000  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT300to500_13TeVRunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12_v1        367000  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT500to700_13TeVRunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12_v1         29370  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT700to1000_13TeV                                                                           3262  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT700to1000_13TeV_2                                                                         3262  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT1000to1500_13TeV_2                                                                        1064  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT1500to2000_13TeV_2                                                                       121.5  $dir $option1 $option2
    ./sub.sh mc $eos QCD_HT2000toInf_13TeV_2                                                                        25.42  $dir $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then 
    ./sub.sh mc $eos ST_t_channel_antitop_4f_inclusiveDecays_13TeV_powhegV2_madspin_pythia8_TuneCUETP8M1          44.0802  $dir $option1 $option2
    ./sub.sh mc $eos ST_t_channel_top_4f_inclusiveDecays_13TeV_powhegV2_madspin_pythia8_TuneCUETP8M1              26.2343  $dir $option1 $option2
    ./sub.sh mc $eos ST_tW_antitop_5f_inclusiveDecays_13TeV_powheg_pythia8_TuneCUETP8M1                              35.6  $dir $option1 $option2
    ./sub.sh mc $eos ST_tW_top_5f_inclusiveDecays_13TeV_powheg_pythia8_TuneCUETP8M1                                  35.6  $dir $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then
    ./sub.sh mc $eos TTJets_13TeV_amcatnloFXFX_pythia8_2                                                           831.76  $dir $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then
    ./sub.sh mc $eos WW_13TeV_pythia8                                                                               118.7  $dir $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then
    ./sub.sh mc $eos WZ_13TeV_pythia8                                                                                47.2  $dir $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then
    ./sub.sh mc $eos ZZ_13TeV_pythia8                                                                                31.8  $dir $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "W") ]]; then
    ./sub.sh mcwcs $eos WJetsToQQ_HT_600ToInf_13TeV                                                                 95.14  $dir $option1 $option2
    ./sub.sh mcvlf $eos WJetsToQQ_HT_600ToInf_13TeV                                                                 95.14  $dir $option1 $option2
fi
# if [[ ($sample = "All") || ($sample != "All" && $sample = "Z") ]]; then
#     ./sub.sh mczbb $eos Spring15_a25ns_ZJetsToQQ_HT600toInf_MINIAOD                                                  5.67  $dir $option1 $option2
#     ./sub.sh mczcc $eos Spring15_a25ns_ZJetsToQQ_HT600toInf_MINIAOD                                                  5.67  $dir $option1 $option2
#     ./sub.sh mcvlf $eos Spring15_a25ns_ZJetsToQQ_HT600toInf_MINIAOD                                                  5.67  $dir $option1 $option2
# fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DY") ]]; then
    ./sub.sh mczbb $eos DYJetsToQQ_HT180_13TeVRunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12_v1   1187.0  $dir $option1 $option2
    ./sub.sh mczcc $eos DYJetsToQQ_HT180_13TeVRunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12_v1   1187.0  $dir $option1 $option2
    ./sub.sh mcvlf $eos DYJetsToQQ_HT180_13TeVRunIIFall15MiniAODv2_PU25nsData2015v1_76X_mcRun2_asymptotic_v12_v1   1187.0  $dir $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then 
    ./sub.sh data $eos JetHTRun2015D_16Dec2015_v1_2                                                                     1  $dir $option1 $option2
fi
