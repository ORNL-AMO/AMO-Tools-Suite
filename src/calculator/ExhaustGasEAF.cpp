/**
 * @file
 * @brief Contains the implementation of the Exhaust Gas EAF loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "calculator/ExhaustGasEAF.h"

void ExhaustGasEAF::calculateTotalHeatExhaust(){
    const double COheatingValue = CO_ * 321 / 100;
	const double H2heatingValue = H2_ * 325 / 100;
    const double combustibles = combustibleGases_ * 1020 / 100;
    const double chemicalHeat = COheatingValue + H2heatingValue + combustibles;

    const double sensibleHeat = 0.0225 * (offGasTemp_ - 60);
	const double heatInDust = dustLoading_ * 0.25 * (offGasTemp_ - 60);
	const double totalHeatFlue = chemicalHeat + sensibleHeat + heatInDust;
    const double totalVfr = vfr_ * 520 / (460 + offGasTemp_);
    totalHeatExhaust = totalVfr * totalHeatFlue * 60;
}

//NAN_GETTER(ExhaustGasEAF::GetVar) {
//	v8::Isolate* isolate = info.GetIsolate();
//	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
//	v8::String::Utf8Value s(property);
//	std::string str(*s);
//
//	if (str == "offGasTemp") info.GetReturnValue().Set(v8::Number::New(isolate, obj->offGasTemp_));
//	else if (str == "CO") info.GetReturnValue().Set(v8::Number::New(isolate, obj->CO_));
//	else if (str == "H2") info.GetReturnValue().Set(v8::Number::New(isolate, obj->H2_));
//	else if (str == "combustibleGases") info.GetReturnValue().Set(v8::Number::New(isolate, obj->combustibleGases_));
//	else if (str == "vfr") info.GetReturnValue().Set(v8::Number::New(isolate, obj->vfr_));
//	else if (str == "dustLoading") info.GetReturnValue().Set(v8::Number::New(isolate, obj->dustLoading_));
//	else if (str == "totalHeatExhaust") info.GetReturnValue().Set(v8::Number::New(isolate, obj->totalHeatExhaust));
//}

//NAN_SETTER(ExhaustGasEAF::SetVar) {
//	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
//	v8::String::Utf8Value s(property);
//	std::string str(*s);
//
//	if (str == "offGasTemp") obj->offGasTemp_ = value->NumberValue();
//	else if (str == "CO") obj->CO_ = value->NumberValue();
//	else if (str == "H2") obj->H2_ = value->NumberValue();
//	else if (str == "combustibleGases") obj->combustibleGases_ = value->NumberValue();
//	else if (str == "vfr") obj->vfr_ = value->NumberValue();
//	else if (str == "dustLoading") obj->dustLoading_ = value->NumberValue();
//	else if (str == "totalHeatExhaust") obj->totalHeatExhaust = value->NumberValue();
//	obj->calculateTotalHeatExhaust();
//}

NAN_GETTER(ExhaustGasEAF::GetOffGasTemp) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->offGasTemp_));
}

NAN_SETTER(ExhaustGasEAF::SetOffGasTemp) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	obj->offGasTemp_ = value->NumberValue();
	obj->calculateTotalHeatExhaust();
}

NAN_GETTER(ExhaustGasEAF::GetCO) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->CO_));
}

NAN_SETTER(ExhaustGasEAF::SetCO) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	obj->CO_ = value->NumberValue();
	obj->calculateTotalHeatExhaust();
}

NAN_GETTER(ExhaustGasEAF::GetH2) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->H2_));
}

NAN_SETTER(ExhaustGasEAF::SetH2) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	obj->H2_ = value->NumberValue();
	obj->calculateTotalHeatExhaust();
}

NAN_GETTER(ExhaustGasEAF::GetCombustibleGases) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->combustibleGases_));
}

NAN_SETTER(ExhaustGasEAF::SetCombustibleGases) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	obj->combustibleGases_ = value->NumberValue();
	obj->calculateTotalHeatExhaust();
}

NAN_GETTER(ExhaustGasEAF::GetVFR) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->vfr_));
}

NAN_SETTER(ExhaustGasEAF::SetVFR) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	obj->vfr_ = value->NumberValue();
	obj->calculateTotalHeatExhaust();
}

NAN_GETTER(ExhaustGasEAF::GetDustLoading) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->dustLoading_));
}

NAN_SETTER(ExhaustGasEAF::SetDustLoading) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	obj->dustLoading_ = value->NumberValue();
	obj->calculateTotalHeatExhaust();
}

NAN_GETTER(ExhaustGasEAF::GetTotalHeatExhaust) {
	v8::Isolate* isolate = info.GetIsolate();
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	info.GetReturnValue().Set(v8::Number::New(isolate, obj->totalHeatExhaust));
}

NAN_SETTER(ExhaustGasEAF::SetTotalHeatExhaust) {
	auto * obj = ObjectWrap::Unwrap<ExhaustGasEAF>(info.This());
	obj->totalHeatExhaust = value->NumberValue();
}
