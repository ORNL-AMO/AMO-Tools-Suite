#include "fans/Fan203.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(fan_enums)
{
    enum_<BaseGasDensity::GasType>("GasType")
        .value("AIR", BaseGasDensity::GasType::AIR)
        .value("STANDARDAIR", BaseGasDensity::GasType::STANDARDAIR)
        .value("OTHERGAS", BaseGasDensity::GasType::OTHERGAS);

    enum_<BaseGasDensity::InputType>("BaseGasDensityInputType")
        .value("DewPoint", BaseGasDensity::InputType::DewPoint)
        .value("RelativeHumidity", BaseGasDensity::InputType::RelativeHumidity)
        .value("WetBulbTemp", BaseGasDensity::InputType::WetBulbTemp);

}
