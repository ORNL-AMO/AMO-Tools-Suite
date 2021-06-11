function validateCompressorsCalc(headerMsg, input, output){
    let validate = function(results, expected, blowOff) {
        testNumberValue(rnd(results.kW_Calc), rnd(expected[0]), "powerCalculated kW_Calc");
        testNumberValue(rnd(results.C_Calc), rnd(expected[1]), "capacityCalculated C_Calc");
        testNumberValue(rnd(results.PerkW), rnd(expected[2]), "percentagePower PerkW");
        testNumberValue(rnd(results.C_Per), rnd(expected[3]),"percentageCapacity C_Per");

        if(input.controlType == Module.ControlType.BlowOff) {
            testNumberValue(rnd(results.C_blow), rnd(expected[4]), "surgeFlow C_blow");
            testNumberValue(rnd(results.blowPer), rnd(expected[5]), "percentageBlowOff blowPer");
        }
    };

    logMessage(headerMsg, true);

    let res;
    if(input.compressorType == Module.CompressorType.Centrifugal) res = compressorsCalcCentrifugal(input);
    else{
        if(input.compressorType == Module.CompressorType.Screw) {
            if (input.lubricantType == Module.Lubricant.Injected && (input.stageType == Module.Stage.Single || input.stageType == Module.Stage.Two)){
                if(input.controlType == Module.ControlType.LoadUnload) {
                    res = compressorsCalcLoadUnload(input);
                }
                else if(input.controlType == Module.ControlType.ModulationWOUnload) {
                    res = compressorsCalcModulationWOUnload(input);
                }
                else if(input.controlType == Module.ControlType.ModulationUnload || input.controlType == Module.ControlType.VariableDisplacementUnload) {
                    res = compressorsCalcModulationWithUnload(input);
                }
                else if(input.controlType == Module.ControlType.VFD) {
                    res = compressorsCalcVFD(input);
                }
            }
            else if (input.lubricantType == Module.Lubricant.Free && input.stageType == Module.Stage.Two) {
                if(input.controlType == Module.ControlType.LoadUnload) {
                    res = compressorsCalcLoadUnload(input);
                }
                else if(input.controlType == Module.ControlType.StartStop) {
                    res = compressorsCalcStartStop(input);
                }
                else if(input.controlType == Module.ControlType.VFD) {
                    res = compressorsCalcVFD(input);
                }
            }
        }
        else if(input.compressorType == Module.CompressorType.Reciprocating) {
            if (input.stageType == Module.Stage.Two && input.controlType == Module.ControlType.MultiStepUnloading) {
                res = compressorsCalcMultiStepUnloading(input);
            }
            else if (input.stageType == Module.Stage.Single || input.stageType == Module.Stage.Two) {
                if(input.controlType == Module.ControlType.LoadUnload) {
                    res = compressorsCalcLoadUnload(input);
                }
                else if(input.controlType == Module.ControlType.StartStop) {
                    res = compressorsCalcStartStop(input);
                }
            }
        }
    }

    validate(res, output);
}

