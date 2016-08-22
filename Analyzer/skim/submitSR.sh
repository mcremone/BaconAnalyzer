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

if [[ ($sample = "All") || ($sample != "All" && $sample = "Bst15MonoHbb") ]]; then
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} SJBTAGUP jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} SJBTAGDO jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} SJMISTAGUP jet jetT
        ./skimMonoX.sh Had Bst15MonoHbb ${reg} ${combo} ${algo} SJMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "Bst8MonoHbb") ]]; then
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBBTAGUP jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBBTAGDO jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBMISTAGUP jet jetT
        ./skimMonoX.sh Had Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ResMonoHbb") ]]; then
        ./skimMonoX.sh Had ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Had ResMonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Had ResMonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Had ResMonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Had ResMonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
fi
