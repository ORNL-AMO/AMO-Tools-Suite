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
        blowdownTime: 40,
        capacityAtFullLoad: 65,
        capacityAtMaxFullFlow: 65,
        capacityAtUnload: 32,
        compressorType: 1, // screw
        computeFrom: 1, //PercentageCapacity
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: .49,
        controlType: 1, //ModulationUnload
        dischargePsiFullLoad: 175,
        dischargePsiMax: 175,
        loadFactorUnloaded: 1,
        lubricantType: 0, //Injected
        modulatingPsi: 20,
        powerAtFullLoad: 18.3,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 4,
        powerAtNolLoad: 4,
        powerAtUnload: 15.1,
        powerMax: 18.3,
        powerMaxPercentage: 1,
        receiverVolume: 13.3680624455617,
        stageType: 0, //Single
        unloadPointCapacity: 50,
        unloadSumpPressure: 15
    };

    input.computeFromVal = .46;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    console.log('perc capacity: ' + results.percentagePower);
    t.equal(results.percentagePower, 74.7);
});
