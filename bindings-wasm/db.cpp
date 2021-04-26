#include <sqlite/SQLite.h>
#include <calculator/losses/SolidLoadChargeMaterial.h>
#include <calculator/losses/LiquidLoadChargeMaterial.h>
#include <calculator/losses/GasLoadChargeMaterial.h>
#include <calculator/losses/GasFlueGasMaterial.h>
#include <calculator/losses/SolidLiquidFlueGasMaterial.h>
#include <calculator/losses/Atmosphere.h>
#include <calculator/losses/WallLosses.h>
#include <calculator/motor/MotorData.h>
#include <calculator/pump/PumpData.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(db_class)
{
    class_<SQLite>("SQLite")
        .constructor<std::string, bool>()

        .function("getCustomSolidLoadChargeMaterials", &SQLite::getCustomSolidLoadChargeMaterials)
        .function("getSolidLoadChargeMaterials", &SQLite::getSolidLoadChargeMaterials)
        .function("getSolidLoadChargeMaterialById", &SQLite::getSolidLoadChargeMaterialById)
        .function("insertSolidLoadChargeMaterials", &SQLite::insertSolidLoadChargeMaterials)
        .function("deleteSolidLoadChargeMaterial", &SQLite::deleteSolidLoadChargeMaterial)
        .function("updateSolidLoadChargeMaterial", &SQLite::updateSolidLoadChargeMaterial)

        .function("getCustomGasLoadChargeMaterials", &SQLite::getCustomGasLoadChargeMaterials)
        .function("getGasLoadChargeMaterials", &SQLite::getGasLoadChargeMaterials)
        .function("getGasLoadChargeMaterialById", &SQLite::getGasLoadChargeMaterialById)
        .function("insertGasLoadChargeMaterials", &SQLite::insertGasLoadChargeMaterials)
        .function("deleteGasLoadChargeMaterial", &SQLite::deleteGasLoadChargeMaterial)
        .function("updateGasLoadChargeMaterial", &SQLite::updateGasLoadChargeMaterial)

        .function("getCustomLiquidLoadChargeMaterials", &SQLite::getCustomLiquidLoadChargeMaterials)
        .function("getLiquidLoadChargeMaterials", &SQLite::getLiquidLoadChargeMaterials)
        .function("getLiquidLoadChargeMaterialById", &SQLite::getLiquidLoadChargeMaterialById)
        .function("insertLiquidLoadChargeMaterials", &SQLite::insertLiquidLoadChargeMaterials)
        .function("deleteLiquidLoadChargeMaterial", &SQLite::deleteLiquidLoadChargeMaterial)
        .function("updateLiquidLoadChargeMaterial", &SQLite::updateLiquidLoadChargeMaterial)

        .function("getCustomSolidLiquidFlueGasMaterials", &SQLite::getCustomSolidLiquidFlueGasMaterials)
        .function("getSolidLiquidFlueGasMaterials", &SQLite::getSolidLiquidFlueGasMaterials)
        .function("getSolidLiquidFlueGasMaterialById", &SQLite::getSolidLiquidFlueGasMaterialById)
        .function("insertSolidLiquidFlueGasMaterial", &SQLite::insertSolidLiquidFlueGasMaterial)
        .function("deleteSolidLiquidFlueGasMaterial", &SQLite::deleteSolidLiquidFlueGasMaterial)
        .function("updateSolidLiquidFlueGasMaterial", &SQLite::updateSolidLiquidFlueGasMaterial)

        .function("getCustomGasFlueGasMaterials", &SQLite::getCustomGasFlueGasMaterials)
        .function("getGasFlueGasMaterials", &SQLite::getGasFlueGasMaterials)
        .function("getGasFlueGasMaterialById", &SQLite::getGasFlueGasMaterialById)
        .function("insertGasFlueGasMaterial", &SQLite::insertGasFlueGasMaterial)
        .function("deleteGasFlueGasMaterial", &SQLite::deleteGasFlueGasMaterial)
        .function("updateGasFlueGasMaterial", &SQLite::updateGasFlueGasMaterial)

        .function("getCustomAtmosphereSpecificHeat", &SQLite::getCustomAtmosphereSpecificHeat)
        .function("getAtmosphereSpecificHeat", &SQLite::getAtmosphereSpecificHeat)
        .function("getAtmosphereSpecificHeatById", &SQLite::getAtmosphereSpecificHeatById)
        .function("insertAtmosphereSpecificHeat", &SQLite::insertAtmosphereSpecificHeat)
        .function("updateAtmosphereSpecificHeat", &SQLite::updateAtmosphereSpecificHeat)
        .function("deleteAtmosphereSpecificHeat", &SQLite::deleteAtmosphereSpecificHeat)

        .function("getCustomWallLossesSurface", &SQLite::getCustomWallLossesSurface)
        .function("getWallLossesSurface", &SQLite::getWallLossesSurface)
        .function("getWallLossesSurfaceById", &SQLite::getWallLossesSurfaceById)
        .function("insertWallLossesSurface", &SQLite::insertWallLossesSurface)
        .function("deleteWallLossesSurface", &SQLite::deleteWallLossesSurface)
        .function("updateWallLossesSurface", &SQLite::updateWallLossesSurface)

        .function("getCustomMotorData", &SQLite::getCustomMotorData)
        .function("getMotorData", &SQLite::getMotorData)
        .function("getMotorDataById", &SQLite::getMotorDataById)
        .function("insertMotorData", &SQLite::insertMotorData)
        .function("deleteMotorData", &SQLite::deleteMotorData)
        .function("updateMotorData", &SQLite::updateMotorData)

        .function("getCustomPumpData", &SQLite::getCustomPumpData)
        .function("getPumpData", &SQLite::getPumpData)
        .function("getPumpDataById", &SQLite::getPumpDataById)
        .function("insertPumpData", &SQLite::insertPumpData)
        .function("deletePumpData", &SQLite::deletePumpData)
        .function("updatePumpData", &SQLite::updatePumpData);
}
