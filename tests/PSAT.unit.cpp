#include "catch.hpp"
#include <psat/Pump.h>
#include <psat/FieldData.h>
#include <psat/Financial.h>
#include <psat/Motor.h>
#include <psat/PSATResult.h>
#include <unordered_map>
#include <calculator/pump/PumpShaftPower.h>
#include <calculator/pump/PumpEfficiency.h>
#include <array>
#include <calculator/motor/MotorEfficiency.h>
#include <string>
#include <calculator/motor/MotorCurrent.h>
#include <calculator/motor/EstimateFLA.h>

TEST_CASE( "PSATResultsPremium", "[PSAT results]" ) {
	double pump_specified = 90, pump_rated_speed = 1780, kinematic_viscosity = 1.0, specific_gravity = 1.0;
	double stages = 2.0, motor_rated_power = 200, motor_rated_speed = 1780, efficiency = 95, motor_rated_voltage = 460;
	double motor_rated_fla = 225.0, margin = 0, operating_fraction = 1.00, cost_kw_hour = 0.05, flow_rate = 1840;
	double head = 174.85, motor_field_power = 80, motor_field_current = 125.857, motor_field_voltage = 480;
	double baseline_pump_efficiency = 0.80;

	Pump::Style style1(Pump::Style::END_SUCTION_ANSI_API);
	Pump::Drive drive1(Pump::Drive::DIRECT_DRIVE);
	Pump::Speed fixed_speed(Pump::Speed::NOT_FIXED_SPEED);
	Motor::LineFrequency lineFrequency(Motor::LineFrequency::FREQ60);
	Motor::EfficiencyClass efficiencyClass(Motor::EfficiencyClass::PREMIUM);
	FieldData::LoadEstimationMethod loadEstimationMethod1(FieldData::LoadEstimationMethod::POWER);

	Pump pump(style1, pump_specified, pump_rated_speed, drive1, kinematic_viscosity, specific_gravity, stages, fixed_speed);
	Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
	Financial fin(operating_fraction, cost_kw_hour);
	FieldData fd(flow_rate, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
	PSATResult psat(pump, motor, fin, fd, baseline_pump_efficiency);

	psat.calculateExisting();
//	psat.calculateModified();
	psat.calculateOptimal();
	auto const & ex = psat.getExisting();
//	auto const & mod = psat.getModified();
	auto const & opt = psat.getOptimal();

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
	CHECK(opt.motorPowerFactor * 100 == Approx(85.121115466));
	CHECK(opt.motorCurrent == Approx(103.3131421918));
	CHECK(opt.motorPower == Approx(73.1130230639));
	CHECK(opt.annualEnergy == Approx(640.4700820397));
	CHECK(opt.annualCost * 1000.0 == Approx(32023.5041019837));

	CHECK(psat.getAnnualSavingsPotential() * 1000 == Approx(0));
	CHECK(psat.getOptimizationRating() == Approx(0));

}

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
	CHECK(mod.motorEfficiency * 100 == Approx(96.3793168362));
	CHECK(mod.motorPowerFactor * 100 == Approx(74.2802249228));
	CHECK(mod.motorCurrent == Approx(127.2407888741));
	CHECK(mod.motorPower == Approx(78.5780827034));
	CHECK(mod.annualEnergy == Approx(688.3440044819));
	CHECK(mod.annualCost * 1000.0 == Approx(34417.2002240953));


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
	CHECK(opt.motorEfficiency * 100 == Approx(95.518544304));
	CHECK(opt.motorPowerFactor * 100 == Approx(85.121115466));
	CHECK(opt.motorCurrent == Approx(103.3131421918));
	CHECK(opt.motorPower == Approx(73.1130230639));
	CHECK(opt.annualEnergy == Approx(640.4700820397));
	CHECK(opt.annualCost * 1000.0 == Approx(32023.5041019837));

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
	CHECK(mod.motorEfficiency * 100 == Approx(96.1899252391));
	CHECK(mod.motorPowerFactor * 100 == Approx(85.4433953642));
	CHECK(mod.motorCurrent == Approx(208.2006410027));
	CHECK(mod.motorPower == Approx(147.8980422134));
	CHECK(mod.annualEnergy == Approx(1295.5868497893));
	CHECK(mod.annualCost * 1000.0 == Approx(77735.210987359));
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

	CHECK(mod.pumpEfficiency * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(200.507050278));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorEfficiency * 100 == Approx(96.1169687629));
	CHECK(mod.motorPowerFactor * 100 == Approx(85.8434808116));
	CHECK(mod.motorCurrent == Approx(227.5321515674));
	CHECK(mod.motorPower == Approx(155.6211254681));
	CHECK(mod.annualEnergy == Approx(1363.2410591006));
	CHECK(mod.annualCost * 1000.0 == Approx(81794.4635460345));

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

	CHECK(mod.pumpEfficiency * 100 == Approx(62.3));
	CHECK(mod.motorRatedPower == Approx(200));
	CHECK(mod.motorShaftPower == Approx(198.2102452363));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorEfficiency * 100 == Approx(96.135214302));
	CHECK(mod.motorPowerFactor * 100 == Approx(85.8021579749));
	CHECK(mod.motorCurrent == Approx(224.9913524857));
	CHECK(mod.motorPower == Approx(153.8092647673));
	CHECK(mod.annualEnergy == Approx(1347.3691593614));
	CHECK(mod.annualCost * 1000.0 == Approx(80842.1495616858));

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

	CHECK(mod.motorShaftPower == Approx(194.767));
	CHECK(mod.pumpShaftPower == Approx(192.468232632));
	CHECK(mod.motorPower == Approx(151.0952083421));
}

