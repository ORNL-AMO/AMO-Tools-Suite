//
// Created by Accawi, Gina K. on 3/13/17.
//
#include <nan.h>
#include "db.h"

using namespace Nan;

NAN_MODULE_INIT(InitDb) {

    // PHAST
    Nan::Set(target, New<String>("selectSolidMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectLiquidMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectLiquidMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectLiquidMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectLiquidMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectFlueGasMaterialSolidLiquid").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialSolidLiquid)).ToLocalChecked());

    Nan::Set(target, New<String>("selectFlueGasMaterialSolidLiquidById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialSolidLiquidById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectFlueGasMaterialGas").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialGas)).ToLocalChecked());

    Nan::Set(target, New<String>("selectFlueGasMaterialGasById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialGasById)).ToLocalChecked());
}

