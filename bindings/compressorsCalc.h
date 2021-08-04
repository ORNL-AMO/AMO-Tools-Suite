#include <nan.h>
#include <node.h>
#include <string>
#include <array>
#include <vector>
#include <exception>
#include <iostream>
#include "./NanDataConverters.h"
#include "calculator/util/Compressors.h"

using namespace Nan;
using namespace v8;

void compressorsCalcCentrifugal(Compressors::ControlType controlType)
{
    int computeFrom = getInteger("computeFrom");
    bool adjustForDischargePressure = getBool("adjustForDischargePressure");

    const double powerAtFullLoad = getDouble("powerAtFullLoad", inp);
    const double capacityAtFullLoad = getDouble("capacityAtFullLoad", inp);

    const double capacityAtMinFullLoadPressure = getDouble("capacityAtMinFullLoadPressure", inp);
    const double capacityAtMaxFullLoadPressure = getDouble("capacityAtMaxFullLoadPressure", inp);
    const double fullLoadPressure = getDouble("fullLoadPressure", inp);
    const double minFullLoadPressure = getDouble("minFullLoadPressure", inp);
    const double maxFullLoadPressure = getDouble("maxFullLoadPressure", inp);

    const double computeFromVal = getDouble("computeFromVal", inp);
    const double computeFromPFVoltage = getDouble("computeFromPFVoltage", inp);
    const double computeFromPFAmps = getDouble("computeFromPFAmps", inp);

    if (controlType == Compressors::ControlType::LoadUnload)
    {
        const double powerAtNoLoad = getDouble("powerAtNoLoad", inp);
        auto cacLUL = Compressors_Centrifugal_LoadUnload(powerAtFullLoad, capacityAtFullLoad, powerAtNoLoad);

        if (adjustForDischargePressure)
        {
            const double fullLoadPressure = getDouble("fullLoadPressure", inp);
            cacLUL.AdjustDischargePressure(
                {capacityAtFullLoad, capacityAtMinFullLoadPressure, capacityAtMaxFullLoadPressure},
                {fullLoadPressure, minFullLoadPressure, maxFullLoadPressure}, fullLoadPressure);

            setR("capacityAtFullLoadAdjusted", cacLUL.C_fl_Adjusted);
        }

        Compressors::Output output;
        if (computeFrom == Compressors::ComputeFrom::PercentagePower)
            output = cacLUL.calculateFromPerkW(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PercentageCapacity)
            output = cacLUL.calculateFromPerC(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PowerMeasured)
            output = cacLUL.calculateFromkWMeasured(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::CapacityMeasured)
            output = cacLUL.calculateFromCMeasured(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PowerFactor)
            output = cacLUL.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
        else
            ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Compute Method in input").c_str());

        setR("powerCalculated", output.kW_Calc);
        setR("capacityCalculated", output.C_Calc);
        setR("percentagePower", output.PerkW);
        setR("percentageCapacity", output.C_Per);
    }
    else if (controlType == Compressors::ControlType::ModulationUnload)
    {
        const double powerAtNoLoad = getDouble("powerAtNoLoad", inp);
        const double capacityAtMaxFullFlow = getDouble("capacityAtMaxFullFlow", inp);
        const double powerAtUnload = getDouble("powerAtUnload", inp);
        const double capacityAtUnload = getDouble("capacityAtUnload", inp);
        auto cacMUL = Compressors_Centrifugal_ModulationUnload(powerAtFullLoad, capacityAtFullLoad, powerAtNoLoad, capacityAtMaxFullFlow, powerAtUnload, capacityAtUnload);

        if (adjustForDischargePressure)
        {
            const double fullLoadPressure = getDouble("fullLoadPressure", inp);
            const double maxPressure = getDouble("maxPressure", inp);
            cacMUL.AdjustDischargePressure(
                {capacityAtFullLoad, capacityAtMinFullLoadPressure, capacityAtMaxFullLoadPressure},
                {fullLoadPressure, minFullLoadPressure, maxFullLoadPressure}, fullLoadPressure, maxPressure);

            setR("capacityAtFullLoadAdjusted", cacMUL.C_fl_Adjusted);
            setR("capacityAtMaxFullFlowAdjusted", cacMUL.C_max_Adjusted);
        }

        Compressors::Output output;
        if (computeFrom == Compressors::ComputeFrom::PercentagePower)
            output = cacMUL.calculateFromPerkW(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PercentageCapacity)
            output = cacMUL.calculateFromPerC(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PowerMeasured)
            output = cacMUL.calculateFromkWMeasured(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::CapacityMeasured)
            output = cacMUL.calculateFromCMeasured(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PowerFactor)
            output = cacMUL.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
        else
            ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Compute Method in input").c_str());

        setR("powerCalculated", output.kW_Calc);
        setR("capacityCalculated", output.C_Calc);
        setR("percentagePower", output.PerkW);
        setR("percentageCapacity", output.C_Per);
    }
    else if (controlType == Compressors::ControlType::BlowOff)
    {
        const double powerAtBlowOff = getDouble("powerAtBlowOff", inp);
        const double surgeFlow = getDouble("surgeFlow", inp);
        const double percentageBlowOff = getDouble("percentageBlowOff", inp);
        auto cacBO = Compressors_Centrifugal_BlowOff(powerAtFullLoad, capacityAtFullLoad, powerAtBlowOff, surgeFlow);

        if (adjustForDischargePressure)
        {
            const double fullLoadPressure = getDouble("fullLoadPressure", inp);
            cacBO.AdjustDischargePressure(
                {capacityAtFullLoad, capacityAtMinFullLoadPressure, capacityAtMaxFullLoadPressure},
                {fullLoadPressure, minFullLoadPressure, maxFullLoadPressure}, fullLoadPressure);

            setR("capacityAtFullLoadAdjusted", cacBO.C_fl_Adjusted);
        }

        Compressors::OutputBlowOff output;
        if (computeFrom == Compressors::ComputeFrom::PercentagePower)
            output = cacBO.calculateFromPerkW_BlowOff(computeFromVal, percentageBlowOff);
        else if (computeFrom == Compressors::ComputeFrom::PercentageCapacity)
            output = cacBO.calculateFromPerC_BlowOff(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PowerMeasured)
            output = cacBO.calculateFromkWMeasured_BlowOff(computeFromVal, percentageBlowOff);
        else if (computeFrom == Compressors::ComputeFrom::CapacityMeasured)
            output = cacBO.calculateFromCMeasured_BlowOff(computeFromVal);
        else if (computeFrom == Compressors::ComputeFrom::PowerFactor)
            output = cacBO.calculateFromVIPFMeasured_BlowOff(computeFromVal, computeFromPFVoltage, computeFromPFAmps, percentageBlowOff);
        else
            ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Compute Method in input").c_str());

        setR("powerCalculated", output.kW_Calc);
        setR("capacityCalculated", output.C_Calc);
        setR("percentagePower", output.PerkW);
        setR("percentageCapacity", output.C_Per);
        setR("percentageBlowOff", output.blowPer);
        setR("surgeFlow", output.C_blow);
    }
    else
        ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Control Type in input").c_str());
}

