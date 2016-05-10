#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="ZCR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	./skimMonoX.sh Zmm BstMonoTop ${reg} ${combo} ${algo} CENT jet
#	./skimMonoX.sh Zmm BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP jet
#	./skimMonoX.sh Zmm BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO jet
	./skimMonoX.sh Zee BstMonoTop ${reg} ${combo} ${algo} CENT jet
#	./skimMonoX.sh Zee BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP jet
#	./skimMonoX.sh Zee BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO jet
	./skimMonoX.sh Pho BstMonoTop ${reg} ${combo} ${algo} CENT jet
#	./skimMonoX.sh Pho BstMonoTop ${reg} ${combo} ${algo} GJETHFUP jet
#	./skimMonoX.sh Pho BstMonoTop ${reg} ${combo} ${algo} GJETHFDO jet
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
        ./skimMonoX.sh Zmm BstMonoHbb ${reg} ${combo} ${algo} CENT jetT
        ./skimMonoX.sh Zee BstMonoHbb ${reg} ${combo} ${algo} CENT jetT
        ./skimMonoX.sh Pho BstMonoHbb ${reg} ${combo} ${algo} CENT jetT
fi
