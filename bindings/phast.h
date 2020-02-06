#ifndef AMO_TOOLS_SUITE_LOSSES_H
#define AMO_TOOLS_SUITE_LOSSES_H

#include "NanDataConverters.h"

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

FlowCalculationsEnergyUse::Gas gas()
{
    return (FlowCalculationsEnergyUse::Gas)(int)getDouble("gasType");
}

FlowCalculationsEnergyUse::Section section()
{
    return (FlowCalculationsEnergyUse::Section)(int)getDouble("sectionType");
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

    const double inletTemperature = getDouble("inletTemperature");
    const double outletTemperature = getDouble("outletTemperature");
    const double flowRate = getDouble("flowRate");
    const double correctionFactor = getDouble("correctionFactor");
    const double specificHeat = getDouble("specificHeat");

    Atmosphere a(inletTemperature, outletTemperature, flowRate, correctionFactor, specificHeat);
    double heatLoss = a.getTotalHeat();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(auxiliaryPowerLoss)
{
    /**
 * Constructor
:q

 * @param motorPhase double, current motor phase - this option is greyed out in PHAST 3.0
 * @param supplyVoltage double, supply voltage in volts
 * @param avgCurrent double, average current in Amperes
 * @param powerFactor double, average power factor value - unitless
 * @param operatingTime double, percent operating time
 */
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double motorPhase = getDouble("motorPhase");
    const double supplyVoltage = getDouble("supplyVoltage");
    const double avgCurrent = getDouble("avgCurrent");
    const double powerFactor = getDouble("powerFactor");
    const double operatingTime = getDouble("operatingTime");

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

    const double naturalGasHeatInput = getDouble("naturalGasHeatInput");
    const double coalCarbonInjection = getDouble("coalCarbonInjection");
    const double coalHeatingValue = getDouble("coalHeatingValue");
    const double electrodeUse = getDouble("electrodeUse");
    const double electrodeHeatingValue = getDouble("electrodeHeatingValue");
    const double otherFuels = getDouble("otherFuels");
    const double electricityInput = getDouble("electricityInput");

    EnergyInputEAF eaf(naturalGasHeatInput, coalCarbonInjection, coalHeatingValue, electrodeUse,
                       electrodeHeatingValue, otherFuels, electricityInput);
    const double heatDelivered = eaf.getHeatDelivered();
    const double totalChemicalEnergyInput = eaf.getTotalChemicalEnergyInput();

    setR("heatDelivered", heatDelivered);
    setR("totalChemicalEnergyInput", totalChemicalEnergyInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(exhaustGasEAF)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double offGasTemp = getDouble("offGasTemp");
    const double CO = getDouble("CO");
    const double H2 = getDouble("H2");
    const double combustibleGases = getDouble("combustibleGases");
    const double vfr = getDouble("vfr");
    const double dustLoading = getDouble("dustLoading");

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

    const double specificHeat = getDouble("specificHeat");
    const double feedRate = getDouble("feedRate");
    const double initialTemperature = getDouble("initialTemperature");
    const double finalTemperature = getDouble("finalTemperature");
    const double correctionFactor = getDouble("correctionFactor");

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

    const double flowRate = getDouble("flowRate");
    const double initialTemperature = getDouble("initialTemperature");
    const double finalTemperature = getDouble("finalTemperature");
    const double specificHeat = getDouble("specificHeat");
    const double correctionFactor = getDouble("correctionFactor");
    const double gasDensity = getDouble("gasDensity");

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

    const double specificHeatGas = getDouble("specificHeatGas");
    const double feedRate = getDouble("feedRate");
    const double percentVapor = getDouble("percentVapor");
    const double initialTemperature = getDouble("initialTemperature");
    const double dischargeTemperature = getDouble("dischargeTemperature");
    const double specificHeatVapor = getDouble("specificHeatVapor");
    const double percentReacted = getDouble("percentReacted");
    const double reactionHeat = getDouble("reactionHeat");
    const double additionalHeat = getDouble("additionalHeat");
    const double thermicReactionTypeInput = getDouble("thermicReactionType");

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

    const double draftPressure = getDouble("draftPressure");
    const double openingArea = getDouble("openingArea");
    const double leakageGasTemperature = getDouble("leakageGasTemperature");
    const double ambientTemperature = getDouble("ambientTemperature");
    const double coefficient = getDouble("coefficient");
    const double specificGravity = getDouble("specificGravity");
    const double correctionFactor = getDouble("correctionFactor");

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

    const double flowRate = getDouble("flowRate");
    const double density = getDouble("density");
    const double initialTemperature = getDouble("initialTemperature");
    const double outletTemperature = getDouble("outletTemperature");
    const double specificHeat = getDouble("specificHeat");
    const double correctionFactor = getDouble("correctionFactor");

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

    const double specificHeatLiquid = getDouble("specificHeatLiquid");
    const double vaporizingTemperature = getDouble("vaporizingTemperature");
    const double latentHeat = getDouble("latentHeat");
    const double specificHeatVapor = getDouble("specificHeatVapor");
    const double chargeFeedRate = getDouble("chargeFeedRate");
    const double initialTemperature = getDouble("initialTemperature");
    const double dischargeTemperature = getDouble("dischargeTemperature");
    const double percentVaporized = getDouble("percentVaporized");
    const double percentReacted = getDouble("percentReacted");
    const double reactionHeat = getDouble("reactionHeat");
    const double additionalHeat = getDouble("additionalHeat");
    const double thermicReactionTypeInput = getDouble("thermicReactionType");

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

    const double emissivity = getDouble("emissivity");
    const double diameter = getDouble("diameter");
    const double thickness = getDouble("thickness");
    const double ratio = getDouble("ratio");
    const double ambientTemperature = getDouble("ambientTemperature");
    const double insideTemperature = getDouble("insideTemperature");
    const double percentTimeOpen = getDouble("percentTimeOpen");
    const double viewFactor = getDouble("viewFactor");

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

    const double emissivity = getDouble("emissivity");
    const double length = getDouble("length");
    const double width = getDouble("width");
    const double thickness = getDouble("thickness");
    const double ratio = getDouble("ratio");
    const double ambientTemperature = getDouble("ambientTemperature");
    const double insideTemperature = getDouble("insideTemperature");
    const double percentTimeOpen = getDouble("percentTimeOpen");
    const double viewFactor = getDouble("viewFactor");

    OpeningLosses ol(emissivity, length, width, thickness, ratio,
                     ambientTemperature, insideTemperature, percentTimeOpen, viewFactor);
    double heatLoss = ol.getHeatLoss();

    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

OpeningLosses::OpeningShape getOpeningShape()
{
    unsigned val = static_cast<unsigned>(getDouble("openingShape"));
    return static_cast<OpeningLosses::OpeningShape>(val);
}

NAN_METHOD(viewFactorCalculation)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double thickness = getDouble("thickness");

    OpeningLosses opening;
    OpeningLosses::OpeningShape shape = getOpeningShape();
    if (shape == OpeningLosses::OpeningShape::CIRCULAR)
    {
        const double diameter = getDouble("diameter");
        Local<Number> rv = Nan::New(opening.calculateViewFactor(thickness, diameter));
        info.GetReturnValue().Set(rv);
    }
    else
    {
        const double length = getDouble("length");
        const double width = getDouble("width");
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

    const double weight = getDouble("weight");
    const double inletTemperature = getDouble("inletTemperature");
    const double outletTemperature = getDouble("outletTemperature");
    const double specificHeat = getDouble("specificHeat");
    const double correctionFactor = getDouble("correctionFactor");

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

    const double specificHeatSolid = getDouble("specificHeatSolid");
    const double latentHeat = getDouble("latentHeat");
    const double specificHeatLiquid = getDouble("specificHeatLiquid");
    const double meltingPoint = getDouble("meltingPoint");
    const double chargeFeedRate = getDouble("chargeFeedRate");
    const double waterContentCharged = getDouble("waterContentCharged");
    const double waterContentDischarged = getDouble("waterContentDischarged");
    const double initialTemperature = getDouble("initialTemperature");
    const double dischargeTemperature = getDouble("dischargeTemperature");
    const double waterVaporDischargeTemperature = getDouble("waterVaporDischargeTemperature");
    const double chargeMelted = getDouble("chargeMelted");
    const double chargeReacted = getDouble("chargeReacted");
    const double reactionHeat = getDouble("reactionHeat");
    const double additionalHeat = getDouble("additionalHeat");
    const double thermicReactionTypeInput = getDouble("thermicReactionType");

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

    const double surfaceArea = getDouble("surfaceArea");
    const double ambientTemperature = getDouble("ambientTemperature");
    const double surfaceTemperature = getDouble("surfaceTemperature");
    const double windVelocity = getDouble("windVelocity");
    const double surfaceEmissivity = getDouble("surfaceEmissivity");
    const double conditionFactor = getDouble("conditionFactor");
    const double correctionFactor = getDouble("correctionFactor");

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

    const double flowRate = getDouble("flowRate");
    const double initialTemperature = getDouble("initialTemperature");
    const double outletTemperature = getDouble("outletTemperature");
    const double correctionFactor = getDouble("correctionFactor");

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

    const double currentFlueGasOxygen = getDouble("currentFlueGasOxygen");
    const double newFlueGasOxygen = getDouble("newFlueGasOxygen");
    const double currentFlueGasTemp = getDouble("currentFlueGasTemp");
    const double newFlueGasTemp = getDouble("newFlueGasTemp");
    const double currentCombustionAirTemp = getDouble("currentCombustionAirTemp");
    const double newCombustionAirTemp = getDouble("newCombustionAirTemp");
    const double currentEnergyInput = getDouble("currentEnergyInput");

    EfficiencyImprovement ei(currentFlueGasOxygen, newFlueGasOxygen, currentFlueGasTemp, newFlueGasTemp,
                             currentCombustionAirTemp, newCombustionAirTemp, currentEnergyInput);
    double currentExcessAir = ei.getCurrentExcessAir();
    double newExcessAir = ei.getNewExcessAir();
    double currentAvailableHeat = ei.getCurrentAvailableHeat();
    double newAvailableHeat = ei.getNewAvailableHeat();
    double newFuelSavings = ei.getNewFuelSavings();
    double newEnergyInput = ei.getNewEnergyInput();

    setR("currentExcessAir", currentExcessAir);
    setR("newExcessAir", newExcessAir);
    setR("currentAvailableHeat", currentAvailableHeat);
    setR("newAvailableHeat", newAvailableHeat);
    setR("newFuelSavings", newFuelSavings);
    setR("newEnergyInput", newEnergyInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(energyEquivalencyElectric)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double fuelFiredEfficiency = getDouble("fuelFiredEfficiency");
    const double electricallyHeatedEfficiency = getDouble("electricallyHeatedEfficiency");
    const double fuelFiredHeatInput = getDouble("fuelFiredHeatInput");

    ElectricalEnergyEquivalency eee(fuelFiredEfficiency, electricallyHeatedEfficiency, fuelFiredHeatInput);
    double electricalHeatInput = eee.getElectricalHeatInput();

    setR("electricalHeatInput", electricalHeatInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(energyEquivalencyFuel)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double electricallyHeatedEfficiency = getDouble("electricallyHeatedEfficiency");
    const double fuelFiredEfficiency = getDouble("fuelFiredEfficiency");
    const double electricalHeatInput = getDouble("electricalHeatInput");

    FuelFiredEnergyEquivalency ffee(electricallyHeatedEfficiency, fuelFiredEfficiency, electricalHeatInput);
    double fuelFiredHeatInput = ffee.getFuelFiredHeatInput();

    setR("fuelFiredHeatInput", fuelFiredHeatInput);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(flowCalculations)
{

    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double specificGravity = getDouble("specificGravity");
    const double orificeDiameter = getDouble("orificeDiameter");
    const double insidePipeDiameter = getDouble("insidePipeDiameter");
    const double dischargeCoefficient = getDouble("dischargeCoefficient");
    const double gasHeatingValue = getDouble("gasHeatingValue");
    const double gasTemperature = getDouble("gasTemperature");
    const double gasPressure = getDouble("gasPressure");
    const double orificePressureDrop = getDouble("orificePressureDrop");
    const double operatingTime = getDouble("operatingTime");

    FlowCalculationsEnergyUse::Gas gas1 = gas();
    FlowCalculationsEnergyUse::Section section1 = section();
    FlowCalculationsEnergyUse fceu(gas1, specificGravity, orificeDiameter, insidePipeDiameter, section1, dischargeCoefficient,
                                   gasHeatingValue, gasTemperature, gasPressure, orificePressureDrop, operatingTime);
    double flow = fceu.getFlow();
    double heatInput = fceu.getHeatInput();
    double totalFlow = fceu.getTotalFlow();

    setR("flow", flow);
    setR("heatInput", heatInput);
    setR("totalFlow", totalFlow);
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

    const double CH4 = getDouble("CH4");
    const double C2H6 = getDouble("C2H6");
    const double N2 = getDouble("N2");
    const double H2 = getDouble("H2");
    const double C3H8 = getDouble("C3H8");
    const double C4H10_CnH2n = getDouble("C4H10_CnH2n");
    const double H2O = getDouble("H2O");
    const double CO = getDouble("CO");
    const double CO2 = getDouble("CO2");
    const double SO2 = getDouble("SO2");
    const double O2 = getDouble("O2");

    const double flueGasTemperature = getDouble("flueGasTemperature");
    const double excessAirPercentage = getDouble("excessAirPercentage");
    const double combustionAirTemperature = getDouble("combustionAirTemperature");
    const double fuelTemperature = getDouble("fuelTemperature");

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

    const double CH4 = getDouble("CH4");
    const double C2H6 = getDouble("C2H6");
    const double N2 = getDouble("N2");
    const double H2 = getDouble("H2");
    const double C3H8 = getDouble("C3H8");
    const double C4H10_CnH2n = getDouble("C4H10_CnH2n");
    const double H2O = getDouble("H2O");
    const double CO = getDouble("CO");
    const double CO2 = getDouble("CO2");
    const double SO2 = getDouble("SO2");
    const double O2 = getDouble("O2");

    GasCompositions comps("", CH4, C2H6, N2, H2, C3H8,
                          C4H10_CnH2n, H2O, CO, CO2, SO2, O2);
    double heatingValue = comps.getHeatingValue();
    double heatingValueVolume = comps.getHeatingValueVolume();
    double specificGravity = comps.getSpecificGravity();

    setR("heatingValue", heatingValue);
    setR("heatingValueVolume", heatingValueVolume);
    setR("specificGravity", specificGravity);
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

    const double flueGasTemperature = getDouble("flueGasTemperature");
    const double excessAirPercentage = getDouble("excessAirPercentage");
    const double combustionAirTemperature = getDouble("combustionAirTemperature");
    const double fuelTemperature = getDouble("fuelTemperature");
    const double moistureInAirComposition = getDouble("moistureInAirComposition");
    const double ashDischargeTemperature = getDouble("ashDischargeTemperature");
    const double unburnedCarbonInAsh = getDouble("unburnedCarbonInAsh");
    const double carbon = getDouble("carbon");
    const double hydrogen = getDouble("hydrogen");
    const double sulphur = getDouble("sulphur");
    const double inertAsh = getDouble("inertAsh");
    const double o2 = getDouble("o2");
    const double moisture = getDouble("moisture");
    const double nitrogen = getDouble("nitrogen");

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

    const double carbon = getDouble("carbon");
    const double hydrogen = getDouble("hydrogen");
    const double sulphur = getDouble("sulphur");
    const double inertAsh = getDouble("inertAsh");
    const double o2 = getDouble("o2");
    const double moisture = getDouble("moisture");
    const double nitrogen = getDouble("nitrogen");

    auto const hv = SolidLiquidFlueGasMaterial::calculateHeatingValueFuel(carbon, hydrogen,
                                                                          sulphur, inertAsh, o2,
                                                                          moisture, nitrogen);

    Local<Number> retval = Nan::New(hv);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(flueGasCalculateO2)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();

    const double CH4 = getDouble("CH4");
    const double C2H6 = getDouble("C2H6");
    const double N2 = getDouble("N2");
    const double H2 = getDouble("H2");
    const double C3H8 = getDouble("C3H8");
    const double C4H10_CnH2n = getDouble("C4H10_CnH2n");
    const double H2O = getDouble("H2O");
    const double CO = getDouble("CO");
    const double CO2 = getDouble("CO2");
    const double SO2 = getDouble("SO2");
    const double O2 = getDouble("O2");
    double excessAir = getDouble("excessAir");

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

    const double CH4 = getDouble("CH4");
    const double C2H6 = getDouble("C2H6");
    const double N2 = getDouble("N2");
    const double H2 = getDouble("H2");
    const double C3H8 = getDouble("C3H8");
    const double C4H10_CnH2n = getDouble("C4H10_CnH2n");
    const double H2O = getDouble("H2O");
    const double CO = getDouble("CO");
    const double CO2 = getDouble("CO2");
    const double SO2 = getDouble("SO2");
    const double O2 = getDouble("O2");
    double o2InFlueGas = getDouble("o2InFlueGas");

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

    double excessAir = getDouble("excessAir");
    double carbon = getDouble("carbon");
    double hydrogen = getDouble("hydrogen");
    double sulphur = getDouble("sulphur");
    double inertAsh = getDouble("inertAsh");
    double o2 = getDouble("o2");
    double moisture = getDouble("moisture");
    double nitrogen = getDouble("nitrogen");
    const double moistureInAirCombustion = getDouble("moistureInAirCombustion");

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

    double o2InFlueGas = getDouble("o2InFlueGas");
    double carbon = getDouble("carbon");
    double hydrogen = getDouble("hydrogen");
    double sulphur = getDouble("sulphur");
    double inertAsh = getDouble("inertAsh");
    double o2 = getDouble("o2");
    double moisture = getDouble("moisture");
    double nitrogen = getDouble("nitrogen");
    const double moistureInAirCombustion = getDouble("moistureInAirCombustion");

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

    const double o2CombAir = getDouble("o2CombAir");
    const double o2CombAirEnriched = getDouble("o2CombAirEnriched");
    const double flueGasTemp = getDouble("flueGasTemp");
    const double flueGasTempEnriched = getDouble("flueGasTempEnriched");
    const double o2FlueGas = getDouble("o2FlueGas");
    const double o2FlueGasEnriched = getDouble("o2FlueGasEnriched");
    const double combAirTemp = getDouble("combAirTemp");
    const double combAirTempEnriched = getDouble("combAirTempEnriched");
    const double fuelConsumption = getDouble("fuelConsumption");

    O2Enrichment oe(o2CombAir, o2CombAirEnriched, flueGasTemp, flueGasTempEnriched, o2FlueGas,
                    o2FlueGasEnriched, combAirTemp, combAirTempEnriched, fuelConsumption);
    double availableHeatInput = oe.getAvailableHeat();
    double availableHeatEnriched = oe.getAvailableHeatEnriched();
    double fuelSavingsEnriched = oe.getFuelSavingsEnriched();
    double fuelConsumptionEnriched = oe.getFuelConsumptionEnriched();

    setR("availableHeatInput", availableHeatInput);
    setR("availableHeatEnriched", availableHeatEnriched);
    setR("fuelSavingsEnriched", fuelSavingsEnriched);
    setR("fuelConsumptionEnriched", fuelConsumptionEnriched);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(energyInputExhaustGasLosses)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double excessAir = getDouble("excessAir");
    const double combustionAirTemp = getDouble("combustionAirTemp");
    const double exhaustGasTemp = getDouble("exhaustGasTemp");
    const double totalHeatInput = getDouble("totalHeatInput");

    EnergyInputExhaustGasLosses e(excessAir, combustionAirTemp, exhaustGasTemp, totalHeatInput);

    setR("heatDelivered", e.getHeatDelivered());
    setR("exhaustGasLosses", e.getExhaustGasLosses());
    setR("availableHeat", e.getAvailableHeat());
    info.GetReturnValue().Set(r);
}

NAN_METHOD(humidityRatio)
{
    inp = Nan::To<Object>(info[0]).ToLocalChecked();
    r = Nan::New<Object>();

    const double atmosphericPressure = getDouble("atmosphericPressure");
    const double dryBulbTemp = getDouble("dryBulbTemp");
    const double relativeHumidity = getDouble("relativeHumidity");
    const double wetBulbTemp = getDouble("wetBulbTemp");

    HumidityRatio hr(atmosphericPressure, dryBulbTemp, relativeHumidity, wetBulbTemp);
    double humidityRatioUsingRH = hr.getHumidityRatioUsingRH();
    double humidityRatioUsingWBT = hr.getHumidityRatioUsingWBT();

    setR("humidityRatioUsingRH", humidityRatioUsingRH);
    setR("humidityRatioUsingWBT", humidityRatioUsingWBT);
    info.GetReturnValue().Set(r);
}

#endif //AMO_TOOLS_SUITE_LOSSES_H
