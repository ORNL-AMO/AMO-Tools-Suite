
#include "calculator/pump/PumpShaftPower.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/HeadTool.h"
// #include "calculator/pump/HeadTool.h"
#include <emscripten/bind.h>
using namespace emscripten;

//pump shaft power (Not Sure Used in Desktop, good example)
EMSCRIPTEN_BINDINGS(pump_shaft_class)
{
    // enum_<Motor::Drive>("Drive")
    //     .value("DIRECT_DRIVE", Motor::Drive::DIRECT_DRIVE)
    //     .value("V_BELT_DRIVE", Motor::Drive::V_BELT_DRIVE)
    //     .value("N_V_BELT_DRIVE", Motor::Drive::N_V_BELT_DRIVE)
    //     .value("S_BELT_DRIVE", Motor::Drive::S_BELT_DRIVE)
    //     .value("SPECIFIED", Motor::Drive::SPECIFIED);

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

    class_<HeadToolBase::Output>("HeadToolSuctionTankOutput")
        .constructor<double, double, double, double, double, double>()
        .property("differentialElevationHead", &HeadToolBase::Output::elevationHead)
        .property("differentialPressureHead", &HeadToolBase::Output::pressureHead)
        .property("differentialVelocityHead", &HeadToolBase::Output::velocityHeadDifferential)
        .property("estimatedSuctionFrictionHead", &HeadToolBase::Output::suctionHead)
        .property("estimatedDischargeFrictionHead", &HeadToolBase::Output::dischargeHead)
        .property("pumpHead", &HeadToolBase::Output::pumpHead);
}
//headTool
//resultsExisting
//resultsModified
//estFLA
//achievableEfficiency
EMSCRIPTEN_BINDINGS(optimal_specified_speed_class)
{
    // enum_<Pump::Style>("PumpStyle")
    //     .value("END_SUCTION_SLURRY", Pump::Style::END_SUCTION_SLURRY)
    //     .value("END_SUCTION_SEWAGE", Pump::Style::END_SUCTION_SEWAGE)
    //     .value("END_SUCTION_STOCK", Pump::Style::END_SUCTION_STOCK)
    //     .value("END_SUCTION_SUBMERSIBLE_SEWAGE", Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE)
    //     .value("API_DOUBLE_SUCTION", Pump::Style::API_DOUBLE_SUCTION)
    //     .value("MULTISTAGE_BOILER_FEED", Pump::Style::MULTISTAGE_BOILER_FEED)
    //     .value("END_SUCTION_ANSI_API", Pump::Style::END_SUCTION_ANSI_API)
    //     .value("DOUBLE_SUCTION", Pump::Style::DOUBLE_SUCTION)
    //     .value("VERTICAL_TURBINE", Pump::Style::VERTICAL_TURBINE)
    //     .value("LARGE_END_SUCTION", Pump::Style::LARGE_END_SUCTION)
    //     .value("SPECIFIED_OPTIMAL_EFFICIENCY", Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY);

    class_<OptimalSpecificSpeedCorrection>("OptimalSpecificSpeedCorrection")
        .constructor<Pump::Style, double>()
        .function("calculate", &OptimalSpecificSpeedCorrection::calculate);
}
//pumpEfficiency
//motorPerformance