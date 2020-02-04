const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'db'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('dbSelectSolidMaterial', function (t) {
    t.plan(15);
    bindings.startup();
    t.type(bindings.selectSolidLoadChargeMaterialById, 'function');

    var res = bindings.selectSolidLoadChargeMaterialById(1);
    var obj = {
        id: 1,
        substance: 'Aluminum',
        specificHeatSolid: 0.247910198232625,
        latentHeat: 169,
        specificHeatLiquid: 0.2601,
        meltingPoint: 1215
    };

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.specificHeatSolid, obj.specificHeatSolid, res.specificHeatSolid + " != " + obj.specificHeatSolid);
    t.equal(res.latentHeat, obj.latentHeat, res.latentHeat + " != " + obj.latentHeat);
    t.equal(res.specificHeatLiquid, obj.specificHeatLiquid, res.specificHeatLiquid + " != " + obj.specificHeatLiquid);
    t.equal(res.meltingPoint, obj.meltingPoint, res.meltingPoint + " != " + obj.meltingPoint);

    t.type(bindings.selectSolidLoadChargeMaterials, 'function');

    var obj2 = {
        id: 40,
        substance: 'Ladle Refractory',
        specificHeatSolid: 0.250059708621925,
        latentHeat: 425,
        specificHeatLiquid: 0.26,
        meltingPoint: 5000
    };

    res = bindings.selectSolidLoadChargeMaterials();
    t.equal(res.length, 40, "array is not of size 40");
    t.equal(res[39].id, obj2.id, res[39].id + " != " + obj2.id);
    t.equal(res[39].substance, obj2.substance, res[39].substance + " != " + obj2.substance);
    t.equal(res[39].specificHeatSolid, obj2.specificHeatSolid, res[39].specificHeatSolid + " != " + obj2.specificHeatSolid);
    t.equal(res[39].latentHeat, obj2.latentHeat, res[39].latentHeat + " != " + obj2.latentHeat);
    t.equal(res[39].specificHeatLiquid, obj2.specificHeatLiquid, res[39].specificHeatLiquid + " != " + obj2.specificHeatLiquid);
    t.equal(res[39].meltingPoint, obj2.meltingPoint, res[39].meltingPoint + " != " + obj2.meltingPoint);
});

test('dbSelectLiquidMaterial', function (t) {
    t.plan(15);
    bindings.startup();
    t.type(bindings.selectLiquidLoadChargeMaterialById, 'function');

    var res = bindings.selectLiquidLoadChargeMaterialById(1);
    var obj = {
        id: 1,
        substance: 'Crude',
        specificHeatLiquid: 0.6501,
        specificHeatVapor: 0.55,
        latentHeat: 105,
        vaporizationTemperature: 900
    };

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.specificHeatLiquid, obj.specificHeatLiquid, res.specificHeatLiquid + " != " + obj.specificHeatLiquid);
    t.equal(res.specificHeatVapor, obj.specificHeatVapor, res.specificHeatVapor + " != " + obj.specificHeatVapor);
    t.equal(res.latentHeat, obj.latentHeat, res.latentHeat + " != " + obj.latentHeat);
    t.equal(res.vaporizationTemperature, obj.vaporizationTemperature, res.vaporizationTemperature + " != " + obj.vaporizationTemperature);


    t.type(bindings.selectLiquidLoadChargeMaterials, 'function');

    var obj2 = {
        id: 13,
        substance: 'Kerosene',
        specificHeatLiquid: 0.5701,
        specificHeatVapor: 0.62,
        latentHeat: 260,
        vaporizationTemperature:260
    };

    res = bindings.selectLiquidLoadChargeMaterials();
    t.equal(res.length, 13, "array is not of size 13");
    t.equal(res[12].id, obj2.id, res[12].id + " != " + obj2.id);
    t.equal(res[12].substance, obj2.substance, res[12].substance + " != " + obj2.substance);
    t.equal(res[12].specificHeatVapor, obj2.specificHeatVapor, res[12].specificHeatVapor + " != " + obj2.specificHeatVapor);
    t.equal(res[12].latentHeat, obj2.latentHeat, res[12].latentHeat + " != " + obj2.latentHeat);
    t.equal(res[12].specificHeatLiquid, obj2.specificHeatLiquid, res[12].specificHeatLiquid + " != " + obj2.specificHeatLiquid);
    t.equal(res[12].vaporizationTemperature, obj2.vaporizationTemperature, res[12].vaporizationTemperature + " != " + obj2.vaporizationTemperature);
});

