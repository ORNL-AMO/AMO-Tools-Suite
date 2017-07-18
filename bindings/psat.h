//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_PSAT_BRIDGE_H
#define AMO_TOOLS_SUITE_PSAT_BRIDGE_H

#include <map>
#include <unordered_map>
#include <nan.h>
#include <node.h>
#include <vector>
#include "psat/PSATResult.h"
#include "psat/Motor.h"
#include "psat/Pump.h"
#include "calculator/motor/EstimateFLA.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/pump/OptimalPrePumpEff.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/OptimalDeviationFactor.h"
#include "calculator/pump/HeadTool.h"

using namespace Nan;
using namespace v8;

//
//// Setup
//
//Isolate* iso;
Local<Object> inp;
Local<Object> r;

NAN_METHOD(headToolSuctionTank) {
    /**
    * Constructor for the HeadToolSuctionTank class with all inputs specified
    *
    * @param specificGravity double, specific gravity - unitless
    * @param flowRate double, flow rate in gpm (gallons per minute)
    * @param suctionPipeDiameter double, diameter of suction pipe in inches
    * @param suctionTankGasOverPressure double, gas over pressure of suction tank in psig (pounds per square inch gauge)
    * @param suctionTankFluidSurfaceElevation double, fluid surface elevation of suction tank in inches
    * @param suctionLineLossCoefficients double, line loss coefficients of suction - unitless
    * @param dischargePipeDiameter double, diameter of discharge pipe in inches
    * @param dischargeGaugePressure double, gauge pressure of discharge in psig (pounds per square inch gauge)
    * @param dischargeGaugeElevation double, gauge elevation of discharge in feet
    * @param dischargeLineLossCoefficients double, line loss coefficients of discharge - unitless
    *
 * */

        const double specificGravity = info[0]->NumberValue();
        const double flowRate = info[1]->NumberValue();
        const double suctionPipeDiameter = info[2]->NumberValue();
        const double suctionTankGasOverPressure = info[3]->NumberValue();
        const double suctionTankFluidSurfaceElevation = info[4]->NumberValue();
        const double suctionLineLossCoefficients = info[5]->NumberValue();
        const double dischargePipeDiameter = info[6]->NumberValue();
        const double dischargeGaugePressure = info[7]->NumberValue();
        const double dischargeGaugeElevation = info[8]->NumberValue();
        const double dischargeLineLossCoefficients = info[9]->NumberValue();

        HeadToolSuctionTank htst(specificGravity, flowRate, suctionPipeDiameter, suctionTankGasOverPressure,
                                 suctionTankFluidSurfaceElevation, suctionLineLossCoefficients, dischargePipeDiameter,
                                 dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);

        ReturnCalcValues retval = htst.calculate();
        Local<String> differentialElevationHead = Nan::New<String>("differentialElevationHead").ToLocalChecked();
        Local<String> differentialPressureHead = Nan::New<String>("differentialPressureHead").ToLocalChecked();
        Local<String> differentialVelocityHead = Nan::New<String>("differentialVelocityHead").ToLocalChecked();
        Local<String> estimatedSuctionFrictionHead = Nan::New<String>("estimatedSuctionFrictionHead").ToLocalChecked();
        Local<String> estimatedDischargeFrictionHead = Nan::New<String>("estimatedDischargeFrictionHead").ToLocalChecked();
        Local<String> pumpHead = Nan::New<String>("pumpHead").ToLocalChecked();
        Local<Object> obj = Nan::New<Object>();
        Nan::Set(obj, differentialElevationHead, Nan::New<Number>(retval.differentialElevationHead));
        Nan::Set(obj, differentialPressureHead, Nan::New<Number>(retval.differentialPressureHead));
        Nan::Set(obj, differentialVelocityHead, Nan::New<Number>(retval.differentialVelocityHead));
        Nan::Set(obj, estimatedSuctionFrictionHead, Nan::New<Number>(retval.estimatedSuctionFrictionHead));
        Nan::Set(obj, estimatedDischargeFrictionHead, Nan::New<Number>(retval.estimatedDischargeFrictionHead));
        Nan::Set(obj, estimatedDischargeFrictionHead, Nan::New<Number>(retval.estimatedDischargeFrictionHead));
        Nan::Set(obj, pumpHead, Nan::New<Number>(retval.pumpHead));

        info.GetReturnValue().Set(obj);
}

