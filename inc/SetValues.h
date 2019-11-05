#ifndef SETVALUES_H
#define SETVALUES_H

// C++
#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <chrono>

// ROOT
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TF1.h"
#include "TFile.h"

// RooFit
#include "RooRealVar.h"
#include "RooConstVar.h"
#include "RooAddPdf.h"
#include "RooDataSet.h"
#include "RooAbsData.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooGlobalFunc.h"

// RooFitFunction
#include "RooChebychev.h"
#include "RooArgusBG.h"
#include "RooBreitWigner.h"
#include "RooGaussian.h"
#include "RooGenericPdf.h"
#include "RooUniform.h"

using namespace std;
using namespace RooFit;
using namespace std::chrono;

auto const oFileMonCar  = "./result/outGeneratorMC.root";
auto const oFilePreP1D  = "./result/outPreProcessing1D.root";
auto const oFilePreP2D  = "./result/outPreProcessing2D.root";
auto const oFileDataFt  = "./result/outDataFormat.root";
auto const oFileAnalys  = "./result/outAnalysis.root";
auto const oFileAnal1D  = "./result/outAnalysis1D.root";
auto const oFileAnal2D  = "./result/outAnalysis2D.root";
auto const oFileEffici  = "./result/outEfficiency.root";
auto const oFileHist1D  = "./result/outHistogram1D.root";
auto const oFileHist2D  = "./result/outHistogram2D.root";
auto const iFileMCEffi  = "./result/outGeneratorMC_Efficiency.root";
auto const hPhiEff      = "hPhiEff";
auto const PTreeNameK2  = "PythiaTreeK2";
auto const PTreeNamePhi = "PythiaTreePhi";
auto const PEvents      = 1e7;

// InvMass range 1D
const Int_t     nBinIM1D    = 100;
const Float_t   fMinIM1D    = 0.99;
const Float_t   fMaxIM1D    = 1.09;

// InvMass range 2D
const Int_t     nBinIM2D    = 75;
const Float_t   fMinIM2D    = 0.99;
const Float_t   fMaxIM2D    = 1.09;

// pT cuts 1D
const Int_t     nBinPT1D    = 40;
const Float_t   fMinPT1D    = 0.;
const Float_t   fMaxPT1D    = 4.;

// pT cuts 2D
const Int_t     nBinPT2D    = 3.;
const Float_t   fMinPT2D    = 0.;
const Float_t   fMaxPT2D    = 4.;

typedef struct
{
    Int_t nKaon, particleID[1024], mother1[1024], mother2[1024], motherID[1024];
    Float_t px[1024], py[1024], pz[1024], pT[1024], e[1024];
} EVKAON;

typedef struct
{
    Int_t   nKaonCouple, iKaon[1024], jKaon[1024];
    Bool_t  bPhi[1024], bRec[1024];
    Float_t InvMass[1024], pT[1024];
} EVKAONCOUPLE;

typedef struct
{
    Int_t   nPhi;
    Float_t pT[1024];
} EVPHI;

Float_t fBoundPT1D (Int_t index)
{
    auto result = {0.,1.,2.,4.};
    return fMinPT1D+(index)*(fMaxPT1D - fMinPT1D)/(static_cast<Float_t>(nBinPT1D));
}

Float_t fBoundPT2D (Int_t index)
{
    return fMinPT2D+(index)*(fMaxPT2D - fMinPT2D)/(static_cast<Float_t>(nBinPT2D));
}

#endif