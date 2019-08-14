#ifndef AMO_LIBRARY_WATERREDUCTION_H
#define AMO_LIBRARY_WATERREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>


class MeteredFlowMethodData {
public:
    MeteredFlowMethodData(const double meterReading)
            : meterReading(meterReading) {}
    double getMeterReading() const { return meterReading; }

    void setMeterReading(double meterReading);

private:
    double meterReading;
};

class VolumeMeterMethodData {
public:
    VolumeMeterMethodData(const double finalMeterReading, const double initialMeterReading, const double elapsedTime)
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
                        const MeteredFlowMethodData meteredFlowMethodData, const VolumeMeterMethodData volumeMeterMethodData,
                        const BucketMethodData bucketMethodData, const WaterOtherMethodData otherMethodData)
            : operatingHours(operatingHours), waterCost(waterCost), measurementMethod(measurementMethod),
              meteredFlowMethodData(meteredFlowMethodData), volumeMeterMethodData(volumeMeterMethodData),
              bucketMethodData(bucketMethodData), otherMethodData(otherMethodData) {}

    int getOperatingHours() const { return operatingHours; }

    double getWaterCost() const { return waterCost; }

    int getMeasurementMethod() const { return measurementMethod; }

    MeteredFlowMethodData getMeteredFlowMethodData() const { return meteredFlowMethodData; }

    VolumeMeterMethodData getVolumeMeterMethodData() const { return volumeMeterMethodData; }

    BucketMethodData getBucketMethodData() const { return bucketMethodData; }

    WaterOtherMethodData getOtherMethodData() const { return otherMethodData; }

    void setMeteredFlowMethodData(MeteredFlowMethodData meteredFlowMethodData);

    void setVolumeMeterMethodData(VolumeMeterMethodData volumeMeterMethodData);

    void setucketMethodData(BucketMethodData bucketMethodData);

    void setOtherMethodData(WaterOtherMethodData otherMethodData);


private:
    int operatingHours, measurementMethod;
    double waterCost;
    MeteredFlowMethodData meteredFlowMethodData;
    VolumeMeterMethodData volumeMeterMethodData;
    BucketMethodData bucketMethodData;
    WaterOtherMethodData otherMethodData;
};


class WaterReduction {

public:
    struct Output {
        Output(double waterUse, double waterCost, double annualWaterSavings, double costSavings)
                : waterUse(waterUse), waterCost(waterCost), annualWaterSavings(annualWaterSavings),
                  costSavings(costSavings) {}

        Output() = default;

        double waterUse = 0, waterCost = 0, annualWaterSavings = 0, costSavings = 0;
    };

    WaterReduction(std::vector<WaterReductionInput> &waterReductionInputVec) : waterReductionInputVec(waterReductionInputVec) {}

    WaterReduction::Output calculate();

    std::vector<WaterReductionInput> const &getWaterReductionInputVec() const {
        return waterReductionInputVec;
    }

    void setWaterReductionInputVec(std::vector<WaterReductionInput> &waterReductionInputVec);

private:
    std::vector<WaterReductionInput> waterReductionInputVec;
    WaterReduction::Output output;
};

#endif // AMO_LIBRARY_WATERREDUCTION_H
