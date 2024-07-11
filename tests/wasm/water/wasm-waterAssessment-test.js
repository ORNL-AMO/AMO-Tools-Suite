function calculateProcessWaterUse(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.recirculatedWater), rnd(expected[0]), "recirculatedWater");
        testNumberValue(rnd(results.incomingWater), rnd(expected[1]), "incomingWater");
        testNumberValue(rnd(results.wasteDischargedAndRecycledOther), rnd(expected[2]), "wasteDischargedAndRecycledOther");
    };

    logMessage('Water Assessment Calculate ProcessWaterUse:', true);
    let instance = new Module.WaterAssessment();
    validate(instance.calculateProcessWaterUse(1000, 700, 50, 0.2), [200, 800, 50]);

    instance.delete();
}

function calculateCoolingTowerLoss(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.grossWaterUse), rnd(expected[0]), "grossWaterUse");
        testNumberValue(rnd(results.evaporationLoss), rnd(expected[1]), "evaporationLoss");
        testNumberValue(rnd(results.cycleOfConcentration), rnd(expected[2]), "cycleOfConcentration");
        testNumberValue(rnd(results.makeupWater), rnd(expected[3]), "makeupWater");
        testNumberValue(rnd(results.blowdownLoss), rnd(expected[4]), "blowdownLoss");
    };

    logMessage('Water Assessment Calculate CoolingTowerLoss:', true);
    let instance = new Module.WaterAssessment();
    validate(instance.calculateCoolingTowerLoss(2000, 5, 0.2, 0.2, 10, 5, 15), [360000, 72000, 3, 108000, 36000]);

    instance.delete();
}

function calculateBoilerWaterLosses(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.cycleOfConcentration), rnd(expected[0]), "cycleOfConcentration");
        testNumberValue(rnd(results.grossWaterUse), rnd(expected[1]), "grossWaterUse");
        testNumberValue(rnd(results.makeupWater), rnd(expected[2]), "makeupWater");
        testNumberValue(rnd(results.steamLoss), rnd(expected[3]), "steamLoss");
        testNumberValue(rnd(results.blowdownLoss), rnd(expected[4]), "blowdownLoss");
        testNumberValue(rnd(results.condensateReturn), rnd(expected[5]), "condensateReturn");
        testNumberValue(rnd(results.rateOfRecirculation), rnd(expected[6]), "rateOfRecirculation");
    };

    logMessage('Water Assessment Calculate BoilerWaterLosses:', true);
    let instance = new Module.WaterAssessment();
    validate(instance.calculateBoilerWaterLosses(2000, 5, 0.2, 0.2, 2.5, 5, 15), [6, 57.6, 28.8, 19.2, 9.6, 28.8, 0.5]);

    instance.delete();
}

function calculateKitchenRestroomGrossWaterUse(){
    logMessage('Water Assessment Calculate KitchenRestroomGrossWaterUse:', true);
    let instance = new Module.WaterAssessment();
    testNumberValue(instance.calculateKitchenRestroomGrossWaterUse(50, 260, 3), 39000, "grossWaterUse");
    instance.delete();
}

function calculateLandscapingGrossWaterUse(){
    logMessage('Water Assessment Calculate LandscapingGrossWaterUse:', true);
    let instance = new Module.WaterAssessment();
    testNumberValue(instance.calculateLandscapingGrossWaterUse(50, 60), 3000, "grossWaterUse");
    instance.delete();
}

function calculateHeatEnergyInDischarge(){
    logMessage('Water Assessment Calculate HeatEnergyInDischarge:', true);
    let instance = new Module.WaterAssessment();
    testNumberValue(instance.calculateHeatEnergyInDischarge(50, 60, 0.8, 200), 0.01335, "heatEnergyUseInDischarge");
    instance.delete();
}

function calculateAddedMotorEnergyUse(){
    logMessage('Water Assessment Calculate AddedMotorEnergyUse:', true);
    let instance = new Module.WaterAssessment();
    testNumberValue(instance.calculateAddedMotorEnergyUse(50, 2000, 100, 0.8, 0.75), 10666666.66666, "energyUse");
    instance.delete();
}

calculateProcessWaterUse();
calculateCoolingTowerLoss();
calculateBoilerWaterLosses();
calculateKitchenRestroomGrossWaterUse();
calculateLandscapingGrossWaterUse();
calculateHeatEnergyInDischarge();
calculateAddedMotorEnergyUse();