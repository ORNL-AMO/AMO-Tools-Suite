#ifndef AMO_LIBRARY_COMPRESSEDAIRREDUCTION_H
#define AMO_LIBRARY_COMPRESSEDAIRREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>

class CompressedAirFlowMeterMethodData
{
  public:
    CompressedAirFlowMeterMethodData(const double meterReading)
        : meterReading(meterReading) {}

    double getMeterReading() const { return meterReading; }
    void setMeterReading(double meterReading);

  private:
    double meterReading;
};

class BagMethodData
{
  public:
    BagMethodData(const double height, const double diameter, const double fillTime)
        : height(height), diameter(diameter), fillTime(fillTime) {}

    double getHeight() const { return height; }
    double getDiameter() const { return diameter; }
    double getFillTime() const { return fillTime; }
    void setHeight(double height);
    void setDiameter(double diameter);
    void setFillTime(double fillTime);

  private:
    double height, diameter, fillTime;
};

class PressureMethodData
{
  public:
    PressureMethodData(const int nozzleType, const int numberOfNozzles, const double supplyPressure)
        : nozzleType(nozzleType), numberOfNozzles(numberOfNozzles), supplyPressure(supplyPressure) {}

    int getNozzleType() const { return nozzleType; }
    int getNumberOfNozzles() const { return numberOfNozzles; }
    double getSupplyPressure() const { return supplyPressure; }
    void setNozzleType(int nozzleType);
    void setNumberOfNozzles(int numberOfNozzles);
    void setSupplyPressure(double supplyPressure);

    double calculate();

  private:
    int nozzleType, numberOfNozzles;
    double supplyPressure;
};

class CompressedAirOtherMethodData
{
  public:
    CompressedAirOtherMethodData(const double consumption)
        : consumption(consumption) {}

    double getConsumption() const { return consumption; }
    void setConsumption(double consumption);

  private:
    double consumption;
};

//calculates electricity use for a compressor if utilityType == electricity
class CompressorElectricityData
{
  public:
    CompressorElectricityData(const double compressorControlAdjustment, const double compressorSpecificPower)
        : compressorControlAdjustment(compressorControlAdjustment), compressorSpecificPower(compressorSpecificPower) {}

    double calculate();

  private:
    double compressorControlAdjustment, compressorSpecificPower;
};

class CompressedAirReductionInput
{
  public:
    CompressedAirReductionInput(const int hoursPerYear, const int utilityType, const double utilityCost, const int measurementMethod,
                                const CompressedAirFlowMeterMethodData flowMeterMethodData, const BagMethodData bagMethodData,
                                const PressureMethodData pressureMethodData, const CompressedAirOtherMethodData otherMethodData,
                                const CompressorElectricityData compressorElectricityData, const int units)
        : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost), measurementMethod(measurementMethod),
          flowMeterMethodData(flowMeterMethodData), bagMethodData(bagMethodData),
          pressureMethodData(pressureMethodData), otherMethodData(otherMethodData),
          compressorElectricityData(compressorElectricityData), units(units) {}

    int getHoursPerYear() const { return hoursPerYear; }
    int getUtilityType() const { return utilityType; }
    int getMeasurementMethod() const { return measurementMethod; }
    int getUnits() const { return units; }
    double getUtilityCost() const { return utilityCost; }
    CompressedAirFlowMeterMethodData getFlowMeterMethodData() const { return flowMeterMethodData; }
    BagMethodData getBagMethodData() const { return bagMethodData; }
    PressureMethodData getPressureMethodData() const { return pressureMethodData; }
    CompressedAirOtherMethodData getOtherMethodData() const { return otherMethodData; }
    CompressorElectricityData getCompressorElectricityData() const { return compressorElectricityData; }

  private:
    int hoursPerYear, utilityType;
    double utilityCost;
    int measurementMethod;
    CompressedAirFlowMeterMethodData flowMeterMethodData;
    BagMethodData bagMethodData;
    PressureMethodData pressureMethodData;
    CompressedAirOtherMethodData otherMethodData;
    CompressorElectricityData compressorElectricityData;
    int units;
};

class CompressedAirReduction
{
  public:
    struct Output
    {
        Output(double energyUse, double energyCost, double flowRate, double singleNozzleFlowRate, double consumption)
            : energyUse(energyUse), energyCost(energyCost), flowRate(flowRate), singleNozzleFlowRate(singleNozzleFlowRate), consumption(consumption) {}

        Output() = default;
        double energyUse = 0, energyCost = 0, flowRate = 0, singleNozzleFlowRate, consumption = 0;
    };

    CompressedAirReduction(std::vector<CompressedAirReductionInput> compressedAirReductionInputVec) : compressedAirReductionInputVec(compressedAirReductionInputVec)
    {
    }

    CompressedAirReduction::Output calculate();
    std::vector<CompressedAirReductionInput> const &getCompressedAirReductionInputVec() const
    {
        return compressedAirReductionInputVec;
    }
    void setCompressedAirReductionInputVec(std::vector<CompressedAirReductionInput> &compressedAirReductionInputVec);

  private:
    std::vector<CompressedAirReductionInput> compressedAirReductionInputVec;
    CompressedAirReduction::Output output;
};

#endif // AMO_LIBRARY_COMPRESSEDAIRREDUCTION_H