#ifndef AMO_TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H
#define AMO_TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H

#include "CondensingTurbineCalculator.h"
#include "HighPressureCondensateCalculator.h"
#include "HighPressureFlashTankCalculator.h"
#include "HighPressureHeaderCalculator.h"
#include "HighToLowSteamTurbineCalculator.h"
#include "HighToMediumSteamTurbineCalculator.h"
#include <ssmt/Boiler.h>
#include <ssmt/FlashTank.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/HeatLossFactory.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>

class HighPressureHeaderModeler {
public:
    HighPressureHeaderCalculationsDomain
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
          const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
          const CondensingTurbine &condensingTurbineInput, const Boiler &boiler) const;

    HighToMediumSteamTurbineCalculationsDomain
    calcHighToMediumSteamTurbine(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                 const PressureTurbine &highToMediumTurbineInput,
                                 const PressureTurbine &highToLowTurbineInput,
                                 const CondensingTurbine &condensingTurbineInput, const Boiler &boiler,
                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                 const std::shared_ptr<Turbine> &condensingTurbine,
                                 const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                 const std::shared_ptr<Turbine> &highToLowPressureTurbineIdeal) const;

private:
    const CondensingTurbineCalculator condensingTurbineCalculator = CondensingTurbineCalculator();
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeatLossFactory heatLossFactory = HeatLossFactory();
    const HighPressureCondensateCalculator highPressureCondensateCalculator = HighPressureCondensateCalculator();
    const HighPressureFlashTankCalculator highPressureFlashTankCalculator = HighPressureFlashTankCalculator();
    const HighPressureHeaderCalculator highPressureHeaderCalculator = HighPressureHeaderCalculator();
    const HighToLowSteamTurbineCalculator highToLowSteamTurbineCalculator = HighToLowSteamTurbineCalculator();
    const HighToMediumSteamTurbineCalculator highToMediumSteamTurbineCalculator = HighToMediumSteamTurbineCalculator();
};

#endif //AMO_TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H
