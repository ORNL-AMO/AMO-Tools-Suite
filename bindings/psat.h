#ifndef AMO_TOOLS_SUITE_PSAT_BRIDGE_H
#define AMO_TOOLS_SUITE_PSAT_BRIDGE_H

#include <iostream>

#include <map>
#include <unordered_map>
#include <nan.h>
#include <node.h>
#include <vector>
#include <array>
#include "results/Results.h"
#include "results/InputData.h"
#include "calculator/motor/EstimateFLA.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/pump/OptimalPrePumpEff.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/OptimalDeviationFactor.h"
#include "calculator/pump/HeadTool.h"
#include "calculator/util/Conversion.h"

using namespace Nan;
using namespace v8;

//
//// Setup
//
//Isolate* iso;
Local<Object> inp;
Local<Object> r;

//NAN function for fetching value associated with provided key
double Get(std::string const & nm) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Value> rObj = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in psat.h: " + nm + " not present in object").c_str());
	}
	return Nan::To<double>(rObj).FromJust();
}

//NAN function for binding data to anonymous object
void SetR(const char *nm, double n)
{
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local<Number> getNum = Nan::New<Number>(n);
    Nan::Set(r, getName, getNum);
}

NAN_METHOD(headToolSuctionTank)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    const double specificGravity = Get("specificGravity");
    const double flowRate = Get("flowRate");
    const double suctionPipeDiameter = Get("suctionPipeDiameter");
    const double suctionTankGasOverPressure = Get("suctionTankGasOverPressure");
    const double suctionTankFluidSurfaceElevation = Get("suctionTankFluidSurfaceElevation");
    const double suctionLineLossCoefficients = Get("suctionLineLossCoefficients");
    const double dischargePipeDiameter = Get("dischargePipeDiameter");
    const double dischargeGaugePressure = Get("dischargeGaugePressure");
    const double dischargeGaugeElevation = Get("dischargeGaugeElevation");
    const double dischargeLineLossCoefficients = Get("dischargeLineLossCoefficients");

    //Calculation procedure
    auto rv = HeadToolSuctionTank(specificGravity, flowRate, suctionPipeDiameter, suctionTankGasOverPressure,
                                  suctionTankFluidSurfaceElevation, suctionLineLossCoefficients, dischargePipeDiameter,
                                  dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients)
                  .calculate();

    //NAN return data
    SetR("differentialElevationHead", rv.elevationHead);
    SetR("differentialPressureHead", rv.pressureHead);
    SetR("differentialVelocityHead", rv.velocityHeadDifferential);
    SetR("estimatedSuctionFrictionHead", rv.suctionHead);
    SetR("estimatedDischargeFrictionHead", rv.dischargeHead);
    SetR("pumpHead", rv.pumpHead);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(headTool)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    const double specificGravity = Get("specificGravity");
    const double flowRate = Get("flowRate");
    const double suctionPipeDiameter = Get("suctionPipeDiameter");
    const double suctionGaugePressure = Get("suctionGaugePressure");
    const double suctionGaugeElevation = Get("suctionGaugeElevation");
    const double suctionLineLossCoefficients = Get("suctionLineLossCoefficients");
    const double dischargePipeDiameter = Get("dischargePipeDiameter");
    const double dischargeGaugePressure = Get("dischargeGaugePressure");
    const double dischargeGaugeElevation = Get("dischargeGaugeElevation");
    const double dischargeLineLossCoefficients = Get("dischargeLineLossCoefficients");

    //Calculation procedure
    auto rv = HeadTool(specificGravity, flowRate, suctionPipeDiameter, suctionGaugePressure,
                       suctionGaugeElevation, suctionLineLossCoefficients, dischargePipeDiameter,
                       dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients)
                  .calculate();

    //NAN return data
    SetR("differentialElevationHead", rv.elevationHead);
    SetR("differentialPressureHead", rv.pressureHead);
    SetR("differentialVelocityHead", rv.velocityHeadDifferential);
    SetR("estimatedSuctionFrictionHead", rv.suctionHead);
    SetR("estimatedDischargeFrictionHead", rv.dischargeHead);
    SetR("pumpHead", rv.pumpHead);
    info.GetReturnValue().Set(r);
}

// Fields

