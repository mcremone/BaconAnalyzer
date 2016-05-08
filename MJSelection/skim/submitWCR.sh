#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="WCR"

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
#	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} WJETHFUP
#	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} WJETHFDO
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
#	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} WJETHFUP
#	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} WJETHFDO
fi