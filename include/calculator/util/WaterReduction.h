#ifndef AMO_LIBRARY_WATERREDUCTION_H
#define AMO_LIBRARY_WATERREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>


class MeteredFlowData {
public:
    MeteredFlowData(const double meterReading)
            : meterReading(meterReading) {}
    double getMeterReading() const { return meterReading; }

    void setMeterReading(double meterReading);

private:
    double meterReading;
};

class VolumeMeterData {
public:
    VolumeMeterData(const double finalMeterReading, const double initialMeterReading, const double elapsedTime)
            : finalMeterReading(finalMeterReading), initialMeterReading(initialMeterReading),
              elapsedTime(elapsedTime) {}
    double getFinalMeterReading() const { return finalMeterReading; }

    double getInitialMeterReading() const { return initialMeterReading; }

    double getElapsedTime() const { return elapsedTime; }

    void setFinalMeterReading(double finalMeterReading);

    void setInitialMeterReading(double initialMeterReading);

    void setElapsedTime(double elapsedTime);

private:
    double finalMeterReading, initialMeterReading, elapsedTime;
};

class BucketMethodData {
public:
    BucketMethodData(const double bucketVolume, const double bucketFillTime)
            : bucketVolume(bucketVolume), bucketFillTime(bucketFillTime) {}

    double getBucketVolume() const { return bucketVolume; }

    double getBucketFillTime() const { return bucketFillTime; }

    void setBucketVolume(double bucketVolume);

    void setBucketFillTime(double bucketFillTime);

private:
    double bucketVolume;
    double bucketFillTime;
};


class WaterOtherMethodData {
public:
    WaterOtherMethodData(const double consumption)
            : consumption(consumption) {}

    double getConsumption() const { return consumption; }

    void setConsumption(double consumption);

private:
    double consumption;
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

    void setMeteredFlowData(MeteredFlowData meteredFlowData);

    void setVolumeMeterData(VolumeMeterData volumeMeterData);

    void setucketMethodData(BucketMethodData bucketMethodData);

    void setWaterOtherMethodData(WaterOtherMethodData waterOtherMethodData);


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
        Output(double waterUse, double waterCost, double annualWaterSavings, double costSavings, double consumption)
                : waterUse(waterUse), waterCost(waterCost), annualWaterSavings(annualWaterSavings),
                  costSavings(costSavings), consumption(consumption) {}

        Output() = default;

        double waterUse = 0, waterCost = 0, annualWaterSavings = 0, costSavings = 0, consumption = 0;
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
