#include <nan.h>
#include "compressorsCalc.h"

using namespace Nan;

NAN_MODULE_INIT(InitCompressorsCalc) {
    Nan::Set(target, New<String>("CompressorsCalc").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompressorsCalc)).ToLocalChecked());

    Nan::Set(target, New<String>("CompEEM_ReduceAirLeaks").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompEEM_ReduceAirLeaks)).ToLocalChecked());

    Nan::Set(target, New<String>("CompEEM_ImproveEndUseEfficiency").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompEEM_ImproveEndUseEfficiency)).ToLocalChecked());

    Nan::Set(target, New<String>("CompEEM_ReduceSystemAirPressure").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompEEM_ReduceSystemAirPressure)).ToLocalChecked());

    Nan::Set(target, New<String>("CompEEM_AdjustCascadingSetPoint").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(CompEEM_AdjustCascadingSetPoint)).ToLocalChecked());

    Nan::Set(target, New<String>("CompEEM_PressureReductionSaving").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompEEM_PressureReductionSaving)).ToLocalChecked());

    Nan::Set(target, New<String>("CompEEM_kWAdjusted").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(CompEEM_kWAdjusted)).ToLocalChecked());
}

NODE_MODULE(compressorsCalc, InitCompressorsCalc)