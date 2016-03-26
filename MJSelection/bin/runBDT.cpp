//================================================================================================
//
// Driver to run Bacon - BDT selection
//
// Input arguments
//   argv[1] => lname = input bacon file name
//   argv[2] => lOption = dataset type: "mcbkg", "mcsig", "data" -- should we include types of jets as input? 
//   argv[3] => lJSON = JSON file for run-lumi filtering of data, specify "none" for MC or no filtering
//   argv[4] => lXS = cross section (pb), ignored for data 
//   argv[5] => weight = total weight, ignored for data
//________________________________________________________________________________________________

#include "../include/GenLoader.hh"
#include "../include/EvtLoader.hh"
#include "../include/ElectronLoader.hh"
#include "../include/MuonLoader.hh"
#include "../include/PhotonLoader.hh"
#include "../include/TauLoader.hh"
#include "../include/JetLoader.hh"
#include "../include/VJetLoader.hh"
#include "../include/RunLumiRangeMap.h"

#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
#include <iostream>

// Object Processors
GenLoader       *fGen      = 0; 
EvtLoader       *fEvt      = 0; 
MuonLoader      *fMuon     = 0; 
ElectronLoader  *fElectron = 0; 
TauLoader       *fTau      = 0; 
PhotonLoader    *fPhoton   = 0; 
JetLoader       *fJet      = 0; 
VJetLoader      *fVJet     = 0;
RunLumiRangeMap *fRangeMap = 0; 

TH1F *fHist                = 0; 

// Load tree and return infile
TTree* load(std::string iName) { 
  TFile *lFile = TFile::Open(iName.c_str());
  TTree *lTree = (TTree*) lFile->FindObjectAny("Events");
  fHist        = (TH1F* ) lFile->FindObjectAny("TotalEvents");
  return lTree;
}

// For Json 
bool passEvent(unsigned int iRun,unsigned int iLumi) { 
  RunLumiRangeMap::RunLumiPairType lRunLumi(iRun,iLumi);
  return fRangeMap->HasRunLumi(lRunLumi);
}

// FIXME class for top tagging + booleans for comparison
class sjpair {
public:
  sjpair (TLorentzVector sj0, TLorentzVector sj1,  float qgtag0, float qgtag1, TLorentzRotation lambda){
    if (sj0.Pt()>0&&sj1.Pt()>0) {
      TLorentzVector sum = sj1+sj0;
      mjj = sum.M();
      mj0 = (sj0.Pt()>sj1.Pt() ? sj0.M() : sj1.M());
      dR = (sj0.DeltaR(sj1)>0) ? sj0.DeltaR(sj1) : 999;

      TVector3 hVelocity = sum.BoostVector();

      // Create a boost to the subjet pair rest frame
      TLorentzRotation Boost(hVelocity);
      TLorentzRotation tosubjetRest = Boost.Inverse();

      bool dRComp(sjpair p1, sjpair p2) {
	return p1.dR<p2.dR;
      }

      bool dRTRFComp(sjpair p1, sjpair p2) {
	return p1.dRTRF<p2.dRTRF;
      }

      bool dPhiWRFComp(sjpair p1, sjpair p2) {
	return p1.dPhiWRF<p2.dPhiWRF;
      }

      bool sumQGComp(sjpair p1, sjpair p2) {
	return p1.sumqg>p2.sumqg;
      }
      // Get the direction of v1 and v2 in the subjet pair rest frame
      TVector3 v1Dir = (tosubjetRest*(sj0)).Vect().Unit();
      TVector3 v2Dir = (tosubjetRest*(sj1)).Vect().Unit();
      float x1 = (sj0).Px();
      float x2 = (sj1).Px();
      float y1 = (sj0).Py();
      float y2 = (sj1).Py();
      float angle_mht = atan2((y1+y2),(x1+x2)) + TMath::Pi();
      Float_t a1 = TMath::Pi() - acos(cos(v1Dir.Phi()-angle_mht));
      Float_t a2 = TMath::Pi() - acos(cos(v2Dir.Phi()-angle_mht));
      dPhiWRF = min(a1,a2);

      TVector3 sjboosted0 = (lambda*(sj0)).Vect();
      TVector3 sjboosted1 = (lambda*(sj1)).Vect();

      dRTRF = sjboosted0.DeltaR(sjboosted1);

      if (qgtag1>qgtag0) qg0 = qgtag0; qg1 = qgtag1;
      else               qg1 = qgtag0; qg0 = qgtag1;

      sumqg = (TMath::TanH(TMath::ATanH(2*qg0-1)+TMath::ATanH(2*qg1-1))+1)/2;
    }
  }
  ~sjpair() { }
  float dR=999;
  float mjj=-1;
  float mj0=-1;
  float qg0=-1;
  float qg1=-1;
  float sumqg=-1;
  float dRTRF=999;
  float dPhiWRF=999;
};
bool dRComp(sjpair p1, sjpair p2) {
  return p1.dR<p2.dR;
}

bool dRTRFComp(sjpair p1, sjpair p2) {
  return p1.dRTRF<p2.dRTRF;
}

bool dPhiWRFComp(sjpair p1, sjpair p2) {
  return p1.dPhiWRF<p2.dPhiWRF;
}

bool sumQGComp(sjpair p1, sjpair p2) {
  return p1.sumqg>p2.sumqg;
}

