const fs = require('fs');
const d3 = require('d3-dsv');
const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../../')
    , bindings = require('bindings')({module_root: testRoot, bindings: 'ssmt'});

//TODO extract make input
//TODO extract make expected
//TODO extract validate results

function logSectionStart(msg) {
    console.log("================================================");
    console.log(msg);
}

//converts spreadsheet-format lettered columns to numerical indices
function convertColumnToIndex(col) {
    let colIndex = -1;
    let a = "a";
    let charCodeA = a.charCodeAt(0);
    for (let i = 0; i < col.length; i++) {
        let exp = (col.length - 1) - i;
        let charNum = col.charCodeAt(i) - charCodeA + 1;
        if (charNum < 1 || charNum > 26) {
            throw "ERROR: Invalid column title: '" + col + "' is not a valid column title. Column titles must contain only characters 'a'-'z'.";
        }

        // use position of the supplied letter within the alphabet
        // to establish a base-26 numerical system
        colIndex += charNum * Math.pow(26, exp);
    }
    return colIndex;
}

function checkRangeOverlap(startA, endA, startB, endB) {
    if (startA == startB) {
        return true;
    }
    if (startA == endB) {
        return true;
    }
    if (endA == startB) {
        return true;
    }
    if (startA > startB) {
        if (startA <= endB) {
            return true;
        }
    }
    if (startA < startB) {
        if (endA >= startB) {
            return true;
        }
    }
}

function loadConfigFile() {
    var configDataFileName = "ssmtTestConfig";
    let configData = loadDataFile(configDataFileName);
    validateDataFile(configData, configDataFileName);
    return configData;
}

function loadDataFile(dataFileName) {
    let file = makeDataFileName(dataFileName);
    return loadCsvFile(file);
}

function makeDataFileName(dataFileName) {
    return testRoot + "/tests/at/csv/" + dataFileName + ".csv";
}

function loadCsvFile(dataFile) {
    logSectionStart('loading file=' + dataFile);
    let rawFile = fs.readFileSync(dataFile, "utf8");
    return d3.csvParse(rawFile);
}

function validateDataFile(data, dataFileName) {
    if (data.length === 0) {
        throw "ERROR: empty file='" + dataFileName + "'.";
    }
}

function validateConfigDataEntry(configDataColumnIndexes) {
    let metaDataStartColumnIndex = configDataColumnIndexes.metaDataStartColumnIndex;
    let metaDataEndColumnIndex = configDataColumnIndexes.metaDataEndColumnIndex;
    let inputDataStartColumnIndex = configDataColumnIndexes.inputDataStartColumnIndex;
    let inputDataEndColumnIndex = configDataColumnIndexes.inputDataEndColumnIndex;
    let expectedDataStartColumnIndex = configDataColumnIndexes.expectedDataStartColumnIndex;
    let expectedDataEndColumnIndex = configDataColumnIndexes.expectedDataEndColumnIndex;

    //makes sure starting points are not beyond ending points
    if (metaDataStartColumnIndex > metaDataEndColumnIndex) {
        throw 'ERROR: metaDataStartColumn is greater than the metaDataEndColumn.';
    }
    if (inputDataStartColumnIndex > inputDataEndColumnIndex) {
        throw 'ERROR: inputDataStartColumn is greater than the inputDataEndColumn.';
    }
    if (expectedDataStartColumnIndex > expectedDataEndColumnIndex) {
        throw 'ERROR: expectedDataStartColumn is greater than the expectedDataEndColumn.';
    }
    //makes sure no overlap between collections of columns
    if (checkRangeOverlap(metaDataStartColumnIndex, metaDataEndColumnIndex, inputDataStartColumnIndex, inputDataEndColumnIndex)) {
        throw 'ERROR: Meta data and Input data ranges overlap. Start and End columns are INCLUSIVE meaning the column supplied for the start and ending points are included in the range.';
    }
    if (checkRangeOverlap(metaDataStartColumnIndex, metaDataEndColumnIndex, expectedDataStartColumnIndex, expectedDataEndColumnIndex)) {
        throw 'ERROR: Meta data and Expected data ranges overlap. Start and End columns are INCLUSIVE meaning the column supplied for the start and ending points are included in the range.';
    }
    if (checkRangeOverlap(inputDataStartColumnIndex, inputDataEndColumnIndex, expectedDataStartColumnIndex, expectedDataEndColumnIndex)) {
        throw 'ERROR: Input data and Expected data ranges overlap. Start and End columns are INCLUSIVE meaning the column supplied for the start and ending points are included in the range.';
    }
}

function validateTestDataEntry(testDataFileName, configDataColumnIndexes, testDataColumnCount, testDataEntry, testIdentification) {
    let metaDataEndColumnIndex = configDataColumnIndexes.metaDataEndColumnIndex;
    let inputDataEndColumnIndex = configDataColumnIndexes.inputDataEndColumnIndex;
    let expectedDataEndColumnIndex = configDataColumnIndexes.expectedDataEndColumnIndex;

    // indexes are 0 based, so add 1
    let configTestDataColumnCount =
        Math.max(metaDataEndColumnIndex, inputDataEndColumnIndex, expectedDataEndColumnIndex) + 1;
    if (configTestDataColumnCount > testDataColumnCount) {
        throw "ERROR: test " + testIdentification +
        " in file='" + testDataFileName + ".csv' has " + testDataColumnCount +
        " columns and config data expected " + configTestDataColumnCount + " columns.";
    }
}

function makeColumnIndexList(configDataEntry) {
    let metaDataStartColumn = configDataEntry.metaDataStartColumn.toLowerCase();
    let metaDataEndColumn = configDataEntry.metaDataEndColumn.toLowerCase();
    let inputDataStartColumn = configDataEntry.inputDataStartColumn.toLowerCase();
    let inputDataEndColumn = configDataEntry.inputDataEndColumn.toLowerCase();
    let expectedDataStartColumn = configDataEntry.expectedDataStartColumn.toLowerCase();
    let expectedDataEndColumn = configDataEntry.expectedDataEndColumn.toLowerCase();

    let metaDataStartColumnIndex = convertColumnToIndex(metaDataStartColumn);
    let metaDataEndColumnIndex = convertColumnToIndex(metaDataEndColumn);
    let inputDataStartColumnIndex = convertColumnToIndex(inputDataStartColumn);
    let inputDataEndColumnIndex = convertColumnToIndex(inputDataEndColumn);
    let expectedDataStartColumnIndex = convertColumnToIndex(expectedDataStartColumn);
    let expectedDataEndColumnIndex = convertColumnToIndex(expectedDataEndColumn);

    return {
        metaDataStartColumnIndex: metaDataStartColumnIndex,
        metaDataEndColumnIndex: metaDataEndColumnIndex,
        inputDataStartColumnIndex: inputDataStartColumnIndex,
        inputDataEndColumnIndex: inputDataEndColumnIndex,
        expectedDataStartColumnIndex: expectedDataStartColumnIndex,
        expectedDataEndColumnIndex: expectedDataEndColumnIndex,
    };
}

function makeTestIdentification(testDataEntry) {
    return "id='" + testDataEntry.id + "', name='" + testDataEntry.testName + "', description='" + testDataEntry.testDescription + "'";
}

function makeSteamInput(testDataEntry) {
    let isBaselineCalc = testDataEntry.isBaselineCalc;
    let baselinePowerDemand = testDataEntry.baselinePowerDemand;

    let boilerInput = makeBoilerInput(testDataEntry);
    let headerInput = makeHeaderInput(testDataEntry);
    let operationsInput = makeOperationsInput(testDataEntry);
    let turbineInput = makeTurbineInput(testDataEntry);

    return {
        isBaselineCalc: isBaselineCalc,
        baselinePowerDemand: baselinePowerDemand,
        boilerInput: boilerInput,
        headerInput: headerInput,
        operationsInput: operationsInput,
        turbineInput: turbineInput
    };
}

function makeExpectedDataNames(configDataColumnIndexes, columnNames) {
    let expectedDataNames = [];

    let expectedDataStartColumnIndex = configDataColumnIndexes.expectedDataStartColumnIndex;
    let expectedDataEndColumnIndex = configDataColumnIndexes.expectedDataEndColumnIndex;

    for (let columnNum = expectedDataStartColumnIndex; columnNum <= expectedDataEndColumnIndex; columnNum++) {
        expectedDataNames.push(columnNames[columnNum]);
    }

    return expectedDataNames;
}

function makeExpectedData(expectedDataNames, testDataEntry) {
    let expectedData = {};

    for (let nameNum = 0; nameNum < expectedDataNames.length; nameNum++) {
        let expectedDataName = expectedDataNames[nameNum];
        expectedData[expectedDataName] = testDataEntry[expectedDataName];
    }

    return expectedData;
}

function run() {
    console.log("================================================================");
    console.log("Running Acceptance Tests");

    let configData = loadConfigFile();

    let configDataEntryCount = configData.length;
    console.log("config file has " + configDataEntryCount + " entries to process");

    for (let configDataEntryNum = 0; configDataEntryNum < configDataEntryCount; configDataEntryNum++) {
        let configDataEntry = configData[configDataEntryNum];
        processConfigDataEntry(configDataEntry);
    }
}

function processConfigDataEntry(configDataEntry) {
    let testDataFileName = configDataEntry.testDataFileName;
    let testData = loadDataFile(testDataFileName);
    validateDataFile(testData, testDataFileName);

    logTestStatuses(testDataFileName, testData);
    processTestDataEntries(testDataFileName, testData, configDataEntry);
}

function logTestStatuses(testDataFileName, testData) {
    let testDataCount = testData.length;
    logSectionStart("Test data file=" + testDataFileName + " has " + testDataCount + " test entries:");
    for (let testDataNum = 0; testDataNum < testDataCount; testDataNum++) {
        let testDataEntry = testData[testDataNum];
        let testIdentification = makeTestIdentification(testDataEntry);
        console.log("enabled=" + testDataEntry.enabled + ", " + testIdentification);
    }
}

function processTestDataEntries(testDataFileName, testData, configDataEntry) {
    let configDataColumnIndexes = makeColumnIndexList(configDataEntry);
    validateConfigDataEntry(configDataColumnIndexes);

    let testDataCount = testData.length;
    let columnNames = testData.columns;
    let testDataColumnCount = columnNames.length;
    let expectedDataNames = makeExpectedDataNames(configDataColumnIndexes, columnNames);

    logSectionStart("Running Acceptance Tests in file=" + testDataFileName);
    for (let testDataNum = 0; testDataNum < testDataCount; testDataNum++) {
        let testDataEntry = testData[testDataNum];
        processTestDataEntry(testDataFileName, configDataColumnIndexes, testDataColumnCount, expectedDataNames, testDataEntry);
    }
}

function processTestDataEntry(testDataFileName, configDataColumnIndexes, testDataColumnCount, expectedDataNames, testDataEntry) {
    let testIdentification = makeTestIdentification(testDataEntry);
    validateTestDataEntry(testDataFileName, configDataColumnIndexes, testDataColumnCount, testDataEntry, testIdentification);

    if (testDataEntry.enabled.toLowerCase() === "true") {
        runTest(expectedDataNames, testDataEntry, testIdentification);
    } else {
        console.log("Skipping disabled test: " + testIdentification)
    }
}

