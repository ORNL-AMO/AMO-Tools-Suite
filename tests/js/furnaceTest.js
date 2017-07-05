
/**
 * Created by ifw on 6/28/2017.
 */
const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

test('efficiencyImprovement', function (t) {
    t.plan(2);
    t.type(bindings.efficiencyImprovement, 'function');

    var inp = {};

    inp.currentFlueGasOxygen = 6;
    inp.newFlueGasOxygen = 2;
    inp.currentFlueGasTemp = 1600;
    inp.fuelFiredHeatInput = 1200;
    inp.currentCombustionAirTemp = 80;
    inp.newCombustionAirTemp = 750;
    inp.currentEnergyInput = 10;

    var res = bindings.efficiencyImprovement(inp);

    t.equal(res.currentExcessAir, 35.80, 'res.currentExcessAir is ' + res.currentExcessAir);

    t.equal(res.newExcessAir, 9.4210532075, 'res.newExcessAir is ' + res.newExcessAir);

    t.equal(res.currentAvailableHeat, 46.6298023469, 'res.currentAvailableHeat is ' + res.currentAvailableHeat);

    t.equal(res.newAvailableHeat, 78.9720318524, 'res.newAvailableHeat is '+ res.newAvailableHeat);

    t.equal(res.newFuelSavings, 40.9540298596, 'res.newFuelSavings is ' + res.newFuelSavings);

    t.equal(res.newEnergyInput, 5.904597014, 'res.newEnergyInput is ' + res.newEnergyInput);

});

test('energyEquivalencyElectric', function (t) {
    t.plan(2);
    t.type(bindings.energyEquivalencyElectric, 'function');
    var inp = {};

    inp.fuelFiredEfficiency = 6.59;
    inp.electricallyHeatedEfficiency = 50;
    inp.fuelFiredHeatInput = 87.3;

    var res = bindings.energyEquivalencyElectric(inp);
    t.equal(res.electricalHeatInput, 3371.2686785819, 'res.electricalHeatInput is ' + res.electricalHeatInput);

});

test('energyEquivalencyFuel', function (t) {
    t.plan(2);
    t.type(bindings.energyEquivalencyFuel, 'function');
    var inp = {};

    inp.electricallyHeatedEfficiency = 52.3;
    inp.fuelFiredEfficiency = 58.9;
    inp.electricalHeatInput = 700;

    var res = bindings.energyEquivalencyFuel(inp);
    t.equal(res.fuelFiredHeatInput, 2.1213910017, 'res.fuelFiredHeatInput is ' + res.fuelFiredHeatInput);

});

test('o2Enrichment', function (t) {
    t.plan(2);
    t.type(bindings.o2Enrichment, 'function');
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

    var res = bindings.o2Enrichment(inp);
    t.equal(res.availableHeatInput, 61.97, 'res.availableHeatInput is ' + res.availableHeatInput);

    t.equal(res.availableHeatEnriched, 74.2210855231, 'res.availableHeatEnriched is ' + res.availableHeatEnriched);

    t.equal(res.fuelSavingsEnriched, 16.5058213035, 'res.fuelSavingsEnriched is ' + res.fuelSavingsEnriched);

    t.equal(res.fuelConsumptionEnriched, 8.3494178697, 'res.fuelConsumptionEnriched is ' + res.fuelConsumptionEnriched);

});

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

    t.equal(res.flow, 647312, 'res.flow is ' + res.flow);

    t.equal(res.heatInput, 75865, 'res.heatInput is ' + res.heatInput);

});