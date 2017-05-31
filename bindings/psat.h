//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_PSAT_BRIDGE_H
#define AMO_TOOLS_SUITE_PSAT_BRIDGE_H

#include <map>
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
    * @param specificGravity no units
    * @param flowRate units in gpm (gallons per minute)
    * @param suctionPipeDiameter units in inches
    * @param suctionTankGasOverPressure units in psig (pounds per square inch gauge)
    * @param suctionTankFluidSurfaceElevation units in inches
    * @param suctionLineLossCoefficients no units
    * @param dischargePipeDiameter units in inches
    * @param dischargeGaugePressure units in psig (pounds per square inch gauge)
    * @param dischargeGaugeElevation units in feet
    * @param dischargeLineLossCoefficients no units
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
    * @param specificGravity no units
    * @param flowRate units in gpm (gallons per minute)
    * @param suctionPipeDiameter units in inches
    * @param suctionTankGasOverPressure units in psig (pounds per square inch gauge)
    * @param suctionTankFluidSurfaceElevation units in inches
    * @param suctionLineLossCoefficients no units
    * @param dischargePipeDiameter units in inches
    * @param dischargeGaugePressure units in psig (pounds per square inch gauge)
    * @param dischargeGaugeElevation units in feet
    * @param dischargeLineLossCoefficients no units
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
 * @param pump_style Style of pump being used.
 * @param pump_specified Pump % efficiency at the specified operating conditions.
 * @param rpm Pump RPM to define its operating speed.
 * @param drive Type of drive the pump uses from either direct or belt drive.
 * @param kinematic_viscosity Kinematic viscosity of the fluid being pumped, in centistokes.
 * @param specific_gravity Specific gravity.
 * @param stages The number of pump stages.
 * @param speed Type of pump speed from either fixed or not fixed.
 */
/**
 * Constructor motor
 * @param line_frequency Mains supply frequency at either 50Hz or 60Hz.
 * @param motor_rated_power Rated power for the motor in hp or kw.
 * @param motor_rated_speed Motor RPM.
 * @param efficiency_class Classification of motor efficiency.
 * @param efficiency Specified % Efficiency of motor, if efficiency class is SPECIFIED
 * @param motor_rated_voltage Motor nameplate design voltage.
 * @param motor_rated_fla Current at full load in amps.
 * @param margin The size margin as defined in %.
 */

/**
 * Constructor financial
 * @param operating_fraction Fraction(%) of calender hours the equipment is operating.
 * @param cost_kw_hour Per unit energy cost of electricity in $/kwhr.
 */

/**
 * Constructor field data
 * @param flow_rate Rate of flow. GPM
 * @param head Pump head measured in feet
 * @param load_estimation_method Estimated power or current on motor input.
 * @param motor_field_power Power output of the pump's motor in hp.
 * @param motor_field_current Current measured from the pump's motor in amps.
 * @param motor_field_voltage The measured bus voltage.
 */

NAN_METHOD(results) {
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
/**
 * Constructor estimate fla
 * @param motor_rated_power Rated Power of motor in hp
 * @param motor_rated_speed RPM of motor.
 * @param line_frequency Line frequency of motor in 50Hz or 60Hz.
 * @param efficiency_class Efficiency class of motor.
 * @param efficiency Specified Efficiency of motor as defined by %.
 * @param motor_rated_voltage Rated voltage of motor.

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
 * @param motor_rated_power Rated Power of motor in hp
 * @param motor_rated_speed RPM of motor.
 * @param line_frequency Line frequency of motor in 50Hz or 60Hz.
 * @param efficiency_class Efficiency class of motor.
 * @param efficiency Specified Efficiency of motor as defined by %.
 * @param load_factor between 0.0001 and 1.25
 * @param motor_rated_voltage Rated voltage of motor
 * @param motor_rated_fla Motor rated full load amps

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
 * @param style style Style of pump being used.
 * @param flow_rate GPM
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
 * @param style style Style of pump being used.
 * @param specific_speed rpm
 */
NAN_METHOD(achievableEfficiency) {
    inp = info[0]->ToObject();
    double specific_speed = Get("specific_speed");
    Pump::Style s = style();
    info.GetReturnValue().Set(OptimalSpecificSpeedCorrection(s, specific_speed).calculate()*100);
}
/**
 * Constructor nema
 * @param motor_rated_power Rated Power of motor in hp
 * @param motor_rated_speed RPM of motor.
 * @param line_frequency Line frequency of motor in 50Hz or 60Hz.
 * @param efficiency_class Efficiency class of motor.
 * @param efficiency Specified Efficiency of motor as defined by %.
 * @param load_factor between 0.0001 and 1.25
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
