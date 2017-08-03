#include "catch.hpp"
#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <calculator/losses/GasFlueGasMaterial.h>
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>
#include <calculator/losses/Atmosphere.h>
#include <calculator/losses/WallLosses.h>

TEST_CASE( "SQLite - getSolidLoadChargeMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const outputs = sqlite.getSolidLoadChargeMaterials();
        CHECK( outputs.size() == 40 );
    }

    {
        auto const output = sqlite.getSolidLoadChargeMaterialById(1);

        SolidLoadChargeMaterial expected;
        expected.setSubstance("Aluminum");
        expected.setSpecificHeatSolid(0.247910198232625);
        expected.setLatentHeat(169);
        expected.setSpecificHeatLiquid(0.2601);
        expected.setMeltingPoint(1215);
        expected.setID(1);

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
        auto const output = sqlite.getGasLoadChargeMaterialById(1);

        GasLoadChargeMaterial expected;
        expected.setSubstance("Water vapor - Near Atm. Pressure");
        expected.setSpecificHeatVapor(0.47);
	    expected.setID(1);

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
        auto const output = sqlite.getLiquidLoadChargeMaterialById(1);

        LiquidLoadChargeMaterial expected;
        expected.setSubstance("Crude");
        expected.setSpecificHeatLiquid(0.6501);
        expected.setLatentHeat(105);
        expected.setSpecificHeatVapor(0.55);
        expected.setVaporizingTemperature(900);
        expected.setID(1);

        CHECK( expected == output );
    }
}

