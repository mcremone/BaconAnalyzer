sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop15") ]]; then
    ./plotMonoX.sh Had Bst15MonoTop SR ${combo} ${algo} CENT jet jetT
    #./plotMonoX.sh Had Bst15MonoTop QCDCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst15MonoTop TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst15MonoTop WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zmm Bst15MonoTop ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zee Bst15MonoTop ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Pho Bst15MonoTop ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst15MonoTop TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst15MonoTop WCR ${combo} ${algo} CENT jet jetT
    #./plotMonoX.sh Muo Bst15MonoTop TTbarCR ${combo} ${algo} CENT jet jetT
    #./plotMonoX.sh Muo Bst15MonoTop minusTau32 ${combo} ${algo} CENT jet jetT
    #./plotMonoX.sh Muo Bst15MonoTop minusMass ${combo} ${algo} CENT jet jetT
    #./plotMonoX.sh Muo Bst15MonoTop minusBtag ${combo} ${algo} CENT jet jetT
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "Bst15MonoTop") ]]; then
    ./plotMonoX.sh Had Bst15SemMonoTop SR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst15SemMonoTop TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele Bst15SemMonoTop WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zmm Bst15SemMonoTop ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zee Bst15SemMonoTop ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Pho Bst15SemMonoTop ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst15SemMonoTop TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo Bst15SemMonoTop WCR ${combo} ${algo} CENT jet jetT
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

if [[ ($sample = "All") || ($sample = "ResMonoHbb") ]]; then
    ./plotMonoX.sh Had ResMonoHbb SR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele ResMonoHbb TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Ele ResMonoHbb WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Pho ResMonoHbb ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo ResMonoHbb TopCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Muo ResMonoHbb WCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zmm ResMonoHbb ZCR ${combo} ${algo} CENT jet jetT
    ./plotMonoX.sh Zee ResMonoHbb ZCR ${combo} ${algo} CENT jet jetT
fi

if [[ ($sample = "All") || ($sample = "MonoHbb8CMS") ]]; then
    ./plotMonoX.sh Had Bst8MonoHbbCMS SR ${combo} ${algo} CENT jet jet
fi

if [[ ($sample = "All") || ($sample = "ResMonoHbbCMS") ]]; then
    ./plotMonoX.sh Had ResMonoHbbCMS SR ${combo} ${algo} CENT jet jet
fi
