/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('phast', function (t) {
    t.plan(3);
    t.type(bindings.energyInput, 'function');
    var inp = {
        naturalGasHeatInput: 50,
        measuredOxygenFlow: 6500,
        coalCarbonInjection: 3300,
        coalHeatingValue: 9000,
        electrodeUse: 500,
        electrodeHeatingValue: 12000,
        otherFuels: 20,
        electricityInput: 18000
    };
    var res = bindings.energyInput(inp);
    t.equal(res.heatDelivered, 55.7, 'res.heatDelivered is ' + res.heatDelivered);
    t.equal(rnd(res.totalChemicalEnergyInput), rnd(48978.898007031734), 'res.totalChemicalEnergyInput is ' + res.totalChemicalEnergyInput);
});