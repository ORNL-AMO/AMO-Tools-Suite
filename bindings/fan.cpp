
#include <nan.h>
#include "fan.h"

using namespace Nan;

NAN_MODULE_INIT(InitFans) {

	Nan::Set(target, New<String>("fanPlaceholder").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fanPlaceholder)).ToLocalChecked());

	Nan::Set(target, New<String>("fanCurve").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fanCurve)).ToLocalChecked());

}

NODE_MODULE(fan, InitFans)
