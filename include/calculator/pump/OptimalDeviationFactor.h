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
    * @param flowRate Rate of flow. Units are gpm, MGD(Million Gallons Per Day), L/s, m^3/hr.
    * @return nothing
    */
    OptimalDeviationFactor(
        double flowRate
    ) :
        flowRate_(flowRate)
    {}

    double calculate();

private:
    double flowRate_;
};


#endif //AMO_LIBRARY_OPTIMALDEVIATIONFACTOR_H
