#include <nan.h>
#include "standalone.h"

using namespace Nan;

NAN_MODULE_INIT(InitStandalone) {
	Nan::Set(target, New<String>("CHP").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(CHP)).ToLocalChecked());
}

NODE_MODULE(standalone, InitStandalone)