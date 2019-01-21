#ifndef AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATOR_H
#define AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATOR_H

#include <ssmt/HeatExchanger.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/HeaderFactory.h>
#include <ssmt/domain/FluidPropertiesFactory.h>

class MakeupWaterAndCondensateHeaderCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const BoilerInput &boilerInput, const SteamSystemModelerTool::FluidProperties &returnCondensate,
         const std::shared_ptr<HeatExchanger::Output> &heatExchangerOutput,
         const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
         const CondensingTurbine &condensingTurbineInput,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeaderFactory headerFactory = HeaderFactory();
};

#endif //AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATOR_H
