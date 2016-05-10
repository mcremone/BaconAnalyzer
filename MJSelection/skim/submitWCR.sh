#!/bin/bash

sample=$1
combo=$2
algo=$3
reg="WCR"

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
#	./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} WJETHFUP jet
#	./skimMonoX.sh Muo BstMonoTop ${reg} ${combo} ${algo} WJETHFDO jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} CENT jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGUP jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGDO jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGUP jet
	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGDO jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJBTAGUP jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJBTAGDO jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJMISTAGUP jet
        ./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} SJMISTAGDO jet
#	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} WJETHFUP jet
#	./skimMonoX.sh Ele BstMonoTop ${reg} ${combo} ${algo} WJETHFDO jet
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
        ./skimMonoX.sh Muo BstMonoHbb ${reg} ${combo} ${algo} CENT jetT
        ./skimMonoX.sh Muo BstMonoHbb ${reg} ${combo} ${algo} BTAGUP jetT
        ./skimMonoX.sh Muo BstMonoHbb ${reg} ${combo} ${algo} BTAGDO jetT
        ./skimMonoX.sh Muo BstMonoHbb ${reg} ${combo} ${algo} MISTAGUP jetT
        ./skimMonoX.sh Muo BstMonoHbb ${reg} ${combo} ${algo} MISTAGDO jetT
#       ./skimMonoX.sh Muo BstMonoHbb ${reg} ${combo} ${algo} WJETHFUP jetT
#       ./skimMonoX.sh Muo BstMonoHbb ${reg} ${combo} ${algo} WJETHFDO jetT
        ./skimMonoX.sh Ele BstMonoHbb ${reg} ${combo} ${algo} CENT jetT
        ./skimMonoX.sh Ele BstMonoHbb ${reg} ${combo} ${algo} BTAGUP jetT
        ./skimMonoX.sh Ele BstMonoHbb ${reg} ${combo} ${algo} BTAGDO jetT
        ./skimMonoX.sh Ele BstMonoHbb ${reg} ${combo} ${algo} MISTAGUP jetT
        ./skimMonoX.sh Ele BstMonoHbb ${reg} ${combo} ${algo} MISTAGDO jetT
#       ./skimMonoX.sh Ele BstMonoHbb ${reg} ${combo} ${algo} WJETHFUP jetT
#       ./skimMonoX.sh Ele BstMonoHbb ${reg} ${combo} ${algo} WJETHFDO jetT
fi
