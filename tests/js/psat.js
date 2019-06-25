const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

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

    t.equal(rnd(res.pumpHead), rnd(100.39593224945455), res.pumpHead + ' != ' + 100.39593224945455);
    t.equal(res.differentialElevationHead, -4, res.differentialElevationHead + ' != ' + -4);
    t.equal(rnd(res.differentialPressureHead), rnd(103.98613494168427), res.differentialPressureHead + ' != ' + 103.98613494168427);
    t.equal(rnd(res.differentialVelocityHead), rnd(0.10385896098722718), res.differentialVelocityHead + ' != ' + 0.10385896098722718);
    t.equal(rnd(res.estimatedDischargeFrictionHead), rnd(0.20489865388514306), res.estimatedDischargeFrictionHead + ' != ' + 0.20489865388514306);
    t.equal(rnd(res.estimatedSuctionFrictionHead), rnd(0.10103969289791588), res.estimatedSuctionFrictionHead + ' != ' + 0.10103969289791588);

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
    t.equal(rnd(res.pumpHead), rnd(18.018614995629626), res.pumpHead + ' != ' + 18.018614995629626);
    t.equal(res.differentialElevationHead, -5, res.differentialElevationHead + ' != ' + -5);
    t.equal(rnd(res.differentialPressureHead), rnd(23.108029987040947), res.differentialPressureHead + ' != ' + 23.108029987040947);
    t.equal(rnd(res.differentialVelocityHead), rnd(-0.10023930753117705), res.differentialVelocityHead + ' != ' + -0.10023930753117705);
    t.equal(rnd(res.estimatedDischargeFrictionHead), rnd(0.0007203468300649561), res.estimatedDischargeFrictionHead + ' != ' + 0.0007203468300649561);
    t.equal(rnd(res.estimatedSuctionFrictionHead), rnd(0.01010396928979159), res.estimatedSuctionFrictionHead + ' != ' + 0.01010396928979159);
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

    t.equal(rnd(res.pumpHead), rnd(22.972865551821844), res.pumpHead + ' != ' + 22.972865551821844);
    t.equal(res.differentialElevationHead, 0.0, res.differentialElevationHead + ' != ' + 0.0);
    t.equal(rnd(res.differentialPressureHead), rnd(20.797226988336853), res.differentialPressureHead + ' != ' + 20.797226988336853);
    t.equal(rnd(res.differentialVelocityHead), rnd(1.0372994352935365), res.differentialVelocityHead + ' != ' + 1.0372994352935365);
    t.equal(rnd(res.estimatedDischargeFrictionHead), rnd(1.0372994352935365), res.estimatedDischargeFrictionHead + ' != ' + 1.0372994352935365);
    t.equal(rnd(res.estimatedSuctionFrictionHead), rnd(0.10103969289791588), res.estimatedSuctionFrictionHead + ' != ' + 0.10103969289791588);


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
    t.equal(rnd(res.pumpHead), rnd(39.41609397604601), res.pumpHead + ' != ' + 39.41609397604601);
    t.equal(res.differentialElevationHead, -5, res.differentialElevationHead + ' != ' + -5);
    t.equal(rnd(res.differentialPressureHead), rnd(43.9052569753778), res.differentialPressureHead + ' != ' + 43.9052569753778);
    t.equal(rnd(res.differentialVelocityHead), rnd(0.20489865388514306), res.differentialVelocityHead + ' != ' + 0.20489865388514306);
    t.equal(rnd(res.estimatedDischargeFrictionHead), rnd(0.20489865388514306), res.estimatedDischargeFrictionHead + ' != ' + 0.20489865388514306);
    t.equal(rnd(res.estimatedSuctionFrictionHead), rnd(0.10103969289791588), res.estimatedSuctionFrictionHead + ' != ' + 0.10103969289791588);
});

test('pump efficiency', function (t) {
    t.plan(3);
    t.type(bindings.pumpEfficiency, 'function');
    var inp = {};
    // Pump Style End suction ansi API
    inp.pump_style = 6;
    inp.flow_rate = 2000;
    var res = bindings.pumpEfficiency(inp);
    t.equal(rnd(res.average), rnd(83.97084437955112), 'res average is ' + res.average);
    t.equal(rnd(res.max), rnd(86.99584193768345), 'res max is ' + res.max);
});

test('nema', function (t) {
    t.plan(2);
    t.type(bindings.nema, 'function');
    var inp = {};
    // Line frequency 60
    inp.line_frequency = 0;
    inp.motor_rated_speed = 1200;
    // Efficiency class = Energy efficient
    inp.efficiency_class = 1;
    inp.efficiency = 0;
    inp.motor_rated_power = 200;
    inp.load_factor = 1;
    var res = bindings.nema(inp);
    t.equal(rnd(res), rnd(95.33208465291122), 'res is ' + res);
});

test('motorPerformance', function (t) {
    t.plan(4);
    t.type(bindings.motorPerformance, 'function');

//    {
//        MotorEfficiency mef(Motor::LineFrequency::FREQ60,1780,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,200,.75);
//        auto mefVal = mef.calculate();
//        Check100(95.69,mefVal);
//
//        MotorCurrent mc(200,1780,Motor::LineFrequency::FREQ60,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,.75,460,225.8);
//        auto mcVal = mc.calculate();
//        Check100(76.63,mcVal/225.8);
//
//        MotorPowerFactor pf(200,.75,mcVal,mefVal,460);
//        Check100(84.82,pf.calculate());
//    }

    var inp = {};
    // Line frequency 60
    inp.line_frequency = 0;
    // Energy efficient
    inp.efficiency_class = 1;
    inp.motor_rated_power = 200;
    inp.motor_rated_speed = 1780;
    inp.efficiency = 0;
    inp.load_factor = .25;
    inp.motor_rated_voltage = 460;
    inp.motor_rated_fla = 225.8;

    var res = bindings.motorPerformance(inp);
    t.equal(rnd(res.motor_current), rnd(36.1065805345533), 'res.motor_current is ' + res.motor_current);
    t.equal(rnd(res.efficiency), rnd(93.03933838910918), 'res.efficiency is ' + res.efficiency);
    t.equal(rnd(res.motor_power_factor), rnd(61.718229798145316), 'res.motor_power_factor is ' + res.motor_power_factor);
});

test('achievableEfficiency achievable efficiency', function (t) {
    t.plan(2);
    t.type(bindings.achievableEfficiency, 'function');
    var inp = {};
    inp.pump_style = 0;
    inp.specific_speed = 1170;
    var res = bindings.achievableEfficiency(inp);
    t.equal(rnd(res), rnd(1.8942771852074485), 'res is ' + res);
});

test('estimateFLA estimate full load amps', function (t) {
    t.plan(2);
    t.type(bindings.estFLA, 'function');
    var inp = {};
    inp.motor_rated_power = 200;
    inp.motor_rated_speed = 1780;
    inp.line_frequency = 1;
    // Either specify an efficiency class OR provide efficiency percentage
    inp.efficiency_class = 1;
    inp.efficiency = 0;
    inp.motor_rated_voltage = 460;
    var res = bindings.estFLA(inp);
    t.equal(rnd(res), rnd(225.800612262395), 'res is ' + res);
});
