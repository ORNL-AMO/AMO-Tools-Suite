//
// Created by qkf on 7/28/2017.
//

#include <nan.h>
#include "ssmt.h"

using namespace Nan;

NAN_MODULE_INIT(InitSsmt) {
    Nan::Set(target, New<String>("saturatedPressure").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(saturatedPressure)).ToLocalChecked());

    Nan::Set(target, New<String>("saturatedTemperature").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(saturatedTemperature)).ToLocalChecked());

    Nan::Set(target, New<String>("saturatedPropertiesGivenPressure").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(saturatedPropertiesGivenPressure)).ToLocalChecked());

    Nan::Set(target, New<String>("saturatedPropertiesGivenTemperature").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(saturatedPropertiesGivenTemperature)).ToLocalChecked());

    Nan::Set(target, New<String>("steamProperties").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(steamProperties)).ToLocalChecked());

    Nan::Set(target, New<String>("boiler").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(boiler)).ToLocalChecked());

    Nan::Set(target, New<String>("heatLoss").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(heatLoss)).ToLocalChecked());

    Nan::Set(target, New<String>("flashTank").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(flashTank)).ToLocalChecked());

    Nan::Set(target, New<String>("deaerator").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deaerator)).ToLocalChecked());

}

NODE_MODULE(ssmt, InitSsmt)