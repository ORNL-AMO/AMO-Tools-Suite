#include "catch.hpp"
#include <calculator/losses/AuxiliaryPower.h>

TEST_CASE( "Calculate power used for ??", "[Power Used]") {
	CHECK(AuxiliaryPower(3, 460, 19, 0.85, 100).getPowerUsed() == Approx(43905.3405494047));
	CHECK(AuxiliaryPower(3, 510, 19, 0.85, 100).getPowerUsed() == Approx(48677.66017434));
	CHECK(AuxiliaryPower(3, 510, 25, 0.85, 100).getPowerUsed() == Approx(64049.5528609737));
	CHECK(AuxiliaryPower(3, 510, 25, 0.55, 100).getPowerUsed() == Approx(41443.8283218065));
	CHECK(AuxiliaryPower(3, 510, 25, 0.550, 75).getPowerUsed() == Approx(31082.8712413549));
}
