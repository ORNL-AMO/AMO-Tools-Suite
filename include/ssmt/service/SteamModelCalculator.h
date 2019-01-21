#ifndef AMO_TOOLS_SUITE_STEAMMODELCALCULATOR_H
#define AMO_TOOLS_SUITE_STEAMMODELCALCULATOR_H

#include "DeaeratorModeler.h"
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/OperationsInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/BoilerFactory.h>
#include <ssmt/domain/EnergyAndCostCalculationsDomain.h>
#include <ssmt/domain/FlashTankFactory.h>
#include <ssmt/domain/SteamModelCalculationsDomain.h>
#include <ssmt/service/energy_and_cost/EnergyAndCostCalculator.h>
#include "ssmt/service/high_pressure_header/HighPressureHeaderModeler.h"
#include "ssmt/service/low_pressure_header/LowPressureHeaderModeler.h"
#include "ssmt/service/medium_pressure_header/MediumPressureHeaderModeler.h"
#include <ssmt/service/power_balance/PowerBalanceChecker.h>
#include <ssmt/service/process_steam_usage/ProcessSteamUsageModeler.h>
#include <ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderModeler.h>

class SteamModelCalculator {
public:
    SteamModelCalculationsDomain
    calc(const bool isBaselineCalc, const double baselinePowerDemand, const HeaderInput &headerInput,
         const BoilerInput &boilerInput, const TurbineInput &turbineInput, const OperationsInput &operationsInput,
         const double initialMassFlow) const;

private:
    const BoilerFactory boilerFactory = BoilerFactory();
    const DeaeratorModeler deaeratorModeler = DeaeratorModeler();
    const EnergyAndCostCalculator energyAndCostCalculator = EnergyAndCostCalculator();
    const FlashTankFactory flashTankFactory = FlashTankFactory();
    const HighPressureHeaderModeler highPressureHeaderModeler = HighPressureHeaderModeler();
    const LowPressureHeaderModeler lowPressureHeaderModeler = LowPressureHeaderModeler();
    const MediumPressureHeaderModeler mediumPressureHeaderModeler = MediumPressureHeaderModeler();
    const MakeupWaterAndCondensateHeaderModeler makeupWaterAndCondensateHeaderModeler = MakeupWaterAndCondensateHeaderModeler();
    const PowerBalanceChecker powerBalanceChecker = PowerBalanceChecker();
    const ProcessSteamUsageModeler processSteamUsageModeler = ProcessSteamUsageModeler();
};

#endif //AMO_TOOLS_SUITE_STEAMMODELCALCULATOR_H
