#include "ssmt/service/high_pressure_header/HighToMediumSteamTurbineCalculator.h"

HighToMediumSteamTurbineCalculationsDomain
HighToMediumSteamTurbineCalculator::calc(const int headerCountInput,
                                         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                         const HeaderWithHighestPressure &highPressureHeaderInput,
                                         const CondensingTurbine &condensingTurbineInput,
                                         const std::shared_ptr<Turbine> &condensingTurbine,
                                         const PressureTurbine &highToLowTurbineInput,
                                         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                         const PressureTurbine &highToMediumTurbineInput,
                                         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                         const Boiler &boiler) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::calc: ";

    HighToMediumSteamTurbineCalculationsDomain highToMediumSteamTurbineCalculationsDomain;

    if (headerCountInput == 3 && highToMediumTurbineInput.isUseTurbine()) {
        std::cout << methodName
                  << "medium turbine provided and highToMediumTurbineInput isUseTurbine, calculating highToMediumPressureTurbine"
                  << std::endl;

        const double availableMassFlow =
                calcAvailableMassFlow(highPressureHeaderInput, highPressureHeaderOutput, condensingTurbineInput,
                                      condensingTurbine, highToLowTurbineInput, highToLowPressureTurbine);
        highToMediumSteamTurbineCalculationsDomain =
                calc(availableMassFlow, highToLowTurbineInput, highToLowPressureTurbine, highToMediumTurbineInput,
                     mediumPressureHeaderInput, highPressureHeaderOutput, lowPressureHeaderInput,
                     boiler);
    } else {
        std::cout << methodName << "medium turbine not provided and highToMediumTurbineInput not isUseTurbine, skipping"
                  << std::endl;
    }

    return highToMediumSteamTurbineCalculationsDomain;
}

HighToMediumSteamTurbineCalculationsDomain
HighToMediumSteamTurbineCalculator::calc(const double availableMassFlow, const PressureTurbine &highToLowTurbineInput,
                                         const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                         const PressureTurbine &highToMediumTurbineInput,
                                         const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                         const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                         const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                         const Boiler &boiler) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::calc: ";

    HighToMediumSteamTurbineCalculationsDomain highToMediumSteamTurbineCalculationsDomain;

    const PressureTurbineOperation &pressureTurbineOperation = highToLowTurbineInput.getOperationType();
    std::cout << methodName << "pressureTurbineOperation=" << pressureTurbineOperation << std::endl;

    switch (pressureTurbineOperation) {
        case PressureTurbineOperation::FLOW_RANGE:
            highToMediumSteamTurbineCalculationsDomain =
                    calcFlowRange(availableMassFlow, highToLowTurbineInput, highToLowPressureTurbine,
                                  highToMediumTurbineInput, highPressureHeaderOutput, mediumPressureHeaderInput,
                                  lowPressureHeaderInput, boiler);
            break;
        case PressureTurbineOperation::POWER_RANGE:
            highToMediumSteamTurbineCalculationsDomain =
                    calcPowerRange(availableMassFlow, highToLowTurbineInput, highToLowPressureTurbine,
                                   highToMediumTurbineInput, highPressureHeaderOutput, mediumPressureHeaderInput,
                                   lowPressureHeaderInput, boiler);
            break;
        case PressureTurbineOperation::POWER_GENERATION:
            highToMediumSteamTurbineCalculationsDomain =
                    calcPowerGeneration(availableMassFlow, highToLowTurbineInput, highToLowPressureTurbine,
                                        highToMediumTurbineInput, highPressureHeaderOutput, mediumPressureHeaderInput,
                                        lowPressureHeaderInput, boiler);
            break;
        case PressureTurbineOperation::STEAM_FLOW:
            highToMediumSteamTurbineCalculationsDomain =
                    calcSteamFlow(availableMassFlow, highToLowTurbineInput, highToLowPressureTurbine,
                                  highToMediumTurbineInput, highPressureHeaderOutput, mediumPressureHeaderInput,
                                  lowPressureHeaderInput, boiler);
            break;
        case PressureTurbineOperation::BALANCE_HEADER:
            highToMediumSteamTurbineCalculationsDomain =
                    calcBalanceHeader(availableMassFlow, highToLowPressureTurbine, highToMediumTurbineInput,
                                      highPressureHeaderOutput, mediumPressureHeaderInput);
            break;
        default:
            std::string msg = methodName + "PressureTurbineOperation enum not handled";
            std::cout << msg << std::endl;
            throw std::invalid_argument(msg);
    }

    return highToMediumSteamTurbineCalculationsDomain;
}

