function solidLoadChargeMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeatSolid() + ', ' +
        item.getLatentHeat() + ', ' + item.getSpecificHeatLiquid()  + ', ' + item.getMeltingPoint());
}

function solidLoadChargeMaterials(sql){
    logMessage('Solid Load Charge Materials', true);

    let item = new Module.SolidLoadChargeMaterial();
    item.setSubstance('DB Test item');
    item.setSpecificHeatSolid(9.9);
    item.setLatentHeat(9.9);
    item.setSpecificHeatLiquid(9.9);
    item.setMeltingPoint(9.9);
    testNumberValue(sql.insertSolidLoadChargeMaterials(item), true, "Insert");

    let listItems = sql.getSolidLoadChargeMaterials();
    let newId = listItems.get(listItems.size()-1).getID();
    item.setID(newId);
    item.setSpecificHeatSolid(999.666);
    testNumberValue(sql.updateSolidLoadChargeMaterial(item), true, "Update");

    let newItem = sql.getSolidLoadChargeMaterialById(newId);
    testNumberValue(newItem.getSpecificHeatSolid(), 999.666, "Select By ID");

    testNumberValue(sql.deleteSolidLoadChargeMaterial(newId), true, "Delete");

    listItems = sql.getSolidLoadChargeMaterials();
    let count = listItems.size();
    testNumberValue(count, 40, "Select All Default Data");

    logMessage('New Test Data');
    solidLoadChargeMaterialsLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        solidLoadChargeMaterialsLog(listItems.get(i));
}

function gasLoadChargeMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeatVapor());
}

function gasLoadChargeMaterials(sql){
    logMessage('Gas Load Charge Materials', true);

    let item = new Module.GasLoadChargeMaterial();
    item.setSubstance('DB Test item');
    item.setSpecificHeatVapor(9.9);
    testNumberValue(sql.insertGasLoadChargeMaterials(item), true, "Insert");

    let listItems = sql.getGasLoadChargeMaterials();
    let newId = listItems.get(listItems.size()-1).getID();
    item.setID(newId);
    item.setSpecificHeatVapor(999.666);
    testNumberValue(sql.updateGasLoadChargeMaterial(item), true, "Update");

    let newItem = sql.getGasLoadChargeMaterialById(newId);
    testNumberValue(newItem.getSpecificHeatVapor(), 999.666, "Select By ID");

    testNumberValue(sql.deleteGasLoadChargeMaterial(newId), true, "Delete");

    listItems = sql.getGasLoadChargeMaterials();
    let count = listItems.size();
    testNumberValue(count, 10, "Select All Default Data");

    logMessage('New Test Data');
    gasLoadChargeMaterialsLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        gasLoadChargeMaterialsLog(listItems.get(i));
}

function liquidLoadChargeMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeatLiquid() + ', ' +
        item.getSpecificHeatVapor() + ', ' + item.getVaporizingTemperature()  + ', ' + item.getLatentHeat());
}

function liquidLoadChargeMaterials(sql){
    logMessage('Liquid Load Charge Materials', true);

    let item = new Module.LiquidLoadChargeMaterial();
    item.setSubstance('DB Test item');
    item.setSpecificHeatVapor(9.9);
    item.setVaporizingTemperature(9.9);
    item.setSpecificHeatLiquid(9.9);
    item.setLatentHeat(9.9);
    testNumberValue(sql.insertLiquidLoadChargeMaterials(item), true, "Insert");

    let listItems = sql.getLiquidLoadChargeMaterials();
    let newId = listItems.get(listItems.size()-1).getID();
    item.setID(newId);
    item.setSpecificHeatLiquid(999.666);
    testNumberValue(sql.updateLiquidLoadChargeMaterial(item), true, "Update");

    let newItem = sql.getLiquidLoadChargeMaterialById(newId);
    testNumberValue(newItem.getSpecificHeatLiquid(), 999.666, "Select By ID");

    testNumberValue(sql.deleteLiquidLoadChargeMaterial(newId), true, "Delete");

    listItems = sql.getLiquidLoadChargeMaterials();
    let count = listItems.size();
    testNumberValue(count, 13, "Select All Default Data");

    logMessage('New Test Data');
    liquidLoadChargeMaterialsLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        liquidLoadChargeMaterialsLog(listItems.get(i));
}

function solidLiquidFlueGasMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getCarbon() + ', ' +
        item.getHydrogen() + ', ' + item.getSulphur()  + ', ' + item.getInertAsh() + ', ' +
        item.getO2() + ', ' + item.getMoisture()  + ', ' + item.getNitrogen());
}

