
//ID: 737 Lubricant injected screw modulation with unloading
function compId737() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 1167,
        capacityAtMaxFullFlow: 1167,
        capacityAtUnload: 584,
        compressorType: Module.CompressorType.Screw,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: Module.ControlType.ModulationUnload,
        dischargePsiFullLoad: 140,
        dischargePsiMax: 140,
        loadFactorUnloaded: 0.20529197080291972,
        lubricantType: Module.Lubricant.Injected,
        modulatingPsi: 20,
        noLoadPowerFM: 0.65,
        powerAtFullLoad: 219.2,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 45,
        powerAtNolLoad: 45,
        powerAtUnload: 180.9,
        powerMax: 219.2,
        powerMaxPercentage: 1,
        pressureAtUnload: 150,
        receiverVolume: 13,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 50,
        unloadSumpPressure: 15
    }

    //9% AIRFLOW
    input.computeFromVal = .09;
    // 1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    //    t.equal(rnd(results.percentagePower), rnd(63));
    //    t.equal(rnd(results.powerCalculated), rnd(137));
    testNumberValue(rnd(results.PerkW), rnd(62.69), "compressorCalc 737: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(137.41), "compressorCalc 737: kW_Calc 1");
    //POWER CALCULATED SLIGHTLY DIFFERENT FOR %POWER CALC VS %CAPACITY

    input.computeFromVal = .63;
    // 0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    //    t.equal(rnd(results.percentageCapacity), rnd(9));
    //    t.equal(rnd(results.powerCalculated), rnd(138));
    testNumberValue(rnd(results.C_Per), rnd(8.73), "compressorCalc 737: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(138.1), "compressorCalc 737: kW_Calc 2");
    //POWER CALCULATED SLIGHTLY DIFFERENT FOR %POWER CALC VS %CAPACITY

    //91% AIRFLOW
    input.computeFromVal = .91;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    //    t.equal(rnd(results.percentagePower), rnd(96.7));
    //    t.equal(rnd(results.powerCalculated), rnd(212.04));
    testNumberValue(rnd(results.PerkW), rnd(96.85), "compressorCalc 737: PerkW 3");
    testNumberValue(rnd(results.kW_Calc), rnd(212.3), "compressorCalc 737: kW_Calc 3");

    input.computeFromVal = .967;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    //    t.equal(rnd(results.percentageCapacity), rnd(91));
    //    t.equal(rnd(results.powerCalculated), rnd(212.04));
    testNumberValue(rnd(results.C_Per), rnd(90.57), "compressorCalc 737: C_Per 3");
    testNumberValue(rnd(results.kW_Calc), rnd(211.97), "compressorCalc 737: kW_Calc 3");
}
//ID: 701 Lubricant injected screw modulation without unloading
function compId701() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 1048,
        capacityAtMaxFullFlow: undefined,
        capacityAtUnload: undefined,
        compressorType: Module.CompressorType.Screw,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: Module.ControlType.ModulationWOUnload,
        dischargePsiFullLoad: 100,
        dischargePsiMax: undefined,
        loadFactorUnloaded: 0.6498498498498498,
        lubricantType: Module.Lubricant.Injected,
        modulatingPsi: 5,
        noLoadPowerFM: 0.65,
        powerAtFullLoad: 166.5,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 108.2,
        powerAtNolLoad: 108.2,
        powerAtUnload: undefined,
        powerMax: 0,
        powerMaxPercentage: NaN,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 50,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .20;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(72.01));
    // t.equal(rnd(results.powerCalculated), rnd(119.9));
    testNumberValue(rnd(results.PerkW), rnd(71.99), "compressorCalc 701: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(119.86), "compressorCalc 701: kW_Calc 1");

    input.computeFromVal = .7201;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(20));
    // t.equal(rnd(results.powerCalculated), rnd(119.9));
    testNumberValue(rnd(results.C_Per), rnd(20.06), "compressorCalc 701: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(119.9), "compressorCalc 701: kW_Calc 2");
}
//ID: 728 Lubricant injected screw variable displacement
function compId728() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 1390,
        capacityAtMaxFullFlow: 1390,
        capacityAtUnload: 556,
        compressorType: Module.CompressorType.Screw,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: Module.ControlType.VariableDisplacementUnload,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 100,
        loadFactorUnloaded: 0.205,
        lubricantType: Module.Lubricant.Injected,
        modulatingPsi: 17,
        noLoadPowerFM: 0.57,
        powerAtFullLoad: 219.2,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 45,
        powerAtNolLoad: 45,
        powerAtUnload: 140,
        powerMax: 219.2,
        powerMaxPercentage: 1,
        pressureAtUnload: 110,
        receiverVolume: 13.4,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 40,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .09;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerKW = results.PerKW * 100;
    // t.equal(rnd(results.percentagePower), rnd(57), "% Power 1");
    // t.equal(rnd(results.powerCalculated), rnd(125), "Power Calculated 1");
    testNumberValue(rnd(results.PerKW), rnd(57), "compressorCalc 728: PerKW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(125), "compressorCalc 728: kW_Calc 1");

    input.computeFromVal = .57;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    // t.equal(rnd(results.powerCalculated), rnd(125), "Power Calculated 2");
    testNumberValue(rnd(results.C_Per), rnd(10), "compressorCalc 728: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(125), "compressorCalc 728: kW_Calc 2");


    input.computeFromVal = .92;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerKW = results.PerKW * 100;
    // t.equal(rnd(results.percentagePower), rnd(93), "% Power 2");
    // t.equal(rnd(results.powerCalculated), rnd(204.72), "Power Calculated 3");
    testNumberValue(rnd(results.PerKW), rnd(93), "compressorCalc 728: PerKW 3");
    testNumberValue(rnd(results.kW_Calc), rnd(204.71), "compressorCalc 728: kW_Calc 3");

    input.computeFromVal = .937;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(92), "% Capacity 2");
    // t.equal(rnd(results.powerCalculated), rnd(204.72), "Power Calculated 4");
    testNumberValue(rnd(results.C_Per), rnd(92), "compressorCalc 728: C_Per 4");
    testNumberValue(rnd(results.kW_Calc), rnd(204.72), "compressorCalc 728: kW_Calc 4");
}
//ID: 629 Lubricant inject screw load/unload
function compId629LoadUnload() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 1390,
        capacityAtMaxFullFlow: 1390,
        capacityAtUnload: 556,
        compressorType: Module.CompressorType.Screw,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: Module.ControlType.LoadUnload,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 100,
        loadFactorUnloaded: 0.205,
        lubricantType: Module.Lubricant.Injected,
        modulatingPsi: 17,
        noLoadPowerFM: 0.57,
        powerAtFullLoad: 219.2,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 45,
        powerAtNolLoad: 45,
        powerAtUnload: 140,
        powerMax: 219.2,
        powerMaxPercentage: 1,
        pressureAtUnload: 110,
        receiverVolume: 13.4,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 40,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .09;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerKW = results.PerKW * 100;
    // t.equal(rnd(results.percentagePower), rnd(57), "% Power 1");
    // t.equal(rnd(results.powerCalculated), rnd(125), "Power Calculated 1");
    testNumberValue(rnd(results.PerKW), rnd(57), "compressorCalc 629 LoadUnload: PerKW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(125), "compressorCalc 629 LoadUnload: kW_Calc 1");

    input.computeFromVal = .57;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    // t.equal(rnd(results.powerCalculated), rnd(125), "Power Calculated 2");
    testNumberValue(rnd(results.C_Per), rnd(10), "compressorCalc 629 LoadUnload: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(125), "compressorCalc 629 LoadUnload: kW_Calc 2");


    input.computeFromVal = .92;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerKW = results.PerKW * 100;
    // t.equal(rnd(results.percentagePower), rnd(93), "% Power 2");
    // t.equal(rnd(results.powerCalculated), rnd(204.72), "Power Calculated 3");
    testNumberValue(rnd(results.PerKW), rnd(93), "compressorCalc 629 LoadUnload: PerKW 3");
    testNumberValue(rnd(results.kW_Calc), rnd(204.72), "compressorCalc 629 LoadUnload: kW_Calc 3");

    input.computeFromVal = .937;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(92), "% Capacity 4");
    // t.equal(rnd(results.powerCalculated), rnd(204.72), "Power Calculated 4");
    testNumberValue(rnd(results.C_Per), rnd(92), "compressorCalc 629 LoadUnload: C_Per 4");
    testNumberValue(rnd(results.kW_Calc), rnd(204.72), "compressorCalc 629 LoadUnload: kW_Calc 4");
}
//ID: 629 Lubricant injected screw start/stop
function compId629StartStop() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 535,
        capacityAtMaxFullFlow: 531,
        capacityAtUnload: undefined,
        compressorType: Module.CompressorType.Screw,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.97,
        controlType: Module.ControlType.StartStop,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 110,
        loadFactorUnloaded: 0,
        lubricantType: Module.Lubricant.Injected,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 85.4,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 90.1,
        powerMaxPercentage: 1.0550351288056206,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: Module.Stage.Single,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    }


    input.computeFromVal = .35;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(35.95), "% Power 1");
    // t.equal(rnd(results.powerCalculated), rnd(30.7), "Power Calculated 1");
    testNumberValue(rnd(results.PerkW), rnd(35.96), "compressorCalc 629 Start/Stop: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(30.71), "compressorCalc 629 Start/Stop: kW_Calc 1");

    input.computeFromVal = .3595;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(35), "% Capacity 1");
    // t.equal(rnd(results.powerCalculated), rnd(30.7), "Power Calculated 2");
    testNumberValue(rnd(results.C_Per), rnd(34.99), "compressorCalc 629 Start/Stop: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(30.7), "compressorCalc 629 Start/Stop: kW_Calc 2");
}
//ID: 861 Lubricant free screw Load/Unload
function compId861LoadUnload() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 40,
        capacityAtFullLoad: 535,
        capacityAtMaxFullFlow: 531,
        capacityAtUnload: undefined,
        compressorType: Module.CompressorType.Screw,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: Module.ControlType.LoadUnload,
        dischargePsiFullLoad: 100,
        dischargePsiMax: 110,
        loadFactorUnloaded: 0,
        lubricantType: Module.Lubricant.Free,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 85.4,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 90.1,
        powerMaxPercentage: 1.0550351288056206,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .35;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(35.95));
    // t.equal(rnd(results.powerCalculated), rnd(30.7));
    testNumberValue(rnd(results.PerkW), rnd(35.96), "compressorCalc 861 Load/Unload: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(30.71), "compressorCalc 861 Load/Unload: kW_Calc 1");


    input.computeFromVal = .3595;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(35));
    // t.equal(rnd(results.powerCalculated), rnd(30.7));
    testNumberValue(rnd(results.C_Per), rnd(34.99), "compressorCalc 861 Load/Unload: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(30.7), "compressorCalc 861 Load/Unload: kW_Calc 2");

}
//ID: 861 Lubricant free start/stop
function compId861StartStop() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: 0.0003,
        capacityAtFullLoad: 231,
        capacityAtMaxFullFlow: 229,
        capacityAtUnload: undefined,
        compressorType: Module.CompressorType.Screw,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.99,
        controlType: Module.ControlType.StartStop,
        dischargePsiFullLoad: 115,
        dischargePsiMax: 125,
        loadFactorUnloaded: 0,
        lubricantType: Module.Lubricant.Free,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 51.3,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 53.7,
        powerMaxPercentage: 1.0467836257309944,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 100,
        unloadSumpPressure: 15
    }

    input.computeFromVal = .65;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    //Test doc has 66.47 % Power...
    // t.equal(rnd(results.percentagePower), rnd(67), "% Power 1");
    // t.equal(rnd(results.powerCalculated), rnd(34.1), "Power Calculated 1");
    testNumberValue(rnd(results.PerkW), rnd(66.52), "compressorCalc 861 StartStop: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(34.13), "compressorCalc 861 StartStop: kW_Calc 1");

    input.computeFromVal = .6647;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(65), "% Capacity 1");
    // t.equal(rnd(results.powerCalculated), rnd(34.1), "Power Calculated 2");
    testNumberValue(rnd(results.C_Per), rnd(64.95), "compressorCalc 861 StartStop: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(34.1), "compressorCalc 861 StartStop: kW_Calc 2");
}
//ID: 1156 Reciprocating Load/Unload
function compId1156LoadUnload() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: null,
        capacityAtFullLoad: 375,
        capacityAtMaxFullFlow: 372,
        capacityAtUnload: undefined,
        compressorType: Module.CompressorType.Reciprocating,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.99,
        controlType: Module.ControlType.LoadUnload,
        dischargePsiFullLoad: 125,
        dischargePsiMax: 135,
        loadFactorUnloaded: 0.15968992248062017,
        lubricantType: Module.Lubricant.None,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 64.5,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 10.3,
        powerAtNolLoad: 10.3,
        powerAtUnload: undefined,
        powerMax: 67.6,
        powerMaxPercentage: 1.0480620155038758,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 100,
        unloadSumpPressure: null
    }

    input.computeFromVal = .10;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(24.5), "% Power 1");
    // t.equal(rnd(results.powerCalculated), rnd(15.8), "Power Calculated 1");
    testNumberValue(rnd(results.PerkW), rnd(24.5), "compressorCalc 1156 LoadUnload: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(15.8), "compressorCalc 1156 LoadUnload: kW_Calc 1");

    input.computeFromVal = .245;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    // t.equal(rnd(results.powerCalculated), rnd(15.8), "Power Calculated 2");
    testNumberValue(rnd(results.C_Per), rnd(10), "compressorCalc 1156 LoadUnload: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(15.8), "compressorCalc 1156 LoadUnload: kW_Calc 2");

    input.computeFromVal = .90;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(94), "% Power 2");
    // t.equal(rnd(results.powerCalculated), rnd(60.3), "Power Calculated 3");
    testNumberValue(rnd(results.PerkW), rnd(94), "compressorCalc 1156 LoadUnload: PerkW 3");
    testNumberValue(rnd(results.kW_Calc), rnd(60.3), "compressorCalc 1156 LoadUnload: kW_Calc 3");
    //Test doc has 93.49% power...

    input.computeFromVal = .9349;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(90), "% Capacity 3");
    // t.equal(rnd(results.powerCalculated), rnd(60.3), "Power Calculated 4");
    testNumberValue(rnd(results.C_Per), rnd(90), "compressorCalc 1156 LoadUnload: C_Per 4");
    testNumberValue(rnd(results.kW_Calc), rnd(60.3), "compressorCalc 1156 LoadUnload: kW_Calc 4");
}

