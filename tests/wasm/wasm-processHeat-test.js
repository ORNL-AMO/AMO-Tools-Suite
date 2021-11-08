function airHeatingUsingExhaust(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.hxColdAir), rnd(expected[0]), "hxColdAir");
        testNumberValue(rnd(results.hxOutletExhaust), rnd(expected[1]), "hxOutletExhaust");
        testNumberValue(rnd(results.energySavings), rnd(expected[2]), "energySavings");
        testNumberValue(rnd(results.heatCapacityFlue), rnd(expected[3]),"heatCapacityFlue");
        testNumberValue(rnd(results.heatCapacityAir), rnd(expected[4]),"heatCapacityAir");
    };

    logMessage('Air Heating Using Exhaust: Test# 1 Gas', true);
    let gasInstance = new Module.GasCompositions('Gas', 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    let instance = new Module.AirHeatingUsingExhaust(gasInstance);
    validate(instance.calculate(400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000), [197829.27, 187, 930.96, 928.78, 4464]);
    instance.delete();
    gasInstance.delete();

    logMessage('Air Heating Using Exhaust: Test# 1 Coal', true);
    let coalInstance = new Module.SolidLiquidFlueGasMaterial('Coal', 75.0, 5.0, 1.00, 9.0, 7.0, 0.0, 1.5);
    let instanceSolid = new Module.AirHeatingUsingExhaust(coalInstance, true);
    validate(instanceSolid.calculate(400, 0.358, 8, 4000, 45, 0.85, 0.60, 4000), [15621.25, 187, 73.512, 73.339, 4464]);
    instanceSolid.delete();
    coalInstance.delete();
}

function cascadeHeatHighToLow(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.priFlueVolume), rnd(expected[0]), "priFlueVolume");
        testNumberValue(rnd(results.hxEnergyRate), rnd(expected[1]), "hxEnergyRate");
        testNumberValue(rnd(results.eqEnergySupply), rnd(expected[2]), "eqEnergySupply");
        testNumberValue(rnd(results.effOpHours), rnd(expected[3]),"effOpHours");
        testNumberValue(rnd(results.energySavings), rnd(expected[4]),"energySavings");
        testNumberValue(rnd(results.costSavings), rnd(expected[5]),"costSavings")
        testNumberValue(rnd(results.hourlySavings), rnd(expected[6]),"hourlySavings")
        testNumberValue(rnd(results.priExcessAir), rnd(expected[7]),"priExcessAir")
        testNumberValue(rnd(results.priAvailableHeat), rnd(expected[8]),"priAvailableHeat")
        testNumberValue(rnd(results.secExcessAir), rnd(expected[9]),"secExcessAir")
        testNumberValue(rnd(results.secAvailableHeat), rnd(expected[10]),"secAvailableHeat");
    };

    logMessage('Cascade Heat High To Low: Test# 1 Gas', true);
    let gasInstance = new Module.GasCompositions('Gas', 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    let instance = new Module.CascadeHeatHighToLow(gasInstance, 1020, 5.00, 12.0, 1475, 0.07, 80, 8000, 9.50, 225, 17.5, 80, 7000, 60, 60, 0);
    validate(instance.calculate(), [174956.62, 4.22636, 4.71, 7000, 33003.13, 165015.65, 4.71, 0.4505, 0.47287, -1.06, 0.9]);
    instance.delete();
    gasInstance.delete();
}

function waterHeatingUsingExhaust(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.recoveredHeat), rnd(expected[0]), "recoveredHeat");
        testNumberValue(rnd(results.hotWaterFlow), rnd(expected[1]), "hotWaterFlow");
        testNumberValue(rnd(results.tonsRefrigeration), rnd(expected[2]), "tonsRefrigeration");
        testNumberValue(rnd(results.capacityChiller), rnd(expected[3]),"capacityChiller");
        testNumberValue(rnd(results.electricalEnergy), rnd(expected[4]),"electricalEnergy");
    };

    logMessage('Water Heating Using Exhaust Chiller Absorption: Test# 1', true);
    let instance = new Module.WaterHeatingUsingExhaust();
    validate(instance.calculate(0.69, 6000000, 0.7, 190, 170, 0.73, 0.88, 5), [1302000, 7810.437912, 79.205, 69.7004, 167280.96]);
    instance.delete();
}

