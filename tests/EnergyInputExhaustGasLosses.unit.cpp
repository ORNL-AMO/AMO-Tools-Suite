#include "catch.hpp"
#include <calculator/losses/EnergyInputExhaustGasLosses.h>

TEST_CASE( "Calculate the Available Heat", "[Available Heat][EnergyInputExhaustGasLosses][Calculator]") {
//	CHECK( AvailableHeat(65, 300, 550).getAvailableHeat() == Approx(82.727942398));
	CHECK( EnergyInputExhaustGasLosses(0, 65, 300, 550).getAvailableHeat() == Approx(82.727942398));
}

TEST_CASE( "Calculate the Heat Delivered to Furnace", "[HeatDelivered][EnergyInputExhaustGasLosses][Calculator]") {
	CHECK( EnergyInputExhaustGasLosses(5000000, 65, 300, 550).getHeatDelivered() == Approx(4136397.1199));
	CHECK( EnergyInputExhaustGasLosses(5000000, 65, 300, 550).getExhaustGasLosses() == Approx(863602.8800999995));
}