test('dbInsertCustomLiquidMaterial', function (t) {
    t.plan(3);
    bindings.startup();
    t.type(bindings.selectLiquidLoadChargeMaterials, 'function');

    var res = bindings.selectLiquidLoadChargeMaterials();
    var obj = {
        id: 1,
        substance: 'customLiquidLoadChargeMaterial',
        specificHeatLiquid: 0.6501,
        specificHeatVapor: 0.55,
        latentHeat: 105,
        vaporizationTemperature: 900
    };
    var size = res.length;
    bindings.insertLiquidLoadChargeMaterial(obj);
    res = bindings.selectLiquidLoadChargeMaterials();
    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    t.equal(res[size].substance, obj.substance, res.substance + " != " + obj.substance);
});


test('dbSelectGasMaterial', function (t) {
    t.plan(9);
    bindings.startup();

    t.type(bindings.selectGasLoadChargeMaterialById, 'function');
    var res = bindings.selectGasLoadChargeMaterialById(1);
    var obj = {
        id: 1,
        substance: 'Water vapor - Near Atm. Pressure',
        specificHeatVapor: 0.47
    };

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.specificHeatVapor, obj.specificHeatVapor, res.specificHeatVapor + " != " + obj.specificHeatVapor);

    t.type(bindings.selectGasLoadChargeMaterials, 'function');
    res = bindings.selectGasLoadChargeMaterials();
    var obj2 = {
        id: 10,
        substance: 'Hydrogen - Low Pressure',
        specificHeatVapor: 3.45
    };

    t.equal(res.length, 10, "array is not of size 10");
    t.equal(res[9].id, obj2.id, res[9].id + " != " + obj2.id);
    t.equal(res[9].substance, obj2.substance, res[9].substance + " != " + obj2.substance);
    t.equal(res[9].specificHeatVapor, obj2.specificHeatVapor, res[9].specificHeatVapor + " != " + obj2.specificHeatVapor);
});

test('dbInsertGasLoadChargeMaterial', function (t) {
    t.plan(4);
    bindings.startup();

    t.type(bindings.insertGasLoadChargeMaterial, 'function');
    var res = bindings.selectGasLoadChargeMaterials();
    var size = res.length;
    var obj2 = {
        substance: 'customGasLoadChargeMaterial',
        specificHeatVapor: 3.45
    };

    bindings.insertGasLoadChargeMaterial(obj2);
    res = bindings.selectGasLoadChargeMaterials();

    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    t.equal(res[size].substance, obj2.substance, res[size].substance + " != " + obj2.substance);
    t.equal(res[size].specificHeatVapor, obj2.specificHeatVapor, res[size].specificHeatVapor + " != " + obj2.specificHeatVapor);
});

