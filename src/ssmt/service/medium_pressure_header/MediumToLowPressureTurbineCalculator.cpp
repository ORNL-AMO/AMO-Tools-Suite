#include <ssmt/service/medium_pressure_header/MediumToLowPressureTurbineCalculator.h>

MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calc(const PressureTurbine &highToLowTurbineInput,
                                           const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                           const PressureTurbine &mediumToLowTurbineInput,
                                           const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                           const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                           const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                                           const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                           const Boiler &boiler) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::calc: ";

    MediumToLowPressureTurbineCalculatorOutput mediumToLowPressureTurbineCalculatorOutput;

    if (mediumToLowTurbineInput.isUseTurbine()) {
        std::cout << methodName
                  << "medium to low turbine input provided and mediumToLowTurbineInput isUseTurbine,"
                  << " calculating mediumToLowPressureTurbine" << std::endl;

        double availableMassFlow = calcAvailableMassFlow(mediumPressureHeaderInput, mediumPressureHeaderOutput);
        mediumToLowPressureTurbineCalculatorOutput =
                calc(availableMassFlow, highToLowTurbineInput, highToLowPressureTurbine, highPressureHeaderOutput,
                     mediumToLowTurbineInput, mediumPressureHeaderOutput, lowPressureHeaderInput, boiler);
    } else {
        std::cout << methodName
                  << "medium to low turbine input not provided and mediumToLowTurbineInput not isUseTurbine, skipping"
                  << std::endl;
    }

    return mediumToLowPressureTurbineCalculatorOutput;
}

MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calc(const double availableMassFlow,
                                           const PressureTurbine &highToLowTurbineInput,
                                           const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                           const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                           const PressureTurbine &mediumToLowTurbineInput,
                                           const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                                           const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                           const Boiler &boiler) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::calc: ";

    MediumToLowPressureTurbineCalculatorOutput mediumToLowPressureTurbineCalculatorOutput;

    const PressureTurbineOperation &pressureTurbineOperation = mediumToLowTurbineInput.getOperationType();
    std::cout << methodName << "pressureTurbineOperation=" << pressureTurbineOperation << std::endl;

    switch (pressureTurbineOperation) {
        case PressureTurbineOperation::FLOW_RANGE:
            mediumToLowPressureTurbineCalculatorOutput =
                    calcFlowRange(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                                  lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                                  highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::POWER_RANGE:
            mediumToLowPressureTurbineCalculatorOutput =
                    calcPowerRange(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                                   lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                                   highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::POWER_GENERATION:
            mediumToLowPressureTurbineCalculatorOutput =
                    calcPowerGeneration(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                                        lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                                        highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::STEAM_FLOW:
            mediumToLowPressureTurbineCalculatorOutput =
                    calcSteamFlow(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                                  lowPressureHeaderInput, boiler, highToLowTurbineInput, highToLowPressureTurbine,
                                  highPressureHeaderOutput);
            break;
        case PressureTurbineOperation::BALANCE_HEADER:
            mediumToLowPressureTurbineCalculatorOutput =
                    calcBalanceHeader(availableMassFlow, mediumToLowTurbineInput, mediumPressureHeaderOutput,
                                      lowPressureHeaderInput, highToLowPressureTurbine);
            break;
        default:
            std::string msg = methodName + "PressureTurbineOperation enum not handled";
            std::cout << msg << std::endl;
            throw std::invalid_argument(msg);
    }

    return mediumToLowPressureTurbineCalculatorOutput;
}

MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calcFlowRange(const double availableMassFlow,
                                                    const PressureTurbine &mediumToLowTurbineInput,
                                                    const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                                                    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                    const Boiler &boiler,
                                                    const PressureTurbine &highToLowTurbineInput,
                                                    const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                    const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::calcFlowRange: ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();
    const double mediumToLowTurbineInputOperationValue2 = mediumToLowTurbineInput.getOperationValue2();

    //if minimum amount needed is greater than available amount
    if (mediumToLowTurbineInputOperationValue1 > availableMassFlow) {
        std::cout << methodName
                  << "mediumToLowTurbineInputOperationValue1=" << mediumToLowTurbineInputOperationValue1
                  << " > availableMassFlow=" << availableMassFlow
                  << ", calculating mediumToLowPressureTurbine with amount needed (mediumToLowTurbineInputOperationValue1)"
                  << " instead of amount available" << std::endl;
        //calculate turbine with amount needed
        mediumToLowPressureTurbine =
                turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                                   mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput);
        highToLowPressureTurbineUpdated =
                checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput, highToLowPressureTurbine,
                                  lowPressureHeaderInput, boiler, mediumToLowPressureTurbine, availableMassFlow);
    } else if (mediumToLowTurbineInputOperationValue2 < availableMassFlow) {
        std::cout << methodName
                  << "mediumToLowTurbineInputOperationValue2=" << mediumToLowTurbineInputOperationValue2
                  << " < availableMassFlow=" << availableMassFlow
                  << ", calculating mediumToLowPressureTurbine with max amount allowed (mediumToLowTurbineInputOperationValue2)"
                  << " instead of the greater amount available" << std::endl;
        mediumToLowPressureTurbine =
                turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                                   mediumToLowTurbineInputOperationValue2, lowPressureHeaderInput);
    } else {
        std::cout << methodName
                  << "availableMassFlow=" << availableMassFlow << " is between needed and max amounts,"
                  << " calculating mediumToLowPressureTurbine with availableMassFlow" << std::endl;
        mediumToLowPressureTurbine =
                turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                                   availableMassFlow, lowPressureHeaderInput);
    }

    return {mediumToLowPressureTurbine, highToLowPressureTurbineUpdated};
}

MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calcPowerRange(const double availableMassFlow,
                                                     const PressureTurbine &mediumToLowTurbineInput,
                                                     const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                                                     const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                     const Boiler &boiler,
                                                     const PressureTurbine &highToLowTurbineInput,
                                                     const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                     const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::calcPowerRange: ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();
    const double mediumToLowTurbineInputOperationValue2 = mediumToLowTurbineInput.getOperationValue2();

    std::cout << methodName
              << "calculating mediumToLowPressureTurbine with availableMassFlow=" << availableMassFlow << std::endl;
    mediumToLowPressureTurbine =
            turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               availableMassFlow, lowPressureHeaderInput);
    //check that power out is in range
    const double mediumToLowPressureTurbinePowerOut = mediumToLowPressureTurbine->getPowerOut();
    if (mediumToLowTurbineInputOperationValue1 > mediumToLowPressureTurbinePowerOut) {
        std::cout << methodName
                  << "mediumToLowTurbineInputOperationValue1=" << mediumToLowTurbineInputOperationValue1
                  << " > mediumToLowPressureTurbinePowerOut=" << mediumToLowPressureTurbinePowerOut
                  << "; not enough power out of turbine,"
                  << " calculating mediumToLowPressureTurbine with amount needed instead of amount available"
                  << std::endl;
        double currentMassFlowAvailable = mediumToLowPressureTurbine->getMassFlow();
        //calculate minimum mass flow needed
        mediumToLowPressureTurbine =
                turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                                   mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput);
        highToLowPressureTurbineUpdated = checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput,
                                                            highToLowPressureTurbine, lowPressureHeaderInput, boiler,
                                                            mediumToLowPressureTurbine, currentMassFlowAvailable);
    } else if (mediumToLowTurbineInputOperationValue2 < mediumToLowPressureTurbinePowerOut) {
        std::cout << methodName
                  << "mediumToLowTurbineInputOperationValue2=" << mediumToLowTurbineInputOperationValue2
                  << " < mediumToLowPressureTurbinePowerOut=" << mediumToLowPressureTurbinePowerOut
                  << " not enough power out of turbine,"
                  << " calculating mediumToLowPressureTurbine with amount needed instead of amount available"
                  << std::endl;
        //if power out with available mass flow is greater than max, calculate turbine with max power out
        mediumToLowPressureTurbine =
                turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                                   mediumToLowTurbineInputOperationValue2, lowPressureHeaderInput);
    }

    return {mediumToLowPressureTurbine, highToLowPressureTurbineUpdated};
}

MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calcPowerGeneration(const double availableMassFlow,
                                                          const PressureTurbine &mediumToLowTurbineInput,
                                                          const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                                                          const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                          const Boiler &boiler,
                                                          const PressureTurbine &highToLowTurbineInput,
                                                          const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                          const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::calcPowerGeneration: ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();

    //calculate turbine with set amount of power out
    mediumToLowPressureTurbine =
            turbineFactory.makePtrWithPowerOut(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput);

    //check enough available steam for set power out
    const double mediumToLowPressureTurbineMassFlow = mediumToLowPressureTurbine->getMassFlow();
    if (mediumToLowPressureTurbineMassFlow > availableMassFlow) {
        highToLowPressureTurbineUpdated =
                checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput, highToLowPressureTurbine,
                                  lowPressureHeaderInput, boiler, mediumToLowPressureTurbine, availableMassFlow);
    }

    return {mediumToLowPressureTurbine, highToLowPressureTurbineUpdated};
}


MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calcSteamFlow(const double availableMassFlow,
                                                    const PressureTurbine &mediumToLowTurbineInput,
                                                    const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                                                    const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                    const Boiler &boiler,
                                                    const PressureTurbine &highToLowTurbineInput,
                                                    const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                    const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::calcSteamFlow: ";

    std::shared_ptr<Turbine> mediumToLowPressureTurbine = nullptr;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double mediumToLowTurbineInputOperationValue1 = mediumToLowTurbineInput.getOperationValue1();

    //calculate turbine with set mass flow
    mediumToLowPressureTurbine =
            turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               mediumToLowTurbineInputOperationValue1, lowPressureHeaderInput);

    //check enough available steam for set mass flow
    const double mediumToLowPressureTurbineMassFlow = mediumToLowPressureTurbine->getMassFlow();
    if (mediumToLowPressureTurbineMassFlow > availableMassFlow) {
        highToLowPressureTurbineUpdated =
                checkSteamBalance(highPressureHeaderOutput, highToLowTurbineInput, highToLowPressureTurbine,
                                  lowPressureHeaderInput, boiler, mediumToLowPressureTurbine, availableMassFlow);
    }

    return {mediumToLowPressureTurbine, highToLowPressureTurbineUpdated};
}

MediumToLowPressureTurbineCalculatorOutput
MediumToLowPressureTurbineCalculator::calcBalanceHeader(const double availableMassFlow,
                                                        const PressureTurbine &mediumToLowTurbineInput,
                                                        const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput,
                                                        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                        const std::shared_ptr<Turbine> &highToLowPressureTurbine) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::calcBalanceHeader: ";

    //balance header send through what is available
    std::shared_ptr<Turbine> mediumToLowPressureTurbine =
            turbineFactory.makePtrWithMassFlow(mediumPressureHeaderOutput, mediumToLowTurbineInput,
                                               availableMassFlow, lowPressureHeaderInput);

    return {mediumToLowPressureTurbine, highToLowPressureTurbine};
}

double MediumToLowPressureTurbineCalculator::calcAvailableMassFlow(
        const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
        const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput) const {
    return mediumPressureHeaderOutput.massFlow - mediumPressureHeaderInput->getProcessSteamUsage();
}

// TODO extract to SteamBalanceCheckerService?
// TODO can share with MediumPressureHeaderCalculator::checkSteamBalance
std::shared_ptr<Turbine>
MediumToLowPressureTurbineCalculator::checkSteamBalance(
        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
        const PressureTurbine &highToLowTurbineInput,
        const std::shared_ptr<Turbine> &highToLowPressureTurbine,
        const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
        const Boiler &boiler,
        const std::shared_ptr<Turbine> &mediumToLowPressureTurbine,
        const double availableMassFlow) const {
    const std::string methodName = "MediumToLowPressureTurbineCalculator::checkSteamBalance: ";
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    //calculate additional steam need
    const double additionalSteamNeeded = mediumToLowPressureTurbine->getMassFlow() - availableMassFlow;
    const double absAdditionalSteamNeeded = std::abs(additionalSteamNeeded);

    //if need more than .0001
    if (absAdditionalSteamNeeded > 1e-3) {
        std::cout << methodName
                  << "mediumToLowPressureTurbine additionalSteamNeeded=" << additionalSteamNeeded << " > " << 1e-3
                  << "; attempting to take steam needed from medium to low turbine" << std::endl;
        const SteamReducerOutput &steamReducerOutput =
                steamReducer.reduceSteamThroughHighToLowTurbine(additionalSteamNeeded, highToLowTurbineInput,
                                                                highToLowPressureTurbine, highPressureHeaderOutput,
                                                                lowPressureHeaderInput);
        const double remainingAdditionalSteamNeeded = steamReducerOutput.remainingAdditionalSteamNeeded;
        highToLowPressureTurbineUpdated = steamReducerOutput.highToLowPressureTurbineUpdated;

        //TODO implement this optimization to partially restart when possible vs full restart
//      if (newSteamNeed < neededSteam) {
//        //restart from 2G
//        if (this.inputData.turbineInput.highToMediumTurbine.useTurbine == true) {
//          this.calculateHighToMediumPressureSteamTurbine();
//        }
//        //3A. Calculate High to Medium PRV
//        this.calculateHighToMediumPRV();
//        //3B. Model Medium Pressure Header
//        this.calculateMediumPressureHeader();
//        //3C. Calculate Heat Loss for Remain Steam in Medium Pressure Header
//        this.calculateHeatLossForMediumPressureHeader();
//        //3D. Calculate Medium Pressure Condensate
//        this.calculateMediumPressureCondensate();
//        //3E. Calculate medium to low steam turbine if in use
//        this.calculateMediumToLowSteamTurbine();
//      } else {
//        //if cant reduce high to medium
//        //re-calculate model with additional needed steam added
        restarter.restartIfNotEnoughSteam(remainingAdditionalSteamNeeded, boiler);
//      }
    }

    return highToLowPressureTurbineUpdated;
}
