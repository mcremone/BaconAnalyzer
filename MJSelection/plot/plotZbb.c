{
  gROOT->ProcessLine(".L plotZbb.C+g");
  plot("Zbb","NoCutBtaggingTau21","PUPPI");
  gROOT->ProcessLine(".q");
}
