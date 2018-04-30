#include "catch.hpp"
#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <calculator/losses/GasFlueGasMaterial.h>
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>
#include <calculator/losses/Atmosphere.h>
#include <calculator/losses/WallLosses.h>
#include <calculator/motor/MotorData.h>
#include <fstream>

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

TEST_CASE( "SQLite - update all materials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

	{
		SolidLoadChargeMaterial slcm;
		slcm.setSubstance("custom");
		slcm.setSpecificHeatSolid(0.25);
		slcm.setLatentHeat(100);
		slcm.setSpecificHeatLiquid(0.50);
		slcm.setMeltingPoint(1200);
		sqlite.insertSolidLoadChargeMaterials(slcm);

		slcm = sqlite.getCustomSolidLoadChargeMaterials()[0];
		slcm.setSubstance("updatedCustom");
		slcm.setSpecificHeatSolid(0.5);
		slcm.setLatentHeat(115);
		slcm.setSpecificHeatLiquid(0.20);
		slcm.setMeltingPoint(900);

		sqlite.updateSolidLoadChargeMaterial(slcm);

		slcm = sqlite.getCustomSolidLoadChargeMaterials()[0];

		CHECK(slcm.getSubstance() == "updatedCustom");
		CHECK(Approx(slcm.getSpecificHeatSolid()) == 0.5);
		CHECK(Approx(slcm.getLatentHeat()) == 115);
		CHECK(Approx(slcm.getSpecificHeatLiquid()) == 0.20);
		CHECK(Approx(slcm.getMeltingPoint()) == 900);
	}

    {
        GasLoadChargeMaterial glcm;
        glcm.setSubstance("custom");
        glcm.setSpecificHeatVapor(0.05);
        sqlite.insertGasLoadChargeMaterials(glcm);

        glcm.setSubstance("custom2");
        sqlite.insertGasLoadChargeMaterials(glcm);

        auto getCustom1 = sqlite.getCustomGasLoadChargeMaterials().at(0);
        auto getCustom2 = sqlite.getCustomGasLoadChargeMaterials().at(1);

        getCustom1.setSubstance("updatedCustom");
        getCustom1.setSpecificHeatVapor(0.1);

        getCustom2.setSubstance("updatedCustom2");
        getCustom2.setSpecificHeatVapor(1.5);

	    sqlite.updateGasLoadChargeMaterial(getCustom1);
        sqlite.updateGasLoadChargeMaterial(getCustom2);

        getCustom1 = sqlite.getCustomGasLoadChargeMaterials().at(0);
        getCustom2 = sqlite.getCustomGasLoadChargeMaterials().at(1);

        CHECK(getCustom1.getSubstance() == "updatedCustom");
        CHECK(getCustom1.getSpecificHeatVapor() == 0.1);
        CHECK(getCustom2.getSubstance() == "updatedCustom2");
        CHECK(getCustom2.getSpecificHeatVapor() == 1.5);
    }

    {
        LiquidLoadChargeMaterial llcm;
        llcm.setSubstance("custom");
        llcm.setSpecificHeatVapor(0.01);
        llcm.setSpecificHeatLiquid(0.02);
        llcm.setLatentHeat(0.03);
        llcm.setVaporizingTemperature(0.05);
        sqlite.insertLiquidLoadChargeMaterials(llcm);

        llcm.setSubstance("custom2");
        llcm.setSpecificHeatVapor(0.06);
        llcm.setSpecificHeatLiquid(0.07);
        llcm.setLatentHeat(0.08);
        llcm.setVaporizingTemperature(0.1);
        sqlite.insertLiquidLoadChargeMaterials(llcm);

        auto getCustom1 = sqlite.getCustomLiquidLoadChargeMaterials().at(0);
        auto getCustom2 = sqlite.getCustomLiquidLoadChargeMaterials().at(1);

        getCustom1.setSubstance("updatedCustom");
        getCustom1.setSpecificHeatVapor(0.1);
        getCustom1.setSpecificHeatLiquid(0.2);
        getCustom1.setLatentHeat(0.3);
        getCustom1.setVaporizingTemperature(0.5);

        getCustom2.setSubstance("updatedCustom2");
        getCustom2.setSpecificHeatVapor(0.6);
        getCustom2.setSpecificHeatLiquid(0.7);
        getCustom2.setLatentHeat(0.8);
        getCustom2.setVaporizingTemperature(1.0);

        sqlite.updateLiquidLoadChargeMaterial(getCustom1);
        sqlite.updateLiquidLoadChargeMaterial(getCustom2);

        getCustom1 = sqlite.getCustomLiquidLoadChargeMaterials().at(0);
        getCustom2 = sqlite.getCustomLiquidLoadChargeMaterials().at(1);

        CHECK(getCustom1.getSubstance() == "updatedCustom");
        CHECK(Approx(getCustom1.getSpecificHeatVapor()) == 0.1);
        CHECK(Approx(getCustom1.getSpecificHeatLiquid()) == 0.2);
        CHECK(Approx(getCustom1.getLatentHeat()) == 0.3);
        CHECK(Approx(getCustom1.getVaporizingTemperature()) == 0.5);

        CHECK(getCustom2.getSubstance() == "updatedCustom2");
        CHECK(Approx(getCustom2.getSpecificHeatVapor()) == 0.6);
        CHECK(Approx(getCustom2.getSpecificHeatLiquid()) == 0.7);
        CHECK(Approx(getCustom2.getLatentHeat()) == 0.8);
        CHECK(Approx(getCustom2.getVaporizingTemperature()) == 1.0);
    }
}

