#ifndef AMO_TOOLS_SUITE_PSAT_BRIDGE_H
#define AMO_TOOLS_SUITE_PSAT_BRIDGE_H

#include "NanDataConverters.h"

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

NAN_METHOD(headToolSuctionTank)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    const double specificGravity = getDouble("specificGravity");
    const double flowRate = getDouble("flowRate");
    const double suctionPipeDiameter = getDouble("suctionPipeDiameter");
    const double suctionTankGasOverPressure = getDouble("suctionTankGasOverPressure");
    const double suctionTankFluidSurfaceElevation = getDouble("suctionTankFluidSurfaceElevation");
    const double suctionLineLossCoefficients = getDouble("suctionLineLossCoefficients");
    const double dischargePipeDiameter = getDouble("dischargePipeDiameter");
    const double dischargeGaugePressure = getDouble("dischargeGaugePressure");
    const double dischargeGaugeElevation = getDouble("dischargeGaugeElevation");
    const double dischargeLineLossCoefficients = getDouble("dischargeLineLossCoefficients");

    //Calculation procedure
    auto rv = HeadToolSuctionTank(specificGravity, flowRate, suctionPipeDiameter, suctionTankGasOverPressure,
                                  suctionTankFluidSurfaceElevation, suctionLineLossCoefficients, dischargePipeDiameter,
                                  dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients)
                  .calculate();

    //NAN return data
    setR("differentialElevationHead", rv.elevationHead);
    setR("differentialPressureHead", rv.pressureHead);
    setR("differentialVelocityHead", rv.velocityHeadDifferential);
    setR("estimatedSuctionFrictionHead", rv.suctionHead);
    setR("estimatedDischargeFrictionHead", rv.dischargeHead);
    setR("pumpHead", rv.pumpHead);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(headTool)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    const double specificGravity = getDouble("specificGravity");
    const double flowRate = getDouble("flowRate");
    const double suctionPipeDiameter = getDouble("suctionPipeDiameter");
    const double suctionGaugePressure = getDouble("suctionGaugePressure");
    const double suctionGaugeElevation = getDouble("suctionGaugeElevation");
    const double suctionLineLossCoefficients = getDouble("suctionLineLossCoefficients");
    const double dischargePipeDiameter = getDouble("dischargePipeDiameter");
    const double dischargeGaugePressure = getDouble("dischargeGaugePressure");
    const double dischargeGaugeElevation = getDouble("dischargeGaugeElevation");
    const double dischargeLineLossCoefficients = getDouble("dischargeLineLossCoefficients");

    //Calculation procedure
    auto rv = HeadTool(specificGravity, flowRate, suctionPipeDiameter, suctionGaugePressure,
                       suctionGaugeElevation, suctionLineLossCoefficients, dischargePipeDiameter,
                       dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients)
                  .calculate();

    //NAN return data
    setR("differentialElevationHead", rv.elevationHead);
    setR("differentialPressureHead", rv.pressureHead);
    setR("differentialVelocityHead", rv.velocityHeadDifferential);
    setR("estimatedSuctionFrictionHead", rv.suctionHead);
    setR("estimatedDischargeFrictionHead", rv.dischargeHead);
    setR("pumpHead", rv.pumpHead);
    info.GetReturnValue().Set(r);
}

// Fields

Motor::LineFrequency line()
{
    unsigned val = static_cast<unsigned>(getDouble("line_frequency"));
    return static_cast<Motor::LineFrequency>(val);
}
Motor::EfficiencyClass effCls()
{
    unsigned val = static_cast<unsigned>(getDouble("efficiency_class"));
    return static_cast<Motor::EfficiencyClass>(val);
}
Motor::Drive drive()
{
    unsigned val = static_cast<unsigned>(getDouble("drive"));
    return static_cast<Motor::Drive>(val);
}
Pump::Style style()
{
    unsigned val = static_cast<unsigned>(getDouble("pump_style"));
    return static_cast<Pump::Style>(val);
}
Motor::LoadEstimationMethod loadEstimationMethod()
{
    unsigned val = static_cast<unsigned>(getDouble("load_estimation_method"));
    return static_cast<Motor::LoadEstimationMethod>(val);
}
Pump::SpecificSpeed speed()
{
    unsigned val = static_cast<unsigned>(getDouble("fixed_speed"));
    return static_cast<Pump::SpecificSpeed>(val);
}

