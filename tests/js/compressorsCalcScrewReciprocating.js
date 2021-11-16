const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressorsCalc' });


function rnd(value) {
    return Number(Math.round(value));
}

//ID: 737 Lubricant injected screw modulation with unloading
test('COMP ID: 737 Lubricant injected screw modulation with unloading', function (t) {
    t.plan(8);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 1167,
        capacityAtMaxFullFlow: 1167,
        capacityAtUnload: 584,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: 1,
        dischargePsiFullLoad: 140,
        dischargePsiMax: 140,
        loadFactorUnloaded: 0.20529197080291972,
        lubricantType: 0,
        modulatingPsi: 20,
        noLoadPowerFM: 0.65,
        powerAtFullLoad: 219.2,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 45,
        powerAtNolLoad: 45,
        powerAtUnload: 180.9,
        powerMax: 219.2,
        powerMaxPercentage: 1,
        pressureAtUnload: 150,
        receiverVolume: 13,
        stageType: 1,
        unloadPointCapacity: 50,
        unloadSumpPressure: 15
    }

    //9% AIRFLOW
    input.computeFromVal = .09;
    // 1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(63));
    t.equal(rnd(results.powerCalculated), rnd(137));
    //POWER CALCULATED SLIGHTLY DIFFERENT FOR %POWER CALC VS %CAPACITY

    input.computeFromVal = .63;
    // 0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(9));
    t.equal(rnd(results.powerCalculated), rnd(138));
    //POWER CALCULATED SLIGHTLY DIFFERENT FOR %POWER CALC VS %CAPACITY

    //91% AIRFLOW
    input.computeFromVal = .91;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(96.7));
    t.equal(rnd(results.powerCalculated), rnd(212.04));

    input.computeFromVal = .967;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(91));
    t.equal(rnd(results.powerCalculated), rnd(212.04));
});
//ID: 701 Lubricant injected screw modulation without unloading
test('COMP ID: 701 Lubricant injected screw modulation without unloading', function (t) {
    t.plan(4);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 1048,
        capacityAtMaxFullFlow: undefined,
        capacityAtUnload: undefined,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: 3,
        dischargePsiFullLoad: 100,
        dischargePsiMax: undefined,
        loadFactorUnloaded: 0.6498498498498498,
        lubricantType: 0,
        modulatingPsi: 5,
        noLoadPowerFM: 0.65,
        powerAtFullLoad: 166.5,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 108.2,
        powerAtNolLoad: 108.2,
        powerAtUnload: undefined,
        powerMax: undefined,
        powerMaxPercentage: NaN,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 50,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .20;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(72.01));
    t.equal(rnd(results.powerCalculated), rnd(119.9));

    input.computeFromVal = .7201;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(20));
    t.equal(rnd(results.powerCalculated), rnd(119.9));
});
//ID: 728 Lubricant injected screw variable displacement
test('COMP ID: 728 Lubricant injected screw variable displacement', function (t) {
    t.plan(8);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 1390,
        capacityAtMaxFullFlow: 1390,
        capacityAtUnload: 556,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: 5,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 100,
        loadFactorUnloaded: 0.205,
        lubricantType: 0,
        modulatingPsi: 17,
        noLoadPowerFM: 0.57,
        powerAtFullLoad: 219.2,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 45,
        powerAtNolLoad: 45,
        powerAtUnload: 140,
        powerMax: 219.2,
        powerMaxPercentage: 1,
        pressureAtUnload: 110,
        receiverVolume: 13.4,
        stageType: 1,
        unloadPointCapacity: 40,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .09;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(57), "% Power 1");
    t.equal(rnd(results.powerCalculated), rnd(125), "Power Calculated 1");

    input.computeFromVal = .57;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    t.equal(rnd(results.powerCalculated), rnd(125), "Power Calculated 2");


    input.computeFromVal = .92;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(93), "% Power 2");
    t.equal(rnd(results.powerCalculated), rnd(204.72), "Power Calculated 3");

    input.computeFromVal = .937;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(92), "% Capacity 2");
    t.equal(rnd(results.powerCalculated), rnd(204.72), "Power Calculated 4");
});
// //ID: 629 Lubricant inject screw load/unload
test('COMP ID: 629 Lubricant inject screw load/unload', function (t) {
    t.plan(8);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 535,
        capacityAtMaxFullFlow: 531,
        capacityAtUnload: undefined,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: 0,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 110,
        loadFactorUnloaded: 0.20608899297423888,
        lubricantType: 0,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 85.4,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 17.6,
        powerAtNolLoad: 17.6,
        powerAtUnload: undefined,
        powerMax: 90.1,
        powerMaxPercentage: 1.0550351288056206,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    }



    input.computeFromVal = .09;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(71), "% Power 1");
    t.equal(rnd(results.powerCalculated), rnd(60), "Power Calculated 1");

    input.computeFromVal = .72;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    t.equal(rnd(results.powerCalculated), rnd(61), "Power Calculated 2");


    input.computeFromVal = .91;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(101.4), "% Power 2");
    t.equal(rnd(results.powerCalculated), rnd(86.54), "Power Calculated 3");

    input.computeFromVal = 1.014;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(91), "% Capacity 2");
    t.equal(rnd(results.powerCalculated), rnd(86.54), "Power Calaculated 4");
});
//ID: 629 Lubricant injected screw start/stop
test('COMP ID: 629 Lubricant inject screw start/stop', function (t) {
    t.plan(4);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 535,
        capacityAtMaxFullFlow: 531,
        capacityAtUnload: undefined,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.97,
        controlType: 4,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 110,
        loadFactorUnloaded: 0,
        lubricantType: 0,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 85.4,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 90.1,
        powerMaxPercentage: 1.0550351288056206,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    }


    input.computeFromVal = .35;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(35.95), "% Power 1");
    t.equal(rnd(results.powerCalculated), rnd(30.7), "Power Calculated 1");

    input.computeFromVal = .3595;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(35), "% Capacity 1");
    t.equal(rnd(results.powerCalculated), rnd(30.7), "Power Calculated 2");
});

