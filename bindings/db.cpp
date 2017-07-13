//
// Created by Accawi, Gina K. on 3/13/17.
//
#include <nan.h>
#include "db.h"

using namespace Nan;

NAN_MODULE_INIT(InitDb) {

    // PHAST
    Nan::Set(target, New<String>("startup").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(startup)).ToLocalChecked());

    Nan::Set(target, New<String>("update").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(update)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLoadChargeMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLoadChargeMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLoadChargeMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLoadChargeMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectLiquidLoadChargeMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectLiquidLoadChargeMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectLiquidLoadChargeMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectLiquidLoadChargeMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasLoadChargeMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasLoadChargeMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasLoadChargeMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasLoadChargeMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLiquidFlueGasMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLiquidFlueGasMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLiquidFlueGasMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLiquidFlueGasMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasFlueGasMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasFlueGasMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasFlueGasMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasFlueGasMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectAtmosphereSpecificHeat").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectAtmosphereSpecificHeat)).ToLocalChecked());

    Nan::Set(target, New<String>("selectAtmosphereSpecificHeatById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectAtmosphereSpecificHeatById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectWallLossesSurface").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectWallLossesSurface)).ToLocalChecked());

    Nan::Set(target, New<String>("selectWallLossesSurfaceById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectWallLossesSurfaceById)).ToLocalChecked());
}

NODE_MODULE(db, InitDb)
