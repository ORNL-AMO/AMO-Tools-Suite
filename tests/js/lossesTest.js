const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('atmosphere', function (t) {
    t.plan(2);
    t.type(bindings.atmosphere, 'function');

    var inp = {
        inletTemperature: 100.0, outletTemperature: 1400.0, flowRate: 1200.0, correctionFactor: 1.0, specificHeat: 0.02
    };

    var res = bindings.atmosphere(inp);
    t.equal(res, 31200.0, res + " != 31200.0");
});

test('auxiliaryPower', function (t) {
    t.plan(6);
    t.type(bindings.auxiliaryPowerLoss, 'function');

    var inp = {
        motorPhase: 3, supplyVoltage: 460, avgCurrent: 19, powerFactor: 0.85, operatingTime: 100
    };

    var res = bindings.auxiliaryPowerLoss(inp);
    t.equal(rnd(res), rnd(43905.3405494047));

    inp.supplyVoltage = 510;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(rnd(res), rnd(48677.66017434));

    inp.avgCurrent = 25;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(rnd(res), rnd(64049.5528609737));

    inp.powerFactor = 0.55;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(rnd(res), rnd(41443.8283218065));

    inp.operatingTime = 75;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(rnd(res), rnd(31082.8712413549));
});

test('fixtureLosses', function (t) {
    t.plan(2);
    t.type(bindings.fixtureLosses, 'function');

    var inp = {
        specificHeat: 0.122, feedRate: 1250.0, initialTemperature: 300.0, finalTemperature: 1800.0, correctionFactor: 1.0
    };

    var res = bindings.fixtureLosses(inp);
    t.equal(res, 228750.0, res + " != 228750.0");
});

test('flueGasByVolume', function (t) {
    t.plan(5);
    t.type(bindings.flueGasLossesByVolume, 'function');
    var inp = {
        flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, substance: 'test substance',
        CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0,
        O2: 0
    };

    var res = bindings.flueGasLossesByVolume(inp);
    t.equal(rnd(res), rnd(0.7689954663391211), res + ' != 0.7689954663391211');


    inp = {
        CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0,
        O2: 0
    };

    t.type(bindings.flueGasByVolumeCalculateHeatingValue, 'function');
    res = bindings.flueGasByVolumeCalculateHeatingValue(inp)
    t.equal(rnd(res.heatingValue), rnd(22630.355481));
    t.equal(rnd(res.specificGravity), rnd(0.631783));
});

test('flueGasByMass', function (t) {
    t.plan(4);
    t.type(bindings.flueGasLossesByMass, 'function');

    var inp = {
        flueGasTemperature: 700, excessAirPercentage: 9.0, combustionAirTemperature: 125, fuelTemperature: 70,
        moistureInAirComposition: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
        carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5
    };

    var res = bindings.flueGasLossesByMass(inp);
    t.equal(rnd(res), rnd(0.8222977480707968), res + ' != 0.8222977480707968');

    inp = {
        carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5
    };

    t.type(bindings.flueGasByMassCalculateHeatingValue, 'function');

    res = bindings.flueGasByMassCalculateHeatingValue(inp)
    t.equal(rnd(res), rnd(13877.969543))

});

test('flueGasLossesByVolumeGivenO2', function (t) {
    t.plan(7);
    t.type(bindings.flueGasLossesByVolumeGivenO2, 'function');
    var inp = {
        flueGasTemperature: 700, flueGasO2: 0.5, combustionAirTemperature: 125, substance: 'test substance',
        CH4: 94.1, C2H6: 2.4, N2: 1.41, H2: 0.03, C3H8: 0.49, C4H10_CnH2n: 0.29, H2O: 0, CO: 0.42, CO2: 0.71, SO2: 0,
        O2: 0
    };

    var res = bindings.flueGasLossesByVolumeGivenO2(inp);
    t.equal(res['heatLoss'], 0.7758857340516403, res + ' != 0.7758857340516403');
    t.equal(res['excessAir'], 2.3172209488353976, res + ' != 2.3172209488353976');

    inp['flueGasO2'] = 3.0;
    res = bindings.flueGasLossesByVolumeGivenO2(inp);
    t.equal(res['heatLoss'], 0.7622712144825897, res + ' != 0.7622712144825897');
    t.equal(res['excessAir'], 15.52234414568954, res + ' != 15.52234414568954');

    inp['flueGasO2'] = 7.0;
    res = bindings.flueGasLossesByVolumeGivenO2(inp);
    t.equal(res['heatLoss'], 0.731683496609056, res + ' != 0.731683496609056');
    t.equal(res['excessAir'], 45.197503654937584, res + ' != 45.197503654937584');
});