function compressorsCalcCentrifugal(input){
    let output;
    let instance;
    let maxPressure = 0;
    let capacityList = new Module.DoubleVector();
    capacityList.push_back(input.capacityAtFullLoad);
    capacityList.push_back(input.capacityAtMinFullLoadPressure);
    capacityList.push_back(input.capacityAtMaxFullLoadPressure);

    let pressureList = new Module.DoubleVector();
    pressureList.push_back(input.fullLoadPressure);
    pressureList.push_back(input.minFullLoadPressure);
    pressureList.push_back(input.maxFullLoadPressure);

    if(input.controlType == Module.ControlType.LoadUnload) {
        instance = new Module.Compressors_Centrifugal_LoadUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerAtNoLoad);
    }
    else if(input.controlType == Module.ControlType.ModulationUnload) {
        instance = new Module.Compressors_Centrifugal_ModulationUnload(input.powerAtFullLoad, input.capacityAtFullLoad,
            input.powerAtNoLoad, input.capacityAtMaxFullFlow, input.powerAtUnload, input.capacityAtUnload);
        if(input.adjustForDischargePressure)
            maxPressure = input.maxPressure;
    }
    if(input.controlType == Module.ControlType.BlowOff) {
        instance = new Module.Compressors_Centrifugal_BlowOff(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerAtBlowOff, input.surgeFlow);
    }

    if(input.adjustForDischargePressure) {
        instance.AdjustDischargePressure(capacityList, pressureList, input.fullLoadPressure, maxPressure);

        logMessage("capacityAtFullLoadAdjusted : " + instance.C_fl_Adjusted);
        if(maxPressure != 0)
            logMessage("capacityAtMaxFullFlowAdjusted : " + instance.C_max_Adjusted);
    }

    if(input.controlType == Module.ControlType.BlowOff) {
        if(input.computeFrom == Module.ComputeFrom.PercentagePower)
            output = instance.calculateFromPerkW_BlowOff(input.computeFromVal, input.percentageBlowOff);
        else if(input.computeFrom == Module.ComputeFrom.PercentageCapacity)
            output = instance.calculateFromPerC_BlowOff(input.computeFromVal);
        else if(input.computeFrom == Module.ComputeFrom.PowerMeasured)
            output = instance.calculateFromkWMeasured_BlowOff(input.computeFromVal, input.percentageBlowOff);
        else if(input.computeFrom == Module.ComputeFrom.CapacityMeasured)
            output = instance.calculateFromCMeasured_BlowOff(input.computeFromVal);
        else if(input.computeFrom == Module.ComputeFrom.PowerFactor)
            output = instance.calculateFromVIPFMeasured_BlowOff(input.computeFromVal, input.computeFromPFVoltage, input.computeFromPFAmps, input.percentageBlowOff);
    }
    else {
        if(input.computeFrom == Module.ComputeFrom.PercentagePower)
            output = instance.calculateFromPerkW(input.computeFromVal);
        else if(input.computeFrom == Module.ComputeFrom.PercentageCapacity)
            output = instance.calculateFromPerC(input.computeFromVal);
        else if(input.computeFrom == Module.ComputeFrom.PowerMeasured)
            output = instance.calculateFromkWMeasured(input.computeFromVal);
        else if(input.computeFrom == Module.ComputeFrom.CapacityMeasured)
            output = instance.calculateFromCMeasured(input.computeFromVal);
        else if(input.computeFrom == Module.ComputeFrom.PowerFactor)
            output = instance.calculateFromVIPFMeasured(input.computeFromVal, input.computeFromPFVoltage, input.computeFromPFAmps);
    }

    instance.delete();
    return output;
}

function compressorsCalc(input, compMethod){
    if(input.applyPressureInletCorrection) {
        compMethod.Pressure_InletCorrection(input.capacity, input.fullLoadPower, input.polyExponent,
            input.ratedDischargePressure, input.ratedInletPressure, input.motorEfficiency, input.fullLoadDischargePressure,
            input.fullLoadDischargePressure, input.inletPressure, true, input.atmosphericPressure);

        logMessage("ReRated Pressure Inlet Correction values" +
            "<br/>New Power: " + rnd(compMethod.kW_fl_Adjusted) +
            "<br/>New Flow: " + rnd(compMethod.C_fl_Adjusted) +
            "<br/>New Power Max: " + rnd(compMethod.kW_max_Adjusted) +
            "<br/>New Flow Max: " + rnd(compMethod.C_max_Adjusted));
    }

    let output;
    if(input.computeFrom == Module.ComputeFrom.PercentagePower)
        output = compMethod.calculateFromPerkW(input.computeFromVal);
    else if(input.computeFrom == Module.ComputeFrom.PercentageCapacity)
        output = compMethod.calculateFromPerC(input.computeFromVal);
    else if(input.computeFrom == Module.ComputeFrom.PowerMeasured)
        output = compMethod.calculateFromkWMeasured(input.computeFromVal);
    else if(input.computeFrom == Module.ComputeFrom.CapacityMeasured)
        output = compMethod.calculateFromCMeasured(input.computeFromVal);
    else if(input.computeFrom == Module.ComputeFrom.PowerFactor)
        output = compMethod.calculateFromVIPFMeasured(input.computeFromVal, input.computeFromPFVoltage, input.computeFromPFAmps);

    return output;
}

