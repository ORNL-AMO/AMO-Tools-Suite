const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'db'});

test('dbSelectSolidMaterial', function (t) {
    t.plan(15);
    bindings.startup();
    t.type(bindings.selectSolidMaterialById, 'function');

    var res = bindings.selectSolidMaterialById(1);
    var obj = {
        id: 1,
        substance: 'Aluminum',
        specificHeatSolid: 0.2479,
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


    t.type(bindings.selectSolidMaterial, 'function');

    var obj2 = {
        id: 40,
        substance: 'Ladle Refractory',
        specificHeatSolid: 0.2501,
        latentHeat: 425,
        specificHeatLiquid: 0.26,
        meltingPoint: 5000
    };

    res = bindings.selectSolidMaterial();
    t.equal(res.length, 40, "array is not of size 40");
    t.equal(res[39].id, obj2.id, res[39].id + " != " + obj2.id);
    t.equal(res[39].substance, obj2.substance, res[39].substance + " != " + obj2.substance);
    t.equal(res[39].specificHeatSolid, obj2.specificHeatSolid, res[39].specificHeatSolid + " != " + obj2.specificHeatSolid);
    t.equal(res[39].latentHeat, obj2.latentHeat, res[39].latentHeat + " != " + obj2.latentHeat);
    t.equal(res[39].specificHeatLiquid, obj2.specificHeatLiquid, res[39].specificHeatLiquid + " != " + obj2.specificHeatLiquid);
    t.equal(res[39].meltingPoint, obj2.meltingPoint, res[39].meltingPoint + " != " + obj2.meltingPoint);
});

test('dbSelectLiquidMaterial', function (t) {
    t.plan(13);
    bindings.startup();
    t.type(bindings.selectLiquidMaterialById, 'function');

    var res = bindings.selectLiquidMaterialById(1);
    var obj = {
        substance: 'Crude',
        specificHeatLiquid: 0.6501,
        specificHeatVapor: 0.55,
        latentHeat: 105,
        vaporizationTemperature: 900
    };

    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.specificHeatLiquid, obj.specificHeatLiquid, res.specificHeatLiquid + " != " + obj.specificHeatLiquid);
    t.equal(res.specificHeatVapor, obj.specificHeatVapor, res.specificHeatVapor + " != " + obj.specificHeatVapor);
    t.equal(res.latentHeat, obj.latentHeat, res.latentHeat + " != " + obj.latentHeat);
    t.equal(res.vaporizationTemperature, obj.vaporizationTemperature, res.vaporizationTemperature + " != " + obj.vaporizationTemperature);


    t.type(bindings.selectLiquidMaterial, 'function');

    var obj2 = {
        substance: 'Kerosene',
        specificHeatLiquid: 0.5701,
        specificHeatVapor: 0.62,
        latentHeat: 260,
        vaporizationTemperature:260
    };

    res = bindings.selectLiquidMaterial();
    t.equal(res.length, 13, "array is not of size 13");
    t.equal(res[12].substance, obj2.substance, res[12].substance + " != " + obj2.substance);
    t.equal(res[12].specificHeatVapor, obj2.specificHeatVapor, res[12].specificHeatVapor + " != " + obj2.specificHeatVapor);
    t.equal(res[12].latentHeat, obj2.latentHeat, res[12].latentHeat + " != " + obj2.latentHeat);
    t.equal(res[12].specificHeatLiquid, obj2.specificHeatLiquid, res[12].specificHeatLiquid + " != " + obj2.specificHeatLiquid);
    t.equal(res[12].vaporizationTemperature, obj2.vaporizationTemperature, res[12].vaporizationTemperature + " != " + obj2.vaporizationTemperature);
});

test('dbSelectGasMaterial', function (t) {
    t.plan(7);
    bindings.startup();

    t.type(bindings.selectGasMaterialById, 'function');
    var res = bindings.selectGasMaterialById(1);
    var obj = {
        substance: 'Water vapor - near atm. pressure',
        specificHeatVapor: 0.47
    };

    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.specificHeatVapor, obj.specificHeatVapor, res.specificHeatVapor + " != " + obj.specificHeatVapor);

    t.type(bindings.selectGasMaterial, 'function');
    res = bindings.selectGasMaterial();
    var obj2 = {
        substance: 'Hydrogen - low pressure',
        specificHeatVapor: 3.45
    };

    t.equal(res.length, 10, "array is not of size 10");
    t.equal(res[9].substance, obj2.substance, res[9].substance + " != " + obj2.substance);
    t.equal(res[9].specificHeatVapor, obj2.specificHeatVapor, res[9].specificHeatVapor + " != " + obj2.specificHeatVapor);
});

