const test = require('tap').test
, testRoot = require('path').resolve(__dirname, '../../')
, bindings = require('bindings')({ module_root: testRoot, bindings: 'psat'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('psatExisting2', function (t) {
    t.plan(5);
    t.type(bindings.resultsExisting, 'function');
    var inp = {
        'pump_style': 2, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 4, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 1.0, 'fixed_speed': 0, 'line_frequency': 0, 'motor_rated_power': 300,
        'motor_rated_speed': 1780, 'efficiency_class': 0, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 337.3, 'margin': 0, 'operating_hours': 8760, 'cost_kw_hour': 0.06, 'flow_rate': 1840,
        'head': 277.0, 'load_estimation_method': 0, 'motor_field_power': 150.0, 'motor_field_current': 80.5,
        'motor_field_voltage': 460, 'baseline_pump_efficiency': 0.69, 'specifiedDriveEfficiency': 95
    };
    var psatResult = bindings.resultsExisting(inp);
    t.equal(rnd(psatResult.pump_efficiency), rnd(71.5541741283), 'existing pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(rnd(psatResult.motor_shaft_power), rnd(189.2746748003), 'existing motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(rnd(psatResult.pump_shaft_power), rnd(179.8109410603), 'existing pump shaft power is ' + psatResult.pump_shaft_power);
    t.equal(rnd(psatResult.motor_efficiency), rnd(94.132604934), 'existing motor efficiency is ' + psatResult.motor_efficiency);
});


test('psatModified', function (t) {
    t.plan(11);
    t.type(bindings.resultsModified, 'function');
    var inp = {
        'pump_style': 6, 'pump_specified': 80, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 100,
        'motor_rated_speed': 1780, 'efficiency_class': 3, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_hours': 8760, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480, 'pump_efficiency': 80
    };

    var psatResult = bindings.resultsModified(inp);

    t.equal(psatResult.pump_efficiency, 80 , 'modified pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 100 , 'modified motor rated power is ' + psatResult.motor_rated_power);
    t.equal(rnd(psatResult.motor_shaft_power), rnd(101.51891512553706), 'modified motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(rnd(psatResult.pump_shaft_power), rnd(101.51891512553706), 'modified pump power is ' + psatResult.pump_shaft_power);
    t.equal(rnd(psatResult.motor_efficiency), rnd(94.973283), 'modified motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(rnd(psatResult.motor_power_factor), rnd(86.926875), 'modified motor power factor is ' + psatResult.motor_power_factor);
    t.equal(rnd(psatResult.motor_current), rnd(110.338892), 'modified motor current is ' + psatResult.motor_current);
    t.equal(rnd(psatResult.motor_power), rnd(79.741528), 'modified motor power is ' + psatResult.motor_power);
    t.equal(rnd(psatResult.annual_energy), rnd(698.535785), 'modified annual energy is ' + psatResult.annual_energy);
    t.equal(rnd(psatResult.annual_cost), rnd(34926.789251), 'modified annual cost is ' + psatResult.annual_cost);
});

test('psatModified2', function (t) {
    t.plan(11);
    t.type(bindings.resultsModified, 'function');
    var inp = {
        'pump_style': 11, 'pump_specified': 90, 'pump_rated_speed':1780, 'drive': 0, 'kinematic_viscosity': 1.0,
        'specific_gravity': 1.0, 'stages': 2.0, 'fixed_speed': 1, 'line_frequency': 0, 'motor_rated_power': 100,
        'motor_rated_speed': 1780, 'efficiency_class': 3, 'efficiency': 95, 'motor_rated_voltage': 460,
        'motor_rated_fla': 225.0, 'margin': 0, 'operating_hours': 8760, 'cost_kw_hour': 0.05, 'flow_rate': 1840,
        'head': 174.85, 'load_estimation_method': 0, 'motor_field_power': 80, 'motor_field_current': 125.857,
        'motor_field_voltage': 480, 'pump_efficiency': 80
    };

    var psatResult = bindings.resultsModified(inp);

    t.equal(psatResult.pump_efficiency, 90, 'modified pump efficiency is ' + psatResult.pump_efficiency);
    t.equal(psatResult.motor_rated_power, 100 , 'modified motor rated power is ' + psatResult.motor_rated_power);
    t.equal(rnd(psatResult.motor_shaft_power), rnd(90.23903566714407), 'modified motor shaft power is ' + psatResult.motor_shaft_power);
    t.equal(rnd(psatResult.pump_shaft_power), rnd(90.23903566714407), 'modified pump power is ' + psatResult.pump_shaft_power);
    t.equal(rnd(psatResult.motor_efficiency), rnd(95.118454), 'modified motor efficiency is ' + psatResult.motor_efficiency);
    t.equal(rnd(psatResult.motor_power_factor), rnd(85.44077), 'modified motor power factor is ' + psatResult.motor_power_factor);
    t.equal(rnd(psatResult.motor_current), rnd(99.63262), 'modified motor current is ' + psatResult.motor_current);
    t.equal(rnd(psatResult.motor_power), rnd(70.773157), 'modified motor power is ' + psatResult.motor_power);
    t.equal(rnd(psatResult.annual_energy), rnd(619.972854), 'modified annual energy is ' + psatResult.annual_energy);
    t.equal(rnd(psatResult.annual_cost), rnd(30998.642708), 'modified annual cost is ' + psatResult.annual_cost);
});
