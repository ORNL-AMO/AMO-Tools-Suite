const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressedAir'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 2) + 'e-' + 2);
}

test('CompressedAirCentrifugal LoadUnload', function (t) {
    t.plan(41);
    t.type(bindings.CompressedAir, 'function');

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
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);

    input.computeFrom = 1;
    input.computeFromVal = 0.24;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);

    input.computeFrom = 2;
    input.computeFromVal = 162.828;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);

    input.computeFrom = 3;
    input.computeFromVal = 753.12;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [162.828, 753.12, 0.36, 0.24]);

    input.computeFrom = 4;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.00945;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [162.865, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [162.865, 753.12, 0.36, 0.24]);
});

test('CompressedAirCentrifugal ModulationUnload', function (t) {
    t.plan(41);
    t.type(bindings.CompressedAir, 'function');

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
    compare(bindings.CompressedAir(input), [425.162, 2820.95, 0.94, 0.93875]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [425.162, 2807, 0.94, 0.947507]);

    input.computeFrom = 1;
    input.computeFromVal = 0.24;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [165.226, 753.12, 0.365302, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [165.226, 753.12, 0.365302, 0.24]);

    input.computeFrom = 2;
    input.computeFromVal = 425.162;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [425.162, 2820.95, 0.94, 0.93875]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [425.162, 2807, 0.94, 0.947507]);

    input.computeFrom = 3;
    input.computeFromVal = 753.12;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [165.226, 753.12, 0.365302, 0.24]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [165.226, 753.12, 0.365302, 0.24]);

    input.computeFrom = 4;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02467;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [425.174, 2821.02, 0.940026, 0.938777]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [425.174, 2807.06, 0.94, 0.947507]);
});

test('CompressedAirCentrifugal BlowOff', function (t) {
    t.plan(61);
    t.type(bindings.CompressedAir, 'function');

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
    compare(bindings.CompressedAir(input), [370.886, 376.788, 0.82, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [370.886, 1080.56, 0.82, 0.344346, 2133.21, 0.6798]);

    input.computeFrom = 1;
    input.computeFromVal = 0.01;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [370.9, 31.38, 0.820031, 0.01, 3182.39, 1.01415]);

    input.computeFrom = 2;
    input.computeFromVal = 370.9;
    input.percentageBlowOff = 0.6798;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [370.9, 376.788, 0.8200309, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [370.9, 1080.56, 0.8200301, 0.344346, 2133.21, 0.6798]);

    input.computeFrom = 3;
    input.computeFromVal = 31.38;
    input.adjustForDischargePressure = false;
    compare(bindings.CompressedAir(input), [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [370.9, 31.38, 0.820031, 0.01, 3182.39, 1.01415]);

    input.computeFrom = 4;
    input.computeFromVal = 50;
    input.adjustForDischargePressure = false;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02152;
    input.percentageBlowOff = 0.6798;
    compare(bindings.CompressedAir(input), [370.885, 376.788, 0.82, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    compare(bindings.CompressedAir(input), [370.885, 1080.56, 0.82, 0.344346, 2133.21, 0.6798]);
});