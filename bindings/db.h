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

double Get(std::string const &nm)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local<Value> rObj = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (rObj->IsUndefined())
    {
        ThrowTypeError(std::string("Get method in db.h: " + nm + " not present in object").c_str());
    }
    return Nan::To<double>(rObj).FromJust();
}

std::string GetStr(std::string const &nm)
{
    v8::Isolate *isolate = v8::Isolate::GetCurrent();
    v8::Local<v8::Context> context = isolate->GetCurrentContext();
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local<Value> obj = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
    if (obj->IsUndefined())
    {
        ThrowTypeError(std::string("GetStr method in db.h: " + nm + " not present in object").c_str());
    }
    v8::String::Utf8Value s(isolate, obj);
    return std::string(*s);
}

inline void SetObj(Local<Object> &obj, const std::string &key, double val)
{
    Nan::Set(obj, Nan::New<String>(key).ToLocalChecked(), Nan::New<Number>(val));
}

inline void SetObj(Local<Object> &obj, const std::string &key, const std::string &val)
{
    Nan::Set(obj, Nan::New<String>(key).ToLocalChecked(), Nan::New<String>(val).ToLocalChecked());
}

// when creating sqlite, add table that has history, put in tools-suite number and the date so that we know where db's came from
// so data is version, timestamp, comment - "initial file based release"
// to save the backup,

