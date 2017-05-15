//
// Created by Accawi, Gina K. on 3/13/17.
//

#ifndef AMO_TOOLS_SUITE_DB_H
#define AMO_TOOLS_SUITE_DB_H
#include <nan.h>
#include <node.h>
#include <sqlite/SQLite.h>

using namespace Nan;
using namespace v8;



class db {
    NAN_METHOD(startup) {
//	    std::string dbName = info[0]->
    }

    NAN_METHOD(update) {
//        std::string
    }

    NAN_METHOD(selectSolidMaterial) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

	    // TODO database name?
//        SQLite sql("DB_Name?", true);
        auto const & slcms = sql.getSolidLoadChargeMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( auto const & slcm : slcms) {
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()));
            Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
            Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
            Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));
	        Nan::Set(objs, sclm, obj); // TODO this is probably not correct
        }

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()));
        Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
        Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));

        info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(selectSolidMaterialById) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

        // TODO
//        SQLite sql("DB_Name?", true);
	    int id = 0; // TODO id comes in as an argument, info[0]->NumberValueSomething()
        SolidLoadChargeMaterial const & slcm = sql.getSolidLoadChargeMaterial(id);

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()));
        Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
        Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));

        info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(selectLiquidMaterial) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();

//        SQLite sql("DB_Name?", true);
        auto const & llcms = sql.getLiquidLoadChargeMaterials();

        auto objs = Nan::New<v8::Array>();
        for ( auto const & llcm : llcms ) {
            Local<Object> obj = Nan::New<Object>();
            Nan::Set(obj, substance, Nan::New<String>(llcm.getSubstance()));
            Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(llcm.getSpecificHeatLiquid()));
            Nan::Set(obj, specificHeatVapor, Nan::New<Number>(llcm.getSpecificHeatVapor()));
            Nan::Set(obj, latentHeat, Nan::New<Number>(llcm.getLatentHeat()));
            Nan::Set(obj, vaporizationTemperature, Nan::New<Number>(llcm.getVaporizationTemperature()));
            Nan::Set(objs, sclm, obj); // TODO this is probably not correct
        }

        info.GetReturnValue().Set(objs);
    }

    NAN_METHOD(selectLiquidMaterialById) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatLiquid = Nan::New<String>("specificHeatLiquid").ToLocalChecked();
        Local<String> specificHeatVapor = Nan::New<String>("specificHeatVapor").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> vaporizationTemperature = Nan::New<String>("vaporizationTemperature").ToLocalChecked();

        SQLite sql("DB_Name?", true);
	    int id = 0;
        auto const & llcm = sql.getLiquidLoadChargeMaterial();

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, substance, Nan::New<String>(llcm.getSubstance()));
        Nan::Set(obj, specificHeatLiquid, Nan::New<Number>(llcm.getSpecificHeatLiquid()));
        Nan::Set(obj, specificHeatVapor, Nan::New<Number>(llcm.getSpecificHeatVapor()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(llcm.getLatentHeat()));
        Nan::Set(obj, vaporizationTemperature, Nan::New<Number>(llcm.getVaporizationTemperature()));
        objs.push_back(obj);

        info.GetReturnValue().Set(objs);
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
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
};


#endif //AMO_TOOLS_SUITE_DB_H