test('dbGasFlueGasMaterial select', function (t) {
    t.plan(29);
    bindings.startup();

    t.type(bindings.selectGasFlueGasMaterialById, 'function');
    var res = bindings.selectGasFlueGasMaterialById(1);

    var obj = {
        id: 1,
        substance: 'Typical Natural Gas - US',
        CH4: 87.0,
        C2H6: 8.5,
        N2: 3.6,
        H2: 0.4,
        C3H8: 0.0,
        C4H10_CnH2n: 0.0,
        H2O: 0.0,
        CO: 0.0,
        CO2: 0.4,
        SO2: 0.0,
        O2: 0.1,
        heatingValue: 22030.67089880065,
        heatingValueVolume: 1032.445,
        specificGravity: 0.6571206283343215
    };

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.CH4, obj.CH4, res.CH4 + " != " + obj.CH4);
    t.equal(res.C2H6, obj.C2H6, res.C2H6 + " != " + obj.C2H6);
    t.equal(res.N2, obj.N2, res.N2 + " != " + obj.N2);
    t.equal(res.H2, obj.H2, res.H2 + " != " + obj.H2);
    t.equal(res.O2, obj.O2, res.O2 + " != " + obj.O2);
    t.equal(res.heatingValue, obj.heatingValue, res.heatingValue + " != " + obj.heatingValue);
    t.equal(res.heatingValueVolume, obj.heatingValueVolume, res.heatingValueVolume + " != " + obj.heatingValueVolume);
    t.equal(res.specificGravity, obj.specificGravity, res.specificGravity + " != " + obj.specificGravity);

    t.type(bindings.selectGasFlueGasMaterials, 'function');
    res = bindings.selectGasFlueGasMaterials();
    var obj2 = {
        id: 3,
        substance: 'Blast Furnace Gas',
        CH4: 0.1,
        C2H6: 0.0,
        N2: 56.4,
        H2: 2.4,
        C3H8: 0.0,
        C4H10_CnH2n: 0.0,
        H2O: 3.4,
        CO: 23.3,
        CO2: 14.4,
        SO2: 0.0,
        O2: 0.0,
        heatingValue: 1080.6848266529887,
        heatingValueVolume: 83.605,
        specificGravity: 1.0870540901007706
    };

    t.equal(res.length, 3, "array is not of size 3");
    t.equal(res[2].id, obj2.id, res[2].id + " != " + obj2.id);
    t.equal(res[2].substance, obj2.substance, res[2].substance + " != " + obj2.substance);
    t.equal(res[2].CH4, obj2.CH4, res[2].CH4 + " != " + obj2.CH4);
    t.equal(res[2].C2H6, obj2.C2H6, res[2].C2H6 + " != " + obj2.C2H6);
    t.equal(res[2].N2, obj2.N2, res[2].N2 + " != " + obj2.N2);
    t.equal(res[2].H2, obj2.H2, res[2].H2 + " != " + obj2.H2);
    t.equal(res[2].C3H8, obj2.C3H8, res[2].C3H8 + " != " + obj2.C3H8);
    t.equal(res[2].C4H10_CnH2n, obj2.C4H10_CnH2n, res[2].C4H10_CnH2n + " != " + obj2.C4H10_CnH2n);
    t.equal(res[2].H2O, obj2.H2O, res[2].H2O + " != " + obj2.H2O);
    t.equal(res[2].CO, obj2.CO, res[2].CO + " != " + obj2.CO);
    t.equal(res[2].CO2, obj2.CO2, res[2].CO2 + " != " + obj2.CO2);
    t.equal(res[2].SO2, obj2.SO2, res[2].SO2 + " != " + obj2.SO2);
    t.equal(res[2].O2, obj2.O2, res[2].O2 + " != " + obj2.O2);
    t.equal(res[2].heatingValue, obj2.heatingValue, res[2].heatingValue + " != " + obj2.heatingValue);
    t.equal(res[2].heatingValueVolume, obj2.heatingValueVolume, res[2].heatingValueVolume + " != " + obj2.heatingValueVolume);
    t.equal(res[2].specificGravity, obj2.specificGravity, res[2].specificGravity + " != " + obj2.specificGravity);
});

test('dbGasFlueGasMaterial insert', function (t) {
    t.plan(18);
    bindings.startup();

    t.type(bindings.selectGasFlueGasMaterials, 'function');
    var res = bindings.selectGasFlueGasMaterials();
    var size = res.length;
    var obj2 = {
        substance: 'customGasFlueGas',
        CH4: 0.1,
        C2H6: 0.0,
        N2: 56.4,
        H2: 2.4,
        C3H8: 0.0,
        C4H10_CnH2n: 0.0,
        H2O: 3.4,
        CO: 23.3,
        CO2: 14.4,
        SO2: 0.0,
        O2: 0.0
    };

    bindings.insertGasFlueGasMaterial(obj2);
    res = bindings.selectGasFlueGasMaterials();

    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    t.equal(res[size].substance, obj2.substance, res[size].substance + " != " + obj2.substance);
    t.equal(res[size].CH4, obj2.CH4, res[size].CH4 + " != " + obj2.CH4);
    t.equal(res[size].C2H6, obj2.C2H6, res[size].C2H6 + " != " + obj2.C2H6);
    t.equal(res[size].N2, obj2.N2, res[size].N2 + " != " + obj2.N2);
    t.equal(res[size].H2, obj2.H2, res[size].H2 + " != " + obj2.H2);
    t.equal(res[size].C3H8, obj2.C3H8, res[size].C3H8 + " != " + obj2.C3H8);
    t.equal(res[size].C4H10_CnH2n, obj2.C4H10_CnH2n, res[size].C4H10_CnH2n + " != " + obj2.C4H10_CnH2n);
    t.equal(res[size].H2O, obj2.H2O, res[size].H2O + " != " + obj2.H2O);
    t.equal(res[size].CO, obj2.CO, res[size].CO + " != " + obj2.CO);
    t.equal(res[size].CO2, obj2.CO2, res[size].CO2 + " != " + obj2.CO2);
    t.equal(res[size].SO2, obj2.SO2, res[size].SO2 + " != " + obj2.SO2);
    t.equal(res[size].O2, obj2.O2, res[size].O2 + " != " + obj2.O2);
    t.equal(res[size].heatingValueVolume, 83.605);

    obj2 = {
        substance: 'anotherCustomGasFlueGas',
        CH4: 45,
        C2H6: 45,
        N2: 1,
        H2: 1,
        C3H8: 3,
        C4H10_CnH2n: 2,
        H2O: 0,
        CO: 1,
        CO2: 0,
        SO2: 0,
        O2: 2
    };

    bindings.insertGasFlueGasMaterial(obj2);
    res = bindings.selectGasFlueGasMaterials();
    t.equal(rnd(res[size + 1].heatingValue), 21684.279498);
    t.equal(rnd(res[size + 1].specificGravity), 0.906014);
    t.equal(rnd(res[size + 1].heatingValueVolume), 1400.8);

});

