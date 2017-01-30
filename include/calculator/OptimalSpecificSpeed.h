/**
 * @brief Header file for OptimalSpecificSpeed class
 *
 * This contains the prototypes of Optimal Specific Speed calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_OPTIMALSPECIFICSPEED_H
#define AMO_LIBRARY_OPTIMALSPECIFICSPEED_H

class OptimalSpecificSpeed {
public:
    /**
     * Constructor
     * @param rpm Pump RPM to define its operating speed.
     * @param flowRate Measured or required flow rate in units that are consistent with the selection in "Pump Fluid" section.
     * @param head Either measured or required pump head im feet or meters.
     * @param stageCount The number of pump stages.
     * @return nothing
     */
    OptimalSpecificSpeed(
        double rpm,
        double flowRate,
        double head,
        double stageCount
    ):
        stageCount_(stageCount),
        flowRate_(flowRate),
        head_(head),
        rpm_(rpm)
    {};

    double calculate();
private:
    double stageCount_;
    double flowRate_;
    double head_;
    double rpm_;
};


#endif //AMO_LIBRARY_OPTIMALSPECIFICSPEED_H
