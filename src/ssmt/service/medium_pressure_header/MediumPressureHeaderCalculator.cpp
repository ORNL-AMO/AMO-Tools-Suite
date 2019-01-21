#include <ssmt/service/medium_pressure_header/MediumPressureHeaderCalculator.h>

MediumPressureHeaderCalculatorOutput
MediumPressureHeaderCalculator::calc(const Boiler &boiler, const PressureTurbine &highToLowTurbineInput,
                                     const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                     const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                     const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                     const std::shared_ptr<PrvWithoutDesuperheating> &highToMediumPressurePrv,
                                     const PressureTurbine &highToMediumTurbineInput,
                                     const std::shared_ptr<Turbine> &highToMediumPressureTurbine,
                                     const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank,
                                     const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
    const std::string methodName = "MediumPressureHeaderCalculator::calc: ";

    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    std::cout << methodName << "calculating mediumPressureHeaderOutput" << std::endl;
    //3B1 & 3B2. Calculate medium pressure header
    const Header mediumPressureHeader =
            headerFactory.make(mediumPressureHeaderInput, highToMediumPressurePrv, highToMediumTurbineInput,
                               highToMediumPressureTurbine, highPressureCondensateFlashTank);
    const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutput =
            fluidPropertiesFactory.make(mediumPressureHeader);

    //3B3. Check that medium pressure header has enough steam to be processed
    const double mediumPressureHeaderMassFlow = mediumPressureHeader.getInletMassFlow();
    const double mediumPressureHeaderInputProcessSteamUsage = mediumPressureHeaderInput->getProcessSteamUsage();

    if (mediumPressureHeaderMassFlow < mediumPressureHeaderInputProcessSteamUsage) {
        highToLowPressureTurbineUpdated =
                checkSteamBalance(boiler, highToLowTurbineInput, highToLowPressureTurbine, highPressureHeaderOutput,
                                  lowPressureHeaderInput, mediumPressureHeaderMassFlow,
                                  mediumPressureHeaderInputProcessSteamUsage);
    }

    return {mediumPressureHeaderOutput, highToLowPressureTurbineUpdated};
}

// TODO extract to SteamBalanceCheckerService?
// TODO can share with MediumToLowPressureTurbineCalculator::checkSteamBalance
std::shared_ptr<Turbine>
MediumPressureHeaderCalculator::checkSteamBalance(const Boiler &boiler, const PressureTurbine &highToLowTurbineInput,
                                                  const std::shared_ptr<Turbine> &highToLowPressureTurbine,
                                                  const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput,
                                                  const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                                  const double mediumPressureHeaderMassFlow,
                                                  const double mediumPressureHeaderInputProcessSteamUsage) const {
    const std::string methodName = "MediumPressureHeaderCalculator::checkSteamBalance: ";
    std::shared_ptr<Turbine> highToLowPressureTurbineUpdated = highToLowPressureTurbine;

    //calculate additional steam needed to meet minimum requirement
    const double additionalSteamNeeded = mediumPressureHeaderInputProcessSteamUsage - mediumPressureHeaderMassFlow;
    const double absAdditionalSteamNeeded = std::abs(additionalSteamNeeded);

    //if need more than .0001
    if (absAdditionalSteamNeeded > 1e-3) {
        std::cout << methodName
                  << "mediumPressureHeader additionalSteamNeeded=" << additionalSteamNeeded << " > " << 1e-3
                  << "; attempting to take steam needed from medium to low turbine" << std::endl;
        const SteamReducerOutput &steamReducerOutput =
                steamReducer.reduceSteamThroughHighToLowTurbine(additionalSteamNeeded, highToLowTurbineInput,
                                                                highToLowPressureTurbine, highPressureHeaderOutput,
                                                                lowPressureHeaderInput);
        const double remainingAdditionalSteamNeeded = steamReducerOutput.remainingAdditionalSteamNeeded;
        highToLowPressureTurbineUpdated = steamReducerOutput.highToLowPressureTurbineUpdated;

        //TODO implement this optimization to partially restart when possible vs full restart
//      //if high to low turbine was reduced and more steam is available
//      if (remainingAdditionalSteamNeeded < additionalSteamNeed) {
//        //restart calculation process from step: 2G
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
//        if (this.inputData.turbineInput.mediumToLowTurbine.useTurbine == true) {
//          //3E. Calculate medium to low steam turbine if in use
//          this.calculateMediumToLowSteamTurbine();
//        }
//        //3B. Redo this step.
//        this.calculateMediumPressureHeader();
//      } else {
        restarter.restartIfNotEnoughSteam(remainingAdditionalSteamNeeded, boiler);
//      }
    }

    return highToLowPressureTurbineUpdated;
}
