#include <iostream>
#include <cmath>
#include "calculator/util/WaterReduction.h"


WaterReduction::Output WaterReduction::calculate() {
    double waterUse = 0, waterCost = 0, annualWaterSavings = 0, costSavings = 0, consumption = 0;

    for (auto &waterReductionInput: waterReductionInputVec) {
        double tmpWaterUse, tmpWaterCost, tmpAnnualWaterSavings, tmpCostSAvings, tmpConsumption;

        if (waterReductionInput.getMeasurementMethod() == 0) {
            MeteredFlowData meteredFlowData = waterReductionInput.getMeteredFlowData();
            tmpConsumption = meteredFlowData.getMeterReading() * 60 * waterReductionInput.getOperatingHours();
            tmpWaterUse = tmpConsumption;
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
            waterUse = waterUse + tmpWaterUse;
            waterCost = waterCost + tmpWaterCost;
        } else if (waterReductionInput.getMeasurementMethod() == 1) {
            VolumeMeterData volumeMeterData = waterReductionInput.getVolumeMeterData();
            tmpConsumption = ((volumeMeterData.getFinalMeterReading() - volumeMeterData.getInitialMeterReading()) /
                    (volumeMeterData.getElapsedTime()*(1/60))) * waterReductionInput.getOperatingHours();
            tmpWaterUse = tmpConsumption;
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
            waterUse = waterUse + tmpWaterUse;
            waterCost = waterCost + tmpWaterCost;
        } else if (waterReductionInput.getMeasurementMethod() == 2) {
            BucketMethodData bucketMethodData = waterReductionInput.getBucketMethodData();
            tmpConsumption = (bucketMethodData.getBucketVolume() / (bucketMethodData.getBucketFillTime() * (1/3600))) * waterReductionInput.getOperatingHours();
            tmpWaterUse = tmpConsumption;
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
            waterUse = waterUse + tmpWaterUse;
            waterCost = waterCost + tmpWaterCost;
        } else {
            WaterOtherMethodData waterOtherMethodData = waterReductionInput.getWaterOtherMethodData();
            tmpConsumption = waterOtherMethodData.getConsumption();
            tmpWaterUse = tmpConsumption;
            tmpWaterCost = waterReductionInput.getWaterCost() * tmpWaterUse;
            waterUse = waterUse + tmpWaterUse;
            waterCost = waterCost + tmpWaterCost;
        }
        consumption = consumption + tmpConsumption;
    }
    return WaterReduction::Output(waterUse, waterCost, annualWaterSavings, costSavings, consumption);
}


void WaterReduction::setWaterReductionInputVec(std::vector<WaterReductionInput> &waterReductionInputVec) {
    this->waterReductionInputVec = std::move(waterReductionInputVec);
}

//Metered Flow Data
void MeteredFlowData::setMeterReading(double meterReading) {
    this->meterReading = meterReading;
}

//Volume Meter Data
void VolumeMeterData::setFinalMeterReading(double finalMeterReading) {
    this->finalMeterReading = finalMeterReading;
}

void VolumeMeterData::setInitialMeterReading(double initialMeterReading) {
    this->initialMeterReading = initialMeterReading;
}

void VolumeMeterData::setElapsedTime(double elapsedTime) {
    this->elapsedTime = elapsedTime;
}

//Bucket Method Data
void BucketMethodData::setBucketVolume(double bucketVolume) {
    this->bucketVolume = bucketVolume;
}

void BucketMethodData::setBucketFillTime(double bucketFillTime) {
    this->bucketFillTime = bucketFillTime;
}

//Water Other Method Data
void WaterOtherMethodData::setConsumption(double consumption) {
    this->consumption = consumption;
}