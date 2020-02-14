
#include "calculator/pump/PumpShaftPower.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/HeadTool.h"
#include "calculator/motor/MotorShaftPower.h"
#include "calculator/pump/PumpEfficiency.h"
#include "results/Results.h"
#include "results/InputData.h"
#include <emscripten/bind.h>
using namespace emscripten;

//pump shaft power (Not Sure Used in Desktop, but good example)
EMSCRIPTEN_BINDINGS(pump_shaft_class)
{
    class_<PumpShaftPower>("PumpShaftPower")
        .constructor<double, Motor::Drive, double>()
        .function("calculate", &PumpShaftPower::calculate);

    class_<PumpShaftPower::Output>("PumpShaftPowerOutput")
        .constructor<double, double>()
        .property("pumpShaftPower", &PumpShaftPower::Output::pumpShaftPower)
        .property("driveEfficiency", &PumpShaftPower::Output::driveEfficiency);
}

//headToolSuctionTank
EMSCRIPTEN_BINDINGS(head_tool_suction_tank_class)
{
    class_<HeadToolSuctionTank>("HeadToolSuctionTank")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &HeadToolSuctionTank::calculate);
}
//headTool
EMSCRIPTEN_BINDINGS(head_tool_class)
{
    class_<HeadTool>("HeadTool")
        .constructor<double, double, double, double, double, double, double, double, double, double>()
        .function("calculate", &HeadTool::calculate);
}
//headToolOutput
EMSCRIPTEN_BINDINGS(head_tool_output)
{
    class_<HeadToolBase::Output>("HeadToolOutput")
        .constructor<double, double, double, double, double, double>()
        .property("differentialElevationHead", &HeadToolBase::Output::elevationHead)
        .property("differentialPressureHead", &HeadToolBase::Output::pressureHead)
        .property("differentialVelocityHead", &HeadToolBase::Output::velocityHeadDifferential)
        .property("estimatedSuctionFrictionHead", &HeadToolBase::Output::suctionHead)
        .property("estimatedDischargeFrictionHead", &HeadToolBase::Output::dischargeHead)
        .property("pumpHead", &HeadToolBase::Output::pumpHead);
}

//resultsExisting & resultsModified
EMSCRIPTEN_BINDINGS(psat_results)
{
    class_<Pump::Input>("PsatInput")
        .constructor<Pump::Style, double, double, Motor::Drive, double, double, int, Pump::SpecificSpeed, double>();

    class_<Pump::FieldData>("PumpFieldData")
        .constructor<double, double, Motor::LoadEstimationMethod, double, double, double>();

    class_<PSATResult>("PSAT")
        .constructor<Pump::Input, Motor, Pump::FieldData, double, double>()
        .function("calculateExisting", &PSATResult::calculateExisting)
        .function("calculateModified", &PSATResult::calculateModified)
        .function("getAnnualSavingsPotential", &PSATResult::getAnnualSavingsPotential)
        .function("getOptimizationRating", &PSATResult::getOptimizationRating);
}

EMSCRIPTEN_BINDINGS(psat_results_output)
{
    class_<PSATResult::Output>("PsatResults")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double>()
        .property("pump_efficiency", &PSATResult::Output::pumpEfficiency)
        .property("motor_rated_power", &PSATResult::Output::motorRatedPower)
        .property("motor_shaft_power", &PSATResult::Output::motorShaftPower)
        .property("pump_shaft_power", &PSATResult::Output::pumpShaftPower)
        .property("motor_efficiency", &PSATResult::Output::motorEfficiency)
        .property("motor_power_factor", &PSATResult::Output::motorPowerFactor)
        .property("motor_current", &PSATResult::Output::motorCurrent)
        .property("motor_power", &PSATResult::Output::motorPower)
        .property("annual_energy", &PSATResult::Output::annualEnergy)
        .property("annual_cost", &PSATResult::Output::annualCost)
        .property("load_factor", &PSATResult::Output::loadFactor)
        .property("drive_efficiency", &PSATResult::Output::driveEfficiency)
        .property("estimatedFLA", &PSATResult::Output::estimatedFLA);
}

//achievableEfficiency
EMSCRIPTEN_BINDINGS(optimal_specified_speed_class)
{
    class_<OptimalSpecificSpeedCorrection>("OptimalSpecificSpeedCorrection")
        .constructor<Pump::Style, double>()
        .function("calculate", &OptimalSpecificSpeedCorrection::calculate);
}
//pumpEfficiency
EMSCRIPTEN_BINDINGS(pump_efficiency)
{
    class_<PumpEfficiency>("PumpEfficiency")
        .constructor<Pump::Style, double>()
        .function("calculate", &PumpEfficiency::calculate);
}

EMSCRIPTEN_BINDINGS(pump_efficiency_output)
{
    class_<PumpEfficiency::Output>("PumpEfficiencyResults")
        .constructor<double, double>()
        .property("average", &PumpEfficiency::Output::average)
        .property("max", &PumpEfficiency::Output::max);
}