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

test('dbSelectMotorData', function (t) {
    t.plan(25);
    bindings.startup();

    t.type(bindings.selectMotorById, 'function');
    var res = bindings.selectMotorById(1);
    
    var obj = {
        id: 1, hp: 1, synchronousSpeed: 900, poles: 8, nominalEfficiency: 74, efficiencyType: "Energy Efficient", 
        nemaTable: "Table 12-11", enclosureType: "ODP", hz: 60, voltageLimit: 600, catalog: "NEMA MG - 1-2018"
    };

    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.hp, obj.hp, res.hp + " != " + obj.hp);
    t.equal(res.synchronousSpeed, obj.synchronousSpeed, res.synchronousSpeed + " != " + obj.synchronousSpeed);
    t.equal(res.poles, obj.poles, res.poles + " != " + obj.poles);
    t.equal(res.nominalEfficiency, obj.nominalEfficiency, res.nominalEfficiency + " != " + obj.nominalEfficiency);
    t.equal(res.efficiencyType, obj.efficiencyType, res.efficiencyType + " != " + obj.efficiencyType);
    t.equal(res.nemaTable, obj.nemaTable, res.nemaTable + " != " + obj.nemaTable);
    t.equal(res.enclosureType, obj.enclosureType, res.enclosureType + " != " + obj.enclosureType);
    t.equal(res.hz, obj.hz, res.hz + " != " + obj.hz);
    t.equal(res.voltageLimit, obj.voltageLimit, res.voltageLimit + " != " + obj.voltageLimit);
    t.equal(res.catalog, obj.catalog, res.catalog + " != " + obj.catalog);

    t.type(bindings.selectMotors, 'function');
    res = bindings.selectMotors();

    t.equal(res.length, 954, "array is not size 954");
    t.equal(res[0].id, obj.id, res[0].id + " != " + obj.id);
    t.equal(res[0].hp, obj.hp, res[0].hp + " != " + obj.hp);
    t.equal(res[0].synchronousSpeed, obj.synchronousSpeed, res[0].synchronousSpeed + " != " + obj.synchronousSpeed);
    t.equal(res[0].poles, obj.poles, res[0].poles + " != " + obj.poles);
    t.equal(res[0].nominalEfficiency, obj.nominalEfficiency, res[0].nominalEfficiency + " != " + obj.nominalEfficiency);
    t.equal(res[0].efficiencyType, obj.efficiencyType, res[0].efficiencyType + " != " + obj.efficiencyType);
    t.equal(res[0].nemaTable, obj.nemaTable, res[0].nemaTable + " != " + obj.nemaTable);
    t.equal(res[0].enclosureType, obj.enclosureType, res[0].enclosureType + " != " + obj.enclosureType);
    t.equal(res[0].hz, obj.hz, res[0].hz + " != " + obj.hz);
    t.equal(res[0].voltageLimit, obj.voltageLimit, res[0].voltageLimit + " != " + obj.voltageLimit);
    t.equal(res[0].catalog, obj.catalog, res[0].catalog + " != " + obj.catalog);
});

test('dbInsertMotor', function (t) {
    t.plan(12);
    bindings.startup();

    t.type(bindings.insertPump, 'function');

    var obj = {
        hp: 1, synchronousSpeed: 3800, poles: 4, nominalEfficiency: 75.8, efficiencyType: "Energy Efficient", 
        nemaTable: "Table 12-11", enclosureType: "TEFC", hz: 60, voltageLimit: 600, catalog: "NEMA MG - 1-2018"
    };

    var res = bindings.selectMotors();
    var size = res.length;
    bindings.insertMotor(obj);
    res = bindings.selectMotors();

    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    //shouldn't have id on set..?
    //t.equal(res[size].id, obj.id, res[size].id + " != " + obj.id);
    t.equal(res[size].hp, obj.hp, res[size].hp + " != " + obj.hp);
    t.equal(res[size].synchronousSpeed, obj.synchronousSpeed, res[size].synchronousSpeed + " != " + obj.synchronousSpeed);
    t.equal(res[size].poles, obj.poles, res[size].poles + " != " + obj.poles);
    t.equal(res[size].nominalEfficiency, obj.nominalEfficiency, res[size].nominalEfficiency + " != " + obj.nominalEfficiency);
    t.equal(res[size].efficiencyType, obj.efficiencyType, res[size].efficiencyType + " != " + obj.efficiencyType);
    t.equal(res[size].nemaTable, obj.nemaTable, res[size].nemaTable + " != " + obj.nemaTable);
    t.equal(res[size].enclosureType, obj.enclosureType, res[size].enclosureType + " != " + obj.enclosureType);
    t.equal(res[size].hz, obj.hz, res[size].hz + " != " + obj.hz);
    t.equal(res[size].voltageLimit, obj.voltageLimit, res[size].voltageLimit + " != " + obj.voltageLimit);
    t.equal(res[size].catalog, obj.catalog, res[size].catalog + " != " + obj.catalog);
});

