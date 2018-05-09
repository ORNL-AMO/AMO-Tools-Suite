/**
 * @brief Header file for OptimalPrePumpEff class
 *
 * This contains the prototypes of OptimalPrePumpEff calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */
#ifndef AMO_LIBRARY_OPTIMALPREPUMPEFF_H
#define AMO_LIBRARY_OPTIMALPREPUMPEFF_H

#include "results/Pump.h"

class OptimalPrePumpEff {
public:
    /**
     * Constructor
     * @param style Pump::Style, style of pump being used.
     * @param achievableEfficiency douuble, pump efficiency at the specified operating conditions as %
     * @param flowRate double, measured or required flow rate in gpm
     */
    OptimalPrePumpEff(
        const Pump::Style style,
        const double achievableEfficiency,
        const double flowRate
    ) :
        achievableEfficiency(achievableEfficiency),
        style(style),
        flowRate(flowRate)
    {};

    /**
     * Calculates the optimal prepump efficiency
     * @return double, optimal prepump efficiency as %
     */
    double calculate();

private:
    const double achievableEfficiency;
    const Pump::Style style;
    const double flowRate;
};


#endif //AMO_LIBRARY_OPTIMALPREPUMPEFF_H
