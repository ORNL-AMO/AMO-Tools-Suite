/**
 * @file
 * @brief Contains the implementation of the Exhaust Gas EAF loss calculator.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */
#include "calculator/losses/ExhaustGasEAF.h"

double ExhaustGasEAF::getCOHeatingValue() {
    this->COHeatingValue_ = (this->CO_/100) * 321;
    return this->COHeatingValue_;
}

double ExhaustGasEAF::getH2HeatingValue() {
    this->H2HeatingValue_ = (this->H2_/100) * 325;
    return this->H2HeatingValue_;
}

double ExhaustGasEAF::getCombustibles() {
    this->combustibles_ = (this->combustibleGases_/100) * 1000;
    return this->combustibles_;
}

double ExhaustGasEAF::getChemicalHeat() {
    double COHeatingValue = getCOHeatingValue();
    double H2HeatingValue = getH2HeatingValue();
    double combustibles = getCombustibles();
    this->chemicalHeat_ = COHeatingValue + H2HeatingValue + combustibles;
    return this->chemicalHeat_;
}

double ExhaustGasEAF::getTotalVfr() {
    this->totalVfr_ = (this->vfr_)*520/(460 + (this->offGasTemp_));
    return this->totalVfr_;
}

double ExhaustGasEAF::getSensibleHeat() {
    this->sensibleHeat_ = 0.0225*((this->offGasTemp_) - 60);
    return this->sensibleHeat_;
}

double ExhaustGasEAF::getHeatInDust() {
    this->heatInDust_ = (this->dustLoading_)*0.25*((this->offGasTemp_) - 60);
    return this->heatInDust_;
}

double ExhaustGasEAF::getTotalHeatFlue() {
    double chemicalHeat = getChemicalHeat();
    double sensibleHeat = getSensibleHeat();
    double heatInDust = getHeatInDust();
    this->totalHeatFlue_ = chemicalHeat + sensibleHeat + heatInDust;
    return this->totalHeatFlue_;
}

double ExhaustGasEAF::getTotalHeatExhaust() {
    double totalVfr = getTotalVfr();
    double totalHeatFlue = getTotalHeatFlue();
    this->totalHeatExhaust_ = (this->cycleTime_)*totalVfr*totalHeatFlue*60;
    return this->totalHeatExhaust_;
}

double ExhaustGasEAF::getChemicalHeatPercent() {
    double chemicalHeat = getChemicalHeat();
    double totalHeatFlue = getTotalHeatFlue();
    this->chemicalHeatPercent_ = chemicalHeat/totalHeatFlue;
    return this->chemicalHeatPercent_*100;
}

double ExhaustGasEAF::getSensibleHeatPercent() {
    double sensibleHeat = getSensibleHeat();
    double totalHeatFlue = getTotalHeatFlue();
    this->sensibleHeatPercent_ = sensibleHeat/totalHeatFlue;
    return this->sensibleHeatPercent_*100;
}

double ExhaustGasEAF::getOtherHeatPercent() {
    double chemicalHeatPercent = getChemicalHeatPercent();
    double sensibleHeatPercent = getSensibleHeatPercent();
    this->otherHeatPercent_ = 1 - (chemicalHeatPercent + sensibleHeatPercent)/100;
    return this->otherHeatPercent_*100;
}