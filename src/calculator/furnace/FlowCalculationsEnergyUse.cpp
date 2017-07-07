/**
 * @file
 * @brief Contains the implementation of the flow calculations energy use for fuel fired furnace.
 *
 * @author Autumn Ferree (ferreeak)
 * @bug No known bugs.
 *
 */

#include "calculator/furnace/FlowCalculationsEnergyUse.h"
#include <cmath>


double FlowCalculationsEnergyUse::getArea() {
    this->area_ = 1300 * (this->orificeDiameter_)*(this->orificeDiameter_);
    return this->area_;
}

double FlowCalculationsEnergyUse::getAdjustedDischargeCoefficient() {
    if ((this->orificeDiameter_) < (this->insidePipeDiameter_)) {
        this->adjustedDischargeCoefficient_ = (this->dischargeCoefficient_)/(pow((1 - pow((this->orificeDiameter_)/(this->insidePipeDiameter_), 4)), .5));
        return this->adjustedDischargeCoefficient_;
    }
    else
        return this->dischargeCoefficient_;
}

double FlowCalculationsEnergyUse::getPressureDrop() {
    this->pressureDrop_ = pow((this->orificePressureDrop_)/(this->specificGravity_), 0.5);
    return this->pressureDrop_;
}

double FlowCalculationsEnergyUse::getAdjustedGasTemperature() {
    this->adjustedGasTemperature_ = pow(520/(460 + (this->gasTemperature_)), 0.5);
    return this->adjustedGasTemperature_;
}

double FlowCalculationsEnergyUse::getAdjustedGasPressure() {
    this->adjustedGasPressure_ = pow(((this->gasPressure_) + 14.7)/14.7, 0.5);
    return this->adjustedGasPressure_;
}

double FlowCalculationsEnergyUse::getFlow() {
    double area = getArea();
    double dischargeCoefficient = getAdjustedDischargeCoefficient();
    double pressureDrop = getPressureDrop();
    double gasPressure = getAdjustedGasPressure();
    double gasTemperature = getAdjustedGasTemperature();
    this->flow_ = area * dischargeCoefficient * pressureDrop * gasTemperature * gasPressure;
    return this->flow_;
}

double FlowCalculationsEnergyUse::getHeatInput() {
    double flow = getFlow();
    if ((this->gasHeatingValue_) <= 0){
        this->heatInput_ = 0;
    }
    else {
        this->heatInput_ = (flow * (this->gasHeatingValue_) * (this->operatingTime_)) / 1000000;
    }
    return this->heatInput_;
}

double FlowCalculationsEnergyUse::getTotalFlow() {
    double flow = getFlow();
    this->totalflow_ = (flow * this->operatingTime_);
    return this->totalflow_;
}