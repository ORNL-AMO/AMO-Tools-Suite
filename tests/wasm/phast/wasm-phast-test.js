function atmosphere() {
    var inletTemperature = 100.0
    var outletTemperature = 1400.0;
    var flowRate = 1200.0;
    var correctionFactor = 1.0;
    var specificHeat = 0.02;

    let atmosphere = new Module.Atmosphere(inletTemperature, outletTemperature, flowRate, correctionFactor, specificHeat);
    let result = atmosphere.getTotalHeat();
    testNumberValue(result, 31200.0, "PHAST Atmosphere (atmosphere)");
    atmosphere.delete();
}

function auxiliaryPowerLoss() {
    var motorPhase = 3;
    var supplyVoltage = 460;
    var avgCurrent = 19;
    var powerFactor = 0.85;
    var operatingTime = 100;

    var auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    var powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 43905.3405494047, "PHAST AuxiliaryPower 1 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();


    supplyVoltage = 510;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();

    testNumberValue(powerUsed, 48677.66017434, "PHAST AuxiliaryPower 2 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();

    avgCurrent = 25;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 64049.5528609737, "PHAST AuxiliaryPower 3 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();


    powerFactor = 0.55;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 41443.8283218065, "PHAST AuxiliaryPower 4 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();

    operatingTime = 75;
    auxiliaryPowerLoss = new Module.AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);
    powerUsed = auxiliaryPowerLoss.getPowerUsed();
    testNumberValue(powerUsed, 31082.8712413549, "PHAST AuxiliaryPower 5 (auxiliaryPowerLoss)");
    auxiliaryPowerLoss.delete();
}

function fixtureLosses() {
    var specificHeat = 0.122;
    var feedRate = 1250.0;
    var initialTemperature = 300.0;
    var finalTemperature = 1800.0;
    var correctionFactor = 1.0;

    var fixtureLosses = new Module.FixtureLosses(specificHeat, feedRate, initialTemperature, finalTemperature, correctionFactor);
    var heatLoss = fixtureLosses.getHeatLoss();
    fixtureLosses.delete();
    testNumberValue(heatLoss, 228750.0, "PHAST FixtureLosses (fixtureLosses)");
}

function energyInputEAF() {
    var naturalGasHeatInput = 50;
    var coalCarbonInjection = 3300;
    var coalHeatingValue = 9000;
    var electrodeUse = 500;
    var electrodeHeatingValue = 12000;
    var otherFuels = 20;
    var electricityInput = 18000;
    var energyInputEAF = new Module.EnergyInputEAF(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse, electrodeHeatingValue, otherFuels, electricityInput);
    var heatDelivered = energyInputEAF.getHeatDelivered();
    var totalChemicalEnergyInput = energyInputEAF.getTotalChemicalEnergyInput();
    energyInputEAF.delete();
    testNumberValue(heatDelivered, 167116000.0, "PHAST Energy Input EAF (heatDelivered)");
    testNumberValue(totalChemicalEnergyInput, 105700000, "PHAST Energy Input EAF (totalChemicalEnergyInput)");
}

function energyInputExhaustGasLosses() {
    var totalHeatInput = 5000000;
    var excessAir = 65;
    var combustionAirTemp = 300;
    var exhaustGasTemp = 550;

    var enInputExhaustGasLosses = new Module.EnergyInputExhaustGasLosses(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);
    var heatDelivered = enInputExhaustGasLosses.getHeatDelivered();
    var exhaustGasLosses = enInputExhaustGasLosses.getExhaustGasLosses();
    var availableHeat = enInputExhaustGasLosses.getAvailableHeat();
    enInputExhaustGasLosses.delete();

    testNumberValue(heatDelivered, 4136397.1199000007, "PHAST Energy Input Ex. Gas Losses (heatDelivered)");
    testNumberValue(exhaustGasLosses, 863602.8800999995, "PHAST Energy Input Ex. Gas Losses (exhaustGasLosses)");
    testNumberValue(availableHeat, 82.727942, "PHAST Energy Input Ex. Gas Losses (availableHeat)");
}

function exhaustGasEAF() {
    var offGasTemp = 2800;
    var CO = 12;
    var H2 = 10;
    var combustibleGases = 3;
    var vfr = 8000;
    var dustLoading = 0.001;

    var exGasEAF = new Module.ExhaustGasEAF(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading);
    var totalHeatExhaust = exGasEAF.getTotalHeatExhaust();
    exGasEAF.delete();
    testNumberValue(totalHeatExhaust, 12553119.018404908, "PHAST Exhaust Gas EAF (totalHeatExhaust)");
}

atmosphere();
auxiliaryPowerLoss();
fixtureLosses();
energyInputEAF();
energyInputExhaustGasLosses();
exhaustGasEAF();