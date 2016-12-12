#include "catch.hpp"
#include <calculator/SolidLoadChargeMaterial.h>

TEST_CASE( "Calculate Total Heat for Charge Material - Solids", "[Total Heat][ChargeMaterial][Solids]") {
    CHECK( SolidLoadChargeMaterial(SolidLoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.150, 60.0, 0.481, 2900.0, 10000.0, 0.1, 0.0, 70.0, 2200.0, 500.0, 0.0, 1.0, 100, 0).getTotalHeat() == Approx(3204056));
}