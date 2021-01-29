#ifndef AMO_TOOLS_SUITE_LOSSES_H
#define AMO_TOOLS_SUITE_LOSSES_H

#include <nan.h>
#include <node.h>
#include <iostream>
#include <string>
#include "calculator/furnace/EfficiencyImprovement.h"
#include "calculator/furnace/EnergyEquivalency.h"
#include "calculator/furnace/FlowCalculationsEnergyUse.h"
#include "calculator/furnace/O2Enrichment.h"
#include "calculator/losses/Atmosphere.h"
#include "calculator/losses/AuxiliaryPower.h"
#include "calculator/losses/EnergyInputExhaustGasLosses.h"
#include "calculator/losses/EnergyInputEAF.h"
#include "calculator/losses/ExhaustGasEAF.h"
#include "calculator/losses/FixtureLosses.h"
#include "calculator/losses/GasFlueGasMaterial.h"
#include "calculator/losses/SolidLiquidFlueGasMaterial.h"
#include "calculator/losses/LoadChargeMaterial.h"
#include "calculator/losses/GasCoolingLosses.h"
#include "calculator/losses/GasLoadChargeMaterial.h"
#include "calculator/losses/LeakageLosses.h"
#include "calculator/losses/LiquidCoolingLosses.h"
#include "calculator/losses/LiquidLoadChargeMaterial.h"
#include "calculator/losses/OpeningLosses.h"
#include "calculator/losses/SlagOtherMaterialLosses.h"
#include "calculator/losses/SolidLoadChargeMaterial.h"
#include "calculator/losses/WallLosses.h"
#include "calculator/losses/WaterCoolingLosses.h"
#include "calculator/furnace/HumidityRatio.h"
#include "calculator/util/Conversion.h"

using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

double Get(std::string const & nm) {
	Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
	v8::Isolate *isolate = v8::Isolate::GetCurrent();
	v8::Local<v8::Context> context = isolate->GetCurrentContext();
	Local<Value> rObj = Nan::To<Object>(inp).ToLocalChecked()->Get(context, getName).ToLocalChecked();
	if (rObj->IsUndefined()) {
		ThrowTypeError(std::string("Get method in phast.h: " + nm + " not present in object").c_str());
	}
	return Nan::To<double>(rObj).FromJust();
}

void SetR(std::string const &nm, double n)
{
    Local<String> getName = Nan::New<String>(nm).ToLocalChecked();
    Local<Number> getNum = Nan::New<Number>(n);
    Nan::Set(r, getName, getNum);
}

FlowCalculationsEnergyUse::Gas gas()
{
    return (FlowCalculationsEnergyUse::Gas)(int)Get("gasType");
}

FlowCalculationsEnergyUse::Section section()
{
    return (FlowCalculationsEnergyUse::Section)(int)Get("sectionType");
}

