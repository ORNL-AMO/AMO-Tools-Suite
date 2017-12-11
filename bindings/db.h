#ifndef AMO_TOOLS_SUITE_DB_H
#define AMO_TOOLS_SUITE_DB_H
#include <nan.h>
#include <node.h>
#include <sqlite/SQLite.h>
#include <fstream>
#include <memory>
#include <chrono>
#include <iostream>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/GasFlueGasMaterial.h>
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>
#include <calculator/losses/Atmosphere.h>
#include <calculator/losses/WallLosses.h>

using namespace Nan;
using namespace v8;

Local<Object> inp;
std::unique_ptr<SQLite> sql;

double Get(std::string const & nm) {
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();

    auto rObj = inp->ToObject()->Get(getName);
    if (rObj->IsUndefined()) {
        ThrowTypeError(std::string("Get method in db.h: " + nm + " not present in object").c_str());
    }
    return rObj->NumberValue();
}

std::string GetStr(std::string const & nm) {
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    auto obj = inp->ToObject()->Get(getName);
    if (obj->IsUndefined()) {
        ThrowTypeError(std::string("GetStr method in db.h: " + nm + " not present in object").c_str());
    }
    v8::String::Utf8Value s(obj);
    return std::string(*s);
}


// update all tables to have secondary key
// when creating sqlite, add table that has history, put in tools-suite number and the date so that we know where db's came from
// so data is version, timestamp, comment - "initial file based release"
// to save the backup,

    NAN_METHOD(startup) {
//        std::string dbName = "db/amo_tools_suite.db";
//        std::ifstream ifs(dbName);
//	    const bool fileExists = ifs.is_open();
//        ifs.close();
//	    sql.reset();
//        sql = std::unique_ptr<SQLite>(new SQLite(dbName, ! fileExists));

	    std::string const dbName = ":memory:";
	    sql.reset();
	    sql = std::unique_ptr<SQLite>(new SQLite(dbName, true));
    }

    // used for unit testing, we don't want files written to the hard drive during testing
    NAN_METHOD(unitTestStartup) {
        std::string dbName = ":memory:";
        sql = std::unique_ptr<SQLite>(new SQLite(dbName, true));
    }

// commented out due to the likely removal of these methods
//// to be run before program shutdown upon software update, shouldn't be used in unit tests
//    NAN_METHOD(preUpdate) {
//        sql.reset();
//        std::rename("db/amo_tools_suite.db", "db/amo_tools_suite_temporary_backup.db");
//    }
//
//// to be called after program shutdown, upon software restart, shouldn't be used in unit tests
//NAN_METHOD(postUpdate) {
//    auto const backupSql = SQLite("db/amo_tools_suite_temporary_backup.db", false);
//    auto const customSolidLoadChargeMats = backupSql.getCustomSolidLoadChargeMaterials();
//
//    auto const now = std::chrono::system_clock::now();
//    auto const date = std::chrono::system_clock::to_time_t(now);
//    std::string dateStr = (ctime(&date));
//    dateStr = dateStr.substr(0, dateStr.size() - 1);
//    std::string db = "db/amo_tools_suite_" + dateStr + ".db";
//    std::rename("db/amo_tools_suite_temporary_backup.db", db.c_str());
//
//    startup(info);
//
//    for (auto const mat : customSolidLoadChargeMats) {
//        sql->insertSolidLoadChargeMaterials(mat);
//    }
//}

    NAN_METHOD(selectSolidLoadChargeMaterials) {
	    Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

        auto const slcms = sql->getSolidLoadChargeMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( std::size_t i = 0; i < slcms.size(); i++ ) {
            auto const & slcm = slcms[i];
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, id, Nan::New<Number>(slcm.getID()));
            Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()).ToLocalChecked());
            Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
            Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
            Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(slcm.getSpecificHeatLiquid()));
            Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));
	        Nan::Set(objs, i, obj);
        }

        info.GetReturnValue().Set(objs);
    }

    NAN_METHOD(selectSolidLoadChargeMaterialById) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

	    auto const slcm = sql->getSolidLoadChargeMaterialById(static_cast<int>(info[0]->NumberValue()));

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(slcm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
        Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(slcm.getSpecificHeatLiquid()));
        Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));

        info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(insertSolidLoadChargeMaterial) {
        inp = info[0]->ToObject();
        SolidLoadChargeMaterial slcm;
        slcm.setSubstance(GetStr("substance"));
        slcm.setSpecificHeatSolid(Get("specificHeatSolid"));
        slcm.setSpecificHeatLiquid(Get("specificHeatLiquid"));
        slcm.setLatentHeat(Get("latentHeat"));
        slcm.setMeltingPoint(Get("meltingPoint"));
        bool success = sql->insertSolidLoadChargeMaterials(slcm);
        info.GetReturnValue().Set(success);
    }

