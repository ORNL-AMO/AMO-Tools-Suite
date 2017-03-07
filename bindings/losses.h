//
// Created by Accawi, Gina K. on 3/7/17.
//

#ifndef AMO_TOOLS_SUITE_LOSSES_H
#define AMO_TOOLS_SUITE_LOSSES_H

#include <nan.h>
#include <node.h>

using namespace Nan;
using namespace v8;



#include "calculator/FixtureLosses.h"
#include "calculator/LoadChargeMaterial.h"
#include "calculator/GasCoolingLosses.h"
#include "calculator/GasLoadChargeMaterial.h"
#include "calculator/LiquidCoolingLosses.h"
#include "calculator/LiquidLoadChargeMaterial.h"
#include "calculator/WallLosses.h"
/**********************
 * Test methods
 */

NAN_METHOD(initTest) {
        Local<String> temp = Nan::New<String>("Hello").ToLocalChecked();
        info.GetReturnValue().Set(temp);
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
#endif //AMO_TOOLS_SUITE_LOSSES_H
