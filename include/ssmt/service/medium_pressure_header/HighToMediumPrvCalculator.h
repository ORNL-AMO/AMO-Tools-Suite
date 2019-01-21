#ifndef AMO_TOOLS_SUITE_HIGHTOMEDIUMPRVCALCULATOR_H
#define AMO_TOOLS_SUITE_HIGHTOMEDIUMPRVCALCULATOR_H

#include <ssmt/PRV.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include "ssmt/service/PrvCalculator.h"

class HighToMediumPrvCalculator {
public:
    const std::shared_ptr<PrvWithoutDesuperheating>
    calc(const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const SteamSystemModelerTool::FluidProperties &highPressureCondensate,
         const HeaderWithHighestPressure &highPressureHeaderInput, const PressureTurbine &highToLowTurbineInput,
         const PressureTurbine &highToMediumTurbineInput, const CondensingTurbine &condensingTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
         const std::shared_ptr<Turbine> &condensingTurbine) const;

private:
    const PrvCalculator prvCalculator = PrvCalculator();
};

#endif //AMO_TOOLS_SUITE_HIGHTOMEDIUMPRVCALCULATOR_H
