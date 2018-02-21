const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('psatExistingAndOptimal', function (t) {
    t.plan(23);
    t.type(bindings.resultsExistingAndOptimal, 'function');

    var inp = {
        'pump_style': 6, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 200,
        'motor_rated_speed': 1780, 'efficiency_class': 3, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480
    };

    var psatResult = bindings.resultsExistingAndOptimal(inp);

    t.equal(rnd(psatResult.pump_efficiency[0]), rnd(80.26203812559545), 'existing pump efficiency is ' + psatResult.pump_efficiency[0]);
    t.equal(rnd(psatResult.pump_efficiency[1]), rnd(86.75480583084276) , 'optimal pump efficiency is ' + psatResult.pump_efficiency[1]);

    t.equal(psatResult.motor_rated_power[0], 200, 'existing motor rated power is ' + psatResult.motor_rated_power[0]);
    t.equal(psatResult.motor_rated_power[1], 100 , 'optimal motor rated power is ' + psatResult.motor_rated_power[1]);

    t.equal(rnd(psatResult.motor_shaft_power[0]), rnd(101.18747791246317), 'existing motor shaft power is ' + psatResult.motor_shaft_power[0]);
    t.equal(rnd(psatResult.motor_shaft_power[1]), rnd(93.61456270075166), 'optimal motor shaft power is ' + psatResult.motor_shaft_power[1]);

    t.equal(rnd(psatResult.pump_shaft_power[0]), rnd(101.18747791246317), 'existing pump shaft power is ' + psatResult.pump_shaft_power[0]);
    t.equal(rnd(psatResult.pump_shaft_power[1]), rnd(93.61456270075166), 'optimal pump power is ' + psatResult.pump_shaft_power[1]);

    t.equal(rnd(psatResult.motor_efficiency[0]), rnd(94.35732315337191), 'existing motor efficiency is ' + psatResult.motor_efficiency[0]);
    t.equal(rnd(psatResult.motor_efficiency[1]), rnd(95.518544), 'optimal motor efficiency is ' + psatResult.motor_efficiency[1]);

    t.equal(rnd(psatResult.motor_power_factor[0]), rnd(76.45602656178534), 'existing motor power factor is ' + psatResult.motor_power_factor[0]);
    t.equal(rnd(psatResult.motor_power_factor[1]), rnd(85.121115), 'optimal motor power factor is ' + psatResult.motor_power_factor[1]);

    t.equal(rnd(psatResult.motor_current[0]), rnd(125.85671685040634), 'existing motor current is ' + psatResult.motor_current[0]);
    t.equal(rnd(psatResult.motor_current[1]), rnd(103.313142), 'optimal motor current is ' + psatResult.motor_current[1]);

    t.equal(psatResult.motor_power[0], 80, 'existing motor power is ' + psatResult.motor_power[0]);
    t.equal(rnd(psatResult.motor_power[1]), rnd(73.113023), 'optimal motor power is ' + psatResult.motor_power[1]);

    t.equal(psatResult.annual_energy[0], 700.8, 'existing annual energy is ' + psatResult.annual_energy[0]);
    t.equal(rnd(psatResult.annual_energy[1]), rnd(640.470082), 'optimal annual energy is ' + psatResult.annual_energy[1]);

    t.equal(psatResult.annual_cost[0], 35040, 'existing annual cost is ' + psatResult.annual_cost[0]);
    t.equal(rnd(psatResult.annual_cost[1]), rnd(32023.504102), 'optimal annual cost is ' + psatResult.annual_cost[1]);

    t.equal(psatResult.annual_savings_potential[0], 0.0, 'annual savings potential is ' + psatResult.annual_savings_potential[0]);
    t.equal(psatResult.optimization_rating[0], 0.0, 'optimization rating is ' + psatResult.optimization_rating[0]);
});

