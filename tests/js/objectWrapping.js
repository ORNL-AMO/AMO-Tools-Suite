// const addon = require('../../build/Release/exhaustGasEAF');
const addon = require('../../build/Release/exhaustGasEAF');


// const test = require('tap').test
//     , testRoot = require('path').resolve(__dirname, '../../')
//     , bindings = require('bindings')({ module_root: testRoot, bindings: 'exhaustGasEAF'});


// test('exhaustGasEAF object wrap', function (t) {

for (i = 0; i < 500; i++) {
    var a = i / 100.0;
    var inp = {
        offGasTemp: 2800 + a, CO: 12 + a, H2: 10 + a, combustibleGases: 3 + a, vfr: 8000 + a, dustLoading: 0.001 + a
    };
    var obj = new addon.ExhaustGasEAF(inp.offGasTemp, inp.CO, inp.H2, inp.combustibleGases, inp.vfr, inp.dustLoading);
    var res = obj.getTotalHeatExhaustNAN();
}

console.log(res + " should be 12553119.02");


obj = new addon.ExhaustGasEAF(2800, 8, 6, 3, 6500, 0.001);
res = obj.getTotalHeatExhaustNAN();
console.log(res + " should be 8591939.26");

// });