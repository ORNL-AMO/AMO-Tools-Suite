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
     * @param specificGravity Specified Gravity.
     * @param flowRate Rate of flow. Units are gpm
     * @param head Pump head measured in feet
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
     * Calculates fluid power
     * @return Fluid Power
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
     * Returning fluid power
     */
    double fluidPower_;
};

#endif //AMO_LIBRARY_FLUIDPOWER_H
