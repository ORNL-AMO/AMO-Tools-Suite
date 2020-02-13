#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/motor/EstimateFLA.h"
#include "calculator/motor/MotorPerformance.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(motor_efficiency)
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

EMSCRIPTEN_BINDINGS(motor_class)
{
    class_<Motor>("Motor")
        .constructor<Motor::LineFrequency, double, double, Motor::EfficiencyClass, double, double, double, double>();
}

EMSCRIPTEN_BINDINGS(motor_current)
{
    class_<MotorCurrent>("MotorCurrent")
        .constructor<double, double, Motor::LineFrequency, Motor::EfficiencyClass, double, double, double>()
        .function("calculateCurrent", &MotorCurrent::calculateCurrent);
}

EMSCRIPTEN_BINDINGS(motor_power_factor)
{
    class_<MotorPowerFactor>("MotorPowerFactor")
        .constructor<double, double, double, double, double>()
        .function("calculate", &MotorPowerFactor::calculate);
}

EMSCRIPTEN_BINDINGS(motor_performance)
{
    class_<MotorPerformance>("MotorPerformance")
        .constructor<Motor::LineFrequency, double, Motor::EfficiencyClass, double, double, double, double, double>()
        .function("calculate", &MotorPerformance::calculate);
}

EMSCRIPTEN_BINDINGS(motor_performance_output)
{
    class_<MotorPerformance::Output>("MotorPerformanceOutput")
        .constructor<double, double, double>()
        .property("current", &MotorPerformance::Output::current)
        .property("efficiency", &MotorPerformance::Output::efficiency)
        .property("powerFactor", &MotorPerformance::Output::powerFactor);
}