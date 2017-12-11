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
     */
    OptimalPumpShaftPower(
        double flowRate,
        double head,
        double specificGravity,
        double pumpEfficiency
    ) :
        flowRate(flowRate),
        head(head),
        specificGravity(specificGravity),
        pumpEfficiency(pumpEfficiency)
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
        return flowRate;
    }

    /**
     * Sets the measured or required flow rate
     *
     * @param flowRate double, measured or required flow rate in gpm
     *
     */
    void setFlowRate(double flowRate) {
        this->flowRate = flowRate;
    }

    /**
     * Gets the measured or required pump head
     *
     * @return double, mesured or required pump head in ft
     */
    double getHead() const {
        return head;
    }

    /**
     * Sets the measured or required pump head
     *
     * @param head double, measured or required pump head in ft
     *
     */
    void setHead(double head) {
        this->head = head;
    }

    /**
     * Gets the specific gravity
     *
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity;
    }

    /**
     * Sets the specific gravity
     *
     * @param specificGravity double, specific gravity - unitless
     *
     */
    void setSpecificGravity(double specificGravity) {
        this->specificGravity = specificGravity;
    }

    /**
     * Gets the pump efficiency
     *
     * @return double, pump efficiency as %
     */
    double getPumpEfficiency() const {
        return pumpEfficiency;
    }

    /**
     * Sets the pump efficiency
     *
     * @param pumpEfficiency double, pump efficiency as %
     *
     */
    void setPumpEfficiency(double pumpEfficiency) {
        this->pumpEfficiency = pumpEfficiency;
    }

private:
    double flowRate;
    double head;
    double specificGravity;
    double pumpEfficiency;
};


#endif //AMO_LIBRARY_OPTIMALPUMPSHAFTPOWER_H
