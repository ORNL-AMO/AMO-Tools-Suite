#include "catch.hpp"
#include <calculator/losses/EnergyInputExhaustGasLosses.h>

TEST_CASE( "Calculate the Available Heat", "[Available Heat][EnergyInputExhaustGasLosses][Calculator]") {
	CHECK( AvailableHeat(65, 300, 550).getAvailableHeat() == Approx(82.727942398));
}

TEST_CASE( "Calculate the Heat Delivered to Furnace", "[HeatDelivered][EnergyInputExhaustGasLosses][Calculator]") {
	CHECK( EnergyInputExhaustGasLosses(5000000, 0, 82.73, 500).getHeatDelivered() == Approx(1212.3388042204 * 3412));
	CHECK( EnergyInputExhaustGasLosses(5000000, 0, 82.73, 500).getExhaustGasLosses() == Approx(863500));
}

