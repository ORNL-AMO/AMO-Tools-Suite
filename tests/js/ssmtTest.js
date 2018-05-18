const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'ssmt'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('steamPropertiesData', function (t) {
    t.plan(12);

    var input = {
        "pressure": 5,
        "wantEntropy": true
    };

    var res = bindings.steamPropertiesData(input);

    var data = res.results;


    input.wantEntropy = false;
    input.temperature = 300;

    res = bindings.steamPropertiesData(input);

    var otherData = res.results;


});

test('saturatedPropertiesGivenTemperature', function (t) {
    t.plan(12);
    t.type(bindings.saturatedPropertiesGivenTemperature, 'function');

    var inp = {};

    inp.saturatedTemperature = 300;

    var res = bindings.saturatedPropertiesGivenTemperature(inp);

    t.equal(rnd(res.saturatedPressure), rnd(0.0035365894130130106), 'res.saturatedPressure is ' + res.saturatedPressure);

    t.equal(res.saturatedTemperature, 300, 'res.saturatedTemperature is ' + res.saturatedTemperature);

    t.equal(rnd(res.liquidEnthalpy), rnd(112.57499081240724), 'res.liquidEnthalpy is ' + res.liquidEnthalpy);

    t.equal(rnd(res.gasEnthalpy), rnd(2549.8930083073265), 'res.gasEnthalpy is '+ res.gasEnthalpy);

    t.equal(rnd(res.evaporationEnthalpy), rnd(2437.3180174949193), 'res.evaporationEnthalpy is ' + res.evaporationEnthalpy);

    t.equal(rnd(res.liquidEntropy), rnd(0.3931236014741), 'res.liquidEntropy is ' + res.liquidEntropy);

    t.equal(rnd(res.gasEntropy), rnd(8.517536685028846), 'res.gasEntropy is '+ res.gasEntropy);

    t.equal(rnd(res.evaporationEntropy), rnd(8.124413083554746), 'res.evaporationEntropy is ' + res.evaporationEntropy);

    t.equal(rnd(res.liquidVolume), rnd(0.0010034979299339492), 'res.liquidVolume is ' + res.liquidVolume);

    t.equal(rnd(res.gasVolume), rnd(39.08205832377987), 'res.gasVolume is '+ res.gasVolume);

    t.equal(rnd(res.evaporationVolume), rnd(39.08105482584993), 'res.evaporationVolume is ' + res.evaporationVolume);

});

test('saturatedPropertiesGivenPressure', function (t) {
    t.plan(12);
    t.type(bindings.saturatedPropertiesGivenPressure, 'function');

    var inp = {};

    inp.saturatedPressure = 20;

    var res = bindings.saturatedPropertiesGivenPressure(inp);

    t.equal(res.saturatedPressure, 20, 'res.saturatedPressure is ' + res.saturatedPressure);

    t.equal(rnd(res.saturatedTemperature), rnd(638.8959115457051), 'res.saturatedTemperature is ' + res.saturatedTemperature);

    t.equal(rnd(res.liquidEnthalpy), rnd(1827.1006242178723), 'res.liquidEnthalpy is ' + res.liquidEnthalpy);

    t.equal(rnd(res.gasEnthalpy), rnd(2421.680542687896), 'res.gasEnthalpy is '+ res.gasEnthalpy);

    t.equal(rnd(res.evaporationEnthalpy), rnd(594.5799184700236), 'res.evaporationEnthalpy is ' + res.evaporationEnthalpy);

    t.equal(rnd(res.liquidEntropy), rnd(4.015381593120578), 'res.liquidEntropy is ' + res.liquidEntropy);

    t.equal(rnd(res.gasEntropy), rnd(4.946001326758373), 'res.gasEntropy is '+ res.gasEntropy);

    t.equal(rnd(res.evaporationEntropy), rnd(0.930619733637795), 'res.evaporationEntropy is ' + res.evaporationEntropy);

    t.equal(rnd(res.liquidVolume), rnd(0.0020386472456956663), 'res.liquidVolume is ' + res.liquidVolume);

    t.equal(rnd(res.gasVolume), rnd(0.005936854102266306), 'res.gasVolume is '+ res.gasVolume);

    t.equal(rnd(res.evaporationVolume), rnd(0.0038982068565706395), 'res.evaporationVolume is ' + res.evaporationVolume);
});

