#include <cmath>
#include <iostream>
#include <sstring>
#include <sstream>

#include "BTagWeightCalculation.hh"

std::vector<double> SFCalculation(std::string flavor, std::string btagScaleFactorFilename, std::string variationType, std::string wp, std::vector<double>i& jetPt, std::vector<double>& jetEta, std::vector<double>& jetFlavor) // measurementType = comb, incl. variationType = central, up, down. wp = L,M,T.  
// Output: A SF for a specific central/up/down value at a specific working point for a specific jet.
{
std::vector<double> vSF, vSFb, vSFlf;
for (int v = 0; v < jetPt.size(); v++)
  {
  bool isB = false;
  bool isC = false;
  bool isLF = false;
  if (abs(std::round(jetFlavor.at(v)))==5) isB = true;
  if (abs(std::round(jetFlavor.at(v)))==4) isC = true;
  if (abs(std::round(jetFlavor.at(v)))==0) isLF = true;
      
  BTagCalibration *fJetCalib = new BTagCalibration("csvv2",btagScaleFactorFilename);
  if (isB || isC)
  {
    if (wp.compare("L")==0) BTagCalibrationReader *fReader = new BTagCalibrationReader(fJetCalib, BTagEntry::OP_LOOSE, "comb", variationType); 
    if (wp.compare("M")==0) BTagCalibrationReader *fReader = new BTagCalibrationReader(fJetCalib, BTagEntry::OP_MEDIUM, "comb", variationType); 
    if (wp.compare("T")==0) BTagCalibrationReader *fReader = new BTagCalibrationReader(fJetCalib, BTagEntry::OP_TIGHT, "comb", variationType); 
  }
  else if (isLF)
  {
    if (wp.compare("L")==0) BTagCalibrationReader *fReader = new BTagCalibrationReader(fJetCalib, BTagEntry::OP_LOOSE, "incl", variationType); 
    if (wp.compare("M")==0) BTagCalibrationReader *fReader = new BTagCalibrationReader(fJetCalib, BTagEntry::OP_MEDIUM, "incl", variationType); 
    if (wp.compare("T")==0) BTagCalibrationReader *fReader = new BTagCalibrationReader(fJetCalib, BTagEntry::OP_TIGHT, "incl", variationType); 
  }

  float SF = 1., SFb=1., SFlf=1.;
  if (isB) 
  {
      if (jetPt.at(v) < 670 && fabs(jetEta.at(v)) < 2.4) 
      {
          SF = fReader->eval(BTagEntry::FLAV_B, jetEta.at(v), jetPt.at(v), 0.);
          SFb = fReader->eval(BTagEntry::FLAV_B, jetEta.at(v), jetPt.at(v), 0.);
      }
      if (fabs(jetEta.at(v)) > 2.4) 
      {
          SF = fReader->eval(BTagEntry::FLAV_B, 2.399, jetPt.at(v), 0.); // eta out of bounds safety
          SFb = fReader->eval(BTagEntry::FLAV_B, 2.399, jetPt.at(v), 0.); // eta out of bounds safety
      }
      if (jetPt.at(v) > 670) 
      {
          SF = fReader->eval(BTagEntry::FLAV_B, jetEta.at(v), 669., 0.); // pt out of bounds safety
          SFb = fReader->eval(BTagEntry::FLAV_B, jetEta.at(v), 669., 0.); // pt out of bounds safety
      }
  }
  else if (isC)
  {
      if (jetPt.at(v) < 670 && fabs(jetEta.at(v)) < 2.4) 
      {
          SF = fReader->eval(BTagEntry::FLAV_C, jetEta.at(v), jetPt.at(v), 0.);
          SFb = fReader->eval(BTagEntry::FLAV_C, jetEta.at(v), jetPt.at(v), 0.);
      }
      if (fabs(jetEta.at(v)) > 2.4) 
      {
          SF = fReader->eval(BTagEntry::FLAV_C, 2.399, jetPt.at(v), 0.); // eta out of bounds safety
          SFb = fReader->eval(BTagEntry::FLAV_C, 2.399, jetPt.at(v), 0.); // eta out of bounds safety
      }
      if (jetPt.at(v) > 670) 
      {
          SF = fReader->eval(BTagEntry::FLAV_C, jetEta.at(v), 669., 0.); // pt out of bounds safety
          SFb = fReader->eval(BTagEntry::FLAV_C, jetEta.at(v), 669., 0.); // pt out of bounds safety
      }
  }
  else if (isLF) // mistag
  {
      if (jetPt.at(v) < 1000 && fabs(jetEta.at(v)) < 2.4) 
      {
          SF = fReader->eval(BTagEntry::FLAV_UDSG, jetEta.at(v), jetPt.at(v), 0.);
          SFlf = fReader->eval(BTagEntry::FLAV_UDSG, jetEta.at(v), jetPt.at(v), 0.);
      }
      if (fabs(jetEta.at(v)) > 2.4) 
      {
          SF = fReader->eval(BTagEntry::FLAV_UDSG, 2.399, jetPt.at(v), 0.); // eta out of bounds safety
          SFlf = fReader->eval(BTagEntry::FLAV_UDSG, 2.399, jetPt.at(v), 0.); // eta out of bounds safety
      }
      if (jetPt.at(v) > 1000) 
      {
          SF = fReader->eval(BTagEntry::FLAV_UDSG, jetEta.at(v), 999.., 0.); // pt out of bounds safety
          SFlf = fReader->eval(BTagEntry::FLAV_UDSG, jetEta.at(v), 999.., 0.); // pt out of bounds safety
      }
  }
    vSF.push_back(SF);
    vSFlf.push_back(SFlf);
    vSFb.push_back(SFb);
  }
  if(flavor.compare("Bs")==0) return vSFb;  
  if(flavor.compare("Ms")==0) return vSFlf;
  return vSF;
}

