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

function auxiliaryPowerLoss(){
    var motorPhase = 3;
    var supplyVoltage = 460;
    var avgCurrent = 19; 
    var powerFactor= 0.85; 
    var operatingTime= 100;

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

atmosphere();
auxiliaryPowerLoss();