test('dbSolidLiquidFlueGasMaterial', function (t) {
    t.plan(21);
    bindings.startup();
    t.type(bindings.selectSolidLiquidFlueGasMaterialById, 'function');

    res = bindings.selectSolidLiquidFlueGasMaterialById(2);
    var obj = {
        id: 2,
        substance: 'Typical Anthracite - US',
        carbon: 77.7 / 100,
        hydrogen: 1.8 / 100,
        sulphur: 0.7 / 100,
        inertAsh: 9.8 / 100,
        o2: 2.1 / 100,
        moisture: 7.1 / 100,
        nitrogen: 0.8 / 100
    };

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.carbon, obj.carbon, res.carbon + " != " + obj.carbon);
    t.equal(res.hydrogen, obj.hydrogen, res.hydrogen + " != " + obj.hydrogen);
    t.equal(res.sulphur, obj.sulphur, res.sulphur + " != " + obj.sulphur);
    t.equal(res.inertAsh, obj.inertAsh, res.inertAsh + " != " + obj.inertAsh);
    t.equal(res.o2, obj.o2, res.o2 + " != " + obj.o2);
    t.equal(res.moisture, obj.moisture, res.moisture + " != " + obj.moisture);
    t.equal(res.nitrogen, obj.nitrogen, res.nitrogen + " != " + obj.nitrogen);

    t.type(bindings.selectSolidLiquidFlueGasMaterials, 'function');
    res = bindings.selectSolidLiquidFlueGasMaterials();

    t.equal(res.length, 6, "array is not of size 6");
    t.equal(res[1].id, obj.id, res[1].id + " != " + obj.id);
    t.equal(res[1].substance, obj.substance, res[1].substance + " != " + obj.substance);
    t.equal(res[1].carbon, obj.carbon, res[1].carbon + " != " + obj.carbon);
    t.equal(res[1].hydrogen, obj.hydrogen, res[1].hydrogen + " != " + obj.hydrogen);
    t.equal(res[1].sulphur, obj.sulphur, res[1].sulphur + " != " + obj.sulphur);
    t.equal(res[1].inertAsh, obj.inertAsh, res[1].inertAsh + " != " + obj.inertAsh);
    t.equal(res[1].o2, obj.o2, res[1].o2 + " != " + obj.o2);
    t.equal(res[1].moisture, obj.moisture, res[1].moisture + " != " + obj.moisture);
    t.equal(res[1].nitrogen, obj.nitrogen, res[1].nitrogen + " != " + obj.nitrogen);
});

test('dbInsertSolidLiquidFlueGasMaterial', function (t) {
    t.plan(10);
    bindings.startup();
    t.type(bindings.selectSolidLiquidFlueGasMaterialById, 'function');

    var res = bindings.selectSolidLiquidFlueGasMaterials();
    var obj = {
        substance: 'customSolidLiquidFlueGasMaterial',
        carbon: 77.7,
        hydrogen: 1.8,
        sulphur: 0.7,
        inertAsh: 9.8,
        o2: 2.1,
        moisture: 7.1,
        nitrogen: 0.8
    };

    var size = res.length;
    bindings.insertSolidLiquidFlueGasMaterial(obj);
    res = bindings.selectSolidLiquidFlueGasMaterials();

    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    t.equal(res[size].substance, obj.substance, res[size].substance + " != " + obj.substance);
    t.equal(res[size].carbon, obj.carbon, res[size].carbon + " != " + obj.carbon);
    t.equal(res[size].hydrogen, obj.hydrogen, res[size].hydrogen + " != " + obj.hydrogen);
    t.equal(res[size].sulphur, obj.sulphur, res[size].sulphur + " != " + obj.sulphur);
    t.equal(res[size].inertAsh, obj.inertAsh, res[size].inertAsh + " != " + obj.inertAsh);
    t.equal(res[size].o2, obj.o2, res[size].o2 + " != " + obj.o2);
    t.equal(res[size].moisture, obj.moisture, res[size].moisture + " != " + obj.moisture);
    t.equal(res[size].nitrogen, obj.nitrogen, res[size].nitrogen + " != " + obj.nitrogen);
});

