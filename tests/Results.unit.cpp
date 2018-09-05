#include "catch.hpp"
#include <results/Results.h>
#include <unordered_map>
#include <calculator/pump/PumpShaftPower.h>
#include <calculator/pump/MoverEfficiency.h>
#include <array>
#include <calculator/motor/EstimateFLA.h>

TEST_CASE( "Fan Output existing", "[Fan results existing]" ) {
	Fan::Input fanInput = {1180, 0.07024, Motor::Drive::DIRECT_DRIVE, 1.00};
	Motor motor = {Motor::LineFrequency::FREQ60, 600, 1180, Motor::EfficiencyClass::ENERGY_EFFICIENT, 96, 460, 683.2505707137};
	Fan::FieldDataBaseline fanFieldData = {460, 460, 660, 129691, -16.36, 1.1, 0.988, Motor::LoadEstimationMethod::POWER};
	FanResult result = {fanInput, motor, 1.0, 0.06};
	auto const output = result.calculateExisting(fanFieldData);

	CHECK(Approx(output.fanEfficiency) == 0.595398315);
	CHECK(Approx(output.motorRatedPower) == 600.0);
	CHECK(Approx(output.motorShaftPower) == 590.622186263);
	CHECK(Approx(output.fanShaftPower) == 590.622186263);
	CHECK(Approx(output.motorEfficiency) == 0.9578351108);
	CHECK(Approx(output.motorPowerFactor) == 0.8577466651);
	CHECK(Approx(output.motorCurrent) == 673.1011529439);
	CHECK(Approx(output.motorPower) == 460.0);
	CHECK(Approx(output.annualEnergy) == 4029.6);
	CHECK(Approx(output.annualCost) == 241.776);
	CHECK(Approx(output.estimatedFLA) == 683.2505707137);
	CHECK(Approx(output.fanEnergyIndex) == 0.9718906186);
}

TEST_CASE( "Fan Output modified", "[Fan results modified]" ) {
	Fan::Input fanInput = {1180, 0.07024, Motor::Drive::DIRECT_DRIVE, 1.00};
	Motor motor = {Motor::LineFrequency::FREQ60, 600, 1180, Motor::EfficiencyClass::ENERGY_EFFICIENT, 96, 460, 683.2505707137};
	Fan::FieldDataModifiedAndOptimal fanFieldData = {460, 660, 129691, -16.36, 1.1, 0.988};
	FanResult result = {fanInput, motor, 1.0, 0.06};
	auto const output = result.calculateModified(fanFieldData, 0.595398315, false);

	CHECK(Approx(output.fanEfficiency) == 0.595398315);
	CHECK(Approx(output.motorRatedPower) == 600.0);
	CHECK(Approx(output.motorShaftPower) == 590.622186263);
	CHECK(Approx(output.fanShaftPower) == 590.622186263);
	CHECK(Approx(output.motorEfficiency) == 0.9578351072);
	CHECK(Approx(output.motorPowerFactor) == 0.8577480086);
	CHECK(Approx(output.motorCurrent) == 673.1003093353);
	CHECK(Approx(output.motorPower) == 460.0001440224);
	CHECK(Approx(output.annualEnergy) == 4029.6012616363);
	CHECK(Approx(output.annualCost) == 241.7760756982);
	CHECK(Approx(output.fanEnergyIndex) == 0.9718903143);
}

TEST_CASE( "Fan Output Optimal", "[Fan results optimal]" ) {
	Fan::Input fanInput = {1180, 0.07024, Motor::Drive::DIRECT_DRIVE, 1.00};
	Motor motor = {Motor::LineFrequency::FREQ60, 500, 1180, Motor::EfficiencyClass::ENERGY_EFFICIENT, 96, 460, 683.2505707137};
	Fan::FieldDataModifiedAndOptimal fanFieldData = {460, 660, 129691, -16.36, 1.1, 0.988};
	FanResult result = {fanInput, motor, 1.0, 0.06};
	auto const output = result.calculateOptimal(fanFieldData, OptimalFanEfficiency::FanType::AirfoilSISW);

	CHECK(Approx(output.fanEfficiency) == 0.7565784493);
	CHECK(Approx(output.motorRatedPower) == 500.0);
	CHECK(Approx(output.motorShaftPower) == 464.7970806678);
	CHECK(Approx(output.fanShaftPower) == 464.7970806678);
	CHECK(Approx(output.motorEfficiency) == 0.9599974605);
	CHECK(Approx(output.motorPowerFactor) == 0.8542724641);
	CHECK(Approx(output.motorCurrent) == 530.6611260876);
	CHECK(Approx(output.motorPower) == 361.1870254817);
	CHECK(Approx(output.annualEnergy) == 3163.9983432194);
	CHECK(Approx(output.annualCost) == 189.839900593);
	CHECK(Approx(output.fanEnergyIndex) == 1.2377789151);
}

