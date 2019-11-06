#ifndef AMO_TOOLS_SUITE_HEATEXCHANGERCALCULATOR_H
#define AMO_TOOLS_SUITE_HEATEXCHANGERCALCULATOR_H

#include <memory>
#include <ssmt/FlashTank.h>
#include <ssmt/HeatExchanger.h>
#include <ssmt/api/BoilerInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>

class HeatExchangerCalculator {
public:
    std::shared_ptr<HeatExchanger::Output> calc(const BoilerInput &boilerInput, const Boiler &boiler,
                                                const SteamSystemModelerTool::FluidProperties &makeupWaterAndMassFlow,
                                                const std::shared_ptr<FlashTank> &blowdownFlashTank) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
};

#endif //AMO_TOOLS_SUITE_HEATEXCHANGERCALCULATOR_H
