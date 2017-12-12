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
	CHECK(mod.motorEfficiency * 100 == Approx(94.3652462131));
	CHECK(mod.motorPowerFactor * 100 == Approx(76.2584456388));
	CHECK(mod.motorCurrent == Approx(126.5852583329));
	CHECK(mod.motorPower == Approx(80.2551564807));
	CHECK(mod.annualEnergy == Approx(703.0351707712));
	CHECK(mod.annualCost * 1000.0 == Approx(35151.7585385623));


	CHECK(opt.pumpEfficiency * 100 == Approx(86.75480583084276));
	CHECK(opt.motorRatedPower == Approx(100));
	CHECK(opt.motorShaftPower == Approx(93.6145627007516));
	CHECK(opt.pumpShaftPower == Approx(93.614562700751));
	CHECK(opt.motorEfficiency * 100 == Approx(95.02783605700556));
	CHECK(opt.motorPowerFactor * 100 == Approx(85.97645176630047));
	CHECK(opt.motorCurrent == Approx(102.81349971661015));
	CHECK(opt.motorPower == Approx(73.49055466145589));
	CHECK(opt.annualEnergy == Approx(643.777258834353));
	CHECK(opt.annualCost * 1000.0 == Approx(32188.86294171768));

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
	CHECK(mod.motorEfficiency * 100 == Approx(95.0700964487));
	CHECK(mod.motorPowerFactor * 100 == Approx(86.8975146434));
	CHECK(mod.motorCurrent == Approx(207.128014213));
	CHECK(mod.motorPower == Approx(149.6401247588));
	CHECK(mod.annualEnergy == Approx(1310.8474928874));
	CHECK(mod.annualCost * 1000.0 == Approx(78650.8495732458));
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
	CHECK(mod.motorPower == Approx(151.8722277599));
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
	const std::vector<std::vector<double>> expected = {
			{18.8775576, 23.6212730421, 34.0613092325, 46.5048449789, 60.381474681, 75.5372248259},
			{48.6495840124, 63.249248253, 96.1954123714, 132.4400532659, 172.6294043084, 215.9593847898},
			{49.55811480809, 56.11300070569, 78.49438625307, 102.84658002297, 129.16907799852, 159.7821494841},
			{28.6566235624, 39.6191308792, 61.8010643593, 86.8044256422, 113.8781958, 142.6893793376},
			{53.3464740091, 75.2070177891, 119.291789, 167.65708225, 219.981424828, 275.6367253},
			{0, 0, 0, 0, 0, 0}

	};

	auto const compare = [&unitTestNumber, &expected](const std::vector<double> & results) {
		for (auto i = 0; i < results.size(); i++) {
			INFO("index is " + std::to_string(i) + " and the unit test number is " + std::to_string(unitTestNumber));
			CHECK(expected.at(unitTestNumber).at(i) == Approx(results[i]));
		}
		unitTestNumber++;
	};

	compare(EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(150, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(100, 900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());
	compare(EstimateFLA(100, 2900, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 0, 100).calculate());

	compare(EstimateFLA(200, 2200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 96.5, 100).calculate());
//	compare(EstimateFLA(200, 2200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 96.5, 150).calculate());

//	auto rv = EstimateFLA(200, 2200, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::SPECIFIED, 56.5, 150).calculate();



	auto blah = 0;

//	CHECK(EstimateFLA(50, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 100).calculate() == Approx(0));
//	CHECK(EstimateFLA(125, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 100).calculate() == Approx(0));
//	CHECK(EstimateFLA(225, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 100).calculate() == Approx(0));
//	CHECK(EstimateFLA(325, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 100).calculate() == Approx(0));
//	CHECK(EstimateFLA(425, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 100).calculate() == Approx(0));
//	CHECK(EstimateFLA(525, 1800, Motor::LineFrequency::FREQ60, Motor::EfficiencyClass::STANDARD, 100).calculate() == Approx(0));


}
