#include <iostream>
#include <cmath>
#include "calculator/util/WaterReduction.h"


void WaterReduction::setWaterReductionInputVec(std::vector<WaterReductionInput> &waterReductionInputVec) {
    this->waterReductionInputVec = std::move(waterReductionInputVec);
}

void MeteredFlowData::setMeterReading(double meterReading) {
    this->meterReading = meterReading;
}

void VolumeMeterData::setFinalMeterReading(double finalMeterReading) {
    this->finalMeterReading = finalMeterReading;
}

void VolumeMeterData::setInitialMeterReading(double initialMeterReading) {
    this->initialMeterReading = initialMeterReading;
}

void VolumeMeterData::setElapsedTime(double elapsedTime) {
    this->elapsedTime = elapsedTime;
}

void BucketMethodData::setBucketVolume(double bucketVolume) {
    this->bucketVolume = bucketVolume;
}

void BucketMethodData::setBucketFillTime(double bucketFillTime) {
    this->bucketFillTime = bucketFillTime;
}

void WaterOtherMethodData::setConsumption(double consumption) {
    this->consumption = consumption;
}