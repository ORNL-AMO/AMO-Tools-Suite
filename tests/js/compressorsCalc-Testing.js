const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressorsCalc' });


function rnd(value) {
    return Number(Math.round(value));
}

// //ID: 629 Lubricant inject screw load/unload
//NOT CLOSE
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