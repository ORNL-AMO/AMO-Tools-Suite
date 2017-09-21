// const addon = require('../../build/Release/exhaustGasEAF');
const addon = require('../../build/Release/exhaustGasEAF');


// const test = require('tap').test
//     , testRoot = require('path').resolve(__dirname, '../../')
//     , bindings = require('bindings')({ module_root: testRoot, bindings: 'exhaustGasEAF'});


// test('exhaustGasEAF object wrap', function (t) {

var inp = {
    offGasTemp: 2800 + a, CO: 12 + a, H2: 10 + a, combustibleGases: 3 + a, vfr: 8000 + a, dustLoading: 0.001 + a
};

var obj = new addon.ExhaustGasEAF(inp.offGasTemp, inp.CO, inp.H2, inp.combustibleGases, inp.vfr, inp.dustLoading);
for (var i = 0; i < 900000; i++) {
    var a = i / 100000.0;
    obj.offGasTemp = obj.offGasTemp + a;
    var res = obj.totalHeatExhaust;
}

// for (var i = 0; i < 900000; i++) {
//     var a = i / 100000.0;
//     var inp = {
//         offGasTemp: 2800 + a, CO: 12 + a, H2: 10 + a, combustibleGases: 3 + a, vfr: 8000 + a, dustLoading: 0.001 + a
//     };
//     var obj = new addon.ExhaustGasEAF(inp.offGasTemp, inp.CO, inp.H2, inp.combustibleGases, inp.vfr, inp.dustLoading);
//     var res = obj.totalHeatExhaust;
// }


// });