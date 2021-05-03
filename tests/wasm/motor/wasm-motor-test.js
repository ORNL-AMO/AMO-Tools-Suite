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

function motorPerformance(){
    // Line frequency 60
    let lineFrequency = Module.LineFrequency.FREQ60;
    // Energy efficient
    let motorEfficiencyClass = Module.MotorEfficiencyClass.ENERGY_EFFICIENT;
    let motorRatedPower = 200;
    let motorRPM = 1780;
    let specifiedEfficiency = 0;
    let loadFactor = .25;
    let motorRatedVoltage = 460;
    let fullLoadAmps = 225.8;

    //Implementation after adding MotoerPerformance.h/MotorPerformance.cpp
    let instance = new Module.MotorPerformance(lineFrequency, motorRPM, motorEfficiencyClass, motorRatedPower, specifiedEfficiency, loadFactor, motorRatedVoltage, fullLoadAmps);
    let calculatedResults = instance.calculate();
    instance.delete();

    //Implementation without addtional MotorPerformance definitio
    //MotorEfficiency
    // let motorEfficiency = new Module.MotorEfficiency(lineFrequency, motorRPM, motorEfficiencyClass, motorRatedPower);
    // let calculatedMotorEfficiency = motorEfficiency.calculate(loadFactor, motorEfficiencyInput)
    // let convertedMotorEfficiency = calculatedMotorEfficiency * 100;
    // //Motor Current
    // let motorCurrent = new Module.MotorCurrent(motorRatedPower, motorRPM, lineFrequency, motorEfficiencyClass, motorEfficiencyInput, loadFactor, motorRatedVoltage);
    // let calculatedCurrent = motorCurrent.calculateCurrent(fullLoadAmps);
    // let convertedCurrent = calculatedCurrent / fullLoadAmps * 100;
    // //Motor Power Factor
    // let motorPowerFactor = new Module.MotorPowerFactor(motorRatedPower, loadFactor, calculatedCurrent, calculatedMotorEfficiency, motorRatedVoltage);
    // let convertedPowerFactor = motorPowerFactor.calculate() * 100;
    testNumberValue(calculatedResults.current, 36.1065805345533, "Motor Performance (current)");
    testNumberValue(calculatedResults.efficiency, 93.03933838910918, "Motor Performance (efficiency)");
    testNumberValue(calculatedResults.powerFactor, 61.718229798145316, "Motor Performance (powerFactor)");
}

//test calls
nemaTest();
estFla();
motorPerformance();
