#ifndef AMO_LIBRARY_STEAMREDUCTION_H
#define AMO_LIBRARY_STEAMREDUCTION_H

#include <exception>
#include <stdexcept>
#include <vector>

class SteamFlowMeterMethodData
{
  public:
    SteamFlowMeterMethodData(const double flowRate)
        : flowRate(flowRate) {}

    double getFlowRate() const { return flowRate; }
    void setFlowRate(double flowRate);

  private:
    double flowRate;
};

class SteamAirMassFlowNameplateData
{
  public:
    SteamAirMassFlowNameplateData(const double airFlow)
        : airFlow(airFlow) {}

    double getAirFlow() const { return airFlow; }

  private:
    double airFlow;
};

class SteamAirMassFlowMeasuredData
{
  public:
    SteamAirMassFlowMeasuredData(const double areaOfDuct, const double airVelocity)
        : areaOfDuct(areaOfDuct), airVelocity(airVelocity) {}

    double getAreaOfDuct() const { return areaOfDuct; }
    double getAirVelocity() const { return airVelocity; }

  private:
    double areaOfDuct, airVelocity;
};

class SteamAirMassFlowMethodData
{
  public:
    SteamAirMassFlowMethodData(const bool isNameplate, const SteamAirMassFlowMeasuredData airMassFlowMeasuredData, const SteamAirMassFlowNameplateData airMassFlowNameplateData,
                               const double inletTemperature, const double outletTemperature)
        : isNameplate(isNameplate), airMassFlowMeasuredData(airMassFlowMeasuredData),
          airMassFlowNameplateData(airMassFlowNameplateData), inletTemperature(inletTemperature), outletTemperature(outletTemperature) {}

    bool getIsNameplate() const { return isNameplate; }
    SteamAirMassFlowMeasuredData getAirMassFlowMeasuredData() { return airMassFlowMeasuredData; }
    SteamAirMassFlowNameplateData getAirMassFlowNameplateData() { return airMassFlowNameplateData; }
    double getInletTemperature() const { return inletTemperature; }
    double getOutletTemperature() const { return outletTemperature; }

  private:
    bool isNameplate;
    double inletTemperature, outletTemperature;
    SteamAirMassFlowMeasuredData airMassFlowMeasuredData;
    SteamAirMassFlowNameplateData airMassFlowNameplateData;
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
    SteamReductionInput(const int hoursPerYear, const int utilityType, const double utilityCost, const int measurementMethod,
                        const SteamFlowMeterMethodData flowMeterMethodData, const SteamAirMassFlowMethodData airMassFlowMethodData,
                        const SteamOtherMethodData otherMethodData, const int units)
        : hoursPerYear(hoursPerYear), utilityType(utilityType), utilityCost(utilityCost), measurementMethod(measurementMethod),
          flowMeterMethodData(flowMeterMethodData), airMassFlowMethodData(airMassFlowMethodData), otherMethodData(otherMethodData), units(units) {}

    int getHoursPerYear() const { return hoursPerYear; }
    int getUtilityType() const { return utilityType; }
    int getMeasurementMethod() const { return measurementMethod; }
    int getUnits() const { return units; }
    double getUtilityCost() const { return utilityCost; }
    SteamFlowMeterMethodData getFlowMeterMethodData() const { return flowMeterMethodData; }
    SteamAirMassFlowMethodData getAirMassFlowMethodData() const { return airMassFlowMethodData; }
    SteamOtherMethodData getOtherMethodData() const { return otherMethodData; }

  private:
    int hoursPerYear, utilityType, measurementMethod, units;
    double utilityCost;
    SteamFlowMeterMethodData flowMeterMethodData;
    SteamAirMassFlowMethodData airMassFlowMethodData;
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
    std::vector<SteamReductionInput> const &getSteamReductionInputVec()
    {
        return steamReductionInputVec;
    }
    void setSteamReductionInputVec(std::vector<SteamReductionInput> &steamReductionInputVec);

  private:
    std::vector<SteamReductionInput> steamReductionInputVec;
    SteamReduction::Output output;
};

#endif // AMO_LIBRARY_STEAMREDUCTION_H