function runTest(expectedDataNames, testDataEntry, testIdentification) {
    test(testIdentification, [{'diagnostic': 'false'}], function (t) {
        let nonExpectedDataTestCount = 3;   // type, same fields actual diff, same fields expected diff
        let testCount = expectedDataNames.length + nonExpectedDataTestCount;
        t.plan(testCount);

        t.type(bindings.steamModeler, 'function');

        let expectedData = makeExpectedData(expectedDataNames, testDataEntry);
        logSectionStart("expectedData=" + JSON.stringify(expectedData));

        let steamInput = makeSteamInput(testDataEntry);
        logSectionStart("steamInput=" + JSON.stringify(steamInput));

        let actualSteamModelerOutput = bindings.steamModeler(steamInput);
        logSectionStart(testIdentification + "\nactual steamOutput=" + JSON.stringify(actualSteamModelerOutput));

        let actualSteamModelerOutputFlattened = mapSteamModelerOutputToFlatArray(actualSteamModelerOutput);

        validateActualAndExpectedHaveSameFields(actualSteamModelerOutputFlattened, expectedData, t);

        validateOutput(expectedDataNames, actualSteamModelerOutputFlattened, expectedData, t);
    });
}

function validateOutput(expectedDataNames, actualSteamModelerOutputFlattened, expectedData, t) {
    let expectedColumnCount = expectedDataNames.length;
    for (let columnNum = 0; columnNum < expectedColumnCount; columnNum++) {
        let expectedDataName = expectedDataNames[columnNum];
        let actual = actualSteamModelerOutputFlattened[expectedDataName];
        let expected = expectedData[expectedDataName];

        compareActualToExpected(expectedDataName, actual, expected, t);
    }
}

function compareActualToExpected(expectedDataName, actual, expected, t) {
    let tolerance = 0.01;
    let result = calcCompareResult(actual, expected);

    let msg =
        expectedDataName + ": actual=" + actual + ", expected=" + expected +
        ", compare result=" + result + ", using tolerance=" + tolerance;

    if (Math.abs(result) < tolerance) {
        t.pass(msg);
    } else {
        t.fail(msg);
    }
}

function calcCompareResult(actual, expected) {
    let diff = expected - actual;

    if (isSpecified(expected)) {
        // prevent divide by 0
        if (expected == 0) {
            // diff alone is good decider
            return diff;
        } else {
            // check using percentage diff
            return diff / expected;
        }
    } else {
        if (isSpecified(actual)) {
            return NaN;
        } else {
            return 0;
        }
    }
}

function isSpecified(value) {
    return !(value === undefined || value === "");
}

function validateActualAndExpectedHaveSameFields(actual, expected, t) {
    let actualKeys = Object.keys(actual);
    let expectedKeys = Object.keys(expected);

    let actualHasDiff = array1MissingInArray2(actualKeys, expectedKeys);
    let expectedHasDiff = array1MissingInArray2(expectedKeys, actualKeys);

    t.same(actualHasDiff, [], "actual output has fields that expected does not.");
    t.same(expectedHasDiff, [], "expected output has fields that actual does not.");
}

function array1MissingInArray2(array1, array2) {
    return array1.filter(element => !array2.includes(element));
}

function makeTurbineInput(inputData) {
    let turbineInput = {
        highToLowTurbine: makeHighToLowTurbineObject(inputData),
        highToMediumTurbine: makeHighToMediumTurbineObject(inputData),
        mediumToLowTurbine: makeMediumToLowTurbineObject(inputData),
        condensingTurbine: makeCondensingTurbineObject(inputData)
    };
    return turbineInput;
}

function makeHighToLowTurbineObject(inputData) {
    let highToLowTurbine = {
        isentropicEfficiency: parseFloat(inputData.highToLowTurbineIsentropicEfficiency),
        generationEfficiency: parseFloat(inputData.highToLowTurbineGenerationEfficiency),
        operationType: parseInt(inputData.highToLowTurbineOperationType),
        operationValue1: parseFloat(inputData.highToLowTurbineOperationValue1),
        operationValue2: parseFloat(inputData.highToLowTurbineOperationValue2),
        useTurbine: inputData.highToLowTurbineUseTurbine
    };

    return highToLowTurbine;
}


function makeHighToMediumTurbineObject(inputData) {
    let highToMediumTurbine = {
        isentropicEfficiency: parseFloat(inputData.highToMediumTurbineIsentropicEfficiency),
        generationEfficiency: parseFloat(inputData.highToMediumTurbineGenerationEfficiency),
        operationType: parseInt(inputData.highToMediumTurbineOperationType),
        operationValue1: parseFloat(inputData.highToMediumTurbineOperationValue1),
        operationValue2: parseFloat(inputData.highToMediumTurbineOperationValue2),
        useTurbine: inputData.highToMediumTurbineUseTurbine
    };

    return highToMediumTurbine;
}

function makeMediumToLowTurbineObject(inputData) {
    let mediumToLowTurbine = {
        isentropicEfficiency: parseFloat(inputData.mediumToLowTurbineIsentropicEfficiency),
        generationEfficiency: parseFloat(inputData.mediumToLowTurbineGenerationEfficiency),
        operationType: parseInt(inputData.mediumToLowTurbineOperationType),
        operationValue1: parseFloat(inputData.mediumToLowTurbineOperationValue1),
        operationValue2: parseFloat(inputData.mediumToLowTurbineOperationValue2),
        useTurbine: inputData.mediumToLowTurbineUseTurbine
    };

    return mediumToLowTurbine;
}

function makeCondensingTurbineObject(inputData) {
    let condensingTurbine = {
        isentropicEfficiency: parseFloat(inputData.condensingTurbineIsentropicEfficiency),
        generationEfficiency: parseFloat(inputData.condensingTurbineGenerationEfficiency),
        condenserPressure: parseFloat(inputData.condensingTurbineCondenserPressure),
        operationType: parseInt(inputData.condensingTurbineOperationType),
        operationValue: parseFloat(inputData.condensingTurbineOperationValue),
        useTurbine: inputData.condensingTurbineUseTurbine
    };

    return condensingTurbine;
}


function makeOperationsInput(inputData) {
    let operationsInput = {
        sitePowerImport: parseFloat(inputData.sitePowerImport),
        makeUpWaterTemperature: parseFloat(inputData.makeUpWaterTemperature),
        operatingHoursPerYear: parseFloat(inputData.operatingHoursPerYear),
        fuelCosts: parseFloat(inputData.fuelCosts),
        electricityCosts: parseFloat(inputData.electricityCosts),
        makeUpWaterCosts: parseFloat(inputData.makeUpWaterCosts)
    };

    return operationsInput;
}

function makeHeaderInput(inputData) {
    let headerInput = {
        highPressureHeader: makeHighPressureHeaderObject(inputData),
        mediumPressureHeader: makeMediumPressureHeaderObject(inputData),
        lowPressureHeader: makeLowPressureHeaderObject(inputData)
    };
    return headerInput;
}


function makeHighPressureHeaderObject(inputData) {
    let highPressureHeader = {
        pressure: parseFloat(inputData.highPressureHeaderPressure),
        processSteamUsage: parseFloat(inputData.highPressureHeaderProcessSteamUsage),
        condensationRecoveryRate: parseFloat(inputData.highPressureHeaderCondensationRecoveryRate),
        heatLoss: parseFloat(inputData.highPressureHeaderHeatLoss),
        flashCondensateIntoHeader: inputData.highPressureHeaderFlashCondensateIntoHeader,
        desuperheatSteamIntoNextHighest: inputData.highPressureHeaderDesuperheatSteamIntoNextHighest,
        desuperheatSteamTemperature: parseFloat(inputData.highPressureHeaderDesuperheatSteamTemperature),
        condensateReturnTemperature: parseFloat(inputData.highPressureHeaderCondensateReturnTemperature),
        flashCondensateReturn: inputData.highPressureHeaderFlashCondensateReturn
    };
    return highPressureHeader;
}

function makeMediumPressureHeaderObject(inputData) {
    let mediumPressureHeader = {
        pressure: parseFloat(inputData.mediumPressureHeaderPressure),
        processSteamUsage: parseFloat(inputData.mediumPressureHeaderProcessSteamUsage),
        condensationRecoveryRate: parseFloat(inputData.mediumPressureHeaderCondensationRecoveryRate),
        heatLoss: parseFloat(inputData.mediumPressureHeaderHeatLoss),
        flashCondensateIntoHeader: inputData.mediumPressureHeaderFlashCondensateIntoHeader,
        desuperheatSteamIntoNextHighest: inputData.mediumPressureHeaderDesuperheatSteamIntoNextHighest,
        desuperheatSteamTemperature: parseFloat(inputData.mediumPressureHeaderDesuperheatSteamTemperature),
        condensateReturnTemperature: inputData.mediumPressureHeaderCondensateReturnTemperature,
        flashCondensateReturn: inputData.mediumPressureHeaderFlashCondensateReturn || null
    };
    return mediumPressureHeader;
}

function makeLowPressureHeaderObject(inputData) {
    let lowPressureHeader = {
        pressure: parseFloat(inputData.lowPressureHeaderPressure),
        processSteamUsage: parseFloat(inputData.lowPressureHeaderProcessSteamUsage),
        condensationRecoveryRate: parseFloat(inputData.lowPressureHeaderCondensationRecoveryRate),
        heatLoss: parseFloat(inputData.lowPressureHeaderHeatLoss),
        flashCondensateIntoHeader: inputData.lowPressureHeaderFlashCondensateIntoHeader,
        desuperheatSteamIntoNextHighest: inputData.lowPressureHeaderDesuperheatSteamIntoNextHighest,
        desuperheatSteamTemperature: parseFloat(inputData.lowPressureHeaderDesuperheatSteamTemperature),
        condensateReturnTemperature: inputData.lowPressureHeaderCondensateReturnTemperature,
        flashCondensateReturn: inputData.lowPressureHeaderFlashCondensateReturn || null
    };
    return lowPressureHeader;
}

function makeBoilerInput(inputData) {
    let boilerInput = {
        fuelType: parseFloat(inputData.fuelType),
        fuel: parseFloat(inputData.fuel),
        combustionEfficiency: parseFloat(inputData.combustionEfficiency),
        blowdownRate: parseFloat(inputData.blowdownRate),
        blowdownFlashed: inputData.blowdownFlashed,
        preheatMakeupWater: inputData.preheatMakeupWater,
        steamTemperature: parseFloat(inputData.steamTemperature),
        deaeratorVentRate: parseFloat(inputData.deaeratorVentRate),
        deaeratorPressure: parseFloat(inputData.deaeratorPressure),
        approachTemperature: parseFloat(inputData.approachTemperature)
    };
    return boilerInput;
}

