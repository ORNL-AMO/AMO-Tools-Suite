#include "ssmt/service/SteamReducer.h"

SteamReducerOutput
SteamReducer::reduceSteamThroughHighToLowTurbine(const double additionalSteamNeeded,
                                                 const PressureTurbine &highToLowTurbineInput,
                                                 const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                 const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
    const std::string methodName = "SteamReducer::reduceSteamThroughHighToLowTurbine: ";

    SteamReducerOutput steamReducerOutput;

    //if the turbine is in use
    if (highToLowTurbineInput.isUseTurbine()) {
        const PressureTurbineOperation &pressureTurbineOperation = highToLowTurbineInput.getOperationType();
        std::cout << methodName << "pressureTurbineOperation=" << pressureTurbineOperation << std::endl;

        switch (pressureTurbineOperation) {
            case PressureTurbineOperation::FLOW_RANGE:
                steamReducerOutput =
                        reduceFlowRange(additionalSteamNeeded, highToLowTurbineInput, highToLowPressureTurbine,
                                        highPressureHeaderOutput, lowPressureHeaderInput);
                break;
            case PressureTurbineOperation::POWER_RANGE:
                steamReducerOutput =
                        reducePowerRange(additionalSteamNeeded, highToLowTurbineInput, highToLowPressureTurbine,
                                         highPressureHeaderOutput, lowPressureHeaderInput);
                break;
            case PressureTurbineOperation::POWER_GENERATION:
                //fixed steam, cannot reduce steam through turbine
                break;
            case PressureTurbineOperation::STEAM_FLOW:
                //fixed steam, cannot reduce steam through turbine
                break;
            case PressureTurbineOperation::BALANCE_HEADER:
                steamReducerOutput =
                        reduceBalanceHeader(additionalSteamNeeded, highToLowTurbineInput, highToLowPressureTurbine,
                                            highPressureHeaderOutput, lowPressureHeaderInput);
                break;
            default:
                std::string msg = methodName + "PressureTurbineOperation enum not handled";
                std::cout << msg << std::endl;
                throw std::invalid_argument(msg);
        }
    } else {
        std::cout << methodName << "high to low turbine not provided, skipping reducing" << std::endl;
        steamReducerOutput = {additionalSteamNeeded, highToLowPressureTurbine};
    }

    std::cout << methodName
              << "remainingAdditionalSteamNeeded=" << steamReducerOutput.remainingAdditionalSteamNeeded << std::endl;

    return steamReducerOutput;
}

SteamReducerOutput
SteamReducer::reduceBalanceHeader(const double additionalSteamNeeded,
                                  const PressureTurbine &highToLowTurbineInput,
                                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
    const std::string methodName = "SteamReducer::reduceBalanceHeader: ";

    double remainingAdditionalSteamNeeded = additionalSteamNeeded;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    //balance header, all steam is available to be taken
    const double availableSteam = highToLowPressureTurbine->getMassFlow();
    const double remainingSteam = availableSteam - additionalSteamNeeded;

    double massFlow = remainingSteam;
    //if all steam can be taken,
    if (remainingSteam >= 0) {
        std::cout << methodName
                  << "calculating highToLowPressureTurbine with remainingSteam=" << remainingSteam << std::endl;
        //all additional steam needed was taken from turbine, no additional steam needed
        remainingAdditionalSteamNeeded = 0;
    } else {
        std::cout << methodName
                  << "calculating highToLowPressureTurbine with steam=0 (using all steam)" << std::endl;
        //take all steam from turbine
        massFlow = 0;
        //steam still needed = needed steam - amount taken
        remainingAdditionalSteamNeeded = additionalSteamNeeded - availableSteam;
    }

    highToLowPressureTurbineUpdated =
            turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput, massFlow,
                                               lowPressureHeaderInput);

    return {remainingAdditionalSteamNeeded, highToLowPressureTurbineUpdated};
}

