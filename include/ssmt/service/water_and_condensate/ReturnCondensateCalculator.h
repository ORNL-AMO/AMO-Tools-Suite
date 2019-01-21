#ifndef AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATOR_H
#define AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATOR_H

#include <ssmt/Header.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/FlashTankFactory.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/ReturnCondensateCalculationsDomain.h>

class ReturnCondensateCalculator {
public:
    SteamSystemModelerTool::FluidProperties
    calc(const HeaderWithHighestPressure &highPressureHeaderInput, const Header &combinedCondensateHeader) const;

    ReturnCondensateCalculationsDomain
    flash(const HeaderWithHighestPressure &highPressureHeaderInput, const BoilerInput &boilerInput,
          const SteamSystemModelerTool::FluidProperties &returnCondensate) const;

private:
    FlashTankFactory flashTankFactory = FlashTankFactory();
    FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
};

#endif //AMO_TOOLS_SUITE_RETURNCONDENSATECALCULATOR_H
