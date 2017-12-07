#include "catch.hpp"
#include <calculator/losses/LoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>

TEST_CASE( "Calculate Total Heat for Charge Material - Liquids", "[Total Heat][ChargeMaterial][Liquids]") {
    CHECK( LiquidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.48, 240.0, 250.0, 0.25, 1000.0, 70.0, 320.0, 100.0, 25.0, 50.0, 0).getTotalHeat() == Approx(364100));
    CHECK( LiquidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.347026510628135, 129.992, 239.0, 0.40004776689754, 10000.0, 50.0, 135.0, 100.0, 0.0, 0.0, 0).getTotalHeat() == Approx(2687628));
    CHECK( LiquidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.347026510628135, 129.992, 239.0, 0.40004776689754, 10000.0, 50.0, 130.0, 10.0, 0.0, 0.0, 0).getTotalHeat() == Approx(516622));
}