#include "catch.hpp"
#include <fans/OptimalFanEfficiency.h>

TEST_CASE( "OptimalFanEfficiency", "[OptimalFanEfficiency]" ) {
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.8056103029);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.7953321519);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.3474991977);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialTipSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.7312425577);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.79);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilDIDW, 1180, 40000, -9, 1, .995).calculate()) == 0.76);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedDIDW, 1180, 40000, -9, 1, .995).calculate()) == 0.74);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedDIDW, 1180, 40000, -9, 1, .995).calculate()) == 0.729);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::VaneAxial, 1180, 40000, -9, 1, .995).calculate()) == 0.62);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirHandling, 1180, 40000, -9, 1, .995).calculate()) == 0.46);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::MaterialHandling, 1180, 40000, -9, 1, .995).calculate()) == 0.39);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::LongShavings, 1180, 40000, -9, 1, .995).calculate()) == 0.36);
//	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::LongShavingsOpen, 1180, 40000, -9, 1, .995).calculate()) == 0.36);
}
