#include "catch.hpp"
#include <ssmt/Boiler.h>

TEST_CASE( "Calculate Boiler properties", "[Boiler][ssmt]") {
    auto b = Boiler(10, 85, 2, 20, SteamProperties::ThermodynamicQuantity::ENTHALPY, 2000, 45);
    CHECK(b.getSteamProperties().energyFlow == Approx(110753.3647508802));
    CHECK(b.getFeedwaterProperties().massFlow == Approx(45.9183673469));
    CHECK(b.getFeedwaterProperties().energyFlow == Approx(64646.9770669091));
    CHECK(b.getBlowdownProperties().massFlow == Approx(0.9183673469));
    CHECK(b.getBlowdownProperties().energyFlow == Approx(1677.9495528531));
//    CHECK(b.getBlowdownProperties().at("quality") == Approx(0)); // Quality question: I have no idea if this is what the quality should actually be or not
    CHECK( b.getBoilerEnergy() == Approx(47784.3372368242));
    CHECK(b.getFuelEnergy() == Approx(56216.8673374402));

    auto b2 = Boiler(0.3631, 72.4, 3.7, 5.5766, SteamProperties::ThermodynamicQuantity::QUALITY, 1, 10864);
    CHECK(b2.getFuelEnergy() == Approx(33344279.4789710045));
}
