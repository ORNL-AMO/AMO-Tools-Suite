#ifndef AMO_TOOLS_SUITE_DEAERATORFACTORY_H
#define AMO_TOOLS_SUITE_DEAERATORFACTORY_H

#include <ssmt/Deaerator.h>
#include <ssmt/Header.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>

class DeaeratorFactory {
public:
    const Deaerator make(const BoilerInput &boilerInput, const double feedwaterMassFlow,
                         const SteamSystemModelerTool::FluidProperties &makeupWaterAndCondensateHeaderOutput,
                         const SteamSystemModelerTool::FluidProperties &inletHeaderOutput) const;

};

#endif //AMO_TOOLS_SUITE_DEAERATORFACTORY_H
