#include "catch.hpp"
#include <calculator/losses/AuxiliaryPower.h>

TEST_CASE( "Calculate power used for ??", "[Power Used]") {
	CHECK( AuxiliaryPower(3, 460, 19, 0.85, 100).getPowerUsed() == Approx(12.867405449) );
	CHECK( AuxiliaryPower(3, 510, 19, 0.85, 100).getPowerUsed() == Approx(14.266036476) );
	CHECK( AuxiliaryPower(3, 510, 25, 0.85, 100).getPowerUsed() == Approx(18.771100627) );
	CHECK( AuxiliaryPower(3, 510, 25, 0.55, 100).getPowerUsed() == Approx(12.146006288) );
	CHECK( AuxiliaryPower(3, 510, 25, 0.550, 75).getPowerUsed() == Approx(9.1095047161) );
}
