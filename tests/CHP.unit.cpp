#include <catch.hpp>
#include "calculator/util/CHP.h"

TEST_CASE( "CHP", "[CHP]") {
	auto chp = CHP(4160, 23781908, 122581, 5.49, 0.214, CHP::Option::PercentAvgkWhElectricCostAvoided, 5.49, 5.49, 90.0, 85.0, 95, 90);

	auto const & costInfo = chp.getCostInfo();

	CHECK(costInfo.at("annualOperationSavings") == Approx(3251705.06182641));
	CHECK(costInfo.at("totalInstalledCostsPayback") == Approx(11890954.0));
	CHECK(costInfo.at("simplePayback") == Approx(3.595330381));
	CHECK(costInfo.at("fuelCosts") == Approx(0.0648161938));
	CHECK(costInfo.at("thermalCredit") == Approx(-0.0284427212));
	CHECK(costInfo.at("incrementalOandM") == Approx(0.0123));
	CHECK(costInfo.at("totalOperatingCosts") == Approx(0.0486734726));
}