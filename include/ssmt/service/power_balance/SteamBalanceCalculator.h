#ifndef AMO_TOOLS_SUITE_STEAMBALANCECALCULATOR_H
#define AMO_TOOLS_SUITE_STEAMBALANCECALCULATOR_H

#include <ssmt/Boiler.h>
#include <ssmt/FlashTank.h>
#include <ssmt/PRV.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/LowPressureHeaderCalculationsDomain.h>
#include <ssmt/domain/MediumPressureHeaderCalculationsDomain.h>
#include "SteamProductionCalculator.h"
#include "SteamUseCalculator.h"

class SteamBalanceCalculator {
public:
    double calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                    const BoilerInput &boilerInput, const CondensingTurbine &condensingTurbineInput,
                    const Boiler &boiler, const std::shared_ptr<FlashTank> &blowdownFlashTank,
                    const double deaeratorInletSteamMassFlow,
                    const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                    const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
                    const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain) const;

private:
    const SteamUseCalculator steamUseCalculator = SteamUseCalculator();
    const SteamProductionCalculator steamProductionCalculator = SteamProductionCalculator();
};

#endif //AMO_TOOLS_SUITE_STEAMBALANCECALCULATOR_H
