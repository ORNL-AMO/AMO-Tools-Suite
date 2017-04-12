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

    Nan::Set(target, New<String>("selectFlueGasMaterialSolid").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialSolid)).ToLocalChecked());

    Nan::Set(target, New<String>("selectFlueGasMaterialSolidById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialSolidById)).ToLocalChecked());

    Nan::Set(target, New<String>("selectFlueGasMaterialLiquidGas").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialLiquidGas)).ToLocalChecked());

    Nan::Set(target, New<String>("selectFlueGasMaterialLiquidGasById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectFlueGasMaterialLiquidGasById)).ToLocalChecked());
}

