#ifndef AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/Header.h>
#include <ssmt/HeatExchanger.h>
#include "MakeupWaterVolumeFlowCalculationsDomain.h"
#include "ReturnCondensateCalculationsDomain.h"

class MakeupWaterAndCondensateHeaderCalculationsDomain {
public:
    SteamSystemModelerTool::FluidProperties combinedCondensate;
    SteamSystemModelerTool::FluidProperties returnCondensate;
    ReturnCondensateCalculationsDomain returnCondensateCalculationsDomain;
    SteamSystemModelerTool::FluidProperties makeupWater;
    MakeupWaterVolumeFlowCalculationsDomain makeupWaterVolumeFlowCalculationsDomain;
    std::shared_ptr <HeatExchanger::Output> heatExchangerOutput;
    SteamSystemModelerTool::FluidProperties makeupWaterAndCondensateHeaderOutput;

    friend std::ostream &operator<<(std::ostream &stream, const MakeupWaterAndCondensateHeaderCalculationsDomain &domain) {
        stream << "MakeupWaterAndCondensateHeaderCalculationsDomain["
               << "combinedCondensate=" << domain.combinedCondensate
               << ", returnCondensate=" << domain.returnCondensate
               << ", returnCondensateCalculationsDomain=" << domain.returnCondensateCalculationsDomain
               << ", makeupWater=" << domain.makeupWater
               << ", makeupWaterVolumeFlowCalculationsDomain=" << domain.makeupWaterVolumeFlowCalculationsDomain
               << ", heatExchangerOutput=" << domain.heatExchangerOutput
               << ", makeupWaterAndCondensateHeaderOutput=" << domain.makeupWaterAndCondensateHeaderOutput
               << "]";
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_MAKEUPWATERANDCONDENSATEHEADERCALCULATIONSDOMAIN_H
