sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    ./plotMonoX.sh Had BstMonoTop SR ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop QCDCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop TopCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop WCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zmm BstMonoTop ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zee BstMonoTop ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Pho BstMonoTop ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo BstMonoTop TopCR ${combo} ${algo} CENT
    ./plotMonoX.sh Muo BstMonoTop WCR ${combo} ${algo} CENT
    cp -r monoxplots/* /afs/cern.ch/user/c/cmantill/www/MonoTop/MonoTop76/
fi

if [[ ($sample = "All") || ($sample = "CutFlow") ]]; then
    ./plotMonoX.sh Had BstMonoTop SR1 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR2 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR3 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR4 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR5 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR6 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR7 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR8 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR9 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR10 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR11 ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop SR12 ${combo} ${algo} CENT
    cp -r monoxplots/* /afs/cern.ch/user/c/cmantill/www/MonoTop/MonoTop76/
fi