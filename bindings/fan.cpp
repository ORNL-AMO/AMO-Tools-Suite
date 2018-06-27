
#include <nan.h>
#include "fan.h"

using namespace Nan;

NAN_MODULE_INIT(InitFans) {

	Nan::Set(target, New<String>("fanResultsExisting").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fanResultsExisting)).ToLocalChecked());

	Nan::Set(target, New<String>("fanResultsModified").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fanResultsModified)).ToLocalChecked());

	Nan::Set(target, New<String>("fanResultsOptimal").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fanResultsOptimal)).ToLocalChecked());

	Nan::Set(target, New<String>("fan203").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fan203)).ToLocalChecked());

	Nan::Set(target, New<String>("getBaseGasDensityRelativeHumidity").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(getBaseGasDensityRelativeHumidity)).ToLocalChecked());

	Nan::Set(target, New<String>("getBaseGasDensityDewPoint").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(getBaseGasDensityDewPoint)).ToLocalChecked());

	Nan::Set(target, New<String>("getBaseGasDensityWetBulb").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(getBaseGasDensityWetBulb)).ToLocalChecked());

	Nan::Set(target, New<String>("getVelocityPressureData").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(getVelocityPressureData)).ToLocalChecked());

	Nan::Set(target, New<String>("getPlaneResults").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(getPlaneResults)).ToLocalChecked());

	Nan::Set(target, New<String>("fanCurve").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(fanCurve)).ToLocalChecked());

	Nan::Set(target, New<String>("optimalFanEfficiency").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(optimalFanEfficiency)).ToLocalChecked());
}

NODE_MODULE(fan, InitFans)
