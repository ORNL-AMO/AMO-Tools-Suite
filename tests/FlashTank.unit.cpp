#include "catch.hpp"
#include <ssmt/FlashTank.h>

TEST_CASE( "Calculate the Inlet Water Energy Flow #1", "[Inlet Water Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getInletWaterProperties().at("energyFlow") == Approx(72266));
    auto ft = FlashTank(4, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 1000, 33133, 4.3884);
	ft.setInletWaterPressure(4.54484);
    ft.setQuantityType(SteamProperties::ThermodynamicQuantity::ENTHALPY);
    ft.setQuantityValue(2000);
    ft.setInletWaterMassFlow(36133);
	ft.setTankPressure(4.3884);
    CHECK( ft.getInletWaterProperties().at("energyFlow") == Approx(72266));
}

TEST_CASE( "Calculate the Outlet Gas Mass Flow #1", "[Outlet Gas Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletSaturatedProperties().at("gasMassFlow") == Approx(19667));
}

TEST_CASE( "Calculate the Outlet Gas Energy Flow #1", "[Outlet Gas Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletSaturatedProperties().at("gasEnergyFlow") == Approx(55127));
}

TEST_CASE( "Calculate the Outlet Liquid Mass Flow #1", "[Outlet Liquid Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletSaturatedProperties().at("liquidMassFlow") == Approx(16466));
}

TEST_CASE( "Calculate the Outlet Liquid Energy Flow #1", "[Outlet Liquid Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletSaturatedProperties().at("liquidEnergyFlow") == Approx(17139));
}

TEST_CASE( "Calculate the Inlet Water Energy Flow #2", "[Inlet Water Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getInletWaterProperties().at("energyFlow") == Approx(6921.0977318671));
}

TEST_CASE( "Calculate the Outlet Gas Mass Flow #2", "[Outlet Gas Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletSaturatedProperties().at("gasMassFlow") == Approx(401.683398632));
}

TEST_CASE( "Calculate the Outlet Gas Energy Flow #2", "[Outlet Gas Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletSaturatedProperties().at("gasEnergyFlow") == Approx(1119.3361991061));
}

TEST_CASE( "Calculate the Outlet Liquid Mass Flow #2", "[Outlet Liquid Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletSaturatedProperties().at("liquidMassFlow") == Approx(7114.316601368));
}

TEST_CASE( "Calculate the Outlet Liquid Energy Flow #2", "[Outlet Liquid Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletSaturatedProperties().at("liquidEnergyFlow") == Approx(5801.761532761));
}