function waterHeatingUsingSteam(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.tempWaterOut), rnd(expected[0]), "tempWaterOut");
        testNumberValue(rnd(results.bpTempWaterOut), rnd(expected[1]), "bpTempWaterOut");
        testNumberValue(rnd(results.enthalpySteamIn), rnd(expected[2]), "enthalpySteamIn");
        testNumberValue(rnd(results.enthalpySteamOut), rnd(expected[3]),"enthalpySteamOut");
        testNumberValue(rnd(results.enthalpyMakeUpWater), rnd(expected[4]),"enthalpyMakeUpWater");
        testNumberValue(rnd(results.flowByPassSteam), rnd(expected[5]),"flowByPassSteam");
        testNumberValue(rnd(results.energySavedDWH), rnd(expected[6]),"energySavedDWH");
        testNumberValue(rnd(results.energySavedBoiler), rnd(expected[7]),"energySavedBoiler");
        testNumberValue(rnd(results.waterSaved), rnd(expected[8]),"waterSaved");
        testNumberValue(rnd(results.heatGainRate), rnd(expected[9]),"heatGainRate");

        logMessage('bpTempWarningFlag : ' + results.bpTempWarningFlag);
    };

    let instance = new Module.WaterHeatingUsingSteam();

    logMessage('Water Heating Using Steam Heat Exchanger: Test# 1', true);
    validate(instance.calculate(0.1565, 340.2, 285.93, 0.5150, 2.7255, 285.93, 0.2048, 0.72, 0.8, 7000),
        [352.304, 426.1, 2695.04, 472.5, 53.876, 0,
            7351062329.1926, 1246124501.2457, 2381.4, 756109.2681]);

    logMessage('Water Heating Using Steam Heat Exchanger: Test# 2', true);
    validate(instance.calculate(0.1703, 226.79, 285.93, 0.2737, 0.6814, 285.93, 0.2048, 0.7, 0.7, 8000),
        [388.75, 403.57, 2698.89, 483.41, 53.876, 94.61,
            3346757808.4035, 648872153.14, 1057.44, 292841.3082]);
    instance.delete();
}

function waterHeatingUsingFlue(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.flowFlueGas), rnd(expected[0]), "flowFlueGas");
        testNumberValue(rnd(results.effBoiler), rnd(expected[1]), "effBoiler");
        testNumberValue(rnd(results.enthalpySteam), rnd(expected[2]),"enthalpySteam");
        testNumberValue(rnd(results.enthalpyFW), rnd(expected[3]),"enthalpyFW");
        testNumberValue(rnd(results.flowSteam), rnd(expected[4]),"flowSteam");
        testNumberValue(rnd(results.flowFW), rnd(expected[5]), "flowFW");
        testNumberValue(rnd(results.specheatFG), rnd(expected[6]), "specheatFG");
        testNumberValue(rnd(results.heatCapacityFG), rnd(expected[7]), "heatCapacityFG");
        testNumberValue(rnd(results.specheatFW), rnd(expected[8]),"specheatFW");
        testNumberValue(rnd(results.heatCapacityFW), rnd(expected[9]),"heatCapacityFW");
        testNumberValue(rnd(results.heatCapacityMin), rnd(expected[10]),"heatCapacityMin");
        testNumberValue(rnd(results.ratingHeatRecFW), rnd(expected[11]), "ratingHeatRecFW");
        testNumberValue(rnd(results.tempFlueGasOut), rnd(expected[12]), "tempFlueGasOut");
        testNumberValue(rnd(results.tempFWOut), rnd(expected[13]),"tempFWOut");
        testNumberValue(rnd(results.energySavingsBoiler), rnd(expected[14]),"energySavingsBoiler");
        testNumberValue(rnd(results.costSavingsBoiler), rnd(expected[15]),"costSavingsBoiler");
    };

    logMessage('Water Heating Using Flue: Test# 1 Gas', true);
    let gasInstance = new Module.GasCompositions('Gas', 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    let instance = new Module.WaterHeatingUsingFlue();
    let results = instance.calculate(gasInstance, 725, 0.05, 80, 0.02, 55.88, 3.45, 60, 500,
        225, 0.04, 0.625, 8000, 5.21, 37706, Module.SteamConditionType.Superheated, 60);
    validate(results, [23637.68, 0.72023, 2865.339, 452.0478, 15994.47,
        16634.25, 1.13247, 26759.76, 4.2285, 70337.7, 26759.76, 4645791.13, 484.537, 446.42, 51653.25, 269113.45]);
    instance.delete();
    gasInstance.delete();
}

function airWaterCoolingUsingFlue(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.excessAir), rnd(expected[0]), "excessAir");
        testNumberValue(rnd(results.flowFlueGas), rnd(expected[1]), "flowFlueGas");
        testNumberValue(rnd(results.specHeat), rnd(expected[2]),"specHeat");
        testNumberValue(rnd(results.fracCondensed), rnd(expected[3]),"fracCondensed");
        testNumberValue(rnd(results.effThermal), rnd(expected[4]), "effThermal");
        testNumberValue(rnd(results.effThermalLH), rnd(expected[5]), "effThermalLH");
        testNumberValue(rnd(results.effLH), rnd(expected[6]),"effLH");
        testNumberValue(rnd(results.heatRecovery), rnd(expected[7]),"heatRecovery");
        testNumberValue(rnd(results.sensibleHeatRecovery), rnd(expected[8]),"sensibleHeatRecovery");
    };

    logMessage('Air Water Cooling Using Flue: Test# 1', true);
    let gasInstance = new Module.GasCompositions('Gas', 94.1, 3.02, 1.41, 0.01, 0.42, 0.28, 0.0, 0.0, 0.7, 0, 0.01);
    let instance = new Module.AirWaterCoolingUsingFlue();
    let results = instance.calculate(gasInstance, 116, 300, 125, 70, 60, 0.04, 60, 0);
    validate(results, [0.21596, 107119.17, 0.2578, 0.19816, 0.8444, 0.86454, 0.02014, 2.3362, 4.83]);
    instance.delete();
    gasInstance.delete();
}

airHeatingUsingExhaust();
waterHeatingUsingExhaust();
waterHeatingUsingSteam();
cascadeHeatHighToLow();
waterHeatingUsingFlue();
airWaterCoolingUsingFlue();