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

    t.equal(res.liquidEnthalpy, 1827.1006242178828, 'res.liquidEnthalpy is ' + res.liquidEnthalpy);

    t.equal(res.gasEnthalpy, 2421.680542687896, 'res.gasEnthalpy is '+ res.gasEnthalpy);

    t.equal(res.evaporationEnthalpy, 594.5799184700131, 'res.evaporationEnthalpy is ' + res.evaporationEnthalpy);

    t.equal(res.liquidEntropy, 4.015381593120595, 'res.liquidEntropy is ' + res.liquidEntropy);

    t.equal(res.gasEntropy, 4.946001326758373, 'res.gasEntropy is '+ res.gasEntropy);

    t.equal(res.evaporationEntropy, 0.9306197336377782, 'res.evaporationEntropy is ' + res.evaporationEntropy);

    t.equal(res.liquidVolume, 0.00203864724569564, 'res.liquidVolume is ' + res.liquidVolume);

    t.equal(res.gasVolume, 0.005936854102266304, 'res.gasVolume is '+ res.gasVolume);

    t.equal(res.evaporationVolume, 0.003898206856570664, 'res.evaporationVolume is ' + res.evaporationVolume);

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

    t.equal(res.steamEnergyFlow, 110.75336475088508, 'res.steamEnergyFlow is ' + res.steamEnergyFlow);
    t.equal(res.blowdownMassFlow, 0.9183673469387756, 'res.blowdownMassFlow is ' + res.blowdownMassFlow);
    t.equal(res.blowdownEnergyFlow, 1.6779495528531578, 'res.blowdownEnergyFlow is ' + res.blowdownEnergyFlow);
    t.equal(res.feedwaterMassFlow, 45.91836734693878, 'res.feedwaterMassFlow is ' + res.feedwaterMassFlow);
    t.equal(res.feedwaterEnergyFlow, 64.64697706690914, 'res.feedwaterEnergyFlow is ' + res.feedwaterEnergyFlow);
    t.equal(res.boilerEnergy, 47.7843372368291, 'res.boilerEnergy is '+ res.boilerEnergy);
    t.equal(res.fuelEnergy, 56.216867337446004, 'res.fuelEnergy is '+ res.fuelEnergy);
});

test('heatLoss', function (t) {
    t.plan(5);
    t.type(bindings.heatLoss, 'function');

    var inp = {
        inletPressure : 2.418,
        thermodynamicQuantity : 0, //0 is TEMPERATURE
        quantityValue : 521,
        inletMassFlow : 5434,
        percentHeatLoss : 2.44
    };

    var res = bindings.heatLoss(inp);

    t.equal(res.inletEnergyFlow, 15642.967348653074, 'res.inletEnergyFlow is ' + res.inletEnergyFlow);
    t.equal(res.outletMassFlow, 5434, 'res.outletMassFlow is ' + res.outletMassFlow);
    t.equal(res.outletEnergyFlow, 15261.278945345939, 'res.outletEnergyFlow is ' + res.outletEnergyFlow);
    t.equal(res.heatLoss, 381.68840330713465, 'res.heatLoss is ' + res.heatLoss);
});

test('flashTank', function (t) {
    t.plan(6);
    t.type(bindings.flashTank, 'function');

    var inp = {
        inletWaterPressure : 4.54484,
        thermodynamicQuantity : 1, //1 is ENTHALPY
        quantityValue : 2000,
        inletWaterMassFlow : 36133,
        tankPressure : 3.3884
    };

    var res = bindings.flashTank(inp);

    t.equal(res.inletWaterEnergyFlow, 72266, 'res.inletWaterEnergyFlow is ' + res.inletWaterEnergyFlow);
    t.equal(res.outletGasMassFlow, 19667.16383431122, 'res.outletGasMassFlow is ' + res.outletGasMassFlow);
    t.equal(res.outletGasEnergyFlow, 55126.79710787576, 'res.outletGasEnergyFlow is ' + res.outletGasEnergyFlow);
    t.equal(res.outletLiquidMassFlow, 16465.83616568878, 'res.outletLiquidMassFlow is ' + res.outletLiquidMassFlow);
    t.equal(res.outletLiquidEnergyFlow, 17139.20289212423, 'res.outletLiquidEnergyFlow is ' + res.outletLiquidEnergyFlow);
});

test('prvWithoutDesuperheating', function (t) {
    t.plan(6);
    t.type(bindings.prvWithoutDesuperheating, 'function');

    var inp = {
        inletPressure : 4.8794,
        thermodynamicQuantity : 0, //0 is TEMPERATURE
        quantityValue : 691.5,
        inletMassFlow : 37970,
        outletPressure : 4.0823
    };

    var res = bindings.prvWithoutDesuperheating(inp);

    t.equal(res.inletEnergyFlow, 123147.93493161911, 'res.inletEnergyFlow is ' + res.inletEnergyFlow);
    t.equal(res.outletMassFlow, 37970, 'res.outletMassFlow is ' + res.outletMassFlow);
    t.equal(res.outletEnergyFlow, 123147.93493161911, 'res.outletEnergyFlow is ' + res.outletEnergyFlow);
    t.equal(res.inletSpecificEnthalpy, 3243.29562632655, 'res.inletSpecificEnthalpy is ' + res.inletSpecificEnthalpy);
    t.equal(res.outletSpecificEnthalpy, 3243.29562632655, 'res.outletSpecificEnthalpy is ' + res.outletSpecificEnthalpy);
});

test('prvWithDesuperheating', function (t) {
    t.plan(6);
    t.type(bindings.prvWithDesuperheating, 'function');

    var inp = {
        inletPressure : 2.8937,
        thermodynamicQuantity : 0, //0 is TEMPERATURE
        quantityValue : 936.3,
        inletMassFlow : 17599,
        outletPressure : 0.8188,
        feedwaterPressure : 0.2937,
        feedwaterThermodynamicQuantity : 2, //2 is ENTROPY
        feedwaterQuantityValue : 5,
        desuperheatingTemp : 708.3
    };

    var res = bindings.prvWithDesuperheating(inp);

    t.equal(res.inletEnergyFlow, 67367.3111113208, 'res.inletEnergyFlow is ' + res.inletEnergyFlow);
    t.equal(res.outletMassFlow, 23583.469367594505, 'res.outletMassFlow is ' + res.outletMassFlow);
    t.equal(res.outletEnergyFlow, 78812.94289252072, 'res.outletEnergyFlow is ' + res.outletEnergyFlow);
    t.equal(res.feedwaterMassFlow, 5984.4693675945055, 'res.feedwaterMassFlow is ' + res.feedwaterMassFlow);
    t.equal(res.feedwaterEnergyFlow, 11445.631781199914, 'res.feedwaterEnergyFlow is ' + res.feedwaterEnergyFlow);
});