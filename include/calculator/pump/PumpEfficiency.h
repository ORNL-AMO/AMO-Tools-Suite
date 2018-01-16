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
     * @param specificGravity double, specific gravity - unitless
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, measured or required pump head in feet
     * @param pumpShaftPower double, pump power as defined in hp
     */
    PumpEfficiency(
        double specificGravity,
        double flowRate,
        double head,
        double pumpShaftPower
    )
            : specificGravity(specificGravity),
              flowRate(flowRate),
              head(head),
              pumpShaftPower(pumpShaftPower)
    {}

    /**
     * Calculates the pump efficiency
     * @return double, pump efficiency as %
     */
    double calculate();

public:
    /**
     * Get the specific gravity
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity;
    }

    /**
     * Set the specific gravity
     * @param specificGravity double, specific gravity - unitless
     */
    void setSpecificGravity(double specificGravity) {
        this->specificGravity = specificGravity;
    }

    /**
     * Get the measured or required flow rate
     * @return double, measured or required flow rate in gpm
     */
    double getFlowRate() const {
        return flowRate;
    }

    /**
     * Set the measured or required flow rate
     * @param flowRate double, measrued or required flow rate in gpm
     */
    void setFlowRate(double flowRate) {
        this->flowRate = flowRate;
    }

    /**
     * Get the measured or required pump head
     * @return double, measure or required pump head in ft
     */
    double getHead() const {
        return head;
    }

    /**
     * Set the measured or required pump head
     * @param head double, measured or required pump head in ft
     */
    void setHead(double head) {
        this->head = head;
    }

    /**
     * Get pump shaft power
     * @return double, pump shaft power in hp
     */
    double getPumpShaftPower() const {
        return pumpShaftPower;
    }

    /**
     * Set the pump shaft power
     * @param pumpShaftPower double, pump shaft power in hp
     */
    void setPumpShaftPower(double pumpShaftPower) {
        this->pumpShaftPower = pumpShaftPower;
    }

private:
    double specificGravity;
    double flowRate; // in gpm
    double head; // in ft
    double pumpShaftPower;
};


#endif //AMO_LIBRARY_PUMPEFFICIENCY_H
