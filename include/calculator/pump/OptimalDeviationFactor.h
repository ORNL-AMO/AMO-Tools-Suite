/**
 * @brief Header file for OptimalDeviationFactor class
 *
 * This contains the prototypes of OptimalDeviationFactor calculator including getters and setters for the important fields.
 *
 * @author Subhankar Mishra (mishras)
 * @author Gina Accawi (accawigk)
 * @bug No known bugs.
 *
 */

#ifndef AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H
#define AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H

class OptimalDeviationFactor {
public:
   /**
    * Constructor
    * @param flowRate double, rate of flow in gpm
    */
    explicit OptimalDeviationFactor(
        double flowRate
    ) :
        flowRate(flowRate)
    {}

    /**
     * Calculates the optimal deviation factor
     * @return double, optimal deviation factor - unitless
     */
    double calculate();

private:
    double flowRate;
};


#endif //AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H
