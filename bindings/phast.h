//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_LOSSES_H
#define AMO_TOOLS_SUITE_LOSSES_H

#include <nan.h>
#include <node.h>
#include "calculator/losses/Atmosphere.h"
#include "calculator/losses/AuxiliaryPower.h"
#include "calculator/losses/ElectricArcFurnaceEAF.h"
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
     * @param inletTemperature Inlet temperature of gasses in °F
     * @param outletTemperature Outlet temperature of gasses in °F
     * @param flowRate Flow rate of gasses in scfh
     * @param correctionFactor Correction factor
     * @param specificHeat Specific heat of gasses at average air temperature in Btu/(scf - °F)
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
 * @param motorPhase current motor phase - this option is greyed out in PHAST 3.0
 * @param supplyVoltage Volts
 * @param avgCurrent average current in Amperes
 * @param powerFactor average power factor value
 * @param operatingTime percent operating time
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
     * @param naturalGasHeatInput value of total heat input to the heating system (furnace/oven) from all
     *                              sources of heat supplied (natural gas, carbon, fuel oil, etc.)
     *                              measured in mm btu/cycle
     * @param naturalGasFlow natural gas flow measured in cu.ft/cycle
     * @param measuredOxygenFlow oxygen flow to the furnace measured in scfh
     * @param coalCarbonInjection mass of coal or carbon injection for the cycle measured in lbs/cycle
     * @param coalHeatingValue heating value for the coal or carbon injected measured in btu/lb
     * @param electrodeUse electrode use measured in lbs/cycle
     * @param electrodeHeatingValue electrode heating value measured in btu/lb
     * @param otherFuels heat supplied from other sources, if any, measured in mm btu/cycle
     * @param electricityInput total electric power supplied for the cycle measured in kwh/cycle
     * @return heatDelivered (btu/cycle)
     *
     * */
    inp = info[0]->ToObject();
    r = Nan::New<Object>();
    ElectricArcFurnaceEAF eaf(Get("naturalGasHeatInput"), Get("naturalGasFlow"), Get("measuredOxygenFlow"), Get("coalCarbonInjection"), Get("coalHeatingValue"), Get("electrodeUse"), Get("electrodeHeatingValue"), Get("otherFuels"), Get("electricityInput"));
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
    * @param specificHeat Specific heat in °F. double
    * @param feedRate Feed Rate for Gas Mixture. double
    * @param initialTemperature Initial temperature in °F. double
    * @param finalTemperature Final temperature in °F. double
    * @param correctionFactor % of correction. double
    *
    * @return heatLoss double
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
     * @param flueGasTemperature in °F
     * @param excessAirPercentage %
     * @param combustionAirTemperature °F
     * @param gasComposition - percentages for CH4, C2H6, N2, H2, C3H8, C4H10_CnH2n, H2O, CO, CO2, SO2 and O2
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
     * @param flueGasTemperature in °F
     * @param excessAirPercentage %
     * @param combustionAirTemperature °F
     * @param fuelTemperature °F
     * @param moistureInAirComposition
     * @param ashDischargeTemperature
     * @param unburnedCarbonInAsh %
     * @param fuel composition of: carbon, hydrogen, sulphur, inertAsh, o2, moisture and nitrogen (in %)
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
  * @param flowRate Air or gas volumetric flow rate in SCFM (ft³/min)
  * @param initialTemperature Inlet temperature of air or gas in °F
  * @param finalTemperature Outlet temperature of air or gas in °F
  * @param specificHeat Specific heat of gas or air at average air temperature in Btu/(scf F)
  * @param correctionFactor Correction factor
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
 * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions 0 = Endo, else = Exo Int
 * @param specificHeatGas Specific Heat of Gas in Btu/(lb- °F) double
 * @param feedRate Feed Rate for Gas Mixture double
 * @param percentVapor Vapor in Gas Mixture (% of Total) double
 * @param initialTemperature Initial Temperature in °F double
 * @param dischargeTemperature Discharge Temperature in °F double
 * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb- °F) double
 * @param percentReacted Feed Gas Reacted (% of Total) double
 * @param reactionHeat Heat of Reaction in Btu/lb double
 * @param additionalHeat Additional Heat Required in Btu/h double
 *
 * @return heatLoss double
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
     * @param draftPressure
     * @param openingArea
     * @param leakageGasTemperature
     * @param ambientTemperature
     * @param coefficient
     * @param specificGravity
     * @param correctionFactor
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
 * @param flowRate Rate of flow. Units are gpm, MGD(Million Gallons Per Day), L/s, m^3/hr. double
 * @param density Density double
 * @param initialTemperature Initial temperature in °F. double
 * @param outletTemperature Outlet temperature in °F. double
 * @param specificHeat Specific heat in °F. double
 * @param correctionFactor Correction factor double
 * @return heatLoss double
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
         * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
         * @param specificHeatLiquid Specific Heat of Liquid in Btu/(lb-°F)
         * @param vaporizingTemperature Vaporizing Temperature in °F
         * @param latentHeat Latent Heat of Vaporization in Btu/lb
         * @param specificHeatVapor Specific Heat of Vapor in Btu/(lb-°F)
         * @param chargeFeedRate Charge (Liquid)-Feed Rate in lb/h
         * @param initialTemperature Initial Temperature in °F
         * @param dischargeTemperature Discharge Temperature in °F
         * @param percentVaporized Charge Liquid Vaporized  (% of Charge)
         * @param percentReacted Charge Liquid Reacted (% of Charge)
         * @param reactionHeat Heat of Reaction in Btu/lb
         * @param additionalHeat Additional Heat Required in %
         * @return heatLoss double
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
         * @param emissivity
         * @param diameterLength
         * @param thickness
         * @param ratio
         * @param ambientTemperature
         * @param insideTemperature
         * @param percentTimeOpen
         * @param viewFactor
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
         * @param emissivity
         * @param length
         * @param widthHeight
         * @param thickness
         * @param ratio
         * @param ambientTemperature
         * @param insideTemperature
         * @param percentTimeOpen
         * @param viewFactor
         * @return heatLoss
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
        * @param weight Lb/cycle
        * @param inletTemperature Inlet temperature of gasses in °F
        * @param outletTemperature Outlet temperature of gasses in °F
        * @param specificHeat Specific heat of material at average air temperature in Btu/(lb - °F)
        * @param correctionFactor Correction factor
        * @return heatLoss
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
 * @param thermicReactionType Enumerated value for either endothermic or exothermic reactions
 * @param specificHeatSolid Average specific heat of the solid material (dry) in Btu/(lb-°F)
 * @param latentHeat Latent heat of fusion in Btu/(lb)
 * @param specificHeatLiquid Specific heat of liquid from molten material in Btu/(lb-°F)
 * @param meltingPoint The melting point of the material in °F
 * @param chargeFeedRate Charge (wet)-feed rate in lb/h
 * @param waterContentCharged Water content as charged (%) in %
 * @param waterContentDischarged Water content as discharged (%) in %
 * @param initialTemperature Initial temperature in °F
 * @param dischargeTemperature Charge material discharge temperature in °F
 * @param waterVaporDischargeTemperature Water vapor discharge temperature in °F
 * @param chargeMelted Charge melted (% of dry charge) in %
 * @param chargedReacted Charge Reacted (% of dry charge) in %
 * @param reactionHeat Heat of reaction in Btu/lb
 * @param additionalHeat Additional heat required in Btu/h
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
  * @param surfaceArea double
  * @param ambientTemperature double
  * @param surfaceTemperature double
  * @param windVelocity double
  * @param surfaceEmissivity double
  * @param conditionFactor double
  * @param correctionFactor double
  * @return heatLoss double
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
     * @param flowRate Rate of flow. Units are gpm, MGD(Million Gallons Per Day), L/s, m^3/hr.
     * @param initialTemperature Initial temperature in °F.
     * @param outletTemperature Outlet temperature in °F.
     * @param correctionFactor Correction factor
     * @return nothing
     */
    inp = info[0]->ToObject();
    WaterCoolingLosses wcl(Get("flowRate"), Get("initialTemperature"), Get("outletTemperature"), Get("correctionFactor"));
    double heatLoss = wcl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

#endif //AMO_TOOLS_SUITE_LOSSES_H

