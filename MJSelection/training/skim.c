{
  gROOT->ProcessLine(".L skim.C+g");
  skim();
  gROOT->ProcessLine(".q");
}
