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
     * Constructor used for pumps
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, measured or required pump head in feet
     * @param specificGravity double, specific gravity - unitless
     * @param pumpEfficiency double, pump efficiency at the specified operating conditions as %
     */
    OptimalPumpShaftPower(const double flowRate, const double head, const double specificGravity, const double pumpEfficiency)
            : flowRate(flowRate), head(head), specificGravity(specificGravity), efficiency(pumpEfficiency), isPump(true)
    {}

    /**
     * Construct used for fans
     * @param flowRate, double in cfm
     * @param inletPressure, double in
     * @param outletPressure
     * @param compressibilityFactor
     * @param fanEfficiency
     */
    OptimalPumpShaftPower(const double flowRate, const double inletPressure, const double outletPressure,
                          const double compressibilityFactor, const double fanEfficiency)
            : flowRate(flowRate), efficiency(fanEfficiency), inletPressure(inletPressure), outletPressure(outletPressure),
              compressibilityFactor(compressibilityFactor), isPump(false)
    {}

    /**
     * Calculates the optimal pump shaft power
     *
     * @return double, optimal pump shaft power in hp
     */
    double calculate();

    /**
     * Gets the measured or required flow rate
     * @return double, measured or required flow rate in gpm
     */
    double getFlowRate() const {
        return flowRate;
    }

    /**
     * Sets the measured or required flow rate
     * @param flowRate double, measured or required flow rate in gpm
     */
    void setFlowRate(double flowRate) {
        this->flowRate = flowRate;
    }

    /**
     * Gets the measured or required pump head
     * @return double, measured or required pump head in ft
     */
    double getHead() const {
        return head;
    }

    /**
     * Sets the measured or required pump head
     * @param head double, measured or required pump head in ft
     */
    void setHead(double head) {
        this->head = head;
    }

    /**
     * Gets the specific gravity
     * @return double, specific gravity - unitless
     */
    double getSpecificGravity() const {
        return specificGravity;
    }

    /**
     * Sets the specific gravity
     * @param specificGravity double, specific gravity - unitless
     */
    void setSpecificGravity(double specificGravity) {
        this->specificGravity = specificGravity;
    }

    /**
     * Gets the pump efficiency
     * @return double, pump efficiency as %
     */
    double getPumpEfficiency() const {
        return efficiency;
    }

    /**
     * Sets the pump efficiency
     * @param pumpEfficiency double, pump efficiency as %
     */
    void setPumpEfficiency(double pumpEfficiency) {
        this->efficiency = pumpEfficiency;
    }

private:
    double flowRate, head = 0, specificGravity = 0, efficiency = 0;

    double inletPressure = 0, outletPressure = 0, compressibilityFactor = 0;

    bool isPump;
};


#endif //AMO_LIBRARY_OPTIMALPUMPSHAFTPOWER_H
