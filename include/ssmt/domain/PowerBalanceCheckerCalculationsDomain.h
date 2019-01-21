#ifndef AMO_TOOLS_SUITE_POWERBALANCECHECKERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_POWERBALANCECHECKERCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/SteamSystemModelerTool.h>
#include "LowPressureVentedSteamCalculationsDomain.h"

class PowerBalanceCheckerCalculationsDomain {
public:
    double steamBalance;
    std::shared_ptr<LowPressureVentedSteamCalculationsDomain> lowPressureVentedSteamCalculationsDomain;
    std::shared_ptr<SteamSystemModelerTool::FluidProperties> lowPressureVentedSteam;
};

#endif //AMO_TOOLS_SUITE_POWERBALANCECHECKERCALCULATIONSDOMAIN_H
