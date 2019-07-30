#ifndef AMO_LIBRARY_STEAMREDUCTION_H
#define AMO_LIBRARY_STEAMREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>
#include "ssmt/SaturatedProperties.h"

class SteamFlowMeterMethodData
{
public:
  SteamFlowMeterMethodData(const double flowRate)
      : flowRate(flowRate) {}
  double getFlowRate() const { return flowRate; }

private:
  double flowRate;
};

class SteamMassFlowNameplateData
{
public:
  SteamMassFlowNameplateData(const double flowRate)
      : flowRate(flowRate) {}

  double getFlowRate() const { return flowRate; }

private:
  double flowRate;
};

class SteamMassFlowMeasuredData
{
public:
  SteamMassFlowMeasuredData(const double areaOfDuct, const double airVelocity)
      : areaOfDuct(areaOfDuct), airVelocity(airVelocity) {}

  double getAreaOfDuct() const { return areaOfDuct; }
  double getAirVelocity() const { return airVelocity; }

private:
  double areaOfDuct, airVelocity;
};

class SteamMassFlowMethodData
{
public:
  SteamMassFlowMethodData(const bool isNameplate, const SteamMassFlowMeasuredData massFlowMeasuredData, const SteamMassFlowNameplateData massFlowNameplateData,
                          const double inletTemperature, const double outletTemperature)
      : isNameplate(isNameplate), massFlowMeasuredData(massFlowMeasuredData),
        massFlowNameplateData(massFlowNameplateData), inletTemperature(inletTemperature), outletTemperature(outletTemperature) {}

  bool getIsNameplate() const { return isNameplate; }
  SteamMassFlowMeasuredData getMassFlowMeasuredData() { return massFlowMeasuredData; }
  SteamMassFlowNameplateData getMassFlowNameplateData() { return massFlowNameplateData; }
  double getInletTemperature() const { return inletTemperature; }
  double getOutletTemperature() const { return outletTemperature; }

private:
  bool isNameplate;
  double inletTemperature, outletTemperature;
  SteamMassFlowMeasuredData massFlowMeasuredData;
  SteamMassFlowNameplateData massFlowNameplateData;
};

class SteamOtherMethodData
{
public:
  SteamOtherMethodData(const double consumption)
      : consumption(consumption) {}

  double getConsumption() const { return consumption; }

private:
  double consumption;
};

class SteamReductionInput
{
public:
  SteamReductionInput(const int hoursPerYear, const int utilityType, const double utilityCost, const int measurementMethod, const double systemEfficiency, const double pressure,
                      const SteamFlowMeterMethodData flowMeterMethodData, const SteamMassFlowMethodData airMassFlowMethodData,
                      const SteamMassFlowMethodData waterMassFlowMethodData, const SteamOtherMethodData otherMethodData, const int units)
      : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost), measurementMethod(measurementMethod), systemEfficiency(systemEfficiency), pressure(pressure),
        flowMeterMethodData(flowMeterMethodData), airMassFlowMethodData(airMassFlowMethodData), waterMassFlowMethodData(waterMassFlowMethodData), otherMethodData(otherMethodData), units(units) {}

  int getHoursPerYear() const { return hoursPerYear; }
  int getUtilityType() const { return utilityType; }
  int getMeasurementMethod() const { return measurementMethod; }
  int getUnits() const { return units; }
  double getUtilityCost() const { return utilityCost; }
  double getSystemEfficiency() const { return systemEfficiency; }
  double getPressure() const { return pressure; }
  SteamFlowMeterMethodData getFlowMeterMethodData() const { return flowMeterMethodData; }
  SteamMassFlowMethodData getAirMassFlowMethodData() const { return airMassFlowMethodData; }
  SteamMassFlowMethodData getWaterMassFlowMethodData() const { return waterMassFlowMethodData; }
  SteamOtherMethodData getOtherMethodData() const { return otherMethodData; }

private:
  int hoursPerYear, utilityType, measurementMethod, units;
  double utilityCost, systemEfficiency, pressure;
  SteamFlowMeterMethodData flowMeterMethodData;
  SteamMassFlowMethodData airMassFlowMethodData;
  SteamMassFlowMethodData waterMassFlowMethodData;
  SteamOtherMethodData otherMethodData;
};

class SteamReduction
{
public:
  struct Output
  {
    Output(double steamUse, double energyUse, double energyCost)
        : steamUse(steamUse), energyUse(energyUse), energyCost(energyCost) {}
    Output() = default;
    double steamUse = 0, energyUse = 0, energyCost = 0;
  };

  SteamReduction(std::vector<SteamReductionInput> &steamReductionInputVec) : steamReductionInputVec(steamReductionInputVec) {}
  SteamReduction::Output calculate();

  std::vector<SteamReductionInput> const &getSteamReductionInputVec() const
  {
    return steamReductionInputVec;
  }
  void setSteamReductionInputVec(std::vector<SteamReductionInput> &steamReductionInputVec);

private:
  std::vector<SteamReductionInput> steamReductionInputVec;
  SteamReduction::Output output;
};

#endif // AMO_LIBRARY_STEAMREDUCTION_H