#ifndef AMO_TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/FlashTank.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>

class HighPressureHeaderCalculationsDomain {
public:
    SteamSystemModelerTool::FluidProperties highPressureHeaderOutput;
    SteamSystemModelerTool::FluidProperties highPressureCondensate;
    std::shared_ptr<FlashTank> highPressureCondensateFlashTank;
    std::shared_ptr<Turbine> condensingTurbine;
    std::shared_ptr<Turbine> highToMediumPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbine;
};

#endif //AMO_TOOLS_SUITE_HIGHPRESSUREHEADERCALCULATIONSDOMAIN_H
