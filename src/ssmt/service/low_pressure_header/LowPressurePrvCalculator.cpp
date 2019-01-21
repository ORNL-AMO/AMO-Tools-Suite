#include "ssmt/service/low_pressure_header/LowPressurePrvCalculator.h"

std::shared_ptr<PrvWithoutDesuperheating>
LowPressurePrvCalculator::calc(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                               const PressureTurbine &highToLowTurbineInput,
                               const CondensingTurbine &condensingTurbineInput,
                               const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                               const PressureTurbine &mediumToLowTurbineInput,
                               const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                               const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain,
                               const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const {
    std::shared_ptr<PrvWithoutDesuperheating> prvPtr;

    const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput =
            highPressureHeaderCalculationsDomain.highPressureHeaderOutput;
    const std::shared_ptr<Turbine> &highToLowPressureTurbine =
            highPressureHeaderCalculationsDomain.highToLowPressureTurbine;
    const std::shared_ptr<Turbine> &condensingTurbine =
            highPressureHeaderCalculationsDomain.condensingTurbine;

    double prvMassFlow =
            calcPrvMassFlow(headerCountInput, highPressureHeaderInput, highPressureHeaderOutput, highToLowTurbineInput,
                            highToLowPressureTurbine, condensingTurbineInput, condensingTurbine,
                            mediumPressureHeaderInput, mediumToLowTurbineInput,
                            mediumPressureHeaderCalculationsDomain);
    if (lowPressureHeaderInput->isDesuperheatSteamIntoNextHighest()) {
        const SteamSystemModelerTool::FluidProperties &mediumPressureCondensate =
                mediumPressureHeaderCalculationsDomain->mediumPressureCondensate;
        const PrvWithDesuperheating &prv =
                prvWithDesuperheatingFactory.make(highPressureHeaderOutput, prvMassFlow, lowPressureHeaderInput,
                                                  mediumPressureCondensate);
        prvPtr = std::make_shared<PrvWithDesuperheating>(prv);
    } else {
        const PrvWithoutDesuperheating &prv =
                prvWithoutDesuperheatingFactory.make(highPressureHeaderOutput, prvMassFlow, lowPressureHeaderInput);
        prvPtr = std::make_shared<PrvWithoutDesuperheating>(prv);
    }

    return prvPtr;
}

double
LowPressurePrvCalculator::calcPrvMassFlow(const int headerCountInput,
                                          const HeaderWithHighestPressure &highPressureHeaderInput,
                                          const SteamSystemModelerTool::FluidProperties &highPressureHeader,
                                          const PressureTurbine &highToLowTurbineInput,
                                          const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                          const CondensingTurbine &condensingTurbineInput,
                                          const std::shared_ptr<Turbine> &condensingTurbine,
                                          const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                          const PressureTurbine &mediumToLowTurbineInput,
                                          const std::shared_ptr<MediumPressureHeaderCalculationsDomain> &mediumPressureHeaderCalculationsDomain) const {
    double prvMassFlow = 0;

    //either medium to low or high to low
    if (headerCountInput == 2) {
        //if 2 headers, next highest is high pressure
        prvMassFlow = highPressureHeader.massFlow - highPressureHeaderInput.getProcessSteamUsage();
        if (highToLowTurbineInput.isUseTurbine()) {
            prvMassFlow = prvMassFlow - highToLowPressureTurbine->getMassFlow();
        }
        if (condensingTurbineInput.isUseTurbine()) {
            prvMassFlow = prvMassFlow - condensingTurbine->getMassFlow();
        }
    } else if (headerCountInput == 3) {
        // if 3 headers, next highest is medium pressure
        const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput =
                mediumPressureHeaderCalculationsDomain->mediumPressureHeaderOutput;
        prvMassFlow = mediumPressureHeaderOutput.massFlow - mediumPressureHeaderInput->getProcessSteamUsage();
        if (mediumToLowTurbineInput.isUseTurbine()) {
            const std::shared_ptr<Turbine> &mediumToLowPressureTurbine =
                    mediumPressureHeaderCalculationsDomain->mediumToLowPressureTurbine;
            prvMassFlow = prvMassFlow - mediumToLowPressureTurbine->getMassFlow();
        }
    }

    return fmax(prvMassFlow, 0);
}
