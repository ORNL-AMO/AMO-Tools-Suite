//
// Created by Mishra, Subhankar on 10/21/16.
//

#include "OptimalSpecificSpeed.h"

double OptimalSpecificSpeed::calculate() {
    double specificSpeed = rpm_ * sqrt(flowRate_) / (pow((head_ / stageCount_), 0.75));
    return specificSpeed;
}