test('psatExisting', function (t) {
    t.plan(11);
    t.type(bindings.resultsExisting, 'function');
    var inp = {
        'pump_style': 6, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 200,
        'motor_rated_speed': 1780, 'efficiency_class': 3, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480
    };

    var psatResult = bindings.resultsExisting(inp);

    t.equal(rnd(psatResult.pump_efficiency), rnd(80.26203812559545), 'existing pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 200, 'existing motor rated power is ' + psatResult.motor_rated_power);
    t.equal(rnd(psatResult.motor_shaft_power), rnd(101.18747791246317), 'existing motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(rnd(psatResult.pump_shaft_power), rnd(101.18747791246317), 'existing pump shaft power is ' + psatResult.pump_shaft_power);
    t.equal(rnd(psatResult.motor_efficiency), rnd(94.35732315337191), 'existing motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(rnd(psatResult.motor_power_factor), rnd(76.45602656178534), 'existing motor power factor is ' + psatResult.motor_power_factor);
    t.equal(rnd(psatResult.motor_current), rnd(125.85671685040634), 'existing motor current is ' + psatResult.motor_current);
    t.equal(psatResult.motor_power, 80, 'existing motor power is ' + psatResult.motor_power);
    t.equal(psatResult.annual_energy, 700.8, 'existing annual energy is ' + psatResult.annual_energy);
    t.equal(psatResult.annual_cost, 35040, 'existing annual cost is ' + psatResult.annual_cost);
});

test('psatOptimal', function (t) {
    t.plan(11);
    t.type(bindings.resultsOptimal, 'function');
    var inp = {
        'pump_style': 6, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 200,
        'motor_rated_speed': 1780, 'efficiency_class': 3, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480
    };

    var psatResult = bindings.resultsOptimal(inp);

    t.equal(rnd(psatResult.pump_efficiency), rnd(86.75480583084276) , 'optimal pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 100 , 'optimal motor rated power is ' + psatResult.motor_rated_power);
    t.equal(rnd(psatResult.motor_shaft_power), rnd(93.61456270075166), 'optimal motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(rnd(psatResult.pump_shaft_power), rnd(93.61456270075166), 'optimal pump power is ' + psatResult.pump_shaft_power);
    t.equal(rnd(psatResult.motor_efficiency), rnd(95.518544), 'optimal motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(rnd(psatResult.motor_power_factor), rnd(85.121115), 'optimal motor power factor is ' + psatResult.motor_power_factor);
    t.equal(rnd(psatResult.motor_current), rnd(103.313142), 'optimal motor current is ' + psatResult.motor_current);
    t.equal(rnd(psatResult.motor_power), rnd(73.113023), 'optimal motor power is ' + psatResult.motor_power);
    t.equal(rnd(psatResult.annual_energy), rnd(640.470082), 'optimal annual energy is ' + psatResult.annual_energy);
    t.equal(rnd(psatResult.annual_cost), rnd(32023.504102), 'optimal annual cost is ' + psatResult.annual_cost);
});

test('psatModified', function (t) {
    t.plan(11);
    t.type(bindings.resultsModified, 'function');
    var inp = {
        'pump_style': 6, 'pump_specified': null, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 100,
        'motor_rated_speed': 1780, 'efficiency_class': 3, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480, 'baseline_pump_efficiency':80
    };

    var psatResult = bindings.resultsModified(inp);

   t.equal(psatResult.pump_efficiency, 80 , 'modified pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 100 , 'modified motor rated power is ' + psatResult.motor_rated_power);
    t.equal(rnd(psatResult.motor_shaft_power), rnd(101.51891512553706), 'modified motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(rnd(psatResult.pump_shaft_power), rnd(101.51891512553706), 'modified pump power is ' + psatResult.pump_shaft_power);
    t.equal(rnd(psatResult.motor_efficiency), rnd(95.371824), 'modified motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(rnd(psatResult.motor_power_factor), rnd(86.144991), 'modified motor power factor is ' + psatResult.motor_power_factor);
    t.equal(rnd(psatResult.motor_current), rnd(110.875106), 'modified motor current is ' + psatResult.motor_current);
    t.equal(rnd(psatResult.motor_power), rnd(79.408308), 'modified motor power is ' + psatResult.motor_power);
    t.equal(rnd(psatResult.annual_energy), rnd(695.61678), 'modified annual energy is ' + psatResult.annual_energy);
    t.equal(rnd(psatResult.annual_cost), rnd(34780.839004), 'modified annual cost is ' + psatResult.annual_cost);
});

test('psatModified2', function (t) {
    t.plan(11);
    t.type(bindings.resultsModified, 'function');
    var inp = {
        'pump_style': 11, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 100,
        'motor_rated_speed': 1780, 'efficiency_class': 3, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_fraction': 1.00, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480, 'baseline_pump_efficiency': 80
    };

    var psatResult = bindings.resultsModified(inp);

   t.equal(psatResult.pump_efficiency, 90, 'modified pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 100 , 'modified motor rated power is ' + psatResult.motor_rated_power);
    t.equal(rnd(psatResult.motor_shaft_power), rnd(90.23903566714407), 'modified motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(rnd(psatResult.pump_shaft_power), rnd(90.23903566714407), 'modified pump power is ' + psatResult.pump_shaft_power);
    t.equal(rnd(psatResult.motor_efficiency), rnd(95.573615), 'modified motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(rnd(psatResult.motor_power_factor), rnd(84.622639), 'modified motor power factor is ' + psatResult.motor_power_factor);
    t.equal(rnd(psatResult.motor_current), rnd(100.116804), 'modified motor current is ' + psatResult.motor_current);
    t.equal(rnd(psatResult.motor_power), rnd(70.436117), 'modified motor power is ' + psatResult.motor_power);
    t.equal(rnd(psatResult.annual_energy), rnd(617.020386), 'modified annual energy is ' + psatResult.annual_energy);
    t.equal(rnd(psatResult.annual_cost), rnd(30851.019318), 'modified annual cost is ' + psatResult.annual_cost);
});
