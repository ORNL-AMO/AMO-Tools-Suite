/**
 * @file
 * @brief Contains the implementation of Bio-Tiger, waste water treatment simulation.
 *
 * @author Mohsen Maniat
 * @bug No known bugs.
 *
 */
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class tableOfCalculations{
    public:
    double Se;
    double HeterBio;
    double CellDeb;
    double InterVes;
    double MLVSS;
    double MLSS;
    double BiomassProd;
    double SludgeProd;
    double SolidProd;
    double Effluent;
    double IntentWaste;
    double OxygenRqd;
    double FlowMgd;
    double NRemoved;
    double NRemovedMgl;
    double NitO2Dem;
    double O2Reqd;
    double EffNH3N;
    double EffNo3N;
    double TotalO2Rqd; 
    double WAS;
    double EstimatedEff;
    double EstimRas;
    double FmRatio;
    double Diff_MLSS;
    double SRT;
};

class outputTable{
    public:
    double TotalAverageDailyFlowRate;
    double VolumeInService;
    double InfluentBOD5Concentration;
    double InfluentBOD5MassLoading;
    double SecWWOxidNLoad;
    double SecWWTSSLoad;
    double FM_ratio;
    double SolidsRetentionTime;
    double MLSS;
    double MLVSS;
    double TSSSludgeProduction;
    double TSSInActivatedSludgeEffluent;
    double TotalOxygenRequirements;
    double TotalOxygenReqWDenit;
    double TotalOxygenSupplied;
    double MixingIntensityInReactor;
    double RASFlowRate;
    double RASRecyclePercentage;
    double WASFlowRate;
    double RASTSSConcentration;
    double TotalSludgeProduction;
    double ReactorDetentionTime;
    double VOLR;
    double EffluentCBOD5;
    double EffluentTSS;
    double EffluentAmmonia_N;
    double EffluentNO3_N;
    double EffluentNO3_N_W_Denit;   

    double AeEnergy;
    double AeCost;
    double FieldOTR;
};

class inputTable{
    public:
    double Temperature;
    double So;
    double Volume;
    double FlowRate;
    double InertVSS;
    double OxidizableN;
    double Biomass;
    double InfluentTSS;
    double InertInOrgTSS;
    double EffluentTSS;
    double RASTSS;
    double MLSSpar;
    double FractionBiomass;
    double BiomassYeild;
    double HalfSaturation;
    double MicrobialDecay;
    double MaxUtilizationRate;
    double MaxDays;
    double TimeIncrement;

    double OperatingDO;
    double Alpha;
    double Beta;
    double SOTR;
    double Aeration;
    double Elevation;
    double OperatingTime;
    int TypeAerators;
    double Speed;
    double EnergyCostUnit;   
      };

double interpolate( vector<double> &xData, vector<double> &yData, double x, bool extrapolate ){
   int size = xData.size();
   int i = 0;                                                                  // find left end of interval for interpolation
   if ( x >= xData[size - 2] ){                                                // special case: beyond right end
      i = size - 2;
   }
   else{
      while ( x > xData[i+1] ) i++;
   }
   double xL = xData[i], yL = yData[i], xR = xData[i+1], yR = yData[i+1];      // points on either side (unless beyond ends)
   if ( !extrapolate ){                                                        // if beyond ends of array and not extrapolating
      if ( x < xL ) yR = yL;
      if ( x > xR ) yL = yR;
   }
   double dydx = ( yR - yL ) / ( xR - xL );                                    // gradient
   return yL + dydx * ( x - xL );                                              // linear interpolation
}

