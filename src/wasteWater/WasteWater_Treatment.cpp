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

double calculateAdjustedMicrobialDecay(double MicrobialDecay, double Temperature)
{
    return MicrobialDecay * pow((1.04), (Temperature - 20.0));
}

double calculateAdjustedMaxUtilizationRate(double MaxUtilizationRate, double Temperature)
{
    return MaxUtilizationRate * pow((1.07), (Temperature - 20.0));
}

double calculateFieldOTR(double Temperature, double Elevation, double SOTR, double Beta, double OperatingDO, double Alpha)
{
    double temp_abs = Temperature + 273.15;
    double cs = exp(-139.34411 + 157570.1 / temp_abs - 66423080 / pow(temp_abs, 2) + 12438000000 / pow(temp_abs, 3.0) - 862194900000 / pow(temp_abs, 4.0));
    double ro = -3.1682615629984E-05 * Elevation + 1.0;
    double ae = (SOTR * ((Beta * cs * ro) - OperatingDO) * Alpha * pow(1.024, (Temperature - 20))) / 9.17;
    return ae;
}

double calculateAeEnergy(double TypeAerators, double Aeration, double OperatingTime, double Speed)
{
    if ((TypeAerators == 1) || (TypeAerators == 2))
    {
        return Aeration * OperatingTime * (Speed / 100) * 0.65 * 30;
    }
    else if (TypeAerators == 3)
    {
        return Aeration * OperatingTime * pow(Speed / 100, 3) * 0.65 * 30;
    }
    return 0;
}

double calculateSe(double HalfSaturation, double AdjustedMicrobialDecay, double SRT, double BiomassYeild, double AdjustedMaxUtilizationRate)
{
    return (HalfSaturation * (1 + AdjustedMicrobialDecay * SRT)) / (SRT * (BiomassYeild * AdjustedMaxUtilizationRate - AdjustedMicrobialDecay) - 1);
}

double calculateHeterBio(double SRT, double Volume, double FlowRate, double BiomassYeild, double So, double Se, double AdjustedMicrobialDecay)
{
    return (SRT / (Volume / FlowRate)) * BiomassYeild * (So - Se) / (1 + AdjustedMicrobialDecay * SRT);
}

double calculateCellDeb(double HeterBio, double FractionBiomass, double AdjustedMicrobialDecay, double SRT)
{
    return HeterBio * FractionBiomass * AdjustedMicrobialDecay * SRT;
}

double calculateInerVes(double InertVSS, double SRT, double Volume, double FlowRate)
{
    return InertVSS * SRT / (Volume / FlowRate);
}

double calculateMLVSS(double HeterBio, double CellDeb, double InterVes)
{
    return HeterBio + CellDeb + InterVes;
}

double calculateMLSS(double HeterBio, double CellDeb, double Biomass, double InterVes, double InertInOrgTSS, double SRT, double Volume, double FlowRate)
{
    return (HeterBio + CellDeb) / Biomass + InterVes + InertInOrgTSS * SRT / (Volume / FlowRate);
}

double calculateBiomassProd(double HeterBio, double CellDeb, double Volume, double SRT)
{
    return (HeterBio + CellDeb) * Volume * 8.34 / SRT;
}

double calculateSludgeProd(double MLVSS, double Volume, double SRT)
{
    return MLVSS * Volume * 8.34 / SRT;
}

double calculateSolidProd(double MLSS, double Volume, double SRT)
{
    return MLSS * Volume * 8.34 / SRT;
}

double calculateEffluent(double EffluentTSS, double FlowRate)
{
    return EffluentTSS * FlowRate * 8.34;
}

double calculateIntentWaste(double SolidProd, double Effluent)
{
    return SolidProd - Effluent;
}

double calculateOxygenRqd(double FlowRate, double So, double Se, double BiomassProd)
{
    return 1.5 * FlowRate * (So - Se) * 8.34 - 1.42 * BiomassProd;
}

double calculateFlowMgd(double IntentWaste, double RASTSS)
{
    return IntentWaste / (RASTSS * 8.34);
}