test('steamProperties', function (t) {
    t.plan(7);
    t.type(bindings.steamProperties, 'function');

    var inp = {};

    inp.pressure = 10;
    inp.thermodynamicQuantity = 1; //1 is ENTHALPY
    inp.quantityValue = 2000;

    var res = bindings.steamProperties(inp);

    t.equal(res.pressure, 10, 'res.pressure is ' + res.pressure);

    t.equal(rnd(res.temperature), rnd(584.1494879985282), 'res.temperature is ' + res.temperature);

    t.equal(res.specificEnthalpy, 2000, 'res.specificEnthalpy is ' + res.specificEnthalpy);

    t.equal(rnd(res.specificEntropy), rnd(4.37395830066478), 'res.specificEntropy is ' + res.specificEntropy);

    t.equal(rnd(res.quality), rnd(0.44940059413065064), 'res.quality is ' + res.quality);

    t.equal(rnd(res.specificVolume), rnd(0.008904111059648875), 'res.specificVolume is '+ res.specificVolume);

});

test('boiler', function (t) {
    t.plan(8);
    t.type(bindings.boiler, 'function');

    var inp = {
        deaeratorPressure : 10, combustionEfficiency : 85, blowdownRate : 2,
        steamPressure : 20, thermodynamicQuantity : 1, //1 is ENTHALPY
        quantityValue : 2000, steamMassFlow : 45
    };

    var res = bindings.boiler(inp);

    t.equal(rnd(res.steamEnergyFlow), rnd(110.7533647508802), 'res.steamEnergyFlow is ' + res.steamEnergyFlow);
    t.equal(rnd(res.blowdownMassFlow), rnd(0.9183673469387756), 'res.blowdownMassFlow is ' + res.blowdownMassFlow);
    t.equal(rnd(res.blowdownEnergyFlow), rnd(1.6779495528531483), 'res.blowdownEnergyFlow is ' + res.blowdownEnergyFlow);
    t.equal(rnd(res.feedwaterMassFlow), rnd(45.91836734693878), 'res.feedwaterMassFlow is ' + res.feedwaterMassFlow);
    t.equal(rnd(res.feedwaterEnergyFlow), rnd(64.64697706690914), 'res.feedwaterEnergyFlow is ' + res.feedwaterEnergyFlow);
    t.equal(rnd(res.boilerEnergy), rnd(47.7843372368242), 'res.boilerEnergy is '+ res.boilerEnergy);
    t.equal(rnd(res.fuelEnergy), rnd(56.216867337440235), 'res.fuelEnergy is '+ res.fuelEnergy);
});

test('heatLoss', function (t) {
    t.plan(5);
    t.type(bindings.heatLoss, 'function');

    var inp = {
        inletPressure : 2.418,
        thermodynamicQuantity : 0, //0 is TEMPERATURE
        quantityValue : 521,
        inletMassFlow : 5434,
        percentHeatLoss : 2.44
    };

    var res = bindings.heatLoss(inp);

    t.equal(rnd(res.inletEnergyFlow), rnd(15642.967348653074), 'res.inletEnergyFlow is ' + res.inletEnergyFlow);
    t.equal(res.outletMassFlow, 5434, 'res.outletMassFlow is ' + res.outletMassFlow);
    t.equal(rnd(res.outletEnergyFlow), rnd(15261.278945345939), 'res.outletEnergyFlow is ' + res.outletEnergyFlow);
    t.equal(rnd(res.heatLoss), rnd(381.68840330713465), 'res.heatLoss is ' + res.heatLoss);
});

