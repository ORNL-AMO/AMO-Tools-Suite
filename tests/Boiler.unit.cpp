#include "catch.hpp"
#include <ssmt/Boiler.h>

TEST_CASE( "Calculate the Steam Energy Flow", "[Steam Energy Flow][Boiler][ssmt]") {
    CHECK( Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45).getSteamEnergyFlow() == Approx(110.7533647509));
}

TEST_CASE( "Calculate the Feedwater Mass Flow", "[Feedwater Mass Flow][Boiler][ssmt]") {
    CHECK( Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45).getFeedwaterMassFlow() == Approx(45.9183673469));
}

TEST_CASE( "Calculate the Feedwater Energy Flow", "[Feedwater Energy Flow][Boiler][ssmt]") {
    CHECK( Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45).getFeedwaterEnergyFlow() == Approx(64.6469770669));
}

TEST_CASE( "Calculate the Blowdown Mass Flow", "[Blowdown Mass Flow][Boiler][ssmt]") {
    CHECK( Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45).getBlowdownMassFlow() == Approx(0.9183673469));
}

TEST_CASE( "Calculate the Blowdown Energy Flow", "[Blowdown Energy Flow][Boiler][ssmt]") {
    CHECK( Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45).getBlowdownEnergyFlow() == Approx(1.6779495529));
}

TEST_CASE( "Calculate the Boiler Energy", "[Boiler Energy][Boiler][ssmt]") {
    CHECK( Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45).getBoilerEnergy() == Approx(47.7843372368));
}

TEST_CASE( "Calculate the Fuel Energy #1", "[Fuel Energy][Boiler][ssmt]") {
    CHECK( Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45).getFuelEnergy() == Approx(56.2168673374));
}

TEST_CASE( "Calculate the Fuel Energy #2", "[Fuel Energy][Boiler][ssmt]") {
    CHECK( Boiler(0.3631, 72.4, 3.7, 5.5766, SteamProperties::ThermodynamicQuantity::QUALITY, 1, 10864).getFuelEnergy() == Approx(33344.279478971));
}