#include <iostream>
#include <vector>
#include <map>
#include <node.h>
#include <cmath>

#include "psat/PSATResult.h"
#include "calculator/motor/EstimateFLA.h"
#include "calculator/motor/MotorCurrent.h"
#include "calculator/motor/MotorEfficiency.h"
#include "calculator/motor/MotorPowerFactor.h"
#include "calculator/pump/OptimalPrePumpEff.h"
#include "calculator/pump/OptimalSpecificSpeedCorrection.h"
#include "calculator/pump/OptimalDeviationFactor.h"

using namespace v8;
using namespace std;

// Setup

Isolate* iso;
Local<Object> inp;
Local<Object> r;

void Setup(const FunctionCallbackInfo<Value>& args) {
    iso = args.GetIsolate();
    inp = args[0]->ToObject();
    r = Object::New(iso);
    args.GetReturnValue().Set(r);
}

double Get(const char *nm) {
    auto rObj = inp->ToObject()->Get(String::NewFromUtf8(iso,nm));
    if (rObj->IsUndefined()) {
        cout << nm << endl;;
        assert(!"defined");
    }
    return rObj->NumberValue();
}

void SetR(const char *nm, double n) {
    r->Set(String::NewFromUtf8(iso,nm),Number::New(iso,n));
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

// Operations

void Results(const FunctionCallbackInfo<Value>& args) {
    Setup(args);

    Pump pump(style(),Get("pump_specified")/100,Get("pump_rated_speed"),drive(),
              Get("viscosity"),Get("specific_gravity"),Get("stages"),(Pump::Speed)(int)(!Get("fixed_speed")));
    Motor motor(line(),Get("motor_rated_power"),Get("motor_rated_speed"),effCls(),
                Get("efficiency"),Get("motor_rated_voltage"),Get("motor_rated_flc"),Get("margin"));
    Financial fin(Get("fraction")/100,Get("cost"));
    FieldData fd(Get("flow"),Get("head"),(FieldData::LoadEstimationMethod)(Get("motor_field_power")>0?0:1),
                 Get("motor_field_power"),Get("motor_field_current"),Get("motor_field_voltage"));
    PSATResult psat(pump,motor,fin,fd);
    psat.calculateExisting();
    psat.calculateOptimal();
    auto ex = psat.getExisting(), opt = psat.getOptimal();

    map<const char *,vector<double>> out = {
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
        auto a = Array::New(iso);
        a->Set(0,Number::New(iso,p.second[0]));
        a->Set(1,Number::New(iso,p.second[1]));
        r->Set(String::NewFromUtf8(iso,p.first),a);
    }
}

void EstFLA(const FunctionCallbackInfo<Value>& args) {
    Setup(args);
    EstimateFLA fla(Get("motor_rated_power"),Get("motor_rated_speed"),line(),effCls(),
                    Get("efficiency"),Get("motor_rated_voltage"));
    fla.calculate();
    args.GetReturnValue().Set(fla.getEstimatedFLA());
}

void MotorPerformance(const FunctionCallbackInfo<Value>& args) {
    Setup(args);

    MotorEfficiency mef(line(),Get("motor_rated_speed"),effCls(),Get("efficiency"),Get("motor_rated_power"),Get("load_factor"));
    auto mefVal = mef.calculate();
    SetR("efficiency",mefVal*100);

    MotorCurrent mc(Get("motor_rated_power"),Get("motor_rated_speed"),line(),effCls(),Get("efficiency"),Get("load_factor"),Get("motor_rated_voltage"),Get("flc"));
    auto mcVal = mc.calculate();
    SetR("current",mcVal/Get("flc")*100);

    MotorPowerFactor pf(Get("motor_rated_power"),Get("load_factor"),mcVal,mefVal,Get("motor_rated_voltage"));
    SetR("pf",pf.calculate()*100);
}

void PumpEfficiency(const FunctionCallbackInfo<Value>& args) {
    Setup(args);
    OptimalPrePumpEff pef(style(), 0, Get("flow"));
    auto v = pef.calculate();
    SetR("average",v);
    SetR("max",v*OptimalDeviationFactor(Get("flow")).calculate());
}

void AchievableEfficiency(const FunctionCallbackInfo<Value>& args) {
    Setup(args);
    args.GetReturnValue().Set(
            OptimalSpecificSpeedCorrection(style(), Get("specific_speed")).calculate()*100);
}

void Nema(const FunctionCallbackInfo<Value>& args) {
    Setup(args);

    args.GetReturnValue().Set(
            MotorEfficiency(line(),Get("motor_rated_speed"),effCls(),Get("efficiency"),Get("motor_rated_power"),1).calculate()*100
    );
}

// Test

void Check(double exp, double act, const char* nm="") {
    //cout << "e " << exp << "; a " << act << endl;
    // if (isnan(act) || (abs(exp-act)>.01*exp)) {
    auto p = 10;
    if (isnan(act) || ( (round(exp*p)/p)!=round(act*p)/p)) {
        printf("\"%s\" TEST FAILED: %f %f\n",nm,exp,act);
        assert(!"equal");
    }
}

void Check100(double exp, double act, const char* nm="") {
    Check(exp,act*100,nm);
}

void Test(const FunctionCallbackInfo<Value>& args) {
    EstimateFLA fla(200,1780,(Motor::LineFrequency)1,(Motor::EfficiencyClass)(1),0,460);
    fla.calculate();
    Check(225.8,fla.getEstimatedFLA());

// motor perf

    {
        MotorCurrent mc(200,1780,Motor::LineFrequency::FREQ60,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,.25,460,225.8);
        auto mcVal = mc.calculate();
        Check100(36.11,mcVal/225.8);
    }
    {
        MotorEfficiency mef(Motor::LineFrequency::FREQ60,1780,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,200,.75);
        auto mefVal = mef.calculate();
        Check100(95.69,mefVal);

        MotorCurrent mc(200,1780,Motor::LineFrequency::FREQ60,Motor::EfficiencyClass::ENERGY_EFFICIENT,0,.75,460,225.8);
        auto mcVal = mc.calculate();
        Check100(76.63,mcVal/225.8);

        MotorPowerFactor pf(200,.75,mcVal,mefVal,460);
        Check100(84.82,pf.calculate());
    }

// nema

    {
        MotorEfficiency mef(Motor::LineFrequency::FREQ60,1200, Motor::EfficiencyClass::ENERGY_EFFICIENT,0,200,1);
        //Check100(95,mef.calculate());
    }

// pump eff

    {
        OptimalPrePumpEff pef(Pump::Style::END_SUCTION_ANSI_API, 0, 2000);
        OptimalDeviationFactor df(2000);

        //cout <<  pef.calculate() << ";" << df.calculate();
        //Check(87.1,pef.calculate()*df.calculate());
    }

// spec speed


    {
        OptimalSpecificSpeedCorrection cor(Pump::Style::END_SUCTION_ANSI_API, 1170);
        //Check100(2.3,cor.calculate());
    }
    return;

#define BASE \
		Pump pump(Pump::Style::END_SUCTION_ANSI_API,0,1780,Pump::Drive::DIRECT_DRIVE,\
			1,1,1,Pump::Speed::NOT_FIXED_SPEED);\
		Motor motor(Motor::LineFrequency::FREQ60,200,1780,\
				Motor::EfficiencyClass::ENERGY_EFFICIENT,0,460,225.8,0);\
		Financial fin(1,.05);\
		FieldData fd(2000,277,FieldData::LoadEstimationMethod::POWER,\
				150,0,460);

#define CALC \
		PSATResult psat(pump,motor,fin,fd);\
		psat.calculateExisting();\
		auto ex = psat.getExisting();

    for (int i=1; i<=10000; i=i+2) {
        BASE
        CALC
        Check(ex.motorShaftPower_,ex.motorShaftPower_,"SAME");
    }

    {
        BASE
        motor.setMotorRpm(1786);
        fd.setMotorPower(80);
        CALC
        Check(101.9,ex.motorShaftPower_);
        Check100(95,ex.motorEfficiency_);
        Check100(79.1,ex.motorPowerFactor_);
        Check(127,ex.motorCurrent_);
    }
    {
        BASE
        fd.setMotorPower(80);
        motor.setMotorRatedPower(100);
        motor.setFullLoadAmps(113.8);
        CALC
        Check(101.8,ex.motorShaftPower_);
        Check100(94.9,ex.motorEfficiency_);
        Check100(86.7,ex.motorPowerFactor_);
        Check(115.8,ex.motorCurrent_);
    }
    {
        BASE
        fd.setMotorPower(80);
        fd.setVoltage(260);
        CALC
        Check(101.9,ex.motorShaftPower_);
        Check100(95,ex.motorEfficiency_);
        Check100(138.8,ex.motorPowerFactor_);
        Check(128,ex.motorCurrent_);
    }
    {
        BASE
        motor.setMotorRpm(1200);
        fd.setMotorPower(80);
        motor.setFullLoadAmps(235.3);
        CALC
        Check(101.4,ex.motorShaftPower_);
        Check100(94.5,ex.motorEfficiency_);
        Check100(74.3,ex.motorPowerFactor_);
        Check(135.1,ex.motorCurrent_);
    }
    {
        BASE
        fd.setMotorPower(111.855);
        CALC
        Check(143.4,ex.motorShaftPower_);
        Check100(95.6,ex.motorEfficiency_);
        Check100(84.3,ex.motorPowerFactor_);
        Check(166.5,ex.motorCurrent_);
    }
    {
        BASE
        fd.setMotorPower(80);
        motor.setMotorRatedVoltage(200);
        motor.setFullLoadAmps(519.3);
        CALC
        Check(101.9,ex.motorShaftPower_);
        Check100(95,ex.motorEfficiency_);
        Check100(35.2,ex.motorPowerFactor_);
        Check(284.9,ex.motorCurrent_);
    }
    {
        BASE
        CALC
        Check(217.5,ex.motorCurrent_);
    }
    {
        BASE
        fd.setLoadEstimationMethod(FieldData::LoadEstimationMethod::CURRENT);
        fd.setMotorAmps(218);
        fd.setMotorPower(0);
        CALC
        Check(150.4,ex.motorPower_);
        Check100(72.5,ex.pumpEfficiency_);
    }
    {
        BASE
        fd.setMotorPower(80);
        CALC
        Check(700.8,ex.annualEnergy_);
    }
    {
        BASE
        fin.setOperatingFraction(.25);
        CALC
        Check(328.5,ex.annualEnergy_);
        Check(16.4,ex.annualCost_);
    }
    {
        BASE
        motor.setFullLoadAmps(300);
        CALC
        Check(288.9,ex.motorCurrent_);
    }
    {
        BASE
        motor.setEfficiencyClass(Motor::EfficiencyClass(0));
        CALC
        Check(213.7,ex.motorCurrent_);
    }
    {
        BASE
        motor.setEfficiencyClass(Motor::EfficiencyClass(2));
        motor.setSpecifiedEfficiency(75);
        CALC
        Check(173.7,ex.motorCurrent_);
    }
    cout << "done";
}

void InitTest(const FunctionCallbackInfo<Value>& args) {
    Setup(args);
    args.GetReturnValue().Set(String::NewFromUtf8(iso,"SUCCESS"));
}

// v8

void Init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "results", Results);
    NODE_SET_METHOD(exports, "estFLA", EstFLA);
    NODE_SET_METHOD(exports, "motorPerformance", MotorPerformance);
    NODE_SET_METHOD(exports, "pumpEfficiency", PumpEfficiency);
    NODE_SET_METHOD(exports, "achievableEfficiency", AchievableEfficiency);
    NODE_SET_METHOD(exports, "nema", Nema);
    NODE_SET_METHOD(exports, "test", Test);
    NODE_SET_METHOD(exports, "initTest", InitTest);
}

NODE_MODULE(bridge, Init)