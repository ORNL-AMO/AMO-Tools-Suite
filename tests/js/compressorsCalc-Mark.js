const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressorsCalc' });

test('CompressorsCalcCentrifugal LoadUnload', function (t) {
    t.plan(2);
    t.type(bindings.CompressorsCalc, 'function');

    // var input = {
    //     adjustForDischargePressure: false,
    //     applyPressureInletCorrection: false,
    //     atmosphericPsi: 14.7,
    //     blowdownTime: 40,
    //     capacityAtFullLoad: 65,
    //     capacityAtMaxFullFlow: 65,
    //     capacityAtUnload: 32,
    //     compressorType: 1, // screw
    //     computeFrom: 0, //PercentagePower
    //     computeFromPFAmps: 0,
    //     computeFromPFVoltage: 0,
    //     computeFromVal: .49,
    //     controlType: 1, //ModulationUnload
    //     dischargePsiFullLoad: 175,
    //     dischargePsiMax: 175,
    //     loadFactorUnloaded: 1,
    //     lubricantType: 0, //Injected
    //     modulatingPsi: 20,
    //     powerAtFullLoad: 18.3,
    //     powerAtFullLoadPercentage: 1,
    //     powerAtNoLoad: 4,
    //     powerAtNolLoad: 4,
    //     powerAtUnload: 15.1,
    //     powerMax: 18.3,
    //     powerMaxPercentage: 1,
    //     receiverVolume: 13.3680624455617,
    //     stageType: 0, //Single
    //     unloadPointCapacity: 50,
    //     unloadSumpPressure: 15
    // };

    // input.computeFromVal = .46;
    // var results = bindings.CompressorsCalc(input);
    // results.percentagePower = results.percentagePower * 100;
    // console.log('perc capacity: ' + results.percentagePower);
    // t.equal(results.percentagePower, 74.7);


    // var input = {
    //     adjustForDischargePressure: false,
    //     applyPressureInletCorrection: false,
    //     atmosphericPsi: 14.7,
    //     blowdownTime: 40,
    //     capacityAtFullLoad: 29,
    //     capacityAtMaxFullFlow: 29,
    //     capacityAtUnload: undefined,
    //     compressorType: 1, //screw
    //     computeFrom: 0,
    //     computeFromPFAmps: 0,
    //     computeFromPFVoltage: 0,
    //     computeFromVal: 1,
    //     controlType: 0, //loadUnload
    //     dischargePsiFullLoad: 175,
    //     dischargePsiMax: 185,
    //     loadFactorUnloaded: .2747,
    //     lubricantType: 0, //injected
    //     modulatingPsi: -9999,
    //     // modulatingPsi: 10,
    //     powerAtFullLoad: 9.1,
    //     powerAtFullLoadPercentage: 1,
    //     powerAtNoLoad: 2.5,
    //     powerAtNolLoad: 2.5,
    //     powerAtUnload: undefined,
    //     powerMax: 9.3,
    //     powerMaxPercentage: 1.0219780219780221,
    //     receiverVolume: 13.3680624455617,
    //     stageType: 0, //single
    //     unloadPointCapacity: 100,
    //     unloadSumpPressure: 15
    // };


    // var input = {
    //     adjustForDischargePressure: false,
    //     applyPressureInletCorrection: false,
    //     atmosphericPsi: 14.7,
    //     blowdownTime: -9999,
    //     capacityAtFullLoad: 270,
    //     capacityAtMaxFullFlow: 268,
    //     capacityAtUnload: 9,
    //     compressorType: 2,
    //     computeFrom: 0,
    //     computeFromPFAmps: 0,
    //     computeFromPFVoltage: 0,
    //     computeFromVal: 0.95,
    //     controlType: 0,
    //     dischargePsiFullLoad: 70,
    //     dischargePsiMax: 80,
    //     loadFactorUnloaded: 0.15903614457831325,
    //     lubricantType: 2,
    //     modulatingPsi: -9999,
    //     powerAtFullLoad: 41.5,
    //     powerAtFullLoadPercentage: 1,
    //     powerAtNoLoad: 6.6,
    //     powerAtNolLoad: 6.6,
    //     powerAtUnload: 4,
    //     powerMax: 44.9,
    //     powerMaxPercentage: 1.0819277108433734,
    //     receiverVolume: 13.3680624455617,
    //     stageType: 0,
    //     unloadPointCapacity: 100,
    //     unloadSumpPressure: -9999
    // }


    //single stage lubricant-injected rotary screw
    //variable displacement with unloading
    // let input = {
    //     adjustForDischargePressure: false,
    //     applyPressureInletCorrection: false,
    //     atmosphericPsi: 14.7,
    //     blowdownTime: 40,
    //     capacityAtFullLoad: 30,
    //     capacityAtMaxFullFlow: 30,
    //     capacityAtUnload: 12,
    //     compressorType: 1,
    //     computeFrom: 1,
    //     computeFromPFAmps: 0,
    //     computeFromPFVoltage: 0,
    //     computeFromVal: 0.985,
    //     controlType: 5,
    //     dischargePsiFullLoad: 175,
    //     dischargePsiMax: 175,
    //     loadFactorUnloaded: 0.2765957446808511,
    //     lubricantType: 0,
    //     modulatingPsi: 16.66699982,
    //     powerAtFullLoad: 9.4,
    //     powerAtFullLoadPercentage: 1,
    //     powerAtNoLoad: 2.6,
    //     powerAtNolLoad: 2.6,
    //     powerAtUnload: 6,
    //     powerMax: 9.4,
    //     powerMaxPercentage: 1,
    //     receiverVolume: 13.3680624455617,
    //     stageType: 0,
    //     unloadPointCapacity: 40,
    //     unloadSumpPressure: 15,
    //     noLoadPowerFM: .57
    // }

    // input.computeFromVal = .40;
    // var results = bindings.CompressorsCalc(input);
    // results.percentagePower = results.percentagePower * 100;
    // console.log('perc power: ' + results.percentagePower);
    // t.equal(63.829, results.percentagePower);
    // input.computeFromVal = .64;
    // input.computeFrom = 0;
    // var results = bindings.CompressorsCalc(input);
    // console.log('perc capacity: ' + results.percentageCapacity);
    // results.percentageCapacity = results.percentageCapacity * 100;
    // t.equal(40, results.percentageCapacity);


    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 637,
        capacityAtMaxFullFlow: 637,
        capacityAtUnload: 318,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.54,
        controlType: 1,
        dischargePsiFullLoad: 115,
        dischargePsiMax: 115,
        loadFactorUnloaded: 0.20630630630630628,
        lubricantType: 0,
        modulatingPsi: 20,
        noLoadPowerFM: 0.65,
        powerAtFullLoad: 111,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 22.9,
        powerAtNolLoad: 22.9,
        powerAtUnload: 91.5,
        powerMax: 111,
        powerMaxPercentage: 1,
        pressureAtUnload: 116,
        receiverVolume: 13.3680624455617,
        stageType: 1,
        unloadPointCapacity: 50,
        unloadSumpPressure: 15,
    }

    // input.computeFromVal = .64;
    // input.computeFrom = 0;
    // var results = bindings.CompressorsCalc(input);
    // console.log('perc capacity: ' + results.percentageCapacity);
    // results.percentageCapacity = results.percentageCapacity * 100;
    // t.equal(0, results.percentageCapacity);

    input.computeFromVal = .44;
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    console.log('perc power: ' + results.percentagePower);
    results.percentagePower = results.percentagePower * 100;
    t.equal(88, results.percentagePower);

});
