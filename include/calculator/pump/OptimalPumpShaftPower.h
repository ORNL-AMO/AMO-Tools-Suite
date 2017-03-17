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
     * @param flowRate Measured or required flow rate in units that are consistent with the selection in "Pump Fluid" section.
     * @param head Either measured or required pump head im feet or meters.
     * @param specificGravity Specific gravity.
     * @param pumpEfficiency Pump efficiency at the specified operating conditions.
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
