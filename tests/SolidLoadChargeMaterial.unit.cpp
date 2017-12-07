#include "catch.hpp"
#include <calculator/losses/LoadChargeMaterial.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>

TEST_CASE( "Calculate Total Heat for Charge Material - Solids", "[Total Heat][ChargeMaterial][Solids]") {
    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.150, 60.0, 0.481, 2900.0, 10000.0, 0.1, 0.0, 70.0, 2200.0, 500.0, 0.0, 1.0, 100, 0).getTotalHeat() == Approx(3204310));
    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0, 0.260090757105326, 1214.996, 10000.0, 0.0, 0.0, 100.0, 1300.0, 220.0, 100.0, 0.0, 100.0, 0).getTotalHeat() == Approx(4675276));
    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0, 0.260090757105326, 1214.996, 10000.0, 0.0, 0.0, 100.0, 1215.0, 220.0, 10.0, 0.0, 100.0, 0).getTotalHeat() == Approx(2933199));
}