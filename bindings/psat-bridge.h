//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_PSAT_BRIDGE_H
#define AMO_TOOLS_SUITE_PSAT_BRIDGE_H

#include <map>
#include <nan.h>
#include <node.h>
#include <vector>

using namespace Nan;
using namespace v8;


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
    * @param flowRate units in meters cubed per hour (m^3/hour)
    * @param suctionPipeDiameter units in millimeters
    * @param suctionTankGasOverPressure units in kPa
    * @param suctionTankFluidSurfaceElevation units in meters
    * @param suctionLineLossCoefficients no units
    * @param dischargePipeDiameter units in millimeters
    * @param dischargeGaugePressure units in kPa
    * @param dischargeGaugeElevation units in meters
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
    * Constructor for HeadTool with no Suction Tank, all inputs specified
    *
    * @param specificGravity no units
    * @param flowRate units in meters cubed per hour (m^3/hour)
    * @param suctionPipeDiameter units in millimeters
    * @param suctionGaugePressure units in kPa
    * @param suctionGaugeElevation units in meters
    * @param suctionLineLossCoefficients no units
    * @param dischargePipeDiameter units in millimeters
    * @param dischargeGaugePressure units in kPa
    * @param dischargeGaugeElevation units in meters
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
    return (Motor::LineFrequency)(int)(!Get("line"));
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

