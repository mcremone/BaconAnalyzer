#!/bin/bash   

sample=$1
option1=$2
option2=$3
dir="Singlebbits"
eos="/store/cmst3/group/monojet/production/singleb/"
if [[ ($sample = "All") || ($sample != "All" && $sample = "QCD") ]]; then
    ./sub.sh mcbkg $eos Fall15_QCD_HT100to200_MINIAOD                    27500000  $dir $option1 $option2
    ./sub.sh mcbkg $eos Fall15_QCD_HT200to300_MINIAOD                     1735000  $dir $option1 $option2
    ./sub.sh mcbkg $eos Fall15_QCD_HT300to500_MINIAOD                      367000  $dir $option1 $option2
    ./sub.sh mcbkg $eos Fall15_QCD_HT500to700_MINIAOD                       29370  $dir $option1 $option2
    ./sub.sh mcbkg $eos Fall15_QCD_HT700to1000_MINIAOD                       6524  $dir $option1 $option2
    ./sub.sh mcbkg $eos Fall15_QCD_HT1000to1500_MINIAOD                      1064  $dir $option1 $option2
    ./sub.sh mcbkg $eos Fall15_QCD_HT1500to2000_MINIAOD                     121.5  $dir $option1 $option2
    ./sub.sh mcbkg $eos Fall15_QCD_HT2000toInf_MINIAOD                      25.42  $dir $option1 $option2
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "Signal") ]]; then
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-1000_W-100_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-1000_W-10_MINIAOD                   1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-1000_W-300_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-1250_W-125_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-1250_W-12p5_MINIAOD                 1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-1500_W-150_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-2000_W-200_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-2000_W-20_MINIAOD                   1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-2000_W-600_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-2500_W-250_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-2500_W-25_MINIAOD                   1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-3000_W-300_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-3000_W-30_MINIAOD                   1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-3000_W-900_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-3500_W-350_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-3500_W-35_MINIAOD                   1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-4000_W-1200_MINIAOD                 1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-4000_W-400_MINIAOD                  1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-4000_W-40_MINIAOD                   1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-500_W-50_MINIAOD                    1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-500_W-5_MINIAOD                     1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-750_W-75_MINIAOD                    1  $dir $option1 $option2
    ./sub.sh mcsig $eos Fall15_ZprimeToTT_M-750_W-7p5_MINIAOD                   1  $dir $option1 $option2
fi