function nemaTest() {
    let lineFrequency = Module.LineFrequency.FREQ60;
    let motorRatedSpeed = 1200;
    let efficiencyClass = Module.MotorEfficiencyClass.ENERGY_EFFICIENT;
    let efficiency = 0;
    let motorRatedPower = 200;
    let loadFactor = 1;
    let instance = new Module.MotorEfficiency(lineFrequency, motorRatedSpeed, efficiencyClass, motorRatedPower);
    let motorEfficiency = instance.calculate(loadFactor, efficiency) * 100;
    instance.delete();
    testNumberValue(motorEfficiency, 95.33208465291122, 'Nema (Motor Efficiency * 100)');
}

function estFla() {
    let motorRatedPower = 200;
    let motorRPM = 1780;
    let lineFrequency = Module.LineFrequency.FREQ50;
    // Either specify an efficiency class OR provide efficiency percentage
    let efficiencyClass = Module.MotorEfficiencyClass.ENERGY_EFFICIENT;
    let specifiedEfficiency = 0;
    let ratedVoltage = 460;
    let instance = new Module.EstimateFLA(motorRatedPower, motorRPM, lineFrequency, efficiencyClass, specifiedEfficiency, ratedVoltage);
    let estimatedFLA = instance.getEstimatedFLA();
    instance.delete();
    testNumberValue(estimatedFLA, 225.800612262395, 'EstimateFLA')
}

//test calls
nemaTest();
estFla();
