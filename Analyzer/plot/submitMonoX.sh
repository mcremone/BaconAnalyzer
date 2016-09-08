sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop15") ]]; then
    ./plotMonoX.sh Had Bst15MonoTop SR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele Bst15MonoTop TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele Bst15MonoTop WCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zmm Bst15MonoTop ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zee Bst15MonoTop ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Pho Bst15MonoTop ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo Bst15MonoTop TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo Bst15MonoTop WCR ${combo} ${algo} CENT 
fi

if [[ ($sample = "All") || ($sample != "All" && $sample = "Bst15MonoTop") ]]; then
    ./plotMonoX.sh Had Bst15MonoTop SR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele Bst15MonoTop TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele Bst15MonoTop WCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zmm Bst15MonoTop ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zee Bst15MonoTop ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Pho Bst15MonoTop ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo Bst15MonoTop TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo Bst15MonoTop WCR ${combo} ${algo} CENT 
fi

if [[ ($sample = "All") || ($sample = "MonoHbb15") ]]; then
    ./plotMonoX.sh Had Bst15MonoHbb SR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele Bst15MonoHbb TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele Bst15MonoHbb WCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Pho Bst15MonoHbb ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo Bst15MonoHbb TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo Bst15MonoHbb WCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zmm Bst15MonoHbb ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zee Bst15MonoHbb ZCR ${combo} ${algo} CENT 
fi

if [[ ($sample = "All") || ($sample = "ResMonoHbb") ]]; then
    ./plotMonoX.sh Had ResMonoHbb SR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele ResMonoHbb TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Ele ResMonoHbb WCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Pho ResMonoHbb ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo ResMonoHbb TopCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Muo ResMonoHbb WCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zmm ResMonoHbb ZCR ${combo} ${algo} CENT 
    ./plotMonoX.sh Zee ResMonoHbb ZCR ${combo} ${algo} CENT 
fi
