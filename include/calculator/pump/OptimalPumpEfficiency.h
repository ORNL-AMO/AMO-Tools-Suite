/**
 * @brief Header file for OptimalPumpEfficiency class
 *
 * This contains the prototypes of OptimalPumpEfficiency calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_OPTIMALPUMPEFFICIENCY_H
#define AMO_LIBRARY_OPTIMALPUMPEFFICIENCY_H

#include "psat/Pump.h"

class OptimalPumpEfficiency {

public:
    /**
     * Constructor
     * @param style Style of pump being used.
     * @param achievableEfficiency Pump efficiency at the specified operating conditions.
     * @param rpm Pump RPM to define its operating speed.
     * @param kinematicViscosity Kinematic viscosity of the fluid being pumped, in centistokes.
     * @param stageCount The number of pump stages.
     * @param flowRate Measured or required flow rate in units that are consistent with the selection in "Pump Fluid" section.
     * @param head Either measured or required pump head im feet or meters.
     * @return nothing
     */
    OptimalPumpEfficiency(
        Pump::Style style,
        double achievableEfficiency,
        double rpm,
        double kinematicViscosity,
        double stageCount,
        double flowRate,
        double head
    ) :
        style_(style),
        achievableEfficiency_(achievableEfficiency),
        rpm_(rpm),
        kinematicViscosity_(kinematicViscosity),
        stageCount_(stageCount),
        flowRate_(flowRate),
        head_(head)
    {}

//    OptimalPumpEfficiency(double rpm, double kinematicViscosity, double stageCount, double flowRate, double head,
//                          Pump::Speed speed, double actualEfficiency) : rpm_(rpm),
//                                                                        kinematicViscosity_(kinematicViscosity),
//                                                                        stageCount_(stageCount), flowRate_(flowRate),
//                                                                        head_(head), speed_(speed),
//                                                                        actualEfficiency_(actualEfficiency) {}

    double calculate();

    Pump::Style getStyle() const {
        return style_;
    }

    void setStyle(Pump::Style style) {
        style_ = style;
    }

    double getRpm() const {
        return rpm_;
    }

    void setRpm(double rpm) {
        rpm_ = rpm;
    }

    double getKinematicViscosity() const {
        return kinematicViscosity_;
    }

    void setKinematicViscosity(double kinematicViscosity) {
        kinematicViscosity_ = kinematicViscosity;
    }

    double getStageCount() const {
        return stageCount_;
    }

    void setStageCount(double stageCount) {
        stageCount_ = stageCount;
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

    double getActualEfficiency() const {
        return actualEfficiency_;
    }

    void setActualEfficiency(double actualEfficiency) {
        actualEfficiency_ = actualEfficiency;
    }

private:
    Pump::Style style_;
    double achievableEfficiency_;
    double rpm_;
    double kinematicViscosity_;
    double stageCount_;
    double flowRate_;
    double head_;
    double actualEfficiency_;
    double optimalEfficiency_;
    double pumpEfficiency = 0.0;
};


#endif //AMO_LIBRARY_OPTIMALPUMPEFFICIENCY_H
