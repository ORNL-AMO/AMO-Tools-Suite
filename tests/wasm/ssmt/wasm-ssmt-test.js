// saturatedPropertiesGivenTemperature
function saturatedPropertiesGivenTemperature() {
    var saturatedTemperature = 300;
    //calc pressure..
    let saturatedPressure = new Module.SaturatedPressure(saturatedTemperature);
    let pressure = saturatedPressure.calculate();
    let saturatedProperties = new Module.SaturatedProperties(pressure, saturatedTemperature);
    let saturatedPropertiesOutput = saturatedProperties.calculate();
    testNumberValue(saturatedPropertiesOutput.saturatedPressure, 0.0035365894130130106, 'SSMT Sat. Props. Given Temp (saturatedPressure)');
    testNumberValue(saturatedPropertiesOutput.saturatedTemperature, 300, 'SSMT Sat. Props. Given Temp (saturatedTemperature)');
    testNumberValue(saturatedPropertiesOutput.liquidEnthalpy, 112.57499081240724, 'SSMT Sat. Props. Given Temp (liquidEnthalpy)');
    testNumberValue(saturatedPropertiesOutput.gasEnthalpy, 2549.8930083073265, 'SSMT Sat. Props. Given Temp (gasEnthalpy)');
    testNumberValue(saturatedPropertiesOutput.evaporationEnthalpy, 2437.3180174949193, 'SSMT Sat. Props. Given Temp (evaporationEnthalpy)');
    testNumberValue(saturatedPropertiesOutput.liquidEntropy, 0.3931236014741, 'SSMT Sat. Props. Given Temp (liquidEntropy)');
    testNumberValue(saturatedPropertiesOutput.gasEntropy, 8.517536685028846, 'SSMT Sat. Props. Given Temp (gasEntropy)');
    testNumberValue(saturatedPropertiesOutput.evaporationEntropy, 8.124413083554746, 'SSMT Sat. Props. Given Temp (evaporationEntropy)');
    testNumberValue(saturatedPropertiesOutput.liquidVolume, 0.0010034979299339492, 'SSMT Sat. Props. Given Temp (liquidVolume)');
    testNumberValue(saturatedPropertiesOutput.gasVolume, 39.08205832377987, 'SSMT Sat. Props. Given Temp (gasVolume)');
    testNumberValue(saturatedPropertiesOutput.evaporationVolume, 39.08105482584993, 'SSMT Sat. Props. Given Temp (evaporationVolume)');
    saturatedPressure.delete();
    saturatedProperties.delete();
}
// saturatedPropertiesGivenPressure
function saturatedPropertiesGivenPressure() {
    var saturatedPressure = 20;
    //calc temp..
    let saturatedTemperrature = new Module.SaturatedTemperature(saturatedPressure);
    let temperature = saturatedTemperrature.calculate();
    let saturatedProperties = new Module.SaturatedProperties(saturatedPressure, temperature);
    let saturatedPropertiesOutput = saturatedProperties.calculate();
    testNumberValue(saturatedPropertiesOutput.saturatedPressure, 20, 'SSMT Sat. Props. Given Pressure (saturatedPressure)');
    testNumberValue(saturatedPropertiesOutput.saturatedTemperature, 638.8959115457051, 'SSMT Sat. Props. Given Pressure (saturatedTemperature)');
    testNumberValue(saturatedPropertiesOutput.liquidEnthalpy, 1827.1006242178723, 'SSMT Sat. Props. Given Pressure (liquidEnthalpy)');
    testNumberValue(saturatedPropertiesOutput.gasEnthalpy, 2421.680542687896, 'SSMT Sat. Props. Given Pressure (gasEnthalpy)');
    testNumberValue(saturatedPropertiesOutput.evaporationEnthalpy, 594.5799184700236, 'SSMT Sat. Props. Given Pressure (evaporationEnthalpy)');
    testNumberValue(saturatedPropertiesOutput.liquidEntropy, 4.015381593120578, 'SSMT Sat. Props. Given Pressure (liquidEntropy)');
    testNumberValue(saturatedPropertiesOutput.gasEntropy, 4.946001326758373, 'SSMT Sat. Props. Given Pressure (gasEntropy)');
    testNumberValue(saturatedPropertiesOutput.evaporationEntropy, 0.930619733637795, 'SSMT Sat. Props. Given Pressure (evaporationEntropy)');
    testNumberValue(saturatedPropertiesOutput.liquidVolume, 0.0020386472456956663, 'SSMT Sat. Props. Given Pressure (liquidVolume)');
    testNumberValue(saturatedPropertiesOutput.gasVolume, 0.005936854102266306, 'SSMT Sat. Props. Given Pressure (gasVolume)');
    testNumberValue(saturatedPropertiesOutput.evaporationVolume, 0.0038982068565706395, 'SSMT Sat. Props. Given Pressure (evaporationVolume)');
    saturatedTemperrature.delete();
    saturatedProperties.delete();
}
// steamProperties
function steamProperties() {
    var inp = {
        pressure: 10,
        thermodynamicQuantity: Module.ThermodynamicQuantity.ENTHALPY,
        quantityValue: 2000
    }
    let steamProperties = new Module.SteamProperties(inp.pressure, inp.thermodynamicQuantity, inp.quantityValue);
    let result = steamProperties.calculate();
    testNumberValue(result.pressure, 10, 'SSMT Steam Properties (pressure)');
    testNumberValue(result.temperature, 584.1494879985282, 'SSMT Steam Properties (temperature)');
    testNumberValue(result.specificEnthalpy, 2000, 'SSMT Steam Properties (specificEnthalpy)');
    testNumberValue(result.specificEntropy, 4.37395830066478, 'SSMT Steam Properties (specificEntropy)');
    testNumberValue(result.quality, 0.44940059413065064, 'SSMT Steam Properties (quality)');
    testNumberValue(result.specificVolume, 0.008904111059648875, 'SSMT Steam Properties (specificVolume)');
    steamProperties.delete();
}
// boiler
function boiler() {
    var inp = {
        deaeratorPressure: 10, combustionEfficiency: 85, blowdownRate: 2,
        steamPressure: 20, thermodynamicQuantity: Module.ThermodynamicQuantity.ENTHALPY,
        quantityValue: 2000, steamMassFlow: 45
    }
    let boiler = new Module.Boiler(inp.deaeratorPressure, inp.combustionEfficiency, inp.blowdownRate, inp.steamPressure, inp.thermodynamicQuantity, inp.quantityValue, inp.steamMassFlow);
    let boilerSteamProperties = boiler.getSteamProperties();
    let boilerBlowdownProperties = boiler.getBlowdownProperties();
    let boilerFeedwaterProperties = boiler.getFeedwaterProperties();
    let boilerEnergy = boiler.getBoilerEnergy();
    let fuelEnergy = boiler.getFuelEnergy();

    testNumberValue(boilerSteamProperties.energyFlow, 110753.36475088508, 'SSMT Boiler (steam.energyFlow)');
    testNumberValue(boilerBlowdownProperties.massFlow, 0.9183673469387756, 'SSMT Boiler (blowdown.massFlow)');
    testNumberValue(boilerBlowdownProperties.energyFlow, 1677.949552853158, 'SSMT Boiler (blowdown.energyFlow)');
    testNumberValue(boilerFeedwaterProperties.massFlow, 45.91836734693878, 'SSMT Boiler (feedwater.massFlow)');
    testNumberValue(boilerFeedwaterProperties.energyFlow, 64646.977066909145, 'SSMT Boiler (feedwater.energyFlow)');
    testNumberValue(boilerEnergy, 47784.337236829095, 'SSMT Boiler (boilerEnergy)');
    testNumberValue(fuelEnergy, 56216.867337446, 'SSMT Boiler (fuelEnergy)');
    boiler.delete();
}
// heatLoss
function heatLoss() {
    var inp = {
        inletPressure: 2.418,
        thermodynamicQuantity: Module.ThermodynamicQuantity.TEMPERATURE,
        quantityValue: 521,
        inletMassFlow: 5434,
        percentHeatLoss: 2.44
    }
    let heatLoss = new Module.HeatLoss(inp.inletPressure, inp.thermodynamicQuantity, inp.quantityValue, inp.inletMassFlow, inp.percentHeatLoss);
    let inletProperties = heatLoss.getInletProperties();
    let outletProperties = heatLoss.getOutletProperties();
    let totalHeatLoss = heatLoss.getHeatLoss();

    testNumberValue(inletProperties.energyFlow, 15642967.348653074, 'SSMT Heat Loss (inlet.energyFlow)');
    testNumberValue(outletProperties.massFlow, 5434, 'SSMT Heat Loss (outlet.massFlow)');
    testNumberValue(outletProperties.energyFlow, 15261278.94534594, 'SSMT Heat Loss (outlet.energyFlow)');
    testNumberValue(totalHeatLoss, 381688.4033071343, 'SSMT Heat Loss (totalHeatLoss)');
    heatLoss.delete();
}
// flashTank
function flashTank() {
    var inp = {
        inletWaterPressure: 4.54484,
        thermodynamicQuantity: Module.ThermodynamicQuantity.ENTHALPY,
        quantityValue: 2000,
        inletWaterMassFlow: 36133,
        tankPressure: 3.3884
    }
    let flashTank = new Module.FlashTank(inp.inletWaterPressure, inp.thermodynamicQuantity, inp.quantityValue, inp.inletWaterMassFlow, inp.tankPressure);
    let waterProperties = flashTank.getInletWaterProperties();
    let outletGasProperties = flashTank.getOutletGasSaturatedProperties();
    let outletLiquidProperties = flashTank.getOutletLiquidSaturatedProperties();

    testNumberValue(waterProperties.energyFlow, 72266000, 'SSMT Flash Tank (water.energyFlow)');
    testNumberValue(outletGasProperties.massFlow, 19667.16383431122, 'SSMT Flash Tank (outletGas.massFlow)');
    testNumberValue(outletGasProperties.energyFlow, 55126797.107875764, 'SSMT Flash Tank (outletGas.energyFlow)');
    testNumberValue(outletLiquidProperties.massFlow, 16465.83616568878, 'SSMT Flash Tank (outletLiquid.massFlow)');
    testNumberValue(outletLiquidProperties.energyFlow, 17139202.892124232, 'SSMT Flash Tank (outletLiquid.energyFlow)');
    flashTank.delete();
}
// prvWithoutDesuperheating
function prvWithoutDesuperheating() {
    var inp = {
        inletPressure: 4.8794,
        thermodynamicQuantity: Module.ThermodynamicQuantity.TEMPERATURE,
        quantityValue: 691.5,
        inletMassFlow: 37970,
        outletPressure: 4.0823
    }
    let prvWithoutDesuperheating = new Module.PrvWithoutDesuperheating(inp.inletPressure, inp.thermodynamicQuantity, inp.quantityValue, inp.inletMassFlow, inp.outletPressure);
    let inletProperties = prvWithoutDesuperheating.getInletProperties();
    let outletProperties = prvWithoutDesuperheating.getOutletProperties();
    let inletMassFlow = prvWithoutDesuperheating.getInletMassFlow();
    let inletEnergyFlow = prvWithoutDesuperheating.getInletEnergyFlow();
    let outletMassFlow = prvWithoutDesuperheating.getOutletMassFlow();
    let outletEnergyFlow = prvWithoutDesuperheating.getOutletEnergyFlow();

    testNumberValue(inletEnergyFlow, 123147934.93161911, 'SSMT PRV W/o Desuperheating (inletEnergyFlow)');
    testNumberValue(outletMassFlow, 37970, 'SSMT PRV W/o Desuperheating (outletMassFlow)');
    testNumberValue(outletEnergyFlow, 123147934.93161911, 'SSMT PRV W/o Desuperheating (outletEnergyFlow)');
    testNumberValue(inletProperties.specificEnthalpy, 3243.29562632655, 'SSMT PRV W/o Desuperheating (inletProperties.specificEnthalpy)');
    testNumberValue(outletProperties.specificEnthalpy, 3243.29562632655, 'SSMT PRV W/o Desuperheating (outletProperties.specificEnthalpy)');
    prvWithoutDesuperheating.delete();
}
// prvWithDesuperheating
function prvWithDesuperheating() {
    var inp = {
        inletPressure: 2.8937,
        thermodynamicQuantity: Module.ThermodynamicQuantity.TEMPERATURE,
        quantityValue: 936.3,
        inletMassFlow: 17599,
        outletPressure: 0.8188,
        feedwaterPressure: 0.2937,
        feedwaterThermodynamicQuantity: Module.ThermodynamicQuantity.ENTROPY,
        feedwaterQuantityValue: 5,
        desuperheatingTemp: 708.3
    }
    let prvWithDesuperheating = new Module.PrvWithDesuperheating(inp.inletPressure, inp.thermodynamicQuantity, inp.quantityValue, inp.inletMassFlow, inp.outletPressure, inp.feedwaterPressure, inp.feedwaterThermodynamicQuantity, inp.feedwaterQuantityValue, inp.desuperheatingTemp);
    let inletProperties = prvWithDesuperheating.getInletProperties();
    let outletProperties = prvWithDesuperheating.getOutletProperties();
    let feedwaterProperties = prvWithDesuperheating.getFeedwaterProperties();
    let inletEnergyFlow = prvWithDesuperheating.getInletEnergyFlow();
    let outletMassFlow = prvWithDesuperheating.getOutletMassFlow();
    let outletEnergyFlow = prvWithDesuperheating.getOutletEnergyFlow();
    let feedwaterMassFlow = prvWithDesuperheating.getFeedwaterMassFlow();
    let feedwaterEnergyFlow = prvWithDesuperheating.getFeedwaterEnergyFlow();

    testNumberValue(inletEnergyFlow, 67367311.1113208, 'SSMT PRV W Desuperheating (inletEnergyFlow)');
    testNumberValue(outletMassFlow, 23583.469367594505, 'SSMT PRV W Desuperheating (outletMassFlow)');
    testNumberValue(outletEnergyFlow, 78812942.89252071, 'SSMT PRV W Desuperheating (outletEnergyFlow)');
    testNumberValue(feedwaterMassFlow, 5984.4693675945055, 'SSMT PRV W Desuperheating (feedwaterProperties.massFlow)');
    testNumberValue(feedwaterEnergyFlow, 11445631.781199913, 'SSMT PRV W Desuperheating (feedwaterProperties.energyFlow)');
    prvWithDesuperheating.delete();
}
// deaerator
function deaerator() {
    var inp = {
        deaeratorPressure: 0.1998,
        ventRate: 0.4,
        feedwaterMassFlow: 41685,
        waterPressure: 0.1235,
        waterThermodynamicQuantity: Module.ThermodynamicQuantity.ENTHALPY,
        waterQuantityValue: 100,
        steamPressure: 0.4777,
        steamThermodynamicQuantity: Module.ThermodynamicQuantity.ENTROPY,
        steamQuantityValue: 6
    }
    let deaerator = new Module.Deaerator(inp.deaeratorPressure, inp.ventRate, inp.feedwaterMassFlow, inp.waterPressure, inp.waterThermodynamicQuantity, inp.waterQuantityValue, inp.steamPressure, inp.steamThermodynamicQuantity, inp.steamQuantityValue);
    let inletWaterProperties = deaerator.getInletWaterProperties();
    let inletSteamProperties = deaerator.getInletSteamProperties();
    let feedwaterProperties = deaerator.getFeedwaterProperties();
    let ventedSteamProperties = deaerator.getVentedSteamProperties();

    testNumberValue(feedwaterProperties.energyFlow, 21032141.29813274, 'SSMT Deaerator (feedwaterProperties.energyFlow)');
    testNumberValue(ventedSteamProperties.massFlow, 166.74, 'SSMT Deaerator (ventedSteamProperties.massFlow)');
    testNumberValue(ventedSteamProperties.energyFlow, 451231.0290232193, 'SSMT Deaerator (ventedSteamProperties.energyFlow)');
    testNumberValue(inletWaterProperties.massFlow, 34305.35779780327, 'SSMT Deaerator (inletWaterProperties.massFlow)');
    testNumberValue(inletWaterProperties.energyFlow, 3430535.779780379, 'SSMT Deaerator (inletWaterProperties.energyFlow)');
    testNumberValue(inletSteamProperties.massFlow, 7546.382202196729, 'SSMT Deaerator (inletSteamProperties.massFlow)');
    testNumberValue(inletSteamProperties.energyFlow, 18052836.54737558, 'SSMT Deaerator (inletSteamProperties.energyFlow)');
    deaerator.delete();
}

