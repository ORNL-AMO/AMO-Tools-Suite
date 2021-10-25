#include "catch.hpp"
#include <calculator/losses/GasFlueGasMaterial.h>

TEST_CASE( "Calculate Heat Loss for flue gas Losses", "[Heat Loss]" ) {
	GasCompositions composition("unit test gas", 94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);

	CHECK(composition.calculateExcessAir(0.005) == Approx(0.0230303207));
	CHECK(composition.calculateExcessAir(0.03) == Approx(0.156085169));
	CHECK(composition.calculateExcessAir(0.07) == Approx(0.4563331236));

	CHECK(composition.calculateO2(0.0231722) == Approx(0.0049367284));
	CHECK(composition.calculateO2(0.1552234) == Approx(0.0294793974));
	CHECK(composition.calculateO2(0.451975) == Approx(0.0690024841));

	CHECK(composition.getProcessHeatProperties(700, 0.0231722095, 125, 125, 60, 0).availableHeat == Approx(0.78354503));
    CHECK(composition.getProcessHeatProperties(700, 0.1552234415, 125, 125, 60, 0).availableHeat == Approx(0.5241678247));
    CHECK(composition.getProcessHeatProperties(700, 0.09, 125, 125, 60, 0).availableHeat == Approx(0.7248426969));

	composition = GasCompositions("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
	CHECK(composition.getHeatingValue() == Approx(22030.67089880065));
	CHECK(composition.getHeatingValueVolume() == Approx(1032.445));
	CHECK(composition.getSpecificGravity() == Approx(0.6571206283343215));

	composition = GasCompositions("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
	CHECK(composition.getHeatingValue() == Approx(19185.932389233436));
	CHECK(composition.getHeatingValueVolume() == Approx(610.52));
	CHECK(composition.getSpecificGravity() == Approx(0.44638781861292243));

	composition = GasCompositions("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
	CHECK(composition.getHeatingValue() == Approx(1080.6848266529887));
	CHECK(composition.getHeatingValueVolume() == Approx(83.605));
	CHECK(composition.getSpecificGravity() == Approx(1.0870540901007706));

	composition = GasCompositions("", 94.1, 2.4, 1.41, 0.03, 0.49, 0.29, 0, 0.42, 0.71, 0, 0);
	CHECK(composition.getHeatingValue() == Approx(22630.345));
	CHECK(composition.getSpecificGravity() == Approx(0.631782959));
	CHECK(composition.getHeatingValueVolume() == Approx(1019.6648));

	composition = GasCompositions("", 93.9, 4.2, 1.0, 0, 0.3, 0.06, 0, 0, 0.5, 0, 0.01);
	CHECK(composition.getHeatingValue() == Approx(23030.1592092352));
	CHECK(composition.getSpecificGravity() == Approx(0.6298888036));
	CHECK(composition.getHeatingValueVolume() == Approx(1034.57));

	composition = GasCompositions("", 100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
	CHECK(composition.getHeatingValue() == Approx(23875));
	CHECK(composition.getSpecificGravity() == Approx(0.5943242442));
	CHECK(composition.getHeatingValueVolume() == Approx(1012));

	composition = GasCompositions("", 45, 45, 1, 1, 3, 2, 0, 1, 0, 0, 2);
	CHECK(composition.getHeatingValue() == Approx(21684.26));
	CHECK(composition.getSpecificGravity() == Approx(0.9060143746));
	CHECK(composition.getHeatingValueVolume() == Approx(1400.8));

	composition = GasCompositions("", 10, 55, 1, 10, 16, 2, 0, 1, 3, 0, 2);
	CHECK(composition.getHeatingValue() == Approx(20585.7766384286));
	CHECK(composition.getSpecificGravity() == Approx(1.0774007113));
	CHECK(composition.getHeatingValueVolume() == Approx(1581.14));
}