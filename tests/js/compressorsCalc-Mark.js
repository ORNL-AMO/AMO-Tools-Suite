const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressorsCalc'});

test('CompressorsCalcCentrifugal LoadUnload', function (t) {
    t.plan(2);
    t.type(bindings.CompressorsCalc, 'function');

    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: .0003,
        capacityAtFullLoad: 473,
        // capacityAtMaxFullFlow: 65,
        // capacityAtUnload: 33,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.8956,
        controlType: 0,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 110,
        loadFactorUnloaded: 1,
        lubricantType: 0,
        modulatingPsi: 10,
        powerAtFullLoad: 85.4,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 16.1,
        powerAtNolLoad: 16.1,
        powerAtUnload: 16.1,
        powerMax: 90.1,
        // powerMaxPercentage: 1,
        receiverVolume: 473,
        stageType: 0,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    };
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    console.log('perc capacity: ' + results.percentagePower);
    t.equal(results.percentagePower, 92.30);
});