test('flashTank', function (t) {
    t.plan(6);
    t.type(bindings.flashTank, 'function');

    var inp = {
        inletWaterPressure : 4.54484,
        thermodynamicQuantity : 1, //1 is ENTHALPY
        quantityValue : 2000,
        inletWaterMassFlow : 36133,
        tankPressure : 3.3884
    };

    var res = bindings.flashTank(inp);

    t.equal(res.inletWaterEnergyFlow, 72266, 'res.inletWaterEnergyFlow is ' + res.inletWaterEnergyFlow);
    t.equal(rnd(res.outletGasMassFlow), rnd(19667.16383431122), 'res.outletGasMassFlow is ' + res.outletGasMassFlow);
    t.equal(rnd(res.outletGasEnergyFlow), rnd(55126.79710787576), 'res.outletGasEnergyFlow is ' + res.outletGasEnergyFlow);
    t.equal(rnd(res.outletLiquidMassFlow), rnd(16465.83616568878), 'res.outletLiquidMassFlow is ' + res.outletLiquidMassFlow);
    t.equal(rnd(res.outletLiquidEnergyFlow), rnd(17139.20289212423), 'res.outletLiquidEnergyFlow is ' + res.outletLiquidEnergyFlow);
});

test('prvWithoutDesuperheating', function (t) {
    t.plan(6);
    t.type(bindings.prvWithoutDesuperheating, 'function');

    var inp = {
        inletPressure : 4.8794,
        thermodynamicQuantity : 0, //0 is TEMPERATURE
        quantityValue : 691.5,
        inletMassFlow : 37970,
        outletPressure : 4.0823
    };

    var res = bindings.prvWithoutDesuperheating(inp);

    t.equal(rnd(res.inletEnergyFlow), rnd(123147.93493161911), 'res.inletEnergyFlow is ' + res.inletEnergyFlow);
    t.equal(res.outletMassFlow, 37970, 'res.outletMassFlow is ' + res.outletMassFlow);
    t.equal(rnd(res.outletEnergyFlow), rnd(123147.93493161911), 'res.outletEnergyFlow is ' + res.outletEnergyFlow);
    t.equal(rnd(res.inletSpecificEnthalpy), rnd(3243.29562632655), 'res.inletSpecificEnthalpy is ' + res.inletSpecificEnthalpy);
    t.equal(rnd(res.outletSpecificEnthalpy), rnd(3243.29562632655), 'res.outletSpecificEnthalpy is ' + res.outletSpecificEnthalpy);
});

test('prvWithDesuperheating', function (t) {
    t.plan(6);
    t.type(bindings.prvWithDesuperheating, 'function');

    var inp = {
        inletPressure : 2.8937,
        thermodynamicQuantity : 0, //0 is TEMPERATURE
        quantityValue : 936.3,
        inletMassFlow : 17599,
        outletPressure : 0.8188,
        feedwaterPressure : 0.2937,
        feedwaterThermodynamicQuantity : 2, //2 is ENTROPY
        feedwaterQuantityValue : 5,
        desuperheatingTemp : 708.3
    };

    var res = bindings.prvWithDesuperheating(inp);

    t.equal(rnd(res.inletEnergyFlow), rnd(67367.3111113208), 'res.inletEnergyFlow is ' + res.inletEnergyFlow);
    t.equal(rnd(res.outletMassFlow), rnd(23583.469367594505), 'res.outletMassFlow is ' + res.outletMassFlow);
    t.equal(rnd(res.outletEnergyFlow), rnd(78812.94289252072), 'res.outletEnergyFlow is ' + res.outletEnergyFlow);
    t.equal(rnd(res.feedwaterMassFlow), rnd(5984.4693675945055), 'res.feedwaterMassFlow is ' + res.feedwaterMassFlow);
    t.equal(rnd(res.feedwaterEnergyFlow), rnd(11445.631781199914), 'res.feedwaterEnergyFlow is ' + res.feedwaterEnergyFlow);
});

