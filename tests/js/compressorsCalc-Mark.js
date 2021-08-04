const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressorsCalc'});

test('CompressorsCalcCentrifugal LoadUnload', function (t) {
    t.plan(2);
    t.type(bindings.CompressorsCalc, 'function');

    var input = {
        adjustForDischargePressure: true,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 50,
        capacityAtFullLoad: 65,
        capacityAtMaxFullFlow: 65,
        capacityAtUnload: 33,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: .49,
        controlType: 1,
        dischargePsiFullLoad: 175,
        dischargePsiMax: 175,
        loadFactorUnloaded: 1,
        lubricantType: 0,
        modulatingPsi: 20,
        powerAtFullLoad: 18.3,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 4,
        powerAtNolLoad: 4,
        powerAtUnload: 15.1,
        powerMax: 18.3,
        powerMaxPercentage: 1,
        receiverVolume: 13.3680624455617,
        stageType: 0,
        unloadPointCapacity: 50,
        unloadSumpPressure: 15
    };
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    console.log('perc capacity: ' + results.percentagePower);
    t.equal(results.percentagePower, 75);
});
