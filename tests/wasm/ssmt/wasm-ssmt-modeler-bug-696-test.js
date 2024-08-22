function validateOutput(results) {
    validateHighPressureToMediumPressurePrv(results);
}

function SectionHead(header) {
    logMessage('Steam Modeler: Bug #696 Fix - ' + header + ' Results ', true);
}

function defined(value) {
    return (value || value == 0);
}


function validatePrvOutput(header, prv) {
    SectionHead(header);
    testNumberValue(prv.getInletMassFlow(), 35000, "inletMassFlow");
    testNumberValue(prv.getOutletMassFlow(), 35000, "outletMassFlow");
}

function validateHighPressureToMediumPressurePrv(results) {
    validatePrvOutput('High Pressure To Medium Pressure Prv', results.mediumPressureHeaderCalculationsDomain.highToMediumPressurePrv);
}


function steamModeler() {
    let boilerInput = {
        approachTemperature: 0,
        blowdownConductivity: "",
        blowdownFlashed: false,
        blowdownRate: 5,
        combustionEfficiency: 84.9,
        deaeratorPressure: 0.14332499999999998,
        deaeratorVentRate: 0,
        feedwaterConductivity: "",
        fuel: 1,
        fuelType: 1,
        preheatMakeupWater: false,
        steamTemperature: 573.15
    };

    let header1 = {
        condensateReturnTemperature: 373.15,
        condensationRecoveryRate: 0,
        flashCondensateReturn: false,
        heatLoss: 0,
        pressure: 2.1013249999999997,
        processSteamUsage: 6000
    };
    let header2 = {
        condensationRecoveryRate: 50,
        desuperheatSteamIntoNextHighest: false,
        desuperheatSteamTemperature: 273.15,
        flashCondensateIntoHeader: false,
        heatLoss: 0,
        pressure: 1.101325,
        processSteamUsage: 35000,
        useBaselineProcessSteamUsage: true
    };
    let header3 = {
        condensationRecoveryRate: 50,
        desuperheatSteamIntoNextHighest: false,
        desuperheatSteamTemperature: 273.15,
        flashCondensateIntoHeader: false,
        heatLoss: 0,
        pressure: 0.301325,
        processSteamUsage: 85000,
        useBaselineProcessSteamUsage: true
    };
    let headerInput = {
        highPressureHeader: header1,
        mediumPressureHeader: header2,
        lowPressureHeader: header3,
    };

    let operationsInput = {
        electricityCosts: 0.000029166671689595998,
        fuelCosts: 0.0000047,
        makeUpWaterCosts: 0.75,
        makeUpWaterTemperature: 293.15,
        operatingHoursPerYear: 8760,
        sitePowerImport: 25199995.6601898
    };


    let condensingTurbine = {
        isentropicEfficiency: 65.7,
        generationEfficiency: 95,
        condenserPressure: 0.015,
        operationType: Module.CondensingTurbineOperation.STEAM_FLOW,
        operationValue: 15000,
        useTurbine: true,

    };
    let highToLowTurbine = {
        isentropicEfficiency: 31.9,
        generationEfficiency: 95,
        condenserPressure: 0.1,
        operationType: Module.PressureTurbineOperation.STEAM_FLOW,
        operationValue1: 104000,
        operationValue2: 4000,
        useTurbine: true,
    };
    let highToMediumTurbine = {
        isentropicEfficiency: 0,
        generationEfficiency: 0,
        condenserPressure: 0,
        operationType: Module.PressureTurbineOperation.POWER_RANGE,
        operationValue1: 0,
        operationValue2: 0,
        useTurbine: false,
    };
    let mediumToLowTurbine = {
        isentropicEfficiency: 0,
        generationEfficiency: 0,
        condenserPressure: 0.0,
        operationType: Module.PressureTurbineOperation.FLOW_RANGE,
        operationValue1: 0,
        operationValue2: 0,
        useTurbine: false,
    };
    let turbineInput = {
        condensingTurbine: condensingTurbine,
        highToLowTurbine: highToLowTurbine,
        highToMediumTurbine: highToMediumTurbine,
        mediumToLowTurbine: mediumToLowTurbine,
    };

    let modelerInput = {
        isBaselineCalc: true,
        baselinePowerDemand: 1,
        boilerInput: boilerInput,
        headerInput: headerInput,
        operationsInput: operationsInput,
        turbineInput: turbineInput,
    };

    let boilerInputObj = new Module.BoilerInput(boilerInput.fuelType, boilerInput.fuel, boilerInput.combustionEfficiency, boilerInput.blowdownRate, boilerInput.blowdownFlashed, boilerInput.preheatMakeupWater, boilerInput.steamTemperature, boilerInput.deaeratorVentRate, boilerInput.deaeratorPressure, boilerInput.approachTemperature);
    let highPressureHeaderObj = new Module.HeaderWithHighestPressure(header1.pressure, header1.processSteamUsage, header1.condensationRecoveryRate, header1.heatLoss, header1.condensateReturnTemperature, header1.flashCondensateReturn);
    let medPressureHeaderObj = new Module.HeaderNotHighestPressure(header2.pressure, header2.processSteamUsage, header2.condensationRecoveryRate, header2.heatLoss, header2.flashCondensateIntoHeader, header2.desuperheatSteamIntoNextHighest, header2.desuperheatSteamTemperature);
    let lowPressureHeaderObj = new Module.HeaderNotHighestPressure(header3.pressure, header3.processSteamUsage, header3.condensationRecoveryRate, header3.heatLoss, header3.flashCondensateIntoHeader, header3.desuperheatSteamIntoNextHighest, header3.desuperheatSteamTemperature);
    let headerInputObj = new Module.HeaderInput(highPressureHeaderObj, medPressureHeaderObj, lowPressureHeaderObj);
    let operationsInputObj = new Module.OperationsInput(operationsInput.sitePowerImport, operationsInput.makeUpWaterTemperature, operationsInput.operatingHoursPerYear, operationsInput.fuelCosts, operationsInput.electricityCosts, operationsInput.makeUpWaterCosts);

    let condensingTurbineObj = new Module.CondensingTurbine(condensingTurbine.isentropicEfficiency, condensingTurbine.generationEfficiency, condensingTurbine.condenserPressure, condensingTurbine.operationType, condensingTurbine.operationValue, condensingTurbine.useTurbine);
    let highToLowTurbineObj = new Module.PressureTurbine(highToLowTurbine.isentropicEfficiency, highToLowTurbine.generationEfficiency, highToLowTurbine.operationType, highToLowTurbine.operationValue1, highToLowTurbine.operationValue2, highToLowTurbine.useTurbine);
    let highToMediumTurbineObj = new Module.PressureTurbine(highToMediumTurbine.isentropicEfficiency, highToMediumTurbine.generationEfficiency, highToMediumTurbine.operationType, highToMediumTurbine.operationValue1, highToMediumTurbine.operationValue2, highToMediumTurbine.useTurbine);
    let mediumToLowTurbineObj = new Module.PressureTurbine(mediumToLowTurbine.isentropicEfficiency, mediumToLowTurbine.generationEfficiency, mediumToLowTurbine.operationType, mediumToLowTurbine.operationValue1, mediumToLowTurbine.operationValue2, mediumToLowTurbine.useTurbine);
    let turbineInputObj = new Module.TurbineInput(condensingTurbineObj, highToLowTurbineObj, highToMediumTurbineObj, mediumToLowTurbineObj);

    let steamModelerInput = new Module.SteamModelerInput(modelerInput.isBaselineCalc, modelerInput.baselinePowerDemand, boilerInputObj, headerInputObj, operationsInputObj, turbineInputObj)

    let modeler = new Module.SteamModeler();
    validateOutput(modeler.model(steamModelerInput));

    modeler.delete();
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