test('deaerator', function (t) {
    t.plan(8);
    t.type(bindings.deaerator, 'function');

    var inp = {
        deaeratorPressure : 0.1998,
        ventRate : 0.4,
        feedwaterMassFlow : 41685,
        waterPressure : 0.1235,
        waterThermodynamicQuantity : 1, //1 is ENTHALPY
        waterQuantityValue : 100,
        steamPressure : 0.4777,
        steamThermodynamicQuantity : 2, //2 is ENTROPY
        steamQuantityValue : 6
    };

    var res = bindings.deaerator(inp);

    t.equal(rnd(res.feedwaterEnergyFlow), rnd(21032.14129813274), 'res.feedwaterEnergyFlow is ' + res.feedwaterEnergyFlow);
    t.equal(res.ventedSteamMassFlow, 166.74, 'res.ventedSteamMassFlow is ' + res.ventedSteamMassFlow);
    t.equal(rnd(res.ventedSteamEnergyFlow), rnd(451.2310290232193), 'res.ventedSteamEnergyFlow is ' + res.ventedSteamEnergyFlow);
    t.equal(rnd(res.inletWaterMassFlow), rnd(34305.35779780327), 'res.inletWaterMassFlow is ' + res.inletWaterMassFlow);
    t.equal(rnd(res.inletWaterEnergyFlow), rnd(3430.535779780379), 'res.inletWaterEnergyFlow is ' + res.inletWaterEnergyFlow);
    t.equal(rnd(res.inletSteamMassFlow), rnd(7546.382202196729), 'res.inletSteamMassFlow is ' + res.inletSteamMassFlow);
    t.equal(rnd(res.inletSteamEnergyFlow), rnd(18052.836547375577), 'res.inletSteamEnergyFlow is ' + res.inletSteamEnergyFlow);
});

test('header', function (t) {
    t.plan(22);
    t.type(bindings.header, 'function');

    var inp = {
        headerPressure: 0.173,
        inlets: [
            {
                pressure: 1.9332,
                thermodynamicQuantity: 0,
                quantityValue: 579.8,
                massFlow: 0.686
            },
            {
                pressure: 2.8682,
                thermodynamicQuantity: 0,
                quantityValue: 308.5,
                massFlow: 0.5019
            },
            {
                pressure: 1.0348,
                thermodynamicQuantity: 0,
                quantityValue: 458,
                massFlow: 0.5633
            },
            {
                pressure: 1.8438,
                thermodynamicQuantity: 0,
                quantityValue: 475.8,
                massFlow: 0.3082
            }
        ]
    };

    var res = bindings.header(inp);
    var header = res.header;
    var inlet1 = res.inlet1;
    var inlet4 = res.inlet4;

    t.equal(header.pressure, 0.173, header.pressure + " != 0.173");
    t.equal(rnd(header.temperature), rnd(388.8366691795), header.temperature + " != 388.8");
    t.equal(rnd(header.massFlow), rnd(2.059399999));
    t.equal(rnd(header.energyFlow), rnd(3998.8128348989585));
    t.equal(rnd(header.quality), rnd(0.6577144796131725));
    t.equal(rnd(header.specificEnthalpy), rnd(1941.7368334946873));
    t.equal(rnd(header.specificEntropy), rnd(5.226216653050388));

    t.equal(rnd(inlet1.energyFlow), rnd(2086.4298803));
    t.equal(rnd(inlet1.massFlow), rnd(0.686));
    t.equal(rnd(inlet1.pressure), rnd(1.9332));
    t.equal(rnd(inlet1.quality), 1);
    t.equal(rnd(inlet1.specificEnthalpy), rnd(3041.442974242245));
    t.equal(rnd(inlet1.specificEntropy), rnd(6.81324727632225));
    t.equal(rnd(inlet1.temperature), rnd(579.8));

    t.equal(rnd(inlet4.energyFlow), rnd(266.41815154210417));
    t.equal(rnd(inlet4.massFlow), rnd(0.3082));
    t.equal(rnd(inlet4.pressure), rnd(1.8438));
    t.equal(rnd(inlet4.quality), 0);
    t.equal(rnd(inlet4.specificEnthalpy), rnd(864.4326785921616));
    t.equal(rnd(inlet4.specificEntropy), rnd(2.3554693941761826));
    t.equal(rnd(inlet4.temperature), rnd(475.8));
});

