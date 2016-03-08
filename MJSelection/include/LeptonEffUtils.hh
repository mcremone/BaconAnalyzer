double getLooseMuonSF(const double pt, const double eta);
double getTightMuonSF(const double pt, const double eta);

double getMuonTriggerDataEff(const double pt, const double eta, const unsigned int runNum=0);
double getMuonTriggerMCEff(const double pt, const double eta);
double getMuonTriggerSF(const double pt, const double eta);

double getVetoEleSF(const double pt, const double eta);
double getTightEleSF(const double pt, const double eta);

double getEleTriggerDataEff(const double pt, const double eta);
double getEleTriggerMCEff(const double pt, const double eta);
double getEleTriggerSF(const double pt, const double eta);


//--------------------------------------------------------------------------------------
double getLooseMuonSF(const double pt, const double eta)
{
  if(fabs(eta)<0.9) {
    if     (pt >  10 && pt <  15) { return 1.004; }
    else if(pt >  15 && pt <  20) { return 0.977; }
    else if(pt >  20 && pt <  25) { return 0.987; }
    else if(pt>   25 && pt <  30) { return 0.997; }
    else if(pt >  30 && pt <  40) { return 0.999; }
    else if(pt >  40 && pt <  50) { return 1.000; }
    else if(pt >  50 && pt <  60) { return 1.000; }
    else if(pt >  60 && pt <  80) { return 0.999; }
    else if(pt >  80 && pt < 100) { return 0.995; }
    else if(pt > 100)             { return 0.998; }

  } else if(fabs(eta)<1.2) {
    if     (pt >  10 && pt <  15) { return 0.968; }
    else if(pt >  15 && pt <  20) { return 0.976; }
    else if(pt >  20 && pt <  25) { return 0.989; }
    else if(pt>   25 && pt <  30) { return 1.002; }
    else if(pt >  30 && pt <  40) { return 1.000; }
    else if(pt >  40 && pt <  50) { return 1.000; }
    else if(pt >  50 && pt <  60) { return 1.001; }
    else if(pt >  60 && pt <  80) { return 1.004; }
    else if(pt >  80 && pt < 100) { return 0.993; }
    else if(pt > 100)             { return 1.000; }

  } else if(fabs(eta)<2.1) {
    if     (pt >  10 && pt <  15) { return 0.993; }
    else if(pt >  15 && pt <  20) { return 0.991; }
    else if(pt >  20 && pt <  25) { return 0.997; }
    else if(pt>   25 && pt <  30) { return 1.001; }
    else if(pt >  30 && pt <  40) { return 1.001; }
    else if(pt >  40 && pt <  50) { return 1.000; }
    else if(pt >  50 && pt <  60) { return 0.999; }
    else if(pt >  60 && pt <  80) { return 0.997; }
    else if(pt >  80 && pt < 100) { return 1.007; }
    else if(pt > 100)             { return 0.998; }

  } else if(fabs(eta)<2.4) {
    if     (pt >  10 && pt <  15) { return 0.961; }
    else if(pt >  15 && pt <  20) { return 0.986; }
    else if(pt >  20 && pt <  25) { return 0.982; }
    else if(pt>   25 && pt <  30) { return 1.004; }
    else if(pt >  30 && pt <  40) { return 0.998; }
    else if(pt >  40 && pt <  50) { return 1.000; }
    else if(pt >  50 && pt <  60) { return 0.999; }
    else if(pt >  60 && pt <  80) { return 1.002; }
    else if(pt >  80 && pt < 100) { return 1.001; }
    else if(pt > 100)             { return 1.007; }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getTightMuonSF(const double pt, const double eta)
{
  if(fabs(eta)<0.9) {
    if     (pt >  10 && pt <  15) { return 1.004; }
    else if(pt >  15 && pt <  20) { return 0.960; }
    else if(pt >  20 && pt <  25) { return 0.977; }
    else if(pt>   25 && pt <  30) { return 0.985; }
    else if(pt >  30 && pt <  40) { return 0.988; }
    else if(pt >  40 && pt <  50) { return 0.991; }
    else if(pt >  50 && pt <  60) { return 0.987; }
    else if(pt >  60 && pt <  80) { return 0.987; }
    else if(pt >  80 && pt < 100) { return 0.982; }
    else if(pt > 100)             { return 0.981; }

  } else if(fabs(eta)<1.2) {
    if     (pt >  10 && pt <  15) { return 0.974; }
    else if(pt >  15 && pt <  20) { return 0.984; }
    else if(pt >  20 && pt <  25) { return 0.982; }
    else if(pt>   25 && pt <  30) { return 0.984; }
    else if(pt >  30 && pt <  40) { return 0.987; }
    else if(pt >  40 && pt <  50) { return 0.986; }
    else if(pt >  50 && pt <  60) { return 0.985; }
    else if(pt >  60 && pt <  80) { return 0.985; }
    else if(pt >  80 && pt < 100) { return 0.977; }
    else if(pt > 100)             { return 0.971; }

  } else if(fabs(eta)<2.1) {
    if     (pt >  10 && pt <  15) { return 0.962; }
    else if(pt >  15 && pt <  20) { return 0.985; }
    else if(pt >  20 && pt <  25) { return 0.982; }
    else if(pt>   25 && pt <  30) { return 0.988; }
    else if(pt >  30 && pt <  40) { return 0.994; }
    else if(pt >  40 && pt <  50) { return 0.993; }
    else if(pt >  50 && pt <  60) { return 0.993; }
    else if(pt >  60 && pt <  80) { return 0.994; }
    else if(pt >  80 && pt < 100) { return 0.988; }
    else if(pt > 100)             { return 0.988; }

  } else if(fabs(eta)<2.4) {
    if     (pt >  10 && pt <  15) { return 0.908; }
    else if(pt >  15 && pt <  20) { return 0.946; }
    else if(pt >  20 && pt <  25) { return 0.957; }
    else if(pt>   25 && pt <  30) { return 0.972; }
    else if(pt >  30 && pt <  40) { return 0.976; }
    else if(pt >  40 && pt <  50) { return 0.981; }
    else if(pt >  50 && pt <  60) { return 0.978; }
    else if(pt >  60 && pt <  80) { return 0.975; }
    else if(pt >  80 && pt < 100) { return 0.982; }
    else if(pt > 100)             { return 0.973; }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getMuonTriggerDataEff(const double pt, const double eta, const unsigned int runNum)
{
  // Trigger efficiencies are computed for up to Run 257819 and for after Run 257819
  // In Run2015D, there is ~0.393/fb up to 257819

  if(runNum==0) {
    //
    // Take weighted average of data efficiencies of the two run eras weighted by relative 
    // integrated luminosity
    //
    double total_lumi = 2.246;
    double lumi1      = 0.393;
    double frac       = lumi1/total_lumi;

    double data_eff1 = getMuonTriggerDataEff(pt, eta, 1);
    double data_eff2 = getMuonTriggerDataEff(pt, eta, 999999);

    return (frac*data_eff1 + (1.-frac)*data_eff2);

  } else if(runNum <=257819) {
    if(fabs(eta) < 0.9) {
      if     (pt > 22 && pt < 25) { return 0.775; }
      else if(pt > 25 && pt < 30) { return 0.842; }
      else if(pt > 30 && pt < 40) { return 0.905; }
      else if(pt > 40 && pt < 50) { return 0.938; }
      else if(pt > 50 && pt < 60) { return 0.950; }
      else if(pt > 60 && pt <120) { return 0.944; }
      else if(pt >120)            { return 0.951; }

    } else if(fabs(eta) < 1.2) {
      if     (pt > 22 && pt < 25) { return 0.803; }
      else if(pt > 25 && pt < 30) { return 0.869; }
      else if(pt > 30 && pt < 40) { return 0.901; }
      else if(pt > 40 && pt < 50) { return 0.929; }
      else if(pt > 50 && pt < 60) { return 0.934; }
      else if(pt > 60 && pt <120) { return 0.933; }
      else if(pt >120)            { return 0.905; }

    } else if(fabs(eta) < 2.1) {
      if     (pt > 22 && pt < 25) { return 0.855; }
      else if(pt > 25 && pt < 30) { return 0.887; }
      else if(pt > 30 && pt < 40) { return 0.907; }
      else if(pt > 40 && pt < 50) { return 0.926; }
      else if(pt > 50 && pt < 60) { return 0.931; }
      else if(pt > 60 && pt <120) { return 0.932; }
      else if(pt >120)            { return 0.931; }

    } else if(fabs(eta) < 2.4) {
      if     (pt > 22 && pt < 25) { return 0.772; }
      else if(pt > 25 && pt < 30) { return 0.826; }
      else if(pt > 30 && pt < 40) { return 0.860; }
      else if(pt > 40 && pt < 50) { return 0.887; }
      else if(pt > 50 && pt < 60) { return 0.888; }
      else if(pt > 60 && pt <120) { return 0.891; }
      else if(pt >120)            { return 0.836; }
    }
  } else {
    if(fabs(eta) < 0.9) {
      if     (pt > 22 && pt < 25) { return 0.914; }
      else if(pt > 25 && pt < 30) { return 0.935; }
      else if(pt > 30 && pt < 40) { return 0.951; }
      else if(pt > 40 && pt < 50) { return 0.960; }
      else if(pt > 50 && pt < 60) { return 0.961; }
      else if(pt > 60 && pt <120) { return 0.964; }
      else if(pt >120)            { return 0.956; }

    } else if(fabs(eta) < 1.2) {
      if     (pt > 22 && pt < 25) { return 0.913; }
      else if(pt > 25 && pt < 30) { return 0.929; }
      else if(pt > 30 && pt < 40) { return 0.939; }
      else if(pt > 40 && pt < 50) { return 0.944; }
      else if(pt > 50 && pt < 60) { return 0.944; }
      else if(pt > 60 && pt <120) { return 0.941; }
      else if(pt >120)            { return 0.937; }

    } else if(fabs(eta) < 2.1) {
      if     (pt > 22 && pt < 25) { return 0.902; }
      else if(pt > 25 && pt < 30) { return 0.916; }
      else if(pt > 30 && pt < 40) { return 0.930; }
      else if(pt > 40 && pt < 50) { return 0.941; }
      else if(pt > 50 && pt < 60) { return 0.944; }
      else if(pt > 60 && pt <120) { return 0.944; }
      else if(pt >120)            { return 0.936; }

    } else if(fabs(eta) < 2.4) {
      if     (pt > 22 && pt < 25) { return 0.819; }
      else if(pt > 25 && pt < 30) { return 0.855; }
      else if(pt > 30 && pt < 40) { return 0.883; }
      else if(pt > 40 && pt < 50) { return 0.897; }
      else if(pt > 50 && pt < 60) { return 0.899; }
      else if(pt > 60 && pt <120) { return 0.898; }
      else if(pt >120)            { return 0.881; }
    }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getMuonTriggerMCEff(const double pt, const double eta)
{
  if(fabs(eta) < 0.9) {
    if     (pt > 22 && pt < 25) { return 0.891; }
    else if(pt > 25 && pt < 30) { return 0.916; }
    else if(pt > 30 && pt < 40) { return 0.943; }
    else if(pt > 40 && pt < 50) { return 0.960; }
    else if(pt > 50 && pt < 60) { return 0.964; }
    else if(pt > 60 && pt <120) { return 0.968; }
    else if(pt >120)            { return 0.957; }

  } else if(fabs(eta) < 1.2) {
    if     (pt > 22 && pt < 25) { return 0.880; }
    else if(pt > 25 && pt < 30) { return 0.897; }
    else if(pt > 30 && pt < 40) { return 0.929; }
    else if(pt > 40 && pt < 50) { return 0.945; }
    else if(pt > 50 && pt < 60) { return 0.948; }
    else if(pt > 60 && pt <120) { return 0.949; }
    else if(pt >120)            { return 0.939; }

  } else if(fabs(eta) < 2.1) {
    if     (pt > 22 && pt < 25) { return 0.887; }
    else if(pt > 25 && pt < 30) { return 0.911; }
    else if(pt > 30 && pt < 40) { return 0.932; }
    else if(pt > 40 && pt < 50) { return 0.950; }
    else if(pt > 50 && pt < 60) { return 0.952; }
    else if(pt > 60 && pt <120) { return 0.953; }
    else if(pt >120)            { return 0.940; }

  } else if(fabs(eta) < 2.4) {
    if     (pt > 22 && pt < 25) { return 0.811; }
    else if(pt > 25 && pt < 30) { return 0.831; }
    else if(pt > 30 && pt < 40) { return 0.863; }
    else if(pt > 40 && pt < 50) { return 0.889; }
    else if(pt > 50 && pt < 60) { return 0.886; }
    else if(pt > 60 && pt <120) { return 0.888; }
    else if(pt >120)            { return 0.890; }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getMuonTriggerSF(const double pt, const double eta)
{
  double data_eff = getMuonTriggerDataEff(pt, eta, 0);
  double mc_eff   = getMuonTriggerMCEff(pt, eta);

  return data_eff / mc_eff;
}

//--------------------------------------------------------------------------------------
double getVetoEleSF(const double pt, const double eta)
{
  if(fabs(eta)<1.4) {
    if     (pt > 10 && pt < 20) { return 1.001; }
    else if(pt > 20 && pt < 30) { return 0.985; }
    else if(pt > 30 && pt < 40) { return 0.993; }
    else if(pt > 40 && pt < 50) { return 0.993; }
    else if(pt > 50 && pt < 60) { return 0.996; }
    else if(pt > 60 && pt < 80) { return 0.993; }
    else if(pt > 80)            { return 0.991; }

  } else if(fabs(eta)<1.6) {
    if     (pt > 10 && pt < 20) { return 1.164; }
    else if(pt > 20 && pt < 30) { return 0.989; }
    else if(pt > 30 && pt < 40) { return 0.993; }
    else if(pt > 40 && pt < 50) { return 0.998; }
    else if(pt > 50 && pt < 60) { return 1.001; }
    else if(pt > 60 && pt < 80) { return 1.044; }
    else if(pt > 80)            { return 1.001; }

  } else if(fabs(eta)<2.1) {
    if     (pt > 10 && pt < 20) { return 1.007; }
    else if(pt > 20 && pt < 30) { return 0.987; }
    else if(pt > 30 && pt < 40) { return 1.010; }
    else if(pt > 40 && pt < 50) { return 1.018; }
    else if(pt > 50 && pt < 60) { return 1.014; }
    else if(pt > 60 && pt < 80) { return 1.004; }
    else if(pt > 80)            { return 1.005; }

  } else if(fabs(eta)<2.4) {
    if     (pt > 10 && pt < 20) { return 1.030; }
    else if(pt > 20 && pt < 30) { return 0.995; }
    else if(pt > 30 && pt < 40) { return 1.006; }
    else if(pt > 40 && pt < 50) { return 1.006; }
    else if(pt > 50 && pt < 60) { return 1.027; }
    else if(pt > 60 && pt < 80) { return 1.004; }
    else if(pt > 80)            { return 0.982; }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getTightEleSF(const double pt, const double eta)
{
  if(fabs(eta)<1.4) {
    if     (pt > 10 && pt < 20) { return 1.039; }
    else if(pt > 20 && pt < 30) { return 0.965; }
    else if(pt > 30 && pt < 40) { return 0.976; }
    else if(pt > 40 && pt < 50) { return 0.968; }
    else if(pt > 50 && pt < 60) { return 0.979; }
    else if(pt > 60 && pt < 80) { return 0.968; }
    else if(pt > 80)            { return 0.975; }
    
  } else if(fabs(eta)<1.6) {
    if     (pt > 10 && pt < 20) { return 1.143; }
    else if(pt > 20 && pt < 30) { return 0.971; }
    else if(pt > 30 && pt < 40) { return 0.955; }
    else if(pt > 40 && pt < 50) { return 0.976; }
    else if(pt > 50 && pt < 60) { return 0.994; }
    else if(pt > 60 && pt < 80) { return 1.045; }
    else if(pt > 80)            { return 0.987; }

  } else if(fabs(eta)<2.1) {
    if     (pt > 10 && pt < 20) { return 0.899; }
    else if(pt > 20 && pt < 30) { return 0.936; }
    else if(pt > 30 && pt < 40) { return 0.965; }
    else if(pt > 40 && pt < 50) { return 0.984; }
    else if(pt > 50 && pt < 60) { return 0.988; }
    else if(pt > 60 && pt < 80) { return 0.982; }
    else if(pt > 80)            { return 0.982; }

  } else if(fabs(eta)<2.4) {
    if     (pt > 10 && pt < 20) { return 1.010; }
    else if(pt > 20 && pt < 30) { return 0.976; }
    else if(pt > 30 && pt < 40) { return 0.985; }
    else if(pt > 40 && pt < 50) { return 0.990; }
    else if(pt > 50 && pt < 60) { return 0.999; }
    else if(pt > 60 && pt < 80) { return 0.998; }
    else if(pt > 80)            { return 1.059; }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getEleTriggerDataEff(const double pt, const double eta)
{
  if(fabs(eta) < 0.4) {
    if     (pt > 30 && pt < 32) { return 0.853; }
    else if(pt > 32 && pt < 35) { return 0.893; }
    else if(pt > 35 && pt < 40) { return 0.924; }
    else if(pt > 40 && pt < 50) { return 0.945; }
    else if(pt > 50 && pt <200) { return 0.967; }
    else                        { return 0.989; }

  } else if(fabs(eta) < 1.4) {
    if     (pt > 30 && pt < 32) { return 0.755; }
    else if(pt > 32 && pt < 35) { return 0.864; }
    else if(pt > 35 && pt < 40) { return 0.914; }
    else if(pt > 40 && pt < 50) { return 0.944; }
    else if(pt > 50 && pt <200) { return 0.963; }
    else                        { return 0.972; }

  } else if(fabs(eta) < 1.6) {
    if     (pt > 30 && pt < 32) { return 0.477; }
    else if(pt > 32 && pt < 35) { return 0.729; }
    else if(pt > 35 && pt < 40) { return 0.858; }
    else if(pt > 40 && pt < 50) { return 0.895; }
    else if(pt > 50 && pt <200) { return 0.917; }
    else                        { return 0.949; }

  } else if(fabs(eta) < 2.1) {
    if     (pt > 30 && pt < 32) { return 0.774; }
    else if(pt > 32 && pt < 35) { return 0.863; }
    else if(pt > 35 && pt < 40) { return 0.890; }
    else if(pt > 40 && pt < 50) { return 0.907; }
    else if(pt > 50 && pt <200) { return 0.908; }
    else                        { return 0.903; }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getEleTriggerMCEff(const double pt, const double eta)
{
  if(fabs(eta) < 0.4) {
    if     (pt > 30 && pt < 32) { return 0.921; }
    else if(pt > 32 && pt < 35) { return 0.943; }
    else if(pt > 35 && pt < 40) { return 0.959; }
    else if(pt > 40 && pt < 50) { return 0.970; }
    else if(pt > 50 && pt <200) { return 0.974; }
    else                        { return 0.996; }

  } else if(fabs(eta) < 1.4) {
    if     (pt > 30 && pt < 32) { return 0.792; }
    else if(pt > 32 && pt < 35) { return 0.879; }
    else if(pt > 35 && pt < 40) { return 0.924; }
    else if(pt > 40 && pt < 50) { return 0.945; }
    else if(pt > 50 && pt <200) { return 0.955; }
    else                        { return 0.940; }

  } else if(fabs(eta) < 1.6) {
    if     (pt > 30 && pt < 32) { return 0.516; }
    else if(pt > 32 && pt < 35) { return 0.782; }
    else if(pt > 35 && pt < 40) { return 0.864; }
    else if(pt > 40 && pt < 50) { return 0.902; }
    else if(pt > 50 && pt <200) { return 0.918; }
    else                        { return 0.950; }

  } else if(fabs(eta) < 2.1) {
    if     (pt > 30 && pt < 32) { return 0.809; }
    else if(pt > 32 && pt < 35) { return 0.901; }
    else if(pt > 35 && pt < 40) { return 0.929; }
    else if(pt > 40 && pt < 50) { return 0.952; }
    else if(pt > 50 && pt <200) { return 0.964; }
    else                        { return 0.961; }
  }

  return 1;
}

//--------------------------------------------------------------------------------------
double getEleTriggerSF(const double pt, const double eta)
{
  std::cout <<   getEleTriggerDataEff(pt,eta) << " " << getEleTriggerMCEff(pt,eta) << std::endl;
  return getEleTriggerDataEff(pt,eta) / getEleTriggerMCEff(pt,eta);
}
