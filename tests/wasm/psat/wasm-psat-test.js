function pumpShaftPowerTest() {
    let instance = new Module.PumpShaftPower(50, Module.Drive.N_V_BELT_DRIVE, 0);
    let pumpShaftPower = instance.calculate().pumpShaftPower;
    testNumberValue(pumpShaftPower, 48.4814329723, 'Pump Shaft Power');
}
//tests
pumpShaftPowerTest();

