#!/bin/bash

#argv[1] => input bacon file name                                                                                                                                                          
#argv[2] => dataset type: "mc", "mczbb", "mczcc", "mcwcs", "mcvlf", "data"                                                                                                              
#argv[3] => JSON file for run-lumi filtering of data, specify "none" for MC or no filtering                                                                                             
#argv[4] => cross section (pb), ignored for data                                                                                                                                       
#argv[5] => total weight, ignored for data       

ismc=$1
dir=$2
label=$3
xs=$4
option1=$5
option2=$6

options1="Output.root --passSumEntries 5:Events  -a 2:"${ismc}" -a 3:none  -n 2000 -q 8nh"
#options1="Output.root --passSumEntries 5:Events  -a 2:"${ismc}" -a 3:none  -n 2000 -q cmscaf1nd"
if [ $ismc = "data" ]; then
    options1="Output.root -a 5:1  -a 2:"${ismc}" -a 3:$PWD/../../Json/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt  -n 2000 -q 8nh"
#    options1="Output.root -a 5:1  -a 2:"${ismc}" -a 3:$PWD/../../Json/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON.txt  -n 2000 -q 8nh"
#    options1="Output.root -a 5:1  -a 2:"${ismc}" -a 3:$PWD/../../Json/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON.txt  -n 2000 -q cmscaf1nd"
fi

scandir=$dir$label
submitted=0
total=0
function scan { 
    local scandir=$1
    echo $scandir
    submitted=0
    for x in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls $scandir |  awk '{print $1}'`; do
	hasdot=`echo $x | grep -c "\."` 
	if [ "$hasdot" -eq 0 ]; then
	    echo "Scanning: "$scandir/$x
	    scan  $scandir/$x
	fi
	hasroot=`echo $x | grep -c .root` 
	if [ "$hasroot" -eq 0 ]; then 
	    echo " "
	else 
	   if [ "$submitted" -eq 0 ]; then
	       python baconBatch.py runMonoX  $options1 -a "4:"$xs -d "1:"$scandir  -o $PWD/../baconbits/${label}_${ismc}   $option1 $option2
	       submitted=$((submitted+1))
	       total=$((total+1))
	   fi
	fi
    done
}
scan $scandir

exit
