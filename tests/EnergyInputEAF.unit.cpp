#include "catch.hpp"
#include <calculator/losses/EnergyInputEAF.h>

TEST_CASE( "Calculate the Total Chemical Energy Input", "[Total Chemical Energy Input][EnergyInputEAF][Furnace]") {
    CHECK(EnergyInputEAF(15, 56000, 900, 9000, 200, 12000, 0, 18000).getTotalChemicalEnergyInput() == Approx(47940000));

    CHECK( EnergyInputEAF(50, 6500, 3300, 9000, 500, 12000, 20, 18000).getTotalChemicalEnergyInput() == Approx(105700000));
}

TEST_CASE( "Calculate the Heat Delivered", "[Heat Delivered][EnergyInputEAF][Furnace]") {
    CHECK( EnergyInputEAF(50, 6500, 3300, 9000, 500, 12000, 20, 18000).getHeatDelivered() == Approx(334232000));

    CHECK(EnergyInputEAF(15, 56000, 900, 9000, 200, 12000, 0, 18000).getHeatDelivered() == Approx(218655831));
}
