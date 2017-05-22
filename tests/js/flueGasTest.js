const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'losses'});

test('flueGasByVolume', function (t) {
    t.plan(2);
    t.type(bindings.flueGasLossesByVolume, 'function');
    var inp = {
        flueGasTemperature: 700,
        excessAirPercentage: 9.0,
        combustionAirTemperature: 125,
        substance: 'js test substance',
        CH4: 94.1,
        C2H6: 2.4,
        N2: 1.41,
        H2: 0.03,
        C3H8: 0.49,
        C4H10_CnH2n: 0.29,
        H2O: 0,
        CO: 0.42,
        CO2: 0.71,
        SO2: 0,
        O2: 0
    };

    var res = bindings.flueGasLossesByVolume(inp);
    t.equal(res, 0.7689954663391211, res + ' != 0.7689954663391211');
});

test('flueGasByMass', function (t) {
    t.plan(2);
    t.type(bindings.flueGasLossesByMass, 'function');

    var inp = {
        flueGasTemperature: 700,
        excessAirPercentage: 9.0,
        combustionAirTemperature: 125,
        fuelTemperature: 70,
        moistureInAirComposition: 1.0,
        ashDischargeTemperature: 100,
        unburnedCarbonInAsh: 1.5,
        carbon: 75.0,
        hydrogen: 5.0,
        sulphur: 1.0,
        inertAsh: 9.0,
        o2: 7.0,
        moisture: 0.0,
        nitrogen: 1.5
    };

    var res = bindings.flueGasLossesByMass(inp);
    t.equal(res, 0.8222977480707968, res + ' != 0.8222977480707968');
});
