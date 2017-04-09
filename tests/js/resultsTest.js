/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

test('psat', function (t) {
    t.plan(1);
    t.type(bindings.results, 'function');
    var inp = {};
    // PUMP INFORMATION
    // Pump Style End suction ansi API
    inp.pump_style = 6;
    // Achievable pump efficiency
    inp.pump_specified = 90;
    inp.pump_rated_speed = 1780;
    inp.motor_rated_speed = 1780;
    // Pump Drive : Direct
    inp.drive = 0;
    // kinematic viscosity
    inp.viscosity = 1.0;
    // specific gravity
    inp.specific_gravity = 1.000;
    // stages count
    inp.stages = 2.0;
    // Not fixed speed
    inp.fixed_speed = 1;

    // MOTOR INFORMATION
    // Line frequency 60
    inp.line = 0;
    // motor rated power
    inp.motor_rated_power = 200;
    // motor speed
    inp.motor_rated_speed = 1780;
    // Efficiency class SPECIFIED
    inp.efficiency_class = 2;
    // efficiency
    inp.efficiency = 95;
    // motor rated voltage
    inp.motor_rated_voltage = 460;
    // Full load amps
    inp.fla = 225.0;
    // Size margin
    inp.margin = 0;

    // FINANCIALS
    inp.fraction = 1.00;
    inp.cost = 0.05;

    // FIELD DATA
    // Flow rate
    inp.flow = 1840;
    // Head
    inp.head = 174.85;
    // enum class LoadEstimationMethod {
    //     POWER,
    //     CURRENT
    // };
    inp.load_estimation_method = 0;
    // motor power
    inp.motor_field_power = 80;
    // motor amps-current
    inp.motor_field_current = 125.857;
    // voltage
    inp.motor_field_voltage = 480;

    /**
     Pump Efficiency: 0.8026203812559545
     Motor Rated power: 200
     Motor Shaft power: 101.1874779124632
     Pump Shaft power: 101.1874779124632
     Motor Efficiency: 0.9435732315337191
     Motor power factor: 0.7645602656178534
     Motor current: 125.8567168504063
     Motor power: 80
     Annual Energy: 700.8
     Annual Cost: 35.04
     Estimated FLA: 227.2883400226323
     Optimal **********************************
     Pump Efficiency: 0.8675480583084275
     Motor Rated power: 100
     Motor Shaft power: 93.61456270075166
     Pump Shaft power: 93.61456270075166
     Motor Efficiency: 0.9502783605700555
     Motor power factor: 0.8597645176630047
     Motor current: 102.8134997166102
     Motor power: 73.49055466145589
     Annual Energy: 643.7772588343536
     Annual Cost: 32.18886294171768
     getAnnualSavingsPotential: 2.851137058282319
     getOptimizationRating: 0.9186319332681986
     */


    var psatResult = bindings.results(inp);

     //t.equal(psatResult.get("pump_efficiency")[0], 0.8026203812559545, 'existing pump efficiency is ' + psatResult[pump_efficiency][0]);
    // t.equal(psatResult["pump_efficiency"][1], 0.8675480583084275, 'optimal pump efficiency is ' + psatResult[pump_efficiency][0]);
    //

    for (var key in psatResult) {
        console.log(key,psatResult[key][0] + " existing.");
        console.log(key, psatResult[key][1] + " optimal.");
    }
    //t.equal(psatResult[0], 86.99584193768345, 'res max is ' + psatResult[0]);

});