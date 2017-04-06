/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

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
    inp.line = 0;
    // Energy efficient
    inp.efficiency_class = 1;
    inp.motor_rated_power = 200;
    inp.motor_rated_speed = 1780;
    inp.efficiency = 0;
    inp.load_factor = .25;
    inp.motor_rated_voltage = 460;
    inp.fla = 225.8;

    var res = bindings.motorPerformance(inp);
    t.equal(res.current, 36.1065805345533, 'res.current is ' + res.current);
    t.equal(res.efficiency, 93.03933838910918, 'res.efficiency is ' + res.efficiency);
    t.equal(res.pf, 61.718229798145316, 'res.pf is ' + res.pf);

});