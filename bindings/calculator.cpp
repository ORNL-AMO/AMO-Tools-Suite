#include <nan.h>
#include "calculator.h"

using namespace Nan;

NAN_MODULE_INIT(InitCalculator) {
    Nan::Set(target, New<String>("electricityReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(electricityReduction)).ToLocalChecked());
}

NODE_MODULE(calculator, InitCalculator)