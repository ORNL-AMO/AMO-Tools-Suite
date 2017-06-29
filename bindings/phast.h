//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_LOSSES_H
#define AMO_TOOLS_SUITE_LOSSES_H

#include <nan.h>
#include <node.h>
#include "calculator/losses/Atmosphere.h"
#include "calculator/losses/AuxiliaryPower.h"
#include "calculator/losses/EnergyInputEAF.h"
#include "calculator/losses/ExhaustGasEAF.h"
#include "calculator/furnace/EfficiencyImprovement.h"
#include "calculator/furnace/EnergyEquivalency.h"
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
#include "calculator/furnace/O2Enrichment.h"
#include "calculator/losses/SlagOtherMaterialLosses.h"
#include "calculator/losses/SolidLoadChargeMaterial.h"
#include "calculator/losses/WallLosses.h"
#include "calculator/losses/WaterCoolingLosses.h"


using namespace Nan;
using namespace v8;

Local<Object> inp;
Local<Object> r;

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

/**********************
 * Test methods
 */

NAN_METHOD(initTest) {
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
}

NAN_METHOD(atmosphere) {

    /**
     * Constructor for the atmospheric heat loss with all inputs specified
     *
     * @param inletTemperature double, inlet temperature of gasses in °F
     * @param outletTemperature double, outlet temperature of gasses in °F
     * @param flowRate double, flow rate of gasses in scfh
     * @param correctionFactor double, correction factor - unitless
     * @param specificHeat double, specific heat of gasses at average air temperature in Btu/(scf - °F)
     * @return nothing
     *
     * */

    inp = info[0]->ToObject();
    Atmosphere a(Get("inletTemperature"), Get("outletTemperature"), Get("flowRate"), Get("correctionFactor"), Get("specificHeat"));
    double heatLoss = a.getTotalHeat();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(auxiliaryPowerLoss) {
/**
 * Constructor
 * @param motorPhase double, current motor phase - this option is greyed out in PHAST 3.0
 * @param supplyVoltage double, supply voltage in volts
 * @param avgCurrent double, average current in Amperes
 * @param powerFactor double, average power factor value - unitless
 * @param operatingTime double, percent operating time
 * @return nothing
 */
    inp = info[0]->ToObject();
    auto const ap = AuxiliaryPower(Get("motorPhase"), Get("supplyVoltage"), Get("avgCurrent"), Get("powerFactor"), Get("operatingTime"));
    const double powerUsed = ap.getPowerUsed();
    Local<Number> retval = Nan::New(powerUsed);
    info.GetReturnValue().Set(retval);
}


NAN_METHOD(energyInput) {

/**
     * Constructor for the Electric Arc Furnace (EAF) heat loss with all inputs specified
     *
     * @param naturalGasHeatInput double, value of total heat input to the heating system (furnace/oven) from all
     *                              sources of heat supplied (natural gas, carbon, fuel oil, etc.)
     *                              measured in mm btu/cycle
     * @param naturalGasFlow double, natural gas flow measured in cu.ft/cycle
     * @param measuredOxygenFlow double, oxygen flow to the furnace measured in scfh
     * @param coalCarbonInjection double, mass of coal or carbon injection for the cycle measured in lbs/cycle
     * @param coalHeatingValue double, heating value for the coal or carbon injected measured in btu/lb
     * @param electrodeUse double, electrode use measured in lbs/cycle
     * @param electrodeHeatingValue double, electrode heating value measured in btu/lb
     * @param otherFuels double, heat supplied from other sources, if any, measured in mm btu/cycle
     * @param electricityInput double, total electric power supplied for the cycle measured in kwh/cycle
     * @return double, heat delivered in btu/cycle
     *
     * */
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    EnergyInputEAF eaf(Get("naturalGasHeatInput"), Get("naturalGasFlow"), Get("measuredOxygenFlow"), Get("coalCarbonInjection"), Get("coalHeatingValue"), Get("electrodeUse"), Get("electrodeHeatingValue"), Get("otherFuels"), Get("electricityInput"));
    double heatDelivered = eaf.getHeatDelivered();
    double kwhCycle = eaf.getKwhCycle();
    double totalKwhCycle = eaf.getTotalKwhPerCycle();
    SetR("heatDelivered", heatDelivered);
    SetR("kwhCycle", kwhCycle);
    SetR("totalKwhCycle", totalKwhCycle);
    info.GetReturnValue().Set(r);
}


NAN_METHOD(fixtureLosses) {

/**
    * Constructor for Fixture Losses
    * @param specificHeat double, pecific heat in btu/(lb*°F)
    * @param feedRate double, feed rate for gas mixture in lb/hr
    * @param initialTemperature double, initial temperature in °F
    * @param finalTemperature double, final temperature in °F
    * @param correctionFactor double, correction factor - unitless
    *
    * @return double, heat loss in btu/cycle
    */
    inp = info[0]->ToObject();
    FixtureLosses fl(Get("specificHeat"), Get("feedRate"), Get("initialTemperature"), Get("finalTemperature"), Get("correctionFactor"));
    double heatLoss = fl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(flueGasLossesByVolume) {
    /**
     * Constructor for the flue gas losses by volume with all inputs specified
     *
     * @param flueGasTemperature double, temperature of flue gas in °F
     * @param excessAirPercentage double, excess air as %
     * @param combustionAirTemperature double, temperature of combustion air in °F
     * @param gasComposition double, percentages for CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2 and O2
     * @return nothing
     *
     * */

    inp = info[0]->ToObject();
    // TODO find a way to get substance name legitimately
    GasCompositions comps("substance", Get("CH4"), Get("C2H6"), Get("N2"), Get("H2"), Get("C3H8"),
                          Get("C4H10_CnH2n"), Get("H2O"), Get("CO"), Get("CO2"), Get("SO2"), Get("O2"));

    GasFlueGasMaterial fg(Get("flueGasTemperature"), Get("excessAirPercentage"), Get("combustionAirTemperature"), comps);

    double heatLoss = fg.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(flueGasLossesByMass) {
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
     * @return nothing
     *
     * */

    inp = info[0]->ToObject();
    SolidLiquidFlueGasMaterial slfgm(Get("flueGasTemperature"), Get("excessAirPercentage"), Get("combustionAirTemperature"),
                                     Get("fuelTemperature"), Get("moistureInAirComposition"), Get("ashDischargeTemperature"),
                                     Get("unburnedCarbonInAsh"), Get("carbon"), Get("hydrogen"), Get("sulphur"),
                                     Get("inertAsh"), Get("o2"), Get("moisture"), Get("nitrogen"));

    double heatLoss = slfgm.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(gasCoolingLosses) {
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
    inp = info[0]->ToObject();
    GasCoolingLosses gcl(Get("flowRate"), Get("initialTemperature"), Get("finalTemperature"), Get("specificHeat"), Get("correctionFactor"));
    double heatLoss = gcl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(gasLoadChargeMaterial) {
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
    inp = info[0]->ToObject();
    LoadChargeMaterial::ThermicReactionType thermicReactionType;
    if (Get("thermicReactionType") == 0) {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
    } else {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
    }
    GasLoadChargeMaterial glcm(thermicReactionType, Get("specificHeatGas"), Get("feedRate"), Get("percentVapor"), Get("initialTemperature"),
                               Get("dischargeTemperature"), Get("specificHeatVapor"), Get("percentReacted"), Get("reactionHeat"), Get("additionalHeat"));
    double heatLoss = glcm.getTotalHeat();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(leakageLosses) {
    /**
     * Constructor
     * @param draftPressure double, furnace draft pressure in inch W.C.
     * @param openingArea double, opening area in ft^2
     * @param leakageGasTemperature double, temperature of gases leaking from furnace in °F
     * @param ambientTemperature double, ambient temperature in °F
     * @param coefficient double, coefficient - unitless
     * @param specificGravity double, specific gravity - unitless
     * @param correctionFactor double, correction factor - unitless
     * @return nothing
     */
    inp = info[0]->ToObject();
    LeakageLosses ll(Get("draftPressure"), Get("openingArea"), Get("leakageGasTemperature"), Get("ambientTemperature"),
                     Get("coefficient"), Get("specificGravity"), Get("correctionFactor"));
    double heatLoss = ll.getExfiltratedGasesHeatContent();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(liquidCoolingLosses) {
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
    inp = info[0]->ToObject();
    LiquidCoolingLosses lcl(Get("flowRate"), Get("density"), Get("initialTemperature"), Get("outletTemperature"),
                            Get("specificHeat"), Get("correctionFactor"));
    double heatLoss = lcl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(liquidLoadChargeMaterial) {
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

    inp = info[0]->ToObject();
    LoadChargeMaterial::ThermicReactionType thermicReactionType;
    if (Get("thermicReactionType") == 0) {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
    } else {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
    }
    LiquidLoadChargeMaterial llcm(thermicReactionType, Get("specificHeatLiquid"), Get("vaporizingTemperature"), Get("latentHeat"),
                                  Get("specificHeatVapor"), Get("chargeFeedRate"), Get("initialTemperature"), Get("dischargeTemperature"),
                                  Get("percentVaporized"), Get("percentReacted"), Get("reactionHeat"), Get("additionalHeat"));
    double heatLoss = llcm.getTotalHeat();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(openingLossesCircular) {

        /**
         * Constructor for a circular opening
         * @param emissivity double, emissivity - unitless
         * @param diameterLength double, length of opening in inches
         * @param thickness double, furnace wall thickness in inches
         * @param ratio double, ratio - unitless
         * @param ambientTemperature double, ambient temperature in °F
         * @param insideTemperature double, inside temperature in °F
         * @param percentTimeOpen double, amount of time open as %
         * @param viewFactor double, view factor - unitless
         * @return nothing
         */
    inp = info[0]->ToObject();
    OpeningLosses ol(Get("emissivity"), Get("diameterLength"), Get("thickness"), Get("ratio"), Get("ambientTemperature"),
                     Get("insideTemperature"), Get("percentTimeOpen"), Get("viewFactor"));
    double heatLoss = ol.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);

}
NAN_METHOD(openingLossesQuad) {

        /**
         * Constructor for a rectangular opening
         * @param emissivity double, emissivity - unitless
         * @param length double, length of openings in inches
         * @param widthHeight double, height of openings in inches
         * @param thickness double, furnace wall thickness in inches
         * @param ratio double, ratio - unitless
         * @param ambientTemperature double, ambient temperature in °F
         * @param insideTemperature double, inside temperature in °F
         * @param percentTimeOpen double, amount of time open as a %
         * @param viewFactor double, view factor - unitless
         * @return double, heatLoss in btu/cycle
         */
    inp = info[0]->ToObject();
    OpeningLosses ol(Get("emissivity"), Get("length"), Get("widthHeight"), Get("thickness"), Get("ratio"),
                     Get("ambientTemperature"), Get("insideTemperature"), Get("percentTimeOpen"), Get("viewFactor"));
    double heatLoss = ol.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(slagOtherMaterialLosses) {

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
    inp = info[0]->ToObject();
    SlagOtherMaterialLosses sl(Get("weight"), Get("inletTemperature"), Get("outletTemperature"), Get("specificHeat"), Get("correctionFactor"));
    double heatLoss = sl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(solidLoadChargeMaterial) {
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
 * @param chargedReacted double, charge Reacted (% of dry charge) in %
 * @param reactionHeat double, heat of reaction in Btu/lb
 * @param additionalHeat double, additional heat required in Btu/hr
 *
 * */

    inp = info[0]->ToObject();
    LoadChargeMaterial::ThermicReactionType thermicReactionType;
    if (Get("thermicReactionType") == 0) {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
    } else {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
    }
    SolidLoadChargeMaterial slcm(thermicReactionType, Get("specificHeatSolid"), Get("latentHeat"), Get("specificHeatLiquid"), Get("meltingPoint"), Get("chargeFeedRate"), Get("waterContentCharged"), Get("waterContentDischarged"), Get("initialTemperature"), Get("dischargeTemperature"), Get("waterVaporDischargeTemperature"), Get("chargeMelted"), Get("chargedReacted"), Get("reactionHeat"), Get("additionalHeat"));
    double heatLoss = slcm.getTotalHeat();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);

}

NAN_METHOD(wallLosses) {
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
    inp = info[0]->ToObject();
    WallLosses wl(Get("surfaceArea"), Get("ambientTemperature"), Get("surfaceTemperature"), Get("windVelocity"),
                  Get("surfaceEmissivity"), Get("conditionFactor"), Get("correctionFactor"));
    double heatLoss = wl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(waterCoolingLosses) {
    /**
     * Constructor
     * @param flowRate double, rate of flow in gpm
     * @param initialTemperature double, initial temperature in °F
     * @param outletTemperature double, outlet temperature in °F
     * @param correctionFactor double, correction factor - unitless
     * @return nothing
     */
    inp = info[0]->ToObject();
    WaterCoolingLosses wcl(Get("flowRate"), Get("initialTemperature"), Get("outletTemperature"), Get("correctionFactor"));
    double heatLoss = wcl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}


NAN_METHOD(energyInputEAF) {

        inp = info[0]->ToObject();
        EnergyInputEAF ei(Get("naturalGasHeatInput"), Get("naturalGasFlow"), Get("measuredOxygenFlow"), Get("coalCarbonInjection"), Get("coalHeatingValue"), get("electrodeUse"), Get("electrodeHeatingValue"), Get("otherFuels"), Get("electricityInput"));
        double heatDelivered = ei.getHeatDelivered();
        Local<Number> retval = Nan::New(heatDelivered);
        info.GetReturnValue().Set(retval);
}

NAN_METHOD(exhaustGasEAF) {

    inp = info[0]->ToObject();
    EnergyInputEAF eg(Get("cycleTime"), Get("offGasTemp"), Get("CO"), Get("H2"), Get("O2"), get("CO2"), Get("combustibleGases"), Get("vfr"), Get("dustLoading"), Get("otherLosses"));
    double heatLoss = eg.getTotalHeatExhaust();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

NAN_METHOD(efficiencyImprovement) {

    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    EnergyInputEAF ei(Get("currentFlueGasOxygen"), Get("newFlueGasOxygen"), Get("currentFlueGasTemp"), Get("newFlueGasTemp"), Get("currentCombustionAirTemp"), Get("newCombustionAirTemp"), Get("currentEnergyInput"));
    double excessAirCurrent = ei.getCurrentExcessAir();
    double excessAirNew = ei.getNewExcessAir();
    double fuelSavings = ei.getNewFuelSavings();
    double energyInputNew = ei.getTotalHeatExhaust();
    double energyInput = ei.getNewEnergyInput();
    double availableHeatCurrent = ei.getCurrentAvailableHeat();
    double availableHeatNew = ei.getNewAvailableHeat();
    SetR("excessAirCurrent", excessAirCurrent);
    SetR("excessAirNew", excessAirNew);
    SetR("fuelSavings", fuelSavings);
    SetR("energyInputNew", energyInputNew);
    SetR("availableHeatCurrent", availableHeatCurrent);
    SetR("availableHeatNew", availableHeatNew);
    info.GetReturnValue().Set(r);
}

NAN_METHOD(energyEquivalency) {

        inp = info[0]->ToObject();
        r = Nan::New<Object>();
        EnergyInputEAF ee(Get("fuelFiredEfficiency"), Get("electricallyHeatedEfficiency"), Get("fuelFiredHeatInput"));
        double electricalHeatInput = ee.getElectricalHeatInput();
        double fuelFiredHeatInput = ee.getFuelFiredHeatInput();
        SetR("electricalHeatInput", electricalHeatInput);
        SetR("fuelFiredHeatInput", fuelFiredHeatInput);
        info.GetReturnValue().Set(r);
}

NAN_METHOD(o2Enrichment) {

        inp = info[0]->ToObject();
        r = Nan::New<Object>();
        O2Enrichment oe(Get("o2CombAir"), Get("o2CombAirEnriched"), Get("flueGasTemp"), Get("flueGasTempEnriched"), Get("o2FlueGas"), Get("o2FlueGasEnriched"), Get("combAirTemp"), Get("combAirTempEnriched"), Get("fuelConsumption"));
        double availableHeatInput = oe.getAvailableHeat();
        double availableHeatEnriched = oe.getAvailableHeatEnriched();
        double fuelSavingsEnriched = oe.getFuelSavingsEnriched();
        double fuelConsumptionEnriched = oe.getFuelConsumptionEnriched();
        SetR("availableHeatInput", electricalHeatInput);
        SetR("availableHeatEnriched", fuelFiredHeatInput);
        SetR("fuelSavingsEnriched", electricalHeatInput);
        SetR("fuelConsumptionEnriched", fuelFiredHeatInput);
        info.GetReturnValue().Set(r);
}



#endif //AMO_TOOLS_SUITE_LOSSES_H