TEST_CASE( "Fan Output Optimal Specified", "[Fan results optimal specified]" ) {
	Fan::Input fanInput = {1180, 0.07024, Motor::Drive::DIRECT_DRIVE, 1.00};
	Motor motor = {Motor::LineFrequency::FREQ60, 500, 1180, Motor::EfficiencyClass::ENERGY_EFFICIENT, 96, 460, 683.2505707137};
	Fan::FieldDataModifiedAndOptimal fanFieldData = {460, 660, 129691, -16.36, 1.1, 0.988};
	FanResult result = {fanInput, motor, 1.0, 0.06};
	auto const output = result.calculateOptimal(fanFieldData, 0.7565784493);

	CHECK(Approx(output.fanEfficiency) == 0.7565784493);
	CHECK(Approx(output.motorRatedPower) == 500.0);
	CHECK(Approx(output.motorShaftPower) == 464.7970806678);
	CHECK(Approx(output.fanShaftPower) == 464.7970806678);
	CHECK(Approx(output.motorEfficiency) == 0.9599974605);
	CHECK(Approx(output.motorPowerFactor) == 0.8542724641);
	CHECK(Approx(output.motorCurrent) == 530.6611260876);
	CHECK(Approx(output.motorPower) == 361.1870254817);
	CHECK(Approx(output.annualEnergy) == 3163.9983432194);
	CHECK(Approx(output.annualCost) == 189.839900593);
	CHECK(Approx(output.fanEnergyIndex) == 1.2377789151);
}


TEST_CASE( "PSATResultsPremium existing and optimal", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.0, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.05, flow_rate = 1840;
	double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
	double baseline_pump_efficiency = 0.80, specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::DIRECT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::PREMIUM);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);

	auto const & ex = psat.calculateExisting();
//	psat.calculateModified();
	auto const & opt = psat.calculateOptimal();
//	auto const & mod = psat.calculateModified();

	CHECK(ex.pumpEfficiency * 100 == Approx(78.555319445));
	CHECK(ex.motorRatedPower == Approx(200));
	CHECK(ex.motorShaftPower == Approx(103.385910304));
	CHECK(ex.pumpShaftPower == Approx(103.385910304));
	CHECK(ex.motorEfficiency * 100 == Approx(96.4073613585));
	CHECK(ex.motorPowerFactor * 100 == Approx(75.3340317395));
	CHECK(ex.motorCurrent == Approx(127.7311762599));
	CHECK(ex.motorPower == Approx(80));
	CHECK(ex.annualEnergy == Approx(700.8));
	CHECK(ex.annualCost * 1000.0 == Approx(35040));

	CHECK(opt.pumpEfficiency * 100 == Approx(86.75480583084276));
	CHECK(opt.motorRatedPower == Approx(100));
	CHECK(opt.motorShaftPower == Approx(93.6145627007516));
	CHECK(opt.pumpShaftPower == Approx(93.614562700751));
	CHECK(opt.motorEfficiency * 100 == Approx(95.5185443048));
	CHECK(opt.motorPowerFactor * 100 == Approx(86.0468881576));
	CHECK(opt.motorCurrent == Approx(102.2016030326));
	CHECK(opt.motorPower == Approx(73.1130230639));
	CHECK(opt.annualEnergy == Approx(640.4700820397));
	CHECK(opt.annualCost * 1000.0 == Approx(32023.5041019837));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));

}

