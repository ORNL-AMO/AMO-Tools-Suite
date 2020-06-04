#include <nan.h>
#include "calculator.h"

using namespace Nan;

NAN_MODULE_INIT(InitCalculator)
{
    Nan::Set(target, New<String>("electricityReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(electricityReduction)).ToLocalChecked());

    Nan::Set(target, New<String>("naturalGasReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(naturalGasReduction)).ToLocalChecked());

    Nan::Set(target, New<String>("compressedAirReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(compressedAirReduction)).ToLocalChecked());

    Nan::Set(target, New<String>("compressedAirLeakSurvey").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(compressedAirLeakSurvey)).ToLocalChecked());

    Nan::Set(target, New<String>("compressedAirPressureReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(compressedAirPressureReduction)).ToLocalChecked());

    Nan::Set(target, New<String>("waterReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(waterReduction)).ToLocalChecked());

    Nan::Set(target, New<String>("pipeInsulationReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(pipeInsulationReduction)).ToLocalChecked());

    Nan::Set(target, New<String>("tankInsulationReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(tankInsulationReduction)).ToLocalChecked());

    Nan::Set(target, New<String>("steamReduction").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(steamReduction)).ToLocalChecked());
}

NODE_MODULE(calculator, InitCalculator)