TEST_CASE( "SQLite - getGasFlueGasMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

  /*  {
        auto const output = sqlite.getGasFlueGasMaterialById(3);
        GasCompositions expected("Natural Gas Ohio", 93.33, 0.25, 3.4, 1.82, 0, 0, 0, 0.45, 0.22, 0, 0.35);
        expected.setID(3);
        CHECK( expected.getID() == output.getID() );
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
    }*/

    //Typical Natural Gas - US
    {
        auto outputs = sqlite.getGasFlueGasMaterials();
        CHECK( outputs.size() == 3 );
        GasCompositions expected("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        expected.setID(1);
        CHECK( expected.getID() == outputs[0].getID() );
        CHECK( expected.getSubstance() == outputs[0].getSubstance() );
        CHECK( expected.getGasByVol("C2H6") == outputs[0].getGasByVol("C2H6") );
        CHECK( expected.getGasByVol("N2") == outputs[0].getGasByVol("N2") );
        CHECK( expected.getGasByVol("H2") == outputs[0].getGasByVol("H2") );
        CHECK( expected.getGasByVol("C3H8") == outputs[0].getGasByVol("C3H8") );
        CHECK( expected.getGasByVol("C4H10_CnH2n") == outputs[0].getGasByVol("C4H10_CnH2n") );
        CHECK( expected.getGasByVol("H2O") == outputs[0].getGasByVol("H2O") );
        CHECK( expected.getGasByVol("CO") == outputs[0].getGasByVol("CO") );
        CHECK( expected.getGasByVol("CO2") == outputs[0].getGasByVol("CO2") );
        CHECK( expected.getGasByVol("SO2") == outputs[0].getGasByVol("SO2") );
        CHECK( expected.getGasByVol("O2") == outputs[0].getGasByVol("O2") );
        CHECK( outputs[0].calculateHeatingValue() == Approx(22030.67089880065) );
        CHECK( outputs[0].calculateSpecificGravity() == Approx(0.6571206283343215));
    }

    {
        auto output = sqlite.getGasFlueGasMaterialById(1);
        GasCompositions expected("Typical Natural Gas - US", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        expected.setID(1);
        CHECK( expected.getID() == output.getID() );
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
        CHECK( output.calculateHeatingValue() == Approx(22030.67089880065) );
        CHECK( output.calculateSpecificGravity() == Approx(0.6571206283343215) );
    }

    //Coke Oven Gas
    {
        auto outputs = sqlite.getGasFlueGasMaterials();
        CHECK( outputs.size() == 3 );
        GasCompositions expected("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
        expected.setID(2);
        CHECK( expected.getID() == outputs[1].getID() );
        CHECK( expected.getSubstance() == outputs[1].getSubstance() );
        CHECK( expected.getGasByVol("C2H6") == outputs[1].getGasByVol("C2H6") );
        CHECK( expected.getGasByVol("N2") == outputs[1].getGasByVol("N2") );
        CHECK( expected.getGasByVol("H2") == outputs[1].getGasByVol("H2") );
        CHECK( expected.getGasByVol("C3H8") == outputs[1].getGasByVol("C3H8") );
        CHECK( expected.getGasByVol("C4H10_CnH2n") == outputs[1].getGasByVol("C4H10_CnH2n") );
        CHECK( expected.getGasByVol("H2O") == outputs[1].getGasByVol("H2O") );
        CHECK( expected.getGasByVol("CO") == outputs[1].getGasByVol("CO") );
        CHECK( expected.getGasByVol("CO2") == outputs[1].getGasByVol("CO2") );
        CHECK( expected.getGasByVol("SO2") == outputs[1].getGasByVol("SO2") );
        CHECK( expected.getGasByVol("O2") == outputs[1].getGasByVol("O2") );
        CHECK( outputs[1].calculateHeatingValue() == Approx(19185.932389233436) );
        CHECK( outputs[1].calculateSpecificGravity() == Approx(0.44638781861292243) );
    }

    {
        auto output = sqlite.getGasFlueGasMaterialById(2);
        GasCompositions expected("Coke Oven Gas", 33.9, 5.2, 3.7, 47.9, 0, 0, 0, 6.1, 2.6, 0, 0.6);
        expected.setID(2);
        CHECK( expected.getID() == output.getID() );
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
        CHECK( output.calculateHeatingValue() == Approx(19185.932389233436) );
        CHECK( output.calculateSpecificGravity() == Approx(0.44638781861292243) );
    }


    //Blast Furnace
    {
        auto outputs = sqlite.getGasFlueGasMaterials();
        CHECK( outputs.size() == 3 );
        GasCompositions expected("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
        expected.setID(3);
        CHECK( expected.getID() == outputs[2].getID() );
        CHECK( expected.getSubstance() == outputs[2].getSubstance() );
        CHECK( expected.getGasByVol("C2H6") == outputs[2].getGasByVol("C2H6") );
        CHECK( expected.getGasByVol("N2") == outputs[2].getGasByVol("N2") );
        CHECK( expected.getGasByVol("H2") == outputs[2].getGasByVol("H2") );
        CHECK( expected.getGasByVol("C3H8") == outputs[2].getGasByVol("C3H8") );
        CHECK( expected.getGasByVol("C4H10_CnH2n") == outputs[2].getGasByVol("C4H10_CnH2n") );
        CHECK( expected.getGasByVol("H2O") == outputs[2].getGasByVol("H2O") );
        CHECK( expected.getGasByVol("CO") == outputs[2].getGasByVol("CO") );
        CHECK( expected.getGasByVol("CO2") == outputs[2].getGasByVol("CO2") );
        CHECK( expected.getGasByVol("SO2") == outputs[2].getGasByVol("SO2") );
        CHECK( expected.getGasByVol("O2") == outputs[2].getGasByVol("O2") );
        CHECK( outputs[2].calculateHeatingValue() == 1080.6848266529887 );
        CHECK( outputs[2].calculateSpecificGravity() == 1.0870540901007706 );
    }

    {
        auto output = sqlite.getGasFlueGasMaterialById(3);
        GasCompositions expected("Blast Furnace Gas", 0.1, 0, 56.4, 2.4, 0, 0, 3.4, 23.3, 14.4, 0, 0);
        expected.setID(3);
        CHECK( expected.getID() == output.getID() );
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
        CHECK( output.calculateHeatingValue() == 1080.6848266529887 );
        CHECK( output.calculateSpecificGravity() == 1.0870540901007706 );
    }


}

TEST_CASE( "SQLite - getSolidLiquidFlueGasMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

   /* {
        auto const outputs = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( outputs.size() == 19 );
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 63.3, 4.5, 1.0, 1.1, 19.0, 0, 11.1);
	    expected.setSubstance("Lignite, North Dakota");
	    expected.setID(7);
        CHECK( expected.getID() == outputs[6].getID() );
        CHECK( expected.getSubstance() == outputs[6].getSubstance() );
        CHECK( expected.getCarbon() == outputs[6].getCarbon() );
        CHECK( expected.getHydrogen() == outputs[6].getHydrogen() );
        CHECK( expected.getSulphur() == outputs[6].getSulphur() );
        CHECK( expected.getInertAsh() == outputs[6].getInertAsh() );
        CHECK( expected.getO2() == outputs[6].getO2() );
        CHECK( expected.getMoisture() == outputs[6].getMoisture() );
        CHECK( expected.getNitrogen() == outputs[6].getNitrogen() );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterialById(1);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 83.7, 1.9, 0.9, 0.7, 2.3, 0, 10.5);
        expected.setID(1);
        expected.setSubstance("Anthracite");
        CHECK( expected.getID() == output.getID() );
        CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getCarbon() == output.getCarbon() );
        CHECK( expected.getHydrogen() == output.getHydrogen() );
        CHECK( expected.getSulphur() == output.getSulphur() );
        CHECK( expected.getInertAsh() == output.getInertAsh() );
        CHECK( expected.getO2() == output.getO2() );
        CHECK( expected.getMoisture() == output.getMoisture() );
        CHECK( expected.getNitrogen() == output.getNitrogen() );
    }*/

    //Typical Bituminous Coal - US
   {
        auto const outputs = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( outputs.size() == 6 );
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5);
        expected.setSubstance("Typical Bituminous Coal - US");
        expected.setID(1);
        CHECK( expected.getID() == outputs[0].getID() );
        CHECK( expected.getSubstance() == outputs[0].getSubstance() );
        CHECK( expected.getCarbon() == outputs[0].getCarbon() );
        CHECK( expected.getHydrogen() == outputs[0].getHydrogen() );
        CHECK( expected.getSulphur() == outputs[0].getSulphur() );
        CHECK( expected.getInertAsh() == outputs[0].getInertAsh() );
        CHECK( expected.getO2() == outputs[0].getO2() );
        CHECK( expected.getMoisture() == outputs[0].getMoisture() );
        CHECK( expected.getNitrogen() == outputs[0].getNitrogen() );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterialById(1);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5);
        expected.setID(1);
        expected.setSubstance("Typical Bituminous Coal - US");
        CHECK( expected.getID() == output.getID() );
        CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getCarbon() == output.getCarbon() );
        CHECK( expected.getHydrogen() == output.getHydrogen() );
        CHECK( expected.getSulphur() == output.getSulphur() );
        CHECK( expected.getInertAsh() == output.getInertAsh() );
        CHECK( expected.getO2() == output.getO2() );
        CHECK( expected.getMoisture() == output.getMoisture() );
        CHECK( expected.getNitrogen() == output.getNitrogen() );
    }


    //Typical Anthracite - US
    {
        auto const outputs = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( outputs.size() == 6 );
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8);
        expected.setSubstance("Typical Anthracite - US");
        expected.setID(2);
        CHECK( expected.getID() == outputs[1].getID() );
        CHECK( expected.getSubstance() == outputs[1].getSubstance() );
        CHECK( expected.getCarbon() == outputs[1].getCarbon() );
        CHECK( expected.getHydrogen() == outputs[1].getHydrogen() );
        CHECK( expected.getSulphur() == outputs[1].getSulphur() );
        CHECK( expected.getInertAsh() == outputs[1].getInertAsh() );
        CHECK( expected.getO2() == outputs[1].getO2() );
        CHECK( expected.getMoisture() == outputs[1].getMoisture() );
        CHECK( expected.getNitrogen() == outputs[1].getNitrogen() );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterialById(2);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 77.7, 1.8, 0.7, 9.8, 2.1, 7.1, 0.8);
        expected.setID(2);
        expected.setSubstance("Typical Anthracite - US");
        CHECK( expected.getID() == output.getID() );
        CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getCarbon() == output.getCarbon() );
        CHECK( expected.getHydrogen() == output.getHydrogen() );
        CHECK( expected.getSulphur() == output.getSulphur() );
        CHECK( expected.getInertAsh() == output.getInertAsh() );
        CHECK( expected.getO2() == output.getO2() );
        CHECK( expected.getMoisture() == output.getMoisture() );
        CHECK( expected.getNitrogen() == output.getNitrogen() );
    }

    //Typical Lignite - US
    {
        auto const outputs = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( outputs.size() == 6 );
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8);
        expected.setSubstance("Typical Lignite - US");
        expected.setID(3);
        CHECK( expected.getID() == outputs[2].getID() );
        CHECK( expected.getSubstance() == outputs[2].getSubstance() );
        CHECK( expected.getCarbon() == outputs[2].getCarbon() );
        CHECK( expected.getHydrogen() == outputs[2].getHydrogen() );
        CHECK( expected.getSulphur() == outputs[2].getSulphur() );
        CHECK( expected.getInertAsh() == outputs[2].getInertAsh() );
        CHECK( expected.getO2() == outputs[2].getO2() );
        CHECK( expected.getMoisture() == outputs[2].getMoisture() );
        CHECK( expected.getNitrogen() == outputs[2].getNitrogen() );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterialById(3);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 47.5, 3.4, 0.8, 8.3, 14.2, 25, 0.8);
        expected.setID(3);
        expected.setSubstance("Typical Lignite - US");
        CHECK( expected.getID() == output.getID() );
        CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getCarbon() == output.getCarbon() );
        CHECK( expected.getHydrogen() == output.getHydrogen() );
        CHECK( expected.getSulphur() == output.getSulphur() );
        CHECK( expected.getInertAsh() == output.getInertAsh() );
        CHECK( expected.getO2() == output.getO2() );
        CHECK( expected.getMoisture() == output.getMoisture() );
        CHECK( expected.getNitrogen() == output.getNitrogen() );
    }

    //Fuel Oil #2
    {
        auto const outputs = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( outputs.size() == 6 );
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 86.6, 12.8, 0.5, 0, 0, 0, 0.1);
        expected.setSubstance("Fuel Oil #2");
        expected.setID(4);
        CHECK( expected.getID() == outputs[3].getID() );
        CHECK( expected.getSubstance() == outputs[3].getSubstance() );
        CHECK( expected.getCarbon() == outputs[3].getCarbon() );
        CHECK( expected.getHydrogen() == outputs[3].getHydrogen() );
        CHECK( expected.getSulphur() == outputs[3].getSulphur() );
        CHECK( expected.getInertAsh() == outputs[3].getInertAsh() );
        CHECK( expected.getO2() == outputs[3].getO2() );
        CHECK( expected.getMoisture() == outputs[3].getMoisture() );
        CHECK( expected.getNitrogen() == outputs[3].getNitrogen() );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterialById(4);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 86.6, 12.8, 0.5, 0, 0, 0, 0.1);
        expected.setID(4);
        expected.setSubstance("Fuel Oil #2");
        CHECK( expected.getID() == output.getID() );
        CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getCarbon() == output.getCarbon() );
        CHECK( expected.getHydrogen() == output.getHydrogen() );
        CHECK( expected.getSulphur() == output.getSulphur() );
        CHECK( expected.getInertAsh() == output.getInertAsh() );
        CHECK( expected.getO2() == output.getO2() );
        CHECK( expected.getMoisture() == output.getMoisture() );
        CHECK( expected.getNitrogen() == output.getNitrogen() );
    }

    //Fuel Oil #6
    {
        auto const outputs = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( outputs.size() == 6 );
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 87.1, 10.6, 2.1, 0.2, 0, 0, 0);
        expected.setSubstance("Fuel Oil #6");
        expected.setID(5);
        CHECK( expected.getID() == outputs[4].getID() );
        CHECK( expected.getSubstance() == outputs[4].getSubstance() );
        CHECK( expected.getCarbon() == outputs[4].getCarbon() );
        CHECK( expected.getHydrogen() == outputs[4].getHydrogen() );
        CHECK( expected.getSulphur() == outputs[4].getSulphur() );
        CHECK( expected.getInertAsh() == outputs[4].getInertAsh() );
        CHECK( expected.getO2() == outputs[4].getO2() );
        CHECK( expected.getMoisture() == outputs[4].getMoisture() );
        CHECK( expected.getNitrogen() == outputs[4].getNitrogen() );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterialById(5);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 87.1, 10.6, 2.1, 0.2, 0, 0, 0);
        expected.setID(5);
        expected.setSubstance("Fuel Oil #6");
        CHECK( expected.getID() == output.getID() );
        CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getCarbon() == output.getCarbon() );
        CHECK( expected.getHydrogen() == output.getHydrogen() );
        CHECK( expected.getSulphur() == output.getSulphur() );
        CHECK( expected.getInertAsh() == output.getInertAsh() );
        CHECK( expected.getO2() == output.getO2() );
        CHECK( expected.getMoisture() == output.getMoisture() );
        CHECK( expected.getNitrogen() == output.getNitrogen() );
    }

    //Typical Wood
    {
        auto const outputs = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( outputs.size() == 6 );
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2);
        expected.setSubstance("Typical Wood");
        expected.setID(6);
        CHECK( expected.getID() == outputs[5].getID() );
        CHECK( expected.getSubstance() == outputs[5].getSubstance() );
        CHECK( expected.getCarbon() == outputs[5].getCarbon() );
        CHECK( expected.getHydrogen() == outputs[5].getHydrogen() );
        CHECK( expected.getSulphur() == outputs[5].getSulphur() );
        CHECK( expected.getInertAsh() == outputs[5].getInertAsh() );
        CHECK( expected.getO2() == outputs[5].getO2() );
        CHECK( expected.getMoisture() == outputs[5].getMoisture() );
        CHECK( expected.getNitrogen() == outputs[5].getNitrogen() );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterialById(6);
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 51.7, 5.4, 0.1, 3.1, 39.5, 0, 0.2);
        expected.setID(6);
        expected.setSubstance("Typical Wood");
        CHECK( expected.getID() == output.getID() );
        CHECK( expected.getSubstance() == output.getSubstance() );
        CHECK( expected.getCarbon() == output.getCarbon() );
        CHECK( expected.getHydrogen() == output.getHydrogen() );
        CHECK( expected.getSulphur() == output.getSulphur() );
        CHECK( expected.getInertAsh() == output.getInertAsh() );
        CHECK( expected.getO2() == output.getO2() );
        CHECK( expected.getMoisture() == output.getMoisture() );
        CHECK( expected.getNitrogen() == output.getNitrogen() );
    }
}

TEST_CASE( "SQLite - getAtmosphereSpecificHeat", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const outputs = sqlite.getAtmosphereSpecificHeat();
        CHECK( outputs.size() == 6 );
    }

    {
        auto const output = sqlite.getAtmosphereSpecificHeatById(1);

        Atmosphere expected;
        expected.setSubstance("Nitrogen");
        expected.setSpecificHeat(0.0185);
        expected.setID(1);

        CHECK( expected == output );
    }
}

TEST_CASE( "SQLite - getWallLossesSurface", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const outputs = sqlite.getWallLossesSurface();
        CHECK( outputs.size() == 7 );
    }

    {
        auto const output = sqlite.getWallLossesSurfaceById(1);

        WallLosses expected;
        expected.setSurface("Horizontal cylinders");
        expected.setConditionFactor(1.016);
        expected.setID(1);

        CHECK( expected == output );
    }
}