TEST_CASE( "PSATResults existing, modified, optimal", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.0, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.05, flow_rate = 1840;
	double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
	double baseline_pump_efficiency = 0.80, specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::DIRECT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);

	auto const & ex = psat.calculateExisting();
	auto const & mod = psat.calculateModified();
	auto const & opt = psat.calculateOptimal();

	CHECK(ex.pumpEfficiency * 100 == Approx(80.2620381));
	CHECK(ex.motorRatedPower == Approx(200));
	CHECK(ex.motorShaftPower == Approx(101.18747791246317));
	CHECK(ex.pumpShaftPower == Approx(101.18747791246317));
	CHECK(ex.motorEfficiency * 100 == Approx(94.35732315337191));
	CHECK(ex.motorPowerFactor * 100 == Approx(76.45602656178534));
	CHECK(ex.motorCurrent == Approx(125.85671685040634));
	CHECK(ex.motorPower == Approx(80));
	CHECK(ex.annualEnergy == Approx(700.8));
	CHECK(ex.annualCost * 1000.0 == Approx(35040));

	CHECK(mod.pumpEfficiency * 100 == Approx(80));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(101.5189151255));
	CHECK(mod.pumpShaftPower == Approx(101.5189151255));
	CHECK(mod.motorEfficiency * 100 == Approx(94.3652462131));
	CHECK(mod.motorPowerFactor * 100 == Approx(76.2584456388));
	CHECK(mod.motorCurrent == Approx(126.5852583329));
	CHECK(mod.motorPower == Approx(80.2551564807));
	CHECK(mod.annualEnergy == Approx(703.0351707712));
	CHECK(mod.annualCost * 1000.0 == Approx(35151.7585385623));


	// these values were modified to pass for the changes we made for optimal (premium)
//	CHECK(opt.motorEfficiency * 100 == Approx(95.4868858345));
//	CHECK(opt.motorPowerFactor * 100 == Approx(83.9640402732));
//	CHECK(opt.motorCurrent == Approx(104.7715676829));
//	CHECK(opt.motorPower == Approx(73.1372514568));
//	CHECK(opt.annualEnergy == Approx(640.6823227615));
//	CHECK(opt.annualCost * 1000.0 == Approx(32034.1161380738));
	CHECK(opt.pumpEfficiency * 100 == Approx(86.75480583084276));
	CHECK(opt.motorRatedPower == Approx(100));
	CHECK(opt.motorShaftPower == Approx(93.6145627007516));
	CHECK(opt.pumpShaftPower == Approx(93.614562700751));
	CHECK(opt.motorEfficiency * 100 == Approx(95.0865215334));
	CHECK(opt.motorPowerFactor * 100 == Approx(85.9233888406));
	CHECK(opt.motorCurrent == Approx(102.8134997166));
	CHECK(opt.motorPower == Approx(73.4451977787));
	CHECK(opt.annualEnergy == Approx(643.3799325415));
	CHECK(opt.annualCost * 1000.0 == Approx(32168.9966270763));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));

}

TEST_CASE( "PSATResults - existing changed voltage", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1185, kinematic_viscosity = 1.0, specific_gravity = 0.99;
	double stages = 1.0, motor_rated_power = 350, motor_rated_speed = 1185, efficiency = 95, motor_rated_voltage = 2300;
	double motor_rated_fla = 83, margin = 0.15, operating_fraction = 1.0, cost_kw_hour = 0.039, flow_rate = 2800;
	double head = 104.0, motor_field_power = 150.0, motor_field_current = 80.5, motor_field_voltage = 2300;
	double baseline_pump_efficiency = 0.382, specified_efficiency = 1.0;
	Pump::Style style1(Pump::Style::END_SUCTION_STOCK);
	Motor::Drive drive1(Motor::Drive::DIRECT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::STANDARD);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::CURRENT);
	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);
	auto const & ex = psat.calculateExisting();
	CHECK(ex.pumpEfficiency * 100 == Approx(21.4684857877));
	CHECK(ex.motorRatedPower == Approx(350));
	CHECK(ex.motorShaftPower == Approx(338.9835681041));
	CHECK(ex.pumpShaftPower == Approx(338.9835681041));
	CHECK(ex.motorEfficiency * 100 == Approx(94.518008321));
	CHECK(ex.motorPowerFactor * 100 == Approx(83.4292940632));
	CHECK(ex.motorCurrent == Approx(80.5));
	CHECK(ex.motorPower == Approx(267.548741554));
	CHECK(ex.annualEnergy == Approx(2343.7));
	CHECK(ex.annualCost * 1000.0 == Approx(91405.352064809));
}