double getBTagEventReweight(int NminBjets, std::vector<double> vJetPt, std::vector<double> vJetEta, std::vector<int> vJetFlavor, std::vector<double> vSF)
// Input: vectors of Pt, Eta, Flavor, SF for 4 jets and NminBjets requirement.
// Output: BtagEventWeight
{

  if(vJetPt.size()<4) return 1;
  
  float mcTag = 1.;
  float mcNoTag = 0.;
  float dataTag = 1.;
  float dataNoTag = 0.;
  
  float mcProd_0 = 1.;
  float dataProd_0 = 1.;
  
  float mcProd_1 = 1.;
  float dataProd_1 = 1.;

  float mcSum = 0.;
  float dataSum = 0.;
 
  float wtbtag;


  std::vector<float> bjet_ptbin_eff, cjet_ptbin_eff, ljet_ptbin_eff;
  // calculation done in all hadronic ttbar (powheg)
  bjet_ptbin_eff.push_back(0.60592);    cjet_ptbin_eff.push_back(0.122067);   ljet_ptbin_eff.push_back(0.0149924); 
  bjet_ptbin_eff.push_back(0.634613);   cjet_ptbin_eff.push_back(0.119659);   ljet_ptbin_eff.push_back(0.0122088);
  bjet_ptbin_eff.push_back(0.645663);   cjet_ptbin_eff.push_back(0.123723);   ljet_ptbin_eff.push_back(0.0116547);
  bjet_ptbin_eff.push_back(0.646712);   cjet_ptbin_eff.push_back(0.132141);   ljet_ptbin_eff.push_back(0.0116757);
  bjet_ptbin_eff.push_back(0.649283);   cjet_ptbin_eff.push_back(0.143654);   ljet_ptbin_eff.push_back(0.0151652);
  bjet_ptbin_eff.push_back(0.621973);   cjet_ptbin_eff.push_back(0.143127);   ljet_ptbin_eff.push_back(0.0165696);
  bjet_ptbin_eff.push_back(0.554093);   cjet_ptbin_eff.push_back(0.133581);   ljet_ptbin_eff.push_back(0.0200991);
  
  std::vector<float> ptbinlow, ptbinhigh;
  ptbinlow.push_back(30);  ptbinhigh.push_back(50);
  ptbinlow.push_back(50);  ptbinhigh.push_back(70);
  ptbinlow.push_back(70);  ptbinhigh.push_back(100);
  ptbinlow.push_back(100); ptbinhigh.push_back(140);
  ptbinlow.push_back(140); ptbinhigh.push_back(200);
  ptbinlow.push_back(200); ptbinhigh.push_back(300);
  ptbinlow.push_back(300); ptbinhigh.push_back(670);
   
  for(unsigned int ij=0; ij<vJetPt.size(); ++ij)
  {
    for(unsigned int ipt=0; ipt<ptbinhigh.size(); ++ipt)
    {
        if (vJetPt[ij] > 670)
        {
        if(vJetFlavor[ij] == 5)    { mcTag  = bjet_ptbin_eff[ipt]; mcNoTag  = (1 - bjet_ptbin_eff[ipt]); dataTag  = bjet_ptbin_eff[ipt]*SF[ij]; dataNoTag  = (1 - bjet_ptbin_eff[ipt]*SF[ij]); } 
        else if(vJetFlavor[ij] == 4) { mcTag  = cjet_ptbin_eff[ipt]; mcNoTag  = (1 - cjet_ptbin_eff[ipt]); dataTag  = cjet_ptbin_eff[ipt]*SF[ij]; dataNoTag  = (1 - cjet_ptbin_eff[ipt]*SF[ij]);} 
        else if(vJetFlavor[ij] == 0)   { mcTag  = ljet_ptbin_eff[ipt]; mcNoTag  = (1 - ljet_ptbin_eff[ipt]); dataTag  = ljet_ptbin_eff[ipt]*SF[ij]; dataNoTag  = (1 - ljet_ptbin_eff[ipt]*SF[ij]); }   
        }
        if(vJetPt[ij] > ptbinlow[ipt] && vJetPt[ij] <= ptbinhigh[ipt])
        {
        if(vJetFlavor[ij] == 5)     {   mcTag  = bjet_ptbin_eff[ipt]; mcNoTag  = (1 - bjet_ptbin_eff[ipt]); dataTag  = bjet_ptbin_eff[ipt]*SF[ij]; dataNoTag  = (1 - bjet_ptbin_eff[ipt]*SF[ij]);} 
        else if (vJetFlavor[ij] == 4) { mcTag  = cjet_ptbin_eff[ipt]; mcNoTag  = (1 - cjet_ptbin_eff[ipt]); dataTag  = cjet_ptbin_eff[ipt]*SF[ij]; dataNoTag  = (1 - cjet_ptbin_eff[ipt]*SF[ij]);} 
        else if (vJetFlavor[ij] == 0) { mcTag  = ljet_ptbin_eff[ipt]; mcNoTag  = (1 - ljet_ptbin_eff[ipt]); dataTag  = ljet_ptbin_eff[ipt]*SF[ij]; dataNoTag  = (1 - ljet_ptbin_eff[ipt]*SF[ij]);}
        }
    }

    mcProd_0   *= mcNoTag;
    dataProd_0 *= dataNoTag;
    
    
    for(unsigned int ik=0; ik < vJetPt.size(); ++ik)
    {
       for(unsigned int jpt=0; jpt<ptbinhigh.size(); ++jpt)
        {
        if(ik == ij) continue;
        if(vJetPt[ik] > 670)
        {
            if(vJetFlavor[ik] == 5)    {    mcNoTag = (1 - bjet_ptbin_eff[jpt]); dataNoTag  = (1 - bjet_ptbin_eff[jpt]*SF[ik]); }
            else if(vJetFlavor[ik] == 4){ mcNoTag = (1 - cjet_ptbin_eff[jpt]); dataNoTag  = (1 - cjet_ptbin_eff[jpt]*SF[ik]);} 
            else if(vJetFlavor[ik] == 0){ mcNoTag = (1 - ljet_ptbin_eff[jpt]); dataNoTag  = (1 - ljet_ptbin_eff[jpt]*SF[ik]);}
        }
        if(vJetPt[ik] > ptbinlow[jpt] && vJetPt[ik] <= ptbinhigh[jpt])
        {
            if (vJetFlavor[ik] == 5)   {    mcNoTag  = (1 - bjet_ptbin_eff[jpt]);  dataNoTag  = (1 - bjet_ptbin_eff[jpt]*SF[ik]);} 
            else if(vJetFlavor[ik] == 4) {  mcNoTag  = (1 - cjet_ptbin_eff[jpt]);  dataNoTag  = (1 - cjet_ptbin_eff[jpt]*SF[ik]);} 
            else if(vJetFlavor[ik] == 0) {  mcNoTag  = (1 - ljet_ptbin_eff[jpt]);  dataNoTag  = (1 - ljet_ptbin_eff[jpt]*SF[ik]);}
        }
       }
       mcProd_1   *= mcNoTag;
       dataProd_1 *= dataNoTag;
    }
    
    mcSum   += mcTag*mcProd_1;
    dataSum += dataTag*dataProd_1;       
  }

  
  // re-weighting for events with 0 jets
  if(NminBjets==0){   
    return wtbtag = dataProd_0/mcProd_0;

    //re-weighting for events with exactly 1 b-tag jet
  } else if(NminBjets==-1){
    return wtbtag = dataSum/mcSum;
    
    // re-weighting for events with 1 or more b-tag jets
  } else if(NminBjets==1){
    return wtbtag = (1 - dataProd_0)/(1 - mcProd_0);

    // re-weighting for events with 2 or more b-tag jets
  } else if(NminBjets==2){
    return wtbtag = (1 - dataProd_0 - dataSum)/(1 - mcProd_0 - mcSum);
    
  } 
  else return 1;

}