TEST_CASE( "PSAT pump shaft power", "[PSAT][pump shaft power][drive]" ) {
	CHECK(PumpShaftPower(50, Pump::Drive::N_V_BELT_DRIVE).calculate() == Approx(48.4814329723));
	CHECK(PumpShaftPower(100, Pump::Drive::N_V_BELT_DRIVE).calculate() == Approx(97.0776282082));
	CHECK(PumpShaftPower(150, Pump::Drive::N_V_BELT_DRIVE).calculate() == Approx(145.6804036099));
	CHECK(PumpShaftPower(200, Pump::Drive::N_V_BELT_DRIVE).calculate() == Approx(194.2722411119));
	CHECK(PumpShaftPower(250, Pump::Drive::N_V_BELT_DRIVE).calculate() == Approx(242.8550331213));

	CHECK(PumpShaftPower(50, Pump::Drive::V_BELT_DRIVE).calculate() == Approx(47.8740061612));
	CHECK(PumpShaftPower(100, Pump::Drive::V_BELT_DRIVE).calculate() == Approx(95.9086794914));
	CHECK(PumpShaftPower(150, Pump::Drive::V_BELT_DRIVE).calculate() == Approx(143.9525650539));
	CHECK(PumpShaftPower(200, Pump::Drive::V_BELT_DRIVE).calculate() == Approx(191.981137556));
	CHECK(PumpShaftPower(250, Pump::Drive::V_BELT_DRIVE).calculate() == Approx(239.9970463698));

	CHECK(PumpShaftPower(50, Pump::Drive::S_BELT_DRIVE).calculate() == Approx(49.3925731889));
	CHECK(PumpShaftPower(100, Pump::Drive::S_BELT_DRIVE).calculate() == Approx(98.8310512833));
	CHECK(PumpShaftPower(150, Pump::Drive::S_BELT_DRIVE).calculate() == Approx(148.272161444));
	CHECK(PumpShaftPower(200, Pump::Drive::S_BELT_DRIVE).calculate() == Approx(197.7088964447));
	CHECK(PumpShaftPower(250, Pump::Drive::S_BELT_DRIVE).calculate() == Approx(247.1420132485));
}

