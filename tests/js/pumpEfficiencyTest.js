/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

test('psat', function (t) {
    t.plan(3);
    t.type(bindings.pumpEfficiency, 'function');
    var inp = {};
    // Pump Style End suction ansi API
    inp.pump_style = 6;
    inp.flow_rate = 2000;
    var res = bindings.pumpEfficiency(inp);
    t.equal(res.average, 83.97084437955112, 'res average is ' + res.average);
    t.equal(res.max, 86.99584193768345, 'res max is ' + res.max);
});