function compressorsCalcModulationWOUnload(input){
    let compMethod = new Module.Compressors_ModulationWOUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerAtNoLoad, Module.CompressorType.Screw);
    let output = compressorsCalc(input,  compMethod);
    compMethod.delete();
    return output;
}

function compressorsCalcStartStop(input){
    let compMethod = new Module.Compressors_StartStop(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerMaxPercentage, input.powerAtFullLoadPercentage);
    let output = compressorsCalc(input,  compMethod);
    compMethod.delete();
    return output;
}

function compressorsCalcLoadUnload(input){
    let compMethod = new Module.Compressors_LoadUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerMax,
        input.dischargePsiFullLoad, input.dischargePsiMax, input.modulatingPsi, input.atmosphericPsi,
        input.compressorType, input.lubricantType, input.controlType, 1);
    let output = compressorsCalc(input,  compMethod);
    compMethod.delete();
    return output;
}

function compressorsCalcModulationWithUnload(input){
    let compMethod = new Module.Compressors_ModulationWithUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerMax,
        input.powerAtNolLoad, input.dischargePsiFullLoad, input.dischargePsiMax, input.modulatingPsi, input.atmosphericPsi, input.controlType);
    let output = compressorsCalc(input,  compMethod);
    compMethod.delete();
    return output;
}

function compressorsCalcMultiStepUnloading(input){

}

function compressorsCalcVFD(input){

}


function compressorsCentrifugalLoadUnload(){
    let input = {
        compressorType : Module.CompressorType.Centrifugal,
        controlType: Module.ControlType.LoadUnload,
        computeFrom: Module.ComputeFrom.PercentagePower,

        powerAtFullLoad: 452.3,
        capacityAtFullLoad: 3138,

        capacityAtMinFullLoadPressure: 3200,
        capacityAtMaxFullLoadPressure: 2885,
        fullLoadPressure: 100,
        minFullLoadPressure: 91,
        maxFullLoadPressure: 117,

        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0,

        powerAtNoLoad: 71.3,
        capacityAtMaxFullFlow: 3005,
        powerAtUnload: 411.9,
        capacityAtUnload: 2731
    };

    input.computeFrom = Module.ComputeFrom.PercentagePower;
    input.computeFromVal = 0.36;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PercentagePower', input, [162.828, 753.84, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PercentagePower - Adjust Pressure', input, [162.828, 753.84, 0.36, 0.24]);

    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    input.computeFromVal = 0.24;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PercentageCapacity', input, [162.74, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PercentageCapacity - Adjust Pressure', input, [162.74, 753.12, 0.36, 0.24]);

    input.computeFrom = Module.ComputeFrom.PowerMeasured;
    input.computeFromVal = 162.828;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PowerMeasured', input, [162.828, 753.84, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PowerMeasured - Adjust Pressure', input, [162.828, 753.84, 0.36, 0.24]);

    input.computeFrom = Module.ComputeFrom.CapacityMeasured;
    input.computeFromVal = 753.12;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: CapacityMeasured', input, [162.74, 753.12, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: CapacityMeasured - Adjust Pressure', input, [162.74, 753.12, 0.36, 0.24]);

    input.computeFrom = Module.ComputeFrom.PowerFactor;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.00945;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PowerFactor', input, [162.865, 754.15, 0.36, 0.24]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Load Unload: PowerFactor - Adjust Pressure', input, [162.865, 754.15, 0.36, 0.24]);
}

