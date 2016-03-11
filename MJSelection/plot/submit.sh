sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
#    ./sub.sh Had BstMonoTop SR ${combo} ${algo} CENT
#    ./sub.sh Muo BstMonoTop TopCR ${combo} ${algo} CENT
#    ./sub.sh Muo BstMonoTop WCR ${combo} ${algo} CENT
    ./sub.sh Muo BstMonoTop minusTau32 ${combo} ${algo} CENT
    ./sub.sh Muo BstMonoTop minusBtag ${combo} ${algo} CENT
    ./sub.sh Muo BstMonoTop minusMass ${combo} ${algo} CENT
#    ./sub.sh Ele BstMonoTop TopCR ${combo} ${algo} CENT
#    ./sub.sh Ele BstMonoTop WCR ${combo} ${algo} CENT
#    ./sub.sh Zmm BstMonoTop ZCR ${combo} ${algo} CENT
#    ./sub.sh Zee BstMonoTop ZCR ${combo} ${algo} CENT
#    ./sub.sh Pho BstMonoTop ZCR ${combo} ${algo} CENT
#    ./sub.sh Had ResMonoTop SR ${combo} ${algo} CENT
#    ./sub.sh Muo ResMonoTop TopCR ${combo} ${algo} CENT
#    ./sub.sh Muo ResMonoTop WCR ${combo} ${algo} CENT
#    ./sub.sh Zmm ResMonoTop ZCR ${combo} ${algo} CENT
#    ./sub.sh Ele ResMonoTop TopCR ${combo} ${algo} CENT
#    ./sub.sh Ele ResMonoTop WCR ${combo} ${algo} CENT
#    ./sub.sh Zee ResMonoTop ZCR ${combo} ${algo} CENT
#    ./sub.sh Pho ResMonoTop ZCR ${combo} ${algo} CENT
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoHbb") ]]; then
    ./sub.sh Had BstMonoHbb SR ${combo} ${algo} CENT
    ./sub.sh Muo BstMonoHbb TopCR ${combo} ${algo} CENT
    ./sub.sh Muo BstMonoHbb WCR ${combo} ${algo} CENT
    ./sub.sh Zmm BstMonoHbb ZCR ${combo} ${algo} CENT
    ./sub.sh Pho BstMonoHbb ZCR ${combo} ${algo} CENT
    ./sub.sh Had ResMonoHbb SR ${combo} ${algo} CENT
    ./sub.sh Muo ResMonoHbb TopCR ${combo} ${algo} CENT
    ./sub.sh Muo ResMonoHbb WCR ${combo} ${algo} CENT
    ./sub.sh Zmm ResMonoHbb ZCR ${combo} ${algo} CENT
    ./sub.sh Pho ResMonoHbb ZCR ${combo} ${algo} CENT
fi
if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoZbb") ]]; then  
    ./sub.sh Had BstMonoZbb SR ${combo} ${algo} CENT
    ./sub.sh Muo BstMonoZbb TopCR ${combo} ${algo} CENT
    ./sub.sh Muo BstMonoZbb WCR ${combo} ${algo} CENT
    ./sub.sh Zmm BstMonoZbb ZCR ${combo} ${algo} CENT
    ./sub.sh Pho BstMonoZbb ZCR ${combo} ${algo} CENT
    ./sub.sh Had ResMonoZbb SR ${combo} ${algo} CENT
    ./sub.sh Muo ResMonoZbb TopCR ${combo} ${algo} CENT
    ./sub.sh Muo ResMonoZbb WCR ${combo} ${algo} CENT
    ./sub.sh Zmm ResMonoZbb ZCR ${combo} ${algo} CENT
    ./sub.sh Pho ResMonoZbb ZCR ${combo} ${algo} CENT
fi