NAN_METHOD(deleteSolidLoadChargeMaterial) {
    inp = info[0]->ToObject();
    sql->deleteSolidLoadChargeMaterial(GetStr("substance"));
}

    NAN_METHOD(selectLiquidLoadChargeMaterials) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
        Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();

        auto const llcms = sql->getLiquidLoadChargeMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( std::size_t i = 0; i < llcms.size(); i++ ) {
	        auto const & llcm = llcms[i];
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, id, Nan::New<Number>(llcm.getID()));
            Nan::Set(obj, substance, Nan::New<String>(llcm.getSubstance()).ToLocalChecked());
            Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(llcm.getSpecificHeatLiquid()));
            Nan::Set(obj, specificHeatVapor, Nan::New<Number>(llcm.getSpecificHeatVapor()));
            Nan::Set(obj, vaporizationTemperature, Nan::New<Number>(llcm.getVaporizingTemperature()));
            Nan::Set(obj, latentHeat, Nan::New<Number>(llcm.getLatentHeat()));
            Nan::Set(objs, i, obj);
        }

        info.GetReturnValue().Set(objs);
    }

NAN_METHOD(insertLiquidLoadChargeMaterial) {
    inp = info[0]->ToObject();
    LiquidLoadChargeMaterial llcm;
    llcm.setSubstance(GetStr("substance"));
    llcm.setSpecificHeatLiquid(Get("specificHeatLiquid"));
    llcm.setSpecificHeatVapor(Get("specificHeatVapor"));
    llcm.setVaporizingTemperature(Get("vaporizationTemperature"));
    llcm.setLatentHeat(Get("latentHeat"));
    bool success = sql->insertLiquidLoadChargeMaterials(llcm);
    info.GetReturnValue().Set(success);
}

NAN_METHOD(deleteLiquidLoadChargeMaterial) {
    inp = info[0]->ToObject();
    sql->deleteLiquidLoadChargeMaterial(GetStr("substance"));
}

    NAN_METHOD(selectLiquidLoadChargeMaterialById) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
        Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();

        auto const llcm = sql->getLiquidLoadChargeMaterialById(static_cast<int>(info[0]->NumberValue()));

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(llcm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(llcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(llcm.getSpecificHeatLiquid()));
        Nan::Set(obj, specificHeatVapor, Nan::New<Number>(llcm.getSpecificHeatVapor()));
        Nan::Set(obj, vaporizationTemperature, Nan::New<Number>(llcm.getVaporizingTemperature()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(llcm.getLatentHeat()));

        info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(selectGasLoadChargeMaterials) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();

        auto const glcms = sql->getGasLoadChargeMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( std::size_t i = 0; i < glcms.size(); i++ ) {
            auto const & glcm = glcms[i];
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, id, Nan::New<Number>(glcm.getID()));
            Nan::Set(obj, substance, Nan::New<String>(glcm.getSubstance()).ToLocalChecked());
            Nan::Set(obj, specificHeatVapor, Nan::New<Number>(glcm.getSpecificHeatVapor()));
            Nan::Set(objs, i, obj);
        }

        info.GetReturnValue().Set(objs);
    }

