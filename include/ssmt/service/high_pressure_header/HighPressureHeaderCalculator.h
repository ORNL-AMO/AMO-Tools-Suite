#ifndef AMO_TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATOR_H
#define AMO_TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATOR_H

#include <ssmt/Boiler.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HeaderFactory.h>

class HighPressureHeaderCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const HeaderWithHighestPressure &highPressureHeaderInput, const Boiler &boiler) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeaderFactory headerFactory = HeaderFactory();
};

#endif //AMO_TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATOR_H
