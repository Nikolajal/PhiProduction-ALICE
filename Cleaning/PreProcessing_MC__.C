#include "../../inc/SetValues.h"
// !TODO: Rebooting the selection process

void Anls_MonteCarloPreProcessing ( const char * fFileName )
{
    if ( !fFileName )
    {
        cout << "Must Specify an input root file" << endl;
        return;
    }
    
    //Retrieving Event data
    TFile *insFileMC     =   new TFile   (fFileName);
    
    //Retrieving Event data TTree
    TTree *PTreePTru    =   (TTree*)insFileMC->Get(fTreeTruName);
    
    if ( !PTreePTru )
    {
        cout << "Input Data Tree not found!" << endl;
        return;
    }
        
    // Define some simple data structures to Set Branch Addresses
    // Phi decay Kaon +- Couples S
    EVPHI               evPhi_Tru;
    if ( bPythiaTest == false )
    {
        PTreePTru  ->SetBranchAddress    ("nPhi",           &evPhi_Tru.nPhi);
        PTreePTru  ->SetBranchAddress    ("bRec",           &evPhi_Tru.bRec);
        PTreePTru  ->SetBranchAddress    ("bEta",           &evPhi_Tru.bEta);
        PTreePTru  ->SetBranchAddress    ("bKdc",           &evPhi_Tru.bKdc);
        PTreePTru  ->SetBranchAddress    ("pT",             &evPhi_Tru.pT);
    }
    else
    {
        PTreePTru  ->SetBranchAddress    ("evPhi.nPhi",           &evPhi_Tru.nPhi);
        PTreePTru  ->SetBranchAddress    ("evPhi.bRec",           &evPhi_Tru.bRec);
        PTreePTru  ->SetBranchAddress    ("evPhi.bEta",           &evPhi_Tru.bEta);
        PTreePTru  ->SetBranchAddress    ("evPhi.bKdc",           &evPhi_Tru.bKdc);
        PTreePTru  ->SetBranchAddress    ("evPhi.pT",             &evPhi_Tru.pT);
    }
    
    //---------------------//
    //  Setting up output  //
    //---------------------//
    
    // Generating the binning array--------------------------------------------------------------------------
    fSetBinPT1D();
    fSetBinIM1D();
    fSetBinPT2D();
    fSetBinIM2D();
    Int_t       S_ArrpT[1024];
    
    // Creating 1D Efficiency histograms---------------------------------------------------------------------
    hName   = "hNP_1D_Gen_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, 1D analysis";
    TH1F * hPhiGen_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiGen_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiGen_1D->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiGen_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiGen_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Rec_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, recordable in ALICE exp, 1D analysis";
    TH1F * hPhiRec_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiRec_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiRec_1D->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiRec_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiRec_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Gen_X2_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, 1D analysis";
    TH1F * hPhiG1D_2X   = new TH1F (hName,hTitle,nBinPT2D,fArrPT2D);
    hPhiG1D_2X->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiG1D_2X->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiG1D_2X->GetXaxis()->SetTitleOffset(1.15);
    hPhiG1D_2X->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Rec_X2_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, recordable in ALICE exp, 1D analysis";
    TH1F * hPhiR1D_2X   = new TH1F (hName,hTitle,nBinPT2D,fArrPT2D);
    hPhiR1D_2X->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiR1D_2X->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiR1D_2X->GetXaxis()->SetTitleOffset(1.15);
    hPhiR1D_2X->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Tru_PT_S";
    hTitle  = "Generated #phi per |y|<5, 1D analysis";
    TH1F * hPhiTru_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiTru_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiTru_1D->GetYaxis()->SetTitle("#frac{d^{2}N_{#phi}}{dydp_{T}}(GeV/c)^{-1}");
    hPhiTru_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiTru_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Eff_PT_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 1D analysis";
    TH1F * hPhiEff_1D   = new TH1F (hName,hTitle,nBinPT1D,fArrPT1D);
    hPhiEff_1D->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPhiEff_1D->GetXaxis()->SetTitleOffset(1.15);
    hPhiEff_1D->GetYaxis()->SetTitleOffset(1.15);
    
    hName   = "hNP_1D_Eff_X2_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 1D analysis";
    TH1F * hPEff1D_2X   = new TH1F (hName,hTitle,nBinPT2D,fArrPT2D);
    hPEff1D_2X->GetXaxis()->SetTitle("p_{T} #phi (GeV/c)");
    hPEff1D_2X->GetXaxis()->SetTitleOffset(1.15);
    hPEff1D_2X->GetYaxis()->SetTitleOffset(1.15);
    
    // Creating 2D Efficiency histograms---------------------------------------------------------------------
    hName   = "hNP_2D_Gen_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, 2D analysis";
    TH2F * hPhiGen_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiGen_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiGen_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiGen_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiGen_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Rec_PT_S";
    hTitle  = "Generated #phi per |y|<5 in K_{+}K_{-} Decay mode, recordable in ALICE exp, 2D analysis";
    TH2F * hPhiRec_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiRec_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiRec_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiRec_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiRec_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Tru_PT_S";
    hTitle  = "Generated #phi per |y|<5, 2D analysis";
    TH2F * hPhiTru_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiTru_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiTru_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiTru_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiTru_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Eff_PT_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 2D analysis";
    TH2F * hPhiEff_2D   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPhiEff_2D->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPhiEff_2D->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPhiEff_2D->GetXaxis()->SetTitleOffset(1.5);
    hPhiEff_2D->GetYaxis()->SetTitleOffset(1.5);
    
    hName   = "hNP_2D_Eff_X2_S";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 1D analysis in 2D";
    TH2F * hPEff2D_2X   = new TH2F (hName,hTitle,nBinPT2D,fArrPT2D,nBinPT2D,fArrPT2D);
    hPEff2D_2X->GetXaxis()->SetTitle("p_{T} #phi_{1} (GeV/c)");
    hPEff2D_2X->GetYaxis()->SetTitle("p_{T} #phi_{2} (GeV/c)");
    hPEff2D_2X->GetXaxis()->SetTitleOffset(1.5);
    hPEff2D_2X->GetYaxis()->SetTitleOffset(1.5);
    
    // Creating the Target Result Histogram------------------------------------------------------------------
    hName   = "MC_Results";
    hTitle  = "Multidimensional #phi production statistics";
    TH1F *          hUtlTarget  = new TH1F (hName,hTitle,2,0.5,2.5);
    hUtlTarget->GetXaxis()->SetTitle("N-Tuples");
    hUtlTarget->GetYaxis()->SetTitle("#frac{1}{N_{evs}}#times#frac{dN_{#phi}}{dy}");
    
    hName   = "Entry_MC";
    hTitle  = "Events in MC";
    TH1F *          hUtlEntry   = new TH1F (hName,hTitle,2,0.5,2.5);
    hUtlEntry                   ->GetXaxis()->SetTitle("");
    hUtlEntry                   ->GetYaxis()->SetTitle("Events");
    
    //-------------------------//
    //  Filling output objects //
    //-------------------------//
    
    // Evaluating entries
    Int_t nEntries = PTreePTru->GetEntries();
    for ( Int_t iEvent = 0; iEvent < nEntries; iEvent++ )
    {
        PTreePTru->GetEntry(iEvent);
        for (Int_t iPhi = 0; iPhi < evPhi_Tru.nPhi; iPhi++ )
        {
            // Region of Physical interest
            if ( !evPhi_Tru.bEta[iPhi] )  continue;
            
            // All True Phi                                                                 #TRU
            hPhiTru_1D-> Fill(evPhi_Tru.pT[iPhi]);
            hUtlTarget-> Fill(1);
            
            // Only |y| < 0.5 Phi in K+- Candidates                                         #GEN
            if ( evPhi_Tru.bKdc[iPhi] )    {hPhiGen_1D-> Fill(evPhi_Tru.pT[iPhi]);  hPhiG1D_2X ->  Fill(evPhi_Tru.pT[iPhi]); }

            // Only Recordable Phi in K+- Candidates                                        #REC
            if ( evPhi_Tru.bRec[iPhi] )    {hPhiRec_1D-> Fill(evPhi_Tru.pT[iPhi]);  hPhiR1D_2X ->  Fill(evPhi_Tru.pT[iPhi]); }
            
            for (Int_t jPhi = 0; jPhi < evPhi_Tru.nPhi; jPhi++ )
            {
                // Auto-correlation protection
                if ( iPhi == jPhi ) continue;
                
                // Region of Physical interest
                if ( !evPhi_Tru.bEta[jPhi] ) continue;
                
                // All True Phi                                                             #TRU
                hPhiTru_2D-> Fill(evPhi_Tru.pT[iPhi],evPhi_Tru.pT[jPhi],0.5);
                hUtlTarget->Fill(2,0.5);

                // Only |y| < 0.5 Phi  in K+- Candidates                                    #GEN
                if ( evPhi_Tru.bKdc[iPhi] && evPhi_Tru.bKdc[jPhi] ) hPhiGen_2D-> Fill(evPhi_Tru.pT[iPhi],evPhi_Tru.pT[jPhi],0.5);
                
                // Only Recordable Phi in K+- Candidates                                    #REC
                if ( evPhi_Tru.bRec[iPhi] && evPhi_Tru.bRec[jPhi] ) hPhiRec_2D-> Fill(evPhi_Tru.pT[iPhi],evPhi_Tru.pT[jPhi],0.5);
            }
        }
    }
    
    // Evaluating the Target value
    hUtlTarget->Scale(1./(nEntries));

    // Fixing the Histograms per binwidth
    hPhiGen_1D    ->Scale(1.,"width");
    hPhiRec_1D    ->Scale(1.,"width");
    hPhiTru_1D    ->Scale(1.,"width");
    hPhiG1D_2X    ->Scale(1.,"width");
    hPhiR1D_2X    ->Scale(1.,"width");
    hPhiGen_2D    ->Scale(1.,"width");
    hPhiRec_2D    ->Scale(1.,"width");
    hPhiTru_2D    ->Scale(1.,"width");
    
    // Fixing the Histograms per Events
    hPhiGen_1D    ->Scale(1./(nEntries));
    hPhiRec_1D    ->Scale(1./(nEntries));
    hPhiTru_1D    ->Scale(1./(nEntries));
    hPhiG1D_2X    ->Scale(1./(nEntries));
    hPhiR1D_2X    ->Scale(1./(nEntries));
    hPhiGen_2D    ->Scale(1./(nEntries));
    hPhiRec_2D    ->Scale(1./(nEntries));
    hPhiTru_2D    ->Scale(1./(nEntries));
    
    nEntries      = PTreePTru->GetEntries();
    hUtlEntry     ->SetBinContent(1,nEntries);
    
    // Evaluating the Efficiencies
    hName   = "1D_Eff";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 1D analysis";
    TGraphAsymmErrors * gEfficiency1D   =   new TGraphAsymmErrors();
    gEfficiency1D                       ->  SetName(hName);
    gEfficiency1D                       ->  SetTitle(hTitle);
    gEfficiency1D                       ->GetXaxis()    ->SetTitle("p_{T} #phi (GeV/c)");
    gEfficiency1D                       ->GetYaxis()    ->SetTitle("#varepsilon");
    
    hName   = "2D_Eff";
    hTitle  = "#phi acceptance in ALICE exp (|y|<5), 2D analysis";
    TGraphAsymmErrors * gEfficiency2D =   new TGraphAsymmErrors();
    gEfficiency2D                       ->  SetName(hName);
    gEfficiency2D                       ->  SetTitle(hTitle);
    gEfficiency2D                       ->  GetXaxis()  ->SetTitle("p_{T} #phi_{1} (GeV/c)");
    gEfficiency2D                       ->  GetYaxis()  ->SetTitle("p_{T} #phi_{2} (GeV/c)");
    gEfficiency2D                       ->  GetZaxis()  ->SetTitle("#varepsilon");
    
    gEfficiency1D->Divide(hPhiRec_1D,hPhiGen_1D,"cl=0.683 b(1,1) mode");
    
    gEfficiency2D->Divide(hPhiR1D_2X,hPhiG1D_2X,"cl=0.683 b(1,1) mode");
    
    // Evalutaing the Efficiencies
    hPhiEff_1D->Divide(hPhiRec_1D,hPhiGen_1D,1.,1.,"b");
    hPhiEff_2D->Divide(hPhiRec_2D,hPhiGen_2D,1.,1.,"b");
    hPEff1D_2X->Divide(hPhiR1D_2X,hPhiG1D_2X,1.,1.,"b");
    for ( Int_t iEff = 0; iEff <= nBinPT2D; iEff++ )
    {
        for ( Int_t jEff = 0; jEff <= nBinPT2D; jEff++ )
        {
            auto Val1 = hPEff1D_2X->GetBinContent(iEff+1);
            auto Val2 = hPEff1D_2X->GetBinContent(jEff+1);
            auto Err1 = hPEff1D_2X->GetBinError(iEff+1);
            auto Err2 = hPEff1D_2X->GetBinError(jEff+1);
            hPEff2D_2X  ->SetBinContent (hPEff2D_2X->GetBin(iEff+1,jEff+1),Val1*Val2);
            hPEff2D_2X  ->SetBinError   (hPEff2D_2X->GetBin(iEff+1,jEff+1),Err1+Err2);
        }
    }
    
    //--------------------------//
    //  Printing output objects //
    //--------------------------//
    TFile * outFile         =   new TFile   (fEfficiHist,"recreate");
    
    // Writing Histograms to Output File
    hUtlEntry       ->Write();
    hPhiGen_1D      ->Write();
    hPhiG1D_2X      ->Write();
    hPhiGen_2D      ->Write();
    hPhiRec_1D      ->Write();
    hPhiR1D_2X      ->Write();
    hPhiRec_2D      ->Write();
    hPhiTru_1D      ->Write();
    hPhiTru_2D      ->Write();
    hPhiEff_1D      ->Write();
    hPhiEff_2D      ->Write();
    hPEff2D_2X      ->Write();
    hUtlTarget      ->Write();
    gEfficiency1D   ->Write();
    gEfficiency2D   ->Write();
    //(hPhiRec_1D->Divide(hPhiRec_1D,hPhiGen_1D));
    hPhiRec_1D->Write();
    
    outFile->Close();
    insFileMC->Close();
}



