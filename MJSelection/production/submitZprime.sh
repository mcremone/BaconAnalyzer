#!/bin/bash   

sample=$1
option1=$2
option2=$3
dir="zprimebits"
eos="/store/cmst3/group/monojet/production/10/"
exec="runZprime"
if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT100to200_13TeV                                                                    27500000  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT200to300_13TeV                                                                     1735000  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT300to500_13TeV                                                                      367000  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT500to700_13TeV                                                                       29370  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT700to1000_13TeV                                                                       6524  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT1000to1500_13TeV                                                                      1064  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT1500to2000_13TeV                                                                     121.5  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ QCD_HT2000toInf_13TeV                                                                      25.42  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then
    ./sub.sh mc $eos TTJets_13TeV_amcatnloFXFX_pythia8_trig                                                           831.76  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then
    ./sub.sh mc $eos WW_13TeV_pythia8_trig                                                                               118.7  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then
    ./sub.sh mc $eos WZ_13TeV_pythia8_trig                                                                                47.2  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then
    ./sub.sh mc $eos ZZ_13TeV_pythia8_trig                                                                                31.8  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WLF") ]]; then
    ./sub.sh mcwlf $eos WJetsToQQ_HT_600ToInf_13TeV                                                                 95.14  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WCS") ]]; then
    ./sub.sh mcwcs $eos WJetsToQQ_HT_600ToInf_13TeV                                                                 95.14  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYbb") ]]; then
    ./sub.sh mczbb $eos DYJetsToQQ_HT180_13TeV                                                                    1338.95  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYcc") ]]; then
    ./sub.sh mczcc $eos DYJetsToQQ_HT180_13TeV                                                                    1338.95  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "DYlf") ]]; then
    ./sub.sh mczlf $eos DYJetsToQQ_HT180_13TeV                                                                    1338.95  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Zprimelf") ]]; then
    ./sub.sh mcZprimelf /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_100GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_150GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_200GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_250GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_300GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_50GeV_v4                                                                                1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Zprimebb") ]]; then
    ./sub.sh mcZprimebb /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_100GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_150GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_200GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_250GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_300GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_50GeV_v4                                                                        1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Zprimecc") ]]; then
    ./sub.sh mcZprimecc /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_100GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_150GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_200GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_250GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_300GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc /store/cmst3/group/monojet/production/09/ ZPrimeToQQ_50GeV_v4                                                                        1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then
    ./sub.sh data $eos JetHTRun2016B_PromptReco_v1_trig                                                                       1  $dir $exec $option1 $option2
    ./sub.sh data $eos JetHTRun2016B_PromptReco_v2_trig                                                                       1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "VectorDiJet") ]]; then
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M10                                                                                1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M100                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M125                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M150                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M200                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M25                                                                                1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M250                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M300                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M50                                                                                1  $dir $exec $option1 $option2
    ./sub.sh mc /store/cmst3/group/monojet/production/09/ VectorDiJet1Jet_M75                                                                                1  $dir $exec $option1 $option2
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
   ./sub.sh data $eos SinglePhotonRun2016B_PromptReco_v1_trig                                                            1  $dir $exec $option1 $option2
   ./sub.sh data $eos SinglePhotonRun2016B_PromptReco_v2_trig                                                            1  $dir $exec $option1 $option2
fi