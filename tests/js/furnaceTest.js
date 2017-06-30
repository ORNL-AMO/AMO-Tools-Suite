
/**
 * Created by ifw on 6/28/2017.
 */
const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

SetR("excessAirCurrent", excessAirCurrent);
SetR("excessAirNew", excessAirNew);
SetR("fuelSavings", fuelSavings);
SetR("energyInputNew", energyInputNew);
SetR("energyInput", energyInput);
SetR("availableHeatCurrent", availableHeatCurrent);
SetR("availableHeatNew", availableHeatNew);

test('efficiencyImprovement', function (t) {
    t.plan(2);
    t.type(bindings.EfficiencyImprovement, 'function');

    var inp = {};

    inp.currentFlueGasOxygen = 6;
    inp.newFlueGasOxygen = 2;
    inp.currentFlueGasTemp = 1600;
    inp.newFlueGasTemp = 1200;
    inp.fuelFiredHeatInput = 80;
    inp.currentCombustionAirTemp = 50;
    inp.fuelFiredHeatInput = 87.3;
    inp.newCombustionAirTemp = 750;
    inp.currentEnergyInput = 10;

    t.equal(res.excessAirCurrent, 35.80, res.excessAirCurrent + " != 35.80");

    t.equal(res.excessAirNew, 35.80, res.excessAirNew + " != 35.80");

    t.equal(res.availableHeatCurrent, 35.80, res.availableHeatCurrent + " != 35.80");

    t.equal(res.availableHeatNew, 35.80, res.availableHeatNew + " != 35.80");

    t.equal(res.fuelSavings, 35.80, res.fuelSavings + " != 35.80");

    t.equal(res.energyInputNew, 35.80, res.energyInputNew + " != 35.80");

});

test('energyEquivalency', function (t) {
    t.plan(2);
    t.type(bindings.EnergyEquivalency, 'function');
    var inp = {};

    inp.fuelFiredEfficiency = 6.59;
    inp.electricallyHeatedEfficiency = 50;

    inp.fuelFiredHeatInput = 87.3;

    var res = bindings.EnergyEquivalency(inp);
    t.equal(res.electricalHeatInput, 3371.27, res.electricalHeatInput + " != 3371.27");

    var inp = {};

    inp.fuelFiredEfficiency = 52.3;
    inp.electricallyHeatedEfficiency = 58.9;
    inp.fuelFiredHeatInput = 700;

    var res = bindings.EnergyEquivalency(inp);
    t.equal(res.fuelFiredHeatInput, 2.1207694397, res.fuelFiredHeatInput + " != 2.1207694397");


});

test('o2Enrichment', function (t) {
    t.plan(2);
    t.type(bindings.O2Enrichment, 'function');
    var inp = {};

    inp.o2CombAir = 21;
    inp.o2CombAirEnriched = 100;
    inp.flueGasTemp = 1800;
    inp.flueGasTempEnriched = 1900;
    inp.o2FlueGas = 5;
    inp.o2FlueGasEnriched = 1;
    inp.combAirTemp = 900;
    inp.combAirTempEnriched = 80;
    inp.fuelConsumption = 10;

    var res = bindings.EnergyEquivalency(inp);
    t.equal(res.getAvailableHeat, 61.97, res.electricalHeatInput + " != 61.97");

    t.equal(res.getAvailableHeatEnriched, 74.2210855231, res.fuelFiredHeatInput + " != 74.2210855231");

    t.equal(res.getFuelSavingsEnriched, 16.5058213035, res.fuelFiredHeatInput + " != 16.5058213035");

    t.equal(res.getFuelConsumptionEnriched, 8.3494178697, res.fuelFiredHeatInput + " != 8.3494178697");

});

test('flowCalculationsEnergyUse', function (t) {
    t.plan(2);
    t.type(bindings.FlowCalculationsEnergyUse, 'function');
    var inp = {};

    inp.gasType = HELIUM;
    inp.specificGravity = 0.14;
    inp.orificeDiameter = 5;
    inp.insidePipeDiameter = 9;
    inp.sectionType = SHARP_EDGE;
    inp.dischargeCoefficient = 0.6;
    inp.gasHeatingValue = 7325;
    inp.gasTemperature = 52;
    inp.gasPressure = 63;
    inp.orificePressureDrop = 26;
    inp.operatingTime = 16;

    var res = bindings.FlowCalculationsEnergyUse(inp);
    t.equal(res.getFlow, 647312, res.electricalHeatInput + " != 647312");

    t.equal(res.getHeatInput, 75865, res.fuelFiredHeatInput + " != 75865");

});
