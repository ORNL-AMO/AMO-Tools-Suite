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
     * @param rpm double, pump RPM to define its operating speed
     * @param flowRate double, measured or required flow rate in gpm
     * @param head double, measured or required pump head in feet
     * @param stageCount double, the number of pump stages
     */
    OptimalSpecificSpeed(
        double rpm,
        double flowRate,
        double head,
        double stageCount
    ):
        stageCount(stageCount),
        flowRate(flowRate),
        head(head),
        rpm(rpm)
    {};

    /**
     * Calculates the optimal specific speed
     * @return double, optimal specific speed in rpm*sqrt(gpm)/((ft/s)^(3/2))
     */
    double calculate();

private:
    double stageCount;
    double flowRate;
    double head;
    double rpm;
};


#endif //AMO_LIBRARY_OPTIMALSPECIFICSPEED_H
