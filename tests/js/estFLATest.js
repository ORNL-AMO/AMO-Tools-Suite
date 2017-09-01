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
    t.type(bindings.estFLA, 'function');
    var inp = {};
    inp.motor_rated_power = 200;
    inp.motor_rated_speed = 1780;
    inp.line_frequency = 1;
    // Either specify an efficiency class OR provide efficiency percentage
    inp.efficiency_class = 1;
    inp.efficiency = 0;
    inp.motor_rated_voltage = 460;
    var res = bindings.estFLA(inp);
    t.equal(rnd(res), rnd(225.800612262395), 'res is ' + res);

});