test('flueGasLossesByMassGivenO2', function (t) {
    t.plan(7);
    t.type(bindings.flueGasLossesByMassGivenO2, 'function');

    var inp = {
        flueGasTemperature: 700, flueGasO2: 0.5, combustionAirTemperature: 125, fuelTemperature: 70,
        moistureInAirComposition: 1.0, ashDischargeTemperature: 100, unburnedCarbonInAsh: 1.5,
        carbon: 75.0, hydrogen: 5.0, sulphur: 1.0, inertAsh: 9.0, o2: 7.0, moisture: 0.0, nitrogen: 1.5
    };

    var res = bindings.flueGasLossesByMassGivenO2(inp);
    t.equal(res['heatLoss'], 0.8297708723770466, res + ' != 0.8297708723770466');
    t.equal(res['excessAir'], 2.29427816716376, res + ' != 2.29427816716376');

    inp['flueGasO2'] = 3.0;
    res = bindings.flueGasLossesByMassGivenO2(inp);
    t.equal(res['heatLoss'], 0.8151987636583022, res + ' != 0.8151987636583022');
    t.equal(res['excessAir'], 15.368657569989644, res + ' != 15.368657569989644');

    inp['flueGasO2'] = 7.0;
    res = bindings.flueGasLossesByMassGivenO2(inp);
    t.equal(res['heatLoss'], 0.7824331921965915, res + ' != 0.7824331921965915');
    t.equal(res['excessAir'], 44.75000361875009, res + ' != 44.75000361875009');
});


test('gasCoolingLosses', function (t) {
    t.plan(3);
    t.type(bindings.gasCoolingLosses, 'function');

    var inp = {
        flowRate: 2500, initialTemperature: 80, finalTemperature: 280, specificHeat: 0.02, correctionFactor: 1.0,
        gasDensity: 1
    };

    var res = bindings.gasCoolingLosses(inp);
    t.equal(res, 600000.0, res + ' != 600000.0');

    inp.flowRate = 600;
    inp.finalTemperature = 350;
    res = bindings.gasCoolingLosses(inp);
    t.equal(res, 194400.0, res + ' != 194400.0');
});

test('gasLoadChargeMaterial', function (t) {
    t.plan(2);
    t.type(bindings.gasLoadChargeMaterial, 'function');

    var inp = {
        thermicReactionType: 0, specificHeatGas: 0.24, feedRate: 1000, percentVapor: 15, initialTemperature: 80,
        dischargeTemperature: 1150, specificHeatVapor: 0.5, percentReacted: 100, reactionHeat: 80, additionalHeat: 5000
    };

    var res = bindings.gasLoadChargeMaterial(inp);
    t.equal(res, 383530.0, res + ' != 383530.0');
});

test('leakageLosses', function (t) {
    t.plan(2);
    t.type(bindings.leakageLosses, 'function');

    var inp = {
        draftPressure: 0.1, openingArea: 3, leakageGasTemperature: 1600, ambientTemperature: 80,
        coefficient: 0.8052, specificGravity: 1.02, correctionFactor: 1.0
    };

    var res = bindings.leakageLosses(inp);
    t.equal(rnd(res), rnd(2850767.216228273), res + ' != 2850767.216228273');
});

test('liquidCoolingLosses', function (t) {
    t.plan(2);
    t.type(bindings.liquidCoolingLosses, 'function');

    var inp = {
        flowRate: 100, density: 9.35, initialTemperature: 80, outletTemperature: 210,
        specificHeat: 0.52, correctionFactor: 1.0
    };

    var res = bindings.liquidCoolingLosses(inp);
    t.equal(res, 3792360.0, res + ' != 3792360.0');
});

test('liquidLoadChargeMaterial', function (t) {
    t.plan(2);
    t.type(bindings.liquidLoadChargeMaterial, 'function');

    var inp = {
        thermicReactionType: 0, specificHeatLiquid: 0.48, vaporizingTemperature: 240, latentHeat: 250,
        specificHeatVapor: 0.25, chargeFeedRate: 1000, initialTemperature: 70, dischargeTemperature: 320,
        percentVaporized: 100, percentReacted: 25, reactionHeat: 50, additionalHeat: 0
    };


    var res = bindings.liquidLoadChargeMaterial(inp);
    t.equal(res, 364100.0, res + ' != 364100.0');
});