//ID: 861 Lubricant free screw Load/Unload
test('COMP ID: 861 Lubricant free screw Load/Unload', function (t) {
    t.plan(4);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 535,
        capacityAtMaxFullFlow: 531,
        capacityAtUnload: undefined,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: 4,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 110,
        loadFactorUnloaded: 0,
        lubricantType: 0,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 85.4,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 90.1,
        powerMaxPercentage: 1.0550351288056206,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .35;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(35.95));
    t.equal(rnd(results.powerCalculated), rnd(30.7));


    input.computeFromVal = .3595;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(35));
    t.equal(rnd(results.powerCalculated), rnd(30.7));
});
// //ID: 861 Lubricant free start/stop
test('COMP ID: 861 Lubricant free start/stop', function (t) {
    t.plan(4);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 0.0003,
        capacityAtFullLoad: 231,
        capacityAtMaxFullFlow: 229,
        capacityAtUnload: undefined,
        compressorType: 1,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.99,
        controlType: 4,
        dischargePsiFullLoad: 115,
        dischargePsiMax: 125,
        loadFactorUnloaded: 0,
        lubricantType: 1,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 51.3,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 53.7,
        powerMaxPercentage: 1.0467836257309944,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .65;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    console.log('PERC POWER: ' + results.percentagePower)
    results.percentagePower = results.percentagePower * 100;
    //Test doc has 66.47 % Power...
    t.equal(rnd(results.percentagePower), rnd(67), "% Power 1");
    t.equal(rnd(results.powerCalculated), rnd(34.1), "Power Calculated 1");

    input.computeFromVal = .6647;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(65), "% Capacity 1");
    t.equal(rnd(results.powerCalculated), rnd(34.1), "Power Calculated 2");
});
// //ID: 1156 Reciprocating Load/Unload
test('COMP ID: 1156 Reciprocating Load/Unload', function (t) {
    t.plan(8);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: null,
        capacityAtFullLoad: 375,
        capacityAtMaxFullFlow: 372,
        capacityAtUnload: undefined,
        compressorType: 2,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.99,
        controlType: 0,
        dischargePsiFullLoad: 125,
        dischargePsiMax: 135,
        loadFactorUnloaded: 0.15968992248062017,
        lubricantType: 2,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 64.5,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 10.3,
        powerAtNolLoad: 10.3,
        powerAtUnload: undefined,
        powerMax: 67.6,
        powerMaxPercentage: 1.0480620155038758,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 100,
        unloadSumpPressure: null
    }

    input.computeFromVal = .10;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(24.5), "% Power 1");
    t.equal(rnd(results.powerCalculated), rnd(15.8), "Power Calculated 1");

    input.computeFromVal = .245;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    t.equal(rnd(results.powerCalculated), rnd(15.8), "Power Calculated 2");

    input.computeFromVal = .90;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(94), "% Power 2");
    t.equal(rnd(results.powerCalculated), rnd(60.3), "Power Calculated 3");
    //Test doc has 93.49% power...

    input.computeFromVal = .9349;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(90), "% Capacity 3");
    t.equal(rnd(results.powerCalculated), rnd(60.3), "Power Calculated 4");
});