NAN_METHOD(insertGasLoadChargeMaterial) {
    inp = info[0]->ToObject();
    GasLoadChargeMaterial glcm;
    glcm.setSubstance(GetStr("substance"));
	glcm.setSpecificHeatVapor(Get("specificHeatVapor"));
    bool success = sql->insertGasLoadChargeMaterials(glcm);
    info.GetReturnValue().Set(success);
}

NAN_METHOD(deleteGasLoadChargeMaterial) {
    inp = info[0]->ToObject();
    sql->deleteGasLoadChargeMaterial(GetStr("substance"));
}

    NAN_METHOD(selectGasLoadChargeMaterialById) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
	    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
	    Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();

	    auto const glcm = sql->getGasLoadChargeMaterialById(static_cast<int>(info[0]->NumberValue()));

	    Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(glcm.getID()));
	    Nan::Set(obj, substance, Nan::New<String>(glcm.getSubstance()).ToLocalChecked());
	    Nan::Set(obj, specificHeatVapor, Nan::New<Number>(glcm.getSpecificHeatVapor()));

	    info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(selectSolidLiquidFlueGasMaterials) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> carbon = Nan::New<String>("carbon").ToLocalChecked();
        Local<String> hydrogen = Nan::New<String>("hydrogen").ToLocalChecked();
        Local<String> sulphur = Nan::New<String>("sulphur").ToLocalChecked();
        Local<String> inertAsh = Nan::New<String>("inertAsh").ToLocalChecked();
        Local<String> o2 = Nan::New<String>("o2").ToLocalChecked();
        Local<String> moisture = Nan::New<String>("moisture").ToLocalChecked();
        Local<String> nitrogen = Nan::New<String>("nitrogen").ToLocalChecked();

        auto const fgMaterials = sql->getSolidLiquidFlueGasMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( std::size_t i = 0; i < fgMaterials.size(); i++ ) {
            auto const & fgm = fgMaterials[i];
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, id, Nan::New<Number>(fgm.getID()));
            Nan::Set(obj, substance, Nan::New<String>(fgm.getSubstance()).ToLocalChecked());
            Nan::Set(obj, carbon, Nan::New<Number>(fgm.getCarbon()));
            Nan::Set(obj, hydrogen, Nan::New<Number>(fgm.getHydrogen()));
            Nan::Set(obj, sulphur, Nan::New<Number>(fgm.getSulphur()));
            Nan::Set(obj, inertAsh, Nan::New<Number>(fgm.getInertAsh()));
            Nan::Set(obj, o2, Nan::New<Number>(fgm.getO2()));
            Nan::Set(obj, moisture, Nan::New<Number>(fgm.getMoisture()));
            Nan::Set(obj, nitrogen, Nan::New<Number>(fgm.getNitrogen()));
            Nan::Set(objs, i, obj);
        }

        info.GetReturnValue().Set(objs);
    };

NAN_METHOD(insertSolidLiquidFlueGasMaterial) {
    inp = info[0]->ToObject();
    SolidLiquidFlueGasMaterial slfgm(0, 0, 0, 0, 0, 0, 0, Get("carbon") * 100, Get("hydrogen") * 100,
                                     Get("sulphur") * 100, Get("inertAsh") * 100, Get("o2") * 100,
                                     Get("moisture") * 100, Get("nitrogen") * 100);

    slfgm.setSubstance(GetStr("substance"));
    bool success = sql->insertSolidLiquidFlueGasMaterial(slfgm);
    info.GetReturnValue().Set(success);
};

