
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(pump_enums)
{
    enum_<Pump::Style>("PumpStyle")
        .value("END_SUCTION_SLURRY", Pump::Style::END_SUCTION_SLURRY)
        .value("END_SUCTION_SEWAGE", Pump::Style::END_SUCTION_SEWAGE)
        .value("END_SUCTION_STOCK", Pump::Style::END_SUCTION_STOCK)
        .value("END_SUCTION_SUBMERSIBLE_SEWAGE", Pump::Style::END_SUCTION_SUBMERSIBLE_SEWAGE)
        .value("API_DOUBLE_SUCTION", Pump::Style::API_DOUBLE_SUCTION)
        .value("MULTISTAGE_BOILER_FEED", Pump::Style::MULTISTAGE_BOILER_FEED)
        .value("END_SUCTION_ANSI_API", Pump::Style::END_SUCTION_ANSI_API)
        .value("AXIAL_FLOW", Pump::Style::AXIAL_FLOW)
        .value("DOUBLE_SUCTION", Pump::Style::DOUBLE_SUCTION)
        .value("VERTICAL_TURBINE", Pump::Style::VERTICAL_TURBINE)
        .value("LARGE_END_SUCTION", Pump::Style::LARGE_END_SUCTION)
        .value("SPECIFIED_OPTIMAL_EFFICIENCY", Pump::Style::SPECIFIED_OPTIMAL_EFFICIENCY);

    enum_<Pump::SpecificSpeed>("SpecificSpeed")
        .value("FIXED_SPEED", Pump::SpecificSpeed::FIXED_SPEED)
        .value("NOT_FIXED_SPEED", Pump::SpecificSpeed::NOT_FIXED_SPEED);
}