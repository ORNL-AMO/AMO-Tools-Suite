//
// Created by Accawi, Gina K. on 6/15/16.
//

#include "Financial.h"

Financial::Financial() {
    operatingFraction_ = 1.0;
    unitCost_ = 1.0;
}

Financial::Financial(double operatingFraction, double unitCost) {
    this->operatingFraction_ = operatingFraction;
    this->unitCost_ = unitCost;
}

double Financial::getOperatingFraction() {
    return operatingFraction_;
}

void Financial::setOperatingFraction(double operatingFraction) {
    this->operatingFraction_ = operatingFraction;
}

double Financial::getUnitCost() {
    return unitCost_;
}

void Financial::setUnitCost(double unitCost) {
    this->unitCost_ = unitCost;
}