const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'standalone'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('CHP', function (t) {
    t.plan(10);
    t.type(bindings.CHPcalculator, 'function');

    var inp = {
        "annualOperatingHours": 4160,
        "annualElectricityConsumption": 23781908,
        "annualThermalDemand": 122581,
        "boilerThermalFuelCosts": 5.49,
        "avgElectricityCosts": 0.214,
        "option": 0,
        "boilerThermalFuelCostsCHPcase": 5.49,
        "CHPfuelCosts": 5.49,
        "percentAvgkWhElectricCostAvoidedOrStandbyRate": 90,
        "displacedThermalEfficiency": 85,
        "chpAvailability": 95,
        "thermalUtilization": 90
    };

    var res = bindings.CHPcalculator(inp);

    t.equal(rnd(res.annualOperationSavings), rnd(3251705.06182641));
    t.equal(rnd(res.totalInstalledCostsPayback), rnd(11890954.0));
    t.equal(rnd(res.simplePayback), rnd(3.595330381));
    t.equal(rnd(res.fuelCosts), rnd(0.0648161938));
    t.equal(rnd(res.thermalCredit), rnd(-0.0284427212));
    t.equal(rnd(res.incrementalOandM), rnd(0.0123));
    t.equal(rnd(res.totalOperatingCosts), rnd(0.0486734726));

    inp.option = 1;
    inp.percentAvgkWhElectricCostAvoidedOrStandbyRate = 9.75;
    res = bindings.CHPcalculator(inp);
    t.equal(rnd(res.annualOperationSavings), rnd(3066325.0889664106));
    t.equal(rnd(res.simplePayback), rnd(3.8126922817));
});

test('PneumaticAirRequirement', function (t) {
    t.plan(7);
    t.type(bindings.pneumaticAirRequirement, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.volumeAirIntakePiston), expected[0]);
        t.equal(rnd(results.compressionRatio), expected[1]);
        t.equal(rnd(results.airRequirementPneumaticCylinder), expected[2]);
    };

    var input = {
        pistonType: 0,
        cylinderDiameter: 1.5,
        cylinderStroke: 6,
        airPressure: 100,
        cyclesPerMinute: 60
    };

    compare(bindings.pneumaticAirRequirement(input), [0.367969, 7.802721, 2.871158]);

    input.pistonType = 1;
    input.pistonRodDiameter = 0.375;
    compare(bindings.pneumaticAirRequirement(input), [0.712939, 7.802721, 5.562868]);
});

test('Receiver Tank Size', function (t) {
    t.plan(9);
    t.type(bindings.receiverTank, 'function');

    t.equal(rnd(bindings.receiverTank({
        method: 0, airDemand: 150, allowablePressureDrop: 3, atmosphericPressure: 14.7
    })), 5497.8);

    t.equal(rnd(bindings.receiverTank({
        method: 0, airDemand: 190, allowablePressureDrop: 8, atmosphericPressure: 12.7
    })), 2256.155);


    t.equal(rnd(bindings.receiverTank({
        method: 1, lengthOfDemand: 0.5, airFlowRequirement: 100, atmosphericPressure: 14.7, initialTankPressure: 110, finalTankPressure: 100
    })), 549.78);

    t.equal(rnd(bindings.receiverTank({
        method: 1, lengthOfDemand: 1.5, airFlowRequirement: 120, atmosphericPressure: 11.7, initialTankPressure: 150, finalTankPressure: 100
    })), 315.0576);


    t.equal(rnd(bindings.receiverTank({
        method: 2, lengthOfDemand: 0.5, airFlowRequirement: 900, atmosphericPressure: 14.7, initialTankPressure: 100, finalTankPressure: 70, meteredControl: 45
    })), 1566.873);

    t.equal(rnd(bindings.receiverTank({
        method: 2, lengthOfDemand: 1.5, airFlowRequirement: 800, atmosphericPressure: 11.7, initialTankPressure: 120, finalTankPressure: 90, meteredControl: 75
    })), 3172.455);


    t.equal(rnd(bindings.receiverTank({
        method: 3, distanceToCompressorRoom: 1000, speedOfAir: 250, atmosphericPressure: 14.7, airDemand: 600, allowablePressureDrop: 2
    })), 2199.12);

    t.equal(rnd(bindings.receiverTank({
        method: 3, distanceToCompressorRoom: 1200, speedOfAir: 350, atmosphericPressure: 11.7, airDemand: 800, allowablePressureDrop: 19
    })), 210.564812);
});