NAN_METHOD(deleteSolidLiquidFlueGasMaterial) {
    inp = info[0]->ToObject();
    sql->deleteSolidLiquidFlueGasMaterial(GetStr("substance"));
};

    NAN_METHOD(selectSolidLiquidFlueGasMaterialById) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> carbon = Nan::New<String>("carbon").ToLocalChecked();
        Local<String> hydrogen = Nan::New<String>("hydrogen").ToLocalChecked();
        Local<String> sulphur = Nan::New<String>("sulphur").ToLocalChecked();
        Local<String> inertAsh = Nan::New<String>("inertAsh").ToLocalChecked();
        Local<String> o2 = Nan::New<String>("o2").ToLocalChecked();
        Local<String> moisture = Nan::New<String>("moisture").ToLocalChecked();
        Local<String> nitrogen = Nan::New<String>("nitrogen").ToLocalChecked();

        auto const fgm = sql->getSolidLiquidFlueGasMaterialById(static_cast<int>(info[0]->NumberValue()));
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(fgm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(fgm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, carbon, Nan::New<Number>(fgm.getCarbon()));
        Nan::Set(obj, hydrogen, Nan::New<Number>(fgm.getHydrogen()));
        Nan::Set(obj, sulphur, Nan::New<Number>(fgm.getSulphur()));
        Nan::Set(obj, inertAsh, Nan::New<Number>(fgm.getInertAsh()));
        Nan::Set(obj, o2, Nan::New<Number>(fgm.getO2()));
        Nan::Set(obj, moisture, Nan::New<Number>(fgm.getMoisture()));
        Nan::Set(obj, nitrogen, Nan::New<Number>(fgm.getNitrogen()));

        info.GetReturnValue().Set(obj);
    };

    NAN_METHOD(selectGasFlueGasMaterials) {
	    Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> CH4 = Nan::New<String>("CH4").ToLocalChecked();
        Local<String> C2H6 = Nan::New<String>("C2H6").ToLocalChecked();
        Local<String> N2 = Nan::New<String>("N2").ToLocalChecked();
        Local<String> H2 = Nan::New<String>("H2").ToLocalChecked();
        Local<String> C3H8 = Nan::New<String>("C3H8").ToLocalChecked();
        Local<String> C4H10_CnH2n = Nan::New<String>("C4H10_CnH2n").ToLocalChecked();
        Local<String> H2O = Nan::New<String>("H2O").ToLocalChecked();
        Local<String> CO = Nan::New<String>("CO").ToLocalChecked();
        Local<String> CO2 = Nan::New<String>("CO2").ToLocalChecked();
        Local<String> SO2 = Nan::New<String>("SO2").ToLocalChecked();
        Local<String> O2 = Nan::New<String>("O2").ToLocalChecked();
        Local<String> heatingValue = Nan::New<String>("heatingValue").ToLocalChecked();
        Local<String> specificGravity = Nan::New<String>("specificGravity").ToLocalChecked();

        auto const fgMaterials = sql->getGasFlueGasMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( std::size_t i = 0; i < fgMaterials.size(); i++ ) {
            auto const & fgm = fgMaterials[i];
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, id, Nan::New<Number>(fgm.getID()));
            Nan::Set(obj, substance, Nan::New<String>(fgm.getSubstance()).ToLocalChecked());
            Nan::Set(obj, CH4, Nan::New<Number>(fgm.getGasByVol("CH4")));
            Nan::Set(obj, C2H6, Nan::New<Number>(fgm.getGasByVol("C2H6")));
            Nan::Set(obj, N2, Nan::New<Number>(fgm.getGasByVol("N2")));
            Nan::Set(obj, H2, Nan::New<Number>(fgm.getGasByVol("H2")));
            Nan::Set(obj, C3H8, Nan::New<Number>(fgm.getGasByVol("C3H8")));
            Nan::Set(obj, C4H10_CnH2n, Nan::New<Number>(fgm.getGasByVol("C4H10_CnH2n")));
            Nan::Set(obj, H2O, Nan::New<Number>(fgm.getGasByVol("H2O")));
            Nan::Set(obj, CO, Nan::New<Number>(fgm.getGasByVol("CO")));
            Nan::Set(obj, CO2, Nan::New<Number>(fgm.getGasByVol("CO2")));
            Nan::Set(obj, SO2, Nan::New<Number>(fgm.getGasByVol("SO2")));
            Nan::Set(obj, O2, Nan::New<Number>(fgm.getGasByVol("O2")));
            Nan::Set(obj, heatingValue, Nan::New<Number>(fgm.getHeatingValue()));
            Nan::Set(obj, specificGravity, Nan::New<Number>(fgm.getSpecificGravity()));
            Nan::Set(objs, i, obj);
        }

        info.GetReturnValue().Set(objs);
    };

