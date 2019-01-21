#include <ssmt/service/high_pressure_header/HighPressureHeatLossCalculator.h>

SteamSystemModelerTool::FluidProperties
HighPressureHeatLossCalculator::updateHighPressureHeaderWithHeatLoss(
        const HeaderWithHighestPressure &highPressureHeaderInput,
        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const {
    std::cout << "HighPressureHeatLossCalculator::updateHighPressureHeaderWithHeatLoss: "
              << "calculating highPressureHeaderOutput with heat loss of steam" << std::endl;
    const HeatLoss &heatLoss = heatLossFactory.make(highPressureHeaderInput, highPressureHeaderOutput);
    return fluidPropertiesFactory.make(heatLoss);
}
