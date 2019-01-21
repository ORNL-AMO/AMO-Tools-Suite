#include "ssmt/service/low_pressure_header/LowPressureHeatLossCalculator.h"

SteamSystemModelerTool::FluidProperties
LowPressureHeatLossCalculator::calc(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                    const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput) const {
    const HeatLoss &lowPressureSteamHeatLoss =
            heatLossFactory.make(lowPressureHeaderInput, lowPressureHeaderOutput);
    const SteamSystemModelerTool::FluidProperties &lowPressureSteamHeatLossOutput =
            fluidPropertiesFactory.make(lowPressureSteamHeatLoss);

    const double specificVolume = lowPressureHeaderOutput.specificVolume;

    return fluidPropertiesFactory.makeWithSpecificVolume(lowPressureSteamHeatLossOutput, specificVolume);
}
