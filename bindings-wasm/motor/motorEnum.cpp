#include "calculator/motor/MotorEfficiency.h"
#include "calculator/pump/PumpShaftPower.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_enums)
{
    enum_<Motor::Drive>("Drive")
        .value("DIRECT_DRIVE", Motor::Drive::DIRECT_DRIVE)
        .value("V_BELT_DRIVE", Motor::Drive::V_BELT_DRIVE)
        .value("N_V_BELT_DRIVE", Motor::Drive::N_V_BELT_DRIVE)
        .value("S_BELT_DRIVE", Motor::Drive::S_BELT_DRIVE)
        .value("SPECIFIED", Motor::Drive::SPECIFIED);

    enum_<Motor::LineFrequency>("LineFrequency")
        .value("FREQ60", Motor::LineFrequency::FREQ60)
        .value("FREQ50", Motor::LineFrequency::FREQ50);

    enum_<Motor::LoadEstimationMethod>("LoadEstimationMethod")
        .value("POWER", Motor::LoadEstimationMethod::POWER)
        .value("CURRENT", Motor::LoadEstimationMethod::CURRENT);

    enum_<Motor::EfficiencyClass>("MotorEfficiencyClass")
        .value("STANDARD", Motor::EfficiencyClass::STANDARD)
        .value("ENERGY_EFFICIENT", Motor::EfficiencyClass::ENERGY_EFFICIENT)
        .value("PREMIUM", Motor::EfficiencyClass::PREMIUM)
        .value("SPECIFIED", Motor::EfficiencyClass::SPECIFIED);
}
