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
     * Below parameters have self explanatory nomenclature.
     * @param specificGravity double, specified gravity - unitless
     * @param flowRate double, rate of flow in gpm
     * @param head double, pump head measured in feet
     * @return nothing
     */
    FluidPower(
        double specificGravity,
        double flowRate,
        double head
    ) :
        specificGravity_(specificGravity),
        flowRate_(flowRate),
        head_(head)
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
    double specificGravity_;
    /**
     * Flow rate in GPM
     */
    double flowRate_;
    /**
     * Length of head in ft
     */
    double head_;
    /**
     * Returning fluid power in kw
     */
    double fluidPower_;
};

#endif //AMO_LIBRARY_FLUIDPOWER_H
