#include "catch.hpp"
#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <calculator/losses/GasFlueGasMaterial.h>

TEST_CASE( "SQLite - getSolidLoadChargeMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

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
    auto sqlite = SQLite(":memory:", true);

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
    auto sqlite = SQLite(":memory:", true);

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

TEST_CASE( "SQLite - getGasChargeMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const outputs = sqlite.getGasFlueGasMaterials();
        CHECK( outputs.size() == 7 );
	    GasCompositions expected("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
	    CHECK( expected.getSubstance() == outputs[6].getSubstance() );
	    CHECK( expected.getGasByVol("C2H6") == outputs[6].getGasByVol("C2H6") );
	    CHECK( expected.getGasByVol("N2") == outputs[6].getGasByVol("N2") );
	    CHECK( expected.getGasByVol("H2") == outputs[6].getGasByVol("H2") );
	    CHECK( expected.getGasByVol("C3H8") == outputs[6].getGasByVol("C3H8") );
	    CHECK( expected.getGasByVol("C4H10_CnH2n") == outputs[6].getGasByVol("C4H10_CnH2n") );
	    CHECK( expected.getGasByVol("H2O") == outputs[6].getGasByVol("H2O") );
	    CHECK( expected.getGasByVol("CO") == outputs[6].getGasByVol("CO") );
	    CHECK( expected.getGasByVol("CO2") == outputs[6].getGasByVol("CO2") );
	    CHECK( expected.getGasByVol("SO2") == outputs[6].getGasByVol("SO2") );
	    CHECK( expected.getGasByVol("O2") == outputs[6].getGasByVol("O2") );
    }

    {
        auto const output = sqlite.getGasFlueGasMaterial(3);
        GasCompositions expected("Natural Gas Ohio", 93.33, 0.25, 3.4, 1.82, 0, 0, 0, 0.45, 0.22, 0, 0.35);
	    CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getGasByVol("C2H6") == output.getGasByVol("C2H6") );
        CHECK( expected.getGasByVol("N2") == output.getGasByVol("N2") );
        CHECK( expected.getGasByVol("H2") == output.getGasByVol("H2") );
        CHECK( expected.getGasByVol("C3H8") == output.getGasByVol("C3H8") );
        CHECK( expected.getGasByVol("C4H10_CnH2n") == output.getGasByVol("C4H10_CnH2n") );
        CHECK( expected.getGasByVol("H2O") == output.getGasByVol("H2O") );
        CHECK( expected.getGasByVol("CO") == output.getGasByVol("CO") );
        CHECK( expected.getGasByVol("CO2") == output.getGasByVol("CO2") );
        CHECK( expected.getGasByVol("SO2") == output.getGasByVol("SO2") );
        CHECK( expected.getGasByVol("O2") == output.getGasByVol("O2") );
    }
}
