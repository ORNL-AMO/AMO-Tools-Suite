#include <nan.h>
#include "chillers.h"

using namespace Nan;

NAN_MODULE_INIT(InitChillers) {
    Nan::Set(target, New<String>("coolingTowerMakeupWater").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(coolingTowerMakeupWater)).ToLocalChecked());

    Nan::Set(target, New<String>("coolingTowerBasinHeaterEnergyConsumption").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(coolingTowerBasinHeaterEnergyConsumption)).ToLocalChecked());

    Nan::Set(target, New<String>("coolingTowerFanEnergyConsumption").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(coolingTowerFanEnergyConsumption)).ToLocalChecked());

    Nan::Set(target, New<String>("chillerCapacityEfficiency").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(chillerCapacityEfficiency)).ToLocalChecked());

    Nan::Set(target, New<String>("chillerStaging").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(chillerStaging)).ToLocalChecked());
}

NODE_MODULE(chillers, InitChillers)