TEST_CASE( "PSATResults - specified drive", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1185, kinematic_viscosity = 1.0, specific_gravity = 0.99;
	double stages = 1.0, motor_rated_power = 350, motor_rated_speed = 1185, efficiency = 95, motor_rated_voltage = 2300;
	double motor_rated_fla = 83, margin = 0.15, operating_fraction = 1.0, cost_kw_hour = 0.039, flow_rate = 2800;
	double head = 104.0, motor_field_power = 150.0, motor_field_current = 80.5, motor_field_voltage = 2300;
	double baseline_pump_efficiency = 0.382, specified_efficiency = 0.95;
	Pump::Style style1(Pump::Style::END_SUCTION_STOCK);
	Motor::Drive drive1(Motor::Drive::SPECIFIED); //SPEC
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::STANDARD);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::CURRENT);
	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);
	auto const & ex = psat.calculateExisting();
	CHECK(ex.pumpEfficiency * 100 == Approx(22.5984060923));
	CHECK(ex.motorRatedPower == Approx(350));
	CHECK(ex.motorShaftPower == Approx(338.9835681041));
	CHECK(ex.pumpShaftPower == Approx(322.0343896989));
	CHECK(ex.motorEfficiency * 100 == Approx(94.518008321));
	CHECK(ex.motorPowerFactor * 100 == Approx(83.4292940632));
	CHECK(ex.motorCurrent == Approx(80.5));
	CHECK(ex.motorPower == Approx(267.548741554));
	CHECK(ex.annualEnergy == Approx(2343.7));
	CHECK(ex.annualCost * 1000.0 == Approx(91405.352064809));
}



TEST_CASE( "PSATResults - existing and modified", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 227.29, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 277.0, motor_field_power = 150.0, motor_field_current = 125.857, motor_field_voltage = 480;
	double baseline_pump_efficiency = 0.382, specified_efficiency = 1.0;
	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::V_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);
	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);
	auto const & ex = psat.calculateExisting();
	auto const & mod = psat.calculateModified();
	CHECK(ex.pumpEfficiency * 100 == Approx(38.1094253534));
	CHECK(ex.motorRatedPower == Approx(200));
	CHECK(ex.motorShaftPower == Approx(191.1541214642));
	CHECK(ex.pumpShaftPower == Approx(183.4851259332));
	CHECK(ex.motorEfficiency * 100 == Approx(95.0673164082));
	CHECK(ex.motorPowerFactor * 100 == Approx(86.3561411197));
	CHECK(ex.motorCurrent == Approx(208.9277690995));
	CHECK(ex.motorPower == Approx(150.0));
	CHECK(ex.annualEnergy == Approx(1314.0));
	CHECK(ex.annualCost * 1000.0 == Approx(78840));
	CHECK(mod.pumpEfficiency * 100 == Approx(38.2));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(190.7010275392));
	CHECK(mod.pumpShaftPower == Approx(183.0500709481));
	CHECK(mod.motorEfficiency * 100 == Approx(95.0700964487));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.8975146434));
	CHECK(mod.motorCurrent == Approx(207.128014213));
	CHECK(mod.motorPower == Approx(149.6401247588));
	CHECK(mod.annualEnergy == Approx(1310.8474928874));
	CHECK(mod.annualCost * 1000.0 == Approx(78650.8495732458));
}

TEST_CASE( "PSATResults2 v-belt type", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double baseline_pump_efficiency = 0.623, specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::V_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);

	auto const & ex = psat.calculateExisting();
	auto const & mod = psat.calculateModified();
	auto const & opt = psat.calculateOptimal();

	CHECK(mod.pumpEfficiency * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(200.507050278));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorEfficiency * 100 == Approx(95.6211069257));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.7354953183));
	CHECK(mod.motorCurrent == Approx(226.3599309627));
	CHECK(mod.motorPower == Approx(156.4281376282));
	CHECK(mod.annualEnergy == Approx(1370.3104856228));
	CHECK(mod.annualCost * 1000.0 == Approx(82218.6291373691));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));
}

