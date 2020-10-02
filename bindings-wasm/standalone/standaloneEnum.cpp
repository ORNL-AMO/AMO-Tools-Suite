
#include "calculator/util/CHP.h"
#include "calculator/util/CompressedAir.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(standalone_enums)
{
    enum_<CHP::Option>("CHPOption")
        .value("PercentAvgkWhElectricCostAvoided", CHP::Option::PercentAvgkWhElectricCostAvoided)
        .value("StandbyRate", CHP::Option::StandbyRate);

        
    enum_<ReceiverTank::Option>("RecieverTankOption")
        .value("General", ReceiverTank::Option::General)
        .value("DedicatedStorage", ReceiverTank::Option::DedicatedStorage)
        .value("MeteredStorage", ReceiverTank::Option::MeteredStorage)
        .value("BridgingCompressorReactionDelay", ReceiverTank::Option::BridgingCompressorReactionDelay);


    enum_<PneumaticAirRequirement::PistonType>("PistonType")
        .value("SingleActing", ReceiverTank::Option::SingleActing)
        .value("DoubleActing", ReceiverTank::Option::DoubleActing);
}