void compressorsModulationWOUnload(Compressors::CompressorType compressorType, Compressors::ControlType controlType, Compressors::Stage stageType, Compressors::Lubricant lubricantType)
{
    const double powerAtFullLoad = getDouble("powerAtFullLoad", inp);
    const double capacityAtFullLoad = getDouble("capacityAtFullLoad", inp);

    const int computeFrom = getInteger("computeFrom");
    const double computeFromVal = getDouble("computeFromVal", inp);
    const bool applyPressureInletCorrection = getBool("applyPressureInletCorrection");

    const double powerAtNoLoad = getDouble("powerAtNoLoad", inp);
    auto compMethod = Compressors_ModulationWOUnload(powerAtFullLoad, capacityAtFullLoad, powerAtNoLoad);

    if (applyPressureInletCorrection)
    {
        const double capacity = getDouble("capacity", inp);
        const double fullLoadPower = getDouble("fullLoadPower", inp);
        const double polyExponent = getDouble("polyExponent", inp);
        const double ratedDischargePressure = getDouble("ratedDischargePressure", inp);
        const double ratedInletPressure = getDouble("ratedInletPressure", inp);
        const double motorEfficiency = getDouble("motorEfficiency", inp);
        const double fullLoadDischargePressure = getDouble("fullLoadDischargePressure", inp);
        const double maxDischargePressure = getDouble("maxDischargePressure", inp);
        const double inletPressure = getDouble("inletPressure", inp);
        const double atmosphericPressure = getDouble("atmosphericPressure", inp);

        compMethod.Pressure_InletCorrection(capacity, fullLoadPower, polyExponent, ratedDischargePressure, ratedInletPressure, motorEfficiency, fullLoadDischargePressure, fullLoadDischargePressure, inletPressure, atmosphericPressure);
    }

    Compressors::Output output;
    if (computeFrom == Compressors::ComputeFrom::PercentagePower)
        output = compMethod.calculateFromPerkW(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PercentageCapacity)
        output = compMethod.calculateFromPerC(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PowerMeasured)
        output = compMethod.calculateFromkWMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::CapacityMeasured)
        output = compMethod.calculateFromCMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PowerFactor)
    {
        const double computeFromPFVoltage = getDouble("computeFromPFVoltage", inp);
        const double computeFromPFAmps = getDouble("computeFromPFAmps", inp);
        output = compMethod.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
    }

    else
        ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Compute Method in input").c_str());

    setR("reRatedFlow", compMethod.C_fl_Adjusted);
    setR("reRatedPower", compMethod.kW_fl_Adjusted);
    setR("reRatedFlowMax", compMethod.C_max_Adjusted);
    setR("reRatedPowerMax", compMethod.kW_max_Adjusted);

    setR("powerCalculated", output.kW_Calc);
    setR("capacityCalculated", output.C_Calc);
    setR("percentagePower", output.PerkW);
    setR("percentageCapacity", output.C_Per);
}