double calculateNRemoved(double SRT, double BiomassProd, double FlowRate, double OxidizableN)
{
    double NRemoved = 0;
    if (SRT < 40)
    {
        NRemoved = BiomassProd * (0.12 + (-0.001 * (SRT - 1)));
    }
    else
    {
        NRemoved = BiomassProd * 0.08;
    }
    if (NRemoved > FlowRate * OxidizableN * 8.34)
    {
        NRemoved = FlowRate * OxidizableN * 8.34;
    }
    return NRemoved;
}

double calculateNRemoveMgl(double NRemoved, double FlowRate)
{
    return NRemoved / (FlowRate * 8.34);
}

double calculateFrNox(double Temperature, double SRT)
{
    double FrNox;
    if (Temperature < 15)
    {
        if (SRT < 40)
        {
            vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
            vector<double> yData = {0.1, 0.2, 0.3, 0.4, 0.6, 0.78, 0.88, 0.93, 0.955, 0.97, 0.98, 0.99};
            FrNox = interpolate(xData, yData, SRT, true);
        }
        else
        {
            FrNox = 0.99;
        }
    }
    else if (Temperature > 15 && Temperature < 24)
    {
        if (SRT < 40)
        {
            vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
            vector<double> yData = {0.1, 0.22, 0.33, 0.43, 0.63, 0.82, 0.92, 0.96, 0.975, 0.98, 0.99, 0.995};
            FrNox = interpolate(xData, yData, SRT, true);
        }
        else
        {
            FrNox = 0.995;
        }
    }
    else
    {
        if (SRT < 40)
        {
            vector<double> xData = {1, 2, 3, 4, 6, 8, 10, 12, 15, 20, 30, 40};
            vector<double> yData = {0.1, 0.25, 0.35, 0.45, 0.65, 0.85, 0.95, 0.98, 0.988, 0.99, 0.995, 0.999};
            FrNox = interpolate(xData, yData, SRT, true);
        }
        else
        {
            FrNox = 0.999;
        }
    }
    return FrNox;
}

double calculateNitO2Dem(double FlowRate, double OxidizableN, double NRemovedMgl, double FrNox)
{
    double NitO2Dem = FlowRate * (OxidizableN - NRemovedMgl) * 8.34 * 4.33 * FrNox;
    if (NitO2Dem < 0)
    {
        NitO2Dem = 0;
    }
    return NitO2Dem;
}

double calculateO2Reqd(double OxygenRqd, double NitO2Dem)
{
    return OxygenRqd + NitO2Dem;
}

double calculateEffNH3N(double OxidizableN, double NRemovedMgl, double FrNox)
{
    double EffNH3N = (OxidizableN - NRemovedMgl) * (1 - FrNox);
    if (EffNH3N < 0)
    {
        EffNH3N = 0;
    }
    return EffNH3N;
}

