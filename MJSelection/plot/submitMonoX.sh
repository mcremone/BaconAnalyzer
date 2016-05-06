sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    ./plotMonoX.sh Had BstMonoTop SR ${combo} ${algo} CENT
    # ./plotMonoX.sh Had BstMonoTop QCDCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop TopCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop WCR ${combo} ${algo} CENT
    # ./plotMonoX.sh Zmm BstMonoTop ZCR ${combo} ${algo} CENT
    # ./plotMonoX.sh Zee BstMonoTop ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Pho BstMonoTop ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo BstMonoTop TopCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo BstMonoTop WCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo BstMonoTop TTbarCR ${combo} ${algo} CENT
    # ./plotMonoX.sh Muo BstMonoTop minusTau32 ${combo} ${algo} CENT
    # ./plotMonoX.sh Muo BstMonoTop minusMass ${combo} ${algo} CENT
    # ./plotMonoX.sh Muo BstMonoTop minusBtag ${combo} ${algo} CENT
fi

if [[ ($sample = "All") || ($sample = "MonoHbb") ]]; then
    ./plotMonoX.sh Had BstMonoHbb SR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoHbb HCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoHbb WCR ${combo} ${algo} CENT
    ./plotMonoX.sh Pho BstMonoHbb ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo BstMonoHbb TopCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo BstMonoHbb WCR ${combo} ${algo} CENT
fi