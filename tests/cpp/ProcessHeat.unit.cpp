#include "catch.hpp"
#include <calculator/processHeat/AirHeatingUsingExhaust.h>
#include <calculator/processHeat/WaterHeatingUsingExhaust.h>
#include <calculator/processHeat/WaterHeatingUsingFlue.h>
#include <calculator/processHeat/WaterHeatingUsingSteam.h>
#include <calculator/processHeat/CascadeHeatHighToLow.h>
#include <calculator/processHeat/AirWaterCoolingUsingFlue.h>

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
    auto resCascadeHeatHighToLow = CascadeHeatHighToLow(gasCH, 1020, 5.00,
                                                        12.0, 1475, 0.07, 80, 8000,
                                                        9.50, 225, 17.5, 80, 7000,
                                                        60, 60, 0).calculate();
    CHECK(resCascadeHeatHighToLow.priFlueVolume == Approx(175123.0293326335));
    CHECK(resCascadeHeatHighToLow.hxEnergyRate == Approx(4.2341865845));
    CHECK(resCascadeHeatHighToLow.eqEnergySupply == Approx(4.7235204084));
    CHECK(resCascadeHeatHighToLow.effOpHours == Approx(7000));
    CHECK(resCascadeHeatHighToLow.energySavings == Approx(33064.6428585547));
    CHECK(resCascadeHeatHighToLow.costSavings == Approx(165323.2142927737));
    CHECK(resCascadeHeatHighToLow.hourlySavings == Approx(4.7235204084));
    CHECK(resCascadeHeatHighToLow.priExcessAir == Approx(0.4519750365));
    CHECK(resCascadeHeatHighToLow.priAvailableHeat == Approx(0.4724916999));
    CHECK(resCascadeHeatHighToLow.secExcessAir == Approx(-1.05775222));
    CHECK(resCascadeHeatHighToLow.secAvailableHeat == Approx(0.896416));


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
    auto resFlueHeat = WaterHeatingUsingFlue().calculate(gasFlue, 725, 0.05, 80,
                                                         0.02, 55.88, 3.45, 60,
                                                         500, 225, 0.04, 0.625,
                                                         8000, 5.21, 37706, WaterHeatingUsingFlue::Superheated, 60);
    CHECK(resFlueHeat.flowFlueGas == Approx(23658.1596137958));
    CHECK(resFlueHeat.effBoiler == Approx(0.7193913738));
    CHECK(resFlueHeat.enthalpySteam == Approx(2865.339));
    CHECK(resFlueHeat.enthalpyFW == Approx(452.0478));
    CHECK(resFlueHeat.flowSteam == Approx(15991.2762656448));
    CHECK(resFlueHeat.flowFW == Approx(16630.9273162706));
    CHECK(resFlueHeat.specheatFG == Approx(1.1319998535));
    CHECK(resFlueHeat.heatCapacityFG == Approx(26781.0332157512));
    CHECK(resFlueHeat.specheatFW == Approx(4.2285));
    CHECK(resFlueHeat.heatCapacityFW == Approx(70323.6515387818));
    CHECK(resFlueHeat.heatCapacityMin == Approx(26781.0332157512));
    CHECK(resFlueHeat.ratingHeatRecFW == Approx(4649484.9332901333));
    CHECK(resFlueHeat.tempFlueGasOut == Approx(484.537));
    CHECK(resFlueHeat.tempFWOut == Approx(446.4877442629));
    CHECK(resFlueHeat.energySavingsBoiler == Approx(51704.6503757363));
    CHECK(resFlueHeat.costSavingsBoiler == Approx(269381.2284575859));

    GasCompositions gasFlueCond("Gas", 94.1, 3.02, 1.41, 0.01, 0.42, 0.28, 0.0, 0.0, 0.7, 0, 0.01);
    auto resHeatRecovery = AirWaterCoolingUsingFlue().calculate(gasFlueCond, 116, 300, 125,
                                                                70, 60, 0.04, 60, 0);
    CHECK(resHeatRecovery.excessAir == Approx(0.2169692841));
    CHECK(resHeatRecovery.flowFlueGas == Approx(107022.7016052115));
    CHECK(resHeatRecovery.specHeat == Approx(0.2577908474));
    CHECK(resHeatRecovery.fracCondensed == Approx(0.19816));
    CHECK(resHeatRecovery.effThermal == Approx(0.8443608099));
    CHECK(resHeatRecovery.effThermalLH == Approx(0.8645004409));
    CHECK(resHeatRecovery.effLH == Approx(0.02014));
    CHECK(resHeatRecovery.heatRecovery == Approx(2.3362));
    CHECK(resHeatRecovery.sensibleHeatRecovery == Approx(4.8281577633));
}