//ID: 1156 Reciprocating Start/stop
test('COMP ID: 1156 Reciprocating Start/Stop', function (t) {
    t.plan(4);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: null,
        capacityAtFullLoad: 375,
        capacityAtMaxFullFlow: 372,
        capacityAtUnload: undefined,
        compressorType: 2,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.99,
        controlType: 4,
        dischargePsiFullLoad: 125,
        dischargePsiMax: 135,
        loadFactorUnloaded: 0,
        lubricantType: 2,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 64.5,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 67.6,
        powerMaxPercentage: 1.0480620155038758,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 100,
        unloadSumpPressure: null
    }
    input.computeFromVal = .35;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(35.66), "% Power 1");
    t.equal(rnd(results.powerCalculated), rnd(23), "Power Calculated 1");

    input.computeFromVal = .3566;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(35), "% Capacity");
    t.equal(rnd(results.powerCalculated), rnd(23), "Power Calculated 2");
});
//ID: 1187 Reciprocating multi-step unloading
test('COMP ID: 1187 Reciprocating multi-step unloading', function (t) {
    t.plan(8);
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: null,
        capacityAtFullLoad: 660,
        capacityAtMaxFullFlow: 655,
        capacityAtUnload: undefined,
        compressorType: 2,
        computeFrom: 1,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: 6,
        dischargePsiFullLoad: 115,
        dischargePsiMax: 125,
        loadFactorUnloaded: 0.15838800374882847,
        lubricantType: 2,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 106.7,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 16.9,
        powerAtNolLoad: 16.9,
        powerAtUnload: undefined,
        powerMax: 112.3,
        powerMaxPercentage: 1.0524835988753514,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: 1,
        unloadPointCapacity: 100,
        unloadSumpPressure: null
    }
    input.computeFromVal = .10;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(25), "% Power 1");
    t.equal(rnd(results.powerCalculated), rnd(26.1), "Power Calculated 1");
    //Test Doc has 24.48 % power


    input.computeFromVal = .2448;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    t.equal(rnd(results.powerCalculated), rnd(26.1), "Power Calculated 2");

    input.computeFromVal = .90;
    //1 = % Airflow
    input.computeFrom = 1;
    var results = bindings.CompressorsCalc(input);
    results.percentagePower = results.percentagePower * 100;
    t.equal(rnd(results.percentagePower), rnd(93.71), "% Power 2");
    t.equal(rnd(results.powerCalculated), rnd(99.9), "Power Calculated 3");

    input.computeFromVal = .9371;
    //0 = Percent Power
    input.computeFrom = 0;
    var results = bindings.CompressorsCalc(input);
    results.percentageCapacity = results.percentageCapacity * 100;
    t.equal(rnd(results.percentageCapacity), rnd(90), "% Capacity 2");
    t.equal(rnd(results.powerCalculated), rnd(99.9), "Power Calculated 4");
});