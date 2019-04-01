#include "ssmt/domain/SteamModelerOutputFactory.h"

SteamModelerOutput SteamModelerOutputFactory::make(const SteamModelCalculationsDomain &domain) const {
    const Boiler &boiler = domain.boiler;
    const std::shared_ptr<FlashTank> &blowdownFlashTank = domain.blowdownFlashTank;
    const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain = domain.highPressureHeaderCalculationsDomain;
    const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain = domain.mediumPressureHeaderCalculationsDomain;
    const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain = domain.lowPressureHeaderCalculationsDomain;
    const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain = domain.makeupWaterAndCondensateHeaderCalculationsDomain;
    const Deaerator &deaerator = domain.deaerator;
    const PowerBalanceCheckerCalculationsDomain &powerBalanceCheckerCalculationsDomain = domain.powerBalanceCheckerCalculationsDomain;
    const ProcessSteamUsageCalculationsDomain &processSteamUsageCalculationsDomain = domain.processSteamUsageCalculationsDomain;
    const EnergyAndCostCalculationsDomain &energyAndCostCalculationsDomain = domain.energyAndCostCalculationsDomain;

    return {boiler, blowdownFlashTank, highPressureHeaderCalculationsDomain, mediumPressureHeaderCalculationsDomain,
            lowPressureHeaderCalculationsDomain, makeupWaterAndCondensateHeaderCalculationsDomain, deaerator,
            powerBalanceCheckerCalculationsDomain, processSteamUsageCalculationsDomain,
            energyAndCostCalculationsDomain};
}
