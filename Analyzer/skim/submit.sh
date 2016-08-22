#!/bin/bash

sample=$1
combo=$2
algo=$3
reg=$4

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    if[($reg="SR")]; then
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} WJETHFUP
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} WJETHFDO
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Had BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
    fi
    if[$reg="WCR"]; 
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} WJETHFUP
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} WJETHFDO
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} WJETHFUP
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} WJETHFDO
    fi
    if[$reg="TopCR"];
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Muo BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGUP
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} BTAGDO
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGUP
	./sub.sh Ele BstMonoTop ${reg} ${combo} ${algo} MISTAGDO
    fi
    if[$reg="ZCR"]; 
	./sub.sh Zmm BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Zmm BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP
	./sub.sh Zmm BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO
	./sub.sh Zee BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Zee BstMonoTop ${reg} ${combo} ${algo} ZJETHFUP
	./sub.sh Zee BstMonoTop ${reg} ${combo} ${algo} ZJETHFDO
	./sub.sh Pho BstMonoTop ${reg} ${combo} ${algo} CENT
	./sub.sh Pho BstMonoTop ${reg} ${combo} ${algo} GJETHFUP
	./sub.sh Pho BstMonoTop ${reg} ${combo} ${algo} GJETHFDO
    fi
fi