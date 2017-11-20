#include "catch.hpp"
#include <psat/Pump.h>
#include <psat/FieldData.h>
#include <psat/Financial.h>
#include <psat/Motor.h>
#include <psat/OptimizationRating.h>
#include <psat/PSATResult.h>
#include <unordered_map>

TEST_CASE( "PSATResults", "[PSAT results]" ) {
	double pump_specified = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.0, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.05, flow_rate = 1840;
	double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
	double baseline_pump_efficiency = 0.80;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Pump::Drive drive1(Pump::Drive::DIRECT_DRIVE);
	Pump::Speed fixed_speed(Pump::Speed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
	FieldData::LoadEstimationMethod loadEstimationMethod1(FieldData::LoadEstimationMethod::POWER);

	Pump pump(style1, pump_specified, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Financial fin(operating_fraction, cost_kw_hour);
	FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fin, fd, baseline_pump_efficiency);

	psat.calculateExisting();
	psat.calculateModified();
	psat.calculateOptimal();
	auto const & ex = psat.getExisting();
	auto const & mod = psat.getModified();
	auto const & opt = psat.getOptimal();

	CHECK(ex.pumpEfficiency_ * 100 == Approx(80.2620381));
	CHECK(ex.motorRatedPower_ == Approx(200));
	CHECK(ex.motorShaftPower_ == Approx(101.18747791246317));
	CHECK(ex.pumpShaftPower_ == Approx(101.18747791246317));
	CHECK(ex.motorEfficiency_ * 100 == Approx(94.35732315337191));
	CHECK(ex.motorPowerFactor_ * 100 == Approx(76.45602656178534));
	CHECK(ex.motorCurrent_ == Approx(125.85671685040634));
	CHECK(ex.motorPower_ == Approx(80));
	CHECK(ex.annualEnergy_ == Approx(700.8));
	CHECK(ex.annualCost_ * 1000.0 == Approx(35040));

	CHECK(mod.pumpEfficiency_ * 100 == Approx(80));
	CHECK(mod.motorRatedPower_ == Approx(200));
	CHECK(mod.motorShaftPower_ == Approx(101.5189151255));
	CHECK(mod.pumpShaftPower_ == Approx(101.5189151255));
	CHECK(mod.motorEfficiency_ * 100 == Approx(94.3652462131));
	CHECK(mod.motorPowerFactor_ * 100 == Approx(76.2584456388));
	CHECK(mod.motorCurrent_ == Approx(126.5852583329));
	CHECK(mod.motorPower_ == Approx(80.2551564807));
	CHECK(mod.annualEnergy_ == Approx(703.0351707712));
	CHECK(mod.annualCost_ * 1000.0 == Approx(35151.7585385623));


	CHECK(opt.pumpEfficiency_ * 100 == Approx(86.75480583084276));
	CHECK(opt.motorRatedPower_ == Approx(100));
	CHECK(opt.motorShaftPower_ == Approx(93.6145627007516));
	CHECK(opt.pumpShaftPower_ == Approx(93.614562700751));
	CHECK(opt.motorEfficiency_ * 100 == Approx(95.02783605700556));
	CHECK(opt.motorPowerFactor_ * 100 == Approx(85.97645176630047));
	CHECK(opt.motorCurrent_ == Approx(102.81349971661015));
	CHECK(opt.motorPower_ == Approx(73.49055466145589));
	CHECK(opt.annualEnergy_ == Approx(643.777258834353));
	CHECK(opt.annualCost_ * 1000.0 == Approx(32188.86294171768));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));

}

TEST_CASE( "PSATResults - new test", "[PSAT results]" ) {
	double pump_specified = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 227.29, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 277.0, motor_field_power = 150.0, motor_field_current = 125.857, motor_field_voltage = 480;
	double baseline_pump_efficiency = 0.382;
	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Pump::Drive drive1(Pump::Drive::V_BELT_DRIVE);
	Pump::Speed fixed_speed(Pump::Speed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::SPECIFIED);
	FieldData::LoadEstimationMethod loadEstimationMethod1(FieldData::LoadEstimationMethod::POWER);
	Pump pump(style1, pump_specified, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Financial fin(operating_fraction, cost_kw_hour);
	FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fin, fd, baseline_pump_efficiency);
	psat.calculateExisting();
	psat.calculateModified();
	auto const & ex = psat.getExisting();
	auto const & mod = psat.getModified();
	CHECK(ex.pumpEfficiency_ * 100 == Approx(38.1094253534));
	CHECK(ex.motorRatedPower_ == Approx(200));
	CHECK(ex.motorShaftPower_ == Approx(191.1541214642));
	CHECK(ex.pumpShaftPower_ == Approx(183.4851259332));
	CHECK(ex.motorEfficiency_ * 100 == Approx(95.0673164082));
	CHECK(ex.motorPowerFactor_ * 100 == Approx(86.3561411197));
	CHECK(ex.motorCurrent_ == Approx(208.9277690995));
	CHECK(ex.motorPower_ == Approx(150.0));
	CHECK(ex.annualEnergy_ == Approx(1314.0));
	CHECK(ex.annualCost_ * 1000.0 == Approx(78840));
	CHECK(mod.pumpEfficiency_ * 100 == Approx(38.2));
	CHECK(mod.motorRatedPower_ == Approx(200));
	CHECK(mod.motorShaftPower_ == Approx(190.7010275392));
	CHECK(mod.pumpShaftPower_ == Approx(183.0500709481));
	CHECK(mod.motorEfficiency_ * 100 == Approx(95.0700964487));
	CHECK(mod.motorPowerFactor_ * 100 == Approx(86.8975146434));
	CHECK(mod.motorCurrent_ == Approx(207.128014213));
	CHECK(mod.motorPower_ == Approx(149.6401247588));
	CHECK(mod.annualEnergy_ == Approx(1310.8474928874));
	CHECK(mod.annualCost_ * 1000.0 == Approx(78650.8495732458));
}

