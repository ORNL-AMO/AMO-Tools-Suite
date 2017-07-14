#include "catch.hpp"
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>

TEST_CASE( "Calculate SolidLiquidFlueGasMaterial Heat Loss", "[Heat Loss]" ) {
	auto excessAir = SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2(0.005, 1.0, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
	REQUIRE(excessAir == Approx(0.0229427817));

	excessAir = SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2(0.03, 1.0, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
	REQUIRE(excessAir == Approx(0.1536865757));

	excessAir = SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2(0.07, 1.0, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5);
	REQUIRE(excessAir == Approx(0.4475000362));

	REQUIRE(SolidLiquidFlueGasMaterial(700, 2.29427817, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5).getHeatLoss() == Approx(0.8297708724));
	REQUIRE(SolidLiquidFlueGasMaterial(700, 15.36865757, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5).getHeatLoss() == Approx(0.8151987637));
	REQUIRE(SolidLiquidFlueGasMaterial(700, 44.75000362, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5).getHeatLoss() == Approx(0.7824331922));
	REQUIRE(SolidLiquidFlueGasMaterial(700, 9.0, 125, 70, 1.0, 100, 1.5, 75.0, 5.0, 1.0, 9.0, 7.0, 0.0, 1.5).getHeatLoss() == Approx(0.8223));
}