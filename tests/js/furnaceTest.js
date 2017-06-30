
/**
 * Created by ifw on 6/28/2017.
 */
const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});


test('flowCalculations', function (t) {
    t.plan(2);
    t.type(bindings.flowCalculations, 'function');
    var inp = {};

    // 7 is helium
    inp.gasType = 7;
    inp.specificGravity = 0.14;
    inp.orificeDiameter = 5;
    inp.insidePipeDiameter = 9;
    // 1 is sharp edge
    inp.sectionType = 1;
    inp.dischargeCoefficient = 0.6;
    inp.gasHeatingValue = 7325;
    inp.gasTemperature = 52;
    inp.gasPressure = 63;
    inp.orificePressureDrop = 26;
    inp.operatingTime = 16;
    
    console.log(inp);

    var res = bindings.flowCalculations(inp);

});