const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'processHeat'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 2) + 'e-' + 2);
}

test('AirHeatingUsingExhaust Gas', function (t) {
    t.plan(6);
    t.type(bindings.airHeatingUsingExhaust, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.hxColdAir), rnd(expected[0]));
        t.equal(rnd(results.hxOutletExhaust), rnd(expected[1]));
        t.equal(rnd(results.energySavings), rnd(expected[2]));
        t.equal(rnd(results.heatCapacityFlue), rnd(expected[3]));
        t.equal(rnd(results.heatCapacityAir), rnd(expected[4]));
    };

    var input = {
        flueTemperature: 400,
        excessAir: 0.358,
        fireRate: 8,
        airflow: 4000,
        inletTemperature: 45,
        heaterEfficiency: 0.85,
        hxEfficiency: 0.60,
        operatingHours: 4000,

        gasFuelType: true,
        substance: 'Gas',
        CH4: 94.0,
        C2H6: 2.07,
        N2: 1.41,
        H2: 0.01,
        C3H8: 0.42,
        C4H10_CnH2n: 0.28,
        H2O: 0.0,
        CO: 1.0,
        CO2: 0.71,
        SO2: 0,
        O2: 0
    };

    compare(bindings.airHeatingUsingExhaust(input), [197829.27, 187, 930.96, 928.78, 4464]);
});

test('AirHeatingUsingExhaust Coal', function (t) {
    t.plan(6);
    t.type(bindings.airHeatingUsingExhaust, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.hxColdAir), rnd(expected[0]));
        t.equal(rnd(results.hxOutletExhaust), rnd(expected[1]));
        t.equal(rnd(results.energySavings), rnd(expected[2]));
        t.equal(rnd(results.heatCapacityFlue), rnd(expected[3]));
        t.equal(rnd(results.heatCapacityAir), rnd(expected[4]));
    };

    var input = {
        flueTemperature: 400,
        excessAir: 0.358,
        fireRate: 8,
        airflow: 4000,
        inletTemperature: 45,
        heaterEfficiency: 0.85,
        hxEfficiency: 0.60,
        operatingHours: 4000,

        gasFuelType: false,
        substance: 'Coal',
        carbon: 75.0,
        hydrogen: 5.0,
        sulphur: 1.00,
        inertAsh: 9.0,
        o2: 7.0,
        moisture: 0.0,
        nitrogen: 1.5
    };

    compare(bindings.airHeatingUsingExhaust(input), [15621.25, 187, 73.512, 73.339, 4464]);
});

test('WaterHeatingUsingExhaust ChillerAbsorption', function (t) {
    t.plan(6);
    t.type(bindings.waterHeatingUsingExhaust, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.recoveredHeat), rnd(expected[0]));
        t.equal(rnd(results.hotWaterFlow), rnd(expected[1]));
        t.equal(rnd(results.tonsRefrigeration), rnd(expected[2]));
        t.equal(rnd(results.capacityChiller), rnd(expected[3]));
        t.equal(rnd(results.electricalEnergy), rnd(expected[4]));
    };

    var input = {
        availableHeat: 0.69,
        heatInput: 6000000,
        hxEfficiency: 0.7,
        chillerInTemperature: 190,
        chillerOutTemperature: 170,
        copChiller: 0.73,
        chillerEfficiency: 0.88,
        copCompressor: 5
    };

    compare(bindings.waterHeatingUsingExhaust(input), [1302000, 7810.437912, 79.205, 69.7004, 167280.96]);
});

test('WaterHeatingUsingSteam HeatExchanger', function (t) {
    t.plan(21);
    t.type(bindings.waterHeatingUsingSteam, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.tempWaterOut), rnd(expected[0]));
        t.equal(rnd(results.bpTempWaterOut), rnd(expected[1]));
        t.equal(rnd(results.enthalpySteamIn), rnd(expected[2]));
        t.equal(rnd(results.enthalpySteamOut), rnd(expected[3]));
        t.equal(rnd(results.enthalpyMakeUpWater), rnd(expected[4]));
        t.equal(rnd(results.flowByPassSteam), rnd(expected[5]));
        t.equal(rnd(results.energySavedDWH), rnd(expected[6]));
        t.equal(rnd(results.energySavedBoiler), rnd(expected[7]));
        t.equal(rnd(results.waterSaved), rnd(expected[8]));
        t.equal(rnd(results.heatGainRate), rnd(expected[9]));
    };


    var input = {
        pressureSteamIn: 0.1565,
        flowSteamRate: 340.2,
        temperatureWaterIn: 285.93,
        pressureWaterOut: 0.5150,
        flowWaterRate: 2.7255,
        tempMakeupWater: 285.93,
        presMakeupWater: 0.2048,
        effWaterHeater: 0.72,
        effBoiler: 0.8,
        operatingHours: 7000
    };
    compare(bindings.waterHeatingUsingSteam(input), [352.304, 426.1, 2695.04, 472.5, 53.876, 0,
        7351062329.1926, 1246124501.2457, 2381.4, 756109.2681]);

    input = {
        pressureSteamIn: 0.1703,
        flowSteamRate: 226.79,
        temperatureWaterIn: 285.93,
        pressureWaterOut: 0.2737,
        flowWaterRate: 0.6814,
        tempMakeupWater: 285.93,
        presMakeupWater: 0.2048,
        effWaterHeater: 0.7,
        effBoiler: 0.7,
        operatingHours: 8000
    };
    compare(bindings.waterHeatingUsingSteam(input), [388.75, 403.57, 2698.89, 483.41, 53.876, 94.61,
        3346757808.4035, 648872153.14, 1057.44, 292841.3082]);
});

