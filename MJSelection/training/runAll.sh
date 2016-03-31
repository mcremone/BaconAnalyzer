#!/bin/bash
training=("unweighted_rALL" "reweighted_rALL" "unweighted_r800" "reweighted_r800")
options=("-a" "-a -w" "" "-w")

l=0
while [ $l -lt 2 ]
do
	jobsrunning=0
	while [[ $jobsrunning -lt 2 ]] 
	do
		echo Processing ${training[l]}
		# mkdir tmp_${training[l]}
		cd tmp_${training[l]}
		echo python ../tmva_training.py -g -c ${options[l]} --file=${training[l]}
		nohup python ../tmva_training.py -g -c ${options[l]} --file=${training[l]} &
		cd ..
		let jobsrunning=$jobsrunning+1
		let l=$l+1
	done
	wait
done