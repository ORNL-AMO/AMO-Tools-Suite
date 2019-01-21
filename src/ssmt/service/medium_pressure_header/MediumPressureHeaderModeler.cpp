#include "ssmt/service/medium_pressure_header/MediumPressureHeaderModeler.h"

std::shared_ptr<MediumPressureHeaderCalculationsDomain>
MediumPressureHeaderModeler::model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                                   const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                   const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                   const PressureTurbine &highToMediumTurbineInput,
                                   const PressureTurbine &highToLowTurbineInput,
                                   const PressureTurbine &mediumToLowTurbineInput,
                                   const CondensingTurbine &condensingTurbineInput,
                                   const Boiler &boiler,
                                   const HighPressureHeaderCalculationsDomain &highPressureHeaderCalculationsDomain) const {
    const std::string methodName = "MediumPressureHeaderModeler::model: ";

    //if medium pressure header exists
    if (headerCountInput == 3) {
        std::cout << methodName << "medium pressure header provided, processing" << std::endl;

        //TODO move these/trace ptrs for NPE elim, into highToMediumPrvCalculator.calc and mediumPressureHeaderCalculator.calc
        const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput =
                highPressureHeaderCalculationsDomain.highPressureHeaderOutput;
        const SteamSystemModelerTool::FluidProperties &highPressureCondensate =
                highPressureHeaderCalculationsDomain.highPressureCondensate;
        const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank =
                highPressureHeaderCalculationsDomain.highPressureCondensateFlashTank;
        const std::shared_ptr<Turbine> &condensingTurbine =
                highPressureHeaderCalculationsDomain.condensingTurbine;
        const std::shared_ptr<Turbine> &highToMediumPressureTurbine =
                highPressureHeaderCalculationsDomain.highToMediumPressureTurbine;
        const std::shared_ptr<Turbine> &highToLowPressureTurbine =
                highPressureHeaderCalculationsDomain.highToLowPressureTurbine;

        //3A. Calculate High to Medium PRV
        std::cout << methodName << "calculating high to medium pressure PRV" << std::endl;
        const std::shared_ptr<PrvWithoutDesuperheating> &highToMediumPressurePrv =
                highToMediumPrvCalculator.calc(mediumPressureHeaderInput, highPressureHeaderOutput,
                                               highPressureCondensate, highPressureHeaderInput, highToLowTurbineInput,
                                               highToMediumTurbineInput, condensingTurbineInput,
                                               highToLowPressureTurbine, highToMediumPressureTurbine,
                                               condensingTurbine);

        //3B. Model Medium Pressure Header
        //3B1. Calculate inlets for medium pressure header
        std::cout << methodName << "calculating medium pressure header" << std::endl;
        const MediumPressureHeaderCalculatorOutput &mediumPressureHeaderCalculatorOutput =
                mediumPressureHeaderCalculator.calc(boiler, highToLowTurbineInput, highToLowPressureTurbine,
                                                    highPressureHeaderOutput, mediumPressureHeaderInput,
                                                    highToMediumPressurePrv, highToMediumTurbineInput,
                                                    highToMediumPressureTurbine, highPressureCondensateFlashTank,
                                                    lowPressureHeaderInput);
        const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutputOriginal =
                mediumPressureHeaderCalculatorOutput.mediumPressureHeaderOutput;

        //3C. Calculate Heat Loss for Remaining Steam in Medium Pressure Header
        std::cout << methodName << "calculating heat loss" << std::endl;
        const SteamSystemModelerTool::FluidProperties &heatLossOutletProperties =
                mediumPressureHeatLossCalculator.calc(mediumPressureHeaderInput, mediumPressureHeaderOutputOriginal);
        const SteamSystemModelerTool::FluidProperties &mediumPressureHeaderOutputUpdated =
                fluidPropertiesFactory.makeWithSpecificVolume(heatLossOutletProperties,
                                                              mediumPressureHeaderOutputOriginal.specificVolume);

        //3D. Calculate Medium Pressure Condensate
        std::cout << methodName << "calculating medium pressure condensate" << std::endl;
        const SteamSystemModelerTool::FluidProperties &mediumPressureCondensate =
                mediumPressureCondensateCalculator.calc(mediumPressureHeaderInput);

        //3E. Calculate medium to low steam turbine if in use
        std::cout << methodName << "calculating medium to low pressure turbine" << std::endl;
        const MediumToLowPressureTurbineCalculatorOutput mediumToLowPressureTurbineCalculatorOutput =
                mediumToLowPressureTurbineCalculator.calc(highToLowTurbineInput, highToLowPressureTurbine,
                                                          mediumToLowTurbineInput, highPressureHeaderOutput,
                                                          mediumPressureHeaderInput, mediumPressureHeaderOutputUpdated,
                                                          lowPressureHeaderInput, boiler);
        const std::shared_ptr<Turbine> &mediumToLowPressureTurbine =
                mediumToLowPressureTurbineCalculatorOutput.mediumToLowPressureTurbine;
        const std::shared_ptr<Turbine> &highToLowPressureTurbineUpdated =
                mediumToLowPressureTurbineCalculatorOutput.highToLowPressureTurbineUpdated;

        const MediumPressureHeaderCalculationsDomain &domain =
                {highToMediumPressurePrv, highPressureCondensateFlashTank, mediumPressureHeaderOutputUpdated,
                 heatLossOutletProperties, mediumPressureCondensate, mediumToLowPressureTurbine,
                 highToLowPressureTurbineUpdated};
        return std::make_shared<MediumPressureHeaderCalculationsDomain>(domain);
    } else {
        std::cout << methodName << "medium pressure header not provided, skipping" << std::endl;
        return nullptr;
    }
}
