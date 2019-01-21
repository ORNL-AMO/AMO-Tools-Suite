#ifndef AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/Header.h>
#include <ssmt/HeatExchanger.h>
#include "MakeupWaterVolumeFlowCalculationsDomain.h"
#include "ReturnCondensateCalculationsDomain.h"

class MakeupWaterAndCondensateHeaderCalculationsDomain {
public:
    Header combinedCondensateHeader;
    SteamSystemModelerTool::FluidProperties returnCondensate;
    ReturnCondensateCalculationsDomain returnCondensateCalculationsDomain;
    SteamSystemModelerTool::FluidProperties makeupWater;
    MakeupWaterVolumeFlowCalculationsDomain makeupWaterVolumeFlowCalculationsDomain;
    std::shared_ptr <HeatExchanger::Output> heatExchangerOutput;
    SteamSystemModelerTool::FluidProperties makeupWaterAndCondensateHeaderOutput;
};

#endif //AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATIONSDOMAIN_H