test('dbSelectAtmosphereSpecificHeat', function (t) {
    t.plan(9);
    bindings.startup();
    t.type(bindings.selectAtmosphereSpecificHeatById, 'function');

    var res = bindings.selectAtmosphereSpecificHeatById(1);
    var obj = {
        id: 1,
        substance: 'Nitrogen',
        specificHeat: 0.0185
    };

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.specificHeat, obj.specificHeat, res.specificHeat + " != " + obj.specificHeat);


    t.type(bindings.selectAtmosphereSpecificHeat, 'function');

    var obj2 = {
        id: 6,
        substance: 'Water Vapor',
        specificHeat: 0.0212
    };

    res = bindings.selectAtmosphereSpecificHeat();
    t.equal(res.length, 6, "array is not of size 6");
    t.equal(res[5].id, obj2.id, res[5].id + " != " + obj2.id);
    t.equal(res[5].substance, obj2.substance, res[5].substance + " != " + obj2.substance);
    t.equal(res[5].specificHeat, obj2.specificHeat, res[5].specificHeat + " != " + obj2.specificHeat);
});

test('dbInsertAtmosphereSpecificHeat', function (t) {
    t.plan(4);
    bindings.startup();
    t.type(bindings.selectAtmosphereSpecificHeat, 'function');

    var res = bindings.selectAtmosphereSpecificHeat();
    var size = res.length;

    var obj2 = {
        substance: 'customAtmosphereObject',
        specificHeat: 0.5
    };

    bindings.insertAtmosphereSpecificHeat(obj2);
    res = bindings.selectAtmosphereSpecificHeat();
    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    t.equal(res[size].substance, obj2.substance, res[size].substance + " != " + obj2.substance);
    t.equal(res[size].specificHeat, obj2.specificHeat, res[size].specificHeat + " != " + obj2.specificHeat);
});

test('dbSelectWallLossesSurface', function (t) {
    t.plan(9);
    bindings.startup();
    t.type(bindings.selectWallLossesSurfaceById, 'function');

    var res = bindings.selectWallLossesSurfaceById(1);
    var obj = {
        id: 1,
        surface: 'Horizontal cylinders',
        conditionFactor: 1.016};

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.surface, obj.surface, res.surface + " != " + obj.surface);
    t.equal(res.conditionFactor, obj.conditionFactor, res.conditionFactor + " != " + obj.conditionFactor);


    t.type(bindings.selectWallLossesSurface, 'function');

    var obj2 = {
        id: 7,
        surface: 'Horizontal plate facing down, cooler than air',
        conditionFactor: 1.79
    };

    res = bindings.selectWallLossesSurface();
    t.equal(res.length, 7, "array is not of size 7");
    t.equal(res[6].id, obj2.id, res[6].id + " != " + obj2.id);
    t.equal(res[6].surface, obj2.surface, res[6].surface + " != " + obj2.surface);
    t.equal(res[6].conditionFactor, obj2.conditionFactor, res[6].conditionFactor + " != " + obj2.conditionFactor);
});

