const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'chillers' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 4) + 'e-' + 4);
}

test('coolingTowerMakeupWater', function (t) {
    t.plan(10);
    t.type(bindings.coolingTowerMakeupWater, 'function');

    // Test 1
    var inp = {
        coolingTowerMakeupWaterCalculator: {
            operatingConditionsData: {
                flowRate: 2500,
			    coolingLoad: 10.00,
			    operationalHours: 1000,
			    lossCorrectionFactor: 1.00
            },
            waterConservationBaselineData: {
                cyclesOfConcentration: 3,
                driftLossFactor: 0.002
            },
            waterConservationModificationData: {
                cyclesOfConcentration: 3,
                driftLossFactor: 0.0001
            }
        }
    };
    
    var res = bindings.coolingTowerMakeupWater(inp);
    t.equal(rnd(res.wcBaseline), rnd(2100000), 'res.wcBaseline is ' + res.wcBaseline);
    t.equal(rnd(res.wcModification), rnd(1815000), 'res.wcModification is ' + res.wcModification);
    t.equal(rnd(res.waterSavings), rnd(285000), 'res.waterSavings is ' + res.waterSavings);
    
    // Test 2
    inp = {
        coolingTowerMakeupWaterCalculator: {
            operatingConditionsData: {
                flowRate: 2500,
			    coolingLoad: 5.00,
			    operationalHours: 2000,
			    lossCorrectionFactor: 1.00
            },
            waterConservationBaselineData: {
                cyclesOfConcentration: 3,
                driftLossFactor: 0.002
            },
            waterConservationModificationData: {
                cyclesOfConcentration: 3,
                driftLossFactor: 0.0001
            }
        }
    };
    res = bindings.coolingTowerMakeupWater(inp);
    t.equal(rnd(res.wcBaseline), rnd(2400000), 'res.wcBaseline is ' + res.wcBaseline);
    t.equal(rnd(res.wcModification), rnd(1830000), 'res.wcModification is ' + res.wcModification);
    t.equal(rnd(res.waterSavings), rnd(570000), 'res.waterSavings is ' + res.waterSavings);

    // Test 3
    inp = {
        coolingTowerMakeupWaterCalculator: {
            operatingConditionsData: {
                flowRate: 2500,
			    coolingLoad: 2.00,
			    operationalHours: 3000,
			    lossCorrectionFactor: 1.00
            },
            waterConservationBaselineData: {
                cyclesOfConcentration: 3,
                driftLossFactor: 0.002
            },
            waterConservationModificationData: {
                cyclesOfConcentration: 3,
                driftLossFactor: 0.0001
            }
        }
    };
    res = bindings.coolingTowerMakeupWater(inp);
    t.equal(rnd(res.wcBaseline), rnd(1980000), 'res.wcBaseline is ' + res.wcBaseline);
    t.equal(rnd(res.wcModification), rnd(1125000), 'res.wcModification is ' + res.wcModification);
    t.equal(rnd(res.waterSavings), rnd(855000), 'res.waterSavings is ' + res.waterSavings);
});


test('CoolingTower BasinHeaterEnergyConsumption', function (t) {
    t.plan(6);
    t.type(bindings.coolingTowerBasinHeaterEnergyConsumption, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.baselinePower), rnd(expected[0]));
        t.equal(rnd(results.baselineEnergy), rnd(expected[1]));
        t.equal(rnd(results.modPower), rnd(expected[2]));
        t.equal(rnd(results.modEnergy), rnd(expected[3]));
        t.equal(rnd(results.savingsEnergy), rnd(expected[4]));
    };

    var input = {
        ratedCapacity: 1201.67,
        ratedTempSetPoint: 40,
        ratedTempDryBulb: -10,
        ratedWindSpeed: 45,

        operatingTempDryBulb: 28,
        operatingWindSpeed: 9.21,
        operatingHours: 1,

        baselineTempSetPoint: 40,
        modTempSetPoint:39
    };

    compare(bindings.coolingTowerBasinHeaterEnergyConsumption(input), [3.0743, 3.0743, 2.761026, 2.761026, 0.313274]);
});

test('CoolingTower FanEnergyConsumption', function (t) {
    t.plan(11);
    t.type(bindings.coolingTowerFanEnergyConsumption, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.baselinePower), rnd(expected[0]));
        t.equal(rnd(results.baselineEnergy), rnd(expected[1]));
        t.equal(rnd(results.modPower), rnd(expected[2]));
        t.equal(rnd(results.modEnergy), rnd(expected[3]));
        t.equal(rnd(results.savingsEnergy), rnd(expected[4]));
    };

    var input = {
        ratedFanPower: 59.5119,

        waterLeavingTemp: 81.6495,
        waterEnteringTemp: 87.98386,
        operatingTempWetBulb: 76,
        operatingHours: 1,

        baselineSpeedType: 0,
        modSpeedType:1
    };

    compare(bindings.coolingTowerFanEnergyConsumption(input), [55.149962, 41.141872, 50.503133, 37.675337, 3.466535]);

    input.modSpeedType = 2;
    compare(bindings.coolingTowerFanEnergyConsumption(input), [55.149962, 41.141872, 44.789615, 33.413053, 7.728819]);
});

