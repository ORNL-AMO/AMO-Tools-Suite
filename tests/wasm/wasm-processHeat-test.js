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
        testNumberValue(rnd(results.costSavings), rnd(expected[5]),"costSavings");
    };

    logMessage('Cascade Heat High To Low: Test# 1 Gas', true);
    let gasInstance = new Module.GasCompositions('Gas', 94.0, 2.07, 1.41, 0.01, 0.42, 0.28, 0.0, 1.0, 0.71, 0, 0);
    let instance = new Module.CascadeHeatHighToLow(gasInstance, 12.0, 1475, 0.07, 80.0, 8000, 1020, 225, 80, 7000, 5.00);
    validate(instance.calculate(), [174619.56, 4.6929, 6.4038, 7000, 44826.53, 224132.65]);
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

airHeatingUsingExhaust();
waterHeatingUsingExhaust();
waterHeatingUsingSteam();
cascadeHeatHighToLow();