#include "ssmt/service/low_pressure_header/LowPressureCondensateCalculator.h"

SteamSystemModelerTool::FluidProperties
LowPressureCondensateCalculator::calc(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
    return fluidPropertiesFactory.make(lowPressureHeaderInput);
}
