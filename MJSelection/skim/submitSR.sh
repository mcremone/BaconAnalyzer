#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="SR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} CENT
#	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP
#	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO
#	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} WJETHFUP
#	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} WJETHFDO
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
fi