#ifndef AMO_TOOLS_SUITE_PRVCALCULATOR_H
#define AMO_TOOLS_SUITE_PRVCALCULATOR_H

#include <ssmt/SteamSystemModelerTool.h>
#include <ssmt/Turbine.h>
#include <ssmt/api/HeaderInput.h>
#include <ssmt/api/TurbineInput.h>
#include <ssmt/domain/PrvWithDesuperheatingFactory.h>
#include <ssmt/domain/PrvWithoutDesuperheatingFactory.h>
#include <ssmt/Boiler.h>

class PrvCalculator {
public:
    PrvWithDesuperheating
    calcHighToMediumPrvWithDesuperheating(const HeaderWithHighestPressure &highPressureHeaderInput,
                                          const PressureTurbine &highToLowTurbineInput,
                                          const PressureTurbine &highToMediumTurbineInput,
                                          const CondensingTurbine &condensingTurbineInput,
                                          const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                          const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
                                          const std::shared_ptr<Turbine> &condensingTurbine,
                                          const Boiler &boiler,
                                          const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

    PrvWithoutDesuperheating
    calcHighToMediumPrvWithoutDesuperheating(
            const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
            const HeaderWithHighestPressure &highPressureHeaderInput,
            const PressureTurbine &highToLowTurbineInput,
            const PressureTurbine &highToMediumTurbineInput,
            const CondensingTurbine &condensingTurbineInput,
            const std::shared_ptr<Turbine> &highToLowPressureTurbine,
            const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
            const std::shared_ptr<Turbine> &condensingTurbine,
            const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const;

private:
    const PrvWithDesuperheatingFactory prvWithDesuperheatingFactory = PrvWithDesuperheatingFactory();
    const PrvWithoutDesuperheatingFactory prvWithoutDesuperheatingFactory = PrvWithoutDesuperheatingFactory();

    double calcPrvMassFlow(const SteamSystemModelerTool::FluidProperties &highPressureHeader,
                           const HeaderWithHighestPressure &highPressureHeaderInput,
                           const PressureTurbine &highToLowTurbineInput,
                           const PressureTurbine &highToMediumTurbineInput,
                           const CondensingTurbine &condensingTurbineInput,
                           const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                           const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
                           const std::shared_ptr<Turbine> &condensingTurbine) const;

    double getTurbineMassFlow(const std::shared_ptr<Turbine> &turbine, const std::string &turbineName) const;
};

#endif //AMO_TOOLS_SUITE_PRVCALCULATOR_H
