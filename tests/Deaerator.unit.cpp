#include "catch.hpp"
#include <ssmt/Deaerator.h>

TEST_CASE( "Calculate the Feedwater Energy Flow for Deaerator calculator #1", "[Feedwater Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getFeedwaterEnergyFlow() == Approx(23707));
}

TEST_CASE( "Calculate the Vented Steam Mass Flow for Deaerator calculator #1", "[Vented Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getVentedSteamMassFlow() == Approx(80.558));
}

TEST_CASE( "Calculate the Vented Steam Energy Flow for Deaerator calculator #1", "[Vented Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getVentedSteamEnergyFlow() == Approx(220.1854575262));
}

TEST_CASE( "Calculate the Inlet Water Mass Flow for Deaerator calculator #1", "[Inlet Water Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletWaterMassFlow() == Approx(35929));
}

TEST_CASE( "Calculate the Inlet Water Energy Flow for Deaerator calculator #1", "[Inlet Water Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletWaterEnergyFlow() == Approx(10742));
}

TEST_CASE( "Calculate the Inlet Steam Mass Flow for Deaerator calculator #1", "[Inlet Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletSteamMassFlow() == Approx(4430.7329148269));
}

TEST_CASE( "Calculate the Inlet Steam Energy Flow for Deaerator calculator #1", "[Inlet Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletSteamEnergyFlow() == Approx(13185.2046114516));
}


TEST_CASE( "Calculate the Feedwater Energy Flow for Deaerator calculator #2", "[Feedwater Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getFeedwaterEnergyFlow() == Approx(21032));
}

TEST_CASE( "Calculate the Vented Steam Mass Flow for Deaerator calculator #2", "[Vented Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getVentedSteamMassFlow() == Approx(166.74));
}

TEST_CASE( "Calculate the Vented Steam Energy Flow for Deaerator calculator #2", "[Vented Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getVentedSteamEnergyFlow() == Approx(451.2310290232));
}

TEST_CASE( "Calculate the Inlet Water Mass Flow for Deaerator calculator #2", "[Inlet Water Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletWaterMassFlow() == Approx(34305));
}

TEST_CASE( "Calculate the Inlet Water Energy Flow for Deaerator calculator #2", "[Inlet Water Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletWaterEnergyFlow() == Approx(3430.5357797804));
}

TEST_CASE( "Calculate the Inlet Steam Mass Flow for Deaerator calculator #2", "[Inlet Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletSteamMassFlow() == Approx(7546.3822021967));
}

TEST_CASE( "Calculate the Inlet Steam Energy Flow for Deaerator calculator #2", "[Inlet Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletSteamEnergyFlow() == Approx(18053));
}

