#include <nan.h>
#include "standalone.h"

using namespace Nan;

NAN_MODULE_INIT(InitStandalone) {
	Nan::Set(target, New<String>("CHPcalculator").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(CHPcalculator)).ToLocalChecked());

	Nan::Set(target, New<String>("pneumaticAirRequirement").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(pneumaticAirRequirement)).ToLocalChecked());
	
	Nan::Set(target, New<String>("usableAirCapacity").ToLocalChecked(),
			 GetFunction(New<FunctionTemplate>(usableAirCapacity)).ToLocalChecked());

	Nan::Set(target, New<String>("receiverTank").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(receiverTank)).ToLocalChecked());

	Nan::Set(target, New<String>("operatingCost").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(operatingCost)).ToLocalChecked());

	Nan::Set(target, New<String>("airSystemCapacity").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(airSystemCapacity)).ToLocalChecked());

	Nan::Set(target, New<String>("airVelocity").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(airVelocity)).ToLocalChecked());

	Nan::Set(target, New<String>("pipeSizing").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(pipeSizing)).ToLocalChecked());

	Nan::Set(target, New<String>("pneumaticValve").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(pneumaticValve)).ToLocalChecked());

	Nan::Set(target, New<String>("bagMethod").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(bagMethod)).ToLocalChecked());
}

NODE_MODULE(standalone, InitStandalone)