NAN_METHOD(atmosphere)
{

    /**
     * Constructor for the atmospheric heat loss with all inputs specified
     *
     * @param inletTemperature double, inlet temperature of gasses in °F
     * @param outletTemperature double, outlet temperature of gasses in °F
     * @param flowRate double, flow rate of gasses in scfh
     * @param correctionFactor double, correction factor - unitless
     * @param specificHeat double, specific heat of gasses at average air temperature in Btu/(scf - °F)
     *
     * */

    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double inletTemperature = Get("inletTemperature");
    const double outletTemperature = Get("outletTemperature");
    const double flowRate = Get("flowRate");
    const double correctionFactor = Get("correctionFactor");
    const double specificHeat = Get("specificHeat");

    Atmosphere a(inletTemperature, outletTemperature, flowRate, correctionFactor, specificHeat);
    double heatLoss = a.getTotalHeat();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(auxiliaryPowerLoss)
{
    /**
 * Constructor

 * @param motorPhase double, current motor phase - this option is greyed out in PHAST 3.0
 * @param supplyVoltage double, supply voltage in volts
 * @param avgCurrent double, average current in Amperes
 * @param powerFactor double, average power factor value - unitless
 * @param operatingTime double, percent operating time
 */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double motorPhase = Get("motorPhase");
    const double supplyVoltage = Get("supplyVoltage");
    const double avgCurrent = Get("avgCurrent");
    const double powerFactor = Get("powerFactor");
    const double operatingTime = Get("operatingTime");

    auto const ap = AuxiliaryPower(motorPhase, supplyVoltage, avgCurrent, powerFactor, operatingTime);

    const double powerUsed = ap.getPowerUsed();
    Local<Number> retval = Nan::New(powerUsed);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(energyInputEAF)
{

    /**
     * Constructor for the Electric Arc Furnace (EAF) heat loss with all inputs specified
     *
     * @param naturalGasHeatInput double, value of total heat input to the heating system (furn:ace/oven) from all
     *                              sources of heat supplied (natural gas, carbon, fuel oil, etc.)
     *                              measured in mm btu/cycle
     * @param coalCarbonInjection double, mass of coal or carbon injection for the cycle measured in lbs/cycle
     * @param coalHeatingValue double, heating value for the coal or carbon injected measured in btu/lb
     * @param electrodeUse double, electrode use measured in lbs/cycle
     * @param electrodeHeatingValue double, electrode heating value measured in btu/lb
     * @param otherFuels double, heat supplied from other sources, if any, measured in mm btu/cycle
     * @param electricityInput double, total electric power supplied for the cycle measured in kwh/cycle
     * @return double, heat delivered in btu/cycle
     *
     * */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double naturalGasHeatInput = Get("naturalGasHeatInput");
    const double coalCarbonInjection = Get("coalCarbonInjection");
    const double coalHeatingValue = Get("coalHeatingValue");
    const double electrodeUse = Get("electrodeUse");
    const double electrodeHeatingValue = Get("electrodeHeatingValue");
    const double otherFuels = Get("otherFuels");
    const double electricityInput = Get("electricityInput");

    EnergyInputEAF eaf(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse,
                       electrodeHeatingValue, otherFuels, electricityInput);
    const double heatDelivered = eaf.getHeatDelivered();
    const double totalChemicalEnergyInput = eaf.getTotalChemicalEnergyInput();

    SetR("heatDelivered", heatDelivered);
    SetR("totalChemicalEnergyInput", totalChemicalEnergyInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(exhaustGasEAF)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double offGasTemp = Get("offGasTemp");
    const double CO = Get("CO");
    const double H2 = Get("H2");
    const double combustibleGases = Get("combustibleGases");
    const double vfr = Get("vfr");
    const double dustLoading = Get("dustLoading");

    ExhaustGasEAF eg(offGasTemp, CO, H2, combustibleGases, vfr, dustLoading);
    const double totalHeatExhaust = eg.getTotalHeatExhaust();

    Local<Number> retval = Nan::New(totalHeatExhaust);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(fixtureLosses)
{

    /**
    * Constructor for Fixture Losses
    * @param specificHeat double, specific heat in btu/(lb*°F)
    * @param feedRate double, feed rate for gas mixture in lb/hr
    * @param initialTemperature double, initial temperature in °F
    * @param finalTemperature double, final temperature in °F
    * @param correctionFactor double, correction factor - unitless
    *
    * @return double, heat loss in btu/cycle
    */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double specificHeat = Get("specificHeat");
    const double feedRate = Get("feedRate");
    const double initialTemperature = Get("initialTemperature");
    const double finalTemperature = Get("finalTemperature");
    const double correctionFactor = Get("correctionFactor");

    FixtureLosses fl(specificHeat, feedRate, initialTemperature, finalTemperature, correctionFactor);
    double heatLoss = fl.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(gasCoolingLosses)
{
    /**
  * Constructor for the gas cooling losses (including air) with all inputs specified
  *
  * @param flowRate double, air or gas volumetric flow rate in SCFM (ft³/min)
  * @param initialTemperature double, inlet temperature of air or gas in °F
  * @param finalTemperature double, outlet temperature of air or gas in °F
  * @param specificHeat double, specific heat of gas or air at average air temperature in Btu/(scf*°F)
  * @param correctionFactor double, correction factor - unitless
  *
  * @return heatLoss double
  * */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double flowRate = Get("flowRate");
    const double initialTemperature = Get("initialTemperature");
    const double finalTemperature = Get("finalTemperature");
    const double specificHeat = Get("specificHeat");
    const double correctionFactor = Get("correctionFactor");
    const double gasDensity = Get("gasDensity");

    GasCoolingLosses gcl(flowRate, initialTemperature, finalTemperature, specificHeat, correctionFactor,
                         gasDensity);
    const double heatLoss = gcl.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(gasLoadChargeMaterial)
{
    /**
 * Constructor for the gas load/charge material with all inputs specified
 *
 * @param thermicReactionType ThermicReactionType, enumerated value for either endothermic or exothermic reactions 0 = Endo, else = Exo Int
 * @param specificHeatGas double, specific heat of gas in Btu/(lb*°F)
 * @param feedRate double, feed rate for gas mixture
 * @param percentVapor double, vapor in gas mixture (% of total)
 * @param initialTemperature double, initial temperature in °F
 * @param dischargeTemperature double, discharge temperature in °F
 * @param specificHeatVapor double, specific heat of vapor in Btu/(lb*°F)
 * @param percentReacted double, feed gas reacted (% of total)
 * @param reactionHeat double, heat of reaction in Btu/lb
 * @param additionalHeat double, additional heat required in Btu/hr
 *
 * @return double, heat loss in btu/cycle
 *
 * */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double specificHeatGas = Get("specificHeatGas");
    const double feedRate = Get("feedRate");
    const double percentVapor = Get("percentVapor");
    const double initialTemperature = Get("initialTemperature");
    const double dischargeTemperature = Get("dischargeTemperature");
    const double specificHeatVapor = Get("specificHeatVapor");
    const double percentReacted = Get("percentReacted");
    const double reactionHeat = Get("reactionHeat");
    const double additionalHeat = Get("additionalHeat");
    const double thermicReactionTypeInput = Get("thermicReactionType");

    LoadChargeMaterial::ThermicReactionType thermicReactionType;
    if (thermicReactionTypeInput == 0)
    {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
    }
    else
    {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
    }
    GasLoadChargeMaterial glcm(thermicReactionType, specificHeatGas, feedRate, percentVapor, initialTemperature,
                               dischargeTemperature, specificHeatVapor, percentReacted, reactionHeat, additionalHeat);
    double heatLoss = glcm.getTotalHeat();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(leakageLosses)
{
    /**
     * Constructor
     * @param draftPressure double, furnace draft pressure in inch W.C.
     * @param openingArea double, opening area in ft^2
     * @param leakageGasTemperature double, temperature of gases leaking from furnace in °F
     * @param ambientTemperature double, ambient temperature in °F
     * @param coefficient double, coefficient - unitless
     * @param specificGravity double, specific gravity - unitless
     * @param correctionFactor double, correction factor - unitless
     */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double draftPressure = Get("draftPressure");
    const double openingArea = Get("openingArea");
    const double leakageGasTemperature = Get("leakageGasTemperature");
    const double ambientTemperature = Get("ambientTemperature");
    const double coefficient = Get("coefficient");
    const double specificGravity = Get("specificGravity");
    const double correctionFactor = Get("correctionFactor");

    LeakageLosses ll(draftPressure, openingArea, leakageGasTemperature, ambientTemperature,
                     coefficient, specificGravity, correctionFactor);
    double heatLoss = ll.getExfiltratedGasesHeatContent();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(liquidCoolingLosses)
{
    /**
 * Constructor
 * @param flowRate double, rate of flow in gpm.
 * @param density double, density in lb/cu.ft
 * @param initialTemperature double, initial temperature in °F.
 * @param outletTemperature double, outlet temperature in °F
 * @param specificHeat double, specific heat in btu/(lb*°F)
 * @param correctionFactor double, correction factor - unitless
 * @return double, heat loss in btu/hr
 */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double flowRate = Get("flowRate");
    const double density = Get("density");
    const double initialTemperature = Get("initialTemperature");
    const double outletTemperature = Get("outletTemperature");
    const double specificHeat = Get("specificHeat");
    const double correctionFactor = Get("correctionFactor");

    LiquidCoolingLosses lcl(flowRate, density, initialTemperature, outletTemperature,
                            specificHeat, correctionFactor);
    double heatLoss = lcl.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(liquidLoadChargeMaterial)
{
    /**
         * Constructor for liquid load/charge material with all inputs specified
         *
         * @param thermicReactionType ThermicReactionType, enumerated value for either endothermic or exothermic reactions
         * @param specificHeatLiquid double, specific heat of liquid in Btu/(lb*°F)
         * @param vaporizingTemperature double, vaporizing temperature in °F
         * @param latentHeat double, latent heat of vaporization in Btu/lb
         * @param specificHeatVapor double, specific heat of vapor in Btu/(lb*°F)
         * @param chargeFeedRate double, charge (liquid)-feed rate in lb/hr
         * @param initialTemperature double, initial temperature in °F
         * @param dischargeTemperature double, discharge temperature in °F
         * @param percentVaporized double, charge liquid vaporized  (% of charge)
         * @param percentReacted double, charge liquid reacted (% of charge)
         * @param reactionHeat double, heat of reaction in Btu/lb
         * @param additionalHeat double, additional heat required in %
         * @return double, heat loss in btu/hr
         * */

    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double specificHeatLiquid = Get("specificHeatLiquid");
    const double vaporizingTemperature = Get("vaporizingTemperature");
    const double latentHeat = Get("latentHeat");
    const double specificHeatVapor = Get("specificHeatVapor");
    const double chargeFeedRate = Get("chargeFeedRate");
    const double initialTemperature = Get("initialTemperature");
    const double dischargeTemperature = Get("dischargeTemperature");
    const double percentVaporized = Get("percentVaporized");
    const double percentReacted = Get("percentReacted");
    const double reactionHeat = Get("reactionHeat");
    const double additionalHeat = Get("additionalHeat");
    const double thermicReactionTypeInput = Get("thermicReactionType");

    LoadChargeMaterial::ThermicReactionType thermicReactionType;
    if (thermicReactionTypeInput == 0)
    {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
    }
    else
    {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
    }
    LiquidLoadChargeMaterial llcm(thermicReactionType, specificHeatLiquid, vaporizingTemperature, latentHeat,
                                  specificHeatVapor, chargeFeedRate, initialTemperature, dischargeTemperature,
                                  percentVaporized, percentReacted, reactionHeat, additionalHeat);
    double heatLoss = llcm.getTotalHeat();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(openingLossesCircular)
{

    /**
         * Constructor for a circular opening
         * @param emissivity double, emissivity - unitless
         * @param diameter double, length of opening in inches
         * @param thickness double, furnace wall thickness in inches
         * @param ratio double, ratio - unitless
         * @param ambientTemperature double, ambient temperature in °F
         * @param insideTemperature double, inside temperature in °F
         * @param percentTimeOpen double, amount of time open as %
         * @param viewFactor double, view factor - unitless
         */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double emissivity = Get("emissivity");
    const double diameter = Get("diameter");
    const double thickness = Get("thickness");
    const double ratio = Get("ratio");
    const double ambientTemperature = Get("ambientTemperature");
    const double insideTemperature = Get("insideTemperature");
    const double percentTimeOpen = Get("percentTimeOpen");
    const double viewFactor = Get("viewFactor");

    OpeningLosses ol(emissivity, diameter, thickness, ratio, ambientTemperature,
                     insideTemperature, percentTimeOpen, viewFactor);
    double heatLoss = ol.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}
NAN_METHOD(openingLossesQuad)
{

    /**
         * Constructor for a rectangular opening
         * @param emissivity double, emissivity - unitless
         * @param length double, length of openings in inches
         * @param width double, height of openings in inches
         * @param thickness double, furnace wall thickness in inches
         * @param ratio double, ratio - unitless
         * @param ambientTemperature double, ambient temperature in °F
         * @param insideTemperature double, inside temperature in °F
         * @param percentTimeOpen double, amount of time open as a %
         * @param viewFactor double, view factor - unitless
         * @return double, heatLoss in btu/cycle
         */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double emissivity = Get("emissivity");
    const double length = Get("length");
    const double width = Get("width");
    const double thickness = Get("thickness");
    const double ratio = Get("ratio");
    const double ambientTemperature = Get("ambientTemperature");
    const double insideTemperature = Get("insideTemperature");
    const double percentTimeOpen = Get("percentTimeOpen");
    const double viewFactor = Get("viewFactor");

    OpeningLosses ol(emissivity, length, width, thickness, ratio,
                     ambientTemperature, insideTemperature, percentTimeOpen, viewFactor);
    double heatLoss = ol.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

OpeningLosses::OpeningShape getOpeningShape()
{
    unsigned val = static_cast<unsigned>(Get("openingShape"));
    return static_cast<OpeningLosses::OpeningShape>(val);
}

NAN_METHOD(viewFactorCalculation)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double thickness = Get("thickness");

    OpeningLosses opening;
    OpeningLosses::OpeningShape shape = getOpeningShape();
    if (shape == OpeningLosses::OpeningShape::CIRCULAR)
    {
        const double diameter = Get("diameter");
        Local<Number> rv = Nan::New(opening.calculateViewFactor(thickness, diameter));
        info.GetReturnValue().Set(rv);
    }
    else
    {
        const double length = Get("length");
        const double width = Get("width");
        Local<Number> rv = Nan::New(opening.calculateViewFactor(thickness, length, width));
        info.GetReturnValue().Set(rv);
    }
}

NAN_METHOD(slagOtherMaterialLosses)
{

    /**     * Constructor for the slag - other material heat loss with all inputs specified
        *
        * @param weight double, weight in lb/cycle
        * @param inletTemperature double, inlet temperature of gasses in °F
        * @param outletTemperature double, outlet temperature of gasses in °F
        * @param specificHeat double, specific heat of material at average air temperature in Btu/(lb*°F)
        * @param correctionFactor double, correction factor - unitless
        * @return double, heat loss in btu/cycle
        *
        * */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double weight = Get("weight");
    const double inletTemperature = Get("inletTemperature");
    const double outletTemperature = Get("outletTemperature");
    const double specificHeat = Get("specificHeat");
    const double correctionFactor = Get("correctionFactor");

    SlagOtherMaterialLosses sl(weight, inletTemperature, outletTemperature, specificHeat, correctionFactor);
    double heatLoss = sl.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(solidLoadChargeMaterial)
{
    /**
 * Constructor for the solid load/charge material with all inputs specified.
 *
 * @param thermicReactionType ThermicReactionType, enumerated value for either endothermic or exothermic reactions
 * @param specificHeatSolid double, average specific heat of the solid material (dry) in Btu/(lb*°F)
 * @param latentHeat double, latent heat of fusion in Btu/(lb)
 * @param specificHeatLiquid double, specific heat of liquid from molten material in Btu/(lb*°F)
 * @param meltingPoint double, the melting point of the material in °F
 * @param chargeFeedRate double, charge (wet)-feed rate in lb/hr
 * @param waterContentCharged double, water content as charged (%) in %
 * @param waterContentDischarged double, water content as discharged (%) in %
 * @param initialTemperature double, initial temperature in °F
 * @param dischargeTemperature double, charge material discharge temperature in °F
 * @param waterVaporDischargeTemperature double, water vapor discharge temperature in °F
 * @param chargeMelted double, charge melted (% of dry charge) in %
 * @param chargeReacted double, charge Reacted (% of dry charge) in %
 * @param reactionHeat double, heat of reaction in Btu/lb
 * @param additionalHeat double, additional heat required in Btu/hr
 *
 * */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double specificHeatSolid = Get("specificHeatSolid");
    const double latentHeat = Get("latentHeat");
    const double specificHeatLiquid = Get("specificHeatLiquid");
    const double meltingPoint = Get("meltingPoint");
    const double chargeFeedRate = Get("chargeFeedRate");
    const double waterContentCharged = Get("waterContentCharged");
    const double waterContentDischarged = Get("waterContentDischarged");
    const double initialTemperature = Get("initialTemperature");
    const double dischargeTemperature = Get("dischargeTemperature");
    const double waterVaporDischargeTemperature = Get("waterVaporDischargeTemperature");
    const double chargeMelted = Get("chargeMelted");
    const double chargeReacted = Get("chargeReacted");
    const double reactionHeat = Get("reactionHeat");
    const double additionalHeat = Get("additionalHeat");
    const double thermicReactionTypeInput = Get("thermicReactionType");

    LoadChargeMaterial::ThermicReactionType thermicReactionType;
    if (thermicReactionTypeInput == 0)
    {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
    }
    else
    {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
    }
    SolidLoadChargeMaterial slcm(thermicReactionType, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint, chargeFeedRate, waterContentCharged, waterContentDischarged,
                                 initialTemperature, dischargeTemperature, waterVaporDischargeTemperature, chargeMelted, chargeReacted, reactionHeat, additionalHeat);
    double heatLoss = slcm.getTotalHeat();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(wallLosses)
{
    /**
  * Wall Losses Arguments
  * @param surfaceArea double, total outside surface area in ft^2
  * @param ambientTemperature double, ambient temperature in °F
  * @param surfaceTemperature double, average surface temperature (measured) in °F
  * @param windVelocity double, wind velocity in miles/hr
  * @param surfaceEmissivity double, surface emissivity - unitless
  * @param conditionFactor double, condition factor - unitless
  * @param correctionFactor double, correction factor - unitless
  * @return double, heat loss in btu/cycle
  */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double surfaceArea = Get("surfaceArea");
    const double ambientTemperature = Get("ambientTemperature");
    const double surfaceTemperature = Get("surfaceTemperature");
    const double windVelocity = Get("windVelocity");
    const double surfaceEmissivity = Get("surfaceEmissivity");
    const double conditionFactor = Get("conditionFactor");
    const double correctionFactor = Get("correctionFactor");

    WallLosses wl(surfaceArea, ambientTemperature, surfaceTemperature, windVelocity,
                  surfaceEmissivity, conditionFactor, correctionFactor);
    double heatLoss = wl.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(waterCoolingLosses)
{
    /**
     * Constructor
     * @param flowRate double, rate of flow in gpm
     * @param initialTemperature double, initial temperature in °F
     * @param outletTemperature double, outlet temperature in °F
     * @param correctionFactor double, correction factor - unitless
     */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double flowRate = Get("flowRate");
    const double initialTemperature = Get("initialTemperature");
    const double outletTemperature = Get("outletTemperature");
    const double correctionFactor = Get("correctionFactor");

    WaterCoolingLosses wcl(flowRate, initialTemperature, outletTemperature, correctionFactor);
    double heatLoss = wcl.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

// Furnace calculators

NAN_METHOD(efficiencyImprovement)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double currentFlueGasOxygen = Get("currentFlueGasOxygen");
    const double newFlueGasOxygen = Get("newFlueGasOxygen");
    const double currentFlueGasTemp = Get("currentFlueGasTemp");
    const double newFlueGasTemp = Get("newFlueGasTemp");
    const double currentCombustionAirTemp = Get("currentCombustionAirTemp");
    const double newCombustionAirTemp = Get("newCombustionAirTemp");
    const double currentEnergyInput = Get("currentEnergyInput");

    EfficiencyImprovement ei(currentFlueGasOxygen, newFlueGasOxygen, currentFlueGasTemp, newFlueGasTemp,
                             currentCombustionAirTemp, newCombustionAirTemp, currentEnergyInput);
    double currentExcessAir = ei.getCurrentExcessAir();
    double newExcessAir = ei.getNewExcessAir();
    double currentAvailableHeat = ei.getCurrentAvailableHeat();
    double newAvailableHeat = ei.getNewAvailableHeat();
    double newFuelSavings = ei.getNewFuelSavings();
    double newEnergyInput = ei.getNewEnergyInput();

    SetR("currentExcessAir", currentExcessAir);
    SetR("newExcessAir", newExcessAir);
    SetR("currentAvailableHeat", currentAvailableHeat);
    SetR("newAvailableHeat", newAvailableHeat);
    SetR("newFuelSavings", newFuelSavings);
    SetR("newEnergyInput", newEnergyInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(energyEquivalencyElectric)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double fuelFiredEfficiency = Get("fuelFiredEfficiency");
    const double electricallyHeatedEfficiency = Get("electricallyHeatedEfficiency");
    const double fuelFiredHeatInput = Get("fuelFiredHeatInput");

    ElectricalEnergyEquivalency eee(fuelFiredEfficiency, electricallyHeatedEfficiency, fuelFiredHeatInput);
    double electricalHeatInput = eee.getElectricalHeatInput();

    SetR("electricalHeatInput", electricalHeatInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(energyEquivalencyFuel)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double electricallyHeatedEfficiency = Get("electricallyHeatedEfficiency");
    const double fuelFiredEfficiency = Get("fuelFiredEfficiency");
    const double electricalHeatInput = Get("electricalHeatInput");

    FuelFiredEnergyEquivalency ffee(electricallyHeatedEfficiency, fuelFiredEfficiency, electricalHeatInput);
    double fuelFiredHeatInput = ffee.getFuelFiredHeatInput();

    SetR("fuelFiredHeatInput", fuelFiredHeatInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(flowCalculations)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double specificGravity = Get("specificGravity");
    const double orificeDiameter = Get("orificeDiameter");
    const double insidePipeDiameter = Get("insidePipeDiameter");
    const double dischargeCoefficient = Get("dischargeCoefficient");
    const double gasHeatingValue = Get("gasHeatingValue");
    const double gasTemperature = Get("gasTemperature");
    const double gasPressure = Get("gasPressure");
    const double orificePressureDrop = Get("orificePressureDrop");
    const double operatingTime = Get("operatingTime");

    FlowCalculationsEnergyUse::Gas gas1 = gas();
    FlowCalculationsEnergyUse::Section section1 = section();
    FlowCalculationsEnergyUse fceu(gas1, specificGravity, orificeDiameter, insidePipeDiameter, section1, dischargeCoefficient,
                                   gasHeatingValue, gasTemperature, gasPressure, orificePressureDrop, operatingTime);
    double flow = fceu.getFlow();
    double heatInput = fceu.getHeatInput();
    double totalFlow = fceu.getTotalFlow();

    SetR("flow", flow);
    SetR("heatInput", heatInput);
    SetR("totalFlow", totalFlow);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(flueGasLossesByVolume)
{
    /**
	 * Constructor for the flue gas losses by volume with all inputs specified
	 *
	 * @param flueGasTemperature double, temperature of flue gas in °F
	 * @param excessAirPercentage double, excess air as %
	 * @param combustionAirTemperature double, temperature of combustion air in °F
	 * @param gasComposition double, percentages for CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2 and O2
	 * @return heatLoss / available heat
	 *
	 * */

    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double CH4 = Get("CH4");
    const double C2H6 = Get("C2H6");
    const double N2 = Get("N2");
    const double H2 = Get("H2");
    const double C3H8 = Get("C3H8");
    const double C4H10_CnH2n = Get("C4H10_CnH2n");
    const double H2O = Get("H2O");
    const double CO = Get("CO");
    const double CO2 = Get("CO2");
    const double SO2 = Get("SO2");
    const double O2 = Get("O2");

    const double flueGasTemperature = Get("flueGasTemperature");
    const double excessAirPercentage = Get("excessAirPercentage");
    const double combustionAirTemperature = Get("combustionAirTemperature");
    const double fuelTemperature = Get("fuelTemperature");

    GasCompositions comps("", CH4, C2H6, N2, H2, C3H8,
                          C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    GasFlueGasMaterial fg(flueGasTemperature, excessAirPercentage, combustionAirTemperature,
                          comps, fuelTemperature);
    double heatLoss = fg.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(flueGasByVolumeCalculateHeatingValue)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double CH4 = Get("CH4");
    const double C2H6 = Get("C2H6");
    const double N2 = Get("N2");
    const double H2 = Get("H2");
    const double C3H8 = Get("C3H8");
    const double C4H10_CnH2n = Get("C4H10_CnH2n");
    const double H2O = Get("H2O");
    const double CO = Get("CO");
    const double CO2 = Get("CO2");
    const double SO2 = Get("SO2");
    const double O2 = Get("O2");

    GasCompositions comps("", CH4, C2H6, N2, H2, C3H8,
                          C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    double heatingValue = comps.getHeatingValue();
    double heatingValueVolume = comps.getHeatingValueVolume();
    double specificGravity = comps.getSpecificGravity();

    SetR("heatingValue", heatingValue);
    SetR("heatingValueVolume", heatingValueVolume);
    SetR("specificGravity", specificGravity);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(flueGasLossesByMass)
{
    /**
	 * Constructor for the flue gas losses by weight with all inputs specified
	 *
	 * @param flueGasTemperature double, flue gas temperature in °F
	 * @param excessAirPercentage double, excess air as %
	 * @param combustionAirTemperature double, combustion air temperature in °F
	 * @param fuelTemperature double, temperature of fuel in °F
	 * @param moistureInAirComposition double, moisture in air composition as %
	 * @param ashDischargeTemperature double, temperature of ash discharge in °F
	 * @param unburnedCarbonInAsh double, amount of unburned carbon in ash as %
	 * @param fuel double, composition of: carbon, hydrogen, sulphur, inertAsh, o2, moisture and nitrogen (in %)
	 * @return heat loss / available heat
	 *
	 * */

    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double flueGasTemperature = Get("flueGasTemperature");
    const double excessAirPercentage = Get("excessAirPercentage");
    const double combustionAirTemperature = Get("combustionAirTemperature");
    const double fuelTemperature = Get("fuelTemperature");
    const double moistureInAirComposition = Get("moistureInAirComposition");
    const double ashDischargeTemperature = Get("ashDischargeTemperature");
    const double unburnedCarbonInAsh = Get("unburnedCarbonInAsh");
    const double carbon = Get("carbon");
    const double hydrogen = Get("hydrogen");
    const double sulphur = Get("sulphur");
    const double inertAsh = Get("inertAsh");
    const double o2 = Get("o2");
    const double moisture = Get("moisture");
    const double nitrogen = Get("nitrogen");

    SolidLiquidFlueGasMaterial slfgm(flueGasTemperature, excessAirPercentage, combustionAirTemperature,
                                     fuelTemperature, moistureInAirComposition, ashDischargeTemperature,
                                     unburnedCarbonInAsh, carbon, hydrogen, sulphur, inertAsh, o2, moisture,
                                     nitrogen);
    double heatLoss = slfgm.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(flueGasByMassCalculateHeatingValue)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double carbon = Get("carbon");
    const double hydrogen = Get("hydrogen");
    const double sulphur = Get("sulphur");
    const double inertAsh = Get("inertAsh");
    const double o2 = Get("o2");
    const double moisture = Get("moisture");
    const double nitrogen = Get("nitrogen");

    auto const hv = SolidLiquidFlueGasMaterial::calculateHeatingValueFuel(carbon, hydrogen,
                                                                          sulphur, inertAsh, o2,
                                                                          moisture, nitrogen);

    Local<Number> retval = Nan::New(hv);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(flueGasCalculateO2)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double CH4 = Get("CH4");
    const double C2H6 = Get("C2H6");
    const double N2 = Get("N2");
    const double H2 = Get("H2");
    const double C3H8 = Get("C3H8");
    const double C4H10_CnH2n = Get("C4H10_CnH2n");
    const double H2O = Get("H2O");
    const double CO = Get("CO");
    const double CO2 = Get("CO2");
    const double SO2 = Get("SO2");
    const double O2 = Get("O2");
    double excessAir = Get("excessAir");

    GasCompositions comp("", CH4, C2H6, N2, H2, C3H8,
                         C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    excessAir = Conversion(excessAir).percentToFraction();
    double result = comp.calculateO2(excessAir);
    result = Conversion(result).fractionToPercent();

    Local<Number> rv = Nan::New(result);
    info.GetReturnValue().Set(rv);
}

NAN_METHOD(flueGasCalculateExcessAir)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double CH4 = Get("CH4");
    const double C2H6 = Get("C2H6");
    const double N2 = Get("N2");
    const double H2 = Get("H2");
    const double C3H8 = Get("C3H8");
    const double C4H10_CnH2n = Get("C4H10_CnH2n");
    const double H2O = Get("H2O");
    const double CO = Get("CO");
    const double CO2 = Get("CO2");
    const double SO2 = Get("SO2");
    const double O2 = Get("O2");
    double o2InFlueGas = Get("o2InFlueGas");

    GasCompositions comp("", CH4, C2H6, N2, H2, C3H8,
                         C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    o2InFlueGas = Conversion(o2InFlueGas).percentToFraction();
    double result = comp.calculateExcessAir(o2InFlueGas);
    result = Conversion(result).fractionToPercent();

    Local<Number> rv = Nan::New(result);
    info.GetReturnValue().Set(rv);
}

NAN_METHOD(flueGasByMassCalculateO2)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    double excessAir = Get("excessAir");
    double carbon = Get("carbon");
    double hydrogen = Get("hydrogen");
    double sulphur = Get("sulphur");
    double inertAsh = Get("inertAsh");
    double o2 = Get("o2");
    double moisture = Get("moisture");
    double nitrogen = Get("nitrogen");
    const double moistureInAirCombustion = Get("moistureInAirCombustion");

    excessAir = Conversion(excessAir).percentToFraction();
    carbon = Conversion(carbon).percentToFraction();
    hydrogen = Conversion(hydrogen).percentToFraction();
    sulphur = Conversion(sulphur).percentToFraction();
    inertAsh = Conversion(inertAsh).percentToFraction();
    o2 = Conversion(o2).percentToFraction();
    moisture = Conversion(moisture).percentToFraction();
    nitrogen = Conversion(nitrogen).percentToFraction();

    double v = SolidLiquidFlueGasMaterial::calculateFlueGasO2(excessAir, carbon,
                                                              hydrogen, sulphur,
                                                              inertAsh, o2, moisture,
                                                              nitrogen, moistureInAirCombustion);
    v = Conversion(v).fractionToPercent();

    Local<Number> rv = Nan::New(v);
    info.GetReturnValue().Set(rv);
}

NAN_METHOD(flueGasByMassCalculateExcessAir)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    double o2InFlueGas = Get("o2InFlueGas");
    double carbon = Get("carbon");
    double hydrogen = Get("hydrogen");
    double sulphur = Get("sulphur");
    double inertAsh = Get("inertAsh");
    double o2 = Get("o2");
    double moisture = Get("moisture");
    double nitrogen = Get("nitrogen");
    const double moistureInAirCombustion = Get("moistureInAirCombustion");

    o2InFlueGas = Conversion(o2InFlueGas).percentToFraction();
    carbon = Conversion(carbon).percentToFraction();
    hydrogen = Conversion(hydrogen).percentToFraction();
    sulphur = Conversion(sulphur).percentToFraction();
    inertAsh = Conversion(inertAsh).percentToFraction();
    o2 = Conversion(o2).percentToFraction();
    moisture = Conversion(moisture).percentToFraction();
    nitrogen = Conversion(nitrogen).percentToFraction();

    double v = SolidLiquidFlueGasMaterial::calculateExcessAirFromFlueGasO2(o2InFlueGas, carbon,
                                                                         hydrogen, sulphur, inertAsh,
                                                                         o2, moisture, nitrogen,
                                                                         moistureInAirCombustion);
    v = Conversion(v).fractionToPercent();

    Local<Number> rv = Nan::New(v);
    info.GetReturnValue().Set(rv);
}

NAN_METHOD(o2Enrichment)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double o2CombAir = Get("o2CombAir");
    const double o2CombAirEnriched = Get("o2CombAirEnriched");
    const double flueGasTemp = Get("flueGasTemp");
    const double flueGasTempEnriched = Get("flueGasTempEnriched");
    const double o2FlueGas = Get("o2FlueGas");
    const double o2FlueGasEnriched = Get("o2FlueGasEnriched");
    const double combAirTemp = Get("combAirTemp");
    const double combAirTempEnriched = Get("combAirTempEnriched");
    const double fuelConsumption = Get("fuelConsumption");

    O2Enrichment oe(o2CombAir, o2CombAirEnriched, flueGasTemp, flueGasTempEnriched, o2FlueGas,
                    o2FlueGasEnriched, combAirTemp, combAirTempEnriched, fuelConsumption);
    double availableHeatInput = oe.getAvailableHeat();
    double availableHeatEnriched = oe.getAvailableHeatEnriched();
    double fuelSavingsEnriched = oe.getFuelSavingsEnriched();
    double fuelConsumptionEnriched = oe.getFuelConsumptionEnriched();

    SetR("availableHeatInput", availableHeatInput);
    SetR("availableHeatEnriched", availableHeatEnriched);
    SetR("fuelSavingsEnriched", fuelSavingsEnriched);
    SetR("fuelConsumptionEnriched", fuelConsumptionEnriched);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(energyInputExhaustGasLosses)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double excessAir = Get("excessAir");
    const double combustionAirTemp = Get("combustionAirTemp");
    const double exhaustGasTemp = Get("exhaustGasTemp");
    const double totalHeatInput = Get("totalHeatInput");

    EnergyInputExhaustGasLosses e(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);

    SetR("heatDelivered", e.getHeatDelivered());
    SetR("exhaustGasLosses", e.getExhaustGasLosses());
    SetR("availableHeat", e.getAvailableHeat());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(humidityRatio)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double atmosphericPressure = Get("atmosphericPressure");
    const double dryBulbTemp = Get("dryBulbTemp");
    const double relativeHumidity = Get("relativeHumidity");
    const double wetBulbTemp = Get("wetBulbTemp");

    HumidityRatio hr(atmosphericPressure, dryBulbTemp, relativeHumidity, wetBulbTemp);
    double humidityRatioUsingRH = hr.getHumidityRatioUsingRH();
    double humidityRatioUsingWBT = hr.getHumidityRatioUsingWBT();

    SetR("humidityRatioUsingRH", humidityRatioUsingRH);
    SetR("humidityRatioUsingWBT", humidityRatioUsingWBT);
    info.GetReturnValue().Set(r);
}

#endif //AMO_TOOLS_SUITE_LOSSES_H
