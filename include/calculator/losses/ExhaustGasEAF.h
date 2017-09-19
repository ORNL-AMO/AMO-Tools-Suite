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
            v8::Local<v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
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

    double getTotalHeatExhaust();

private:
    const double offGasTemp_, CO_, H2_, combustibleGases_, vfr_, dustLoading_;


    static NAN_METHOD(New) {
        auto * obj = new ExhaustGasEAF(2800, 12, 10, 3, 8000, 0.001);
        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    }
};

void InitExhaustGasEAF(v8::Local<v8::Object> exports) {
    ExhaustGasEAF::Init(exports);
}

NODE_MODULE(exhaustGasEAF, InitExhaustGasEAF)

#endif //AMO_TOOLS_SUITE_EXHAUSTGASEAF_H
