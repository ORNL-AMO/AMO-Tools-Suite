#include "ssmt/domain/HeatLossFactory.h"

const HeatLoss HeatLossFactory::make(const HeaderWithHighestPressure &highestPressureHeaderInput,
                                     const SteamSystemModelerTool::FluidProperties &headerOutput) const {
    double inletPressure = headerOutput.pressure;
    SteamProperties::ThermodynamicQuantity quantityType = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double quantityValue = headerOutput.specificEnthalpy;
    double inletMassFlow = headerOutput.massFlow;
    double percentHeatLoss = highestPressureHeaderInput.getHeatLoss();

    return {inletPressure, quantityType, quantityValue, inletMassFlow, percentHeatLoss};
}

const HeatLoss HeatLossFactory::make(const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput,
                                     const SteamSystemModelerTool::FluidProperties &headerOutput) const {
    double inletPressure = headerOutput.pressure;
    SteamProperties::ThermodynamicQuantity quantityType = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double quantityValue = headerOutput.specificEnthalpy;
    double inletMassFlow = headerOutput.massFlow;
    double percentHeatLoss = notHighestPressureHeaderInput->getHeatLoss();

    return {inletPressure, quantityType, quantityValue, inletMassFlow, percentHeatLoss};
}
