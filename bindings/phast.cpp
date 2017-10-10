
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

    Nan::Set(target, New<String>("energyInputEAF").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(energyInputEAF)).ToLocalChecked());

    Nan::Set(target, New<String>("energyInputExhaustGasLosses").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(energyInputExhaustGasLosses)).ToLocalChecked());

    Nan::Set(target, New<String>("exhaustGasEAF").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(exhaustGasEAF)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasLossesByVolume").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasLossesByVolume)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasByVolumeCalculateHeatingValue").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasByVolumeCalculateHeatingValue)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasLossesByVolumeGivenO2").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasLossesByVolumeGivenO2)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasLossesByMass").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasLossesByMass)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasByMassCalculateHeatingValue").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasByMassCalculateHeatingValue)).ToLocalChecked());

    Nan::Set(target, New<String>("flueGasLossesByMassGivenO2").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flueGasLossesByMassGivenO2)).ToLocalChecked());

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

    Nan::Set(target, New<String>("efficiencyImprovement").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(efficiencyImprovement)).ToLocalChecked());

    Nan::Set(target, New<String>("energyEquivalencyElectric").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(energyEquivalencyElectric)).ToLocalChecked());

    Nan::Set(target, New<String>("energyEquivalencyFuel").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(energyEquivalencyFuel)).ToLocalChecked());

    Nan::Set(target, New<String>("flowCalculations").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(flowCalculations)).ToLocalChecked());

    Nan::Set(target, New<String>("o2Enrichment").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(o2Enrichment)).ToLocalChecked());

    Nan::Set(target, New<String>("availableHeat").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(availableHeat)).ToLocalChecked());

    Nan::Set(target, New<String>("humidityRatio").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(humidityRatio)).ToLocalChecked());

}

NODE_MODULE(phast, InitPhast)
