#include <nan.h>
#include "chillers.h"

using namespace Nan;

NAN_MODULE_INIT(InitChillers) {
    Nan::Set(target, New<String>("coolingTowerMakeupWater").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(coolingTowerMakeupWater)).ToLocalChecked());
}

NODE_MODULE(chillers, InitChillers)
