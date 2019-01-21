#ifndef AMO_TOOLS_SUITE_POWERBALANCECHECKER_H
#define AMO_TOOLS_SUITE_POWERBALANCECHECKER_H

#include "SteamBalanceCalculator.h"
#include "LowPressureVentedSteamCalculator.h"
#include <ssmt/Boiler.h>
#include <ssmt/Deaerator.h>
#include <ssmt/FlashTank.h>
#include <ssmt/PRV.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/OperationsInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/PowerBalanceCheckerCalculationsDomain.h>
#include <ssmt/service/DeaeratorModeler.h>
#include <ssmt/service/Restarter.h>
#include "ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.h"
#include "ssmt/service/water_and_condensate/MakeupWaterMassFlowCalculator.h"

class PowerBalanceChecker {
public:
    PowerBalanceCheckerCalculationsDomain
    check(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToLowTurbineInput, const PressureTurbine &highToMediumTurbineInput,
          const PressureTurbine &mediumToLowTurbineInput, const BoilerInput &boilerInput,
          const CondensingTurbine &condensingTurbineInput, const OperationsInput &operationsInput, const Boiler &boiler,
          const std::shared_ptr<FlashTank> &blowdownFlashTank, const double deaeratorInletSteamMassFlow,
          const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
          const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
          const MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const Restarter restarter = Restarter();
    const LowPressureVentedSteamCalculator lowPressureVentedSteamCalculator = LowPressureVentedSteamCalculator();
    const SteamBalanceCalculator steamBalanceCalculator = SteamBalanceCalculator();

    bool
    isVentingOnlyExcessSteamOption(const int headerCountInput, const PressureTurbine &highToLowTurbineInput,
                                   const PressureTurbine &highToMediumTurbineInput,
                                   const PressureTurbine &mediumToLowTurbineInput) const;
};

#endif //AMO_TOOLS_SUITE_POWERBALANCECHECKER_H
