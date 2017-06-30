
#include <nan.h>
#include "phast.h"

using namespace Nan;

NAN_MODULE_INIT(InitPhast) {

    // PHAST Losses
    Nan::Set(target, New<String>("atmosphere").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(atmosphere)).ToLocalChecked());

    Nan::Set(target, New<String>("auxiliaryPowerLoss").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(auxiliaryPowerLoss)).ToLocalChecked());

    Nan::Set(target, New<String>("fixtureLosses").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(fixtureLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("energyInput").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(energyInput)).ToLocalChecked());

    Nan::Set(target, New<String>("exhaustGas").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(exhaustGas)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasLossesByVolume").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasLossesByVolume)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasLossesByMass").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasLossesByMass)).ToLocalChecked());

    Nan::Set(target, New<String>("gasCoolingLosses").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(gasCoolingLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("gasLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(gasLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("leakageLosses").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(leakageLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("liquidCoolingLosses").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(liquidCoolingLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("liquidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(liquidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("openingLossesCircular").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(openingLossesCircular)).ToLocalChecked());

    Nan::Set(target, New<String>("openingLossesQuad").ToLocalChecked(),
    GetFunction(New<FunctionTemplate>(openingLossesQuad)).ToLocalChecked());

        Nan::Set(target, New<String>("slagOtherMaterialLosses").ToLocalChecked(),
        GetFunction(New<FunctionTemplate>(slagOtherMaterialLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("solidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(solidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("wallLosses").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(wallLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("waterCoolingLosses").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(waterCoolingLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("initTest").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(initTest)).ToLocalChecked());


    // Furnace calculators

    Nan::Set(target, New<String>("efficiencyImprovement").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(efficiencyImprovement)).ToLocalChecked());

    Nan::Set(target, New<String>("energyEquivalencyElectric").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(energyEquivalencyElectric)).ToLocalChecked());

    Nan::Set(target, New<String>("energyEquivalencyFuel").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(energyEquivalencyFuel)).ToLocalChecked());

    Nan::Set(target, New<String>("o2Enrichment").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(o2Enrichment)).ToLocalChecked());

}

NODE_MODULE(phast, InitPhast)