Motor::LineFrequency line()
{
    unsigned val = static_cast<unsigned>(Get("line_frequency"));
    return static_cast<Motor::LineFrequency>(val);
}
Motor::EfficiencyClass effCls()
{
    unsigned val = static_cast<unsigned>(Get("efficiency_class"));
    return static_cast<Motor::EfficiencyClass>(val);
}
Motor::Drive drive()
{
    unsigned val = static_cast<unsigned>(Get("drive"));
    return static_cast<Motor::Drive>(val);
}
Pump::Style style()
{
    unsigned val = static_cast<unsigned>(Get("pump_style"));
    return static_cast<Pump::Style>(val);
}
Motor::LoadEstimationMethod loadEstimationMethod()
{
    unsigned val = static_cast<unsigned>(Get("load_estimation_method"));
    return static_cast<Motor::LoadEstimationMethod>(val);
}
Pump::SpecificSpeed speed()
{
    unsigned val = static_cast<unsigned>(Get("fixed_speed"));
    return static_cast<Pump::SpecificSpeed>(val);
}

NAN_METHOD(resultsExisting)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    Pump::Style style1 = style();
    double pumpSpecified = Get("pump_specified");
    double pumpRatedSpeed = Get("pump_rated_speed");
    Motor::Drive drive1 = drive();
    double kinematicViscosity = 0;
    double specificGravity = Get("specific_gravity");
    int stages = static_cast<int>(Get("stages"));
    double specifiedDriveEfficiency;
    if (drive1 == Motor::Drive::SPECIFIED)
    {
        specifiedDriveEfficiency = Get("specifiedDriveEfficiency");
    }
    else
    {
        specifiedDriveEfficiency = 100.0;
    }
    Motor::LineFrequency lineFrequency = line();
    double motorRatedPower = Get("motor_rated_power");
    double motorRatedSpeed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double specifiedMotorEfficiency = Get("efficiency");
    double motorRatedVoltage = Get("motor_rated_voltage");
    double motorRatedFLA = Get("motor_rated_fla");
    double flowRate = Get("flow_rate");
    double head = Get("head");
    Motor::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();
    double motorFieldPower = Get("motor_field_power");
    double motorFieldCurrent = Get("motor_field_current");
    double motorFieldVoltage = Get("motor_field_voltage");
    double operatingHours = Get("operating_hours");
    double costKwHour = Get("cost_kw_hour");

    //Calculation procedure
    pumpSpecified = Conversion(pumpSpecified).percentToFraction();
    specifiedDriveEfficiency = Conversion(specifiedDriveEfficiency).percentToFraction();
    Pump::Input pump(style1, pumpSpecified, pumpRatedSpeed, drive1, kinematicViscosity,
                     specificGravity, stages, Pump::SpecificSpeed::FIXED_SPEED, specifiedDriveEfficiency);
    Motor motor(lineFrequency, motorRatedPower, motorRatedSpeed, efficiencyClass, specifiedMotorEfficiency,
                motorRatedVoltage, motorRatedFLA);
    Pump::FieldData fd(flowRate, head, loadEstimationMethod1, motorFieldPower,
                       motorFieldCurrent, motorFieldVoltage);
    PSATResult psat(pump, motor, fd, operatingHours, costKwHour);

    try
    {
        auto ex = psat.calculateExisting();
        //perform conversions for return object
        ex.pumpEfficiency = Conversion(ex.pumpEfficiency).fractionToPercent();
        ex.motorEfficiency = Conversion(ex.motorEfficiency).fractionToPercent();
        ex.motorPowerFactor = Conversion(ex.motorPowerFactor).fractionToPercent();
        ex.driveEfficiency = Conversion(ex.driveEfficiency).fractionToPercent();
        ex.annualCost = Conversion(ex.annualCost).manualConversion(1000.0);
        double annualSavingsPotentialResult = Conversion(psat.getAnnualSavingsPotential()).manualConversion(1000.0);

        //NAN return data
        SetR("pump_efficiency", ex.pumpEfficiency);
        SetR("motor_rated_power", ex.motorRatedPower);
        SetR("motor_shaft_power", ex.motorShaftPower);
        SetR("pump_shaft_power", ex.pumpShaftPower);
        SetR("motor_efficiency", ex.motorEfficiency);
        SetR("motor_power_factor", ex.motorPowerFactor);
        SetR("motor_current", ex.motorCurrent);
        SetR("motor_power", ex.motorPower);
        SetR("load_factor", ex.loadFactor);
        SetR("drive_efficiency", ex.driveEfficiency);
        SetR("annual_energy", ex.annualEnergy);
        SetR("annual_cost", ex.annualCost);
        SetR("annual_savings_potential", annualSavingsPotentialResult);
        SetR("optimization_rating", psat.getOptimizationRating());
        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in resultsExisting - psat.h: " + what).c_str());
        info.GetReturnValue().Set(r);
    }
}

