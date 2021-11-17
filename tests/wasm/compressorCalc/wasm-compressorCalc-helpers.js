function compressorCalc(input) {
    let instance;
    if (input.compressorType == Module.CompressorType.Centrifugal) {
        instance = compressorsCalcCentrifugal(input);
    }
    else {
        if (input.controlType == Module.ControlType.LoadUnload) {
            instance = compressorsCalcLoadUnload(input);
        }
        else if (input.controlType == Module.ControlType.ModulationWOUnload) {
            instance = compressorsCalcModulationWOUnload(input);
        }
        else if (input.controlType == Module.ControlType.ModulationUnload) {
            instance = compressorsCalcModulationWithUnload(input);
        }
        else if (input.controlType == Module.ControlType.VariableDisplacementUnload) {
            instance = compressorsCalcVariableDisplacement(input);
        } else if (input.controlType == Module.ControlType.MultiStepUnloading) {
            instance = compressorsCalcMultiStepUnloading(input);
        }
        else if (input.controlType == Module.ControlType.StartStop) {
            instance = compressorsCalcStartStop(input);
        }
    }
    let output;
    if (input.controlType == Module.ControlType.BlowOff) {
        if (input.computeFrom == Module.ComputeFrom.PercentagePower)
            output = instance.calculateFromPerkW_BlowOff(input.computeFromVal, input.percentageBlowOff);
        else if (input.computeFrom == Module.ComputeFrom.PercentageCapacity)
            output = instance.calculateFromPerC_BlowOff(input.computeFromVal);
        else if (input.computeFrom == Module.ComputeFrom.PowerMeasured)
            output = instance.calculateFromkWMeasured_BlowOff(input.computeFromVal, input.percentageBlowOff);
        else if (input.computeFrom == Module.ComputeFrom.CapacityMeasured)
            output = instance.calculateFromCMeasured_BlowOff(input.computeFromVal);
        else if (input.computeFrom == Module.ComputeFrom.PowerFactor)
            output = instance.calculateFromVIPFMeasured_BlowOff(input.computeFromVal, input.computeFromPFVoltage, input.computeFromPFAmps, input.percentageBlowOff);
    }
    else {
        if (input.computeFrom == Module.ComputeFrom.PercentagePower)
            output = instance.calculateFromPerkW(input.computeFromVal);
        else if (input.computeFrom == Module.ComputeFrom.PercentageCapacity)
            output = instance.calculateFromPerC(input.computeFromVal);
        else if (input.computeFrom == Module.ComputeFrom.PowerMeasured)
            output = instance.calculateFromkWMeasured(input.computeFromVal);
        else if (input.computeFrom == Module.ComputeFrom.CapacityMeasured)
            output = instance.calculateFromCMeasured(input.computeFromVal);
        else if (input.computeFrom == Module.ComputeFrom.PowerFactor)
            output = instance.calculateFromVIPFMeasured(input.computeFromVal, input.computeFromPFVoltage, input.computeFromPFAmps);
    }

    instance.delete();
    return output;
}

function compressorsCalcCentrifugal(input) {
    if (input.controlType == Module.ControlType.LoadUnload) {
        return new Module.Compressors_Centrifugal_LoadUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerAtNoLoad);
    }
    else if (input.controlType == Module.ControlType.ModulationUnload) {
        return new Module.Compressors_Centrifugal_ModulationUnload(input.powerAtFullLoad, input.capacityAtFullLoad,
            input.powerAtNoLoad, input.capacityAtMaxFullFlow, input.powerAtUnload, input.capacityAtUnload);
    } else if (input.controlType == Module.ControlType.BlowOff) {
        return new Module.Compressors_Centrifugal_BlowOff(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerAtBlowOff, input.surgeFlow);
    }
}



function compressorsCalcModulationWOUnload(input) {
    return new Module.Compressors_ModulationWOUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerAtNoLoad);
}

function compressorsCalcStartStop(input) {
    return new Module.Compressors_StartStop(input.powerAtFullLoad, input.capacityAtFullLoad, input.powerMaxPercentage, input.powerAtFullLoadPercentage);
}

function compressorsCalcLoadUnload(input) {
    return new Module.Compressors_LoadUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.receiverVolume, input.powerMax,
        input.dischargePsiFullLoad, input.dischargePsiMax, input.modulatingPsi, input.loadFactorUnloaded, input.atmosphericPsi,
        input.compressorType, input.lubricantType, input.controlType, input.powerAtNoLoad, input.unloadPointCapacity, input.blowdownTime,
        input.unloadSumpPressure, input.noLoadPowerFM);
}

function compressorsCalcModulationWithUnload(input) {
    return new Module.Compressors_ModulationWithUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.receiverVolume, input.powerMax, input.powerAtNoLoad, input.dischargePsiFullLoad, input.dischargePsiMax, input.modulatingPsi, input.atmosphericPsi, input.unloadPointCapacity, input.controlType, input.blowdownTime, input.unloadSumpPressure, input.noLoadPowerFM, input.powerAtUnload, input.pressureAtUnload, input.capacityAtUnload);
}


function compressorsCalcVariableDisplacement(input) {
     return new Module.Compressors_ModulationWithUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.receiverVolume, input.powerMax, input.powerAtNoLoad, input.dischargePsiFullLoad, input.dischargePsiMax, input.modulatingPsi, input.atmosphericPsi, input.unloadPointCapacity, input.controlType, input.blowdownTime, input.unloadSumpPressure, input.noLoadPowerFM, 0, 0, 0);
}


function compressorsCalcMultiStepUnloading(input) {
    return new Module.Compressors_LoadUnload(input.powerAtFullLoad, input.capacityAtFullLoad, input.receiverVolume, input.powerMax,
        input.dischargePsiFullLoad, input.dischargePsiMax, input.modulatingPsi, input.loadFactorUnloaded, input.atmosphericPsi,
        input.compressorType, input.lubricantType, input.controlType, input.powerAtNoLoad, input.unloadPointCapacity, input.blowdownTime,
        input.unloadSumpPressure, input.noLoadPowerFM);
}
