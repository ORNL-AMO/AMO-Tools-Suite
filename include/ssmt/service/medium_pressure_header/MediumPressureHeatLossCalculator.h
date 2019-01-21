#ifndef AMO_TOOLS_SUITE_MEDIUMPRESSUREHEATLOSSCALCULATOR_H
#define AMO_TOOLS_SUITE_MEDIUMPRESSUREHEATLOSSCALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/HeatLossFactory.h>

class MediumPressureHeatLossCalculator {
public:
    const SteamSystemModelerTool::FluidProperties
    calc(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) const;

private:
    const HeatLossFactory heatLossFactory = HeatLossFactory();
};

#endif //AMO_TOOLS_SUITE_MEDIUMPRESSUREHEATLOSSCALCULATOR_H
