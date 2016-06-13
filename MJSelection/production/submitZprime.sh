#!/bin/bash   

sample=$1
option1=$2
option2=$3
dir="zprimebits"
eos="/store/cmst3/group/monojet/production/09/"
exec="runZprime"
if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then 
    ./sub.sh mc $eos QCD_HT100to200_13TeV                                                                        27500000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT200to300_13TeV                                                                         1735000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT300to500_13TeV                                                                          367000  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT500to700_13TeV                                                                           29370  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT700to1000_13TeV                                                                           6524  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1000to1500_13TeV                                                                          1064  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT1500to2000_13TeV                                                                         121.5  $dir $exec $option1 $option2
    ./sub.sh mc $eos QCD_HT2000toInf_13TeV                                                                          25.42  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "TT") ]]; then
    ./sub.sh mc $eos TTJets_13TeV_amcatnloFXFX_pythia8_2                                                           831.76  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WW") ]]; then
    ./sub.sh mc $eos WW_13TeV_pythia8                                                                               118.7  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "WZ") ]]; then
    ./sub.sh mc $eos WZ_13TeV_pythia8                                                                                47.2  $dir $exec $option1 $option2; 
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "ZZ") ]]; then
    ./sub.sh mc $eos ZZ_13TeV_pythia8                                                                                31.8  $dir $exec $option1 $option2; 
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
    ./sub.sh mcZprimelf $eos ZPrimeToQQ_100GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf $eos ZPrimeToQQ_150GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf $eos ZPrimeToQQ_200GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf $eos ZPrimeToQQ_250GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf $eos ZPrimeToQQ_300GeV_v4                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mcZprimelf $eos ZPrimeToQQ_50GeV_v4                                                                                1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Zprimebb") ]]; then
    ./sub.sh mcZprimebb $eos ZPrimeToQQ_100GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb $eos ZPrimeToQQ_150GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb $eos ZPrimeToQQ_200GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb $eos ZPrimeToQQ_250GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb $eos ZPrimeToQQ_300GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimebb $eos ZPrimeToQQ_50GeV_v4                                                                        1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Zprimecc") ]]; then
    ./sub.sh mcZprimecc $eos ZPrimeToQQ_100GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc $eos ZPrimeToQQ_150GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc $eos ZPrimeToQQ_200GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc $eos ZPrimeToQQ_250GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc $eos ZPrimeToQQ_300GeV_v4                                                                       1  $dir $exec $option1 $option2
    ./sub.sh mcZprimecc $eos ZPrimeToQQ_50GeV_v4                                                                        1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "JetHT") ]]; then
    ./sub.sh data $eos JetHTRun2015D_16Dec2015_v1_2                                                                     1  $dir $exec $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "VectorDiJet") ]]; then
    ./sub.sh mc $eos VectorDiJet1Jet_M10                                                                                1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M100                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M125                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M150                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M200                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M25                                                                                1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M250                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M300                                                                               1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M50                                                                                1  $dir $exec $option1 $option2
    ./sub.sh mc $eos VectorDiJet1Jet_M75                                                                                1  $dir $exec $option1 $option2
fi
