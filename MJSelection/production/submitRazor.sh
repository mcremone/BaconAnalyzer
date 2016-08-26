#!/bin/bash   

sample=$1
option1=$2
option2=$3

dir="razorbits"
eos="/store/cmst3/group/monojet/production/10/"
exec="runRazor"

if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then 
    ./sub.sh mc $eos QCD_HT100to200_13TeV                   27500000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT200to300_13TeV                   1735000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT200to300_13TeV_ext                   1735000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT300to500_13TeV                   367000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT300to500_13TeV_ext                   367000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT500to700_13TeV                   29370  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT500to700_13TeV_ext                   29370  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT700to1000_13TeV                  6524  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT700to1000_13TeV_ext                  6524  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1000to1500_13TeV                 1064  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1000to1500_13TeV_ext                 1064  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1500to2000_13TeV                 121.5  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1500to2000_13TeV_ext                 121.5  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT2000toInf_13TeV                  25.42  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT2000toInf_13TeV_ext                  25.42  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WHF") ]]; then
   ./sub.sh mcwplushf $eos WJetsToLNu_HT_100To200_13TeV_ext                                                      1343  $dir $exec $option1 $option2
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_200To400_13TeV                                                         359.6  $dir $exec $option1 $option2
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_200To400_13TeV_ext                                                     359.6  $dir $exec $option1 $option2
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_400To600_13TeV                                                         48.85  $dir $exec $option1 $option2                                                  
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_600To800_13TeV                                                         12.05  $dir $exec $option1 $option2
    #./sub.sh mcwplushf $eos WJetsToLNu_HT_600ToInf_13TeV_2 18.91 $dir $exec $option1 $option2 
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_800To1200_13TeV                                                        5.501  $dir $exec $option1 $option2
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_800To1200_13TeV_ext                                                    5.501  $dir $exec $option1 $option2
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_1200To2500_13TeV_ext                                                   1.329  $dir $exec $option1 $option2
    ./sub.sh mcwplushf $eos WJetsToLNu_HT_2500ToInf_13TeV                                                      0.03216  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_100To200_13TeV_ext                                                        1343  $dir $exec $option1 $option2
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_200To400_13TeV                                                         359.6  $dir $exec $option1 $option2
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_200To400_13TeV_ext                                                     359.6  $dir $exec $option1 $option2  
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_400To600_13TeV                                                         48.85  $dir $exec $option1 $option2
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_600To800_13TeV                                                         12.05  $dir $exec $option1 $option2
  # ./sub.sh mcwpluslf $eos WJetsToLNu_HT_600ToInf_13TeV_2 18.91 $dir $exec $option1 $option2 
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_800To1200_13TeV                                                        5.501  $dir $exec $option1 $option2
   ./sub.sh mcwplushf $eos WJetsToLNu_HT_800To1200_13TeV_ext                                                    5.501  $dir $exec $option1 $option2
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_1200To2500_13TeV_ext                                                   1.329  $dir $exec $option1 $option2
   ./sub.sh mcwpluslf $eos WJetsToLNu_HT_2500ToInf_13TeV                                                      0.03216  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYHF") ]]; then
   ./sub.sh mcdyplushf $eos DYJetsToLL_M_50_HT_100to200_13TeV_ext                                               148.0  $dir $exec $option1 $option2
   ./sub.sh mcdyplushf $eos DYJetsToLL_M_50_HT_200to400_13TeV_ext                                               40.94  $dir $exec $option1 $option2
   ./sub.sh mcdyplushf $eos DYJetsToLL_M_50_HT_400to600_13TeV_ext                                               5.497  $dir $exec $option1 $option2
   ./sub.sh mcdyplushf $eos DYJetsToLL_M_50_HT_600toInf_13TeV                                                   2.193  $dir $exec $option1 $option2
