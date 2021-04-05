#include <nan.h>
#include "svi.h"

using namespace Nan;

NAN_MODULE_INIT(InitSludgeVolumeIndex) {
    Nan::Set(target, New<String>("svi").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(svi)).ToLocalChecked());
}

NODE_MODULE(svi, InitSludgeVolumeIndex)