function mapSteamModelerOutputToFlatArray(resultData) {
    let normalizedResultData = {
        boilerOutput_steamPressure: resultData.boilerOutput.steamPressure,
        boilerOutput_steamTemperature: resultData.boilerOutput.steamTemperature,
        boilerOutput_steamSpecificEnthalpy: resultData.boilerOutput.steamSpecificEnthalpy,
        boilerOutput_steamSpecificEntropy: resultData.boilerOutput.steamSpecificEntropy,
        boilerOutput_steamQuality: resultData.boilerOutput.steamQuality,
        boilerOutput_steamVolume: resultData.boilerOutput.steamVolume,
        boilerOutput_steamMassFlow: resultData.boilerOutput.steamMassFlow,
        boilerOutput_steamEnergyFlow: resultData.boilerOutput.steamEnergyFlow,
        boilerOutput_blowdownPressure: resultData.boilerOutput.blowdownPressure,
        boilerOutput_blowdownTemperature: resultData.boilerOutput.blowdownTemperature,
        boilerOutput_blowdownSpecificEnthalpy: resultData.boilerOutput.blowdownSpecificEnthalpy,
        boilerOutput_blowdownSpecificEntropy: resultData.boilerOutput.blowdownSpecificEntropy,
        boilerOutput_blowdownQuality: resultData.boilerOutput.blowdownQuality,
        boilerOutput_blowdownVolume: resultData.boilerOutput.blowdownVolume,
        boilerOutput_blowdownMassFlow: resultData.boilerOutput.blowdownMassFlow,
        boilerOutput_blowdownEnergyFlow: resultData.boilerOutput.blowdownEnergyFlow,
        boilerOutput_feedwaterPressure: resultData.boilerOutput.feedwaterPressure,
        boilerOutput_feedwaterTemperature: resultData.boilerOutput.feedwaterTemperature,
        boilerOutput_feedwaterSpecificEnthalpy: resultData.boilerOutput.feedwaterSpecificEnthalpy,
        boilerOutput_feedwaterSpecificEntropy: resultData.boilerOutput.feedwaterSpecificEntropy,
        boilerOutput_feedwaterQuality: resultData.boilerOutput.feedwaterQuality,
        boilerOutput_feedwaterVolume: resultData.boilerOutput.feedwaterVolume,
        boilerOutput_feedwaterMassFlow: resultData.boilerOutput.feedwaterMassFlow,
        boilerOutput_feedwaterEnergyFlow: resultData.boilerOutput.feedwaterEnergyFlow,
        boilerOutput_boilerEnergy: resultData.boilerOutput.boilerEnergy,
        boilerOutput_fuelEnergy: resultData.boilerOutput.fuelEnergy,
        boilerOutput_blowdownRate: resultData.boilerOutput.blowdownRate,
        boilerOutput_combustionEff: resultData.boilerOutput.combustionEff,

        blowdownFlashTankOutput_inletWaterEnergyFlow: resultData.blowdownFlashTank.inletWaterEnergyFlow,
        blowdownFlashTankOutput_inletWaterMassFlow: resultData.blowdownFlashTank.inletWaterMassFlow,
        blowdownFlashTankOutput_inletWaterPressure: resultData.blowdownFlashTank.inletWaterPressure,
        blowdownFlashTankOutput_inletWaterQuality: resultData.blowdownFlashTank.inletWaterQuality,
        blowdownFlashTankOutput_inletWaterVolume: resultData.blowdownFlashTank.inletWaterVolume,
        blowdownFlashTankOutput_inletWaterSpecificEnthalpy: resultData.blowdownFlashTank.inletWaterSpecificEnthalpy,
        blowdownFlashTankOutput_inletWaterSpecificEntropy: resultData.blowdownFlashTank.inletWaterSpecificEntropy,
        blowdownFlashTankOutput_inletWaterTemperature: resultData.blowdownFlashTank.inletWaterTemperature,
        blowdownFlashTankOutput_outletGasEnergyFlow: resultData.blowdownFlashTank.outletGasEnergyFlow,
        blowdownFlashTankOutput_outletGasMassFlow: resultData.blowdownFlashTank.outletGasMassFlow,
        blowdownFlashTankOutput_outletGasPressure: resultData.blowdownFlashTank.outletGasPressure,
        blowdownFlashTankOutput_outletGasQuality: resultData.blowdownFlashTank.outletGasQuality,
        blowdownFlashTankOutput_outletGasVolume: resultData.blowdownFlashTank.outletGasVolume,
        blowdownFlashTankOutput_outletGasSpecificEnthalpy: resultData.blowdownFlashTank.outletGasSpecificEnthalpy,
        blowdownFlashTankOutput_outletGasSpecificEntropy: resultData.blowdownFlashTank.outletGasSpecificEntropy,
        blowdownFlashTankOutput_outletGasTemperature: resultData.blowdownFlashTank.outletGasTemperature,
        blowdownFlashTankOutput_outletLiquidEnergyFlow: resultData.blowdownFlashTank.outletLiquidEnergyFlow,
        blowdownFlashTankOutput_outletLiquidMassFlow: resultData.blowdownFlashTank.outletLiquidMassFlow,
        blowdownFlashTankOutput_outletLiquidPressure: resultData.blowdownFlashTank.outletLiquidPressure,
        blowdownFlashTankOutput_outletLiquidQuality: resultData.blowdownFlashTank.outletLiquidQuality,
        blowdownFlashTankOutput_outletLiquidVolume: resultData.blowdownFlashTank.outletLiquidVolume,
        blowdownFlashTankOutput_outletLiquidSpecificEnthalpy: resultData.blowdownFlashTank.outletLiquidSpecificEnthalpy,
        blowdownFlashTankOutput_outletLiquidSpecificEntropy: resultData.blowdownFlashTank.outletLiquidSpecificEntropy,
        blowdownFlashTankOutput_outletLiquidTemperature: resultData.blowdownFlashTank.outletLiquidTemperature,

        highPressureSteamHeatLossOutput_heatLoss: resultData.highPressureSteamHeatLoss.heatLoss,
        highPressureSteamHeatLossOutput_inletPressure: resultData.highPressureSteamHeatLoss.inletPressure,
        highPressureSteamHeatLossOutput_inletTemperature: resultData.highPressureSteamHeatLoss.inletTemperature,
        highPressureSteamHeatLossOutput_inletSpecificEnthalpy: resultData.highPressureSteamHeatLoss.inletSpecificEnthalpy,
        highPressureSteamHeatLossOutput_inletSpecificEntropy: resultData.highPressureSteamHeatLoss.inletSpecificEntropy,
        highPressureSteamHeatLossOutput_inletQuality: resultData.highPressureSteamHeatLoss.inletQuality,
        highPressureSteamHeatLossOutput_inletSpecificVolume: resultData.highPressureSteamHeatLoss.inletVolume,
        highPressureSteamHeatLossOutput_inletMassFlow: resultData.highPressureSteamHeatLoss.inletMassFlow,
        highPressureSteamHeatLossOutput_inletEnergyFlow: resultData.highPressureSteamHeatLoss.inletEnergyFlow,
        highPressureSteamHeatLossOutput_outletPressure: resultData.highPressureSteamHeatLoss.outletPressure,
        highPressureSteamHeatLossOutput_outletTemperature: resultData.highPressureSteamHeatLoss.outletTemperature,
        highPressureSteamHeatLossOutput_outletSpecificEnthalpy: resultData.highPressureSteamHeatLoss.outletSpecificEnthalpy,
        highPressureSteamHeatLossOutput_outletSpecificEntropy: resultData.highPressureSteamHeatLoss.outletSpecificEntropy,
        highPressureSteamHeatLossOutput_outletQuality: resultData.highPressureSteamHeatLoss.outletQuality,
        highPressureSteamHeatLossOutput_outletSpecificVolume: resultData.highPressureSteamHeatLoss.outletVolume,
        highPressureSteamHeatLossOutput_outletMassFlow: resultData.highPressureSteamHeatLoss.outletMassFlow,
        highPressureSteamHeatLossOutput_outletEnergyFlow: resultData.highPressureSteamHeatLoss.outletEnergyFlow,

        highPressureCondensateOutput_pressure: resultData.highPressureCondensate.pressure,
        highPressureCondensateOutput_temperature: resultData.highPressureCondensate.temperature,
        highPressureCondensateOutput_specificEnthalpy: resultData.highPressureCondensate.specificEnthalpy,
        highPressureCondensateOutput_specificEntropy: resultData.highPressureCondensate.specificEntropy,
        highPressureCondensateOutput_quality: resultData.highPressureCondensate.quality,
        highPressureCondensateOutput_specificVolume: resultData.highPressureCondensate.specificVolume,
        highPressureCondensateOutput_massFlow: resultData.highPressureCondensate.massFlow,
        highPressureCondensateOutput_energyFlow: resultData.highPressureCondensate.energyFlow,

        highPressureHeaderSteamOutput_pressure: resultData.highPressureHeaderSteam.pressure,
        highPressureHeaderSteamOutput_temperature: resultData.highPressureHeaderSteam.temperature,
        highPressureHeaderSteamOutput_specificEnthalpy: resultData.highPressureHeaderSteam.specificEnthalpy,
        highPressureHeaderSteamOutput_specificEntropy: resultData.highPressureHeaderSteam.specificEntropy,
        highPressureHeaderSteamOutput_quality: resultData.highPressureHeaderSteam.quality,
        highPressureHeaderSteamOutput_specificVolume: resultData.highPressureHeaderSteam.specificVolume,
        highPressureHeaderSteamOutput_massFlow: resultData.highPressureHeaderSteam.massFlow,
        highPressureHeaderSteamOutput_energyFlow: resultData.highPressureHeaderSteam.energyFlow,

        combinedCondensateOutput_pressure: resultData.combinedCondensate.pressure,
        combinedCondensateOutput_temperature: resultData.combinedCondensate.temperature,
        combinedCondensateOutput_specificEnthalpy: resultData.combinedCondensate.specificEnthalpy,
        combinedCondensateOutput_specificEntropy: resultData.combinedCondensate.specificEntropy,
        combinedCondensateOutput_quality: resultData.combinedCondensate.quality,
        combinedCondensateOutput_volume: resultData.combinedCondensate.specificVolume,
        combinedCondensateOutput_massFlow: resultData.combinedCondensate.massFlow,
        combinedCondensateOutput_energyFlow: resultData.combinedCondensate.energyFlow,

        returnCondensateOutput_pressure: resultData.returnCondensate.pressure,
        returnCondensateOutput_temperature: resultData.returnCondensate.temperature,
        returnCondensateOutput_specificEnthalpy: resultData.returnCondensate.specificEnthalpy,
        returnCondensateOutput_specificEntropy: resultData.returnCondensate.specificEntropy,
        returnCondensateOutput_quality: resultData.returnCondensate.quality,
        returnCondensateOutput_volume: resultData.returnCondensate.specificVolume,
        returnCondensateOutput_massFlow: resultData.returnCondensate.massFlow,
        returnCondensateOutput_energyFlow: resultData.returnCondensate.energyFlow,

        highPressureCondensateFlashTankOutput_inletWaterEnergyFlow: resultData.highPressureCondensateFlashTank.inletWaterEnergyFlow,
        highPressureCondensateFlashTankOutput_inletWaterMassFlow: resultData.highPressureCondensateFlashTank.inletWaterMassFlow,
        highPressureCondensateFlashTankOutput_inletWaterPressure: resultData.highPressureCondensateFlashTank.inletWaterPressure,
        highPressureCondensateFlashTankOutput_inletWaterQuality: resultData.highPressureCondensateFlashTank.inletWaterQuality,
        highPressureCondensateFlashTankOutput_inletWaterVolume: resultData.highPressureCondensateFlashTank.inletWaterVolume,
        highPressureCondensateFlashTankOutput_inletWaterSpecificEnthalpy: resultData.highPressureCondensateFlashTank.inletWaterSpecificEnthalpy,
        highPressureCondensateFlashTankOutput_inletWaterSpecificEntropy: resultData.highPressureCondensateFlashTank.inletWaterSpecificEntropy,
        highPressureCondensateFlashTankOutput_inletWaterTemperature: resultData.highPressureCondensateFlashTank.inletWaterTemperature,
        highPressureCondensateFlashTankOutput_outletGasEnergyFlow: resultData.highPressureCondensateFlashTank.outletGasEnergyFlow,
        highPressureCondensateFlashTankOutput_outletGasMassFlow: resultData.highPressureCondensateFlashTank.outletGasMassFlow,
        highPressureCondensateFlashTankOutput_outletGasPressure: resultData.highPressureCondensateFlashTank.outletGasPressure,
        highPressureCondensateFlashTankOutput_outletGasQuality: resultData.highPressureCondensateFlashTank.outletGasQuality,
        highPressureCondensateFlashTankOutput_outletGasVolume: resultData.highPressureCondensateFlashTank.outletGasVolume,
        highPressureCondensateFlashTankOutput_outletGasSpecificEnthalpy: resultData.highPressureCondensateFlashTank.outletGasSpecificEnthalpy,
        highPressureCondensateFlashTankOutput_outletGasSpecificEntropy: resultData.highPressureCondensateFlashTank.outletGasSpecificEntropy,
        highPressureCondensateFlashTankOutput_outletGasTemperature: resultData.highPressureCondensateFlashTank.outletGasTemperature,
        highPressureCondensateFlashTankOutput_outletLiquidEnergyFlow: resultData.highPressureCondensateFlashTank.outletLiquidEnergyFlow,
        highPressureCondensateFlashTankOutput_outletLiquidMassFlow: resultData.highPressureCondensateFlashTank.outletLiquidMassFlow,
        highPressureCondensateFlashTankOutput_outletLiquidPressure: resultData.highPressureCondensateFlashTank.outletLiquidPressure,
        highPressureCondensateFlashTankOutput_outletLiquidQuality: resultData.highPressureCondensateFlashTank.outletLiquidQuality,
        highPressureCondensateFlashTankOutput_outletLiquidVolume: resultData.highPressureCondensateFlashTank.outletLiquidVolume,
        highPressureCondensateFlashTankOutput_outletLiquidSpecificEnthalpy: resultData.highPressureCondensateFlashTank.outletLiquidSpecificEnthalpy,
        highPressureCondensateFlashTankOutput_outletLiquidSpecificEntropy: resultData.highPressureCondensateFlashTank.outletLiquidSpecificEntropy,
        highPressureCondensateFlashTankOutput_outletLiquidTemperature: resultData.highPressureCondensateFlashTank.outletLiquidTemperature,

        condensingTurbineOutput_energyOut: resultData.condensingTurbine.energyOut,
        condensingTurbineOutput_generatorEfficiency: resultData.condensingTurbine.generatorEfficiency,
        condensingTurbineOutput_inletEnergyFlow: resultData.condensingTurbine.inletEnergyFlow,
        condensingTurbineOutput_inletPressure: resultData.condensingTurbine.inletPressure,
        condensingTurbineOutput_inletQuality: resultData.condensingTurbine.inletQuality,
        condensingTurbineOutput_inletVolume: resultData.condensingTurbine.inletVolume,
        condensingTurbineOutput_inletSpecificEnthalpy: resultData.condensingTurbine.inletSpecificEnthalpy,
        condensingTurbineOutput_inletSpecificEntropy: resultData.condensingTurbine.inletSpecificEntropy,
        condensingTurbineOutput_inletTemperature: resultData.condensingTurbine.inletTemperature,
        condensingTurbineOutput_isentropicEfficiency: resultData.condensingTurbine.isentropicEfficiency,
        condensingTurbineOutput_massFlow: resultData.condensingTurbine.massFlow,
        condensingTurbineOutput_outletEnergyFlow: resultData.condensingTurbine.outletEnergyFlow,
        condensingTurbineOutput_outletPressure: resultData.condensingTurbine.outletPressure,
        condensingTurbineOutput_outletQuality: resultData.condensingTurbine.outletQuality,
        condensingTurbineOutput_outletVolume: resultData.condensingTurbine.outletVolume,
        condensingTurbineOutput_outletSpecificEnthalpy: resultData.condensingTurbine.outletSpecificEnthalpy,
        condensingTurbineOutput_outletSpecificEntropy: resultData.condensingTurbine.outletSpecificEntropy,
        condensingTurbineOutput_outletTemperature: resultData.condensingTurbine.outletTemperature,
        condensingTurbineOutput_powerOut: resultData.condensingTurbine.powerOut,

        condensingTurbineIdealOutput_energyOut: resultData.condensingTurbineIdeal.energyOut,
        condensingTurbineIdealOutput_generatorEfficiency: resultData.condensingTurbineIdeal.generatorEfficiency,
        condensingTurbineIdealOutput_inletEnergyFlow: resultData.condensingTurbineIdeal.inletEnergyFlow,
        condensingTurbineIdealOutput_inletPressure: resultData.condensingTurbineIdeal.inletPressure,
        condensingTurbineIdealOutput_inletQuality: resultData.condensingTurbineIdeal.inletQuality,
        condensingTurbineIdealOutput_inletVolume: resultData.condensingTurbineIdeal.inletVolume,
        condensingTurbineIdealOutput_inletSpecificEnthalpy: resultData.condensingTurbineIdeal.inletSpecificEnthalpy,
        condensingTurbineIdealOutput_inletSpecificEntropy: resultData.condensingTurbineIdeal.inletSpecificEntropy,
        condensingTurbineIdealOutput_inletTemperature: resultData.condensingTurbineIdeal.inletTemperature,
        condensingTurbineIdealOutput_isentropicEfficiency: resultData.condensingTurbineIdeal.isentropicEfficiency,
        condensingTurbineIdealOutput_massFlow: resultData.condensingTurbineIdeal.massFlow,
        condensingTurbineIdealOutput_outletEnergyFlow: resultData.condensingTurbineIdeal.outletEnergyFlow,
        condensingTurbineIdealOutput_outletPressure: resultData.condensingTurbineIdeal.outletPressure,
        condensingTurbineIdealOutput_outletQuality: resultData.condensingTurbineIdeal.outletQuality,
        condensingTurbineIdealOutput_outletVolume: resultData.condensingTurbineIdeal.outletVolume,
        condensingTurbineIdealOutput_outletSpecificEnthalpy: resultData.condensingTurbineIdeal.outletSpecificEnthalpy,
        condensingTurbineIdealOutput_outletSpecificEntropy: resultData.condensingTurbineIdeal.outletSpecificEntropy,
        condensingTurbineIdealOutput_outletTemperature: resultData.condensingTurbineIdeal.outletTemperature,
        condensingTurbineIdealOutput_powerOut: resultData.condensingTurbineIdeal.powerOut,

        highPressureToLowPressureTurbineOutput_energyOut: resultData.highPressureToLowPressureTurbine.energyOut,
        highPressureToLowPressureTurbineOutput_generatorEfficiency: resultData.highPressureToLowPressureTurbine.generatorEfficiency,
        highPressureToLowPressureTurbineOutput_inletEnergyFlow: resultData.highPressureToLowPressureTurbine.inletEnergyFlow,
        highPressureToLowPressureTurbineOutput_inletPressure: resultData.highPressureToLowPressureTurbine.inletPressure,
        highPressureToLowPressureTurbineOutput_inletQuality: resultData.highPressureToLowPressureTurbine.inletQuality,
        highPressureToLowPressureTurbineOutput_inletVolume: resultData.highPressureToLowPressureTurbine.inletVolume,
        highPressureToLowPressureTurbineOutput_inletSpecificEnthalpy: resultData.highPressureToLowPressureTurbine.inletSpecificEnthalpy,
        highPressureToLowPressureTurbineOutput_inletSpecificEntropy: resultData.highPressureToLowPressureTurbine.inletSpecificEntropy,
        highPressureToLowPressureTurbineOutput_inletTemperature: resultData.highPressureToLowPressureTurbine.inletTemperature,
        highPressureToLowPressureTurbineOutput_isentropicEfficiency: resultData.highPressureToLowPressureTurbine.isentropicEfficiency,
        highPressureToLowPressureTurbineOutput_massFlow: resultData.highPressureToLowPressureTurbine.massFlow,
        highPressureToLowPressureTurbineOutput_outletEnergyFlow: resultData.highPressureToLowPressureTurbine.outletEnergyFlow,
        highPressureToLowPressureTurbineOutput_outletPressure: resultData.highPressureToLowPressureTurbine.outletPressure,
        highPressureToLowPressureTurbineOutput_outletQuality: resultData.highPressureToLowPressureTurbine.outletQuality,
        highPressureToLowPressureTurbineOutput_outletVolume: resultData.highPressureToLowPressureTurbine.outletVolume,
        highPressureToLowPressureTurbineOutput_outletSpecificEnthalpy: resultData.highPressureToLowPressureTurbine.outletSpecificEnthalpy,
        highPressureToLowPressureTurbineOutput_outletSpecificEntropy: resultData.highPressureToLowPressureTurbine.outletSpecificEntropy,
        highPressureToLowPressureTurbineOutput_outletTemperature: resultData.highPressureToLowPressureTurbine.outletTemperature,
        highPressureToLowPressureTurbineOutput_powerOut: resultData.highPressureToLowPressureTurbine.powerOut,

        highPressureToLowPressureTurbineIdealOutput_energyOut: resultData.highPressureToLowPressureTurbineIdeal.energyOut,
        highPressureToLowPressureTurbineIdealOutput_generatorEfficiency: resultData.highPressureToLowPressureTurbineIdeal.generatorEfficiency,
        highPressureToLowPressureTurbineIdealOutput_inletEnergyFlow: resultData.highPressureToLowPressureTurbineIdeal.inletEnergyFlow,
        highPressureToLowPressureTurbineIdealOutput_inletPressure: resultData.highPressureToLowPressureTurbineIdeal.inletPressure,
        highPressureToLowPressureTurbineIdealOutput_inletQuality: resultData.highPressureToLowPressureTurbineIdeal.inletQuality,
        highPressureToLowPressureTurbineIdealOutput_inletVolume: resultData.highPressureToLowPressureTurbineIdeal.inletVolume,
        highPressureToLowPressureTurbineIdealOutput_inletSpecificEnthalpy: resultData.highPressureToLowPressureTurbineIdeal.inletSpecificEnthalpy,
        highPressureToLowPressureTurbineIdealOutput_inletSpecificEntropy: resultData.highPressureToLowPressureTurbineIdeal.inletSpecificEntropy,
        highPressureToLowPressureTurbineIdealOutput_inletTemperature: resultData.highPressureToLowPressureTurbineIdeal.inletTemperature,
        highPressureToLowPressureTurbineIdealOutput_isentropicEfficiency: resultData.highPressureToLowPressureTurbineIdeal.isentropicEfficiency,
        highPressureToLowPressureTurbineIdealOutput_massFlow: resultData.highPressureToLowPressureTurbineIdeal.massFlow,
        highPressureToLowPressureTurbineIdealOutput_outletEnergyFlow: resultData.highPressureToLowPressureTurbineIdeal.outletEnergyFlow,
        highPressureToLowPressureTurbineIdealOutput_outletPressure: resultData.highPressureToLowPressureTurbineIdeal.outletPressure,
        highPressureToLowPressureTurbineIdealOutput_outletQuality: resultData.highPressureToLowPressureTurbineIdeal.outletQuality,
        highPressureToLowPressureTurbineIdealOutput_outletVolume: resultData.highPressureToLowPressureTurbineIdeal.outletVolume,
        highPressureToLowPressureTurbineIdealOutput_outletSpecificEnthalpy: resultData.highPressureToLowPressureTurbineIdeal.outletSpecificEnthalpy,
        highPressureToLowPressureTurbineIdealOutput_outletSpecificEntropy: resultData.highPressureToLowPressureTurbineIdeal.outletSpecificEntropy,
        highPressureToLowPressureTurbineIdealOutput_outletTemperature: resultData.highPressureToLowPressureTurbineIdeal.outletTemperature,
        highPressureToLowPressureTurbineIdealOutput_powerOut: resultData.highPressureToLowPressureTurbineIdeal.powerOut,

        highPressureToMediumPressureTurbineOutput_energyOut: resultData.highPressureToMediumPressureTurbine.energyOut,
        highPressureToMediumPressureTurbineOutput_generatorEfficiency: resultData.highPressureToMediumPressureTurbine.generatorEfficiency,
        highPressureToMediumPressureTurbineOutput_inletEnergyFlow: resultData.highPressureToMediumPressureTurbine.inletEnergyFlow,
        highPressureToMediumPressureTurbineOutput_inletPressure: resultData.highPressureToMediumPressureTurbine.inletPressure,
        highPressureToMediumPressureTurbineOutput_inletQuality: resultData.highPressureToMediumPressureTurbine.inletQuality,
        highPressureToMediumPressureTurbineOutput_inletVolume: resultData.highPressureToMediumPressureTurbine.inletVolume,
        highPressureToMediumPressureTurbineOutput_inletSpecificEnthalpy: resultData.highPressureToMediumPressureTurbine.inletSpecificEnthalpy,
        highPressureToMediumPressureTurbineOutput_inletSpecificEntropy: resultData.highPressureToMediumPressureTurbine.inletSpecificEntropy,
        highPressureToMediumPressureTurbineOutput_inletTemperature: resultData.highPressureToMediumPressureTurbine.inletTemperature,
        highPressureToMediumPressureTurbineOutput_isentropicEfficiency: resultData.highPressureToMediumPressureTurbine.isentropicEfficiency,
        highPressureToMediumPressureTurbineOutput_massFlow: resultData.highPressureToMediumPressureTurbine.massFlow,
        highPressureToMediumPressureTurbineOutput_outletEnergyFlow: resultData.highPressureToMediumPressureTurbine.outletEnergyFlow,
        highPressureToMediumPressureTurbineOutput_outletPressure: resultData.highPressureToMediumPressureTurbine.outletPressure,
        highPressureToMediumPressureTurbineOutput_outletQuality: resultData.highPressureToMediumPressureTurbine.outletQuality,
        highPressureToMediumPressureTurbineOutput_outletVolume: resultData.highPressureToMediumPressureTurbine.outletVolume,
        highPressureToMediumPressureTurbineOutput_outletSpecificEnthalpy: resultData.highPressureToMediumPressureTurbine.outletSpecificEnthalpy,
        highPressureToMediumPressureTurbineOutput_outletSpecificEntropy: resultData.highPressureToMediumPressureTurbine.outletSpecificEntropy,
        highPressureToMediumPressureTurbineOutput_outletTemperature: resultData.highPressureToMediumPressureTurbine.outletTemperature,
        highPressureToMediumPressureTurbineOutput_powerOut: resultData.highPressureToMediumPressureTurbine.powerOut,

        highPressureToMediumPressureTurbineIdealOutput_energyOut: resultData.highPressureToMediumPressureTurbineIdeal.energyOut,
        highPressureToMediumPressureTurbineIdealOutput_generatorEfficiency: resultData.highPressureToMediumPressureTurbineIdeal.generatorEfficiency,
        highPressureToMediumPressureTurbineIdealOutput_inletEnergyFlow: resultData.highPressureToMediumPressureTurbineIdeal.inletEnergyFlow,
        highPressureToMediumPressureTurbineIdealOutput_inletPressure: resultData.highPressureToMediumPressureTurbineIdeal.inletPressure,
        highPressureToMediumPressureTurbineIdealOutput_inletQuality: resultData.highPressureToMediumPressureTurbineIdeal.inletQuality,
        highPressureToMediumPressureTurbineIdealOutput_inletVolume: resultData.highPressureToMediumPressureTurbineIdeal.inletVolume,
        highPressureToMediumPressureTurbineIdealOutput_inletSpecificEnthalpy: resultData.highPressureToMediumPressureTurbineIdeal.inletSpecificEnthalpy,
        highPressureToMediumPressureTurbineIdealOutput_inletSpecificEntropy: resultData.highPressureToMediumPressureTurbineIdeal.inletSpecificEntropy,
        highPressureToMediumPressureTurbineIdealOutput_inletTemperature: resultData.highPressureToMediumPressureTurbineIdeal.inletTemperature,
        highPressureToMediumPressureTurbineIdealOutput_isentropicEfficiency: resultData.highPressureToMediumPressureTurbineIdeal.isentropicEfficiency,
        highPressureToMediumPressureTurbineIdealOutput_massFlow: resultData.highPressureToMediumPressureTurbineIdeal.massFlow,
        highPressureToMediumPressureTurbineIdealOutput_outletEnergyFlow: resultData.highPressureToMediumPressureTurbineIdeal.outletEnergyFlow,
        highPressureToMediumPressureTurbineIdealOutput_outletPressure: resultData.highPressureToMediumPressureTurbineIdeal.outletPressure,
        highPressureToMediumPressureTurbineIdealOutput_outletQuality: resultData.highPressureToMediumPressureTurbineIdeal.outletQuality,
        highPressureToMediumPressureTurbineIdealOutput_outletVolume: resultData.highPressureToMediumPressureTurbineIdeal.outletVolume,
        highPressureToMediumPressureTurbineIdealOutput_outletSpecificEnthalpy: resultData.highPressureToMediumPressureTurbineIdeal.outletSpecificEnthalpy,
        highPressureToMediumPressureTurbineIdealOutput_outletSpecificEntropy: resultData.highPressureToMediumPressureTurbineIdeal.outletSpecificEntropy,
        highPressureToMediumPressureTurbineIdealOutput_outletTemperature: resultData.highPressureToMediumPressureTurbineIdeal.outletTemperature,
        highPressureToMediumPressureTurbineIdealOutput_powerOut: resultData.highPressureToMediumPressureTurbineIdeal.powerOut,

        highPressureToMediumPressurePrvOutput_feedwaterEnergyFlow: resultData.highPressureToMediumPressurePrv.feedwaterEnergyFlow,
        highPressureToMediumPressurePrvOutput_feedwaterMassFlow: resultData.highPressureToMediumPressurePrv.feedwaterMassFlow,
        highPressureToMediumPressurePrvOutput_feedwaterPressure: resultData.highPressureToMediumPressurePrv.feedwaterPressure,
        highPressureToMediumPressurePrvOutput_feedwaterQuality: resultData.highPressureToMediumPressurePrv.feedwaterQuality,
        highPressureToMediumPressurePrvOutput_feedwaterVolume: resultData.highPressureToMediumPressurePrv.feedwaterVolume,
        highPressureToMediumPressurePrvOutput_feedwaterSpecificEnthalpy: resultData.highPressureToMediumPressurePrv.feedwaterSpecificEnthalpy,
        highPressureToMediumPressurePrvOutput_feedwaterSpecificEntropy: resultData.highPressureToMediumPressurePrv.feedwaterSpecificEntropy,
        highPressureToMediumPressurePrvOutput_feedwaterTemperature: resultData.highPressureToMediumPressurePrv.feedwaterTemperature,
        highPressureToMediumPressurePrvOutput_inletEnergyFlow: resultData.highPressureToMediumPressurePrv.inletEnergyFlow,
        highPressureToMediumPressurePrvOutput_inletMassFlow: resultData.highPressureToMediumPressurePrv.inletMassFlow,
        highPressureToMediumPressurePrvOutput_inletPressure: resultData.highPressureToMediumPressurePrv.inletPressure,
        highPressureToMediumPressurePrvOutput_inletQuality: resultData.highPressureToMediumPressurePrv.inletQuality,
        highPressureToMediumPressurePrvOutput_inletVolume: resultData.highPressureToMediumPressurePrv.inletVolume,
        highPressureToMediumPressurePrvOutput_inletSpecificEnthalpy: resultData.highPressureToMediumPressurePrv.inletSpecificEnthalpy,
        highPressureToMediumPressurePrvOutput_inletSpecificEntropy: resultData.highPressureToMediumPressurePrv.inletSpecificEntropy,
        highPressureToMediumPressurePrvOutput_inletTemperature: resultData.highPressureToMediumPressurePrv.inletTemperature,
        highPressureToMediumPressurePrvOutput_outletEnergyFlow: resultData.highPressureToMediumPressurePrv.outletEnergyFlow,
        highPressureToMediumPressurePrvOutput_outletMassFlow: resultData.highPressureToMediumPressurePrv.outletMassFlow,
        highPressureToMediumPressurePrvOutput_outletPressure: resultData.highPressureToMediumPressurePrv.outletPressure,
        highPressureToMediumPressurePrvOutput_outletQuality: resultData.highPressureToMediumPressurePrv.outletQuality,
        highPressureToMediumPressurePrvOutput_outletVolume: resultData.highPressureToMediumPressurePrv.outletVolume,
        highPressureToMediumPressurePrvOutput_outletSpecificEnthalpy: resultData.highPressureToMediumPressurePrv.outletSpecificEnthalpy,
        highPressureToMediumPressurePrvOutput_outletSpecificEntropy: resultData.highPressureToMediumPressurePrv.outletSpecificEntropy,
        highPressureToMediumPressurePrvOutput_outletTemperature: resultData.highPressureToMediumPressurePrv.outletTemperature,

        mediumPressureHeaderSteamOutput_pressure: resultData.mediumPressureHeaderSteam.pressure,
        mediumPressureHeaderSteamOutput_temperature: resultData.mediumPressureHeaderSteam.temperature,
        mediumPressureHeaderSteamOutput_specificEnthalpy: resultData.mediumPressureHeaderSteam.specificEnthalpy,
        mediumPressureHeaderSteamOutput_specificEntropy: resultData.mediumPressureHeaderSteam.specificEntropy,
        mediumPressureHeaderSteamOutput_quality: resultData.mediumPressureHeaderSteam.quality,
        mediumPressureHeaderSteamOutput_specificVolume: resultData.mediumPressureHeaderSteam.specificVolume,
        mediumPressureHeaderSteamOutput_massFlow: resultData.mediumPressureHeaderSteam.massFlow,
        mediumPressureHeaderSteamOutput_energyFlow: resultData.mediumPressureHeaderSteam.energyFlow,

        mediumPressureSteamHeatLossOutput_heatLoss: resultData.mediumPressureSteamHeatLoss.heatLoss,
        mediumPressureSteamHeatLossOutput_inletPressure: resultData.mediumPressureSteamHeatLoss.inletPressure,
        mediumPressureSteamHeatLossOutput_inletTemperature: resultData.mediumPressureSteamHeatLoss.inletTemperature,
        mediumPressureSteamHeatLossOutput_inletSpecificEnthalpy: resultData.mediumPressureSteamHeatLoss.inletSpecificEnthalpy,
        mediumPressureSteamHeatLossOutput_inletSpecificEntropy: resultData.mediumPressureSteamHeatLoss.inletSpecificEntropy,
        mediumPressureSteamHeatLossOutput_inletQuality: resultData.mediumPressureSteamHeatLoss.inletQuality,
        mediumPressureSteamHeatLossOutput_inletSpecificVolume: resultData.mediumPressureSteamHeatLoss.inletVolume,
        mediumPressureSteamHeatLossOutput_inletMassFlow: resultData.mediumPressureSteamHeatLoss.inletMassFlow,
        mediumPressureSteamHeatLossOutput_inletEnergyFlow: resultData.mediumPressureSteamHeatLoss.inletEnergyFlow,
        mediumPressureSteamHeatLossOutput_outletPressure: resultData.mediumPressureSteamHeatLoss.outletPressure,
        mediumPressureSteamHeatLossOutput_outletTemperature: resultData.mediumPressureSteamHeatLoss.outletTemperature,
        mediumPressureSteamHeatLossOutput_outletSpecificEnthalpy: resultData.mediumPressureSteamHeatLoss.outletSpecificEnthalpy,
        mediumPressureSteamHeatLossOutput_outletSpecificEntropy: resultData.mediumPressureSteamHeatLoss.outletSpecificEntropy,
        mediumPressureSteamHeatLossOutput_outletQuality: resultData.mediumPressureSteamHeatLoss.outletQuality,
        mediumPressureSteamHeatLossOutput_outletSpecificVolume: resultData.mediumPressureSteamHeatLoss.outletVolume,
        mediumPressureSteamHeatLossOutput_outletMassFlow: resultData.mediumPressureSteamHeatLoss.outletMassFlow,
        mediumPressureSteamHeatLossOutput_outletEnergyFlow: resultData.mediumPressureSteamHeatLoss.outletEnergyFlow,

        mediumPressureCondensateOutput_pressure: resultData.mediumPressureCondensate.pressure,
        mediumPressureCondensateOutput_temperature: resultData.mediumPressureCondensate.temperature,
        mediumPressureCondensateOutput_specificEnthalpy: resultData.mediumPressureCondensate.specificEnthalpy,
        mediumPressureCondensateOutput_specificEntropy: resultData.mediumPressureCondensate.specificEntropy,
        mediumPressureCondensateOutput_quality: resultData.mediumPressureCondensate.quality,
        mediumPressureCondensateOutput_specificVolume: resultData.mediumPressureCondensate.specificVolume,
        mediumPressureCondensateOutput_massFlow: resultData.mediumPressureCondensate.massFlow,
        mediumPressureCondensateOutput_energyFlow: resultData.mediumPressureCondensate.energyFlow,

        mediumPressureCondensateFlashTankOutput_inletWaterEnergyFlow: resultData.mediumPressureCondensateFlashTank.inletWaterEnergyFlow,
        mediumPressureCondensateFlashTankOutput_inletWaterMassFlow: resultData.mediumPressureCondensateFlashTank.inletWaterMassFlow,
        mediumPressureCondensateFlashTankOutput_inletWaterPressure: resultData.mediumPressureCondensateFlashTank.inletWaterPressure,
        mediumPressureCondensateFlashTankOutput_inletWaterQuality: resultData.mediumPressureCondensateFlashTank.inletWaterQuality,
        mediumPressureCondensateFlashTankOutput_inletWaterVolume: resultData.mediumPressureCondensateFlashTank.inletWaterVolume,
        mediumPressureCondensateFlashTankOutput_inletWaterSpecificEnthalpy: resultData.mediumPressureCondensateFlashTank.inletWaterSpecificEnthalpy,
        mediumPressureCondensateFlashTankOutput_inletWaterSpecificEntropy: resultData.mediumPressureCondensateFlashTank.inletWaterSpecificEntropy,
        mediumPressureCondensateFlashTankOutput_inletWaterTemperature: resultData.mediumPressureCondensateFlashTank.inletWaterTemperature,
        mediumPressureCondensateFlashTankOutput_outletGasEnergyFlow: resultData.mediumPressureCondensateFlashTank.outletGasEnergyFlow,
        mediumPressureCondensateFlashTankOutput_outletGasMassFlow: resultData.mediumPressureCondensateFlashTank.outletGasMassFlow,
        mediumPressureCondensateFlashTankOutput_outletGasPressure: resultData.mediumPressureCondensateFlashTank.outletGasPressure,
        mediumPressureCondensateFlashTankOutput_outletGasQuality: resultData.mediumPressureCondensateFlashTank.outletGasQuality,
        mediumPressureCondensateFlashTankOutput_outletGasVolume: resultData.mediumPressureCondensateFlashTank.outletGasVolume,
        mediumPressureCondensateFlashTankOutput_outletGasSpecificEnthalpy: resultData.mediumPressureCondensateFlashTank.outletGasSpecificEnthalpy,
        mediumPressureCondensateFlashTankOutput_outletGasSpecificEntropy: resultData.mediumPressureCondensateFlashTank.outletGasSpecificEntropy,
        mediumPressureCondensateFlashTankOutput_outletGasTemperature: resultData.mediumPressureCondensateFlashTank.outletGasTemperature,
        mediumPressureCondensateFlashTankOutput_outletLiquidEnergyFlow: resultData.mediumPressureCondensateFlashTank.outletLiquidEnergyFlow,
        mediumPressureCondensateFlashTankOutput_outletLiquidMassFlow: resultData.mediumPressureCondensateFlashTank.outletLiquidMassFlow,
        mediumPressureCondensateFlashTankOutput_outletLiquidPressure: resultData.mediumPressureCondensateFlashTank.outletLiquidPressure,
        mediumPressureCondensateFlashTankOutput_outletLiquidQuality: resultData.mediumPressureCondensateFlashTank.outletLiquidQuality,
        mediumPressureCondensateFlashTankOutput_outletLiquidVolume: resultData.mediumPressureCondensateFlashTank.outletLiquidVolume,
        mediumPressureCondensateFlashTankOutput_outletLiquidSpecificEnthalpy: resultData.mediumPressureCondensateFlashTank.outletLiquidSpecificEnthalpy,
        mediumPressureCondensateFlashTankOutput_outletLiquidSpecificEntropy: resultData.mediumPressureCondensateFlashTank.outletLiquidSpecificEntropy,
        mediumPressureCondensateFlashTankOutput_outletLiquidTemperature: resultData.mediumPressureCondensateFlashTank.outletLiquidTemperature,

        mediumPressureToLowPressureTurbineOutput_energyOut: resultData.mediumPressureToLowPressureTurbine.energyOut,
        mediumPressureToLowPressureTurbineOutput_generatorEfficiency: resultData.mediumPressureToLowPressureTurbine.generatorEfficiency,
        mediumPressureToLowPressureTurbineOutput_inletEnergyFlow: resultData.mediumPressureToLowPressureTurbine.inletEnergyFlow,
        mediumPressureToLowPressureTurbineOutput_inletPressure: resultData.mediumPressureToLowPressureTurbine.inletPressure,
        mediumPressureToLowPressureTurbineOutput_inletQuality: resultData.mediumPressureToLowPressureTurbine.inletQuality,
        mediumPressureToLowPressureTurbineOutput_inletVolume: resultData.mediumPressureToLowPressureTurbine.inletVolume,
        mediumPressureToLowPressureTurbineOutput_inletSpecificEnthalpy: resultData.mediumPressureToLowPressureTurbine.inletSpecificEnthalpy,
        mediumPressureToLowPressureTurbineOutput_inletSpecificEntropy: resultData.mediumPressureToLowPressureTurbine.inletSpecificEntropy,
        mediumPressureToLowPressureTurbineOutput_inletTemperature: resultData.mediumPressureToLowPressureTurbine.inletTemperature,
        mediumPressureToLowPressureTurbineOutput_isentropicEfficiency: resultData.mediumPressureToLowPressureTurbine.isentropicEfficiency,
        mediumPressureToLowPressureTurbineOutput_massFlow: resultData.mediumPressureToLowPressureTurbine.massFlow,
        mediumPressureToLowPressureTurbineOutput_outletEnergyFlow: resultData.mediumPressureToLowPressureTurbine.outletEnergyFlow,
        mediumPressureToLowPressureTurbineOutput_outletPressure: resultData.mediumPressureToLowPressureTurbine.outletPressure,
        mediumPressureToLowPressureTurbineOutput_outletQuality: resultData.mediumPressureToLowPressureTurbine.outletQuality,
        mediumPressureToLowPressureTurbineOutput_outletVolume: resultData.mediumPressureToLowPressureTurbine.outletVolume,
        mediumPressureToLowPressureTurbineOutput_outletSpecificEnthalpy: resultData.mediumPressureToLowPressureTurbine.outletSpecificEnthalpy,
        mediumPressureToLowPressureTurbineOutput_outletSpecificEntropy: resultData.mediumPressureToLowPressureTurbine.outletSpecificEntropy,
        mediumPressureToLowPressureTurbineOutput_outletTemperature: resultData.mediumPressureToLowPressureTurbine.outletTemperature,
        mediumPressureToLowPressureTurbineOutput_powerOut: resultData.mediumPressureToLowPressureTurbine.powerOut,

        mediumPressureToLowPressureTurbineIdealOutput_energyOut: resultData.mediumPressureToLowPressureTurbineIdeal.energyOut,
        mediumPressureToLowPressureTurbineIdealOutput_generatorEfficiency: resultData.mediumPressureToLowPressureTurbineIdeal.generatorEfficiency,
        mediumPressureToLowPressureTurbineIdealOutput_inletEnergyFlow: resultData.mediumPressureToLowPressureTurbineIdeal.inletEnergyFlow,
        mediumPressureToLowPressureTurbineIdealOutput_inletPressure: resultData.mediumPressureToLowPressureTurbineIdeal.inletPressure,
        mediumPressureToLowPressureTurbineIdealOutput_inletQuality: resultData.mediumPressureToLowPressureTurbineIdeal.inletQuality,
        mediumPressureToLowPressureTurbineIdealOutput_inletVolume: resultData.mediumPressureToLowPressureTurbineIdeal.inletVolume,
        mediumPressureToLowPressureTurbineIdealOutput_inletSpecificEnthalpy: resultData.mediumPressureToLowPressureTurbineIdeal.inletSpecificEnthalpy,
        mediumPressureToLowPressureTurbineIdealOutput_inletSpecificEntropy: resultData.mediumPressureToLowPressureTurbineIdeal.inletSpecificEntropy,
        mediumPressureToLowPressureTurbineIdealOutput_inletTemperature: resultData.mediumPressureToLowPressureTurbineIdeal.inletTemperature,
        mediumPressureToLowPressureTurbineIdealOutput_isentropicEfficiency: resultData.mediumPressureToLowPressureTurbineIdeal.isentropicEfficiency,
        mediumPressureToLowPressureTurbineIdealOutput_massFlow: resultData.mediumPressureToLowPressureTurbineIdeal.massFlow,
        mediumPressureToLowPressureTurbineIdealOutput_outletEnergyFlow: resultData.mediumPressureToLowPressureTurbineIdeal.outletEnergyFlow,
        mediumPressureToLowPressureTurbineIdealOutput_outletPressure: resultData.mediumPressureToLowPressureTurbineIdeal.outletPressure,
        mediumPressureToLowPressureTurbineIdealOutput_outletQuality: resultData.mediumPressureToLowPressureTurbineIdeal.outletQuality,
        mediumPressureToLowPressureTurbineIdealOutput_outletVolume: resultData.mediumPressureToLowPressureTurbineIdeal.outletVolume,
        mediumPressureToLowPressureTurbineIdealOutput_outletSpecificEnthalpy: resultData.mediumPressureToLowPressureTurbineIdeal.outletSpecificEnthalpy,
        mediumPressureToLowPressureTurbineIdealOutput_outletSpecificEntropy: resultData.mediumPressureToLowPressureTurbineIdeal.outletSpecificEntropy,
        mediumPressureToLowPressureTurbineIdealOutput_outletTemperature: resultData.mediumPressureToLowPressureTurbineIdeal.outletTemperature,
        mediumPressureToLowPressureTurbineIdealOutput_powerOut: resultData.mediumPressureToLowPressureTurbineIdeal.powerOut,

        mediumPressureToLowPressurePrvOutput_feedwaterEnergyFlow: resultData.mediumPressureToLowPressurePrv.feedwaterEnergyFlow,
        mediumPressureToLowPressurePrvOutput_feedwaterMassFlow: resultData.mediumPressureToLowPressurePrv.feedwaterMassFlow,
        mediumPressureToLowPressurePrvOutput_feedwaterPressure: resultData.mediumPressureToLowPressurePrv.feedwaterPressure,
        mediumPressureToLowPressurePrvOutput_feedwaterQuality: resultData.mediumPressureToLowPressurePrv.feedwaterQuality,
        mediumPressureToLowPressurePrvOutput_feedwaterVolume: resultData.mediumPressureToLowPressurePrv.feedwaterVolume,
        mediumPressureToLowPressurePrvOutput_feedwaterSpecificEnthalpy: resultData.mediumPressureToLowPressurePrv.feedwaterSpecificEnthalpy,
        mediumPressureToLowPressurePrvOutput_feedwaterSpecificEntropy: resultData.mediumPressureToLowPressurePrv.feedwaterSpecificEntropy,
        mediumPressureToLowPressurePrvOutput_feedwaterTemperature: resultData.mediumPressureToLowPressurePrv.feedwaterTemperature,
        mediumPressureToLowPressurePrvOutput_inletEnergyFlow: resultData.mediumPressureToLowPressurePrv.inletEnergyFlow,
        mediumPressureToLowPressurePrvOutput_inletMassFlow: resultData.mediumPressureToLowPressurePrv.inletMassFlow,
        mediumPressureToLowPressurePrvOutput_inletPressure: resultData.mediumPressureToLowPressurePrv.inletPressure,
        mediumPressureToLowPressurePrvOutput_inletQuality: resultData.mediumPressureToLowPressurePrv.inletQuality,
        mediumPressureToLowPressurePrvOutput_inletVolume: resultData.mediumPressureToLowPressurePrv.inletVolume,
        mediumPressureToLowPressurePrvOutput_inletSpecificEnthalpy: resultData.mediumPressureToLowPressurePrv.inletSpecificEnthalpy,
        mediumPressureToLowPressurePrvOutput_inletSpecificEntropy: resultData.mediumPressureToLowPressurePrv.inletSpecificEntropy,
        mediumPressureToLowPressurePrvOutput_inletTemperature: resultData.mediumPressureToLowPressurePrv.inletTemperature,
        mediumPressureToLowPressurePrvOutput_outletEnergyFlow: resultData.mediumPressureToLowPressurePrv.outletEnergyFlow,
        mediumPressureToLowPressurePrvOutput_outletMassFlow: resultData.mediumPressureToLowPressurePrv.outletMassFlow,
        mediumPressureToLowPressurePrvOutput_outletPressure: resultData.mediumPressureToLowPressurePrv.outletPressure,
        mediumPressureToLowPressurePrvOutput_outletQuality: resultData.mediumPressureToLowPressurePrv.outletQuality,
        mediumPressureToLowPressurePrvOutput_outletVolume: resultData.mediumPressureToLowPressurePrv.outletVolume,
        mediumPressureToLowPressurePrvOutput_outletSpecificEnthalpy: resultData.mediumPressureToLowPressurePrv.outletSpecificEnthalpy,
        mediumPressureToLowPressurePrvOutput_outletSpecificEntropy: resultData.mediumPressureToLowPressurePrv.outletSpecificEntropy,
        mediumPressureToLowPressurePrvOutput_outletTemperature: resultData.mediumPressureToLowPressurePrv.outletTemperature,

        lowPressureHeaderSteamOutput_pressure: resultData.lowPressureHeaderSteam.pressure,
        lowPressureHeaderSteamOutput_temperature: resultData.lowPressureHeaderSteam.temperature,
        lowPressureHeaderSteamOutput_specificEnthalpy: resultData.lowPressureHeaderSteam.specificEnthalpy,
        lowPressureHeaderSteamOutput_specificEntropy: resultData.lowPressureHeaderSteam.specificEntropy,
        lowPressureHeaderSteamOutput_quality: resultData.lowPressureHeaderSteam.quality,
        lowPressureHeaderSteamOutput_specificVolume: resultData.lowPressureHeaderSteam.specificVolume,
        lowPressureHeaderSteamOutput_massFlow: resultData.lowPressureHeaderSteam.massFlow,
        lowPressureHeaderSteamOutput_energyFlow: resultData.lowPressureHeaderSteam.energyFlow,

        lowPressureSteamHeatLossOutput_heatLoss: resultData.lowPressureSteamHeatLoss.heatLoss,
        lowPressureSteamHeatLossOutput_inletPressure: resultData.lowPressureSteamHeatLoss.inletPressure,
        lowPressureSteamHeatLossOutput_inletTemperature: resultData.lowPressureSteamHeatLoss.inletTemperature,
        lowPressureSteamHeatLossOutput_inletSpecificEnthalpy: resultData.lowPressureSteamHeatLoss.inletSpecificEnthalpy,
        lowPressureSteamHeatLossOutput_inletSpecificEntropy: resultData.lowPressureSteamHeatLoss.inletSpecificEntropy,
        lowPressureSteamHeatLossOutput_inletQuality: resultData.lowPressureSteamHeatLoss.inletQuality,
        lowPressureSteamHeatLossOutput_inletSpecificVolume: resultData.lowPressureSteamHeatLoss.inletVolume,
        lowPressureSteamHeatLossOutput_inletMassFlow: resultData.lowPressureSteamHeatLoss.inletMassFlow,
        lowPressureSteamHeatLossOutput_inletEnergyFlow: resultData.lowPressureSteamHeatLoss.inletEnergyFlow,
        lowPressureSteamHeatLossOutput_outletPressure: resultData.lowPressureSteamHeatLoss.outletPressure,
        lowPressureSteamHeatLossOutput_outletTemperature: resultData.lowPressureSteamHeatLoss.outletTemperature,
        lowPressureSteamHeatLossOutput_outletSpecificEnthalpy: resultData.lowPressureSteamHeatLoss.outletSpecificEnthalpy,
        lowPressureSteamHeatLossOutput_outletSpecificEntropy: resultData.lowPressureSteamHeatLoss.outletSpecificEntropy,
        lowPressureSteamHeatLossOutput_outletQuality: resultData.lowPressureSteamHeatLoss.outletQuality,
        lowPressureSteamHeatLossOutput_outletSpecificVolume: resultData.lowPressureSteamHeatLoss.outletVolume,
        lowPressureSteamHeatLossOutput_outletMassFlow: resultData.lowPressureSteamHeatLoss.outletMassFlow,
        lowPressureSteamHeatLossOutput_outletEnergyFlow: resultData.lowPressureSteamHeatLoss.outletEnergyFlow,

        lowPressureCondensateOutput_pressure: resultData.lowPressureCondensate.pressure,
        lowPressureCondensateOutput_temperature: resultData.lowPressureCondensate.temperature,
        lowPressureCondensateOutput_specificEnthalpy: resultData.lowPressureCondensate.specificEnthalpy,
        lowPressureCondensateOutput_specificEntropy: resultData.lowPressureCondensate.specificEntropy,
        lowPressureCondensateOutput_quality: resultData.lowPressureCondensate.quality,
        lowPressureCondensateOutput_specificVolume: resultData.lowPressureCondensate.specificVolume,
        lowPressureCondensateOutput_massFlow: resultData.lowPressureCondensate.massFlow,
        lowPressureCondensateOutput_energyFlow: resultData.lowPressureCondensate.energyFlow,

        condensateFlashTankOutput_inletWaterEnergyFlow: resultData.condensateFlashTank.inletWaterEnergyFlow,
        condensateFlashTankOutput_inletWaterMassFlow: resultData.condensateFlashTank.inletWaterMassFlow,
        condensateFlashTankOutput_inletWaterPressure: resultData.condensateFlashTank.inletWaterPressure,
        condensateFlashTankOutput_inletWaterQuality: resultData.condensateFlashTank.inletWaterQuality,
        condensateFlashTankOutput_inletWaterVolume: resultData.condensateFlashTank.inletWaterVolume,
        condensateFlashTankOutput_inletWaterSpecificEnthalpy: resultData.condensateFlashTank.inletWaterSpecificEnthalpy,
        condensateFlashTankOutput_inletWaterSpecificEntropy: resultData.condensateFlashTank.inletWaterSpecificEntropy,
        condensateFlashTankOutput_inletWaterTemperature: resultData.condensateFlashTank.inletWaterTemperature,
        condensateFlashTankOutput_outletGasEnergyFlow: resultData.condensateFlashTank.outletGasEnergyFlow,
        condensateFlashTankOutput_outletGasMassFlow: resultData.condensateFlashTank.outletGasMassFlow,
        condensateFlashTankOutput_outletGasPressure: resultData.condensateFlashTank.outletGasPressure,
        condensateFlashTankOutput_outletGasQuality: resultData.condensateFlashTank.outletGasQuality,
        condensateFlashTankOutput_outletGasVolume: resultData.condensateFlashTank.outletGasVolume,
        condensateFlashTankOutput_outletGasSpecificEnthalpy: resultData.condensateFlashTank.outletGasSpecificEnthalpy,
        condensateFlashTankOutput_outletGasSpecificEntropy: resultData.condensateFlashTank.outletGasSpecificEntropy,
        condensateFlashTankOutput_outletGasTemperature: resultData.condensateFlashTank.outletGasTemperature,
        condensateFlashTankOutput_outletLiquidEnergyFlow: resultData.condensateFlashTank.outletLiquidEnergyFlow,
        condensateFlashTankOutput_outletLiquidMassFlow: resultData.condensateFlashTank.outletLiquidMassFlow,
        condensateFlashTankOutput_outletLiquidPressure: resultData.condensateFlashTank.outletLiquidPressure,
        condensateFlashTankOutput_outletLiquidQuality: resultData.condensateFlashTank.outletLiquidQuality,
        condensateFlashTankOutput_outletLiquidVolume: resultData.condensateFlashTank.outletLiquidVolume,
        condensateFlashTankOutput_outletLiquidSpecificEnthalpy: resultData.condensateFlashTank.outletLiquidSpecificEnthalpy,
        condensateFlashTankOutput_outletLiquidSpecificEntropy: resultData.condensateFlashTank.outletLiquidSpecificEntropy,
        condensateFlashTankOutput_outletLiquidTemperature: resultData.condensateFlashTank.outletLiquidTemperature,

        makeupWaterOutput_pressure: resultData.makeupWater.pressure,
        makeupWaterOutput_temperature: resultData.makeupWater.temperature,
        makeupWaterOutput_specificEnthalpy: resultData.makeupWater.specificEnthalpy,
        makeupWaterOutput_specificEntropy: resultData.makeupWater.specificEntropy,
        makeupWaterOutput_quality: resultData.makeupWater.quality,
        makeupWaterOutput_specificVolume: resultData.makeupWater.specificVolume,
        makeupWaterOutput_massFlow: resultData.makeupWater.massFlow,
        makeupWaterOutput_energyFlow: resultData.makeupWater.energyFlow,

        heatExchangerColdOutletOutput_pressure: resultData.heatExchanger.coldOutletPressure,
        heatExchangerColdOutletOutput_temperature: resultData.heatExchanger.coldOutletTemperature,
        heatExchangerColdOutletOutput_specificEnthalpy: resultData.heatExchanger.coldOutletSpecificEnthalpy,
        heatExchangerColdOutletOutput_specificEntropy: resultData.heatExchanger.coldOutletSpecificEntropy,
        heatExchangerColdOutletOutput_quality: resultData.heatExchanger.coldOutletQuality,
        heatExchangerColdOutletOutput_specificVolume: resultData.heatExchanger.coldOutletVolume,
        heatExchangerColdOutletOutput_massFlow: resultData.heatExchanger.coldOutletMassFlow,
        heatExchangerColdOutletOutput_energyFlow: resultData.heatExchanger.coldOutletEnergyFlow,

        heatExchangerHotOutletOutput_pressure: resultData.heatExchanger.hotOutletPressure,
        heatExchangerHotOutletOutput_temperature: resultData.heatExchanger.hotOutletTemperature,
        heatExchangerHotOutletOutput_specificEnthalpy: resultData.heatExchanger.hotOutletSpecificEnthalpy,
        heatExchangerHotOutletOutput_specificEntropy: resultData.heatExchanger.hotOutletSpecificEntropy,
        heatExchangerHotOutletOutput_quality: resultData.heatExchanger.hotOutletQuality,
        heatExchangerHotOutletOutput_specificVolume: resultData.heatExchanger.hotOutletVolume,
        heatExchangerHotOutletOutput_massFlow: resultData.heatExchanger.hotOutletMassFlow,
        heatExchangerHotOutletOutput_energyFlow: resultData.heatExchanger.hotOutletEnergyFlow,

        makeupWaterAndCondensateOutput_pressure: resultData.makeupWaterAndCondensate.pressure,
        makeupWaterAndCondensateOutput_temperature: resultData.makeupWaterAndCondensate.temperature,
        makeupWaterAndCondensateOutput_specificEnthalpy: resultData.makeupWaterAndCondensate.specificEnthalpy,
        makeupWaterAndCondensateOutput_specificEntropy: resultData.makeupWaterAndCondensate.specificEntropy,
        makeupWaterAndCondensateOutput_quality: resultData.makeupWaterAndCondensate.quality,
        makeupWaterAndCondensateOutput_specificVolume: resultData.makeupWaterAndCondensate.specificVolume,
        makeupWaterAndCondensateOutput_massFlow: resultData.makeupWaterAndCondensate.massFlow,
        makeupWaterAndCondensateOutput_energyFlow: resultData.makeupWaterAndCondensate.energyFlow,

        deaeratorOutput_feedwaterEnergyFlow: resultData.deaeratorOutput.feedwaterEnergyFlow,
        deaeratorOutput_feedwaterMassFlow: resultData.deaeratorOutput.feedwaterMassFlow,
        deaeratorOutput_feedwaterPressure: resultData.deaeratorOutput.feedwaterPressure,
        deaeratorOutput_feedwaterQuality: resultData.deaeratorOutput.feedwaterQuality,
        deaeratorOutput_feedwaterSpecificEnthalpy: resultData.deaeratorOutput.feedwaterSpecificEnthalpy,
        deaeratorOutput_feedwaterSpecificEntropy: resultData.deaeratorOutput.feedwaterSpecificEntropy,
        deaeratorOutput_feedwaterVolume: resultData.deaeratorOutput.feedwaterVolume,
        deaeratorOutput_feedwaterTemperature: resultData.deaeratorOutput.feedwaterTemperature,
        deaeratorOutput_inletSteamEnergyFlow: resultData.deaeratorOutput.inletSteamEnergyFlow,
        deaeratorOutput_inletSteamMassFlow: resultData.deaeratorOutput.inletSteamMassFlow,
        deaeratorOutput_inletSteamPressure: resultData.deaeratorOutput.inletSteamPressure,
        deaeratorOutput_inletSteamQuality: resultData.deaeratorOutput.inletSteamQuality,
        deaeratorOutput_inletSteamSpecificEnthalpy: resultData.deaeratorOutput.inletSteamSpecificEnthalpy,
        deaeratorOutput_inletSteamSpecificEntropy: resultData.deaeratorOutput.inletSteamSpecificEntropy,
        deaeratorOutput_inletSteamVolume: resultData.deaeratorOutput.inletSteamVolume,
        deaeratorOutput_inletSteamTemperature: resultData.deaeratorOutput.inletSteamTemperature,
        deaeratorOutput_inletWaterEnergyFlow: resultData.deaeratorOutput.inletWaterEnergyFlow,
        deaeratorOutput_inletWaterMassFlow: resultData.deaeratorOutput.inletWaterMassFlow,
        deaeratorOutput_inletWaterPressure: resultData.deaeratorOutput.inletWaterPressure,
        deaeratorOutput_inletWaterQuality: resultData.deaeratorOutput.inletWaterQuality,
        deaeratorOutput_inletWaterSpecificEnthalpy: resultData.deaeratorOutput.inletWaterSpecificEnthalpy,
        deaeratorOutput_inletWaterSpecificEntropy: resultData.deaeratorOutput.inletWaterSpecificEntropy,
        deaeratorOutput_inletWaterVolume: resultData.deaeratorOutput.inletWaterVolume,
        deaeratorOutput_inletWaterTemperature: resultData.deaeratorOutput.inletWaterTemperature,
        deaeratorOutput_ventedSteamEnergyFlow: resultData.deaeratorOutput.ventedSteamEnergyFlow,
        deaeratorOutput_ventedSteamMassFlow: resultData.deaeratorOutput.ventedSteamMassFlow,
        deaeratorOutput_ventedSteamPressure: resultData.deaeratorOutput.ventedSteamPressure,
        deaeratorOutput_ventedSteamQuality: resultData.deaeratorOutput.ventedSteamQuality,
        deaeratorOutput_ventedSteamSpecificEnthalpy: resultData.deaeratorOutput.ventedSteamSpecificEnthalpy,
        deaeratorOutput_ventedSteamSpecificEntropy: resultData.deaeratorOutput.ventedSteamSpecificEntropy,
        deaeratorOutput_ventedSteamVolume: resultData.deaeratorOutput.ventedSteamVolume,
        deaeratorOutput_ventedSteamTemperature: resultData.deaeratorOutput.ventedSteamTemperature,

        lowPressureVentedSteamOutput_pressure: resultData.lowPressureVentedSteam.pressure,
        lowPressureVentedSteamOutput_temperature: resultData.lowPressureVentedSteam.temperature,
        lowPressureVentedSteamOutput_specificEnthalpy: resultData.lowPressureVentedSteam.specificEnthalpy,
        lowPressureVentedSteamOutput_specificEntropy: resultData.lowPressureVentedSteam.specificEntropy,
        lowPressureVentedSteamOutput_quality: resultData.lowPressureVentedSteam.quality,
        lowPressureVentedSteamOutput_specificVolume: resultData.lowPressureVentedSteam.specificVolume,
        lowPressureVentedSteamOutput_massFlow: resultData.lowPressureVentedSteam.massFlow,
        lowPressureVentedSteamOutput_energyFlow: resultData.lowPressureVentedSteam.energyFlow,

        highPressureProcessSteamUsageOutput_pressure: resultData.highPressureProcessSteamUsage.pressure,
        highPressureProcessSteamUsageOutput_temperature: resultData.highPressureProcessSteamUsage.temperature,
        highPressureProcessSteamUsageOutput_energyFlow: resultData.highPressureProcessSteamUsage.energyFlow,
        highPressureProcessSteamUsageOutput_massFlow: resultData.highPressureProcessSteamUsage.massFlow,
        highPressureProcessSteamUsageOutput_processUsage: resultData.highPressureProcessSteamUsage.processUsage,

        mediumPressureProcessSteamUsageOutput_pressure: resultData.mediumPressureProcessSteamUsage.pressure,
        mediumPressureProcessSteamUsageOutput_temperature: resultData.mediumPressureProcessSteamUsage.temperature,
        mediumPressureProcessSteamUsageOutput_energyFlow: resultData.mediumPressureProcessSteamUsage.energyFlow,
        mediumPressureProcessSteamUsageOutput_massFlow: resultData.mediumPressureProcessSteamUsage.massFlow,
        mediumPressureProcessSteamUsageOutput_processUsage: resultData.mediumPressureProcessSteamUsage.processUsage,

        lowPressureProcessSteamUsageOutput_pressure: resultData.lowPressureProcessSteamUsage.pressure,
        lowPressureProcessSteamUsageOutput_temperature: resultData.lowPressureProcessSteamUsage.temperature,
        lowPressureProcessSteamUsageOutput_energyFlow: resultData.lowPressureProcessSteamUsage.energyFlow,
        lowPressureProcessSteamUsageOutput_massFlow: resultData.lowPressureProcessSteamUsage.massFlow,
        lowPressureProcessSteamUsageOutput_processUsage: resultData.lowPressureProcessSteamUsage.processUsage,

        operationsOutput_powerGenerated: resultData.operationsOutput.powerGenerated,
        operationsOutput_boilerFuelCost: resultData.operationsOutput.boilerFuelCost,
        operationsOutput_makeupWaterVolumeFlow: resultData.operationsOutput.makeupWaterVolumeFlow,
        operationsOutput_makeupWaterVolumeFlowAnnual: resultData.operationsOutput.makeupWaterVolumeFlowAnnual,
        operationsOutput_makeupWaterCost: resultData.operationsOutput.makeupWaterCost,
        operationsOutput_totalOperatingCost: resultData.operationsOutput.totalOperatingCost,
        operationsOutput_powerGenerationCost: resultData.operationsOutput.powerGenerationCost,
        operationsOutput_boilerFuelUsage: resultData.operationsOutput.boilerFuelUsage,
        operationsOutput_sitePowerImport: resultData.operationsOutput.sitePowerImport,
        operationsOutput_sitePowerDemand: resultData.operationsOutput.sitePowerDemand,
    };

    return normalizedResultData;
}

run();
