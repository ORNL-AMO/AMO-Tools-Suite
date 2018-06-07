#include "catch.hpp"
#include <sqlite/SQLite.h>
#include <calculator/motor/MotorCurrent.h>

TEST_CASE( "Motor Current", "[MotorCurrent]" ) {
    // Added new unit tests by Kristina Armstrong
    auto const fq60 = Motor::LineFrequency::FREQ60;
    auto const ee = Motor::EfficiencyClass::ENERGY_EFFICIENT;
    CHECK(MotorCurrent(100, 1500, fq60, ee, 0, 0.25, 460).calculateCurrent(113.8) == Approx(42.72830));
    CHECK(MotorCurrent(500, 1785, fq60, ee, 0, 0.25, 2300).calculateCurrent(557.9) == Approx(197.4057226065));
    CHECK(MotorCurrent(500, 1785, fq60, ee, 0, 0.5, 2300).calculateCurrent(557.9) == Approx(304.6652143255));
    CHECK(MotorCurrent(500, 1785, fq60, ee, 0, 0.75, 2300).calculateCurrent(557.9) == Approx(426.5420335857));
}