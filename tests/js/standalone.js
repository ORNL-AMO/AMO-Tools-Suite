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
