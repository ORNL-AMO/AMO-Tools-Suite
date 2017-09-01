/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('psat', function (t) {
    t.plan(2);
    t.type(bindings.nema, 'function');
    var inp = {};
    // Line frequency 60
    inp.line_frequency = 0;
    inp.motor_rated_speed = 1200;
    // Efficiency class = Energy efficient
    inp.efficiency_class = 1;
    inp.efficiency = 0;
    inp.motor_rated_power = 200;
    inp.load_factor = 1;
    var res = bindings.nema(inp);
    t.equal(rnd(res), rnd(95.33208465291122), 'res is ' + res);
});