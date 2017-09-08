#include "catch.hpp"
#include <calculator/losses/EnergyInputEAF.h>

TEST_CASE( "Calculate the Total Chemical Energy Input", "[Total Chemical Energy Input][EnergyInputEAF][Furnace]") {
    CHECK( EnergyInputEAF(50, 3300, 9000, 500, 12000, 20, 18000).getTotalChemicalEnergyInput() == Approx(105700000));

    CHECK(EnergyInputEAF(15, 900, 9000, 200, 12000, 0, 18000).getTotalChemicalEnergyInput() == Approx(25500000.0));
}

TEST_CASE( "Calculate the Heat Delivered", "[Heat Delivered][EnergyInputEAF][Furnace]") {
    CHECK( EnergyInputEAF(50, 3300, 9000, 500, 12000, 20, 18000).getHeatDelivered() == Approx(167116000.0));

    CHECK(EnergyInputEAF(15, 900, 9000, 200, 12000, 0, 18000).getHeatDelivered() == Approx(86916000));
}
