#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="TopCR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} CENT jet
	./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGUP jet
	./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGDO jet
	./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGUP jet
	./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGDO jet
        ./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} SJBTAGUP jet
        ./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} SJBTAGDO jet
        ./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} SJMISTAGUP jet
        ./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} SJMISTAGDO jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} CENT jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGUP jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGDO jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGUP jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGDO jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJBTAGUP jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJBTAGDO jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJMISTAGUP jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJMISTAGDO jet
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MuoBst15MonoHbb") ]]; then
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} SJBTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} SJBTAGDO jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} SJMISTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15MonoHbb ${reg} ${combo} ${algo} SJMISTAGDO jet jetT
fi 

if [[ ($sample = "All") || ($sample != "All" && $sample = "EleBst15MonoHbb") ]]; then
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} SJBTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} SJBTAGDO jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} SJMISTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15MonoHbb ${reg} ${combo} ${algo} SJMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MuoBst8MonoHbb") ]]; then
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBBTAGUP jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBBTAGDO jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBMISTAGUP jet jetT
        ./skimMonoX.sh Muo Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "EleBst8MonoHbb") ]]; then
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBBTAGUP jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBBTAGDO jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBMISTAGUP jet jetT
        ./skimMonoX.sh Ele Bst8MonoHbb ${reg} ${combo} ${algo} DOUBLEBMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MuoResMonoHbb") ]]; then
        ./skimMonoX.sh Muo ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Muo ResMonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Muo ResMonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Muo ResMonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Muo ResMonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "EleResMonoHbb") ]]; then
        ./skimMonoX.sh Ele ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Ele ResMonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Ele ResMonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Ele ResMonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Ele ResMonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
fi
