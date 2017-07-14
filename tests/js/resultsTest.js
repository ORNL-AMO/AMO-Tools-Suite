/**
 * Created by g9a on 3/31/17.
 */
const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

test('psatExistingAndOptimal', function (t) {
    t.plan(23);
    t.type(bindings.resultsExistingAndOptimal, 'function');

    var inp = {
        'pump_style': 6, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 200,
        'motor_rated_speed': 1780, 'efficiency_class': 2, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480
    };

    var psatResult = bindings.resultsExistingAndOptimal(inp);

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

test('psatExisting', function (t) {
    t.plan(11);
    t.type(bindings.resultsExisting, 'function');
    var inp = {
        'pump_style': 6, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 200,
        'motor_rated_speed': 1780, 'efficiency_class': 2, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480
    };

    var psatResult = bindings.resultsExisting(inp);

    t.equal(psatResult.pump_efficiency, 80.26203812559545, 'existing pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 200, 'existing motor rated power is ' + psatResult.motor_rated_power);
    t.equal(psatResult.motor_shaft_power, 101.18747791246317, 'existing motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(psatResult.pump_shaft_power, 101.18747791246317, 'existing pump shaft power is ' + psatResult.pump_shaft_power);
    t.equal(psatResult.motor_efficiency, 94.35732315337191, 'existing motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(psatResult.motor_power_factor, 76.45602656178534, 'existing motor power factor is ' + psatResult.motor_power_factor);
    t.equal(psatResult.motor_current, 125.85671685040634, 'existing motor current is ' + psatResult.motor_current);
    t.equal(psatResult.motor_power, 80, 'existing motor power is ' + psatResult.motor_power);
    t.equal(psatResult.annual_energy, 700.8, 'existing annual energy is ' + psatResult.annual_energy);
    t.equal(psatResult.annual_cost, 35040, 'existing annual cost is ' + psatResult.annual_cost);
    // t.equal(psatResult.annual_savings_potential, 2851.1370582823192, 'annual savings potential is ' + psatResult.annual_savings_potential);
    // t.equal(psatResult.optimization_rating, 0.9186319332681986, 'optimization rating is ' + psatResult.optimization_rating);
});

test('psatOptimal', function (t) {
    t.plan(11);
    t.type(bindings.resultsOptimal, 'function');
    var inp = {
        'pump_style': 6, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 200,
        'motor_rated_speed': 1780, 'efficiency_class': 2, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480
    };

    var psatResult = bindings.resultsOptimal(inp);

    t.equal(psatResult.pump_efficiency, 86.75480583084276 , 'optimal pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 100 , 'optimal motor rated power is ' + psatResult.motor_rated_power);
    t.equal(psatResult.motor_shaft_power, 93.61456270075166, 'optimal motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(psatResult.pump_shaft_power, 93.61456270075166, 'optimal pump power is ' + psatResult.pump_shaft_power);
    t.equal(psatResult.motor_efficiency, 95.02783605700556, 'optimal motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(psatResult.motor_power_factor, 85.97645176630047, 'optimal motor power factor is ' + psatResult.motor_power_factor);
    t.equal(psatResult.motor_current, 102.81349971661015, 'optimal motor current is ' + psatResult.motor_current);
    t.equal(psatResult.motor_power, 73.49055466145589, 'optimal motor power is ' + psatResult.motor_power);
    t.equal(psatResult.annual_energy, 643.7772588343536, 'optimal annual energy is ' + psatResult.annual_energy);
    t.equal(psatResult.annual_cost, 32188.86294171768, 'optimal annual cost is ' + psatResult.annual_cost);
    // t.equal(psatResult.annual_savings_potential, 2851.1370582823192, 'annual savings potential is ' + psatResult.annual_savings_potential);
    // t.equal(psatResult.optimization_rating, 0.9186319332681986, 'optimization rating is ' + psatResult.optimization_rating);
});
