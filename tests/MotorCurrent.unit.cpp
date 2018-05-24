#include "catch.hpp"
#include <sqlite/SQLite.h>
#include <calculator/motor/MotorCurrent.h>

TEST_CASE( "Motor Current", "[MotorCurrent]" ) {
//	auto const fq60 = Motor::LineFrequency::FREQ60;
//	auto const ee = Motor::EfficiencyClass::ENERGY_EFFICIENT;
//	CHECK(MotorCurrent(350, 1185, fq60, Motor::EfficiencyClass::STANDARD, 0, 0.97, 2300).calculateCurrent(83) == Approx(80.5));
//
//	CHECK(MotorCurrent(100, 1500, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(113.9111396342));
//	CHECK(MotorCurrent(120, 1500, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(112.2355948772));
//	CHECK(MotorCurrent(150, 1500, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(110.3328367693));
//	CHECK(MotorCurrent(180, 1500, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(108.97704567));
//	CHECK(MotorCurrent(250, 1500, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(107.1512567277));
//
//	CHECK(MotorCurrent(100, 1500, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(37.5854798264));
//	CHECK(MotorCurrent(120, 1500, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(44.3069065935));
//	CHECK(MotorCurrent(150, 1500, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(54.302310895));
//	CHECK(MotorCurrent(180, 1500, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(64.2525815938));
//	CHECK(MotorCurrent(250, 1500, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(87.4774527372));
//
//	CHECK(MotorCurrent(200, 900, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(135.991122668));
//	CHECK(MotorCurrent(200, 1500, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(108.2986719078));
//	CHECK(MotorCurrent(200, 2200, fq60, ee, 0, 0.15, 200).calculateCurrent(150) == Approx(100.0520070981));
//
//	CHECK(MotorCurrent(200, 900, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(98.8934787908));
//	CHECK(MotorCurrent(200, 1500, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(70.8808881854));
//	CHECK(MotorCurrent(200, 2200, fq60, ee, 0, 0.15, 200).calculateOptimalCurrent() == Approx(63.7958929808));
//
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.25, 200).calculateCurrent(150) == Approx(124.5677028442));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.45, 200).calculateCurrent(150) == Approx(177.671084306));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.65, 200).calculateCurrent(150) == Approx(234.3014255141));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.85, 200).calculateCurrent(150) == Approx(295.7379620495));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.15, 200).calculateCurrent(150) == Approx(396.4781133009));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.5, 200).calculateCurrent(150) == Approx(524.1751512313));
//
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.25, 200).calculateOptimalCurrent() == Approx(81.528879914));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.45, 200).calculateOptimalCurrent() == Approx(116.2847525149));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.65, 200).calculateOptimalCurrent() == Approx(153.3490009711));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.85, 200).calculateOptimalCurrent() == Approx(193.558877971));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.15, 200).calculateOptimalCurrent() == Approx(259.4927557449));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.5, 200).calculateOptimalCurrent() == Approx(343.06976835));
//
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.25, 50).calculateCurrent(150) == Approx(498.2708113768));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.45, 100).calculateCurrent(150) == Approx(355.3421686122));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.65, 150).calculateCurrent(150) == Approx(312.4019006854));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.15, 250).calculateCurrent(150) == Approx(317.1824906408));
//
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.25, 50).calculateOptimalCurrent() == Approx(81.528879914));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.45, 100).calculateOptimalCurrent() == Approx(116.2847525149));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.65, 150).calculateOptimalCurrent() == Approx(153.3490009711));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.15, 250).calculateOptimalCurrent() == Approx(259.4927557449));
//
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.25, 50).calculateCurrent(70) == Approx(232.5263786425));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.45, 100).calculateCurrent(100) == Approx(236.8947790748));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 0.65, 150).calculateCurrent(140) == Approx(291.5751073064));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.15, 250).calculateCurrent(190) == Approx(401.764488145));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.15, 250).calculateCurrent(240) == Approx(507.4919850252));
//	CHECK(MotorCurrent(200, 1800, fq60, ee, 0, 1.15, 250).calculateCurrent(290) == Approx(613.2194819055));
}