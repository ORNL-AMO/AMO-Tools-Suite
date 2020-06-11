const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'chillers' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
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