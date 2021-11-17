const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressorsCalc'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 2) + 'e-' + 2);
}

test('CompressorsCalcCentrifugal LoadUnload', function (t) {
    t.plan(41);
    t.type(bindings.CompressorsCalc, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.powerCalculated), rnd(expected[0]));
        t.equal(rnd(results.capacityCalculated), rnd(expected[1]));
        t.equal(rnd(results.percentagePower), rnd(expected[2]));
        t.equal(rnd(results.percentageCapacity), rnd(expected[3]));
    };

    var input = {
        compressorType : 0,
        controlType: 0,
        computeFrom: 0,

        fullLoadPressure: 100,

        powerAtFullLoad: 452.3,
        capacityAtFullLoad: 3138,

        capacityAtMinFullLoadPressure: 3200,
        capacityAtMaxFullLoadPressure: 2885,
        fullLoadPressure: 100,
        minFullLoadPressure: 91,
        maxFullLoadPressure: 117,

        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0,

        powerAtNoLoad: 71.3,
        capacityAtMaxFullFlow: 3005,
        powerAtUnload: 411.9,
        capacityAtUnload: 2731
    };

    input.computeFrom = 0;
    input.computeFromVal = 0.36;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [162.828, 753.84, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [162.828, 753.84, 0.36, 0.24]);

    input.computeFrom = 1;
    input.computeFromVal = 0.24;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [162.74, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [162.74, 753.12, 0.36, 0.24]);

    input.computeFrom = 2;
    input.computeFromVal = 162.828;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [162.83, 753.84, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [162.83, 753.84, 0.36, 0.24]);

    input.computeFrom = 3;
    input.computeFromVal = 753.12;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [162.74, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [162.74, 753.12, 0.36, 0.24]);

    input.computeFrom = 4;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 2.152;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [82, 88.126,0.1813,0.02808]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [82, 88.126,0.1813,0.02808]);
});

test('CompressorsCalcCentrifugal ModulationUnload', function (t) {
    t.plan(41);
    t.type(bindings.CompressorsCalc, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.powerCalculated), rnd(expected[0]));
        t.equal(rnd(results.capacityCalculated), rnd(expected[1]));
        t.equal(rnd(results.percentagePower), rnd(expected[2]));
        t.equal(rnd(results.percentageCapacity), rnd(expected[3]));
    };

    var input = {
        compressorType : 0,
        controlType: 1,
        computeFrom: 0,

        fullLoadPressure: 100,
        maxPressure: 58.23,

        powerAtFullLoad: 452.3,
        capacityAtFullLoad: 3138,

        capacityAtMinFullLoadPressure: 3200,
        capacityAtMaxFullLoadPressure: 2885,
        fullLoadPressure: 100,
        minFullLoadPressure: 91,
        maxFullLoadPressure: 117,

        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0,

        powerAtNoLoad: 71.3,
        capacityAtMaxFullFlow: 3005,
        powerAtUnload: 411.9,
        capacityAtUnload: 2731
    };

    input.computeFrom = 0;
    input.computeFromVal = 0.94;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [425.162, 2820.95, 0.94, 0.93875]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [425.162, 2820.92, 0.94, 0.94]);

    input.computeFrom = 1;
    input.computeFromVal = 0.24;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [165.226, 753.12, 0.365302, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [165.226, 753.12, 0.365302, 0.24]);

    input.computeFrom = 2;
    input.computeFromVal = 425.162;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [425.162, 2820.95, 0.94, 0.93875]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [425.162, 2820.92, 0.94, 0.94]);

    input.computeFrom = 3;
    input.computeFromVal = 753.12;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [165.226, 753.12, 0.365302, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [165.226, 753.12, 0.365302, 0.24]);

    input.computeFrom = 4;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 2.152;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [82, 85.7932, 0.1813, 0.027340]);
    input.adjustForDischargePressure = true;
    let res = bindings.CompressorsCalc(input);
    compare(res, [82, 85.7932, 0.1813, 0.027340]);

    console.log(" \n \nAdjusted Capacity for Discharge Pressure Change test\nFull Load: ", rnd(res.capacityAtFullLoadAdjusted), "\nMaxFullFlow: ", rnd(res.capacityAtMaxFullFlowAdjusted), "\n ");
});