/*
hTRU_Parameter->Scale(1.,"width");
hTRU_Parameter->Scale(1./nEntries);

for ( Int_t i = 0; i < nBinMult; ++i )
{
    auto c_bin1     =   hTRU_Parameter->GetBin(i+1,2);
    auto c_bin2     =   hTRU_Parameter->GetBin(i+1,3);
    auto c_yield1   =   hTRU_Parameter->GetBinContent(c_bin1);
    auto c_yield2   =   hTRU_Parameter->GetBinContent(c_bin2);
    auto c_yielE1   =   hTRU_Parameter->GetBinError(c_bin1);
    auto c_yielE2   =   hTRU_Parameter->GetBinError(c_bin2);
    
    auto valGmPhi   =   2*c_yield2/(c_yield1) - c_yield1;
    auto ErrGmPhi   =   sqrt(pow((sqrt( pow((c_yielE1/c_yield1),2) + pow((c_yielE2/c_yield2),2) )*2*c_yield2/(c_yield1)),2) + pow(c_yielE1,2));
    hTRU_GammaPhi   ->SetBinContent (i+1,valGmPhi);
    hTRU_GammaPhi   ->SetBinError   (i+1,ErrGmPhi);
    
    auto valRatio   =   c_yield2/(c_yield1*c_yield1);
    auto ErrRatio   =   sqrt( 2*pow((c_yielE1/c_yield1),2) + pow((c_yielE2/c_yield2),2) );
    hTRU_Ratio      ->SetBinContent (i+1,valRatio);
    hTRU_Ratio      ->SetBinError   (i+1,ErrRatio*valRatio);
}
*/