HighToMediumSteamTurbineCalculationsDomain
HighToMediumSteamTurbineCalculator::calcFlowRange(const double availableMassFlow,
                                                  const PressureTurbine &highToLowTurbineInput,
                                                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                  const PressureTurbine &highToMediumTurbineInput,
                                                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                  const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                  const Boiler &boiler) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::calcFlowRange: ";

    std::shared_ptr<Turbine> highToMediumPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double highToMediumTurbineInputOperationValue1 = highToMediumTurbineInput.getOperationValue1();
    const double highToMediumTurbineInputOperationValue2 = highToMediumTurbineInput.getOperationValue2();

    //if more steam needed for minimum than is available
    if (highToMediumTurbineInputOperationValue1 > availableMassFlow) {
        std::cout << methodName
                  << "highToMediumTurbineInputOperationValue1=" << highToMediumTurbineInputOperationValue1
                  << " > availableMassFlow=" << availableMassFlow
                  << ", calculating highToMediumPressureTurbine with amount needed (highToMediumTurbineInputOperationValue1)"
                  << " instead of amount available" << std::endl;
        //calculate turbine with amount needed
        highToMediumPressureTurbine =
                turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToMediumTurbineInput,
                                                   highToMediumTurbineInputOperationValue1, mediumPressureHeaderInput);
        highToLowPressureTurbineUpdated =
                checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput, highToLowPressureTurbine,
                                  lowPressureHeaderInput, boiler, highToMediumPressureTurbine, availableMassFlow);
    } else if (highToMediumTurbineInputOperationValue2 < availableMassFlow) {
        std::cout << methodName
                  << "highToMediumTurbineInputOperationValue2=" << highToMediumTurbineInputOperationValue2
                  << " < availableMassFlow=" << availableMassFlow
                  << ", calculating highToMediumPressureTurbine with max amount allowed (highToMediumTurbineInputOperationValue2)"
                  << " instead of the greater amount available" << std::endl;
        highToMediumPressureTurbine =
                turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToMediumTurbineInput,
                                                   highToMediumTurbineInputOperationValue2, mediumPressureHeaderInput);
    } else {
        std::cout << methodName
                  << "availableMassFlow=" << availableMassFlow << " is between needed and max amounts,"
                  << " calculating highToMediumPressureTurbine with availableMassFlow" << std::endl;
        highToMediumPressureTurbine =
                turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToMediumTurbineInput,
                                                   availableMassFlow, mediumPressureHeaderInput);
    }

    return {highToMediumPressureTurbine, highToLowPressureTurbineUpdated};
}

