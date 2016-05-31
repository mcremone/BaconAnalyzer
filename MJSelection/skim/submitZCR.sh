#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="ZCR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	./skimMonoX.sh Zmm BstMonoTop ${reg} ${combo} ${algo} CENT jet
	./skimMonoX.sh Zee BstMonoTop ${reg} ${combo} ${algo} CENT jet
	./skimMonoX.sh Pho BstMonoTop ${reg} ${combo} ${algo} CENT jet
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "Bst15MonoHbb") ]]; then
        ./skimMonoX.sh Zmm Bst15MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Zee Bst15MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Pho Bst15MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "Bst8MonoHbb") ]]; then
        ./skimMonoX.sh Zmm Bst8MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Zee Bst8MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Pho Bst8MonoHbb ${reg} ${combo} ${algo} CENT jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ResZmmMonoHbb") ]]; then
        ./skimMonoX.sh Zmm ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Zee ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        ./skimMonoX.sh Pho ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        # ./skimMonoX.sh Zmm ResMonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        # ./skimMonoX.sh Zmm ResMonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        # ./skimMonoX.sh Zmm ResMonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        # ./skimMonoX.sh Zmm ResMonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ResZeeMonoHbb") ]]; then
        ./skimMonoX.sh Zee ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        # ./skimMonoX.sh Zee ResMonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        # ./skimMonoX.sh Zee ResMonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        # ./skimMonoX.sh Zee ResMonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        # ./skimMonoX.sh Zee ResMonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "ResPhoMonoHbb") ]]; then
        ./skimMonoX.sh Pho ResMonoHbb ${reg} ${combo} ${algo} CENT jet jetT
        # ./skimMonoX.sh Pho ResMonoHbb ${reg} ${combo} ${algo} BTAGUP jet jetT
        # ./skimMonoX.sh Pho ResMonoHbb ${reg} ${combo} ${algo} BTAGDO jet jetT
        # ./skimMonoX.sh Pho ResMonoHbb ${reg} ${combo} ${algo} MISTAGUP jet jetT
        # ./skimMonoX.sh Pho ResMonoHbb ${reg} ${combo} ${algo} MISTAGDO jet jetT

fi

