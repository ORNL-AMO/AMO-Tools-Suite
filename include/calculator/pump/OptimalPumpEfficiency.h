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
     * @param style Pump::Style, style of pump being used.
     * @param achievableEfficiency double, pump efficiency at the specified operating conditions as %
     * @param rpm double, pump RPM to define its operating speed
     * @param kinematicViscosity double, kinematic viscosity of the fluid being pumped in centistokes
     * @param stageCount double, the number of pump stages
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, pump head in ft
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

/**
     * Calculates the optimal pump efficiency
     *
     * @return double, optimal pump efficiency as %
     */
    double calculate();

    /**
     * Gets the style of the pump
     *
     * @return Pump::Style, style of pump
     */
    Pump::Style getStyle() const {
        return style_;
    }

    /**
     * Sets the pump style
     *
     * @param style Pump::Style, pump style
     *
     */
    void setStyle(Pump::Style style) {
        style_ = style;
    }

    /**
     * Gets the pump RPM to define operation speed
     *
     * @return double, pump RPM
     */
    double getRpm() const {
        return rpm_;
    }

    /**
     * Sets the pump RPM to define operation speed
     *
     * @param rpm double, pump RPM
     *
     */
    void setRpm(double rpm) {
        rpm_ = rpm;
    }

    /**
     * Gets the kinematic viscosity of the fluid being pumped
     *
     * @return double, kinematic viscosity in centistokes
     */
    double getKinematicViscosity() const {
        return kinematicViscosity_;
    }

    /**
     * Sets the kinematic viscosity of the fluid being pumped
     *
     * @param kinematicViscosity double, kinematic viscosity in centistokes
     *
     */
    void setKinematicViscosity(double kinematicViscosity) {
        kinematicViscosity_ = kinematicViscosity;
    }

    /**
     * Gets the number of pump stages
     *
     * @return double, number of pump stages
     */
    double getStageCount() const {
        return stageCount_;
    }

    /**
     * Sets the number of pump stages
     *
     * @param stageCount double, number of pump stages
     *
     */
    void setStageCount(double stageCount) {
        stageCount_ = stageCount;
    }

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
     */
    void setFlowRate(double flowRate) {
        flowRate_ = flowRate;
    }

    /**
     * Gets the measured or required pump head
     *
     * @return double, measured or required pump head in ft
     */
    double getHead() const {
        return head_;
    }

    /**
     * CSet the measured or required pump head
     *
     * @param head double, measured or required pump head in ft
     *
     */
    void setHead(double head) {
        head_ = head;
    }

    /**
     * Gets the actual efficiency of specified conditions
     *
     * @return double, actual efficiency as %
     */
    double getActualEfficiency() const {
        return actualEfficiency_;
    }

    /**
     * Sets the actual efficiency of specified conditions
     *
     * @param actualEfficiency double, actual efficiency as %
     *
     */
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