NAN_METHOD(resultsExisting)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();
    Pump::Style style1 = style();
    double pumpSpecified = getDouble("pump_specified");
    double pumpRatedSpeed = getDouble("pump_rated_speed");
    Motor::Drive drive1 = drive();
    double kinematicViscosity = 0;
    double specificGravity = getDouble("specific_gravity");
    int stages = static_cast<int>(getDouble("stages"));
    double specifiedDriveEfficiency;
    if (drive1 == Motor::Drive::SPECIFIED)
    {
        specifiedDriveEfficiency = getDouble("specifiedDriveEfficiency");
    }
    else
    {
        specifiedDriveEfficiency = 100.0;
    }
    Motor::LineFrequency lineFrequency = line();
    double motorRatedPower = getDouble("motor_rated_power");
    double motorRatedSpeed = getDouble("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double specifiedMotorEfficiency = getDouble("efficiency");
    double motorRatedVoltage = getDouble("motor_rated_voltage");
    double motorRatedFLA = getDouble("motor_rated_fla");
    double flowRate = getDouble("flow_rate");
    double head = getDouble("head");
    Motor::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();
    double motorFieldPower = getDouble("motor_field_power");
    double motorFieldCurrent = getDouble("motor_field_current");
    double motorFieldVoltage = getDouble("motor_field_voltage");
    double operatingHours = getDouble("operating_hours");
    double costKwHour = getDouble("cost_kw_hour");

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
        setR("pump_efficiency", ex.pumpEfficiency);
        setR("motor_rated_power", ex.motorRatedPower);
        setR("motor_shaft_power", ex.motorShaftPower);
        setR("pump_shaft_power", ex.pumpShaftPower);
        setR("motor_efficiency", ex.motorEfficiency);
        setR("motor_power_factor", ex.motorPowerFactor);
        setR("motor_current", ex.motorCurrent);
        setR("motor_power", ex.motorPower);
        setR("load_factor", ex.loadFactor);
        setR("drive_efficiency", ex.driveEfficiency);
        setR("annual_energy", ex.annualEnergy);
        setR("annual_cost", ex.annualCost);
        setR("annual_savings_potential", annualSavingsPotentialResult);
        setR("optimization_rating", psat.getOptimizationRating());
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
    double pumpSpecified = getDouble("pump_specified");
    double pumpRatedSpeed = getDouble("pump_rated_speed");
    Motor::Drive drive1 = drive();
    double kinematicViscosity = getDouble("kinematic_viscosity");
    double specificGravity = getDouble("specific_gravity");
    int stages = static_cast<int>(getDouble("stages"));
    double specifiedDriveEfficiency;
    if (drive1 == Motor::Drive::SPECIFIED)
    {
        specifiedDriveEfficiency = getDouble("specifiedDriveEfficiency");
    }
    else
    {
        specifiedDriveEfficiency = 100.0;
    }
    Motor::LineFrequency lineFrequency = line();
    double motorRatedPower = getDouble("motor_rated_power");
    double motorRatedSpeed = getDouble("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double specifiedMotorEfficiency = getDouble("efficiency");
    double motorRatedVoltage = getDouble("motor_rated_voltage");
    double motorRatedFLA = getDouble("motor_rated_fla");
    double margin = getDouble("margin");
    double flowRate = getDouble("flow_rate");
    double head = getDouble("head");
    Motor::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();
    double motorFieldPower = getDouble("motor_field_power");
    double motorFieldCurrent = getDouble("motor_field_current");
    double motorFieldVoltage = getDouble("motor_field_voltage");
    double operatingHours = getDouble("operating_hours");
    double costKwHour = getDouble("cost_kw_hour");

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
        setR("pump_efficiency", mod.pumpEfficiency);
        setR("motor_rated_power", mod.motorRatedPower);
        setR("motor_shaft_power", mod.motorShaftPower);
        setR("pump_shaft_power", mod.pumpShaftPower);
        setR("motor_efficiency", mod.motorEfficiency);
        setR("motor_power_factor", mod.motorPowerFactor);
        setR("motor_current", mod.motorCurrent);
        setR("motor_power", mod.motorPower);
        setR("load_factor", mod.loadFactor);
        setR("drive_efficiency", mod.driveEfficiency);
        setR("annual_energy", mod.annualEnergy);
        setR("annual_cost", mod.annualCost);
        setR("annual_savings_potential", annualSavingsPotential);
        setR("optimization_rating", psat.getOptimizationRating());
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
    double motor_rated_power = getDouble("motor_rated_power");
    double motor_rated_speed = getDouble("motor_rated_speed");
    Motor::LineFrequency l = line();
    Motor::EfficiencyClass e = effCls();
    double efficiency = getDouble("efficiency");
    double motor_rated_voltage = getDouble("motor_rated_voltage");

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
    double motorRatedSpeed = getDouble("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = getDouble("efficiency");
    double motorRatedPower = getDouble("motor_rated_power");
    double loadFactor = getDouble("load_factor");
    double motorRatedVoltage = getDouble("motor_rated_voltage");
    double motorRatedFLA = getDouble("motor_rated_fla");

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
        setR("efficiency", motorEfficiencyResult);
        setR("motor_current", motorCurrentResult);
        setR("motor_power_factor", motorPowerFactorResult);
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
    double flow = getDouble("flow_rate");

    //Calculation procedure
    OptimalPrePumpEff pef(s, flow);
    double v = pef.calculate();
    double odf = OptimalDeviationFactor(flow).calculate();
    double max = v * odf;

    //NAN return data
    setR("average", v);
    setR("max", max);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(achievableEfficiency)
{
    //NAN initialize data
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    double specificSpeed = getDouble("specific_speed");
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
    double motorRatedSpeed = getDouble("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = getDouble("efficiency");
    double motorRatedPower = getDouble("motor_rated_power");
    double loadFactor = getDouble("load_factor");
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

#endif //AMO_TOOLS_SUITE_PSAT_BRIDGE_H
