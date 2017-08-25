/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('psat', function (t) {
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