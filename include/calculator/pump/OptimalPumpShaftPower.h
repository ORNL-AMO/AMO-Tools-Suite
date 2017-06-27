/**
 * @brief Header file for OptimalPumpShaftPower class
 *
 * This contains the prototypes of OptimalPumpShaftPower calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_LIBRARY_OPTIMALPUMPSHAFTPOWER_H
#define AMO_LIBRARY_OPTIMALPUMPSHAFTPOWER_H

#include "FluidPower.h"

class OptimalPumpShaftPower {
public:
    /**
     * Constructor
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, measured or required pump head in feet
     * @param specificGravity double, specific gravity - unitless
     * @param pumpEfficiency double, pump efficiency at the specified operating conditions as %
     * @return nothing
     */
    OptimalPumpShaftPower(
        double flowRate,
        double head,
        double specificGravity,
        double pumpEfficiency
    ) :
        flowRate_(flowRate),
        head_(head),
        specificGravity_(specificGravity),
        pumpEfficiency_(pumpEfficiency)
    {}

    /**
     * Calculates the optimal pump shaft power
     *
     * @return double, optimal pump shaft power in hp
     */
    double calculate();

    /**
     * Gets the measured or required flow rate
     *
     * @return double, measured or required flow rate in gpm
     */
    double getFlowRate() const {
        return flowRate_;
    }

    /**
     * Sets the measured or required flow rate
     *
     * @param flowRate double, measured or required flow rate in gpm
     *
     * @return nothing
     */
    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    /**
     * Gets the measured or required pump head
     *
     * @return double, mesured or required pump head in ft
     */
    double getHead() const {
        return head_;
    }

    /**
     * Sets the measured or required pump head
     *
     * @param head double, measured or required pump head in ft
     *
     * @return nothing
     */
    void setHead(double head) {
        head_ = head;
    }

    /**
     * Gets the specific gravity
     *
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity_;
    }

    /**
     * Sets the specific gravity
     *
     * @param specificGravity double, specific gravity - unitless
     *
     * @return nothing
     */
    void setSpecificGravity(double specificGravity) {
        specificGravity_ = specificGravity;
    }

    /**
     * Gets the pump efficiency
     *
     * @return double, pump efficiency as %
     */
    double getPumpEfficiency() const {
        return pumpEfficiency_;
    }

    /**
     * Sets the pump efficiency
     *
     * @param pumpEfficiency double, pump efficiency as %
     *
     * @return nothing
     */
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
