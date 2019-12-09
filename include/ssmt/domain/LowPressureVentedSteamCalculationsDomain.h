#ifndef AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATIONSDOMAIN_H

#include <ssmt/Deaerator.h>
#include <ssmt/SteamSystemModelerTool.h>
#include "MakeupWaterVolumeFlowCalculationsDomain.h"

class LowPressureVentedSteamCalculationsDomain {
public:
    double lowPressureVentedSteam;
    SteamSystemModelerTool::FluidProperties makeupWater;
    SteamSystemModelerTool::FluidProperties makeupWaterAndCondensateHeaderOutputUpdated;
    MakeupWaterVolumeFlowCalculationsDomain makeupWaterVolumeFlowCalculationsDomain;
    Deaerator deaerator;

    friend std::ostream &operator<<(std::ostream &stream, const LowPressureVentedSteamCalculationsDomain &domain) {
        stream << "LowPressureVentedSteamCalculationsDomain["
               << "lowPressureVentedSteam=" << domain.lowPressureVentedSteam
               << ", makeupWater=" << domain.makeupWater
               << ", makeupWaterAndCondensateHeaderOutputUpdated=" << domain.makeupWaterAndCondensateHeaderOutputUpdated
               << ", makeupWaterVolumeFlowCalculationsDomain=" << domain.makeupWaterVolumeFlowCalculationsDomain
               << ", deaerator=" << domain.deaerator
               << "]";
        return stream;
    }

    friend std::ostream &
    operator<<(std::ostream &stream, const std::shared_ptr<LowPressureVentedSteamCalculationsDomain> &domain) {
        if (domain == nullptr) {
            stream << "LowPressureVentedSteamCalculationsDomain[nullptr]";
        } else {
            stream << *domain;
        }
        return stream;
    }
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATIONSDOMAIN_H
