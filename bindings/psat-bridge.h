//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_PSAT_BRIDGE_H
#define AMO_TOOLS_SUITE_PSAT_BRIDGE_H

#include <nan.h>
#include <node.h>

using namespace Nan;
using namespace v8;


#include "psat/PSATResult.h"
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

        double head = htst.calculate();
        Local<Number> retval = Nan::New(head);
        info.GetReturnValue().Set(retval);
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

        double head = ht.calculate();
        Local<Number> retval = Nan::New(head);
        info.GetReturnValue().Set(retval);
}
//
//void Setup(const FunctionCallbackInfo<Value>& args) {
//    iso = args.GetIsolate();
//    inp = args[0]->ToObject();
//    r = Object::New(iso);
//    args.GetReturnValue().Set(r);
//}
//
//double Get(const char *nm) {
//    auto rObj = inp->ToObject()->Get(String::NewFromUtf8(iso,nm));
//    if (rObj->IsUndefined()) {
//        cout << nm << endl;;
//        assert(!"defined");
//    }
//    return rObj->NumberValue();
//}
//
//void SetR(const char *nm, double n) {
//    r->Set(String::NewFromUtf8(iso,nm),Number::New(iso,n));
//}
//
//// Fields
//
//Motor::LineFrequency line() {
//    return (Motor::LineFrequency)(int)(!Get("line"));
//}
//Motor::EfficiencyClass effCls() {
//    return (Motor::EfficiencyClass)(int)Get("efficiency_class");
//}
//Pump::Drive drive() {
//    return (Pump::Drive)(int)Get("drive");
//}
//Pump::Style style() {
//    return (Pump::Style)(int)Get("pump_style");
//}
//
//// Operations
//
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
//void EstFLA(const FunctionCallbackInfo<Value>& args) {
//    Setup(args);
//    EstimateFLA fla(Get("motor_rated_power"),Get("motor_rated_speed"),line(),effCls(),
//                    Get("efficiency"),Get("motor_rated_voltage"));
//    fla.calculate();
//    args.GetReturnValue().Set(fla.getEstimatedFLA());
//}
//
//void MotorPerformance(const FunctionCallbackInfo<Value>& args) {
//    Setup(args);
//
//    MotorEfficiency mef(line(),Get("motor_rated_speed"),effCls(),Get("efficiency"),Get("motor_rated_power"),Get("load_factor"));
//    auto mefVal = mef.calculate();
//    SetR("efficiency",mefVal*100);
//
//    MotorCurrent mc(Get("motor_rated_power"),Get("motor_rated_speed"),line(),effCls(),Get("efficiency"),Get("load_factor"),Get("motor_rated_voltage"),Get("flc"));
//    auto mcVal = mc.calculate();
//    SetR("current",mcVal/Get("flc")*100);
//
//    MotorPowerFactor pf(Get("motor_rated_power"),Get("load_factor"),mcVal,mefVal,Get("motor_rated_voltage"));
//    SetR("pf",pf.calculate()*100);
//}
//
//void PumpEfficiency(const FunctionCallbackInfo<Value>& args) {
//    Setup(args);
//    OptimalPrePumpEff pef(style(), 0, Get("flow"));
//    auto v = pef.calculate();
//    SetR("average",v);
//    SetR("max",v*OptimalDeviationFactor(Get("flow")).calculate());
//}
//

NAN_METHOD(achievableEfficiency) {
        inp = info[0]->ToObject();
        r = Nan::New<Object>();
        info.GetReturnValue().Set(r);
}

//void AchievableEfficiency(const FunctionCallbackInfo<Value>& args) {
//    Setup(args);
//    args.GetReturnValue().Set(
//            OptimalSpecificSpeedCorrection(style(), Get("specific_speed")).calculate()*100);
//}
//
//void Nema(const FunctionCallbackInfo<Value>& args) {
//    Setup(args);
//
//    args.GetReturnValue().Set(
//            MotorEfficiency(line(),Get("motor_rated_speed"),effCls(),Get("efficiency"),Get("motor_rated_power"),1).calculate()*100
//    );
//}
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
//// nema
//
//    {
//        MotorEfficiency mef(Motor::LineFrequency::FREQ60,1200, Motor::EfficiencyClass::ENERGY_EFFICIENT,0,200,1);
//        //Check100(95,mef.calculate());
//    }
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
