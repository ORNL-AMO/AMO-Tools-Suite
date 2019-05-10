#include <iostream>
#include <cmath>
#include "calculator/util/CompressedAirReduction.h"

CompressedAirReduction::Output CompressedAirReduction::calculate()
{
    double totalEnergyUse = 0, totalEnergyCost = 0, totalFlowRate = 0, singleNozzleFlowRate = 0, totalConsumption = 0;

    for (auto &compressedAirReductionInput : compressedAirReductionInputVec)
    {
        double tmpEnergyUse = 0, tmpEnergyCost = 0, tmpFlowRate = 0, tmpSingleNozzleFlowRate = 0, tmpTotalConsumption = 0;

        // compressed air flow meter
        if (compressedAirReductionInput.getMeasurementMethod() == 0)
        {
            CompressedAirFlowMeterMethodData flowMeterMethodData = compressedAirReductionInput.getFlowMeterMethodData();
            tmpTotalConsumption = flowMeterMethodData.getMeterReading() * 60.0 * compressedAirReductionInput.getHoursPerYear() * compressedAirReductionInput.getUnits();
        }
        // bag method
        else if (compressedAirReductionInput.getMeasurementMethod() == 1)
        {
            BagMethodData bagMethodData = compressedAirReductionInput.getBagMethodData();
            tmpFlowRate = (60.0 / bagMethodData.getFillTime()) * M_PI * bagMethodData.getHeight() * pow((bagMethodData.getDiameter() / 2.0), 2.0) * (1.0 / pow(12.0, 3.0));
            tmpTotalConsumption = tmpFlowRate * 60.0 * compressedAirReductionInput.getHoursPerYear() * compressedAirReductionInput.getUnits();
        }
        // orifice/pressure method
        else if (compressedAirReductionInput.getMeasurementMethod() == 2)
        {
            PressureMethodData pressureMethodData = compressedAirReductionInput.getPressureMethodData();
            tmpSingleNozzleFlowRate = pressureMethodData.calculate();
            tmpFlowRate = tmpSingleNozzleFlowRate * pressureMethodData.getNumberOfNozzles();
            tmpTotalConsumption = tmpFlowRate * 60.0 * compressedAirReductionInput.getHoursPerYear();
        }
        // other method
        else if (compressedAirReductionInput.getMeasurementMethod() == 3)
        {
            CompressedAirOtherMethodData otherMethodData = compressedAirReductionInput.getOtherMethodData();
            tmpTotalConsumption = otherMethodData.getConsumption();
        }

        //electricity calculation
        if (compressedAirReductionInput.getUtilityType() == 1)
        {
            CompressorElectricityData compressorElectricityData = compressedAirReductionInput.getCompressorElectricityData();
            double electricityCalculation = compressorElectricityData.calculate();
            tmpEnergyUse = electricityCalculation * tmpTotalConsumption;
            tmpEnergyCost = tmpEnergyUse * compressedAirReductionInput.getUtilityCost();
        }

        totalEnergyUse += tmpEnergyUse;
        totalEnergyCost += tmpEnergyCost;
        totalFlowRate += tmpFlowRate;
        singleNozzleFlowRate += tmpSingleNozzleFlowRate;
        totalConsumption += tmpTotalConsumption;
    }

    return CompressedAirReduction::Output(totalEnergyUse, totalEnergyCost, totalFlowRate, singleNozzleFlowRate, totalConsumption);
}

double PressureMethodData::calculate()
{
    static double nozzleTable[13][3] = {
        {-2.2e-07, 0.018893, 0.268476},
        {-2.8e-05, 0.038377, 1.061905},
        {-7.6e-05, 1.537424, 14.3},
        {-2.2e-05, 0.345931, 5.780952},
        {0.000682, 0.643182, 13.83333},
        {5.41e-06, 0.228851, 2.968095},
        {-2.1e-06, 0.075463, 1.089857},
        {-2.8e-05, 0.14871, 1.841905},
        {0.002652, 2.250152, 46.56667},
        {0.000747, 0.842056, 15.95714},
        {0.000411, 0.560649, 10.1619},
        {0.000935, 0.130792, 4.429524},
        {0.000935, 0.130792, 4.429524}};

    const double a = nozzleTable[this->nozzleType][0];
    const double b = nozzleTable[this->nozzleType][1];
    const double c = nozzleTable[this->nozzleType][2];
    double singleNozzleFlowRate = (a * (pow(this->supplyPressure, 2.0))) + (b * this->supplyPressure) + c;
    return singleNozzleFlowRate;
}

double CompressorElectricityData::calculate()
{
    const double c = 1.0 / 60;
    return c * this->compressorControlAdjustment * this->compressorSpecificPower;
}

void CompressedAirReduction::setCompressedAirReductionInputVec(std::vector<CompressedAirReductionInput> &compressedAirReductionInputVec)
{
    this->compressedAirReductionInputVec = std::move(compressedAirReductionInputVec);
}

void CompressedAirOtherMethodData::setConsumption(const double consumption)
{
    this->consumption = consumption;
}

void PressureMethodData::setNozzleType(const int nozzleType)
{
    this->nozzleType = nozzleType;
}

void PressureMethodData::setNumberOfNozzles(const int numberOfNozzles)
{
    this->numberOfNozzles = numberOfNozzles;
}

void PressureMethodData::setSupplyPressure(const double supplyPressure)
{
    this->supplyPressure = supplyPressure;
}

void BagMethodData::setHeight(const double height)
{
    this->height = height;
}

void BagMethodData::setDiameter(const double diameter)
{
    this->diameter = diameter;
}

void BagMethodData::setFillTime(const double fillTime)
{
    this->fillTime = fillTime;
}

void CompressedAirFlowMeterMethodData::setMeterReading(const double meterReading)
{
    this->meterReading = meterReading;
}