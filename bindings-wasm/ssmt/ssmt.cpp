

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
        .property("temperature", &SteamSystemModelerTool::SteamPropertiesOutput::temperature)
        .property("pressure", &SteamSystemModelerTool::SteamPropertiesOutput::pressure)
        .property("quality", &SteamSystemModelerTool::SteamPropertiesOutput::quality)
        .property("specificVolume", &SteamSystemModelerTool::SteamPropertiesOutput::specificVolume)
        .property("density", &SteamSystemModelerTool::SteamPropertiesOutput::density)
        .property("specificEnthalpy", &SteamSystemModelerTool::SteamPropertiesOutput::specificEnthalpy)
        .property("specificEntropy", &SteamSystemModelerTool::SteamPropertiesOutput::specificEntropy)
        .property("internalEnergy", &SteamSystemModelerTool::SteamPropertiesOutput::internalEnergy);

    class_<SteamSystemModelerTool::FluidProperties>("FluidProperties")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .property("massFlow", &SteamSystemModelerTool::FluidProperties::massFlow)
        .property("energyFlow", &SteamSystemModelerTool::FluidProperties::energyFlow)
        .property("temperature", &SteamSystemModelerTool::FluidProperties::temperature)
        .property("pressure", &SteamSystemModelerTool::FluidProperties::pressure)
        .property("quality", &SteamSystemModelerTool::FluidProperties::quality)
        .property("specificVolume", &SteamSystemModelerTool::FluidProperties::specificVolume)
        .property("density", &SteamSystemModelerTool::FluidProperties::density)
        .property("specificEnthalpy", &SteamSystemModelerTool::FluidProperties::specificEnthalpy)
        .property("specificEntropy", &SteamSystemModelerTool::FluidProperties::specificEntropy)
        .property("internalEnergy", &SteamSystemModelerTool::FluidProperties::internalEnergy);
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
        .function("calculate", &SaturatedTemperature::calculate);
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
        .function("getFuelEnergy", &Boiler::getFuelEnergy);
}
// heatLoss
EMSCRIPTEN_BINDINGS(heatLoss)
{
    class_<HeatLoss>("HeatLoss")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double, double>()
        .function("getInletProperties", &HeatLoss::getInletProperties)
        .function("getOutletProperties", &HeatLoss::getOutletProperties)
        .function("getHeatLoss", &HeatLoss::getHeatLoss);
}
// flashTank
EMSCRIPTEN_BINDINGS(flashTank)
{
    class_<FlashTank>("FlashTank")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double>()
        .function("getInletWaterProperties", &FlashTank::getInletWaterProperties)
        .function("getOutletGasSaturatedProperties", &FlashTank::getOutletGasSaturatedProperties)
        .function("getOutletLiquidSaturatedProperties", &FlashTank::getOutletLiquidSaturatedProperties);
}
// prvWithoutDesuperheating
EMSCRIPTEN_BINDINGS(prvWithoutDesuperheating)
{
    class_<PrvWithoutDesuperheating>("PrvWithoutDesuperheating")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double>()
        .function("getInletProperties", &PrvWithoutDesuperheating::getInletProperties)
        .function("getOutletProperties", &PrvWithoutDesuperheating::getOutletProperties)
        .function("getInletMassFlow", &PrvWithoutDesuperheating::getInletMassFlow)
        .function("getInletEnergyFlow", &PrvWithoutDesuperheating::getInletEnergyFlow)
        .function("getOutletMassFlow", &PrvWithoutDesuperheating::getOutletMassFlow)
        .function("getOutletEnergyFlow", &PrvWithoutDesuperheating::getOutletEnergyFlow);
}
// prvWithDesuperheating
EMSCRIPTEN_BINDINGS(prvWithDesuperheating)
{
    class_<PrvWithDesuperheating>("PrvWithoutDesuperheating")
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double, double, double, SteamProperties::ThermodynamicQuantity, double, double>()
        .function("getInletProperties", &PrvWithDesuperheating::getInletProperties)
        .function("getOutletProperties", &PrvWithDesuperheating::getOutletProperties)
        .function("getInletMassFlow", &PrvWithDesuperheating::getInletMassFlow)
        .function("getInletEnergyFlow", &PrvWithDesuperheating::getInletEnergyFlow)
        .function("getOutletMassFlow", &PrvWithDesuperheating::getOutletMassFlow)
        .function("getOutletEnergyFlow", &PrvWithDesuperheating::getOutletEnergyFlow)
        .function("getFeedwaterProperties", &PrvWithDesuperheating::getFeedwaterProperties)
        .function("getFeedwaterMassFlow", &PrvWithDesuperheating::getFeedwaterMassFlow)
        .function("getFeedwaterEnergyFlow", &PrvWithDesuperheating::getFeedwaterEnergyFlow);
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
        .constructor<double, SteamProperties::ThermodynamicQuantity, double, double>();

    register_vector<Inlet>("InletVector");

    class_<Header>("Header")
        .constructor<double, std::vector<Inlet>>()
        .function("getHeaderProperties", &Header::getHeaderProperties)
        .function("getHeaderPressure", &Header::getHeaderPressure)
        .function("getInletEnergyFlow", &Header::getInletEnergyFlow)
        .function("getInletMassFlow", &Header::getInletMassFlow);
}
// turbine
EMSCRIPTEN_BINDINGS(turbine)
{
    class_<Turbine>("Turbine")
        .constructor<Turbine::Solve, double, SteamProperties::ThermodynamicQuantity, double, Turbine::TurbineProperty, double, double, double, double>()
        .constructor<Turbine::Solve, double, SteamProperties::ThermodynamicQuantity, double, Turbine::TurbineProperty, double, double, double, SteamProperties::ThermodynamicQuantity, double>()
        .function("getHeaderProperties", &Turbine::getInletProperties)
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
        .property("hotOutlet", &HeatExchanger::Output::hotOutlet)
        .property("coldOutlet", &HeatExchanger::Output::coldOutlet);
}
// steamModeler