test('ChillerEfficiency CapacityEnergyConsumption', function (t) {
    t.plan(55);
    t.type(bindings.chillerCapacityEfficiency, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.baselineActualEfficiency), rnd(expected[0]));
        t.equal(rnd(results.baselineActualCapacity), rnd(expected[1]));
        t.equal(rnd(results.baselinePower), rnd(expected[2]));
        t.equal(rnd(results.baselineEnergy), rnd(expected[3]));
        t.equal(rnd(results.modActualEfficiency), rnd(expected[4]));
        t.equal(rnd(results.modActualCapacity), rnd(expected[5]));
        t.equal(rnd(results.modPower), rnd(expected[6]));
        t.equal(rnd(results.modEnergy), rnd(expected[7]));
        t.equal(rnd(results.savingsEnergy), rnd(expected[8]));
    };

    var input = {
        chillerType: 0,
        condenserCoolingType: 0,
        compressorConfigType: 0,

        ariCapacity: 1000,
        ariEfficiency: 0.676,
        maxCapacityRatio: 1.0,

        operatingHours: 1.0,
        waterFlowRate: 2000,
        waterDeltaT: 10,

        baselineWaterSupplyTemp: 42,
        baselineWaterEnteringTemp: 82.12,
        modWaterSupplyTemp:43,
        modWaterEnteringTemp:82.12
    };
    compare(bindings.chillerCapacityEfficiency(input), [0.552199,995.546437,549.740164,549.740164,0.526177,1033.117955,543.60299,543.60299,6.137174]);

    input.compressorConfigType = 1;
    compare(bindings.chillerCapacityEfficiency(input), [0.50594,1017.8465,514.9762,514.9762,0.477184,1038.2663,495.4494,495.4494,19.5268]);

    input.compressorConfigType = 2;
    compare(bindings.chillerCapacityEfficiency(input), [0.5335,985.4549,525.74132,525.74132,0.486282,1047.968,509.608,509.608,16.13328]);

    input.chillerType = 1;
    input.compressorConfigType = 0;
    compare(bindings.chillerCapacityEfficiency(input), [0.5899,963.0877,568.13317,568.13317,0.56246,1000.57839,562.7885,562.7885,5.34465]);

    input.condenserCoolingType =  1;
    compare(bindings.chillerCapacityEfficiency(input), [0.47777,1050.0458,501.67899,501.67899,0.4604,1081.77855,498.0641,498.0641,3.61489]);

    input.chillerType = 0;
    compare(bindings.chillerCapacityEfficiency(input), [0.442926,1130.9202,500.91377,500.91377,0.4285,1168.492,500.7157,500.7157,0.19807]);
});

test('ChillerEfficiency Staging', function (t) {
    t.plan(12);
    t.type(bindings.chillerStaging, 'function');

    var compare = function(results, expected, baselinePowerList, modPowerList) {
        t.equal(rnd(results.baselineTotalPower), rnd(expected[0]));
        t.equal(rnd(results.baselineTotalEnergy), rnd(expected[1]));
        t.equal(rnd(results.modTotalPower), rnd(expected[2]));
        t.equal(rnd(results.modTotalEnergy), rnd(expected[3]));
        t.equal(rnd(results.savingsEnergy), rnd(expected[4]));

        for (var i = 0; i < baselinePowerList.length; i++) {
            t.equal(rnd(results.baselinePowerList[i]), baselinePowerList[i]);
            t.equal(rnd(results.modPowerList[i]), modPowerList[i]);
        }
    };

    var input = {
        chillerType: 0,
        condenserCoolingType: 0,
        compressorConfigType: 1,

        ariCapacity: 1000,
        ariEfficiency: 0.676,
        maxCapacityRatio: 1.0,

        operatingHours: 1.0,
        waterSupplyTemp: 42,
        waterEnteringTemp: 82.12,

        baselineLoadList: [300, 300, 300],
        modLoadList: [450, 450, 0]
    };

    compare(bindings.chillerStaging(input), [820.5018,820.5018,603.9089,603.9089,216.5928], [273.5006,273.5006,273.5006], [301.9545,301.9545,0]);
});