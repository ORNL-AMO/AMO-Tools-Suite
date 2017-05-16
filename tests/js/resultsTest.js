/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

test('psat', function (t) {
    t.plan(23);
    t.type(bindings.results, 'function');
    var inp = {};
    // PUMP INFORMATION
    // Pump Style End suction ansi API
    inp.pump_style = 6;
    // Achievable pump efficiency
    inp.pump_specified = 90;
    inp.pump_rated_speed = 1780;

    // Pump Drive : Direct
    inp.drive = 0;
    // kinematic viscosity
    inp.kinematic_viscosity = 1.0;
    // specific gravity
    inp.specific_gravity = 1.000;
    // stages count
    inp.stages = 2.0;
    // Not fixed speed
    inp.fixed_speed = 1;

    // MOTOR INFORMATION
    // Line frequency 60
    inp.line_frequency = 0;
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
    inp.motor_rated_fla = 225.0;
    // Size margin
    inp.margin = 0;

    // FINANCIALS
    inp.operating_fraction = 1.00;
    inp.cost_kw_hour = 0.05;

    // FIELD DATA
    // Flow rate
    inp.flow_rate = 1840;
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

    t.equal(psatResult.pump_efficiency[0], 80.26203812559545, 'existing pump efficiency is ' + psatResult.pump_efficiency[0]);
    t.equal(psatResult.pump_efficiency[1], 86.75480583084276 , 'optimal pump efficiency is ' + psatResult.pump_efficiency[1]);

    t.equal(psatResult.motor_rated_power[0], 200, 'existing motor rated power is ' + psatResult.motor_rated_power[0]);
    t.equal(psatResult.motor_rated_power[1], 100 , 'optimal motor rated power is ' + psatResult.motor_rated_power[1]);

    t.equal(psatResult.motor_shaft_power[0], 101.18747791246317, 'existing motor shaft power is ' + psatResult.motor_shaft_power[0]);
    t.equal(psatResult.motor_shaft_power[1], 93.61456270075166, 'optimal motor shaft power is ' + psatResult.motor_shaft_power[1]);

    t.equal(psatResult.pump_shaft_power[0], 101.18747791246317, 'existing pump shaft power is ' + psatResult.pump_shaft_power[0]);
    t.equal(psatResult.pump_shaft_power[1], 93.61456270075166, 'optimal pump power is ' + psatResult.pump_shaft_power[1]);

    t.equal(psatResult.motor_efficiency[0], 94.35732315337191, 'existing motor efficiency is ' + psatResult.motor_efficiency[0]);
    t.equal(psatResult.motor_efficiency[1], 95.02783605700556, 'optimal motor efficiency is ' + psatResult.motor_efficiency[1]);

    t.equal(psatResult.motor_power_factor[0], 76.45602656178534, 'existing motor power factor is ' + psatResult.motor_power_factor[0]);
    t.equal(psatResult.motor_power_factor[1], 85.97645176630047, 'optimal motor power factor is ' + psatResult.motor_power_factor[1]);

    t.equal(psatResult.motor_current[0], 125.85671685040634, 'existing motor current is ' + psatResult.motor_current[0]);
    t.equal(psatResult.motor_current[1], 102.81349971661015, 'optimal motor current is ' + psatResult.motor_current[1]);

    t.equal(psatResult.motor_power[0], 80, 'existing motor power is ' + psatResult.motor_power[0]);
    t.equal(psatResult.motor_power[1], 73.49055466145589, 'optimal motor power is ' + psatResult.motor_power[1]);

    t.equal(psatResult.annual_energy[0], 700.8, 'existing annual energy is ' + psatResult.annual_energy[0]);
    t.equal(psatResult.annual_energy[1], 643.7772588343536, 'optimal annual energy is ' + psatResult.annual_energy[1]);

    t.equal(psatResult.annual_cost[0], 35040, 'existing annual cost is ' + psatResult.annual_cost[0]);
    t.equal(psatResult.annual_cost[1], 32188.86294171768, 'optimal annual cost is ' + psatResult.annual_cost[1]);

    t.equal(psatResult.annual_savings_potential[0], 2851.1370582823192, 'annual savings potential is ' + psatResult.annual_savings_potential[0]);
    t.equal(psatResult.optimization_rating[0], 0.9186319332681986, 'optimization rating is ' + psatResult.optimization_rating[0]);

});