//ID: 1156 Reciprocating Start/stop
function compId1156StartStop() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: null,
        capacityAtFullLoad: 375,
        capacityAtMaxFullFlow: 372,
        capacityAtUnload: undefined,
        compressorType: Module.CompressorType.Reciprocating,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.99,
        controlType: Module.ControlType.StartStop,
        dischargePsiFullLoad: 125,
        dischargePsiMax: 135,
        loadFactorUnloaded: 0,
        lubricantType: Module.Lubricant.None,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 64.5,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 0,
        powerAtNolLoad: 0,
        powerAtUnload: undefined,
        powerMax: 67.6,
        powerMaxPercentage: 1.0480620155038758,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 100,
        unloadSumpPressure: null
    }
    input.computeFromVal = .35;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(35.66), "% Power 1");
    // t.equal(rnd(results.powerCalculated), rnd(23), "Power Calculated 1");
    testNumberValue(rnd(results.PerkW), rnd(35.84), "compressorCalc 1156 StartStop: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(23.12), "compressorCalc 1156 StartStop: kW_Calc 1");

    input.computeFromVal = .3566;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(35), "% Capacity");
    // t.equal(rnd(results.powerCalculated), rnd(23), "Power Calculated 2");
    testNumberValue(rnd(results.C_Per), rnd(34.82), "compressorCalc 1156 StartStop: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(23), "compressorCalc 1156 StartStop: kW_Calc 2");
}
//ID: 1187 Reciprocating multi-step unloadin
function compId1187() {
    var input = {
        adjustForDischargePressure: false,
        applyPressureInletCorrection: false,
        atmosphericPsi: 14.7,
        blowdownTime: null,
        capacityAtFullLoad: 660,
        capacityAtMaxFullFlow: 655,
        capacityAtUnload: undefined,
        compressorType: Module.CompressorType.Reciprocating,
        computeFrom: Module.ComputeFrom.PercentageCapacity,
        computeFromPFAmps: 0,
        computeFromPFVoltage: 0,
        computeFromVal: 0.995,
        controlType: Module.ControlType.MultiStepUnloading,
        dischargePsiFullLoad: 115,
        dischargePsiMax: 125,
        loadFactorUnloaded: 0.15838800374882847,
        lubricantType: Module.Lubricant.None,
        modulatingPsi: null,
        noLoadPowerFM: 0,
        powerAtFullLoad: 106.7,
        powerAtFullLoadPercentage: 1,
        powerAtNoLoad: 16.9,
        powerAtNolLoad: 16.9,
        powerAtUnload: undefined,
        powerMax: 112.3,
        powerMaxPercentage: 1.0524835988753514,
        pressureAtUnload: undefined,
        receiverVolume: 13.400145795431047,
        stageType: Module.Stage.Two,
        unloadPointCapacity: 100,
        unloadSumpPressure: null
    }
    input.computeFromVal = .10;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(25), "% Power 1");
    // t.equal(rnd(results.powerCalculated), rnd(26.1), "Power Calculated 1");
    testNumberValue(rnd(results.PerkW), rnd(25), "compressorCalc 1187: PerkW 1");
    testNumberValue(rnd(results.kW_Calc), rnd(26.1), "compressorCalc 1187: kW_Calc 1");
    //Test Doc has 24.48 % power


    input.computeFromVal = .2448;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentagePower;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(10), "% Capacity 1");
    // t.equal(rnd(results.powerCalculated), rnd(26.1), "Power Calculated 2");
    testNumberValue(rnd(results.C_Per), rnd(10), "compressorCalc 1187: C_Per 2");
    testNumberValue(rnd(results.kW_Calc), rnd(26.1), "compressorCalc 1187: kW_Calc 2");

    input.computeFromVal = .90;
    //1 = % Airflow
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.PerkW = results.PerkW * 100;
    // t.equal(rnd(results.percentagePower), rnd(93.71), "% Power 2");
    // t.equal(rnd(results.powerCalculated), rnd(99.9), "Power Calculated 3");
    testNumberValue(rnd(results.PerkW), rnd(93.71), "compressorCalc 1187: PerkW 3");
    testNumberValue(rnd(results.kW_Calc), rnd(99.9), "compressorCalc 1187: kW_Calc 3");

    input.computeFromVal = .9371;
    //0 = Percent Power
    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    var results = compressorCalc(input);
    results.C_Per = results.C_Per * 100;
    // t.equal(rnd(results.percentageCapacity), rnd(90), "% Capacity 2");
    // t.equal(rnd(results.powerCalculated), rnd(99.9), "Power Calculated 4");
    testNumberValue(rnd(results.C_Per), rnd(90), "compressorCalc 1187: C_Per 4");
    testNumberValue(rnd(results.kW_Calc), rnd(99.9), "compressorCalc 1187: kW_Calc 4");
}

compId737();
compId701();
compId728();
compId629LoadUnload();
compId629StartStop();
// compId861LoadUnload();
compId861StartStop();
// compId1156LoadUnload();
compId1156StartStop();
// compId1187();