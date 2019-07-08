#ifndef AMO_LIBRARY_WATERREDUCTION_H
#define AMO_LIBRARY_WATERREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>


class MeteredFlowData {
    MeteredFlowData(const double meterReading)
    : meterReading(meterReading){}

    double getMeterReading() const { return meterReading; }

private:
    double meterReading;
};

class VolumeMeterData {
    VolumeMeterData(const double finalMeterReading, const double initialMeterReading, const double elapsedTime)
    : finalMeterReading(finalMeterReading), initialMeterReading(initialMeterReading), elapsedTime(elapsedTime) {}

    double getFinalMeterReading() const { return finalMeterReading; }
    double getInitialMeterReading() const { return initialMeterReading; }
    double getElapsedTime() const { return elapsedTime; }

private:
    double finalMeterReading, initialMeterReading, elapsedTime;
};

class BucketMethodData {
public:
    BucketMethodData(const double bucketVolume, const double bucketFillTime, const int operatingHours)
            : bucketVolume(bucketVolume), bucketFillTime(bucketFillTime) {}

    double getBucketVolume() const { return bucketVolume; }

    double getBucketFillTime() const { return bucketFillTime; }

private:
    double bucketVolume;
    double bucketFillTime;
};


class WaterOtherMethodData {
public:
    WaterOtherMethodData(const double water)
            : water(water) {}

    double getWater() const { return water; }

    void setWater(double water);

private:
    double water;
};


class WaterReductionInput {
public:
    WaterReductionInput(const int operatingHours, const double waterCost, const int measurementMethod,
                        const MeteredFlowData meteredFlowData, const VolumeMeterData volumeMeterData,
                        const BucketMethodData bucketMethodData, const WaterOtherMethodData waterOtherMethodData,
                        const int units)
            : operatingHours(operatingHours), waterCost(waterCost), measurementMethod(measurementMethod),
              meteredFlowData(meteredFlowData), volumeMeterData(volumeMeterData),
              bucketMethodData(bucketMethodData), waterOtherMethodData(waterOtherMethodData),
              units(units) {}

    int getOperatingHours() const { return operatingHours; }

    double getWaterCost() const { return waterCost; }

    int getMeasurementMethod() const { return measurementMethod; }

    int getUnits() const { return units; }

    MeteredFlowData getMeteredFlowData() const { return meteredFlowData; }

    VolumeMeterData getVolumeMeterData() const { return volumeMeterData; }

    BucketMethodData getBucketMethodData() const { return bucketMethodData; }

    WaterOtherMethodData getWaterOtherMethodData() const { return waterOtherMethodData; }


private:
    int operatingHours, measurementMethod, units;
    double waterCost;
    MeteredFlowData meteredFlowData;
    VolumeMeterData volumeMeterData;
    BucketMethodData bucketMethodData;
    WaterOtherMethodData waterOtherMethodData;
};


class WaterReduction {

public:
    struct Output {
        Output(double energyUse, double energyCost, double annualEnergySaving, double costSaving, double power)
                : energyUse(energyUse), energyCost(energyCost), annualEnergySavings(annualEnergySaving),
                  costSavings(costSaving), power(power) {}

        Output() = default;

        double energyUse = 0, energyCost = 0, annualEnergySavings = 0, costSavings = 0, power = 0;
    };

    WaterReduction(
            std::vector<WaterReductionInput> &waterReductionInput) : waterReductionInputVec(waterReductionInputVec) {}

    WaterReduction::Output calculate();

    WaterReduction::Output getOutput() { return output; }

    std::vector<WaterReductionInput> const &getWaterReductionInputVec() const {
        return waterReductionInputVec;
    }

    void setWaterReductionInputVec(std::vector<WaterReductionInput> &waterReductionInputVec);

private:
    std::vector<WaterReductionInput> waterReductionInputVec;
    WaterReduction::Output output;
};

#endif // AMO_LIBRARY_WATERREDUCTION_H