NAN_METHOD(startup)
{
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

NAN_METHOD(selectSolidLoadChargeMaterials)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
    Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
    Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
    Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

    auto const slcms = sql->getSolidLoadChargeMaterials();

    auto objs = Nan::New<v8::Array>();
    for (std::size_t i = 0; i < slcms.size(); i++)
    {
        auto const &slcm = slcms[i];
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

NAN_METHOD(selectSolidLoadChargeMaterialById)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
    Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
    Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
    Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

    Local<Object> obj = Nan::New<Object>();
    try
    {
        auto const slcm = sql->getSolidLoadChargeMaterialById(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
        Nan::Set(obj, id, Nan::New<Number>(slcm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
        Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(slcm.getSpecificHeatLiquid()));
        Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in selectSolidLoadChargeMaterialById - db.h: " + what).c_str());
    }

    info.GetReturnValue().Set(obj);
}

NAN_METHOD(insertSolidLoadChargeMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double specificHeatSolid = Get("specificHeatSolid");
    double specificHeatLiquid = Get("specificHeatLiquid");
    double latentHeat = Get("latentHeat");
    double meltingPoint = Get("meltingPoint");

    SolidLoadChargeMaterial slcm;
    slcm.setSubstance(substance);
    slcm.setSpecificHeatSolid(specificHeatSolid);
    slcm.setSpecificHeatLiquid(specificHeatLiquid);
    slcm.setLatentHeat(latentHeat);
    slcm.setMeltingPoint(meltingPoint);
    bool success = sql->insertSolidLoadChargeMaterials(slcm);

    info.GetReturnValue().Set(success);
}

NAN_METHOD(deleteSolidLoadChargeMaterial)
{
    bool success = sql->deleteSolidLoadChargeMaterial(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
    info.GetReturnValue().Set(success);
}

NAN_METHOD(updateSolidLoadChargeMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double specificHeatSolid = Get("specificHeatSolid");
    double specificHeatLiquid = Get("specificHeatLiquid");
    double latentHeat = Get("latentHeat");
    double meltingPoint = Get("meltingPoint");
    int id = (int)Get("id");

    SolidLoadChargeMaterial slcm;
    slcm.setSubstance(substance);
    slcm.setSpecificHeatSolid(specificHeatSolid);
    slcm.setSpecificHeatLiquid(specificHeatLiquid);
    slcm.setLatentHeat(latentHeat);
    slcm.setMeltingPoint(meltingPoint);
    slcm.setID(id);
    bool success = sql->updateSolidLoadChargeMaterial(slcm);

    info.GetReturnValue().Set(success);
}

NAN_METHOD(selectLiquidLoadChargeMaterials)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
    Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
    Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();
    Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();

    auto const llcms = sql->getLiquidLoadChargeMaterials();

    auto objs = Nan::New<v8::Array>();
    for (std::size_t i = 0; i < llcms.size(); i++)
    {
        auto const &llcm = llcms[i];
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

NAN_METHOD(insertLiquidLoadChargeMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    std::string substance = GetStr("substance");
    double specificHeatLiquid = Get("specificHeatLiquid");
    double specificHeatVapor = Get("specificHeatVapor");
    double vaporizationTemperature = Get("vaporizationTemperature");
    double latentHeat = Get("latentHeat");

    LiquidLoadChargeMaterial llcm;
    llcm.setSubstance(substance);
    llcm.setSpecificHeatLiquid(specificHeatLiquid);
    llcm.setSpecificHeatVapor(specificHeatVapor);
    llcm.setVaporizingTemperature(vaporizationTemperature);
    llcm.setLatentHeat(latentHeat);
    bool success = sql->insertLiquidLoadChargeMaterials(llcm);
    info.GetReturnValue().Set(success);
}

NAN_METHOD(deleteLiquidLoadChargeMaterial)
{
    bool success = sql->deleteLiquidLoadChargeMaterial(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
    info.GetReturnValue().Set(success);
}

NAN_METHOD(updateLiquidLoadChargeMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double specificHeatLiquid = Get("specificHeatLiquid");
    double specificHeatVapor = Get("specificHeatVapor");
    double vaporizationTemperature = Get("vaporizationTemperature");
    double latentHeat = Get("latentHeat");
    int id = (int)Get("id");

    LiquidLoadChargeMaterial llcm;
    llcm.setSubstance(substance);
    llcm.setSpecificHeatLiquid(specificHeatLiquid);
    llcm.setSpecificHeatVapor(specificHeatVapor);
    llcm.setVaporizingTemperature(vaporizationTemperature);
    llcm.setLatentHeat(latentHeat);
    llcm.setID(id);
    bool success = sql->updateLiquidLoadChargeMaterial(llcm);

    info.GetReturnValue().Set(success);
}

NAN_METHOD(selectLiquidLoadChargeMaterialById)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
    Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
    Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();
    Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();

    Local<Object> obj = Nan::New<Object>();
    try
    {
        auto const llcm = sql->getLiquidLoadChargeMaterialById(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
        Nan::Set(obj, id, Nan::New<Number>(llcm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(llcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(llcm.getSpecificHeatLiquid()));
        Nan::Set(obj, specificHeatVapor, Nan::New<Number>(llcm.getSpecificHeatVapor()));
        Nan::Set(obj, vaporizationTemperature, Nan::New<Number>(llcm.getVaporizingTemperature()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(llcm.getLatentHeat()));
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in selectLiquidLoadChargeMaterialById - db.h: " + what).c_str());
    }

    info.GetReturnValue().Set(obj);
}

NAN_METHOD(selectGasLoadChargeMaterials)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();

    auto const glcms = sql->getGasLoadChargeMaterials();

    auto objs = Nan::New<v8::Array>();
    for (std::size_t i = 0; i < glcms.size(); i++)
    {
        auto const &glcm = glcms[i];
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(glcm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(glcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatVapor, Nan::New<Number>(glcm.getSpecificHeatVapor()));
        Nan::Set(objs, i, obj);
    }

    info.GetReturnValue().Set(objs);
}

NAN_METHOD(insertGasLoadChargeMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    GasLoadChargeMaterial glcm;
    glcm.setSubstance(GetStr("substance"));
    glcm.setSpecificHeatVapor(Get("specificHeatVapor"));
    bool success = sql->insertGasLoadChargeMaterials(glcm);
    info.GetReturnValue().Set(success);
}

NAN_METHOD(deleteGasLoadChargeMaterial)
{
    bool success = sql->deleteGasLoadChargeMaterial(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
    info.GetReturnValue().Set(success);
}

NAN_METHOD(updateGasLoadChargeMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double specificHeatVapor = Get("specificHeatVapor");
    int id = (int)Get("id");

    GasLoadChargeMaterial glcm;
    glcm.setSubstance(substance);
    glcm.setSpecificHeatVapor(specificHeatVapor);
    glcm.setID(id);
    bool success = sql->updateGasLoadChargeMaterial(glcm);

    info.GetReturnValue().Set(success);
}

NAN_METHOD(selectGasLoadChargeMaterialById)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();

    Local<Object> obj = Nan::New<Object>();
    try
    {
        auto const glcm = sql->getGasLoadChargeMaterialById(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
        Nan::Set(obj, id, Nan::New<Number>(glcm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(glcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatVapor, Nan::New<Number>(glcm.getSpecificHeatVapor()));
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in selectGasLoadChargeMaterialById - db.h: " + what).c_str());
    }

    info.GetReturnValue().Set(obj);
}

NAN_METHOD(selectSolidLiquidFlueGasMaterials)
{
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
    for (std::size_t i = 0; i < fgMaterials.size(); i++)
    {
        auto const &fgm = fgMaterials[i];
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

NAN_METHOD(insertSolidLiquidFlueGasMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    double carbon = Get("carbon") * 100.0;
    double hydrogen = Get("hydrogen") * 100.0;
    double sulphur = Get("sulphur") * 100.0;
    double inertAsh = Get("inertAsh") * 100.0;
    double o2 = Get("o2") * 100.0;
    double moisture = Get("moisture") * 100.0;
    double nitrogen = Get("nitrogen") * 100.0;
    std::string substance = GetStr("substance");

    SolidLiquidFlueGasMaterial slfgm(0, 0, 0, 0, 0, 0, 0, carbon, hydrogen,
                                     sulphur, inertAsh, o2,
                                     moisture, nitrogen);
    slfgm.setSubstance(substance);
    bool success = sql->insertSolidLiquidFlueGasMaterial(slfgm);

    info.GetReturnValue().Set(success);
};

NAN_METHOD(deleteSolidLiquidFlueGasMaterial)
{
    bool success = sql->deleteSolidLiquidFlueGasMaterial(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
    info.GetReturnValue().Set(success);
};

NAN_METHOD(updateSolidLiquidFlueGasMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    double carbon = Get("carbon") * 100.0;
    double hydrogen = Get("hydrogen") * 100.0;
    double sulphur = Get("sulphur") * 100.0;
    double inertAsh = Get("inertAsh") * 100.0;
    double o2 = Get("o2") * 100.0;
    double moisture = Get("moisture") * 100.0;
    double nitrogen = Get("nitrogen") * 100.0;
    std::string substance = GetStr("substance");
    int id = (int)Get("id");

    SolidLiquidFlueGasMaterial slfgm(0, 0, 0, 0, 0, 0, 0, carbon, hydrogen,
                                     sulphur, inertAsh, o2,
                                     moisture, nitrogen);
    slfgm.setSubstance(substance);
    slfgm.setID(id);
    bool success = sql->updateSolidLiquidFlueGasMaterial(slfgm);

    info.GetReturnValue().Set(success);
};

NAN_METHOD(selectSolidLiquidFlueGasMaterialById)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> carbon = Nan::New<String>("carbon").ToLocalChecked();
    Local<String> hydrogen = Nan::New<String>("hydrogen").ToLocalChecked();
    Local<String> sulphur = Nan::New<String>("sulphur").ToLocalChecked();
    Local<String> inertAsh = Nan::New<String>("inertAsh").ToLocalChecked();
    Local<String> o2 = Nan::New<String>("o2").ToLocalChecked();
    Local<String> moisture = Nan::New<String>("moisture").ToLocalChecked();
    Local<String> nitrogen = Nan::New<String>("nitrogen").ToLocalChecked();

    Local<Object> obj = Nan::New<Object>();
    try
    {
        auto const fgm = sql->getSolidLiquidFlueGasMaterialById(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
        Nan::Set(obj, id, Nan::New<Number>(fgm.getID()));
        Nan::Set(obj, substance, Nan::New<String>(fgm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, carbon, Nan::New<Number>(fgm.getCarbon()));
        Nan::Set(obj, hydrogen, Nan::New<Number>(fgm.getHydrogen()));
        Nan::Set(obj, sulphur, Nan::New<Number>(fgm.getSulphur()));
        Nan::Set(obj, inertAsh, Nan::New<Number>(fgm.getInertAsh()));
        Nan::Set(obj, o2, Nan::New<Number>(fgm.getO2()));
        Nan::Set(obj, moisture, Nan::New<Number>(fgm.getMoisture()));
        Nan::Set(obj, nitrogen, Nan::New<Number>(fgm.getNitrogen()));
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in selectSolidLiquidFlueGasMaterialById - db.h: " + what).c_str());
    }

    info.GetReturnValue().Set(obj);
};

NAN_METHOD(selectGasFlueGasMaterials)
{
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
    Local<String> heatingValueVolume = Nan::New<String>("heatingValueVolume").ToLocalChecked();
    Local<String> specificGravity = Nan::New<String>("specificGravity").ToLocalChecked();

    auto const fgMaterials = sql->getGasFlueGasMaterials();

    auto objs = Nan::New<v8::Array>();
    for (std::size_t i = 0; i < fgMaterials.size(); i++)
    {
        auto const &fgm = fgMaterials[i];
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
        Nan::Set(obj, heatingValueVolume, Nan::New<Number>(fgm.getHeatingValueVolume()));
        Nan::Set(obj, specificGravity, Nan::New<Number>(fgm.getSpecificGravity()));
        Nan::Set(objs, i, obj);
    }

    info.GetReturnValue().Set(objs);
};

NAN_METHOD(insertGasFlueGasMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double CH4 = Get("CH4");
    double C2H6 = Get("C2H6");
    double N2 = Get("N2");
    double H2 = Get("H2");
    double C3H8 = Get("C3H8");
    double C4H10_CnH2n = Get("C4H10_CnH2n");
    double H2O = Get("H2O");
    double CO = Get("CO");
    double CO2 = Get("CO2");
    double SO2 = Get("SO2");
    double O2 = Get("O2");

    GasCompositions comp(substance, CH4, C2H6, N2, H2, C3H8,
                         C4H10_CnH2n, H2O, CO, CO2, SO2, O2);

    try
    {
        bool success = sql->insertGasFlueGasMaterial(comp);

        info.GetReturnValue().Set(success);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in insertGasFlueGasMaterial - db.h: " + what).c_str());
        info.GetReturnValue().Set(false);
    }
}

NAN_METHOD(deleteGasFlueGasMaterial)
{
    bool success = sql->deleteGasFlueGasMaterial(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
    info.GetReturnValue().Set(success);
}

NAN_METHOD(updateGasFlueGasMaterial)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double CH4 = Get("CH4");
    double C2H6 = Get("C2H6");
    double N2 = Get("N2");
    double H2 = Get("H2");
    double C3H8 = Get("C3H8");
    double C4H10_CnH2n = Get("C4H10_CnH2n");
    double H2O = Get("H2O");
    double CO = Get("CO");
    double CO2 = Get("CO2");
    double SO2 = Get("SO2");
    double O2 = Get("O2");
    int id = (int)Get("id");

    GasCompositions comp(substance, CH4, C2H6, N2, H2, C3H8,
                         C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    comp.setID(id);

    try
    {
        bool success = sql->updateGasFlueGasMaterial(comp);
        info.GetReturnValue().Set(success);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in updateGasFlueGasMaterial - db.h: " + what).c_str());
        info.GetReturnValue().Set(false);
    }
}

NAN_METHOD(selectGasFlueGasMaterialById)
{
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
    Local<String> heatingValueVolume = Nan::New<String>("heatingValueVolume").ToLocalChecked();
    Local<String> specificGravity = Nan::New<String>("specificGravity").ToLocalChecked();

    Local<Object> obj = Nan::New<Object>();
    try
    {
        auto const fgm = sql->getGasFlueGasMaterialById(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
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
        Nan::Set(obj, heatingValueVolume, Nan::New<Number>(fgm.getHeatingValueVolume()));
        Nan::Set(obj, specificGravity, Nan::New<Number>(fgm.getSpecificGravity()));
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in selectGasFlueGasMaterialById - db.h: " + what).c_str());
    }

    info.GetReturnValue().Set(obj);
};

NAN_METHOD(selectAtmosphereSpecificHeat)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeat = Nan::New<String>("specificHeat").ToLocalChecked();
    auto const aMaterials = sql->getAtmosphereSpecificHeat();

    auto objs = Nan::New<v8::Array>();
    for (std::size_t i = 0; i < aMaterials.size(); i++)
    {
        auto const ash = aMaterials[i];
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(ash.getID()));
        Nan::Set(obj, substance, Nan::New<String>(ash.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeat, Nan::New<Number>(ash.getSpecificHeat()));
        Nan::Set(objs, i, obj);
    }

    info.GetReturnValue().Set(objs);
};

NAN_METHOD(insertAtmosphereSpecificHeat)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double specificHeat = Get("specificHeat");

    Atmosphere atmos;
    atmos.setSubstance(substance);
    atmos.setSpecificHeat(specificHeat);
    bool success = sql->insertAtmosphereSpecificHeat(atmos);

    info.GetReturnValue().Set(success);
};

NAN_METHOD(deleteAtmosphereSpecificHeat)
{
    bool success = sql->deleteAtmosphereSpecificHeat(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
    info.GetReturnValue().Set(success);
};

NAN_METHOD(updateAtmosphereSpecificHeat)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string substance = GetStr("substance");
    double specificHeat = Get("specificHeat");
    int id = (int)Get("id");

    Atmosphere atmos;
    atmos.setSubstance(substance);
    atmos.setSpecificHeat(specificHeat);
    atmos.setID(id);
    bool success = sql->updateAtmosphereSpecificHeat(atmos);

    info.GetReturnValue().Set(success);
};

NAN_METHOD(selectAtmosphereSpecificHeatById)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
    Local<String> specificHeat = Nan::New<String>("specificHeat").ToLocalChecked();

    Local<Object> obj = Nan::New<Object>();
    try
    {
        auto const ash = sql->getAtmosphereSpecificHeatById(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
        Nan::Set(obj, id, Nan::New<Number>(ash.getID()));
        Nan::Set(obj, substance, Nan::New<String>(ash.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeat, Nan::New<Number>(ash.getSpecificHeat()));
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in selectAtmosphereSpecificHeatById - db.h: " + what).c_str());
    }

    info.GetReturnValue().Set(obj);
};

NAN_METHOD(selectWallLossesSurface)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> surface = Nan::New<String>("surface").ToLocalChecked();
    Local<String> conditionFactor = Nan::New<String>("conditionFactor").ToLocalChecked();
    auto const wlSurfaces = sql->getWallLossesSurface();

    auto objs = Nan::New<v8::Array>();
    for (std::size_t i = 0; i < wlSurfaces.size(); i++)
    {
        auto const &wls = wlSurfaces[i];
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, id, Nan::New<Number>(wls.getID()));
        Nan::Set(obj, surface, Nan::New<String>(wls.getSurface()).ToLocalChecked());
        Nan::Set(obj, conditionFactor, Nan::New<Number>(wls.getConditionFactor()));
        Nan::Set(objs, i, obj);
    }

    info.GetReturnValue().Set(objs);
};

NAN_METHOD(insertWallLossesSurface)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string surface = GetStr("surface");
    double conditionFactor = Get("conditionFactor");

    WallLosses wl;
    wl.setSurface(surface);
    wl.setConditionFactor(conditionFactor);
    bool success = sql->insertWallLossesSurface(wl);

    info.GetReturnValue().Set(success);
};

NAN_METHOD(deleteWallLossesSurface)
{
    bool success = sql->deleteWallLossesSurface(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
    info.GetReturnValue().Set(success);
};

NAN_METHOD(updateWallLossesSurface)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    std::string surface = GetStr("surface");
    double conditionFactor = Get("conditionFactor");
    int id = (int)Get("id");

    WallLosses wl;
    wl.setSurface(surface);
    wl.setConditionFactor(conditionFactor);
    wl.setID(id);
    bool success = sql->updateWallLossesSurface(wl);

    info.GetReturnValue().Set(success);
};

NAN_METHOD(selectWallLossesSurfaceById)
{
    Local<String> id = Nan::New<String>("id").ToLocalChecked();
    Local<String> surface = Nan::New<String>("surface").ToLocalChecked();
    Local<String> conditionFactor = Nan::New<String>("conditionFactor").ToLocalChecked();

    Local<Object> obj = Nan::New<Object>();
    try
    {
        auto const wls = sql->getWallLossesSurfaceById(static_cast<int>(Nan::To<double>(info[0]).FromJust()));
        Nan::Set(obj, id, Nan::New<Number>(wls.getID()));
        Nan::Set(obj, surface, Nan::New<String>(wls.getSurface()).ToLocalChecked());
        Nan::Set(obj, conditionFactor, Nan::New<Number>(wls.getConditionFactor()));
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in selectWallLossesSurfaceById - db.h: " + what).c_str());
    }

    info.GetReturnValue().Set(obj);
};

#endif //AMO_TOOLS_SUITE_DB_H