fi  
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYLF") ]]; then
   ./sub.sh mcdypluslf $eos DYJetsToLL_M_50_HT_100to200_13TeV_ext                                               148.0  $dir $exec $option1 $option2
   ./sub.sh mcdypluslf $eos DYJetsToLL_M_50_HT_200to400_13TeV_ext                                               40.94  $dir $exec $option1 $option2
   ./sub.sh mcdypluslf $eos DYJetsToLL_M_50_HT_400to600_13TeV_ext                                               5.497  $dir $exec $option1 $option2
   ./sub.sh mcdypluslf $eos DYJetsToLL_M_50_HT_600toInf_13TeV                                                   2.193  $dir $exec $option1 $option2
fi 
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZHF") ]]; then
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_100To200_13TeV_madgraph_ext                                          280.5  $dir $exec $option1 $option2
    ./sub.sh mczplushf /store/cmst3/group/monojet/production/08/ ZJetsToNuNu_HT_200To400_13TeV_madgraph                                               77.7  $dir $exec $option1 $option2
    ./sub.sh mczplushf /store/cmst3/group/monojet/production/08/ ZJetsToNuNu_HT_400To600_13TeV_madgraph                                              10.71  $dir $exec $option1 $option2
    #./sub.sh mczplushf $eos ZJetsToNuNu_HT_600ToInf_13TeV_madgraph                                              4.098  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_600To800_13TeV_madgraph                                              2.559  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_800To1200_13TeV_madgraph                                            1.1826  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_1200To2500_13TeV_madgraph                                          0.2922  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_1200To2500_13TeV_madgraph_ext                                          0.2922  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_2500ToInf_13TeV_madgraph                                            0.0069  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZLF") ]]; then
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_100To200_13TeV_madgraph_ext                                          280.5  $dir $exec $option1 $option2
    ./sub.sh mczplushf /store/cmst3/group/monojet/production/08/ ZJetsToNuNu_HT_200To400_13TeV_madgraph                                               77.7  $dir $exec $option1 $option2
    ./sub.sh mczplushf /store/cmst3/group/monojet/production/08/ ZJetsToNuNu_HT_400To600_13TeV_madgraph                                              10.71  $dir $exec $option1 $option2
    #./sub.sh mczplushf $eos ZJetsToNuNu_HT_600ToInf_13TeV_madgraph                                              4.098  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_600To800_13TeV_madgraph                                              2.559  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_800To1200_13TeV_madgraph                                            1.1826  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_1200To2500_13TeV_madgraph                                          0.2922  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_1200To2500_13TeV_madgraph_ext                                          0.2922  $dir $exec $option1 $option2
    ./sub.sh mczplushf $eos ZJetsToNuNu_HT_2500ToInf_13TeV_madgraph                                            0.0069  $dir $exec $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "T") ]]; then
    ./sub.sh mc /store/cmst3/group/monojet/production/08/ ST_t_channel_antitop_4f_inclusiveDecays_13TeV_powhegV2_madspin_pythia8_TuneCUETP8M1      44.0802  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/08/ ST_t_channel_top_4f_inclusiveDecays_13TeV_powhegV2_madspin_pythia8_TuneCUETP8M1          26.2343  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/08/ ST_tW_antitop_5f_inclusiveDecays_13TeV_powheg_pythia8_TuneCUETP8M1                          35.6  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/08/ ST_tW_top_5f_inclusiveDecays_13TeV_powheg_pythia8_TuneCUETP8M1                              35.6  $dir $exec $option1 $option2
fi