// === MAIN =======================================================================================================
int main( int argc, char **argv ) {
  gROOT->ProcessLine("#include <vector>");
  const std::string lName        = argv[1];
  const std::string lOption      = argv[2];
  const std::string lJSON        = argv[3];
  const double      lXS          = atof(argv[4]);
  const double      weight       = atof(argv[5]);

  fRangeMap = new RunLumiRangeMap();
  if(lJSON.size() > 0) fRangeMap->AddJSONFile(lJSON.c_str());

  TTree *lTree = load(lName); 
  float lWeight = (float(lXS)*1000.)/weight; if(lOption.find("data")!=std::string::npos) lWeight = 1.;
  
  // Declare Readers 
  fEvt      = new EvtLoader     (lTree,lName);                                           // fEvt, fEvtBr, fVertices, fVertexBr
  fMuon     = new MuonLoader    (lTree);                                                 // fMuon and fMuonBr, fN = 2 - muonArr and muonBr
  fElectron = new ElectronLoader(lTree);                                                 // fElectrons and fElectronBr, fN = 2
  fTau      = new TauLoader     (lTree);                                                 // fTaus and fTaurBr, fN = 1
  fPhoton   = new PhotonLoader  (lTree);                                                 // fPhotons and fPhotonBr, fN = 1
  fJet      = new JetLoader     (lTree);                                                 // fJets and fJetBr => AK4CHS, fN = 4 - includes jet corrections (corrParams), fN = 4, Implement AK4CHS?
  fVJet     = new VJetLoader    (lTree,"CA15Puppi","AddCA15Puppi");                      // fVJets, fVJetBr =>CA8PUPPI, CA15PUPPI, AK8CHS, CA15CHS fN =1
  if(lOption.find("data")==std::string::npos) fGen      = new GenLoader     (lTree);     // fGenInfo, fGenInfoBr => GenEvtInfo, fGens and fGenBr => GenParticle

  TFile *lFile = new TFile("Output.root","RECREATE");
  TTree *lOut  = new TTree("Events","Events");

  // Setup Tree - Set branch address depends on object processor, see src/*Loader.cc
  fEvt     ->setupTree      (lOut,lWeight); 
  fJet     ->setupTree      (lOut,"res_PUPPIjet"); 
  fVJet    ->setupTree      (lOut,"bst15_PUPPIjet"); 
  fMuon    ->setupTree      (lOut); 
  fElectron->setupTree      (lOut); 
  fTau     ->setupTree      (lOut); 
  fPhoton  ->setupTree      (lOut); 
  if(lOption.find("data")==std::string::npos) fGen ->setupTree (lOut,float(lXS));

  //
  // Loop over events i0 = iEvent
  //
  int neventstest = 0;
  for(int i0 = 0; i0 < int(lTree->GetEntriesFast()); i0++) {
  //for(int i0 = 0; i0 < int(10000); i0++){ // for testing
    if(i0 % 1000 == 0) std::cout << "===> Processed " << i0 << " - Done : " << (float(i0)/float(lTree->GetEntriesFast())*100) << " -- " << lOption << std::endl;
    
    // check GenInfo
    if(lOption.find("data")==std::string::npos)    fGen->load(i0);

    // primary vertex requirement
    fEvt->load(i0);           if(!fEvt->PV()) continue;
    
    // triggerbits for MET, Electrons, Photons and Muons
    unsigned int trigbits=1;    
    if(fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_NoID_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*") ||
       fEvt ->passTrigger("HLT_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_NoID_v*")) trigbits = trigbits | 2; 
    if(fEvt ->passTrigger("HLT_Ele27_WP85_Gsf_v*") ||
       fEvt ->passTrigger("HLT_Ele27_WPLoose_Gsf_v*") ||
       fEvt ->passTrigger("HLT_Ele23_CaloIdL_TrackIdL_IsoVL_v*"))  trigbits = trigbits | 4;
    if(fEvt ->passTrigger("HLT_Photon175_v*") ||
       fEvt ->passTrigger("HLT_Photon165_HE10_v*")) trigbits = trigbits | 8;
    if(trigbits==1) continue;
    
    // Objects
    std::vector<TLorentzVector> lMuons, lElectrons, lPhotons, lJets, lVetoes;
    // Muons
    fMuon    ->load(i0);
    fMuon    ->selectMuons(lMuons);

    fEvt      ->load(i0);
    fEvt      ->fillEvent(trigbits);
    
    // Electrons
    fElectron ->load(i0);
    fElectron ->selectElectrons(fEvt->fRho,lElectrons);

    fEvt->fillVetoes(lElectrons,lVetoes);
    fEvt->fillVetoes(lMuons,lVetoes);        // In principle this will produce a different output from Matteo

    if(lOption.find("data")!=std::string::npos && !passEvent(fEvt->fRun,fEvt->fLumi)) continue;

    // Taus
    fTau     ->load(i0);
    fTau     ->selectTaus(lVetoes);

    // Photons
    fPhoton  ->load(i0);
    fPhoton  ->selectPhotons(fEvt->fRho,lElectrons,lPhotons);
    
    // Trigger Efficiencies
    fEvt->triggerEff(lElectrons, lPhotons);
    
    // CA15Puppi Jets
    fVJet->load(i0);
    fVJet->selectVJets(lVetoes,lJets,1.5,fEvt->fPuppEtPhi,fEvt->fRho);
    
    if(lJets.size()>0){ if((lOption.compare("mcttbst")==0 && fGen->ismatchedJet(lJets[0],1.5,fVJet->ftopSize))
			   || (lOption.compare("mcttcom")==0 && !fGen->ismatchedJet(lJets[0],1.5,fVJet->ftopSize))){
	fEvt->fselectBits |= 2; 
      }
    }
    
    lOut->Fill();
    neventstest++;
  }
  std::cout << neventstest << std::endl;
  std::cout << lTree->GetEntriesFast() << std::endl;
  lFile->cd();
  lOut->Write();
  lFile->Close();
}
