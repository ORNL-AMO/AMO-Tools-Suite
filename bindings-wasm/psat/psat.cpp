
#include "calculator/pump/PumpShaftPower.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/HeadTool.h"
#include <calculator/motor/MotorShaftPower.h>
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

//resultsExisting
EMSCRIPTEN_BINDINGS(psat_results_existing)
{
    class_<Pump::Input>("PsatInput")
        .constructor<Pump::Style, double, double, Motor::Drive, double, double, int, Pump::SpecificSpeed, double>();

    class_<Pump::FieldData>("PumpFieldData")
        .constructor<double, double, Motor::LoadEstimationMethod, double, double, double>();

    class_<PSATResult>("ResultsExisting")
        .constructor<Pump::Input, Motor, Pump::FieldData, double, double>()
        .function("calculateExisting", &PSATResult::calculateExisting);
}

EMSCRIPTEN_BINDINGS(psat_results_output)
{
    class_<PSATResult::Output>("PsatResults")
        .constructor<double, double, double, double, double, double, double, double, double, double, double, double>()
        .property("pumpEfficiency", &PSATResult::Output::pumpEfficiency)
        .property("motorRatedPower", &PSATResult::Output::motorRatedPower)
        .property("motorShaftPower", &PSATResult::Output::motorShaftPower)
        .property("pumpShaftPower", &PSATResult::Output::pumpShaftPower)
        .property("motorEfficiency", &PSATResult::Output::motorEfficiency)
        .property("motorPowerFactor", &PSATResult::Output::motorPowerFactor)
        .property("motorCurrent", &PSATResult::Output::motorCurrent)
        .property("motorPower", &PSATResult::Output::motorPower)
        .property("annualEnergy", &PSATResult::Output::annualEnergy)
        .property("annualCost", &PSATResult::Output::annualCost)
        .property("loadFactor", &PSATResult::Output::loadFactor)
        .property("driveEfficiency", &PSATResult::Output::driveEfficiency)
        .property("estimatedFLA", &PSATResult::Output::estimatedFLA);
}

//resultsModified
//estFLA
//achievableEfficiency
EMSCRIPTEN_BINDINGS(optimal_specified_speed_class)
{
    class_<OptimalSpecificSpeedCorrection>("OptimalSpecificSpeedCorrection")
        .constructor<Pump::Style, double>()
        .function("calculate", &OptimalSpecificSpeedCorrection::calculate);
}
//pumpEfficiency
//motorPerformance