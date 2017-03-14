/**
 * @brief Header file for PumpEfficiency class
 *
 * This contains the prototypes of PumpEfficiency calculator including getters and setters for the important fields.
 *
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_PUMPEFFICIENCY_H
#define AMO_LIBRARY_PUMPEFFICIENCY_H

#include "FluidPower.h"

class PumpEfficiency {

public:
    /**
     * Constructor
     * @param specificGravity Specific gravity.
     * @param flowRate Measured or required flow rate in units that are consistent with the selection in "Pump Fluid" section.
     * @param head Either measured or required pump head im feet or meters.
     * @param pumpShaftPower Pump power as defined in hp or kW.
     * @return nothing
     */
    PumpEfficiency(
        double specificGravity,
        double flowRate,
        double head,
        double pumpShaftPower
    ) :
        specificGravity_(specificGravity),
         flowRate_(flowRate),
         head_(head),
         pumpShaftPower_(pumpShaftPower)
    {}

    double calculate();

public:
    double getSpecificGravity() const {
        return specificGravity_;
    }

    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
    }

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

    double getPumpShaftPower() const {
        return pumpShaftPower_;
    }

    void setPumpShaftPower(double pumpShaftPower) {
        pumpShaftPower_ = pumpShaftPower;
    }

private:
    double specificGravity_;
    double flowRate_; // in gpm
    double head_; // in ft
    double pumpShaftPower_;
    double fluidPower_; //Fluid Power (in kW)
    double fluidPowerHp_; // Fluid Power in hP
    double pumpEfficiency_; // in %
};


#endif //AMO_LIBRARY_PUMPEFFICIENCY_H
