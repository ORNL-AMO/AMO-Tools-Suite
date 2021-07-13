#include "catch.hpp"
#include <calculator/processHeat/AirHeatingUsingExhaust.h>
#include <calculator/processHeat/WaterHeatingUsingExhaust.h>
#include <calculator/processHeat/WaterHeatingUsingFlue.h>
#include <calculator/processHeat/WaterHeatingUsingSteam.h>
#include <calculator/processHeat/CascadeHeatHighToLow.h>

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


    GasCompositions gasCH("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    auto resCascadeHeatHighToLow = CascadeHeatHighToLow(gasCH, 12.0, 1074.82, 0.07, 299.82, 8000, 1020,
                                                        9.50, 380.37, 299.82, 7000, 5.00).calculate();
    CHECK(resCascadeHeatHighToLow.priFlueVolume == Approx(174956.62));
    CHECK(resCascadeHeatHighToLow.hxEnergyRate == Approx(2.6122));
    CHECK(resCascadeHeatHighToLow.eqEnergySupply == Approx(5.3248));
    CHECK(resCascadeHeatHighToLow.effOpHours == Approx(7000));
    CHECK(resCascadeHeatHighToLow.energySavings == Approx(37273.736));
    CHECK(resCascadeHeatHighToLow.costSavings == Approx(186368.68));
    CHECK(resCascadeHeatHighToLow.hourlySavings == Approx(5.3248));


    auto resSteamEnergy = WaterHeatingUsingSteam().calculate(0.1565, 340.2,285.93,0.5150, 2.7255,285.93, 0.2048,
                                                             0.72, 0.8, 7000);
    CHECK(resSteamEnergy.tempWaterOut == Approx(352.304));
    CHECK(resSteamEnergy.bpTempWaterOut == Approx(426.1));
    CHECK(resSteamEnergy.enthalpySteamIn == Approx(2695.04));
    CHECK(resSteamEnergy.enthalpySteamOut == Approx(472.5));
    CHECK(resSteamEnergy.enthalpyMakeUpWater == Approx(53.876));
    CHECK(resSteamEnergy.energySavedDWH == Approx(7351062329.1926));
    CHECK(resSteamEnergy.energySavedBoiler == Approx(1246124501.2457));
    CHECK(resSteamEnergy.waterSaved == Approx(2381.4 ));
    CHECK(resSteamEnergy.heatGainRate == Approx(756109.2681));

    resSteamEnergy = WaterHeatingUsingSteam().calculate(0.1703, 226.79,285.93,0.2737, 0.6814,285.93, 0.2048,
                                                        0.7, 0.7, 8000);
    CHECK(resSteamEnergy.tempWaterOut == Approx(388.75));
    CHECK(resSteamEnergy.bpTempWaterOut == Approx(403.57));
    CHECK(resSteamEnergy.enthalpySteamIn == Approx(2698.89));
    CHECK(resSteamEnergy.enthalpySteamOut == Approx(483.41));
    CHECK(resSteamEnergy.enthalpyMakeUpWater == Approx(53.876));
    CHECK(resSteamEnergy.flowByPassSteam == Approx(94.61));
    CHECK(resSteamEnergy.energySavedDWH == Approx(3346757808.4035));
    CHECK(resSteamEnergy.energySavedBoiler == Approx(648872153.14));
    CHECK(resSteamEnergy.waterSaved == Approx(1057.44));
    CHECK(resSteamEnergy.heatGainRate == Approx(292841.3082));



    GasCompositions gasFlue("Gas", 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    auto resFlueHeat = WaterHeatingUsingFlue().calculate(gasFlue, 658.15, 0.05, 299.82,
                                                         0.02, 55.88, 3.45, 288.71,
                                                         533.15, 380.37, 0.04, 0.625,
                                                         8000, 5.21, 37706, WaterHeatingUsingFlue::Superheated);
    CHECK(resFlueHeat.tempSteamSat == Approx(514.886));
    CHECK(resFlueHeat.flowFlueGas == Approx(23538.374));
    CHECK(resFlueHeat.effBoiler == Approx(0.734627));
    CHECK(resFlueHeat.enthalpySteam == Approx(2865.339));
    CHECK(resFlueHeat.enthalpyFW == Approx(452.038));
    CHECK(resFlueHeat.flowSteam == Approx(16329.899));
    CHECK(resFlueHeat.flowFW == Approx(16983.0949));
    CHECK(resFlueHeat.specheatFG == Approx(1.13247));
    CHECK(resFlueHeat.heatCapacityFG == Approx(26656.559));
    CHECK(resFlueHeat.specheatFW == Approx(4.2285));
    CHECK(resFlueHeat.heatCapacityFW == Approx(71812.936));
    CHECK(resFlueHeat.heatCapacityMin == Approx(26656.55));
    CHECK(resFlueHeat.ratingHeatRecFW == Approx(4627911.87));
    CHECK(resFlueHeat.tempFlueGasOut == Approx(484.537));
    CHECK(resFlueHeat.tempFWOut == Approx(444.818));
    CHECK(resFlueHeat.energySavingsBoiler == Approx(50397.36));
    CHECK(resFlueHeat.costSavingsBoiler == Approx(262570.24));
}