void compressorsStartStop(Compressors::CompressorType compressorType, Compressors::ControlType controlType, Compressors::Stage stageType, Compressors::Lubricant lubricantType)
{
    const double powerAtFullLoad = getDouble("powerAtFullLoad", inp);
    const double capacityAtFullLoad = getDouble("capacityAtFullLoad", inp);

    const int computeFrom = getInteger("computeFrom");
    const double computeFromVal = getDouble("computeFromVal", inp);
    const bool applyPressureInletCorrection = getBool("applyPressureInletCorrection");

    const double powerMaxPercentage = getDouble("powerMaxPercentage", inp);
    const double powerAtFullLoadPercentage = getDouble("powerAtFullLoadPercentage", inp);
    auto compMethod = Compressors_StartStop(powerAtFullLoad, capacityAtFullLoad, powerMaxPercentage, powerAtFullLoadPercentage);

    if (applyPressureInletCorrection)
    {
        const double capacity = getDouble("capacity", inp);
        const double fullLoadPower = getDouble("fullLoadPower", inp);
        const double polyExponent = getDouble("polyExponent", inp);
        const double ratedDischargePressure = getDouble("ratedDischargePressure", inp);
        const double ratedInletPressure = getDouble("ratedInletPressure", inp);
        const double motorEfficiency = getDouble("motorEfficiency", inp);
        const double fullLoadDischargePressure = getDouble("fullLoadDischargePressure", inp);
        const double maxDischargePressure = getDouble("maxDischargePressure", inp);
        const double inletPressure = getDouble("inletPressure", inp);
        const double atmosphericPressure = getDouble("atmosphericPressure", inp);

        compMethod.Pressure_InletCorrection(capacity, fullLoadPower, polyExponent, ratedDischargePressure, ratedInletPressure, motorEfficiency, fullLoadDischargePressure, fullLoadDischargePressure, inletPressure, atmosphericPressure);
    }

    Compressors::Output output;
    if (computeFrom == Compressors::ComputeFrom::PercentagePower)
        output = compMethod.calculateFromPerkW(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PercentageCapacity)
        output = compMethod.calculateFromPerC(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PowerMeasured)
        output = compMethod.calculateFromkWMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::CapacityMeasured)
        output = compMethod.calculateFromCMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PowerFactor)
    {
        const double computeFromPFVoltage = getDouble("computeFromPFVoltage", inp);
        const double computeFromPFAmps = getDouble("computeFromPFAmps", inp);
        output = compMethod.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
    }

    else
        ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Compute Method in input").c_str());

    setR("reRatedFlow", compMethod.C_fl_Adjusted);
    setR("reRatedPower", compMethod.kW_fl_Adjusted);
    setR("reRatedFlowMax", compMethod.C_max_Adjusted);
    setR("reRatedPowerMax", compMethod.kW_max_Adjusted);

    setR("powerCalculated", output.kW_Calc);
    setR("capacityCalculated", output.C_Calc);
    setR("percentagePower", output.PerkW);
    setR("percentageCapacity", output.C_Per);
}

