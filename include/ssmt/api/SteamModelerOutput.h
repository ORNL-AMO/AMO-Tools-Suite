#ifndef AMO_TOOLS_SUITE_STEAMMODELEROUPUT_H
#define AMO_TOOLS_SUITE_STEAMMODELEROUPUT_H

#include <ssmt/Boiler.h>
#include <ssmt/Deaerator.h>
#include <ssmt/domain/EnergyAndCostCalculationsDomain.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/PowerBalanceCheckerCalculationsDomain.h>
#include <ssmt/domain/ProcessSteamUsageCalculationsDomain.h>

/**
 * Steam Modeler output data; holds all of the resulting output data.
 */
class SteamModelerOutput {
public:
    const Boiler boiler;
    const std::shared_ptr<FlashTank> blowdownFlashTank;
    const HighPressureHeaderCalculationsDomain highPressureHeaderCalculationsDomain;
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain> mediumPressureHeaderCalculationsDomain;
    const std::shared_ptr<LowPressureHeaderCalculationsDomain> lowPressureHeaderCalculationsDomain;
    const MakeupWaterAndCondensateHeaderCalculationsDomain makeupWaterAndCondensateHeaderCalculationsDomain;
    const Deaerator deaerator;
    const PowerBalanceCheckerCalculationsDomain powerBalanceCheckerCalculationsDomain;
    const ProcessSteamUsageCalculationsDomain processSteamUsageCalculationsDomain;
    const EnergyAndCostCalculationsDomain energyAndCostCalculationsDomain;

    friend std::ostream &operator<<(std::ostream &stream, const SteamModelerOutput &domain) {
        stream << "SteamModelerOutput["
               << "boiler=" << domain.boiler
               << ", blowdownFlashTank=" << domain.blowdownFlashTank
               << ", highPressureHeaderCalculationsDomain=" << domain.highPressureHeaderCalculationsDomain
               << ", mediumPressureHeaderCalculationsDomain=" << domain.mediumPressureHeaderCalculationsDomain
               << ", lowPressureHeaderCalculationsDomain=" << domain.lowPressureHeaderCalculationsDomain
               << ", makeupWaterAndCondensateHeaderCalculationsDomain=" << domain.makeupWaterAndCondensateHeaderCalculationsDomain
               << ", deaerator=" << domain.deaerator
               << ", powerBalanceCheckerCalculationsDomain=" << domain.powerBalanceCheckerCalculationsDomain
               << ", processSteamUsageCalculationsDomain=" << domain.processSteamUsageCalculationsDomain
               << ", energyAndCostCalculationsDomain=" << domain.energyAndCostCalculationsDomain
               << "]";

        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_STEAMMODELEROUPUT_H