NAN_METHOD(insertGasFlueGasMaterial) {
	inp = info[0]->ToObject();
	GasCompositions comp(GetStr("substance"), Get("CH4"), Get("C2H6"), Get("N2"), Get("H2"), Get("C3H8"),
	                     Get("C4H10_CnH2n"), Get("H2O"), Get("CO"), Get("CO2"), Get("SO2"), Get("O2"));

	bool success = sql->insertGasFlueGasMaterial(comp);
	info.GetReturnValue().Set(success);
}

NAN_METHOD(deleteGasFlueGasMaterial) {
    inp = info[0]->ToObject();
    sql->deleteGasFlueGasMaterial(GetStr("substance"));
}

    NAN_METHOD(selectGasFlueGasMaterialById) {
        Local<String> id = Nan::New<String>("id").ToLocalChecked();
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> CH4 = Nan::New<String>("CH4").ToLocalChecked();
        Local<String> C2H6 = Nan::New<String>("C2H6").ToLocalChecked();
        Local<String> N2 = Nan::New<String>("N2").ToLocalChecked();
        Local<String> H2 = Nan::New<String>("H2").ToLocalChecked();
        Local<String> C3H8 = Nan::New<String>("C3H8").ToLocalChecked();
        Local<String> C4H10_CnH2n = Nan::New<String>("C4H10_CnH2n").ToLocalChecked();
        Local<String> H2O = Nan::New<String>("H2O").ToLocalChecked();
        Local<String> CO = Nan::New<String>("CO").ToLocalChecked();
        Local<String> CO2 = Nan::New<String>("CO2").ToLocalChecked();
        Local<String> SO2 = Nan::New<String>("SO2").ToLocalChecked();
        Local<String> O2 = Nan::New<String>("O2").ToLocalChecked();
        Local<String> heatingValue = Nan::New<String>("heatingValue").ToLocalChecked();
        Local<String> specificGravity = Nan::New<String>("specificGravity").ToLocalChecked();

        auto const fgm = sql->getGasFlueGasMaterialById(static_cast<int>(info[0]->NumberValue()));

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(fgm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(fgm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, CH4, Nan::New<Number>(fgm.getGasByVol("CH4")));
        Nan::Set(obj, C2H6, Nan::New<Number>(fgm.getGasByVol("C2H6")));
        Nan::Set(obj, N2, Nan::New<Number>(fgm.getGasByVol("N2")));
        Nan::Set(obj, H2, Nan::New<Number>(fgm.getGasByVol("H2")));
        Nan::Set(obj, C3H8, Nan::New<Number>(fgm.getGasByVol("C3H8")));
        Nan::Set(obj, C4H10_CnH2n, Nan::New<Number>(fgm.getGasByVol("C4H10_CnH2n")));
        Nan::Set(obj, H2O, Nan::New<Number>(fgm.getGasByVol("H2O")));
        Nan::Set(obj, CO, Nan::New<Number>(fgm.getGasByVol("CO")));
        Nan::Set(obj, CO2, Nan::New<Number>(fgm.getGasByVol("CO2")));
        Nan::Set(obj, SO2, Nan::New<Number>(fgm.getGasByVol("SO2")));
        Nan::Set(obj, O2, Nan::New<Number>(fgm.getGasByVol("O2")));
        Nan::Set(obj, heatingValue, Nan::New<Number>(fgm.getHeatingValue()));
        Nan::Set(obj, specificGravity, Nan::New<Number>(fgm.getSpecificGravity()));

        info.GetReturnValue().Set(obj);
    };


NAN_METHOD(selectAtmosphereSpecificHeat) {
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeat = Nan::New<String>("specificHeat").ToLocalChecked();
    auto const aMaterials = sql->getAtmosphereSpecificHeat();

    auto objs = Nan::New<v8::Array>();
    for ( std::size_t i = 0; i < aMaterials.size(); i++ ) {
        auto const ash = aMaterials[i];
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(ash.getID()));
        Nan::Set(obj, substance, Nan::New<String>(ash.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeat, Nan::New<Number>(ash.getSpecificHeat()));
        Nan::Set(objs, i, obj);
    }

    info.GetReturnValue().Set(objs);
};

NAN_METHOD(insertAtmosphereSpecificHeat) {
    inp = info[0]->ToObject();
	Atmosphere atmos;
    atmos.setSubstance(GetStr("substance"));
	atmos.setSpecificHeat(Get("specificHeat"));
    bool success = sql->insertAtmosphereSpecificHeat(atmos);
    info.GetReturnValue().Set(success);
};

NAN_METHOD(deleteAtmosphereSpecificHeat) {
    inp = info[0]->ToObject();
    sql->deleteAtmosphereSpecificHeat(GetStr("substance"));
};

NAN_METHOD(selectAtmosphereSpecificHeatById) {
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeat = Nan::New<String>("specificHeat").ToLocalChecked();

    auto const ash = sql->getAtmosphereSpecificHeatById(static_cast<int>(info[0]->NumberValue()));
    Local<Object> obj = Nan::New<Object>();
    Nan::Set(obj, id, Nan::New<Number>(ash.getID()));
    Nan::Set(obj, substance, Nan::New<String>(ash.getSubstance()).ToLocalChecked());
    Nan::Set(obj, specificHeat, Nan::New<Number>(ash.getSpecificHeat()));

    info.GetReturnValue().Set(obj);
};

NAN_METHOD(selectWallLossesSurface) {
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> surface = Nan::New<String>("surface").ToLocalChecked();
    Local<String> conditionFactor = Nan::New<String>("conditionFactor").ToLocalChecked();
    auto const wlSurfaces = sql->getWallLossesSurface();

    auto objs = Nan::New<v8::Array>();
    for ( std::size_t i = 0; i < wlSurfaces.size(); i++ ) {
        auto const & wls = wlSurfaces[i];
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(wls.getID()));
        Nan::Set(obj, surface, Nan::New<String>(wls.getSurface()).ToLocalChecked());
        Nan::Set(obj, conditionFactor, Nan::New<Number>(wls.getConditionFactor()));
        Nan::Set(objs, i, obj);
    }

    info.GetReturnValue().Set(objs);
};

