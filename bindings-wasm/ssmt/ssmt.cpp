#include "ssmt/SaturatedProperties.h"
#include "ssmt/SteamSystemModelerTool.h"
#include "ssmt/SteamProperties.h"
#include "ssmt/HeatLoss.h"
#include "ssmt/Boiler.h"
#include "ssmt/HeatLoss.h"
#include "ssmt/FlashTank.h"
#include "ssmt/PRV.h"
#include "ssmt/Deaerator.h"
#include "ssmt/Header.h"
#include "ssmt/Turbine.h"
#include "ssmt/HeatExchanger.h"
#include "ssmt/api/SteamModeler.h"
#include <vector>
#include <emscripten/bind.h>
using namespace emscripten;

//steamModelerTool
EMSCRIPTEN_BINDINGS(steamModelerTool)
{
    class_<SteamSystemModelerTool::SaturatedPropertiesOutput>("SaturatedPropertiesOutput")
        .property("saturatedPressure", &SteamSystemModelerTool::SaturatedPropertiesOutput::pressure)
        .property("saturatedTemperature", &SteamSystemModelerTool::SaturatedPropertiesOutput::temperature)
        .property("liquidEnthalpy", &SteamSystemModelerTool::SaturatedPropertiesOutput::liquidSpecificEnthalpy)
        .property("gasEnthalpy", &SteamSystemModelerTool::SaturatedPropertiesOutput::gasSpecificEnthalpy)
        .property("evaporationEnthalpy", &SteamSystemModelerTool::SaturatedPropertiesOutput::evaporationSpecificEnthalpy)
        .property("liquidEntropy", &SteamSystemModelerTool::SaturatedPropertiesOutput::liquidSpecificEntropy)
        .property("gasEntropy", &SteamSystemModelerTool::SaturatedPropertiesOutput::gasSpecificEntropy)
        .property("evaporationEntropy", &SteamSystemModelerTool::SaturatedPropertiesOutput::evaporationSpecificEntropy)
        .property("liquidVolume", &SteamSystemModelerTool::SaturatedPropertiesOutput::liquidSpecificVolume)
        .property("gasVolume", &SteamSystemModelerTool::SaturatedPropertiesOutput::gasSpecificVolume)
        .property("evaporationVolume", &SteamSystemModelerTool::SaturatedPropertiesOutput::evaporationSpecificVolume);

    class_<SteamSystemModelerTool::SteamPropertiesOutput>("SteamPropertiesOutput")
        .constructor<double, double, double, double, double, double, double, double>()
        .property("temperature", &SteamSystemModelerTool::SteamPropertiesOutput::temperature)
        .property("pressure", &SteamSystemModelerTool::SteamPropertiesOutput::pressure)
        .property("quality", &SteamSystemModelerTool::SteamPropertiesOutput::quality)
        .property("specificVolume", &SteamSystemModelerTool::SteamPropertiesOutput::specificVolume)
        .property("density", &SteamSystemModelerTool::SteamPropertiesOutput::density)
        .property("specificEnthalpy", &SteamSystemModelerTool::SteamPropertiesOutput::specificEnthalpy)
        .property("specificEntropy", &SteamSystemModelerTool::SteamPropertiesOutput::specificEntropy)
        .property("internalEnergy", &SteamSystemModelerTool::SteamPropertiesOutput::internalEnergy);

    class_<SteamSystemModelerTool::FluidProperties, emscripten::base<SteamSystemModelerTool::SteamPropertiesOutput>>("FluidProperties")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .smart_ptr<std::shared_ptr<SteamSystemModelerTool::FluidProperties>>("FluidProperties")
        .property("massFlow", &SteamSystemModelerTool::FluidProperties::massFlow)
        .property("energyFlow", &SteamSystemModelerTool::FluidProperties::energyFlow);
}

// saturatedPressure
EMSCRIPTEN_BINDINGS(saturatedPressure)
{
    class_<SaturatedPressure>("SaturatedPressure")
        .constructor<double>()
        .function("calculate", &SaturatedPressure::calculate);
}
// saturatedTemperature
EMSCRIPTEN_BINDINGS(saturatedTemperature)
{
    class_<SaturatedTemperature>("SaturatedTemperature")
        .constructor<double>()
        .function("calculate", &SaturatedTemperature::calculate);
}
// saturatedPropertiesGivenTemperature
// saturatedPropertiesGivenPressure
//(SaturatedProperties)
EMSCRIPTEN_BINDINGS(saturatedProperties)
{
    class_<SaturatedProperties>("SaturatedProperties")
        .constructor<double, double>()
        .function("calculate", &SaturatedProperties::calculate);
}