TEST_CASE( "PSATResults2 v-belt type", "[PSAT results]" ) {
	double pump_specified = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double baseline_pump_efficiency = 0.623;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Pump::Drive drive1(Pump::Drive::V_BELT_DRIVE);
	Pump::Speed fixed_speed(Pump::Speed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	FieldData::LoadEstimationMethod loadEstimationMethod1(FieldData::LoadEstimationMethod::POWER);

	Pump pump(style1, pump_specified, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Financial fin(operating_fraction, cost_kw_hour);
	FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fin, fd, baseline_pump_efficiency);

	psat.calculateExisting();
	psat.calculateModified();
	psat.calculateOptimal();
	auto const & ex = psat.getExisting();
	auto const & mod = psat.getModified();
	auto const & opt = psat.getOptimal();

	CHECK(mod.pumpEfficiency_ * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower_ == Approx(200));
	CHECK(mod.motorShaftPower_ == Approx(200.507050278));
	CHECK(mod.pumpShaftPower_ == Approx(192.468232632));
	CHECK(mod.motorEfficiency_ * 100 == Approx(95.6211069257));
	CHECK(mod.motorPowerFactor_ * 100 == Approx(86.7354953183));
	CHECK(mod.motorCurrent_ == Approx(226.3599309627));
	CHECK(mod.motorPower_ == Approx(156.4281376282));
	CHECK(mod.annualEnergy_ == Approx(1370.3104856228));
	CHECK(mod.annualCost_ * 1000.0 == Approx(82218.6291373691));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));
}

TEST_CASE( "PSATResults notched v belt", "[PSAT results]" ) {
	double pump_specified = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double baseline_pump_efficiency = 0.623;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Pump::Drive drive1(Pump::Drive::N_V_BELT_DRIVE);
	Pump::Speed fixed_speed(Pump::Speed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	FieldData::LoadEstimationMethod loadEstimationMethod1(FieldData::LoadEstimationMethod::POWER);

	Pump pump(style1, pump_specified, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Financial fin(operating_fraction, cost_kw_hour);
	FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fin, fd, baseline_pump_efficiency);

	psat.calculateExisting();
	psat.calculateModified();
	psat.calculateOptimal();
	auto const & ex = psat.getExisting();
	auto const & mod = psat.getModified();
	auto const & opt = psat.getOptimal();

	CHECK(mod.pumpEfficiency_ * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower_ == Approx(200));
	CHECK(mod.motorShaftPower_ == Approx(198.2102452363));
	CHECK(mod.pumpShaftPower_ == Approx(192.468232632));
	CHECK(mod.motorEfficiency_ * 100 == Approx(95.6417064886));
	CHECK(mod.motorPowerFactor_ * 100 == Approx(86.6915209945));
	CHECK(mod.motorCurrent_ == Approx(223.8322217984));
	CHECK(mod.motorPower_ == Approx(154.6029182589));
	CHECK(mod.annualEnergy_ == Approx(1354.3215639476));
	CHECK(mod.annualCost_ * 1000.0 == Approx(81259.2938368578));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));
}

TEST_CASE( "PSATResults sync belt", "[PSAT results]" ) {
	double pump_specified = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 1.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.8, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.06, flow_rate = 1000;
	double head = 475, motor_field_power = 150, motor_field_current = 125.857, motor_field_voltage = 460;
	double baseline_pump_efficiency = 0.623;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Pump::Drive drive1(Pump::Drive::S_BELT_DRIVE);
	Pump::Speed fixed_speed(Pump::Speed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::ENERGY_EFFICIENT);
	FieldData::LoadEstimationMethod loadEstimationMethod1(FieldData::LoadEstimationMethod::POWER);

	Pump pump(style1, pump_specified, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Financial fin(operating_fraction, cost_kw_hour);
	FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fin, fd, baseline_pump_efficiency);

	psat.calculateExisting();
	psat.calculateModified();
	psat.calculateOptimal();
	auto const & ex = psat.getExisting();
	auto const & mod = psat.getModified();
	auto const & opt = psat.getOptimal();

	CHECK(mod.motorShaftPower_ == Approx(194.767));
	CHECK(mod.pumpShaftPower_ == Approx(192.468232632));
	CHECK(mod.motorPower_ == Approx(151.8722277599));
}

