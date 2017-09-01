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
    t.plan(4);
    t.type(bindings.energyInput, 'function');
    var inp = {};
    inp.naturalGasHeatInput = 50;
    inp.naturalGasFlow = 0;
    inp.measuredOxygenFlow = 6500;
    inp.coalCarbonInjection = 3300;
    inp.coalHeatingValue = 9000;
    inp.electrodeUse = 500;
    inp.electrodeHeatingValue = 12000;
    inp.otherFuels = 20;
    inp.electricityInput = 18000;
    var res = bindings.energyInput(inp);
    t.equal(rnd(res.kwhCycle), rnd(30978.898007031734), 'res.kwhCycle is ' + res.kwhCycle);
    t.equal(res.heatDelivered, 55.7, 'res.heatDelivered is ' + res.heatDelivered);
    t.equal(rnd(res.totalKwhCycle), rnd(48978.898007031734), 'res.totalKwhCycle is ' + res.totalKwhCycle);
});