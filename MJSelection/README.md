# MJSelection

 * Depends on BaconAna and BaconProd packages
 * Place BaconAnalyzer in `$CMSSW_BASE/src` area

Setup
-------------
 * Setup $CMSSW_BASE area
 * Setup BaconProd, BaconAna
	
    `git clone https://github.com/cmantill/BaconProd.git -b singleb --single-branch`

    `git clone https://github.com/cmantill/BaconAna.git -b singleb --single-branch`

 * Setup BaconAnalyzer, Development Packages

    `git clone https://github.com/mcremone/BaconAnalyzer.git`

    `cd BaconAnalyzer`

    `git checkout CMSSW_7_6_X`
    
    `source setup.sh`

 * Compile

   scram b -j 10

Define Analysis
----------
Define $YOURANALYSIS in bin/run$YOURANALYSIS.cpp - don't forget to include it in bin/BuildFile.xml

Modify it according to your analysis preselection.

Triggers are listed in 	    
	 `/src/BaconAna/DataFormats/data/HLTFile_25ns`	

After modifications compile before running.

Baconbits production
-----------
1) Define list of samples on production/submit$YOURANALYSIS.sh along with xsec

2) Make output directory

   `mkdir $YOURANALYSISbits`

3) Make configuration files for the $OPTION samples (or All)

   `cd production/`
   
   `./submit$YOURANALYSIS.sh $OPTION`

4) After compiling, submit jobs to Batch as 
   `./submit$YOURANALYSIS.sh $OPTION --monitor sub`

5) When production is done combine files using
   `./combine$YOURANALYSIS.sh $OPTION`

Baconbits are stored in $YOURANALYSISbits/*.root

Plot tools for preselection
----------
plot$YOURANALYSIS.C can produce Data/MC plots and implement additional selection requirements

Declare variables and preselection functions in macros/$YOURANALYSISBitsLoader.*

Modify list of input baconbits in plot$YOURANALYSIS.C and input options(jet, systematics, etc.)

       e.g. `plotMonoX.C ONLY PUPPI CENT`