NAN_METHOD(insertWallLossesSurface) {
    inp = info[0]->ToObject();
    WallLosses wl;
    wl.setSurface(GetStr("surface"));
    wl.setConditionFactor(Get("conditionFactor"));
    bool success = sql->insertWallLossesSurface(wl);
    info.GetReturnValue().Set(success);
};

NAN_METHOD(deleteWallLossesSurface) {
    inp = info[0]->ToObject();
    sql->deleteWallLossesSurface(GetStr("surface"));
};

NAN_METHOD(selectWallLossesSurfaceById) {
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> surface = Nan::New<String>("surface").ToLocalChecked();
    Local<String> conditionFactor = Nan::New<String>("conditionFactor").ToLocalChecked();

    auto const wls = sql->getWallLossesSurfaceById(static_cast<int>(info[0]->NumberValue()));
    Local<Object> obj = Nan::New<Object>();
    Nan::Set(obj, id, Nan::New<Number>(wls.getID()));
    Nan::Set(obj, surface, Nan::New<String>(wls.getSurface()).ToLocalChecked());
    Nan::Set(obj, conditionFactor, Nan::New<Number>(wls.getConditionFactor()));

    info.GetReturnValue().Set(obj);
};


#endif //AMO_TOOLS_SUITE_DB_H
