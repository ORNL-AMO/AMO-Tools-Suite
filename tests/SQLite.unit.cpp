#include "catch.hpp"
#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <calculator/losses/GasFlueGasMaterial.h>
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>
#include <calculator/losses/Atmosphere.h>
#include <calculator/losses/WallLosses.h>
#include <calculator/pump/PumpData.h>
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

    {
        SolidLiquidFlueGasMaterial slfgm(0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7);
	    slfgm.setSubstance("initial");
	    sqlite.insertSolidLiquidFlueGasMaterial(slfgm);

        slfgm = {0, 0, 0, 0, 0, 0, 0, 8, 9, 10, 11, 12, 13, 14};
        slfgm.setSubstance("initial2");
        sqlite.insertSolidLiquidFlueGasMaterial(slfgm);

        auto custom1 = sqlite.getCustomSolidLiquidFlueGasMaterials().at(0);
        auto custom2 = sqlite.getCustomSolidLiquidFlueGasMaterials().at(1);

        custom1.setSubstance("updatedCustom1");
        custom1.setCarbon(0.1);
        custom1.setHydrogen(0.2);
        custom1.setSulphur(0.3);
        custom1.setInertAsh(0.4);
        custom1.setO2(0.5);
        custom1.setMoisture(0.6);
        custom1.setNitrogen(0.7);

        custom2.setSubstance("updatedCustom2");
        custom2.setCarbon(80);
        custom2.setHydrogen(90);
        custom2.setSulphur(100);
        custom2.setInertAsh(110);
        custom2.setO2(120);
        custom2.setMoisture(130);
        custom2.setNitrogen(140);

        sqlite.updateSolidLiquidFlueGasMaterial(custom1);
        sqlite.updateSolidLiquidFlueGasMaterial(custom2);

        CHECK(custom1.getSubstance() == "updatedCustom1");
        CHECK(Approx(custom1.getCarbon()) == 0.1);;
        CHECK(Approx(custom1.getHydrogen()) == 0.2);
        CHECK(Approx(custom1.getSulphur()) == 0.3);
        CHECK(Approx(custom1.getInertAsh()) == 0.4);
        CHECK(Approx(custom1.getO2()) == 0.5);
        CHECK(Approx(custom1.getMoisture()) == 0.6);
        CHECK(Approx(custom1.getNitrogen()) == 0.7);

        CHECK(custom2.getSubstance() == "updatedCustom2");
        CHECK(Approx(custom2.getCarbon()) == 80);
        CHECK(Approx(custom2.getHydrogen()) == 90);
        CHECK(Approx(custom2.getSulphur()) == 100);
        CHECK(Approx(custom2.getInertAsh()) == 110);
        CHECK(Approx(custom2.getO2()) == 120);
        CHECK(Approx(custom2.getMoisture()) == 130);
        CHECK(Approx(custom2.getNitrogen()) == 140);
    }

	{
        sqlite.insertGasFlueGasMaterial({"custom1", 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11});
        sqlite.insertGasFlueGasMaterial({"custom2", 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22});

        GasCompositions custom1 = {"updatedCustom1", 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110};
        custom1.setID(sqlite.getCustomGasFlueGasMaterials().at(0).getID());
        GasCompositions custom2 = {"updatedCustom2", 120, 130, 140, 150, 160, 170, 180, 19, 20, 21, 22};
		custom2.setID(sqlite.getCustomGasFlueGasMaterials().at(1).getID());

        sqlite.updateGasFlueGasMaterial(custom1);
        sqlite.updateGasFlueGasMaterial(custom2);

        CHECK(custom1.getSubstance() == "updatedCustom1");
        CHECK(Approx(custom1.getGasByVol("CH4")) == 10);
        CHECK(Approx(custom1.getGasByVol("C2H6")) == 20);
        CHECK(Approx(custom1.getGasByVol("N2")) == 30);
        CHECK(Approx(custom1.getGasByVol("H2")) == 40);
        CHECK(Approx(custom1.getGasByVol("C3H8")) == 50);
        CHECK(Approx(custom1.getGasByVol("C4H10_CnH2n")) == 60);
        CHECK(Approx(custom1.getGasByVol("H2O")) == 70);
        CHECK(Approx(custom1.getGasByVol("CO")) == 80);
        CHECK(Approx(custom1.getGasByVol("CO2")) == 90);
        CHECK(Approx(custom1.getGasByVol("SO2")) == 100);
        CHECK(Approx(custom1.getGasByVol("O2")) == 110);

        CHECK(custom2.getSubstance() == "updatedCustom2");
        CHECK(Approx(custom2.getGasByVol("CH4")) == 120);
        CHECK(Approx(custom2.getGasByVol("C2H6")) == 130);
        CHECK(Approx(custom2.getGasByVol("N2")) == 140);
        CHECK(Approx(custom2.getGasByVol("H2")) == 150);
        CHECK(Approx(custom2.getGasByVol("C3H8")) == 160);
        CHECK(Approx(custom2.getGasByVol("C4H10_CnH2n")) == 170);
        CHECK(Approx(custom2.getGasByVol("H2O")) == 180);
        CHECK(Approx(custom2.getGasByVol("CO")) == 19);
        CHECK(Approx(custom2.getGasByVol("CO2")) == 20);
        CHECK(Approx(custom2.getGasByVol("SO2")) == 21);
        CHECK(Approx(custom2.getGasByVol("O2")) == 22);
	}

    {
        Atmosphere custom1;
        custom1.setSubstance("custom1");
        custom1.setSpecificHeat(0.5);
        sqlite.insertAtmosphereSpecificHeat(custom1);

        custom1.setSubstance("custom2");
        custom1.setSpecificHeat(0.75);
        sqlite.insertAtmosphereSpecificHeat(custom1);

        auto custom2 = sqlite.getCustomAtmosphereSpecificHeat().at(0);
        custom2.setSpecificHeat(500);
        custom2.setSubstance("updatedCustom1");

        auto custom3 = sqlite.getCustomAtmosphereSpecificHeat().at(1);
        custom3.setSpecificHeat(150);
        custom3.setSubstance("updatedCustom2");

        sqlite.updateAtmosphereSpecificHeat(custom2);
        sqlite.updateAtmosphereSpecificHeat(custom3);

		CHECK(sqlite.getCustomAtmosphereSpecificHeat().at(0).getSubstance() == "updatedCustom1");
        CHECK(sqlite.getCustomAtmosphereSpecificHeat().at(1).getSubstance() == "updatedCustom2");
        CHECK(sqlite.getCustomAtmosphereSpecificHeat().at(0).getSpecificHeat() == 500);
        CHECK(sqlite.getCustomAtmosphereSpecificHeat().at(1).getSpecificHeat() == 150);
    }

    {
        WallLosses wl;
        wl.setSurface("custom");
        wl.setConditionFactor(0.1);
        sqlite.insertWallLossesSurface(wl);
        wl.setSurface("custom2");
        wl.setConditionFactor(0.2);
        sqlite.insertWallLossesSurface(wl);

        auto custom = sqlite.getCustomWallLossesSurface().at(0);
        auto custom2 = sqlite.getCustomWallLossesSurface().at(1);

        custom.setSurface("updatedCustom");
        custom.setConditionFactor(0.5);
        custom2.setSurface("updatedCustom2");
        custom2.setConditionFactor(0.75);

        sqlite.updateWallLossesSurface(custom);
        sqlite.updateWallLossesSurface(custom2);

        CHECK(sqlite.getCustomWallLossesSurface().at(0).getSurface() == "updatedCustom");
        CHECK(sqlite.getCustomWallLossesSurface().at(1).getSurface() == "updatedCustom2");
        CHECK(Approx(sqlite.getCustomWallLossesSurface().at(0).getConditionFactor()) == 0.5);
        CHECK(Approx(sqlite.getCustomWallLossesSurface().at(1).getConditionFactor()) == 0.75);
    }

    {

		PumpData pump1("manufacturerCustom1", "modelCustom1", "typeCustom1", "serialNumberCustom1", "statusCustom1", "pumpTypeCustom1",
                    "radialBearingTypeCustom1", "thrustBearingTypeCustom1", "shaftOrientationCustom1", "shaftSealTypeCustom1", "fluidTypeCustom1",
                    "priorityCustom1", "driveTypeCustom1", "flangeConnectionClassCustom1", "flangeConnectionSizeCustom1", 1, 2, 1, 9000, 2018, 1780,
                    5, 90, 6, 89, 90, 85, 99, 15, 11, 13, 14, 0.5, 250, 85, 1.5, 600, 400, 70, 15, 20, 88, 15, 15, 15, 1);

        PumpData pump2("manufacturerCustom2", "modelCustom2", "typeCustom2", "serialNumberCustom2", "statusCustom2", "pumpTypeCustom2",
                    "radialBearingTypeCustom2", "thrustBearingTypeCustom2", "shaftOrientationCustom2", "shaftSealTypeCustom2", "fluidTypeCustom2",
                    "priorityCustom2", "driveTypeCustom2", "flangeConnectionClassCustom2", "flangeConnectionSizeCustom2", 1, 2, 1, 9000, 2018, 1780,
                    5, 90, 6, 89, 90, 85, 99, 15, 11, 13, 14, 0.5, 250, 85, 1.5, 600, 400, 70, 15, 20, 88, 15, 15, 15, 1);

		sqlite.insertPumpData(pump1);
        sqlite.insertPumpData(pump2);

        /*
        std::ofstream ofs("debug.txt");
        auto test = sqlite.getPumpData();
        ofs << std::endl;
        ofs << "getPumpData() returned size " << test.size() << std::endl;
        ofs << std::endl;
        ofs.close();
        */

        auto custom1 = sqlite.getCustomPumpData().at(0);
        auto custom2 = sqlite.getCustomPumpData().at(1);

		custom1.setManufacturer("updatedManufacturerCustom1");
        custom2.setManufacturer("updatedManufacturerCustom2");

        sqlite.updatePumpData(custom1);
        sqlite.updatePumpData(custom2);

        CHECK(sqlite.getCustomPumpData().at(0).getManufacturer() == "updatedManufacturerCustom1");
        CHECK(sqlite.getCustomPumpData().at(1).getManufacturer() == "updatedManufacturerCustom2");
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
        auto const last = output.back().getSubstance();
        GasCompositions gc("custom", 12, 13, 14, 15, 16, 14, 12, 12, 12, 12, 11);

        sqlite.insertGasFlueGasMaterial(gc);
        sqlite.deleteGasFlueGasMaterial(sqlite.getCustomGasFlueGasMaterials().back().getID());
        CHECK( sqlite.getGasFlueGasMaterials().back().getSubstance() == last );
    }

    {
        auto const last = sqlite.getSolidLiquidFlueGasMaterials().back().getSubstance();
        SolidLiquidFlueGasMaterial slfgm(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
        slfgm.setSubstance("custom");

        sqlite.insertSolidLiquidFlueGasMaterial(slfgm);
        sqlite.deleteSolidLiquidFlueGasMaterial(sqlite.getCustomSolidLiquidFlueGasMaterials().back().getID());
        CHECK( sqlite.getSolidLiquidFlueGasMaterials().back().getSubstance() == last );
    }

    {
        auto const output = sqlite.getAtmosphereSpecificHeat();
        auto const last = output.back().getSubstance();
	    Atmosphere a;
        a.setSubstance("custom");
		a.setSpecificHeat(0.56);

        sqlite.insertAtmosphereSpecificHeat(a);
        sqlite.deleteAtmosphereSpecificHeat(sqlite.getCustomAtmosphereSpecificHeat().back().getID());
        CHECK( sqlite.getAtmosphereSpecificHeat().back().getSubstance() == last );
    }

    {
        auto const output = sqlite.getWallLossesSurface();
        auto const last = output.back().getSurface();
	    WallLosses wall;
        wall.setSurface("custom");

        sqlite.insertWallLossesSurface(wall);
        sqlite.deleteWallLossesSurface(sqlite.getCustomWallLossesSurface().back().getID());
        auto const output2 = sqlite.getWallLossesSurface();
        CHECK( output2[output2.size() - 1].getSurface() == last );
    }

    {
        auto const output = sqlite.getPumpData();
        auto const last = output.back().getManufacturer();
        PumpData pump(
                "throw this pump away delete", "model", "type", "serialNumber", "status", "pumpType", "radial",
                "thrustBearingType", "shaftOrientation", "shaftSealType", "fluidType", "priority", "driveType",
                "flangeConnectionClass", "flangeConnectionSize", 1, 2, 1, 9000, 2018, 1780, 5, 90, 6, 89, 90,
                85, 99, 15, 11, 13, 14, 0.5, 250, 85, 1.5, 600, 400, 70, 15, 20, 88, 15, 15, 15, 1 );

        sqlite.insertPumpData(pump);
        sqlite.deletePumpData(sqlite.getPumpData().back().getId());
        auto const output2 = sqlite.getPumpData();
        CHECK( output2[output2.size() - 1].getManufacturer() == last );
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