NAN_METHOD(headTool) {

    /**
    * Constructor for the HeadTool class with all inputs specified
    *
    * @param specificGravity double, specific gravity - unitless
    * @param flowRate double, flow rate in gpm (gallons per minute)
    * @param suctionPipeDiameter double, diameter of suction pipe in inches
    * @param suctionTankGasOverPressure double, gas over pressure of suction tank in psig (pounds per square inch gauge)
    * @param suctionTankFluidSurfaceElevation double, fluid surface elevation of suction tank in inches
    * @param suctionLineLossCoefficients double, line loss coefficients of suction - unitless
    * @param dischargePipeDiameter double, diameter of discharge pipe in inches
    * @param dischargeGaugePressure double, gauge pressure of discharge in psig (pounds per square inch gauge)
    * @param dischargeGaugeElevation double, gauge elevation of discharge in feet
    * @param dischargeLineLossCoefficients double, line loss coefficients of discharge - unitless
    *
 * */

        const double specificGravity = info[0]->NumberValue();
        const double flowRate = info[1]->NumberValue();
        const double suctionPipeDiameter = info[2]->NumberValue();
        const double suctionGaugePressure = info[3]->NumberValue();
        const double suctionGaugeElevation = info[4]->NumberValue();
        const double suctionLineLossCoefficients = info[5]->NumberValue();
        const double dischargePipeDiameter = info[6]->NumberValue();
        const double dischargeGaugePressure = info[7]->NumberValue();
        const double dischargeGaugeElevation = info[8]->NumberValue();
        const double dischargeLineLossCoefficients = info[9]->NumberValue();

        HeadTool ht(specificGravity, flowRate, suctionPipeDiameter, suctionGaugePressure,
                    suctionGaugeElevation, suctionLineLossCoefficients, dischargePipeDiameter,
                    dischargeGaugePressure, dischargeGaugeElevation, dischargeLineLossCoefficients);

        ReturnCalcValues retval = ht.calculate();
    Local<String> differentialElevationHead = Nan::New<String>("differentialElevationHead").ToLocalChecked();
    Local<String> differentialPressureHead = Nan::New<String>("differentialPressureHead").ToLocalChecked();
    Local<String> differentialVelocityHead = Nan::New<String>("differentialVelocityHead").ToLocalChecked();
    Local<String> estimatedSuctionFrictionHead = Nan::New<String>("estimatedSuctionFrictionHead").ToLocalChecked();
    Local<String> estimatedDischargeFrictionHead = Nan::New<String>("estimatedDischargeFrictionHead").ToLocalChecked();
    Local<String> pumpHead = Nan::New<String>("pumpHead").ToLocalChecked();
    Local<Object> obj = Nan::New<Object>();
    Nan::Set(obj, differentialElevationHead, Nan::New<Number>(retval.differentialElevationHead));
    Nan::Set(obj, differentialPressureHead, Nan::New<Number>(retval.differentialPressureHead));
    Nan::Set(obj, differentialVelocityHead, Nan::New<Number>(retval.differentialVelocityHead));
    Nan::Set(obj, estimatedSuctionFrictionHead, Nan::New<Number>(retval.estimatedSuctionFrictionHead));
    Nan::Set(obj, estimatedDischargeFrictionHead, Nan::New<Number>(retval.estimatedDischargeFrictionHead));
    Nan::Set(obj, estimatedDischargeFrictionHead, Nan::New<Number>(retval.estimatedDischargeFrictionHead));
    Nan::Set(obj, pumpHead, Nan::New<Number>(retval.pumpHead));
        info.GetReturnValue().Set(obj);
}

double Get(const char *nm) {
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    auto rObj = inp->ToObject()->Get(getName);
    if (rObj->IsUndefined()) {
        assert(!"defined");
    }
    return rObj->NumberValue();
}

void SetR(const char *nm, double n) {
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local<Number> getNum = Nan::New<Number>(n);
    Nan::Set(r, getName, getNum);
}

// Fields

Motor::LineFrequency line() {
    return (Motor::LineFrequency)(int)(!Get("line_frequency"));
}
Motor::EfficiencyClass effCls() {
    return (Motor::EfficiencyClass)(int)Get("efficiency_class");
}
Pump::Drive drive() {
    return (Pump::Drive)(int)Get("drive");
}
Pump::Style style() {
    return (Pump::Style)(int)Get("pump_style");
}
FieldData::LoadEstimationMethod  loadEstimationMethod() {
    return (FieldData::LoadEstimationMethod)(int)Get("load_estimation_method");
}
Pump::Speed speed() {
    return (Pump::Speed)(int)(!Get("fixed_speed"));
}
//
//// Operations
//

