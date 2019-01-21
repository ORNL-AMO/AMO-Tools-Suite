#ifndef AMO_TOOLS_SUITE_LOWPRESSUREFLASHEDSTEAMINTOHEADERCALCULATOR_H
#define AMO_TOOLS_SUITE_LOWPRESSUREFLASHEDSTEAMINTOHEADERCALCULATOR_H

#include <memory>
#include <ssmt/FlashTank.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/FlashTankFactory.h>
#include <ssmt/domain/HeaderFactory.h>
#include <ssmt/domain/LowPressureFlashedSteamIntoHeaderCalculatorDomain.h>

class LowPressureFlashedSteamIntoHeaderCalculator {
public:
    LowPressureFlashedSteamIntoHeaderCalculatorDomain
    calc(const int headerCountInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
         const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const;

private:
    const FlashTankFactory flashTankFactory = FlashTankFactory();
    const HeaderFactory headerFactory = HeaderFactory();

    std::shared_ptr<FlashTank>
    makeMediumPressureCondensateFlashTank(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                          const SteamSystemModelerTool::FluidProperties &mediumPressureCondensate,
                                          const SteamSystemModelerTool::FluidProperties &highPressureCondensate,
                                          const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank) const;

    std::shared_ptr<FlashTank>
    makeHighPressureCondensateFlashTank(const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                        const SteamSystemModelerTool::FluidProperties &highPressureCondensate) const;
};

#endif //AMO_TOOLS_SUITE_LOWPRESSUREFLASHEDSTEAMINTOHEADERCALCULATOR_H
