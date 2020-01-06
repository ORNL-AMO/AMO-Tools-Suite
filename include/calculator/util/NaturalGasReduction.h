#ifndef AMO_LIBRARY_NATURALGASREDUCTION_H
#define AMO_LIBRARY_NATURALGASREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>

class FlowMeterMethodData
{
public:
  FlowMeterMethodData(const double flowRate)
      : flowRate(flowRate) {}

  double getFlowRate() const { return flowRate; }
  void setFlowRate(double flowRate);

private:
  double flowRate;
};

class NaturalGasOtherMethodData
{
public:
  NaturalGasOtherMethodData(const double consumption)
      : consumption(consumption) {}

  double getConsumption() const { return consumption; }
  void setConsumption(double consumption);

private:
  double consumption;
};

class AirMassFlowMeasuredData
{
public:
  AirMassFlowMeasuredData(const double areaOfDuct, const double airVelocity)
      : areaOfDuct(areaOfDuct), airVelocity(airVelocity) {}

  double getAreaOfDuct() const { return areaOfDuct; }
  double getAirVelocity() const { return airVelocity; }
  void setAreaOfDuct(double areaOfDuct);
  void setAirVelocity(double airVelocity);

private:
  double areaOfDuct, airVelocity;
};

class AirMassFlowNameplateData
{
public:
  AirMassFlowNameplateData(const double airFlow)
      : airFlow(airFlow) {}

  double getAirFlow() const { return airFlow; }
  void setAirFlow(double airFlow);

private:
  double airFlow;
};

class AirMassFlowData
{
public:
  AirMassFlowData(const bool isNameplate, const AirMassFlowMeasuredData airMassFlowMeasuredData, const AirMassFlowNameplateData airMassFlowNameplateData, const double inletTemperature, const double outletTemperature, const double systemEfficiency)
      : isNameplate(isNameplate), airMassFlowMeasuredData(airMassFlowMeasuredData), airMassFlowNameplateData(airMassFlowNameplateData), inletTemperature(inletTemperature), outletTemperature(outletTemperature), systemEfficiency(systemEfficiency) {}

  bool getIsNameplate() const { return isNameplate; }
  AirMassFlowMeasuredData getAirMassFlowMeasuredData() const { return airMassFlowMeasuredData; }
  AirMassFlowNameplateData getAirMassFlowNameplateData() const { return airMassFlowNameplateData; }
  double getInletTemperature() const { return inletTemperature; }
  double getOutletTemperature() const { return outletTemperature; }
  double getSystemEfficiency() const { return systemEfficiency; }
  void setIsNameplate(bool isNameplate);
  void setAirMassFlowMeasuredData(AirMassFlowMeasuredData airMassFlowMeasuredData);
  void setAirMassFlowNameplateData(AirMassFlowNameplateData airMassFlowNameplateData);
  void setInletTemperature(double inletTemperature);
  void setOutletTemperature(double outletTemperature);
  void setSystemEfficiency(double systemEfficiency);

private:
  bool isNameplate;
  AirMassFlowMeasuredData airMassFlowMeasuredData;
  AirMassFlowNameplateData airMassFlowNameplateData;
  double inletTemperature, outletTemperature, systemEfficiency;
};

class WaterMassFlowData
{
public:
  WaterMassFlowData(const double waterFlow, const double inletTemperature, const double outletTemperature, const double systemEfficiency) : waterFlow(waterFlow), inletTemperature(inletTemperature), outletTemperature(outletTemperature), systemEfficiency(systemEfficiency) {}
  double getWaterFlow() const { return waterFlow; }
  double getInletTemperature() const { return inletTemperature; }
  double getOutletTemperature() const { return outletTemperature; }
  double getSystemEfficiency() const { return systemEfficiency; }
  void setWaterFlow(double waterFlow);
  void setInletTemperature(double inletTemperature);
  void setOutletTemperature(double outletTemperature);
  void setSystemEfficiency(double systemEfficiency);

private:
  double waterFlow, inletTemperature, outletTemperature, systemEfficiency;
};

class NaturalGasReductionInput
{
public:
  NaturalGasReductionInput(const int operatingHours, const double fuelCost, const int measurementMethod, 
                           const FlowMeterMethodData flowMeterMethodData, const NaturalGasOtherMethodData otherMethodData,
                           const AirMassFlowData airMassFlowData, const WaterMassFlowData waterMassFlowData, 
                           const int units)
      : operatingHours(operatingHours), fuelCost(fuelCost), measurementMethod(measurementMethod), flowMeterMethodData(flowMeterMethodData),
        otherMethodData(otherMethodData), airMassFlowData(airMassFlowData), waterMassFlowData(waterMassFlowData), units(units) {}

  int getOperatingHours() const { return operatingHours; }
  double getFuelCost() const { return fuelCost; }
  int getMeasurementMethod() const { return measurementMethod; }
  int getUnits() const { return units; }
  FlowMeterMethodData getFlowMeterMethodData() const { return flowMeterMethodData; }
  NaturalGasOtherMethodData getNaturalGasOtherMethodData() const { return otherMethodData; }
  AirMassFlowData getAirMassFlowData() const { return airMassFlowData; }
  WaterMassFlowData getWaterMassFlowData() const { return waterMassFlowData; }

private:
  int operatingHours;
  double fuelCost;
  int measurementMethod;
  FlowMeterMethodData flowMeterMethodData;
  NaturalGasOtherMethodData otherMethodData;
  AirMassFlowData airMassFlowData;
  WaterMassFlowData waterMassFlowData;
  int units;
};

class NaturalGasReduction
{
public:
  struct Output
  {
    Output(double energyUse, double energyCost, double heatFlow, double totalFlow)
        : energyUse(energyUse), energyCost(energyCost), heatFlow(heatFlow), totalFlow(totalFlow) {}

    Output() = default;
    double energyUse = 0, energyCost = 0, heatFlow = 0, totalFlow = 0;
  };

  NaturalGasReduction(
      std::vector<NaturalGasReductionInput> &naturalGasReductionInputVec) : naturalGasReductionInputVec(naturalGasReductionInputVec)
  {
  }

  NaturalGasReduction::Output calculate();
  std::vector<NaturalGasReductionInput> const &getNaturalGasReductionInputVec() const
  {
    return naturalGasReductionInputVec;
  }
  void setNaturalGasReductionInputVec(std::vector<NaturalGasReductionInput> &naturalGasReductionInputVec);

private:
  std::vector<NaturalGasReductionInput> naturalGasReductionInputVec;
  NaturalGasReduction::Output output;
};

#endif // AMO_LIBRARY_NATURALGASREDUCTION_H