void compressorsLoadUnload(Compressors::CompressorType compressorType, Compressors::ControlType controlType, Compressors::Stage stageType, Compressors::Lubricant lubricantType)
{
    const double powerAtFullLoad = getDouble("powerAtFullLoad", inp);
    const double capacityAtFullLoad = getDouble("capacityAtFullLoad", inp);
    const double receiverVolume = getDouble("receiverVolume", inp);

    const int computeFrom = getInteger("computeFrom");
    const double computeFromVal = getDouble("computeFromVal", inp);
    const bool applyPressureInletCorrection = getBool("applyPressureInletCorrection");

    const double powerMax = getDouble("powerMax", inp);
    const double dischargePsiFullLoad = getDouble("dischargePsiFullLoad", inp);
    const double dischargePsiMax = getDouble("dischargePsiMax", inp);
    const double modulatingPsi = getDouble("modulatingPsi", inp);
    const double loadFactorUnloaded = getDouble("loadFactorUnloaded", inp);
    const double atmosphericPsi = getDouble("atmosphericPsi", inp);
    const double unloadPointCapacity = getDouble("unloadPointCapacity", inp);
    const double powerAtNolLoad = getDouble("powerAtNolLoad", inp);
    const double blowdownTime = getDouble("blowdownTime", inp);
    const double unloadSumpPressure = getDouble("unloadSumpPressure", inp);
    auto compMethod = Compressors_LoadUnload(powerAtFullLoad, capacityAtFullLoad, receiverVolume, powerMax, dischargePsiFullLoad, dischargePsiMax, modulatingPsi, loadFactorUnloaded, atmosphericPsi, compressorType, lubricantType, controlType, powerAtNolLoad, unloadPointCapacity, blowdownTime, unloadSumpPressure);

    if (applyPressureInletCorrection)
    {
        const double capacity = getDouble("capacity", inp);
        const double fullLoadPower = getDouble("fullLoadPower", inp);
        const double polyExponent = getDouble("polyExponent", inp);
        const double ratedDischargePressure = getDouble("ratedDischargePressure", inp);
        const double ratedInletPressure = getDouble("ratedInletPressure", inp);
        const double motorEfficiency = getDouble("motorEfficiency", inp);
        const double fullLoadDischargePressure = getDouble("fullLoadDischargePressure", inp);
        const double maxDischargePressure = getDouble("maxDischargePressure", inp);
        const double inletPressure = getDouble("inletPressure", inp);
        const double atmosphericPressure = getDouble("atmosphericPressure", inp);

        compMethod.Pressure_InletCorrection(capacity, fullLoadPower, polyExponent, ratedDischargePressure, ratedInletPressure, motorEfficiency, fullLoadDischargePressure, fullLoadDischargePressure, inletPressure, atmosphericPressure);
    }

    Compressors::Output output;
    if (computeFrom == Compressors::ComputeFrom::PercentagePower)
        output = compMethod.calculateFromPerkW(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PercentageCapacity)
        output = compMethod.calculateFromPerC(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PowerMeasured)
        output = compMethod.calculateFromkWMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::CapacityMeasured)
        output = compMethod.calculateFromCMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PowerFactor)
    {
        const double computeFromPFVoltage = getDouble("computeFromPFVoltage", inp);
        const double computeFromPFAmps = getDouble("computeFromPFAmps", inp);
        output = compMethod.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
    }

    else
        ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Compute Method in input").c_str());

    setR("reRatedFlow", compMethod.C_fl_Adjusted);
    setR("reRatedPower", compMethod.kW_fl_Adjusted);
    setR("reRatedFlowMax", compMethod.C_max_Adjusted);
    setR("reRatedPowerMax", compMethod.kW_max_Adjusted);

    setR("powerCalculated", output.kW_Calc);
    setR("capacityCalculated", output.C_Calc);
    setR("percentagePower", output.PerkW);
    setR("percentageCapacity", output.C_Per);
}

