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

    /**
     * Calculates the pump efficiency
     *
     * @return double, pump efficiency as %
     */
    double calculate();

public:
    /**
     * Get the specific gravity
     *
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity_;
    }

    /**
     * Set the specific gravity
     *
     * @param specificGravity double, specific gravity - unitless
     *
     * @return nothing
     */
    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
    }

    /**
     * Get the measured or required flow rate
     *
     * @return double, measured or required flow rate in gpm
     */
    double getFlowRate() const {
        return flowRate_;
    }

    /**
     * Set the measured or required flow rate
     *
     * @param flowRate double, measrued or required flow rate in gpm
     *
     * @return nothing
     */
    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    /**
     * Get the measured or required pump head
     *
     * @return double, measure or required pump head in ft or m
     */
    double getHead() const {
        return head_;
    }

    /**
     * Set the measured or required pump head
     *
     * @param head double, measured or required pump head in ft or m
     *
     * @return nothing
     */
    void setHead(double head) {
        head_ = head;
    }

    /**
     * Get pump shaft power
     *
     * @return double, pump shaft power in hp or kw
     */
    double getPumpShaftPower() const {
        return pumpShaftPower_;
    }

    /**
     * Set the pump shaft power
     *
     * @param pumpShaftPower double, pump shaft power in hp or kw
     *
     * @return nothing
     */
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