/**
 * Constructor Pump
 * @param pump_style Pump::Style, style of pump being used
 * @param pump_specified double, pump % efficiency at the specified operating conditions
 * @param rpm double, pump RPM to define its operating speed
 * @param drive Drive, type of drive the pump uses from either direct or belt drive
 * @param kinematic_viscosity double, kinematic viscosity of the fluid being pumped in centistokes
 * @param specific_gravity double, specific gravity - unitless
 * @param stages double, the number of pump stages
 * @param speed Speed, type of pump speed from either fixed or not fixed
 */
/**
 * Constructor motor
 * @param line_frequency LineFrequency, mains supply frequency at either 50Hz or 60Hz
 * @param motor_rated_power double, rated power for the motor in hp
 * @param motor_rated_speed double, motor RPM
 * @param efficiency_class EfficiencyClass, classification of motor efficiency
 * @param efficiency double, specified % efficiency of motor, if efficiency class is SPECIFIED
 * @param motor_rated_voltage double, motor nameplate design voltage in volts
 * @param motor_rated_fla double, current at full load in amps
 * @param margin double, the size margin as defined in %
 */

/**
 * Constructor financial
 * @param operating_fraction double, fraction(%) of calender hours the equipment is operating
 * @param cost_kw_hour double, per unit energy cost of electricity in $/kwhr.
 */

/**
 * Constructor field data
 * @param flow_rate double, rate of flow in GPM
 * @param head double, pump head measured in feet
 * @param load_estimation_method LoadEstimationMethod, estimated power or current on motor input
 * @param motor_field_power double, power output of the pump's motor in hp
 * @param motor_field_current double, current measured from the pump's motor in amps
 * @param motor_field_voltage double, the measured bus voltage in volts
 */

NAN_METHOD(resultsExistingAndOptimal) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    Pump::Style style1 = style();
    Pump::Drive drive1 = drive();
    double viscosity = Get("kinematic_viscosity");
    double specifc_gravity = Get("specific_gravity");
    double stages = Get("stages");
    Pump::Speed fixed_speed = speed();
    double pump_specified = Get("pump_specified")/100;
    double pump_rated_speed = Get("pump_rated_speed");

    Motor::LineFrequency lineFrequency = line();
    double motor_rated_power = Get("motor_rated_power");
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_voltage = Get("motor_rated_voltage");
    double motor_rated_fla = Get("motor_rated_fla");
    double margin = Get("margin");

    double fraction = Get("operating_fraction");
    double cost = Get("cost_kw_hour");

    double flow = Get("flow_rate");
    double head = Get("head");
    FieldData::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();
    double motor_field_power = Get("motor_field_power");
    double motor_field_current = Get("motor_field_current");
    double motor_field_voltage = Get("motor_field_voltage");

    Pump pump(style1, pump_specified, pump_rated_speed, drive1, viscosity, specifc_gravity, stages, fixed_speed);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, motor_rated_fla, margin);
    Financial fin(fraction, cost);
    FieldData fd(flow, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
    PSATResult psat(pump, motor, fin, fd);
    psat.calculateExisting();
    psat.calculateOptimal();
    auto ex = psat.getExisting();
    auto opt = psat.getOptimal();
    std::map<const char *,std::vector<double>> out = {
            {"pump_efficiency",{ex.pumpEfficiency_ * 100, opt.pumpEfficiency_ * 100}},
            {"motor_rated_power",{ex.motorRatedPower_,  opt.motorRatedPower_}},
            {"motor_shaft_power",{ex.motorShaftPower_,opt.motorShaftPower_}},
            {"pump_shaft_power",{ex.pumpShaftPower_, opt.pumpShaftPower_}},
            {"motor_efficiency",{ex.motorEfficiency_* 100, opt.motorEfficiency_ * 100}},
            {"motor_power_factor",{ex.motorPowerFactor_ * 100, opt.motorPowerFactor_ * 100}},
            {"motor_current",{ex.motorCurrent_, opt.motorCurrent_}},
            {"motor_power", {ex.motorPower_, opt.motorPower_}},
            {"annual_energy", {ex.annualEnergy_  ,opt.annualEnergy_}},
            {"annual_cost", {ex.annualCost_*1000,opt.annualCost_ * 1000}},
            {"annual_savings_potential", {psat.getAnnualSavingsPotential()  * 1000, -1}},
            {"optimization_rating", {psat.getOptimizationRating(), -1}}
    };
    for(auto p: out) {
        auto a = Nan::New<v8::Array>();
        a->Set(0,Nan::New<Number>(p.second[0]));
        a->Set(1,Nan::New<Number>(p.second[1]));
        Local<String> nm = Nan::New<String>(p.first).ToLocalChecked();
        //SetR(nm,a);
        Nan::Set(r, nm, a);
    }
    info.GetReturnValue().Set(r);
}

