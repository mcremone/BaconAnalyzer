# HiggsTagger
ROOT TMVA based Higgs Tagger

In order to run, you need to have ROOT installed. At PSI you can do 
cd /swshare/ROOT/root_v5.34.18_slc6_amd64_py26_pythia6; export LD_LIBRARY_PATH=/swshare/ROOT/pythia6/pythia6:; source bin/thisroot.sh; cd -

Short description of the scripts:

To run:

python tmva_training.py --file=outfilename

Parser options:

parser.add_option("-c", "--categories", dest="categories", default=False, action="store_true",
                              help="train in pt-eta categories")
                              
parser.add_option("-w", "--weight", dest="weight", default=False, action="store_true",
                              help="pt-eta reweight")
                              
parser.add_option("-g", "--gluonsplitting", dest="gluonsplitting", default=False, action="store_true",
                              help="train bb vs. gsp")
                              
parser.add_option("-C", "--charm", dest="charm", default=False, action="store_true",
                              help="train bb vs. charm") 
                              
parser.add_option("-p", "--usePT", dest="usePT", default=False, action="store_true",
                              help="use pT in training") 
                              
parser.add_option("-a", "--useALL", dest="useALL", default=False, action="store_true",
                              help="use all signal samples in training")                 
                              
parser.add_option("-f", "--file", dest="filename",
                  help="write to FILE", metavar="FILE")                      
                  
For instance:

python tmva_training.py -c -w -g --file==BBvsGSPreweighted

for training using different pt-eta categories (c), reweighted in pt-eta (w), train with gluonsplitting as background (g). file" is the name you want to use for your outfile without extensions.
You can validate the training on different files using the function
read(inDirName, file)
If you want to validate on different files in parallel:
readParallel()

If you want to run parallell training processes you can edit and use the shell script runAll.sh (obs! Then readParallel() does not work, use read(inDirName, file))

To create jet pt-eta weights and store as separate branch in training trees do:

python createEtaPtWeightHists.py:

This creates 2D histograms of pT versus eta for each sample. These are used to reweight each jet by 1/bin content of the bin the jet falls in. Same procedure as what was done for the CSV

python addWeightBranch.py:

adds a branch b_weight_etaPt to the training trees.

