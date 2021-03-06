// Illustrates how to find peaks in histograms.
// This script generates a random number of gaussian peaks
// on top of a linear background.
// The position of the peaks is found via TSpectrum and injected
// as initial values of parameters to make a global fit.
// The background is computed and drawn on top of the original histogram.
//
// To execute this example, do
//  root > .x peaks.C  (generate 10 peaks by default)
//  root > .x peaks.C++ (use the compiler)
//  root > .x peaks.C++(30) (generates 30 peaks)
//
// To execute only the first part of the script (without fitting)
// specify a negative value for the number of peaks, eg
//  root > .x peaks.C(-20)
//
//Author: Rene Brun

#include "TCanvas.h"
#include "TMath.h"
#include "TH1.h"
#include "TF1.h"
#include "TRandom.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
// all comments added by YYCHEN


// how many peaks   
Int_t npeaks = 10 ;
Double_t fpeaks(Double_t *x, Double_t *par) {
   Double_t result = 0; //initiate the fitting function = linear function //I do not need linear background.
   for (Int_t p=0;p<npeaks;p++) {
      Double_t norm  = par[3*p+0];
      Double_t mean  = par[3*p+1];
      Double_t sigma = par[3*p+2];
      result += norm*TMath::Gaus(x[0],mean,sigma); //add n peaks to the fitting funtion
   }
   return result;
}


void peaks1(Int_t np=10) {
   npeaks = TMath::Abs(np);
   Double_t par[3000];
   Int_t p;
   /*
   TH1F *h = new TH1F("h","test",500,0,1000);

   //generate n peaks at random
   Double_t par[3000];
   par[0] = 0.8;
   par[1] = -0.6/1000;
   Int_t p;
   for (p=0;p<npeaks;p++) {
      par[3*p+2] = 1;
      par[3*p+3] = 10+gRandom->Rndm()*980;
      par[3*p+4] = 1+2*gRandom->Rndm();
   }
   TF1 *f = new TF1("f",fpeaks,0,1000,2+3*npeaks);
   f->SetNpx(1000);
   f->SetParameters(par);
   TCanvas *c1 = new TCanvas("c1","c1",10,10,1000,900);
   c1->Divide(1,2);
   c1->cd(1);
   h->FillRandom("f",200000);
   
   h->Draw();
*/
///////////load a file//////////////////
   TCanvas *c1 = new TCanvas("c1","c1",10,10,1000,900);
   c1->Divide(1,2);
   c1->cd(1);
   TFile *f = new TFile("run6091_test22.root");
   TH1F *h1 = (TH1F*)f->Get("h159");
   h1->Draw("");
////////////////////////////////////////

   TH1F *h2 = (TH1F*)h1->Clone("h2");

   //Use TSpectrum to find the peak candidates
   TSpectrum *s = new TSpectrum(2*npeaks);
   Int_t nfound = s->Search(h1,3,"",0.05);
   printf("Found %d candidate peaks to fit\n",nfound);// change the last number to fit more peaks.
   //Estimate background using TSpectrum::Background
 //  TH1 *hb = s->Background(h1,20,"same");
 //  if (hb) c1->Update();
   if (np <0) return;

   //estimate linear background using a fitting method
   c1->cd(2);
  // TF1 *fline = new TF1("fline","pol1",0,1000);
  // h1->Fit("fline","qn");
   //Loop on all found peaks. Eliminate peaks at the background level
  // par[0] = fline->GetParameter(0);
  // par[1] = fline->GetParameter(1);
   npeaks = 0;
   Float_t *xpeaks = s->GetPositionX();
   for (p=0;p<nfound;p++) {
      Float_t xp = xpeaks[p];
      Int_t bin = h1->GetXaxis()->FindBin(xp);
      Float_t yp = h1->GetBinContent(bin);
    //  if (yp-TMath::Sqrt(yp) < fline->Eval(xp)) continue;
      par[3*npeaks+0] = yp;
      par[3*npeaks+1] = xp;
      par[3*npeaks+2] = 1;
      npeaks++;
   }
   printf("Found %d useful peaks to fit\n",npeaks);
   printf("Now fitting: Be patient\n");
   TF1 *fit = new TF1("fit",fpeaks,0,1000,3*npeaks);
   //we may have more than the default 25 parameters
   TVirtualFitter::Fitter(h2,10+3*npeaks);
   fit->SetParameters(par);
   fit->SetNpx(1000);
   h2->Fit("fit");
  
}
