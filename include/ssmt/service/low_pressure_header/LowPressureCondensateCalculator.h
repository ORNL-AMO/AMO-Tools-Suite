#ifndef AMO_TOOLS_SUITE_LOWPRESSURECONDENSATECALCULATOR_H
#define AMO_TOOLS_SUITE_LOWPRESSURECONDENSATECALCULATOR_H

#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>

class LowPressureCondensateCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
};

#endif //AMO_TOOLS_SUITE_LOWPRESSURECONDENSATECALCULATOR_H
