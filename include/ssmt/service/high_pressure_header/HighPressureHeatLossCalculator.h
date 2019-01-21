#ifndef AMO_TOOLS_SUITE_HIGHPRESSUREHEATLOSSCALCULATOR_H
#define AMO_TOOLS_SUITE_HIGHPRESSUREHEATLOSSCALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HeatLossFactory.h>

class HighPressureHeatLossCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    updateHighPressureHeaderWithHeatLoss(const HeaderWithHighestPressure &highPressureHeaderInput,
                                         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
};

#endif //AMO_TOOLS_SUITE_HIGHPRESSUREHEATLOSSCALCULATOR_H