// steamProperties
EMSCRIPTEN_BINDINGS(steamProperties)
{
    class_<SteamProperties>("SteamProperties")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double>()
        .function("calculate", &SteamProperties::calculate);
}
// boiler
EMSCRIPTEN_BINDINGS(boiler)
{
    class_<Boiler>("Boiler")
        .constructor<double, double, double, double, SteamProperties::ThermodynamicQuantity, double, double>()
        .function("getSteamProperties", &Boiler::getSteamProperties)
        .function("getBlowdownProperties", &Boiler::getBlowdownProperties)
        .function("getFeedwaterProperties", &Boiler::getFeedwaterProperties)
        .function("getBoilerEnergy", &Boiler::getBoilerEnergy)
        .function("getFuelEnergy", &Boiler::getFuelEnergy)
        .function("getBlowdownRate", &Boiler::getBlowdownRate)
        .function("getCombustionEfficiency", &Boiler::getCombustionEfficiency);
}
// heatLoss
EMSCRIPTEN_BINDINGS(heatLoss)
{
    class_<HeatLoss>("HeatLoss")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double>()
        .function("getInletProperties", &HeatLoss::getInletProperties)
        .function("getOutletProperties", &HeatLoss::getOutletProperties)
        .function("getHeatLoss", &HeatLoss::getHeatLoss)
        .function("getInletPressure", &HeatLoss::getInletPressure)
        .function("getQuantityValue", &HeatLoss::getQuantityValue)
        .function("getInletMassFlow", &HeatLoss::getInletMassFlow)
        .function("getPercentHeatLoss", &HeatLoss::getPercentHeatLoss)
        .function("getQuantityType", &HeatLoss::getQuantityType);
}
// flashTank
EMSCRIPTEN_BINDINGS(flashTank)
{
    class_<FlashTank>("FlashTank")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double>()
        .smart_ptr<std::shared_ptr<FlashTank>>("FlashTank")
        .function("getInletWaterProperties", &FlashTank::getInletWaterProperties)
        .function("getOutletGasSaturatedProperties", &FlashTank::getOutletGasSaturatedProperties)
        .function("getOutletLiquidSaturatedProperties", &FlashTank::getOutletLiquidSaturatedProperties);
}
// prvWithoutDesuperheating
EMSCRIPTEN_BINDINGS(prvWithoutDesuperheating)
{
    class_<PrvWithoutDesuperheating>("PrvWithoutDesuperheating")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double>()
        .smart_ptr<std::shared_ptr<PrvWithoutDesuperheating>>("PrvWithoutDesuperheating")
        .function("getInletProperties", &PrvWithoutDesuperheating::getInletProperties)
        .function("getOutletProperties", &PrvWithoutDesuperheating::getOutletProperties)
        .function("getInletMassFlow", &PrvWithoutDesuperheating::getInletMassFlow)
        .function("getInletEnergyFlow", &PrvWithoutDesuperheating::getInletEnergyFlow)
        .function("getOutletMassFlow", &PrvWithoutDesuperheating::getOutletMassFlow)
        .function("getOutletEnergyFlow", &PrvWithoutDesuperheating::getOutletEnergyFlow)
        .function("isWithDesuperheating", &PrvWithoutDesuperheating::isWithDesuperheating);
}
// prvWithDesuperheating
EMSCRIPTEN_BINDINGS(prvWithDesuperheating)
{
    class_<PrvWithDesuperheating>("PrvWithDesuperheating")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double, double, SteamProperties::ThermodynamicQuantity, double, double>()
        .smart_ptr<std::shared_ptr<PrvWithDesuperheating>>("PrvWithDesuperheating")
        .function("getInletProperties", &PrvWithDesuperheating::getInletProperties)
        .function("getOutletProperties", &PrvWithDesuperheating::getOutletProperties)
        .function("getInletMassFlow", &PrvWithDesuperheating::getInletMassFlow)
        .function("getInletEnergyFlow", &PrvWithDesuperheating::getInletEnergyFlow)
        .function("getOutletMassFlow", &PrvWithDesuperheating::getOutletMassFlow)
        .function("getOutletEnergyFlow", &PrvWithDesuperheating::getOutletEnergyFlow)
        .function("getFeedwaterProperties", &PrvWithDesuperheating::getFeedwaterProperties)
        .function("getFeedwaterMassFlow", &PrvWithDesuperheating::getFeedwaterMassFlow)
        .function("getFeedwaterEnergyFlow", &PrvWithDesuperheating::getFeedwaterEnergyFlow)
        .function("isWithDesuperheating", &PrvWithDesuperheating::isWithDesuperheating);
}
//prvCastDesuperheating
EMSCRIPTEN_BINDINGS(PrvCastDesuperheating)
{
    class_<PrvCastDesuperheating>("PrvCastDesuperheating")
        .constructor<>()
        .function("Cast", &PrvCastDesuperheating::Cast);
}
// deaerator
EMSCRIPTEN_BINDINGS(deaerator)
{
    class_<Deaerator>("Deaerator")
        .constructor<double, double, double, double, SteamProperties::ThermodynamicQuantity, double, double, SteamProperties::ThermodynamicQuantity, double>()
        .function("getFeedwaterProperties", &Deaerator::getFeedwaterProperties)
        .function("getVentedSteamProperties", &Deaerator::getVentedSteamProperties)
        .function("getInletWaterProperties", &Deaerator::getInletWaterProperties)
        .function("getInletSteamProperties", &Deaerator::getInletSteamProperties);
}
// header
EMSCRIPTEN_BINDINGS(header)
{
    class_<Inlet>("Inlet")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double>()
        .function("getInletProperties", &Inlet::getInletProperties)
        .function("getInletEnergyFlow", &Inlet::getInletEnergyFlow)
        .function("getMassFlow", &Inlet::getMassFlow);

    register_vector<Inlet>("InletVector");

    class_<Header>("Header")
        .constructor<double, std::vector<Inlet>>()
        .function("getHeaderProperties", &Header::getHeaderProperties)
        .function("getHeaderPressure", &Header::getHeaderPressure)
        .function("getInletEnergyFlow", &Header::getInletEnergyFlow)
        .function("getInletMassFlow", &Header::getInletMassFlow)
        .function("getInlets", &Header::getInlets);
}
// turbine
EMSCRIPTEN_BINDINGS(turbine)
{
    class_<Turbine>("Turbine")
        .constructor<Turbine::Solve, double, SteamProperties::ThermodynamicQuantity, double, Turbine::TurbineProperty, double, double, double, double>()
        .constructor<Turbine::Solve, double, SteamProperties::ThermodynamicQuantity, double, Turbine::TurbineProperty, double, double, double, SteamProperties::ThermodynamicQuantity, double>()
        .smart_ptr<std::shared_ptr<Turbine>>("Turbine")
        .function("getInletProperties", &Turbine::getInletProperties)
        .function("getInletEnergyFlow", &Turbine::getInletEnergyFlow)
        .function("getOutletProperties", &Turbine::getOutletProperties)
        .function("getOutletEnergyFlow", &Turbine::getOutletEnergyFlow)
        .function("getMassFlow", &Turbine::getMassFlow)
        .function("getIsentropicEfficiency", &Turbine::getIsentropicEfficiency)
        .function("getEnergyOut", &Turbine::getEnergyOut)
        .function("getPowerOut", &Turbine::getPowerOut)
        .function("getGeneratorEfficiency", &Turbine::getGeneratorEfficiency);
}
// heatExchanger
EMSCRIPTEN_BINDINGS(heatExchanger)
{
    class_<HeatExchanger>("HeatExchanger")
        .constructor<SteamSystemModelerTool::FluidProperties, SteamSystemModelerTool::FluidProperties, double>()
        .function("calculate", &HeatExchanger::calculate);

    class_<HeatExchanger::Output>("HeatExchangerOutput")
        .smart_ptr<std::shared_ptr<HeatExchanger::Output>>("HeatExchangerOutput")
        .property("hotOutlet", &HeatExchanger::Output::hotOutlet)
        .property("coldOutlet", &HeatExchanger::Output::coldOutlet);
}