TEST_CASE( "PSAT pump efficiency", "[PSAT][pump efficiency]" ) {
	CHECK(PumpEfficiency(0.5, 1000, 125, 125).calculate() == Approx(0.126218641));
	CHECK(PumpEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(PumpEfficiency(3.5, 1000, 125, 125).calculate() == Approx(0.8835304869));
	CHECK(PumpEfficiency(9.5, 1000, 125, 125).calculate() == Approx(2.3981541786));
	CHECK(PumpEfficiency(20.5, 1000, 125, 125).calculate() == Approx(5.1749642801));
	CHECK(PumpEfficiency(50.5, 1000, 125, 125).calculate() == Approx(12.7480827388));

	CHECK(PumpEfficiency(1.5, 500, 125, 125).calculate() == Approx(0.1893279615));
	CHECK(PumpEfficiency(1.5, 700, 125, 125).calculate() == Approx(0.2650591461));
	CHECK(PumpEfficiency(1.5, 1100, 125, 125).calculate() == Approx(0.4165215152));
	CHECK(PumpEfficiency(1.5, 1800, 125, 125).calculate() == Approx(0.6815806613));
	CHECK(PumpEfficiency(1.5, 2800, 125, 125).calculate() == Approx(1.0602365842));

	CHECK(PumpEfficiency(1.5, 1000, 25, 125).calculate() == Approx(0.0757311846));
	CHECK(PumpEfficiency(1.5, 1000, 75, 125).calculate() == Approx(0.2271935538));
	CHECK(PumpEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(PumpEfficiency(1.5, 1000, 195, 125).calculate() == Approx(0.5907032398));
	CHECK(PumpEfficiency(1.5, 1000, 225, 125).calculate() == Approx(0.6815806613));
	CHECK(PumpEfficiency(1.5, 1000, 325, 125).calculate() == Approx(0.9845053996));

	CHECK(PumpEfficiency(1.5, 1000, 125, 25).calculate() == Approx(1.8932796147));
	CHECK(PumpEfficiency(1.5, 1000, 125, 75).calculate() == Approx(0.6310932049));
	CHECK(PumpEfficiency(1.5, 1000, 125, 155).calculate() == Approx(0.3053676798));
	CHECK(PumpEfficiency(1.5, 1000, 125, 255).calculate() == Approx(0.1856156485));
	CHECK(PumpEfficiency(1.5, 1000, 125, 425).calculate() == Approx(0.1113693891));
}

TEST_CASE( "PSAT motor efficiency", "[PSAT][pump efficiency]" ) {
	CHECK(PumpEfficiency(0.5, 1000, 125, 125).calculate() == Approx(0.126218641));
	CHECK(PumpEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(PumpEfficiency(3.5, 1000, 125, 125).calculate() == Approx(0.8835304869));
	CHECK(PumpEfficiency(9.5, 1000, 125, 125).calculate() == Approx(2.3981541786));
	CHECK(PumpEfficiency(20.5, 1000, 125, 125).calculate() == Approx(5.1749642801));
	CHECK(PumpEfficiency(50.5, 1000, 125, 125).calculate() == Approx(12.7480827388));

	CHECK(PumpEfficiency(1.5, 500, 125, 125).calculate() == Approx(0.1893279615));
	CHECK(PumpEfficiency(1.5, 700, 125, 125).calculate() == Approx(0.2650591461));
	CHECK(PumpEfficiency(1.5, 1100, 125, 125).calculate() == Approx(0.4165215152));
	CHECK(PumpEfficiency(1.5, 1800, 125, 125).calculate() == Approx(0.6815806613));
	CHECK(PumpEfficiency(1.5, 2800, 125, 125).calculate() == Approx(1.0602365842));

	CHECK(PumpEfficiency(1.5, 1000, 25, 125).calculate() == Approx(0.0757311846));
	CHECK(PumpEfficiency(1.5, 1000, 75, 125).calculate() == Approx(0.2271935538));
	CHECK(PumpEfficiency(1.5, 1000, 125, 125).calculate() == Approx(0.3786559229));
	CHECK(PumpEfficiency(1.5, 1000, 195, 125).calculate() == Approx(0.5907032398));
	CHECK(PumpEfficiency(1.5, 1000, 225, 125).calculate() == Approx(0.6815806613));
	CHECK(PumpEfficiency(1.5, 1000, 325, 125).calculate() == Approx(0.9845053996));

	CHECK(PumpEfficiency(1.5, 1000, 125, 25).calculate() == Approx(1.8932796147));
	CHECK(PumpEfficiency(1.5, 1000, 125, 75).calculate() == Approx(0.6310932049));
	CHECK(PumpEfficiency(1.5, 1000, 125, 155).calculate() == Approx(0.3053676798));
	CHECK(PumpEfficiency(1.5, 1000, 125, 255).calculate() == Approx(0.1856156485));
	CHECK(PumpEfficiency(1.5, 1000, 125, 425).calculate() == Approx(0.1113693891));
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
	CHECK(t.getEstimatedFLA() ==  Approx(301.1782164872));

	t = EstimateFLA(90, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 95, 120);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(432.5925070407));

	t = EstimateFLA(150, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 55, 90);
	t.calculate();
	CHECK(t.getEstimatedFLA() ==  Approx(1457.2693184418));
}
