/**
 * @file
 * @brief Calculator for gas exhaust losses in an Electric Arc Furnace (EAF)
 *
 * This contains the inputs for calculating the exhaust gas losses for an Electric Arc
 * Furnace (EAF)
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#ifndef AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
#define AMO_TOOLS_SUITE_EXHAUSTGASEAF_H

#include <nan.h>
using namespace Nan;

static Nan::Persistent<v8::FunctionTemplate> constructor;

/**
 * Exhaust Gas for an Electric Arc Furnace class
 * Contains all of the properties of the exhaust gas from the furnace.
 * Used to calculate the heat loss caused by the exhaust gas coming out of the electric arc furnace.
 */
class ExhaustGasEAF : public Nan::ObjectWrap {
public:
    static NAN_MODULE_INIT(Init) {
            v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(ExhaustGasEAF::New);
            constructor.Reset(tpl);
            tpl->SetClassName(Nan::New<v8::String>("ExhaustGasEAF").ToLocalChecked());
            tpl->InstanceTemplate()->SetInternalFieldCount(1);
            SetPrototypeMethod(tpl, "getTotalHeatExhaustNAN", ExhaustGasEAF::getTotalHeatExhaustNAN);
            v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
            SetAccessor(itpl, Nan::New<v8::String>("offGasTemp").ToLocalChecked(), ExhaustGasEAF::GetVar, ExhaustGasEAF::SetVar);
            Set(target, Nan::New<v8::String>("ExhaustGasEAF").ToLocalChecked(), tpl->GetFunction());
    }

    /**
     * Constructor for the exhaust gas EAF heat loss with all inputs specified
     *
     * @param offGasTemp double, temperature of exhaust gases from EAF before the gases mix with outside air measured in °F
     * @param CO double, % of CO in exhaust gas
     * @param H2 double, % of H2 in exhaust gas
     * @param combustibleGases double, average value of combustible gases % in exhaust gases
     * @param vfr double, (volume flow rate) total volume of exhaust gases measured in cfm
     * @param dustLoading double, dust loading for exhaust gases measured in s/scf (number of dust particles per scf)
     * @return nothing
     *
     * */
    explicit ExhaustGasEAF(const double offGasTemp, const double CO, const double H2,
                  const double combustibleGases, const double vfr, const double dustLoading)
            : offGasTemp_(offGasTemp), CO_(CO), H2_(H2), combustibleGases_(combustibleGases),
              vfr_(vfr), dustLoading_(dustLoading)
    {}



    double getTotalHeatExhaust() const { return totalHeatExhaust; }



private:
    const double offGasTemp_, CO_, H2_, combustibleGases_, vfr_, dustLoading_;
    double totalHeatExhaust = 0;

    void calculateTotalHeatExhaust();

    static NAN_METHOD(New) {
        auto * obj = new ExhaustGasEAF(info[0]->NumberValue(), info[1]->NumberValue(), info[2]->NumberValue(),
                                       info[3]->NumberValue(), info[4]->NumberValue(), info[5]->NumberValue());
        obj->calculateTotalHeatExhaust();
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }

    static NAN_GETTER(GetVar);
    static NAN_SETTER(SetVar);
    static NAN_METHOD(getTotalHeatExhaustNAN);
};

//NAN_METHOD(ExhaustGasEAF::getTotalHeatExhaustNAN) {
//	ExhaustGasEAF * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.Holder());
//	info.GetReturnValue().Set(Nan::New<v8::Number>(obj->getTotalHeatExhaust()));
//}

void InitExhaustGasEAF(v8::Local<v8::Object> exports) {
    ExhaustGasEAF::Init(exports);
}

NODE_MODULE(exhaustGasEAF, InitExhaustGasEAF)

#endif //AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
