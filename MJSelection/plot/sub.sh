#!/bin/bash

#void plotMonoX(const string preselection, const string selection, const string subsample, const string combo, const string algo)
preselection=$1
selection=$2
subsample=$3
combo=$4
algo=$5
syst=$6

python plotMonoX.py -p ${preselection} -l ${selection} -b ${subsample} -c ${combo} -a ${algo} -s ${syst}
chmod u+x $PWD/batch/${preselection}_${selection}_${subsample}_${combo}_${algo}_${syst}.sh
#bsub  -q 8nh -o $PWD/batch/${preselection}_${selection}_${subsample}_${combo}_${algo}_${syst}.sh.log $PWD/batch/${preselection}_${selection}_${subsample}_${combo}_${algo}_${syst}.sh
./batch/${preselection}_${selection}_${subsample}_${combo}_${algo}_${syst}.sh