//
// Created by Accawi, Gina K. on 3/13/17.
//

#ifndef AMO_TOOLS_SUITE_DB_H
#define AMO_TOOLS_SUITE_DB_H
#include <nan.h>
#include <node.h>
#include <sqlite/SQLite.h>
#include <fstream>
#include <memory>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>

using namespace Nan;
using namespace v8;

std::unique_ptr<SQLite> sql;

    NAN_METHOD(startup) {
	    std::string dbName = "amo-tools-suite.db";
	    std::ifstream f(dbName.c_str());
	    sql = std::unique_ptr<SQLite>(new SQLite(dbName, !f.good()));
    }

    NAN_METHOD(update) {
//        db migration code goes here
    }

    NAN_METHOD(selectSolidMaterial) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

        auto const slcms = sql->getSolidLoadChargeMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( size_t i = 0; i < slcms.size(); i++ ) {
            auto const slcm = slcms[i];
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()).ToLocalChecked());
            Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
            Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
            Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(slcm.getSpecificHeatLiquid()));
            Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));
	        Nan::Set(objs, i, obj);
        }

        info.GetReturnValue().Set(objs);
    }

    NAN_METHOD(selectSolidMaterialById) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

	    auto const slcm = sql->getSolidLoadChargeMaterial(1);

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
        Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(slcm.getSpecificHeatLiquid()));
        Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));

        info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(selectLiquidMaterial) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
        Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();

        auto const llcms = sql->getLiquidLoadChargeMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( size_t i = 0; i < llcms.size(); i++ ) {
	        auto const llcm = llcms[i];
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, substance, Nan::New<String>(llcm.getSubstance()).ToLocalChecked());
            Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(llcm.getSpecificHeatLiquid()));
            Nan::Set(obj, specificHeatVapor, Nan::New<Number>(llcm.getSpecificHeatVapor()));
            Nan::Set(obj, vaporizationTemperature, Nan::New<Number>(llcm.getVaporizingTemperature()));
            Nan::Set(obj, latentHeat, Nan::New<Number>(llcm.getLatentHeat()));
            Nan::Set(objs, i, obj);
        }

        info.GetReturnValue().Set(objs);
    }

    NAN_METHOD(selectLiquidMaterialById) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
        Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();

        auto const llcm = sql->getLiquidLoadChargeMaterial(1);

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, substance, Nan::New<String>(llcm.getSubstance()).ToLocalChecked());
        Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(llcm.getSpecificHeatLiquid()));
        Nan::Set(obj, specificHeatVapor, Nan::New<Number>(llcm.getSpecificHeatVapor()));
        Nan::Set(obj, vaporizationTemperature, Nan::New<Number>(llcm.getVaporizingTemperature()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(llcm.getLatentHeat()));

        info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(selectGasMaterial) {
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
    }
    NAN_METHOD(selectGasMaterialById) {
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
    }
    NAN_METHOD(selectFlueGasMaterialSolidLiquid) {
        Local<Object> obj = Nan::New<Object>();
        info.GetReturnValue().Set(obj);
    };
    NAN_METHOD(selectFlueGasMaterialSolidLiquidById) {
        Local<Object> obj = Nan::New<Object>();
        info.GetReturnValue().Set(obj);
    };
    NAN_METHOD(selectFlueGasMaterialGas) {
        Local<Object> obj = Nan::New<Object>();
        info.GetReturnValue().Set(obj);
    };
    NAN_METHOD(selectFlueGasMaterialGasById) {
        Local<Object> obj = Nan::New<Object>();
        info.GetReturnValue().Set(obj);
    };


#endif //AMO_TOOLS_SUITE_DB_H