test('openingLosses - both circular and quad', function (t) {
    t.plan(3);
    t.type(bindings.openingLossesCircular, 'function');

    var inp = {
        emissivity: 0.95, diameterLength: 12, thickness: 9, ratio: 1.33, ambientTemperature: 75,
        insideTemperature: 1600, percentTimeOpen: 100, viewFactor: 0.70
    };


    var res = bindings.openingLossesCircular(inp);
    t.equal(rnd(res), rnd(16038.269976979091), res + ' != 16038.269976979091');


    inp = {
        emissivity: 0.95, length: 48, widthHeight: 15, thickness: 9, ratio: 1.67, ambientTemperature: 75,
        insideTemperature: 1600, percentTimeOpen: 20, viewFactor: 0.64
    };
    res = bindings.openingLossesQuad(inp);
    t.equal(rnd(res), rnd(18670.2258869289), res + ' != 18670.2258869289');
});

test('slagOtherMaterialLosses', function (t) {
    t.plan(3);
    t.type(bindings.slagOtherMaterialLosses, 'function');

    var inp = {
        weight: 3, inletTemperature: 500, outletTemperature: 550, specificHeat: 0.2479, correctionFactor: 1.0
    };

    var res = bindings.slagOtherMaterialLosses(inp);
    t.equal(res, 37.185, res + ' != 37.185');

    inp = {
        weight: 10, inletTemperature: 725, outletTemperature: 850, specificHeat: 0.033, correctionFactor: 0.8
    };
    res = bindings.slagOtherMaterialLosses(inp);
    t.equal(res, 33.0, res + ' != 33.0');
});

test('solidLoadChargeMaterial', function (t) {
    t.plan(2);
    t.type(bindings.solidLoadChargeMaterial, 'function');

    var inp = {
        thermicReactionType: 1, specificHeatSolid: 0.15, latentHeat: 60, specificHeatLiquid: 0.481, meltingPoint: 2900,
        chargeFeedRate: 10000, waterContentCharged: 0.1, waterContentDischarged: 0, initialTemperature: 70,
        dischargeTemperature: 2200, waterVaporDischargeTemperature: 500, chargeMelted: 0, chargeReacted: 1,
        reactionHeat: 100, additionalHeat: 0
    };

    var res = bindings.solidLoadChargeMaterial(inp);
    t.equal(res, 3204310.28, res + ' != 3204310.28');
});

test('wallLosses', function (t) {
    t.plan(2);
    t.type(bindings.wallLosses, 'function');

    var inp = {
        surfaceArea: 500, ambientTemperature: 80, surfaceTemperature: 225, windVelocity: 10,
        surfaceEmissivity: 0.9, conditionFactor: 1.394, correctionFactor: 1
    };

    var res = bindings.wallLosses(inp);
    t.equal(rnd(res), rnd(399122.25367509428), res + ' != 399122.25367509428');
});

test('wallLosses', function (t) {
    t.plan(2);
    t.type(bindings.waterCoolingLosses, 'function');

    var inp = {
        flowRate: 100, initialTemperature: 80, outletTemperature: 120, correctionFactor: 1
    };

    var res = bindings.waterCoolingLosses(inp);
    t.equal(rnd(res), rnd(1989032.7936134234), res + ' != 1989032.7936134234');
});

test('exhaustGasEAF', function (t) {
    t.plan(2);
    t.type(bindings.exhaustGasEAF, 'function');

    var inp = {
        offGasTemp: 2800, CO: 12, H2: 10, combustibleGases: 3, vfr: 8000, dustLoading: 0.001
    };

    var res = bindings.exhaustGasEAF(inp);
    t.equal(rnd(res), rnd(12553119.018404908), res + ' != 12553119.018405');
});

test('availableHeat', function (t) {
    t.plan(2);
    t.type(bindings.availableHeat, 'function');

    var inp = {
        excessAir: 65, combustionAirTemp: 300, exhaustGasTemp: 550
    };

    var res = bindings.availableHeat(inp);
    t.equal(rnd(res), rnd(82.72794239800001), res + ' != 82.72794239800001');
});

test('energyInputExhaustGasLosses', function (t) {
    t.plan(3);
    t.type(bindings.energyInputExhaustGasLosses, 'function');

    var inp = {
        totalHeatInput: 5000000, electricalPowerInput: 0, availableHeat: 82.73, otherLosses: 500
    };

    var res = bindings.energyInputExhaustGasLosses(inp);
    t.equal(rnd(res["heatDelivered"]), rnd(1212.3388042203985 * 3412), res["heatDelivered"] + ' != 1212.339 * 3412');
    t.equal(rnd(res["exhaustGasLosses"]), rnd(863499.9999999998), res["exhaustGasLosses"] + ' != 863500');
});