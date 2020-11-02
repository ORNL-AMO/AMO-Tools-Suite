#include <nan.h>
#include "compressedAir.h"

using namespace Nan;

NAN_MODULE_INIT(InitCompressedAir) {
    Nan::Set(target, New<String>("CompressedAir").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompressedAir)).ToLocalChecked());
}

NODE_MODULE(compressedAir, InitCompressedAir)