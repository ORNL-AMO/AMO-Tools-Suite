//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_LOSSES_H
#define AMO_TOOLS_SUITE_LOSSES_H

#include <nan.h>
#include <node.h>

using namespace Nan;
using namespace v8;



#include "calculator/losses/Atmosphere.h"
#include "calculator/losses/FixtureLosses.h"
#include "calculator/losses/FlueGas.h"
#include "calculator/losses/LoadChargeMaterial.h"
#include "calculator/losses/GasCoolingLosses.h"
#include "calculator/losses/GasLoadChargeMaterial.h"
#include "calculator/losses/LeakageLosses.h"
#include "calculator/losses/LiquidCoolingLosses.h"
#include "calculator/losses/LiquidLoadChargeMaterial.h"
#include "calculator/losses/OpeningLosses.h"
#include "calculator/losses/SolidLoadChargeMaterial.h"
#include "calculator/losses/WallLosses.h"
#include "calculator/losses/WaterCoolingLosses.h"

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
     double inletTemperature = info[0]->NumberValue();
     double outletTemperature = info[1]->NumberValue();
     double flowRate = info[2]->NumberValue();
     double correctionFactor = info[3]->NumberValue();
     double specificHeat = info[4]->NumberValue();
     Atmosphere a(inletTemperature, outletTemperature, flowRate, correctionFactor, specificHeat);
     double heatLoss = a.getTotalHeat();
     Local<Number> retval = Nan::New(heatLoss);
     info.GetReturnValue().Set(retval);
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
        double specificHeat = info[0]->NumberValue();
        double feedRate = info[1]->NumberValue();
        double initialTemperature = info[2]->NumberValue();
        double finalTemperature = info[3]->NumberValue();
        double correctionFactor = info[4]->NumberValue();
        FixtureLosses fl(specificHeat, feedRate, initialTemperature, finalTemperature, correctionFactor);
        double heatLoss = fl.getHeatLoss();
        Local<Number> retval = Nan::New(heatLoss);
        info.GetReturnValue().Set(retval);
}

NAN_METHOD(flueGas) {
    /**
     * Constructor for the flue gas losses with all inputs specified
     *
     * @param furnaceDraft Furnace daft in inch W.C
     * @param leakageTemperature Leakage temperature of gases in °F
     * @param openingArea Opening area of flue in ft²
     * @param leakageTemperature Temperature of leakage gases in °F
     * @param ambientTemperature Ambient temparture of gases in °F
     * @param flowCoeeficient Coefficient of discharge double
     * @param specificGravity Specific gravity of flue gases
     * @param correction Factor
     * @return nothing
     *
     * */
        double furnaceDraft = info[0]->NumberValue();
        double openingArea = info[1]->NumberValue();
        double leakageTemperature = info[2]->NumberValue();
        double ambientTemperature = info[3]->NumberValue();
        double flowCoefficient = info[4]->NumberValue();
        double specificGravity = info[5]->NumberValue();
        double correctionFactor = info[6]->NumberValue();
        FlueGas fg(furnaceDraft, openingArea, leakageTemperature, ambientTemperature, flowCoefficient, specificGravity, correctionFactor);
        double heatLoss = fg.getHeatLoss();
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
        double flowRate = info[0]->NumberValue();
        double initialTemperature = info[1]->NumberValue();
        double finalTemperature = info[2]->NumberValue();
        double specificHeat = info[3]->NumberValue();
        double correctionFactor = info[4]->NumberValue();
        GasCoolingLosses gcl(flowRate, initialTemperature, finalTemperature, specificHeat, correctionFactor);
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
        LoadChargeMaterial::ThermicReactionType thermicReactionType;
        int trt = info[0]->NumberValue();
        if (trt == 0) {
            thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
        } else {
            thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
        }
        double specificHeatGas = info[1]->NumberValue();
        double feedRate = info[2]->NumberValue();
        double percentVapor = info[3]->NumberValue();
        double initialTemperature = info[4]->NumberValue();
        double dischargeTemperature = info[5]->NumberValue();
        double specificHeatVapor = info[6]->NumberValue();
        double percentReacted = info[7]->NumberValue();
        double reactionHeat = info[8]->NumberValue();
        double additionalHeat = info[9]->NumberValue();
        GasLoadChargeMaterial glcm(thermicReactionType, specificHeatGas, feedRate, percentVapor, initialTemperature, dischargeTemperature, specificHeatVapor,
        percentReacted, reactionHeat, additionalHeat);
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
        double draftPressure = info[0]->NumberValue();
        double openingArea = info[1]->NumberValue();
        double leakageGasTemperature = info[2]->NumberValue();
        double ambientTemperature = info[3]->NumberValue();
        double coefficient = info[4]->NumberValue();
        double specificGravity = info[5]->NumberValue();
        double correctionFactor = info[6]->NumberValue();
        LeakageLosses ll(draftPressure, openingArea, leakageGasTemperature, ambientTemperature, coefficient, specificGravity, correctionFactor);
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
        double flowRate = info[0]->NumberValue();
        double density = info[1]->NumberValue();
        double initialTemperature = info[2]->NumberValue();
        double outletTemperature = info[3]->NumberValue();
        double specificHeat = info[4]->NumberValue();
        double correctionFactor = info[5]->NumberValue();
        LiquidCoolingLosses lcl(flowRate, density, initialTemperature, outletTemperature, specificHeat, correctionFactor);
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

        LoadChargeMaterial::ThermicReactionType thermicReactionType;
        int trt = info[0]->NumberValue();
        if (trt == 0) {
            thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
        } else {
            thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
        }
        double specificHeatLiquid = info[1]->NumberValue();
        double vaporizingTemperature = info[2]->NumberValue();
        double latentHeat = info[3]->NumberValue();
        double specificHeatVapor = info[4]->NumberValue();
        double chargeFeedRate = info[5]->NumberValue();
        double initialTemperature = info[6]->NumberValue();
        double dischargeTemperature = info[7]->NumberValue();
        double percentVaporized = info[8]->NumberValue();
        double percentReacted = info[9]->NumberValue();
        double reactionHeat = info[10]->NumberValue();
        double additionalHeat = info[11]->NumberValue();
        LiquidLoadChargeMaterial llcm(thermicReactionType, specificHeatLiquid, vaporizingTemperature, latentHeat,
        specificHeatVapor, chargeFeedRate, initialTemperature,
        dischargeTemperature, percentVaporized, percentReacted, reactionHeat, additionalHeat);
        double heatLoss = llcm.getTotalHeat();
        Local<Number> retval = Nan::New(heatLoss);
        info.GetReturnValue().Set(retval);
}