HighToMediumSteamTurbineCalculationsDomain
HighToMediumSteamTurbineCalculator::calcPowerRange(const double availableMassFlow,
                                                   const PressureTurbine &highToLowTurbineInput,
                                                   const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                   const PressureTurbine &highToMediumTurbineInput,
                                                   const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                   const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                   const Boiler &boiler) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::calcPowerRange: ";

    std::shared_ptr<Turbine> highToMediumPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double highToMediumTurbineInputOperationValue1 = highToMediumTurbineInput.getOperationValue1();
    const double highToMediumTurbineInputOperationValue2 = highToMediumTurbineInput.getOperationValue2();

    std::cout << methodName
              << "calculating highToMediumPressureTurbine with availableMassFlow=" << availableMassFlow << std::endl;
    highToMediumPressureTurbine =
            turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToMediumTurbineInput, availableMassFlow,
                                               mediumPressureHeaderInput);
    //check to see if power out is in range
    const double highToMediumPressureTurbinePowerOut = highToMediumPressureTurbine->getPowerOut();
    if (highToMediumTurbineInputOperationValue1 > highToMediumPressureTurbinePowerOut) {
        std::cout << methodName
                  << "highToMediumTurbineInputOperationValue1=" << highToMediumTurbineInputOperationValue1
                  << " > highToMediumPressureTurbinePowerOut=" << highToMediumPressureTurbinePowerOut
                  << "; not enough power out of turbine,"
                  << " calculating highToMediumPressureTurbine with amount needed instead of amount available"
                  << std::endl;
        double currentMassFlowAvailable = highToMediumPressureTurbine->getMassFlow();
        //calculate minimum mass flow needed
        highToMediumPressureTurbine =
                turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToMediumTurbineInput,
                                                   highToMediumTurbineInputOperationValue1, mediumPressureHeaderInput);
        highToLowPressureTurbineUpdated = checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput,
                                                            highToLowPressureTurbine, lowPressureHeaderInput, boiler,
                                                            highToMediumPressureTurbine, currentMassFlowAvailable);
    } else if (highToMediumTurbineInputOperationValue2 < highToMediumPressureTurbinePowerOut) {
        std::cout << methodName
                  << "highToMediumTurbineInputOperationValue2=" << highToMediumTurbineInputOperationValue2
                  << " < highToMediumPressureTurbinePowerOut=" << highToMediumPressureTurbinePowerOut
                  << " not enough power out of turbine,"
                  << " calculating highToMediumPressureTurbine with amount needed instead of amount available"
                  << std::endl;
        //if power out with available mass flow is greater than max, calculate turbine with max power out
        highToMediumPressureTurbine =
                turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToMediumTurbineInput,
                                                   highToMediumTurbineInputOperationValue2, mediumPressureHeaderInput);
    }

    return {highToMediumPressureTurbine, highToLowPressureTurbineUpdated};
}

HighToMediumSteamTurbineCalculationsDomain
HighToMediumSteamTurbineCalculator::calcPowerGeneration(const double availableMassFlow,
                                                        const PressureTurbine &highToLowTurbineInput,
                                                        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                        const PressureTurbine &highToMediumTurbineInput,
                                                        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                        const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                        const Boiler &boiler) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::calcPowerGeneration: ";

    std::shared_ptr<Turbine> highToMediumPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double highToMediumTurbineInputOperationValue1 = highToMediumTurbineInput.getOperationValue1();

    std::cout << methodName
              << "calculating highToMediumPressureTurbine with power out (highToMediumTurbineInputOperationValue1)="
              << highToMediumTurbineInputOperationValue1 << std::endl;
    highToMediumPressureTurbine =
            turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToMediumTurbineInput,
                                               highToMediumTurbineInputOperationValue1, mediumPressureHeaderInput);

    //check that there is enough mass flow available to meet need for given power out
    const double highToMediumPressureTurbineMassFlow = highToMediumPressureTurbine->getMassFlow();
    if (highToMediumPressureTurbineMassFlow > availableMassFlow) {
        highToLowPressureTurbineUpdated =
                checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput, highToLowPressureTurbine,
                                  lowPressureHeaderInput, boiler, highToMediumPressureTurbine, availableMassFlow);
    }

    return {highToMediumPressureTurbine, highToLowPressureTurbineUpdated};
}

HighToMediumSteamTurbineCalculationsDomain
HighToMediumSteamTurbineCalculator::calcSteamFlow(const double availableMassFlow,
                                                  const PressureTurbine &highToLowTurbineInput,
                                                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                  const PressureTurbine &highToMediumTurbineInput,
                                                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                  const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                  const Boiler &boiler) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::calcPowerGeneration: ";

    std::shared_ptr<Turbine> highToMediumPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double highToMediumTurbineInputOperationValue1 = highToMediumTurbineInput.getOperationValue1();

    std::cout << methodName
              << "calculating highToMediumPressureTurbine with mass flow (highToMediumTurbineInputOperationValue1)="
              << highToMediumTurbineInputOperationValue1
              << std::endl;
    highToMediumPressureTurbine =
            turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToMediumTurbineInput,
                                               highToMediumTurbineInputOperationValue1, mediumPressureHeaderInput);
    //check enough mass flow exists for set mass flow
    const double highToMediumPressureTurbineMassFlow = highToMediumPressureTurbine->getMassFlow();
    if (highToMediumPressureTurbineMassFlow > availableMassFlow) {
        highToLowPressureTurbineUpdated =
                checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput, highToLowPressureTurbine,
                                  lowPressureHeaderInput, boiler, highToMediumPressureTurbine, availableMassFlow);
    }

    return {highToMediumPressureTurbine, highToLowPressureTurbineUpdated};
}

