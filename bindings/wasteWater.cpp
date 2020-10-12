#include <nan.h>
#include "wasteWater.h"

using namespace Nan;

NAN_MODULE_INIT(InitWasteWater) {
	Nan::Set(target, New<String>("WasteWaterTreatment").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(WasteWaterTreatment)).ToLocalChecked());
}

NODE_MODULE(wasteWater, InitWasteWater)