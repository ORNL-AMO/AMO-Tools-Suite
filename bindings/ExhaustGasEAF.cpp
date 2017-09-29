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

#include <calculator/losses/ExhaustGasEAF.h>
#include <nan.h>

using namespace Nan;

static Nan::Persistent<v8::FunctionTemplate> constructor;

/**
 * Exhaust Gas for an Electric Arc Furnace class
 * Contains all of the properties of the exhaust gas from the furnace.
 * Used to calculate the heat loss caused by the exhaust gas coming out of the electric arc furnace.
 */
class ExhaustGasEAFWrapper : public Nan::ObjectWrap, public ExhaustGasEAF {
public:
	static NAN_MODULE_INIT(Init) {
		v8::Local <v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(ExhaustGasEAFWrapper::New);
		constructor.Reset(tpl);
		tpl->SetClassName(Nan::New<v8::String>("ExhaustGasEAF").ToLocalChecked());
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		v8::Local <v8::ObjectTemplate> itpl = tpl->InstanceTemplate();
		SetAccessor(itpl, Nan::New<v8::String>("offGasTemp").ToLocalChecked(), ExhaustGasEAFWrapper::GetOffGasTemp,
		            ExhaustGasEAFWrapper::SetOffGasTemp);
		SetAccessor(itpl, Nan::New<v8::String>("CO").ToLocalChecked(), ExhaustGasEAFWrapper::GetCO, ExhaustGasEAFWrapper::SetCO);
		SetAccessor(itpl, Nan::New<v8::String>("H2").ToLocalChecked(), ExhaustGasEAFWrapper::GetH2, ExhaustGasEAFWrapper::SetH2);
		SetAccessor(itpl, Nan::New<v8::String>("combustibleGases").ToLocalChecked(), ExhaustGasEAFWrapper::GetCombustibleGases,
		            ExhaustGasEAFWrapper::SetCombustibleGases);
		SetAccessor(itpl, Nan::New<v8::String>("vfr").ToLocalChecked(), ExhaustGasEAFWrapper::GetVFR, ExhaustGasEAFWrapper::SetVFR);
		SetAccessor(itpl, Nan::New<v8::String>("dustLoading").ToLocalChecked(), ExhaustGasEAFWrapper::GetDustLoading,
		            ExhaustGasEAFWrapper::SetDustLoading);
		SetAccessor(itpl, Nan::New<v8::String>("totalHeatExhaust").ToLocalChecked(), ExhaustGasEAFWrapper::GetTotalHeatExhaust,
		            ExhaustGasEAFWrapper::SetTotalHeatExhaust);
		Set(target, Nan::New<v8::String>("ExhaustGasEAF").ToLocalChecked(), tpl->GetFunction());
	}

	ExhaustGasEAFWrapper(const double offGasTemp, const double CO, const double H2,
	                       const double combustibleGases, const double vfr, const double dustLoading)
			: ExhaustGasEAF(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading) {}
private:
	static NAN_METHOD(New) {
		auto *obj = new ExhaustGasEAFWrapper(info[0]->NumberValue(), info[1]->NumberValue(), info[2]->NumberValue(),
		                                     info[3]->NumberValue(), info[4]->NumberValue(), info[5]->NumberValue());
		obj->calculateTotalHeatExhaust();
		obj->Wrap(info.This());
		info.GetReturnValue().Set(info.This());
	}

	static NAN_GETTER(GetOffGasTemp);
	static NAN_GETTER(GetCO);
	static NAN_GETTER(GetH2);
	static NAN_GETTER(GetCombustibleGases);
	static NAN_GETTER(GetVFR);
	static NAN_GETTER(GetDustLoading);
	static NAN_GETTER(GetTotalHeatExhaust);

	static NAN_SETTER(SetOffGasTemp);
	static NAN_SETTER(SetCO);
	static NAN_SETTER(SetH2);
	static NAN_SETTER(SetCombustibleGases);
	static NAN_SETTER(SetVFR);
	static NAN_SETTER(SetDustLoading);
	static NAN_SETTER(SetTotalHeatExhaust);
};

void InitExhaustGasEAF(v8::Local<v8::Object> exports) {
    ExhaustGasEAFWrapper::Init(exports);
}

NAN_GETTER(ExhaustGasEAFWrapper::GetOffGasTemp) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->offGasTemp));
}

NAN_SETTER(ExhaustGasEAFWrapper::SetOffGasTemp) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	obj->setOffGasTemp(value->NumberValue());
}

NAN_GETTER(ExhaustGasEAFWrapper::GetCO) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->CO));
}

NAN_SETTER(ExhaustGasEAFWrapper::SetCO) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	obj->setCO(value->NumberValue());
}

NAN_GETTER(ExhaustGasEAFWrapper::GetH2) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->H2));
}

NAN_SETTER(ExhaustGasEAFWrapper::SetH2) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	obj->setH2(value->NumberValue());
}

NAN_GETTER(ExhaustGasEAFWrapper::GetCombustibleGases) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->combustibleGases));
}

NAN_SETTER(ExhaustGasEAFWrapper::SetCombustibleGases) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	obj->setCombustibleGases(value->NumberValue());
}

NAN_GETTER(ExhaustGasEAFWrapper::GetVFR) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->vfr));
}

NAN_SETTER(ExhaustGasEAFWrapper::SetVFR) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	obj->setVfr(value->NumberValue());
}

NAN_GETTER(ExhaustGasEAFWrapper::GetDustLoading) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->dustLoading));
}

NAN_SETTER(ExhaustGasEAFWrapper::SetDustLoading) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	obj->setDustLoading(value->NumberValue());
}

NAN_GETTER(ExhaustGasEAFWrapper::GetTotalHeatExhaust) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->totalHeatExhaust));
}

NAN_SETTER(ExhaustGasEAFWrapper::SetTotalHeatExhaust) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAFWrapper>(info.This());
	obj->totalHeatExhaust = value->NumberValue();
}

NODE_MODULE(exhaustGasEAF, InitExhaustGasEAF)
