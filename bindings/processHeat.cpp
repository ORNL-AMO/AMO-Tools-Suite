#include <nan.h>
#include "processHeat.h"

using namespace Nan;

NAN_MODULE_INIT(InitProcessHeat) {
    Nan::Set(target, New<String>("airHeatingUsingExhaust").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(airHeatingUsingExhaust)).ToLocalChecked());

    Nan::Set(target, New<String>("waterHeatingUsingExhaust").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(waterHeatingUsingExhaust)).ToLocalChecked());

    Nan::Set(target, New<String>("waterHeatingUsingSteam").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(waterHeatingUsingSteam)).ToLocalChecked());

    Nan::Set(target, New<String>("cascadeHeatHighToLow").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(cascadeHeatHighToLow)).ToLocalChecked());

    Nan::Set(target, New<String>("waterHeatingUsingFlue").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(waterHeatingUsingFlue)).ToLocalChecked());
}

NODE_MODULE(processHeat, InitProcessHeat)