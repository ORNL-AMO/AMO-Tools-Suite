#include "catch.hpp"
#include <fans/OptimalFanEfficiency.h>

TEST_CASE( "OptimalFanEfficiency", "[OptimalFanEfficiency]" ) {
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.8056103029);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.7953321519);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.3474991977);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialTipSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.7312425577);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedSISW, 1180, 40000, -9, 1, .995).calculate()) == 0.795733737);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilDIDW, 1180, 40000, -9, 1, .995).calculate()) == 0.7672457454);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedDIDW, 1180, 40000, -9, 1, .995).calculate()) == 0.7450780156);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedDIDW, 1180, 40000, -9, 1, .995).calculate()) == 0.7294332986);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::VaneAxial, 1180, 40000, -9, 1, .995).calculate()) == 0.620617052);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirHandling, 1180, 40000, -9, 1, .995).calculate()) == 0.4616312646);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::MaterialHandling, 1180, 40000, -9, 1, .995).calculate()) == 0.3971050412);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::LongShavings, 1180, 40000, -9, 1, .995).calculate()) == 0.3623692017);

	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilSISW, 1180, 10000, -9, 1, .995).calculate()) == 0.6902100469);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedSISW, 1180, 10000, -9, 1, .995).calculate()) == 0.7480133871);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialSISW, 1180, 10000, -9, 1, .995).calculate()) == 0.5758852848);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialTipSISW, 1180, 10000, -9, 1, .995).calculate()) == 0.7338991444);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedSISW, 1180, 10000, -9, 1, .995).calculate()) == 0.7620531542);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilDIDW, 1180, 10000, -9, 1, .995).calculate()) == 0.7013544059);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedDIDW, 1180, 10000, -9, 1, .995).calculate()) == 0.6998167713);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedDIDW, 1180, 10000, -9, 1, .995).calculate()) == 0.7294332986);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::VaneAxial, 1180, 10000, -9, 1, .995).calculate()) == 0.620617052);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirHandling, 1180, 10000, -9, 1, .995).calculate()) == 0.6887947846);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::MaterialHandling, 1180, 10000, -9, 1, .995).calculate()) == 0.6473690517);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::LongShavings, 1180, 10000, -9, 1, .995).calculate()) == 0.606953126);

	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilSISW, 1180, 500000, -6, 1, .995).calculate()) == 0.288496945);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedSISW, 1180, 500000, -6, 1, .995).calculate()) == 0.4672099681);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialSISW, 1180, 500000, -6, 1, .995).calculate()) == 0.0918033416);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::RadialTipSISW, 1180, 500000, -6, 1, .995).calculate()) == 0.1691654819);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedSISW, 1180, 500000, -6, 1, .995).calculate()) == 0.2907461986);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirfoilDIDW, 1180, 500000, -6, 1, .995).calculate()) == 0.3514341411);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardCurvedDIDW, 1180, 500000, -6, 1, .995).calculate()) == 0.2931237501);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::BackwardInclinedDIDW, 1180, 500000, -6, 1, .995).calculate()) == 0.2717324805);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::VaneAxial, 1180, 500000, -6, 1, .995).calculate()) == 0.516389969);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::AirHandling, 1180, 500000, -6, 1, .995).calculate()) == 0.288276231);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::MaterialHandling, 1180, 500000, -6, 1, .995).calculate()) == 0.2347489227);
	CHECK(Approx(OptimalFanEfficiency(OptimalFanEfficiency::FanType::LongShavings, 1180, 500000, -6, 1, .995).calculate()) == 0.0615065739);
}
