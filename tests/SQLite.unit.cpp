#include "catch.hpp"
#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>

TEST_CASE( "SQLite - getSolidLoadChargeMaterials", "[sqlite]" ) {
    bool ok;
    auto sqlite = SQLite(":memory:", ok, true);

    {
        auto const outputs = sqlite.getSolidLoadChargeMaterials();
        CHECK( outputs.size() == 40 );
    }

    {
        auto const output = sqlite.getSolidLoadChargeMaterial(1);

        SolidLoadChargeMaterial expected;
        expected.setSubstance("Aluminum");
        expected.setSpecificHeatSolid(0.2479);
        expected.setLatentHeat(169);
        expected.setSpecificHeatLiquid(0.2601);
        expected.setMeltingPoint(1215);

        CHECK( expected == output );
    }
}

TEST_CASE( "SQLite - getGasLoadChargeMaterials", "[sqlite]" ) {
    bool ok;
    auto sqlite = SQLite(":memory:", ok, true);

    {
        auto const outputs = sqlite.getGasLoadChargeMaterials();
        CHECK( outputs.size() == 10 );
    }

    {
        auto const output = sqlite.getGasLoadChargeMaterial(1);

        GasLoadChargeMaterial expected;
        expected.setSubstance("Water vapor - near atm. pressure");
        expected.setSpecificHeatVapor(0.47);

        CHECK( expected == output );
    }
}

TEST_CASE( "SQLite - getLiquidLoadChargeMaterials", "[sqlite]" ) {
    bool ok;
    auto sqlite = SQLite(":memory:", ok, true);

    {
        auto const outputs = sqlite.getLiquidLoadChargeMaterials();
        CHECK( outputs.size() == 13 );
    }

    {
        auto const output = sqlite.getLiquidLoadChargeMaterial(1);

        LiquidLoadChargeMaterial expected;
        expected.setSubstance("Crude");
        expected.setSpecificHeatLiquid(0.6501);
        expected.setLatentHeat(105);
        expected.setSpecificHeatVapor(0.55);
        expected.setVaporizingTemperature(900);

        CHECK( expected == output );
    }
}
