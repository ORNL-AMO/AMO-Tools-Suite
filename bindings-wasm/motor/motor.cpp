#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/EstimateFLA.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_efficiency_class)
{
    class_<MotorEfficiency>("MotorEfficiency")
        .constructor<Motor::LineFrequency, double, Motor::EfficiencyClass, double>()
        .function("calculate", &MotorEfficiency::calculate);
}

EMSCRIPTEN_BINDINGS(est_fla_class)
{
    class_<EstimateFLA>("EstimateFLA")
        .constructor<double, double, Motor::LineFrequency, Motor::EfficiencyClass, double, double>()
        .function("getEstimatedFLA", &EstimateFLA::getEstimatedFLA);
}