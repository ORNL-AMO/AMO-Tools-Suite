#include "catch.hpp"
#include <calculator/furnace/FlowCalculationsEnergyUse.h>

TEST_CASE( "Calculate the Flow(1)", "[Flow][FlowCalculationsEnergyUse][Calculator]") {
    CHECK( FlowCalculationsEnergyUse(FlowCalculationsEnergyUse::Gas::HELIUM, 0.14, 5, 9, FlowCalculationsEnergyUse::Section::SHARP_EDGE, 0.6, 7325, 52, 63, 26, 16).getFlow() == Approx(647312.3211663722));
}

TEST_CASE( "Calculate the Heat Input(1)", "[Heat Input][FlowCalculationsEnergyUse][Calculator]") {
    CHECK( FlowCalculationsEnergyUse(FlowCalculationsEnergyUse::Gas::HELIUM, 0.14, 5, 9, FlowCalculationsEnergyUse::Section::SHARP_EDGE, 0.6, 7325, 52, 63, 26, 16).getHeatInput() == Approx(75865));
}

TEST_CASE( "Calculate the Flow(2)", "[Flow][FlowCalculationsEnergyUse][Calculator]") {
    CHECK( FlowCalculationsEnergyUse(FlowCalculationsEnergyUse::Gas::OTHER, 7, 6, 18, FlowCalculationsEnergyUse::Section::VENTURI, 0.8, 60000, 85, 55, 20, 10).getFlow() == Approx(135444));
}

TEST_CASE( "Calculate the Heat Input(2)", "[Heat Input][FlowCalculationsEnergyUse][Calculator]") {
    CHECK( FlowCalculationsEnergyUse(FlowCalculationsEnergyUse::Gas::OTHER, 7, 6, 18, FlowCalculationsEnergyUse::Section::VENTURI, 0.8, 60000, 85, 55, 20, 10).getHeatInput() == Approx(81266.53));
}

