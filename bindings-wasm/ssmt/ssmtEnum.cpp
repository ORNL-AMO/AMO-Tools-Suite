#include "ssmt/SteamProperties.h"
#include "ssmt/Turbine.h"
#include "ssmt/api/TurbineInput.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(ssmt_enums)
{
    enum_<SteamProperties::ThermodynamicQuantity>("ThermodynamicQuantity")
        .value("TEMPERATURE", SteamProperties::ThermodynamicQuantity::TEMPERATURE)
        .value("ENTHALPY", SteamProperties::ThermodynamicQuantity::ENTHALPY)
        .value("ENTROPY", SteamProperties::ThermodynamicQuantity::ENTROPY)
        .value("QUALITY", SteamProperties::ThermodynamicQuantity::QUALITY);

    enum_<Turbine::Solve>("Solve")
        .value("OutletProperties", Turbine::Solve::OutletProperties)
        .value("IsentropicEfficiency", Turbine::Solve::IsentropicEfficiency);

    enum_<Turbine::TurbineProperty>("TurbineProperty")
        .value("MassFlow", Turbine::TurbineProperty::MassFlow)
        .value("PowerOut", Turbine::TurbineProperty::PowerOut);

    enum_<CondensingTurbineOperation>("CondensingTurbineOperation")
        .value("POWER_GENERATION", CondensingTurbineOperation::POWER_GENERATION)
        .value("STEAM_FLOW", CondensingTurbineOperation::STEAM_FLOW);

    enum_<PressureTurbineOperation>("PressureTurbineOperation")
        .value("BALANCE_HEADER", PressureTurbineOperation::BALANCE_HEADER)
        .value("FLOW_RANGE", PressureTurbineOperation::FLOW_RANGE)
        .value("POWER_GENERATION", PressureTurbineOperation::POWER_GENERATION)
        .value("POWER_RANGE", PressureTurbineOperation::POWER_RANGE)
        .value("STEAM_FLOW", PressureTurbineOperation::STEAM_FLOW);
}