function compressorsCentrifugalModulationUnload(){
    let input = {
        compressorType : Module.CompressorType.Centrifugal,
        controlType: Module.ControlType.ModulationUnload,
        computeFrom: Module.ComputeFrom.PercentagePower,

        fullLoadPressure: 100,
        maxPressure: 58.23,

        powerAtFullLoad: 452.3,
        capacityAtFullLoad: 3138,

        capacityAtMinFullLoadPressure: 3200,
        capacityAtMaxFullLoadPressure: 2885,
        fullLoadPressure: 100,
        minFullLoadPressure: 91,
        maxFullLoadPressure: 117,

        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0,

        powerAtNoLoad: 71.3,
        capacityAtMaxFullFlow: 3005,
        powerAtUnload: 411.9,
        capacityAtUnload: 2731
    };

    input.computeFrom = Module.ComputeFrom.PercentagePower;
    input.computeFromVal = 0.94;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PercentagePower', input, [425.162, 2820.95, 0.94, 0.93875]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PercentagePower - Adjust Pressure', input, [425.162, 2820.92, 0.94, 0.94]);

    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    input.computeFromVal = 0.24;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PercentageCapacity', input, [165.226, 753.12, 0.365302, 0.24]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PercentageCapacity - Adjust Pressure', input, [165.226, 753.12, 0.365302, 0.24]);

    input.computeFrom = Module.ComputeFrom.PowerMeasured;
    input.computeFromVal = 425.162;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PowerMeasured', input, [425.162, 2820.95, 0.94, 0.93875]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PowerMeasured - Adjust Pressure', input, [425.162, 2820.92, 0.94, 0.94]);

    input.computeFrom = Module.ComputeFrom.CapacityMeasured;
    input.computeFromVal = 753.12;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: CapacityMeasured', input, [165.226, 753.12, 0.365302, 0.24]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: CapacityMeasured - Adjust Pressure', input, [165.226, 753.12, 0.365302, 0.24]);

    input.computeFrom = Module.ComputeFrom.PowerFactor;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02467;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PowerFactor', input, [425.174, 2821.02, 0.940026, 0.938777]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal Modulation Unload: PowerFactor - Adjust Pressure', input, [425.174, 2821, 0.94, 0.94]);
}

function compressorsCentrifugalBlowOff(){
    let input = {
        compressorType : Module.CompressorType.Centrifugal,
        controlType: Module.ControlType.BlowOff,
        computeFrom: Module.ComputeFrom.PercentagePower,

        fullLoadPressure: 100,

        powerAtFullLoad: 452.3,
        capacityAtFullLoad: 3138,

        capacityAtMinFullLoadPressure: 3200,
        capacityAtMaxFullLoadPressure: 2885,
        fullLoadPressure: 100,
        minFullLoadPressure: 91,
        maxFullLoadPressure: 117,

        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0,

        powerAtBlowOff: 370.9,
        surgeFlow: 2510
    };

    input.computeFrom = Module.ComputeFrom.PercentagePower;
    input.computeFromVal = 0.82;
    input.adjustForDischargePressure = false;
    input.percentageBlowOff = 0.6798;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PercentagePower', input, [370.886, 376.788, 0.82, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PercentagePower - Adjust Pressure', input, [370.886, 376.79, 0.82, 0.120073, 2133.21, 0.6798]);

    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    input.computeFromVal = 0.01;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PercentageCapacity', input, [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PercentageCapacity - Adjust Pressure', input, [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);

    input.computeFrom = Module.ComputeFrom.PowerMeasured;
    input.computeFromVal = 370.9;
    input.percentageBlowOff = 0.6798;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PowerMeasured', input, [370.9, 376.788, 0.8200309, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PowerMeasured - Adjust Pressure', input, [370.9, 376.79, 0.8200301, 0.120073, 2133.21, 0.6798]);

    input.computeFrom = Module.ComputeFrom.CapacityMeasured;
    input.computeFromVal = 31.38;
    input.adjustForDischargePressure = false;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: CapacityMeasured', input, [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: CapacityMeasured - Adjust Pressure', input, [370.9, 31.38, 0.820031, 0.01, 2478.62, 0.789873]);

    input.computeFrom = Module.ComputeFrom.PowerFactor;
    input.computeFromVal = 50;
    input.adjustForDischargePressure = false;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02152;
    input.percentageBlowOff = 0.6798;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PowerFactor', input, [370.885, 376.788, 0.82, 0.120073, 2133.21, 0.6798]);
    input.adjustForDischargePressure = true;
    validateCompressorsCalc('Compressors Centrifugal BlowOff: PowerFactor - Adjust Pressure', input, [370.885, 376.79, 0.82, 0.120073, 2133.21, 0.6798]);
}

