#include "catch.hpp"
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>

TEST_CASE( "Calculate SolidLiquidFlueGasMaterial Heat Loss", "[Heat Loss]" ) {
	REQUIRE(SolidLiquidFlueGasMaterial(700, 9.0, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5).getHeatLoss() == Approx(0.8223));
}