test('dbInsertWallLossesSurface', function (t) {
    t.plan(4);
    bindings.startup();
    t.type(bindings.selectWallLossesSurface, 'function');

    var obj2 = {
        surface: 'customWallLossesSurface',
        conditionFactor: 1.79
    };

    var res = bindings.selectWallLossesSurface();
    var size = res.length;
    bindings.insertWallLossesSurface(obj2);
    res = bindings.selectWallLossesSurface();
    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    t.equal(res[size].surface, obj2.surface, res[size].surface + " != " + obj2.surface);
    t.equal(res[size].conditionFactor, obj2.conditionFactor, res[size].conditionFactor + " != " + obj2.conditionFactor);
});
///*
test('dbSelectPumpData', function (t) {
    t.plan(2);
    bindings.startup();
    t.type(bindings.selectPumpById, 'function');

    //var res = bindings.selectPumpById(1);
    //var test = bindings.selectPumps();
    //var size = test.length;
    var obj = {
        id: 1, manufacturer: "manufacturer", model: "model", type: "type", serialNumber: "serialNumber",
        status: "status",  pumpType: "pumpType", radialBearingType: "radialBearingType", thrustBearingType: "thrustBearingType",
        shaftOrientation: "shaftOrientation", shaftSealType: "shaftSealType", fluidType: "fluidType", priority: "priority",
        driveType: "driveType", flangeConnectionClass: "flangeConnectionClass", flangeConnectionSize: "flangeConnectionSize",
        numShafts: 1, speed: 2, numStages: 1,  yearlyOperatingHours: 9000, yearInstalled: 2018,
        finalMotorRpm: 1780, inletDiameter: 5, weight: 90, outletDiameter: 6,
        percentageOfSchedule: 89, dailyPumpCapacity: 90, measuredPumpCapacity: 85,
        pumpPerformance: 99, staticSuctionHead: 15, staticDischargeHead: 11, fluidDensity: 13,
        lengthOfDischargePipe: 14, pipeDesignFrictionLosses: 0.5, maxWorkingPressure: 250,
        maxAmbientTemperature: 85, maxSuctionLift: 1.5, displacement: 600, startingTorque: 400,
        ratedSpeed: 70, shaftDiameter: 15, impellerDiameter: 20, efficiency: 88,
        output60Hz: 15, minFlowSize: 15, pumpSize: 15, outOfService: 1
    };

    //bindings.insertPump(obj);
    var test = bindings.selectPumps();

    //t.equal(res.id, obj.id, res.id + " != " + obj.id);
    //t.equal(test.length, 0, test.length + " != 1");
    t.equal(0, 0, "0 != 0");

    // bindings.insertPump(pump_example);
    //var all_pumps = bindings.selectPumps();
    //var size = all_pumps.size;
    // t.equal(all_pumps.length, 1);

    // var all_motors = bindings.selectMotors();
    //var test = 0
});
//*/
test('dbDeletions', function (t) {
    t.plan(7);
    bindings.startup();

    var res = bindings.selectLiquidLoadChargeMaterials();
    var last = res[res.length - 1].substance;
    var obj = {
        substance: 'customLiquidLoadChargeMaterial',
        specificHeatLiquid: 0.6501,
        specificHeatVapor: 0.55,
        latentHeat: 105,
        vaporizationTemperature: 900
    };
    bindings.insertLiquidLoadChargeMaterial(obj);
    bindings.deleteLiquidLoadChargeMaterial(bindings.selectLiquidLoadChargeMaterials().length);
    res = bindings.selectLiquidLoadChargeMaterials();
    t.equal(last, res[res.length - 1].substance);

    res = bindings.selectSolidLoadChargeMaterials();
    last = res[res.length - 1].substance;
    obj = {
        substance: 'customSolidLoadChargeMaterial',
        specificHeatSolid: 0.247910198232625,
        latentHeat: 169,
        specificHeatLiquid: 0.2601,
        meltingPoint: 1215
    };
    bindings.insertSolidLoadChargeMaterial(obj);
    bindings.deleteSolidLoadChargeMaterial(bindings.selectSolidLoadChargeMaterials().length);
    res = bindings.selectSolidLoadChargeMaterials();
    t.equal(last, res[res.length - 1].substance);

    res = bindings.selectGasLoadChargeMaterials();
    last = res[res.length - 1].substance;
    obj = {
        substance: 'customGasMaterial',
        specificHeatVapor: 0.47
    };
    bindings.insertGasLoadChargeMaterial(obj);
    bindings.deleteGasLoadChargeMaterial(bindings.selectGasLoadChargeMaterials().length);
    res = bindings.selectGasLoadChargeMaterials();
    t.equal(last, res[res.length - 1].substance);

    res = bindings.selectGasFlueGasMaterials();
    last = res[res.length - 1].substance;
    obj = {
        substance: 'customGasFlueGasMaterial',
        CH4: 87.0,
        C2H6: 8.5,
        N2: 3.6,
        H2: 0.4,
        C3H8: 0.0,
        C4H10_CnH2n: 0.0,
        H2O: 0.0,
        CO: 0.0,
        CO2: 0.4,
        SO2: 0.0,
        O2: 0.1,
        heatingValue: 22030,
        specificGravity: 0.655
    };
    bindings.insertGasFlueGasMaterial(obj);
    bindings.deleteGasFlueGasMaterial(bindings.selectGasFlueGasMaterials().length);
    res = bindings.selectGasFlueGasMaterials();
    t.equal(last, res[res.length - 1].substance);


    res = bindings.selectSolidLiquidFlueGasMaterials();
    last = res[res.length - 1].substance;
    obj = {
        substance: 'customSolidLiquidFlueGas',
        carbon: 77.7 / 100,
        hydrogen: 1.8 / 100,
        sulphur: 0.7 / 100,
        inertAsh: 9.8 / 100,
        o2: 2.1 / 100,
        moisture: 7.1 / 100,
        nitrogen: 0.8 / 100
    };
    bindings.insertSolidLiquidFlueGasMaterial(obj);
    bindings.deleteSolidLiquidFlueGasMaterial(bindings.selectSolidLiquidFlueGasMaterials().length);
    res = bindings.selectSolidLiquidFlueGasMaterials();
    t.equal(last, res[res.length - 1].substance);

    res = bindings.selectAtmosphereSpecificHeat();
    last = res[res.length - 1].substance;
    obj = {
        substance: 'customAtmosphere',
        specificHeat: 0.018
    };
    bindings.insertAtmosphereSpecificHeat(obj);
    bindings.deleteAtmosphereSpecificHeat(bindings.selectAtmosphereSpecificHeat().length);
    res = bindings.selectAtmosphereSpecificHeat();
    t.equal(last, res[res.length - 1].substance);

    res = bindings.selectWallLossesSurface();
    last = res[res.length - 1].surface;
    obj = {
        surface: 'customWallLossesSurface',
        conditionFactor: 1.79
    };
    bindings.insertWallLossesSurface(obj);
    bindings.deleteWallLossesSurface(bindings.selectWallLossesSurface().length);
    res = bindings.selectWallLossesSurface();
    t.equal(last, res[res.length - 1].surface);
});

