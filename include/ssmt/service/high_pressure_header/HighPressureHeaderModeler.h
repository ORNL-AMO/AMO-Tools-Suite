#ifndef AMO_TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H
#define AMO_TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H

#include "CondensingTurbineCalculator.h"
#include "HighPressureCondensateCalculator.h"
#include "HighPressureFlashTankCalculator.h"
#include "HighPressureHeaderCalculator.h"
#include "HighPressureHeatLossCalculator.h"
#include "HighToLowSteamTurbineCalculator.h"
#include "HighToMediumSteamTurbineCalculator.h"
#include <ssmt/Boiler.h>
#include <ssmt/FlashTank.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/HighPressureHeaderCalculationsDomain.h>

class HighPressureHeaderModeler {
public:
    HighPressureHeaderCalculationsDomain
    model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
              const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
              const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
              const PressureTurbine &highToMediumTurbineInput, const PressureTurbine &highToLowTurbineInput,
              const CondensingTurbine &condensingTurbineInput, const Boiler &boiler) const;

private:
    CondensingTurbineCalculator condensingTurbineCalculator = CondensingTurbineCalculator();
    HighPressureHeatLossCalculator heatLossCalculator = HighPressureHeatLossCalculator();
    HighPressureCondensateCalculator highPressureCondensateCalculator = HighPressureCondensateCalculator();
    HighPressureFlashTankCalculator highPressureFlashTankCalculator = HighPressureFlashTankCalculator();
    HighPressureHeaderCalculator highPressureHeaderCalculator = HighPressureHeaderCalculator();
    HighToLowSteamTurbineCalculator highToLowSteamTurbineCalculator = HighToLowSteamTurbineCalculator();
    HighToMediumSteamTurbineCalculator highToMediumSteamTurbineCalculator = HighToMediumSteamTurbineCalculator();
};

#endif //AMO_TOOLS_SUITE_HIGHPRESSUREHEADERMODELER_H