void compressorsModulationWithUnload(Compressors::CompressorType compressorType, Compressors::ControlType controlType, Compressors::Stage stageType, Compressors::Lubricant lubricantType)
{
    const double powerAtFullLoad = getDouble("powerAtFullLoad", inp);
    std::cout << "powerAtFullLoad: " <<  powerAtFullLoad << std::endl;
    const double capacityAtFullLoad = getDouble("capacityAtFullLoad", inp);
    std::cout << "capacityAtFullLoad: " <<  capacityAtFullLoad << std::endl;
    const double receiverVolume = getDouble("receiverVolume", inp);
    std::cout << "receiverVolume: " <<  receiverVolume << std::endl;

    const int computeFrom = getInteger("computeFrom");
    const double computeFromVal = getDouble("computeFromVal", inp);
    const bool applyPressureInletCorrection = getBool("applyPressureInletCorrection");

    const double powerMax = getDouble("powerMax", inp);
    std::cout << "powerMax: " <<  powerMax << std::endl;
    const double powerAtNolLoad = getDouble("powerAtNolLoad", inp);
    std::cout << "powerAtNolLoad: " <<  powerAtNolLoad << std::endl;
    const double dischargePsiFullLoad = getDouble("dischargePsiFullLoad", inp);
    std::cout << "dischargePsiFullLoad: " <<  dischargePsiFullLoad << std::endl;
    const double dischargePsiMax = getDouble("dischargePsiMax", inp);
    std::cout << "dischargePsiMax: " <<  dischargePsiMax << std::endl;
    const double modulatingPsi = getDouble("modulatingPsi", inp);
    std::cout << "modulatingPsi: " <<  modulatingPsi << std::endl;
    const double atmosphericPsi = getDouble("atmosphericPsi", inp);
    std::cout << "atmosphericPsi: " <<  atmosphericPsi << std::endl;
    const double unloadPointCapacity = getDouble("unloadPointCapacity", inp);
    std::cout << "unloadPointCapacity: " <<  unloadPointCapacity << std::endl;
    const double blowdownTime = getDouble("blowdownTime", inp);
    std::cout << "blowdownTime: " <<  blowdownTime << std::endl;
    const double unloadSumpPressure = getDouble("unloadSumpPressure", inp);
    std::cout << "unloadSumpPressure: " <<  unloadSumpPressure << std::endl;

    
    auto compMethod = Compressors_ModulationWithUnload(powerAtFullLoad, capacityAtFullLoad, receiverVolume, powerMax, powerAtNolLoad, dischargePsiFullLoad, dischargePsiMax, modulatingPsi, atmosphericPsi, unloadPointCapacity, controlType, blowdownTime, unloadSumpPressure);

    if (applyPressureInletCorrection)
    {
        const double capacity = getDouble("capacity", inp);
        const double fullLoadPower = getDouble("fullLoadPower", inp);
        const double polyExponent = getDouble("polyExponent", inp);
        const double ratedDischargePressure = getDouble("ratedDischargePressure", inp);
        const double ratedInletPressure = getDouble("ratedInletPressure", inp);
        const double motorEfficiency = getDouble("motorEfficiency", inp);
        const double fullLoadDischargePressure = getDouble("fullLoadDischargePressure", inp);
        const double maxDischargePressure = getDouble("maxDischargePressure", inp);
        const double inletPressure = getDouble("inletPressure", inp);
        const double atmosphericPressure = getDouble("atmosphericPressure", inp);

        compMethod.Pressure_InletCorrection(capacity, fullLoadPower, polyExponent, ratedDischargePressure, ratedInletPressure, motorEfficiency, fullLoadDischargePressure, fullLoadDischargePressure, inletPressure, atmosphericPressure);
    }

    Compressors::Output output;
    if (computeFrom == Compressors::ComputeFrom::PercentagePower)
        output = compMethod.calculateFromPerkW(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PercentageCapacity)
    {
        output = compMethod.calculateFromPerC(computeFromVal);
    }
    else if (computeFrom == Compressors::ComputeFrom::PowerMeasured)
        output = compMethod.calculateFromkWMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::CapacityMeasured)
        output = compMethod.calculateFromCMeasured(computeFromVal);
    else if (computeFrom == Compressors::ComputeFrom::PowerFactor)
    {
        const double computeFromPFVoltage = getDouble("computeFromPFVoltage", inp);
        const double computeFromPFAmps = getDouble("computeFromPFAmps", inp);
        output = compMethod.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
    }
    else
        ThrowTypeError(std::string("Compressors Centrifugal: calculator : Invalid Compute Method in input").c_str());

    std::cout << "=================" << std::endl;
    setR("reRatedFlow", compMethod.C_fl_Adjusted);
    setR("reRatedPower", compMethod.kW_fl_Adjusted);
    setR("reRatedFlowMax", compMethod.C_max_Adjusted);
    setR("reRatedPowerMax", compMethod.kW_max_Adjusted);

    setR("powerCalculated", output.kW_Calc);
    setR("capacityCalculated", output.C_Calc);
    setR("percentagePower", output.PerkW);
    setR("percentageCapacity", output.C_Per);
}

