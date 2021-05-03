
#include "calculator/util/CHP.h"
#include "calculator/util/CompressedAir.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(standalone_enums)
{
    enum_<CHP::Option>("CHPOption")
        .value("PercentAvgkWhElectricCostAvoided", CHP::Option::PercentAvgkWhElectricCostAvoided)
        .value("StandbyRate", CHP::Option::StandbyRate);

        
    enum_<ReceiverTank::Method>("ReceiverTankMethod")
        .value("General", ReceiverTank::Method::General)
        .value("DedicatedStorage", ReceiverTank::Method::DedicatedStorage)
        .value("MeteredStorage", ReceiverTank::Method::MeteredStorage)
        .value("BridgingCompressorReactionDelay", ReceiverTank::Method::BridgingCompressorReactionDelay);


    enum_<PneumaticAirRequirement::PistonType>("PistonType")
        .value("SingleActing", PneumaticAirRequirement::PistonType::SingleActing)
        .value("DoubleActing", PneumaticAirRequirement::PistonType::DoubleActing);
}