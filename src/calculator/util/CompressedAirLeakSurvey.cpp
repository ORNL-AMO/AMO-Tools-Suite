#include <iostream>
#include <cmath>
#include "calculator/util/CompressedAirLeakSurvey.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

CompressedAirLeakSurvey::Output CompressedAirLeakSurvey::calculate()
{
    double annualTotalElectricity = 0, annualTotalElectricityCost = 0, totalFlowRate = 0, annualTotalFlowRate = 0;

    for (auto &compressedAirLeakSurveyInput : compressedAirLeakSurveyInputVec)
    {
        double tmpAnnualTotalElectricity = 0, tmpAnnualTotalElectricityCost = 0, tmpTotalFlowRate = 0, tmpSingleNozzleFlowRate = 0, tmpAnnualTotalFlowRate = 0;

        // estimate method
        if (compressedAirLeakSurveyInput.getMeasurementMethod() == 0)
        {
            EstimateMethodData estimateMethodData = compressedAirLeakSurveyInput.getEstimateMethodData();
            tmpTotalFlowRate = estimateMethodData.getLeakRateEstimate() * compressedAirLeakSurveyInput.getUnits();
            tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
        }
        // decibels method
        else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 1)
        {
            DecibelsMethodData decibelsMethodData = compressedAirLeakSurveyInput.getDecibelsMethodData();
            tmpTotalFlowRate = decibelsMethodData.calculate() * compressedAirLeakSurveyInput.getUnits();
            tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
        }
        // bag method
        else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 2)
        {
            BagMethodData bagMethodData = compressedAirLeakSurveyInput.getBagMethodData();
            tmpTotalFlowRate = ((60.0 / bagMethodData.getFillTime()) * M_PI * bagMethodData.getHeight() * pow((bagMethodData.getDiameter() / 2.0), 2.0) * (1.0 / pow(12.0, 3.0))) * compressedAirLeakSurveyInput.getUnits();
            tmpAnnualTotalFlowRate = tmpTotalFlowRate * 60.0 * compressedAirLeakSurveyInput.getHoursPerYear();
        }
        // orifice method
        else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 3)
        {
            OrificeMethodData orificeMethodData = compressedAirLeakSurveyInput.getOrificeMethodData();
            tmpTotalFlowRate = orificeMethodData.calculate() * compressedAirLeakSurveyInput.getUnits();
            tmpAnnualTotalFlowRate = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpTotalFlowRate * 60);
        }

        // compressed air
        if (compressedAirLeakSurveyInput.getUtilityType() == 0)
        {
            tmpAnnualTotalElectricityCost = compressedAirLeakSurveyInput.getUtilityCost() * tmpAnnualTotalFlowRate;
        }
        // electricity
        else if (compressedAirLeakSurveyInput.getUtilityType() == 1)
        {
            CompressorElectricityData compressorElectricityData = compressedAirLeakSurveyInput.getCompressorElectricityData();
            double electricityCalculation = compressorElectricityData.calculate();
            tmpAnnualTotalElectricity = electricityCalculation * tmpAnnualTotalFlowRate;
            tmpAnnualTotalElectricityCost = tmpAnnualTotalElectricity * compressedAirLeakSurveyInput.getUtilityCost();
        }
        annualTotalElectricity += tmpAnnualTotalElectricity;
        annualTotalElectricityCost += tmpAnnualTotalElectricityCost;
        totalFlowRate += tmpTotalFlowRate;
        annualTotalFlowRate += tmpAnnualTotalFlowRate;
    }
    return CompressedAirLeakSurvey::Output(annualTotalElectricity, annualTotalElectricityCost, totalFlowRate, annualTotalFlowRate);
}

