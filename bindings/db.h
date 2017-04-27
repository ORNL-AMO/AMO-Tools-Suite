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
    NAN_METHOD(selectSolidMaterial) {
        Local<String> substance = Nan::New<String>("substance").ToLocalChecked();
        Local<String> specificHeatSolid = Nan::New<String>("specificHeatSolid").ToLocalChecked();
        Local<String> latentHeat = Nan::New<String>("latentHeat").ToLocalChecked();
        Local<String> meltingPoint = Nan::New<String>("meltingPoint").ToLocalChecked();

	    // TODO database name?
        SQLite sql("DB_Name?", true);
	    // TODO this is a vector of SolidLoadChargeMaterial objects ?
        auto const & slcms = sql.getSolidLoadChargeMaterials();

        for ( auto const & slcm : slcms) {
             // TODO ?
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
        SQLite sql("DB_Name?", true);
	    int id = 0; // TODO what id ?
        SolidLoadChargeMaterial const & slcm = sql.getSolidLoadChargeMaterial(id);

        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, substance, Nan::New<String>(slcm.getSubstance()));
        Nan::Set(obj, specificHeatSolid, Nan::New<Number>(slcm.getSpecificHeatSolid()));
        Nan::Set(obj, latentHeat, Nan::New<Number>(slcm.getLatentHeat()));
        Nan::Set(obj, meltingPoint, Nan::New<Number>(slcm.getMeltingPoint()));

        info.GetReturnValue().Set(obj);
    }

    NAN_METHOD(selectLiquidMaterial) {
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
    }
    NAN_METHOD(selectLiquidMaterialById) {
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
