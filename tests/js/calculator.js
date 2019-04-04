const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'calculator' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('electricityReduction', function (t) {
    console.log('========electricityReduction hello');
    t.plan(2);
    t.type(bindings.electricityReduction, 'function');

    var inp = {
        electricityReductionInputVec: [
            {
                hoursPerDay: 24,
                daysPerMonth: 30,
                monthsPerYear: 12,
                electricityCost: 0.12,
                measurementMethod: 0,
                MultimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                NameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                PowerMeterData: {
                    power: 50
                },
                OtherMethodData: {
                    energy: 432000
                },
                units: 1
            }
        ]
    };

    var res = bindings.electricityReduction(inp);
    console.log('res = ');
    console.log(res);


    t.equal(rnd(res.energyUse), rnd(407045.796185));
    t.equal(rnd(res.energyCost), rnd(48845.495542));

});