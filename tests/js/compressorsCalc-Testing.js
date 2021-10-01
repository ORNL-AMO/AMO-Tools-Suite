const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'compressorsCalc' });


function rnd(value) {
    return Number(Math.round(value));
}

//ID: 728 Lubricant injected screw variable displacement
// THESE ARE ALL CLOSE (PROBABLY WITHIN TOLERANCE..)
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