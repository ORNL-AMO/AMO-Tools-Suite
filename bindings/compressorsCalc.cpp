#include <nan.h>
#include "compressorsCalc.h"

using namespace Nan;

NAN_MODULE_INIT(InitCompressorsCalc) {
    Nan::Set(target, New<String>("CompressorsCalc").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompressorsCalc)).ToLocalChecked());
}

NODE_MODULE(compressorsCalc, InitCompressorsCalc)