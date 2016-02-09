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

void makeTTree(){

	//	Declaring 
	Double_t num;
	Double_t xNumBins, yNumBins;

	//	Setting up Canvas to put plot the 2D histogram (from Tamii) and the 2 Bracnh Tree (created by this program)
	TCanvas *canvas = new TCanvas("canvas","Canvas");
	canvas->Divide(2,1);
	canvas->cd(1);


	//	Opening up histogram file from tamii's analyzer
	//	Remember to do h2root before this program runs.
	TFile *f1 = new TFile("run6106_test44.root");
	TH2F *hist2D = (TH2F*)f1->Get("h159");
	//	Plotting the 2D histogram on the first part of the Canvas
	hist2D->Draw("COLZ");
	
	//	Going through 2D hist and getting the total number of x and y bins.
	xNumBins = hist2D->GetNbinsX();
	yNumBins = hist2D->GetNbinsY();
	
	//	Creating a new file to save the 2 branch tree to.
	TFile *t1 = new TFile("~/e329/root/13C/runs/run3014.root","recreate");

	//	This is the actual tree being created.
	//	!!! For you YingYing, instead of x vs theta, you would have theta(fp or target) vs Yfp !!!
	TNtuple *DATA = new TNtuple("DATA","Xpos vs Theta","Xpos:Theta");
	

	//	This is the main nested for loop that goes through each bin in the 2D hist 
	//	takes the number of counts in that (x,y)bin and creates that many events
	//	in the 2 branch tree  
	for (int binx = 0; binx < xNumBins+2; binx++){

		for (int biny = 0; biny < yNumBins+2; biny++){

			//getting the number of events in a particular (x,y)bin
			num = hist2D->GetBinContent(binx,biny);
			double x = hist2D->GetXaxis()->GetBinCenter(binx); 
			double y = hist2D->GetYaxis()->GetBinCenter(biny); 
			//cout << num << " at x= " << x << ", y= " << y << endl;

			//Filling the Tree 'num' times with xbin and ybin events
			for (int i = 0; i < num; i++){
				DATA->Fill(x,y);
			}
		}
	}
	
	//Saving the Tree that was just created and filled
	t1->Write();

	//Ploting the Tree in the second part of the canvas.
	canvas->cd(2);
	DATA->Draw("Theta:Xpos>>(2000,-600,600,1000,-3,3)","","COLZ");
}

