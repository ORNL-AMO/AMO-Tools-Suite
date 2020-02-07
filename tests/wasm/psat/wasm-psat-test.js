function pumpShaftPowerTest() {
    let instance = new Module.PumpShaftPower(50, Module.Drive.N_V_BELT_DRIVE, 0);
    let pumpShaftPower = instance.calculate().pumpShaftPower;
    testNumberValue(pumpShaftPower, 48.4814329723, 'Pump Shaft Power');
}

function achievableEfficiency(){
    let pumpStyle = Module.PumpStyle.END_SUCTION_SLURRY;
    let specificSpeed = 1170;
    let instance = new Module.OptimalSpecificSpeedCorrection(pumpStyle, specificSpeed);
    let achievableEfficiency = instance.calculate() * 100;
    testNumberValue(achievableEfficiency, 1.8942771852074485, 'Achievable Pump Efficiency');
}

function headToolSuctionTank(){
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
    
    console.log(results);
    testNumberValue(results.pumpHead, 22.972865551821844, 'Head Tool Suction Tank 1 (pumpHead)');
    testNumberValue(results.differentialElevationHead, 0.0, 'Head Tool Suction Tank 1 (differentialElevationHead)');
    testNumberValue(results.differentialPressureHead, 20.797226988336853, 'Head Tool Suction Tank 1 (differentialPressureHead)');
    testNumberValue(results.differentialVelocityHead, 1.0372994352935365, 'Head Tool Suction Tank 1 (differentialVelocityHead)');
    testNumberValue(results.estimatedDischargeFrictionHead, 1.0372994352935365, 'Head Tool Suction Tank 1 (estimatedDischargeFrictionHead)');
    testNumberValue(results.estimatedSuctionFrictionHead, 0.10103969289791588, 'Head Tool Suction Tank 1 (estimatedSuctionFrictionHead)');
}

//execute tests
pumpShaftPowerTest();
achievableEfficiency();
headToolSuctionTank();

