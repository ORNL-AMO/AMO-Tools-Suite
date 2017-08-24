/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

test('headTool', function (t) {
    t.plan(13);
    t.type(bindings.headTool, 'function');

    var inp = {
        specificGravity: 1.0,
        flowRate: 2000,
        suctionPipeDiameter: 17.9,
        suctionGaugePressure: 5,
        suctionGaugeElevation: 5,
        suctionLineLossCoefficients: 1,
        dischargePipeDiameter: 15,
        dischargeGaugePressure: 50,
        dischargeGaugeElevation: 1,
        dischargeLineLossCoefficients: 1
    };

    var res = bindings.headTool(inp);

    t.equal(res.pumpHead, 100.39593224945455, res.pumpHead + ' != ' + 100.39593224945455);
    t.equal(res.differentialElevationHead, -4, res.differentialElevationHead + ' != ' + -4);
    t.equal(res.differentialPressureHead, 103.98613494168427, res.differentialPressureHead + ' != ' + 103.98613494168427);
    t.equal(res.differentialVelocityHead, 0.10385896098722718, res.differentialVelocityHead + ' != ' + 0.10385896098722718);
    t.equal(res.estimatedDischargeFrictionHead, 0.20489865388514306, res.estimatedDischargeFrictionHead + ' != ' + 0.20489865388514306);
    t.equal(res.estimatedSuctionFrictionHead, 0.10103969289791588, res.estimatedSuctionFrictionHead + ' != ' + 0.10103969289791588);

    inp = {
        specificGravity: 1.0,
        flowRate: 2000,
        suctionPipeDiameter: 17.9,
        suctionGaugePressure: 10,
        suctionGaugeElevation: 15,
        suctionLineLossCoefficients: 0.1,
        dischargePipeDiameter: 60,
        dischargeGaugePressure: 20,
        dischargeGaugeElevation: 10,
        dischargeLineLossCoefficients: 0.9
    };

    res = bindings.headTool(inp);
    t.equal(res.pumpHead, 18.018614995629626, res.pumpHead + ' != ' + 18.018614995629626);
    t.equal(res.differentialElevationHead, -5, res.differentialElevationHead + ' != ' + -5);
    t.equal(res.differentialPressureHead, 23.108029987040947, res.differentialPressureHead + ' != ' + 23.108029987040947);
    t.equal(res.differentialVelocityHead, -0.10023930753117705, res.differentialVelocityHead + ' != ' + -0.10023930753117705);
    t.equal(res.estimatedDischargeFrictionHead, 0.0007203468300649561, res.estimatedDischargeFrictionHead + ' != ' + 0.0007203468300649561);
    t.equal(res.estimatedSuctionFrictionHead, 0.01010396928979159, res.estimatedSuctionFrictionHead + ' != ' + 0.01010396928979159);
});

test('headToolSuctionTank', function (t) {
    t.plan(13);
    t.type(bindings.headToolSuctionTank, 'function');

    var inp = {
        specificGravity: 1.0,
        flowRate: 2000,
        suctionPipeDiameter: 17.9,
        suctionTankGasOverPressure: 115,
        suctionTankFluidSurfaceElevation: 0,
        suctionLineLossCoefficients: 1,
        dischargePipeDiameter: 10,
        dischargeGaugePressure: 124,
        dischargeGaugeElevation: 0,
        dischargeLineLossCoefficients: 1
    };

    var res = bindings.headToolSuctionTank(inp);

    t.equal(res.pumpHead, 22.972865551821844, res.pumpHead + ' != ' + 22.972865551821844);
    t.equal(res.differentialElevationHead, 0.0, res.differentialElevationHead + ' != ' + 0.0);
    t.equal(res.differentialPressureHead, 20.797226988336853, res.differentialPressureHead + ' != ' + 20.797226988336853);
    t.equal(res.differentialVelocityHead, 1.0372994352935365, res.differentialVelocityHead + ' != ' + 1.0372994352935365);
    t.equal(res.estimatedDischargeFrictionHead, 1.0372994352935365, res.estimatedDischargeFrictionHead + ' != ' + 1.0372994352935365);
    t.equal(res.estimatedSuctionFrictionHead, 0.10103969289791588, res.estimatedSuctionFrictionHead + ' != ' + 0.10103969289791588);


    inp = {
        specificGravity: 1.0,
        flowRate: 2000,
        suctionPipeDiameter: 17.9,
        suctionTankGasOverPressure: 105,
        suctionTankFluidSurfaceElevation: 5,
        suctionLineLossCoefficients: 1,
        dischargePipeDiameter: 15,
        dischargeGaugePressure: 124,
        dischargeGaugeElevation: 0,
        dischargeLineLossCoefficients: 1
    };

    res = bindings.headToolSuctionTank(inp);
    t.equal(res.pumpHead, 39.41609397604601, res.pumpHead + ' != ' + 39.41609397604601);
    t.equal(res.differentialElevationHead, -5, res.differentialElevationHead + ' != ' + -5);
    t.equal(res.differentialPressureHead, 43.9052569753778, res.differentialPressureHead + ' != ' + 43.9052569753778);
    t.equal(res.differentialVelocityHead, 0.20489865388514306, res.differentialVelocityHead + ' != ' + 0.20489865388514306);
    t.equal(res.estimatedDischargeFrictionHead, 0.20489865388514306, res.estimatedDischargeFrictionHead + ' != ' + 0.20489865388514306);
    t.equal(res.estimatedSuctionFrictionHead, 0.10103969289791588, res.estimatedSuctionFrictionHead + ' != ' + 0.10103969289791588);
});
