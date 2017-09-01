#include "catch.hpp"
#include <ssmt/FlashTank.h>

TEST_CASE( "Calculate the Inlet Water Energy Flow #1", "[Inlet Water Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getInletWaterEnergyFlow() == Approx(72266));
}

TEST_CASE( "Calculate the Outlet Gas Mass Flow #1", "[Outlet Gas Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletGasMassFlow() == Approx(19667));
}

TEST_CASE( "Calculate the Outlet Gas Energy Flow #1", "[Outlet Gas Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletGasEnergyFlow() == Approx(55127));
}

TEST_CASE( "Calculate the Outlet Liquid Mass Flow #1", "[Outlet Liquid Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletLiquidMassFlow() == Approx(16466));
}

TEST_CASE( "Calculate the Outlet Liquid Energy Flow #1", "[Outlet Liquid Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(4.54484, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 36133, 3.3884).getOutletLiquidEnergyFlow() == Approx(17139));
}

TEST_CASE( "Calculate the Inlet Water Energy Flow #2", "[Inlet Water Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getInletWaterEnergyFlow() == Approx(6921.0977318671));
}

TEST_CASE( "Calculate the Outlet Gas Mass Flow #2", "[Outlet Gas Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletGasMassFlow() == Approx(401.683398632));
}

TEST_CASE( "Calculate the Outlet Gas Energy Flow #2", "[Outlet Gas Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletGasEnergyFlow() == Approx(1119.3361991061));
}

TEST_CASE( "Calculate the Outlet Liquid Mass Flow #2", "[Outlet Liquid Mass Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletLiquidMassFlow() == Approx(7114.316601368));
}

TEST_CASE( "Calculate the Outlet Liquid Energy Flow #2", "[Outlet Liquid Energy Flow][FlashTank][ssmt]") {
    CHECK( FlashTank(2.1077, SteamProperties::ThermodynamicQuantity::QUALITY, 0, 7516, 1.3047).getOutletLiquidEnergyFlow() == Approx(5801.761532761));
}