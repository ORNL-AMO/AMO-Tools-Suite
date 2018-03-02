
#include <nan.h>
#include "fan.h"

using namespace Nan;

NAN_MODULE_INIT(InitFans) {

	Nan::Set(target, New<String>("fan203").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fan203)).ToLocalChecked());

    Nan::Set(target, New<String>("getBaseGasDensity").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(getBaseGasDensity)).ToLocalChecked());

	Nan::Set(target, New<String>("getVelocityPressureData").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(getVelocityPressureData)).ToLocalChecked());


	Nan::Set(target, New<String>("fanCurve").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fanCurve)).ToLocalChecked());

}

NODE_MODULE(fan, InitFans)
