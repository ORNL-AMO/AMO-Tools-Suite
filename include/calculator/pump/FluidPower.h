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
     * FluidPower constructor for pump systems
     * @param specificGravity double, specified gravity - unitless
     * @param flowRate double, rate of flow in gpm
     * @param head double, pump head measured in feet
     */
    FluidPower(double specificGravity, double flowRate, double head)
            : specificGravity(specificGravity), flowRate(flowRate), head(head), isPump(true)
    {};

    /**
     * FluidPower constructor for Fan systems
     * @param flowRate double, rate of flow in cfm
     * @param inletPressure double, in inches of water column, gauge
     * @param outletPressure double, in inches of water column, gauge
     * @param compressibilityFactor double, unitless
     */
    FluidPower(double flowRate, const double inletPressure, const double outletPressure, const double compressibilityFactor)
            : flowRate(flowRate), inletPressure(inletPressure), outletPressure(outletPressure),
              compressibilityFactor(compressibilityFactor), isPump(false)
    {};

    /**
     * Calculates pump or fan fluid power in kw, depending on the number of constructor inputs (isPump)
     * @return double, fluid power
     */
    double calculate() {
        if (isPump) {
            return 0.746 * flowRate * head * specificGravity / 3961.38;
        }
        return 0.746 * flowRate * (outletPressure - inletPressure) * compressibilityFactor / 6362;
    }

private:
    const double specificGravity = 0, flowRate, head = 0;

    // used only for fan fluid power calculations
    const double inletPressure = 0, outletPressure = 0, compressibilityFactor = 0;

    const bool isPump;


};

#endif //AMO_LIBRARY_FLUIDPOWER_H