# if [[ ($sample = "All") || ($sample != "All" && $sample = "THQ") ]]; then
#     ./sub.sh mc $eos /THQ_Hincl_13TeV_madgraph_pythia8_TuneCUETP8M1                                          0.070940  $dir $exec $option1 $option2;
# fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then
   #./sub.sh mctt $eos TTJets_13TeV                                                                             831.76  $dir $exec $option1 $option2;
   ./sub.sh mctt $eos TTJets_13TeV_amcatnloFXFX_pythia8                                                        831.76  $dir $exec $option1 $option2;
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then
    ./sub.sh mc $eos WW_13TeV_pythia8                                                                           118.7  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then
    ./sub.sh mc $eos WZ_13TeV_pythia8                                                                            47.2  $dir $exec $option1 $option2; 
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then
    ./sub.sh mc $eos ZZ_13TeV_pythia8                                                                            31.8  $dir $exec $option1 $option2; 
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MET") ]]; then 
    ./sub.sh data $eos METRun2016B_PromptReco_v2                              1  $dir $exec $option1 $option2
    ./sub.sh data $eos METRun2016C_PromptReco_v2                              1  $dir $exec $option1 $option2
    ./sub.sh data $eos METRun2016D_PromptReco_v2                              1  $dir $exec $option1 $option2
    ./sub.sh data $eos METRun2016D_PromptReco_v3                              1  $dir $exec $option1 $option2
    ./sub.sh data $eos METRun2016D_PromptReco_v4                              1  $dir $exec $option1 $option2
    ./sub.sh data $eos METRun2016E_PromptReco_v2                              1  $dir $exec $option1 $option2
    ./sub.sh data $eos METRun2016F_PromptReco_v1                              1  $dir $exec $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "GHF") ]]; then 
    ./sub.sh mcgplushf $eos GJets_HT_100To200_13TeV                                                              9235  $dir $exec $option1 $option2
    ./sub.sh mcgplushf $eos GJets_HT_200To400_13TeV                                                              2298  $dir $exec $option1 $option2
    ./sub.sh mcgplushf $eos GJets_HT_400To600_13TeV                                                             277.6  $dir $exec $option1 $option2
    ./sub.sh mcgplushf $eos GJets_HT_600ToInf_13TeV                                                             93.47  $dir $exec $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "GLF") ]]; then
    ./sub.sh mcgpluslf $eos GJets_HT_100To200_13TeV                                                              9235  $dir $exec $option1 $option2
    ./sub.sh mcgpluslf $eos GJets_HT_200To400_13TeV                                                              2298  $dir $exec $option1 $option2
    ./sub.sh mcgpluslf $eos GJets_HT_400To600_13TeV                                                             277.6  $dir $exec $option1 $option2
    ./sub.sh mcgpluslf $eos GJets_HT_600ToInf_13TeV                                                             93.47  $dir $exec $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "SinglePhoton") ]]; then
   ./sub.sh data $eos SinglePhotonRun2016B_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SinglePhotonRun2016C_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SinglePhotonRun2016D_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SinglePhotonRun2016D_PromptReco_v3                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SinglePhotonRun2016D_PromptReco_v4                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SinglePhotonRun2016E_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SinglePhotonRun2016F_PromptReco_v1                              1  $dir $exec $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "SingleElectron") ]]; then
   ./sub.sh data $eos SingleElectronRun2016B_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SingleElectronRun2016C_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SingleElectronRun2016D_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SingleElectronRun2016D_PromptReco_v3                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SingleElectronRun2016D_PromptReco_v4                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SingleElectronRun2016E_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos SingleElectronRun2016F_PromptReco_v1                              1  $dir $exec $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then
   ./sub.sh data $eos JetHTRun2016B_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos JetHTRun2016C_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos JetHTRun2016D_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos JetHTRun2016D_PromptReco_v3                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos JetHTRun2016D_PromptReco_v4                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos JetHTRun2016E_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos JetHTRun2016F_PromptReco_v1                              1  $dir $exec $option1 $option2
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "HTMHT") ]]; then
   ./sub.sh data $eos HTMHTRun2016B_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos HTMHTRun2016C_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos HTMHTRun2016D_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos HTMHTRun2016D_PromptReco_v3                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos HTMHTRun2016D_PromptReco_v4                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos HTMHTRun2016E_PromptReco_v2                              1  $dir $exec $option1 $option2
   ./sub.sh data $eos HTMHTRun2016F_PromptReco_v1                              1  $dir $exec $option1 $option2
fi