NAN_METHOD(resultsModified)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    Pump::SpecificSpeed fixedSpeed = speed();
    Pump::Style style1 = style();
    double pumpSpecified = Get("pump_specified");
    double pumpRatedSpeed = Get("pump_rated_speed");
    Motor::Drive drive1 = drive();
    double kinematicViscosity = Get("kinematic_viscosity");
    double specificGravity = Get("specific_gravity");
    int stages = static_cast<int>(Get("stages"));
    double specifiedDriveEfficiency;
    if (drive1 == Motor::Drive::SPECIFIED)
    {
        specifiedDriveEfficiency = Get("specifiedDriveEfficiency");
    }
    else
    {
        specifiedDriveEfficiency = 100.0;
    }
    Motor::LineFrequency lineFrequency = line();
    double motorRatedPower = Get("motor_rated_power");
    double motorRatedSpeed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double specifiedMotorEfficiency = Get("efficiency");
    double motorRatedVoltage = Get("motor_rated_voltage");
    double motorRatedFLA = Get("motor_rated_fla");
    double margin = Get("margin");
    double flowRate = Get("flow_rate");
    double head = Get("head");
    Motor::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();
    double motorFieldPower = Get("motor_field_power");
    double motorFieldCurrent = Get("motor_field_current");
    double motorFieldVoltage = Get("motor_field_voltage");
    double operatingHours = Get("operating_hours");
    double costKwHour = Get("cost_kw_hour");

    //Calculation procedure
    specifiedDriveEfficiency = Conversion(specifiedDriveEfficiency).percentToFraction();
    pumpSpecified = Conversion(pumpSpecified).percentToFraction();
    Pump::Input pump(style1, pumpSpecified, pumpRatedSpeed, drive1, kinematicViscosity,
                     specificGravity, stages, fixedSpeed, specifiedDriveEfficiency);

    Motor motor(lineFrequency, motorRatedPower, motorRatedSpeed, efficiencyClass, specifiedMotorEfficiency,
                motorRatedVoltage, motorRatedFLA, margin);

    Pump::FieldData fd(flowRate, head, loadEstimationMethod1, motorFieldPower,
                       motorFieldCurrent, motorFieldVoltage);

    PSATResult psat(pump, motor, fd, operatingHours, costKwHour);
    try
    {
        auto mod = psat.calculateModified();
        //perform conversions for return object
        mod.pumpEfficiency = Conversion(mod.pumpEfficiency).fractionToPercent();
        mod.motorEfficiency = Conversion(mod.motorEfficiency).fractionToPercent();
        mod.motorPowerFactor = Conversion(mod.motorPowerFactor).fractionToPercent();
        mod.driveEfficiency = Conversion(mod.driveEfficiency).fractionToPercent();
        mod.annualCost = Conversion(mod.annualCost).manualConversion(1000.0);
        double annualSavingsPotential = Conversion(psat.getAnnualSavingsPotential()).manualConversion(1000.0);

        //NAN return data
        SetR("pump_efficiency", mod.pumpEfficiency);
        SetR("motor_rated_power", mod.motorRatedPower);
        SetR("motor_shaft_power", mod.motorShaftPower);
        SetR("pump_shaft_power", mod.pumpShaftPower);
        SetR("motor_efficiency", mod.motorEfficiency);
        SetR("motor_power_factor", mod.motorPowerFactor);
        SetR("motor_current", mod.motorCurrent);
        SetR("motor_power", mod.motorPower);
        SetR("load_factor", mod.loadFactor);
        SetR("drive_efficiency", mod.driveEfficiency);
        SetR("annual_energy", mod.annualEnergy);
        SetR("annual_cost", mod.annualCost);
        SetR("annual_savings_potential", annualSavingsPotential);
        SetR("optimization_rating", psat.getOptimizationRating());
        info.GetReturnValue().Set(r);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in resultsModified - psat.h: " + what).c_str());
        info.GetReturnValue().Set(r);
    }
}

NAN_METHOD(estFLA)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    double motor_rated_power = Get("motor_rated_power");
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::LineFrequency l = line();
    Motor::EfficiencyClass e = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_voltage = Get("motor_rated_voltage");

    //Calculation procedure
    EstimateFLA fla(motor_rated_power, motor_rated_speed, l, e, efficiency, motor_rated_voltage);
    fla.calculate();

    //NAN return data
    info.GetReturnValue().Set(fla.getEstimatedFLA());
}

