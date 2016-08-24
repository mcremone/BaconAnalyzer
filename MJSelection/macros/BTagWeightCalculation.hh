#ifndef BTAGWEIGHTCALCULATION_HH
#define BTAGWEIGHTCALCULATION_HH

#include "CondFormats/BTauObjects/interface/BTagEntry.h"
#include "CondFormats/BTauObjects/interface/BTagCalibration.h"
#include "CondFormats/BTauObjects/interface/BTagCalibrationReader.h"
#include "../include/BTagCalibrationStandalone.h"

// ROOT headers
#include <TLorentzVector.h>
#include <TMath.h>
#include <TClonesArray.h>

// C++ headers 
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <cassert>

// Function Declarations
std::vector<double> SFCalculation(std::string btagScaleFactorFilename, std::string variationType, std::string wp, std::vector<double>i& jetPt, std::vector<double>& jetEta, std::vector<double>& jetFlavor);

double getBTagEventReweight(int NminBjets, std::vector<double> vJetPt, std::vector<double> vJetEta, std::vector<int> vJetFlavor, std::vector<double> vSF);

#endif
