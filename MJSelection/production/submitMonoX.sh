sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop15") ]]; then
    ./plotMonoX.sh Had Bst15MonoTop SR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Had Bst15MonoTop QCDCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Ele Bst15MonoTop TopCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Ele Bst15MonoTop WCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Zmm Bst15MonoTop ZCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Zee Bst15MonoTop ZCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Pho Bst15MonoTop ZCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Muo Bst15MonoTop TopCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Muo Bst15MonoTop WCR ${combo} ${algo} CENT jet
    ./plotMonoX.sh Muo Bst15MonoTop TTbarCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo Bst15MonoTop minusTau32 ${combo} ${algo} CENT
    ./plotMonoX.sh Muo Bst15MonoTop minusMass ${combo} ${algo} CENT
    ./plotMonoX.sh Muo Bst15MonoTop minusBtag ${combo} ${algo} CENT
fi

if [[ ($sample = "All") || ($sample = "MonoHbb15") ]]; then
    ./plotMonoX.sh Had Bst15MonoHbb SR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst15MonoHbb TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst15MonoHbb WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Pho Bst15MonoHbb ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst15MonoHbb TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst15MonoHbb WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zmm Bst15MonoHbb ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zee Bst15MonoHbb ZCR ${combo} ${algo} CENT jet jetT
fi

if [[ ($sample = "All") || ($sample = "MonoHbb8") ]]; then
    ./plotMonoX.sh Had Bst8MonoHbb SR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst8MonoHbb TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst8MonoHbb WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Pho Bst8MonoHbb ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst8MonoHbb TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst8MonoHbb WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zmm Bst8MonoHbb ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zee Bst8MonoHbb ZCR ${combo} ${algo} CENT jet jetT
fi