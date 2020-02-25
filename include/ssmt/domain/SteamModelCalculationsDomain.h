#ifndef AMO_TOOLS_SUITE_STEAMMODELCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_STEAMMODELCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/Boiler.h>
#include <ssmt/Deaerator.h>
#include <ssmt/domain/EnergyAndCostCalculationsDomain.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MakeupWaterAndCondensateHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/PowerBalanceCheckerCalculationsDomain.h>
#include <ssmt/domain/ProcessSteamUsageCalculationsDomain.h>

class SteamModelCalculationsDomain {
public:
    Boiler boiler;
    std::shared_ptr<FlashTank> blowdownFlashTank;
    HighPressureHeaderCalculationsDomain highPressureHeaderCalculationsDomain;
    std::shared_ptr<MediumPressureHeaderCalculationsDomain> mediumPressureHeaderCalculationsDomain;
    std::shared_ptr<LowPressureHeaderCalculationsDomain> lowPressureHeaderCalculationsDomain;
    MakeupWaterAndCondensateHeaderCalculationsDomain makeupWaterAndCondensateHeaderCalculationsDomain;
    Deaerator deaerator;
    PowerBalanceCheckerCalculationsDomain powerBalanceCheckerCalculationsDomain;
    ProcessSteamUsageCalculationsDomain processSteamUsageCalculationsDomain;
    EnergyAndCostCalculationsDomain energyAndCostCalculationsDomain;
};

#endif //AMO_TOOLS_SUITE_STEAMMODELCALCULATIONSDOMAIN_H