test('CascadeHeatHighToLow Gas', function (t) {
    t.plan(7);
    t.type(bindings.cascadeHeatHighToLow, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.priFlueVolume), rnd(expected[0]));
        t.equal(rnd(results.hxEnergyRate), rnd(expected[1]));
        t.equal(rnd(results.eqEnergySupply), rnd(expected[2]));
        t.equal(rnd(results.effOpHours), rnd(expected[3]));
        t.equal(rnd(results.energySavings), rnd(expected[4]));
        t.equal(rnd(results.costSavings), rnd(expected[5]));
    };

    var input = {
        priFiringRate: 12.0,
        priExhaustTemperature: 1074.82,
        priExhaustO2: 0.07,
        priCombAirTemperature: 299.82,
        priOpHours: 8000,
        priFuelHV: 1020,

        secFiringRate: 9.50,
        secExhaustTemperature: 380.37,
        secCombAirTemperature: 299.82,
        secOpHours: 7000,
        secFuelCost: 5.00,

        gasFuelType: true,
        substance: 'Gas',
        CH4: 94.0,
        C2H6: 2.07,
        N2: 1.41,
        H2: 0.01,
        C3H8: 0.42,
        C4H10_CnH2n: 0.28,
        H2O: 0.0,
        CO: 1.0,
        CO2: 0.71,
        SO2: 0,
        O2: 0
    };

    compare(bindings.cascadeHeatHighToLow(input), [174956.62, 2.6122, 5.3238, 7000, 37273.74, 186368.68, 5.3238]);
});

test('WaterHeatingUsingFlue Gas', function (t) {
    t.plan(17);
    t.type(bindings.waterHeatingUsingFlue, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.flowFlueGas), rnd(expected[0]));
        t.equal(rnd(results.effBoiler), rnd(expected[1]));
        t.equal(rnd(results.enthalpySteam), rnd(expected[2]));
        t.equal(rnd(results.enthalpyFW), rnd(expected[3]));
        t.equal(rnd(results.flowSteam), rnd(expected[4]));
        t.equal(rnd(results.flowFW), rnd(expected[5]));
        t.equal(rnd(results.specheatFG), rnd(expected[6]));
        t.equal(rnd(results.heatCapacityFG), rnd(expected[7]));
        t.equal(rnd(results.specheatFW), rnd(expected[8]));
        t.equal(rnd(results.heatCapacityFW), rnd(expected[9]));
        t.equal(rnd(results.heatCapacityMin), rnd(expected[10]));
        t.equal(rnd(results.ratingHeatRecFW), rnd(expected[11]));
        t.equal(rnd(results.tempFlueGasOut), rnd(expected[12]));
        t.equal(rnd(results.tempFWOut), rnd(expected[13]));
        t.equal(rnd(results.energySavingsBoiler), rnd(expected[14]));
        t.equal(rnd(results.costSavingsBoiler), rnd(expected[15]));
    };

    var input = {
        tempFlueGas: 658.15,
        percO2: 0.05,
        tempCombAir: 299.82,
        moistCombAir: 0.02,
        ratingBoiler: 55.88,
        prSteam: 3.45,
        tempAmbientAir: 288.71,
        tempSteam: 533.15,
        tempFW: 380.37,
        percBlowDown: 0.04,
        effHX: 0.625,
        opHours: 8000,
        costFuel: 5.21,
        hhvFuel: 37706,
        condSteam: 0,

        gasFuelType: true,
        substance: 'Gas',
        CH4: 94.0,
        C2H6: 2.07,
        N2: 1.41,
        H2: 0.01,
        C3H8: 0.42,
        C4H10_CnH2n: 0.28,
        H2O: 0.0,
        CO: 1.0,
        CO2: 0.71,
        SO2: 0,
        O2: 0
    };

    compare(bindings.waterHeatingUsingFlue(input), [23538.374, 0.73457, 2865.339, 452.038, 16329.9,
        16983.09, 1.13247, 26656.559, 4.2285, 71812.94, 26656.56, 4627911.87, 484.537, 444.81, 50397.36, 262570.24]);
});