#include "ssmt/SteamProperties.h"
#include "ssmt/Turbine.h"
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

}