// header
function returnInletVector(inletsArray) {
    let inletVector = new Module.InletVector();

    for (x of inletsArray) {
        let inlet = new Module.Inlet(x.pressure, x.thermodynamicQuantity, x.quantityValue, x.massFlow);
        inletVector.push_back(inlet);
    }

    return inletVector;
}
function header() {
    var inp = {
        headerPressure: 0.173,
        inlets: [
            {
                pressure: 1.9332,
                thermodynamicQuantity: Module.ThermodynamicQuantity.TEMPERATURE,
                quantityValue: 579.8,
                massFlow: 0.686
            },
            {
                pressure: 2.8682,
                thermodynamicQuantity: Module.ThermodynamicQuantity.TEMPERATURE,
                quantityValue: 308.5,
                massFlow: 0.5019
            },
            {
                pressure: 1.0348,
                thermodynamicQuantity: Module.ThermodynamicQuantity.TEMPERATURE,
                quantityValue: 458,
                massFlow: 0.5633
            },
            {
                pressure: 1.8438,
                thermodynamicQuantity: Module.ThermodynamicQuantity.TEMPERATURE,
                quantityValue: 475.8,
                massFlow: 0.3082
            }
        ]
    }

    let inletVector = returnInletVector(inp.inlets);

    let header = new Module.Header(inp.headerPressure, inletVector);
    let headerProps = header.getHeaderProperties();
    headerProps.energyFlow = header.getInletEnergyFlow();
    headerProps.massFlow = header.getInletMassFlow();
    let inlets = header.getInlets();
    let allInletProperties = new Array();
    for (let i = 0; i < inlets.size(); i++) {
        let inlet = inlets.get(i);
        let inletProperties = inlet.getInletProperties();
        inletProperties.energyFlow = inlet.getInletEnergyFlow();
        inletProperties.massFlow = inlet.getMassFlow();
        allInletProperties.push(inletProperties);
    }
    let inlet1 = allInletProperties[0];
    let inlet4 = allInletProperties[3];
    testNumberValue(headerProps.pressure, 0.173, 'SSMT Header (headerProps.pressure)');
    testNumberValue(headerProps.temperature, 388.8366691795, 'SSMT Header (headerProps.temperature)');
    testNumberValue(headerProps.massFlow, 2.059399999, 'SSMT Header (headerProps.massFlow)');
    testNumberValue(headerProps.energyFlow, 3998.8128348989585, 'SSMT Header (headerProps.energyFlow)');
    testNumberValue(headerProps.quality, 0.6577144796131725, 'SSMT Header (headerProps.quality)');
    testNumberValue(headerProps.specificEnthalpy, 1941.7368334946873, 'SSMT Header (headerProps.specificEnthalpy)');
    testNumberValue(headerProps.specificEntropy, 5.226216653050388, 'SSMT Header (headerProps.specificEntropy)');

    testNumberValue(inlet1.energyFlow, 2086.4298803, 'SSMT Header (inlet1.energyFlow)');
    testNumberValue(inlet1.massFlow, 0.686, 'SSMT Header (inlet1.massFlow)');
    testNumberValue(inlet1.pressure, 1.9332, 'SSMT Header (inlet1.pressure)');
    testNumberValue(inlet1.quality, 1, 'SSMT Header (inlet1.quality)');
    testNumberValue(inlet1.specificEnthalpy, 3041.442974242245, 'SSMT Header (inlet1.specificEnthalpy)');
    testNumberValue(inlet1.specificEntropy, 6.81324727632225, 'SSMT Header (inlet1.specificEntropy)');
    testNumberValue(inlet1.temperature, 579.8, 'SSMT Header (inlet1.temperature)');

    testNumberValue(inlet4.energyFlow, 266.41815154210417, 'SSMT Header (inlet4.energyFlow)');
    testNumberValue(inlet4.massFlow, 0.3082, 'SSMT Header (inlet4.massFlow)');
    testNumberValue(inlet4.pressure, 1.8438, 'SSMT Header (inlet4.pressure)');
    testNumberValue(inlet4.quality, 0, 'SSMT Header (inlet4.quality)');
    testNumberValue(inlet4.specificEnthalpy, 864.4326785921616, 'SSMT Header (inlet4.specificEnthalpy)');
    testNumberValue(inlet4.specificEntropy, 2.3554693941761826, 'SSMT Header (inlet4.specificEntropy)');
    testNumberValue(inlet4.temperature, 475.8, 'SSMT Header (inlet4.temperature)');
    header.delete();
    for (let i = 0; i < inletVector.size(); i++) {
        let inlet = inletVector.get(i);
        inlet.delete();
    }
}
// turbine
function turbine() {
    var inp = {
        solveFor: Module.Solve.OutletProperties, // outlet properties - unknown to solve for
        inletPressure: 4.2112,
        inletQuantity: Module.ThermodynamicQuantity.TEMPERATURE, // SteamProperties::ThermodynamicQuantity::temperature
        inletQuantityValue: 888,
        turbineProperty: Module.TurbineProperty.MassFlow, // massFlow
        isentropicEfficiency: 40.1,
        generatorEfficiency: 94.2,
        massFlowOrPowerOut: 15844, // massFlow in this case
        outletSteamPressure: 3.4781
    }
    let turbine = new Module.Turbine(inp.solveFor, inp.inletPressure, inp.inletQuantity, inp.inletQuantityValue, inp.turbineProperty, inp.isentropicEfficiency, inp.generatorEfficiency, inp.massFlowOrPowerOut, inp.outletSteamPressure);
    let inletProperties = turbine.getInletProperties();
    inletProperties.energyFlow = turbine.getInletEnergyFlow();
    let outletProperties = turbine.getOutletProperties();
    outletProperties.energyFlow = turbine.getOutletEnergyFlow();
    let massFlow = turbine.getMassFlow();
    let isentropicEfficiency = turbine.getIsentropicEfficiency();
    let energyOut = turbine.getEnergyOut();
    let powerOut = turbine.getPowerOut();
    let generatorEfficiency = turbine.getGeneratorEfficiency();

    testNumberValue(inletProperties.pressure, 4.2112, 'SSMT Turbine (inletProperties.pressure)');
    testNumberValue(inletProperties.temperature, 888, 'SSMT Turbine (inletProperties.temperature)');
    testNumberValue(inletProperties.specificEnthalpy, 3707.397118, 'Turbine Header (inletProperties.specificEnthalpy)');
    testNumberValue(inletProperties.specificEntropy, 7.384098, 'SSMT Turbine (inletProperties.specificEntropy)');
    testNumberValue(inletProperties.quality, 1, 'SSMT Turbine (inletProperties.quality)');
    testNumberValue(inletProperties.energyFlow, 58739999.930197, 'SSMT Turbine (inletProperties.energyFlow)');
   

    testNumberValue(outletProperties.pressure, 3.4781, 'SSMT Turbine (outletProperties.pressure)');
    testNumberValue(outletProperties.temperature, 872.338861, 'SSMT Turbine (outletProperties.temperature)');
    testNumberValue(outletProperties.specificEnthalpy, 3677.155392, 'SSMT Turbine (outletProperties.specificEnthalpy)');
    testNumberValue(outletProperties.specificEntropy, 7.436479, 'SSMT Turbine (outletProperties.specificEntropy)');
    testNumberValue(outletProperties.quality, 1, 'SSMT Turbine (outletProperties.quality)');
    testNumberValue(outletProperties.energyFlow, 58260850.026976, 'SSMT Turbine (outletProperties.energyFlow)');

    testNumberValue(massFlow, 15844, 'SSMT Turbine (massFlow)');
    testNumberValue(isentropicEfficiency, 40.1, 'SSMT Turbine (isentropicEfficiency)');
    testNumberValue(energyOut, 479149.903221, 'SSMT Turbine (energyOut)');
    testNumberValue(powerOut, 451359.208834, 'SSMT Turbine (powerOut)');
    testNumberValue(generatorEfficiency, 94.2, 'SSMT Turbine (generatorEfficiency)');

    inp = {
        solveFor: Module.Solve.IsentropicEfficiency, // isentropicEfficiency - unknown to solve for
        inletPressure: 5.5627,
        inletQuantity: Module.ThermodynamicQuantity.TEMPERATURE, // SteamProperties::ThermodynamicQuantity::temperature
        inletQuantityValue: 823.8,
        turbineProperty: Module.TurbineProperty.PowerOut, // powerOut
        generatorEfficiency: 82,
        massFlowOrPowerOut: 1000, // powerOut in this case
        outletSteamPressure: 4.4552,
        outletQuantity: Module.ThermodynamicQuantity.TEMPERATURE, // SteamProperties::ThermodynamicQuantity::temperature
        outletQuantityValue: 798.1
    }

    turbine = new Module.Turbine(inp.solveFor, inp.inletPressure, inp.inletQuantity, inp.inletQuantityValue, inp.turbineProperty, inp.generatorEfficiency, inp.massFlowOrPowerOut, inp.outletSteamPressure, inp.outletQuantity, inp.outletQuantityValue);
    inletProperties = turbine.getInletProperties();
    inletProperties.energyFlow = turbine.getInletEnergyFlow();
    outletProperties = turbine.getOutletProperties();
    outletProperties.energyFlow = turbine.getOutletEnergyFlow();
    massFlow = turbine.getMassFlow();
    isentropicEfficiency = turbine.getIsentropicEfficiency();
    energyOut = turbine.getEnergyOut();
    powerOut = turbine.getPowerOut();
    generatorEfficiency = turbine.getGeneratorEfficiency();

    testNumberValue(inletProperties.specificEnthalpy, 3546.905437, 'SSMT Turbine (inletProperties.specificEnthalpy-2)');
    testNumberValue(inletProperties.specificEntropy, 7.071209, 'SSMT Turbine (inletProperties.specificEntropy-2)');
    testNumberValue(inletProperties.quality, 1, 'SSMT Turbine (inletProperties.quality-2)');
    testNumberValue(inletProperties.energyFlow, 88851.276592, 'SSMT Turbine (inletProperties.energyFlow-2)');
   

    testNumberValue(outletProperties.specificEnthalpy, 3498.223025, 'SSMT Turbine (outletProperties.specificEnthalpy-2)');
    testNumberValue(outletProperties.specificEntropy, 7.110366, 'SSMT Turbine (outletProperties.specificEntropy-2)');
    testNumberValue(outletProperties.quality, 1, 'SSMT Turbine (outletProperties.quality-2)');
    testNumberValue(outletProperties.energyFlow, 87631.764397, 'SSMT Turbine (outletProperties.energyFlow-2)');

    testNumberValue(massFlow, 25.050365, 'SSMT Turbine (massFlow-2)');
    testNumberValue(isentropicEfficiency, 61.105109, 'SSMT Turbine (isentropicEfficiency-2)');
    testNumberValue(energyOut, 1219.512195, 'SSMT Turbine (energyOut-2)');
    testNumberValue(powerOut, 1000, 'SSMT Turbine (powerOut-2)');
    testNumberValue(generatorEfficiency, 82, 'SSMT Turbine (generatorEfficiency-2)');
    turbine.delete();
}
// heatExchanger
function heatExchanger() {
    var inp = {
        approachTemp: 10,
        coldInletDensity: 999.7015401695024,
        coldInletEnergyFlow: 262530220.6437767,
        coldInletMassFlow: 6233100.275643423,
        coldInletPressure: 0.101325,
        coldInletQuality: 0,
        coldInletSpecificEnthalpy: 42.11872247100606,
        coldInletSpecificEntropy: 0.15107627374941596,
        coldInletSpecificVolume: 0.0010002985489353622,
        coldInletTemperature: 283.15,
        hotInletDensity: 866.6499783621422,
        hotInletEnergyFlow: 81817968.94625004,
        hotInletMassFlow: 96858.44750370324,
        hotInletPressure: 1.5,
        hotInletQuality: 0,
        hotInletSpecificEnthalpy: 844.716914785588,
        hotInletSpecificEntropy: 2.314681630438997,
        hotInletSpecificVolume: 0.0011538683724309003,
        hotInletTemperature: 471.4452428824141,
    }

    let coldInletFluidProps = new Module.FluidProperties(inp.coldInletMassFlow, inp.coldInletEnergyFlow, inp.coldInletTemperature, inp.coldInletPressure, inp.coldInletQuality, inp.coldInletSpecificVolume, inp.coldInletDensity, inp.coldInletSpecificEnthalpy, inp.coldInletSpecificEntropy, 0);
    let hotInletFluidProps = new Module.FluidProperties(inp.hotInletMassFlow, inp.hotInletEnergyFlow, inp.hotInletTemperature, inp.hotInletPressure, inp.hotInletQuality, inp.hotInletSpecificVolume, inp.hotInletDensity, inp.hotInletSpecificEnthalpy, inp.hotInletSpecificEntropy, 0);
    let heatExchanger = new Module.HeatExchanger(hotInletFluidProps, coldInletFluidProps, inp.approachTemp);
    let results =  heatExchanger.calculate();

    debugger
    
    testNumberValue(results.hotOutlet.pressure, 1.5, 'SSMT Heat Exchanger (results.hotOutlet.pressure)');
    testNumberValue(results.hotOutlet.temperature, 293.15, 'SSMT Heat Exchanger (results.hotOutlet.temperature)');
    testNumberValue(results.hotOutlet.specificEnthalpy, 85.328522053958, 'SSMT Heat Exchanger (results.hotOutlet.specificEnthalpy)');
    testNumberValue(results.hotOutlet.specificEntropy, 0.2961917501711791, 'SSMT Heat Exchanger (results.hotOutlet.specificEntropy)');
    testNumberValue(results.hotOutlet.quality, 0, 'SSMT Heat Exchanger (results.hotOutlet.quality)');
    testNumberValue(results.hotOutlet.specificVolume, 0.0010011563539881817, 'SSMT Heat Exchanger (results.hotOutlet.specificVolume)');
    testNumberValue(results.hotOutlet.massFlow, 96858.44750370324, 'SSMT Heat Exchanger (results.hotOutlet.massFlow)');
    testNumberValue(results.hotOutlet.energyFlow, 8264788.173931874, 'SSMT Heat Exchanger (results.hotOutlet.energyFlow)');

    
    testNumberValue(results.coldOutlet.pressure, 0.101325, 'SSMT Heat Exchanger (results.coldOutlet.pressure)');
    testNumberValue(results.coldOutlet.temperature, 285.9640221738703, 'SSMT Heat Exchanger (results.coldOutlet.temperature)');
    testNumberValue(results.coldOutlet.specificEnthalpy, 53.91913920098477, 'SSMT Heat Exchanger (results.coldOutlet.specificEnthalpy)');
    testNumberValue(results.coldOutlet.specificEntropy, 0.19254607216780856, 'SSMT Heat Exchanger (results.coldOutlet.specificEntropy)');
    testNumberValue(results.coldOutlet.quality, 0, 'SSMT Heat Exchanger (results.coldOutlet.quality)');
    testNumberValue(results.coldOutlet.specificVolume, 0.0010005983512689238, 'SSMT Heat Exchanger (results.coldOutlet.specificVolume)');
    testNumberValue(results.coldOutlet.massFlow, 6233100.275643423, 'SSMT Heat Exchanger (results.coldOutlet.massFlow)');
    testNumberValue(results.coldOutlet.energyFlow, 336083401.4161143, 'SSMT Heat Exchanger (results.coldOutlet.energyFlow)');

    inp = {
        approachTemp: 10,
        coldInletDensity: 999.7015401695024,
        coldInletEnergyFlow: 662268.2787552822,
        coldInletMassFlow: 15723.845356686172,
        coldInletPressure: 0.101325,
        coldInletQuality: 0,
        coldInletSpecificEnthalpy: 42.11872247100606,
        coldInletSpecificEntropy: 0.15107627374941596,
        coldInletSpecificVolume: 0.0010002985489353622,
        coldInletTemperature: 283.15,
        hotInletDensity: 798.3582064389988,
        hotInletEnergyFlow: 749645.9791564117,
        hotInletMassFlow: 689.376530177306,
        hotInletPressure: 4,
        hotInletQuality: 0,
        hotInletSpecificEnthalpy: 1087.4260238647878,
        hotInletSpecificEntropy: 2.7966534294996848,
        hotInletSpecificVolume: 0.0012525705778868427,
        hotInletTemperature: 523.5075191240655
    }


    coldInletFluidProps = new Module.FluidProperties(inp.coldInletMassFlow, inp.coldInletEnergyFlow, inp.coldInletTemperature, inp.coldInletPressure, inp.coldInletQuality, inp.coldInletSpecificVolume, inp.coldInletDensity, inp.coldInletSpecificEnthalpy, inp.coldInletSpecificEntropy, 0);
    hotInletFluidProps = new Module.FluidProperties(inp.hotInletMassFlow, inp.hotInletEnergyFlow, inp.hotInletTemperature, inp.hotInletPressure, inp.hotInletQuality, inp.hotInletSpecificVolume, inp.hotInletDensity, inp.hotInletSpecificEnthalpy, inp.hotInletSpecificEntropy, 0);
    heatExchanger = new Module.HeatExchanger(hotInletFluidProps, coldInletFluidProps, inp.approachTemp);
    results =  heatExchanger.calculate();

    testNumberValue(results.hotOutlet.pressure, 4, 'SSMT Heat Exchanger (results.hotOutlet.pressure)');
    testNumberValue(results.hotOutlet.temperature, 293.15, 'SSMT Heat Exchanger (results.hotOutlet.temperature)');
    testNumberValue(results.hotOutlet.specificEnthalpy, 87.6755402690778, 'SSMT Heat Exchanger (results.hotOutlet.specificEnthalpy)');
    testNumberValue(results.hotOutlet.specificEntropy, 0.2956648955932186, 'SSMT Heat Exchanger (results.hotOutlet.specificEntropy)');
    testNumberValue(results.hotOutlet.quality, 0, 'SSMT Heat Exchanger (results.hotOutlet.quality)');
    testNumberValue(results.hotOutlet.specificVolume, 0.0010000175423266124, 'SSMT Heat Exchanger (results.hotOutlet.specificVolume)');
    testNumberValue(results.hotOutlet.massFlow, 689.376530177306, 'SSMT Heat Exchanger (results.hotOutlet.massFlow)');
    testNumberValue(results.hotOutlet.energyFlow, 60441.45973211752, 'SSMT Heat Exchanger (results.hotOutlet.energyFlow)');

    
    testNumberValue(results.coldOutlet.pressure, 0.101325, 'SSMT Heat Exchanger (results.coldOutlet.pressure)');
    testNumberValue(results.coldOutlet.temperature, 293.6129961502827, 'SSMT Heat Exchanger (results.coldOutlet.temperature)');
    testNumberValue(results.coldOutlet.specificEnthalpy, 85.95052721024926, 'SSMT Heat Exchanger (results.coldOutlet.specificEnthalpy)');
    testNumberValue(results.coldOutlet.specificEntropy, 0.30308657179435106, 'SSMT Heat Exchanger (results.coldOutlet.specificEntropy)');
    testNumberValue(results.coldOutlet.quality, 0, 'SSMT Heat Exchanger (results.coldOutlet.quality)');
    testNumberValue(results.coldOutlet.specificVolume, 0.0010018940982539372, 'SSMT Heat Exchanger (results.coldOutlet.specificVolume)');
    testNumberValue(results.coldOutlet.massFlow, 15723.845356686172, 'SSMT Heat Exchanger (results.coldOutlet.massFlow)');
    testNumberValue(results.coldOutlet.energyFlow, 1351472.7981796062, 'SSMT Heat Exchanger (results.coldOutlet.energyFlow)');
    coldInletFluidProps.delete();
    hotInletFluidProps.delete();
    heatExchanger.delete();
}

saturatedPropertiesGivenTemperature();
saturatedPropertiesGivenPressure();
steamProperties();
boiler();
heatLoss();
flashTank();
prvWithoutDesuperheating();
prvWithDesuperheating();
deaerator();
header();
turbine();
heatExchanger();


