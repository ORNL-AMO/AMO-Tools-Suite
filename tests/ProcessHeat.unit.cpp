#include "catch.hpp"
#include <calculator/processHeat/AirHeatingUsingExhaust.h>

TEST_CASE( "Estimate maximum air flow that can be heated by using exhaust gas", "[processHeat]" ) {
    GasCompositions gas("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    auto res = AirHeatingUsingExhaust(gas).calculate(400,35.8,8,4000,45,85,60,24);
    CHECK(res.hxColdAir == Approx(95083200));
    CHECK(res.hxOutletExhaust == Approx(272.86));
    CHECK(res.energySavings == Approx(26.847));

    SolidLiquidFlueGasMaterial coal("Coal", 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
    res = AirHeatingUsingExhaust(coal).calculate(400,35.8,8,4000,45,85,60,24);
    CHECK(res.hxColdAir == Approx(95083200));
    CHECK(res.hxOutletExhaust == Approx(-1200.659));
    CHECK(res.energySavings == Approx(26.847));
}