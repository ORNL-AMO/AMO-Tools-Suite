#include <iostream>
#include <cmath>
#include "calculator/util/WaterReduction.h"


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