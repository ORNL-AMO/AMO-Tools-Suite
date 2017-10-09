#ifndef AMO_TOOLS_SUITE_STANDALONE_H
#define AMO_TOOLS_SUITE_STANDALONE_H

#include <nan.h>
#include <node.h>
#include "calculator/util/CHP.h"
#include <string>


using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(std::string const & nm) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();

	auto rObj = inp->ToObject()->Get(getName);
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in standalone.h: " + nm + " not present in object").c_str());
	}
	return rObj->NumberValue();
}

void SetR(std::string const & nm, double n) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	Local<Number> getNum = Nan::New<Number>(n);
	Nan::Set(r, getName, getNum);
}

NAN_METHOD(CHP) {
	inp = info[0]->ToObject();
	r = Nan::New<Object>();

	CHP::Option option = static_cast<CHP::Option>(Get("option"));

	auto const chp = CHP::CHP(Get("annualOperatingHours"), Get("annualElectricityConsumption"), Get("annualThermalDemand"),
	                     Get("boilerThermalFuelCosts"), Get("avgElectricityCosts"), option, Get("boilerThermalFuelCostsCHPcase"),
	                     Get("CHPfuelCosts"), Get("percentAvgkWhElectricCostAvoidedOrStandbyRate"), Get("displacedThermalEfficiency"),
	                     Get("chpAvailability"), Get("thermalUtilization"));

	auto const & costInfo = chp.getCostInfo();

	SetR("annualOperationSavings", costInfo.at("annualOperationSavings"));
	SetR("totalInstalledCostsPayback", costInfo.at("totalInstalledCostsPayback"));
	SetR("simplePayback", costInfo.at("simplePayback"));
	SetR("fuelCosts", costInfo.at("fuelCosts"));
	SetR("thermalCredit", costInfo.at("thermalCredit"));
	SetR("incrementalOandM", costInfo.at("incrementalOandM"));
	SetR("totalOperatingCosts", costInfo.at("totalOperatingCosts"));
	info.GetReturnValue().Set(r);
}

#endif //AMO_TOOLS_SUITE_STANDALONE_H