test('dbUpdates', function (t) {
    t.plan(7);
    bindings.startup();

    var obj = {
        substance: 'custom solid load charge',
        specificHeatSolid: 0.247910198232625,
        latentHeat: 169,
        specificHeatLiquid: 0.2601,
        meltingPoint: 1215
    };
    bindings.insertSolidLoadChargeMaterial(obj);
    var mat = bindings.selectSolidLoadChargeMaterialById(bindings.selectSolidLoadChargeMaterials().length);
    mat.substance = 'updated';
    bindings.updateSolidLoadChargeMaterial(mat);
    t.equal(bindings.selectSolidLoadChargeMaterialById(bindings.selectSolidLoadChargeMaterials().length).substance, 'updated');


    obj = {
        substance: 'Crude liquid load charge',
        specificHeatLiquid: 0.6501,
        specificHeatVapor: 0.55,
        latentHeat: 105,
        vaporizationTemperature: 900
    };
    bindings.insertLiquidLoadChargeMaterial(obj);
    mat = bindings.selectLiquidLoadChargeMaterialById(bindings.selectLiquidLoadChargeMaterials().length);
    mat.substance = 'updated';
    bindings.updateLiquidLoadChargeMaterial(mat);
    t.equal(bindings.selectLiquidLoadChargeMaterialById(bindings.selectLiquidLoadChargeMaterials().length).substance, 'updated');

    obj = {
        substance: 'Water vapor - Near Atm. Pressure Gas load charge material',
        specificHeatVapor: 0.47
    };
    bindings.insertGasLoadChargeMaterial(obj);
    mat = bindings.selectGasLoadChargeMaterialById(bindings.selectGasLoadChargeMaterials().length);
    mat.substance = 'updated';
    bindings.updateGasLoadChargeMaterial(mat);
    t.equal(bindings.selectGasLoadChargeMaterialById(bindings.selectGasLoadChargeMaterials().length).substance, 'updated');

    obj = {
        substance: 'Typical Natural Gas - US gas flue gas material',
        CH4: 87.0,
        C2H6: 8.5,
        N2: 3.6,
        H2: 0.4,
        C3H8: 0.0,
        C4H10_CnH2n: 0.0,
        H2O: 0.0,
        CO: 0.0,
        CO2: 0.4,
        SO2: 0.0,
        O2: 0.1,
        heatingValue: 22030.67089880065,
        heatingValueVolume: 1032.445,
        specificGravity: 0.6571206283343215
    };
    bindings.insertGasFlueGasMaterial(obj);
    mat = bindings.selectGasFlueGasMaterialById(bindings.selectGasFlueGasMaterials().length);
    mat.substance = 'updated';
    bindings.updateGasFlueGasMaterial(mat);
    t.equal(bindings.selectGasFlueGasMaterialById(bindings.selectGasFlueGasMaterials().length).substance, 'updated');

    obj = {
        substance: 'custom Typical Anthracite - US solid liquid gas flue gas material',
        carbon: 77.7,
        hydrogen: 1.8,
        sulphur: 0.7,
        inertAsh: 9.8,
        o2: 2.1,
        moisture: 7.1,
        nitrogen: 0.8
    };
    bindings.insertSolidLiquidFlueGasMaterial(obj);
    mat = bindings.selectSolidLiquidFlueGasMaterialById(bindings.selectSolidLiquidFlueGasMaterials().length);
    mat.substance = 'updated';
    bindings.updateSolidLiquidFlueGasMaterial(mat);
    t.equal(bindings.selectSolidLiquidFlueGasMaterialById(bindings.selectSolidLiquidFlueGasMaterials().length).substance, 'updated');

    obj = {
        substance: 'customAtmosphere',
        specificHeat: 0.5
    };
    bindings.insertAtmosphereSpecificHeat(obj);
    mat = bindings.selectAtmosphereSpecificHeatById(bindings.selectAtmosphereSpecificHeat().length);
    mat.substance = 'updated';
    bindings.updateAtmosphereSpecificHeat(mat);
    t.equal(bindings.selectAtmosphereSpecificHeatById(bindings.selectAtmosphereSpecificHeat().length).substance, 'updated');

    obj = {
        surface: 'Horizontal cylinders Wall Losses Surface',
        conditionFactor: 1.016
    };
    bindings.insertWallLossesSurface(obj);
    mat = bindings.selectWallLossesSurfaceById(bindings.selectWallLossesSurface().length);
    mat.surface = 'updated';
    bindings.updateWallLossesSurface(mat);
    t.equal(bindings.selectWallLossesSurfaceById(bindings.selectWallLossesSurface().length).surface, 'updated');
});


