{
  // include path for RooFit
  TString path = gSystem->GetIncludePath();
  path += "-I. -I$ROOTSYS/src -I$ROOFITSYS/include";
  gSystem->SetIncludePath(path.Data());

  if(gSystem->Getenv("CMSSW_VERSION")) {
    gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
    gSystem->AddIncludePath("-I$CMSSW_RELEASE_BASE/src/");
    //    gSystem->AddIncludePath("-I$CMSSW_BASE/src/DMSAna/Utils/interface");
    
    gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/");
    gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_RELEASE_BASE"))+"/src/");
    // gInterpreter->AddIncludePath(TString(gSystem->Getenv("CMSSW_BASE"))+"/src/DMSAna/Utils/interface");
    
    // gSystem->Load(Form("%s/lib/%s/%s",
    //                    gSystem->Getenv("CMSSW_BASE"),
    //                    gSystem->Getenv("SCRAM_ARCH"),
    //                    "libDMSAnaUtils.so"));
  }

  // for plots
  gROOT->Macro("../macros/CPlot.cc+");
  gROOT->Macro("../macros/KStyle.cc+");
  gROOT->Macro("../macros/ZprimeBitsLoader.cc+");
  gROOT->Macro("../macros/MonoXBitsLoader.cc+");
}
