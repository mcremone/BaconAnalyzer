sample=$1
combo=$2
algo=$3

if [[ ($sample = "All") || ($sample != "All" && $sample = "MonoTop") ]]; then
    ./plotMonoX.sh Had BstMonoTop SR ${combo} ${algo} CENT
    ./plotMonoX.sh Had BstMonoTop QCDCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop TopCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop WCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop WHFCR ${combo} ${algo} CENT
    ./plotMonoX.sh Ele BstMonoTop WLFCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zmm BstMonoTop ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zmm BstMonoTop ZHFCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zmm BstMonoTop ZLFCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zee BstMonoTop ZCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zee BstMonoTop ZHFCR ${combo} ${algo} CENT
    ./plotMonoX.sh Zee BstMonoTop ZLFCR ${combo} ${algo} CENT
    ./plotMonoX.sh Pho BstMonoTop ZCR ${combo} ${algo} CENT
    cp -r MonoXPlots/* /afs/cern.ch/user/c/cmantill/www/MonoTop/MonoTop76/
fi