test('CompressorsCalcCentrifugal BlowOff', function (t) {
    t.plan(61);
    t.type(bindings.CompressorsCalc, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.powerCalculated), rnd(expected[0]));
        t.equal(rnd(results.capacityCalculated), rnd(expected[1]));
        t.equal(rnd(results.percentagePower), rnd(expected[2]));
        t.equal(rnd(results.percentageCapacity), rnd(expected[3]));
        t.equal(rnd(results.surgeFlow), rnd(expected[4]));
        t.equal(rnd(results.percentageBlowOff), rnd(expected[5]));
    };

    var input = {
        compressorType : 0,
        controlType: 2,
        computeFrom: 0,

        fullLoadPressure: 100,

        powerAtFullLoad: 452.3,
        capacityAtFullLoad: 3138,

        capacityAtMinFullLoadPressure: 3200,
        capacityAtMaxFullLoadPressure: 2885,
        fullLoadPressure: 100,
        minFullLoadPressure: 91,
        maxFullLoadPressure: 117,

        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0,

        powerAtBlowOff: 370.9,
        surgeFlow: 2510
    };

    input.computeFrom = 0;
    input.computeFromVal = 0.82;
    input.adjustForDischargePressure = false;
    input.percentageBlowOff = 0.6798;
    compare(bindings.CompressorsCalc(input), [370.886, 376.788, 0.82, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [370.886, 376.79, 0.82, 0.120073, 2133.21, 0.6798]);

    input.computeFrom = 1;
    input.computeFromVal = 0.01;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);

    input.computeFrom = 2;
    input.computeFromVal = 370.9;
    input.percentageBlowOff = 0.6798;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [370.9, 376.788, 0.8200309, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [370.9, 376.79, 0.8200301, 0.120073, 2133.21, 0.6798]);

    input.computeFrom = 3;
    input.computeFromVal = 31.38;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressorsCalc(input), [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);

    input.computeFrom = 4;
    input.computeFromVal = 50;
    input.adjustForDischargePressure = false;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02152;
    input.percentageBlowOff = 0.6798;
    compare(bindings.CompressorsCalc(input), [0.82, 376.788, 0.0018129518, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressorsCalc(input), [0.82, 376.79, 0.0018129518, 0.120073, 2133.21, 0.6798]);
});

test('CompEEM_ReduceAirLeaks', function (t) {
    t.plan(4);
    t.type(bindings.CompEEM_ReduceAirLeaks, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.C_lkred), rnd(expected[0]));
        t.equal(rnd(results.C_usage_lkred), rnd(expected[1]));
        t.equal(rnd(results.PerC_lkred), rnd(expected[2]));
    };

    var input = {
        C_fl: 473,
        C_usage: 100,
        C_lk: 10,
        PerC_lkred: 0.5
    };

    compare(bindings.CompEEM_ReduceAirLeaks(input), [5, 95, 0.20084]);
});

test('CompEEM_ImproveEndUseEfficiency', function (t) {
    t.plan(3);
    t.type(bindings.CompEEM_ImproveEndUseEfficiency, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.C_af_red), rnd(expected[0]));
        t.equal(rnd(results.CPer_af_red), rnd(expected[1]));
    };

    var input = {
        C_fl: 473,
        C_usage: 236,
        C_avgaf_red: 20
    };

    compare(bindings.CompEEM_ImproveEndUseEfficiency(input), [216, 0.45666]);
});

test('CompEEM_ReduceSystemAirPressure', function (t) {
    t.plan(5);
    t.type(bindings.CompEEM_ReduceSystemAirPressure, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.P_fl_rpred), rnd(expected[0]));
        t.equal(rnd(results.kW_fl_rpadj), rnd(expected[1]));
        t.equal(rnd(results.C_usage_rpred), rnd(expected[2]));
        t.equal(rnd(results.PerC_rpred), rnd(expected[3]));
    };

    var input = {
        C_fl: 473,
        C_usage: 100,
        P_fl: 100,
        kW_fl: 85.4,
        P_rpred: 5,
        P_alt: 14.7,
        P_atm: 14.7
    };

    compare(bindings.CompEEM_ReduceSystemAirPressure(input), [95, 82.972, 97.384, 0.2059]);
});

test('CompEEM_AdjustCascadingSetPoint', function (t) {
    t.plan(4);
    t.type(bindings.CompEEM_AdjustCascadingSetPoint, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.kW_fl_adj), rnd(expected[0]));
        t.equal(rnd(results.C_usage_adj), rnd(expected[1]));
        t.equal(rnd(results.PerC_adj), rnd(expected[2]));
    };

    var input = {
        C_fl: 2578,
        C_usage: 1000,
        P_fl: 100,
        kW_fl: 414.4,
        P_fl_adj: 105,
        P_alt: 14.7,
        P_atm: 14.7
    };

    compare(bindings.CompEEM_AdjustCascadingSetPoint(input), [425.82, 1026.16, 0.398]);
});

test('CompEEM_PressureReductionSaving', function (t) {
    t.plan(4);
    t.type(bindings.CompEEM_PressureReductionSaving, 'function');

    var compare = function(results, expected) {
        t.equal(rnd(results.kW_savings), rnd(expected[0]));
        t.equal(rnd(results.kWh_savings), rnd(expected[1]));
        t.equal(rnd(results.cost_savings), rnd(expected[2]));
    };

    var input = {
        operatingHours: 8760,
        costPerkWh: 0.066,
        kW_fl_rated: 75,
        P_fl_rated: 125,
        dischargePresBaseline: 110,
        dischargePresMod: 100,
        P_alt: 14.7,
        P_atm: 14.7
    };

    compare(bindings.CompEEM_PressureReductionSaving(input), [3.6031, 31563.3423, 2083.18]);
});

test('CompEEM_kWAdjusted', function (t) {
    t.plan(2);
    t.type(bindings.CompEEM_kWAdjusted, 'function');

    var input = {
        kW_fl_rated: 75,
        P_fl_rated: 125,
        P_discharge: 110,
        P_alt: 14.7,
        P_atm: 14.7
    };

    t.equal(rnd(bindings.CompEEM_kWAdjusted(input).kW_adjusted), rnd(69.97));
});