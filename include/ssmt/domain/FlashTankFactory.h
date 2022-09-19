#ifndef AMO_TOOLS_SUITE_FLASHTANKFACTORY_H
#define AMO_TOOLS_SUITE_FLASHTANKFACTORY_H

#include <ssmt/Boiler.h>
#include <ssmt/FlashTank.h>
#include <ssmt/Header.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>

class FlashTankFactory {
public:
    std::shared_ptr<FlashTank>
    make(const HeaderInput &headerInput, const BoilerInput &boilerInput, const Boiler &boiler) const;

    FlashTank make(const double pressure, const Boiler &boiler) const;

    FlashTank make(const double pressure, const SteamSystemModelerTool::FluidProperties &condensate) const;

    FlashTank make(const std::shared_ptr<Header> &header,
                   const std::shared_ptr<HeaderNotHighestPressure> &headerNotHighestPressure) const;

    FlashTank
    make(const SteamSystemModelerTool::FluidProperties &properties) const;
};

#endif //AMO_TOOLS_SUITE_FLASHTANKFACTORY_H
