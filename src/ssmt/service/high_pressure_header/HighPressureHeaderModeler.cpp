#include "ssmt/service/high_pressure_header/HighPressureHeaderModeler.h"

HighPressureHeaderCalculationsDomain
HighPressureHeaderModeler::model(const int headerCountInput, const HeaderWithHighestPressure &highPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput,
                                 const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput,
                                 const PressureTurbine &highToMediumTurbineInput,
                                 const PressureTurbine &highToLowTurbineInput,
                                 const CondensingTurbine &condensingTurbineInput, const Boiler &boiler) const {
    const std::string methodName = "HighPressureHeaderModeler::model: ";

    //2A. Calculate High Pressure Header
    std::cout << methodName << "calculating high pressure header" << std::endl;
    const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutputOriginal =
            highPressureHeaderCalculator.calc(highPressureHeaderInput, boiler);

    //2B. Calculate Heat Loss of steam in high pressure header
    std::cout << methodName << "calculating heat loss of steam in high pressure header" << std::endl;
    const SteamSystemModelerTool::FluidProperties &highPressureHeaderOutput =
            heatLossCalculator.updateHighPressureHeaderWithHeatLoss(highPressureHeaderInput,
                                                                    highPressureHeaderOutputOriginal);

    //2C. Calculate High Pressure Condensate
    std::cout << methodName << "calculating high pressure condensate" << std::endl;
    const SteamSystemModelerTool::FluidProperties &highPressureCondensate =
            highPressureCondensateCalculator.calc(highPressureHeaderInput, boiler);

    //2D. Calculate High Pressure Flash Tank if 3 header and on
    std::cout << methodName << "calculating high pressure flash tank" << std::endl;
    const std::shared_ptr<FlashTank> &highPressureCondensateFlashTank =
            highPressureFlashTankCalculator.calc(headerCountInput, mediumPressureHeaderInput, highPressureCondensate);

    //2E. Calculate condensing turbine
    std::cout << methodName << "calculating condensing turbine" << std::endl;
    const std::shared_ptr<Turbine> &condensingTurbine =
            condensingTurbineCalculator.calc(condensingTurbineInput, highPressureHeaderOutput);

    //2F. Calculate high to low steam turbine if in use
    std::cout << methodName << "calculating highToLowPressureTurbine" << std::endl;
    const std::shared_ptr<Turbine> &highToLowPressureTurbine =
            highToLowSteamTurbineCalculator.calc(headerCountInput, highToLowTurbineInput, highPressureHeaderOutput,
                                                 highPressureHeaderInput, condensingTurbineInput, condensingTurbine,
                                                 lowPressureHeaderInput, boiler);

    //2G. Calculate high to medium steam turbine if in use
    std::cout << methodName << "calculating high to medium steam turbine" << std::endl;
    const HighToMediumSteamTurbineCalculationsDomain &highToMediumSteamTurbineCalculationsDomain =
            highToMediumSteamTurbineCalculator.calc(headerCountInput, highPressureHeaderOutput, highPressureHeaderInput,
                                                    condensingTurbineInput, condensingTurbine, highToLowTurbineInput,
                                                    highToLowPressureTurbine, highToMediumTurbineInput,
                                                    mediumPressureHeaderInput, lowPressureHeaderInput, boiler);
    const std::shared_ptr<Turbine> &highToMediumPressureTurbine =
            highToMediumSteamTurbineCalculationsDomain.highToMediumPressureTurbine;
    const std::shared_ptr<Turbine> &highToLowPressureTurbineUpdated =
            highToMediumSteamTurbineCalculationsDomain.highToLowPressureTurbineUpdated;

    return {highPressureHeaderOutput, highPressureCondensate, highPressureCondensateFlashTank, condensingTurbine,
            highToMediumPressureTurbine, highToLowPressureTurbineUpdated};
}
