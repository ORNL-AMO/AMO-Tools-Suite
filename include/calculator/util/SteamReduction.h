/**
 * @file Header file for Steam Reduction Calculations
 *
 * @brief Calculate Steam Use and Energy Use.
 *
 * @author Updater Omer Aziz (omerb)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_STEAMREDUCTION_H
#define AMO_LIBRARY_STEAMREDUCTION_H

#include <exception>
#include <stdexcept>
#include <utility>
#include <vector>
#include "ssmt/SaturatedProperties.h"
#include "ssmt/SteamSystemModelerTool.h"
#include "ssmt/SteamProperties.h"

class SteamFlowMeterMethodData
{
public:
  /**
   *
   * @param flowRate double, water m3/min, steam kg/hr
   */
  explicit SteamFlowMeterMethodData(const double flowRate) : flowRate(flowRate) {}

  double getFlowRate() const { return flowRate; }

private:
  double flowRate;
};

class SteamMassFlowNameplateData
{
public:
  /**
   *
   * @param flowRate double, water m3/min, steam kg/hr
   */
  explicit SteamMassFlowNameplateData(const double flowRate) : flowRate(flowRate) {}

  double getFlowRate() const { return flowRate; }

private:
  double flowRate;
};

class SteamMassFlowMeasuredData
{
public:
  /**
   *
   * @param areaOfDuct double, units m2
   * @param airVelocity double, units m/min
   */
  SteamMassFlowMeasuredData(const double areaOfDuct, const double airVelocity) : areaOfDuct(areaOfDuct), airVelocity(airVelocity) {}

  double getAreaOfDuct() const { return areaOfDuct; }
  double getAirVelocity() const { return airVelocity; }

private:
  double areaOfDuct, airVelocity;
};

class SteamMassFlowMethodData
{
public:
  /**
   *
   * @param isNameplate boolean, true or false
   * @param massFlowMeasuredData
   * @param massFlowNameplateData
   * @param inletTemperature double, units C
   * @param outletTemperature double, units C
   */
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
  SteamMassFlowMeasuredData massFlowMeasuredData;
  SteamMassFlowNameplateData massFlowNameplateData;
  double inletTemperature, outletTemperature;
};

class SteamOffsheetMethodData
{
public:
  /**
   *
   * @param consumption double, units kJ/hr
   */
  explicit SteamOffsheetMethodData(const double consumption) : consumption(consumption) {}

  double getConsumption() const { return consumption; }

private:
  double consumption;
};

class SteamReductionInput
{
public:
  /**
   *
   * @param hoursPerYear double, units hr/yr
   * @param utilityType int, 0 or 1 0r 2
   * @param utilityCost double, $ (USD)
   * @param measurementMethod int, 0 for flow meter, 1 for air mass flow, 2 for water mass flow, 3 for Offsheet method
   * @param systemEfficiency double, % as decimal value
   * @param pressure double, units MPaa
   * @param flowMeterMethodData
   * @param airMassFlowMethodData
   * @param waterMassFlowMethodData
   * @param offsheetMethodData
   * @param units int
   * @param boilerEfficiency double, % as decimal value
   * @param steamVariableOption int, enum value SteamProperties::ThermodynamicQuantity
   * @param steamVariable double, Thermodynamic Property used for calculation- Temperature (K), Enthalpy (kJ/kg), Entropy (kJ/kg-K), or Quality (unit less)
   * @param feedWaterTemperature double, units K
   */
  SteamReductionInput(const int hoursPerYear, const int utilityType, const double utilityCost, const int measurementMethod, const double systemEfficiency, const double pressure,
                      const SteamFlowMeterMethodData flowMeterMethodData, const SteamMassFlowMethodData airMassFlowMethodData,
                      const SteamMassFlowMethodData waterMassFlowMethodData, const SteamOffsheetMethodData offsheetMethodData, const int units,
                      const double boilerEfficiency, const SteamProperties::ThermodynamicQuantity steamVariableOption, const double steamVariable, const double feedWaterTemperature)
      : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost), measurementMethod(measurementMethod), systemEfficiency(systemEfficiency), pressure(pressure),
        flowMeterMethodData(flowMeterMethodData), airMassFlowMethodData(airMassFlowMethodData), waterMassFlowMethodData(waterMassFlowMethodData), offsheetMethodData(offsheetMethodData), units(units),
        boilerEfficiency(boilerEfficiency), steamVariableOption(steamVariableOption), steamVariable(steamVariable), feedWaterTemperature(feedWaterTemperature) {}

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
  SteamOffsheetMethodData getOffsheetMethodData() const { return offsheetMethodData; }
  double getBoilerEfficiency() const { return boilerEfficiency; }
  double getFeedWaterTemperature() const { return feedWaterTemperature; }
  double getSteamVariable() const { return steamVariable; }
  SteamProperties::ThermodynamicQuantity getSteamVariableOption() const { return steamVariableOption; }

private:
  int hoursPerYear, utilityType;
  double utilityCost;
  int measurementMethod;
  double systemEfficiency, pressure;
  SteamFlowMeterMethodData flowMeterMethodData;
  SteamMassFlowMethodData airMassFlowMethodData;
  SteamMassFlowMethodData waterMassFlowMethodData;
  SteamOffsheetMethodData offsheetMethodData;
  int units;
  double boilerEfficiency;
  SteamProperties::ThermodynamicQuantity steamVariableOption;
  double steamVariable;
  double feedWaterTemperature;
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

  /**
   *
   * @param steamReductionInputVec
   */
  explicit SteamReduction(std::vector<SteamReductionInput> steamReductionInputVec) : steamReductionInputVec(std::move(steamReductionInputVec)) {}

  /**
   *
   * @param none
   *
   * @return Output
   *  @param steamUse double, units kg/hr
   *  @param energyUse double, units kJ/yr
   *  @param energyCost double, units $
   */
  SteamReduction::Output calculate();

private:
  std::vector<SteamReductionInput> steamReductionInputVec;
  SteamReduction::Output output;
};

#endif // AMO_LIBRARY_STEAMREDUCTION_H