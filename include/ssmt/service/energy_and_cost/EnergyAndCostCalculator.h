#ifndef AMO_TOOLS_SUITE_ENERGYANDCOSTCALCULATOR_H
#define AMO_TOOLS_SUITE_ENERGYANDCOSTCALCULATOR_H

#include <memory>
#include <ssmt/Boiler.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/OperationsInput.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/EnergyAndCostCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>

class EnergyAndCostCalculator {
public:
    EnergyAndCostCalculationsDomain
    calc(const bool isBaselineCalc, const double baselinePowerDemand, const OperationsInput &operationsInput,
         const Boiler &boiler, const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
         const double makeupWaterVolumeFlowAnnual) const;

    double
    calcPowerGenerated(const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                       const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;

    double
    addPowerOutToPowerGenerated(const std::string &name, const std::shared_ptr<Turbine> &turbine,
                                const double powerGenerated) const;

    double
    calcPowerImport(const bool isBaselineCalc, const double sitePowerImportInput, const double baselinePowerDemand,
                    const double powerGenerated) const;

    double
    calcPowerDemand(const double sitePowerImport, const double powerGenerated) const;

    double
    calcPowerGenerationCost(const double sitePowerImport, const double electricityCosts,
                            const double operatingHoursPerYear) const;

    double
    calcBoilerFuelCost(const double fuelEnergyInput, const double operatingHoursPerYearInput,
                       const double fuelCostsInput) const;

    double
    calcMakeupWaterCost(const double makeUpWaterCostsInput, const double makeupWaterVolumeFlowAnnual) const;

    double
    calcTotalOperatingCost(const double powerGenerationCost, const double boilerFuelCost,
                           const double makeupWaterCost) const;

    double
    calcBoilerFuelUsage(const double fuelEnergyInput, const double operatingHoursPerYearInput) const;
};

#endif //AMO_TOOLS_SUITE_ENERGYANDCOSTCALCULATOR_H
