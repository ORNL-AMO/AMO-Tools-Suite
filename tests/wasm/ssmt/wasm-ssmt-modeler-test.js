function steamModeler() {
    var boilerInput = {
        fuelType: 1,
        fuel: 1,
        combustionEfficiency: 85,
        blowdownRate: 2,
        blowdownFlashed: true,
        preheatMakeupWater: true,
        steamTemperature: 514.2,
        deaeratorVentRate: 0.1,
        deaeratorPressure: 0.204747,
        approachTemperature: 10,
    };

    var header1 = {
        pressure: 1.136,
        processSteamUsage: 22680,
        condensationRecoveryRate: 50,
        heatLoss: 0.1,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 1,

        condensateReturnTemperature: 338.7,
        flashCondensateReturn: true,
    };
    var header2 = {
        pressure: 2,
        processSteamUsage: 2,
        condensationRecoveryRate: 2,
        heatLoss: 2,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 338.7,

        condensateReturnTemperature: null,
        flashCondensateReturn: null,
    };
    var header3 = {
        pressure: 3,
        processSteamUsage: 3,
        condensationRecoveryRate: 3,
        heatLoss: 3,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 338.7,

        condensateReturnTemperature: null,
        flashCondensateReturn: null,
    };
    var headerInput = {
        highPressureHeader: header1,
        mediumPressureHeader: null,
        lowPressureHeader: null,
    };

    var operationsInput = {
        sitePowerImport: 18000000,
        makeUpWaterTemperature: 283.15,
        operatingHoursPerYear: 8000,
        fuelCosts: 0.000005478,
        electricityCosts: 1.39E-05,
        makeUpWaterCosts: 0.66,
    };

    var condensingTurbine = {
        isentropicEfficiency: 1,
        generationEfficiency: 1,
        condenserPressure: 1,
        operationType: Module.CondensingTurbineOperation.POWER_GENERATION,
        operationValue: 1,
        useTurbine: true,
    };
    var highToLowTurbine = {
        isentropicEfficiency: 2,
        generationEfficiency: 2,
        condenserPressure: 2,
        operationType: Module.PressureTurbineOperation.BALANCE_HEADER,
        operationValue1: 2,
        operationValue2: 2,
        useTurbine: true,
    };
    var highToMediumTurbine = {
        isentropicEfficiency: 3,
        generationEfficiency: 3,
        condenserPressure: 3,
        operationType: Module.PressureTurbineOperation.POWER_RANGE,
        operationValue1: 3,
        operationValue2: 3,
        useTurbine: true,
    };
    var mediumToLowTurbine = {
        isentropicEfficiency: 4,
        generationEfficiency: 4,
        condenserPressure: 4,
        operationType: Module.PressureTurbineOperation.FLOW_RANGE,
        operationValue1: 4,
        operationValue2: 4,
        useTurbine: true,
    };
    var turbineInput = {
        condensingTurbine: condensingTurbine,
        highToLowTurbine: highToLowTurbine,
        highToMediumTurbine: highToMediumTurbine,
        mediumToLowTurbine: mediumToLowTurbine,
    };

    var modelerInput = {
        isBaselineCalc: true,
        baselinePowerDemand: 1,
        boilerInput: boilerInput,
        headerInput: headerInput,
        operationsInput: operationsInput,
        turbineInput: turbineInput,
    };



    let modeler = new Module.SteamModeler();
    debugger
    let boilerInputObj = new Module.BoilerInput(boilerInput.fuelType, boilerInput.fuel, boilerInput.combustionEfficiency, boilerInput.blowdownRate, boilerInput.blowdownFlashed, boilerInput.preheatMakeupWater, boilerInput.steamTemperature, boilerInput.deaeratorVentRate, boilerInput.deaeratorPressure, boilerInput.approachTemperature);
    let highPressureHeaderObj = new Module.HeaderWithHighestPressure(header1.pressure, header1.processSteamUsage, header1.condensationRecoveryRate, header1.heatLoss, header1.condensateReturnTemperature, header1.flashCondensateReturn);
    // let mediumPressureHeaderObj =  Module.nullptr;
    // let lowPressureHeaderObj = Module.nullptr;
    let headerInputObj = new Module.HeaderInput(highPressureHeaderObj);
    let operationsInputObj = new Module.operationsInput(operationsInput.sitePowerImport, operationsInput.makeUpWaterTemperature, operationsInput.operatingHoursPerYear, operationsInput.fuelCosts, operationsInput.electricityCosts, operationsInput.makeUpWaterCosts);

    let condensingTurbineObj = new Module.CondensingTurbine(condensingTurbine.isentropicEfficiency, condensingTurbine.generationEfficiency, condensingTurbine.condenserPressure, condensingTurbine.operationType, condensingTurbine.operationValue, condensingTurbine.useTurbine);
    let highToLowTurbineObj = new Module.PressureTurbine(highToLowTurbine.isentropicEfficiency, highToLowTurbine.generationEfficiency, highToLowTurbine.operationType, highToLowTurbine.operationValue1, highToLowTurbine.operationValue2, highToLowTurbine.useTurbine);
    let highToMediumTurbineObj = new Module.PressureTurbine(highToMediumTurbine.isentropicEfficiency, highToMediumTurbine.generationEfficiency, highToMediumTurbine.operationType, highToMediumTurbine.operationValue1, highToMediumTurbine.operationValue2, highToMediumTurbine.useTurbine);
    let mediumToLowTurbineObj = new Module.PressureTurbine(mediumToLowTurbine.isentropicEfficiency, mediumToLowTurbine.generationEfficiency, mediumToLowTurbine.operationType, mediumToLowTurbine.operationValue1, mediumToLowTurbine.operationValue2, mediumToLowTurbine.useTurbine);
    let turbineInputObj = new Module.TurbineInput(condensingTurbineObj, highToLowTurbineObj, highToMediumTurbineObj, mediumToLowTurbineObj);

    let steamModelerInput = new Module.SteamModelerInput(modelerInput.isBaselineCalc, modelerInput.baselinePowerDemand, boilerInputObj, headerInputObj, operationsInputObj, turbineInputObj)

    let results = modeler.model(steamModelerInput);
    console.log(results);

    model.delete();
    boilerInputObj.delete();
    highPressureHeaderObj.delete();
    headerInputObj.delete();
    operationsInputObj.delete();
    condensingTurbineObj.delete();
    highToLowTurbineObj.delete();
    highToMediumTurbineObj.delete();
    mediumToLowTurbineObj.delete();
    turbineInputObj.delete();
    steamModelerInput.delete();
}

steamModeler();
