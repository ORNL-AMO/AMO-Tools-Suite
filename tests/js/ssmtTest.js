/**
 * Created by qkf on 7/28/2017.
 */

const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'ssmt'});

test('saturatedPropertiesGivenTemperature', function (t) {
    t.plan(12);
    t.type(bindings.saturatedPropertiesGivenTemperature, 'function');

    var inp = {};

    inp.saturatedTemperature = 300;

    var res = bindings.saturatedPropertiesGivenTemperature(inp);

    t.equal(res.saturatedPressure, 0.0035365894130130106, 'res.saturatedPressure is ' + res.saturatedPressure);

    t.equal(res.saturatedTemperature, 300, 'res.saturatedTemperature is ' + res.saturatedTemperature);

    t.equal(res.liquidEnthalpy, 112.57499081240724, 'res.liquidEnthalpy is ' + res.liquidEnthalpy);

    t.equal(res.gasEnthalpy, 2549.8930083073265, 'res.gasEnthalpy is '+ res.gasEnthalpy);

    t.equal(res.evaporationEnthalpy, 2437.3180174949193, 'res.evaporationEnthalpy is ' + res.evaporationEnthalpy);

    t.equal(res.liquidEntropy, 0.3931236014741, 'res.liquidEntropy is ' + res.liquidEntropy);

    t.equal(res.gasEntropy, 8.517536685028846, 'res.gasEntropy is '+ res.gasEntropy);

    t.equal(res.evaporationEntropy, 8.124413083554746, 'res.evaporationEntropy is ' + res.evaporationEntropy);

    t.equal(res.liquidVolume, 0.0010034979299339492, 'res.liquidVolume is ' + res.liquidVolume);

    t.equal(res.gasVolume, 39.08205832377987, 'res.gasVolume is '+ res.gasVolume);

    t.equal(res.evaporationVolume, 39.08105482584993, 'res.evaporationVolume is ' + res.evaporationVolume);

});

test('saturatedPropertiesGivenPressure', function (t) {
    t.plan(12);
    t.type(bindings.saturatedPropertiesGivenPressure, 'function');

    var inp = {};

    inp.saturatedPressure = 20;

    var res = bindings.saturatedPropertiesGivenPressure(inp);

    t.equal(res.saturatedPressure, 20, 'res.saturatedPressure is ' + res.saturatedPressure);

    t.equal(res.saturatedTemperature, 638.8959115457051, 'res.saturatedTemperature is ' + res.saturatedTemperature);

    t.equal(res.liquidEnthalpy, 1827.1006242178723, 'res.liquidEnthalpy is ' + res.liquidEnthalpy);

    t.equal(res.gasEnthalpy, 2421.680542687896, 'res.gasEnthalpy is '+ res.gasEnthalpy);

    t.equal(res.evaporationEnthalpy, 594.5799184700236, 'res.evaporationEnthalpy is ' + res.evaporationEnthalpy);

    t.equal(res.liquidEntropy, 4.015381593120578, 'res.liquidEntropy is ' + res.liquidEntropy);

    t.equal(res.gasEntropy, 4.946001326758373, 'res.gasEntropy is '+ res.gasEntropy);

    t.equal(res.evaporationEntropy, 0.930619733637795, 'res.evaporationEntropy is ' + res.evaporationEntropy);

    t.equal(res.liquidVolume, 0.0020386472456956663, 'res.liquidVolume is ' + res.liquidVolume);

    t.equal(res.gasVolume, 0.005936854102266306, 'res.gasVolume is '+ res.gasVolume);

    t.equal(res.evaporationVolume, 0.0038982068565706395, 'res.evaporationVolume is ' + res.evaporationVolume);

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

    t.equal(res.temperature, 584.1494879985282, 'res.temperature is ' + res.temperature);

    t.equal(res.specificEnthalpy, 2000, 'res.specificEnthalpy is ' + res.specificEnthalpy);

    t.equal(res.specificEntropy, 4.37395830066478, 'res.specificEntropy is ' + res.specificEntropy);

    t.equal(res.quality, 0.44940059413065064, 'res.quality is ' + res.quality);

    t.equal(res.specificVolume, 0.008904111059648875, 'res.specificVolume is '+ res.specificVolume);

});

test('boiler', function (t) {
    t.plan(8);
    t.type(bindings.boiler, 'function');

    var inp = {
        deaeratorPressure : 10, combustionEfficiency : 85, blowdownRate : 2,
        steamPressure : 20, thermodynamicQuantity : 1, //1 is ENTHALPY
        quantityValue : 2000, steamMassFlow : 45
    };

    var res = bindings.boiler(inp);

    t.equal(res.steamEnergyFlow, 110.7533647508802, 'res.steamEnergyFlow is ' + res.steamEnergyFlow);
    t.equal(res.blowdownMassFlow, 0.9183673469387756, 'res.blowdownMassFlow is ' + res.blowdownMassFlow);
    t.equal(res.blowdownEnergyFlow, 1.6779495528531483, 'res.blowdownEnergyFlow is ' + res.blowdownEnergyFlow);
    t.equal(res.feedwaterMassFlow, 45.91836734693878, 'res.feedwaterMassFlow is ' + res.feedwaterMassFlow);
    t.equal(res.feedwaterEnergyFlow, 64.64697706690914, 'res.feedwaterEnergyFlow is ' + res.feedwaterEnergyFlow);
    t.equal(res.boilerEnergy, 47.7843372368242, 'res.boilerEnergy is '+ res.boilerEnergy);
    t.equal(res.fuelEnergy, 56.216867337440235, 'res.fuelEnergy is '+ res.fuelEnergy);
});

test('heatLoss', function (t) {
    t.plan(8);
    t.type(bindings.heatLoss, 'function');

    var inp = {
        inletPressure : 2.418,
        thermodynamicQuantity : 0, //0 is TEMPERATURE
        quantityValue : 521,
        inletMassFlow : 5434,
        percentHeatLoss : 2.44
    };

    var res = bindings.heatLoss(inp);

    t.equal(res.inletEnergyFlow, 15643, 'res.inletEnergyFlow is ' + res.inletEnergyFlow);
    t.equal(res.outletMassFlow, 5434, 'res.outletMassFlow is ' + res.outletMassFlow);
    t.equal(res.outletEnergyFlow, 15261.2789453459, 'res.outletEnergyFlow is ' + res.outletEnergyFlow);
    t.equal(res.heatLoss, 381.6884033071, 'res.heatLoss is ' + res.heatLoss);
});