double DecibelsMethodData::calculate()
{

    // double linePressure; // X
    // double decibels; // Y
    // double decibelRatingA; // Y1
    // double pressureA; // X1
    // double firstFlowA; // Q11
    // double secondFlowA; // Q21
    // double decibelRatingB; // Y2
    // double pressureB; // X2
    // double firstFlowB; // Q12
    // double secondFlowB; // Q22

    const double denominator = (pressureB - pressureA) * (decibelRatingB - decibelRatingA);
    const double leakRateEstimate = ((pressureB - linePressure) * (decibelRatingB - decibels)) / denominator * firstFlowA + ((linePressure - pressureA) * (decibelRatingB - decibels)) / denominator * secondFlowA + ((pressureB - linePressure) * (decibels - decibelRatingA)) / denominator * firstFlowB + ((linePressure - pressureA) * (decibels - decibelRatingA)) / denominator * secondFlowB;

    return leakRateEstimate;
}

// BagMathodData::calculate() implemented in CompressedAirReduction.cpp

double OrificeMethodData::calculate()
{
    const double caPressurePSIA = atmPressure + supplyPressure;

    //convert to rankine for density calcs
    const double airTempRankine = airTemp + 459.67;

    const double caDensity = caPressurePSIA * 144 / (53.34 * airTempRankine);
    const double standardDensity = atmPressure * 144 / (53.34 * airTempRankine);
    const double sonicDensity = std::pow((caDensity * (2 / 2.4)), (1 / .4));

    const double leakVelocity = std::pow(((2 * 1.4) / (1.4 + 1)) * 53.34 * airTempRankine * 32.2, 0.5);
    const double leakRateLBMmin = sonicDensity * (diameter * diameter) * (M_PI / (4 * 144)) * leakVelocity * 60 * dischargeCoef;
    const double leakRateScfm = leakRateLBMmin / standardDensity;
    const double leakRateEstimate = leakRateScfm * numOrifices;
    return leakRateEstimate;
}

void EstimateMethodData::setLeakRateEstimate(const double leakRateEstimate)
{
    this->leakRateEstimate = leakRateEstimate;
}

void DecibelsMethodData::setLinePressure(double linePressure)
{
    this->linePressure = linePressure;
}
void DecibelsMethodData::setDecibels(double decibels)
{
    this->decibels = decibels;
}
void DecibelsMethodData::setDecibelRatingA(double decibelRatingA)
{
    this->decibelRatingA = decibelRatingA;
}
void DecibelsMethodData::setPressureA(double pressureA)
{
    this->pressureA = pressureA;
}
void DecibelsMethodData::setFirstFlowA(double firstFlowA)
{
    this->firstFlowA = firstFlowA;
}
void DecibelsMethodData::setSecondFlowA(double secondFlowA)
{
    this->secondFlowA = secondFlowA;
}
void DecibelsMethodData::setDecibelRatingB(double decibelRatingB)
{
    this->decibelRatingB = decibelRatingB;
}
void DecibelsMethodData::setPressureB(double pressureB)
{
    this->pressureB = pressureB;
}
void DecibelsMethodData::setFirstFlowB(double firstFlowB)
{
    this->firstFlowB = firstFlowB;
}
void DecibelsMethodData::setSecondFlowB(double secondFlowB)
{
    this->secondFlowB = secondFlowB;
}

// BagMethodData methods implemented in CompressedAirReduction.cpp

void OrificeMethodData::setAirTemp(const double airTemp)
{
    this->airTemp = airTemp;
}
void OrificeMethodData::setAtmPressure(const double atmPressure)
{
    this->atmPressure = atmPressure;
}
void OrificeMethodData::setDischargeCoef(const double dischargeCoef)
{
    this->dischargeCoef = dischargeCoef;
}
void OrificeMethodData::setDiameter(const double diameter)
{
    this->diameter = diameter;
}
void OrificeMethodData::setSupplyPressure(const double supplyPressure)
{
    this->supplyPressure = supplyPressure;
}
void OrificeMethodData::setNumOrifices(const int numOrifices)
{
    this->numOrifices = numOrifices;
}