#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="ZCR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	./sub.sh Zmm BstMonoTop ${reg} ${combo} ${algo} CENT
#	./sub.sh Zmm BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP
#	./sub.sh Zmm BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO
	./sub.sh Zee BstMonoTop ${reg} ${combo} ${algo} CENT
#	./sub.sh Zee BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP
#	./sub.sh Zee BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO
	./sub.sh Pho BstMonoTop ${reg} ${combo} ${algo} CENT
#	./sub.sh Pho BstMonoTop ${reg} ${combo} ${algo} GJETHFUP
#	./sub.sh Pho BstMonoTop ${reg} ${combo} ${algo} GJETHFDO
fi