TEST_CASE( "PSATResults notched v belt", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double baseline_pump_efficiency = 0.623, specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::N_V_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);

	auto const & ex = psat.calculateExisting();
	auto const & mod = psat.calculateModified();
	auto const & opt = psat.calculateOptimal();

	CHECK(mod.pumpEfficiency * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(198.2102452363));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorEfficiency * 100 == Approx(95.6417064886));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.6915209945));
	CHECK(mod.motorCurrent == Approx(223.8322217984));
	CHECK(mod.motorPower == Approx(154.6029182589));
	CHECK(mod.annualEnergy == Approx(1354.3215639476));
	CHECK(mod.annualCost * 1000.0 == Approx(81259.2938368578));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));
}

TEST_CASE( "PSATResults sync belt", "[PSAT results]" ) {
	double achievableEfficiency = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double baseline_pump_efficiency = 0.623, specified_efficiency = 1.0;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Motor::Drive drive1(Motor::Drive::S_BELT_DRIVE);
	Pump::SpecificSpeed fixed_speed(Pump::SpecificSpeed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	Motor::LoadEstimationMethod loadEstimationMethod1(Motor::LoadEstimationMethod::POWER);

	Pump::Input pump(style1, achievableEfficiency, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed, specified_efficiency);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Pump::FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fd, baseline_pump_efficiency, operating_fraction, cost_kw_hour);

	auto const & ex = psat.calculateExisting();
	auto const & mod = psat.calculateModified();
	auto const & opt = psat.calculateOptimal();

	CHECK(mod.motorShaftPower == Approx(194.767));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorPower == Approx(151.8722277599));
}

TEST_CASE( "PSAT pump shaft power", "[PSAT][pump shaft power][drive]" ) {
	CHECK(PumpShaftPower(50, Motor::Drive::N_V_BELT_DRIVE, 0).calculate() == Approx(48.4814329723));
	CHECK(PumpShaftPower(100, Motor::Drive::N_V_BELT_DRIVE, 0).calculate() == Approx(97.0776282082));
	CHECK(PumpShaftPower(150, Motor::Drive::N_V_BELT_DRIVE, 0).calculate() == Approx(145.6804036099));
	CHECK(PumpShaftPower(200, Motor::Drive::N_V_BELT_DRIVE, 0).calculate() == Approx(194.2722411119));
	CHECK(PumpShaftPower(250, Motor::Drive::N_V_BELT_DRIVE, 0).calculate() == Approx(242.8550331213));

	CHECK(PumpShaftPower(50, Motor::Drive::V_BELT_DRIVE, 0).calculate() == Approx(47.8740061612));
	CHECK(PumpShaftPower(100, Motor::Drive::V_BELT_DRIVE, 0).calculate() == Approx(95.9086794914));
	CHECK(PumpShaftPower(150, Motor::Drive::V_BELT_DRIVE, 0).calculate() == Approx(143.9525650539));
	CHECK(PumpShaftPower(200, Motor::Drive::V_BELT_DRIVE, 0).calculate() == Approx(191.981137556));
	CHECK(PumpShaftPower(250, Motor::Drive::V_BELT_DRIVE, 0).calculate() == Approx(239.9970463698));

	CHECK(PumpShaftPower(50, Motor::Drive::S_BELT_DRIVE, 0).calculate() == Approx(49.3925731889));
	CHECK(PumpShaftPower(100, Motor::Drive::S_BELT_DRIVE, 0).calculate() == Approx(98.8310512833));
	CHECK(PumpShaftPower(150, Motor::Drive::S_BELT_DRIVE, 0).calculate() == Approx(148.272161444));
	CHECK(PumpShaftPower(200, Motor::Drive::S_BELT_DRIVE, 0).calculate() == Approx(197.7088964447));
	CHECK(PumpShaftPower(250, Motor::Drive::S_BELT_DRIVE, 0).calculate() == Approx(247.1420132485));

	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 1.00).calculate() == Approx(50));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.98).calculate() == Approx(49));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.96).calculate() == Approx(48));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.94).calculate() == Approx(47));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.92).calculate() == Approx(46));
	CHECK(PumpShaftPower(50, Motor::Drive::SPECIFIED, 0.90).calculate() == Approx(45));

	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 1.00).calculate() == Approx(250));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.98).calculate() == Approx(245));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.96).calculate() == Approx(240));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.94).calculate() == Approx(235));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.92).calculate() == Approx(230));
	CHECK(PumpShaftPower(250, Motor::Drive::SPECIFIED, 0.90).calculate() == Approx(225));
}

