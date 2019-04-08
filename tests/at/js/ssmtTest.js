const d3 = require('d3');
const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../../')
    , bindings = require('bindings')({module_root: testRoot, bindings: 'ssmt'});

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
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

        //  use position of the supplied letter within the alphabet 
        //  to establish a base-26 numerical system
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

function runTest() {
    console.log('================================================================');
    console.log('Running Acceptance Tests');

    var configFile = "file://" + testRoot + "/tests/at/csv/ssmtTestConfig.csv";
    console.log('Using configuration file=' + configFile);

    d3.csv(configFile, function (errConfig, configData) {
        let testCount = configData.length;
        for (let i = 0; i < testCount; i++) {
            console.log('================================================');
            console.log('Running Acceptance Test #' + i);
            let testFileName = configData[i].testDataFileName;
            var testDataFile = "file://" + testRoot + "/tests/at/csv/" + testFileName + ".csv";
            console.log('Using test data file=' + testDataFile);

            d3.csv(testDataFile, function (err, data) {
                if (data.length == 0) {
                    console.log('data.length is 0, throwing error');
                    throw "ERROR: No data found in file='" + testFileName + ". It is empty or missing.";
                } else {
                    console.log('going into data handling');
                    let metaDataStartColumn = configData[i].metaDataStartColumn.toLowerCase();
                    let metaDataEndColumn = configData[i].metaDataEndColumn.toLowerCase();
                    let inputDataStartColumn = configData[i].inputDataStartColumn.toLowerCase();
                    let inputDataEndColumn = configData[i].inputDataEndColumn.toLowerCase();
                    let expectedDataStartColumn = configData[i].expectedDataStartColumn.toLowerCase();
                    let expectedDataEndColumn = configData[i].expectedDataEndColumn.toLowerCase();
                    let metaDataStartColumnIndex = convertColumnToIndex(metaDataStartColumn);
                    let metaDataEndColumnIndex = convertColumnToIndex(metaDataEndColumn);
                    let inputDataStartColumnIndex = convertColumnToIndex(inputDataStartColumn);
                    let inputDataEndColumnIndex = convertColumnToIndex(inputDataEndColumn);
                    let expectedDataStartColumnIndex = convertColumnToIndex(expectedDataStartColumn);
                    let expectedDataEndColumnIndex = convertColumnToIndex(expectedDataEndColumn);
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

                    let columns = data.columns;
                    //  check if number of columns is less than or equal to number of columns
                    //  described in config file to avoid index out of array error
                    let maxColumns = Math.max(Math.max(inputDataEndColumnIndex, expectedDataEndColumnIndex), metaDataEndColumnIndex);
                    if (maxColumns > columns.length - 1) {
                        throw "ERROR: In file '" + testFileName + ".csv', only found " + columns.length + " columns, expected " + (maxColumns + 1) + " columns. Please check your config file.";
                    }

                    let metaDataNames = [];
                    let inputDataNames = [];
                    let expectedDataNames = [];
                    let activeData = [];
                    let inputData = {};
                    let expectedData = {};

                    let enabledIndex = -1;
                    //create objects with column titles as parameter names
                    for (let j = metaDataStartColumnIndex; j <= metaDataEndColumnIndex; j++) {
                        metaDataNames.push(columns[j]);
                        //check if there is an enable flag column and grab index
                        if (metaDataNames[j].toLowerCase() == "enabled") {
                            enabledIndex = j;
                        }
                    }
                    for (let j = inputDataStartColumnIndex; j <= inputDataEndColumnIndex; j++) {
                        inputDataNames.push(columns[j]);
                        inputData[columns[j]] = null;
                    }
                    for (let j = expectedDataStartColumnIndex; j <= expectedDataEndColumnIndex; j++) {
                        expectedDataNames.push(columns[j]);
                        expectedData[columns[j]] = null;
                    }
                    //if there is an enable flag, only check enabled tests
                    if (enabledIndex >= 0) {
                        //collect all rows that are enabled
                        for (let j = 0; j < data.length; j++) {
                            if (data[j][metaDataNames[enabledIndex]].toLowerCase() == "true") {
                                activeData.push(data[j]);
                            }
                        }
                    } else {
                        //if no enabled flag, just use all rows
                        activeData = data;
                    }

                    let testCount = activeData.length;
                    for (let testNum = 0; testNum < testCount; testNum++) {
                        let testData = activeData[testNum];
                        let testId = testData[metaDataNames[1]];
                        let testName = testData[metaDataNames[2]];

                        test('Running test id=' + testId + ', test name="' + testName + '"', [{'diagnostic': 'false'}], function (t) {
                            t.plan(expectedDataNames.length);
                            t.type(bindings.steamModeler, 'function');
                            inputData = {};
                            expectedData = {};

                            for (let k = 0; k < inputDataNames.length; k++) {
                                inputData[inputDataNames[k]] = activeData[j][inputDataNames[k]];
                            }
                            for (let k = 0; k < expectedDataNames.length; k++) {
                                expectedData[expectedDataNames[k]] = activeData[j][expectedDataNames[k]];
                            }

                            let isBaselineCalc = inputData.isBaselineCalc;
                            let baselinePowerDemand = inputData.baselinePowerDemand;

                            console.log("isBaselineCalc=" + isBaselineCalc);
                            console.log("baselinePowerDemand=" + baselinePowerDemand);

                            //construct input objects
                            let boilerInput = makeBoilerInput(inputData);
                            let headerInput = makeHeaderInput(inputData);
                            let operationsInput = makeOperationsInput(inputData);
                            let turbineInput = makeTurbineInput(inputData);

                            let steamInput = {
                                isBaselineCalc: isBaselineCalc,
                                baselinePowerDemand: baselinePowerDemand ,
                                boilerInput: boilerInput,
                                headerInput: headerInput,
                                operationsInput: operationsInput,
                                turbineInput: turbineInput
                            };

                            //call binding and store return object
                            let resultData = bindings.steamModeler(steamInput);
                            resultData = normalizeResultData(resultData);


                            for (let k = 0; k < expectedDataNames.length; k++) {
                                t.equal(rnd(resultData[expectedDataNames[k]]), rnd(expectedData[expectedDataNames[k]]), expectedDataNames[k] + ': ' + resultData[expectedDataNames[k]] + ' != ' + expectedData[expectedDataNames[k]]);
                            }

                            console.log('--------------------------------');
                            console.log('');
                        });
                    }
                }
            });
        }
    });
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

function normalizeResultData(resultData) {
    let normalizedResultData = {
        operationsOutput_powerGenerated: resultData.operationsOutput.powerGenerated,
        operationsOutput_boilerFuelCost: resultData.operationsOutput.boilerFuelCost,
        operationsOutput_makeupWaterVolumeFlowGpm: resultData.operationsOutput.makeupWaterVolumeFlowGpm,
        operationsOutput_makeupWaterVolumeFlowGpmAnnual: resultData.operationsOutput.makeupWaterVolumeFlowGpmAnnual,
        operationsOutput_makeupWaterCost: resultData.operationsOutput.makeupWaterCost,
        operationsOutput_totalOperatingCost: resultData.operationsOutput.totalOperatingCost,
        operationsOutput_powerGenerationCost: resultData.operationsOutput.powerGenerationCost,
        operationsOutput_boilerFuelUsage: resultData.operationsOutput.boilerFuelUsage,
        operationsOutput_sitePowerImport: resultData.operationsOutput.sitePowerImport,
        operationsOutput_sitePowerDemand: resultData.operationsOutput.sitePowerDemand,

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

        makeupWaterOutput_pressure: resultData.makeupWater.pressure,
        makeupWaterOutput_temperature: resultData.makeupWater.temperature,
        makeupWaterOutput_specificEnthalpy: resultData.makeupWater.specificEnthalpy,
        makeupWaterOutput_specificEntropy: resultData.makeupWater.specificEntropy,
        makeupWaterOutput_quality: resultData.makeupWater.quality,
        makeupWaterOutput_specificVolume: resultData.makeupWater.specificVolume,

        makeupWaterAndCondensateOutput_pressure: resultData.makeupWaterAndCondensate.pressure,
        makeupWaterAndCondensateOutput_temperature: resultData.makeupWaterAndCondensate.temperature,
        makeupWaterAndCondensateOutput_specificEnthalpy: resultData.makeupWaterAndCondensate.specificEnthalpy,
        makeupWaterAndCondensateOutput_specificEntropy: resultData.makeupWaterAndCondensate.specificEntropy,
        makeupWaterAndCondensateOutput_quality: resultData.makeupWaterAndCondensate.quality,
        makeupWaterAndCondensateOutput_specificVolume: resultData.makeupWaterAndCondensate.specificVolume,
        makeupWaterAndCondensateOutput_massFlow: resultData.makeupWaterAndCondensate.massFlow,
        makeupWaterAndCondensateOutput_energyFlow: resultData.makeupWaterAndCondensate.energyFlow,

        highPressureProcessSteamUsageOutput_pressure: resultData.highPressureProcessSteamUsage.pressure,
        highPressureProcessSteamUsageOutput_temperature: resultData.highPressureProcessSteamUsage.temperature,
        highPressureProcessSteamUsageOutput_massFlow: resultData.highPressureProcessSteamUsage.massFlow,
        highPressureProcessSteamUsageOutput_energyFlow: resultData.highPressureProcessSteamUsage.energyFlow,
        highPressureProcessSteamUsageOutput_processUsage: resultData.highPressureProcessSteamUsage.processUsage,

        condensingTurbineOutput_energyOut: resultData.condensingTurbine.energyOut,
        condensingTurbineOutput_generatorEfficiency: resultData.condensingTurbine.generatorEfficiency,
        condensingTurbineOutput_inletEnergyFlow: resultData.condensingTurbine.inletEnergyFLow,
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
        condensingTurbineOutput_outletIdealPressure: resultData.condensingTurbine.outletIdealPressure,
        condensingTurbineOutput_outletIdealTemperature: resultData.condensingTurbine.outletIdealTemperature,
        condensingTurbineOutput_outletIdealSpecificEnthalpy: resultData.condensingTurbine.outletIdealSpecificEnthalpy,
        condensingTurbineOutput_outletIdealSpecificEntropy: resultData.condensingTurbine.outletIdealSpecificEntropy,
        condensingTurbineOutput_outletIdealQuality: resultData.condensingTurbine.outletIdealQuality,
        condensingTurbineOutput_outletIdealVolume: resultData.condensingTurbine.outletIdealVolume,

        highPressureToMediumPressureTurbineOutput_energyOut: resultData.highPressureToMediumPressureTurbine.energyOut,
        highPressureToMediumPressureTurbineOutput_generatorEfficiency: resultData.highPressureToMediumPressureTurbine.generatorEfficiency,
        highPressureToMediumPressureTurbineOutput_inletEnergyFlow: resultData.highPressureToMediumPressureTurbine.inletEnergyFLow,
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
        highPressureToMediumPressureTurbineOutput_outletIdealPressure: resultData.highPressureToMediumPressureTurbine.outletIdealPressure,
        highPressureToMediumPressureTurbineOutput_outletIdealTemperature: resultData.highPressureToMediumPressureTurbine.outletIdealTemperature,
        highPressureToMediumPressureTurbineOutput_outletIdealSpecificEnthalpy: resultData.highPressureToMediumPressureTurbine.outletIdealSpecificEnthalpy,
        highPressureToMediumPressureTurbineOutput_outletIdealSpecificEntropy: resultData.highPressureToMediumPressureTurbine.outletIdealSpecificEntropy,
        highPressureToMediumPressureTurbineOutput_outletIdealQuality: resultData.highPressureToMediumPressureTurbine.outletIdealQuality,
        highPressureToMediumPressureTurbineOutput_outletIdealVolume: resultData.highPressureToMediumPressureTurbine.outletIdealVolume,

        highPressureToLowPressureTurbineOutput_energyOut: resultData.highPressureToLowPressureTurbine.energyOut,
        highPressureToLowPressureTurbineOutput_generatorEfficiency: resultData.highPressureToLowPressureTurbine.generatorEfficiency,
        highPressureToLowPressureTurbineOutput_inletEnergyFlow: resultData.highPressureToLowPressureTurbine.inletEnergyFLow,
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
        highPressureToLowPressureTurbineOutput_outletIdealPressure: resultData.highPressureToLowPressureTurbine.outletIdealPressure,
        highPressureToLowPressureTurbineOutput_outletIdealTemperature: resultData.highPressureToLowPressureTurbine.outletIdealTemperature,
        highPressureToLowPressureTurbineOutput_outletIdealSpecificEnthalpy: resultData.highPressureToLowPressureTurbine.outletIdealSpecificEnthalpy,
        highPressureToLowPressureTurbineOutput_outletIdealSpecificEntropy: resultData.highPressureToLowPressureTurbine.outletIdealSpecificEntropy,
        highPressureToLowPressureTurbineOutput_outletIdealQuality: resultData.highPressureToLowPressureTurbine.outletIdealQuality,
        highPressureToLowPressureTurbineOutput_outletIdealVolume: resultData.highPressureToLowPressureTurbine.outletIdealVolume,

        mediumPressureToLowPressureTurbineOutput_energyOut: resultData.mediumPressureToLowPressureTurbine.energyOut,
        mediumPressureToLowPressureTurbineOutput_generatorEfficiency: resultData.mediumPressureToLowPressureTurbine.generatorEfficiency,
        mediumPressureToLowPressureTurbineOutput_inletEnergyFlow: resultData.mediumPressureToLowPressureTurbine.inletEnergyFLow,
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
        mediumPressureToLowPressureTurbineOutput_outletIdealPressure: resultData.mediumPressureToLowPressureTurbine.outletIdealPressure,
        mediumPressureToLowPressureTurbineOutput_outletIdealTemperature: resultData.mediumPressureToLowPressureTurbine.outletIdealTemperature,
        mediumPressureToLowPressureTurbineOutput_outletIdealSpecificEnthalpy: resultData.mediumPressureToLowPressureTurbine.outletIdealSpecificEnthalpy,
        mediumPressureToLowPressureTurbineOutput_outletIdealSpecificEntropy: resultData.mediumPressureToLowPressureTurbine.outletIdealSpecificEntropy,
        mediumPressureToLowPressureTurbineOutput_outletIdealQuality: resultData.mediumPressureToLowPressureTurbine.outletIdealQuality,
        mediumPressureToLowPressureTurbineOutput_outletIdealVolume: resultData.mediumPressureToLowPressureTurbine.outletIdealVolume,

        highPressureHeaderSteamOutput_pressure: resultData.highPressureHeaderSteam.pressure,
        highPressureHeaderSteamOutput_temperature: resultData.highPressureHeaderSteam.temperature,
        highPressureHeaderSteamOutput_specificEnthalpy: resultData.highPressureHeaderSteam.specificEnthalpy,
        highPressureHeaderSteamOutput_specificEntropy: resultData.highPressureHeaderSteam.specificEntropy,
        highPressureHeaderSteamOutput_quality: resultData.highPressureHeaderSteam.quality,
        highPressureHeaderSteamOutput_specificVolume: resultData.highPressureHeaderSteam.specificVolume,
        highPressureHeaderSteamOutput_massFlow: resultData.highPressureHeaderSteam.massFlow,
        highPressureHeaderSteamOutput_energyFlow: resultData.highPressureHeaderSteam.energyFlow,

        mediumPressureHeaderSteamOutput_pressure: resultData.mediumPressureHeaderSteam.pressure,
        mediumPressureHeaderSteamOutput_temperature: resultData.mediumPressureHeaderSteam.temperature,
        mediumPressureHeaderSteamOutput_specificEnthalpy: resultData.mediumPressureHeaderSteam.specificEnthalpy,
        mediumPressureHeaderSteamOutput_specificEntropy: resultData.mediumPressureHeaderSteam.specificEntropy,
        mediumPressureHeaderSteamOutput_quality: resultData.mediumPressureHeaderSteam.quality,
        mediumPressureHeaderSteamOutput_specificVolume: resultData.mediumPressureHeaderSteam.specificVolume,
        mediumPressureHeaderSteamOutput_massFlow: resultData.mediumPressureHeaderSteam.massFlow,
        mediumPressureHeaderSteamOutput_energyFlow: resultData.mediumPressureHeaderSteam.energyFlow,

        lowPressureHeaderSteamOutput_pressure: resultData.lowPressureHeaderSteam.pressure,
        lowPressureHeaderSteamOutput_temperature: resultData.lowPressureHeaderSteam.temperature,
        lowPressureHeaderSteamOutput_specificEnthalpy: resultData.lowPressureHeaderSteam.specificEnthalpy,
        lowPressureHeaderSteamOutput_specificEntropy: resultData.lowPressureHeaderSteam.specificEntropy,
        lowPressureHeaderSteamOutput_quality: resultData.lowPressureHeaderSteam.quality,
        lowPressureHeaderSteamOutput_specificVolume: resultData.lowPressureHeaderSteam.specificVolume,
        lowPressureHeaderSteamOutput_massFlow: resultData.lowPressureHeaderSteam.massFlow,
        lowPressureHeaderSteamOutput_energyFlow: resultData.lowPressureHeaderSteam.energyFlow,

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

        ventedSteamOutput_pressure: resultData.ventedSteam.pressure,
        ventedSteamOutput_temperature: resultData.ventedSteam.temperature,
        ventedSteamOutput_specificEnthalpy: resultData.ventedSteam.specificEnthalpy,
        ventedSteamOutput_specificEntropy: resultData.ventedSteam.specificEntropy,
        ventedSteamOutput_quality: resultData.ventedSteam.quality,
        ventedSteamOutput_specificVolume: resultData.ventedSteam.specificVolume,
        ventedSteamOutput_massFlow: resultData.ventedSteam.massFlow,
        ventedSteamOutput_energyFlow: resultData.ventedSteam.energyFlow
    }

    return normalizedResultData;
}


runTest();