TEST_CASE( "SQLite - deleteMaterials", "[sqlite]" ) {
	auto sqlite = SQLite(":memory:", true);

	{
		auto const output = sqlite.getSolidLoadChargeMaterials();

		SolidLoadChargeMaterial mat;
		mat.setSubstance("custom");
        SolidLoadChargeMaterial mat2;
        mat2.setSubstance("custom2");

        sqlite.insertSolidLoadChargeMaterials(mat);
        sqlite.insertSolidLoadChargeMaterials(mat2);

		auto getMat2 = sqlite.getCustomSolidLoadChargeMaterials().back();
        auto getMat1 = sqlite.getCustomSolidLoadChargeMaterials().at(0);
        sqlite.deleteSolidLoadChargeMaterial(getMat2.getID());
        sqlite.deleteSolidLoadChargeMaterial(getMat1.getID());
        auto const output2 = sqlite.getSolidLoadChargeMaterials();
        CHECK( output2.back().getSubstance() == output.back().getSubstance() );
	}

    {
        auto const output = sqlite.getLiquidLoadChargeMaterials();
        LiquidLoadChargeMaterial mat;
        mat.setSubstance("custom");
        LiquidLoadChargeMaterial mat2;
        mat2.setSubstance("custom2");

        sqlite.insertLiquidLoadChargeMaterials(mat);
        sqlite.insertLiquidLoadChargeMaterials(mat2);

        auto getMat2 = sqlite.getCustomLiquidLoadChargeMaterials().back();
        auto getMat1 = sqlite.getCustomLiquidLoadChargeMaterials().at(0);
        sqlite.deleteLiquidLoadChargeMaterial(getMat2.getID());
        sqlite.deleteLiquidLoadChargeMaterial(getMat1.getID());
        auto const output2 = sqlite.getLiquidLoadChargeMaterials();
        CHECK( output2.back().getSubstance() == output.back().getSubstance() );
    }

    {
        auto const originalMats = sqlite.getGasLoadChargeMaterials();

        GasLoadChargeMaterial glcm;
        glcm.setSubstance("custom");
        sqlite.insertGasLoadChargeMaterials(glcm);

        glcm.setSubstance("custom2");
        sqlite.insertGasLoadChargeMaterials(glcm);

        auto const custom = sqlite.getCustomGasLoadChargeMaterials();
        sqlite.deleteGasLoadChargeMaterial(custom.at(1).getID());
        sqlite.deleteGasLoadChargeMaterial(custom.at(0).getID());

        auto const afterDeleteMats = sqlite.getGasLoadChargeMaterials();
        CHECK( afterDeleteMats.back().getSubstance() == originalMats.back().getSubstance() );
    }

    {
        auto const output = sqlite.getGasFlueGasMaterials();
        auto const last = output[output.size() - 1].getSubstance();
//        GasCompositions gc("custom", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        GasCompositions gc("custom", 12, 13, 14, 15, 16, 14, 12, 12, 12, 12, 11);
        gc.setID(output.size());

        sqlite.insertGasFlueGasMaterial(gc);
        sqlite.deleteGasFlueGasMaterial(gc.getSubstance());
        auto const output2 = sqlite.getGasFlueGasMaterials();
        CHECK( output2[output2.size() - 1].getSubstance() == last );
    }

    {
        auto const output = sqlite.getSolidLiquidFlueGasMaterials();
        auto const last = output[output.size() - 1].getSubstance();
        SolidLiquidFlueGasMaterial slfgm(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        slfgm.setID(output.size());
        slfgm.setSubstance("custom");

        sqlite.insertSolidLiquidFlueGasMaterial(slfgm);
        sqlite.deleteSolidLiquidFlueGasMaterial(slfgm.getSubstance());
        auto const output2 = sqlite.getSolidLiquidFlueGasMaterials();
        CHECK( output2[output2.size() - 1].getSubstance() == last );
    }

    {
        auto const output = sqlite.getAtmosphereSpecificHeat();
        auto const last = output[output.size() - 1].getSubstance();
	    Atmosphere a;
        a.setID(output.size());
        a.setSubstance("custom");

        sqlite.insertAtmosphereSpecificHeat(a);
        sqlite.deleteAtmosphereSpecificHeat(a.getSubstance());
        auto const output2 = sqlite.getAtmosphereSpecificHeat();
        CHECK( output2[output2.size() - 1].getSubstance() == last );
    }

    {
        auto const output = sqlite.getWallLossesSurface();
        auto const last = output[output.size() - 1].getSurface();
	    WallLosses wall;
        wall.setID(output.size());
        wall.setSurface("custom");

        sqlite.insertWallLossesSurface(wall);
        sqlite.deleteWallLossesSurface(wall.getSurface());
        auto const output2 = sqlite.getWallLossesSurface();
        CHECK( output2[output2.size() - 1].getSurface() == last );
    }
}

//// commented because it writes to HDD
//TEST_CASE( "SQLite - test db init", "[sqlite]" ) {
//    {
//        std::ifstream ifs("amo_tools_suite.db");
//        auto const isOpen = ifs.is_open();
//        ifs.close();
//        auto sqlite = SQLite("amo_tools_suite.db", ! isOpen);
//
//        auto res = sqlite.getSolidLoadChargeMaterials();
//        auto const resSize = res.size() + 1;
//        SolidLoadChargeMaterial expected;
//        expected.setSubstance("custom" + std::to_string(resSize));
//        expected.setSpecificHeatSolid(0.25);
//        expected.setLatentHeat(100);
//        expected.setSpecificHeatLiquid(0.50);
//        expected.setMeltingPoint(1200);
//        expected.setID(resSize);
//        sqlite.insertSolidLoadChargeMaterials(expected);
//
//        res = sqlite.getSolidLoadChargeMaterials();
//	    auto const last = res[resSize - 1];
//        CHECK( expected.getSubstance() == last.getSubstance() );
//        CHECK( expected.getID() == last.getID() );
//        CHECK( expected.getSpecificHeatLiquid() == last.getSpecificHeatLiquid() );
//        CHECK( expected.getSpecificHeatSolid() == last.getSpecificHeatSolid() );
//        CHECK( expected.getMeltingPoint() == last.getMeltingPoint() );
//        CHECK( expected.getLatentHeat() == last.getLatentHeat() );
//    }
//
//    {
//        std::ifstream ifs("amo_tools_suite.db");
//        auto const isOpen = ! ifs.is_open();
//        ifs.close();
//        auto sqlite = SQLite("amo_tools_suite.db", isOpen);
//
//        auto res = sqlite.getSolidLoadChargeMaterials();
//        auto const resSize = res.size() + 1;
//
//        SolidLoadChargeMaterial expected;
//        expected.setSubstance("custom" + std::to_string(resSize));
//        expected.setSpecificHeatSolid(0.25);
//        expected.setLatentHeat(100);
//        expected.setSpecificHeatLiquid(0.50);
//        expected.setMeltingPoint(1200);
//        expected.setID(resSize);
//        sqlite.insertSolidLoadChargeMaterials(expected);
//
//        res = sqlite.getSolidLoadChargeMaterials();
//        auto const last = res[resSize - 1];
//        CHECK( expected.getSubstance() == last.getSubstance() );
//        CHECK( expected.getID() == last.getID() );
//        CHECK( expected.getSpecificHeatLiquid() == last.getSpecificHeatLiquid() );
//        CHECK( expected.getSpecificHeatSolid() == last.getSpecificHeatSolid() );
//        CHECK( expected.getMeltingPoint() == last.getMeltingPoint() );
//        CHECK( expected.getLatentHeat() == last.getLatentHeat() );
//    }
//}

TEST_CASE( "SQLite - TestSolidLoadChargeMaterialsMigrations", "[sqlite]" ) {
    auto sourceSqlite = SQLite(":memory:", true);
    auto const mats = sourceSqlite.getSolidLoadChargeMaterials();

    {
        SolidLoadChargeMaterial expected;
        expected.setSubstance("custom");
        expected.setSpecificHeatSolid(0.25);
        expected.setLatentHeat(100);
        expected.setSpecificHeatLiquid(0.50);
        expected.setMeltingPoint(1200);
        expected.setID(mats.size() + 1);
        sourceSqlite.insertSolidLoadChargeMaterials(expected);

	    auto const output = sourceSqlite.getCustomSolidLoadChargeMaterials();
	    CHECK( output[0] == expected );
    }

    {
        SolidLoadChargeMaterial expected;
        expected.setSubstance("custom2");
        expected.setSpecificHeatSolid(0.55);
        expected.setLatentHeat(200);
        expected.setSpecificHeatLiquid(0.70);
        expected.setMeltingPoint(1000);
        expected.setID(mats.size() + 2);
        sourceSqlite.insertSolidLoadChargeMaterials(expected);

        auto const output = sourceSqlite.getCustomSolidLoadChargeMaterials();
        CHECK( output[1] == expected );
    }

    auto destinationSqlite = SQLite(":memory:", true);
    auto const customData = sourceSqlite.getCustomSolidLoadChargeMaterials();
    for (auto const material : customData) {
        destinationSqlite.insertSolidLoadChargeMaterials(material);
    }

    {
        SolidLoadChargeMaterial expected;
        expected.setSubstance("custom2");
        expected.setSpecificHeatSolid(0.55);
        expected.setLatentHeat(200);
        expected.setSpecificHeatLiquid(0.70);
        expected.setMeltingPoint(1000);
        expected.setID(mats.size() + 2);

        auto const output = destinationSqlite.getCustomSolidLoadChargeMaterials();
        CHECK( output[1] == expected );
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

TEST_CASE( "SQLite - CustomGasLoadChargeMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const size = sqlite.getGasLoadChargeMaterials().size();
        GasLoadChargeMaterial glcm;
        glcm.setSubstance("custom");
        glcm.setID(size);
        sqlite.insertGasLoadChargeMaterials(glcm);
        auto const outputs = sqlite.getGasLoadChargeMaterials();
        CHECK(outputs[size].getSubstance() == glcm.getSubstance());
        CHECK( outputs.size() == size + 1 );
    }

    {
        auto const size = sqlite.getGasLoadChargeMaterials().size();
        GasLoadChargeMaterial glcm;
        glcm.setSubstance("custom2");
        glcm.setID(size);
        sqlite.insertGasLoadChargeMaterials(glcm);
        auto const outputs = sqlite.getCustomGasLoadChargeMaterials();
        CHECK( outputs[1].getSubstance() == "custom2" );
        CHECK( outputs.size() == 2 );
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

TEST_CASE( "SQLite - customLiquidLoadChargeMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const size = sqlite.getLiquidLoadChargeMaterials().size();
        LiquidLoadChargeMaterial llcm;
        llcm.setSubstance("custom");
        llcm.setID(size);
        sqlite.insertLiquidLoadChargeMaterials(llcm);

        auto const output = sqlite.getLiquidLoadChargeMaterials();
        CHECK( output.size() == size + 1);
        CHECK( output[size].getSubstance() == llcm.getSubstance());
    }

    {
        auto const size = sqlite.getLiquidLoadChargeMaterials().size();
        LiquidLoadChargeMaterial llcm;
        llcm.setSubstance("custom2");
        llcm.setID(size);
        sqlite.insertLiquidLoadChargeMaterials(llcm);

	    auto const check = sqlite.getLiquidLoadChargeMaterials();
        auto const output = sqlite.getCustomLiquidLoadChargeMaterials();
        CHECK( output.size() == 2);
        CHECK( output[1].getSubstance() == llcm.getSubstance());
    }
}

TEST_CASE( "SQLite - getGasFlueGasMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

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
        CHECK( outputs[0].getHeatingValue() == Approx(22030.67089880065) );
        CHECK( outputs[0].getHeatingValueVolume() == Approx(1032.445) );
        CHECK( outputs[0].getSpecificGravity() == Approx(0.6571206283343215));
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
        CHECK( output.getHeatingValue() == Approx(22030.67089880065) );
        CHECK( output.getHeatingValueVolume() == Approx(1032.445) );
        CHECK( output.getSpecificGravity() == Approx(0.6571206283343215) );
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
        CHECK( outputs[1].getHeatingValue() == Approx(19185.932389233436) );
        CHECK( outputs[1].getHeatingValueVolume() == Approx(610.52) );
        CHECK( outputs[1].getSpecificGravity() == Approx(0.44638781861292243) );
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
        CHECK( output.getHeatingValue() == Approx(19185.932389233436) );
        CHECK( output.getHeatingValueVolume() == Approx(610.52) );
        CHECK( output.getSpecificGravity() == Approx(0.44638781861292243) );
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
        CHECK( outputs[2].getHeatingValue() == 1080.6848266529887 );
        CHECK( outputs[2].getHeatingValueVolume() == 83.605 );
        CHECK( outputs[2].getSpecificGravity() == 1.0870540901007706 );
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
        CHECK( output.getHeatingValue() == 1080.6848266529887 );
        CHECK( output.getHeatingValueVolume() == 83.605 );
        CHECK( output.getSpecificGravity() == 1.0870540901007706 );
    }
}

TEST_CASE( "SQLite - CustomGasFlueGasMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto size = sqlite.getGasFlueGasMaterials().size();
        GasCompositions expected("customGasFlueGas", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        expected.setID(size);
        sqlite.insertGasFlueGasMaterial(expected);
	    auto const output = sqlite.getGasFlueGasMaterials();
	    CHECK(output[size].getSubstance() == expected.getSubstance());
    }

    {
        auto size = sqlite.getGasFlueGasMaterials().size();
        GasCompositions expected("customGasFlueGas2", 87, 8.5, 3.6, 0.4, 0, 0, 0, 0, 0.4, 0, 0.1);
        expected.setID(size);
        sqlite.insertGasFlueGasMaterial(expected);
        auto const output = sqlite.getCustomGasFlueGasMaterials();
        CHECK(output.size() == 2);
        CHECK(output[1].getSubstance() == expected.getSubstance());
    }
    {
        auto comp = GasCompositions("customGasFlueGas3", 45, 45, 1, 1, 3, 2, 0, 1, 0, 0, 2);
        comp.setID(sqlite.getGasFlueGasMaterials().size());
        sqlite.insertGasFlueGasMaterial(comp);
        auto const output = sqlite.getCustomGasFlueGasMaterials();
        CHECK(output.size() == 3);
        CHECK(output[2].getSubstance() == comp.getSubstance());
        CHECK(output[2].getHeatingValue() == Approx(21684.26));
        CHECK(output[2].getSpecificGravity() == Approx(0.9060143746));
        CHECK(output[2].getHeatingValueVolume() == Approx(1400.8));
    }

}
TEST_CASE( "SQLite - getSolidLiquidFlueGasMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

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

TEST_CASE( "SQLite - CustomSolidLiquidFlueGasMaterials", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const size = sqlite.getSolidLiquidFlueGasMaterials().size();
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5);
        expected.setSubstance("customSolidLiquidFlueGas");
        expected.setID(size);
	    sqlite.insertSolidLiquidFlueGasMaterial(expected);
        auto const output = sqlite.getSolidLiquidFlueGasMaterials();
	    CHECK(output[size].getSubstance() == expected.getSubstance());
    }

    {
        auto const size = sqlite.getSolidLiquidFlueGasMaterials().size();
        auto expected = SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 70.3, 4.9, 2.2, 8.7, 7.5, 4.9, 1.5);
        expected.setSubstance("customSolidLiquidFlueGas2");
        expected.setID(size);
        sqlite.insertSolidLiquidFlueGasMaterial(expected);
        auto const output = sqlite.getCustomSolidLiquidFlueGasMaterials();
        CHECK(output.size() == 2);
        CHECK(output[1].getSubstance() == expected.getSubstance());
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

TEST_CASE( "SQLite - CustomAtmosphereSpecificHeat", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
        auto const size = sqlite.getAtmosphereSpecificHeat().size();
        Atmosphere expected;
        expected.setSubstance("customAtmosphere");
        expected.setID(size);
        sqlite.insertAtmosphereSpecificHeat(expected);
        auto const outputs = sqlite.getAtmosphereSpecificHeat();
        CHECK( outputs.size() == size + 1 );
        CHECK( outputs[size].getSubstance() == expected.getSubstance() );
    }

    {
        auto const size = sqlite.getAtmosphereSpecificHeat().size();
        Atmosphere expected;
        expected.setSubstance("customAtmosphere2");
        expected.setID(size);
        sqlite.insertAtmosphereSpecificHeat(expected);
        auto const outputs = sqlite.getCustomAtmosphereSpecificHeat();
        CHECK( outputs.size() == 2 );
        CHECK( outputs[1].getSubstance() == expected.getSubstance() );
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

TEST_CASE( "SQLite - CustomWallLossesSurface", "[sqlite]" ) {
    auto sqlite = SQLite(":memory:", true);

    {
	    auto const size = sqlite.getWallLossesSurface().size();
        WallLosses expected;
        expected.setSurface("customSurface");
        expected.setConditionFactor(10);
        expected.setID(size);
        sqlite.insertWallLossesSurface(expected);
        auto const output = sqlite.getWallLossesSurface();
        CHECK( output.size() == size + 1 );
        CHECK( output[size].getConditionFactor() == expected.getConditionFactor() );
    }

    {
        auto const size = sqlite.getWallLossesSurface().size();
        WallLosses expected;
        expected.setSurface("customSurface2");
        expected.setConditionFactor(19);
        expected.setID(size);
        sqlite.insertWallLossesSurface(expected);
        auto const output = sqlite.getCustomWallLossesSurface();
        CHECK( output.size() == 2 );
        CHECK( output[1].getConditionFactor() == expected.getConditionFactor() );
    }
}

TEST_CASE( "SQLite - Motor Data", "[sqlite][motor]" ) {
    auto const compare = [](MotorData result, MotorData expected) {
		CHECK(result.getManufacturer() == expected.getManufacturer());
		CHECK(result.getModel() == expected.getModel());
		CHECK(result.getCatalog() == expected.getCatalog());
		CHECK(result.getMotorType() == expected.getMotorType());
		CHECK(result.getHp() == expected.getHp());
		CHECK(result.getSpeed() == expected.getSpeed());
		CHECK(result.getFullLoadSpeed() == expected.getFullLoadSpeed());
		CHECK(result.getEnclosureType() == expected.getEnclosureType());
		CHECK(result.getFrameNumber() == expected.getFrameNumber());
		CHECK(result.getVoltageRating() == expected.getVoltageRating());
		CHECK(result.getPurpose() == expected.getPurpose());
		CHECK(result.getUFrame() == expected.getUFrame());
		CHECK(result.getCFace() == expected.getCFace());
		CHECK(result.getVerticalShaft() == expected.getVerticalShaft());
		CHECK(result.getDFlange() == expected.getDFlange());
		CHECK(result.getServiceFactor() == expected.getServiceFactor());
		CHECK(result.getInsulationClass() == expected.getInsulationClass());
		CHECK(result.getWeight() == expected.getWeight());
		CHECK(result.getListPrice() == expected.getListPrice());
		CHECK(result.getWindingResistance() == expected.getWindingResistance());
		CHECK(result.getWarranty() == expected.getWarranty());
		CHECK(result.getRotorBars() == expected.getRotorBars());
		CHECK(result.getStatorSlots() == expected.getStatorSlots());
		CHECK(result.getEfficiency100() == expected.getEfficiency100());
		CHECK(result.getEfficiency75() == expected.getEfficiency75());
		CHECK(result.getEfficiency50() == expected.getEfficiency50());
		CHECK(result.getEfficiency25() == expected.getEfficiency25());
		CHECK(result.getPowerFactor100() == expected.getPowerFactor100());
		CHECK(result.getPowerFactor75() == expected.getPowerFactor75());
		CHECK(result.getPowerFactor50() == expected.getPowerFactor50());
		CHECK(result.getPowerFactor25() == expected.getPowerFactor25());
		CHECK(result.getTorqueFullLoad() == expected.getTorqueFullLoad());
		CHECK(result.getTorqueBreakDown() == expected.getTorqueBreakDown());
		CHECK(result.getTorqueLockedRotor() == expected.getTorqueLockedRotor());
		CHECK(result.getAmpsFullLoad() == expected.getAmpsFullLoad());
		CHECK(result.getAmpsIdle() == expected.getAmpsIdle());
		CHECK(result.getAmpsLockedRotor() == expected.getAmpsLockedRotor());
		CHECK(result.getStalledRotorTimeHot() == expected.getStalledRotorTimeHot());
		CHECK(result.getStalledRotorTimeCold() == expected.getStalledRotorTimeCold());
		CHECK(result.getPeakVoltage0ms() == expected.getPeakVoltage0ms());
		CHECK(result.getPeakVoltage5ms() == expected.getPeakVoltage5ms());
        CHECK(result.getId() == expected.getId());
    };

    auto sqlite = SQLite(":memory:", true);

    {
        auto const motors = sqlite.getMotorData();

        auto expected = MotorData(
                "GE", "X$D Ultra IEEE 841", "M9455", "NEMA Design B", 50, 1800, 1780, "TEFC", "326T", 460,
                "IEEE 841 Petroleum/Chemical", 0, 0, 0, 0, 1.15, "F", 511, 4, 615, 99.5, 5, 38, 48, 94.5, 94.7,
                94.3, 91.6, 78, 73.6, 63.3, 41.5, 147.4, 294.8, 206.4, 63.5, 25.7, 362.5, 92.9, 115.2, 2000
        );
        expected.setId(1);

	    compare(motors[0], expected);

	    auto expected2 = MotorData(
			    "WEG Electric", "W22-NEMA Premium SD", "20018ET3G447", "NEMA Design B", 200, 1800, 0, "TEFC",
			    "447/9T", 460, "undefined", 0, 0, 0, 0, 1.15, "undefined", 1899, 21098, 0, 0, 0, 0, 96.2, 96.2,
			    95.4, 0, 85, 82, 73, 0, 582, 1455, 1396.8, 230, 0, 1564, 16, 35, 0, 0
	    );
        expected2.setId(2);

	    auto const motor = sqlite.getMotorDataById(2);
        compare(motor, expected2);
    }

    {
        auto ktm = MotorData(
                "KTM", "Freeride-e", "KTM Motors 2018", "electric motor", 24, 4500, 5000, "TEFC",
                "447/9T", 260, "to provide hours of fun on a single charge", 0, 0, 0, 0, 1.15, "undefined", 60, 5000, 0, 2, 0, 0, 96.2, 96.2,
                95.4, 0, 85, 82, 73, 0, 42, 42, 42, 230, 0, 1564, 16, 35, 300, 300
        );
	    ktm.setId(4);

        sqlite.insertMotorData(ktm);
        auto const motors = sqlite.getMotorData();
	    compare(ktm, motors.back());

        auto const customMotors = sqlite.getCustomMotorData();
        compare(ktm, customMotors[0]);

        sqlite.deleteMotorData(ktm.getId());
	    CHECK(sqlite.getCustomMotorData().size() == 0);
    }
}

