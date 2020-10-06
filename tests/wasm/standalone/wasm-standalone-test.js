// CHP
function CHP() {
    var inp = {
        annualOperatingHours: 4160,
        annualElectricityConsumption: 23781908,
        annualThermalDemand: 122581,
        boilerThermalFuelCosts: 5.49,
        avgElectricityCosts: 0.214,
        option: Module.CHPOption.PercentAvgkWhElectricCostAvoided,
        boilerThermalFuelCostsCHPcase: 5.49,
        CHPfuelCosts: 5.49,
        percentAvgkWhElectricCostAvoidedOrStandbyRate: 90,
        displacedThermalEfficiency: 85,
        chpAvailability: 95,
        thermalUtilization: 90
    };

    let chp = new Module.CHP(inp.annualOperatingHours, inp.annualElectricityConsumption, inp.annualThermalDemand, inp.boilerThermalFuelCosts, inp.avgElectricityCosts, inp.option, inp.boilerThermalFuelCostsCHPcase, inp.CHPfuelCosts, inp.percentAvgkWhElectricCostAvoidedOrStandbyRate, inp.displacedThermalEfficiency, inp.chpAvailability, inp.thermalUtilization);
    let result = chp.getCostInfo();
    testNumberValue(result.annualOperationSavings, 3251705.06182641, "STANDALONE CHP (annualOperationSavings-1)");
    testNumberValue(result.totalInstalledCostsPayback, 11890954.0, "STANDALONE CHP (totalInstalledCostsPayback-1)");
    testNumberValue(result.simplePayback, 3.595330381, "STANDALONE CHP (simplePayback-1)");
    testNumberValue(result.fuelCosts, 0.0648161938, "STANDALONE CHP (fuelCosts-1)");
    testNumberValue(result.thermalCredit, -0.0284427212, "STANDALONE CHP (thermalCredit-1)");
    testNumberValue(result.incrementalOandM, 0.0123, "STANDALONE CHP (incrementalOandM-1)");
    testNumberValue(result.totalOperatingCosts, 0.0486734726, "STANDALONE CHP (totalOperatingCosts-1)");

    inp.option = Module.CHPOption.StandbyRate;
    inp.percentAvgkWhElectricCostAvoidedOrStandbyRate = 9.75;
    chp = new Module.CHP(inp.annualOperatingHours, inp.annualElectricityConsumption, inp.annualThermalDemand, inp.boilerThermalFuelCosts, inp.avgElectricityCosts, inp.option, inp.boilerThermalFuelCostsCHPcase, inp.CHPfuelCosts, inp.percentAvgkWhElectricCostAvoidedOrStandbyRate, inp.displacedThermalEfficiency, inp.chpAvailability, inp.thermalUtilization);
    result = chp.getCostInfo();
    testNumberValue(result.annualOperationSavings, 3066325.0889664106, "STANDALONE CHP (annualOperationSavings-2)");
    testNumberValue(result.simplePayback, 3.8126922817, "STANDALONE CHP (simplePayback-2)");
    chp.delete();
}

