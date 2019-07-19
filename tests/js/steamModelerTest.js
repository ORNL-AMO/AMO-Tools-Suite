const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({module_root: testRoot, bindings: 'ssmt'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('steamModeler', function (t) {
    t.type(bindings.steamModeler, 'function');

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
        operationType: 1,
        operationValue: 1,
        useTurbine: true,
    };
    var highToLowTurbine = {
        isentropicEfficiency: 2,
        generationEfficiency: 2,
        condenserPressure: 2,
        operationType: 2,
        operationValue1: 2,
        operationValue2: 2,
        useTurbine: true,
    };
    var highToMediumTurbine = {
        isentropicEfficiency: 3,
        generationEfficiency: 3,
        condenserPressure: 3,
        operationType: 3,
        operationValue1: 3,
        operationValue2: 3,
        useTurbine: true,
    };
    var mediumToLowTurbine = {
        isentropicEfficiency: 4,
        generationEfficiency: 4,
        condenserPressure: 4,
        operationType: 4,
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

    return {
        isBaselineCalc: true,
        baselinePowerDemand: 1,
        boilerInput: boilerInput,
        headerInput: headerInput,
        operationsInput: operationsInput,
        turbineInput: turbineInput,
    };

    var actual = bindings.steamModeler(steamModelerInput);

    //TODO remove me and assert values when actual results return
    console.log("================");
    console.log("JS steamModelerInput=");
    console.log(JSON.stringify(steamModelerInput));
    console.log("================");
    console.log("JS actual=");
    console.log(JSON.stringify(actual));
    console.log("================");

    validateOperationsOutput(t, actual);
    validateBoilerOutput(t, actual);
    validateDeaeratorOutput(t, actual);

    validateFeedwaterResponse(t, actual);
    validateHighPressureHeaderSteam(t, actual);
    validateBlowdown(t, actual);
    validateCondensate(t, actual);
    validateMakeupWater(t, actual);
    validateMakeupWaterAndCondensate(t, actual);
    validateHighPressureProcessSteamUsage(t, actual);

    validateCondensingTurbine(t, actual);
    validateHighPressureToMediumPressureTurbine(t, actual);
    validateHighPressureToLowPressureTurbine(t, actual);
    validateMediumPressureToLowPressureTurbine(t, actual);

    validateMediumPressureHeaderSteam(t, actual);
    validateLowPressureHeaderSteam(t, actual);

    validateHighPressureToMediumPressurePrv(t, actual);
    validateMediumPressureToLowPressurePrv(t, actual);

    validateBlowdownFlashTank(t, actual);
    validateCondensateFlashTank(t, actual);
    validateHighPressureCondensateFlashTank(t, actual);
    validateMediumPressureCondensateFlashTank(t, actual);

    validateVentedSteam(t, actual);

    // TODO resolve these
    // not used: validateHeaderOutputObj(t, actual);
    // not used (part of unused headerOutputObj): validateHeatLossOutput(t, actual);

    t.end();
});

function validateOperationsOutput(t, actual) {
    var actualOperations = actual.operationsOutput;

    t.equal(actualOperations.powerBalanceGeneration, 0);
    t.equal(actualOperations.powerBalanceDemand, 0);
    t.equal(actualOperations.powerBalanceImport, 0);
    t.equal(actualOperations.powerBalanceUnitCost, 0);
    t.equal(actualOperations.powerBalanceUnitCostPerYear, 0);
    t.equal(actualOperations.fuelBalanceBoiler, 0);
    t.equal(actualOperations.fuelBalanceUnitCost, 0);
    t.equal(actualOperations.fuelBalanceUnitCostPerYear, 0);
    t.equal(actualOperations.makeupWaterFlow, 0);
    t.equal(actualOperations.makeupWaterFlowRate, 0);
    t.equal(actualOperations.makeupWaterUnitCost, 0);
    t.equal(actualOperations.makeupWaterUnitCostPerYear, 0);
    t.equal(actualOperations.totalOperatingCostPerYear, 0);
    t.equal(actualOperations.highPressureCost, 0);
    t.equal(actualOperations.mediumPressureCost, 0);
    t.equal(actualOperations.lowPressureCost, 0);
}

function validateBoilerOutput(t, actual) {
    var actualBoiler = actual.boilerOutput;

    t.equal(actualBoiler.steamPressure, 0);
    t.equal(actualBoiler.steamTemperature, 0);
    t.equal(actualBoiler.steamSpecificEnthalpy, 0);
    t.equal(actualBoiler.steamSpecificEntropy, 0);
    t.equal(actualBoiler.steamQuality, 0);
    t.equal(actualBoiler.steamVolume, 0);
    t.equal(actualBoiler.steamMassFlow, 0);
    t.equal(actualBoiler.steamEnergyFlow, 0);

    t.equal(actualBoiler.blowdownPressure, 0);
    t.equal(actualBoiler.blowdownTemperature, 0);
    t.equal(actualBoiler.blowdownSpecificEnthalpy, 0);
    t.equal(actualBoiler.blowdownSpecificEntropy, 0);
    t.equal(actualBoiler.blowdownQuality, 0);
    t.equal(actualBoiler.blowdownVolume, 0);
    t.equal(actualBoiler.blowdownMassFlow, 0);
    t.equal(actualBoiler.blowdownEnergyFlow, 0);

    t.equal(actualBoiler.feedwaterPressure, 0);
    t.equal(actualBoiler.feedwaterTemperature, 0);
    t.equal(actualBoiler.feedwaterSpecificEnthalpy, 0);
    t.equal(actualBoiler.feedwaterSpecificEntropy, 0);
    t.equal(actualBoiler.feedwaterQuality, 0);
    t.equal(actualBoiler.feedwaterVolume, 0);
    t.equal(actualBoiler.feedwaterMassFlow, 0);
    t.equal(actualBoiler.feedwaterEnergyFlow, 0);

    t.equal(actualBoiler.boilerEnergy, 0);
    t.equal(actualBoiler.fuelEnergy, 0);
    t.equal(actualBoiler.blowdownRate, 0);
    t.equal(actualBoiler.combustionEff, 0);
}

function validateSteamPropertiesOutput(t, actual) {
    t.equal(actual.pressure, 0);
    t.equal(actual.temperature, 0);
    t.equal(actual.specificEnthalpy, 0);
    t.equal(actual.specificEntropy, 0);
    t.equal(actual.quality, 0);
    t.equal(actual.specificVolume, 0);
    t.equal(actual.massFlow, 0);
    t.equal(actual.energyFlow, 0);
}

function validateFeedwaterResponse(t, actual) {
    validateSteamPropertiesOutput(t, actual.feedwater);
}

function validateHighPressureHeaderSteam(t, actual) {
    validateSteamPropertiesOutput(t, actual.highPressureHeaderSteam);
}

function validateBlowdown(t, actual) {
    validateSteamPropertiesOutput(t, actual.blowdown);
}

function validateCondensate(t, actual) {
    validateSteamPropertiesOutput(t, actual.condensate);
}

function validateMakeupWater(t, actual) {
    validateSteamPropertiesOutput(t, actual.makeupWater);
}

function validateMakeupWaterAndCondensate(t, actual) {
    validateSteamPropertiesOutput(t, actual.makeupWaterAndCondensate);
}

function validateHighPressureProcessSteamUsage(t, actual) {
    validateSteamPropertiesOutput(t, actual.highPressureProcessSteamUsage);
}

function validateMediumPressureHeaderSteam(t, actual) {
    validateSteamPropertiesOutput(t, actual.mediumPressureHeaderSteam);
}

function validateLowPressureHeaderSteam(t, actual) {
    validateSteamPropertiesOutput(t, actual.lowPressureHeaderSteam);
}

function validateVentedSteam(t, actual) {
    validateSteamPropertiesOutput(t, actual.ventedSteam);
}

function validateDeaeratorOutput(t, actual) {
    var actualDeaerator = actual.deaeratorOutput;

    t.equal(actualDeaerator.feedwaterEnergyFlow, 0);
    t.equal(actualDeaerator.feedwaterMassFlow, 0);
    t.equal(actualDeaerator.feedwaterPressure, 0);
    t.equal(actualDeaerator.feedwaterQuality, 0);
    t.equal(actualDeaerator.feedwaterSpecificEnthalpy, 0);
    t.equal(actualDeaerator.feedwaterSpecificEntropy, 0);
    t.equal(actualDeaerator.feedwaterTemperature, 0);
    t.equal(actualDeaerator.feedwaterVolume, 0);
    t.equal(actualDeaerator.inletSteamEnergyFlow, 0);
    t.equal(actualDeaerator.inletSteamMassFlow, 0);
    t.equal(actualDeaerator.inletSteamPressure, 0);
    t.equal(actualDeaerator.inletSteamQuality, 0);
    t.equal(actualDeaerator.inletSteamSpecificEnthalpy, 0);
    t.equal(actualDeaerator.inletSteamSpecificEntropy, 0);
    t.equal(actualDeaerator.inletSteamVolume, 0);
    t.equal(actualDeaerator.inletSteamTemperature, 0);
    t.equal(actualDeaerator.inletWaterEnergyFlow, 0);
    t.equal(actualDeaerator.inletWaterMassFlow, 0);
    t.equal(actualDeaerator.inletWaterPressure, 0);
    t.equal(actualDeaerator.inletWaterQuality, 0);
    t.equal(actualDeaerator.inletWaterSpecificEnthalpy, 0);
    t.equal(actualDeaerator.inletWaterSpecificEntropy, 0);
    t.equal(actualDeaerator.inletWaterVolume, 0);
    t.equal(actualDeaerator.inletWaterTemperature, 0);
    t.equal(actualDeaerator.ventedSteamEnergyFlow, 0);
    t.equal(actualDeaerator.ventedSteamMassFlow, 0);
    t.equal(actualDeaerator.ventedSteamPressure, 0);
    t.equal(actualDeaerator.ventedSteamQuality, 0);
    t.equal(actualDeaerator.ventedSteamSpecificEnthalpy, 0);
    t.equal(actualDeaerator.ventedSteamSpecificEntropy, 0);
    t.equal(actualDeaerator.ventedSteamVolume, 0);
    t.equal(actualDeaerator.ventedSteamTemperature, 0);
}

function validateFlashTankOutput(t, actual) {
    t.equal(actual.inletWaterEnergyFlow, 0);
    t.equal(actual.inletWaterMassFlow, 0);
    t.equal(actual.inletWaterPressure, 0);
    t.equal(actual.inletWaterQuality, 0);
    t.equal(actual.inletWaterVolume, 0);
    t.equal(actual.inletWaterSpecificEnthalpy, 0);
    t.equal(actual.inletWaterSpecificEntropy, 0);
    t.equal(actual.inletWaterTemperature, 0);
    t.equal(actual.outletGasEnergyFlow, 0);
    t.equal(actual.outletGasMassFlow, 0);
    t.equal(actual.outletGasPressure, 0);
    t.equal(actual.outletGasQuality, 0);
    t.equal(actual.outletGasVolume, 0);
    t.equal(actual.outletGasSpecificEnthalpy, 0);
    t.equal(actual.outletGasSpecificEntropy, 0);
    t.equal(actual.outletGasTemperature, 0);
    t.equal(actual.outletLiquidEnergyFlow, 0);
    t.equal(actual.outletLiquidMassFlow, 0);
    t.equal(actual.outletLiquidPressure, 0);
    t.equal(actual.outletLiquidQuality, 0);
    t.equal(actual.outletLiquidVolume, 0);
    t.equal(actual.outletLiquidSpecificEnthalpy, 0);
    t.equal(actual.outletLiquidSpecificEntropy, 0);
    t.equal(actual.outletLiquidTemperature, 0);
}

function validateBlowdownFlashTank(t, actual) {
    validateFlashTankOutput(t, actual.blowdownFlashTank);
}

function validateCondensateFlashTank(t, actual) {
    validateFlashTankOutput(t, actual.condensateFlashTank);
}

function validateHighPressureCondensateFlashTank(t, actual) {
    validateFlashTankOutput(t, actual.highPressureCondensateFlashTank);
}

function validateMediumPressureCondensateFlashTank(t, actual) {
    validateFlashTankOutput(t, actual.mediumPressureCondensateFlashTank);
}

function validateHeaderOutputObj(t, actual) {
    var actualHeader = actual.headerOutput;

    t.equal(actualHeader.energyFlow, 0);
    t.equal(actualHeader.massFlow, 0);
    t.equal(actualHeader.pressure, 0);
    t.equal(actualHeader.quality, 0);
    t.equal(actualHeader.specificEnthalpy, 0);
    t.equal(actualHeader.specificEntropy, 0);
    t.equal(actualHeader.temperature, 0);
    //t.equal(actualHeader.heatLoss, 0);
}

function validateHeatLossOutput(t, actual) {
    var actualHeatLoss = actual.heatLossOutput;

    t.equal(actualHeatLoss.heatLoss, 0);
    t.equal(actualHeatLoss.inletEnergyFlow, 0);
    t.equal(actualHeatLoss.inletMassFlow, 0);
    t.equal(actualHeatLoss.inletPressure, 0);
    t.equal(actualHeatLoss.inletQuality, 0);
    t.equal(actualHeatLoss.inletSpecificEnthalpy, 0);
    t.equal(actualHeatLoss.inletSpecificEntropy, 0);
    t.equal(actualHeatLoss.inletTemperature, 0);
    t.equal(actualHeatLoss.outletEnergyFlow, 0);
    t.equal(actualHeatLoss.outletMassFlow, 0);
    t.equal(actualHeatLoss.outletPressure, 0);
    t.equal(actualHeatLoss.outletQuality, 0);
    t.equal(actualHeatLoss.outletSpecificEnthalpy, 0);
    t.equal(actualHeatLoss.outletSpecificEntropy, 0);
    t.equal(actualHeatLoss.outletTemperature, 0);
}

function validatePrvOutput(t, actual) {
    t.equal(actual.feedwaterEnergyFlow, 0);
    t.equal(actual.feedwaterMassFlow, 0);
    t.equal(actual.feedwaterPressure, 0);
    t.equal(actual.feedwaterQuality, 0);
    t.equal(actual.feedwaterVolume, 0);
    t.equal(actual.feedwaterSpecificEnthalpy, 0);
    t.equal(actual.feedwaterSpecificEntropy, 0);
    t.equal(actual.feedwaterTemperature, 0);
    t.equal(actual.inletEnergyFlow, 0);
    t.equal(actual.inletMassFlow, 0);
    t.equal(actual.inletPressure, 0);
    t.equal(actual.inletQuality, 0);
    t.equal(actual.inletVolume, 0);
    t.equal(actual.inletSpecificEnthalpy, 0);
    t.equal(actual.inletSpecificEntropy, 0);
    t.equal(actual.inletTemperature, 0);
    t.equal(actual.outletEnergyFlow, 0);
    t.equal(actual.outletMassFlow, 0);
    t.equal(actual.outletPressure, 0);
    t.equal(actual.outletQuality, 0);
    t.equal(actual.outletVolume, 0);
    t.equal(actual.outletSpecificEnthalpy, 0);
    t.equal(actual.outletSpecificEntropy, 0);
    t.equal(actual.outletTemperature, 0);
}

function validateHighPressureToMediumPressurePrv(t, actual) {
    validatePrvOutput(t, actual.highPressureToMediumPressurePrv);
}

function validateMediumPressureToLowPressurePrv(t, actual) {
    validatePrvOutput(t, actual.mediumPressureToLowPressurePrv);
}

function validateTurbineOutput(t, actual) {
    t.equal(actual.energyOut, 0);
    t.equal(actual.generatorEfficiency, 0);
    t.equal(actual.inletEnergyFlow, 0);
    t.equal(actual.inletPressure, 0);
    t.equal(actual.inletQuality, 0);
    t.equal(actual.inletVolume, 0);
    t.equal(actual.inletSpecificEnthalpy, 0);
    t.equal(actual.inletSpecificEntropy, 0);
    t.equal(actual.inletTemperature, 0);
    t.equal(actual.isentropicEfficiency, 0);
    t.equal(actual.massFlow, 0);
    t.equal(actual.outletEnergyFlow, 0);
    t.equal(actual.outletPressure, 0);
    t.equal(actual.outletQuality, 0);
    t.equal(actual.outletVolume, 0);
    t.equal(actual.outletSpecificEnthalpy, 0);
    t.equal(actual.outletSpecificEntropy, 0);
    t.equal(actual.outletTemperature, 0);
    t.equal(actual.powerOut, 0);
    t.equal(actual.outletIdealPressure, 0);
    t.equal(actual.outletIdealTemperature, 0);
    t.equal(actual.outletIdealSpecificEnthalpy, 0);
    t.equal(actual.outletIdealSpecificEntropy, 0);
    t.equal(actual.outletIdealQuality, 0);
    t.equal(actual.outletIdealVolume, 0);
}

function validateCondensingTurbine(t, actual) {
    validateTurbineOutput(t, actual.condensingTurbine);
}

function validateHighPressureToMediumPressureTurbine(t, actual) {
    validateTurbineOutput(t, actual.highPressureToMediumPressureTurbine);
}

function validateHighPressureToLowPressureTurbine(t, actual) {
    validateTurbineOutput(t, actual.highPressureToLowPressureTurbine);
}

function validateMediumPressureToLowPressureTurbine(t, actual) {
    validateTurbineOutput(t, actual.mediumPressureToLowPressureTurbine);
}