NAN_METHOD(results) {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();

    Pump::Style style1 = style();
    Pump::Drive drive1 = drive();
    double viscosity = Get("viscosity");
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
    double fla = Get("fla");
    double margin = Get("margin");

    double fraction = Get("fraction");
    double cost = Get("cost");

    double flow = Get("flow");
    double head = Get("head");
    FieldData::LoadEstimationMethod loadEstimationMethod1 = loadEstimationMethod();
    double motor_field_power = Get("motor_field_power");
    double motor_field_current = Get("motor_field_current");
    double motor_field_voltage = Get("motor_field_voltage");

    Pump pump(style1, pump_specified, pump_rated_speed, drive1, viscosity, specifc_gravity, stages, fixed_speed);
    Motor motor(lineFrequency, motor_rated_power, motor_rated_speed, efficiencyClass, efficiency, motor_rated_voltage, fla, margin);
    Financial fin(fraction, cost);
    FieldData fd(flow, head, loadEstimationMethod1, motor_field_power, motor_field_current, motor_field_voltage);
    PSATResult psat(pump, motor, fin, fd);
    psat.calculateExisting();
    psat.calculateOptimal();
    auto ex = psat.getExisting();
    auto opt = psat.getOptimal();
    std::map<const char *,std::vector<double>> out = {
            {"Pump Efficiency",{ex.pumpEfficiency_ * 100, opt.pumpEfficiency_ * 100}},
            {"Motor Rated Power",{ex.motorRatedPower_,  opt.motorRatedPower_}},
            {"Motor Shaft Power",{ex.motorShaftPower_,opt.motorShaftPower_}},
            {"Pump Shaft Power",{ex.pumpShaftPower_, opt.pumpShaftPower_}},
            {"Motor Efficiency",{ex.motorEfficiency_* 100, opt.motorEfficiency_ * 100}},
            {"Motor Power Factor",{ex.motorPowerFactor_ * 100, opt.motorPowerFactor_ * 100}},
            {"Motor Current",{ex.motorCurrent_, opt.motorCurrent_}},
            {"Motor Power", {ex.motorPower_, opt.motorPower_}},
            {"Annual Energy", {ex.annualEnergy_  ,opt.annualEnergy_}},
            {"Annual Cost", {ex.annualCost_*1000,opt.annualCost_ * 1000}},
            {"Savings Potential", {psat.getAnnualSavingsPotential()  * 1000, -1}},
            {"Optimization Rating", {psat.getOptimizationRating(), -1}}
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


//void Results(const FunctionCallbackInfo<Value>& args) {
//    Setup(args);
//
//    Pump pump(style(),Get("pump_specified")/100,Get("pump_rated_speed"),drive(),
//              Get("viscosity"),Get("specific_gravity"),Get("stages"),(Pump::Speed)(int)(!Get("fixed_speed")));
//    Motor motor(line(),Get("motor_rated_power"),Get("motor_rated_speed"),effCls(),
//                Get("efficiency"),Get("motor_rated_voltage"),Get("motor_rated_flc"),Get("margin"));
//    Financial fin(Get("fraction")/100,Get("cost"));
//    FieldData fd(Get("flow"),Get("head"),(FieldData::LoadEstimationMethod)(Get("motor_field_power")>0?0:1),
//                 Get("motor_field_power"),Get("motor_field_current"),Get("motor_field_voltage"));
//    PSATResult psat(pump,motor,fin,fd);
//    psat.calculateExisting();
//    psat.calculateOptimal();
//    auto ex = psat.getExisting(), opt = psat.getOptimal();
//
//    map<const char *,vector<double>> out = {
//            {"Pump Efficiency",{ex.pumpEfficiency_ * 100, opt.pumpEfficiency_ * 100}},
//            {"Motor Rated Power",{ex.motorRatedPower_,  opt.motorRatedPower_}},
//            {"Motor Shaft Power",{ex.motorShaftPower_,opt.motorShaftPower_}},
//            {"Pump Shaft Power",{ex.pumpShaftPower_, opt.pumpShaftPower_}},
//            {"Motor Efficiency",{ex.motorEfficiency_* 100, opt.motorEfficiency_ * 100}},
//            {"Motor Power Factor",{ex.motorPowerFactor_ * 100, opt.motorPowerFactor_ * 100}},
//            {"Motor Current",{ex.motorCurrent_, opt.motorCurrent_}},
//            {"Motor Power", {ex.motorPower_, opt.motorPower_}},
//            {"Annual Energy", {ex.annualEnergy_  ,opt.annualEnergy_}},
//            {"Annual Cost", {ex.annualCost_*1000,opt.annualCost_ * 1000}},
//            {"Savings Potential", {psat.getAnnualSavingsPotential()  * 1000, -1}},
//            {"Optimization Rating", {psat.getOptimizationRating(), -1}}
//    };
//    for(auto p: out) {
//        auto a = Array::New(iso);
//        a->Set(0,Number::New(iso,p.second[0]));
//        a->Set(1,Number::New(iso,p.second[1]));
//        r->Set(String::NewFromUtf8(iso,p.first),a);
//    }
//}
//

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
    double fla = Get("fla");
    MotorCurrent mc(motor_rated_power, motor_rated_speed, l, efficiencyClass, efficiency, load_factor, motor_rated_voltage, fla);
    double mcVal = mc.calculate();
    SetR("current", mcVal/fla * 100);

    MotorPowerFactor motorPowerFactor(motor_rated_power, load_factor, mcVal, mefVal, motor_rated_voltage);
    SetR("pf", motorPowerFactor.calculate() * 100);

    info.GetReturnValue().Set(r);

}

NAN_METHOD(pumpEfficiency)  {
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    Pump::Style s = style();
    double flow = Get("flow");
    OptimalPrePumpEff pef(s, 0, flow);
    double v = pef.calculate();
    SetR("average",v);
    double odf = OptimalDeviationFactor(flow).calculate();
    SetR("max",v*odf);
    info.GetReturnValue().Set(r);
}


NAN_METHOD(achievableEfficiency) {
    inp = info[0]->ToObject();
    double specific_speed = Get("specific_speed");
    Pump::Style s = style();
    info.GetReturnValue().Set(OptimalSpecificSpeedCorrection(s, specific_speed).calculate()*100);
}

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


//
//// Test
//
//void Check(double exp, double act, const char* nm="") {
//    //cout << "e " << exp << "; a " << act << endl;
//    // if (isnan(act) || (abs(exp-act)>.01*exp)) {
//    auto p = 10;
//    if (isnan(act) || ( (round(exp*p)/p)!=round(act*p)/p)) {
//        printf("\"%s\" TEST FAILED: %f %f\n",nm,exp,act);
//        assert(!"equal");
//    }
//}
//
//void Check100(double exp, double act, const char* nm="") {
//    Check(exp,act*100,nm);
//}
//
//void Test(const FunctionCallbackInfo<Value>& args) {
//    EstimateFLA fla(200,1780,(Motor::LineFrequency)1,(Motor::EfficiencyClass)(1),0,460);
//    fla.calculate();
//    Check(225.8,fla.getEstimatedFLA());
//
//// motor perf
//
//    {
//        MotorCurrent mc(200,1780,Motor::LineFrequency::FREQ60,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,.25,460,225.8);
//        auto mcVal = mc.calculate();
//        Check100(36.11,mcVal/225.8);
//    }
//    {
//        MotorEfficiency mef(Motor::LineFrequency::FREQ60,1780,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,200,.75);
//        auto mefVal = mef.calculate();
//        Check100(95.69,mefVal);
//
//        MotorCurrent mc(200,1780,Motor::LineFrequency::FREQ60,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,.75,460,225.8);
//        auto mcVal = mc.calculate();
//        Check100(76.63,mcVal/225.8);
//
//        MotorPowerFactor pf(200,.75,mcVal,mefVal,460);
//        Check100(84.82,pf.calculate());
//    }
//
//
//// pump eff
//
//    {
//        OptimalPrePumpEff pef(Pump::Style::END_SUCTION_ANSI_API, 0, 2000);
//        OptimalDeviationFactor df(2000);
//
//        //cout <<  pef.calculate() << ";" << df.calculate();
//        //Check(87.1,pef.calculate()*df.calculate());
//    }
//
//// spec speed
//
//
//    {
//        OptimalSpecificSpeedCorrection cor(Pump::Style::END_SUCTION_ANSI_API, 1170);
//        //Check100(2.3,cor.calculate());
//    }
//    return;
//

#endif //AMO_TOOLS_SUITE_PSAT_BRIDGE_H
