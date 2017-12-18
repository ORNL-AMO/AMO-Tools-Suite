#include <nan.h>
#include "standalone.h"

using namespace Nan;

NAN_MODULE_INIT(InitStandalone) {
	Nan::Set(target, New<String>("CHPcalculator").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(CHPcalculator)).ToLocalChecked());

	Nan::Set(target, New<String>("pneumaticAirRequirement").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(pneumaticAirRequirement)).ToLocalChecked());

	Nan::Set(target, New<String>("receiverTank").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(receiverTank)).ToLocalChecked());
}

NODE_MODULE(standalone, InitStandalone)