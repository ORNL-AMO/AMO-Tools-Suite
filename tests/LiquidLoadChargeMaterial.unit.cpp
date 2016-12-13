#include "catch.hpp"
#include <calculator/SolidLoadChargeMaterial.h>

TEST_CASE( "Calculate Total Heat for Charge Material - Liquids", "[Total Heat][ChargeMaterial][Liquids]") {
    CHECK( LiquidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.48, 240.0, 250.0, 0.25, 1000.0, 70.0, 320.0, 100.0, 25.0, 50.0, 0).getTotalHeat() == Approx(364100));
}