function compressorsModulationWOUnload(){
    let input = {
        //required
        compressorType : Module.CompressorType.Screw,
        controlType: Module.ControlType.ModulationWOUnload,
        stageType: Module.Stage.Single,
        lubricantType: Module.Lubricant.Injected,

        powerAtFullLoad: 85.4,
        capacityAtFullLoad: 473,
        powerAtNoLoad: 55.3,

        //needed for Pressure Inlet Correction for control type ModulationWOUnload
        capacity: 473,
        fullLoadPower: 105,
        polyExponent:1.4,
        ratedDischargePressure : 100,
        ratedInletPressure: 14.5,
        motorEfficiency: 0.917,
        fullLoadDischargePressure : 110,
        maxDischargePressure : 110,
        inletPressure : 14.7,
        atmosphericPressure:14.69,

        //compute method
        computeFrom: 0,
        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0
    };

    input.computeFrom = Module.ComputeFrom.PercentagePower;
    input.computeFromVal = 0.89;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PercentagePower', input, [76.006, 325.38, 0.89, 0.69]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PercentagePower - Press Correction', input, [80.1, 335.51, 0.89, 0.71]);

    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    input.computeFromVal = 1.66173;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PercentageCapacity', input, [105.32, 786, 1.23326, 1.66173]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PercentageCapacity - Press Correction', input, [112.96, 780.1, 1.25547, 1.66173]);

    input.computeFrom = Module.ComputeFrom.PowerMeasured;
    input.computeFromVal = 75.9;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PowerMeasured', input, [75.9, 323.71, 0.89, 0.68]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PowerMeasured - Press Correction', input, [75.9, 278.72, 0.84, 0.59]);

    input.computeFrom = Module.ComputeFrom.CapacityMeasured;
    input.computeFromVal = 786;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : CapacityMeasured', input, [105.32, 786, 1.23326, 1.66173]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : CapacityMeasured - Press Correction', input, [113.39, 786, 1.26024, 1.67426]);

    input.computeFrom = Module.ComputeFrom.PowerFactor;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02467;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PowerFactor', input, [80.278, 392.51, 0.94, 0.83]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected ModulationWOUnload : PowerFactor - Press Correction', input, [84.6, 396.42, 0.94, 0.84]);
}

function compressorsStartStop(){
    let input = {
        //required
        compressorType : Module.CompressorType.Screw,
        controlType: Module.ControlType.StartStop,
        stageType: Module.Stage.Two,
        lubricantType: Module.Lubricant.Free,

        powerAtFullLoad: 89.5,
        capacityAtFullLoad: 560,
        powerMaxPercentage: 1.05,
        powerAtFullLoadPercentage:1,

        //needed for Pressure Inlet Correction for control type ModulationWOUnload
        capacity: 473,
        fullLoadPower: 105,
        polyExponent:1.4,
        ratedDischargePressure : 100,
        ratedInletPressure: 14.5,
        motorEfficiency: 0.917,
        fullLoadDischargePressure : 110,
        maxDischargePressure : 110,
        inletPressure : 14.7,
        atmosphericPressure:14.7,

        //compute method
        computeFrom: 0,
        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0
    };

    input.computeFrom = Module.ComputeFrom.PercentagePower;
    input.computeFromVal = 0.205;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PercentagePower', input, [18.3475, 112, 0.21, 0.2]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PercentagePower - Press Correction', input, [18.47, 93.891998291, 0.21, 0.2]);

    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    input.computeFromVal = 0.2;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PercentageCapacity', input, [18.35, 112, 0.20503, 0.2]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PercentageCapacity - Press Correction', input, [18.47, 93.892, 0.21, 0.2]);

    input.computeFrom = Module.ComputeFrom.PowerMeasured;
    input.computeFromVal = 18.35;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PowerMeasured', input, [18.35, 112.015, 0.21, 0.2]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PowerMeasured - Press Correction', input, [18.35, 93.31, 0.2, 0.2]);

    input.computeFrom = Module.ComputeFrom.CapacityMeasured;
    input.computeFromVal = 112;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : CapacityMeasured', input, [18.35, 112, 0.21, 0.2]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : CapacityMeasured - Press Correction', input, [22.03, 112, 0.2445875515, 0.238572]);

    input.computeFrom = Module.ComputeFrom.PowerFactor;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02467;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PowerFactor', input, [84.1323, 513.575, 0.94, 0.92]);
    input.applyPressureInletCorrection = true;
    validateCompressorsCalc('Two Stage Screw Lubricant Free StartStop : PowerFactor - Press Correction', input, [84.67, 430.54, 0.94, 0.92]);
}

