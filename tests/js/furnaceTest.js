const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('efficiencyImprovement', function (t) {
    t.plan(7);
    t.type(bindings.efficiencyImprovement, 'function');

    var inp = {};

    inp.currentFlueGasOxygen = 6;
    inp.newFlueGasOxygen = 2;
    inp.currentFlueGasTemp = 1600;
    inp.currentCombustionAirTemp = 80;
    inp.newCombustionAirTemp = 750;
    inp.currentEnergyInput = 10;
    inp.newFlueGasTemp = 1200;

    var res = bindings.efficiencyImprovement(inp);
    t.equal(rnd(res.currentExcessAir), rnd(35.80000271600005), 'res.currentExcessAir is ' + res.currentExcessAir);
    t.equal(rnd(res.newExcessAir), rnd(9.421053207479227), 'res.newExcessAir is ' + res.newExcessAir);
    t.equal(rnd(res.currentAvailableHeat), rnd(45.550889), 'res.currentAvailableHeat is ' + res.currentAvailableHeat);
    t.equal(rnd(res.newAvailableHeat), rnd(77.893119), 'res.newAvailableHeat is '+ res.newAvailableHeat);
    t.equal(rnd(res.newFuelSavings), rnd(41.521293), 'res.newFuelSavings is ' + res.newFuelSavings);
    t.equal(rnd(res.newEnergyInput), rnd(5.847870740975683), 'res.newEnergyInput is ' + res.newEnergyInput);
});

test('energyEquivalencyElectric', function (t) {
    t.plan(2);
    t.type(bindings.energyEquivalencyElectric, 'function');
    var inp = {};

    inp.fuelFiredEfficiency = 6.59;
    inp.electricallyHeatedEfficiency = 50;
    inp.fuelFiredHeatInput = 87.3;

    var res = bindings.energyEquivalencyElectric(inp);
    t.equal(rnd(res.electricalHeatInput), rnd(3371.268678581893), 'res.electricalHeatInput is ' + res.electricalHeatInput);
});

test('energyEquivalencyFuel', function (t) {
    t.plan(2);
    t.type(bindings.energyEquivalencyFuel, 'function');
    var inp = {};

    inp.electricallyHeatedEfficiency = 52.3;
    inp.fuelFiredEfficiency = 58.9;
    inp.electricalHeatInput = 700;

    var res = bindings.energyEquivalencyFuel(inp);
    t.equal(rnd(res.fuelFiredHeatInput), rnd(2.121391001697793), 'res.fuelFiredHeatInput is ' + res.fuelFiredHeatInput);

});

test('o2Enrichment', function (t) {
    t.plan(17);
    t.type(bindings.o2Enrichment, 'function');
    var inp = {
        o2CombAir: 21, o2CombAirEnriched: 100, flueGasTemp: 1800, flueGasTempEnriched: 1900, o2FlueGas: 5,
        o2FlueGasEnriched: 1, combAirTemp: 900, combAirTempEnriched: 80, fuelConsumption: 10
    };

    var res = bindings.o2Enrichment(inp);
    t.equal(rnd(res.availableHeatInput), rnd(61.97028577716948), 'res.availableHeatInput is ' + res.availableHeatInput);
    t.equal(rnd(res.availableHeatEnriched), rnd(74.2210855230995), 'res.availableHeatEnriched is ' + res.availableHeatEnriched);
    t.equal(rnd(res.fuelSavingsEnriched), rnd(16.505821303458657), 'res.fuelSavingsEnriched is ' + res.fuelSavingsEnriched);
    t.equal(rnd(res.fuelConsumptionEnriched), rnd(8.349417869654134), 'res.fuelConsumptionEnriched is ' + res.fuelConsumptionEnriched);

    inp.flueGasTemp = 2200;
    inp.flueGasTempEnriched = 2300;
    res = bindings.o2Enrichment(inp);
    t.equal(rnd(res.availableHeatInput), rnd(49.7183629149), 'res.availableHeatInput is ' + res.availableHeatInput);
    t.equal(rnd(res.availableHeatEnriched), rnd(69.9474376972), 'res.availableHeatEnriched is ' + res.availableHeatEnriched);
    t.equal(rnd(res.fuelSavingsEnriched), rnd(28.9203942964), 'res.fuelSavingsEnriched is ' + res.fuelSavingsEnriched);
    t.equal(rnd(res.fuelConsumptionEnriched), rnd(7.1079605704), 'res.fuelConsumptionEnriched is ' + res.fuelConsumptionEnriched);

    inp.o2FlueGas = 8;
    inp.o2FlueGasEnriched = 3;
    res = bindings.o2Enrichment(inp);
    t.equal(rnd(res.availableHeatInput), rnd(42.6248055296), 'res.availableHeatInput is ' + res.availableHeatInput);
    t.equal(rnd(res.availableHeatEnriched), rnd(65.7672982588), 'res.availableHeatEnriched is ' + res.availableHeatEnriched);
    t.equal(rnd(res.fuelSavingsEnriched), rnd(35.1884497948), 'res.fuelSavingsEnriched is ' + res.fuelSavingsEnriched);
    t.equal(rnd(res.fuelConsumptionEnriched), rnd(6.4811550205), 'res.fuelConsumptionEnriched is ' + res.fuelConsumptionEnriched);

    inp.combAirTemp = 1100;
    inp.combAirTempEnriched = 110;
    res = bindings.o2Enrichment(inp);
    t.equal(rnd(res.availableHeatInput), rnd(49.1204784776), 'res.availableHeatInput is ' + res.availableHeatInput);
    t.equal(rnd(res.availableHeatEnriched), rnd(66.3723712295), 'res.availableHeatEnriched is ' + res.availableHeatEnriched);
    t.equal(rnd(res.fuelSavingsEnriched), rnd(25.9925816002), 'res.fuelSavingsEnriched is ' + res.fuelSavingsEnriched);
    t.equal(rnd(res.fuelConsumptionEnriched), rnd(7.40074184), 'res.fuelConsumptionEnriched is ' + res.fuelConsumptionEnriched);
});

test('flowCalculations', function (t) {
    t.plan(4);
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
    
    var res = bindings.flowCalculations(inp);
    t.equal(rnd(res.flow), rnd(647312.3211663722), 'res.flow is ' + res.flow);
    t.equal(rnd(res.heatInput), rnd(75865.00404069883), 'res.heatInput is ' + res.heatInput);
    t.equal(rnd(res.totalFlow), rnd(10356997.138661955), 'res.totalFlow is ' + res.totalFlow);

});

test('humidityRatio', function (t) {
    t.plan(3);
    t.type(bindings.humidityRatio, 'function');
    var inp = {};

    inp.atmosphericPressure = 0.8;
    inp.dryBulbTemp = 120;
    inp.relativeHumidity = 30;
    inp.wetBulbTemp = 85;

    var res = bindings.humidityRatio(inp);
    t.equal(rnd(res.humidityRatioUsingRH), rnd(0.028113628942036617), 'res.humidityRatioUsingRH is ' + res.humidityRatioUsingRH);
    t.equal(rnd(res.humidityRatioUsingWBT), rnd(0.024579434176341366), 'res.humidityRatioUsingWBT is ' + res.humidityRatioUsingWBT);

});