function solidLiquidFlueGasMaterials(sql){
    logMessage('Solid Liquid Flue Gas Materials', true);

    let item = new Module.SolidLiquidFlueGasMaterial(0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8);
    item.setSubstance('DB Test item');
    testNumberValue(sql.insertSolidLiquidFlueGasMaterial(item), true, "Insert");

    let listItems = sql.getSolidLiquidFlueGasMaterials();
    let newId = listItems.get(listItems.size()-1).getID();
    item.setID(newId);
    item.setCarbon(999.666);
    testNumberValue(sql.updateSolidLiquidFlueGasMaterial(item), true, "Update");

    let newItem = sql.getSolidLiquidFlueGasMaterialById(newId);
    testNumberValue(newItem.getCarbon(), 999.666, "Select By ID");

    testNumberValue(sql.deleteSolidLiquidFlueGasMaterial(newId), true, "Delete");

    listItems = sql.getSolidLiquidFlueGasMaterials();
    let count = listItems.size();
    testNumberValue(count, 6, "Select All Default Data");

    logMessage('New Test Data');
    solidLiquidFlueGasMaterialsLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        solidLiquidFlueGasMaterialsLog(listItems.get(i));
}

function gasFlueGasMaterialsLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' +
        item.getGasByVol("CH4") + ', ' +
        item.getGasByVol("C2H6") + ', ' +
        item.getGasByVol("N2") + ', ' +
        item.getGasByVol("H2") + ', ' +
        item.getGasByVol("C3H8") + ', ' +
        item.getGasByVol("C4H10_CnH2n") + ', ' +
        item.getGasByVol("H2O") + ', ' +
        item.getGasByVol("CO") + ', ' +
        item.getGasByVol("CO2") + ', ' +
        item.getGasByVol("SO2") + ', ' +
        item.getGasByVol("O2") + ', ' +
        item.getHeatingValue() + ', ' + item.getHeatingValueVolume()  + ', ' + item.getSpecificGravity());
}

