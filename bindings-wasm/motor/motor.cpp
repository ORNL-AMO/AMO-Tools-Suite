#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/motor/EstimateFLA.h"
#include "calculator/motor/MotorPerformance.h"
#include <calculator/motor/MotorData.h>
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(motorData_class)
{
    class_<MotorData>("MotorData")
        .constructor<double, int, int, double, Motor::EfficiencyClass, std::string, std::string, Motor::LineFrequency, int, std::string>()
            .function("getId", &MotorData::getId)
            .function("getHp", &MotorData::getHp)
            .function("getSynchronousSpeed", &MotorData::getSynchronousSpeed)
            .function("getPoles", &MotorData::getPoles)
            .function("getNominalEfficiency", &MotorData::getNominalEfficiency)
            .function("getEfficiencyClass", &MotorData::getEfficiencyClass)
            .function("getNemaTable", &MotorData::getNemaTable)
            .function("getEnclosureType", &MotorData::getEnclosureType)
            .function("getLineFrequency", &MotorData::getLineFrequency)
            .function("getVoltageLimit", &MotorData::getVoltageLimit)
            .function("getCatalog", &MotorData::getCatalog)
            .function("setId", &MotorData::setId)
            .function("setHp", &MotorData::setHp)
            .function("setSynchronousSpeed", &MotorData::setSynchronousSpeed)
            .function("setPoles", &MotorData::setPoles)
            .function("setNominalEfficiency", &MotorData::setNominalEfficiency)
            .function("setEfficiencyClass", &MotorData::setEfficiencyClass)
            .function("setNemaTable", &MotorData::setNemaTable)
            .function("setEnclosureType", &MotorData::setEnclosureType)
            .function("setLineFrequency", &MotorData::setLineFrequency)
            .function("setVoltageLimit", &MotorData::setVoltageLimit)
            .function("setCatalog", &MotorData::setCatalog);

    register_vector<MotorData>("MotorDataV");
}

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