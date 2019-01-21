#ifndef AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATIONSDOMAIN_H

#include <ssmt/Deaerator.h>
#include <ssmt/SteamSystemModelerTool.h>
#include "MakeupWaterVolumeFlowCalculationsDomain.h"

class LowPressureVentedSteamCalculationsDomain {
public:
    double lowPressureVentedSteam;
    SteamSystemModelerTool::FluidProperties makeupWaterAndMassFlow;
    SteamSystemModelerTool::FluidProperties makeupWaterAndCondensateHeaderOutputUpdated;
    MakeupWaterVolumeFlowCalculationsDomain makeupWaterVolumeFlowCalculationsDomain;
    Deaerator deaerator;
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREVENTEDSTEAMCALCULATIONSDOMAIN_H
