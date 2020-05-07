#include <iostream>
#include <cmath>
#include "calculator/util/CompressedAirLeakSurvey.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

CompressedAirLeakSurvey::Output CompressedAirLeakSurvey::calculate()
{
    double totalEnergyUse = 0, totalEnergyCost = 0, totalFlowRate = 0, totalCompressedAirUse = 0;

    for (auto &compressedAirLeakSurveyInput : compressedAirLeakSurveyInputVec)
    {
        double tmpEnergyUse = 0, tmpEnergyCost = 0, tmpFlowRate = 0, tmpSingleNozzleFlowRate = 0, tmpTotalCompressedAirUse = 0;

        // estimate method
        if(compressedAirLeakSurveyInput.getMeasurementMethod() == 0)
        {
            EstimateMethodData estimateMethodData = compressedAirLeakSurveyInput.getEstimateMethodData();
            tmpFlowRate = estimateMethodData.getLeakRateEstimate();
            tmpTotalCompressedAirUse = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpFlowRate * 60) * compressedAirLeakSurveyInput.getUnits();
        }
        // decibels method
        else if(compressedAirLeakSurveyInput.getMeasurementMethod() == 1)
        {
            DecibelsMethodData decibelsMethodData = compressedAirLeakSurveyInput.getDecibelsMethodData();
            tmpFlowRate = decibelsMethodData.calculate();
            tmpTotalCompressedAirUse = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpFlowRate * 60) * compressedAirLeakSurveyInput.getUnits();
        }
        // bag method
        else if (compressedAirLeakSurveyInput.getMeasurementMethod() == 2)
        {
            BagMethodData bagMethodData = compressedAirLeakSurveyInput.getBagMethodData();
            tmpFlowRate = (60.0 / bagMethodData.getFillTime()) * M_PI * bagMethodData.getHeight() * pow((bagMethodData.getDiameter() / 2.0), 2.0) * (1.0 / pow(12.0, 3.0));
            tmpTotalCompressedAirUse = tmpFlowRate * 60.0 * compressedAirLeakSurveyInput.getHoursPerYear() * compressedAirLeakSurveyInput.getUnits();
        }
        // orifice method
        else if(compressedAirLeakSurveyInput.getMeasurementMethod() == 3)
        {
            OrificeMethodData orificeMethodData = compressedAirLeakSurveyInput.getOrificeMethodData();
            tmpFlowRate = orificeMethodData.calculate();
            tmpTotalCompressedAirUse = (compressedAirLeakSurveyInput.getHoursPerYear() * tmpFlowRate * 60) * compressedAirLeakSurveyInput.getUnits();
        }

        //electricity calculation
        if (compressedAirLeakSurveyInput.getUtilityType() == 0)
        {
            tmpEnergyCost = compressedAirLeakSurveyInput.getUtilityCost() * tmpTotalCompressedAirUse;
        }
        else if (compressedAirLeakSurveyInput.getUtilityType() == 1)
        {
            CompressorElectricityData compressorElectricityData = compressedAirLeakSurveyInput.getCompressorElectricityData();
            double electricityCalculation = compressorElectricityData.calculate();
            tmpEnergyUse = electricityCalculation * tmpTotalCompressedAirUse;
            tmpEnergyCost = tmpEnergyUse * compressedAirLeakSurveyInput.getUtilityCost();
        }

        totalEnergyUse += tmpEnergyUse;
        totalEnergyCost += tmpEnergyCost;
        totalFlowRate += tmpFlowRate;
        totalCompressedAirUse += tmpTotalCompressedAirUse;
    }

    return CompressedAirLeakSurvey::Output(totalEnergyUse, totalEnergyCost, totalFlowRate, totalCompressedAirUse);
}

double DecibelsMethodData::calculate()
{
    
    //double linePressure; // X
    //double decibels; // Y
    //double decibelRatingA; // Y1
    //double pressureA; // X1
    //double firstFlowA; // Q11
    //double secondFlowA; // Q21
    //double decibelRatingB; // Y2
    //double pressureB; // X2
    //double firstFlowB; // Q12
    //double secondFlowB; // Q22
	

	const double denominator = (pressureB - pressureA) * (decibelRatingB - decibelRatingA);
	const double leakRateEstimate = ((pressureB - linePressure) * (decibelRatingB - decibels)) / denominator * firstFlowA
							      + ((linePressure - pressureA) * (decibelRatingB - decibels)) / denominator * secondFlowA
							      + ((pressureB - linePressure) * (decibels - decibelRatingA)) / denominator * firstFlowB
							      + ((linePressure - pressureA) * (decibels - decibelRatingA)) / denominator * secondFlowB;

    return leakRateEstimate;
}

// BagMathodData::calculate() implemented in CompressedAirReduction.cpp

double OrificeMethodData::calculate()
{
    const double standardDensity = (atmPressure + supplyPressure) * (144 / (53.34 * airTemp));
	const double sonicDensity = std::pow(standardDensity * (2 / (1.4 + 1)), 1/(1.4 - 1));
	const double leakVelocity = std::pow(((2 * 1.4) / (1.4 + 1)) * 53.34 * airTemp * 32.2, 0.5);
	const double leakRateLBMmin = sonicDensity * (diameter * diameter) * (M_PI/(4 * 144)) * leakVelocity * 60 * dischargeCoef;
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