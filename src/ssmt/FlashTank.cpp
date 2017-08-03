///**
// * @file
// * @brief Contains the implementation of the flash tank calculator for steam systems.
// *
// * @author Autumn Ferree (ferreeak)
// * @bug No known bugs.
// *
// */
//
//#include "ssmt/FlashTank.h"
//
//std::unordered_map <std::string, double> FlashTank::getInletWaterProperties() {
//    SteamProperties sp = SteamProperties(this->inletWaterPressure_, this->quantityType_, this->quantityValue_);
//    std::unordered_map <std::string, double> waterProperties = sp.calculate();
//    this->inletWaterProperties_ = waterProperties;
//    return this->inletWaterProperties_;
//}
//
//SaturatedProperties FlashTank::getOutletSaturatedProperties() {
//    SaturatedTemperature temperature = SaturatedTemperature(this->tankPressure_);
//    double saturatedTemperature = temperature.calculate();
//    SaturatedProperties sp = SaturatedProperties(this->tankPressure_, saturatedTemperature);
//    this->outletSaturatedProperties_ = sp;
//    return this->outletSaturatedProperties_;
//}
//
//double FlashTank::getOutletLiquidMassFlow() {
//    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
//    SaturatedProperties satProps = getOutletSaturatedProperties();
//    this->outletLiquidMassFlow_ = this->inletWaterMassFlow_ * (inletWaterProps["specificEnthalpy"] - satProps.getGasEnthalpy()) / (satProps.getLiquidEnthalpy() - satProps.getGasEnthalpy());
//    return this->outletLiquidMassFlow_;
//}
//
//double FlashTank::getOutletGasMassFlow() {
//    this->outletGasMassFlow_ = this->inletWaterMassFlow_ - getOutletLiquidMassFlow();
//    return this->outletGasMassFlow_;
//}
//
//double FlashTank::getInletWaterEnergyFlow(){
//    std::unordered_map <std::string, double> inletWaterProps = getInletWaterProperties();
//    this->inletWaterEnergyFlow_ = this->inletWaterMassFlow_ * inletWaterProps["specificEnthalpy"];
//    return this->inletWaterEnergyFlow_;
//}
//
//double FlashTank::getOutletGasEnergyFlow(){
//    SaturatedProperties satProps = getOutletSaturatedProperties();
//    this->outletGasEnergyFlow_ = getOutletGasMassFlow() * satProps.getGasEnthalpy();
//    return this->outletGasEnergyFlow_;
//}
//
//double FlashTank::getOutletLiquidEnergyFlow(){
//    SaturatedProperties satProps = getOutletSaturatedProperties();
//    this->outletLiquidEnergyFlow_ = getOutletLiquidMassFlow() * satProps.getLiquidEnthalpy();
//    return this->outletLiquidEnergyFlow_;
//}
