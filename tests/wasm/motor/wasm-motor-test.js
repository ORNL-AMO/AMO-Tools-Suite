function nemaTest() {
    let lineFrequency = Module.LineFrequency.FREQ60;
    let motorRatedSpeed = 1200;
    let efficiencyClass = Module.EfficiencyClass.ENERGY_EFFICIENT;
    let efficiency = 0;
    let motorRatedPower = 200;
    let loadFactor = 1;
    let instance = new Module.MotorEfficiency(lineFrequency, motorRatedSpeed, efficiencyClass, motorRatedPower);
    let motorEfficiency = instance.calculate(loadFactor, efficiency) * 100;
    testNumberValue(motorEfficiency, 95.33208465291122, 'Nema (Motor Efficiency * 100)');
}
//tests
nemaTest();

