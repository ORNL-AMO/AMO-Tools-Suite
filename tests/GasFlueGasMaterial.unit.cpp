#include "catch.hpp"
#include <calculator/losses/GasFlueGasMaterial.h>

TEST_CASE( "Calculate Heat Loss for flue gas Losses", "[Heat Loss]" ) {
	GasCompositions composition("unit test gas", 94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);

	REQUIRE(composition.calculateExcessAir(0.005) == Approx(0.0231722));
	REQUIRE(composition.calculateExcessAir(0.03) == Approx(0.1552234));
	REQUIRE(composition.calculateExcessAir(0.07) == Approx(0.451975));

	REQUIRE(GasFlueGasMaterial(700, 2.31722095, 125, composition).getHeatLoss() == Approx(0.7758857341));
	REQUIRE(GasFlueGasMaterial(700, 15.52234415, 125, composition).getHeatLoss() == Approx(0.7622712145));
	REQUIRE(GasFlueGasMaterial(700, 45.19750365, 125, composition).getHeatLoss() == Approx(0.7316834966));
	REQUIRE(GasFlueGasMaterial(700, 9.0, 125, composition).getHeatLoss() == Approx(0.76899));


	composition = GasCompositions("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
	REQUIRE(composition.calculateHeatingValue() == Approx(22030.67089880065));
	REQUIRE(composition.calculateSpecificGravity() == Approx(0.6571206283343215));

	composition = GasCompositions("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
	REQUIRE(composition.calculateHeatingValue() == Approx(19185.932389233436));
	REQUIRE(composition.calculateSpecificGravity() == Approx(0.44638781861292243));

	composition = GasCompositions("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
	REQUIRE(composition.calculateHeatingValue() == Approx(1080.6848266529887));
	REQUIRE(composition.calculateSpecificGravity() == Approx(1.0870540901007706));
}