int main()
{
    //----------------------------------- Initializing --------------------------------------
    outputTable finalResult;
    inputTable inputParameters;
    // double Inp[29] = {20, 200, 1, 1, 40, 35, 0.85, 200, 20, 8, 10000, 3000, 0.1, 0.6, 60, 0.1, 8, 72, 2,4.5, 0.84, 0.92, 2.7, 150, 200, 24, 1, 100, 0.09};
    double Inp[29] = {26, 280, 9, 28, 30, 60, 0.85, 150, 15, 11, 10000, 3300, 0.1, 0.6, 60, 0.1, 8, 22, 0.5,1.2, 0.84, 0.92, 3, 2100, 100, 24, 3, 100, 0.09};
    inputParameters.Temperature = Inp[0];
    inputParameters.So = Inp[1];
    inputParameters.Volume = Inp[2];
    inputParameters.FlowRate = Inp[3];
    inputParameters.InertVSS = Inp[4];
    inputParameters.OxidizableN = Inp[5];
    inputParameters.Biomass = Inp[6];
    inputParameters.InfluentTSS = Inp[7];
    inputParameters.InertInOrgTSS = Inp[8];
    inputParameters.EffluentTSS = Inp[9];
    inputParameters.RASTSS = Inp[10];
    inputParameters.MLSSpar = Inp[11];
    inputParameters.FractionBiomass = Inp[12];
    inputParameters.BiomassYeild = Inp[13];
    inputParameters.HalfSaturation = Inp[14];
    inputParameters.MicrobialDecay = Inp[15];
    inputParameters.MaxUtilizationRate = Inp[16];
    inputParameters.MaxDays = Inp[17];
    inputParameters.TimeIncrement = Inp[18];

    inputParameters.OperatingDO = Inp[19];
    inputParameters.Alpha = Inp[20];
    inputParameters.Beta = Inp[21];
    inputParameters.SOTR = Inp[22];
    inputParameters.Aeration = Inp[23];
    inputParameters.Elevation = Inp[24];
    inputParameters.OperatingTime = Inp[25];
    inputParameters.TypeAerators = Inp[26];
    inputParameters.Speed = Inp[27];
    inputParameters.EnergyCostUnit = Inp[28];
   
    //Adjustment Kd and K for temperture
    double AdjustedMicrobialDecay = inputParameters.MicrobialDecay * pow((1.04), (inputParameters.Temperature - 20.0));
    double AdjustedMaxUtilizationRate = inputParameters.MaxUtilizationRate * pow((1.07), (inputParameters.Temperature - 20.0));

    //----------------------------------- Aerator performance --------------------------------------
    double temp_abs = inputParameters.Temperature + 273.15;
    double cs = exp(-139.34411 + 157570.1 / temp_abs - 66423080 / pow(temp_abs, 2) + 12438000000 / pow(temp_abs, 3.0) - 862194900000 / pow(temp_abs, 4.0));
    double ro = -3.1682615629984E-05 * inputParameters.Elevation + 1.0;
    double ae = (inputParameters.SOTR * ((inputParameters.Beta * cs * ro) - inputParameters.OperatingDO) * inputParameters.Alpha * pow(1.024, (inputParameters.Temperature - 20))) / 9.17;
    finalResult.FieldOTR = ae;
    //Compute aerator energy usage 
    if ((inputParameters.TypeAerators == 1) || (inputParameters.TypeAerators == 2)) {
        finalResult.AeEnergy = inputParameters.Aeration * inputParameters.OperatingTime * (inputParameters.Speed/ 100) * 0.65 * 30;
    } else if (inputParameters.TypeAerators == 3) {
        finalResult.AeEnergy = inputParameters.Aeration * inputParameters.OperatingTime * pow(inputParameters.Speed/ 100, 3) * 0.65 * 30;
    } else {
        finalResult.AeEnergy = 0;
    }
    //Compute Aerator Energy Cost ($) for Current Conditions
    finalResult.AeCost = finalResult.AeEnergy * inputParameters.EnergyCostUnit;

    //----------------------------------- Current Conditions Calculation--------------------------------------
    int numberRows = round(inputParameters.MaxDays/inputParameters.TimeIncrement);
    std::vector<tableOfCalculations> calcTable(numberRows) ;
    for (int i = 0; i < numberRows + 1; i++) {
        calcTable[i].SRT = 1.0 + inputParameters.TimeIncrement*i;
    }
    //The main loop to make the calculations
    for (int i = 0; i < numberRows; i++) {
        // Compute Se
        calcTable[i].Se = (inputParameters.HalfSaturation * (1 + AdjustedMicrobialDecay * calcTable[i].SRT)) / (calcTable[i].SRT * (inputParameters.BiomassYeild * AdjustedMaxUtilizationRate - AdjustedMicrobialDecay) - 1);
        //Compute Heter Biomass
        calcTable[i].HeterBio = (calcTable[i].SRT / (inputParameters.Volume / inputParameters.FlowRate)) * inputParameters.BiomassYeild * (inputParameters.So - calcTable[i].Se) / (1 + AdjustedMicrobialDecay * calcTable[i].SRT);
        //Compute CellDeb
        calcTable[i].CellDeb = calcTable[i].HeterBio * inputParameters.FractionBiomass * AdjustedMicrobialDecay * calcTable[i].SRT;
        //Compute InterVes
        calcTable[i].InterVes = inputParameters.InertVSS * calcTable[i].SRT / (inputParameters.Volume / inputParameters.FlowRate);
        //Compute MLVSS
        calcTable[i].MLVSS = calcTable[i].HeterBio + calcTable[i].CellDeb + calcTable[i].InterVes;
        //Compute MLSS
        calcTable[i].MLSS = (calcTable[i].HeterBio + calcTable[i].CellDeb) / inputParameters.Biomass + calcTable[i].InterVes + inputParameters.InertInOrgTSS * calcTable[i].SRT / (inputParameters.Volume / inputParameters.FlowRate);
        //Compute BiomassProd
        calcTable[i].BiomassProd = (calcTable[i].HeterBio + calcTable[i].CellDeb) * inputParameters.Volume * 8.34 / calcTable[i].SRT;
        //Compute SludgeProd
        calcTable[i].SludgeProd = calcTable[i].MLVSS * inputParameters.Volume * 8.34 / calcTable[i].SRT;
        //Compute SolidProd
        calcTable[i].SolidProd = calcTable[i].MLSS * inputParameters.Volume * 8.34 / calcTable[i].SRT;
        //Compute Effluent
        calcTable[i].Effluent = inputParameters.EffluentTSS * inputParameters.FlowRate * 8.34;
        //Compue IntentWaste
        calcTable[i].IntentWaste = calcTable[i].SolidProd - calcTable[i].Effluent;
        //Compute OxygenRqd
        calcTable[i].OxygenRqd = 1.5 * inputParameters.FlowRate * (inputParameters.So - calcTable[i].Se) * 8.34 - 1.42 * calcTable[i].BiomassProd;
        //Compute FlowMgd
        calcTable[i].FlowMgd = calcTable[i].IntentWaste / (inputParameters.RASTSS * 8.34);
        //Compute NRemoved
        if  (calcTable[i].SRT < 40) {
            calcTable[i].NRemoved = calcTable[i].BiomassProd * (0.12 + (-0.001 * (calcTable[i].SRT - 1)));
        } else {
            calcTable[i].NRemoved = calcTable[i].BiomassProd * 0.08;
        }
        if (calcTable[i].NRemoved > inputParameters.FlowRate * inputParameters.OxidizableN * 8.34) {
            calcTable[i].NRemoved = inputParameters.FlowRate * inputParameters.OxidizableN * 8.34;
        }
        //Compute NremovedMgl
        calcTable[i].NRemovedMgl = calcTable[i].NRemoved / (inputParameters.FlowRate * 8.34);
        //Compute Fraction Nox : FrNox
        double FrNox;
        if (inputParameters.Temperature < 15) {
            if (calcTable[i].SRT < 40) {
                vector<double> xData = {  1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40 };
                vector<double> yData = {  0.1, 0.2, 0.3, 0.4, 0.6, 0.78, 0.88, 0.93, 0.955, 0.97, 0.98, 0.99 };
                FrNox = interpolate( xData, yData, calcTable[i].SRT, true);
            } else {FrNox = 0.99;}
        } else if (inputParameters.Temperature > 15 && inputParameters.Temperature < 24){
            if (calcTable[i].SRT < 40) {
                vector<double> xData = {  1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40 };
                vector<double> yData = {  0.1, 0.22, 0.33, 0.43, 0.63, 0.82, 0.92, 0.96, 0.975, 0.98, 0.99, 0.995 };
                FrNox = interpolate( xData, yData, calcTable[i].SRT, true);
            } else {FrNox = 0.995;}   
        } else {
            if (calcTable[i].SRT < 40) {
                vector<double> xData = {  1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40 };
                vector<double> yData = {  0.1, 0.25, 0.35, 0.45, 0.65, 0.85, 0.95, 0.98, 0.988, 0.99, 0.995, 0.999 };
                FrNox = interpolate( xData, yData, calcTable[i].SRT, true);
            } else {FrNox = 0.999;}
        }
        //Compute NitO2Dem
        calcTable[i].NitO2Dem = inputParameters.FlowRate * (inputParameters.OxidizableN - calcTable[i].NRemovedMgl) * 8.34 * 4.33 * FrNox;
        if (calcTable[i].NitO2Dem < 0) {calcTable[i].NitO2Dem = 0;} 
        //Compute O2Reqd
        calcTable[i].O2Reqd = calcTable[i].OxygenRqd + calcTable[i].NitO2Dem;
        //Compute EffNH3N
        calcTable[i].EffNH3N = (inputParameters.OxidizableN - calcTable[i].NRemovedMgl) * (1 - FrNox);
        if (calcTable[i].EffNH3N < 0) {calcTable[i].EffNH3N = 0;}
        //Compute EffNo3N
        if (inputParameters.OxidizableN > calcTable[i].NRemovedMgl && i > 0) {
                if (calcTable[i].SRT < 30) {
                    vector<double> xData = {  1, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32 };
                    vector<double> yData = {  0, 0.1, 0.25, 0.4, 0.5, 0.55, 0.58, 0.6, 0.62, 0.63, 0.65, 0.66, 0.68, 0.69, 0.7, 0.7};
                    double Coef = interpolate( xData, yData, calcTable[i].SRT, true);
                    calcTable[i].EffNo3N = (calcTable[0].EffNH3N - calcTable[i].EffNH3N) + Coef * (calcTable[0].NRemovedMgl - calcTable[i].NRemovedMgl);
                } else{
                    calcTable[i].EffNo3N = (calcTable[0].EffNH3N - calcTable[i].EffNH3N) + 0.7 * (calcTable[0].NRemovedMgl - calcTable[i].NRemovedMgl);
                    }
                if (calcTable[i].EffNo3N < 0) {calcTable[i].EffNo3N = 0;}
        } else {calcTable[i].EffNo3N = 0;}
        //Compute TotalO2Rqd
        calcTable[i].TotalO2Rqd = calcTable[i].O2Reqd - (inputParameters.FlowRate) * calcTable[i].EffNo3N * 8.34 * 2.86 * 0.7;
        //Compute WAS
        calcTable[i].WAS = calcTable[i].IntentWaste / (inputParameters.RASTSS * 8.34);
        //Compute EstimatedEff
        if (calcTable[i].SRT < 40) {
            calcTable[i].EstimatedEff = calcTable[i].Se + inputParameters.EffluentTSS * (-0.00000000014086 * pow(calcTable[i].SRT, 5) + 0.000000057556 * pow(calcTable[i].SRT , 4) - 0.0000091279 * pow(calcTable[i].SRT , 3) + 0.0007014 * pow(calcTable[i].SRT , 2) - 0.0262 * calcTable[i].SRT + 0.6322);
        } else {
            calcTable[i].EstimatedEff = calcTable[i].Se + inputParameters.EffluentTSS * (0.25);
        }
        if ((calcTable[i].MLSS / (inputParameters.RASTSS - calcTable[i].MLSS) * inputParameters.FlowRate) > 0) {
            calcTable[i].EstimRas = calcTable[i].MLSS / (inputParameters.RASTSS - calcTable[i].MLSS) * inputParameters.FlowRate;
        } else {calcTable[i].EstimRas = 0;}
        //Compute FmRatio
        calcTable[i].FmRatio = (inputParameters.So * inputParameters.FlowRate * 8.34) / (calcTable[i].MLVSS * inputParameters.Volume * 8.34);
        //Compute Square of Differences for The Best Match
        calcTable[i].Diff_MLSS = pow(calcTable[i].MLSS - inputParameters.MLSSpar, 2);
    }
    //end of for loop
    //Finding The best MLSS match
    int iCount = 0;
    double temp = calcTable[0].Diff_MLSS;
    for (int i = 1; i < numberRows ; i++)
        if (temp > calcTable[i].Diff_MLSS){
            iCount = i;
            temp = calcTable[i].Diff_MLSS;
        }
    //Setting the Output Table
    finalResult.TotalAverageDailyFlowRate = inputParameters.FlowRate;
    finalResult.VolumeInService = inputParameters.Volume;
    finalResult.InfluentBOD5Concentration = inputParameters.So;
    finalResult.InfluentBOD5MassLoading = inputParameters.So * inputParameters.FlowRate * 8.34;
    finalResult.SecWWOxidNLoad = inputParameters.FlowRate * inputParameters.OxidizableN * 8.34;
    finalResult.SecWWTSSLoad = inputParameters.FlowRate * inputParameters.InfluentTSS * 8.34;
    finalResult.FM_ratio = calcTable[iCount].FmRatio;
    finalResult.SolidsRetentionTime = calcTable[iCount].SRT;
    finalResult.MLSS = calcTable[iCount].MLSS;
    finalResult.MLVSS = calcTable[iCount].MLVSS;
    finalResult.TSSSludgeProduction = calcTable[iCount].IntentWaste;
    finalResult.TSSInActivatedSludgeEffluent = calcTable[iCount].Effluent;
    finalResult.TotalOxygenRequirements = calcTable[iCount].O2Reqd;
    finalResult.TotalOxygenReqWDenit = calcTable[iCount].TotalO2Rqd;
    finalResult.TotalOxygenSupplied = inputParameters.Aeration * inputParameters.OperatingTime * inputParameters.Speed * ae / 100;
    finalResult.MixingIntensityInReactor = (inputParameters.Aeration * inputParameters.Speed / 100) / inputParameters.Volume;
    finalResult.RASFlowRate = calcTable[iCount].EstimRas;
    finalResult.RASRecyclePercentage = calcTable[iCount].EstimRas / inputParameters.FlowRate * 100;
    finalResult.WASFlowRate = calcTable[iCount].WAS;
    finalResult.RASTSSConcentration = inputParameters.RASTSS;
    finalResult.TotalSludgeProduction = calcTable[iCount].SolidProd;
    finalResult.ReactorDetentionTime = inputParameters.Volume / inputParameters.FlowRate * 24;
    finalResult.VOLR = inputParameters.So * inputParameters.FlowRate * 8.34 / (inputParameters.Volume * 133.69);
    finalResult.EffluentCBOD5 = calcTable[iCount].EstimatedEff;
    finalResult.EffluentTSS = inputParameters.EffluentTSS;
    finalResult.EffluentAmmonia_N = calcTable[iCount].EffNH3N;
    finalResult.EffluentNO3_N = calcTable[iCount].EffNo3N;
    finalResult.EffluentNO3_N_W_Denit = calcTable[iCount].EffNo3N * 0.3;

    //----------------------------------- Print on console --------------------------------------    
    std::cout << "-----------------------------------Output of First Table"<< std::endl;
    std::cout <<"TotalAverageDailyFlowRate: "<< finalResult.TotalAverageDailyFlowRate<< std::endl;
    std::cout <<"VolumeInService: "<< finalResult.VolumeInService << std::endl;
    std::cout <<"InfluentBOD5Concentration: "<< finalResult.InfluentBOD5Concentration << std::endl;
    std::cout <<"InfluentBOD5MassLoading: "<< finalResult.InfluentBOD5MassLoading << std::endl;
    std::cout <<"SecWWOxidNLoad: "<< finalResult.SecWWOxidNLoad << std::endl;
    std::cout <<"SecWWTSSLoad: "<< finalResult.SecWWTSSLoad << std::endl;
    std::cout <<"FM_ratio: "<< finalResult.FM_ratio << std::endl;
    std::cout <<"SolidsRetentionTime: "<< finalResult.SolidsRetentionTime << std::endl;
    std::cout <<"MLSS: "<< finalResult.MLSS  << std::endl;
    std::cout <<"MLVSS: "<< finalResult.MLVSS  << std::endl;
    std::cout <<"TSSSludgeProduction: "<< finalResult.TSSSludgeProduction << std::endl;
    std::cout <<"TSSInActivatedSludgeEffluent: "<< finalResult.TSSInActivatedSludgeEffluent << std::endl;
    std::cout <<"TotalOxygenRequirements: "<< finalResult.TotalOxygenRequirements << std::endl;
    std::cout <<"TotalOxygenReqWDenit: "<< finalResult.TotalOxygenReqWDenit << std::endl;
    std::cout <<"TotalOxygenSupplied: "<< finalResult.TotalOxygenSupplied << std::endl;
    std::cout <<"MixingIntensityInReactor: "<< finalResult.MixingIntensityInReactor << std::endl;
    std::cout <<"RASFlowRate: "<< finalResult.RASFlowRate << std::endl;
    std::cout <<"RASRecyclePercentage: "<< finalResult.RASRecyclePercentage << std::endl;
    std::cout <<"WASFlowRate: "<< finalResult.WASFlowRate << std::endl;
    std::cout <<"RASTSSConcentration: "<< finalResult.RASTSSConcentration << std::endl;
    std::cout <<"TotalSludgeProduction: "<< finalResult.TotalSludgeProduction << std::endl;
    std::cout <<"ReactorDetentionTime: "<< finalResult.ReactorDetentionTime << std::endl;
    std::cout <<"VOLR: "<< finalResult.VOLR << std::endl;
    std::cout <<"EffluentCBOD5: "<< finalResult.EffluentCBOD5 << std::endl;
    std::cout <<"EffluentTSS: "<< finalResult.EffluentTSS << std::endl;
    std::cout <<"EffluentAmmonia_N: "<< finalResult.EffluentAmmonia_N << std::endl;
    std::cout <<"EffluentNO3_N: "<< finalResult.EffluentNO3_N << std::endl;
    std::cout <<"EffluentNO3_N_W_Denit: "<< finalResult.EffluentNO3_N_W_Denit << std::endl;
    std::cout << "-----------------------------------Output of Second Table"<< std::endl;
    std::cout <<"FieldOTR: "<<finalResult.FieldOTR << std::endl;
    std::cout <<"AeEnergy: "<<finalResult.AeEnergy << std::endl;
    std::cout <<"AeCost: "<<finalResult.AeCost << std::endl;
    
    std::cout << "-----------------------------------Output of First Table"<< std::endl;
    std::cout << finalResult.TotalAverageDailyFlowRate<< std::endl;
    std::cout << finalResult.VolumeInService << std::endl;
    std::cout << finalResult.InfluentBOD5Concentration << std::endl;
    std::cout << finalResult.InfluentBOD5MassLoading << std::endl;
    std::cout <<finalResult.SecWWOxidNLoad << std::endl;
    std::cout << finalResult.SecWWTSSLoad << std::endl;
    std::cout << finalResult.FM_ratio << std::endl;
    std::cout << finalResult.SolidsRetentionTime << std::endl;
    std::cout << finalResult.MLSS  << std::endl;
    std::cout << finalResult.MLVSS  << std::endl;
    std::cout << finalResult.TSSSludgeProduction << std::endl;
    std::cout << finalResult.TSSInActivatedSludgeEffluent << std::endl;
    std::cout << finalResult.TotalOxygenRequirements << std::endl;
    std::cout <<finalResult.TotalOxygenReqWDenit << std::endl;
    std::cout << finalResult.TotalOxygenSupplied << std::endl;
    std::cout << finalResult.MixingIntensityInReactor << std::endl;
    std::cout <<finalResult.RASFlowRate << std::endl;
    std::cout << finalResult.RASRecyclePercentage << std::endl;
    std::cout <<finalResult.WASFlowRate << std::endl;
    std::cout <<finalResult.RASTSSConcentration << std::endl;
    std::cout <<finalResult.TotalSludgeProduction << std::endl;
    std::cout << finalResult.ReactorDetentionTime << std::endl;
    std::cout <<finalResult.VOLR << std::endl;
    std::cout <<finalResult.EffluentCBOD5 << std::endl;
    std::cout <<finalResult.EffluentTSS << std::endl;
    std::cout << finalResult.EffluentAmmonia_N << std::endl;
    std::cout <<finalResult.EffluentNO3_N << std::endl;
    std::cout << finalResult.EffluentNO3_N_W_Denit << std::endl;
    std::cout << "-----------------------------------Output of Second Table"<< std::endl;
    std::cout <<"FieldOTR: "<<finalResult.FieldOTR << std::endl;
    std::cout <<"AeEnergy: "<<finalResult.AeEnergy << std::endl;
    std::cout <<"AeCost: "<<finalResult.AeCost << std::endl;
}