NAN_METHOD(motorPerformance)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    Motor::LineFrequency l = line();
    double motorRatedSpeed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = Get("efficiency");
    double motorRatedPower = Get("motor_rated_power");
    double loadFactor = Get("load_factor");
    double motorRatedVoltage = Get("motor_rated_voltage");
    double motorRatedFLA = Get("motor_rated_fla");

    try
    {
        //Calculation procedure
        MotorEfficiency mef(l, motorRatedSpeed, efficiencyClass, motorRatedPower);
        double motorEfficiencyVal = mef.calculate(loadFactor, efficiency);
        double motorEfficiencyResult = Conversion(motorEfficiencyVal).fractionToPercent();
        MotorCurrent mc(motorRatedPower, motorRatedSpeed, l, efficiencyClass, efficiency, loadFactor,
                        motorRatedVoltage);
        double motorCurrentVal = mc.calculateCurrent(motorRatedFLA);
        double motorCurrentResult = Conversion(motorCurrentVal / motorRatedFLA).fractionToPercent();
        MotorPowerFactor motorPowerFactor(motorRatedPower, loadFactor, motorCurrentVal, motorEfficiencyVal, motorRatedVoltage);
        double motorPowerFactorVal = motorPowerFactor.calculate();
        double motorPowerFactorResult = Conversion(motorPowerFactorVal).fractionToPercent();

        //NAN return data
        SetR("efficiency", motorEfficiencyResult);
        SetR("motor_current", motorCurrentResult);
        SetR("motor_power_factor", motorPowerFactorResult);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in motorPerformance - psat.h: " + what).c_str());
        info.GetReturnValue().Set(0);
    }

    info.GetReturnValue().Set(r);
}

NAN_METHOD(pumpEfficiency)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    Pump::Style s = style();
    double flow = Get("flow_rate");

    //Calculation procedure
    OptimalPrePumpEff pef(s, flow);
    double v = pef.calculate();
    double odf = OptimalDeviationFactor(flow).calculate();
    double max = v * odf;

    //NAN return data
    SetR("average", v);
    SetR("max", max);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(achievableEfficiency)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    double specificSpeed = Get("specific_speed");
    Pump::Style s = style();

    //Calculation procedure
    double optimalSpecificSpeedCorrectionVal = OptimalSpecificSpeedCorrection(s, specificSpeed).calculate();
    double optimalSpecificSpeedCorrectionResult = Conversion(optimalSpecificSpeedCorrectionVal).fractionToPercent();

    //NAN return data
    info.GetReturnValue().Set(optimalSpecificSpeedCorrectionResult);
}

NAN_METHOD(nema)
{
    //NAN initialize data
    // inp = Nan::To<Object>(info[0]).ToLocalChecked();
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    Motor::LineFrequency l = line();
    double motorRatedSpeed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = Get("efficiency");
    double motorRatedPower = Get("motor_rated_power");
    double loadFactor = Get("load_factor");
    try
    {
        //Calculation procedure
        double motorEfficiencyVal = MotorEfficiency(l, motorRatedSpeed, efficiencyClass, motorRatedPower).calculate(loadFactor, efficiency);
        double motorEfficiencyResult = Conversion(motorEfficiencyVal).fractionToPercent();

        //NAN return data
        info.GetReturnValue().Set(motorEfficiencyResult);
    }
    catch (std::runtime_error const &e)
    {
        std::string const what = e.what();
        ThrowError(std::string("std::runtime_error thrown in nema - psat.h: " + what).c_str());
        info.GetReturnValue().Set(0);
    }
}

NAN_METHOD(motorPowerFactor)
{
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	const double motorRatedPower = Get("motorRatedPower");
	const double loadFactor = Get("loadFactor");
	const double motorCurrent = Get("motorCurrent");
	const double motorEfficiency = Get("motorEfficiency");
	const double ratedVoltage = Get("ratedVoltage");

	MotorPowerFactor motorPowerFactor(motorRatedPower, loadFactor, motorCurrent, motorEfficiency, ratedVoltage);
	double motorPowerFactorVal = motorPowerFactor.calculate();
    double motorPowerFactorResult = Conversion(motorPowerFactorVal).fractionToPercent();
	Local<Number> retval = Nan::New(motorPowerFactorResult);
	info.GetReturnValue().Set(retval);
}

NAN_METHOD(motorCurrent)
{
	inp = Nan::To<Object>(info[0]).ToLocalChecked();
	r = Nan::New<Object>();

	const double motorRatedPower = Get("motorRatedPower");
    const double motorRPM = Get("motorRPM");
    Motor::LineFrequency lineFrequency = line();
    Motor::EfficiencyClass efficiencyClass = effCls();
    const double specifiedEfficiency = Get("specifiedEfficiency");
	const double loadFactor = Get("loadFactor");
	const double ratedVoltage = Get("ratedVoltage");

    const double fullLoadAmps = Get("fullLoadAmps");

	MotorCurrent motorCurrent(motorRatedPower, motorRPM, lineFrequency, efficiencyClass, specifiedEfficiency, loadFactor, ratedVoltage);
	double motorCurrentVal = motorCurrent.calculateCurrent(fullLoadAmps);
	Local<Number> retval = Nan::New(motorCurrentVal);
	info.GetReturnValue().Set(retval);
}


#endif //AMO_TOOLS_SUITE_PSAT_BRIDGE_H
