#include "ssmt/service/medium_pressure_header/HighToMediumPrvCalculator.h"

const std::shared_ptr<PrvWithoutDesuperheating>
HighToMediumPrvCalculator::calc(const HeaderWithHighestPressure &highPressureHeaderInput,
                                const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                const PressureTurbine &highToLowTurbineInput,
                                const PressureTurbine &highToMediumTurbineInput,
                                const CondensingTurbine &condensingTurbineInput,
                                const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
                                const std::shared_ptr<Turbine> &condensingTurbine, const Boiler &boiler,
                                const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const {
    std::shared_ptr<PrvWithoutDesuperheating> prvPtr;

    if (mediumPressureHeaderInput->isDesuperheatSteamIntoNextHighest()) {
        const PrvWithDesuperheating &prv =
                prvCalculator.calcHighToMediumPrvWithDesuperheating(highPressureHeaderInput, highToLowTurbineInput,
                                                                    highToMediumTurbineInput, condensingTurbineInput,
                                                                    highToLowPressureTurbine,
                                                                    highToMediumPressureTurbine, condensingTurbine,
                                                                    boiler, highPressureHeaderOutput,
                                                                    mediumPressureHeaderInput);
        prvPtr = std::make_shared<PrvWithDesuperheating>(prv);
    } else {
        const PrvWithoutDesuperheating &prv =
                prvCalculator.calcHighToMediumPrvWithoutDesuperheating(highPressureHeaderOutput,
                                                                       highPressureHeaderInput, highToLowTurbineInput,
                                                                       highToMediumTurbineInput, condensingTurbineInput,
                                                                       highToLowPressureTurbine,
                                                                       highToMediumPressureTurbine, condensingTurbine,
                                                                       mediumPressureHeaderInput);
        prvPtr = std::make_shared<PrvWithoutDesuperheating>(prv);
    }

    return prvPtr;
}
