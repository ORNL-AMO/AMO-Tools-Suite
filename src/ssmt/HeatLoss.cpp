/**
 * @file
 * @brief Contains the implementation of the heat loss calculator for steam systems.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "ssmt/HeatLoss.h"

HeatLoss::HeatLoss(const double inletPressure, const SteamProperties::ThermodynamicQuantity quantityType,
                   const double quantityValue, const double inletMassFlow, const double percentHeatLoss)
        : inletPressure(inletPressure), quantityType(quantityType), quantityValue(quantityValue),
          inletMassFlow(inletMassFlow), percentHeatLoss(percentHeatLoss / 100),
          inletProperties(SteamProperties(inletPressure, quantityType, quantityValue).calculate()),
          inletEnergyFlow(inletProperties.at("specificEnthalpy") * inletMassFlow / 1000),
          outletEnergyFlow(inletEnergyFlow * (1 - this->percentHeatLoss)),
          outletProperties(SteamProperties(inletPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY,
                                           outletEnergyFlow / inletMassFlow).calculate()),
          heatLoss(inletEnergyFlow - outletEnergyFlow)
{
	inletProperties["massFlow"] = inletMassFlow;
	inletProperties["energyFlow"] = inletEnergyFlow;
	outletProperties["massFlow"] = inletMassFlow;
	outletProperties["energyFlow"] = outletEnergyFlow;
}

//std::unordered_map <std::string, double> HeatLoss::getInletProperties() {
//    SteamProperties sp = SteamProperties(inletPressure, quantityType, quantityValue);
//    std::unordered_map <std::string, double> steamProperties = sp.calculate();
//    inletProperties = steamProperties;
//    return inletProperties;
//}

//double HeatLoss::getInletEnergyFlow(){
////    std::unordered_map <std::string, double> inletProps = getInletProperties();
//    inletEnergyFlow = inletProperties.at("specificEnthalpy") * inletMassFlow;
//    return inletEnergyFlow/1000;
//}

//double HeatLoss::getOutletMassFlow(){
//    outletMassFlow = inletMassFlow;
//    return outletMassFlow;
//}

//double HeatLoss::getOutletEnergyFlow(){
//    outletEnergyFlow = inletEnergyFlow * (1 - percentHeatLoss/100);
//    return outletEnergyFlow;
//}

//std::unordered_map <std::string, double> HeatLoss::getOutletProperties() {
////    double outletEnthalpy = getOutletEnergyFlow()/getInletMassFlow();
//    double outletEnthalpy = outletEnergyFlow / inletMassFlow;
//    SteamProperties sp = SteamProperties(inletPressure, SteamProperties::ThermodynamicQuantity::ENTHALPY, outletEnthalpy);
//    std::unordered_map <std::string, double> steamProperties = sp.calculate();
//    outletProperties = steamProperties;
//    return outletProperties;
//}

//double HeatLoss::getHeatLoss(){
//    heatLoss = getInletEnergyFlow() - getOutletEnergyFlow();
//    return heatLoss;
//}