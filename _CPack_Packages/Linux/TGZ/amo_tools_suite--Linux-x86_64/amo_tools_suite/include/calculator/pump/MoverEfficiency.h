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

class MoverEfficiency {

public:
    /**
     * Constructor for calculating pump mover efficiency
     * @param specificGravity double, specific gravity - unitless
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, measured or required pump head in feet
     * @param pumpShaftPower double, pump power as defined in hp
     */
    MoverEfficiency(double const specificGravity, double const flowRate, double const head, double const pumpShaftPower)
            : specificGravity(specificGravity),
              head(head),
              flowRate(flowRate),
              moverShaftPower(pumpShaftPower),
              isPump(true)
    {}

    /**
     * Constructor for calculating fan mover efficiency
     * @param flowRate double, measured or required flow rate in gpm
     * @param fanShaftPower double, fanShaftPower as defined in hp
     * @param inletPressure double,
     * @param outletPressure double,
     * @param compressibilityFactor double,
     */
    MoverEfficiency(double const flowRate, double const  fanShaftPower, double const inletPressure, double const outletPressure,
                    double const compressibilityFactor)
            : flowRate(flowRate), moverShaftPower(fanShaftPower), inletPressure(inletPressure), outletPressure(outletPressure),
              compressibilityFactor(compressibilityFactor), isPump(false)
    {}

    /**
     * Calculates the mover efficiency, either for a pump or fan system depending on constructor number of inputs
     * @return double, mover efficiency as %
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
        return moverShaftPower;
    }

    /**
     * Set the pump shaft power
     * @param pumpShaftPower double, pump shaft power in hp
     */
    void setPumpShaftPower(double pumpShaftPower) {
        this->moverShaftPower = pumpShaftPower;
    }

private:
    double specificGravity = 0, head = 0;
    double flowRate, moverShaftPower;
    double inletPressure = 0, outletPressure = 0, compressibilityFactor = 0;

    const bool isPump;
};


#endif //AMO_LIBRARY_PUMPEFFICIENCY_H
