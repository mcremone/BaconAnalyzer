sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    ./plotMonoX.sh Had BstMonoTop SR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Had BstMonoTop QCDCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Ele BstMonoTop TopCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Ele BstMonoTop WCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Zmm BstMonoTop ZCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Zee BstMonoTop ZCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Pho BstMonoTop ZCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Muo BstMonoTop TopCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Muo BstMonoTop WCR ${combo} ${algo} CENT jet
    # ./plotMonoX.sh Muo BstMonoTop TTbarCR ${combo} ${algo} CENT
    # ./plotMonoX.sh Muo BstMonoTop minusTau32 ${combo} ${algo} CENT
    # ./plotMonoX.sh Muo BstMonoTop minusMass ${combo} ${algo} CENT
    # ./plotMonoX.sh Muo BstMonoTop minusBtag ${combo} ${algo} CENT
fi

if [[ ($sample = "All") || ($sample = "MonoHbb") ]]; then
    ./plotMonoX.sh Had BstMonoHbb SR ${combo} ${algo} CENT jetT
    ./plotMonoX.sh Ele BstMonoHbb TopCR ${combo} ${algo} CENT jetT
    ./plotMonoX.sh Ele BstMonoHbb WCR ${combo} ${algo} CENT jetT
    ./plotMonoX.sh Pho BstMonoHbb ZCR ${combo} ${algo} CENT jetT
    ./plotMonoX.sh Muo BstMonoHbb TopCR ${combo} ${algo} CENT jetT
    ./plotMonoX.sh Muo BstMonoHbb WCR ${combo} ${algo} CENT jetT
    ./plotMonoX.sh Zmm BstMonoHbb ZCR ${combo} ${algo} CENT jetT
    ./plotMonoX.sh Zee BstMonoHbb ZCR ${combo} ${algo} CENT jetT
fi