test('dbSelectPumpData', function (t) {
    t.plan(97); //2
    bindings.startup();

    t.type(bindings.selectPumpById, 'function');
    var res = bindings.selectPumpById(1);
    
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

    //t.equal(res, obj, res.toString() + " != " + obj.toString());
    t.equal(res.id, obj.id, res.id + " != " + obj.id);
    t.equal(res.manufacturer, obj.manufacturer, res.manufacturer + " != " + obj.manufacturer);
    t.equal(res.model, obj.model, res.model + " != " + obj.model);
    t.equal(res.type, obj.type, res.type + " != " + obj.type);
    t.equal(res.serialNumber, obj.serialNumber, res.serialNumber + " != " + obj.serialNumber);
    t.equal(res.status, obj.status, res.status + " != " + obj.status);
    t.equal(res.pumpType, obj.pumpType, res.pumpType + " != " + obj.pumpType);
    t.equal(res.radialBearingType, obj.radialBearingType, res.radialBearingType + " != " + obj.radialBearingType);
    t.equal(res.thrustBearingType, obj.thrustBearingType, res.thrustBearingType + " != " + obj.thrustBearingType);
    t.equal(res.shaftOrientation, obj.shaftOrientation, res.shaftOrientation + " != " + obj.shaftOrientation);
    t.equal(res.shaftSealType, obj.shaftSealType, res.shaftSealType + " != " + obj.shaftSealType);
    t.equal(res.fluidType, obj.fluidType, res.fluidType + " != " + obj.fluidType);
    t.equal(res.priority, obj.priority, res.priority + " != " + obj.priority);
    t.equal(res.driveType, obj.driveType, res.driveType + " != " + obj.driveType);
    t.equal(res.flangeConnectionClass, obj.flangeConnectionClass, res.flangeConnectionClass + " != " + obj.flangeConnectionClass);
    t.equal(res.flangeConnectionSize, obj.flangeConnectionSize, res.flangeConnectionSize + " != " + obj.flangeConnectionSize);
    t.equal(res.numShafts, obj.numShafts, res.numShafts + " != " + obj.numShafts);
    t.equal(res.speed, obj.speed, res.speed + " != " + obj.speed);
    t.equal(res.numStages, obj.numStages, res.numStages + " != " + obj.numStages);
    t.equal(res.yearlyOperatingHours, obj.yearlyOperatingHours, res.yearlyOperatingHours + " != " + obj.yearlyOperatingHours);
    t.equal(res.yearInstalled, obj.yearInstalled, res.yearInstalled + " != " + obj.yearInstalled);
    t.equal(res.finalMotorRpm, obj.finalMotorRpm, res.finalMotorRpm + " != " + obj.finalMotorRpm);
    t.equal(res.inletDiameter, obj.inletDiameter, res.inletDiameter + " != " + obj.inletDiameter);
    t.equal(res.weight, obj.weight, res.weight + " != " + obj.weight);
    t.equal(res.outletDiameter, obj.outletDiameter, res.outletDiameter + " != " + obj.outletDiameter);
    t.equal(res.percentageOfSchedule, obj.percentageOfSchedule, res.percentageOfSchedule + " != " + obj.percentageOfSchedule);
    t.equal(res.dailyPumpCapacity, obj.dailyPumpCapacity, res.dailyPumpCapacity + " != " + obj.dailyPumpCapacity);
    t.equal(res.measuredPumpCapacity, obj.measuredPumpCapacity, res.measuredPumpCapacity + " != " + obj.measuredPumpCapacity);
    t.equal(res.pumpPerformance, obj.pumpPerformance, res.pumpPerformance + " != " + obj.pumpPerformance);
    t.equal(res.staticSuctionHead, obj.staticSuctionHead, res.staticSuctionHead + " != " + obj.staticSuctionHead);
    t.equal(res.staticDischargeHead, obj.staticDischargeHead, res.staticDischargeHead + " != " + obj.staticDischargeHead);
    t.equal(res.fluidDensity, obj.fluidDensity, res.fluidDensity + " != " + obj.fluidDensity);
    t.equal(res.lengthOfDischargePipe, obj.lengthOfDischargePipe, res.lengthOfDischargePipe + " != " + obj.lengthOfDischargePipe);
    t.equal(res.pipeDesignFrictionLosses, obj.pipeDesignFrictionLosses, res.pipeDesignFrictionLosses + " != " + obj.pipeDesignFrictionLosses);
    t.equal(res.maxWorkingPressure, obj.maxWorkingPressure, res.maxWorkingPressure + " != " + obj.maxWorkingPressure);
    t.equal(res.maxAmbientTemperature, obj.maxAmbientTemperature, res.maxAmbientTemperature + " != " + obj.maxAmbientTemperature);
    t.equal(res.maxSuctionLift, obj.maxSuctionLift, res.maxSuctionLift + " != " + obj.maxSuctionLift);
    t.equal(res.displacement, obj.displacement, res.displacement + " != " + obj.displacement);
    t.equal(res.startingTorque, obj.startingTorque, res.startingTorque + " != " + obj.startingTorque);
    t.equal(res.ratedSpeed, obj.ratedSpeed, res.ratedSpeed + " != " + obj.ratedSpeed);
    t.equal(res.shaftDiameter, obj.shaftDiameter, res.shaftDiameter + " != " + obj.shaftDiameter);
    t.equal(res.impellerDiameter, obj.impellerDiameter, res.impellerDiameter + " != " + obj.impellerDiameter);
    t.equal(res.efficiency, obj.efficiency, res.efficiency + " != " + obj.efficiency);
    t.equal(res.output60Hz, obj.output60Hz, res.output60Hz + " != " + obj.output60Hz);
    t.equal(res.minFlowSize, obj.minFlowSize, res.minFlowSize + " != " + obj.minFlowSize);
    t.equal(res.pumpSize, obj.pumpSize, res.pumpSize + " != " + obj.pumpSize);
    t.equal(res.outOfService, obj.outOfService, res.outOfService + " != " + obj.outOfService);


    t.type(bindings.selectPumps, 'function');
    res = bindings.selectPumps();

    t.equal(res.length, 1, "array is not of size 1");
    t.equal(res[0].id, obj.id, res[0].id + " != " + obj.id);
    t.equal(res[0].manufacturer, obj.manufacturer, res[0].manufacturer + " != " + obj.manufacturer);
    t.equal(res[0].model, obj.model, res[0].model + " != " + obj.model);
    t.equal(res[0].type, obj.type, res[0].type + " != " + obj.type);
    t.equal(res[0].serialNumber, obj.serialNumber, res[0].serialNumber + " != " + obj.serialNumber);
    t.equal(res[0].status, obj.status, res[0].status + " != " + obj.status);
    t.equal(res[0].pumpType, obj.pumpType, res[0].pumpType + " != " + obj.pumpType);
    t.equal(res[0].radialBearingType, obj.radialBearingType, res[0].radialBearingType + " != " + obj.radialBearingType);
    t.equal(res[0].thrustBearingType, obj.thrustBearingType, res[0].thrustBearingType + " != " + obj.thrustBearingType);
    t.equal(res[0].shaftOrientation, obj.shaftOrientation, res[0].shaftOrientation + " != " + obj.shaftOrientation);
    t.equal(res[0].shaftSealType, obj.shaftSealType, res[0].shaftSealType + " != " + obj.shaftSealType);
    t.equal(res[0].fluidType, obj.fluidType, res[0].fluidType + " != " + obj.fluidType);
    t.equal(res[0].priority, obj.priority, res[0].priority + " != " + obj.priority);
    t.equal(res[0].driveType, obj.driveType, res[0].driveType + " != " + obj.driveType);
    t.equal(res[0].flangeConnectionClass, obj.flangeConnectionClass, res[0].flangeConnectionClass + " != " + obj.flangeConnectionClass);
    t.equal(res[0].flangeConnectionSize, obj.flangeConnectionSize, res[0].flangeConnectionSize + " != " + obj.flangeConnectionSize);
    t.equal(res[0].numShafts, obj.numShafts, res[0].numShafts + " != " + obj.numShafts);
    t.equal(res[0].speed, obj.speed, res[0].speed + " != " + obj.speed);
    t.equal(res[0].numStages, obj.numStages, res[0].numStages + " != " + obj.numStages);
    t.equal(res[0].yearlyOperatingHours, obj.yearlyOperatingHours, res[0].yearlyOperatingHours + " != " + obj.yearlyOperatingHours);
    t.equal(res[0].yearlyInstalled, obj.yearlyInstalled, res[0].yearlyInstalled + " != " + obj.yearlyInstalled);
    t.equal(res[0].finalMotorRpm, obj.finalMotorRpm, res[0].finalMotorRpm + " != " + obj.finalMotorRpm);
    t.equal(res[0].inletDiameter, obj.inletDiameter, res[0].inletDiameter + " != " + obj.inletDiameter);
    t.equal(res[0].weight, obj.weight, res[0].weight + " != " + obj.weight);
    t.equal(res[0].outletDiameter, obj.outletDiameter, res[0].outletDiameter + " != " + obj.outletDiameter);
    t.equal(res[0].percentageOfSchedule, obj.percentageOfSchedule, res[0].percentageOfSchedule + " != " + obj.percentageOfSchedule);
    t.equal(res[0].dailyPumpCapacity, obj.dailyPumpCapacity, res[0].dailyPumpCapacity + " != " + obj.dailyPumpCapacity);
    t.equal(res[0].measuredPumpCapacity, obj.measuredPumpCapacity, res[0].measuredPumpCapacity + " != " + obj.measuredPumpCapacity);
    t.equal(res[0].pumpPerformance, obj.pumpPerformance, res[0].pumpPerformance + " != " + obj.pumpPerformance);
    t.equal(res[0].staticSuctionHead, obj.staticSuctionHead, res[0].staticSuctionHead + " != " + obj.staticSuctionHead);
    t.equal(res[0].staticDischargeHead, obj.staticDischargeHead, res[0].staticDischargeHead + " != " + obj.staticDischargeHead);
    t.equal(res[0].fluidDensity, obj.fluidDensity, res[0].fluidDensity + " != " + obj.fluidDensity);
    t.equal(res[0].lengthOfDischargePipe, obj.lengthOfDischargePipe, res[0].lengthOfDischargePipe + " != " + obj.lengthOfDischargePipe);
    t.equal(res[0].pipeDesignFrictionLosses, obj.pipeDesignFrictionLosses, res[0].pipeDesignFrictionLosses + " != " + obj.pipeDesignFrictionLosses);
    t.equal(res[0].maxWorkingPressure, obj.maxWorkingPressure, res[0].maxWorkingPressure + " != " + obj.maxWorkingPressure);
    t.equal(res[0].maxAmbientTemperature, obj.maxAmbientTemperature, res[0].maxAmbientTemperature + " != " + obj.maxAmbientTemperature);
    t.equal(res[0].maxSuctionLift, obj.maxSuctionLift, res[0].maxSuctionLift + " != " + obj.maxSuctionLift);
    t.equal(res[0].displacement, obj.displacement, res[0].displacement + " != " + obj.displacement);
    t.equal(res[0].startingTorque, obj.startingTorque, res[0].startingTorque + " != " + obj.startingTorque);
    t.equal(res[0].ratedSpeed, obj.ratedSpeed, res[0].ratedSpeed + " != " + obj.ratedSpeed);
    t.equal(res[0].shaftDiameter, obj.shaftDiameter, res[0].shaftDiameter + " != " + obj.shaftDiameter);
    t.equal(res[0].impellerDiameter, obj.impellerDiameter, res[0].impellerDiameter + " != " + obj.impellerDiameter);
    t.equal(res[0].efficiency, obj.efficiency, res[0].efficiency + " != " + obj.efficiency);
    t.equal(res[0].output60Hz, obj.output60Hz, res[0].output60Hz + " != " + obj.output60Hz);
    t.equal(res[0].minFlowSize, obj.minFlowSize, res[0].minFlowSize + " != " + obj.minFlowSize);
    t.equal(res[0].pumpSize, obj.pumpSize, res[0].pumpSize + " != " + obj.pumpSize);
    t.equal(res[0].outOfService, obj.outOfService, res[0].outOfService + " != " + obj.outOfService);
});

