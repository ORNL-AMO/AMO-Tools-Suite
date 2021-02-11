/**
 * @file
 * @brief contains logic to calculate wast water treatment results
 * 
 * @author Mark Root (mroot)
 * @author Mohsen Maniat
 * @bug No known bugs.
 *
 */

#include "wasteWater/WasteWater_Treatment.h"
#include <cmath>
#include <vector>
using namespace std;

double interpolate(vector<double> &xData, vector<double> &yData, double x, bool extrapolate)
{
    int size = xData.size();
    int i = 0; // find left end of interval for interpolation
    if (x >= xData[size - 2])
    { // special case: beyond right end
        i = size - 2;
    }
    else
    {
        while (x > xData[i + 1])
            i++;
    }
    double xL = xData[i], yL = yData[i], xR = xData[i + 1], yR = yData[i + 1]; // points on either side (unless beyond ends)
    if (!extrapolate)
    { // if beyond ends of array and not extrapolating
        if (x < xL)
            yR = yL;
        if (x > xR)
            yL = yR;
    }
    double dydx = (yR - yL) / (xR - xL); // gradient
    return yL + dydx * (x - xL);         // linear interpolation
}

WasteWater_Treatment::Output WasteWater_Treatment::calculate()
{
    double AdjustedMicrobialDecay = MicrobialDecay * pow((1.04), (Temperature - 20.0));
    double AdjustedMaxUtilizationRate = MaxUtilizationRate * pow((1.07), (Temperature - 20.0));

    //----------------------------------- Aerator performance --------------------------------------
    double temp_abs = Temperature + 273.15;
    double cs = exp(-139.34411 + 157570.1 / temp_abs - 66423080 / pow(temp_abs, 2) + 12438000000 / pow(temp_abs, 3.0) - 862194900000 / pow(temp_abs, 4.0));
    double ro = -3.1682615629984E-05 * Elevation + 1.0;
    double ae = (SOTR * ((Beta * cs * ro) - OperatingDO) * Alpha * pow(1.024, (Temperature - 20))) / 9.17;
    double FieldOTR = ae;
    //Compute aerator energy usage
    double AeEnergy = 0;
    if ((TypeAerators == 1) || (TypeAerators == 2))
    {
        AeEnergy = Aeration * OperatingTime * (Speed / 100) * 0.65 * 30;
    }
    else if (TypeAerators == 3)
    {
        AeEnergy = Aeration * OperatingTime * pow(Speed / 100, 3) * 0.65 * 30;
    }
    //Compute Aerator Energy Cost ($) for Current Conditions
    double AeCost = AeEnergy * EnergyCostUnit;

    //----------------------------------- Current Conditions Calculation--------------------------------------
    int numberRows = round(MaxDays / TimeIncrement);
    std::vector<CalculationsTable> calcTable(numberRows);
    for (int i = 0; i < numberRows; i++)
    {
        calcTable[i].SRT = 1.0 + TimeIncrement * i;
    }
    //The main loop to make the calculations
    for (int i = 0; i < numberRows; i++)
    {
        // Compute Se
        calcTable[i].Se = (HalfSaturation * (1 + AdjustedMicrobialDecay * calcTable[i].SRT)) / (calcTable[i].SRT * (BiomassYeild * AdjustedMaxUtilizationRate - AdjustedMicrobialDecay) - 1);
        //Compute Heter Biomass
        calcTable[i].HeterBio = (calcTable[i].SRT / (Volume / FlowRate)) * BiomassYeild * (So - calcTable[i].Se) / (1 + AdjustedMicrobialDecay * calcTable[i].SRT);
        //Compute CellDeb
        calcTable[i].CellDeb = calcTable[i].HeterBio * FractionBiomass * AdjustedMicrobialDecay * calcTable[i].SRT;
        //Compute InterVes
        calcTable[i].InterVes = InertVSS * calcTable[i].SRT / (Volume / FlowRate);
        //Compute MLVSS
        calcTable[i].MLVSS = calcTable[i].HeterBio + calcTable[i].CellDeb + calcTable[i].InterVes;
        //Compute MLSS
        calcTable[i].MLSS = (calcTable[i].HeterBio + calcTable[i].CellDeb) / Biomass + calcTable[i].InterVes + InertInOrgTSS * calcTable[i].SRT / (Volume / FlowRate);
        //Compute BiomassProd
        calcTable[i].BiomassProd = (calcTable[i].HeterBio + calcTable[i].CellDeb) * Volume * 8.34 / calcTable[i].SRT;
        //Compute SludgeProd
        calcTable[i].SludgeProd = calcTable[i].MLVSS * Volume * 8.34 / calcTable[i].SRT;
        //Compute SolidProd
        calcTable[i].SolidProd = calcTable[i].MLSS * Volume * 8.34 / calcTable[i].SRT;
        //Compute Effluent
        calcTable[i].Effluent = EffluentTSS * FlowRate * 8.34;
        //Compue IntentWaste
        calcTable[i].IntentWaste = calcTable[i].SolidProd - calcTable[i].Effluent;
        //Compute OxygenRqd
        calcTable[i].OxygenRqd = 1.5 * FlowRate * (So - calcTable[i].Se) * 8.34 - 1.42 * calcTable[i].BiomassProd;
        //Compute FlowMgd
        calcTable[i].FlowMgd = calcTable[i].IntentWaste / (RASTSS * 8.34);
        //Compute NRemoved
        if (calcTable[i].SRT < 40)
        {
            calcTable[i].NRemoved = calcTable[i].BiomassProd * (0.12 + (-0.001 * (calcTable[i].SRT - 1)));
        }
        else
        {
            calcTable[i].NRemoved = calcTable[i].BiomassProd * 0.08;
        }
        if (calcTable[i].NRemoved > FlowRate * OxidizableN * 8.34)
        {
            calcTable[i].NRemoved = FlowRate * OxidizableN * 8.34;
        }
        //Compute NremovedMgl
        calcTable[i].NRemovedMgl = calcTable[i].NRemoved / (FlowRate * 8.34);
        //Compute Fraction Nox : FrNox
        double FrNox;
        if (Temperature < 15)
        {
            if (calcTable[i].SRT < 40)
            {
                vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
                vector<double> yData = {0.1, 0.2, 0.3, 0.4, 0.6, 0.78, 0.88, 0.93, 0.955, 0.97, 0.98, 0.99};
                FrNox = interpolate(xData, yData, calcTable[i].SRT, true);
            }
            else
            {
                FrNox = 0.99;
            }
        }
        else if (Temperature > 15 && Temperature < 24)
        {
            if (calcTable[i].SRT < 40)
            {
                vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
                vector<double> yData = {0.1, 0.22, 0.33, 0.43, 0.63, 0.82, 0.92, 0.96, 0.975, 0.98, 0.99, 0.995};
                FrNox = interpolate(xData, yData, calcTable[i].SRT, true);
            }
            else
            {
                FrNox = 0.995;
            }
        }
        else
        {
            if (calcTable[i].SRT < 40)
            {
                vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
                vector<double> yData = {0.1, 0.25, 0.35, 0.45, 0.65, 0.85, 0.95, 0.98, 0.988, 0.99, 0.995, 0.999};
                FrNox = interpolate(xData, yData, calcTable[i].SRT, true);
            }
            else
            {
                FrNox = 0.999;
            }
        }
        //Compute NitO2Dem
        calcTable[i].NitO2Dem = FlowRate * (OxidizableN - calcTable[i].NRemovedMgl) * 8.34 * 4.33 * FrNox;
        if (calcTable[i].NitO2Dem < 0)
        {
            calcTable[i].NitO2Dem = 0;
        }
        //Compute O2Reqd
        calcTable[i].O2Reqd = calcTable[i].OxygenRqd + calcTable[i].NitO2Dem;
        //Compute EffNH3N
        calcTable[i].EffNH3N = (OxidizableN - calcTable[i].NRemovedMgl) * (1 - FrNox);
        if (calcTable[i].EffNH3N < 0)
        {
            calcTable[i].EffNH3N = 0;
        }
        //Compute EffNo3N
        if (OxidizableN > calcTable[i].NRemovedMgl && i > 0)
        {
            if (calcTable[i].SRT < 30)
            {
                vector<double> xData = {1, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
                vector<double> yData = {0, 0.1, 0.25, 0.4, 0.5, 0.55, 0.58, 0.6, 0.62, 0.63, 0.65, 0.66, 0.68, 0.69, 0.7, 0.7};
                double Coef = interpolate(xData, yData, calcTable[i].SRT, true);
                calcTable[i].EffNo3N = (calcTable[0].EffNH3N - calcTable[i].EffNH3N) + Coef * (calcTable[0].NRemovedMgl - calcTable[i].NRemovedMgl);
            }
            else
            {
                calcTable[i].EffNo3N = (calcTable[0].EffNH3N - calcTable[i].EffNH3N) + 0.7 * (calcTable[0].NRemovedMgl - calcTable[i].NRemovedMgl);
            }
            if (calcTable[i].EffNo3N < 0)
            {
                calcTable[i].EffNo3N = 0;
            }
        }
        else
        {
            calcTable[i].EffNo3N = 0;
        }
        //Compute TotalO2Rqd
        calcTable[i].TotalO2Rqd = calcTable[i].O2Reqd - (FlowRate)*calcTable[i].EffNo3N * 8.34 * 2.86 * 0.7;
        //Compute WAS
        calcTable[i].WAS = calcTable[i].IntentWaste / (RASTSS * 8.34);
        //Compute EstimatedEff
        if (calcTable[i].SRT < 40)
        {
            calcTable[i].EstimatedEff = calcTable[i].Se + EffluentTSS * (-0.00000000014086 * pow(calcTable[i].SRT, 5) + 0.000000057556 * pow(calcTable[i].SRT, 4) - 0.0000091279 * pow(calcTable[i].SRT, 3) + 0.0007014 * pow(calcTable[i].SRT, 2) - 0.0262 * calcTable[i].SRT + 0.6322);
        }
        else
        {
            calcTable[i].EstimatedEff = calcTable[i].Se + EffluentTSS * (0.25);
        }
        if ((calcTable[i].MLSS / (RASTSS - calcTable[i].MLSS) * FlowRate) > 0)
        {
            calcTable[i].EstimRas = calcTable[i].MLSS / (RASTSS - calcTable[i].MLSS) * FlowRate;
        }
        else
        {
            calcTable[i].EstimRas = 0;
        }
        //Compute FmRatio
        calcTable[i].FmRatio = (So * FlowRate * 8.34) / (calcTable[i].MLVSS * Volume * 8.34);
        //Compute Square of Differences for The Best Match
        calcTable[i].Diff_MLSS = pow(calcTable[i].MLSS - MLSSpar, 2);
    }
    //end of for loop
    //Finding The best MLSS match
    int iCount = 0;
    double temp = calcTable[0].Diff_MLSS;
    for (int i = 1; i < numberRows; i++)
        if (temp > calcTable[i].Diff_MLSS)
        {
            iCount = i;
            temp = calcTable[i].Diff_MLSS;
        }
    //Setting the Output Table
    double TotalAverageDailyFlowRate = FlowRate;
    double VolumeInService = Volume;
    double InfluentBOD5Concentration = So;
    double InfluentBOD5MassLoading = So * FlowRate * 8.34;
    double SecWWOxidNLoad = FlowRate * OxidizableN * 8.34;
    double SecWWTSSLoad = FlowRate * InfluentTSS * 8.34;
    double FM_ratio = calcTable[iCount].FmRatio;
    double SolidsRetentionTime = calcTable[iCount].SRT;
    double MLSS = calcTable[iCount].MLSS;
    double MLVSS = calcTable[iCount].MLVSS;
    double TSSSludgeProduction = calcTable[iCount].IntentWaste;
    double TSSInActivatedSludgeEffluent = calcTable[iCount].Effluent;
    double TotalOxygenRequirements = calcTable[iCount].O2Reqd;
    double TotalOxygenReqWDenit = calcTable[iCount].TotalO2Rqd;
    double TotalOxygenSupplied = Aeration * OperatingTime * Speed * ae / 100;
    double MixingIntensityInReactor = (Aeration * Speed / 100) / Volume;
    double RASFlowRate = calcTable[iCount].EstimRas;
    double RASRecyclePercentage = calcTable[iCount].EstimRas / FlowRate * 100;
    double WASFlowRate = calcTable[iCount].WAS;
    double RASTSSConcentration = RASTSS;
    double TotalSludgeProduction = calcTable[iCount].SolidProd;
    double ReactorDetentionTime = Volume / FlowRate * 24;
    double VOLR = So * FlowRate * 8.34 / (Volume * 133.69);
    double EffluentCBOD5 = calcTable[iCount].EstimatedEff;
    double EffluentAmmonia_N = calcTable[iCount].EffNH3N;
    double EffluentNO3_N = calcTable[iCount].EffNo3N;
    double EffluentNO3_N_W_Denit = calcTable[iCount].EffNo3N * 0.3;

    WasteWater_Treatment::Output output(
        TotalAverageDailyFlowRate,
        VolumeInService,
        InfluentBOD5Concentration,
        InfluentBOD5MassLoading,
        SecWWOxidNLoad,
        SecWWTSSLoad,
        FM_ratio,
        SolidsRetentionTime,
        MLSS,
        MLVSS,
        TSSSludgeProduction,
        TSSInActivatedSludgeEffluent,
        TotalOxygenRequirements,
        TotalOxygenReqWDenit,
        TotalOxygenSupplied,
        MixingIntensityInReactor,
        RASFlowRate,
        RASRecyclePercentage,
        WASFlowRate,
        RASTSSConcentration,
        TotalSludgeProduction,
        ReactorDetentionTime,
        VOLR,
        EffluentCBOD5,
        EffluentTSS,
        EffluentAmmonia_N,
        EffluentNO3_N,
        EffluentNO3_N_W_Denit,
        AeEnergy,
        AeCost,
        FieldOTR,
        calcTable);
    return output;
}

WasteWater_Treatment::OutputWithoutTable WasteWater_Treatment::calculateGivenSRT()
{

    double AdjustedMicrobialDecay = MicrobialDecay * pow((1.04), (Temperature - 20.0));
    double AdjustedMaxUtilizationRate = MaxUtilizationRate * pow((1.07), (Temperature - 20.0));

    //----------------------------------- Aerator performance --------------------------------------
    double temp_abs = Temperature + 273.15;
    double cs = exp(-139.34411 + 157570.1 / temp_abs - 66423080 / pow(temp_abs, 2) + 12438000000 / pow(temp_abs, 3.0) - 862194900000 / pow(temp_abs, 4.0));
    double ro = -3.1682615629984E-05 * Elevation + 1.0;
    double ae = (SOTR * ((Beta * cs * ro) - OperatingDO) * Alpha * pow(1.024, (Temperature - 20))) / 9.17;
    double FieldOTR = ae;
    //Compute aerator energy usage
    double AeEnergy = 0;
    if ((TypeAerators == 1) || (TypeAerators == 2))
    {
        AeEnergy = Aeration * OperatingTime * (Speed / 100) * 0.65 * 30;
    }
    else if (TypeAerators == 3)
    {
        AeEnergy = Aeration * OperatingTime * pow(Speed / 100, 3) * 0.65 * 30;
    }
    //Compute Aerator Energy Cost ($) for Current Conditions
    double AeCost = AeEnergy * EnergyCostUnit;

    //----------------------------------- Current Conditions Calculation--------------------------------------

    // Compute Se
    double Se = (HalfSaturation * (1 + AdjustedMicrobialDecay * DefinedSRT)) / (DefinedSRT * (BiomassYeild * AdjustedMaxUtilizationRate - AdjustedMicrobialDecay) - 1);
    double SeSRT1 = (HalfSaturation * (1 + AdjustedMicrobialDecay * 1)) / (1 * (BiomassYeild * AdjustedMaxUtilizationRate - AdjustedMicrobialDecay) - 1);
    //Compute Heter Biomass
    double HeterBio = (DefinedSRT / (Volume / FlowRate)) * BiomassYeild * (So - Se) / (1 + AdjustedMicrobialDecay * DefinedSRT);
    double HeterBioSRT1 = (1 / (Volume / FlowRate)) * BiomassYeild * (So - SeSRT1) / (1 + AdjustedMicrobialDecay * 1);
    //Compute CellDeb
    double CellDeb = HeterBio * FractionBiomass * AdjustedMicrobialDecay * DefinedSRT;
    double CellDebSRT1 = HeterBioSRT1 * FractionBiomass * AdjustedMicrobialDecay * 1;
    //Compute InterVes
    double InterVes = InertVSS * DefinedSRT / (Volume / FlowRate);
    //Compute MLVSS
    double MLVSS = HeterBio + CellDeb + InterVes;
    //Compute MLSS
    double MLSS = (HeterBio + CellDeb) / Biomass + InterVes + InertInOrgTSS * DefinedSRT / (Volume / FlowRate);
    //Compute BiomassProd
    double BiomassProd = (HeterBio + CellDeb) * Volume * 8.34 / DefinedSRT;
    double BiomassProdSRT1 = (HeterBioSRT1 + CellDebSRT1) * Volume * 8.34 / 1;
    //Compute SludgeProd
    double SludgeProd = MLVSS * Volume * 8.34 / DefinedSRT;
    //Compute SolidProd
    double SolidProd = MLSS * Volume * 8.34 / DefinedSRT;
    //Compute Effluent
    double Effluent = EffluentTSS * FlowRate * 8.34;
    //Compue IntentWaste
    double IntentWaste = SolidProd - Effluent;
    //Compute OxygenRqd
    double OxygenRqd = 1.5 * FlowRate * (So - Se) * 8.34 - 1.42 * BiomassProd;
    //Compute FlowMgd
    double FlowMgd = IntentWaste / (RASTSS * 8.34);
    //Compute NRemoved
    double NRemoved;
    if (DefinedSRT < 40)
    {
        NRemoved = BiomassProd * (0.12 + (-0.001 * (DefinedSRT - 1)));
    }
    else
    {
        NRemoved = BiomassProd * 0.08;
    }
    if (NRemoved > FlowRate * OxidizableN * 8.34)
    {
        NRemoved = FlowRate * OxidizableN * 8.34;
    }

    double NRemovedSRT1 = BiomassProdSRT1 * 0.12;
    if (NRemovedSRT1 > FlowRate * OxidizableN * 8.34)
    {
        NRemovedSRT1 = FlowRate * OxidizableN * 8.34;
    }

    //Compute NremovedMgl
    double NRemovedMgl = NRemoved / (FlowRate * 8.34);
    double NRemovedMglSRT1 = NRemovedSRT1 / (FlowRate * 8.34);
    //Compute Fraction Nox : FrNox
    double FrNox;
    double FrNoxSRT1;
    if (Temperature < 15)
    {
        vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
        vector<double> yData = {0.1, 0.2, 0.3, 0.4, 0.6, 0.78, 0.88, 0.93, 0.955, 0.97, 0.98, 0.99};
        FrNoxSRT1 = interpolate(xData, yData, 1, true);
        if (DefinedSRT < 40)
        {
            FrNox = interpolate(xData, yData, DefinedSRT, true);
        }
        else
        {
            FrNox = 0.99;
        }
    }
    else if (Temperature > 15 && Temperature < 24)
    {
        vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
        vector<double> yData = {0.1, 0.22, 0.33, 0.43, 0.63, 0.82, 0.92, 0.96, 0.975, 0.98, 0.99, 0.995};
        FrNoxSRT1 = interpolate(xData, yData, 1, true);
        if (DefinedSRT < 40)
        {
            FrNox = interpolate(xData, yData, DefinedSRT, true);
        }
        else
        {
            FrNox = 0.995;
        }
    }
    else
    {
        vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
        vector<double> yData = {0.1, 0.25, 0.35, 0.45, 0.65, 0.85, 0.95, 0.98, 0.988, 0.99, 0.995, 0.999};
        FrNoxSRT1 = interpolate(xData, yData, 1, true);
        if (DefinedSRT < 40)
        {
            FrNox = interpolate(xData, yData, DefinedSRT, true);
        }
        else
        {
            FrNox = 0.999;
        }
    }
    //Compute NitO2Dem
    double NitO2Dem = FlowRate * (OxidizableN - NRemovedMgl) * 8.34 * 4.33 * FrNox;
    if (NitO2Dem < 0)
    {
        NitO2Dem = 0;
    }
    //Compute O2Reqd
    double O2Reqd = OxygenRqd + NitO2Dem;
    //Compute EffNH3N
    double EffNH3N = (OxidizableN - NRemovedMgl) * (1 - FrNox);
    if (EffNH3N < 0)
    {
        EffNH3N = 0;
    }

    double EffNH3NSRT1 = (OxidizableN - NRemovedMglSRT1) * (1 - FrNoxSRT1);
    if (EffNH3NSRT1 < 0)
    {
        EffNH3NSRT1 = 0;
    }
    //Compute EffNo3N
    double EffNo3N;
    if (OxidizableN > NRemovedMgl)
    {
        if (DefinedSRT < 30)
        {
            vector<double> xData = {1, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
            vector<double> yData = {0, 0.1, 0.25, 0.4, 0.5, 0.55, 0.58, 0.6, 0.62, 0.63, 0.65, 0.66, 0.68, 0.69, 0.7, 0.7};
            double Coef = interpolate(xData, yData, DefinedSRT, true);
            EffNo3N = (EffNH3NSRT1 - EffNH3N) + Coef * (NRemovedMglSRT1 - NRemovedMgl);
        }
        else
        {
            EffNo3N = (EffNH3NSRT1 - EffNH3N) + 0.7 * (NRemovedMglSRT1 - NRemovedMgl);
        }
        if (EffNo3N < 0)
        {
            EffNo3N = 0;
        }
    }
    else
    {
        EffNo3N = 0;
    }
    //Compute TotalO2Rqd
    double TotalO2Rqd = O2Reqd - (FlowRate)*EffNo3N * 8.34 * 2.86 * 0.7;
    //Compute WAS
    double WAS = IntentWaste / (RASTSS * 8.34);
    //Compute EstimatedEff
    double EstimatedEff;
    double EstimRas;
    if (DefinedSRT < 40)
    {
        EstimatedEff = Se + EffluentTSS * (-0.00000000014086 * pow(DefinedSRT, 5) + 0.000000057556 * pow(DefinedSRT, 4) - 0.0000091279 * pow(DefinedSRT, 3) + 0.0007014 * pow(DefinedSRT, 2) - 0.0262 * DefinedSRT + 0.6322);
    }
    else
    {
        EstimatedEff = Se + EffluentTSS * (0.25);
    }
    if ((MLSS / (RASTSS - MLSS) * FlowRate) > 0)
    {
        EstimRas = MLSS / (RASTSS - MLSS) * FlowRate;
    }
    else
    {
        EstimRas = 0;
    }
    //Compute FmRatio
    double FmRatio = (So * FlowRate * 8.34) / (MLVSS * Volume * 8.34);
    //Compute Square of Differences for The Best Match
    double Diff_MLSS = pow(MLSS - MLSSpar, 2);

    //Setting the Output Table
    double TotalAverageDailyFlowRate = FlowRate;
    double VolumeInService = Volume;
    double InfluentBOD5Concentration = So;
    double InfluentBOD5MassLoading = So * FlowRate * 8.34;
    double SecWWOxidNLoad = FlowRate * OxidizableN * 8.34;
    double SecWWTSSLoad = FlowRate * InfluentTSS * 8.34;
    double FM_ratio = FmRatio;
    // double SolidsRetentionTime = SRT;
    // double MLSS = MLSS;
    // double MLVSS = MLVSS;
    double TSSSludgeProduction = IntentWaste;
    double TSSInActivatedSludgeEffluent = Effluent;
    double TotalOxygenRequirements = O2Reqd;
    double TotalOxygenReqWDenit = TotalO2Rqd;
    double TotalOxygenSupplied = Aeration * OperatingTime * Speed * ae / 100;
    double MixingIntensityInReactor = (Aeration * Speed / 100) / Volume;
    double RASFlowRate = EstimRas;
    double RASRecyclePercentage = EstimRas / FlowRate * 100;
    double WASFlowRate = WAS;
    double RASTSSConcentration = RASTSS;
    double TotalSludgeProduction = SolidProd;
    double ReactorDetentionTime = Volume / FlowRate * 24;
    double VOLR = So * FlowRate * 8.34 / (Volume * 133.69);
    double EffluentCBOD5 = EstimatedEff;
    double EffluentAmmonia_N = EffNH3N;
    double EffluentNO3_N = EffNo3N;
    double EffluentNO3_N_W_Denit = EffNo3N * 0.3;

    WasteWater_Treatment::OutputWithoutTable outputWithoutTable(
        TotalAverageDailyFlowRate,
        VolumeInService,
        InfluentBOD5Concentration,
        InfluentBOD5MassLoading,
        SecWWOxidNLoad,
        SecWWTSSLoad,
        FM_ratio,
        DefinedSRT,
        MLSS,
        MLVSS,
        TSSSludgeProduction,
        TSSInActivatedSludgeEffluent,
        TotalOxygenRequirements,
        TotalOxygenReqWDenit,
        TotalOxygenSupplied,
        MixingIntensityInReactor,
        RASFlowRate,
        RASRecyclePercentage,
        WASFlowRate,
        RASTSSConcentration,
        TotalSludgeProduction,
        ReactorDetentionTime,
        VOLR,
        EffluentCBOD5,
        EffluentTSS,
        EffluentAmmonia_N,
        EffluentNO3_N,
        EffluentNO3_N_W_Denit,
        AeEnergy,
        AeCost,
        FieldOTR);
    return outputWithoutTable;
}