TEST_CASE( "PSAT pump efficiency", "[PSAT][pump efficiency]" ) {
	CHECK(MoverEfficiency(0.5, 1000, 125, 125).calculate() == Approx(0.126218641));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(3.5, 1000, 125, 125).calculate() == Approx(0.8835304869));
	CHECK(MoverEfficiency(9.5, 1000, 125, 125).calculate() == Approx(2.3981541786));
	CHECK(MoverEfficiency(20.5, 1000, 125, 125).calculate() == Approx(5.1749642801));
	CHECK(MoverEfficiency(50.5, 1000, 125, 125).calculate() == Approx(12.7480827388));

	CHECK(MoverEfficiency(1.5, 500, 125, 125).calculate() == Approx(0.1893279615));
	CHECK(MoverEfficiency(1.5, 700, 125, 125).calculate() == Approx(0.2650591461));
	CHECK(MoverEfficiency(1.5, 1100, 125, 125).calculate() == Approx(0.4165215152));
	CHECK(MoverEfficiency(1.5, 1800, 125, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 2800, 125, 125).calculate() == Approx(1.0602365842));

	CHECK(MoverEfficiency(1.5, 1000, 25, 125).calculate() == Approx(0.0757311846));
	CHECK(MoverEfficiency(1.5, 1000, 75, 125).calculate() == Approx(0.2271935538));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(1.5, 1000, 195, 125).calculate() == Approx(0.5907032398));
	CHECK(MoverEfficiency(1.5, 1000, 225, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 1000, 325, 125).calculate() == Approx(0.9845053996));

	CHECK(MoverEfficiency(1.5, 1000, 125, 25).calculate() == Approx(1.8932796147));
	CHECK(MoverEfficiency(1.5, 1000, 125, 75).calculate() == Approx(0.6310932049));
	CHECK(MoverEfficiency(1.5, 1000, 125, 155).calculate() == Approx(0.3053676798));
	CHECK(MoverEfficiency(1.5, 1000, 125, 255).calculate() == Approx(0.1856156485));
	CHECK(MoverEfficiency(1.5, 1000, 125, 425).calculate() == Approx(0.1113693891));
}

TEST_CASE( "PSAT motor efficiency", "[PSAT][pump efficiency]" ) {
	CHECK(MoverEfficiency(0.5, 1000, 125, 125).calculate() == Approx(0.126218641));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(3.5, 1000, 125, 125).calculate() == Approx(0.8835304869));
	CHECK(MoverEfficiency(9.5, 1000, 125, 125).calculate() == Approx(2.3981541786));
	CHECK(MoverEfficiency(20.5, 1000, 125, 125).calculate() == Approx(5.1749642801));
	CHECK(MoverEfficiency(50.5, 1000, 125, 125).calculate() == Approx(12.7480827388));

	CHECK(MoverEfficiency(1.5, 500, 125, 125).calculate() == Approx(0.1893279615));
	CHECK(MoverEfficiency(1.5, 700, 125, 125).calculate() == Approx(0.2650591461));
	CHECK(MoverEfficiency(1.5, 1100, 125, 125).calculate() == Approx(0.4165215152));
	CHECK(MoverEfficiency(1.5, 1800, 125, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 2800, 125, 125).calculate() == Approx(1.0602365842));

	CHECK(MoverEfficiency(1.5, 1000, 25, 125).calculate() == Approx(0.0757311846));
	CHECK(MoverEfficiency(1.5, 1000, 75, 125).calculate() == Approx(0.2271935538));
	CHECK(MoverEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(MoverEfficiency(1.5, 1000, 195, 125).calculate() == Approx(0.5907032398));
	CHECK(MoverEfficiency(1.5, 1000, 225, 125).calculate() == Approx(0.6815806613));
	CHECK(MoverEfficiency(1.5, 1000, 325, 125).calculate() == Approx(0.9845053996));

	CHECK(MoverEfficiency(1.5, 1000, 125, 25).calculate() == Approx(1.8932796147));
	CHECK(MoverEfficiency(1.5, 1000, 125, 75).calculate() == Approx(0.6310932049));
	CHECK(MoverEfficiency(1.5, 1000, 125, 155).calculate() == Approx(0.3053676798));
	CHECK(MoverEfficiency(1.5, 1000, 125, 255).calculate() == Approx(0.1856156485));
	CHECK(MoverEfficiency(1.5, 1000, 125, 425).calculate() == Approx(0.1113693891));
}

