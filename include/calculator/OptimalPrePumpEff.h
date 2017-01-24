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

#include "../Pump.h"

class OptimalPrePumpEff {
public:
    /**
     * Constructor
     * @param style style Style of pump being used.
     * @param achievableEfficiency Pump efficiency at the specified operating conditions.
     * @param flowRate Measured or required flow rate in units that are consistent with the selection in "Pump Fluid" section.
     * @return nothing
     */
    OptimalPrePumpEff(
        Pump::Style style,
        double achievableEfficiency,
        double flowRate
    ) :
        achievableEfficiency_(achievableEfficiency),
        style_(style),
        flowRate_(flowRate)
    {};

    double calculate();

private:
    double achievableEfficiency_;
    Pump::Style style_;
    double flowRate_;
    double pumpEfficiency = 0.0;
};


#endif //AMO_LIBRARY_OPTIMALPREPUMPEFF_H
