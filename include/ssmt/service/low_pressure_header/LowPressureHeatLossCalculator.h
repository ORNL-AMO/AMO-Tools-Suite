#ifndef AMO_TOOLS_SUITE_LOWPRESSUREHEATLOSSCALCULATOR_H
#define AMO_TOOLS_SUITE_LOWPRESSUREHEATLOSSCALCULATOR_H

#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HeatLossFactory.h>

class LowPressureHeatLossCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREHEATLOSSCALCULATOR_H
