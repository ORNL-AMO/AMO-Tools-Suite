#include "calculator/motor/MotorEfficiency.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_efficiency_class)
{
    // enum_<Motor::LineFrequency>("LineFrequency")
    //     .value("FREQ60", Motor::LineFrequency::FREQ60)
    //     .value("FREQ50", Motor::LineFrequency::FREQ50);

    
    // enum_<Motor::EfficiencyClass>("EfficiencyClass")
    //     .value("STANDARD", Motor::EfficiencyClass::STANDARD)
    //     .value("ENERGY_EFFICIENT", Motor::EfficiencyClass::ENERGY_EFFICIENT)
    //     .value("PREMIUM", Motor::EfficiencyClass::PREMIUM)
    //     .value("SPECIFIED", Motor::EfficiencyClass::SPECIFIED);

    class_<MotorEfficiency>("MotorEfficiency")
        .constructor<Motor::LineFrequency, double, Motor::EfficiencyClass, double>()
        .function("calculate", &MotorEfficiency::calculate);
}