#include "catch.hpp"
#include <calculator/losses/FlueGas.h>

TEST_CASE( "Calculate Heat Loss for flue gas Losses", "[Heat Loss]" ) {
	const gasComposition composition(94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);
//	auto testVal1 = composition.CH4.specificHeat( 200 );
//	auto testVal2 = composition.C2H6.specificHeat( 200 );
	const double whereIsTheOxygenPercentageInput = -1;

	auto const randomAnswer = -1;
	REQUIRE(FlueGas(700, whereIsTheOxygenPercentageInput, 9.0, 125, composition).getHeatLoss() == Approx(randomAnswer));
}