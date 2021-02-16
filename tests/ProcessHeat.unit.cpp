#include "catch.hpp"
#include <calculator/processHeat/AirHeatingUsingExhaust.h>
#include <calculator/processHeat/WaterHeatingUsingExhaust.h>

TEST_CASE( "Estimate maximum air flow that can be heated by using exhaust gas", "[processHeat]" ) {
    GasCompositions gas("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    auto res = AirHeatingUsingExhaust(gas).calculate(400,0.358,8,4000,45,0.85,0.60,4000);
    CHECK(res.hxColdAir == Approx(197829.27));
    CHECK(res.hxOutletExhaust == Approx(187));
    CHECK(res.energySavings == Approx(930.96));
    CHECK(res.heatCapacityFlue == Approx(928.78));
    CHECK(res.heatCapacityAir == Approx(4464));

    SolidLiquidFlueGasMaterial coal("Coal", 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
    res = AirHeatingUsingExhaust(coal).calculate(400,0.358,8,4000,45,0.85,0.60,4000);
    CHECK(res.hxColdAir == Approx(15621.25));
    CHECK(res.hxOutletExhaust == Approx(187));
    CHECK(res.energySavings == Approx(73.512));
    CHECK(res.heatCapacityFlue == Approx(73.339));
    CHECK(res.heatCapacityAir == Approx(4464));


    auto resChillerAbsorpEnergy = WaterHeatingUsingExhaust().calculate(0.69, 6000000, 0.7, 190, 170, 0.73, 0.88, 5);
    CHECK(resChillerAbsorpEnergy.recoveredHeat == Approx(1302000));
    CHECK(resChillerAbsorpEnergy.hotWaterFlow == Approx(7810.437912));
    CHECK(resChillerAbsorpEnergy.tonsRefrigeration == Approx(79.205));
    CHECK(resChillerAbsorpEnergy.capacityChiller == Approx(69.7004));
    CHECK(resChillerAbsorpEnergy.electricalEnergy == Approx(167280.96));
}