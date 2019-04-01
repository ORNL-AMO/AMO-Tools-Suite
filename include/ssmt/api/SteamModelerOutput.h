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
};

#endif //AMO_TOOLS_SUITE_STEAMMODELEROUPUT_H