function compressorsLoadUnload(){
    let input = {
        //required
        compressorType : Module.CompressorType.Reciprocating,
        controlType: Module.ControlType.LoadUnload,
        stageType: Module.Stage.Single,
        lubricantType: Module.Lubricant.None,

        powerAtFullLoad: 166.5,
        capacityAtFullLoad: 1048,
        powerMax: 175.5,
        dischargePsiFullLoad:100,
        dischargePsiMax:110,
        modulatingPsi:5,
        atmosphericPsi:14.7,

        //needed for Pressure Inlet Correction for control type ModulationWOUnload
        capacity: 473,
        fullLoadPower: 105,
        polyExponent:1.4,
        ratedDischargePressure : 100,
        ratedInletPressure: 14.5,
        motorEfficiency: 0.917,
        fullLoadDischargePressure : 110,
        maxDischargePressure : 110,
        inletPressure : 14.7,
        atmosphericPressure:14.7,

        //compute method
        computeFrom: 0,
        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0
    };

    input.computeFrom = Module.ComputeFrom.PercentagePower;
    input.computeFromVal = 0.94;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PercentagePower', input, [156.51, 937.88, 0.94, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PercentagePower - Press Correction', input, [156.51, 937.88, 0.94, 0.89]);

    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    input.computeFromVal = 0.895;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PercentageCapacity', input, [156.442, 937.96, 0.93959, 0.9]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PercentageCapacity - Press Correction', input, [156.442, 937.96, 0.93959, 0.9]);

    input.computeFrom = Module.ComputeFrom.PowerMeasured;
    input.computeFromVal = 156;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PowerMeasured', input, [156, 933.85, 0.93693, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PowerMeasured - Press Correction', input, [156, 933.85, 0.93693, 0.89]);

    input.computeFrom = Module.ComputeFrom.CapacityMeasured;
    input.computeFromVal = 937;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : CapacityMeasured', input, [156.322, 937, 0.938872, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : CapacityMeasured - Press Correction', input, [156.322, 937, 0.938872, 0.89]);

    input.computeFrom = Module.ComputeFrom.PowerFactor;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02467;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PowerFactor', input, [156.514, 937.922, 0.94002, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Reciprocating LoadUnload : PowerFactor - Press Correction', input, [156.514, 937.922, 0.94002, 0.89]);
}