HighToMediumSteamTurbineCalculationsDomain
HighToMediumSteamTurbineCalculator::calcBalanceHeader(const double availableMassFlow,
                                                      const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                      const PressureTurbine &highToMediumTurbineInput,
                                                      const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                      const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::calcPowerGeneration: ";

    std::shared_ptr<Turbine> highToMediumPressureTurbine = nullptr;

    std::cout << methodName
              << "calculating highToMediumPressureTurbine with availableMassFlow=" << availableMassFlow << std::endl;
    highToMediumPressureTurbine =
            turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToMediumTurbineInput, availableMassFlow,
                                               mediumPressureHeaderInput);

    return {highToMediumPressureTurbine, highToLowPressureTurbine};
}

double
HighToMediumSteamTurbineCalculator::calcAvailableMassFlow(const HeaderWithHighestPressure &highPressureHeaderInput,
                                                          const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                          const CondensingTurbine &condensingTurbineInput,
                                                          const std::shared_ptr<Turbine> &condensingTurbine,
                                                          const PressureTurbine &highToLowTurbineInput,
                                                          const std::shared_ptr<Turbine> &highToLowPressureTurbine) const {
    double availableMassFlow = highPressureHeaderOutput.massFlow - highPressureHeaderInput.getProcessSteamUsage();

    //remove steam that goes through condensing turbine
    if (condensingTurbineInput.isUseTurbine()) {
        availableMassFlow -= condensingTurbine->getMassFlow();
    }

    //remove steam that goes through high to low turbine
    if (highToLowTurbineInput.isUseTurbine()) {
        availableMassFlow -= highToLowPressureTurbine->getMassFlow();
    }

    return availableMassFlow;
}

// TODO extract to SteamBalanceCheckerService?
std::shared_ptr<Turbine> HighToMediumSteamTurbineCalculator::checkSteamBalance(
        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
        const PressureTurbine &highToLowTurbineInput, const std::shared_ptr<Turbine> &highToLowPressureTurbine,
        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput, const Boiler &boiler,
        const std::shared_ptr<Turbine> &highToMediumPressureTurbine, const double availableMassFlow) const {
    const std::string methodName = "HighToMediumSteamTurbineCalculator::checkSteamBalance: ";

    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    //calculate additional steam needed to meet minimum requirement
    const double additionalSteamNeeded = highToMediumPressureTurbine->getMassFlow() - availableMassFlow;
    const double absAdditionalSteamNeeded = abs(additionalSteamNeeded);

    //if need more than .0001
    if (absAdditionalSteamNeeded > 1e-3) {
        std::cout << methodName
                  << "highToMediumPressureTurbine additionalSteamNeeded=" << additionalSteamNeeded << " > " << 1e-3
                  << "; attempting to take steam needed from high to low turbine" << std::endl;
        const SteamReducerOutput &steamReducerOutput =
                steamReducer.reduceSteamThroughHighToLowTurbine(additionalSteamNeeded, highToLowTurbineInput,
                                                                highToLowPressureTurbine, highPressureHeaderOutput,
                                                                lowPressureHeaderInput);
        const double remainingAdditionalSteamNeeded = steamReducerOutput.remainingAdditionalSteamNeeded;
        highToLowPressureTurbineUpdated = steamReducerOutput.highToLowPressureTurbineUpdated;

        restarter.restartIfNotEnoughSteam(remainingAdditionalSteamNeeded, boiler);
    }

    return highToLowPressureTurbineUpdated;
}
