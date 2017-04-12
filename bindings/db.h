//
// Created by Accawi, Gina K. on 3/13/17.
//

#ifndef AMO_TOOLS_SUITE_DB_H
#define AMO_TOOLS_SUITE_DB_H
#include <nan.h>
#include <node.h>

using namespace Nan;
using namespace v8;



class db {
    NAN_METHOD(selectSolidMaterial) {
            Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
            info.GetReturnValue().Set(temp);
    }
    NAN_METHOD(selectSolidMaterialById) {
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
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
