#ifndef AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATOR_H
#define AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATOR_H

#include <ssmt/FlashTank.h>
#include <ssmt/PRV.h>
#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/FluidPropertiesFactory.h>
#include <ssmt/domain/HeaderFactory.h>
#include <ssmt/service/Restarter.h>
#include <ssmt/service/SteamReducer.h>

class MediumPressureHeaderCalculatorOutput {
public:
    SteamSystemModelerTool::FluidProperties mediumPressureHeaderOutput;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated;
};

class MediumPressureHeaderCalculator {
public:
    MediumPressureHeaderCalculatorOutput
    calc(const Boiler &boiler, const PressureTurbine &highToLowTurbineInput,
         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
         const std::shared_ptr<PrvWithoutDesuperheating> &highToMediumPressurePrv, const PressureTurbine &highToMediumTurbineInput,
         const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
         const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank,
         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const;

private:
    const FluidPropertiesFactory fluidPropertiesFactory = FluidPropertiesFactory();
    const HeaderFactory headerFactory = HeaderFactory();
    const Restarter restarter = Restarter();
    const SteamReducer steamReducer = SteamReducer();

    std::shared_ptr<Turbine>
    checkSteamBalance(const Boiler &boiler, const PressureTurbine &highToLowTurbineInput,
                      const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                      const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                      const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                      const double mediumPressureHeaderMassFlow,
                      const double mediumPressureHeaderInputProcessSteamUsage) const;
};

#endif //AMO_TOOLS_SUITE_MEDIUMPRESSUREHEADERCALCULATOR_H