NAN_METHOD(resultsExisting) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    Pump::Style style1 = style();
    Pump::Drive drive1 = drive();
    Pump::Speed fixed_speed = speed();

    Motor::LineFrequency lineFrequency = line();
    Motor::EfficiencyClass efficiencyClass = effCls();

    FieldData::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();

    Pump pump(style1, Get("pump_specified") / 100.0, Get("pump_rated_speed"), drive1, Get("kinematic_viscosity"),
              Get("specific_gravity"), Get("stages"), fixed_speed);

    Motor motor(lineFrequency, Get("motor_rated_power"), Get("motor_rated_speed"), efficiencyClass, Get("efficiency"),
                Get("motor_rated_voltage"), Get("motor_rated_fla"), Get("margin"));

    Financial fin(Get("operating_fraction"), Get("cost_kw_hour"));

    FieldData fd(Get("flow_rate"), Get("head"), loadEstimationMethod1, Get("motor_field_power"),
                 Get("motor_field_current"), Get("motor_field_voltage"));

    PSATResult psat(pump, motor, fin, fd);
    psat.calculateExisting();
    auto const & ex = psat.getExisting();

    std::unordered_map<std::string, double> out = {
            {"pump_efficiency", ex.pumpEfficiency_ * 100},
            {"motor_rated_power", ex.motorRatedPower_},
            {"motor_shaft_power", ex.motorShaftPower_},
            {"pump_shaft_power", ex.pumpShaftPower_},
            {"motor_efficiency", ex.motorEfficiency_* 100},
            {"motor_power_factor", ex.motorPowerFactor_ * 100},
            {"motor_current", ex.motorCurrent_},
            {"motor_power", ex.motorPower_},
            {"annual_energy", ex.annualEnergy_},
            {"annual_cost", ex.annualCost_ * 1000},
            {"annual_savings_potential", psat.getAnnualSavingsPotential()  * 1000},
            {"optimization_rating", psat.getOptimizationRating()}
    };

    for(auto const & p: out) {
        Local<String> key = Nan::New<String>(p.first).ToLocalChecked();
        Local<Number> value = Nan::New(p.second);
        Nan::Set(r, key, value);
    }
    info.GetReturnValue().Set(r);
}

NAN_METHOD(resultsOptimal) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    Pump::Style style1 = style();
    Pump::Drive drive1 = drive();
    Pump::Speed fixed_speed = speed();

    Motor::LineFrequency lineFrequency = line();
    Motor::EfficiencyClass efficiencyClass = effCls();

    FieldData::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();

    Pump pump(style1, Get("pump_specified") / 100.0, Get("pump_rated_speed"), drive1, Get("kinematic_viscosity"),
              Get("specific_gravity"), Get("stages"), fixed_speed);

    Motor motor(lineFrequency, Get("motor_rated_power"), Get("motor_rated_speed"), efficiencyClass, Get("efficiency"),
                Get("motor_rated_voltage"), Get("motor_rated_fla"), Get("margin"));

    Financial fin(Get("operating_fraction"), Get("cost_kw_hour"));

    FieldData fd(Get("flow_rate"), Get("head"), loadEstimationMethod1, Get("motor_field_power"),
                 Get("motor_field_current"), Get("motor_field_voltage"));

    PSATResult psat(pump, motor, fin, fd);
    psat.calculateOptimal();
    auto const & opt = psat.getOptimal();

    std::unordered_map<std::string, double> out = {
            {"pump_efficiency", opt.pumpEfficiency_ * 100},
            {"motor_rated_power", opt.motorRatedPower_},
            {"motor_shaft_power", opt.motorShaftPower_},
            {"pump_shaft_power", opt.pumpShaftPower_},
            {"motor_efficiency", opt.motorEfficiency_* 100},
            {"motor_power_factor", opt.motorPowerFactor_ * 100},
            {"motor_current", opt.motorCurrent_},
            {"motor_power", opt.motorPower_},
            {"annual_energy", opt.annualEnergy_},
            {"annual_cost", opt.annualCost_ * 1000},
            {"annual_savings_potential", psat.getAnnualSavingsPotential()  * 1000},
            {"optimization_rating", psat.getOptimizationRating()}
    };

    for(auto const & p: out) {
        Local<String> key = Nan::New<String>(p.first).ToLocalChecked();
        Local<Number> value = Nan::New(p.second);
        Nan::Set(r, key, value);
    }
    info.GetReturnValue().Set(r);
}

