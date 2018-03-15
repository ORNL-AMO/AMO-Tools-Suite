#include "catch.hpp"
#include <calculator/losses/LoadChargeMaterial.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>

TEST_CASE( "Calculate Total Heat for Charge Material - Solids", "[Total Heat][ChargeMaterial][Solids]") {
//    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.139957009792214, 117.15, 0.16, 2550, 20000.0, 1.0, 0.0, 70, 1500.0, 212.0, 0.0, 0.0, 100.0, 0).getTotalHeat() == Approx(3991143));
//    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.247910198232625, 169.0, 0.260090757105326, 1214.996, 10000.0, 2.0, 1.0, 70.0, 1500.0, 250.0, 10.0, 10.0, 100.0, 0).getTotalHeat() == Approx(3873223));
//    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0, 0.260090757105326, 1214.996, 10000.0, 2.0, 1.0, 70.0, 1500.0, 250.0, 10.0, 10.0, 100.0, 0).getTotalHeat() == Approx(3775223));
//    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0, 0.260090757105326, 1214.996, 10000.0, 2.0, 1.0, 70.0, 1500.0, 250.0, 10.0, 10.0, 0.0, 0).getTotalHeat() == Approx(3775223));
//    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC, 0.032959159, 28.5, 0.0339144972534403, 1945.004, 100.0, 10, 0.0, 70.0, 1500.0, 212.0, 0.0, 100.0, 200.0, 0).getTotalHeat() == Approx(23662));
//    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.032959159, 28.5, 0.0339144972534403, 1945.004, 100.0, 10, 0.0, 70.0, 1500.0, 212.0, 0.0, 100.0, 200.0, 0).getTotalHeat() == Approx(5662));

    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.150, 60.0, 0.481, 2900.0, 10000.0, 0.1, 0.0, 70.0, 2200.0, 500.0, 0.0, 1.0, 100, 0).getTotalHeat() == Approx(3204310));
    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0, 0.260090757105326, 1214.996, 10000.0, 0.0, 0.0, 100.0, 1300.0, 220.0, 100.0, 0.0, 100.0, 0).getTotalHeat() == Approx(4675276));
    CHECK(SolidLoadChargeMaterial(LoadChargeMaterial::ThermicReactionType::EXOTHERMIC, 0.247910198232625, 169.0, 0.260090757105326, 1214.996, 10000.0, 0.0, 0.0, 100.0, 1215.0, 220.0, 10.0, 0.0, 100.0, 0).getTotalHeat() == Approx(2933199));
}