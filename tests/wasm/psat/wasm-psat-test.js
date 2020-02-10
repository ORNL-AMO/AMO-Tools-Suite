function pumpShaftPowerTest() {
    let instance = new Module.PumpShaftPower(50, Module.Drive.N_V_BELT_DRIVE, 0);
    let pumpShaftPower = instance.calculate().pumpShaftPower;
    instance.delete();
    testNumberValue(pumpShaftPower, 48.4814329723, 'Pump Shaft Power');
}

function achievableEfficiency() {
    let pumpStyle = Module.PumpStyle.END_SUCTION_SLURRY;
    let specificSpeed = 1170;
    let instance = new Module.OptimalSpecificSpeedCorrection(pumpStyle, specificSpeed);
    let achievableEfficiency = instance.calculate() * 100;
    instance.delete();
    testNumberValue(achievableEfficiency, 1.8942771852074485, 'Achievable Pump Efficiency');
}

function headToolSuctionTank() {
    let specificGravity = 1.0;
    let flowRate = 2000;
    let suctionPipeDiameter = 17.9;
    let suctionTankGasOverPressure = 115;
    let suctionTankFluidSurfaceElevation = 0;
    let suctionLineLossCoefficients = 1;
    let dischargePipeDiameter = 10;
    let dischargeGaugePressure = 124;
    let dischargeGaugeElevation = 0;
    let dischargeLineLossCoefficients = 1;
    let instance = new Module.HeadToolSuctionTank(specificGravity, flowRate, suctionPipeDiameter, suctionTankGasOverPressure, suctionTankFluidSurfaceElevation, suctionLineLossCoefficients, dischargePipeDiameter, dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);
    let results = instance.calculate();
    instance.delete();

    testNumberValue(results.pumpHead, 22.972865551821844, 'Head Tool Suction Tank (pumpHead)');
    testNumberValue(results.differentialElevationHead, 0.0, 'Head Tool Suction Tank (differentialElevationHead)');
    testNumberValue(results.differentialPressureHead, 20.797226988336853, 'Head Tool Suction Tank (differentialPressureHead)');
    testNumberValue(results.differentialVelocityHead, 1.0372994352935365, 'Head Tool Suction Tank (differentialVelocityHead)');
    testNumberValue(results.estimatedDischargeFrictionHead, 1.0372994352935365, 'Head Tool Suction Tank (estimatedDischargeFrictionHead)');
    testNumberValue(results.estimatedSuctionFrictionHead, 0.10103969289791588, 'Head Tool Suction Tank (estimatedSuctionFrictionHead)');
}

function headTool() {
    let specificGravity = 1.0;
    let flowRate = 2000;
    let suctionPipeDiameter = 17.9;
    let suctionGaugePressure = 5;
    let suctionGaugeElevation = 5;
    let suctionLineLossCoefficients = 1;
    let dischargePipeDiameter = 15;
    let dischargeGaugePressure = 50;
    let dischargeGaugeElevation = 1;
    let dischargeLineLossCoefficients = 1;
    let instance = new Module.HeadTool(specificGravity, flowRate, suctionPipeDiameter, suctionGaugePressure,
        suctionGaugeElevation, suctionLineLossCoefficients, dischargePipeDiameter,
        dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);
    let results = instance.calculate();
    instance.delete();

    testNumberValue(results.pumpHead, 100.39593224945455,  'Head Tool (pumpHead)');
    testNumberValue(results.differentialElevationHead, -4, 'Head Tool (differentialElevationHead)');
    testNumberValue(results.differentialPressureHead, 103.98613494168427, 'Head Tool (differentialPressureHead)');
    testNumberValue(results.differentialVelocityHead, 0.10385896098722718, 'Head Tool (differentialVelocityHead)');
    testNumberValue(results.estimatedDischargeFrictionHead, 0.20489865388514306, 'Head Tool (estimatedDischargeFrictionHead)');
    testNumberValue(results.estimatedSuctionFrictionHead, 0.10103969289791588, 'Head Tool (estimatedSuctionFrictionHead)');
}

//execute tests
pumpShaftPowerTest();
achievableEfficiency();
headToolSuctionTank();
headTool();

