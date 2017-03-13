
#include <nan.h>
#include "psat-bridge.h"

using namespace Nan;

NAN_MODULE_INIT(InitPsat) {

    // PSAT
    Nan::Set(target, New<String>("achievableEfficiency").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(achievableEfficiency)).ToLocalChecked());

}

NODE_MODULE(psat, InitPsat)