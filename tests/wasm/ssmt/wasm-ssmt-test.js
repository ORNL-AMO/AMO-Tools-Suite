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
function returnInletVector(inletsArray)
{
    let inletVector = new Module.InletVector();

    for (x of inletsArray)
    {
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
    let inlets = header.getInlets();
    let allInletProperties = new Array();
    for(let i = 0; i < inlets.size(); i++){
        let inlet = inlets.get(i);
        let inletProperties = inlet.getInletProperties();
        allInletProperties.push(inletProperties);
    }
    console.log(allInletProperties);
    // let inletWaterProperties = Deaerator.getInletWaterProperties();
    // let inletSteamProperties = Deaerator.getInletSteamProperties();
    // let feedwaterProperties = Deaerator.getFeedwaterProperties();
    // let ventedSteamProperties = Deaerator.getVentedSteamProperties();

    // testNumberValue(feedwaterProperties.energyFlow, 21032141.29813274, 'SSMT Deaerator (feedwaterProperties.energyFlow)');
    // testNumberValue(ventedSteamProperties.massFlow, 166.74, 'SSMT Deaerator (ventedSteamProperties.massFlow)');
    // testNumberValue(ventedSteamProperties.energyFlow, 451231.0290232193, 'SSMT Deaerator (ventedSteamProperties.energyFlow)');
    // testNumberValue(inletWaterProperties.massFlow, 34305.35779780327, 'SSMT Deaerator (inletWaterProperties.massFlow)');
    // testNumberValue(inletWaterProperties.energyFlow, 3430535.779780379, 'SSMT Deaerator (inletWaterProperties.energyFlow)');
    // testNumberValue(inletSteamProperties.massFlow, 7546.382202196729, 'SSMT Deaerator (inletSteamProperties.massFlow)');
    // testNumberValue(inletSteamProperties.energyFlow, 18052836.54737558, 'SSMT Deaerator (inletSteamProperties.energyFlow)');
    // Deaerator.delete();
}
// turbine
// heatExchanger






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