test('dbInsertPump', function (t) {
    t.plan(49);
    bindings.startup();

    t.type(bindings.insertPump, 'function');
    
    var obj = {
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

    var res = bindings.selectPumps();
    var size = res.length;
    bindings.insertPump(obj);
    res = bindings.selectPumps();

    t.equal(res.length, size + 1, res.length + " != " + (size + 1));
    t.equal(res[size].id, obj.id, res[size].id + " != " + obj.id);
    t.equal(res[size].manufacturer, obj.manufacturer, res[size].manufacturer + " != " + obj.manufacturer);
    t.equal(res[size].model, obj.model, res[size].model + " != " + obj.model);
    t.equal(res[size].type, obj.type, res[size].type + " != " + obj.type);
    t.equal(res[size].serialNumber, obj.serialNumber, res[size].serialNumber + " != " + obj.serialNumber);
    t.equal(res[size].status, obj.status, res[size].status + " != " + obj.status);
    t.equal(res[size].pumpType, obj.pumpType, res[size].pumpType + " != " + obj.pumpType);
    t.equal(res[size].radialBearingType, obj.radialBearingType, res[size].radialBearingType + " != " + obj.radialBearingType);
    t.equal(res[size].thrustBearingType, obj.thrustBearingType, res[size].thrustBearingType + " != " + obj.thrustBearingType);
    t.equal(res[size].shaftOrientation, obj.shaftOrientation, res[size].shaftOrientation + " != " + obj.shaftOrientation);
    t.equal(res[size].shaftSealType, obj.shaftSealType, res[size].shaftSealType + " != " + obj.shaftSealType);
    t.equal(res[size].fluidType, obj.fluidType, res[size].fluidType + " != " + obj.fluidType);
    t.equal(res[size].priority, obj.priority, res[size].priority + " != " + obj.priority);
    t.equal(res[size].driveType, obj.driveType, res[size].driveType + " != " + obj.driveType);
    t.equal(res[size].flangeConnectionClass, obj.flangeConnectionClass, res[size].flangeConnectionClass + " != " + obj.flangeConnectionClass);
    t.equal(res[size].flangeConnectionSize, obj.flangeConnectionSize, res[size].flangeConnectionSize + " != " + obj.flangeConnectionSize);
    t.equal(res[size].numShafts, obj.numShafts, res[size].numShafts + " != " + obj.numShafts);
    t.equal(res[size].speed, obj.speed, res[size].speed + " != " + obj.speed);
    t.equal(res[size].numStages, obj.numStages, res[size].numStages + " != " + obj.numStages);
    t.equal(res[size].yearlyOperatingHours, obj.yearlyOperatingHours, res[size].yearlyOperatingHours + " != " + obj.yearlyOperatingHours);
    t.equal(res[size].yearInstalled, obj.yearInstalled, res[size].yearInstalled + " != " + obj.yearInstalled);
    t.equal(res[size].finalMotorRpm, obj.finalMotorRpm, res[size].finalMotorRpm + " != " + obj.finalMotorRpm);
    t.equal(res[size].inletDiameter, obj.inletDiameter, res[size].inletDiameter + " != " + obj.inletDiameter);
    t.equal(res[size].weight, obj.weight, res[size].weight + " != " + obj.weight);
    t.equal(res[size].outletDiameter, obj.outletDiameter, res[size].outletDiameter + " != " + obj.outletDiameter);
    t.equal(res[size].percentageOfSchedule, obj.percentageOfSchedule, res[size].percentageOfSchedule + " != " + obj.percentageOfSchedule);
    t.equal(res[size].dailyPumpCapacity, obj.dailyPumpCapacity, res[size].dailyPumpCapacity + " != " + obj.dailyPumpCapacity);
    t.equal(res[size].measuredPumpCapacity, obj.measuredPumpCapacity, res[size].measuredPumpCapacity + " != " + obj.measuredPumpCapacity);
    t.equal(res[size].pumpPerformance, obj.pumpPerformance, res[size].pumpPerformance + " != " + obj.pumpPerformance);
    t.equal(res[size].staticSuctionHead, obj.staticSuctionHead, res[size].staticSuctionHead + " != " + obj.staticSuctionHead);
    t.equal(res[size].staticDischargeHead, obj.staticDischargeHead, res[size].staticDischargeHead + " != " + obj.staticDischargeHead);
    t.equal(res[size].fluidDensity, obj.fluidDensity, res[size].fluidDensity + " != " + obj.fluidDensity);
    t.equal(res[size].lengthOfDischargePipe, obj.lengthOfDischargePipe, res[size].lengthOfDischargePipe + " != " + obj.lengthOfDischargePipe);
    t.equal(res[size].pipeDesignFrictionLosses, obj.pipeDesignFrictionLosses, res[size].pipeDesignFrictionLosses + " != " + obj.pipeDesignFrictionLosses);
    t.equal(res[size].maxWorkingPressure, obj.maxWorkingPressure, res[size].maxWorkingPressure + " != " + obj.maxWorkingPressure);
    t.equal(res[size].maxAmbientTemperature, obj.maxAmbientTemperature, res[size].maxAmbientTemperature + " != " + obj.maxAmbientTemperature);
    t.equal(res[size].maxSuctionLift, obj.maxSuctionLift, res[size].maxSuctionLift + " != " + obj.maxSuctionLift);
    t.equal(res[size].displacement, obj.displacement, res[size].displacement + " != " + obj.displacement);
    t.equal(res[size].startingTorque, obj.startingTorque, res[size].startingTorque + " != " + obj.startingTorque);
    t.equal(res[size].ratedSpeed, obj.ratedSpeed, res[size].ratedSpeed + " != " + obj.ratedSpeed);
    t.equal(res[size].shaftDiameter, obj.shaftDiameter, res[size].shaftDiameter + " != " + obj.shaftDiameter);
    t.equal(res[size].impellerDiameter, obj.impellerDiameter, res[size].impellerDiameter + " != " + obj.impellerDiameter);
    t.equal(res[size].efficiency, obj.efficiency, res[size].efficiency + " != " + obj.efficiency);
    t.equal(res[size].output60Hz, obj.output60Hz, res[size].output60Hz + " != " + obj.output60Hz);
    t.equal(res[size].minFlowSize, obj.minFlowSize, res[size].minFlowSize + " != " + obj.minFlowSize);
    t.equal(res[size].pumpSize, obj.pumpSize, res[size].pumpSize + " != " + obj.pumpSize);
    t.equal(res[size].outOfService, obj.outOfService, res[size].outOfService + " != " + obj.outOfService);
});

test('dbDeletions', function (t) {
    t.plan(9);
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

    res = bindings.selectPumps();
    last = res[res.length - 1].id;
    obj = {
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
    bindings.insertPump(obj);
    bindings.deletePump(bindings.selectPumps().length);
    res = bindings.selectPumps();
    t.equal(last, res[res.length - 1].id);

    res = bindings.selectMotors();
    last = res[res.length - 1].id;
    obj = {
        id: 162, hp: 1, synchronousSpeed: 3800, poles: 4, nominalEfficiency: 75.8, efficiencyType: "Energy Efficient", 
        nemaTable: "Table 12-11", enclosureType: "TEFC", hz: 60, voltageLimit: 600, catalog: "NEMA MG - 1-2018"
    };
    bindings.insertMotor(obj);
    bindings.deleteMotor(bindings.selectMotors().length);
    res = bindings.selectMotors();
    t.equal(last, res[res.length - 1].id);
});

test('dbUpdates', function (t) {
    t.plan(9);
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

    obj = {
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
    bindings.insertPump(obj);
    pump = bindings.selectPumpById(bindings.selectPumps().length);
    pump.manufacturer = 'updated';
    bindings.updatePump(pump);
    t.equal(bindings.selectPumpById(bindings.selectPumps().length).manufacturer, 'updated');

    obj = {
        id: 162, hp: 1, synchronousSpeed: 3800, poles: 4, nominalEfficiency: 75.8, efficiencyType: "Energy Efficient", 
        nemaTable: "Table 12-11", enclosureType: "TEFC", hz: 60, voltageLimit: 600, catalog: "NEMA MG - 1-2018"
    };
    bindings.insertMotor(obj);
    motor = bindings.selectMotorById(bindings.selectMotors().length);
    motor.efficiencyType = 'updated';
    bindings.updateMotor(motor);
    t.equal(bindings.selectMotorById(bindings.selectMotors().length).efficiencyType, 'updated');
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