function compressorsModulationWithUnload(){
    let input = {
        //required
        compressorType : Module.CompressorType.Screw,
        controlType: Module.ControlType.VariableDisplacementUnload,
        stageType: Module.Stage.Single,
        lubricantType: Module.Lubricant.Injected,

        powerAtFullLoad: 166.5,
        capacityAtFullLoad: 1048,
        powerMax: 175.5,
        dischargePsiFullLoad:100,
        dischargePsiMax:110,
        modulatingPsi:5,
        atmosphericPsi:14.7,
        powerAtNolLoad:107.5,

        //needed for Pressure Inlet Correction for control type ModulationWOUnload
        capacity: 473,
        fullLoadPower: 105,
        polyExponent:1.4,
        ratedDischargePressure : 100,
        ratedInletPressure: 14.5,
        motorEfficiency: 0.917,
        fullLoadDischargePressure : 110,
        maxDischargePressure : 110,
        inletPressure : 14.7,
        atmosphericPressure:14.7,

        //compute method
        computeFrom: 0,
        computeFromVal: 0,
        computeFromPFVoltage : 0,
        computeFromPFAmps : 0
    };

    input.computeFrom = Module.ComputeFrom.PercentagePower;
    input.computeFromVal = 0.94;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PercentagePower', input, [156.51, 937.89, 0.94, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PercentagePower - Press Correction', input, [156.51, 937.89, 0.94, 0.89]);

    input.computeFrom = Module.ComputeFrom.PercentageCapacity;
    input.computeFromVal = 0.895;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PercentageCapacity', input, [156.442, 937.96, 0.93959, 0.9]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PercentageCapacity - Press Correction', input, [156.442, 937.96, 0.93959, 0.9]);

    input.computeFrom = Module.ComputeFrom.PowerMeasured;
    input.computeFromVal = 156;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PowerMeasured', input, [156, 933.86, 0.93693, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PowerMeasured - Press Correction', input, [156, 933.86, 0.93693, 0.89]);

    input.computeFrom = Module.ComputeFrom.CapacityMeasured;
    input.computeFromVal = 937;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : CapacityMeasured', input, [156.322, 937, 0.938872, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : CapacityMeasured - Press Correction', input, [156.322, 937, 0.938872, 0.89]);

    input.computeFrom = Module.ComputeFrom.PowerFactor;
    input.computeFromVal = 50;
    input.computeFromPFVoltage = 440;
    input.computeFromPFAmps = 0.02467;
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PowerFactor', input, [156.514, 937.922, 0.94002, 0.89]);
    input.applyPressureInletCorrection = false;
    validateCompressorsCalc('Single Stage Screw Lubricant Injected VariableDisplacementUnload : PowerFactor - Press Correction', input, [156.514, 937.922, 0.94002, 0.89]);
}

function reduceAirLeaks(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.C_lkred), rnd(expected[0]),"Reduce leaks by flow - leaks C_lkred");
        testNumberValue(rnd(results.C_usage_lkred), rnd(expected[1]),"Air usage reduced - leaks C_usage_lkred");
        testNumberValue(rnd(results.PerC_lkred), rnd(expected[2]),"Percent air usage reduced - leaks PerC_lkred");
    };

    let input = {
        C_fl: 473,
        C_usage: 100,
        C_lk: 10,
        PerC_lkred: 0.5
    };

    logMessage('Compressors EEM Reduce Air Leaks: Test# 1', true);
    validate(Module.ReduceAirLeaks(input.C_fl, input.C_usage, input.C_lk, input.PerC_lkred), [5, 95, 0.20084]);
}

function  improveEndUseEfficiency(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.C_af_red), rnd(expected[0]), "Reduced airflow C_af_red");
        testNumberValue(rnd(results.CPer_af_red), rnd(expected[1]), "Compressor capacity with airflow reduction CPer_af_red");
    };

    let input = {
        C_fl: 473,
        C_usage: 236,
        C_avgaf_red: 20
    };

    logMessage('Compressors EEM Improve End Use Efficiency: Test# 1', true);
    validate(Module.ImproveEndUseEfficiency(input.C_fl, input.C_usage, input.C_avgaf_red), [216, 0.45666]);
}

