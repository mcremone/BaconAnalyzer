#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="SR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	#./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} CENT jet jetT
	./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} BTAGUP jet jetT
	./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} BTAGDO jet jetT
	./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} MISTAGUP jet jetT
	./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} MISTAGDO jet jetT
        ./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} SJBTAGUP jet jetT
        ./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} SJBTAGDO jet jetT
        ./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} SJMISTAGUP jet jetT
        ./skimMonoX.sh Had Bst15MonoTop ${reg} ${combo} ${algo} SJMISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "SemMonoTop") ]]; then
        ./skimMonoX.sh Had Bst15SemMonoTop ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Had Bst15SemMonoTop ${reg} ${combo} ${algo} BTAGUP jet jetT
        ./skimMonoX.sh Had Bst15SemMonoTop ${reg} ${combo} ${algo} BTAGDO jet jetT
        ./skimMonoX.sh Had Bst15SemMonoTop ${reg} ${combo} ${algo} MISTAGUP jet jetT
        ./skimMonoX.sh Had Bst15SemMonoTop ${reg} ${combo} ${algo} MISTAGDO jet jetT
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
