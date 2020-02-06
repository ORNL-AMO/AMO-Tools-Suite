
#include "calculator/pump/PumpShaftPower.h"
#include <emscripten/bind.h>
using namespace emscripten;


EMSCRIPTEN_BINDINGS(pump_shaft_class)
{
    enum_<Motor::Drive>("Drive")
        .value("DIRECT_DRIVE", Motor::Drive::DIRECT_DRIVE)
        .value("V_BELT_DRIVE", Motor::Drive::V_BELT_DRIVE)
        .value("N_V_BELT_DRIVE", Motor::Drive::N_V_BELT_DRIVE)
        .value("S_BELT_DRIVE", Motor::Drive::S_BELT_DRIVE)
        .value("SPECIFIED", Motor::Drive::SPECIFIED);

    class_<PumpShaftPower>("PumpShaftPower")
        .constructor<double, Motor::Drive, double>()
        .function("calculate", &PumpShaftPower::calculate);

    class_<PumpShaftPower::Output>("Output")
        .constructor<double, double>()
        .property("pumpShaftPower", &PumpShaftPower::Output::pumpShaftPower)
        .property("driveEfficiency", &PumpShaftPower::Output::driveEfficiency);
}