// PneumaticAirRequirement
function pneumaticAirRequirement() {
    var inp = {
        pistonType: Module.PistonType.SingleActing,
        cylinderDiameter: 1.5,
        cylinderStroke: 6,
        airPressure: 100,
        cyclesPerMinute: 60
    };

    let pneumaticAirRequirement = new Module.PneumaticAirRequirement(inp.pistonType, inp.cylinderDiameter, inp.cylinderStroke, inp.airPressure, inp.cyclesPerMinute);
    let result = pneumaticAirRequirement.calculate();
    testNumberValue(result.volumeAirIntakePiston, 0.367969, "STANDALONE Pneumatic Air Requirement (volumeAirIntakePiston-1)");
    testNumberValue(result.compressionRatio, 7.802721, "STANDALONE Pneumatic Air Requirement (compressionRatio-1)");
    testNumberValue(result.airRequirementPneumaticCylinder, 2.871158, "STANDALONE CHPneumatic Air RequirementP (airRequirementPneumaticCylinder-1)");

    inp.pistonType = Module.PistonType.DoubleActing;
    inp.pistonRodDiameter = 0.375;
    pneumaticAirRequirement = new Module.PneumaticAirRequirement(inp.pistonType, inp.cylinderDiameter, inp.cylinderStroke, inp.pistonRodDiameter, inp.airPressure, inp.cyclesPerMinute);
    result = pneumaticAirRequirement.calculate();
    testNumberValue(result.volumeAirIntakePiston, 0.712939, "STANDALONE Pneumatic Air Requirement (volumeAirIntakePiston-2)");
    testNumberValue(result.compressionRatio, 7.802721, "STANDALONE Pneumatic Air Requirement (compressionRatio-2)");
    testNumberValue(result.airRequirementPneumaticCylinder, 5.562868, "STANDALONE CHPneumatic Air RequirementP (airRequirementPneumaticCylinder-2)");
    pneumaticAirRequirement.delete();
}
// usableAirCapacity
function usableAirCapacity() {
    var inp = { tankSize: 660, airPressureIn: 110, airPressureOut: 100 };

    let receiverTank = new Module.ReceiverTank();
    let result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 60.024009603, "STANDALONE Usable Air Capacity (calculateUsableCapacity-1)");

    inp = { tankSize: 760, airPressureIn: 110, airPressureOut: 100 };
    result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 69.1185565135, "STANDALONE Usable Air Capacity (calculateUsableCapacity-2)");

    inp = { tankSize: 760, airPressureIn: 150, airPressureOut: 100 };
    result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 345.5927825676, "STANDALONE Usable Air Capacity (calculateUsableCapacity-3)");

    inp = { tankSize: 760, airPressureIn: 150, airPressureOut: 130 };
    result = receiverTank.calculateUsableCapacity(inp.tankSize, inp.airPressureIn, inp.airPressureOut);
    testNumberValue(result, 138.237113027, "STANDALONE Usable Air Capacity (calculateUsableCapacity-4)");
    receiverTank.delete();
}
// Receiver Tank Size
function receiverTankSize() {
    var input = {
        method: Module.ReceiverTankMethod.General, airDemand: 150, allowablePressureDrop: 3, atmosphericPressure: 14.7
    };

    let receiverTank = new Module.ReceiverTank(input.method, input.airDemand, input.allowablePressureDrop, input.atmosphericPressure);
    let result = receiverTank.calculateSize();
    testNumberValue(result, 5497.8, "STANDALONE Receiver Tank (General-1)");

    input = {
        method: Module.ReceiverTankMethod.General, airDemand: 190, allowablePressureDrop: 8, atmosphericPressure: 12.7
    }
    receiverTank = new Module.ReceiverTank(input.method, input.airDemand, input.allowablePressureDrop, input.atmosphericPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 2256.155, "STANDALONE Receiver Tank (General-2)");

    input = {
        method: Module.ReceiverTankMethod.DedicatedStorage, lengthOfDemand: 0.5, airFlowRequirement: 100, atmosphericPressure: 14.7, initialTankPressure: 110, finalTankPressure: 100
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 549.78, "STANDALONE Receiver Tank (DedicatedStorage-1)");

    input = {
        method: Module.ReceiverTankMethod.DedicatedStorage, lengthOfDemand: 0.5, airFlowRequirement: 100, atmosphericPressure: 14.7, initialTankPressure: 110, finalTankPressure: 100
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 549.78, "STANDALONE Receiver Tank (DedicatedStorage-2)");

    input = {
        method: Module.ReceiverTankMethod.DedicatedStorage, lengthOfDemand: 1.5, airFlowRequirement: 120, atmosphericPressure: 11.7, initialTankPressure: 150, finalTankPressure: 100
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure);
    result = receiverTank.calculateSize();
    testNumberValue(result, 315.0576, "STANDALONE Receiver Tank (DedicatedStorage-3)");

    input = {
        method: Module.ReceiverTankMethod.MeteredStorage, lengthOfDemand: 0.5, airFlowRequirement: 900, atmosphericPressure: 14.7, initialTankPressure: 100, finalTankPressure: 70, meteredControl: 45
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure, input.meteredControl);
    result = receiverTank.calculateSize();
    testNumberValue(result, 1566.873, "STANDALONE Receiver Tank (MeteredStorage-1)");

    input = {
        method: Module.ReceiverTankMethod.MeteredStorage, lengthOfDemand: 1.5, airFlowRequirement: 800, atmosphericPressure: 11.7, initialTankPressure: 120, finalTankPressure: 90, meteredControl: 75
    }
    receiverTank = new Module.ReceiverTank(input.method, input.lengthOfDemand, input.airFlowRequirement, input.atmosphericPressure, input.initialTankPressure, input.finalTankPressure, input.meteredControl);
    result = receiverTank.calculateSize();
    testNumberValue(result, 3172.455, "STANDALONE Receiver Tank (MeteredStorage-2)");


    input = {
        method: Module.ReceiverTankMethod.BridgingCompressorReactionDelay, distanceToCompressorRoom: 1000, speedOfAir: 250, atmosphericPressure: 14.7, airDemand: 600, allowablePressureDrop: 2
    }
    receiverTank = new Module.ReceiverTank(input.method, input.distanceToCompressorRoom, input.speedOfAir, input.atmosphericPressure, input.airDemand, input.allowablePressureDrop);
    result = receiverTank.calculateSize();
    testNumberValue(result, 2199.12, "STANDALONE Receiver Tank (BridgingCompressorReactionDelay-1)");

    input = {
        method: Module.ReceiverTankMethod.BridgingCompressorReactionDelay, distanceToCompressorRoom: 1200, speedOfAir: 350, atmosphericPressure: 11.7, airDemand: 800, allowablePressureDrop: 19
    }
    receiverTank = new Module.ReceiverTank(input.method, input.distanceToCompressorRoom, input.speedOfAir, input.atmosphericPressure, input.airDemand, input.allowablePressureDrop);
    result = receiverTank.calculateSize();
    testNumberValue(result, 210.564812, "STANDALONE Receiver Tank (BridgingCompressorReactionDelay-2)");

    receiverTank.delete();
}
// Operating Cost
function operatingCost() {
    var inp = {
        motorBhp: 215, bhpUnloaded: 25, annualOperatingHours: 6800, runTimeLoaded: 85, efficiencyLoaded: 95,
        efficiencyUnloaded: 90, costOfElectricity: 0.05
    };

    let operatingCost = new Module.OperatingCost(inp.motorBhp, inp.bhpUnloaded, inp.annualOperatingHours, inp.runTimeLoaded, inp.efficiencyLoaded, inp.efficiencyUnloaded, inp.costOfElectricity);
    let result = operatingCost.calculate();
    testNumberValue(result.runTimeUnloaded, 15, "STANDALONE Operating Cost (runTimeUnloaded-1)");
    testNumberValue(result.costForLoaded, 48792.326316, "STANDALONE Operating Cost (costForLoaded-1)");
    testNumberValue(result.costForUnloaded, 2272.191667, "STANDALONE Operating Cost (costForUnloaded-1)");
    testNumberValue(result.totalAnnualCost, 51064.517982, "STANDALONE Operating Cost (totalAnnualCost-1)");

    inp = {
        motorBhp: 255, bhpUnloaded: 35, annualOperatingHours: 6000, runTimeLoaded: 89, efficiencyLoaded: 93,
        efficiencyUnloaded: 90, costOfElectricity: 0.09
    };
    operatingCost = new Module.OperatingCost(inp.motorBhp, inp.bhpUnloaded, inp.annualOperatingHours, inp.runTimeLoaded, inp.efficiencyLoaded, inp.efficiencyUnloaded, inp.costOfElectricity);
    result = operatingCost.calculate();
    testNumberValue(result.runTimeUnloaded, 11, "STANDALONE Operating Cost (runTimeUnloaded-2)");
    testNumberValue(result.costForLoaded, 98305.954839, "STANDALONE Operating Cost (costForLoaded-2)");
    testNumberValue(result.costForUnloaded, 4394.313, "STANDALONE Operating Cost (costForUnloaded-2)");
    testNumberValue(result.totalAnnualCost, 102700.267839, "STANDALONE Operating Cost (totalAnnualCost-2)");

    operatingCost.delete();
}
function returnDoubleVector(doublesArray)
{
    let doubleVector = new Module.DoubleVector();

    for (x of doublesArray)
    {
        doubleVector.push_back(x);
    }

    return doubleVector;
}

