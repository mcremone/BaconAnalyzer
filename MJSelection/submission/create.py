#!/bin/env python

import math
import os,sys
import ROOT
import glob
import argparse

def submitJobs(analyzer = '', dataset_type = 'mc', channel = '', events_per_job = 50000, outputDir = ''):
    queue = '8nm'
    basedir = os.environ['CMSSW_BASE']+'/src/BaconAnalyzer/MJSelection/'
    outdir = basedir+'/submission/'+outputDir
    if not os.path.exists(outdir): os.makedirs(outdir)
    outdir = outdir+'/'+channel
    if not os.path.exists(outdir): os.makedirs(outdir)
    if not os.path.exists(outdir+'/log'): os.makedirs(outdir+'/log')
    if not os.path.exists(outdir+'/ntuples'): os.makedirs(outdir+'/ntuples')
    if not os.path.exists(outdir+'/src'): os.makedirs(outdir+'/src')
    file_list = basedir+"lists/production11/"+channel+".txt"
    script = basedir+"submission/run.sh"
    logfile = outdir+"/log/"+channel
    outname = outdir+"/ntuples/"+channel
    srcname = outdir+"/src/"+channel
    index = 0
    with open(file_list) as flist:
        for f in flist:
            fin = f.strip('\n')
            mounted_file = fin.replace("root://eoscms.cern.ch/","eos/cms")
            if os.path.getsize(mounted_file) < 200000000:
                index += 1
                begin_evt = 0
                end_evt = 50000
                cmd = ['bsub','-q',queue,'-o',logfile+'_'+str(index)+'.log','-J',channel+'_'+str(index),script,analyzer,fin,dataset_type,'none',str(begin_evt),str(end_evt),outname+'_'+str(index)+'.root']
                os.environ['LSB_JOB_REPORT_MAIL'] = 'N'
                print ' '.join(cmd)
                with open(srcname+'_'+str(index)+'.sh','w') as src_file:
                    src_file.write(' '.join(cmd))
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
                    cmd = ['bsub','-q',queue,'-o',logfile+'_'+str(index)+'.log','-J',channel+'_'+str(index),script,analyzer,fin,dataset_type,'none',str(begin_evt),str(end_evt),outname+'_'+str(index)+'.root']
                    os.environ['LSB_JOB_REPORT_MAIL'] = 'N'
                    print ' '.join(cmd)
                    with open(srcname+'_'+str(index)+'.sh','w') as src_file:
                        src_file.write(' '.join(cmd))
                    begin = end_evt + 1

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-a', '--analyzer', help = 'Analyzer binary. Can be runRazor, runMonojetSplit, ...', required = True)
    parser.add_argument('-t', '--datatype', default = 'mc', choices = ['data','mc','mctt','mcwplushf','mcwpluslf','mcdyplushf','mcdypluslf','mcgplushf','mcgpluslf','mczplushf','mczpluslf'], help = 'Dataset type. Can be data, mc, mctt, mcwplushf, mcwpluslf, mcdyplushf, mcdypluslf, mczplushf, ...')
    parser.add_argument('-d', '--directory', help = 'Output directory\'s name', required = True)
    parser.add_argument('-c', '--channel', help = 'Input channel', required = True)
    parser.add_argument('-n', '--nevents', default = 50000, help = 'Number of events per job (used for big ntuples)', type = int)
    
    args = parser.parse_args()
    print "Analyzer: ", args.analyzer
    print "Input channel: ", args.channel
   

    # Check if EOS is mounted
    if not os.path.isdir('eos/cms/store'):
        sys.exit("Please mount EOS under ./eos before using this tool.")
    
    submitJobs(args.analyzer, args.datatype, args.channel, args.nevents, args.directory)
