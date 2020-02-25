#include <cmath>
#include "calculator/util/WaterReduction.h"

WaterReduction::Output WaterReduction::calculate()
{
    double waterUse = 0, waterCost = 0, annualWaterSavings = 0, costSavings = 0;

    for (auto & waterReductionInput : waterReductionInputVec)
    {
        double tmpWaterUse, tmpWaterCost;

        if (waterReductionInput.getMeasurementMethod() == 0)
        {
            MeteredFlowMethodData meteredFlowMethodData = waterReductionInput.getMeteredFlowMethodData();
            tmpWaterUse = meteredFlowMethodData.getMeterReading() * 60.0 * waterReductionInput.getOperatingHours();
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
        }
        else if (waterReductionInput.getMeasurementMethod() == 1)
        {
            VolumeMeterMethodData volumeMeterMethodData = waterReductionInput.getVolumeMeterMethodData();
            tmpWaterUse = ((volumeMeterMethodData.getFinalMeterReading() - volumeMeterMethodData.getInitialMeterReading()) /
                              (volumeMeterMethodData.getElapsedTime() * (1.0 / 60.0))) *
                             waterReductionInput.getOperatingHours();
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
        }
        else if (waterReductionInput.getMeasurementMethod() == 2)
        {
            BucketMethodData bucketMethodData = waterReductionInput.getBucketMethodData();
            tmpWaterUse = (bucketMethodData.getBucketVolume() / (bucketMethodData.getBucketFillTime() * (1.0 / 3600.0))) * waterReductionInput.getOperatingHours();
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
        }
        else
        {
            WaterOtherMethodData otherMethodData = waterReductionInput.getOtherMethodData();
            tmpWaterUse = otherMethodData.getConsumption();
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
        }
        waterUse = waterUse + tmpWaterUse;
        waterCost = waterCost + tmpWaterCost;
    }
    return WaterReduction::Output(waterUse, waterCost, annualWaterSavings, costSavings);
}

void WaterReduction::setWaterReductionInputVec(std::vector<WaterReductionInput> &waterReductionInputVec)
{
    this->waterReductionInputVec = std::move(waterReductionInputVec);
}

//Metered Flow Data
void MeteredFlowMethodData::setMeterReading(double meterReading)
{
    this->meterReading = meterReading;
}

//Volume Meter Data
void VolumeMeterMethodData::setFinalMeterReading(double finalMeterReading)
{
    this->finalMeterReading = finalMeterReading;
}

void VolumeMeterMethodData::setInitialMeterReading(double initialMeterReading)
{
    this->initialMeterReading = initialMeterReading;
}

void VolumeMeterMethodData::setElapsedTime(double elapsedTime)
{
    this->elapsedTime = elapsedTime;
}

//Bucket Method Data
void BucketMethodData::setBucketVolume(double bucketVolume)
{
    this->bucketVolume = bucketVolume;
}

void BucketMethodData::setBucketFillTime(double bucketFillTime)
{
    this->bucketFillTime = bucketFillTime;
}

//Water Other Method Data
void WaterOtherMethodData::setConsumption(double consumption)
{
    this->consumption = consumption;
}