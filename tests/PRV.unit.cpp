#include "catch.hpp"
#include <ssmt/PRV.h>

TEST_CASE( "Calculate the Inlet Energy Flow without Desuperheating", "[Inlet Energy Flow][PRV][ssmt]") {
    CHECK( PrvWithoutDesuperheating(4.8794, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 691.5, 37970, 4.0823).getInletEnergyFlow() == Approx(123148));
}

TEST_CASE( "Calculate the Outlet Mass Flow without Desuperheating", "[Outlet Mass Flow][PRV][ssmt]") {
    CHECK( PrvWithoutDesuperheating(4.8794, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 691.5, 37970, 4.0823).getOutletMassFlow() == Approx(37970));
}

TEST_CASE( "Calculate the Outlet Energy Flow without Desuperheating", "[Outlet Energy Flow][PRV][ssmt]") {
    CHECK( PrvWithoutDesuperheating(4.8794, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 691.5, 37970, 4.0823).getOutletEnergyFlow() == Approx(123148));
}

TEST_CASE( "Calculate the Outlet Temperature without Desuperheating", "[Outlet Temperature][PRV][ssmt]") {
    std::unordered_map <std::string, double> props = PrvWithoutDesuperheating(4.8794, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 691.5, 37970, 4.0823).getOutletProperties();
    CHECK( props["temperature"] == Approx(686.0087848902));
}

TEST_CASE( "Calculate the Inlet Energy Flow with Desuperheating", "[Inlet Energy Flow][PRV][ssmt]") {
    CHECK( PrvWithDesuperheating(2.8937, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 936.3, 17599, 0.8188, 0.2937, SteamProperties::ThermodynamicQuantity::ENTROPY, 5, 708.3).getInletEnergyFlow() == Approx(67367));
}

TEST_CASE( "Calculate the Outlet Mass Flow with Desuperheating", "[Outlet Mass Flow][PRV][ssmt]") {
    CHECK( PrvWithDesuperheating(2.8937, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 936.3, 17599, 0.8188, 0.2937, SteamProperties::ThermodynamicQuantity::ENTROPY, 5, 708.3).getOutletMassFlow() == Approx(23583.4693675945));
}

TEST_CASE( "Calculate the Outlet Energy Flow with Desuperheating", "[Outlet Energy Flow][PRV][ssmt]") {
    CHECK( PrvWithDesuperheating(2.8937, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 936.3, 17599, 0.8188, 0.2937, SteamProperties::ThermodynamicQuantity::ENTROPY, 5, 708.3).getOutletEnergyFlow() == Approx(78813));
}

TEST_CASE( "Calculate the Feedwater Mass Flow with Desuperheating", "[Feedwater Mass Flow][PRV][ssmt]") {
    CHECK( PrvWithDesuperheating(2.8937, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 936.3, 17599, 0.8188, 0.2937, SteamProperties::ThermodynamicQuantity::ENTROPY, 5, 708.3).getFeedwaterMassFlow() == Approx(5984.4693675945));
}

TEST_CASE( "Calculate the Feedwater Energy Flow with Desuperheating", "[Feedwater Energy Flow][PRV][ssmt]") {
    CHECK( PrvWithDesuperheating(2.8937, SteamProperties::ThermodynamicQuantity::TEMPERATURE, 936.3, 17599, 0.8188, 0.2937, SteamProperties::ThermodynamicQuantity::ENTROPY, 5, 708.3).getFeedwaterEnergyFlow() == Approx(11445.6317811999));
}