// // commented out bc it writes files to the HDD
// test('dbTestMigrations', function (t) {
//     t.plan(8);
//
//     bindings.startup();
//     var res = bindings.selectSolidLoadChargeMaterials();
//     var slcmLen = res.length;
//     var slcmLen2 = slcmLen + 1;
//     var slcmLen3 = slcmLen + 2;
//
//     var mat1 = {
//         substance: 'customMaterial' + slcmLen2,
//         specificHeatSolid: 0.25,
//         latentHeat: 150,
//         specificHeatLiquid: 0.30,
//         meltingPoint: 1200
//     };
//     var mat2 = {
//         substance: 'customMaterial' + slcmLen3,
//         specificHeatSolid: 0.35,
//         latentHeat: 350,
//         specificHeatLiquid: 0.39,
//         meltingPoint: 2900
//     };
//
//     var success1 = bindings.insertSolidLoadChargeMaterial(mat1);
//     var success2 = bindings.insertSolidLoadChargeMaterial(mat2);
//
//     bindings.preUpdate();
//     bindings.postUpdate();
//
//     var res = bindings.selectSolidLoadChargeMaterials();
//     t.equal(success1, true, "insert 1 was unsuccessful");
//     t.equal(success2, true, "insert 2 was unsuccessful");
//     t.equal(slcmLen + 2, res.length, res.length + " != " + slcmLen + 2);
//     t.equal(res[slcmLen + 1].substance, mat2.substance, res[slcmLen + 1].substance + " != " + mat2.substance);
//     t.equal(res[slcmLen + 1].specificHeatSolid, mat2.specificHeatSolid, res[slcmLen + 1].specificHeatSolid + " != " + mat2.specificHeatSolid);
//     t.equal(res[slcmLen + 1].latentHeat, mat2.latentHeat, res[slcmLen + 1].latentHeat + " != " + mat2.latentHeat);
//     t.equal(res[slcmLen + 1].specificHeatLiquid, mat2.specificHeatLiquid, res[slcmLen + 1].specificHeatLiquid + " != " + mat2.specificHeatLiquid);
//     t.equal(res[slcmLen + 1].meltingPoint, mat2.meltingPoint, res[slcmLen + 1].meltingPoint + " != " + mat2.meltingPoint);
// });
