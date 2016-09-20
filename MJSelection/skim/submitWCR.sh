#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="WCR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MuoMonoTop") ]]; then
	./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} CENT jet jetT
	./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} BTAGUP jet jetT
	./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} BTAGDO jet jetT
	./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} MISTAGUP jet jetT
	./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} SJBTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} SJBTAGDO jet jetT
        ./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} SJMISTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15MonoTop ${reg} ${combo} ${algo} SJMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "EleMonoTop") ]]; then
	./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} CENT jet jetT
	./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} BTAGUP jet jetT
	./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} BTAGDO jet jetT
	./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} MISTAGUP jet jetT
	./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} SJBTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} SJBTAGDO jet jetT
        ./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} SJMISTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15MonoTop ${reg} ${combo} ${algo} SJMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MuoSemMonoTop") ]]; then
        ./skimMonoX.sh Muo Bst15SemMonoTop ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Muo Bst15SemMonoTop ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15SemMonoTop ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Muo Bst15SemMonoTop ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Muo Bst15SemMonoTop ${reg} ${combo} ${algo} MISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "EleSemMonoTop") ]]; then
        ./skimMonoX.sh Ele Bst15SemMonoTop ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Ele Bst15SemMonoTop ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15SemMonoTop ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Ele Bst15SemMonoTop ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Ele Bst15SemMonoTop ${reg} ${combo} ${algo} MISTAGDO jet jetT
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
