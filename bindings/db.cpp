#include <nan.h>
#include "db.h"

using namespace Nan;

NAN_MODULE_INIT(InitDb) {

    // PHAST
    Nan::Set(target, New<String>("startup").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(startup)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLoadChargeMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLoadChargeMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLoadChargeMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLoadChargeMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("insertSolidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(insertSolidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteSolidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteSolidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("updateSolidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateSolidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectLiquidLoadChargeMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectLiquidLoadChargeMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectLiquidLoadChargeMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectLiquidLoadChargeMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("insertLiquidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(insertLiquidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteLiquidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteLiquidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("updateLiquidLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateLiquidLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasLoadChargeMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasLoadChargeMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasLoadChargeMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasLoadChargeMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("insertGasLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(insertGasLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteGasLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteGasLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("updateGasLoadChargeMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateGasLoadChargeMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLiquidFlueGasMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLiquidFlueGasMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectSolidLiquidFlueGasMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectSolidLiquidFlueGasMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("insertSolidLiquidFlueGasMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(insertSolidLiquidFlueGasMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteSolidLiquidFlueGasMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteSolidLiquidFlueGasMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("updateSolidLiquidFlueGasMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateSolidLiquidFlueGasMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasFlueGasMaterials").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasFlueGasMaterials)).ToLocalChecked());

    Nan::Set(target, New<String>("selectGasFlueGasMaterialById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectGasFlueGasMaterialById)).ToLocalChecked());

    Nan::Set(target, New<String>("insertGasFlueGasMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(insertGasFlueGasMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteGasFlueGasMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteGasFlueGasMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("updateGasFlueGasMaterial").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateGasFlueGasMaterial)).ToLocalChecked());

    Nan::Set(target, New<String>("selectAtmosphereSpecificHeat").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectAtmosphereSpecificHeat)).ToLocalChecked());

    Nan::Set(target, New<String>("selectAtmosphereSpecificHeatById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectAtmosphereSpecificHeatById)).ToLocalChecked());

    Nan::Set(target, New<String>("insertAtmosphereSpecificHeat").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(insertAtmosphereSpecificHeat)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteAtmosphereSpecificHeat").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteAtmosphereSpecificHeat)).ToLocalChecked());

    Nan::Set(target, New<String>("updateAtmosphereSpecificHeat").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateAtmosphereSpecificHeat)).ToLocalChecked());

    Nan::Set(target, New<String>("selectWallLossesSurface").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectWallLossesSurface)).ToLocalChecked());

    Nan::Set(target, New<String>("selectWallLossesSurfaceById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectWallLossesSurfaceById)).ToLocalChecked());

    Nan::Set(target, New<String>("insertWallLossesSurface").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(insertWallLossesSurface)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteWallLossesSurface").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteWallLossesSurface)).ToLocalChecked());

    Nan::Set(target, New<String>("updateWallLossesSurface").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateWallLossesSurface)).ToLocalChecked());

    Nan::Set(target, New<String>("selectMotors").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectMotors)).ToLocalChecked());

    Nan::Set(target, New<String>("selectMotorById").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(selectMotorById)).ToLocalChecked());

	Nan::Set(target, New<String>("insertMotor").ToLocalChecked(),
	         GetFunction(New<FunctionTemplate>(insertMotor)).ToLocalChecked());

    Nan::Set(target, New<String>("deleteMotor").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(deleteMotor)).ToLocalChecked());

    Nan::Set(target, New<String>("updateMotor").ToLocalChecked(),
             GetFunction(New<FunctionTemplate>(updateMotor)).ToLocalChecked());
}

NODE_MODULE(db, InitDb)
