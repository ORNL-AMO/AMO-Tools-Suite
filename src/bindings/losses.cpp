#include <nan.h>
using namespace Nan;
using namespace v8;

#include "calculator/WallLosses.h"

/**
  * Wall Losses Arguments
  * @param surfaceArea double
  * @param ambientTemperature double
  * @param surfaceTemperature double
  * @param windVelocity double
  * @param surfaceEmissivity double
  * @param conditionFactor double
  * @param correctionFactor double
  * @return heatLoss double
  */

NAN_METHOD(wallLosses) {
    double surfaceArea = info[0]->NumberValue();
    double ambientTemperature = info[1]->NumberValue();
    double surfaceTemperature = info[2]->NumberValue();
    double windVelocity = info[3]->NumberValue();
    double surfaceEmissivity = info[4]->NumberValue();
    double conditionFactor = info[5]->NumberValue();
    double correctionFactor = info[6]->NumberValue();
    WallLosses wl(surfaceArea, ambientTemperature, surfaceTemperature, windVelocity, surfaceEmissivity, conditionFactor, correctionFactor);
    double heatLoss = wl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_MODULE_INIT(InitializeLosses) {
    Nan::Set(target, New<String>("wallLosses").ToLocalChecked(), GetFunction(New<FunctionTemplate>(wallLosses)).ToLocalChecked());
}

NODE_MODULE(losses, InitializeLosses)