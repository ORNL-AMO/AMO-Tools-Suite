const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'fan'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('fan test', function (t) {
    t.plan(3);
    t.type(bindings.fanPlaceholder, 'function');
    var inp = {
        fanSpeed: 1191,
        motorSpeed: 1191,
        fanSpeedCorrected: 1170,
        densityCorrected: 0.05,
        pressureBarometricCorrected: 26.28
    };

    var res = bindings.fanPlaceholder(inp);
    // t.equal(rnd(res.totalChemicalEnergyInput), rnd(0));
});