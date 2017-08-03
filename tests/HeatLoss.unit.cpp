#include "catch.hpp"
#include <ssmt/HeatLoss.h>

TEST_CASE( "Calculate the Inlet Energy Flow #1", "[Inlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getInletEnergyFlow() == Approx(15643));
}

TEST_CASE( "Calculate the Outlet Mass Flow", "[Outlet Mass Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getOutletMassFlow() == Approx(5434));
}

TEST_CASE( "Calculate the Outlet Energy Flow #1", "[Outlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getOutletEnergyFlow() == Approx(15261.2789453459));
}

TEST_CASE( "Calculate the Heat Loss #1", "[Inlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getHeatLoss() == Approx(381.6884033071));
}

TEST_CASE( "Calculate the Inlet Energy Flow #2", "[Inlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(5.1414, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36011, 3.11).getInletEnergyFlow() == Approx(72022));
}

TEST_CASE( "Calculate the Outlet Energy Flow #2", "[Outlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(5.1414, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36011, 3.11).getOutletEnergyFlow() == Approx(69782));
}

TEST_CASE( "Calculate the Heat Loss #2", "[Heat Loss][HeatLoss][ssmt]") {
    CHECK( HeatLoss(5.1414, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36011, 3.11).getHeatLoss() == Approx(2239.8842));
}