//airSystemCapacity
function airSystemCapacity() {
    var inp = {
        oneHalf: 3000, threeFourths: 2000, one: 1000, oneAndOneFourth: 200, oneAndOneHalf: 100, two: 500, twoAndOneHalf: 500, three: 300,
        threeAndOneHalf: 0, four: 1000, five: 0, six: 0,
        receiverCapacities: returnDoubleVector([
            400, 500, 660, 1060
        ])
    };

    let pipeData = new Module.PipeData(inp.oneHalf, inp.threeFourths, inp.one, inp.oneAndOneFourth, inp.oneAndOneHalf, inp.two, inp.twoAndOneHalf, inp.three, inp.threeAndOneHalf, inp.four, inp.five, inp.six);
    let airSystemCapacity = new Module.AirSystemCapacity(pipeData, inp.receiverCapacities);
    let result = airSystemCapacity.calculate();
    console.log(result.pipeLengths);
    let receiverCapacities = new Array();
    for(let i = 0; i < result.receiverCapacities.size(); i++){
        receiverCapacities.push(result.receiverCapacities.get(i));
    }
    testNumberValue(result.totalPipeVolume, 155.28, "STANDALONE Air System Capacity (totalPipeVolume)");
    testNumberValue(result.totalReceiverVolume, 350.26738, "STANDALONE Air System Capacity (totalReceiverVolume)");
    testNumberValue(result.totalCapacityOfCompressedAirSystem, 505.54738, "STANDALONE Air System Capacity (totalCapacityOfCompressedAirSystem)");
    testNumberValue(result.pipeLengths.oneHalf, 6.3, "STANDALONE Air System Capacity (pipeLengths.oneHalf)");
    testNumberValue(result.pipeLengths.threeFourths, 7.4, "STANDALONE Air System Capacity (pipeLengths.threeFourths)");
    testNumberValue(result.pipeLengths.one, 6, "STANDALONE Air System Capacity (pipeLengths.one)");
    testNumberValue(result.pipeLengths.oneAndOneFourth, 2.08, "STANDALONE Air System Capacity (pipeLengths.oneAndOneFourth)");
    testNumberValue(result.pipeLengths.oneAndOneHalf, 1.41, "STANDALONE Air System Capacity (pipeLengths.oneAndOneHalf)");
    testNumberValue(result.pipeLengths.two, 11.65, "STANDALONE Air System Capacity (pipeLengths.two)");
    testNumberValue(result.pipeLengths.twoAndOneHalf, 16.65, "STANDALONE Air System Capacity (pipeLengths.twoAndOneHalf)");
    testNumberValue(result.pipeLengths.three, 15.39, "STANDALONE Air System Capacity (pipeLengths.three)");
    testNumberValue(result.pipeLengths.threeAndOneHalf, 0, "STANDALONE Air System Capacity (pipeLengths.threeAndOneHalf)");
    testNumberValue(result.pipeLengths.four, 88.4, "STANDALONE Air System Capacity (pipeLengths.four)");
    testNumberValue(result.pipeLengths.five, 0, "STANDALONE Air System Capacity (pipeLengths.five)");
    testNumberValue(result.pipeLengths.six, 0, "STANDALONE Air System Capacity (pipeLengths.six)");
    testNumberValue(receiverCapacities[0], 53.475936, "STANDALONE Air System Capacity (receiverCapacities-1)");
    testNumberValue(receiverCapacities[1], 66.84492, "STANDALONE Air System Capacity (receiverCapacities-2)");
    testNumberValue(receiverCapacities[2], 88.235294, "STANDALONE Air System Capacity (receiverCapacities-3)");
    testNumberValue(receiverCapacities[3], 141.71123, "STANDALONE Air System Capacity (receiverCapacities-4)");
    pipeData.delete();
    airSystemCapacity.delete();
}
//airVelocity
function airVelocity() {
    var inp = {
        airFlow: 1800, pipePressure: 100, atmosphericPressure: 14.7
    };

    let airVelocity = new Module.AirVelocity(inp.airFlow, inp.pipePressure, inp.atmosphericPressure);

    let result = airVelocity.calculate();
    testNumberValue(result.oneHalf, 1845.510026, "STANDALONE Air Velocity (oneHalf)");
    testNumberValue(result.threeFourths, 1044.628317, "STANDALONE Air Velocity (threeFourths)");
    testNumberValue(result.one, 643.782567, "STANDALON Air Velocity (one)");
    testNumberValue(result.oneAndOneFourth, 369.102005, "STANDALONE Air Velocity (oneAndOneFourth)");
    testNumberValue(result.oneAndOneHalf, 271.398533, "STANDALONE Air Velocity (oneAndOneHalf)");
    testNumberValue(result.two, 164.777681, "STANDALONE Air Velocity (two)");
    testNumberValue(result.twoAndOneHalf, 115.585179, "STANDALONE Air Velocity (twoAndOneHalf)");
    testNumberValue(result.three, 74.919216, "STANDALONE Air Velocity (three)");
    testNumberValue(result.threeAndOneHalf, 55.981093, "STANDALONE Air Velocity (threeAndOneHalf)");
    testNumberValue(result.four, 43.491988, "STANDALONE Air Velocity (four)");
    testNumberValue(result.five, 27.68265, "STANDALONE Air Velocity (five)");
    testNumberValue(result.six, 19.164175, "STANDALONE Air Velocity (six)");
    airVelocity.delete();
}
// Pipe Sizing
function pipeSizing() {
    var inp = {
        airFlow: 1000, airlinePressure: 90, designVelocity: 25, atmosphericPressure: 14.5
    };

    let pipeSizing = new Module.PipeSizing(inp.airFlow, inp.airlinePressure, inp.designVelocity, inp.atmosphericPressure);
    let result = pipeSizing.calculate();
    testNumberValue(result.crossSectionalArea, 13.320574, "STANDALONE Air Velocity (crossSectionalArea)");
    testNumberValue(result.pipeDiameter, 4.132512, "STANDALONE Air Velocity (pipeDiameter)");

    inp = {
        airFlow: 1400, airlinePressure: 110, designVelocity: 30, atmosphericPressure: 11.5
    };
    pipeSizing = new Module.PipeSizing(inp.airFlow, inp.airlinePressure, inp.designVelocity, inp.atmosphericPressure);
    result = pipeSizing.calculate();
    testNumberValue(result.crossSectionalArea, 10.600823, "STANDALONE Air Velocity (crossSectionalArea)");
    testNumberValue(result.pipeDiameter, 3.68657, "STANDALONE Air Velocity (pipeDiameter)");
    pipeSizing.delete();
}
// Pneumatic Valve
function pneumaticValve() {
    var inp = { inletPressure: 100, outletPressure: 70 }

    let pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure);
    let result = pneumaticValve.calculate();
    testNumberValue(result, 49.09732, "STANDALONE Pneumatic Valve (calculate-1)");

    inp = { inletPressure: 120, outletPressure: 90 };
    pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure);
    result = pneumaticValve.calculate();
    testNumberValue(result, 54.568621, "STANDALONE Pneumatic Valve (calculate-2)");

    inp = { inletPressure: 80, outletPressure: 75, flowRate: 55 };
    pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure, inp.flowRate);
    result = pneumaticValve.calculate();
    testNumberValue(result, 2.873685, "STANDALONE Pneumatic Valve (calculate-3)");

    inp = { inletPressure: 90, outletPressure: 85, flowRate: 95 };
    pneumaticValve = new Module.PneumaticValve(inp.inletPressure, inp.outletPressure, inp.flowRate);
    result = pneumaticValve.calculate();
    testNumberValue(result, 4.671398, "STANDALONE Pneumatic Valve (calculate-4)");
    pneumaticValve.delete();
}
// Bag Method
function bagMethod() {
    var inp = { operatingTime: 115200 / 60.0, bagFillTime: 25, heightOfBag: 10, diameterOfBag: 10, numberOfUnits: 1 }

    let bagMethod = new Module.BagMethod(inp.operatingTime, inp.bagFillTime, inp.heightOfBag, inp.diameterOfBag, inp.numberOfUnits);
    let result = bagMethod.calculate();
    testNumberValue(result.flowRate, 1.092, "STANDALONE Bag Method (flowRate-1)");
    testNumberValue(result.annualConsumption, 125.7984, "STANDALONE Bag Method (annualConsumption-1)");

    inp = { operatingTime: 100000 / 60.0, bagFillTime: 20, heightOfBag: 10, diameterOfBag: 10, numberOfUnits: 1 };
    bagMethod = new Module.BagMethod(inp.operatingTime, inp.bagFillTime, inp.heightOfBag, inp.diameterOfBag, inp.numberOfUnits);
    result = bagMethod.calculate();
    testNumberValue(result.flowRate, 1.365, "STANDALONE Bag Method (flowRate-2)");
    testNumberValue(result.annualConsumption, 136.5, "STANDALONE Bag Method (annualConsumption-2)");
    bagMethod.delete();
}

CHP();
pneumaticAirRequirement();
usableAirCapacity();
receiverTankSize();
operatingCost();
airSystemCapacity();
airVelocity();
pipeSizing();
pneumaticValve();
bagMethod();