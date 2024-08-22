function validateElectricityReduction(testName, inp, expected){
    let validate = function(results) {
        testNumberValue(rnd(results.energyUse), rnd(expected[0]), "energyUse");
        testNumberValue(rnd(results.energyCost), rnd(expected[1]), "energyCost");
        testNumberValue(rnd(results.power), rnd(expected[2]), "power");
    };

    logMessage('Calculator - Electricity Reduction: Test# ' + testName, true);
    let inputList = new Module.ElectricityReductionInputV();
    for (let i = 0; i < inp.electricityReductionInputVec.length; i++) {
        let inpElem = inp.electricityReductionInputVec[i];
        multimeterData = new Module.MultimeterData(inpElem.multimeterData.numberOfPhases,
            inpElem.multimeterData.supplyVoltage,inpElem.multimeterData.averageCurrent, inpElem.multimeterData.powerFactor);
        nameplateData = new Module.NameplateData(inpElem.nameplateData.ratedMotorPower, inpElem.nameplateData.variableSpeedMotor,
            inpElem.nameplateData.operationalFrequency, inpElem.nameplateData.lineFrequency, inpElem.nameplateData.motorAndDriveEfficiency, inpElem.nameplateData.loadFactor);
        powerMeterData = new Module.PowerMeterData(inpElem.powerMeterData.power);
        otherMethodData = new Module.OtherMethodData(inpElem.otherMethodData.energy);

        input = new Module.ElectricityReductionInput(inpElem.operatingHours, inpElem.electricityCost, inpElem.measurementMethod,
            multimeterData, nameplateData, powerMeterData, otherMethodData, inpElem.units);
        inputList.push_back(input);

        input.delete();
        multimeterData.delete();
        nameplateData.delete();
        powerMeterData.delete();
        otherMethodData.delete();
    }

    let instance = new Module.ElectricityReduction(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function electricityReduction(){
    let inp = {
        electricityReductionInputVec: [
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 0,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            }
        ]
    };
    validateElectricityReduction('1', inp, [407045.796185, 48845.495542, 47.111782]);

    inp = {
        electricityReductionInputVec: [
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 0,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 0,
                multimeterData: {
                    numberOfPhases: 1,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 1,
                multimeterData: {
                    numberOfPhases: 1,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 1
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 2,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 2
            },
            {
                operatingHours: 8640,
                electricityCost: 0.12,
                measurementMethod: 3,
                multimeterData: {
                    numberOfPhases: 3,
                    supplyVoltage: 800,
                    averageCurrent: 40,
                    powerFactor: 0.85
                },
                nameplateData: {
                    ratedMotorPower: 100,
                    variableSpeedMotor: false,
                    operationalFrequency: 55,
                    lineFrequency: 60,
                    motorAndDriveEfficiency: 100,
                    loadFactor: 1
                },
                powerMeterData: {
                    power: 50
                },
                otherMethodData: {
                    energy: 432000
                },
                units: 2
            }
        ] };
    validateElectricityReduction('2 - All', inp, [1945004.716987, 233400.566038, 432175.12]);
}

function validateNaturalGasReduction(testName, inp, expected){
    let validate = function(results) {
        testNumberValue(rnd(results.energyUse), rnd(expected[0]), "energyUse");
        testNumberValue(rnd(results.energyCost), rnd(expected[1]), "energyCost");
        testNumberValue(rnd(results.heatFlow), rnd(expected[2]), "heatFlow");
        testNumberValue(rnd(results.totalFlow), rnd(expected[3]), "totalFlow");
    };

    logMessage('Calculator - Natural Gas Reduction: Test# ' + testName, true);
    let inputList = new Module.NaturalGasReductionInputV();
    for (let i = 0; i < inp.naturalGasReductionInputVec.length; i++) {
        let inpElem = inp.naturalGasReductionInputVec[i];
        let flowMeterMethodData = new Module.FlowMeterMethodData(inpElem.flowMeterMethodData.flowRate);
        let naturalGasOtherMethodData = new Module.NaturalGasOtherMethodData(inpElem.naturalGasOtherMethodData.consumption);
        let airMassFlowMeasuredData = new Module.AirMassFlowMeasuredData(inpElem.airMassFlowData.airMassFlowMeasuredData.areaOfDuct,
            inpElem.airMassFlowData.airMassFlowMeasuredData.airVelocity);
        let airMassFlowNameplateData = new Module.AirMassFlowNameplateData(inpElem.airMassFlowData.airMassFlowNameplateData.airFlow);
        let airMassFlowData = new Module.AirMassFlowData(inpElem.airMassFlowData.isNameplate, airMassFlowMeasuredData, airMassFlowNameplateData,
            inpElem.airMassFlowData.inletTemperature, inpElem.airMassFlowData.outletTemperature, inpElem.airMassFlowData.systemEfficiency);
        let waterMassFlowData = new Module.WaterMassFlowData(inpElem.waterMassFlowData.waterFlow,
            inpElem.waterMassFlowData.inletTemperature, inpElem.waterMassFlowData.outletTemperature, inpElem.waterMassFlowData.systemEfficiency);

        let input = new Module.NaturalGasReductionInput(inpElem.operatingHours, inpElem.fuelCost, inpElem.measurementMethod,
            flowMeterMethodData, naturalGasOtherMethodData, airMassFlowData, waterMassFlowData, inpElem.units);
        inputList.push_back(input);

        input.delete();
        waterMassFlowData.delete();
        airMassFlowData.delete();
        airMassFlowNameplateData.delete();
        airMassFlowMeasuredData.delete();
        naturalGasOtherMethodData.delete();
        flowMeterMethodData.delete();
    }

    let instance = new Module.NaturalGasReduction(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function naturalGasReduction(){
    let inp = {
        naturalGasReductionInputVec: [
            {
                operatingHours: 8640,
                fuelCost: 0.12,
                measurementMethod: 0,
                flowMeterMethodData: {
                    flowRate: 5
                },
                naturalGasOtherMethodData: {
                    consumption: 30.00
                },
                airMassFlowData: {
                    isNameplate: false,
                    airMassFlowMeasuredData: {
                        areaOfDuct: 3,
                        airVelocity: 15
                    },
                    airMassFlowNameplateData: {
                        airFlow: 30
                    },
                    inletTemperature: 70,
                    outletTemperature: 800,
                    systemEfficiency: 80
                },
                waterMassFlowData: {
                    waterFlow: 10,
                    inletTemperature: 70,
                    outletTemperature: 100,
                    systemEfficiency: 80
                },
                units: 2
            }
        ]
    };
    validateNaturalGasReduction('1', inp, [88.992, 10.67904, 0, 10]);
}

function validateCompressedAirReduction(testName, inp, expected){
    let validate = function(results) {
        testNumberValue(rnd(results.energyUse), rnd(expected[0]), "energyUse");
        testNumberValue(rnd(results.energyCost), rnd(expected[1]), "energyCost");
        testNumberValue(rnd(results.flowRate), rnd(expected[2]), "flowRate");
        testNumberValue(rnd(results.singleNozzleFlowRate), rnd(expected[3]), "singleNozzleFlowRate");
        testNumberValue(rnd(results.consumption), rnd(expected[4]), "consumption");
    };

    logMessage('Calculator - Compressed Air Reduction: Test# ' + testName, true);
    let inputList = new Module.CompressedAirReductionInputV();
    for (let i = 0; i < inp.compressedAirReductionInputVec.length; i++) {
        let inpElem = inp.compressedAirReductionInputVec[i];
        let compressedAirFlowMeterMethodData = new Module.CompressedAirFlowMeterMethodData(inpElem.flowMeterMethodData.meterReading);
        let bagMethodData = new Module.BagMethodData(inpElem.bagMethodData.height, inpElem.bagMethodData.diameter, inpElem.bagMethodData.fillTime);
        let pressureMethodData = new Module.PressureMethodData(inpElem.pressureMethodData.nozzleType, inpElem.pressureMethodData.numberOfNozzles,
            inpElem.pressureMethodData.supplyPressure);
        let compressedAirOtherMethodData = new Module.CompressedAirOtherMethodData(inpElem.otherMethodData.consumption);
        let compressorElectricityData = new Module.CompressorElectricityData(inpElem.compressorElectricityData.compressorControlAdjustment,
            inpElem.compressorElectricityData.compressorSpecificPower);

        let input = new Module.CompressedAirReductionInput(inpElem.hoursPerYear, inpElem.utilityType, inpElem.utilityCost, inpElem.measurementMethod,
            compressedAirFlowMeterMethodData, bagMethodData, pressureMethodData, compressedAirOtherMethodData, compressorElectricityData, inpElem.units);
        inputList.push_back(input);

        input.delete();
        compressorElectricityData.delete();
        compressedAirOtherMethodData.delete();
        pressureMethodData.delete();
        bagMethodData.delete();
        compressedAirFlowMeterMethodData.delete();
    }

    let instance = new Module.CompressedAirReduction(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function compressedAirReduction(){
    let inp = {
        compressedAirReductionInputVec: [
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirReduction('1', inp, [276480000, 33177600, 200000, 0, 103680000000]);

    inp = {
        compressedAirReductionInputVec: [
            // flow measurement with electricity
            // energyUse = 221184000.0
            // energyCost = 26542080.0
            // flowRate = 0.0
            // singleNozzleFlowRate = 0.0
            // consumption = 103680000000.0
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // bag method with electricity
            // energyUse = 3769.9111
            // energyCost = 452.3893
            // flowRate = 3.408846
            // singleNozzleFlowRate = 0.0
            // consumption = 3534291.73528
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 1,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // pressure method, no electricity
            // flowRate = 1.778508
            // singleNozzleFlowRate = 1.778508
            // consumption = 921978.5471999
            {
                hoursPerYear: 8640,
                utilityType: 0,
                utilityCost: 0.12,
                measurementMethod: 2,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // other method with electricity
            // consumption = 200000.0
            // energyUse = 213.3333
            // energyCost = 25.6
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 3,
                flowMeterMethodData: {
                    meterReading: 200000.0
                },
                bagMethodData: {
                    height: 10,
                    diameter: 5,
                    fillTime: 30
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 200000
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirReduction('2 - All', inp, [276485245.722314, 33288866.912342, 200005.187354, 1.778508, 103682889124.41486]);
}

function validateCompressedAirLeakSurvey(testName, inp, expected){
    let validate = function(results) {
        testNumberValue(rnd(results.annualTotalElectricity), rnd(expected[0]), "annualTotalElectricity");
        testNumberValue(rnd(results.annualTotalElectricityCost), rnd(expected[1]), "annualTotalElectricityCost");
        testNumberValue(rnd(results.totalFlowRate), rnd(expected[2]), "totalFlowRate");
        testNumberValue(rnd(results.annualTotalFlowRate), rnd(expected[3]), "annualTotalFlowRate");
    };

    logMessage('Calculator - Compressed Air Leak Survey: Test# ' + testName, true);
    let inputList = new Module.CompressedAirLeakSurveyInputV();
    for (let i = 0; i < inp.compressedAirLeakSurveyInputVec.length; i++) {
        let inpElem = inp.compressedAirLeakSurveyInputVec[i];
        let estimateMethodData = new Module.EstimateMethodData(inpElem.estimateMethodData.leakRateEstimate);
        let bagMethodData = new Module.BagMethodData(inpElem.bagMethodData.height, inpElem.bagMethodData.diameter, inpElem.bagMethodData.fillTime);
        let decibelsMethodData = new Module.DecibelsMethodData(inpElem.decibelsMethodData.linePressure,
            inpElem.decibelsMethodData.decibels, inpElem.decibelsMethodData.decibelRatingA, inpElem.decibelsMethodData.pressureA,
            inpElem.decibelsMethodData.firstFlowA, inpElem.decibelsMethodData.secondFlowA, inpElem.decibelsMethodData.decibelRatingB,
            inpElem.decibelsMethodData.pressureB, inpElem.decibelsMethodData.firstFlowB, inpElem.decibelsMethodData.secondFlowB);
        let orificeMethodData = new Module.OrificeMethodData(inpElem.orificeMethodData.compressorAirTemp,
            inpElem.orificeMethodData.atmosphericPressure, inpElem.orificeMethodData.dischargeCoefficient,
            inpElem.orificeMethodData.orificeDiameter, inpElem.orificeMethodData.supplyPressure, inpElem.orificeMethodData.numberOfOrifices);
        let compressorElectricityData = new Module.CompressorElectricityData(inpElem.compressorElectricityData.compressorControlAdjustment,
            inpElem.compressorElectricityData.compressorSpecificPower);

        let input = new Module.CompressedAirLeakSurveyInput(inpElem.hoursPerYear, inpElem.utilityType, inpElem.utilityCost, inpElem.measurementMethod,
            estimateMethodData, decibelsMethodData, bagMethodData, orificeMethodData, compressorElectricityData, inpElem.units);
        inputList.push_back(input);

        input.delete();
        compressorElectricityData.delete();
        orificeMethodData.delete();
        decibelsMethodData.delete();
        bagMethodData.delete();
        estimateMethodData.delete();
    }

    let instance = new Module.CompressedAirLeakSurvey(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function compressedAirLeakSurvey(){
    let inp = {
        compressedAirLeakSurveyInputVec: [
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirLeakSurvey('1', inp, [138.24, 16.5888, 0.1, 51840]);

    inp = {
        compressedAirLeakSurveyInputVec: [
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 100
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 2
            },
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 14
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 0.785398163397448
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 6.32517756495803
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.25,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirLeakSurvey('2 - Additional', inp, [309908.582941, 37189.029953, 221.110576, 116215718.602824]);

    inp = {
        compressedAirLeakSurveyInputVec: [
            // estimate method with electricity
            // energyUse = 55.296
            // energyCost = 6.63552
            // flowRate = 0.1
            // compressedAirUse = 51840
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 0,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // decibels method with electricity
            // energyUse = 790.17984
            // energyCost = 94.8215808
            // flowRate = 1.429
            // compressedAirUse = 740793.6
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 1,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            },
            // bag method with electricity
            // energyUse = 3769.9111
            // energyCost = 452.3893
            // flowRate = 6.8176923906
            // compressedAirUse = 3534291.73528
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 2,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 2
            },
            // orifice method with electricity
            // energyUse = 1253583.3379004421
            // energyCost = 150430.000548053
            // flowRate = 2267.0416267007
            // compressedAirUse = 1175234379
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 3,
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                decibelsMethodData: {
                    linePressure: 130,
                    decibels: 25,
                    decibelRatingA: 20,
                    pressureA: 150,
                    firstFlowA: 1.04,
                    secondFlowA: 1.2,
                    decibelRatingB: 30,
                    pressureB: 125,
                    firstFlowB: 1.85,
                    secondFlowB: 1.65
                },
                bagMethodData: {
                    height: 15,
                    diameter: 10,
                    fillTime: 12
                },
                orificeMethodData: {
                    compressorAirTemp: 250.0,
                    atmosphericPressure: 14.7,
                    dischargeCoefficient: 1.0,
                    orificeDiameter: 6.0,
                    supplyPressure: 6.2,
                    numberOfOrifices: 4
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.40,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };
    validateCompressedAirLeakSurvey('3 - All', inp, [3145496.812312, 377459.617477, 2275.388319, 1179561304.616953]);
}

function validateCompressedAirPressureReduction(testName, inp, expected){
    let validate = function(results) {
        testNumberValue(rnd(results.energyUse), rnd(expected[0]), "energyUse");
        testNumberValue(rnd(results.energyCost), rnd(expected[1]), "energyCost");
    };

    logMessage('Calculator - Compressed Air Pressure Reduction: Test# ' + testName, true);
    let inputList = new Module.CompressedAirPressureReductionInputV();
    for (let i = 0; i < inp.compressedAirPressureReductionInputVec.length; i++) {
        let inpElem = inp.compressedAirPressureReductionInputVec[i];

        let input = new Module.CompressedAirPressureReductionInput(inpElem.isBaseline, inpElem.hoursPerYear, inpElem.electricityCost,
            inpElem.compressorPower, inpElem.pressure, inpElem.proposedPressure, inpElem.atmosphericPressure, inpElem.pressureRated);
        inputList.push_back(input);
    }

    let instance = new Module.CompressedAirPressureReduction(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function compressedAirPressureReduction(){
    let inp = {
        compressedAirPressureReductionInputVec: [
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 500,
                pressure: 150,
                proposedPressure: 0,
                atmosphericPressure: 0,
                pressureRated: 0
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 250,
                pressure: 150,
                proposedPressure: 0,
                atmosphericPressure: 0,
                pressureRated: 0
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 500,
                pressure: 120,
                proposedPressure: 120,
                atmosphericPressure: 0,
                pressureRated: 0
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 450,
                pressure: 170,
                proposedPressure: 100,
                atmosphericPressure: 0,
                pressureRated: 0
            }
        ]
    };
    validateCompressedAirPressureReduction('1 - Baseline', inp, [14688000, 73440]);

    inp = {
        compressedAirPressureReductionInputVec: [
            {
                isBaseline: false,
                hoursPerYear: 8760,
                electricityCost: 0.005,
                compressorPower: 200,
                pressure: 100,
                proposedPressure: 90,
                atmosphericPressure: 14.7,
                pressureRated: 100
            }
        ]
    };
    validateCompressedAirPressureReduction('2 - Modification', inp,[1650714.710542, 8253.57355271]);
}

function validateWaterReduction(testName, inp, expected){
    let validate = function(results) {
        testNumberValue(rnd(results.waterUse), rnd(expected[0]), "waterUse");
        testNumberValue(rnd(results.waterCost), rnd(expected[1]), "waterCost");
        testNumberValue(rnd(results.annualWaterSavings), rnd(expected[2]), "annualWaterSavings");
        testNumberValue(rnd(results.costSavings), rnd(expected[3]), "costSavings");
    };

    logMessage('Calculator - Water Reduction: Test# ' + testName, true);
    let inputList = new Module.WaterReductionInputV();
    for (let i = 0; i < inp.waterReductionInputVec.length; i++) {
        let inpElem = inp.waterReductionInputVec[i];
        let meteredFlowMethodData = new Module.MeteredFlowMethodData(inpElem.meteredFlowMethodData.meterReading);
        let volumeMeterMethodData = new Module.VolumeMeterMethodData(inpElem.volumeMeterMethodData.initialMeterReading,
            inpElem.volumeMeterMethodData.finalMeterReading, inpElem.volumeMeterMethodData.elapsedTime);
        let bucketMethodData = new Module.BucketMethodData(inpElem.bucketMethodData.bucketVolume, inpElem.bucketMethodData.bucketFillTime);
        let otherMethodData = new Module.WaterOtherMethodData(inpElem.otherMethodData.consumption);

        let input = new Module.WaterReductionInput(inpElem.hoursPerYear, inpElem.waterCost, inpElem.measurementMethod,
            meteredFlowMethodData, volumeMeterMethodData, bucketMethodData, otherMethodData);
        inputList.push_back(input);

        input.delete();
        otherMethodData.delete();
        bucketMethodData.delete();
        volumeMeterMethodData.delete();
        meteredFlowMethodData.delete();
    }

    let instance = new Module.WaterReduction(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function waterReduction(){
    let inp = {
        waterReductionInputVec: [
            {
                hoursPerYear: 8640,
                waterCost: 0.005,
                measurementMethod: 0,
                volumeMeterMethodData: {
                    initialMeterReading: 4235,
                    finalMeterReading: 5942,
                    elapsedTime: 15
                },
                meteredFlowMethodData: {
                    meterReading: 100
                },
                bucketMethodData: {
                    bucketVolume: 10,
                    bucketFillTime: 20
                },
                otherMethodData: {
                    consumption: 15000
                }
            }
        ]
    };
    validateWaterReduction('1', inp, [51840000, 259200, 0, 0]);

    inp = {
        waterReductionInputVec: [
            {
                hoursPerYear: 8640,
                waterCost: 0.005,
                measurementMethod: 0,
                volumeMeterMethodData: {
                    initialMeterReading: 4235,
                    finalMeterReading: 5942,
                    elapsedTime: 15
                },
                meteredFlowMethodData: {
                    meterReading: 100
                },
                bucketMethodData: {
                    bucketVolume: 10,
                    bucketFillTime: 20
                },
                otherMethodData: {
                    consumption: 15000
                }
            },
            {
                hoursPerYear: 8640,
                waterCost: 0.005,
                measurementMethod: 1,
                volumeMeterMethodData: {
                    initialMeterReading: 4235,
                    finalMeterReading: 5942,
                    elapsedTime: 15
                },
                meteredFlowMethodData: {
                    meterReading: 100
                },
                bucketMethodData: {
                    bucketVolume: 10,
                    bucketFillTime: 20
                },
                otherMethodData: {
                    consumption: 15000
                }
            },
            {
                hoursPerYear: 8640,
                waterCost: 0.005,
                measurementMethod: 2,
                volumeMeterMethodData: {
                    initialMeterReading: 4235,
                    finalMeterReading: 5942,
                    elapsedTime: 15
                },
                meteredFlowMethodData: {
                    meterReading: 100
                },
                bucketMethodData: {
                    bucketVolume: 10,
                    bucketFillTime: 20
                },
                otherMethodData: {
                    consumption: 15000
                }
            },
            {
                hoursPerYear: 8640,
                waterCost: 0.005,
                measurementMethod: 3,
                volumeMeterMethodData: {
                    initialMeterReading: 4235,
                    finalMeterReading: 5942,
                    elapsedTime: 15
                },
                meteredFlowMethodData: {
                    meterReading: 100
                },
                bucketMethodData: {
                    bucketVolume: 10,
                    bucketFillTime: 20
                },
                otherMethodData: {
                    consumption: 15000
                }
            }
        ]
    };
    validateWaterReduction('2 - All', inp, [8413080, 42065.4, 0, 0]);
}

function validateSteamReduction(testName, inp, expected) {
    let validate = function (results) {
        testNumberValue(rnd(results.steamUse), rnd(expected[0]), "steamUse");
        testNumberValue(rnd(results.energyUse), rnd(expected[1]), "energyUse");
        testNumberValue(rnd(results.energyCost), rnd(expected[2]), "energyCost");
    };

    logMessage('Calculator - Steam Reduction: Test# ' + testName, true);

    let inputList = new Module.SteamReductionInputV();
    for (let i = 0; i < inp.steamReductionInputVec.length; i++) {
        let inpElem = inp.steamReductionInputVec[i];
        let flowMeterMethodData = new Module.SteamFlowMeterMethodData(inpElem.flowMeterMethodData.flowRate);

        let massFlowMeasuredData = new Module.SteamMassFlowMeasuredData(inpElem.airMassFlowMethodData.massFlowMeasuredData.areaOfDuct,
            inpElem.airMassFlowMethodData.massFlowMeasuredData.airVelocity);
        let massFlowNameplateData = new Module.SteamMassFlowNameplateData(inpElem.airMassFlowMethodData.massFlowNameplateData.flowRate);
        let airMassFlowMethodData = new Module.SteamMassFlowMethodData(inpElem.airMassFlowMethodData.isNameplate,
            massFlowMeasuredData, massFlowNameplateData,
            inpElem.airMassFlowMethodData.inletTemperature, inpElem.airMassFlowMethodData.outletTemperature);

        massFlowMeasuredData = new Module.SteamMassFlowMeasuredData(inpElem.waterMassFlowMethodData.massFlowMeasuredData.areaOfDuct,
            inpElem.waterMassFlowMethodData.massFlowMeasuredData.airVelocity);
        massFlowNameplateData = new Module.SteamMassFlowNameplateData(inpElem.waterMassFlowMethodData.massFlowNameplateData.flowRate);
        let waterMassFlowMethodData = new Module.SteamMassFlowMethodData(inpElem.waterMassFlowMethodData.isNameplate,
            massFlowMeasuredData, massFlowNameplateData,
            inpElem.waterMassFlowMethodData.inletTemperature, inpElem.waterMassFlowMethodData.outletTemperature);

        let offsheetMethodData = new Module.SteamOffsheetMethodData(inpElem.offsheetMethodData.consumption);

        let input = new Module.SteamReductionInput(inpElem.hoursPerYear, inpElem.utilityType, inpElem.utilityCost,
            inpElem.measurementMethod, inpElem.systemEfficiency, inpElem.pressure,
            flowMeterMethodData, airMassFlowMethodData, waterMassFlowMethodData, offsheetMethodData, inpElem.units,
            inpElem.boilerEfficiency, inpElem.steamVariableOption, inpElem.steamVariable, inpElem.feedWaterTemperature);
        inputList.push_back(input);

        input.delete();
        offsheetMethodData.delete();
        waterMassFlowMethodData.delete();
        airMassFlowMethodData.delete();
        massFlowNameplateData.delete();
        massFlowMeasuredData.delete();
        flowMeterMethodData.delete();
    }

    let instance = new Module.SteamReduction(inputList);
    validate(instance.calculate());

    instance.delete();
    inputList.delete();
}

function steamReduction(){
    let inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8000,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 0,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: {
                    flowRate: 1000
                },
                airMassFlowMethodData: {
                    isNameplate: false,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 4000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 40000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: {
                    consumption: 13000000
                },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: Module.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ]
    };
    validateSteamReduction('1 - Flow Meter Method Data', inp, [10000000.0, 38671503020.03, 212693266610.1651]);

    inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8000,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 1,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: {
                    flowRate: 1000
                },
                airMassFlowMethodData: {
                    isNameplate: false,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 4000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 40000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: {
                    consumption: 13000000
                },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: Module.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ]
    };
    validateSteamReduction('2 - Air Mass Flow - Measured', inp, [9982.3376, 38603200.0, 212317600.0]);

    inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8000,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 1,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: {
                    flowRate: 1000
                },
                airMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 4000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 40000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: {
                    consumption: 13000000
                },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: Module.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ]
    };
    validateSteamReduction('3 - Air Mass Flow - Nameplate', inp, [399293.5054, 1544127999.9999, 8492703999.9999]);

    inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8000,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 2,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: {
                    flowRate: 1000
                },
                airMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 100,
                        airVelocity: 5
                    },
                    massFlowNameplateData: {
                        flowRate: 400
                    },
                    inletTemperature: 70,
                    outletTemperature: 200
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 1
                    },
                    inletTemperature: 25,
                    outletTemperature: 225
                },
                offsheetMethodData: {
                    consumption: 13000000
                },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: Module.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ]
    };
    validateSteamReduction('4 - Water Mass Flow - Nameplate', inp, [173112830.1340, 669453333333.3332, 3681993333333.3330]);

    inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8000,
                utilityType: 0,
                utilityCost: 5.5,
                measurementMethod: 3,
                systemEfficiency: 0.8,
                pressure: 3.5,
                flowMeterMethodData: {
                    flowRate: 50000
                },
                airMassFlowMethodData: {
                    isNameplate: false,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 4000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 1,
                        airVelocity: 100
                    },
                    massFlowNameplateData: {
                        flowRate: 4000
                    },
                    inletTemperature: 25,
                    outletTemperature: 425
                },
                offsheetMethodData: {
                    consumption: 13000000
                },
                units: 1,
                boilerEfficiency: 0.75,
                steamVariableOption: Module.ThermodynamicQuantity.TEMPERATURE,
                steamVariable: 560,
                feedWaterTemperature: 283.15
            }
        ]
    };
    validateSteamReduction('5 - Offsheet Method', inp, [3361.6485, 13000000.0, 18489.0667]);
}

function validateInsulatedPipeCalculator(testName, inp, expected){
    let validate = function (results) {
        testNumberValue(rnd(results.getHeatLength()), rnd(expected[0]), "heatLength");
        testNumberValue(rnd(results.getAnnualHeatLoss()), rnd(expected[1]), "annualHeatLoss");
    };

    logMessage('Calculator - Pipe Insulation Reduction: Test# ' + testName, true);

    let pipeMaterialCoefficients = new Module.DoubleVector();
    let insulationMaterialCoefficients= new Module.DoubleVector();
    for (dblVal of inp.pipeMaterialCoefficients) pipeMaterialCoefficients.push_back(dblVal);
    for (dblVal of inp.insulationMaterialCoefficients) insulationMaterialCoefficients.push_back(dblVal);
    let input = new Module.InsulatedPipeInput(inp.operatingHours, inp.pipeLength, inp.pipeDiameter, inp.pipeThickness,
        inp.pipeTemperature, inp.ambientTemperature, inp.windVelocity, inp.systemEfficiency, inp.insulationThickness,
        inp.pipeEmissivity, inp.jacketEmissivity, pipeMaterialCoefficients, insulationMaterialCoefficients);
    let instance = new Module.InsulatedPipeCalculator(input);
    validate(instance.calculate());

    instance.delete();
    input.delete();
    insulationMaterialCoefficients.delete();
    pipeMaterialCoefficients.delete();
}

function insulatedPipeCalculator(){
    let inp = {
        operatingHours: 8640,
        pipeLength: 15.24,
        pipeDiameter: 0.025399,
        pipeThickness: 0.0033782,
        pipeTemperature: 422.039,
        ambientTemperature: 299.817,
        windVelocity: 0.89408,
        systemEfficiency: 90,
        insulationThickness: 0.0762,
        pipeEmissivity: 0.8000,
        jacketEmissivity: 0.1,
        pipeMaterialCoefficients: [0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1],
        insulationMaterialCoefficients: [1.57526e-12, -2.02822e-9, 8.6328e-7, 0, 0.006729488]
    };
    validateInsulatedPipeCalculator('1 - With Insulation', inp, [19.385877, 28362.313687633672]);

    inp = {
        operatingHours: 8640,
        pipeLength: 15.24,
        pipeDiameter: 0.025399,
        pipeThickness: 0.0033782,
        pipeTemperature: 422.039,
        ambientTemperature: 299.817,
        windVelocity: 0.89408,
        systemEfficiency: 90,
        insulationThickness: -1,
        pipeEmissivity: 0.8000,
        jacketEmissivity: 0.1,
        pipeMaterialCoefficients: [0, 2.08333e-9, 3.67044e-19, -5.10833e-2, 7.90000e1],
        insulationMaterialCoefficients: [1.57526e-12, -2.02822e-9, 8.6328e-7, 0, 0.006729488]
    };
    validateInsulatedPipeCalculator('2 - No Insulation', inp, [278.8984025085, 408039.51880608]);
}

function validateInsulatedTankCalculator(testName, inp, expected){
    let validate = function (results) {
        testNumberValue(rnd(results.getHeatLoss()), rnd(expected[0]), "heatLoss");
        testNumberValue(rnd(results.getAnnualHeatLoss()), rnd(expected[1]), "annualHeatLoss");
    };

    logMessage('Calculator - Tank Insulation Reduction: Test# ' + testName, true);

    let input = new Module.InsulatedTankInput(
        inp.operatingHours, 
        inp.tankHeight, 
        inp.tankDiameter, 
        inp.tankThickness,
        inp.tankEmissivity, 
        inp.tankConductivity, 
        inp.tankTemperature, 
        inp.ambientTemperature, 
        inp.systemEfficiency,
        inp.insulationThickness, 
        inp.insulationConductivity, 
        inp.jacketEmissivity,
        inp.surfaceTemperature);
    let instance = new Module.InsulatedTankCalculator(input);
    validate(instance.calculate());

    instance.delete();
    input.delete();
}

function insulatedTankCalculator(){
    let inp = {
        operatingHours: 8760,
        tankHeight: 10,
        tankDiameter: 5,
        tankThickness: 0.5,
        tankEmissivity: 0.8,
        tankConductivity: 46.2320,
        tankTemperature: 959.67,
        ambientTemperature: 529.67,
        systemEfficiency: 90,
        insulationThickness: 0.5,
        insulationConductivity: 0.0191,
        jacketEmissivity: 0.9,
        surfaceTemperature: 959.67
    };
    validateInsulatedTankCalculator('1 - Insulated', inp, [0.044464, 0.43278176]);

    inp = {
        operatingHours: 8760,
        tankHeight: 50,
        tankDiameter: 1,
        tankThickness: 0.25,
        tankEmissivity: 0.3,
        tankConductivity: 9.25,
        tankTemperature: 759.67,
        ambientTemperature: 539.67,
        systemEfficiency: 90,
        insulationThickness: 0.5,
        insulationConductivity: 0.0231,
        jacketEmissivity: 0.1,
        surfaceTemperature: 759.67
    };
    validateInsulatedTankCalculator('2 - Insulated', inp, [0.030515, 0.29701354]);

    inp = {
        operatingHours: 8760,
        tankHeight: 10,
        tankDiameter: 5,
        tankThickness: 0.5,
        tankEmissivity: 0.8,
        tankConductivity: 46.2320,
        tankTemperature: 959.67,
        ambientTemperature: 529.67,
        systemEfficiency: 90,
        insulationThickness: 0,
        insulationConductivity: 0,
        jacketEmissivity: 0.9,
        surfaceTemperature: 959.67
    };
    validateInsulatedTankCalculator('3 - No Insulation', inp, [1.1112001223, 10.81568119]);
}

electricityReduction();
naturalGasReduction();
compressedAirReduction();
compressedAirLeakSurvey();
compressedAirPressureReduction();
waterReduction();
steamReduction();
insulatedPipeCalculator();
insulatedTankCalculator();