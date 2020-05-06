const test = require('tap').test
    , testRoot = require('path').resolve(__dirname, '../../')
    , bindings = require('bindings')({ module_root: testRoot, bindings: 'calculator' });

function rnd(value) {
    return Number(Math.round(value + 'e' + 6) + 'e-' + 6);
}

test('electricityReduction', function (t) {
    t.plan(4);
    t.type(bindings.electricityReduction, 'function');

    var inp = {
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
    var res = bindings.electricityReduction(inp);
    t.equal(rnd(res.energyUse), rnd(407045.796185), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(48845.495542), 'res.energyCost is ' + res.energyCost);
    t.equal(rnd(res.power), rnd(47.111782), 'res.power is ' + res.power);

});

test('electricityReduction all calc types', function (t) {
    t.plan(3);
    t.type(bindings.electricityReduction, 'function');

    var inp = {
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
        ]
    };
    var res = bindings.electricityReduction(inp);
    t.equal(rnd(res.energyUse), rnd(1945004.716987), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(233400.566038), 'res.energyCost is ' + res.energyCost);
});


test('Natural Gas Reduction test 1', function (t) {
    t.plan(3);
    t.type(bindings.electricityReduction, 'function');

    var inp = {
        naturalGasReductionInputVec: [
            {
                operatingHours: 8640,
                fuelCost: 0.12,
                measurementMethod: 0,
                flowMeterMethodData: {
                    flowRate: 5
                },
                otherMethodData: {
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

    var res = bindings.naturalGasReduction(inp);
    t.equal(rnd(res.energyUse), rnd(88.992), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(10.67904), 'res.energyCost is ' + res.energyCost);
});


test('Compressed Air Reduction Basic Test', function (t) {
    t.plan(6);
    t.type(bindings.compressedAirReduction, 'function');

    var inp = {
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
                orificeMethodData: {
                    compressorAirTemp: 0,
                    atmosphericPressure: 0,
                    dischargeCoefficient: 0,
                    orificeDiameter: 0,
                    supplyPressure: 0,
                    numberOfOrifices: 1
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
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };

    var res = bindings.compressedAirReduction(inp);
    t.equal(rnd(res.energyUse), rnd(2211840.0));
    t.equal(rnd(res.energyCost), rnd(265420.8));
    t.equal(rnd(res.flowRate), rnd(200000.0));
    t.equal(rnd(res.singleNozzleFlowRate), rnd(0.0));
    t.equal(rnd(res.consumption), rnd(103680000000.0));
});
/*
test('Compressed Air Reduction Test (misc)', function (t) {
    t.plan(6);
    t.type(bindings.compressedAirReduction, 'function');

    var inp = {
        compressedAirReductionInputVec: [
            {
                hoursPerYear: 8640,
                utilityType: 1,
                utilityCost: 0.12,
                measurementMethod: 5,
                flowMeterMethodData: {
                    meterReading: 0
                },
                bagMethodData: {
                    height: 0,
                    diameter: 0,
                    fillTime: 0
                },
                pressureMethodData: {
                    nozzleType: 0,
                    numberOfNozzles: 1,
                    supplyPressure: 80
                },
                otherMethodData: {
                    consumption: 0
                },
                orificeMethodData: {
                    compressorAirTemp: 0,
                    atmosphericPressure: 0,
                    dischargeCoefficient: 0,
                    orificeDiameter: 0,
                    supplyPressure: 0,
                    numberOfOrifices: 0
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
                estimateMethodData: {
                    leakRateEstimate: 0
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.4,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };

    var res = bindings.compressedAirReduction(inp);
    t.equal(rnd(res.energyUse), rnd(790.1798));
    t.equal(rnd(res.energyCost), rnd(94.8216));
    t.equal(rnd(res.flowRate), rnd(1.429));
    t.equal(rnd(res.singleNozzleFlowRate), rnd(0.0));
    t.equal(rnd(res.consumption), rnd(740793.6));
});
*/
test('Compressed Air Reduction Test All', function (t) {
    t.plan(6);
    t.type(bindings.compressedAirReduction, 'function');

    var inp = {
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
                orificeMethodData: {
                    compressorAirTemp: 0,
                    atmosphericPressure: 0,
                    dischargeCoefficient: 0,
                    orificeDiameter: 0,
                    supplyPressure: 0,
                    numberOfOrifices: 1
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
                estimateMethodData: {
                    leakRateEstimate: 0.1
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
                orificeMethodData: {
                    compressorAirTemp: 0,
                    atmosphericPressure: 0,
                    dischargeCoefficient: 0,
                    orificeDiameter: 0,
                    supplyPressure: 0,
                    numberOfOrifices: 1
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
                estimateMethodData: {
                    leakRateEstimate: 0.1
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
                orificeMethodData: {
                    compressorAirTemp: 0,
                    atmosphericPressure: 0,
                    dischargeCoefficient: 0,
                    orificeDiameter: 0,
                    supplyPressure: 0,
                    numberOfOrifices: 1
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
                estimateMethodData: {
                    leakRateEstimate: 0.1
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
                orificeMethodData: {
                    compressorAirTemp: 0,
                    atmosphericPressure: 0,
                    dischargeCoefficient: 0,
                    orificeDiameter: 0,
                    supplyPressure: 0,
                    numberOfOrifices: 1
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
                estimateMethodData: {
                    leakRateEstimate: 0.1
                },
                compressorElectricityData: {
                    compressorControlAdjustment: 0.8,
                    compressorSpecificPower: 0.16
                },
                units: 1
            }
        ]
    };

    var res = bindings.compressedAirReduction(inp);
    t.equal(rnd(res.energyUse), rnd(2211881.965779));
    t.equal(rnd(res.energyCost), rnd(376063.261557));
    t.equal(rnd(res.flowRate), rnd(200005.187354));
    t.equal(rnd(res.singleNozzleFlowRate), rnd(1.778508));
    t.equal(rnd(res.consumption), rnd(103682889124.41486));
});


test('Compressed Air Pressure Reduction - Baseline', function (t) {
    t.plan(3);
    t.type(bindings.compressedAirPressureReduction, 'function');

    var inp = {
        compressedAirPressureReductionInputVec: [
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 500,
                pressure: 150,
                proposedPressure: null
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 250,
                pressure: 150,
                proposedPressure: null
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 500,
                pressure: 120,
                proposedPressure: 120
            },
            {
                isBaseline: true,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 450,
                pressure: 170,
                proposedPressure: 100
            }
        ]
    };

    var res = bindings.compressedAirPressureReduction(inp);
    t.equal(rnd(res.energyUse), rnd(14688000.0));
    t.equal(rnd(res.energyCost), rnd(73440.0));
});

test('Compressed Air Pressure Reduction - Modification', function (t) {
    t.plan(3);
    t.type(bindings.compressedAirPressureReduction, 'function');

    var inp = {
        compressedAirPressureReductionInputVec: [
            {
                isBaseline: false,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 500,
                pressure: 150,
                proposedPressure: 50
            },
            {
                isBaseline: false,
                hoursPerYear: 8640,
                electricityCost: 0.005,
                compressorPower: 250,
                pressure: 150,
                proposedPressure: 89
            }
        ]
    };

    var res = bindings.compressedAirPressureReduction(inp);
    t.equal(rnd(res.energyUse), rnd(3661200.0));
    t.equal(rnd(res.energyCost), rnd(18306.0));
});



test('Water Reduction - Metered Flow Data', function (t) {
    t.plan(3);
    t.type(bindings.waterReduction, 'function');

    var inp = {
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

    var res = bindings.waterReduction(inp);
    t.equal(rnd(res.waterUse), rnd(51840000.0));
    t.equal(rnd(res.waterCost), rnd(259200.0));
});

test('Water Reduction - All Types', function (t) {
    t.plan(3);
    t.type(bindings.waterReduction, 'function');

    var inp = {
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

    var res = bindings.waterReduction(inp);
    t.equal(rnd(res.waterUse), rnd(126400920.0));
    t.equal(rnd(res.waterCost), rnd(632004.6));
});

test('Pipe Insulation Reduction - With Insulation', function (t) {
    t.plan(3);
    t.type(bindings.pipeInsulationReduction, 'function');

    var inp = {
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
    var res = bindings.pipeInsulationReduction(inp);
    t.equal(rnd(res.heatLength), rnd(19.385877), 'res.heatLength is ' + res.heatLength);
    t.equal(rnd(res.annualHeatLoss), rnd(2836231.3687633672), 'res.annualHeatLoss is ' + res.annualHeatLoss);
});

test('Pipe Insulation Reduction - No Insulation', function (t) {
    t.plan(3);
    t.type(bindings.pipeInsulationReduction, 'function');

    var inp = {
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
    var res = bindings.pipeInsulationReduction(inp);
    t.equal(rnd(res.heatLength), rnd(278.8984025085), 'res.heatLength is ' + res.heatLength);
    t.equal(rnd(res.annualHeatLoss), rnd(40803951.880608), 'res.annualHeatLoss is ' + res.annualHeatLoss);
});


//Tank Insulation Reduction
test('Tank Insulation Reduction - Insulated', function (t) {
    t.plan(3);
    t.type(bindings.tankInsulationReduction, 'function');

    var inp = {
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
        jacketEmissivity: 0.9
    };
    var res = bindings.tankInsulationReduction(inp);
    t.equal(rnd(res.heatLoss), rnd(0.044464), 'res.heatLoss is ' + res.heatLoss);
    t.equal(rnd(res.annualHeatLoss), rnd(43.278176), 'res.annualHeatLoss is ' + res.annualHeatLoss);
});

test('Tank Insulation Reduction - Insulated 2', function (t) {
    t.plan(3);
    t.type(bindings.tankInsulationReduction, 'function');

    var inp = {
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
        jacketEmissivity: 0.1
    };
    var res = bindings.tankInsulationReduction(inp);
    t.equal(rnd(res.heatLoss), rnd(0.030515), 'res.heatLoss is ' + res.heatLoss);
    t.equal(rnd(res.annualHeatLoss), rnd(29.701354), 'res.annualHeatLoss is ' + res.annualHeatLoss);
});

test('Tank Insulation Reduction - No Insulation', function (t) {
    t.plan(3);
    t.type(bindings.tankInsulationReduction, 'function');

    var inp = {
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
    };
    var res = bindings.tankInsulationReduction(inp);
    t.equal(rnd(res.heatLoss), rnd(1.1112001223), 'res.heatLoss is ' + res.heatLoss);
    t.equal(rnd(res.annualHeatLoss), rnd(1081.568119), 'res.annualHeatLoss is ' + res.annualHeatLoss);
});


//Steam Reduction
test('Steam Reduction - Flow Meter Method Data', function (t) {
    t.plan(4);
    t.type(bindings.steamReduction, 'function');

    var inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 0,
                systemEfficiency: 100,
                pressure: 0.790800732,
                flowMeterMethodData: {
                    flowRate: 50000
                },
                airMassFlowMethodData: {
                    isNameplate: false,
                    massFlowMeasuredData: {
                        areaOfDuct: 100,
                        airVelocity: 5
                    },
                    massFlowNameplateData: {
                        flowRate: 400
                    },
                    inletTemperature: 75,
                    outletTemperature: 500
                },
                waterMassFlowMethodData: {
                    isNameplate: true,
                    massFlowMeasuredData: {
                        areaOfDuct: 50,
                        airVelocity: 1000
                    },
                    massFlowNameplateData: {
                        flowRate: 40000
                    },
                    inletTemperature: 75,
                    outletTemperature: 500
                },
                otherMethodData: {
                    consumption: 400000
                },
                units: 1
            }
        ]
    };

    var res = bindings.steamReduction(inp);
    t.equal(rnd(res.steamUse), rnd(438000000.00), 'res.steamUse is ' + res.steamUse);
    t.equal(rnd(res.energyUse), rnd(385822.092201), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(2122021.507107), 'res.energyCost is ' + res.energyCost);
});

test('Steam Reduction - Air Mass Flow - Measured', function (t) {
    t.plan(4);
    t.type(bindings.steamReduction, 'function');

    var inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 1,
                systemEfficiency: 100,
                pressure: 0.790800732,
                flowMeterMethodData: {
                    flowRate: 50000
                },
                airMassFlowMethodData: {
                    isNameplate: false,
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
                        areaOfDuct: 50,
                        airVelocity: 1000
                    },
                    massFlowNameplateData: {
                        flowRate: 40000
                    },
                    inletTemperature: 75,
                    outletTemperature: 500
                },
                otherMethodData: {
                    consumption: 400000
                },
                units: 1
            }
        ]
    };

    var res = bindings.steamReduction(inp);
    t.equal(rnd(res.steamUse), rnd(698117.037475), 'res.steamUse is ' + res.steamUse);
    t.equal(rnd(res.energyUse), rnd(614.952), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(3382.236), 'res.energyCost is ' + res.energyCost);
});

test('Steam Reduction - Air Mass Flow - Nameplate', function (t) {
    t.plan(4);
    t.type(bindings.steamReduction, 'function');

    var inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 1,
                systemEfficiency: 100,
                pressure: 0.790800732,
                flowMeterMethodData: {
                    flowRate: 50000
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
                        areaOfDuct: 50,
                        airVelocity: 1000
                    },
                    massFlowNameplateData: {
                        flowRate: 40000
                    },
                    inletTemperature: 75,
                    outletTemperature: 500
                },
                otherMethodData: {
                    consumption: 400000
                },
                units: 1
            }
        ]
    };

    var res = bindings.steamReduction(inp);
    t.equal(rnd(res.steamUse), rnd(558493.62998), 'res.steamUse is ' + res.steamUse);
    t.equal(rnd(res.energyUse), rnd(491.9616), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(2705.7888), 'res.energyCost is ' + res.energyCost);
});

test('Steam Reduction - Water Mass Flow - Nameplate', function (t) {
    t.plan(4);
    t.type(bindings.steamReduction, 'function');

    var inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8760,
                utilityType: 1,
                utilityCost: 5.5,
                measurementMethod: 2,
                systemEfficiency: 100,
                pressure: 0.790800732,
                flowMeterMethodData: {
                    flowRate: 50000
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
                        areaOfDuct: 50,
                        airVelocity: 1000
                    },
                    massFlowNameplateData: {
                        flowRate: 8.0
                    },
                    inletTemperature: 70,
                    outletTemperature: 100
                },
                otherMethodData: {
                    consumption: 400000
                },
                units: 1
            }
        ]
    };

    var res = bindings.steamReduction(inp);
    t.equal(rnd(res.steamUse), rnd(1193362.457222), 'res.steamUse is ' + res.steamUse);
    t.equal(rnd(res.energyUse), rnd(1051.2), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(5781.6), 'res.energyCost is ' + res.energyCost);
});

test('Steam Reduction - Other Method', function (t) {
    t.plan(4);
    t.type(bindings.steamReduction, 'function');

    var inp = {
        steamReductionInputVec: [
            {
                hoursPerYear: 8760,
                utilityType: 0,
                utilityCost: 1.5,
                measurementMethod: 3,
                systemEfficiency: 100,
                pressure: 0.790800732,
                flowMeterMethodData: {
                    flowRate: 50000
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
                        areaOfDuct: 50,
                        airVelocity: 1000
                    },
                    massFlowNameplateData: {
                        flowRate: 8.0
                    },
                    inletTemperature: 70,
                    outletTemperature: 100
                },
                otherMethodData: {
                    consumption: 400000
                },
                units: 1
            }
        ]
    };

    var res = bindings.steamReduction(inp);
    t.equal(rnd(res.steamUse), rnd(454095303.357088), 'res.steamUse is ' + res.steamUse);
    t.equal(rnd(res.energyUse), rnd(400000.0), 'res.energyUse is ' + res.energyUse);
    t.equal(rnd(res.energyCost), rnd(681.142955), 'res.energyCost is ' + res.energyCost);
});