void compressorMultiStepUnloading(Compressors::CompressorType compressorType, Compressors::ControlType controlType, Compressors::Stage stageType, Compressors::Lubricant lubricantType)
{
}

void compressorVFD(Compressors::CompressorType compressorType, Compressors::ControlType controlType, Compressors::Stage stageType, Compressors::Lubricant lubricantType)
{
}

NAN_METHOD(CompressorsCalc)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        int compressorType = getInteger("compressorType");
        int controlType = getInteger("controlType");

        Compressors::CompressorType CompressorType = (Compressors::CompressorType)compressorType;
        Compressors::ControlType ControlType = (Compressors::ControlType)controlType;

        if (compressorType == Compressors::CompressorType::Centrifugal)
            compressorsCalcCentrifugal(ControlType);
        else
        {
            int stageType = getInteger("stageType");
            int lubricantType = getInteger("lubricantType");

            Compressors::Stage StageType = (Compressors::Stage)stageType;
            Compressors::Lubricant LubricantType = (Compressors::Lubricant)lubricantType;

            if (compressorType == Compressors::CompressorType::Screw)
            {
                if (lubricantType == Compressors::Lubricant::Injected && (stageType == Compressors::Stage::Single || stageType == Compressors::Stage::Two))
                {
                    if (controlType == Compressors::ControlType::LoadUnload)
                    {
                        compressorsLoadUnload(CompressorType, ControlType, StageType, LubricantType);
                    }
                    else if (controlType == Compressors::ControlType::ModulationWOUnload)
                    {
                        compressorsModulationWOUnload(CompressorType, ControlType, StageType, LubricantType);
                    }
                    else if (controlType == Compressors::ControlType::ModulationUnload || controlType == Compressors::ControlType::VariableDisplacementUnload)
                    {
                        compressorsModulationWithUnload(CompressorType, ControlType, StageType, LubricantType);
                    }
                    else if (controlType == Compressors::ControlType::VFD)
                    {
                        compressorVFD(CompressorType, ControlType, StageType, LubricantType);
                    }
                    else if (controlType == Compressors::ControlType::StartStop)
                    {
                        compressorsStartStop(CompressorType, ControlType, StageType, LubricantType);
                    }
                }
                else if (lubricantType == Compressors::Lubricant::Free && stageType == Compressors::Stage::Two)
                {
                    if (controlType == Compressors::ControlType::LoadUnload)
                    {
                        compressorsLoadUnload(CompressorType, ControlType, StageType, LubricantType);
                    }
                    else if (controlType == Compressors::ControlType::StartStop)
                    {
                        compressorsStartStop(CompressorType, ControlType, StageType, LubricantType);
                    }
                    else if (controlType == Compressors::ControlType::VFD)
                    {
                        compressorVFD(CompressorType, ControlType, StageType, LubricantType);
                    }
                }
            }
            else if (compressorType == Compressors::CompressorType::Reciprocating)
            {
                if (stageType == Compressors::Stage::Two && controlType == Compressors::ControlType::MultiStepUnloading)
                {
                    //Per Alex Botts: "multi step unloading is identical to LoadUnload"
                    // compressorMultiStepUnloading(CompressorType, ControlType, StageType, LubricantType);
                    compressorsLoadUnload(CompressorType, ControlType, StageType, LubricantType);
                }
                else if (stageType == Compressors::Stage::Single || stageType == Compressors::Stage::Two)
                {
                    if (controlType == Compressors::ControlType::LoadUnload)
                    {
                        compressorsLoadUnload(CompressorType, ControlType, StageType, LubricantType);
                    }
                    else if (controlType == Compressors::ControlType::StartStop)
                    {
                        compressorsStartStop(CompressorType, ControlType, StageType, LubricantType);
                    }
                }
            }
        }

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Compressors - calculator: " + what).c_str());
    }
}

