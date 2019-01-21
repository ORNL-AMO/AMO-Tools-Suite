#ifndef AMO_TOOLS_SUITE_LOWPRESSUREHEADERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_LOWPRESSUREHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/PRV.h>
#include <ssmt/SteamSystemModelerTool.h>
#include "LowPressureFlashedSteamIntoHeaderCalculatorDomain.h"

class LowPressureHeaderCalculationsDomain {
public:
    std::shared_ptr<PrvWithoutDesuperheating> lowPressurePrv;
    SteamSystemModelerTool::FluidProperties lowPressureHeaderOutput;
    SteamSystemModelerTool::FluidProperties lowPressureCondensate;
    LowPressureFlashedSteamIntoHeaderCalculatorDomain lowPressureFlashedSteamIntoHeaderCalculatorDomain;
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREHEADERCALCULATIONSDOMAIN_H
