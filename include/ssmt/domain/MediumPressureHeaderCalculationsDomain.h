#ifndef AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATIONSDOMAIN_H
#define AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATIONSDOMAIN_H

#include <memory>
#include <ssmt/FlashTank.h>
#include <ssmt/PRV.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>

class MediumPressureHeaderCalculationsDomain {
public:
    std::shared_ptr<PrvWithoutDesuperheating> highToMediumPressurePrv;
    std::shared_ptr<FlashTank> highPressureCondensateFlashTank;
    SteamSystemModelerTool::FluidProperties mediumPressureHeaderOutput;
    SteamSystemModelerTool::FluidProperties heatLossOutletProperties;
    SteamSystemModelerTool::FluidProperties mediumPressureCondensate;
    std::shared_ptr<Turbine> mediumToLowPressureTurbine;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
};

#endif //AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATIONSDOMAIN_H
