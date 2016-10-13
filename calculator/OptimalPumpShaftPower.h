//
// Created by Accawi, Gina K. on 8/19/16.
//

#ifndef AMO_LIBRARY_OPTIMALPUMPSHAFTPOWER_H
#define AMO_LIBRARY_OPTIMALPUMPSHAFTPOWER_H

#include "FluidPower.h"

class OptimalPumpShaftPower {
public:
    OptimalPumpShaftPower(double flowRate, double head, double specificGravity, double pumpEfficiency) : flowRate_(
            flowRate), head_(head), specificGravity_(specificGravity), pumpEfficiency_(pumpEfficiency) {}

    double calculate();

    double getFlowRate() const {
        return flowRate_;
    }

    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    double getHead() const {
        return head_;
    }

    void setHead(double head) {
        head_ = head;
    }

    double getSpecificGravity() const {
        return specificGravity_;
    }

    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
    }

    double getPumpEfficiency() const {
        return pumpEfficiency_;
    }

    void setPumpEfficiency(double pumpEfficiency) {
        pumpEfficiency_ = pumpEfficiency;
    }

private:
    double flowRate_;
    double head_;
    double specificGravity_;
    double pumpEfficiency_;
};


#endif //AMO_LIBRARY_OPTIMALPUMPSHAFTPOWER_H