NAN_METHOD(CompEEM_ReduceAirLeaks)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double C_fl = getDouble("C_fl", inp);
        const double C_usage = getDouble("C_usage", inp);
        const double C_lk = getDouble("C_lk", inp);
        const double PerC_lkred = getDouble("PerC_lkred", inp);

        auto output = CompressorEEMs::ReduceAirLeaks(C_fl, C_usage, C_lk, PerC_lkred);

        setR("C_lkred", output.C_lkred);
        setR("C_usage_lkred", output.C_usage_lkred);
        setR("PerC_lkred", output.PerC_lkred);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Compressors - EEM - ReduceAirLeaks: " + what).c_str());
    }
}

NAN_METHOD(CompEEM_ImproveEndUseEfficiency)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double C_fl = getDouble("C_fl", inp);
        const double C_usage = getDouble("C_usage", inp);
        const double C_avgaf_red = getDouble("C_avgaf_red", inp);

        auto output = CompressorEEMs::ImproveEndUseEfficiency(C_fl, C_usage, C_avgaf_red);

        setR("C_af_red", output.C_af_red);
        setR("CPer_af_red", output.CPer_af_red);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Compressors - EEM - ImproveEndUseEfficiency: " + what).c_str());
    }
}

NAN_METHOD(CompEEM_ReduceSystemAirPressure)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double C_fl = getDouble("C_fl", inp);
        const double C_usage = getDouble("C_usage", inp);
        const double P_fl = getDouble("P_fl", inp);
        const double kW_fl = getDouble("kW_fl", inp);
        const double P_rpred = getDouble("P_rpred", inp);
        const double P_alt = getDouble("P_alt", inp);
        const double P_atm = getDouble("P_atm", inp);

        auto output = CompressorEEMs::ReduceSystemAirPressure(C_fl, C_usage, P_fl, kW_fl, P_rpred, P_alt, P_atm);

        setR("P_fl_rpred", output.P_fl_rpred);
        setR("kW_fl_rpadj", output.kW_fl_rpadj);
        setR("C_usage_rpred", output.C_usage_rpred);
        setR("PerC_rpred", output.PerC_rpred);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Compressors - EEM - ReduceSystemAirPressure: " + what).c_str());
    }
}

