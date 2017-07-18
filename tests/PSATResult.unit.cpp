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
	PSATResult psat(pump, motor, fin, fd);

	psat.calculateExisting();
	psat.calculateOptimal();
	auto const & ex = psat.getExisting();
	auto const & opt = psat.getOptimal();

	REQUIRE(ex.pumpEfficiency_ * 100 == Approx(80.2620381));
	REQUIRE(ex.motorRatedPower_ == Approx(200));
	REQUIRE(ex.motorShaftPower_ == Approx(101.18747791246317));
	REQUIRE(ex.pumpShaftPower_ == Approx(101.18747791246317));
	REQUIRE(ex.motorEfficiency_ * 100 == Approx(94.35732315337191));
	REQUIRE(ex.motorPowerFactor_ * 100 == Approx(76.45602656178534));
	REQUIRE(ex.motorCurrent_ == Approx(125.85671685040634));
	REQUIRE(ex.motorPower_ == Approx(80));
	REQUIRE(ex.annualEnergy_ == Approx(700.8));
	REQUIRE(ex.annualCost_ * 1000.0 == Approx(35040));


	REQUIRE(opt.pumpEfficiency_ * 100 == Approx(86.75480583084276));
	REQUIRE(opt.motorRatedPower_ == Approx(100));
	REQUIRE(opt.motorShaftPower_ == Approx(93.6145627007516));
	REQUIRE(opt.pumpShaftPower_ == Approx(93.614562700751));
	REQUIRE(opt.motorEfficiency_ * 100 == Approx(95.02783605700556));
	REQUIRE(opt.motorPowerFactor_ * 100 == Approx(85.97645176630047));
	REQUIRE(opt.motorCurrent_ == Approx(102.81349971661015));
	REQUIRE(opt.motorPower_ == Approx(73.49055466145589));
	REQUIRE(opt.annualEnergy_ == Approx(643.777258834353));
	REQUIRE(opt.annualCost_ * 1000.0 == Approx(32188.86294171768));

	REQUIRE(psat.getAnnualSavingsPotential() * 1000 == Approx(2851.1370582823192));
	REQUIRE(psat.getOptimizationRating() == Approx(0.9186319332681986));

}


