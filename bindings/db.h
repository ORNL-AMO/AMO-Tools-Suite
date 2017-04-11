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
    NAN_METHOD(selectGasßMaterialById) {
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
    }

};


#endif //AMO_TOOLS_SUITE_DB_H
