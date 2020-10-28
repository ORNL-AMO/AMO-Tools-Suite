#include <nan.h>
#include <node.h>
#include <string>
#include <array>
#include <vector>
#include <exception>
#include <iostream>
#include "./NanDataConverters.h"
#include "calculator/util/CompressedAir.h"
#include "calculator/util/CompressedAirCentrifugal.h"

using namespace Nan;
using namespace v8;

void compressedAirCentrifugal()
{
    int controlType = getInteger("controlType");
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

    if(controlType == CompressedAirCentrifugal::ControlType::LoadUnload) {
        const double powerAtNoLoad = getDouble("powerAtNoLoad", inp);
        auto cacLUL = CompressedAirCentrifugal_LoadUnload(powerAtFullLoad, capacityAtFullLoad, powerAtNoLoad);

        if(adjustForDischargePressure) {
            const double fullLoadPressure = getDouble("fullLoadPressure", inp);
            cacLUL.AdjustDischargePressure(
                    {capacityAtFullLoad, capacityAtMinFullLoadPressure, capacityAtMaxFullLoadPressure},
                    {fullLoadPressure, minFullLoadPressure, maxFullLoadPressure}, fullLoadPressure);
        }

        CompressedAirCentrifugalBase::Output output;
        if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PercentagePower)
            output = cacLUL.calculateFromPerkW(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PercentageCapacity)
            output = cacLUL.calculateFromPerC(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PowerMeasured)
            output = cacLUL.calculateFromkWMeasured(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::CapacityMeasured)
            output = cacLUL.calculateFromCMeasured(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PowerFactor)
            output = cacLUL.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
        else ThrowTypeError(std::string("CompressedAirCentrifugal: calculator : Invalid Compute Method in input").c_str());

        setR("powerCalculated", output.kW_Calc);
        setR("capacityCalculated", output.C_Calc);
        setR("percentagePower", output.PerkW);
        setR("percentageCapacity", output.C_Per);
    }
    else if(controlType == CompressedAirCentrifugal::ControlType::ModulationUnload) {
        const double powerAtNoLoad = getDouble("powerAtNoLoad", inp);
        const double capacityAtMaxFullFlow = getDouble("capacityAtMaxFullFlow", inp);
        const double powerAtUnload = getDouble("powerAtUnload", inp);
        const double capacityAtUnload = getDouble("capacityAtUnload", inp);
        auto cacMUL = CompressedAirCentrifugal_ModulationUnload(powerAtFullLoad, capacityAtFullLoad, powerAtNoLoad, capacityAtMaxFullFlow, powerAtUnload, capacityAtUnload);

        if(adjustForDischargePressure) {
            const double fullLoadPressure = getDouble("fullLoadPressure", inp);
            const double maxPressure = getDouble("maxPressure", inp);
            cacMUL.AdjustDischargePressure(
                    {capacityAtFullLoad, capacityAtMinFullLoadPressure, capacityAtMaxFullLoadPressure},
                    {fullLoadPressure, minFullLoadPressure, maxFullLoadPressure}, fullLoadPressure, maxPressure);
        }

        CompressedAirCentrifugalBase::Output output;
        if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PercentagePower)
            output = cacMUL.calculateFromPerkW(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PercentageCapacity)
            output = cacMUL.calculateFromPerC(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PowerMeasured)
            output = cacMUL.calculateFromkWMeasured(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::CapacityMeasured)
            output = cacMUL.calculateFromCMeasured(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PowerFactor)
            output = cacMUL.calculateFromVIPFMeasured(computeFromVal, computeFromPFVoltage, computeFromPFAmps);
        else ThrowTypeError(std::string("CompressedAirCentrifugal: calculator : Invalid Compute Method in input").c_str());

        setR("powerCalculated", output.kW_Calc);
        setR("capacityCalculated", output.C_Calc);
        setR("percentagePower", output.PerkW);
        setR("percentageCapacity", output.C_Per);
    }
    else if(controlType == CompressedAirCentrifugal::ControlType::BlowOff) {
        const double powerAtBlowOff = getDouble("powerAtBlowOff", inp);
        const double surgeFlow = getDouble("surgeFlow", inp);
        const double percentageBlowOff = getDouble("percentageBlowOff", inp);
        auto cacBO = CompressedAirCentrifugal_BlowOff(powerAtFullLoad, capacityAtFullLoad, powerAtBlowOff, surgeFlow);

        if(adjustForDischargePressure) {
            const double fullLoadPressure = getDouble("fullLoadPressure", inp);
            cacBO.AdjustDischargePressure(
                    {capacityAtFullLoad, capacityAtMinFullLoadPressure, capacityAtMaxFullLoadPressure},
                    {fullLoadPressure, minFullLoadPressure, maxFullLoadPressure}, fullLoadPressure);
        }

        CompressedAirCentrifugalBase::OutputBlowOff output;
        if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PercentagePower)
            output = cacBO.calculateFromPerkW_BlowOff(computeFromVal, percentageBlowOff);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PercentageCapacity)
            output = cacBO.calculateFromPerC_BlowOff(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PowerMeasured)
            output = cacBO.calculateFromkWMeasured_BlowOff(computeFromVal, percentageBlowOff);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::CapacityMeasured)
            output = cacBO.calculateFromCMeasured_BlowOff(computeFromVal);
        else if(computeFrom == CompressedAirCentrifugal::ComputeFrom::PowerFactor)
            output = cacBO.calculateFromVIPFMeasured_BlowOff(computeFromVal, computeFromPFVoltage, computeFromPFAmps, percentageBlowOff);
        else ThrowTypeError(std::string("CompressedAirCentrifugal: calculator : Invalid Compute Method in input").c_str());

        setR("powerCalculated", output.kW_Calc);
        setR("capacityCalculated", output.C_Calc);
        setR("percentagePower", output.PerkW);
        setR("percentageCapacity", output.C_Per);
        setR("percentageBlowOff", output.blowPer);
        setR("surgeFlow", output.C_blow);
    }
    else ThrowTypeError(std::string("CompressedAirCentrifugal: calculator : Invalid Control Type in input").c_str());
}

NAN_METHOD(CompressedAir)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    try
    {
        int compressorType = getInteger("compressorType");

        if(compressorType == CompressedAir::CompressorType::Centrifugal) compressedAirCentrifugal();

        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in CompressedAir - calculator: " + what).c_str());
    }
}
