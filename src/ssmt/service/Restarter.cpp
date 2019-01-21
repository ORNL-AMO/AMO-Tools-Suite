#include <ssmt/service/Restarter.h>
#include <ssmt/service/SteamBalanceException.h>

void Restarter::restartIfNotEnoughSteam(const std::shared_ptr<Turbine> &turbine, const double availableMassFlow,
                                        const Boiler &boiler) const {
    const std::string methodName = "Restarter::restartIfNotEnoughSteam(turbine, need, boiler): ";

    // additional steam needed = amount needed - current amount
    const double neededMassFlow = turbine->getMassFlow();
    const double additionalSteamNeeded = neededMassFlow - availableMassFlow;

    std::cout << methodName
              << "neededMassFlow=" << neededMassFlow << ", availableMassFlow=" << availableMassFlow
              << ", additionalSteamNeeded=" << additionalSteamNeeded << std::endl;

    restartIfNotEnoughSteam(additionalSteamNeeded, boiler);
}

void Restarter::restartIfNotEnoughSteam(const double additionalSteamNeeded, const Boiler &boiler) const {
    const std::string methodName = "Restarter::restartIfNotEnoughSteam(need, boiler): ";

    const double absAdditionalSteamNeeded = abs(additionalSteamNeeded);

    const double tolerance = 1e-3;

    std::cout << methodName
              << "checking if the steam amount shortage is within tolerance; additionalSteamNeeded="
              << additionalSteamNeeded << "; tolerance=+-" << tolerance << std::endl;

    //if need more than .0001
    if (absAdditionalSteamNeeded > tolerance) {
        std::cout << methodName
                  << "additionalSteamNeeded=" << absAdditionalSteamNeeded << " > " << tolerance << "; starting over"
                  << std::endl;
        //re-run model with additional needed steam added
        const double steamMassFlow = boiler.getSteamMassFlow();
        double adjustedSteam = steamMassFlow + additionalSteamNeeded;
        std::cout << methodName
                  << "steamMassFlow=" << steamMassFlow << ", additionalSteamNeeded=" << additionalSteamNeeded
                  << ", adjustedSteam=" << adjustedSteam << std::endl;
        throw SteamBalanceException(additionalSteamNeeded, adjustedSteam);
    } else {
        std::cout << methodName
                  << "additionalSteamNeeded=" << absAdditionalSteamNeeded << " < " << tolerance << "; continuing"
                  << std::endl;
    }
}

//TODO this is actually SteamBalanceChecker
//void Restarter::restartIfNotEnoughSteam(const std::shared_ptr<Turbine> &turbine, const double availableMassFlow,
//                                        const Boiler &boiler, const PressureTurbine &highToLowTurbineInput,
//                                        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
//                                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
//                                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
//    const std::string methodName = "Restarter::restartIfNotEnoughSteam: ";
//
//    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;
//
//    // additional steam needed = amount needed - current amount
//    const double additionalSteamNeeded = turbine->getMassFlow() - availableMassFlow;
//    const double absAdditionalSteamNeeded = std::abs(additionalSteamNeeded);
//
//    std::cout << methodName
//              << "checking if the steam amount shortage is within tolerance; additionalSteamNeeded="
//              << absAdditionalSteamNeeded << "; tolerance=" << 1e-3 << std::endl;
//
//    //if need more than .0001
//    if (absAdditionalSteamNeeded > 1e-3) {
//        std::cout << methodName
//                  << "additionalSteamNeeded=" << absAdditionalSteamNeeded << " > " << 1e-3
//                  << " > " << 1e-3 << "; attempting to take steam needed from high to low turbine"
//                  << std::endl;
//        const SteamReducerOutput &steamReducerOutput =
//                steamReducer.reduceSteamThroughHighToLowTurbine(additionalSteamNeeded,
//                                                                highToLowTurbineInput,
//                                                                highToLowPressureTurbine,
//                                                                highPressureHeaderOutput,
//                                                                lowPressureHeaderInput);
//        const double remainingAdditionalSteamNeeded =
//                steamReducerOutput.remainingAdditionalSteamNeeded;
//        highToLowPressureTurbineUpdated = steamReducerOutput.highToLowPressureTurbineUpdated;
//
//        restarter.restartIfNotEnoughSteam(remainingAdditionalSteamNeeded, boiler);
//    } else {
//        std::cout << methodName
//                  << "additionalSteamNeeded=" << absAdditionalSteamNeeded << " < " << 1e-3
//                  << "; has enough steam????" << std::endl;
//    }
//}
