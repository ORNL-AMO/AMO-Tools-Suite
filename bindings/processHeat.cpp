#include <nan.h>
#include "processHeat.h"

using namespace Nan;

NAN_MODULE_INIT(InitProcessHeat) {
    Nan::Set(target, New<String>("airHeatingUsingExhaust").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(airHeatingUsingExhaust)).ToLocalChecked());
}

NODE_MODULE(processHeat, InitProcessHeat)