/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

test('psat', function (t) {
    t.plan(2);
    t.type(bindings.achievableEfficiency, 'function');
    var inp = {};
    inp.pump_style = 0;
    inp.specific_speed = 1170;
    var res = bindings.achievableEfficiency(inp);
    t.equal(res, 1.8942771852074485, 'res is ' + res);

});