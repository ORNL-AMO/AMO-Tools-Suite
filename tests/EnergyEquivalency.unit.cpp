#include "catch.hpp"
#include <calculator/EnergyEquivalency.h>

TEST_CASE( "Calculate the Equivalent Electrical Heat Input", "[Electrical Heat Input][EnergyEquivalency][Calculator]") {
    CHECK( ElectricalEnergyEquivalency(6.59, 50, 87.3).getElectricalHeatInput() == Approx(3371.27));
}

TEST_CASE( "Calculate the Equivalent Fuel-Fired Heat Input", "[Fuel-Fired Heat Input][EnergyEquivalency][Calculator]") {
    CHECK( FuelFiredEnergyEquivalency(52.3, 58.9, 700).getFuelFiredHeatInput() == Approx(2.1207694397));
}

