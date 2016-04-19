# MJSelection

 * Depends on BaconAna and BaconProd packages
 * Place package in `$CMSSW_BASE/src` area

Setup
-------------
 * Setup $CMSSW_BASE area
 * Setup BaconProd, BaconAna
	
    git clone https://github.com/cmantill/BaconProd.git -b singleb --single-branch

    git clone https://github.com/cmantill/BaconAna.git -b singleb --single-branch

 * Setup BaconAnalyzer, Development Packages

    git clone https://github.com/mcremone/BaconAnalyzer.git 

    git checkout CMSSW_7_6_X
    
    source setup.sh

 * Compile

   scram b -j 10

Define Analysis
----------
Define $YOURANALYSIS in bin/run$YOURANALYSIS.cpp - don't forget to include it in bin/BuildFile.xml

Modify it according to your analysis preselection

Triggers are listed in 	    
	 `/src/BaconAna/DataFormats/data/HLTFile_25ns`	

Baconbits production
-----------
1) Define list of samples on production/submit$YOURANALYSIS.sh along with xsec

2) Make output directory

   mkdir $YOURANALYSISbits

3) Make configuration files for the $OPTION samples (or All)

   cd production/
   
   ./submit$YOURANALYSIS.sh $OPTION

4) After compiling, submit jobs to Batch as 
   ./submir$YOURANALYSIS.sh All --monitor sub