/**
 * Constructor estimate fla
 * @param motor_rated_power double, rated Power of motor in hp
 * @param motor_rated_speed double, RPM of motor
 * @param line_frequency LineFrequency, line frequency of motor in 50Hz or 60Hz
 * @param efficiency_class EfficiencyClass, efficiency class of motor
 * @param efficiency double, specified efficiency of motor as defined by %
 * @param motor_rated_voltage double, rated voltage of motor in volts

 */
NAN_METHOD(estFLA) {
    inp = info[0]->ToObject();
    double motor_rated_power = Get("motor_rated_power");
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::LineFrequency l = line();
    Motor::EfficiencyClass e = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_voltage = Get("motor_rated_voltage");
    EstimateFLA fla(motor_rated_power, motor_rated_speed, l, e, efficiency, motor_rated_voltage);
    fla.calculate();
    info.GetReturnValue().Set(fla.getEstimatedFLA());
}
/**
 * Constructor motor performance
 * @param motor_rated_power double, rated power of motor in hp
 * @param motor_rated_speed double, RPM of motor
 * @param line_frequency LineFrequency, line frequency of motor in 50Hz or 60Hz
 * @param efficiency_class EfficiencyClass, efficiency class of motor
 * @param efficiency double, specified efficiency of motor as defined by %
 * @param load_factor double, load factor between 0.0001 and 1.25 - unitless
 * @param motor_rated_voltage double, rated voltage of motor in volts
 * @param motor_rated_fla double, motor rated full load amps

 */
NAN_METHOD(motorPerformance) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    Motor::LineFrequency l = line();
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_power = Get("motor_rated_power");
    double load_factor = Get("load_factor");
    MotorEfficiency mef(l, motor_rated_speed, efficiencyClass, efficiency, motor_rated_power, load_factor);
    double mefVal = mef.calculate();
    SetR("efficiency", mefVal * 100);

    double motor_rated_voltage = Get("motor_rated_voltage");
    double fla = Get("motor_rated_fla");
    MotorCurrent mc(motor_rated_power, motor_rated_speed, l, efficiencyClass, efficiency, load_factor, motor_rated_voltage, fla);
    double mcVal = mc.calculate();
    SetR("motor_current", mcVal/fla * 100);

    MotorPowerFactor motorPowerFactor(motor_rated_power, load_factor, mcVal, mefVal, motor_rated_voltage);
    SetR("motor_power_factor", motorPowerFactor.calculate() * 100);

    info.GetReturnValue().Set(r);

}
/**
 * Constructor
 * @param style Pump::Style, style of pump being used
 * @param flow_rate double, flow rate in GPM
 */
NAN_METHOD(pumpEfficiency)  {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    Pump::Style s = style();
    double flow = Get("flow_rate");
    OptimalPrePumpEff pef(s, 0, flow);
    double v = pef.calculate();
    SetR("average",v);
    double odf = OptimalDeviationFactor(flow).calculate();
    SetR("max",v*odf);
    info.GetReturnValue().Set(r);
}

/**
 * Constructor
 * @param style Pump::Style, style Style of pump being used.
 * @param specific_speed double, specific speed in rpm*sqrt(gpm)/((ft/s)^(3/2))
 */
NAN_METHOD(achievableEfficiency) {
    inp = info[0]->ToObject();
    double specific_speed = Get("specific_speed");
    Pump::Style s = style();
    info.GetReturnValue().Set(OptimalSpecificSpeedCorrection(s, specific_speed).calculate()*100);
}
/**
 * Constructor nema
 * @param motor_rated_power double, rated power of motor in hp
 * @param motor_rated_speed double, RPM of motor
 * @param line_frequency LineFrequency, line frequency of motor in 50Hz or 60Hz
 * @param efficiency_class EfficiencyClass, efficiency class of motor
 * @param efficiency double, specified efficiency of motor as defined by %
 * @param load_factor double, load factor between 0.0001 and 1.25 - unitless
 */
NAN_METHOD(nema) {
    inp = info[0]->ToObject();
    Motor::LineFrequency l = line();
    double motor_rated_speed = Get("motor_rated_speed");
    Motor::EfficiencyClass efficiencyClass = effCls();
    double efficiency = Get("efficiency");
    double motor_rated_power = Get("motor_rated_power");
    double load_factor = Get("load_factor");
    info.GetReturnValue().Set(MotorEfficiency(l, motor_rated_speed, efficiencyClass, efficiency, motor_rated_power,load_factor).calculate()*100);
}


#endif //AMO_TOOLS_SUITE_PSAT_BRIDGE_H
