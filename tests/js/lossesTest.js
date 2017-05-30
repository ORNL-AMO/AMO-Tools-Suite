const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'phast'});

test('auxiliaryPower', function (t) {
    t.plan(6);
    t.type(bindings.auxiliaryPowerLoss, 'function');

    var inp = {
        motorPhase: 3,
        supplyVoltage: 460,
        avgCurrent: 19,
        powerFactor: 0.85,
        operatingTime: 100
    };

    var res = bindings.auxiliaryPowerLoss(inp);
    t.equal(res, 12.867405449429189, res + " != 12.867405449429189");

    inp.supplyVoltage = 510;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(res, 14.266036476541055, res + " != 14.266036476541055");

    inp.avgCurrent = 25;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(res, 18.771100627027707, res + " != 18.771100627027707");

    inp.powerFactor = 0.55;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(res, 12.146006288076753, res + " != 12.146006288076753");

    inp.operatingTime = 75;
    res = bindings.auxiliaryPowerLoss(inp);
    t.equal(res, 9.109504716057565, res + " != 9.109504716057565");
});