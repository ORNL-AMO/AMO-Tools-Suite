#ifndef AMO_TOOLS_SUITE_HEATLOSSFACTORY_H
#define AMO_TOOLS_SUITE_HEATLOSSFACTORY_H

#include <ssmt/api/HeaderInput.h>
#include "ssmt/Header.h"
#include "ssmt/HeatLoss.h"

class HeatLossFactory {
public:
    const HeatLoss make(const HeaderWithHighestPressure &highestPressureHeaderInput,
                        const SteamSystemModelerTool::FluidProperties &headerOutput) const;

    const HeatLoss make(const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput,
                        const SteamSystemModelerTool::FluidProperties &headerOutput) const;
};

#endif //AMO_TOOLS_SUITE_HEATLOSSFACTORY_H