function reduceSystemAirPressure(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.P_fl_rpred), rnd(expected[0]), "Full Load (cut-in) Pressure (psig) reduced P_fl_rpred");
        testNumberValue(rnd(results.kW_fl_rpadj), rnd(expected[1]), "Power at Full Load Operating Pressure adjusted kW_fl_rpadj");
        testNumberValue(rnd(results.C_usage_rpred), rnd(expected[2]), "Air usage reduced - reduced pressure C_usage_rpred");
        testNumberValue(rnd(results.PerC_rpred), rnd(expected[3]), "Percent air usage reduced - reduced pressure PerC_rpred");
    };

    var input = {
        C_fl: 473,
        C_usage: 100,
        P_fl: 100,
        kW_fl: 85.4,
        P_rpred: 5,
        P_alt: 14.7,
        P_atm: 14.7
    };

    logMessage('Compressors EEM Reduce System Air Pressure: Test# 1', true);
    validate(Module.ReduceSystemAirPressure(input.C_fl, input.C_usage, input.P_fl, input.kW_fl, input.P_rpred, input.P_alt, input.P_atm),
        [95, 82.972, 97.384, 0.2059]);
}

function adjustCascadingSetPoint(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.kW_fl_adj), rnd(expected[0]), "Power at Full Load Operating Pressure adjusted kW_fl_adj");
        testNumberValue(rnd(results.C_usage_adj), rnd(expected[1]), "Air usage @ adjusted pressure C_usage_adj");
        testNumberValue(rnd(results.PerC_adj), rnd(expected[2]), "Percent air usage @ adjusted pressure PerC_adj");
    };

    var input = {
        C_fl: 2578,
        C_usage: 1000,
        P_fl: 100,
        kW_fl: 414.4,
        P_fl_adj: 105,
        P_alt: 14.7,
        P_atm: 14.7
    };

    logMessage('Compressors EEM Adjust Cascading Set Point: Test# 1', true);
    validate(Module.AdjustCascadingSetPoint(input.C_fl, input.C_usage, input.P_fl, input.kW_fl, input.P_fl_adj, input.P_alt, input.P_atm),
        [425.82, 1026.16, 0.398]);
}

function pressureReductionSaving(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.kW_savings), rnd(expected[0]), "Power Savings kW_savings");
        testNumberValue(rnd(results.kWh_savings), rnd(expected[1]), "Power hour kWh_savings");
        testNumberValue(rnd(results.cost_savings), rnd(expected[2]), "Cost cost_savings");
    };

    var input = {
        operatingHours: 8760,
        costPerkWh: 0.066,
        kW_fl_rated: 75,
        P_fl_rated: 125,
        dischargePresBaseline: 110,
        dischargePresMod: 100,
        P_alt: 14.7,
        P_atm: 14.7
    };

    logMessage('Compressors EEM Pressure Reduction Saving: Test# 1', true);
    validate(Module.PressureReductionSaving(input.operatingHours, input.costPerkWh, input.kW_fl_rated, input.P_fl_rated,
        input.dischargePresBaseline, input.dischargePresMod, input.P_alt, input.P_atm),
        [3.6031, 31563.3423, 2083.18]);
}

function kW_adjusted(){
    let validate = function(results, expected) {
        testNumberValue(rnd(results.kW_savings), rnd(expected[0]), "Power Savings kW_savings");
        testNumberValue(rnd(results.kWh_savings), rnd(expected[1]), "Power hour kWh_savings");
        testNumberValue(rnd(results.cost_savings), rnd(expected[2]), "Cost cost_savings");
    };

    var input = {
        kW_fl_rated: 75,
        P_fl_rated: 125,
        P_discharge: 110,
        P_alt: 14.7,
        P_atm: 14.7
    };

    logMessage('Compressors EEM Adjusted Power: Test# 1', true);
    testNumberValue(rnd(Module.kWAdjusted(input.kW_fl_rated, input.P_fl_rated, input.P_discharge, input.P_alt, input.P_atm)), 69.97, "Power Adjusted kW_adjusted");
}

compressorsCentrifugalLoadUnload();
compressorsCentrifugalModulationUnload();
compressorsCentrifugalBlowOff();

compressorsModulationWOUnload();
compressorsStartStop();
compressorsLoadUnload();
compressorsModulationWithUnload();

reduceAirLeaks();
improveEndUseEfficiency();
reduceSystemAirPressure();
adjustCascadingSetPoint();

pressureReductionSaving();
kW_adjusted();
