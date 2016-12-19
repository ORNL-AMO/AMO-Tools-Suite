#include "catch.hpp"
#include <calculator/LoadChargeMaterial.h>
#include <calculator/GasLoadChargeMaterial.h>

TEST_CASE( "Calculate Total Heat for Charge Material - Gas", "[Total Heat][ChargeMaterial][Gas]") {
    CHECK( GasLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.24, 1000.0, 15.0, 80.0, 1150.0, 0.5, 100.0, 80.0, 5000.0).getTotalHeat() == Approx(383530.0));
}