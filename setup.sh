#!/bin/bash

#---------------------------
# Setup development packages needed for Bacon
# *NOTE* Could also pick directly from mycmssw
#--------------------------


if test -z $CMSSW_VERSION; then
  echo "[BaconAnalyzer] Need CMSSW project area setup!";
  echo
  return 0;
fi

CURRDIR=$PWD
PATCHDIR=/afs/cern.ch/work/c/cmantill/public/Bacon/BaconProduction/CMSSW_7_6_2/src
cd $CMSSW_BASE/src

cp -r ${PATCHDIR}/CommonTools ./
cp -r ${PATCHDIR}/RecoMET ./
cp -r ${PATCHDIR}/ShowerDeconstruction ./

echo
echo "[BaconAnalyzer] Setup complete!"

cd $CURRDIR

return 1;