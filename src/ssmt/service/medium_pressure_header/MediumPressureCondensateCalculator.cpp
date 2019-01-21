#include <ssmt/service/medium_pressure_header/MediumPressureCondensateCalculator.h>

const SteamSystemModelerTool::FluidProperties
MediumPressureCondensateCalculator::calc(
        const std::shared_ptr<HeaderNotHighestPressure> &mediumPressureHeaderInput) const {
    std::cout << "MediumPressureCondensateCalculator::calc" << "calculating mediumPressureCondensate" << std::endl;

    const double pressure = mediumPressureHeaderInput->getPressure();
    const SteamProperties::ThermodynamicQuantity quantity = SteamProperties::ThermodynamicQuantity::QUALITY;
    const double quantityValue = 0;
    const SteamSystemModelerTool::SteamPropertiesOutput &steamPropertiesOutput =
            SteamProperties(pressure, quantity, quantityValue).calculate();

    const double massFlow = massFlowCalculator.calc(mediumPressureHeaderInput);
    const double energyFlow = energyFlowCalculator.calc(massFlow, steamPropertiesOutput);

    return SteamSystemModelerTool::FluidProperties(massFlow, energyFlow, steamPropertiesOutput);
}
