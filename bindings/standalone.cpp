#include <nan.h>
#include "standalone.h"

using namespace Nan;

NAN_MODULE_INIT(InitStandalone) {
	Nan::Set(target, New<String>("CHPcalculator").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(CHPcalculator)).ToLocalChecked());
}

NODE_MODULE(standalone, InitStandalone)