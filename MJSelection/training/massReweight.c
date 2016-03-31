{
  gROOT->ProcessLine(".L massReweight.C+g");
  massReweight("bst15","PUPPI","mcsig15");
  //massReweight("bst15","CHS","mcsig15");
  //massReweight("bst8","PUPPI","mcsig8");
  //massReweight("bst8","CHS","mcsig8");
  gROOT->ProcessLine(".q");
}
