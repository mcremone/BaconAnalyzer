#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="SR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} CENT jet
#	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP jet
#	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO jet
#	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} WJETHFUP jet
#	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} WJETHFDO jet
	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} BTAGUP jet
	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} BTAGDO jet
	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} MISTAGUP jet
	./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} MISTAGDO jet
        ./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} SJBTAGUP jet
        ./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} SJBTAGDO jet
        ./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} SJMISTAGUP jet
        ./skimMonoX.sh Had BstMonoTop ${reg} ${combo} ${algo} SJMISTAGDO jet
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
        ./skimMonoX.sh Had BstMonoHbb ${reg} ${combo} ${algo} CENT jetT
        ./skimMonoX.sh Had BstMonoHbb ${reg} ${combo} ${algo} BTAGUP jetT
        ./skimMonoX.sh Had BstMonoHbb ${reg} ${combo} ${algo} BTAGDO jetT
        ./skimMonoX.sh Had BstMonoHbb ${reg} ${combo} ${algo} MISTAGUP jetT
        ./skimMonoX.sh Had BstMonoHbb ${reg} ${combo} ${algo} MISTAGDO jetT
fi