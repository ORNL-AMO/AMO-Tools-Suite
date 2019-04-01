const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({module_root: testRoot, bindings: 'ssmt'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('steamModeler', function (t) {
    t.type(bindings.steamModeler, 'function');

    var steamModelerInput = makeSteamModelerInput();
    var actual = bindings.steamModeler(steamModelerInput);

    //TODO remove me and assert values when actual results return
    console.log("================");
    console.log("JS steamModelerInput=");
    console.log(JSON.stringify(steamModelerInput));
    console.log("================");
    console.log("JS actual=");
    console.log(JSON.stringify(actual));
    console.log("================");

    validate(t, actual);

    // not used: validateHeaderOutputObj(t, actual);
    // not used (part of unused headerOutputObj): validateHeatLossOutput(t, actual);

    t.end();
});

function makeSteamModelerInput() {
    // Values that work for SteamSystemModelerTool::regionSelect()
    var temperature = 594.65;

    var boilerInput = {
        fuelType: 1,
        fuel: 1,
        combustionEfficiency: 1,
        blowdownRate: 1,
        blowdownFlashed: 1,
        preheatMakeupWater: 1,
        steamTemperature: temperature,
        deaeratorVentRate: 1,
        deaeratorPressure: 1,
        approachTemperature: 1,
    };

    var header1 = {
        pressure: 1,
        processSteamUsage: 1,
        condensationRecoveryRate: 1,
        heatLoss: 1,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: 1,

        condensateReturnTemperature: temperature,
        flashCondensateReturn: true,
    };
    var header2 = {
        pressure: 2,
        processSteamUsage: 2,
        condensationRecoveryRate: 2,
        heatLoss: 2,

        flashCondensateIntoHeader: true,
        desuperheatSteamIntoNextHighest: true,
        desuperheatSteamTemperature: temperature,

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
        desuperheatSteamTemperature: temperature,

        condensateReturnTemperature: null,
        flashCondensateReturn: null,
    };
    var headerInput = {
        highPressureHeader: header1,
        // TODO try mediumPressureHeader: null,
        mediumPressureHeader: header2,
        lowPressureHeader: header3,
    }

    var operationsInput = {
        sitePowerImport: 1,
        makeUpWaterTemperature: temperature,
        operatingHoursPerYear: 1,
        fuelCosts: 1,
        electricityCosts: 1,
        makeUpWaterCosts: 1,
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

    var steamModelerInput = {
        isBaselineCalc: true,
        baselinePowerDemand: 1,
        boilerInput: boilerInput,
        headerInput: headerInput,
        operationsInput: operationsInput,
        turbineInput: turbineInput,
    };

    return steamModelerInput;
}

function validate(t, actual) {
    validateOperations(t, actual);
    validateBoiler(t, actual);
    validateDeaerator(t, actual);

    validateHighPressureHeaderSteam(t, actual);
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
}

function validateOperations(t, actual) {
    var actualOperations = actual.operationsOutput;

    t.equal(actualOperations.powerGenerated, 2.679200946487e-312);
    t.equal(actualOperations.boilerFuelCost, 2.67920095451e-312);
    t.equal(actualOperations.makeupWaterCost, 2.67920095451e-312);
    t.equal(actualOperations.totalOperatingCost, 2.679200947514e-312);
    t.equal(actualOperations.powerGenerationCost, 2.679200947514e-312);
    t.equal(actualOperations.boilerFuelUsage, 1400.945054970803);
    t.equal(actualOperations.sitePowerImport, 2.67920095048e-312);
    t.equal(actualOperations.sitePowerDemand, 6.9530161006562e-310);
}

function validateBoiler(t, actual) {
    var actualBoiler = actual.boilerOutput;

    t.equal(actualBoiler.steamPressure, 1);
    t.equal(actualBoiler.steamTemperature, 594.65);
    t.equal(actualBoiler.steamSpecificEnthalpy, 3097.591269286749);
    t.equal(actualBoiler.steamSpecificEntropy, 7.203311626195247);
    t.equal(actualBoiler.steamQuality, 1);
    t.equal(actualBoiler.steamVolume, 0.26858473001463523);
    t.equal(actualBoiler.steamMassFlow, 6);
    t.equal(actualBoiler.steamEnergyFlow, 18.585547615720493);

    t.equal(actualBoiler.blowdownPressure, 1);
    t.equal(actualBoiler.blowdownTemperature, 453.0356323914666);
    t.equal(actualBoiler.blowdownSpecificEnthalpy, 762.6828443354106);
    t.equal(actualBoiler.blowdownSpecificEntropy, 2.138431350899127);
    t.equal(actualBoiler.blowdownQuality, 0);
    t.equal(actualBoiler.blowdownVolume, 0.0011272337454016697);
    t.equal(actualBoiler.blowdownMassFlow, 0.06060606060606061);
    t.equal(actualBoiler.blowdownEnergyFlow, 0.046223202686994584);

    t.equal(actualBoiler.feedwaterPressure, 1);
    t.equal(actualBoiler.feedwaterTemperature, 453.0356323914666);
    t.equal(actualBoiler.feedwaterSpecificEnthalpy, 762.6828443354106);
    t.equal(actualBoiler.feedwaterSpecificEntropy, 2.138431350899127);
    t.equal(actualBoiler.feedwaterQuality, 0);
    t.equal(actualBoiler.feedwaterVolume, 0.0011272337454016697);
    t.equal(actualBoiler.feedwaterMassFlow, 6.0606060606060606);
    t.equal(actualBoiler.feedwaterEnergyFlow, 4.6223202686994584);

    t.equal(actualBoiler.boilerEnergy, 14.009450549708031);
    t.equal(actualBoiler.fuelEnergy, 1400.945054970803);
    t.equal(actualBoiler.blowdownRate, 1);
    t.equal(actualBoiler.combustionEff, 1);
}

function validateFluidProperties(t, actual, expected) {
    t.equal(actual.pressure, expected.pressure);
    t.equal(actual.temperature, expected.temperature);
    t.equal(actual.specificEnthalpy, expected.specificEnthalpy);
    t.equal(actual.specificEntropy, expected.specificEntropy);
    t.equal(actual.quality, expected.quality);
    t.equal(actual.specificVolume, expected.specificVolume);
    t.equal(actual.massFlow, expected.massFlow);
    t.equal(actual.energyFlow, expected.energyFlow);
}

function validateHighPressureHeaderSteam(t, actual) {
    var expected = {
        pressure: 0,
        temperature: 0,
        specificEnthalpy: 0,
        specificEntropy: 0,
        quality: 0,
        specificVolume: 0,
        massFlow: 0,
        energyFlow: 0,
    }
    validateFluidProperties(t, actual.highPressureHeaderSteam, expected);
}

function validateMakeupWater(t, actual) {
    var expected = {
        pressure: 0,
        temperature: 0,
        specificEnthalpy: 0,
        specificEntropy: 0,
        quality: 0,
        specificVolume: 0,
        massFlow: 0,
        energyFlow: 0,
    }
    validateFluidProperties(t, actual.makeupWater, expected);
}

function validateMakeupWaterAndCondensate(t, actual) {
    var expected = {
        pressure: 0,
        temperature: 0,
        specificEnthalpy: 0,
        specificEntropy: 0,
        quality: 0,
        specificVolume: 0,
        massFlow: 0,
        energyFlow: 0,
    }
    validateFluidProperties(t, actual.makeupWaterAndCondensate, expected);
}

function validateHighPressureProcessSteamUsage(t, actual) {
    var expected = {
        pressure: 0,
        temperature: 0,
        specificEnthalpy: 0,
        specificEntropy: 0,
        quality: 0,
        specificVolume: 0,
        massFlow: 0,
        energyFlow: 0,
    }
    validateFluidProperties(t, actual.highPressureProcessSteamUsage, expected);
}

function validateMediumPressureHeaderSteam(t, actual) {
    var expected = {
        pressure: 0,
        temperature: 0,
        specificEnthalpy: 0,
        specificEntropy: 0,
        quality: 0,
        specificVolume: 0,
        massFlow: 0,
        energyFlow: 0,
    }
    validateFluidProperties(t, actual.mediumPressureHeaderSteam, expected);
}

function validateLowPressureHeaderSteam(t, actual) {
    var expected = {
        pressure: 0,
        temperature: 0,
        specificEnthalpy: 0,
        specificEntropy: 0,
        quality: 0,
        specificVolume: 0,
        massFlow: 0,
        energyFlow: 0,
    }
    validateFluidProperties(t, actual.lowPressureHeaderSteam, expected);
}

function validateVentedSteam(t, actual) {
    var ventedSteam = actual.ventedSteam;
    if (typeof ventedSteam !== 'undefined') {
        var expected = {
            pressure: 0,
            temperature: 0,
            specificEnthalpy: 0,
            specificEntropy: 0,
            quality: 0,
            specificVolume: 0,
            massFlow: 0,
            energyFlow: 0,
        }
        validateFluidProperties(t, ventedSteam, expected);
    }
}

function validateDeaerator(t, actual) {
    var actualDeaerator = actual.deaeratorOutput;

    t.equal(actualDeaerator.feedwaterEnergyFlow, 4.6223202686994584);
    t.equal(actualDeaerator.feedwaterMassFlow, 6.0606060606060606);
    t.equal(actualDeaerator.feedwaterPressure, 1);
    t.equal(actualDeaerator.feedwaterQuality, 0);
    t.equal(actualDeaerator.feedwaterSpecificEnthalpy, +762.6828443354106);
    t.equal(actualDeaerator.feedwaterSpecificEntropy, 2.138431350899127);
    t.equal(actualDeaerator.feedwaterTemperature, 453.0356323914666);
    t.equal(actualDeaerator.feedwaterVolume, 0);
    t.ok(isNaN(actualDeaerator.inletSteamEnergyFlow));
    t.ok(isNaN(actualDeaerator.inletSteamMassFlow));
    t.equal(actualDeaerator.inletSteamPressure, 3);
    t.equal(actualDeaerator.inletSteamQuality, 1);
    t.ok(isNaN(actualDeaerator.inletSteamSpecificEnthalpy));
    t.ok(isNaN(actualDeaerator.inletSteamSpecificEntropy));
    t.ok(isNaN(actualDeaerator.inletSteamVolume));
    t.ok(isNaN(actualDeaerator.inletSteamTemperature));
    t.ok(isNaN(actualDeaerator.inletWaterEnergyFlow));
    t.ok(isNaN(actualDeaerator.inletWaterMassFlow));
    t.equal(actualDeaerator.inletWaterPressure, 1);
    t.equal(actualDeaerator.inletWaterQuality, 1);
    t.ok(isNaN(actualDeaerator.inletWaterSpecificEnthalpy));
    t.ok(isNaN(actualDeaerator.inletWaterSpecificEntropy));
    t.ok(isNaN(actualDeaerator.inletWaterVolume));
    t.ok(isNaN(actualDeaerator.inletWaterTemperature));
    t.equal(actualDeaerator.ventedSteamEnergyFlow, 0.16831027501119167);
    t.equal(actualDeaerator.ventedSteamMassFlow, 0.06060606060606061);
    t.equal(actualDeaerator.ventedSteamPressure, 1);
    t.equal(actualDeaerator.ventedSteamQuality, 1);
    t.equal(actualDeaerator.ventedSteamSpecificEnthalpy, 2777.119537684662);
    t.equal(actualDeaerator.ventedSteamSpecificEntropy, 6.58497899635217);
    t.equal(actualDeaerator.ventedSteamVolume, 0);
    t.equal(actualDeaerator.ventedSteamTemperature, 453.0356323914666);
}

function validateFlashTank(t, actual, expected) {
    t.equal(actual.inletWaterEnergyFlow, expected.inletWaterEnergyFlow);
    t.equal(actual.inletWaterMassFlow, expected.inletWaterMassFlow);
    t.equal(actual.inletWaterPressure, expected.inletWaterPressure);
    t.equal(actual.inletWaterQuality, expected.inletWaterQuality);
    t.equal(actual.inletWaterVolume, expected.inletWaterVolume);
    t.equal(actual.inletWaterSpecificEnthalpy, expected.inletWaterSpecificEnthalpy);
    t.equal(actual.inletWaterSpecificEntropy, expected.inletWaterSpecificEntropy);
    t.equal(actual.inletWaterTemperature, expected.inletWaterTemperature);
    t.equal(actual.outletGasEnergyFlow, expected.outletGasEnergyFlow);
    t.equal(actual.outletGasMassFlow, expected.outletGasMassFlow);
    t.equal(actual.outletGasPressure, expected.outletGasPressure);
    t.equal(actual.outletGasQuality, expected.outletGasQuality);
    t.equal(actual.outletGasVolume, expected.outletGasVolume);
    t.equal(actual.outletGasSpecificEnthalpy, expected.outletGasSpecificEnthalpy);
    t.equal(actual.outletGasSpecificEntropy, expected.outletGasSpecificEntropy);
    t.equal(actual.outletGasTemperature, expected.outletGasTemperature);
    t.equal(actual.outletLiquidEnergyFlow, expected.outletLiquidEnergyFlow);
    t.equal(actual.outletLiquidMassFlow, expected.outletLiquidMassFlow);
    t.equal(actual.outletLiquidPressure, expected.outletLiquidPressure);
    t.equal(actual.outletLiquidQuality, expected.outletLiquidQuality);
    t.equal(actual.outletLiquidVolume, expected.outletLiquidVolume);
    t.equal(actual.outletLiquidSpecificEnthalpy, expected.outletLiquidSpecificEnthalpy);
    t.equal(actual.outletLiquidSpecificEntropy, expected.outletLiquidSpecificEntropy);
    t.equal(actual.outletLiquidTemperature, expected.outletLiquidTemperature);
}

function validateBlowdownFlashTank(t, actual) {
    var expected = {
        inletWaterEnergyFlow: 0.046223202686994584,
        inletWaterMassFlow: 0.06060606060606061,
        inletWaterPressure: 1,
        inletWaterQuality: 0,
        inletWaterVolume: 0.0011272337454016697,
        inletWaterSpecificEnthalpy: 762.6828443354106,
        inletWaterSpecificEntropy: 2.138431350899127,
        inletWaterTemperature: 453.0356323914666,
        outletGasEnergyFlow: 0,
        outletGasMassFlow: 0,
        outletGasPressure: 3,
        outletGasQuality: 1,
        outletGasVolume: 0.06666407913357607,
        outletGasSpecificEnthalpy: 2803.2647389701606,
        outletGasSpecificEntropy: 6.185787810829954,
        outletGasTemperature: 507.0084450062522,
        outletLiquidEnergyFlow: 0.046223202686994584,
        outletLiquidMassFlow: 0.06060606060606061,
        outletLiquidPressure: 1,
        outletLiquidQuality: 0,
        outletLiquidVolume: 0.0011272337454016697,
        outletLiquidSpecificEnthalpy: 762.6828443354106,
        outletLiquidSpecificEntropy: 2.138431350899127,
        outletLiquidTemperature: 453.0356323914666,
    }
    validateFlashTank(t, actual.blowdownFlashTank, expected);
}

function validateCondensateFlashTank(t, actual) {
    var expected = {
        inletWaterEnergyFlow: 0,
        inletWaterMassFlow: 6.9515608029468e-310,
        inletWaterPressure: 1.069240014688e-311,
        inletWaterQuality: 6.9515608031658e-310,
        inletWaterVolume: 1.140068544056e-311,
        inletWaterSpecificEnthalpy: 1.457898223123e-311,
        inletWaterSpecificEntropy: 4.07e-321,
        inletWaterTemperature: 6.9515608908319e-310,
        outletGasEnergyFlow: 1.5e-323,
        outletGasMassFlow: 0,
        outletGasPressure: 1.5831766736227e-311,
        outletGasQuality: 5.417114295187e-312,
        outletGasVolume: 1.5831769110667e-311,
        outletGasSpecificEnthalpy: 4.42284461694e-312,
        outletGasSpecificEntropy: 4.42284461694e-312,
        outletGasTemperature: 1e-323,
        outletLiquidEnergyFlow: 0,
        outletLiquidMassFlow: 6.9515608898051e-310,
        outletLiquidPressure: 1.5831769110785e-311,
        outletLiquidQuality: 1.5831769110904e-311,
        outletLiquidVolume: 1.5831769110904e-311,
        outletLiquidSpecificEnthalpy: 0,
        outletLiquidSpecificEntropy: 0,
        outletLiquidTemperature: 1.5831769110904e-311,
    }
    validateFlashTank(t, actual.condensateFlashTank, expected);
}

function validateHighPressureCondensateFlashTank(t, actual) {
    var expected = {
        inletWaterEnergyFlow: 0.0076268284433541065,
        inletWaterMassFlow: 0.01,
        inletWaterPressure: 1,
        inletWaterQuality: 0,
        inletWaterVolume: 0.0011272337454016697,
        inletWaterSpecificEnthalpy: 762.6828443354106,
        inletWaterSpecificEntropy: 2.138431350899127,
        inletWaterTemperature: 453.0356323914666,
        outletGasEnergyFlow: 0,
        outletGasMassFlow: 0,
        outletGasPressure: 2,
        outletGasQuality: 1,
        outletGasVolume: 0.09958054416889665,
        outletGasSpecificEnthalpy: 2798.384140241516,
        outletGasSpecificEntropy: 6.339164377128661,
        outletGasTemperature: 485.5345353184905,
        outletLiquidEnergyFlow: 0.0076268284433541065,
        outletLiquidMassFlow: 0.01,
        outletLiquidPressure: 1,
        outletLiquidQuality: 0,
        outletLiquidVolume: 0.0011272337454016697,
        outletLiquidSpecificEnthalpy: 762.6828443354106,
        outletLiquidSpecificEntropy: 2.138431350899127,
        outletLiquidTemperature: 453.0356323914666,
    }
    validateFlashTank(t, actual.highPressureCondensateFlashTank, expected);
}

function validateMediumPressureCondensateFlashTank(t, actual) {
    var expected = {
        inletWaterEnergyFlow: 0.0439717024888124,
        inletWaterMassFlow: 0.05,
        inletWaterPressure: 3,
        inletWaterQuality: 0,
        inletWaterVolume: 0.0011645473179549442,
        inletWaterSpecificEnthalpy: 879.434049776248,
        inletWaterSpecificEntropy: 2.3840762829025266,
        inletWaterTemperature: 479.0276501729469,
        outletGasEnergyFlow: 0,
        outletGasMassFlow: 0,
        outletGasPressure: 3,
        outletGasQuality: 1,
        outletGasVolume: 0.06666407913357607,
        outletGasSpecificEnthalpy: 2803.2647389701606,
        outletGasSpecificEntropy: 6.185787810829954,
        outletGasTemperature: 507.0084450062522,
        outletLiquidEnergyFlow: 0.0439717024888124,
        outletLiquidMassFlow: 0.05,
        outletLiquidPressure: 3,
        outletLiquidQuality: 0,
        outletLiquidVolume: 0.0011645473179549442,
        outletLiquidSpecificEnthalpy: 879.434049776248,
        outletLiquidSpecificEntropy: 2.3840762829025266,
        outletLiquidTemperature: 479.0276501729469,
    }
    validateFlashTank(t, actual.mediumPressureCondensateFlashTank, expected);
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
