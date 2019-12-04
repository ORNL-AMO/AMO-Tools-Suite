#ifndef AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATOR_H
#define AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATOR_H

#include <ssmt/Boiler.h>
#include <ssmt/HeatExchanger.h>
#include <ssmt/PRV.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/OperationsInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/LowPressureVentedSteamCalculationsDomain.h>
#include <ssmt/service/DeaeratorModeler.h>
#include <ssmt/service/water_and_condensate/MakeupWaterAndCondensateHeaderCalculator.h>
#include <ssmt/service/water_and_condensate/MakeupWaterMassFlowCalculator.h>
#include <ssmt/service/water-and-condensate/MakeupWaterVolumeFlowCalculator.h>

class LowPressureVentedSteamCalculator {
public:
    LowPressureVentedSteamCalculationsDomain
    calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
             const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
             const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
             const CondensingTurbine &condensingTurbineInput, const OperationsInput &operationsInput,
             const BoilerInput &boilerInput, const Boiler &boiler,
             const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
             const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain,
             const std::shared_ptr<LowPressureHeaderCalculationsDomain> &lowPressureHeaderCalculationsDomain,
             MakeupWaterAndCondensateHeaderCalculationsDomain &makeupWaterAndCondensateHeaderCalculationsDomain,
             const double deaeratorInletSteamMassFlow, const bool recalcMakeupWaterAndMassFlow) const;

private:
    const DeaeratorModeler deaeratorModeler = DeaeratorModeler();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const MakeupWaterAndCondensateHeaderCalculator makeupWaterAndCondensateHeaderCalculator = MakeupWaterAndCondensateHeaderCalculator();
    const MakeupWaterMassFlowCalculator makeupWaterMassFlowCalculator = MakeupWaterMassFlowCalculator();
    const MakeupWaterVolumeFlowCalculator makeupWaterVolumeFlowCalculator = MakeupWaterVolumeFlowCalculator();

    double
    calcLowPressureVentedSteam(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                               const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput,
                               const double massFlow) const;
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATOR_H
