#include "catch.hpp"
#include <calculator/losses/FlueGas.h>

TEST_CASE( "Calculate Heat Loss for flue gas Losses", "[Heat Loss]" ) {
	const gasComposition composition(94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);
	const double whereIsTheOxygenPercentageInput = -1;

	REQUIRE(FlueGas(700, whereIsTheOxygenPercentageInput, 9.0, 125, composition).getHeatLoss() == Approx(1924294214.0));
//    REQUIRE(FlueGas(0.1, 3.0, 1600.0).getHeatLoss() == Approx(2850767.0 ) );

}