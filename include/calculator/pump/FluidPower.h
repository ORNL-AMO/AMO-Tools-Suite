/**
 * @brief Contains the skeleton of FluidPower class.
 *      calculate(): Calculates the fluid power
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_FLUIDPOWER_H
#define AMO_LIBRARY_FLUIDPOWER_H

class FluidPower {
public:
    /**
     * Constructor
     * @param specificGravity double, specified gravity - unitless
     * @param flowRate double, rate of flow in gpm
     * @param head double, pump head measured in feet
     */
    FluidPower(
        double specificGravity,
        double flowRate,
        double head
    ) :
        specificGravity(specificGravity),
        flowRate(flowRate),
        head(head)
    {};

    /**
     * Calculates fluid power in kw
     * @return double, fluid power
     */
    double calculate();

private:
    /**
     * Specific Gravity
     */
    double specificGravity;
    /**
     * Flow rate in GPM
     */
    double flowRate;
    /**
     * Length of head in ft
     */
    double head;
};

#endif //AMO_LIBRARY_FLUIDPOWER_H
