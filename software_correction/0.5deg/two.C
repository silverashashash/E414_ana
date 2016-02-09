//****************************************************************************
//
//	Alexander Long 
//	03/20/14
//	University of Notre Dame 
//	Department of Physics	
//	
//	This program was created in order to convert a 2D histograms given from 
//	Tamii's ANALYZER into a TTree with 2 branches
//
//
//****************************************************************************

#include <TTree.h>
#include <iostream>
#include <TFile.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TMath.h>

void two(){

	//	Declaring 
	Double_t num;
	Double_t xNumBins, yNumBins;

	//	Setting up Canvas to put plot the 2D histogram (from Tamii) and the 2 Bracnh Tree (created by this program)
	TCanvas *canvas = new TCanvas("canvas","Canvas");
	canvas->Divide(2,1);
	canvas->cd(1);


	//	Opening up histogram file from tamii's analyzer
	//	Remember to do h2root before this program runs.
	TFile *f1 = new TFile("run6093_test44.root");
	TH2F *hist2D = (TH2F*)f1->Get("h157");
	//TH2F *hist2D = (TH2F*)f1->Get("h168");
	//	Plotting the 2D histogram on the first part of the Canvas
	hist2D->Draw("COLZ");
	
	
	canvas->cd(2);
	TH2F *hist2D2 = (TH2F*)f1->Get("h166");
	//TH2F *hist2D2 = (TH2F*)f1->Get("h176");
	hist2D2->Draw("COLZ");

}