NAN_METHOD(CompEEM_AdjustCascadingSetPoint)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double C_fl = getDouble("C_fl", inp);
        const double C_usage = getDouble("C_usage", inp);
        const double P_fl = getDouble("P_fl", inp);
        const double kW_fl = getDouble("kW_fl", inp);
        const double P_fl_adj = getDouble("P_fl_adj", inp);
        const double P_alt = getDouble("P_alt", inp);
        const double P_atm = getDouble("P_atm", inp);

        auto output = CompressorEEMs::AdjustCascadingSetPoint(C_fl, C_usage, P_fl, kW_fl, P_fl_adj, P_alt, P_atm);

        setR("kW_fl_adj", output.kW_fl_adj);
        setR("C_usage_adj", output.C_usage_adj);
        setR("PerC_adj", output.PerC_adj);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Compressors - EEM - AdjustCascadingSetPoint: " + what).c_str());
    }
}

NAN_METHOD(CompEEM_PressureReductionSaving)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double operatingHours = getDouble("operatingHours", inp);
        const double costPerkWh = getDouble("costPerkWh", inp);
        const double kW_fl_rated = getDouble("kW_fl_rated", inp);
        const double P_fl_rated = getDouble("P_fl_rated", inp);
        const double dischargePresBaseline = getDouble("dischargePresBaseline", inp);
        const double dischargePresMod = getDouble("dischargePresMod", inp);
        const double P_alt = getDouble("P_alt", inp);
        const double P_atm = getDouble("P_atm", inp);

        auto output = CompressorEEMs::PressureReductionSaving(operatingHours, costPerkWh, kW_fl_rated, P_fl_rated,
                                                              dischargePresBaseline, dischargePresMod, P_alt, P_atm);

        setR("kW_savings", output.kW_savings);
        setR("kWh_savings", output.kWh_savings);
        setR("cost_savings", output.cost_savings);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Compressors - EEM - PressureReductionSaving: " + what).c_str());
    }
}

NAN_METHOD(CompEEM_kWAdjusted)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        const double kW_fl_rated = getDouble("kW_fl_rated", inp);
        const double P_fl_rated = getDouble("P_fl_rated", inp);
        const double P_discharge = getDouble("P_discharge", inp);
        const double P_alt = getDouble("P_alt", inp);
        const double P_atm = getDouble("P_atm", inp);

        auto kW_adjusted = CompressorEEMs::kWAdjusted(kW_fl_rated, P_fl_rated, P_discharge, P_alt, P_atm);

        setR("kW_adjusted", kW_adjusted);

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in Compressors - EEM - CompEEM_kWAdjusted: " + what).c_str());
    }
}