double calculateEffNo3N(double OxidizableN, double NRemovedMgl, double SRT, double EffNH3N, double i, double EffNH3NSRT1, double NRemovedMglSRT1)
{
    double EffNo3N;
    if (OxidizableN > NRemovedMgl && i > 0)
    {
        if (SRT < 30)
        {
            vector<double> xData = {1, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32};
            vector<double> yData = {0, 0.1, 0.25, 0.4, 0.5, 0.55, 0.58, 0.6, 0.62, 0.63, 0.65, 0.66, 0.68, 0.69, 0.7, 0.7};
            double Coef = interpolate(xData, yData, SRT, true);
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
    return EffNo3N;
}

double calculateWAS(double IntentWaste, double RASTSS)
{
    return IntentWaste / (RASTSS * 8.34);
}

double calculateEstimatedEff(double SRT, double Se, double EffluentTSS)
{
    if (SRT < 40)
    {
        return Se + EffluentTSS * (-0.00000000014086 * pow(SRT, 5) + 0.000000057556 * pow(SRT, 4) - 0.0000091279 * pow(SRT, 3) + 0.0007014 * pow(SRT, 2) - 0.0262 * SRT + 0.6322);
    }
    else
    {
        return Se + EffluentTSS * (0.25);
    }
}

double calculateEstimRas(double MLSS, double RASTSS, double FlowRate)
{
    if ((MLSS / (RASTSS - MLSS) * FlowRate) > 0)
    {
        return MLSS / (RASTSS - MLSS) * FlowRate;
    }
    else
    {
        return 0;
    }
}

double calculateFmRatio(double So, double FlowRate, double MLVSS, double Volume)
{
    return (So * FlowRate * 8.34) / (MLVSS * Volume * 8.34);
}

double calculateTotalO2Rqd(double O2Reqd, double FlowRate, double EffNo3N)
{
    return O2Reqd - (FlowRate)*EffNo3N * 8.34 * 2.86 * 0.7;
}
WasteWater_Treatment::Output WasteWater_Treatment::calculate()
{
    double AdjustedMicrobialDecay = calculateAdjustedMicrobialDecay(MicrobialDecay, Temperature);
    double AdjustedMaxUtilizationRate = calculateAdjustedMaxUtilizationRate(MaxUtilizationRate, Temperature);
    //----------------------------------- Aerator performance --------------------------------------
    double FieldOTR = calculateFieldOTR(Temperature, Elevation, SOTR, Beta, OperatingDO, Alpha);
    //Compute aerator energy usage
    double AeEnergy = calculateAeEnergy(TypeAerators, Aeration, OperatingTime, Speed);
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
        calcTable[i].Se = calculateSe(HalfSaturation, AdjustedMicrobialDecay, calcTable[i].SRT, BiomassYeild, AdjustedMaxUtilizationRate);
        //Compute Heter Biomass
        calcTable[i].HeterBio = calculateHeterBio(calcTable[i].SRT, Volume, FlowRate, BiomassYeild, So, calcTable[i].Se, AdjustedMicrobialDecay);
        //Compute CellDeb
        calcTable[i].CellDeb = calculateCellDeb(calcTable[i].HeterBio, FractionBiomass, AdjustedMicrobialDecay, calcTable[i].SRT);
        //Compute InterVes
        calcTable[i].InterVes = calculateInerVes(InertVSS, calcTable[i].SRT, Volume, FlowRate);
        //Compute MLVSS
        calcTable[i].MLVSS = calculateMLVSS(calcTable[i].HeterBio, calcTable[i].CellDeb, calcTable[i].InterVes);
        //Compute MLSS
        calcTable[i].MLSS = calculateMLSS(calcTable[i].HeterBio, calcTable[i].CellDeb, Biomass, calcTable[i].InterVes, InertInOrgTSS, calcTable[i].SRT, Volume, FlowRate);
        //Compute BiomassProd
        calcTable[i].BiomassProd = calculateBiomassProd(calcTable[i].HeterBio, calcTable[i].CellDeb, Volume, calcTable[i].SRT);
        //Compute SludgeProd
        calcTable[i].SludgeProd = calculateSludgeProd(calcTable[i].MLVSS, Volume, calcTable[i].SRT);
        //Compute SolidProd
        calcTable[i].SolidProd = calculateSolidProd(calcTable[i].MLSS, Volume, calcTable[i].SRT);
        //Compute Effluent
        calcTable[i].Effluent = calculateEffluent(EffluentTSS, FlowRate);
        //Compue IntentWaste
        calcTable[i].IntentWaste = calculateIntentWaste(calcTable[i].SolidProd, calcTable[i].Effluent);
        //Compute OxygenRqd
        calcTable[i].OxygenRqd = calculateOxygenRqd(FlowRate, So, calcTable[i].Se, calcTable[i].BiomassProd);
        //Compute FlowMgd
        calcTable[i].FlowMgd = calculateFlowMgd(calcTable[i].IntentWaste, RASTSS);
        //Compute NRemoved
        calcTable[i].NRemoved = calculateNRemoved(calcTable[i].SRT, calcTable[i].BiomassProd, FlowRate, OxidizableN);
        //Compute NremovedMgl
        calcTable[i].NRemovedMgl = calculateNRemoveMgl(calcTable[i].NRemoved, FlowRate);
        //Compute Fraction Nox : FrNox
        double FrNox = calculateFrNox(Temperature, calcTable[i].SRT);
        //Compute NitO2Dem
        calcTable[i].NitO2Dem = calculateNitO2Dem(FlowRate, OxidizableN, calcTable[i].NRemovedMgl, FrNox);
        //Compute O2Reqd
        calcTable[i].O2Reqd = calculateO2Reqd(calcTable[i].OxygenRqd, calcTable[i].NitO2Dem);
        //Compute EffNH3N
        calcTable[i].EffNH3N = calculateEffNH3N(OxidizableN, calcTable[i].NRemovedMgl, FrNox);
        //Compute EffNo3N
        calcTable[i].EffNo3N = calculateEffNo3N(OxidizableN, calcTable[i].NRemovedMgl, calcTable[i].SRT, calcTable[i].EffNH3N, i, calcTable[0].EffNH3N, calcTable[0].NRemovedMgl);
        //Compute TotalO2Rqd
        calcTable[i].TotalO2Rqd = calculateTotalO2Rqd(calcTable[i].O2Reqd, FlowRate, calcTable[i].EffNo3N);
        //Compute WAS
        calcTable[i].WAS = calculateWAS(calcTable[i].IntentWaste, RASTSS);
        //Compute EstimatedEff
        calcTable[i].EstimatedEff = calculateEstimatedEff(calcTable[i].SRT, calcTable[i].Se, EffluentTSS);
        //Compute EstimRas
        calcTable[i].EstimRas = calculateEstimRas(calcTable[i].MLSS, RASTSS, FlowRate);
        //Compute FmRatio
        calcTable[i].FmRatio = calculateFmRatio(So, FlowRate, calcTable[i].MLVSS, Volume);
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
    double TotalOxygenSupplied = Aeration * OperatingTime * Speed * FieldOTR / 100;
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

    double AdjustedMicrobialDecay = calculateAdjustedMicrobialDecay(MicrobialDecay, Temperature);
    double AdjustedMaxUtilizationRate = calculateAdjustedMaxUtilizationRate(MaxUtilizationRate, Temperature);

    //----------------------------------- Aerator performance --------------------------------------
    double FieldOTR = calculateFieldOTR(Temperature, Elevation, SOTR, Beta, OperatingDO, Alpha);
    //Compute aerator energy usage
    double AeEnergy = calculateAeEnergy(TypeAerators, Aeration, OperatingTime, Speed);
    //Compute Aerator Energy Cost ($) for Current Conditions
    double AeCost = AeEnergy * EnergyCostUnit;

    //----------------------------------- Current Conditions Calculation--------------------------------------

    // Compute Se
    double Se = calculateSe(HalfSaturation, AdjustedMicrobialDecay, DefinedSRT, BiomassYeild, AdjustedMaxUtilizationRate);
    double SeSRT1 = calculateSe(HalfSaturation, AdjustedMicrobialDecay, 1, BiomassYeild, AdjustedMaxUtilizationRate);
    //Compute Heter Biomass
    double HeterBio = calculateHeterBio(DefinedSRT, Volume, FlowRate, BiomassYeild, So, Se, AdjustedMicrobialDecay);
    double HeterBioSRT1 = calculateHeterBio(1, Volume, FlowRate, BiomassYeild, So, SeSRT1, AdjustedMicrobialDecay);
    //Compute CellDeb
    double CellDeb = calculateCellDeb(HeterBio, FractionBiomass, AdjustedMicrobialDecay, DefinedSRT);
    double CellDebSRT1 = calculateCellDeb(HeterBioSRT1, FractionBiomass, AdjustedMicrobialDecay, 1);
    //Compute InterVes
    double InterVes = calculateInerVes(InertVSS, DefinedSRT, Volume, FlowRate);
    //Compute MLVSS
    double MLVSS = calculateMLVSS(HeterBio, CellDeb, InterVes);
    //Compute MLSS
    double MLSS = calculateMLSS(HeterBio, CellDeb, Biomass, InterVes, InertInOrgTSS, DefinedSRT, Volume, FlowRate);
    //Compute BiomassProd
    double BiomassProd = calculateBiomassProd(HeterBio, CellDeb, Volume, DefinedSRT);
    double BiomassProdSRT1 = calculateBiomassProd(HeterBioSRT1, CellDebSRT1, Volume, 1);
    //Compute SludgeProd
    double SludgeProd = calculateSludgeProd(MLVSS, Volume, DefinedSRT);
    //Compute SolidProd
    double SolidProd = calculateSolidProd(MLSS, Volume, DefinedSRT);
    //Compute Effluent
    double Effluent = calculateEffluent(EffluentTSS, FlowRate);
    //Compue IntentWaste
    double IntentWaste = calculateIntentWaste(SolidProd, Effluent);
    //Compute OxygenRqd
    double OxygenRqd = calculateOxygenRqd(FlowRate, So, Se, BiomassProd);
    //Compute FlowMgd
    double FlowMgd = calculateFlowMgd(IntentWaste, RASTSS);
    //Compute NRemoved
    double NRemoved = calculateNRemoved(DefinedSRT, BiomassProd, FlowRate, OxidizableN);
    double NRemovedSRT1 = calculateNRemoved(1, BiomassProdSRT1, FlowRate, OxidizableN);

    //Compute NremovedMgl
    double NRemovedMgl = calculateNRemoveMgl(NRemoved, FlowRate);
    double NRemovedMglSRT1 = calculateNRemoveMgl(NRemovedSRT1, FlowRate);
    //Compute Fraction Nox : FrNox
    double FrNox = calculateFrNox(Temperature, DefinedSRT);
    double FrNoxSRT1 = calculateFrNox(Temperature, 1);
    //Compute NitO2Dem
    double NitO2Dem = calculateNitO2Dem(FlowRate, OxidizableN, NRemovedMgl, FrNox);
    //Compute O2Reqd
    double O2Reqd = calculateO2Reqd(OxygenRqd, NitO2Dem);
    //Compute EffNH3N
    double EffNH3N = calculateEffNH3N(OxidizableN, NRemovedMgl, FrNox);

    double EffNH3NSRT1 = calculateEffNH3N(OxidizableN, NRemovedMglSRT1, FrNoxSRT1);
    //Compute EffNo3N
    double EffNo3N = calculateEffNo3N(OxidizableN, NRemovedMgl, DefinedSRT, EffNH3N, DefinedSRT, EffNH3NSRT1, NRemovedMglSRT1);
    //Compute TotalO2Rqd
    double TotalO2Rqd = calculateTotalO2Rqd(O2Reqd, FlowRate, EffNo3N);
    //Compute WAS
    double WAS = calculateWAS(IntentWaste, RASTSS);
    //Compute EstimatedEff
    double EstimatedEff = calculateEstimatedEff(DefinedSRT, Se, EffluentTSS);
    double EstimRas = calculateEstimRas(MLSS, RASTSS, FlowRate);
    //Compute FmRatio
    double FmRatio = calculateFmRatio(So, FlowRate, MLVSS, Volume);

    //Setting the Output Table
    double TotalAverageDailyFlowRate = FlowRate;
    double VolumeInService = Volume;
    double InfluentBOD5Concentration = So;
    double InfluentBOD5MassLoading = So * FlowRate * 8.34;
    double SecWWOxidNLoad = FlowRate * OxidizableN * 8.34;
    double SecWWTSSLoad = FlowRate * InfluentTSS * 8.34;
    double FM_ratio = FmRatio;
    double TSSSludgeProduction = IntentWaste;
    double TSSInActivatedSludgeEffluent = Effluent;
    double TotalOxygenRequirements = O2Reqd;
    double TotalOxygenReqWDenit = TotalO2Rqd;
    double TotalOxygenSupplied = Aeration * OperatingTime * Speed * FieldOTR / 100;
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
