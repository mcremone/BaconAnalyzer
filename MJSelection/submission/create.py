#!/bin/env python

import math
import os,sys
import ROOT
import re
import glob
import argparse
from subprocess import call, check_output
from bacon_dictionary import SAMPLES, MC_TYPES

samples = SAMPLES
mc = MC_TYPES
 
def haddFiles(channel = '', outputDir = ''):
    basedir = os.environ['CMSSW_BASE']+'/src/BaconAnalyzer/MJSelection/'
    outdir = basedir+'/submission/'+outputDir
    for esample in samples[channel]:
        print "Sample: ", esample
        #sample = esample.replace('_ext3','_')
        sample = re.sub('_ext[1-4]','',esample)
        sample = sample.replace('_ext','')
        fname = outdir+'/'+sample+'_'+mc[channel]+'.root'
        print "ROOT file", fname
        query = outdir+'/'+sample+'_*'+mc[channel]+'/ntuples/*.root'
        print "Looking at ", query
        jobfiles = glob.glob( query )
        if os.path.isfile( fname ):
            call(['rm',fname])
            call(['hadd','-k',fname]+jobfiles)
        else:
            call(['hadd','-k',fname]+jobfiles)

def haddFinal(channel = '', outputDir = ''):
    basedir = os.environ['CMSSW_BASE']+'/src/BaconAnalyzer/MJSelection/'
    outdir = basedir+'/submission/'+outputDir
    finalDir = outdir+'/Final'
#    print finalDir
    if not os.path.isdir(finalDir):
        os.makedirs(finalDir)
        print "Making ", finalDir
    jobfiles = []
    for esample in samples[channel]:
        sample = re.sub('_ext[1-4]','',esample)
        sample = sample.replace('_ext','')
        fname = finalDir+'/'+channel+'.root'
        query = outdir+'/'+sample+'*'+mc[channel]+'*_1pb_weighted.root'
        jobfiles += glob.glob(query)
    jobfiles = list(set(jobfiles)) #remove overlap
    if os.path.isfile( fname ):
        call(['rm',fname])
        call(['hadd','-k',fname]+jobfiles)
    else:
        call(['hadd','-k',fname]+jobfiles)

def submitJobs(analyzer = '', channel = '', events_per_job = 50000, outputDir = '',submit=False, queue = '1nh'):
    basedir = os.environ['CMSSW_BASE']+'/src/BaconAnalyzer/MJSelection/'
    _outdir = basedir+'/submission/'+outputDir
    samples = SAMPLES
    if not os.path.exists(_outdir): os.makedirs(_outdir)
    for sample in samples[channel]:
        outdir = _outdir+'/'+sample+'_'+mc[channel]
        if not os.path.exists(outdir): os.makedirs(outdir)
        if not os.path.exists(outdir+'/log'): os.makedirs(outdir+'/log')
        if not os.path.exists(outdir+'/ntuples'): os.makedirs(outdir+'/ntuples')
        if not os.path.exists(outdir+'/src'): os.makedirs(outdir+'/src')
        file_list = basedir+"lists/production11/"+sample+".txt"
        print "File list: ", file_list
        script = basedir+"submission/run.sh"
        logfile = outdir+"/log/"+sample+"_"+mc[channel]
        outname = outdir+"/ntuples/"+sample+"_"+mc[channel]
        srcname = outdir+"/src/"+sample+"_"+mc[channel]
        index = 0
        with open(file_list) as flist:
            for f in flist:
                fin = f.strip('\n')
                mounted_file = fin.replace("root://eoscms.cern.ch/","eos/cms")
                if os.path.getsize(mounted_file) < 200000000:
                    index += 1
                    begin_evt = 0
                    end_evt = 50000
                    cmd = ['bsub','-q',queue,'-o',logfile+'_'+str(index)+'.log','-J',sample+'_'+str(index),script,analyzer,fin,mc[channel],'none',str(begin_evt),str(end_evt),outname+'_'+str(index)+'.root']
                    os.environ['LSB_JOB_REPORT_MAIL'] = 'N'
                    #print ' '.join(cmd)
                    with open(srcname+'_'+str(index)+'.sh','w') as src_file:
                        src_file.write(' '.join(cmd))
                    if submit: call(cmd)
                else:
                    filein = ROOT.TFile.Open(fin,"read")
                    nevents = int(filein.Get("Events").GetEntries())
                    filein.Close()
                    begin=0
                    njobs = nevents/events_per_job + 1
                    for i in range (1, njobs):
                        index += 1
                        begin_evt = begin
                        end_evt = nevents/njobs * i
                        cmd = ['bsub','-q',queue,'-o',logfile+'_'+str(index)+'.log','-J',sample+'_'+str(index),script,analyzer,fin,mc[channel],'none',str(begin_evt),str(end_evt),outname+'_'+str(index)+'.root']
                        os.environ['LSB_JOB_REPORT_MAIL'] = 'N'
                        #print ' '.join(cmd)
                        with open(srcname+'_'+str(index)+'.sh','w') as src_file:
                            src_file.write(' '.join(cmd))
                        begin = end_evt + 1
                        if submit: call(cmd)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-a', '--analyzer', help = 'Analyzer binary. Can be runRazor, runMonojet_split, ...')
    parser.add_argument('-d', '--directory', help = 'Output directory\'s name', required = True)
    parser.add_argument('-c', '--channel', help = 'Input channel')
    parser.add_argument('--everything', action='store_true', help = 'Run on all channels')
    parser.add_argument('-n', '--nevents', default = 50000, help = 'Number of events per job (used for big ntuples)', type = int)
    parser.add_argument('--dryRun', action='store_true', help = 'No submit') 
    parser.add_argument('--submit', action='store_true', help = 'Run submission jobs')
    parser.add_argument('--hadd', action='store_true', help = 'Hadd files')
    parser.add_argument('--haddFinal', action='store_true', help = 'Hadd files')
    parser.add_argument('-q','--queue', default = '8nm', help = 'Queue to submit')
    args = parser.parse_args()

    wetRun=True
    wetRun=(not args.dryRun)

    # Check if EOS is mounted
    if not os.path.isdir('eos/cms/store'):
        sys.exit("Please mount EOS under ./eos before using this tool.")

    if not args.hadd and not args.submit and not args.haddFinal:
        sys.exit("What on the earth do you want?")
    if args.submit and not args.analyzer:
        sys.exit("-a ANALYZER required (runMonojet_split, ...)")
    if args.submit or args.hadd or args.haddFinal:
        if not args.everything:
            if not args.channel:
                sys.exit("-c CHANNEL required (QCD, DYHF, DYLF, ST, ...)")
            else:
                print "Input channel: ", args.channel
                if args.submit:
                    submitJobs(args.analyzer, args.channel, args.nevents, args.directory, wetRun, args.queue)
                elif args.hadd:
                    haddFiles(args.channel, args.directory)
                elif args.haddFinal:
                    haddFinal(args.channel, args.directory)
        elif args.everything: 
            for channel in samples:
                if args.submit:
                    submitJobs(args.analyzer, channel, args.nevents, args.directory, wetRun, args.queue)
                elif args.hadd:
                    haddFiles(channel, args.directory)
                elif args.haddFinal:
                    haddFinal(channel, args.directory)

