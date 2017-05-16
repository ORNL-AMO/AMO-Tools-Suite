
#include <nan.h>
#include "psat.h"

using namespace Nan;

NAN_MODULE_INIT(InitPsat) {

    // PSAT
    Nan::Set(target, New<String>("achievableEfficiency").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(achievableEfficiency)).ToLocalChecked());

    Nan::Set(target, New<String>("estFLA").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(estFLA)).ToLocalChecked());

    Nan::Set(target, New<String>("headToolSuctionTank").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(headToolSuctionTank)).ToLocalChecked());

    Nan::Set(target, New<String>("headTool").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(headTool)).ToLocalChecked());

    Nan::Set(target, New<String>("motorPerformance").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(motorPerformance)).ToLocalChecked());

    Nan::Set(target, New<String>("nema").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(nema)).ToLocalChecked());

    Nan::Set(target, New<String>("pumpEfficiency").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(pumpEfficiency)).ToLocalChecked());

    Nan::Set(target, New<String>("results").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(results)).ToLocalChecked());

}

NODE_MODULE(psat, InitPsat)