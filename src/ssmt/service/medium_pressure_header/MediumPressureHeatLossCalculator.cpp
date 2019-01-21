#include <ssmt/service/medium_pressure_header/MediumPressureHeatLossCalculator.h>
#include <ssmt/HeatLoss.h>

const SteamSystemModelerTool::FluidProperties
MediumPressureHeatLossCalculator::calc(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                       const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) const {
    std::cout << "MediumPressureHeatLossCalculator::calc: calculating heatLoss outlet" << std::endl;
    const HeatLoss heatLoss =
            heatLossFactory.make(mediumPressureHeaderInput, mediumPressureHeaderOutput);
    return heatLoss.getOutletProperties();
}
