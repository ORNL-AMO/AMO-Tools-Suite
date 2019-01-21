#ifndef AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/FlashTank.h>

class ReturnCondensateCalculationsDomain {
public:
    const std::shared_ptr<FlashTank> condensateFlashTank;
    const SteamSystemModelerTool::FluidProperties returnCondensateFlashed;
};

#endif //AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATIONSDOMAIN_H