//TEST_CASE( "Motor Current", "[MotorCurrent][PSAT]" ) {
//	CHECK(MotorCurrent(150, 1600, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 1.5, 25, 225).calculate() == Approx(0));
//
//	EstimateFLA estimateFLA(motorRatedPower, motorRPM, lineFrequency, efficiencyClass, specifiedEfficiency,
//	                        ratedVoltage);
//}

TEST_CASE( "EstimateFLA", "[EstimateFLA]" ) {
	auto unitTestNumber = 0; // unit test number 0 indexed
	const std::array<std::array<double, 6>, 9> expected = {
			{
					{{18.8775576, 23.6212730421, 34.0613092325, 46.5048449789, 60.381474681, 75.5372248259}},
					{{48.6495840124, 63.249248253, 96.1954123714, 132.4400532659, 172.6294043084, 215.9593847898}},
					{{49.55811480809, 56.11300070569, 78.49438625307, 102.84658002297, 129.16907799852, 159.7821494841}},
					{{28.6566235624, 39.6191308792, 61.8010643593, 86.8044256422, 113.8781958, 142.6893793376}},
					{{53.3464740091, 75.2070177891, 119.291789, 167.65708225, 219.981424828, 275.6367253}},
					{{66.1147879039, 93.2122073949, 148.887425814, 209.314953096, 274.6608259936, 344.15001497}},
					{{66.1147879039, 93.2122073949, 148.887425814, 209.314953096, 274.6608259936, 344.15001497}},
					{{88.3024614572, 116.2594022102, 179.8542042707, 249.6685871227, 326.1945449939, 408.0693757874}},
					{{494.2117767987, 618.953071161, 849.5097896611, 1130.1225205859, 1439.4257134111, 1780.5696074895}}
			}
	};

	auto const compare = [&unitTestNumber, &expected](const std::array<double, 6> & results) {
		for (auto i = 0; i < results.size(); i++) {
			INFO("index is " + std::to_string(i) + " and the unit test number is " + std::to_string(unitTestNumber));
			CHECK(expected.at(unitTestNumber).at(i) == Approx(results[i]));
		}
		unitTestNumber++;
	};

	// test voltages
	compare(EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(150, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(100, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());

	compare(EstimateFLA(200, 2200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 96.5, 100).calculate());
	compare(EstimateFLA(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 98.5, 110).calculate());

	compare(EstimateFLA(250, 2800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 98.5, 110).calculate());
	compare(EstimateFLA(290, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 93.5, 110).calculate());
	compare(EstimateFLA(1200, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 65.5, 210).calculate());

	// test FLA
	auto t = EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(277.7547835326));

	t = EstimateFLA(150, 2400, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 110);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(707.6948056564));

	t = EstimateFLA(75, 2000, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 110);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(348.9439377969));

	t = EstimateFLA(175, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::ENERGY_EFFICIENT, 0, 220);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(460.3700518143));

	t = EstimateFLA(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 80, 220);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(311.3720600292));

	t = EstimateFLA(120, 1900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 90, 220);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(291.0633925033));

	t = EstimateFLA(90, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 95, 120);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(432.5925070407));

	t = EstimateFLA(150, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 55, 90);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(1457.2693184418));
}
