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

#include <results/InputData.h>

class OptimalPumpEfficiency {

public:
    /**
     * Constructor
     * @param style Pump::Style, style of pump being used.
     * @param pumpEfficiency double, pump efficiency at the specified operating conditions as %
     * @param rpm double, pump RPM to define its operating speed
     * @param kinematicViscosity double, kinematic viscosity of the fluid being pumped in centistokes
     * @param stageCount double, the number of pump stages
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, pump head in ft
     */
    OptimalPumpEfficiency(
        Pump::Style style,
        double pumpEfficiency,
        double rpm,
        double kinematicViscosity,
        double stageCount,
        double flowRate,
        double head
    ) :
        style(style),
        pumpEfficiency(pumpEfficiency),
        rpm(rpm),
        kinematicViscosity(kinematicViscosity),
        stageCount(stageCount),
        flowRate(flowRate),
        head(head)
    {}

//    OptimalPumpEfficiency(double rpm, double kinematicViscosity, double stageCount, double flowRate, double head,
//                          Pump::SpecificSpeed speed, double actualEfficiency) : rpm(rpm),
//                                                                        kinematicViscosity(kinematicViscosity),
//                                                                        stageCount(stageCount), flowRate(flowRate),
//                                                                        head(head), speed(speed),
//                                                                        actualEfficiency(actualEfficiency) {}

/**
     * Calculates the optimal pump efficiency
     * @return double, optimal pump efficiency as %
     */
    double calculate();

    /**
     * Gets the style of the pump
     * @return Pump::Style, style of pump
     */
    Pump::Style getStyle() const {
        return style;
    }

    /**
     * Sets the pump style
     * @param style Pump::Style, pump style
     */
    void setStyle(Pump::Style style) {
        this->style = style;
    }

    /**
     * Gets the pump RPM to define operation speed
     * @return double, pump RPM
     */
    double getRpm() const {
        return rpm;
    }

    /**
     * Sets the pump RPM to define operation speed
     * @param rpm double, pump RPM
     */
    void setRpm(double rpm) {
        this->rpm = rpm;
    }

    /**
     * Gets the kinematic viscosity of the fluid being pumped
     * @return double, kinematic viscosity in centistokes
     */
    double getKinematicViscosity() const {
        return kinematicViscosity;
    }

    /**
     * Sets the kinematic viscosity of the fluid being pumped
     * @param kinematicViscosity double, kinematic viscosity in centistokes
     */
    void setKinematicViscosity(double kinematicViscosity) {
        this->kinematicViscosity = kinematicViscosity;
    }

    /**
     * Gets the number of pump stages
     * @return double, number of pump stages
     */
    double getStageCount() const {
        return stageCount;
    }

    /**
     * Sets the number of pump stages
     * @param stageCount double, number of pump stages
     */
    void setStageCount(double stageCount) {
        this->stageCount = stageCount;
    }

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
     * Set the measured or required pump head
     * @param head double, measured or required pump head in ft
     */
    void setHead(double head) {
        this->head = head;
    }

    /**
     * Gets the actual efficiency of specified conditions
     * @return double, actual efficiency as %
     */
    double getActualEfficiency() const {
        return actualEfficiency;
    }

    /**
     * Sets the actual efficiency of specified conditions
     * @param actualEfficiency double, actual efficiency as %
     */
    void setActualEfficiency(double actualEfficiency) {
        this->actualEfficiency = actualEfficiency;
    }

private:
    Pump::Style style;
    double pumpEfficiency;
    double rpm;
    double kinematicViscosity;
    double stageCount;
    double flowRate;
    double head;
    double actualEfficiency;
    double optimalEfficiency;
    double prePumpEfficiency = 0.0;
};


#endif //AMO_LIBRARY_OPTIMALPUMPEFFICIENCY_H
