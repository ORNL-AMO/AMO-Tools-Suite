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
             GetFunction(New<FunctionTemplate>(selectSolidMaterial)).ToLocalChecked());

}

