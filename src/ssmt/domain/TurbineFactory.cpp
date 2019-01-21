#include "ssmt/domain/TurbineFactory.h"

Turbine
TurbineFactory::make(const SteamSystemModelerTool::FluidProperties &headerProperties,
                     const Turbine::TurbineProperty &turbineProperty,
                     const PressureTurbine &highToLowTurbine, const double massFlowOrPowerOut,
                     const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const {
    Turbine::Solve solveFor = Turbine::Solve::OutletProperties;
    double inletPressure = headerProperties.pressure;
    SteamProperties::ThermodynamicQuantity inletQuantity = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double inletQuantityValue = headerProperties.specificEnthalpy;
    double isentropicEfficiency = highToLowTurbine.getIsentropicEfficiency();
    double generatorEfficiency = highToLowTurbine.getGenerationEfficiency();
    double outletSteamPressure = headerWithLowPressure->getPressure();

    return {solveFor, inletPressure, inletQuantity, inletQuantityValue, turbineProperty, isentropicEfficiency,
            generatorEfficiency, massFlowOrPowerOut, outletSteamPressure};
}

Turbine TurbineFactory::make(const SteamSystemModelerTool::FluidProperties &headerProperties,
                             const CondensingTurbine &condensingTurbine) const {
    const Turbine::Solve solveFor = Turbine::Solve::OutletProperties;
    const double inletPressure = headerProperties.pressure;
    const SteamProperties::ThermodynamicQuantity inletQuantity = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    const double inletQuantityValue = headerProperties.specificEnthalpy;

    const CondensingTurbineOperation operationType = condensingTurbine.getOperationType();
    const Turbine::TurbineProperty turbineProperty =
            convertCondensingTurbineOperationToTurbineProperty(operationType);

    const double isentropicEfficiency = condensingTurbine.getIsentropicEfficiency();
    const double generatorEfficiency = condensingTurbine.getGenerationEfficiency();
    const double massFlowOrPowerOut = condensingTurbine.getOperationValue();
    const double outletSteamPressure = condensingTurbine.getCondenserPressure();

    return {solveFor, inletPressure, inletQuantity, inletQuantityValue, turbineProperty, isentropicEfficiency,
            generatorEfficiency, massFlowOrPowerOut, outletSteamPressure};
}

Turbine TurbineFactory::make(const Header &mediumPressureHeader, const Turbine::TurbineProperty &turbineProperty,
                             const PressureTurbine &mediumToLowTurbineInput, const double massFlowOrPowerOut,
                             const std::shared_ptr<HeaderNotHighestPressure> &lowPressureHeaderInput) const {
    Turbine::Solve solveFor = Turbine::Solve::OutletProperties;

    // TODO these two from output or not?
//    const SteamSystemModelerTool::SteamPropertiesOutput &output = mediumPressureHeader->getHeaderProperties();
//    double inletPressure = output.pressure;
//    SteamProperties::ThermodynamicQuantity inletQuantity = SteamProperties::ThermodynamicQuantity::ENTHALPY;
//    double inletQuantityValue = output.specificEnthalpy;
    double inletPressure = mediumPressureHeader.getHeaderPressure();
    SteamProperties::ThermodynamicQuantity inletQuantity = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double inletQuantityValue = mediumPressureHeader.getSpecificEnthalpy();
    double isentropicEfficiency = mediumToLowTurbineInput.getIsentropicEfficiency();
    double generatorEfficiency = mediumToLowTurbineInput.getGenerationEfficiency();
    double outletSteamPressure = lowPressureHeaderInput->getPressure();

    return {solveFor, inletPressure, inletQuantity, inletQuantityValue, turbineProperty, isentropicEfficiency,
            generatorEfficiency, massFlowOrPowerOut, outletSteamPressure};
}

Turbine::TurbineProperty TurbineFactory::convertCondensingTurbineOperationToTurbineProperty(
        const CondensingTurbineOperation &operationType) const {
    Turbine::TurbineProperty turbineProperty;

    switch (operationType) {
        case CondensingTurbineOperation::POWER_GENERATION:
            turbineProperty = Turbine::TurbineProperty::PowerOut;
            break;
        case CondensingTurbineOperation::STEAM_FLOW:
            turbineProperty = Turbine::TurbineProperty::MassFlow;
            break;
        default:
            std::string msg = "TurbineFactory::convertCondensingTurbineOperationToTurbineProperty<<: operator enum not handled";
            std::cout << msg << std::endl;
            throw std::invalid_argument(msg);
    }

    return turbineProperty;
}

Turbine TurbineFactory::makeWithMassFlow(const SteamSystemModelerTool::FluidProperties &headerProperties,
                                         const PressureTurbine &pressureTurbine, const double massFlow,
                                         const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const {
    Turbine::Solve solveFor = Turbine::Solve::OutletProperties;
    double inletPressure = headerProperties.pressure;
    SteamProperties::ThermodynamicQuantity inletQuantity = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double inletQuantityValue = headerProperties.specificEnthalpy;
    const Turbine::TurbineProperty turbineProperty = Turbine::TurbineProperty::MassFlow;
    double isentropicEfficiency = pressureTurbine.getIsentropicEfficiency();
    double generatorEfficiency = pressureTurbine.getGenerationEfficiency();
    double outletSteamPressure = headerWithLowPressure->getPressure();

    return {solveFor, inletPressure, inletQuantity, inletQuantityValue, turbineProperty, isentropicEfficiency,
            generatorEfficiency, massFlow, outletSteamPressure};
}

Turbine TurbineFactory::makeWithPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                                         const PressureTurbine &pressureTurbine, const double powerOut,
                                         const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const {
    Turbine::Solve solveFor = Turbine::Solve::OutletProperties;
    double inletPressure = headerProperties.pressure;
    SteamProperties::ThermodynamicQuantity inletQuantity = SteamProperties::ThermodynamicQuantity::ENTHALPY;
    double inletQuantityValue = headerProperties.specificEnthalpy;
    const Turbine::TurbineProperty turbineProperty = Turbine::TurbineProperty::PowerOut;
    double isentropicEfficiency = pressureTurbine.getIsentropicEfficiency();
    double generatorEfficiency = pressureTurbine.getGenerationEfficiency();
    double outletSteamPressure = headerWithLowPressure->getPressure();

    return {solveFor, inletPressure, inletQuantity, inletQuantityValue, turbineProperty, isentropicEfficiency,
            generatorEfficiency, powerOut, outletSteamPressure};
}

std::shared_ptr<Turbine>
TurbineFactory::makePtrWithMassFlow(const SteamSystemModelerTool::FluidProperties &headerProperties,
                                    const PressureTurbine &pressureTurbine, double massFlow,
                                    const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const {
    const Turbine turbine = makeWithMassFlow(headerProperties, pressureTurbine, massFlow, headerWithLowPressure);
    return std::make_shared<Turbine>(turbine);
}

std::shared_ptr<Turbine>
TurbineFactory::makePtrWithPowerOut(const SteamSystemModelerTool::FluidProperties &headerProperties,
                                    const PressureTurbine &pressureTurbine, double massFlow,
                                    const std::shared_ptr<HeaderNotHighestPressure> &headerWithLowPressure) const {
    const Turbine turbine = makeWithPowerOut(headerProperties, pressureTurbine, massFlow, headerWithLowPressure);
    return std::make_shared<Turbine>(turbine);
}
