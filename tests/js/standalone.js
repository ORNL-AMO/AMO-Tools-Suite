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

test('usableAirCapacity', function (t) {
    t.plan(5);
    t.type(bindings.usableAirCapacity, 'function');
    t.equal(rnd(bindings.usableAirCapacity({tankSize: 660, airPressureIn: 110, airPressureOut: 100})), rnd(60.024009603));
    t.equal(rnd(bindings.usableAirCapacity({tankSize: 760, airPressureIn: 110, airPressureOut: 100})), rnd(69.1185565135));
    t.equal(rnd(bindings.usableAirCapacity({tankSize: 760, airPressureIn: 150, airPressureOut: 100})), rnd(345.5927825676));
    t.equal(rnd(bindings.usableAirCapacity({tankSize: 760, airPressureIn: 150, airPressureOut: 130})), rnd(138.237113027));
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

test('Operating Cost', function (t) {
    t.plan(9);
    t.type(bindings.operatingCost, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.runTimeUnloaded), expected[0]);
        t.equal(rnd(results.costForLoaded), expected[1]);
        t.equal(rnd(results.costForUnloaded), expected[2]);
        t.equal(rnd(results.totalAnnualCost), expected[3]);
    };

    var input = {
        motorBhp: 215, bhpUnloaded: 25, annualOperatingHours: 6800, runTimeLoaded: 85, efficiencyLoaded: 95,
        efficiencyUnloaded: 90, costOfElectricity: 0.05
    };
    compare(bindings.operatingCost(input), [15, 48792.326316, 2272.191667, 51064.517982]);

    input = {
        motorBhp: 255, bhpUnloaded: 35, annualOperatingHours: 6000, runTimeLoaded: 89, efficiencyLoaded: 93,
        efficiencyUnloaded: 90, costOfElectricity: 0.09
    };
    compare(bindings.operatingCost(input), [11, 98305.954839, 4394.313, 102700.267839]);
});

test('Air System Capacity', function (t) {
    t.plan(20);
    t.type(bindings.airSystemCapacity, 'function');

    var compare = function(results, expected, gallons) {
        t.equal(rnd(results.oneHalf), expected[0]);
        t.equal(rnd(results.threeFourths), expected[1]);
        t.equal(rnd(results.one), expected[2]);
        t.equal(rnd(results.oneAndOneFourth), expected[3]);
        t.equal(rnd(results.oneAndOneHalf), expected[4]);
        t.equal(rnd(results.two), expected[5]);
        t.equal(rnd(results.twoAndOneHalf), expected[6]);
        t.equal(rnd(results.three), expected[7]);
        t.equal(rnd(results.threeAndOneHalf), expected[8]);
        t.equal(rnd(results.four), expected[9]);
        t.equal(rnd(results.five), expected[10]);
        t.equal(rnd(results.six), expected[11]);

        for (var i = 0; i < gallons.length; i++) {
            t.equal(rnd(results.receiverCapacities[i]), gallons[i]);
        }
    };

    var inp = {
        oneHalf: 3000, threeFourths: 2000, one: 1000, oneAndOneFourth: 200, oneAndOneHalf: 100, two: 500, twoAndOneHalf: 500, three: 300,
        threeAndOneHalf: 0, four: 1000, five: 0, six: 0,
        receiverCapacities: [
            400, 500, 660, 1060
        ]
    };

    var results = bindings.airSystemCapacity(inp);
    t.equal(rnd(results.totalPipeVolume), 155.28);
    t.equal(rnd(results.totalReceiverVolume), 350.26738);
    t.equal(rnd(results.totalCapacityOfCompressedAirSystem), 505.54738);
    compare(results, [6.3, 7.4, 6, 2.08, 1.41, 11.65, 16.65, 15.39, 0, 88.4, 0, 0], [53.475936, 66.84492, 88.235294, 141.71123]);
});

test('Air Velocity', function (t) {
    t.plan(13);
    t.type(bindings.airVelocity, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.oneHalf), expected[0]);
        t.equal(rnd(results.threeFourths), expected[1]);
        t.equal(rnd(results.one), expected[2]);
        t.equal(rnd(results.oneAndOneFourth), expected[3]);
        t.equal(rnd(results.oneAndOneHalf), expected[4]);
        t.equal(rnd(results.two), expected[5]);
        t.equal(rnd(results.twoAndOneHalf), expected[6]);
        t.equal(rnd(results.three), expected[7]);
        t.equal(rnd(results.threeAndOneHalf), expected[8]);
        t.equal(rnd(results.four), expected[9]);
        t.equal(rnd(results.five), expected[10]);
        t.equal(rnd(results.six), expected[11]);
    };

    var inp = {
        airFlow: 1800, pipePressure: 100, atmosphericPressure: 14.7
    };

    compare(bindings.airVelocity(inp), [1845.510026, 1044.628317, 643.782567, 369.102005, 271.398533, 164.777681, 115.585179, 74.919216, 55.981093, 43.491988, 27.68265, 19.164175]);
});

test('Pipe Sizing', function (t) {
    t.plan(5);
    t.type(bindings.pipeSizing, 'function');

    var inp = {
        airFlow: 1000, airlinePressure: 90, designVelocity: 25, atmosphericPressure: 14.5
    };

    var results = bindings.pipeSizing(inp);
    t.equal(rnd(results.crossSectionalArea), 13.320574);
    t.equal(rnd(results.pipeDiameter), 4.132512);

    inp = {
        airFlow: 1400, airlinePressure: 110, designVelocity: 30, atmosphericPressure: 11.5
    };

    results = bindings.pipeSizing(inp);
    t.equal(rnd(results.crossSectionalArea), 10.600823);
    t.equal(rnd(results.pipeDiameter), 3.68657);
});

test('Pneumatic Valve', function (t) {
    t.plan(5);
    t.type(bindings.pneumaticValve, 'function');

    var results = bindings.pneumaticValve({ inletPressure: 100, outletPressure: 70 });
    t.equal(rnd(results.flowRate), 49.09732);

    results = bindings.pneumaticValve({ inletPressure: 120, outletPressure: 90 });
    t.equal(rnd(results.flowRate), 54.568621);

    results = bindings.pneumaticValve({ inletPressure: 80, outletPressure: 75, flowRate: 55 });
    t.equal(rnd(results.flowCoefficient), 2.873685);

    results = bindings.pneumaticValve({ inletPressure: 90, outletPressure: 85, flowRate: 95 });
    t.equal(rnd(results.flowCoefficient), 4.671398);
});

test('Bag Method', function (t) {
    t.plan(5);
    t.type(bindings.bagMethod, 'function');

    var results = bindings.bagMethod({ operatingTime: 115200 / 60.0, bagFillTime: 25, heightOfBag: 10, diameterOfBag: 10, numberOfUnits: 1 });
    t.equal(rnd(results.flowRate), 1.092);
    t.equal(rnd(results.annualConsumption), 125.7984);

    results = bindings.bagMethod({ operatingTime: 100000 / 60.0, bagFillTime: 20, heightOfBag: 10, diameterOfBag: 10, numberOfUnits: 1 });
    t.equal(rnd(results.flowRate), 1.365);
    t.equal(rnd(results.annualConsumption), 136.5);
});