test('dbGasFlueGasMaterial', function (t) {
    t.plan(21);
    bindings.startup();

    t.type(bindings.selectFlueGasMaterialGasById, 'function');
    var res = bindings.selectFlueGasMaterialGasById(1);

    var obj = {
        substance: 'Natural Gas Pennsylvania',
        CH4: 83.4,
        C2H6: 15.8,
        N2: 0.8,
        H2: 0.0,
        C3H8: 0.0,
        C4H10_CnH2n: 0.0,
        H2O: 0.0,
        CO: 0.0,
        CO2: 0.0,
        SO2: 0.0,
        O2: 0.0
    };

    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.CH4, obj.CH4, res.CH4 + " != " + obj.CH4);
    t.equal(res.C2H6, obj.C2H6, res.C2H6 + " != " + obj.C2H6);
    t.equal(res.N2, obj.N2, res.N2 + " != " + obj.N2);
    t.equal(res.H2, obj.H2, res.H2 + " != " + obj.H2);
    t.equal(res.O2, obj.O2, res.O2 + " != " + obj.O2);

    t.type(bindings.selectFlueGasMaterialGas, 'function');
    res = bindings.selectFlueGasMaterialGas();
    var obj2 = {
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
        O2: 0.0
    };

    t.equal(res.length, 7, "array is not of size 7");
    t.equal(res[6].substance, obj2.substance, res[6].substance + " != " + obj2.substance);
    t.equal(res[6].CH4, obj2.CH4, res[6].CH4 + " != " + obj2.CH4);
    t.equal(res[6].C2H6, obj2.C2H6, res[6].C2H6 + " != " + obj2.C2H6);
    t.equal(res[6].N2, obj2.N2, res[6].N2 + " != " + obj2.N2);
    t.equal(res[6].H2, obj2.H2, res[6].H2 + " != " + obj2.H2);
    t.equal(res[6].C3H8, obj2.C3H8, res[6].C3H8 + " != " + obj2.C3H8);
    t.equal(res[6].C4H10_CnH2n, obj2.C4H10_CnH2n, res[6].C4H10_CnH2n + " != " + obj2.C4H10_CnH2n);
    t.equal(res[6].H2O, obj2.H2O, res[6].H2O + " != " + obj2.H2O);
    t.equal(res[6].CO, obj2.CO, res[6].CO + " != " + obj2.CO);
    t.equal(res[6].CO2, obj2.CO2, res[6].CO2 + " != " + obj2.CO2);
    t.equal(res[6].SO2, obj2.SO2, res[6].SO2 + " != " + obj2.SO2);
    t.equal(res[6].O2, obj2.O2, res[6].O2 + " != " + obj2.O2);
});

test('dbSolidLiquidFlueGasMaterial', function (t) {
    t.plan(19);
    bindings.startup();
    t.type(bindings.selectFlueGasMaterialSolidLiquidById, 'function');

    res = bindings.selectFlueGasMaterialSolidLiquidById(1);
    var obj = {
        substance: 'Anthracite',
        carbon: 83.7 / 100,
        hydrogen: 1.9 / 100,
        sulphur: 0.9 / 100,
        inertAsh: 0.7 / 100,
        o2: 2.3 / 100,
        moisture: 0 / 100,
        nitrogen: 10.5 / 100
    };

    t.equal(res.substance, obj.substance, res.substance + " != " + obj.substance);
    t.equal(res.carbon, obj.carbon, res.carbon + " != " + obj.carbon);
    t.equal(res.hydrogen, obj.hydrogen, res.hydrogen + " != " + obj.hydrogen);
    t.equal(res.sulphur, obj.sulphur, res.sulphur + " != " + obj.sulphur);
    t.equal(res.inertAsh, obj.inertAsh, res.inertAsh + " != " + obj.inertAsh);
    t.equal(res.o2, obj.o2, res.o2 + " != " + obj.o2);
    t.equal(res.moisture, obj.moisture, res.moisture + " != " + obj.moisture);
    t.equal(res.nitrogen, obj.nitrogen, res.nitrogen + " != " + obj.nitrogen);

    t.type(bindings.selectFlueGasMaterialSolidLiquid, 'function');
    res = bindings.selectFlueGasMaterialSolidLiquid();
    var obj2 = {
        substance: 'Anthracite',
        carbon: 83.7 / 100,
        hydrogen: 1.9 / 100,
        sulphur: 0.9 / 100,
        inertAsh: 0.7 / 100,
        o2: 2.3 / 100,
        moisture: 0 / 100,
        nitrogen: 10.5 / 100
    };

    t.equal(res.length, 19, "array is not of size 19");
    t.equal(res[0].substance, obj2.substance, res[0].substance + " != " + obj2.substance);
    t.equal(res[0].carbon, obj2.carbon, res[0].carbon + " != " + obj2.carbon);
    t.equal(res[0].hydrogen, obj2.hydrogen, res[0].hydrogen + " != " + obj2.hydrogen);
    t.equal(res[0].sulphur, obj2.sulphur, res[0].sulphur + " != " + obj2.sulphur);
    t.equal(res[0].inertAsh, obj2.inertAsh, res[0].inertAsh + " != " + obj2.inertAsh);
    t.equal(res[0].o2, obj2.o2, res[0].o2 + " != " + obj2.o2);
    t.equal(res[0].moisture, obj2.moisture, res[0].moisture + " != " + obj2.moisture);
    t.equal(res[0].nitrogen, obj2.nitrogen, res[0].nitrogen + " != " + obj2.nitrogen);
});