function gasFlueGasMaterials(sql){
    logMessage('Gas Flue Gas Materials', true);

    let item = new Module.GasCompositions('substance', 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
    testNumberValue(sql.insertGasFlueGasMaterial(item), true, "Insert");

    let listItems = sql.getGasFlueGasMaterials();
    let newId = listItems.get(listItems.size()-1).getID();
    item = new Module.GasCompositions('update substance', 11, 12, 13, 14, 15, 16, 17, 18, 19, 110, 111);
    item.setID(newId);
    testNumberValue(sql.updateGasFlueGasMaterial(item), true, "Update");

    let newItem = sql.getGasFlueGasMaterialById(newId);
    testNumberValue(newItem.getHeatingValue(), 70.66832043871939, "Select By ID");

    testNumberValue(sql.deleteGasFlueGasMaterial(newId), true, "Delete");

    listItems = sql.getGasFlueGasMaterials();
    let count = listItems.size();
    testNumberValue(count, 3, "Select All Default Data");

    logMessage('New Test Data');
    gasFlueGasMaterialsLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        gasFlueGasMaterialsLog(listItems.get(i));
}

function wallLossesSurfaceLog(item){
    logMessage(item.getID() + ', ' + item.getSurface() + ', ' + item.getConditionFactor());
}

function wallLossesSurface(sql){
    logMessage('Wall Losses', true);

    let item = new Module.WallLosses();
    item.setSurface('DB Test item');
    item.setConditionFactor(9.9);
    testNumberValue(sql.insertWallLossesSurface(item), true, "Insert");

    let listItems = sql.getWallLossesSurface();
    let newId = listItems.get(listItems.size()-1).getID();
    item.setID(newId);
    item.setConditionFactor(999.666);
    testNumberValue(sql.updateWallLossesSurface(item), true, "Update");

    let newItem = sql.getWallLossesSurfaceById(newId);
    testNumberValue(newItem.getConditionFactor(), 999.666, "Select By ID");

    testNumberValue(sql.deleteWallLossesSurface(newId), true, "Delete");

    listItems = sql.getWallLossesSurface();
    let count = listItems.size();
    testNumberValue(count, 7, "Select All Default Data");

    logMessage('New Test Data');
    wallLossesSurfaceLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        wallLossesSurfaceLog(listItems.get(i));
}

function atmosphereDataLog(item){
    logMessage(item.getID() + ', ' + item.getSubstance() + ', ' + item.getSpecificHeat());
}

function atmosphereData(sql){
    logMessage('Atmosphere', true);

    let item = new Module.Atmosphere();
    item.setSubstance('DB Test item');
    item.setSpecificHeat(9.9);
    testNumberValue(sql.insertAtmosphereSpecificHeat(item), true, "Insert");

    let listItems = sql.getAtmosphereSpecificHeat();
    let newId = listItems.get(listItems.size()-1).getID();
    item.setID(newId);
    item.setSpecificHeat(999.666);
    testNumberValue(sql.updateAtmosphereSpecificHeat(item), true, "Update");

    let newItem = sql.getAtmosphereSpecificHeatById(newId);
    testNumberValue(newItem.getSpecificHeat(), 999.666, "Select By ID");

    testNumberValue(sql.deleteAtmosphereSpecificHeat(newId), true, "Delete");

    listItems = sql.getAtmosphereSpecificHeat();
    let count = listItems.size();
    testNumberValue(count, 6, "Select All Default Data");

    logMessage('New Test Data');
    atmosphereDataLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        atmosphereDataLog(listItems.get(i));
}

function motorDataLog(item){
    logMessage(item.getId() + ', ' + item.getHp() + ', ' + item.getSynchronousSpeed() + ', ' +
        item.getPoles() + ', ' + item.getNominalEfficiency()  + ', ' + item.getEfficiencyClass().value + ', ' +
        item.getNemaTable() + ', ' + item.getEnclosureType()  + ', ' + item.getLineFrequency().value + ', ' +
        item.getVoltageLimit() + ', ' + item.getCatalog());
}

function motorData(sql){
    logMessage('Motor Data', true);

    let item = new Module.MotorData(1, 2, 3, 4, Module.MotorEfficiencyClass.STANDARD, 'Table 12-11', 'ODP', Module.LineFrequency.FREQ60, 5, 'NEMA MG - 1-2018');
    testNumberValue(sql.insertMotorData(item), true, "Insert");

    let listItems = sql.getMotorData();
    let newId = listItems.get(listItems.size()-1).getId();
    item.setId(newId);
    item.setHp(999.666);
    testNumberValue(sql.updateMotorData(item), true, "Update");

    let newItem = sql.getMotorDataById(newId);
    testNumberValue(newItem.getHp(), 999.666, "Select By ID");

    testNumberValue(sql.deleteMotorData(newId), true, "Delete");

    listItems = sql.getMotorData();
    let count = listItems.size();
    testNumberValue(count, 954, "Select All Default Data");

    logMessage('New Test Data');
    motorDataLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        motorDataLog(listItems.get(i));
}

function pumpDataLog(item){
    logMessage(item.getId() + ', ' +
        item.getManufacturer() + ', ' +
        item.getModel() + ', ' +
        item.getType() + ', ' +
        item.getSerialNumber() + ', ' +
        item.getStatus() + ', ' +
        item.getRadialBearingType() + ', ' +
        item.getThrustBearingType() + ', ' +
        item.getShaftOrientation() + ', ' +
        item.getShaftSealType() + ', ' +
        item.getFluidType() + ', ' +
        item.getPriority() + ', ' +
        item.getDriveType() + ', ' +
        item.getFlangeConnectionClass() + ', ' +
        item.getFlangeConnectionSize() + ', ' +
        item.getNumShafts() + ', ' +
        item.getSpeed() + ', ' +
        item.getNumStages() + ', ' +
        item.getYearlyOperatingHours() + ', ' +
        item.getYearInstalled() + ', ' +
        item.getPumpType() + ', ' +
        item.getFinalMotorRpm() + ', ' +
        item.getInletDiameter() + ', ' +
        item.getWeight() + ', ' +
        item.getOutletDiameter() + ', ' +
        item.getPercentageOfSchedule() + ', ' +
        item.getDailyPumpCapacity() + ', ' +
        item.getMeasuredPumpCapacity() + ', ' +
        item.getPumpPerformance() + ', ' +
        item.getStaticSuctionHead() + ', ' +
        item.getStaticDischargeHead() + ', ' +
        item.getFluidDensity() + ', ' +
        item.getLengthOfDischargePipe() + ', ' +
        item.getPipeDesignFrictionLosses() + ', ' +
        item.getMaxWorkingPressure() + ', ' +
        item.getMaxAmbientTemperature() + ', ' +
        item.getMaxSuctionLift() + ', ' +
        item.getDisplacement() + ', ' +
        item.getStartingTorque() + ', ' +
        item.getRatedSpeed() + ', ' +
        item.getShaftDiameter() + ', ' +
        item.getImpellerDiameter() + ', ' +
        item.getEfficiency() + ', ' +
        item.getOutput60Hz() + ', ' +
        item.getMinFlowSize() + ', ' +
        item.getPumpSize() + ', ' +
        item.getOutOfService());
}

function pumpData(sql){
    logMessage('Pump Data', true);

    let pump = {
        id: 2, manufacturer: "manufacturer2", model: "model2", type: "type2", serialNumber: "serialNumber2",
        status: "status2",  pumpType: "pumpType2", radialBearingType: "radialBearingType2", thrustBearingType: "thrustBearingType2",
        shaftOrientation: "shaftOrientation2", shaftSealType: "shaftSealType2", fluidType: "fluidType2", priority: "priority2",
        driveType: "driveType2", flangeConnectionClass: "flangeConnectionClass2", flangeConnectionSize: "flangeConnectionSize2",
        numShafts: 1, speed: 2, numStages: 1,  yearlyOperatingHours: 9000, yearInstalled: 2018,
        finalMotorRpm: 1780, inletDiameter: 5, weight: 90, outletDiameter: 6,
        percentageOfSchedule: 89, dailyPumpCapacity: 90, measuredPumpCapacity: 85,
        pumpPerformance: 99, staticSuctionHead: 15, staticDischargeHead: 11, fluidDensity: 13,
        lengthOfDischargePipe: 14, pipeDesignFrictionLosses: 0.5, maxWorkingPressure: 250,
        maxAmbientTemperature: 85, maxSuctionLift: 1.5, displacement: 600, startingTorque: 400,
        ratedSpeed: 70, shaftDiameter: 15, impellerDiameter: 20, efficiency: 88,
        output60Hz: 15, minFlowSize: 15, pumpSize: 15, outOfService: 1
    };

    let item = new Module.PumpData(pump.manufacturer, pump.model, pump.type, pump.serialNumber,
        pump.status, pump.pumpType, pump.radialBearingType,  pump.thrustBearingType,
        pump.shaftOrientation, pump.shaftSealType, pump.fluidType, pump.priority,
        pump.driveType, pump.flangeConnectionClass, pump.flangeConnectionSize,
        pump.numShafts, pump.speed, pump.numStages,  pump.yearlyOperatingHours, pump.yearInstalled, pump.finalMotorRpm,
        pump.inletDiameter, pump.weight, pump.outletDiameter, pump.percentageOfSchedule,
        pump.dailyPumpCapacity, pump.measuredPumpCapacity, pump.pumpPerformance, pump.staticSuctionHead,
        pump.staticDischargeHead, pump.fluidDensity, pump.lengthOfDischargePipe,
        pump.pipeDesignFrictionLosses,  pump.maxWorkingPressure, pump.maxAmbientTemperature,
        pump.maxSuctionLift,  pump.displacement, pump.startingTorque, pump.ratedSpeed,
        pump.shaftDiameter, pump.impellerDiameter, pump.efficiency, pump.output60Hz, pump.minFlowSize,
        pump.pumpSize,  pump.outOfService);
    item.setId(pump.id);
    testNumberValue(sql.insertPumpData(item), true, "Insert");

    let listItems = sql.getPumpData();
    let newId = listItems.get(listItems.size()-1).getId();
    item.setId(newId);
    item.setWeight(999.666);
    testNumberValue(sql.updatePumpData(item), true, "Update");

    let newItem = sql.getPumpDataById(newId);
    testNumberValue(newItem.getWeight(), 999.666, "Select By ID");

    testNumberValue(sql.deletePumpData(newId), true, "Delete");

    listItems = sql.getPumpData();
    let count = listItems.size();
    testNumberValue(count, 1, "Select All Default Data");

    logMessage('New Test Data');
    pumpDataLog(newItem);
    logMessage('All Default Data:');
    for(let i = 0; i < count; i++)
        pumpDataLog(listItems.get(i));
}

function enableSharedCache(sql) {
    logMessage('Enable Shared Cache', true);

    let share_cache = 1;

    let success = sql.enableSharedCache(share_cache);
    console.log('sql', sql);
    console.log('db success', success);
    testNumberValue(success, 0, "Return SQLITE_OK (0) result code");
}

function db(){
    logMessage('DB Test:', true);

    let instance = new Module.SQLite(":memory:", true);
    enableSharedCache(instance);

    solidLoadChargeMaterials(instance);
    gasLoadChargeMaterials(instance);
    liquidLoadChargeMaterials(instance);
    solidLiquidFlueGasMaterials(instance);
    gasFlueGasMaterials(instance);
    wallLossesSurface(instance);
    atmosphereData(instance);
    motorData(instance);
    pumpData(instance);

    instance.delete();
}

function shared_db(){
    logMessage('Shared DB Test:', true);

    let instance = new Module.SQLite("file::memory:?cache=shared", true);
    enableSharedCache(instance);

    solidLoadChargeMaterials(instance);
    gasLoadChargeMaterials(instance);
    liquidLoadChargeMaterials(instance);
    solidLiquidFlueGasMaterials(instance);
    gasFlueGasMaterials(instance);
    wallLossesSurface(instance);
    atmosphereData(instance);
    motorData(instance);
    pumpData(instance);

    instance.delete();
}


// db();
shared_db();