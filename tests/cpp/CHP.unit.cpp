#include <catch.hpp>
#include "calculator/util/CHP.h"

TEST_CASE( "CHP", "[CHP]") {
	auto chp = CHP(4160, 23781908, 122581, 5.49, 0.214, CHP::Option::PercentAvgkWhElectricCostAvoided, 5.49, 5.49, 90.0, 85.0, 95, 90);

	auto const & costInfo = chp.getCostInfo();

	CHECK(costInfo.annualOperationSavings == Approx(3251705.06182641));
	CHECK(costInfo.totalInstalledCostsPayback == Approx(11890954.0));
	CHECK(costInfo.simplePayback == Approx(3.595330381));
	CHECK(costInfo.fuelCosts == Approx(0.0648161938));
	CHECK(costInfo.thermalCredit == Approx(-0.0284427212));
	CHECK(costInfo.incrementalOandMDollarsKwH == Approx(0.0123));
	CHECK(costInfo.totalOperatingCostsToGenerate == Approx(0.0486734726));

	auto chp2 = CHP(4160, 23781908, 122581, 5.49, 0.214, CHP::Option::StandbyRate, 5.49, 5.49, 9.75, 85.0, 95, 90);

	auto const & costInfo2 = chp2.getCostInfo();

	CHECK(costInfo2.annualOperationSavings == Approx(3066325.0889664106));
	CHECK(costInfo2.totalInstalledCostsPayback == Approx(11890954.0));
	CHECK(costInfo2.simplePayback == Approx(3.8126922817));
	CHECK(costInfo2.fuelCosts == Approx(0.0648161938));
	CHECK(costInfo2.thermalCredit == Approx(-0.0284427212));
	CHECK(costInfo2.incrementalOandMDollarsKwH == Approx(0.0123));
	CHECK(costInfo2.totalOperatingCostsToGenerate == Approx(0.0486734726));
}