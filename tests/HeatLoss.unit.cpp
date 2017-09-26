#include "catch.hpp"
#include <ssmt/HeatLoss.h>

TEST_CASE( "Calculate the Inlet Energy Flow #1", "[Inlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getInletProperties().at("energyFlow") == Approx(15643));

    auto hl = HeatLoss(2.0, SteamProperties::ThermodynamicQuantity::ENTHALPY, 500, 5000, 2.0);
    hl.setInletPressure(2.418);
    hl.setQuantityType(SteamProperties::ThermodynamicQuantity::TEMPERATURE);
    hl.setQuantityValue(521);
    hl.setInletMassFlow(5434);
    hl.setPercentHeatLoss(2.44);
    CHECK( hl.getInletProperties().at("energyFlow") == Approx(15643));
}

TEST_CASE( "Calculate the Outlet Mass Flow", "[Outlet Mass Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getOutletProperties().at("massFlow") == Approx(5434));
}

TEST_CASE( "Calculate the Outlet Energy Flow #1", "[Outlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getOutletProperties().at("energyFlow") == Approx(15261.2789453459));
}

TEST_CASE( "Calculate the Heat Loss #1", "[Inlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(2.418, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 521, 5434, 2.44).getHeatLoss() == Approx(381.6884033071));
}

TEST_CASE( "Calculate the Inlet Energy Flow #2", "[Inlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(5.1414, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36011, 3.11).getInletProperties().at("energyFlow") == Approx(72022));
}

TEST_CASE( "Calculate the Outlet Energy Flow #2", "[Outlet Energy Flow][HeatLoss][ssmt]") {
    CHECK( HeatLoss(5.1414, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36011, 3.11).getOutletProperties().at("energyFlow") == Approx(69782));
}

TEST_CASE( "Calculate the Heat Loss #2", "[Heat Loss][HeatLoss][ssmt]") {
    CHECK( HeatLoss(5.1414, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36011, 3.11).getHeatLoss() == Approx(2239.8842));
}