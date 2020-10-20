#include <nan.h>
#include "caCentrifugal.h"

using namespace Nan;

NAN_MODULE_INIT(InitCACentrifugal) {
    Nan::Set(target, New<String>("CompressedAirCentrifugal").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompressedAirCentrifugal)).ToLocalChecked());
}

NODE_MODULE(caCentrifugal, InitCACentrifugal)