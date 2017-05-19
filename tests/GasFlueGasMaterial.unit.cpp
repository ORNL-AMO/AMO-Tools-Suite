#include "catch.hpp"
#include <calculator/losses/GasFlueGasMaterial.h>

TEST_CASE( "Calculate Heat Loss for flue gas Losses", "[Heat Loss]" ) {
	GasCompositions composition("unit test gas", 94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);

	REQUIRE(GasFlueGasMaterial(700, 9.0, 125, composition).getHeatLoss() == Approx(0.76899));
}