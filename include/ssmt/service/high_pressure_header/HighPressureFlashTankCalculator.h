#ifndef AMO_TOOLS_SUITE_HIGHPRESSUREFLASHTANKCALCULATOR_H
#define AMO_TOOLS_SUITE_HIGHPRESSUREFLASHTANKCALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/FlashTank.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/domain/FlashTankFactory.h>

class HighPressureFlashTankCalculator
{
public:
    const std::shared_ptr<FlashTank>
    calc(const int headerCountInput, const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &highPressureCondensate) const;

private:
    const FlashTankFactory flashTankFactory = FlashTankFactory();
};

#endif //AMO_TOOLS_SUITE_HIGHPRESSUREFLASHTANKCALCULATOR_H
