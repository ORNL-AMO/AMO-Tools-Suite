#ifndef AMO_TOOLS_SUITE_PRVWITHDESUPERHEATINGFACTORY_H
#define AMO_TOOLS_SUITE_PRVWITHDESUPERHEATINGFACTORY_H

#include <ssmt/PRV.h>
#include <ssmt/SteamProperties.h>
#include <ssmt/api/HeaderInput.h>

class PrvWithDesuperheatingFactory {
public:
    PrvWithDesuperheating make(const SteamSystemModelerTool::FluidProperties &remainingSteam, const double massFlow,
                               const std::shared_ptr<HeaderNotHighestPressure> &headerNotHighestPressure,
                               const double feedwaterPressure) const;
};

#endif //AMO_TOOLS_SUITE_PRVWITHDESUPERHEATINGFACTORY_H