NAN_METHOD(openingLosses) {

    /**
     * Constructor
     * @param emissivity
     * @param diameterWidth
     * @param thickness
     * @param ratio
     * @param ambientTemperature
     * @param insideTemperature
     * @param percentTimeOpen
     * @param viewFactor
     * @return nothing
     */

    double emissivity = info[0]->NumberValue();
    double diameterWidth = info[1]->NumberValue();
    double thickness = info[2]->NumberValue();
    double ratio = info[3]->NumberValue();
    double ambientTemperature = info[4]->NumberValue();
    double insideTemperature = info[5]->NumberValue();
    double percentTimeOpen = info[6]->NumberValue();
    double viewFactor = info[7]->NumberValue();
    OpeningLosses::OpeningShape openingShape;
    int trt = info[8]->NumberValue();
    if (trt == 0) {
        openingShape = OpeningLosses::OpeningShape::CIRCULAR;
    } else {
        openingShape = OpeningLosses::OpeningShape::RECTANGULAR;
    }
    OpeningLosses ol(emissivity, diameterWidth, thickness, ratio, ambientTemperature, insideTemperature, percentTimeOpen, viewFactor, openingShape);
    double heatLoss = ol.getHeatLoss();
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

    LoadChargeMaterial::ThermicReactionType thermicReactionType;
    int trt = info[0]->NumberValue();
    if (trt == 0) {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::ENDOTHERMIC;
    } else {
        thermicReactionType = LoadChargeMaterial::ThermicReactionType::EXOTHERMIC;
    }
    double specificHeatSolid = info[1]->NumberValue();
    double latentHeat = info[2]->NumberValue();
    double specificHeatLiquid = info[3]->NumberValue();
    double meltingPoint = info[4]->NumberValue();
    double chargeFeedRate = info[5]->NumberValue();
    double waterContentCharged = info[6]->NumberValue();
    double waterContentDischarged = info[7]->NumberValue();
    double initialTemperature = info[8]->NumberValue();
    double dischargeTemperature = info[9]->NumberValue();
    double waterVaporDischargeTemperature = info[10]->NumberValue();
    double chargeMelted = info[11]->NumberValue();
    double chargedReacted = info[12]->NumberValue();
    double reactionHeat = info[13]->NumberValue();
    double additionalHeat = info[14]->NumberValue();
    SolidLoadChargeMaterial slcm(thermicReactionType, specificHeatSolid, latentHeat, specificHeatLiquid, meltingPoint, chargeFeedRate, waterContentCharged, waterContentDischarged, initialTemperature, dischargeTemperature, waterVaporDischargeTemperature, chargeMelted, chargedReacted, reactionHeat, additionalHeat);
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
    double surfaceArea = info[0]->NumberValue();
    double ambientTemperature = info[1]->NumberValue();
    double surfaceTemperature = info[2]->NumberValue();
    double windVelocity = info[3]->NumberValue();
    double surfaceEmissivity = info[4]->NumberValue();
    double conditionFactor = info[5]->NumberValue();
    double correctionFactor = info[6]->NumberValue();
    WallLosses wl(surfaceArea, ambientTemperature, surfaceTemperature, windVelocity, surfaceEmissivity, conditionFactor, correctionFactor);
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

    double flowRate = info[0]->NumberValue();
    double initialTemperature = info[1]->NumberValue();
    double outletTemperature = info[2]->NumberValue();
    double correctionFactor = info[3]->NumberValue();
    WaterCoolingLosses wcl(flowRate, initialTemperature, outletTemperature, correctionFactor);
    double heatLoss = wcl.getHeatLoss();
    Local<Number> retval = Nan::New(heatLoss);
    info.GetReturnValue().Set(retval);
}

#endif //AMO_TOOLS_SUITE_LOSSES_H

