#include "catch.hpp"
#include <ssmt/Deaerator.h>

TEST_CASE( "Calculate the Feedwater Energy Flow for Deaerator calculator #1", "[Feedwater Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getFeedwaterProperties().energyFlow == Approx(23706979.8592));
    auto d = Deaerator(0.3, 0.3, 40275, 0.25, SteamProperties::ThermodynamicQuantity::ENTROPY, 354.55, 0.5, SteamProperties::ThermodynamicQuantity::ENTROPY, 538.65);
    d.setDeaeratorPressure(0.36);
    d.setVentRate(0.2);
    d.setFeedwaterMassFlow(40279);
    d.setWaterPressure(0.15);
    d.setWaterQuantityType(SteamProperties::ThermodynamicQuantity::TEMPERATURE);
    d.setWaterQuantityValue(344.55);
    d.setSteamPressure(0.4);
    d.setSteamQuantityType(SteamProperties::ThermodynamicQuantity::TEMPERATURE);
    d.setSteamQuantityValue(528.65);
    CHECK(d.getFeedwaterProperties().energyFlow == Approx(23706979.8592));
}

TEST_CASE( "Calculate the Vented Steam Mass Flow for Deaerator calculator #1", "[Vented Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getVentedSteamProperties().massFlow == Approx(80.558));
}

TEST_CASE( "Calculate the Vented Steam Energy Flow for Deaerator calculator #1", "[Vented Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getVentedSteamProperties().energyFlow == Approx(220185.4575262));
}

TEST_CASE( "Calculate the Inlet Water Mass Flow for Deaerator calculator #1", "[Inlet Water Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletWaterProperties().massFlow == Approx(35929));
}

TEST_CASE( "Calculate the Inlet Water Energy Flow for Deaerator calculator #1", "[Inlet Water Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletWaterProperties().energyFlow == Approx(10741960.7053));
}

TEST_CASE( "Calculate the Inlet Steam Mass Flow for Deaerator calculator #1", "[Inlet Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletSteamProperties().massFlow == Approx(4430.7329148269));
}

TEST_CASE( "Calculate the Inlet Steam Energy Flow for Deaerator calculator #1", "[Inlet Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.36, 0.2, 40279, 0.15, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 344.55, 0.4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 528.65).getInletSteamProperties().energyFlow == Approx(13185204.6114516));
}

TEST_CASE( "Calculate the Feedwater Energy Flow for Deaerator calculator #2", "[Feedwater Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getFeedwaterProperties().energyFlow == Approx(21032141.2981));
}

TEST_CASE( "Calculate the Vented Steam Mass Flow for Deaerator calculator #2", "[Vented Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getVentedSteamProperties().massFlow == Approx(166.74));
}

TEST_CASE( "Calculate the Vented Steam Energy Flow for Deaerator calculator #2", "[Vented Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getVentedSteamProperties().energyFlow == Approx(451231.0290232));
}

TEST_CASE( "Calculate the Inlet Water Mass Flow for Deaerator calculator #2", "[Inlet Water Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletWaterProperties().massFlow == Approx(34305));
}

TEST_CASE( "Calculate the Inlet Water Energy Flow for Deaerator calculator #2", "[Inlet Water Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletWaterProperties().energyFlow == Approx(3430535.7797804));
}

TEST_CASE( "Calculate the Inlet Steam Mass Flow for Deaerator calculator #2", "[Inlet Steam Mass Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletSteamProperties().massFlow == Approx(7546.3822021967));
}

TEST_CASE( "Calculate the Inlet Steam Energy Flow for Deaerator calculator #2", "[Inlet Steam Energy Flow][Deaerator][ssmt]") {
    CHECK( Deaerator(0.1998, 0.4, 41685, 0.1235, SteamProperties::ThermodynamicQuantity::ENTHALPY, 100, 0.4777, SteamProperties::ThermodynamicQuantity::ENTROPY, 6).getInletSteamProperties().energyFlow == Approx(18052836.5474));
}

