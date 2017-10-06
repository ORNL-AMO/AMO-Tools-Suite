#include <catch.hpp>
#include "calculator/util/CHP.h"

TEST_CASE( "CHP", "[CHP]") {
	auto chp = CHP(4160, 23781908, 122581, 5.49, 0.214, CHP::Option::PercentAvgkWhElectricCostAvoided, 5.49, 5.49, 90.0, 85.0);

//	CHECK(header.getSpecificEnthalpy() == Approx(1820.064143168));
}