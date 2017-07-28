/**
 * Created by qkf on 7/28/2017.
 */

const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

test('saturatedPropertiesGivenTemperature', function (t) {
    t.plan(12);
    t.type(bindings.saturatedPropertiesGivenTemperature, 'function');

    var inp = {};

    inp.saturatedTemperature = 300;

    var res = bindings.saturatedPropertiesGivenTemperature(inp);

    t.equal(res.saturatedPressure, 0.0035, 'res.saturatedPressure is ' + res.saturatedPressure);

    t.equal(res.saturatedTemperature, 300, 'res.saturatedTemperature is ' + res.saturatedTemperature);

    t.equal(res.liquidEnthalpy, 112.6, 'res.liquidEnthalpy is ' + res.liquidEnthalpy);

    t.equal(res.gasEnthalpy, 2549.9, 'res.gasEnthalpy is '+ res.gasEnthalpy);

    t.equal(res.evaporationEnthalpy, 2437.3, 'res.evaporationEnthalpy is ' + res.evaporationEnthalpy);

    t.equal(res.liquidEntropy, 0.393, 'res.liquidEntropy is ' + res.liquidEntropy);

    t.equal(res.gasEntropy, 8.518, 'res.gasEntropy is '+ res.gasEntropy);

    t.equal(res.evaporationEntropy, 8.124, 'res.evaporationEntropy is ' + res.evaporationEntropy);

    t.equal(res.liquidVolume, 0.001, 'res.liquidVolume is ' + res.liquidVolume);

    t.equal(res.gasVolume, 39.082, 'res.gasVolume is '+ res.gasVolume);

    t.equal(res.evaporationVolume, 39.081, 'res.evaporationVolume is ' + res.evaporationVolume);

});

test('saturatedPropertiesGivenPressure', function (t) {
    t.plan(12);
    t.type(bindings.saturatedPropertiesGivenPressure, 'function');

    var inp = {};

    inp.saturatedPressure = 20;

    var res = bindings.saturatedPropertiesGivenPressure(inp);

    t.equal(res.saturatedPressure, 20, 'res.saturatedPressure is ' + res.saturatedPressure);

    t.equal(res.saturatedTemperature, 638.9, 'res.saturatedTemperature is ' + res.saturatedTemperature);

    t.equal(res.liquidEnthalpy, 1827.1, 'res.liquidEnthalpy is ' + res.liquidEnthalpy);

    t.equal(res.gasEnthalpy, 2421.7, 'res.gasEnthalpy is '+ res.gasEnthalpy);

    t.equal(res.evaporationEnthalpy, 594.6, 'res.evaporationEnthalpy is ' + res.evaporationEnthalpy);

    t.equal(res.liquidEntropy, 4.015, 'res.liquidEntropy is ' + res.liquidEntropy);

    t.equal(res.gasEntropy, 4.946, 'res.gasEntropy is '+ res.gasEntropy);

    t.equal(res.evaporationEntropy, 0.931, 'res.evaporationEntropy is ' + res.evaporationEntropy);

    t.equal(res.liquidVolume, 0.002, 'res.liquidVolume is ' + res.liquidVolume);

    t.equal(res.gasVolume, 0.006, 'res.gasVolume is '+ res.gasVolume);

    t.equal(res.evaporationVolume, 0.004, 'res.evaporationVolume is ' + res.evaporationVolume);

});

test('steamProperties', function (t) {
    t.plan(7);
    t.type(bindings.steamProperties, 'function');

    var inp = {};

    inp.pressure = 10;
    inp.thermodynamicQuantity = 1; //1 is ENTHALPY
    inp.quantityValue = 2000;

    var res = bindings.steamProperties(inp);

    t.equal(res.pressure, 10, 'res.pressure is ' + res.pressure);

    t.equal(res.temperature, 584.1, 'res.temperature is ' + res.temperature);

    t.equal(res.specificEnthalpy, 2000, 'res.specificEnthalpy is ' + res.spcificEnthalpy);

    t.equal(res.specificEntropy, 4.374, 'res.specificEntropy is ' + res.specificEntropy);

    t.equal(res.quality, 0.45, 'res.quality is ' + res.quality);

    t.equal(res.specificVolume, 0.009, 'res.specificVolume is '+ res.specificVolume);

});