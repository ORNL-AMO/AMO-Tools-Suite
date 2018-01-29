const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('phast energy Input EAF', function (t) {
    t.plan(3);
    t.type(bindings.energyInputEAF, 'function');
    var inp = {
        naturalGasHeatInput: 50,
        coalCarbonInjection: 3300,
        coalHeatingValue: 9000,
        electrodeUse: 500,
        electrodeHeatingValue: 12000,
        otherFuels: 20,
        electricityInput: 18000
    };
    var res = bindings.energyInputEAF(inp);
    t.equal(res.heatDelivered, 167116000.0, 'res.heatDelivered is ' + res.heatDelivered);
    t.equal(rnd(res.totalChemicalEnergyInput), rnd(105700000), 'res.totalChemicalEnergyInput is ' + res.totalChemicalEnergyInput);
});