test('turbine', function (t) {
    t.plan(31);
    t.type(bindings.turbine, 'function');

    var inp = {
        solveFor: 0, // outlet properties - unknown to solve for
        inletPressure: 4.2112,
        inletQuantity: 0, // SteamProperties::ThermodynamicQuantity::temperature
        inletQuantityValue: 888,
        turbineProperty: 0, // massFlow
        isentropicEfficiency: 40.1,
        generatorEfficiency: 94.2,
        massFlowOrPowerOut: 15844, // massFlow in this case
        outletSteamPressure: 3.4781
    };

    var res = bindings.turbine(inp);
    t.equal(rnd(res.inletPressure), rnd(4.2112));
    t.equal(rnd(res.inletTemperature), rnd(888));
    t.equal(rnd(res.inletSpecificEnthalpy), rnd(3707.397118));
    t.equal(rnd(res.inletSpecificEntropy), rnd(7.384098));
    t.equal(rnd(res.inletQuality), rnd(1));
    t.equal(rnd(res.inletEnergyFlow), rnd(58739.99993));

    t.equal(rnd(res.outletPressure), rnd(3.4781));
    t.equal(rnd(res.outletTemperature), rnd(872.338861));
    t.equal(rnd(res.outletSpecificEnthalpy), rnd(3677.155392));
    t.equal(rnd(res.outletSpecificEntropy), rnd(7.436479));
    t.equal(rnd(res.outletQuality), rnd(1));
    t.equal(rnd(res.outletEnergyFlow), rnd(58260.850027));

    t.equal(rnd(res.massFlow), rnd(15.844));
    t.equal(rnd(res.isentropicEfficiency), rnd(40.1));
    t.equal(rnd(res.energyOut), rnd(479.149903));
    t.equal(rnd(res.powerOut), rnd(451.359209));
    t.equal(rnd(res.generatorEfficiency), rnd(94.2));

    inp = {
        solveFor: 1, // isentropicEfficiency - unknown to solve for
        inletPressure: 5.5627,
        inletQuantity: 0, // SteamProperties::ThermodynamicQuantity::temperature
        inletQuantityValue: 823.8,
        turbineProperty: 1, // powerOut
        generatorEfficiency: 82,
        massFlowOrPowerOut: 1000, // powerOut in this case
        outletSteamPressure: 4.4552,
        outletQuantity: 0, // SteamProperties::ThermodynamicQuantity::temperature
        outletQuantityValue: 798.1
    };

    res = bindings.turbine(inp);
    t.equal(rnd(res.inletSpecificEnthalpy), rnd(3546.905437));
    t.equal(rnd(res.inletSpecificEntropy), rnd(7.071209));
    t.equal(rnd(res.inletQuality), rnd(1));
    t.equal(rnd(res.inletEnergyFlow), rnd(88851.276592));

    t.equal(rnd(res.outletSpecificEnthalpy), rnd(3498.223025));
    t.equal(rnd(res.outletSpecificEntropy), rnd(7.110366));
    t.equal(rnd(res.outletQuality), rnd(1));
    t.equal(rnd(res.outletEnergyFlow), rnd(87631.764397));

    t.equal(rnd(res.massFlow), rnd(25.050365));
    t.equal(rnd(res.isentropicEfficiency), rnd(61.105109));
    t.equal(rnd(res.energyOut), rnd(1219.512195));
    t.equal(rnd(res.powerOut), rnd(1000));
    t.equal(rnd(res.generatorEfficiency), rnd(82));

});