SteamReducerOutput
SteamReducer::reducePowerRange(const double additionalSteamNeeded,
                               const PressureTurbine &highToLowTurbineInput,
                               const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                               const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                               const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
    const std::string methodName = "SteamReducer::reducePowerRange: ";

    double remainingAdditionalSteamNeeded = additionalSteamNeeded;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    //if current power out is greater than the minimum amount needed there is steam available
    const double highToLowPressureTurbinePowerOut = highToLowPressureTurbine->getPowerOut();
    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();

    if (highToLowPressureTurbinePowerOut > highToLowTurbineInputOperationValue1) {
        //calculate amount of steam taken when reducing power out to minimum
        const double previousMassFlow = highToLowPressureTurbine->getMassFlow();

        //calculate header using minimum power out needed
        std::cout << methodName
                  << "calculating highToLowPressureTurbine with minimum power out needed (highToLowTurbineInputOperationValue1)="
                  << highToLowTurbineInputOperationValue1 << std::endl;
        highToLowPressureTurbineUpdated =
                turbineFactory.makePtrWithPowerOut(highPressureHeaderOutput, highToLowTurbineInput,
                                                   highToLowTurbineInputOperationValue1,
                                                   lowPressureHeaderInput);

        //amount reduced = previous mass flow - mass flow at min need
        const double highToLowPressureTurbineMassFlow = highToLowPressureTurbineUpdated->getMassFlow();
        const double massFlowReduction = previousMassFlow - highToLowPressureTurbineMassFlow;

        //amount of steam take = needed steam - amount reduced
        const double newSteamNeed = additionalSteamNeeded - massFlowReduction;

        //if excess amount of steam was taken than needed when reducing, put excess steam taken back into turbine
        if (newSteamNeed < 0) {
            const double massFlow = highToLowPressureTurbineMassFlow + std::abs(newSteamNeed);
            std::cout << methodName
                      << "calculating highToLowPressureTurbine, returning excess steam amount, with mass flow="
                      << massFlow << std::endl;
            highToLowPressureTurbineUpdated =
                    turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                                       massFlow, lowPressureHeaderInput);
            remainingAdditionalSteamNeeded = 0;
        } else {
            //return new steam need
            remainingAdditionalSteamNeeded = newSteamNeed;
        }
    } else {
        //no steam available from turbine
        remainingAdditionalSteamNeeded = additionalSteamNeeded;
    }

    return {remainingAdditionalSteamNeeded, highToLowPressureTurbineUpdated};
}

SteamReducerOutput
SteamReducer::reduceFlowRange(const double additionalSteamNeeded,
                              const PressureTurbine &highToLowTurbineInput,
                              const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                              const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                              const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
    const std::string methodName = "SteamReducer::reduceFlowRange: ";

    double remainingAdditionalSteamNeeded = additionalSteamNeeded;
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    const double highToLowPressureTurbineMassFlow = highToLowPressureTurbine->getMassFlow();
    const double highToLowTurbineInputOperationValue1 = highToLowTurbineInput.getOperationValue1();

    //if current mass flow is greater than minimum needed
    if (highToLowPressureTurbineMassFlow > highToLowTurbineInputOperationValue1) {
        //calculate amount of steam that can be taken
        const double currentMassFlow = highToLowPressureTurbineMassFlow;

        //calculate turbine at minimum value
        std::cout << methodName
                  << "calculating highToLowPressureTurbine with amount needed (highToLowTurbineInputOperationValue1)="
                  << highToLowTurbineInputOperationValue1 << std::endl;
        highToLowPressureTurbineUpdated =
                turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                                   highToLowTurbineInputOperationValue1,
                                                   lowPressureHeaderInput);

        //calculate amount of mass flow reduced
        const double massFlowReduction = currentMassFlow - highToLowPressureTurbineUpdated->getMassFlow();

        //calculate new steam need
        double newSteamNeed = additionalSteamNeeded - massFlowReduction;

        //if more steam taken than needed when reducing, put excess steam taken back into turbine
        if (newSteamNeed < 0) {
            const double massFlow = highToLowPressureTurbineUpdated->getMassFlow() + std::abs(newSteamNeed);
            std::cout << methodName
                      << "calculating highToLowPressureTurbine, returning excess steam amount, with mass flow="
                      << massFlow << std::endl;
            highToLowPressureTurbineUpdated =
                    turbineFactory.makePtrWithMassFlow(highPressureHeaderOutput, highToLowTurbineInput,
                                                       massFlow, lowPressureHeaderInput);
            remainingAdditionalSteamNeeded = 0;
        } else {
            remainingAdditionalSteamNeeded = newSteamNeed;
        }
    }

    return {remainingAdditionalSteamNeeded, highToLowPressureTurbineUpdated};
}
