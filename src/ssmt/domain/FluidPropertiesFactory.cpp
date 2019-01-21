#include <ssmt/domain/FluidPropertiesFactory.h>

SteamSystemModelerTool::FluidProperties FluidPropertiesFactory::make(const Header &header) const {
    const SteamSystemModelerTool::SteamPropertiesOutput &headerSteamProperties = header.getHeaderProperties();
    const double massFlow = header.getInletMassFlow();
    const double energyFlow = header.getInletEnergyFlow();

    return {massFlow, energyFlow, headerSteamProperties};
}

SteamSystemModelerTool::FluidProperties
FluidPropertiesFactory::make(const SteamSystemModelerTool::FluidProperties &properties) const {
    const double massFlow = properties.massFlow;
    const double energyFlow = properties.energyFlow;
    const double temperature = properties.temperature;
    const double pressure = properties.pressure;
    const double quality = properties.quality;
    const double specificVolume = properties.specificVolume;
    const double density = properties.density;
    const double specificEnthalpy = properties.specificEnthalpy;
    const double specificEntropy = properties.specificEntropy;

    return {massFlow, energyFlow, temperature, pressure, quality, specificVolume, density, specificEnthalpy,
            specificEntropy,};
}

SteamSystemModelerTool::FluidProperties FluidPropertiesFactory::make(const HeatLoss &heatLoss) const {
    const SteamSystemModelerTool::FluidProperties &outletProperties = heatLoss.getOutletProperties();

    return make(outletProperties);
}

SteamSystemModelerTool::FluidProperties
FluidPropertiesFactory::makeWithSpecificVolume(
        const SteamSystemModelerTool::FluidProperties &lowPressureSteamHeatLossOutput,
        const double specificVolume) const {
    SteamSystemModelerTool::FluidProperties properties = make(lowPressureSteamHeatLossOutput);
    properties.specificVolume = specificVolume;
    return properties;
}

SteamSystemModelerTool::FluidProperties
FluidPropertiesFactory::makeWithMassFlow(const SteamSystemModelerTool::FluidProperties &lowPressureHeaderOutput,
                                         const double massFlow) const {
    SteamSystemModelerTool::FluidProperties properties = make(lowPressureHeaderOutput);
    properties.massFlow = massFlow;
    return properties;
}

SteamSystemModelerTool::FluidProperties
FluidPropertiesFactory::makeWithVentedSteamAmount(const SteamSystemModelerTool::FluidProperties &makeupWater,
                                                  const double ventedSteamAmount) const {
    SteamSystemModelerTool::FluidProperties properties = make(makeupWater);
    properties.massFlow += ventedSteamAmount;
    properties.energyFlow = calcEnergyFlow(properties.massFlow, properties);
    return properties;
}

SteamSystemModelerTool::FluidProperties FluidPropertiesFactory::makeFromBlowdown(const Boiler &boiler) const {
    const SteamSystemModelerTool::FluidProperties &blowdownProperties = boiler.getBlowdownProperties();

    return make(blowdownProperties);
}

SteamSystemModelerTool::FluidProperties
FluidPropertiesFactory::makeFromBlowdown(const Boiler &boiler, const double massFlow, const double energyFlow) const {
    SteamSystemModelerTool::FluidProperties fluidProperties = makeFromBlowdown(boiler);
    fluidProperties.massFlow = massFlow;
    fluidProperties.energyFlow = energyFlow;

    return fluidProperties;
}

SteamSystemModelerTool::FluidProperties
FluidPropertiesFactory::make(const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput) const {
    const double massFlow = calcHeaderMassFlow(notHighestPressureHeaderInput);
    const SteamSystemModelerTool::SteamPropertiesOutput steamPropertiesOutput =
            calcLowPressureCondensateSteamOutput(notHighestPressureHeaderInput);
    const double energyFlow = calcEnergyFlow(massFlow, steamPropertiesOutput);
    return {massFlow, energyFlow, steamPropertiesOutput};
}

double
FluidPropertiesFactory::calcHeaderMassFlow(
        const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput) const {
    const double processSteamUsage = notHighestPressureHeaderInput->getProcessSteamUsage();
    const double condensationRecoveryRate = notHighestPressureHeaderInput->getCondensationRecoveryRate();
    return processSteamUsage * (condensationRecoveryRate / 100);
}

SteamSystemModelerTool::SteamPropertiesOutput FluidPropertiesFactory::calcLowPressureCondensateSteamOutput(
        const std::shared_ptr<HeaderNotHighestPressure> &notHighestPressureHeaderInput) const {
    const double pressure = notHighestPressureHeaderInput->getPressure();
    const SteamProperties::ThermodynamicQuantity quantity = SteamProperties::ThermodynamicQuantity::QUALITY;
    const double quantityValue = 0;
    SteamProperties lowPressureCondensateSteam = {pressure, quantity, quantityValue};
    return lowPressureCondensateSteam.calculate();
}

double FluidPropertiesFactory::calcEnergyFlow(double massFlow,
                                              const SteamSystemModelerTool::SteamPropertiesOutput &steamPropertiesOutput) const {
    const double specificEnthalpy = steamPropertiesOutput.specificEnthalpy;
    return massFlow * specificEnthalpy / 1000;
}

SteamSystemModelerTool::FluidProperties
FluidPropertiesFactory::make(const HeaderWithHighestPressure &highPressureHeaderInput,
                             const Header &combinedCondensateHeader) const {
    const double pressure = combinedCondensateHeader.getHeaderPressure();
    const SteamProperties::ThermodynamicQuantity quantity = SteamProperties::ThermodynamicQuantity::TEMPERATURE;
    const double quantityValue = highPressureHeaderInput.getCondensateReturnTemperature();
    SteamProperties returnCondensate = {pressure, quantity, quantityValue};

    const double massFlow = combinedCondensateHeader.getInletMassFlow();

    const SteamSystemModelerTool::SteamPropertiesOutput &steamPropertiesOutput = returnCondensate.calculate();
    const double energyFlow = calcEnergyFlow(massFlow, steamPropertiesOutput);

    return {massFlow, energyFlow, steamPropertiesOutput};
}
